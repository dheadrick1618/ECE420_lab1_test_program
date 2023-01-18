#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <string.h>

int isPerfectSquare(int value);

int main(int argc, char* argv[]){
    float calculationTime = 0.0;

    if(argc < 2){
        printf("Missing path to the main, matrixgen, and serialtester executables. (Arg[1]). \n");
        return 1;
    }

    //Change current process directory to where the main, matrixgen, and serialtester executable are
    chdir(argv[1]);

    FILE * fp; //Pointer to CSV data output file
    FILE * fpOut; //Pointer to matrix output file generated from main executable
    fp = fopen ("csvTestData.txt", "w+");
    fprintf(fp, "Matrix Size , Thread Count , Elapsed Time \n");

    if(argc < 3){
        printf("Missing max matrix size. (Arg[2]) \n");
        return 1;
    }
    int maxMatrixSize = atoi(argv[2]);
    if(maxMatrixSize > 256){
        maxMatrixSize = 256;
    }
    else if(maxMatrixSize < 1){
        maxMatrixSize = 1;
    }

    char matrixGenBuffer [256];
    char mainBuffer [256];
    char timeBuffer[1024];

    for(int i = 1; i <= maxMatrixSize; i++){
        snprintf ( matrixGenBuffer, 100, "./matrixgen -s %d", i);
        //Generate an input matrix with the matrixgen exec
        if(system(matrixGenBuffer) != 0){
            return 6;
        }

        //Loop through all the valid thread counts for the given matrix size 
        //Run the executable main and then validate its output with serialtester 
        int it = 0;
        int threadcount = 1;
        while(1){
            //thread count must be a factor of the matrix size (i), otherwise ignore
            if((i*i)%threadcount == 0 || it == 0){
                snprintf ( mainBuffer, 100, "./main %d", threadcount);

                if(system(mainBuffer) != 0){
                    return 6;
                }

                if(system("./serialtester") != 0){
                    return 6;
                }

                fpOut = fopen ("data_output", "r");
                
                //Get last line of data output file for total elasped time
                fseek(fpOut, 0, SEEK_SET); // make sure start from 0
                while(!feof(fpOut)){
                    memset(timeBuffer, 0x00, 1024); // clean buffer
                    fscanf(fpOut, "%[^\n]\n", timeBuffer); // read file *prefer using fscanf
                }
                // printf("%s \n", timeBuffer);

                char* endPtr; //Needed for string to double converstion below
                calculationTime = strtod(timeBuffer, &endPtr);

                //Write test results to CSV file in the following format: 
                //  matrix size, thread count, total elapsed time
                fprintf(fp, "%d , %d , %.5f \n", i, threadcount, calculationTime );
            }

            //increment the iterator to get the next square number 
            it+=1;

            //Thread count must be a perfect square 
            threadcount = it*it;

            //if the threadcount is greater that the number of matrix elements (i^2) finish testing this matrix and increment matrix size
            if(threadcount > i*i){
                break;
            }
        }
    }
    fclose(fp);
    return 0;
}


int isPerfectSquare(int value){
    int iVar;
    float fVar;
 
    fVar=sqrt((double)value);
    iVar=fVar;
 
    if(iVar==fVar)
        return 1;
    else
        return 0;
}