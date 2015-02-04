#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;


void aFlag(const char *file)
{
    DIR *dir;
    dirent *entry;

    if((dir = opendir(file)) == NULL)
    {
        perror("open directory");
        return;
    }
    else
    {
        while((entry = readdir(dir)))
        {
           //ntry =  readdir(dir);
            if(errno != 0)
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

void noFlags()
{
    string dot = ".";
    const char *file = dot.c_str();
    DIR *dir;
    dirent *entry;

    if((dir = opendir(file)) == NULL)
    {
        perror("open directory");
        return;
    }
    else
    {
        while((entry = readdir(dir)))
        {
           //ntry =  readdir(dir);
            if(errno != 0)
            {
                perror("reading file");
                return;
            }
            else
            {
                if(entry->d_name[0] != '.')
                {
                     cout << entry->d_name << endl;
                }
            }
        }

    }
}


int main(int argc, char **argv)
{
    bool a = false;
   // bool l = false;
   // bool R = false;
    string test = ".";
    vector< char* > filenames;

    for(int i = 1; i < argc; i++)
    {
        if(argv[i][1] == 'a')
        {
            a = true;
        }
        else if(argv[i][1] == 'l')
        {
          //  l = true;
        }
        else if(argv[i][1] == 'R')
        {
           // R = true;
        }
        else
        {
            filenames.push_back(argv[i]);
        }

    }

    if(argc == 1){
        noFlags();
        return 0;
    }
    if(a)
    {
        aFlag(filenames.at(0));
    }
    return 0;
}
