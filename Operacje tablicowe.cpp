//Konrad Sitek

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int* inputRow(int n)
{
    int* tmp = malloc((n + 1) * sizeof(*tmp) );
    *tmp = n;
    int i;
    for (i = 0; i < n; ++i)
    {
        scanf(" %d", tmp + i + 1);
    }

    return tmp;

}

void swapRow(int** row1, int** row2)
{
    int* tmp = *row1;
    *row1 = *row2;
    *row2 = tmp;
}


void swapElement(int* element1, int* element2)
{
    int tmp = *element1;
    *element1 = *element2;
    *element2 = tmp;
}


int** addRow(int** arr, int* row, int position, int* height)
{

    if (*height == 0)
    {
        arr = malloc(1 * sizeof(*arr));
        *arr = row;
    }
    else
    {
        arr = realloc(arr, (*height+1) * sizeof(*arr));
        *(arr+*height) = row;

        int i;

        for(i = *height ; i > position ; --i) swapRow(&(*(arr + i)), &(*(arr + i-1)));

    }

    *height += 1;

    return arr;

}


int** removeRow(int** arr, int position, int* height)
{
    int i;
    if (*height <= 0) return arr;
    else
    {
        if(position < *height)
        {

            for(i = position ; i  < *height-1 ;i++)
            {
                swapRow(&(*(arr+i)), &(*(arr+i+1)));
            }
            free(*(arr+i));
            *height-=1;
            arr = realloc(arr,*height*sizeof(*arr));
        }

    }

    return arr;


}


int* addElement(int* row, int element, int position)
{
    if (position < 0) return row;

    int size = *row;

    if (position >= size) position = size;

    row = realloc(row, (size + 2) * sizeof(*row));

    int i;



    for(i = size ; i > position ; --i)
    {
        swapElement(row+i+1,row+i);
    }

    *(row+i+1) = element;
    *row += 1;

    return row;

}

int* removeElement(int* row, int position)
{
    if (position >= *row) return row;

    int i;

    for (i = position; i < *row - 1; ++i)
    {
        swapElement(row + i + 1, row + i + 2);
    }

    *row -= 1;

    return realloc(row, (*row+1) * sizeof(*row));



}

int* unR2R(int* row1, int* row2, int position)
{

    int i = position;

    while (*row2 != 0)
    {
        row1 = addElement(row1, *(row2 + 1), i);
        row2 = removeElement(row2, 0);
        i++;

    }
    free(row2);

    return row1;


}

int** afc(int** arr, int h, int* height)
{
    if (h <= 0) return arr;


    int i = 0, element;
    int* row;
    while (i < h)
    {

        scanf("%d", &element);

        if (i >= *height)
        {
            row = malloc(sizeof(*row) * 1);
            *row = 0;
            arr = addRow(arr, row, i, height);
        }

        *(arr + i) = addElement(*(arr + i), element, 0);

        ++i;
    }

    return arr;
}

int** alc(int** arr, int h, int* height)
{
    if (h <= 0) return arr;

    int i = 0, element;
    int* row;
    while (i < h)
    {

        scanf("%d", &element);

        if (i >= *height)
        {
            row = malloc(sizeof(*row) * 1);
            *row = 0;
            arr = addRow(arr, row, i, height);
        }

        *(arr + i) = addElement(*(arr + i), element, *(*(arr + i) + 0));

        ++i;
    }

    return arr;

}

int** afr(int** arr, int n, int* height)
{
    if (n <= 0) return arr;

    return addRow(arr, inputRow(n), 0, height);
}

int** alr(int** arr, int n, int* height)
{
    if (n <= 0) return arr;

    return addRow(arr, inputRow(n), *height, height);
}

int** dlr(int** arr, int* height)
{
    if (*height <= 0) return arr;

    return removeRow(arr, *height - 1, height);
}

int** dfr(int** arr, int* height)
{
    if (*height <= 0) return arr;

    return removeRow(arr, 0, height);
}

int** rmr(int** arr, int position, int* height)
{
    if (*height <= 0 || position >= *height) return arr;

    return removeRow(arr, position, height);
}

int** swr(int** arr, int r, int s, int* height)
{
    if (r >= *height || s >= *height || r==s) return arr;


    swapRow(&(*(arr + r)), &(*(arr + s)));
    return arr;
}

int** ibr(int** arr, int position, int w, int* height)
{
    if (w <= 0) return arr;

    if (position >= *height) return arr;
    else
    {
        return addRow(arr, inputRow(w), position, height);
    }
}

int** iar(int** arr, int position, int w, int* height)
{
    if (w <= 0) return arr;


    if (position >= *height) return arr;
    else
    {
        return addRow(arr, inputRow(w), position + 1, height);
    }
}

int** swc(int** arr, int c, int d, int* height)
{

    int i;
    int size;
    for (i = 0; i < *height; i++)
    {
        size = *(*(arr + i) + 0);

        if (c < size && d < size)
        {
            swapElement(&(*(*(arr + i) + c + 1)), &(*(*(arr + i) + d + 1)));
        }
    }

    return arr;
}

int** dfc(int** arr, int* height)
{

    if (*height <= 0) return arr;


    int i;

    for (i = 0; i < *height; i++) *(arr + i) = removeElement(*(arr + i), 0);


    for (i = 0; i < *height; i++)
    {
        if (*(*(arr + i) + 0) == 0)
        {
            arr = removeRow(arr, i, height);
            i--;
        }
    }

    return arr;
}

int** dlc(int** arr, int* height)
{
    if (*height <= 0) return arr;

    int i;

    for (i = 0; i < *height; i++) *(arr + i) = removeElement(*(arr + i), *(*(arr + i) + 0) - 1);


    for (i = 0; i < *height; i++)
    {
        if (*(*(arr + i) + 0) == 0)
        {
            arr = removeRow(arr, i, height);
            i--;
        }
    }


    return arr;
}

int** ibc(int** arr, int c, int h, int* height)
{
    if (h <= 0) return arr;

    int i;
    int element = 0;

    for (i = 0; i < h; i++)
    {
        if (i >= *height)
        {
            arr = addRow(arr, inputRow(1), i, height);
        }
        else
        {

            scanf("%d", &element);

            if (*(*(arr + i) + 0) < c)
            {
                *(arr + i) = addElement(*(arr + i), element, *(*(arr + i) + 0));
            }
            else
            {
                *(arr + i) = addElement(*(arr + i), element, c);
            }

        }
    }

    return arr;

}


int** iac(int** arr, int c, int h, int* height)
{
    if (h <= 0) return arr;

    int i = 0;
    int element;
    for (i = 0; i < h; i++)
    {
        if (i >= *height)
        {
            arr = addRow(arr, inputRow(1), i, height);
        }
        else
        {

            scanf("%d", &element);

            if (*(*(arr + i) + 0) < c)
            {
                *(arr + i) = addElement(*(arr + i), element, *(*(arr + i) + 0));
            }
            else
            {
                *(arr + i) = addElement(*(arr + i), element, c + 1);
            }

        }
    }

    return arr;

}


int** rmc(int** arr, int c, int* height)
{

    int i;
    for (i = 0; i < *height; i++)
    {
        if (*(*(arr + i) + 0) > c)
        {
            *(arr + i) = removeElement(*(arr + i), c);
        }
    }

    for (i = 0; i < *height; i++)
    {
        if (*(*(arr + i) + 0) == 0)
        {
            arr = removeRow(arr, i, height);
            i--;
        }
    }

    return arr;
}


int** rmb(int** arr, int r, int h, int c, int w, int* height)
{
    int i, x;
    for (i = r; i < *height; i++)
    {

        if (i >= r + h) break;

        x = 0;

        while (*(*(arr + i) + 0) != 0)
        {
            if (x == w) break;

            *(arr + i) = removeElement(*(arr + i), c);
            x++;
        }
    }

    for (i = 0; i < *height; i++)
    {
        if (*(*(arr + i) + 0) == 0)
        {
            arr = removeRow(arr, i, height);
            i--;
        }
    }

    return arr;
}


int** isb(int** arr, int r, int c, int h, int w, int* height)
{
    int i;
    int* row;

    for (i = r; i < h + r; i++)
    {
        row = inputRow(w);

        if (i >= *height)
        {

            arr = addRow(arr, row, *height, height);
        }
        else
        {
            *(arr + i) = unR2R(*(arr + i), row, c);

        }
    }

    return arr;
}

int bigEndInt(int num)
{
    int new = (((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000));

    return new;
}

unsigned short bigEndUs(unsigned short num)
{
    unsigned short new = ((num>>8) | (num<<8));

    return new;

}



int main()
{
    int height = 0;

    char* operation = malloc(4);

    int** arr;


    int n, h, r, w, c, s, d, i, j, rowL;


    while(1)
    {
        scanf("%s", operation);


        if (strcmp(operation, "AFR") == 0)
        {

            scanf("%d", &n);
            arr = afr(arr, n, &height);
        }
        else if (strcmp(operation, "ALR") == 0)
        {

            scanf("%d", &n);
            arr = alr(arr, n, &height);

        }
        else if (strcmp(operation, "AFC") == 0)
        {

            scanf("%d", &h);
            arr = afc(arr, h, &height);

        }
        else if (strcmp(operation, "ALC") == 0)
        {
            scanf("%d", &h);
            arr = alc(arr, h, &height);
        }
        else if (strcmp(operation, "IBR") == 0)
        {
            scanf("%d", &r);
            scanf("%d", &w);
            arr = ibr(arr, r, w, &height);

        }
        else if (strcmp(operation, "IAR") == 0)
        {
            scanf("%d", &r);
            scanf("%d", &w);
            arr = iar(arr, r, w, &height);

        }
        else if (strcmp(operation, "IBC") == 0)
        {

            scanf("%d", &c);
            scanf("%d", &h);

            arr = ibc(arr, c, h, &height);

        }
        else if (strcmp(operation, "IAC") == 0)
        {

            scanf("%d", &c);
            scanf("%d", &h);

            arr = iac(arr, c, h, &height);

        }
        else if (strcmp(operation, "SWR") == 0)
        {

            scanf("%d", &r);
            scanf("%d", &s);

            arr = swr(arr, r, s, &height);
        }
        else if (strcmp(operation, "SWC") == 0)
        {
            scanf("%d", &c);
            scanf("%d", &d);
            arr = swc(arr, c, d, &height);

        }
        else if (strcmp(operation, "DFR") == 0)
        {
            arr = dfr(arr, &height);


        }
        else if (strcmp(operation, "DLR") == 0)
        {
            arr = dlr(arr, &height);

        }
        else if (strcmp(operation, "DFC") == 0)
        {
            arr = dfc(arr, &height);

        }
        else if (strcmp(operation, "DLC") == 0)
        {
            arr = dlc(arr, &height);

        }
        else if (strcmp(operation, "RMR") == 0)
        {
            scanf("%d", &n);
            arr = rmr(arr, n, &height);


        }
        else if (strcmp(operation, "RMC") == 0)
        {

            scanf("%d", &c);
            arr = rmc(arr, c, &height);

        }
        else if (strcmp(operation, "RMB") == 0)
        {

            scanf("%d", &r);
            scanf("%d", &h);
            scanf("%d", &c);
            scanf("%d", &w);

            arr = rmb(arr, r, h, c, w, &height);

        }
        else if (strcmp(operation, "ISB") == 0)
        {

            scanf(" %d", &r);
            scanf(" %d", &c);
            scanf(" %d", &h);
            scanf( " %d", &w);

            arr = isb(arr, r, c, h, w, &height);


        }
        else if (strcmp(operation, "WRF") == 0)
        {
            char* name = malloc(256);
            int i,j;
            scanf("%s" , name);

            FILE* file = fopen(name,"wb");
            fprintf(file,"%d\n", height);


            for(i = 0 ; i < height ; ++i)
            {

                 unsigned short size = bigEndUs((unsigned short) *(*(arr + i) + 0));
                 fwrite(&size,sizeof(unsigned short ),1,file);

                for(j = 1 ; j <= *(*(arr + i) + 0) ; ++j)
                {

                    int element = bigEndInt(*(*(arr + i) + j ));
                    fwrite(&element, sizeof(int) , 1 ,file);
                }

            }

            fclose(file);
            free(name);



        }
        else if (strcmp(operation, "RDF") == 0)
        {

            int size = height,i,j,element;
            unsigned short row = 0, column = 0;
            unsigned char c;

            for(i = 0 ; i < size ; i++) free(*(arr+i));

            if(height > 0 ) free(arr);

            height = 0;

             char* name = malloc(256);

             scanf("%s" , name);

             FILE* file = fopen(name, "rb");



             while(1)
             {
                fread(&c,sizeof(char),1,file);
                if(c == '\n') break;
                row *= 10;
                row += c-'0';
             }


             height = row;

            arr = malloc(height * sizeof(*arr));


            for(i = 0 ; i < height ; i++)
            {
                fread(&column,sizeof(unsigned short),1,file);
                column = (int)(bigEndUs(column));

                 *(arr+i) = malloc((column+1) * sizeof(**arr));
                 *(*(arr+i)+0) = column;


                for(j = 1 ; j <= column;j++)
                {
                    fread(&element,sizeof(int),1,file);
                    element = bigEndInt(element);
                     *(*(arr+i)+j) = element;

                }

            }

            fclose(file);
            free(name);

        }
        else if (strcmp(operation, "PRT") == 0)
        {


            printf("%d\n", height);


            for (i = 0; i < height; ++i)
            {
                rowL = *(*(arr + i) + 0);

                printf("%d", rowL);
                for (j = 0; j < rowL; j++)
                {
                    printf(" %d", *(*(arr + i) + j + 1));

                }

                printf("%s", "\n");

            }

        }
        else if (strcmp(operation, "END") == 0)
        {


            int i;
            int size = height;

            for(i = 0 ; i < size ; i++) free(*(arr+i));

            if(height > 0 ) free(arr);

            break;
        }

    }

    free(operation);


    return 0;


}
