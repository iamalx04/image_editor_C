// Copyright, Istrate Alexandru-Daniel, 314CA
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Structura pentru imaginea color
typedef struct {
int red, green, blue;
} matrix_rgb;

int main(void)
{
// definirea variabilelor
int x1 = 0, x2 = 0, y1 = 0, y2 = 0, max_color, max_x = 0, max_y = 0;
int color, **image = NULL, **new_image = NULL, **new_image2 = NULL, valid = 0;
matrix_rgb **image_c = NULL, **new_image_c = NULL;
matrix_rgb **image_filter = NULL, **new_image2_c = NULL;
char option[100], *p, magic_word[3], ignore[1], out_name[100], line[100];
FILE *input = NULL, *output = NULL;
// meniul pentru citirea comenzilor
while (1) {
	// citesc intreaga linie
	fgets(option, 100, stdin);
	// impart linia in cuvinte
	p = strtok(option, " \n");
	if (p) {
		if (strcmp(p, "LOAD") == 0) {
			// optiunea LOAD
			p = strtok(NULL, " \n");
			if (!p) {
				printf("Invalid command\n");
			} else {
				// verific daca exista o imagine incarcata
				if (input) {
					fclose(input);
					input = NULL;
				}
				if (image) {
					for (int i = 0; i < max_y; i++)
						free(image[i]);
					free(image);
					image = NULL;
				}
				if (image_c) {
					for (int i = 0; i < max_y; i++)
						free(image_c[i]);
					free(image_c);
					image_c = NULL;
				}
				input = fopen(p, "r");
				if (!input) {
					printf("Failed to load %s\n", p);
				} else {
					valid = 0;
					while (valid == 0) {
						fgets(line, 100, input);
						if(line[0] != '#') {
							fseek(input, -strlen(line), SEEK_CUR);
							valid = 1;
						}
					}
					fgets(magic_word, 3, input);
					magic_word[2] = '\0';
					if (strcmp(magic_word, "P2") == 0) {
						// incarcarea imaginii grayscale, text
						valid = 0;
						while (valid == 0) {
							fgets(line, 100, input);
							if(line[0] != '#') {
								fseek(input, -strlen(line), SEEK_CUR);
								valid = 1;
							}
						}
						fscanf(input, "%d %d", &max_x, &max_y);
						valid = 0;
						while (valid == 0) {
							fgets(line, 100, input);
							if(line[0] != '#') {
								fseek(input, -strlen(line), SEEK_CUR);
								valid = 1;
							}
						}
						fscanf(input, "%d", &max_color);
						valid = 0;
						while (valid == 0) {
							fgets(line, 100, input);
							if(line[0] != '#') {
								fseek(input, -strlen(line), SEEK_CUR);
								valid = 1;
							}
						}
						image = (int **)malloc(max_y * sizeof(int *));
						if (!image) {
							printf("Failed malloc\n");
							return -1;
						} else {
							for (int i = 0; i < max_y; i++) {
								image[i] = (int *)malloc(max_x * sizeof(int));
								if (!image[i]) {
									printf("Failed malloc\n");
									return -1;
								} else {
									for (int j = 0; j < max_x; j++)
										fscanf(input, "%d", &image[i][j]);
								}
							}
							printf("Loaded %s\n", p);
							color = 0;
						}
					} else if (strcmp(magic_word, "P3") == 0) {
						// incarcarea imaginii color, text
						valid = 0;
						while (valid == 0) {
							fgets(line, 100, input);
							if(line[0] != '#') {
								fseek(input, -strlen(line), SEEK_CUR);
								valid = 1;
							}
						}
						fscanf(input, "%d %d", &max_x, &max_y);
						valid = 0;
						while (valid == 0) {
							fgets(line, 100, input);
							if(line[0] != '#') {
								fseek(input, -strlen(line), SEEK_CUR);
								valid = 1;
							}
						}
						fscanf(input, "%d", &max_color);
						valid = 0;
						while (valid == 0) {
							fgets(line, 100, input);
							if(line[0] != '#') {
								fseek(input, -strlen(line), SEEK_CUR);
								valid = 1;
							}
						}
						image_c = (matrix_rgb **)malloc(max_y * sizeof(matrix_rgb *));
						if (!image_c) {
							printf("Failed malloc\n");
							return -1;
						} else {
							for (int i = 0; i < max_y; i++) {
								image_c[i] = (matrix_rgb *)malloc(max_x * sizeof(matrix_rgb));
								if (!image_c[i]) {
									printf("Failed malloc\n");
									return -1;
								} else {
									for (int j = 0; j < max_x; j++)
										fscanf(input, "%d %d %d", &image_c[i][j].red, &image_c[i][j].green, &image_c[i][j].blue);
								}
							}
							printf("Loaded %s\n", p);
							color = 1;
						}
					} else if (strcmp(magic_word, "P5") == 0) {
						// incarcarea imaginii grayscale, binar
						valid = 0;
						while (valid == 0) {
							fgets(line, 100, input);
							if(line[0] != '#') {
								fseek(input, -strlen(line), SEEK_CUR);
								valid = 1;
							}
						}
						fscanf(input, "%d %d", &max_x, &max_y);
						valid = 0;
						while (valid == 0) {
							fgets(line, 100, input);
							if(line[0] != '#') {
								fseek(input, -strlen(line), SEEK_CUR);
								valid = 1;
							}
						}
						fscanf(input, "%d", &max_color);
						valid = 0;
						while (valid == 0) {
							fgets(line, 100, input);
							if(line[0] != '#') {
								fseek(input, -strlen(line), SEEK_CUR);
								valid = 1;
							}
						}
						image = (int **)malloc(max_y * sizeof(int *));
						if (!image) {
							printf("Failed malloc\n");
							return -1;
						} else {
							for (int i = 0; i < max_y; i++) {
								image[i] = (int *)malloc(max_x * sizeof(int));
								if (!image[i]) {
									printf("Failed malloc\n");
									return -1;
								}
							}
							fscanf(input, "%c", &ignore[0]);
							unsigned char *data_raw = malloc(max_x * max_y * sizeof(unsigned char));
							if (!data_raw) {
								printf("Failed malloc\n");
								return -1;
							} else {
								fread(data_raw, sizeof(unsigned char), max_x * max_y, input);
								int count = 0;
								for (int i = 0; i < max_y; i++)
									for (int j = 0; j < max_x; j++) {
										image[i][j] = (int)data_raw[count];
										count++;
									}
								free(data_raw);
								printf("Loaded %s\n", p);
								color = 0;
							}
						}
					} else if (strcmp(magic_word, "P6") == 0) {
						// incarcarea imaginii color, binar
						valid = 0;
						while (valid == 0) {
							fgets(line, 100, input);
							if(line[0] != '#') {
								fseek(input, -strlen(line), SEEK_CUR);
								valid = 1;
							}
						}
						fscanf(input, "%d %d", &max_x, &max_y);
						valid = 0;
						while (valid == 0) {
							fgets(line, 100, input);
							if(line[0] != '#') {
								fseek(input, -strlen(line), SEEK_CUR);
								valid = 1;
							}
						}
						fscanf(input, "%d", &max_color);
						valid = 0;
						while (valid == 0) {
							fgets(line, 100, input);
							if(line[0] != '#') {
								fseek(input, -strlen(line), SEEK_CUR);
								valid = 1;
							}
						}
						image_c = (matrix_rgb **)malloc(max_y * sizeof(matrix_rgb *));
						if (!image_c) {
							printf("Failed malloc\n");
							return -1;
						} else {
							for (int i = 0; i < max_y; i++) {
								image_c[i] = (matrix_rgb *)malloc(max_x * sizeof(matrix_rgb));
								if (!image_c[i]) {
									printf("Failed malloc\n");
									return -1;
								}
							}
							fscanf(input, "%c", &ignore[0]);
							unsigned char *data_raw = malloc(3 * max_x * max_y * sizeof(unsigned char));
							if (!data_raw) {
								printf("Failed malloc\n");
								return -1;
							} else {
								fread(data_raw, sizeof(unsigned char), 3 * max_x * max_y, input);
								int count = 0;
								for (int i = 0; i < max_y; i++)
									for (int j = 0; j < max_x; j++) {
										image_c[i][j].red = (int)data_raw[count];
										count++;
										image_c[i][j].green = (int)data_raw[count];
										count++;
										image_c[i][j].blue = (int)data_raw[count];
										count++;
									}
								free(data_raw);
								printf("Loaded %s\n", p);
								color = 1;
							}
						}
					}
					// setez coordonatele de selectie pe toata imaginea
					x1 = 0;
					y1 = 0;
					x2 = max_x;
					y2 = max_y;
				}
			}
		} else if (strcmp(p, "SELECT") == 0) {
			if (!input) {
				printf("No image loaded\n");
			} else {
				if (!p) {
					printf("Invalid command\n");
				} else {
					p = strtok(NULL, " \n");
					if (strcmp(p, "ALL") == 0) {
						// selectez toata imaginea
						x1 = 0;
						y1 = 0;
						x2 = max_x;
						y2 = max_y;
						printf("Selected ALL\n");
					} else {
						int x1_new = 0, y1_new = 0, x2_new = 0, y2_new = 0;
						if (atoi(p) == 0 && isdigit(p[0]) == 0) {
							printf("Invalid command\n");
						} else {
							x1_new = atoi(p);
							p = strtok(NULL, " \n");
							if (!p) {
								printf("Invalid command\n");
							} else {
								if (atoi(p) == 0 && isdigit(p[0]) == 0) {
									// verific daca sirul de caractere este numar
									printf("Invalid command\n");
								} else {
									y1_new = atoi(p);
									p = strtok(NULL, " \n");
									if (!p) {
										printf("Invalid command\n");
									} else {
										// verific daca sirul de caractere este numar
										if (atoi(p) == 0 && isdigit(p[0]) == 0) {
											printf("Invalid command\n");
										} else {
											x2_new = atoi(p);
											p = strtok(NULL, " \n");
											if (!p) {
												printf("Invalid command\n");
											} else {
												if (atoi(p) == 0 && isdigit(p[0]) == 0) {
													// verific daca sirul de caractere este numar
													printf("Invalid command\n");
												} else {
													y2_new = atoi(p);
													if (x1_new < 0 || x2_new < 0 || x1_new > max_x || x2_new > max_x || y1_new < 0 || y2_new < 0 || y1_new > max_y || y2_new > max_y) {
														printf("Invalid set of coordinates\n");
													} else if ((x1_new == 0 && x2_new == 0 && y1_new == 0 && y2_new == 0)) {
														printf("Invalid set of coordinates\n");
													} else {
														// ma asigur ca sunt citite coordonatele crescator
														if (x1_new > x2_new) {
															int aux = x1_new;
															x1_new = x2_new;
															x2_new = aux;
														}
														if (y1_new > y2_new) {
															int aux = y1_new;
															y1_new = y2_new;
															y2_new = aux;
														}
														x1 = x1_new;
														y1 = y1_new;
														x2 = x2_new;
														y2 = y2_new;
														if (x1 == x2 || y1 == y2)
															printf("Invalid set of coordinates\n");
														else
															printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		} else if (strcmp(p, "CROP") == 0) {
			// optiunea CROP
			if (!input) {
				printf("No image loaded\n");
			} else {
				int new_dim_y = y2 - y1;
				int new_dim_x = x2 - x1;
				if (color == 0) {
					// decuparea imaginilor grayscale
					new_image = (int **)malloc(new_dim_y * sizeof(int *));
					if (!new_image) {
						printf("Failed malloc\n");
						return -1;
					}
					for (int i = 0; i < new_dim_y; i++) {
						new_image[i] = (int *)malloc(new_dim_x * sizeof(int));
						if (!new_image[i]) {
							printf("Failed malloc\n");
							return -1;
						}
						for (int j = 0; j < new_dim_x; j++)
							new_image[i][j] = image[i + y1][j + x1];
					}
					for (int i = 0; i < max_y; i++)
						free(image[i]);
					free(image);
					image = (int **)malloc(new_dim_y * sizeof(int *));
					if (!image) {
						printf("Failed malloc\n");
						return -1;
					}
					for (int i = 0; i < new_dim_y; i++) {
						image[i] = (int *)malloc(new_dim_x * sizeof(int));
						if (!image[i]) {
							printf("Failed malloc\n");
							return -1;
						}
						for (int j = 0; j < new_dim_x; j++)
							image[i][j] = new_image[i][j];
					}

					for (int i = 0; i < new_dim_y; i++)
						free(new_image[i]);
					free(new_image);

					x1 = 0;
					y1 = 0;
					x2 = new_dim_x;
					y2 = new_dim_y;
					max_x = new_dim_x;
					max_y = new_dim_y;
					printf("Image cropped\n");
				} else {
					// decuparea imaginilor color
					new_image_c = (matrix_rgb **)malloc(new_dim_y * sizeof(matrix_rgb *));
					if (!new_image_c) {
						printf("Failed malloc\n");
						return -1;
					}
					for (int i = 0; i < new_dim_y; i++) {
						new_image_c[i] = (matrix_rgb *)malloc(new_dim_x * sizeof(matrix_rgb));
						if (!new_image_c[i]) {
							printf("Failed malloc\n");
							return -1;
						}
						for (int j = 0; j < new_dim_x; j++) {
							new_image_c[i][j].red = image_c[i + y1][j + x1].red;
							new_image_c[i][j].green = image_c[i + y1][j + x1].green;
							new_image_c[i][j].blue = image_c[i + y1][j + x1].blue;
						}
					}

					for (int i = 0; i < max_y; i++)
						free(image_c[i]);
					free(image_c);

					image_c = (matrix_rgb **)malloc(new_dim_y * sizeof(matrix_rgb *));
					if (!image_c) {
						printf("Failed malloc\n");
						return -1;
					}
					for (int i = 0; i < new_dim_y; i++) {
						image_c[i] = (matrix_rgb *)malloc(new_dim_x * sizeof(matrix_rgb));
						if (!image_c[i]) {
							printf("Failed malloc\n");
							return -1;
						}
						for (int j = 0; j < new_dim_x; j++)
							image_c[i][j] = new_image_c[i][j];
					}
					for (int i = 0; i < new_dim_y; i++)
						free(new_image_c[i]);
					free(new_image_c);

					x1 = 0;
					y1 = 0;
					x2 = new_dim_x;
					y2 = new_dim_y;
					max_x = new_dim_x;
					max_y = new_dim_y;
					printf("Image cropped\n");
				}
			}
		} else if (strcmp(p, "APPLY") == 0) {
			// optiunea APPLY
			p = strtok(NULL, " \n");
			if (!input) {
				printf("No image loaded\n");
			} else if (!p) {
				printf("Invalid command\n");
			} else if (color == 0) {
				printf("Easy, Charlie Chaplin\n");
			} else {
				image_filter = (matrix_rgb **)malloc(max_y * sizeof(matrix_rgb *));
				if (!image_filter) {
					printf("Failed malloc\n");
					return -1;
				}
				for (int i = 0; i < max_y; i++) {
					image_filter[i] = (matrix_rgb *)malloc(max_x * sizeof(matrix_rgb));
					if (!image_filter[i]) {
						printf("Failed malloc\n");
						return -1;
					}
				}
				double suma_red = 0, suma_green = 0, suma_blue = 0;
				if (strcmp(p, "SHARPEN") == 0) {
					// aplic filtrul SHARPEN
					for (int i = y1; i < y2; i++)
						for (int j = x1; j < x2; j++) {
							if (i == 0 || i == max_y - 1 || j == 0 || j == max_x - 1) {
								image_filter[i][j] = image_c[i][j];
							} else {
								suma_red = 0, suma_green = 0, suma_blue = 0;
								suma_red = image_c[i][j].red * 5 + image_c[i - 1][j - 1].red * 0 + image_c[i - 1][j].red * (-1) + image_c[i - 1][j + 1].red * 0 + image_c[i][j + 1].red * (-1) + image_c[i + 1][j + 1].red * 0 + image_c[i + 1][j].red * (-1) + image_c[i + 1][j - 1].red * 0 + image_c[i][j - 1].red * (-1);
								suma_green = image_c[i][j].green * 5 + image_c[i - 1][j - 1].green * 0 + image_c[i - 1][j].green * (-1) + image_c[i - 1][j + 1].green * 0 + image_c[i][j + 1].green * (-1) + image_c[i + 1][j + 1].green * 0 + image_c[i + 1][j].green * (-1) + image_c[i + 1][j - 1].green * 0 + image_c[i][j - 1].green * (-1);
								suma_blue = image_c[i][j].blue * 5 + image_c[i - 1][j - 1].blue * 0 + image_c[i - 1][j].blue * (-1) + image_c[i - 1][j + 1].blue * 0 + image_c[i][j + 1].blue * (-1) + image_c[i + 1][j + 1].blue * 0 + image_c[i + 1][j].blue * (-1) + image_c[i + 1][j - 1].blue * 0 + image_c[i][j - 1].blue * (-1);
								// functia clamp
								if (suma_red > 255)
									suma_red = 255;
								else if (suma_red < 0)
									suma_red = 0;
								if (suma_green > 255)
									suma_green = 255;
								else if (suma_green < 0)
									suma_green = 0;
								if (suma_blue > 255)
									suma_blue = 255;
								else if (suma_blue < 0)
									suma_blue = 0;
								image_filter[i][j].red = (int)suma_red;
								image_filter[i][j].green = (int)suma_green;
								image_filter[i][j].blue = (int)suma_blue;
							}
						}
					for (int i = y1; i < y2; i++)
						for (int j = x1; j < x2; j++)
							image_c[i][j] = image_filter[i][j];

					for (int i = 0; i < max_y; i++)
						free(image_filter[i]);
					free(image_filter);
					printf("APPLY SHARPEN done\n");
				} else if (strcmp(p, "EDGE") == 0) {
					// aplic filtrul EDGE
					for (int i = y1; i < y2; i++)
						for (int j = x1; j < x2; j++) {
							if (i == 0 || i == max_y - 1 || j == 0 || j == max_x - 1) {
								image_filter[i][j] = image_c[i][j];
							} else {
								suma_red = 0, suma_green = 0, suma_blue = 0;
								suma_red = image_c[i][j].red * 8 + image_c[i - 1][j - 1].red * (-1) + image_c[i - 1][j].red * (-1) + image_c[i - 1][j + 1].red * (-1) + image_c[i][j + 1].red * (-1) + image_c[i + 1][j + 1].red * (-1) + image_c[i + 1][j].red * (-1) + image_c[i + 1][j - 1].red * (-1) + image_c[i][j - 1].red * (-1);
								suma_green = image_c[i][j].green * 8 + image_c[i - 1][j - 1].green * (-1) + image_c[i - 1][j].green * (-1) + image_c[i - 1][j + 1].green * (-1) + image_c[i][j + 1].green * (-1) + image_c[i + 1][j + 1].green * (-1) + image_c[i + 1][j].green * (-1) + image_c[i + 1][j - 1].green * (-1) + image_c[i][j - 1].green * (-1);
								suma_blue = image_c[i][j].blue * 8 + image_c[i - 1][j - 1].blue * (-1) + image_c[i - 1][j].blue * (-1) + image_c[i - 1][j + 1].blue * (-1) + image_c[i][j + 1].blue * (-1) + image_c[i + 1][j + 1].blue * (-1) + image_c[i + 1][j].blue * (-1) + image_c[i + 1][j - 1].blue * (-1) + image_c[i][j - 1].blue * (-1);
								// functia clamp
								if (suma_red > 255)
									suma_red = 255;
								else if (suma_red < 0)
									suma_red = 0;
								if (suma_green > 255)
									suma_green = 255;
								else if (suma_green < 0)
									suma_green = 0;
								if (suma_blue > 255)
									suma_blue = 255;
								else if (suma_blue < 0)
									suma_blue = 0;
								image_filter[i][j].red = (int)suma_red;
								image_filter[i][j].green = (int)suma_green;
								image_filter[i][j].blue = (int)suma_blue;
							}
						}
					for (int i = y1; i < y2; i++)
						for (int j = x1; j < x2; j++)
							image_c[i][j] = image_filter[i][j];

					for (int i = 0; i < max_y; i++)
						free(image_filter[i]);
					free(image_filter);
					printf("APPLY EDGE done\n");
				} else if (strcmp(p, "BLUR") == 0) {
					// aplic filtrul BLUR
					for (int i = y1; i < y2; i++)
						for (int j = x1; j < x2; j++) {
							if (i == 0 || i == max_y - 1 || j == 0 || j == max_x - 1) {
								image_filter[i][j] = image_c[i][j];
							} else {
								suma_red = 0, suma_green = 0, suma_blue = 0;
								suma_red = (1.0 / 9) * (image_c[i][j].red * 1 + image_c[i - 1][j - 1].red * 1 + image_c[i - 1][j].red * 1 + image_c[i - 1][j + 1].red * 1 + image_c[i][j + 1].red * 1 + image_c[i + 1][j + 1].red * 1 + image_c[i + 1][j].red * 1 + image_c[i + 1][j - 1].red * 1 + image_c[i][j - 1].red * 1);
								suma_green = (1.0 / 9) * (image_c[i][j].green * 1 + image_c[i - 1][j - 1].green * 1 + image_c[i - 1][j].green * 1 + image_c[i - 1][j + 1].green * 1 + image_c[i][j + 1].green * 1 + image_c[i + 1][j + 1].green * 1 + image_c[i + 1][j].green * 1 + image_c[i + 1][j - 1].green * 1 + image_c[i][j - 1].green * 1);
								suma_blue = (1.0 / 9) * (image_c[i][j].blue * 1 + image_c[i - 1][j - 1].blue * 1 + image_c[i - 1][j].blue * 1 + image_c[i - 1][j + 1].blue * 1 + image_c[i][j + 1].blue * 1 + image_c[i + 1][j + 1].blue * 1 + image_c[i + 1][j].blue * 1 + image_c[i + 1][j - 1].blue * 1 + image_c[i][j - 1].blue * 1);

								// functia clamp
								if (suma_red > 255)
									suma_red = 255;
								else if (suma_red < 0)
									suma_red = 0;
								if (suma_green > 255)
									suma_green = 255;
								else if (suma_green < 0)
									suma_green = 0;
								if (suma_blue > 255)
									suma_blue = 255;
								else if (suma_blue < 0)
									suma_blue = 0;
								image_filter[i][j].red = (int)suma_red;
								image_filter[i][j].green = (int)suma_green;
								image_filter[i][j].blue = (int)suma_blue;
							}
						}
					for (int i = y1; i < y2; i++)
						for (int j = x1; j < x2; j++)
							image_c[i][j] = image_filter[i][j];

					for (int i = 0; i < max_y; i++)
						free(image_filter[i]);
					free(image_filter);
					printf("APPLY BLUR done\n");
				} else if (strcmp(p, "GAUSSIAN_BLUR") == 0) {
					// aplic filtrul GAUSSIAN_BLUR
					for (int i = y1; i < y2; i++)
						for (int j = x1; j < x2; j++) {
							if (i == 0 || i == max_y - 1 || j == 0 || j == max_x - 1) {
								image_filter[i][j] = image_c[i][j];
							} else {
								suma_red = 0, suma_green = 0, suma_blue = 0;
								suma_red = (1.0 / 16) * (image_c[i][j].red * 4 + image_c[i - 1][j - 1].red * 1 + image_c[i - 1][j].red * 2 + image_c[i - 1][j + 1].red * 1 + image_c[i][j + 1].red * 2 + image_c[i + 1][j + 1].red * 1 + image_c[i + 1][j].red * 2 + image_c[i + 1][j - 1].red * 1 + image_c[i][j - 1].red * 2);
								suma_green = (1.0 / 16) * (image_c[i][j].green * 4 + image_c[i - 1][j - 1].green * 1 + image_c[i - 1][j].green * 2 + image_c[i - 1][j + 1].green * 1 + image_c[i][j + 1].green * 2 + image_c[i + 1][j + 1].green * 1 + image_c[i + 1][j].green * 2 + image_c[i + 1][j - 1].green * 1 + image_c[i][j - 1].green * 2);
								suma_blue = (1.0 / 16) * (image_c[i][j].blue * 4 + image_c[i - 1][j - 1].blue * 1 + image_c[i - 1][j].blue * 2 + image_c[i - 1][j + 1].blue * 1 + image_c[i][j + 1].blue * 2 + image_c[i + 1][j + 1].blue * 1 + image_c[i + 1][j].blue * 2 + image_c[i + 1][j - 1].blue * 1 + image_c[i][j - 1].blue * 2);
								// functia clamp
								if (suma_red > 255)
									suma_red = 255;
								else if (suma_red < 0)
									suma_red = 0;
								if (suma_green > 255)
									suma_green = 255;
								else if (suma_green < 0)
									suma_green = 0;
								if (suma_blue > 255)
									suma_blue = 255;
								else if (suma_blue < 0)
									suma_blue = 0;
								image_filter[i][j].red = suma_red;
								image_filter[i][j].green = suma_green;
								image_filter[i][j].blue = suma_blue;
							}
						}
					for (int i = y1; i < y2; i++)
						for (int j = x1; j < x2; j++)
							image_c[i][j] = image_filter[i][j];

					for (int i = 0; i < max_y; i++)
						free(image_filter[i]);
					free(image_filter);
					printf("APPLY GAUSSIAN_BLUR done\n");
				} else {
					printf("APPLY parameter invalid\n");
				}
			}
		} else if (strcmp(p, "HISTOGRAM") == 0) {
			// optiunea HISTOGRAMA
			if (!input) {
				printf("No image loaded\n");
			} else {
				p = strtok(NULL, " \n");
				if (!p) {
					printf("Invalid command\n");
				} else {
					if (color == 1) {
						printf("Black and white image needed\n");
					} else {
						int max_stars = 0, max_bin = 0, step = 0;
						max_stars = atoi(p);
						p = strtok(NULL, " \n");
						if (!p) {
							printf("Invalid command\n");
						} else {
							max_bin = atoi(p);
							p = strtok(NULL, " \n");
							if (p) {
								printf("Invalid command\n");
							} else {
								int frequence[257] = {0};
								// calculez frecventa pixelilor
								for (int i = 0; i < max_y; i++)
									for (int j = 0; j < max_x; j++)
										frequence[image[i][j]]++;
								int max_freq = 0, sum = 0;
								// calculez cati pixeli sa apara intr-un bin
								step = 256 / max_bin;
								/* determin frecventa maxima in raport
								cu bin-urile */
								for (int i = 0; i <= 256; i++) {
									if (i % step == 0) {
										if (sum > max_freq) {
											max_freq = sum;
										}
										sum = frequence[i];
									} else {
										sum = sum + frequence[i];
									}
								}
								sum = frequence[0];
								// afisez histograma
								for (int i = 1; i <= 256; i++) {
									if (i % step == 0) {
										int stars = sum * max_stars / max_freq;
										printf("%d\t|\t", stars);
										for (int j = 0; j < stars; j++)
											printf("*");
										printf("\n");
										sum = frequence[i];
									} else {
										sum = sum + frequence[i];
									}
								}
							}
						}
					}
				}
			}
		} else if (strcmp(p, "EQUALIZE") == 0) {
			// optiunea EQUALIZE
			if (!input) {
				printf("No image loaded\n");
			} else {
				if (color == 1) {
					printf("Black and white image needed\n");
				} else {
					int frequence[257] = {0};
					// determin frecventa pixelilor
					for (int i = 0; i < max_y; i++)
						for (int j = 0; j < max_x; j++)
							frequence[image[i][j]]++;

					double **new_image_eq = (double **)malloc(max_y * sizeof(double *));
					if (!new_image_eq) {
						printf("Failed malloc\n");
						return -1;
					}
					for (int i = 0; i < max_y; i++) {
						new_image_eq[i] = (double *)malloc(max_x * sizeof(double));
						if (!new_image_eq[i]) {
							printf("Failed malloc\n");
							return -1;
						}
					}
					int sum;
					// determin noua valoare a pixelilor
					for (int i = 0; i < max_y; i++)
						for (int j = 0; j < max_x; j++) {
							sum = 0;
							for (int k = 0; k <= image[i][j]; k++)
								sum = sum + frequence[k];
							new_image_eq[i][j] = (255.0 * sum) / (max_x * max_y);
						}

					// mut noua valoare a pixelilor in matricea initiala
					for (int i = 0; i < max_y; i++)
						for (int j = 0; j < max_x; j++)
							image[i][j] = round(new_image_eq[i][j]);

					for (int i = 0; i < max_y; i++)
						free(new_image_eq[i]);
					free(new_image_eq);
					printf("Equalize done\n");
				}
			}
		} else if (strcmp(p, "ROTATE") == 0) { // optiunea ROTATE
			p = strtok(NULL, " \n");
			if (!input) {
				printf("No image loaded\n");
			} else if (!p) {
				printf("Invalid command\n");
			} else if (x1 == 0 && x2 == max_x && y1 == 0 && y2 == max_y) {
				if (color == 0) {
					// rotesc imaginea grayscale
					int unghi = atoi(p);
					if (unghi == 0 || unghi == 360 || unghi == -360) {
						printf("Rotated %d\n", unghi);
					} else if (unghi == -90 || unghi == 270) {
						/* am realizat rotirea la stanga cu 90 de grade
							sau la dreapta cu 270 de grade*/
						new_image = (int **)malloc(max_x * sizeof(int *));
						for (int i = 0; i < max_x; i++)
							new_image[i] = (int *)malloc(max_y * sizeof(int));

						for (int i = 0; i < max_y; i++)
							for (int j = max_x - 1; j >= 0; j--) {
								new_image[max_x - j - 1][i] = image[i][j];
							}

						for (int i = 0; i < max_y; i++)
							free(image[i]);
						free(image);

						image = (int **)malloc(max_x * sizeof(int *));
						for (int i = 0; i < max_x; i++) {
							image[i] = (int *)malloc(max_y * sizeof(int));
							for (int j = 0; j < max_y; j++)
								image[i][j] = new_image[i][j];
						}

						for (int i = 0; i < max_x; i++)
							free(new_image[i]);
						free(new_image);
						int aux = max_x;
						max_x = max_y;
						max_y = aux;
						x1 = 0;
						x2 = 0;
						x2 = max_x;
						y2 = max_y;

						printf("Rotated %d\n", unghi);
					} else if (unghi == 90 || unghi == -270) {
						/* am realizat rotirea la dreapta cu 90 de grade
							sau la stanga cu 270 de grade */
						for (int i = 0; i < 3; i++) {
							new_image = (int **)malloc(max_x * sizeof(int *));
							for (int i = 0; i < max_x; i++)
								new_image[i] = (int *)malloc(max_y * sizeof(int));

							for (int i = 0; i < max_y; i++)
								for (int j = max_x - 1; j >= 0; j--) {
									new_image[max_x - j - 1][i] = image[i][j];
								}

							for (int i = 0; i < max_y; i++)
								free(image[i]);
							free(image);

							image = (int **)malloc(max_x * sizeof(int *));
							for (int i = 0; i < max_x; i++) {
								image[i] = (int *)malloc(max_y * sizeof(int));
								for (int j = 0; j < max_y; j++)
									image[i][j] = new_image[i][j];
							}

							for (int i = 0; i < max_x; i++)
								free(new_image[i]);
							free(new_image);
							int aux = max_x;
							max_x = max_y;
							max_y = aux;
							x2 = max_x;
							y2 = max_y;
						}
						printf("Rotated %d\n", unghi);
					} else if (unghi == 180 || unghi == -180) {
						/* am realizat rotirea cu 180 de grade la
						stanga sau la dreapta */
						for (int i = 0; i < 2; i++) {
							new_image = (int **)malloc(max_x * sizeof(int *));
							for (int i = 0; i < max_x; i++)
								new_image[i] = (int *)malloc(max_y * sizeof(int));

							for (int i = 0; i < max_y; i++)
								for (int j = max_x - 1; j >= 0; j--) {
									new_image[max_x - j - 1][i] = image[i][j];
								}

							for (int i = 0; i < max_y; i++)
								free(image[i]);
							free(image);

							image = (int **)malloc(max_x * sizeof(int *));
							for (int i = 0; i < max_x; i++) {
								image[i] = (int *)malloc(max_y * sizeof(int));
								for (int j = 0; j < max_y; j++)
									image[i][j] = new_image[i][j];
							}

							for (int i = 0; i < max_x; i++)
								free(new_image[i]);
							free(new_image);
							int aux = max_x;
							max_x = max_y;
							max_y = aux;
							x2 = max_x;
							y2 = max_y;
						}
						printf("Rotated %d\n", unghi);
					} else {
						printf("Unsupported rotation angle\n");
					}
				} else {
					// rotesc imagini color
					int unghi = atoi(p);
					if (unghi == 0 || unghi == 360 || unghi == -360) {
						printf("Rotated %d\n", unghi);
					} else if (unghi == -90 || unghi == 270) {
						/* am realizat rotirea la stanga cu 90 de grade
							sau la dreapta cu 270 de grade */
						new_image_c = (matrix_rgb **)malloc(max_x * sizeof(matrix_rgb *));
						for (int i = 0; i < max_x; i++)
							new_image_c[i] = (matrix_rgb *)malloc(max_y * sizeof(matrix_rgb));

						for (int i = 0; i < max_y; i++)
							for (int j = max_x - 1; j >= 0; j--) {
								new_image_c[max_x - j - 1][i] = image_c[i][j];
							}

						for (int i = 0; i < max_y; i++)
							free(image_c[i]);
						free(image_c);

						image_c = (matrix_rgb **)malloc(max_x * sizeof(matrix_rgb *));
						for (int i = 0; i < max_x; i++) {
							image_c[i] = (matrix_rgb *)malloc(max_y * sizeof(matrix_rgb));
							for (int j = 0; j < max_y; j++)
								image_c[i][j] = new_image_c[i][j];
						}

						for (int i = 0; i < max_x; i++)
							free(new_image_c[i]);
						free(new_image_c);
						int aux = max_x;
						max_x = max_y;
						max_y = aux;
						x2 = max_x;
						y2 = max_y;

						printf("Rotated %d\n", unghi);
					} else if (unghi == 90 || unghi == -270) {
						/* am realizat rotirea la dreapta cu 90 de grade
							sau la stanga cu 270 de grade */
						for (int i = 0; i < 3; i++) {
							new_image_c = (matrix_rgb **)malloc(max_x * sizeof(matrix_rgb *));
							for (int i = 0; i < max_x; i++)
								new_image_c[i] = (matrix_rgb *)malloc(max_y * sizeof(matrix_rgb));

							for (int i = 0; i < max_y; i++)
								for (int j = max_x - 1; j >= 0; j--)
									new_image_c[max_x - j - 1][i] = image_c[i][j];

							for (int i = 0; i < max_y; i++)
								free(image_c[i]);
							free(image_c);

							image_c = (matrix_rgb **)malloc(max_x * sizeof(matrix_rgb *));
							for (int i = 0; i < max_x; i++) {
								image_c[i] = (matrix_rgb *)malloc(max_y * sizeof(matrix_rgb));
								for (int j = 0; j < max_y; j++)
									image_c[i][j] = new_image_c[i][j];
							}

							for (int i = 0; i < max_x; i++)
								free(new_image_c[i]);
							free(new_image_c);
							int aux = max_x;
							max_x = max_y;
							max_y = aux;
							x2 = max_x;
							y2 = max_y;
						}
						printf("Rotated %d\n", unghi);
					} else if (unghi == 180 || unghi == -180) {
						/* am realizat rotirea cu 180 de grade la
						stanga sau la dreapta */
						for (int i = 0; i < 2; i++) {
							new_image_c = (matrix_rgb **)malloc(max_x * sizeof(matrix_rgb *));
							for (int i = 0; i < max_x; i++)
								new_image_c[i] = (matrix_rgb *)malloc(max_y * sizeof(matrix_rgb));

							for (int i = 0; i < max_y; i++)
								for (int j = max_x - 1; j >= 0; j--)
									new_image_c[max_x - j - 1][i] = image_c[i][j];
							for (int i = 0; i < max_y; i++)
								free(image_c[i]);
							free(image_c);

							image_c = (matrix_rgb **)malloc(max_x * sizeof(matrix_rgb *));
							for (int i = 0; i < max_x; i++) {
								image_c[i] = (matrix_rgb *)malloc(max_y * sizeof(matrix_rgb));
								for (int j = 0; j < max_y; j++)
									image_c[i][j] = new_image_c[i][j];
							}

							for (int i = 0; i < max_x; i++)
								free(new_image_c[i]);
							free(new_image_c);
							int aux = max_x;
							max_x = max_y;
							max_y = aux;
							x2 = max_x;
							y2 = max_y;
						}

						printf("Rotated %d\n", unghi);
					} else {
						printf("Unsupported rotation angle\n");
					}
				}
			} else if ((x2 - x1) != (y2 - y1)) {
				/* in cazul in care nu am selectat toata poza,
				verific daca selectia este patrata */
				printf("The selection must be square\n");
			} else {
				int dim = x2 - x1;
				if (color == 0) {
					// rotesc secvente de imagini grayscale
					int unghi = atoi(p);
					if (unghi == 0 || unghi == 360 || unghi == -360) {
						printf("Rotated %d\n", unghi);
					} else if (unghi == -90 || unghi == 270) {
						/* am realizat rotirea la stanga cu 90 de grade
							sau la dreapta cu 270 de grade */
						new_image = (int **)malloc(dim * sizeof(int *));
						for (int i = 0; i < dim; i++)
							new_image[i] = (int *)malloc(dim * sizeof(int));

						for (int i = 0; i < dim; i++)
							for (int j = 0; j < dim; j++)
								new_image[i][j] = image[i + y1][j + x1];

						new_image2 = (int **)malloc(dim * sizeof(int *));
						for (int i = 0; i < dim; i++)
							new_image2[i] = (int *)malloc(dim * sizeof(int));

						for (int i = 0; i < dim; i++)
							for (int j = dim - 1; j >= 0; j--)
								new_image2[dim - j - 1][i] = new_image[i][j];

						for (int i = 0; i < dim; i++)
							for (int j = 0; j < dim; j++)
								image[i + y1][j + x1] = new_image2[i][j];

						for (int i = 0; i < dim; i++)
							free(new_image[i]);
						free(new_image);

						for (int i = 0; i < dim; i++)
							free(new_image2[i]);
						free(new_image2);

						printf("Rotated %d\n", unghi);
					} else if (unghi == 90 || unghi == -270) {
						/* am realizat rotirea la dreapta cu 90 de grade
							sau la stanga cu 270 de grade */
						for (int i = 0; i < 3; i++) {
							new_image = (int **)malloc(dim * sizeof(int *));
							for (int i = 0; i < dim; i++)
								new_image[i] = (int *)malloc(dim * sizeof(int));

							for (int i = 0; i < dim; i++)
								for (int j = 0; j < dim; j++)
									new_image[i][j] = image[i + y1][j + x1];

							new_image2 = (int **)malloc(dim * sizeof(int *));
							for (int i = 0; i < dim; i++)
								new_image2[i] = (int *)malloc(dim * sizeof(int));

							for (int i = 0; i < dim; i++)
								for (int j = dim - 1; j >= 0; j--)
									new_image2[dim - j - 1][i] = new_image[i][j];

							for (int i = 0; i < dim; i++)
								for (int j = 0; j < dim; j++)
									image[i + y1][j + x1] = new_image2[i][j];

							for (int i = 0; i < dim; i++)
								free(new_image[i]);
							free(new_image);

							for (int i = 0; i < dim; i++)
								free(new_image2[i]);
							free(new_image2);
						}
						printf("Rotated %d\n", unghi);
					} else if (unghi == 180 || unghi == -180) {
						/* am realizat rotirea cu 180 de grade la
						stanga sau la dreapta */
						for (int i = 0; i < 2; i++) {
							new_image = (int **)malloc(dim * sizeof(int *));
							for (int i = 0; i < dim; i++)
								new_image[i] = (int *)malloc(dim * sizeof(int));

							for (int i = 0; i < dim; i++)
								for (int j = 0; j < dim; j++)
									new_image[i][j] = image[i + y1][j + x1];

							new_image2 = (int **)malloc(dim * sizeof(int *));
							for (int i = 0; i < dim; i++)
								new_image2[i] = (int *)malloc(dim * sizeof(int));

							for (int i = 0; i < dim; i++)
								for (int j = dim - 1; j >= 0; j--)
									new_image2[dim - j - 1][i] = new_image[i][j];

							for (int i = 0; i < dim; i++)
								for (int j = 0; j < dim; j++)
									image[i + y1][j + x1] = new_image2[i][j];

							for (int i = 0; i < dim; i++)
								free(new_image[i]);
							free(new_image);

							for (int i = 0; i < dim; i++)
								free(new_image2[i]);
							free(new_image2);
						}
						printf("Rotated %d\n", unghi);
					} else {
						printf("Unsupported rotation angle\n");
					}
				} else {
					// rotesc secvente de imagini color
					int unghi = atoi(p);
					if (unghi == 0 || unghi == 360 || unghi == -360) {
						printf("Rotated %d\n", unghi);
					} else if (unghi == -90 || unghi == 270) {
						/* am realizat rotirea la stanga cu 90 de grade
							sau la dreapta cu 270 de grade */
						new_image_c = (matrix_rgb **)malloc(dim * sizeof(matrix_rgb *));
						for (int i = 0; i < dim; i++)
							new_image_c[i] = (matrix_rgb *)malloc(dim * sizeof(matrix_rgb));

						for (int i = 0; i < dim; i++)
							for (int j = 0; j < dim; j++)
								new_image_c[i][j] = image_c[i + y1][j + x1];

						new_image2_c = (matrix_rgb **)malloc(dim * sizeof(matrix_rgb *));
						for (int i = 0; i < dim; i++)
							new_image2_c[i] = (matrix_rgb *)malloc(dim * sizeof(matrix_rgb));

						for (int i = 0; i < dim; i++)
							for (int j = dim - 1; j >= 0; j--)
								new_image2_c[dim - j - 1][i] = new_image_c[i][j];

						for (int i = 0; i < dim; i++)
							for (int j = 0; j < dim; j++)
								image_c[i + y1][j + x1] = new_image2_c[i][j];

						for (int i = 0; i < dim; i++)
							free(new_image_c[i]);
						free(new_image_c);

						for (int i = 0; i < dim; i++)
							free(new_image2_c[i]);
						free(new_image2_c);

						printf("Rotated %d\n", unghi);
					} else if (unghi == 90 || unghi == -270) {
						/* am realizat rotirea la dreapta cu 90 de grade
							sau la stanga cu 270 de grade */
						for (int i = 0; i < 3; i++) {
							new_image_c = (matrix_rgb **)malloc(dim * sizeof(matrix_rgb *));
							for (int i = 0; i < dim; i++)
								new_image_c[i] = (matrix_rgb *)malloc(dim * sizeof(matrix_rgb));

							for (int i = 0; i < dim; i++)
								for (int j = 0; j < dim; j++)
									new_image_c[i][j] = image_c[i + y1][j + x1];

							new_image2_c = (matrix_rgb **)malloc(dim * sizeof(matrix_rgb *));
							for (int i = 0; i < dim; i++)
								new_image2_c[i] = (matrix_rgb *)malloc(dim * sizeof(matrix_rgb));

							for (int i = 0; i < dim; i++)
								for (int j = dim - 1; j >= 0; j--)
									new_image2_c[dim - j - 1][i] = new_image_c[i][j];

							for (int i = 0; i < dim; i++)
								for (int j = 0; j < dim; j++)
									image_c[i + y1][j + x1] = new_image2_c[i][j];

							for (int i = 0; i < dim; i++)
								free(new_image_c[i]);
							free(new_image_c);

							for (int i = 0; i < dim; i++)
								free(new_image2_c[i]);
							free(new_image2_c);
						}
						printf("Rotated %d\n", unghi);
					} else if (unghi == 180 || unghi == -180) {
						/* am realizat rotirea cu 180 de grade la
						stanga sau la dreapta */
						for (int i = 0; i < 2; i++) {
							new_image_c = (matrix_rgb **)malloc(dim * sizeof(matrix_rgb *));
							for (int i = 0; i < dim; i++)
								new_image_c[i] = (matrix_rgb *)malloc(dim * sizeof(matrix_rgb));

							for (int i = 0; i < dim; i++)
								for (int j = 0; j < dim; j++)
									new_image_c[i][j] = image_c[i + y1][j + x1];

							new_image2_c = (matrix_rgb **)malloc(dim * sizeof(matrix_rgb *));
							for (int i = 0; i < dim; i++)
								new_image2_c[i] = (matrix_rgb *)malloc(dim * sizeof(matrix_rgb));

							for (int i = 0; i < dim; i++)
								for (int j = dim - 1; j >= 0; j--)
									new_image2_c[dim - j - 1][i] = new_image_c[i][j];

							for (int i = 0; i < dim; i++)
								for (int j = 0; j < dim; j++)
									image_c[i + y1][j + x1] = new_image2_c[i][j];

							for (int i = 0; i < dim; i++)
								free(new_image_c[i]);
							free(new_image_c);

							for (int i = 0; i < dim; i++)
								free(new_image2_c[i]);
							free(new_image2_c);
						}
						printf("Rotated %d\n", unghi);
					} else {
						printf("Unsupported rotation angle\n");
					}
				}
			}
		} else if (strcmp(p, "SAVE") == 0) {
			// optiunea SAVE
			if (!input) {
				printf("No image loaded\n");
			} else {
				p = strtok(NULL, " \n");
				if (!p) {
					printf("Invalid command");
				} else {
					strcpy(out_name, p);
					p = strtok(NULL, " \n");
					if (!p) {
						output = fopen(out_name, "wb");
						if (!output) {
							printf("Failed load output\n");
						} else {
							// salvez imaginea grayscale binar
							if (color == 0) {
								fprintf(output, "P5\n");
								fprintf(output, "%d %d\n", max_x, max_y);
								fprintf(output, "%d\n", max_color);
								for (int i = 0; i < max_y; i++)
									for (int j = 0; j < max_x; j++) {
										unsigned char aux = image[i][j];
										fwrite(&aux, sizeof(unsigned char), 1, output);
									}
								printf("Saved %s\n", out_name);
								fclose(output);
							} else {
								// salvez imaginea color binar
								fprintf(output, "P6\n");
								fprintf(output, "%d %d\n", max_x, max_y);
								fprintf(output, "%d\n", max_color);
								for (int i = 0; i < max_y; i++)
									for (int j = 0; j < max_x; j++) {
										unsigned char aux = image_c[i][j].red;
										fwrite(&aux, sizeof(unsigned char), 1, output);
										aux = image_c[i][j].green;
										fwrite(&aux, sizeof(unsigned char), 1, output);
										aux = image_c[i][j].blue;
										fwrite(&aux, sizeof(unsigned char), 1, output);
									}
								printf("Saved %s\n", out_name);
								fclose(output);
							}
						}
					} else if (strcmp(p, "ascii") == 0) {
						output = fopen(out_name, "w");
						if (!output) {
							printf("Failed load output\n");
						} else {
							if (color == 0) {
								// salvez imaginea grayscale ascii
								fprintf(output, "P2\n");
								fprintf(output, "%d %d\n", max_x, max_y);
								fprintf(output, "%d\n", max_color);
								for (int i = 0; i < max_y; i++) {
									for (int j = 0; j < max_x; j++) {
										unsigned char aux = image[i][j];
										fprintf(output, "%hhu ", aux);
									}
									fprintf(output, "\n");
								}
								printf("Saved %s\n", out_name);
								fclose(output);
							} else {
								// salvez imaginea color ascii
								fprintf(output, "P3\n");
								fprintf(output, "%d %d\n", max_x, max_y);
								fprintf(output, "%d\n", max_color);
								for (int i = 0; i < max_y; i++) {
									for (int j = 0; j < max_x; j++) {
										unsigned char aux = image_c[i][j].red;
										fprintf(output, "%hhu ", aux);
										aux = image_c[i][j].green;
										fprintf(output, "%hhu ", aux);
										aux = image_c[i][j].blue;
										fprintf(output, "%hhu ", aux);
									}
									fprintf(output, "\n");
								}
								printf("Saved %s\n", out_name);
								fclose(output);
							}
						}
					} else {
						printf("Invalid command\n");
					}
				}
			}
		} else if (strcmp(p, "EXIT") == 0) {
			break;
		} else {
			printf("Invalid command\n");
		}
	}
}

// eliberez resursele la finalul programului daca acestea nu au fost eliberate
if (input)
	fclose(input);
else
	printf("No image loaded\n");

if (image) {
	for (int i = 0; i < max_y; i++)
		free(image[i]);
	free(image);
} else {
	free(image);
}

if (image_c) {
	for (int i = 0; i < max_y; i++)
		free(image_c[i]);
	free(image_c);
} else {
	free(image_c);
}

return 0;
}
