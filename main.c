#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void walk_in_dirs(char* basePath,char filename[],char *search_string){
    char path[1000];
    char *word;
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // Unable to open directory stream
    if (dir != 0){
        while ((dp = readdir(dir)) != NULL)
        {
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
            {
                printf("\nCurrent : %s",dp->d_name);

                strcpy(path, basePath);
                strcat(path, "/");
                strcat(path, dp->d_name);

                word = strtok(dp->d_name,".");
                word = strtok(NULL,".");

                if( word!=NULL && strcmp(word,"txt")==0){
                    search_in_file(path,search_string);
                }

                walk_in_dirs(path,filename,search_string);
            }
        }
    }else{
        return;
    }

    closedir(dir);
}

void search_in_file(char filename[],char *search_string){

    printf("\n\nSearching in ............... %s",filename);
    int line_count=0,i;
    int occurence_count=0;
    int count=0;
    char line[1000];
    char *word;
    char delimeter[] = " \n";
    FILE *fp=fopen(filename,"r");

    while( fgets ( line, sizeof line, fp ) != NULL ){
        line_count++;
        //printf("\n\nLine:%s",line);
        word = strtok(line,delimeter);

        int len = strlen(word);

        while(word != NULL ){

            if(strcmp(word,search_string) == 0){
                printf("\nLine Count:%d in file:%s",line_count,filename);
                occurence_count++;
            }
            word = strtok(NULL," ");
        }

    }
    printf("\nTotal Occurence:%d\n",occurence_count);
    fclose(fp);
}
int main(int argc, char *argv[])
{
    int i;
    char filename[] = "test.txt";
    char *search_string = argv[1];
    char *path = "Test/";
    //search_in_file(filename,search_string);
    walk_in_dirs(path,filename,search_string);
    /*for(i=0;i<argc;i++){
        printf("\n%s",argv[i]);
    }*/


    return 0;
}
