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
#include <string.h>

using namespace std;



void notDir(const char *file, char flag)
{
    struct stat s;
   //:wq cout << "in not dir" << endl;
   cout << file << endl;
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
   	if(closedir(dir) == -1)
	{
		perror("closing dir");
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
   	if(closedir(dir) == -1)
	{
		perror("closing dir");
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
                char filepath[1024];
                strcpy(filepath, filename);
                string slash = "/";
                strcat(filepath, slash.c_str());
                strcat(filepath, entry->d_name);
                    if(flag)
                    {
                        if( (stat((filepath), &s)) != 0)
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
							if( (stat(filepath, &s)) != 0)
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

								cout <<( direc ? "d" : "-");
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
   
    if(errno != 0)
    {
        perror("reading file");
        return;
    }
	if(closedir(dir) == -1)
	{
		perror("closing dir");
	}
}

void Rflag(const char *filename,char flag, char flag2)
{
    vector<char*> dirs;
    DIR *dir;
    dirent *entry;
   if((dir = opendir(filename)) == NULL)
   {
       perror("open dir");
       return;
   }
   
   cout << filename << ":" << endl;

   while((entry = readdir(dir)))
   {
        struct stat s;

        char filepath[1024];
        string dash = "/";
        strcpy(filepath, filename);
        strcat(filepath, dash.c_str());
        strcat(filepath, entry->d_name);
        if((stat(filepath, &s)) == -1)
        {
            perror("Stat Error");
            return;
        }
        if((flag == 'a' || flag2 == 'a') && (flag != 'l' && flag2 != 'l')) 
        {
            aFlag(entry->d_name);
        }
        else if( flag == 'l' || flag2 == 'l')
        {
            if(flag2 == 'a' || flag == 'a')
            {
                lFlag(entry->d_name, true);
            }
            else
            {
                lFlag(entry->d_name, false);
            }
        }
        else
        {
            cout << entry->d_name << endl;
        }
        if(S_ISDIR(s.st_mode))
        {
            dirs.push_back(entry->d_name);
        }
   }
   if(errno != 0)
   {
       perror("Reading Dir");
       return;
   }

   cout << endl;
   cout << endl;

   for(size_t i = 0; i < dirs.size(); i++)
   {
       char dir[1024];
       string dash = "/";
       strcpy(dir, filename);
       strcat(dir, dash.c_str());
       strcat(dir, dirs.at(i));
       Rflag(dir, flag, flag2);
   }

   if((closedir(dir)) == -1)
   {
       perror("Closing dir");
   }
   
   return;

}

int main(int argc, char **argv)
{
    bool a = false;
    bool l = false;
    bool al= false;
    bool flags = false;
    bool R = false;
    string dot = ".";
    vector< char* > filenames;

    for(int i = 1; i < argc; i++)
    {
        if(argv[i][1] == 'a')
        {
            flags = true;
            if(argv[i][2] == 'l')
            {
                 al = true;
                 l = true;
            }
            a = true;
        }
        else if(argv[i][1] == 'l')
        {
            l = true;
            flags = true;
            if(argv[i][2] == 'a')
            {
                al = true;
            }
        }
        else if(argv[i][1] == 'R')
        {
            flags = true;
            R = true;
        }
        else
        {
            filenames.push_back(argv[i]);
        }

    }

    if(a && l)
    {
        al = true;
    }
    //cout << filenames.at(0);
    if(!filenames.empty() && !flags)
    {
       // cout << "in no flag" << endl;
       for(unsigned int i= 0; i < filenames.size(); i++)
       {
           noFlags(filenames.at(i));
       }
    }
    if(argc == 1)
    {
        noFlags(dot.c_str());
    }
    if(a && !l && !al)
    {
        if(filenames.empty())
        {
            aFlag(dot.c_str());
        }
        for(unsigned int i = 0; i < filenames.size(); ++i)
        {
           if(filenames.size() > 1) cout << filenames.at(i) << ":" << endl;
            aFlag(filenames[i]);
        }
    }
    if(l)
    {  
       // cout << "in l" << endl;
        if(filenames.empty())
        {
            lFlag(dot.c_str(), al);
        }
        for(unsigned int i = 0; i < filenames.size(); ++i)
        {
           if(filenames.size() > 1) cout << filenames.at(i) << ":" << endl;
         //  cout << filenames.at(i) << endl;
           lFlag(filenames.at(i), al);
        }

    }
    if(R)
    {
         if(filenames.empty())
        {
            Rflag(dot.c_str(),' ' , ' ');
        }
        for(unsigned int i = 0; i < filenames.size(); ++i)
        {
           if(filenames.size() > 1) cout << filenames.at(i) << ":" << endl;
         //  cout << filenames.at(i) << endl;
           Rflag(filenames.at(i), ' ', ' ');
        }

    }
    return 0;
}
