#include<ctype.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#define FILENAME_LEN 40
#define FILES_COUNT 2
enum input
    
{
    file,
    cin,
    arg
    
};
int are_strings_equal(char*s0,char*s1) 
{
    char*ptr0=s0;
    char*ptr1=s1;
    while(*ptr0 || *ptr1) 
    
    {
        if(*ptr0!=*ptr1) 
        {
            return 0;
        }
        ++ptr0;
        ++ptr1;
    }
    return 1;
    
}
    
int is_space(char c) 
{
    return c== '\n' || c== ' ' || c== '\t' || c==EOF;
}
int is_flag(char const*arg) 
{
    return arg[0]== '-' || arg[0]== '/';
}
int main(int argc,char*argv[]) 
{
    
    if(argc==1) 
    {
        printf("There is not arguments!\n");
    
    
        return 1;
    }
    char*flag=NULL;
    
    
    
    if(is_flag(argv[1])) 
    {
        flag=argv[1];
        ++flag;
    
    
    }
    else
    {
        printf("Flag name is incorrect!\n");
    
    
        return 1;
    }
    enum input in;
    if(are_strings_equal(flag, "fi")) 
    {
        in=file;
    }
    else if(are_strings_equal(flag, "cin")) 
    {
        in=cin;
    }
    else if(are_strings_equal(flag, "arg")) {
        in=arg;
    }
    else
    {
        printf("Such flag doesn't exists!\n");
        return 1;
    
    }
    if(in==file&&argc!=3 ||
        in==cin&&argc!=2 ||
        in==arg&&argc<3) 
    
    
    {
        printf("Wrong number of arguments!\n");
        return 1;
    }
    char**files=(char**) calloc(sizeof(char*) ,FILES_COUNT);
    if(files==NULL) 
    {
    
        printf("Memory cannot be allocated!\n");
        return 2;
    }
    int it=0;
    int file_it=0;
    int cur_files=FILES_COUNT;
    if(in==file || in==cin) 
    {
    
    
        FILE*fi;
    
    
        char c;
        if(in==file) 
        {
            fi=fopen(argv[2], "r");
            if(fi==NULL) 
            {
                printf("Such file doesn't exists!\n");
                return 1;
            }
            c=fgetc(fi);
        }
    
        else if(in==cin) 
        {
            printf("Enter filenames:\n");
    
            c=getchar();
        }
        char _c= ' ';
        files[file_it]=(char*) malloc(sizeof(char) *FILENAME_LEN);
        if(files[file_it]==NULL) 
        {
            printf("Memory cannot be allocated!\n");
            free(files);
            return 2;
        }
    
        files[file_it][FILENAME_LEN-1]= '\0';
        int cur_len=FILENAME_LEN;
        while(_c!=EOF) 
        {
            if(!is_space(c)) 
            {
                if(cur_len==it-1) 
                {
                    cur_len*=2;
    
                    char*ptr=realloc(files[file_it],sizeof(char*) *cur_len);
                    if(ptr==NULL) 
                    {
                        printf("Not enough memory!\n");
    
    
    
                        int i;
                        for(i=0;i<cur_files;++i) 
                        {
                            free(files[i]);
    
    
                        }
    
                        free(files);
    
                        return 1;
                    }
                    files[file_it]=ptr;
                }
                *(*(files+file_it) +it++) =c;
            }
            else
            {
                files[file_it][it]= '\0';
                ++file_it;
                cur_len=FILENAME_LEN;
                it=0;
                if(cur_files==file_it) 
                {
                    cur_files*=2;
                    char*ptr=realloc(files,sizeof(char*) *cur_files);
                    if(ptr==NULL) 
                    {
                        printf("Not enough memory!\n");
                        int i;
                        for(i=0;i<cur_files;++i) 
                        {
                            free(files[i]);
                        }
                        free(files);
    
                        return 1;
                    }
                    files=ptr;
                }
    
                files[file_it]=(char*) malloc(sizeof(char) *FILENAME_LEN);
    
    
            }
            _c=c;
            if(in==file) 
    
            {
                c=fgetc(fi);
    
            }
            else if(in==cin) 
            {
                c=getchar();
    
            }
        }
        if(in==file) 
        {
            fclose(fi);
        }
    }
    else
    {
        int j;
    
        for(j=0;j<argc-2;++j) 
        {
            if(j==cur_files) 
            {
    
    
    
                cur_files*=2;
                files=realloc(files,sizeof(char*) *cur_files);
                if(files==NULL) 
    
                {
                    printf("Not enough memory!\n");
                    int i;
                    for(i=0;i<cur_files;++i) 
                    {
                        free(files[i]);
    
                    }
                    free(files);
                    return 1;
    
                }
            }
            files[j]=argv[j+2];
    
        }
        file_it=argc-2;
    }
    FILE*out=fopen("out.txt", "w+");
    char c;
    if(are_strings_equal(files[file_it-1], "")) 
    {
        --file_it;
    
    }
    int i;
    for(i=0;i<file_it;++i) 
    
    {
    
        FILE*file=fopen(files[i], "r");
    
        if(file==NULL) 
    
        {
    
            printf("%s\nSuch file doesn't exists!\n",  files[i]);
            continue;
        }
        while((c=fgetc(file)) !=EOF) 
        {
    
            putc(c,out);
    
        }
        fclose(file);
        if(in!=arg) 
        {
            free(files[i]);
        }
    }
    free(files);
    fclose(out);
    printf("Success\n");
    
    return 0;
}
