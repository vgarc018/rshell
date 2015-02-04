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

bool isDir(const char *name)
{
    struct stat s;
    if((stat(name, &s)) != 0)
    {
        perror("Stat error");
        return false;
    }
    else
    {
        if(S_ISDIR(s.st_mode))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}


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

void noFlags(const char *file)
{
   // string dot = ".";
   // const char *file = dot.c_str();
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

void lFlag(const char *filename, bool flag)
{
    struct stat s;
    DIR *dir;
    dirent *entry;
    bool direc = isDir(filename);
   if(direc)
   {
        if((dir = opendir(filename)) == NULL)
        {
            perror("open directory");
            return;
        }
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
                if( (stat(entry->d_name, &s)) != 0)
                {
                    perror("Stat Error");
                    return;
                }
                else
                {
                    cout << ((s.st_mode & S_IRUSR) ? "r":"-");
                    cout << ((s.st_mode & S_IWUSR) ? "w":"-");
                    cout << ((s.st_mode & S_IXUSR) ? "x":"-");
                }
            }
         }
      }
}

int main(int argc, char **argv)
{
    bool a = false;
    bool l = false;
   // bool R = false;
    string dot = ".";
    vector< char* > filenames;

    for(int i = 1; i < argc; i++)
    {
        if(argv[i][1] == 'a')
        {
            a = true;
        }
        else if(argv[i][1] == 'l')
        {
            l = true;
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

    if(!filenames.empty() && !a)
    {
       for(unsigned int i= 0; i < filenames.size(); i++)
       {
           noFlags(filenames.at(i));
       }
    }
    if(argc == 1)
    {
        noFlags(dot.c_str());
    }
    if(a)
    {
       for(unsigned int i = 0; i < filenames.size(); ++i)
        {
            cout << filenames.at(i) << ":" << endl;
            aFlag(filenames.at(i));
        }
    }
    if(l)
    {
        string test = "ls.cpp";
        lFlag(test.c_str(), a);
    }
    return 0;
}
