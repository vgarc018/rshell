#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


void aFlag(const char *file)
{
    DIR *dirp; 
    if((dirp = opendir(file)) == NULL) 
    {
        perror("Open Dir");
        exit(1);
    }
    else
    {
        int direntp;
        struct dirent *prevEntry = NULL;
        struct dirent **dirEntry = NULL;
        if((readdir_r(dirp,prevEntry,dirEntry)) != 0)
        {
            perror("reading dir");
            exit(1);
        }
        else
        {

            while(!(direntp = readdir_r(dirp, prevEntry, dirEntry )))
            {
                cout << "It worked" << endl;
            }
            closedir(dirp);
        }
    }
}


int main()
{
    string line;
    getline(cin,line);

    const char *filename = line.c_str();
    aFlag(filename);


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
