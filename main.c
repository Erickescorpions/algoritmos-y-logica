#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LETTERS_SIZE 5

void print_matrix(char matrix[5][5]);
FILE *open_file(const char *name, char *mode);
char *read_text_from_file(FILE *file);
char *read_file(const char *file_name);
void write_file(const char *file_name, const char *data);

void get_letters(char letters[LETTERS_SIZE]);
void sort_alphabetically(char letters[LETTERS_SIZE], int n);

void encode_file(char matrix[5][5]);
char *encode(char matrix[5][5], char letters[LETTERS_SIZE], char *data);

void decode_file(char matrix[5][5]);
char *decode(char matrix[5][5], char letters[LETTERS_SIZE], char *data_encoded);

void print_menu(const char *name)
{
    puts("\nOpciones del programa:");
    puts("1. Codificar una cadena");
    puts("2. Decodificar una cadena");
    puts("3. Salir del programa");
    printf("Selecciona una opción (1-3): ");
}

int main()
{
    char matrix[5][5] = {
        {'a', 'b', 'c', 'd', 'e'},
        {'f', 'g', 'h', 'i' /*i o j*/, 'k'},
        {'l', 'm', 'n' /*n o ñ*/, 'o', 'p'},
        {'q', 'r', 's', 't', 'u'},
        {'v', 'w', 'x', 'y', 'z'}};

    char input;
    char name[30];

    puts("Bienvenido al programa de codificación y decodificación de cadenas.\n");
    puts("Consideraciones adicionales:");
    puts("- Para decodificar una cadena, ingresa las mismas 5 letras que usaste para codificarla.");
    puts("- El programa solo leerá la primera línea del archivo con la cadena codificada o sin codificar.\n");

    printf("Por favor, ingresa tu nombre: ");
    scanf("%s", name);
    puts("");

    printf("¡Bienvenido, %s!\n", name);

    do
    {
        print_menu(name);
        scanf(" %c", &input);

        switch (input)
        {
        case '1':
            puts("\nHas seleccionado la opción 1: Codificar una cadena.");
            encode_file(matrix);
            break;
        case '2':
            puts("\nHas seleccionado la opción 2: Decodificar una cadena.");
            decode_file(matrix);
            break;
        case '3':
            puts("\nSaliendo del programa. ¡Hasta luego!");
            break;
        default:
            puts("\n¡Opción inválida! Por favor, selecciona una opción válida (1-3).");
            break;
        }

    } while (input != '3');

    return 0;
}

void print_matrix(char matrix[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%c ", matrix[i][j]);
        }

        printf("\n");
    }
}

FILE *open_file(const char *name, char *mode)
{
    // Puntero para abrir un archivo
    FILE *file = fopen(name, mode);

    if (file == NULL)
    {
        puts("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    return file;
}

char *read_text_from_file(FILE *file)
{
    char *data = malloc(sizeof(char));
    char c;
    int size = 0;

    while ((c = fgetc(file)) != EOF)
    {
        char *new_data = realloc(data, (size + 1) * sizeof(char));
        if (data == NULL)
        {
            puts("Error allocationg memory\n");
            free(data);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        data = new_data;

        new_data[size] = c;
        size++;
    }

    if (data == NULL)
    {
        puts("No data in the file]\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    data = realloc(data, (size + 1) * sizeof(char));
    data[size] = '\0';

    return data;
}

char *read_file(const char *file_name)
{
    FILE *file = open_file(file_name, "r");
    char *data = read_text_from_file(file);
    fclose(file);
    return data;
}

void write_file(const char *file_name, const char *data)
{
    FILE *file = open_file(file_name, "w");
    fprintf(file, "%s", data);
    fclose(file);
}

void get_letters(char letters[LETTERS_SIZE])
{
    puts("Ingresa 5 letras para codificar tu cadena");

    for (int i = 0; i < 5; i++)
    {
        char c;

        do
        {
            printf("Ingresa la letra %d: ", i + 1);
            scanf(" %c", &c);

            if (!isalpha(c))
            {
                printf("Ingresa una letra valida del abecedario, faltan %d letras.\n", (5 - i));
            }

        } while (!isalpha(c));

        letters[i] = c;
    }
}

void sort_alphabetically(char letters[LETTERS_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (letters[j] > letters[j + 1]) {
                char aux = letters[j];
                letters[j] = letters[j + 1];
                letters[j + 1] = aux;
            }
        }
    }
}

void encode_file(char matrix[5][5])
{
    char letters[LETTERS_SIZE];
    get_letters(letters);
    sort_alphabetically(letters, LETTERS_SIZE);

    char file_name[50];
    printf("Ingresa el nombre del archivo donde se encuentra tu cadena sin codificar: ");
    scanf("%s", file_name);

    char *data = read_file(file_name);
    printf("Contenido del archivo: %s Tam: %ld\n", data, strlen(data));
    fflush(stdout);

    char *data_encoded = encode(matrix, letters, data);
    printf("Cadena codificada = %s\n", data_encoded);

    printf("Ingresa el nombre del archivo resultante: ");
    scanf("%s", file_name);
    write_file(file_name, data_encoded);
}

char *encode(char matrix[5][5], char encoder[LETTERS_SIZE], char *data)
{
    int size = strlen(data);
    char *data_encoded = malloc((size + 1) * 2 * sizeof(char));
    int index = 0;

    for (int i = 0; i < size; i++)
    {
        char data_val = tolower(data[i]);
        int car_esp = (data_val == 'j' || strncmp(&data[i], "ñ", 1) == 0);

        // recorremos el alfabeto
        for (int row = 0; row < 5; row++)
        {
            for (int col = 0; col < 5; col++)
            {
                char m_val = matrix[row][col];

                if (car_esp &&
                        (m_val == 'i' && data_val == 'j') ||
                    (m_val == 'n' && strncmp(&data_val, "ñ", 1) == 0))
                {
                    data_encoded[index] = encoder[row];
                    data_encoded[index + 1] = encoder[col];
                    index += 2;
                }
                else if (m_val == data_val)
                {
                    data_encoded[index] = encoder[row];
                    data_encoded[index + 1] = encoder[col];
                    index += 2;
                }
            }
        }
    }

    data_encoded[size * 2] = '\0';

    return data_encoded;
}

void decode_file(char matrix[5][5])
{
    char letters[LETTERS_SIZE];
    get_letters(letters);
    sort_alphabetically(letters, LETTERS_SIZE);

    char file_name[50];
    puts("Ingresa el nombre del archivo donde se encuentra tu cadena codificada: ");
    scanf("%s", file_name);

    char *data_encoded = read_file(file_name);
    printf("Contenido del archivo: %s Tam: %ld\n", data_encoded, strlen(data_encoded));
    fflush(stdout);

    char *data_decoded = decode(matrix, letters, data_encoded);
    printf("Cadena decodificada = %s\n", data_decoded);

    printf("Ingresa el nombre del archivo resultante: ");
    scanf("%s", file_name);
    write_file(file_name, data_decoded);
}

char *decode(char matrix[5][5], char encoder[LETTERS_SIZE], char *data_encoded)
{
    int size = strlen(data_encoded);
    char *data_decoded = malloc((int)((size / 2) + 1) * sizeof(char));
    int index = 0;

    for (int i = 0; i < size; i += 2)
    {
        int row = 0;
        int col = 0;

        for (int j = 0; j < LETTERS_SIZE; j++)
        {
            if (data_encoded[i] == encoder[j])
            {
                row = j;
            }

            if (data_encoded[i + 1] == encoder[j])
            {
                col = j;
            }
        }

        data_decoded[index++] = matrix[row][col];
    }

    data_decoded[index] = '\0';

    return data_decoded;
}