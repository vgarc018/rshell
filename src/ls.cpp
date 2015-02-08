#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <iomanip>
#include <pwd.h>
#include <grp.h>
#include <time.h>

using namespace std;



void notDir(const char *file, char flag)
{
    struct stat s;
    if((stat(file, &s)) != 0)
    {
        perror("Stat Error");
        return;
    }
    else
    {
        if(flag == 'l')
        {
             register struct passwd *pw;
             register struct group *reg;
             pw = getpwuid(s.st_uid);
             char buf [80];
            
             if(!pw)
             {
                 perror(" getting username" );
             }
             reg = getgrgid(s.st_gid);
             if(!reg)
             {
                 perror(" getting group");
             }

             cout << ("-");
             cout << ((s.st_mode & S_IRUSR) ? "r":"-");
             cout << ((s.st_mode & S_IWUSR) ? "w":"-");
             cout << ((s.st_mode & S_IXUSR) ? "x":"-");
             cout << ((s.st_mode & S_IRGRP) ? "r":"-");
             cout << ((s.st_mode & S_IWGRP) ? "w":"-");
             cout << ((s.st_mode & S_IXGRP) ? "x":"-");
             cout << ((s.st_mode & S_IROTH) ? "r":"-");
             cout << ((s.st_mode & S_IWOTH) ? "w":"-");
             cout << ((s.st_mode & S_IXOTH) ? "x":"-");
             cout << " " << s.st_nlink << " ";
             cout << setw(5);
             cout << pw->pw_name << " ";
             cout << setw(5);
             cout << reg->gr_name << " ";
             cout << setw(4);
             cout << s.st_size << " ";
             cout << setw(3);
             struct tm *timeinfo;
             timeinfo = localtime (&s.st_mtime);
             strftime(buf,80,  "%b %d  %I:%M ", timeinfo);
             printf("%s",buf);
             cout << setw(5);
             cout << file << endl;

        }   
        else
        {
            cout << file << endl;
        }
    }
}



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
        if(S_ISREG(s.st_mode))
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
    bool direc = isDir(file);
    if(direc)
    {
        notDir(file, 'f');
        return;
    }

    if((dir = opendir(file)) == NULL)
    {
        perror("open directory");
        return;
    }
    else
    {
        while((entry = readdir(dir)))
        {

                cout << entry->d_name << endl;
        }
        if(errno != 0)
        {
             perror("reading file");
             return;
        }

    }
}

void noFlags(const char *file)
{
   // string dot = ".";
   // const char *file = dot.c_str();
    DIR *dir;
    dirent *entry;
    bool direc = isDir(file);
    if(direc)
    {
        notDir(file, 'f');
        return;
    }

    if((dir = opendir(file)) == NULL)
    {
        perror("open directory");
        return;
    }
    else
    {
        while((entry = readdir(dir)))
        {
           if(entry->d_name[0] != '.')
           {
                cout << entry->d_name << endl;
           }
        }
        if(errno != 0)
        {
            perror("reading file");
            return;
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
        notDir(filename, 'l');
        return;
    }

    if((dir = opendir(filename)) == NULL)
    {
        perror("open directory");
        return;
    }
    else
    {
        while((entry = readdir(dir)))
        {
            if(errno != 0)
            {
                perror("reading file");
                return;
            }
            else
            {
                if(flag)
                {
                    if( (stat(entry->d_name, &s)) != 0)
                    {
                        perror("Stat Error");
                        return;
                    }
					else
					{
						register struct passwd *pw;
						register struct group *reg;
						pw = getpwuid(s.st_uid);
						char buf [80];
				
						if(!pw)
						{
							perror(" getting username" );
						}
						reg = getgrgid(s.st_gid);
						if(!reg)
						{
							perror(" getting group");
						}

						cout <<( !direc ? "-":"d");
						cout << ((s.st_mode & S_IRUSR) ? "r":"-");
						cout << ((s.st_mode & S_IWUSR) ? "w":"-");
						cout << ((s.st_mode & S_IXUSR) ? "x":"-");
						cout << ((s.st_mode & S_IRGRP) ? "r":"-");
						cout << ((s.st_mode & S_IWGRP) ? "w":"-");
						cout << ((s.st_mode & S_IXGRP) ? "x":"-");
						cout << ((s.st_mode & S_IROTH) ? "r":"-");
						cout << ((s.st_mode & S_IWOTH) ? "w":"-");
						cout << ((s.st_mode & S_IXOTH) ? "x":"-");
						cout << " " << s.st_nlink << " ";
						cout << setw(5);
						cout << pw->pw_name << " ";
						cout << setw(5);
						cout << reg->gr_name << " ";
						cout << setw(6);
						cout << s.st_size << " ";
						cout << setw(3);
						struct tm *timeinfo;
						timeinfo = localtime (&s.st_mtime);
						strftime(buf,80,  "%b %d  %I:%M ", timeinfo);
						printf("%s",buf);
						cout << setw(5);
						cout << entry->d_name  << endl;
                  

                }
            }
            else
            {
				if(entry->d_name[0] != '.')
				{
					if( (stat(entry->d_name, &s)) != 0)
						{
							perror("Stat Error");
							return;
						}
						else
						{
							register struct passwd *pw;
							register struct group *reg;
							pw = getpwuid(s.st_uid);
							char buf [80];
					
							if(!pw)
							{
								perror(" getting username" );
							}
							reg = getgrgid(s.st_gid);
							if(!reg)
							{
								perror(" getting group");
							}

							cout <<( !direc ? "-":"d");
							cout << ((s.st_mode & S_IRUSR) ? "r":"-");
							cout << ((s.st_mode & S_IWUSR) ? "w":"-");
							cout << ((s.st_mode & S_IXUSR) ? "x":"-");
							cout << ((s.st_mode & S_IRGRP) ? "r":"-");
							cout << ((s.st_mode & S_IWGRP) ? "w":"-");
							cout << ((s.st_mode & S_IXGRP) ? "x":"-");
							cout << ((s.st_mode & S_IROTH) ? "r":"-");
							cout << ((s.st_mode & S_IWOTH) ? "w":"-");
							cout << ((s.st_mode & S_IXOTH) ? "x":"-");
							cout << " " << s.st_nlink << " ";
							cout << setw(5);
							cout << pw->pw_name << " ";
							cout << setw(5);
							cout << reg->gr_name << " ";
							cout << setw(6);
							cout << s.st_size << " ";
							cout << setw(3);
							struct tm *timeinfo;
							timeinfo = localtime (&s.st_mtime);
							strftime(buf,80,  "%b %d  %I:%M ", timeinfo);
							printf("%s",buf);
							cout << setw(5);
							cout << entry->d_name  << endl;
					}
				}
			}
         }
      }
   }
}

int main(int argc, char **argv)
{
    bool a = false;
    bool l = false;
    bool al= false;
    string dot = ".";
    vector< char* > filenames;

    for(int i = 1; i < argc; i++)
    {
        if(argv[i][1] == 'a')
        {
            al = true;
            a = true;
        }
        else if(argv[i][1] == 'l')
        {
            l = true;
            if(argv[i][2] == 'a')
            {
                al = true;
            }
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
    if(a && !l)
    {
        if(filenames.empty())
        {
            lFlag(dot.c_str(), al);
        }
        for(unsigned int i = 0; i < filenames.size(); ++i)
        {
           if(filenames.size() > 1) cout << filenames.at(i) << ":" << endl;
            aFlag(filenames.at(i));
        }
    }
    if(l)
    {  
        if(filenames.empty())
        {
            lFlag(dot.c_str(), al);
        }
        for(unsigned int i = 0; i < filenames.size(); ++i)
        {
           if(filenames.size() > 1) cout << filenames.at(i) << ":" << endl;
            lFlag(filenames.at(i), al);
        }

    }
    return 0;
}
