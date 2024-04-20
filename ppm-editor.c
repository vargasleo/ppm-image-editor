#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int R, G, B;
} Pixel;

void convertToGrayscale(Pixel **image, int width, int height)
{
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			int gray = image[i][j].R * 0.3 + image[i][j].G * 0.59 + image[i][j].B * 0.11;
			image[i][j].R = gray;
			image[i][j].G = gray;
			image[i][j].B = gray;
		}
	}
}

void generateNegative(Pixel **image, int width, int height)
{
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			image[i][j].R = 255 - image[i][j].R;
			image[i][j].G = 255 - image[i][j].G;
			image[i][j].B = 255 - image[i][j].B;
		}
	}
}

void adjustBrightness(Pixel **image, int width, int height, float multiplier)
{
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			image[i][j].R = (image[i][j].R * multiplier) > 255 ? 255 : (image[i][j].R * multiplier);
			image[i][j].G = (image[i][j].G * multiplier) > 255 ? 255 : (image[i][j].G * multiplier);
			image[i][j].B = (image[i][j].B * multiplier) > 255 ? 255 : (image[i][j].B * multiplier);
		}
	}
}

void rotateImage(Pixel ***image, int *width, int *height)
{
	int i, j;
	Pixel **newImage = (Pixel **)malloc(*width * sizeof(Pixel *));
	for (i = 0; i < *width; i++)
	{
		newImage[i] = (Pixel *)malloc(*height * sizeof(Pixel));
	}

	for (i = 0; i < *height; i++)
	{
		for (j = 0; j < *width; j++)
		{
			newImage[j][*height - i - 1] = (*image)[i][j];
		}
	}

    for (i = 0; i < *height; i++)
    {
        free((*image)[i]);
    }
    free(*image);

    *image = newImage;

    int temp = *width;
    *width = *height;
    *height = temp;
}

void applyAgingEffect(Pixel **image, int width, int height)
{
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			image[i][j].R = (image[i][j].R - 20) > 0 ? (image[i][j].R - 20) : 0;
			image[i][j].G = (image[i][j].G - 20) > 0 ? (image[i][j].G - 20) : 0;
			image[i][j].B = (image[i][j].B - 20) > 0 ? (image[i][j].B - 20) : 0;
		}
	}
}

int main()
{
	FILE *fp;

	char tipo_img[3];
	int i, j, width, height, valor, r, g, b;
	char filename[256], second_line[256], comment[256];

	printf("Digite o nome do arquivo: ");
	scanf("%s", filename);

	fp = fopen(filename, "r");

	fscanf(fp, "%s", tipo_img);
	printf("Tipo de imagem: %s\n", tipo_img);

	fgets(comment, 256, fp);
	fgets(second_line, 256, fp);
	if (second_line[0] == '#')
	{
		fgets(second_line, 256, fp);
	}

	sscanf(second_line, "%d %d", &width, &height);

	printf("Largura: %d\n", width);
	printf("Altura: %d\n", height);

	if (width < 400 || height < 400)
	{
		printf("Imagem muito pequena. Tamanho minimo: 400x400 px.\n");
		exit(1);
	}

	fscanf(fp, "%d", &valor);
	printf("Limite de intensidade: %d\n", valor);

	Pixel **image = (Pixel **)malloc(height * sizeof(Pixel *));
	for (i = 0; i < height; i++)
	{
		image[i] = (Pixel *)malloc(width * sizeof(Pixel));
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fscanf(fp, "%d", &r);
			fscanf(fp, "%d", &g);
			fscanf(fp, "%d", &b);
			image[i][j].R = r;
			image[i][j].G = g;
			image[i][j].B = b;
		}
	}

	fclose(fp);

	int choice;
	do
	{
		printf("1. Preto e Branco\n");
		printf("2. Negativo\n");
		printf("3. Brilho +\n");
		printf("4. Brilho -\n");
		printf("5. Rotacionar 90 graus\n");
		printf("6. Envelhecimento de imagem\n");
		printf("0. Aplicar Efeito e Encerrar\n");
		printf("Escolha: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			convertToGrayscale(image, width, height);
			break;
		case 2:
			generateNegative(image, width, height);
			break;
		case 3:
			adjustBrightness(image, width, height, 1.25);
			break;
		case 4:
			adjustBrightness(image, width, height, 0.75);
			break;
		case 5:
			rotateImage(&image, &width, &height);
			break;
		case 6:
			applyAgingEffect(image, width, height);
			break;
		}

	} while (choice != 0);

	FILE *fp_novo = fopen("resultado.ppm", "w");
	if (fp_novo == NULL)
	{
		printf("Erro ao criar o arquivo.\n");
		exit(1);
	}

	fprintf(fp_novo, "P3\n");
	fprintf(fp_novo, "%d %d\n", width, height);
	fprintf(fp_novo, "%d\n", valor);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			fprintf(fp_novo, "%d\n%d\n%d\n", image[i][j].R, image[i][j].G, image[i][j].B);
		}
	}

	fclose(fp_novo);

	for (i = 0; i < width; i++)
	{
		free(image[i]);
	}
	free(image);

	printf("Sucesso ao aplicar efeito(s): %s\n", "resultado.ppm");
	return 0;
}
