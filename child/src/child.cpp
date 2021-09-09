#include <child.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>


#include <spawn.h>
#include <sys/wait.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    printf("CHILD IS ALIVE ! argnum = %d\n",argc);
    for (int i = 0; i<argc ; i++) {
        printf("arg %d = [%s]\n",i, argv[i]);
    }
    printf("CHILD 0\n");

    char* reqpath = argv[0];
    char* respath = argv[1];
    
    printf("CHILD 1 [%s] [%s]\n",reqpath,respath);

    int req = open(reqpath,O_RDONLY);
    printf("CHILD 2 req = %d\n",req);
    int res = open(respath,O_WRONLY);
    printf("CHILD 3 res = %d\n",res);
    
    
    
    char buf[256];
    memset(buf,0,256);
    int timeout_cnt = 0;
    int cnt = 0;
    
    while (true)
    {
        //printf("CHILD READ\n");
        ssize_t readbytes = read(req, buf, 256);
        //printf("CHILD READ done\n");

        if(readbytes == 0)
        {
            printf("CHILD EOF\n");
            if(timeout_cnt > 5)
            {
                break;
            }
            sleep(2);
            timeout_cnt++;
        }
        else if (readbytes == -1)
        {
            printf("CHILD IO ERROR %d [%s]\n",errno,strerror(errno));
            break;
        }
        else
        {
            printf("CHILD  read %ld chars: [%s]\n",readbytes,buf);
            char num[17];
            sprintf(num,"%d",cnt);
            strcat(buf,num);
            write(res,buf,strlen(buf));
            cnt++;
        }
        sleep(2);

    }
    
    close(req);
    close(res);
    printf("CHILD END\n");
    return 1;
}
