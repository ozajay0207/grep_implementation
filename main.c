#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void search_in_file(char filename[],char *search_string){

    printf("\n..........................................................................");
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
        /*word = strtok(line,delimeter);

        int len = strlen(word);

        while(word != NULL ){

            if(strcmp(word,search_string) == 0){
                printf("\nLine Count:%d in file:%s",line_count,filename);
                occurence_count++;
            }
            word = strtok(NULL,delimeter);
        }*/
        word = line;
        while(word = strstr(word,search_string)){
            printf("\nLine Count:%d \t\t File:%s",line_count,filename);
            occurence_count++;
            word = word + sizeof(search_string);
        }
    }
    printf("\nTotal Occurence:%d",occurence_count);
    printf("\n..........................................................................\n");
    fclose(fp);
}


void walk_in_dirs(char basePath[],char filename[],char *search_string){
    char path[1000];
    char *word;
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (dir != 0){
        while ((dp = readdir(dir)) != NULL)
        {
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
            {


                strcpy(path, basePath);
                strcat(path, "/");
                strcat(path, dp->d_name);
                printf("\nCurrent Location: %s",path);

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

int main(int argc, char *argv[])
{
    int i;
    char filename[] = "test.txt";
    char *search_string =argv[1];
    char path[] = "Test/";
    for(i=2;i<argc;i++){
        strcat(search_string," ");
        strcat(search_string,argv[i]);
    }
    printf("\nSTRING TO SEARCH: %s\n",search_string);
    //search_in_file(filename,search_string);
    walk_in_dirs(path,filename,search_string);
    /*for(i=0;i<argc;i++){
        printf("\n%s",argv[i]);
    }*/


    return 0;
}
