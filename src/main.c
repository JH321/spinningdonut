#include <stdio.h>
#include <math.h>
#include <limits.h>

#define MAJOR_RADIUS 12
#define MINOR_RADIUS 6
#define N (MAJOR_RADIUS + MINOR_RADIUS) * 2 + 1
#define PI 3.1415926535897932385

#define GET_POS_X(u, v) (MAJOR_RADIUS + MINOR_RADIUS * cos(v)) * cos(u)
#define GET_POS_Y(u, v) (MAJOR_RADIUS + MINOR_RADIUS * cos(v)) * sin(u)
#define GET_POS_Z(u, v) MINOR_RADIUS * sin(v)

#define ROTATE_X(x, y, z, a, b, c) x * (cos(b) * cos(c)) + y * (sin(a) * sin(b) * cos(c) - cos(a) * sin(c)) + z * (cos(a) * sin(b) * cos(c) + sin(a) * sin(c))
#define ROTATE_Y(x, y, z, a, b, c) x * (cos(b) * sin(c)) + y * (sin(a) * sin(b) * sin(c) + cos(a) * cos(c)) + z * (cos(a) * sin(b) * sin(c) - sin(a) * cos(c))
#define ROTATE_Z(x, y, z, a, b, c) x * (-sin(b)) + y * (sin(a) * cos(b)) + z * (cos(a) * cos(b))

#define GET_ASCII(z) 41 - z

void print_donut(int height_matrix[N][N])
{
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            if(height_matrix[i][j] == INT_MIN)
                fputs(" ", stdout);
            else
                printf("%c", GET_ASCII(height_matrix[i][j]));
        }
        printf("\n");
    }
    printf("\n");
}

void generate_donut(int height_matrix[N][N], float a, float b, float c)
{
    for(float u = 0.0f; u <= 2 * PI; u += 0.01f)
    {
        for(float v = 0.0f; v <= 2 * PI; v += 0.01f)
        {
            int x_real_pos = GET_POS_X(u, v);
            int y_real_pos = GET_POS_Y(u, v);
            int z_real_pos = GET_POS_Z(u, v);

            x_real_pos = ROTATE_X(x_real_pos, y_real_pos, z_real_pos, a, b, c);
            y_real_pos = ROTATE_Y(x_real_pos, y_real_pos, z_real_pos, a, b, c);
            z_real_pos = ROTATE_Z(x_real_pos, y_real_pos, z_real_pos, a, b, c);

            int x = (int) round(x_real_pos) + (MAJOR_RADIUS + MINOR_RADIUS);
            int y = (int) round(y_real_pos) + (MAJOR_RADIUS + MINOR_RADIUS);
            int z = (int) round(z_real_pos);
            //printf("%f %f\n", GET_POS_X(u, v), GET_POS_Y(u, v));
            if(height_matrix[x][y] < z)
                height_matrix[x][y] = z;
        }
    }
}

void reset_height_matrix(int height_matrix[N][N])
{
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            height_matrix[i][j] = INT_MIN;
        }
    }
}

int main(int argc, char** argv)
{
    int height_matrix[N][N];
    float a = 0.0f;
    float b = 0.0f;
    float c = 0.0f;

    float a_increment = 0.1f;
    float b_increment = 0.1f;
    float c_increment = 0.1f;

    while(1)
    {
        reset_height_matrix(height_matrix);
        generate_donut(height_matrix, a, b, c);
        print_donut(height_matrix);
        a += a_increment;
        b += b_increment;
        c += c_increment;
        if(a >= 2 * PI)
            a = 0.0f;
        if(b >= 2 * PI)
            b = 0.0f;
        if(c >= 2 * PI)
            c = 0.0f;
    }

}