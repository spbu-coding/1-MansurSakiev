#include <stdio.h>
#include <math.h>
#include <string.h>

#define partitions_count 6

char answer[partitions_count][25];
double l_border, r_border;

double calculate_with_rectangle_method(int n)
{
    double result = 0, sector;
    sector = (r_border - l_border) / n;

    for (int i = 0; i < n; i++)
    {
        result += sin(l_border + sector * (i + 0.5));
    }

    result *= sector;
    return result;
}

double calculate_with_simpson_method(int n)
{
    double x, sector, integral;
    sector = (r_border - l_border) / 2 / n;
    integral = sin(l_border) + sin(r_border);
    x = l_border + sector;
    for (int i = 1; i < 2 * n; i++)
    {
        if (i % 2 == 0) integral += 2 * sin(x);
        else integral += 4 * sin(x);
        x += sector;
    }
    integral *= sector / 3;
    return integral;
}

void entering_numbers()
{
    int borderA = 0, borderB = 0;

    while (!borderB){
        while (!borderA) {
            printf("Enter left border of the interval: ");
            char first_input[20];
            fgets(first_input, 20, stdin);
            int scanning_result = sscanf(first_input, "%lf", &l_border);
            if (scanning_result != 1) {
                printf("Error reading left border value!\n");
                continue;
            }
            if (l_border < 0) {
                printf("Error:Left border must be more than or equal to 0 \n");
                continue;
            } else if (l_border > M_PI) {
                printf("Error: Left border must be less than PI \n");
                continue;
            }
            borderA = 1;
        }

        printf("Enter right border of the interval:");
        char second_input[20];
        fgets(second_input, 20, stdin);
        int scanning_result = sscanf(second_input, "%lf", &r_border);
        if (scanning_result != 1) {
            printf("Error reading right border value!\n");
            continue;
        }

        if (r_border < 0) {
            printf("Error: Right border must be more than 0 \n");
            continue;
        } else if (r_border > M_PI) {
            printf("Error: Right border must be less than PI \n");
            continue;
        }
        if (l_border >= r_border) {
            printf("Error: Right border must be more than left \n");
            continue;
        }
        borderB = 1;
    }
}

void print_to_console(int array[])
{
    char intermediate_line[15];
    for (int i = 0; i < partitions_count; i++)
    {
        double simpson_method, rectangle_method;
        rectangle_method = calculate_with_rectangle_method(array[i]);
        simpson_method = calculate_with_simpson_method(array[i]);
        sprintf(intermediate_line, "%d", array[i]);
        strcat(answer[i], intermediate_line);
        strcat(answer[i], " ");
        sprintf(intermediate_line, "%2.5f", rectangle);
        strcat(answer[i], intermediate_line);
        strcat(answer[i], " ");
        sprintf(intermediate_line, "%2.5f", simpson);
        strcat(answer[i], intermediate_line);
    }
}

int main()
{
    int array[] = { 6, 10, 20, 100, 500, 1000 };
    entering_numbers();
    print_to_console(array);
    for (int i = 0; i < partitions_count; i++)
    {
        printf("%s\n", answer[i]);
    }
    return 0;
}
