#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;


void aFlag(const char *file)
{
    DIR *dirp; 
    if((dirp = opendir(file)) == NULL) 
    {
        perror("Open Dir");
        return;
    }
    else
    {
        dirent *direntp;
        bool test = true;
        while(test)
        {
            if((direntp = readdir(dirp)) == NULL)
            {
                perror("Reading File");
                test = false;
            }
            else
            {    
                cout << direntp->d_name  << endl;
            }
        }
        closedir(dirp);
    }
}

void noFlags()
{
    const char file[] = {'.'}; 
    DIR *dir;
    dirent *entry;

    if((dir = opendir(file)) == NULL)
    {
        perror("open directory");
        return;
    }
    else
    {
        bool res = true;
        while((entry = readdir(dir)))
        {
           //ntry =  readdir(dir);
            if(errno)
            {
                perror("reading file");
                return;
            }
            else
            {
                cout << entry->d_name << endl;
            }
        }

    }
}


int main(int argc, char **argv)
{
    //const char *file = argv[0][0];

    //aFlag(file);
    noFlags();

    return 0;
    //cout << line << endl;


   /* const char *dirName = line.c_str();
    DIR *dirp = opendir(dirName);
    dirent *direntp;
    while ((direntp = readdir(dirp)))
          cout << direntp->d_name << endl;  // use stat here to find attributes of file
    closedir(dirp);
    */
}
