#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "the2.h"


/*
INPUT:
    int *row_count: vertical size of the matrix to be assigned (passed by reference from the main function)
    int *row_size: horizontal size of the matrix to be assigned (passed by reference from the main function)

OUTPUT:
    double **matrix: created data matrix

METHOD:
    This function creates the matrix streamed via stdin. 
    During this process, assigns row_count and row_size variables.
*/
double **initialize_the_data(int *row_count, int *row_size){ 
    double **matrix;
    double i,j;
    int size, count, trav_1, trav_2;
    j = size = i = count = trav_1 = trav_2 = 0;
    
    matrix = malloc(sizeof(double*));
    matrix[0] = malloc(sizeof(double));
    
    while (1){
        scanf("%lf", &i);
        if (i == -1 && j == -1){
            break;
        }
        else{
            if (i == -1){
                count++;
                trav_1++;
                trav_2 = 0;
                matrix = realloc(matrix, sizeof(double*)*(count+1));
                matrix[trav_1] = malloc(sizeof(double)*size);
                j = i;
            }
            else{
                if (trav_1 == 0){
                    size++;
                    matrix[0] = realloc(matrix[0], sizeof(double)*size);
                }
                matrix[trav_1][trav_2] = i;
                trav_2++;
                j = i;
            }
        }
    }
    
    
    *row_size = size;
    *row_count = count;
    return matrix; 
}

/*
INPUT:
    double **matrix: data matrix
    int n: number of rows to be printed
    int row_size: horizontal size of the matrix

METHOD:
    This function prints first n row of the matrix.
*/
void print_first_n_row(double **matrix, int n, int row_size) {
    int trav_1, trav_2;
    for (trav_1 = 0; trav_1 < n; trav_1++){
        for(trav_2 = 0; trav_2 < row_size; trav_2++){
            if(trav_2 != 0){
                printf(" %.4f", matrix[trav_1][trav_2]);
            }
            else{
                printf("%.4f", matrix[trav_1][trav_2]);
            }
        }
        if(trav_1 != n-1){
            printf("\n");
        }
    }
    
}

/*
INPUT:
    double **matrix: data matrix
    int row_size: horizontal size of the data matrix
    int row1: index of the first row in the calculation
    int row2: index of the second row in the calculation

METHOD:
    This function calculates dot product of the row1 and the row2 and prints it in the following format:
        Dot product of rows <row1>, <row2>: <dot_product>
*/
void calculate_dot_product(double **matrix, int row_size, int row1, int row2){
    
    double sum, product;
    int trav_1;
    sum = product = 0;
    
    for(trav_1 = 0; trav_1 < row_size; trav_1++){
        product = (matrix[row1][trav_1])*(matrix[row2][trav_1]);
        sum += product;
    }
    
    printf("Dot product of rows %d, %d: %.4f", row1, row2, sum);
    
}
    
    

/*
INPUT:
    double **matrix: data matrix
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix

OUTPUT:
    double **covariance_matrix: Created covariance matrix with size of row_size X row_size

METHOD:
    This function creates covariance matrix of the original data matrix and returns it.

*/

double sigma(double **matrix, int column_1, int column_2, double *mean, int count){
    int k;
    double sum = 0;
    
    for(k = 0; k < count; k++){
        sum += ((matrix[k][column_1]-mean[column_1])*(matrix[k][column_2]-mean[column_2]));
    }
    return sum;
}


double **calculate_covariance_matrix(double **matrix, int row_count, int row_size){ 
    
    int size = row_size;
    int count = row_count;
    double dividor = count;
    double **covar_matrix = malloc(sizeof(double*)*size);
    double *mean = malloc(sizeof(double)*size);
    int i,j;
    int trav_1, trav_2, sett;
    double sum;

    for (i = 0; i < size; i++){
        for(j = 0; j < count; j++){
            mean[i] += (matrix[j][i]/dividor);
        }
    }

    for(sett = 0; sett < size; sett++){
        covar_matrix[sett] = malloc(sizeof(double)*size);
    }
    
    for(trav_1 = 0; trav_1 < size; trav_1++){
        for(trav_2 = 0; trav_2 < size; trav_2++){
            sum = sigma(matrix, trav_1, trav_2, mean, count);
            sum /= (dividor-1);
            covar_matrix[trav_1][trav_2] = sum;
            sum = 0;
        }
    }
    
    free(mean);
    return covar_matrix; 
    
}

/*
INPUT:
    double **matrix: data matrix
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix

OUTPUT:
    double **result: Created result matrix with size of row_size X row_size

METHOD:
    This function calculates x^T * x. First finds the transpose of the original data matrix and apply matrix multiplication.
    At the end it returns the calculated matrix with size of row_size X row_size.

*/
double matrix_product(double **matrix, double **transpose, int row_from_trans, int column_from_original, int count){
    int j;
    double sum = 0;
    
    for(j = 0; j < count; j++){
        sum += (transpose[row_from_trans][j]*matrix[j][column_from_original]);
    }
    
    return sum;
}

double **calculate_x_transpose_times_x(double **matrix, int row_count, int row_size){
    
    double **product = malloc(sizeof(double*)*row_size);
    double **transpose = malloc(sizeof(double)*row_size);
    int sett, count = row_count, size = row_size, sett_2, i, j, trav_pro_1, trav_pro_2;
    double sum;
    
    for(sett = 0; sett < size; sett++){
        product[sett] = malloc(sizeof(double)*size);
    }
    
    for(sett_2 = 0; sett_2 < count; sett_2++){
        transpose[sett_2] = malloc(sizeof(double)*count); 
    }
    
    for(i = 0; i < size; i++){
        for(j = 0; j < count; j++){
            transpose[i][j] = matrix[j][i];
        }
    }
    
    for(trav_pro_1 = 0; trav_pro_1 < size; trav_pro_1++){
        for(trav_pro_2 = 0; trav_pro_2 < size; trav_pro_2++){
            sum = matrix_product(matrix, transpose, trav_pro_1, trav_pro_2, count);
            product[trav_pro_1][trav_pro_2] = sum;
        }
    }
    free(transpose);
    return product; 
}
/*
INPUT:
    double **matrix: data matrix
    int *group_count: number of the groups to be assigned (passed by reference from the main function)
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix
    int group_column: index of the column to apply grouping over
    int operation: index of the operation to apply during grouping
        SUM -> 0
        AVG -> 1
        MAX -> 2
        MIN -> 3

OUTPUT:
    double **grouped_matrix: Created grouped matrix with size of group_count X row_size

METHOD:
    This function applies grouping over desired column index, creates a grouped matrix. It returns this grouped matrix.
    During this process it calculates group count and assigns to the variable.

*/

int bool_in_list(double *array, double value, int size){
    int i;
    for (i = 0; i < size; i++){
        if (array[i] == value){
            return 1;
        }
    }
    return 0;
}

double count_occurrence(double **matrix, double value, int column_num, int count){
    int i;
    double counter = 0;
    for(i = 0; i < count; i++){
        if(matrix[i][column_num]==value){
            counter++;
        }
    }
    return counter;
}

double element(double **matrix, double **grouped, double current, double unique, int count, int operation, int n, int group_column, int unique_count, int size){
    int i;
    double value = 0, dividor = 0;
    
    if (operation == 0){
        for(i = 0; i < count; i++){
            if(matrix[i][group_column] == unique){
                value += matrix[i][n];
            }
        }
    }
    
    else if(operation == 1){
        for(i = 0; i < count; i++){
            if(matrix[i][group_column] == unique){
                value += matrix[i][n];
                dividor++;
            }
        }
        value /=dividor;
    }
    
    else if(operation == 2){
        value = MIN_VAL;
        for(i = 0; i < count; i++){
            if(matrix[i][group_column] == unique && value < matrix[i][n]){
                value = matrix[i][n];
            }
        }
    }
    
    else if(operation == 3){
        value = MAX_VAL;
        for(i = 0; i < count; i++){
            if(matrix[i][group_column] == unique && value > matrix[i][n]){
                value = matrix[i][n];
            }
        }
    }
    return value;
}




double **group_by(double **matrix, int *group_count, int row_count, int row_size, int group_column, int operation){ 
    double **grouped;
    int size = row_size, count = row_count, m,n,x,y,z;
    double *unique_values = malloc(sizeof(double)*count);
    int i, val_index = 0, unique_count = 0, j, k;
    
    for(x = 0; x < count; x++){
        matrix[x][group_column]++;
    }
    
    for (i = 0; i < count; i++){
        if(!(bool_in_list(unique_values, matrix[i][group_column], count))){
            unique_values[val_index] = matrix[i][group_column];
            unique_count++;
            val_index++;
        }
    }
    
    *group_count = unique_count;
    grouped = malloc(sizeof(double *)*unique_count);
    
    for(j = 0; j < unique_count; j++){
        grouped[j] = malloc(sizeof(double)*size);
    }
    
    for(k = 0; k < unique_count; k++){
        grouped[k][group_column] = unique_values[k];
    }
    
    for(m = 0; m < unique_count; m++){
        for(n = 0; n < size; n++){
            if(n != group_column){
                grouped[m][n] = element(matrix, grouped, grouped[m][n], grouped[m][group_column], count, operation, n, group_column, unique_count, size);
            }
        }
    }
    
    for(y = 0; y < count; y++){
        matrix[y][group_column]--;
    }
    
    for(z = 0; z < unique_count; z++){
        grouped[z][group_column]--;
    }
    
    return grouped;
}

/*
INPUT:
    double **matrix: data matrix
    int row_count: vertical size of the data matrix
    int row_size: horizontal size of the data matrix
    double **kernel: kernel matrix
    int kernel_height: vertical size of the kernel matrix
    int kernel_width: horizontal size of the kernel matrix

OUTPUT:
    double **convoluted_matrix: Created convoluted matrix

METHOD:
    This function applies convolution over data matrix using kernel matrix and returns created matrix.

*/
double convolute(double **square, double **kernel, int kernel_height, int kernel_width){
    double result = 0;
    int i,j;
    for(i = 0; i < kernel_height; i++){
        for(j = 0; j < kernel_width; j++){
            result += (square[i][j]*kernel[i][j]);
        }
    }
    return result;
}

double **sub_matrix(double **matrix, int kernel_height, int kernel_width, int j, int k){
    double **to_return = malloc(sizeof(double *)*kernel_height);
    int i, m, n, hold = k;
    
    for(i=0; i < kernel_height; i++){
        to_return[i]=malloc(sizeof(double)*kernel_width);
    }
    
    for(m = 0; m < kernel_height; m++){
        for(n = 0; n < kernel_width; n++){
            to_return[m][n]=matrix[j][k];
            k++;
        }
        j++;
        k = hold;
    }
    
    return to_return;
}

double **convolution(double **matrix, int row_count, int row_size, double **kernel, int kernel_height, int kernel_width){ 
    int count = row_count, size = row_size;
    double **convoluted = malloc(sizeof(double*)*(count-kernel_height+1));
    int i, j, k, m;
    double **sub = malloc(sizeof(double *)*kernel_height);
    for(m = 0; m < kernel_height; m++){
        sub[m] = malloc(sizeof(double)*kernel_width);
    }
    
    for(i = 0; i < count-kernel_height+1; i++){
        convoluted[i] = malloc(sizeof(double)*(size-kernel_width+1));
    }
    
    for(j = 0; j < count-kernel_height+1; j++){
        for(k = 0; k < size-kernel_width+1; k++){
            sub = sub_matrix(matrix, kernel_height, kernel_width, j, k);
            convoluted[j][k] = convolute(sub, kernel, kernel_height, kernel_width);
            /*printf("J IS: %d, K IS: %d ASSIGNED: %f\n", j,k, convoluted[j][k]);*/
        }
    }
    
    free(sub);
    return convoluted; 
}
    
    
    
    
    
    
    
    
    
    
    
    
