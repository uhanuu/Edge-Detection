#include <stdio.h>
typedef unsigned char byte;
#include <memory.h>
#include <math.h>

byte clamping(int,int);
// byte clamping1(int);
byte threshold (byte);

int main()
{

    int width = 640;
    int height = 480;
    byte size[480][640];
    byte head[1078];
    FILE *fp1 = fopen("city.bmp", "rb");
    fseek(fp1, 1078, SEEK_SET);
    fread(size, sizeof(byte), width * height, fp1);
    fclose(fp1);
    byte out1[480][640];



    // 초기화
    memset(out1, 0, sizeof(out1));


    // 수평방향
    int sobelHeight[3][3] = {{1, 0, -1},
                             {2, 0, -2},
                             {1, 0, -1}};

    // 수직방향
    int sobelWidth[3][3] = {{1, 2, 1},
                            {0, 0, 0},
                            {-1, -2, -1}};

    int sobelHeightSum = 0;
    int sobelWidthSum = 0;


    for (int i = 1; i < height; i++)
    {
        for (int j = 1; j < width; j++)
        {
            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    sobelHeightSum += size[i - 1 + y][j - 1 + x] * sobelHeight[y][x];
                    sobelWidthSum += size[i - 1 + y][j - 1 + x] * sobelWidth[y][x];

                }
            }
            out1[i][j] = clamping(sobelHeightSum, sobelWidthSum);
            out1[i][j] = threshold(out1[i][j]);


            sobelHeightSum = 0;
            sobelWidthSum = 0;
        }
    }


    fp1 = fopen("city.bmp", "rb");
    fread(head, sizeof(char), 1078, fp1);
    fclose(fp1);

    FILE *fp2 = fopen("sobelCity.bmp", "wb");
    fwrite(head, sizeof(char), 1078, fp2);
    fwrite(out1, sizeof(char), width * height, fp2);
    fclose(fp2);

    return 0;
}

byte clamping(int valueX, int valueY)
{
    int result;
    result = (int)sqrt((valueX*valueX)+(valueY*valueY));
    result = (result>255) ? 255:result;
    return (byte)result;
}

byte threshold (byte value){
    byte th;
    if(value > 120) return 255;
    else return 0;
}

// byte clamping1(int value){
//     // 제곱 루트 -> 곱셈 연산량 많아서 사용 안함
//     int result;

//     if (value > 255)
//         result = 255;
//     else if (value < 0)
//         result = 0;
//     else
//         result = value;

//     return (byte)result;
// }
