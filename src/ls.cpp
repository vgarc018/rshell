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

void Rflag(const char *filename)
{
    vector<char*> dirs;
    DIR *dir;
    dirent *entry;
     struct stat s;
    if((dir = opendir(filename)) == NULL)
    {
		perror("Open Dir");
	}
	cout << filename << ":" << endl;
	while((entry = readdir(dir)))
	{
		char filepath[1024];
		strcpy(filepath, filename);
        string slash = "/";
        strcat(filepath, slash.c_str());
        strcat(filepath, entry->d_name);
        
        if((stat(filepath, &s)) == -1)
        {
			perror("Stat Error");
		}
		if( entry->d_name[0] == '.')
		{
			continue;
		}
		
		cout << entry->d_name << endl;
		
		if(S_ISDIR(s.st_mode))
		{
			dirs.push_back(entry->d_name);
		}
		cout << endl;
	}
	if(errno != 0)
	{
		perror("reading Dir");
	}
	
	int vecsize = dirs.size();
	
	for(int i = 0; i < vecsize; ++i)
	{
		char filepath[1024];
		strcpy(filepath, filename);
        string slash = "/";
        strcat(filepath, slash.c_str());
        strcat(filepath, dirs[i]);
        Rflag(filepath);
	}
	if((closedir(dir) == -1))
	{
		perror("Closing Dir");
	}
	
	return;
}


int main(int argc, char **argv)
{
    bool a = false;
    bool l = false;
    bool R = false;
    string dot = ".";
    vector< char* > filenames;

    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-a") == 0)
        {
            a = true;        
        }
        else if(strcmp(argv[i], "-l") == 0)
        {
            l = true;
        }
        else if(strcmp(argv[i], "-R") == 0)
        {
            R = true;
        }
        else if((strcmp(argv[i], "-la") == 0) || (strcmp(argv[i], "-al") == 0))
        {
            a = true;
            l = true;
        }
        else if((strcmp(argv[i], "-aR") == 0) || (strcmp(argv[i], "-Ra") == 0))
        {
            a = true;
            R= true;
        } 
        else if((strcmp(argv[i], "-lR") == 0) || (strcmp(argv[i], "-Rl") == 0))
        {
            l = true;
            R =  true;
        }
        else if((strcmp(argv[i], "-alR") == 0) || (strcmp(argv[i], "-aRl") == 0))
        {
            a = true;
            l = true;
            R = true;
        }
        else  if((strcmp(argv[i], "-laR") == 0) || (strcmp(argv[i], "-lRa") == 0))
        {
            l = true;
            a = true;
            R = true;
        }
        else if((strcmp(argv[i], "-Ral") == 0) || (strcmp(argv[i], "-Rla") == 0))
        {
            R = true;
            l = true;
            a = true;
        }
        else
        {
            filenames.push_back(argv[i]);
        }
    }


    int filesize = filenames.size();
    if(!a && !l && !R)
    {
        if(filesize > 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                cout << filenames[i] << ":" << endl;
                noFlags(filenames[i]);
                cout << endl;
            }
        }
        else
        {
            noFlags(dot.c_str());
        }
    }

    if( l && !a && !R)
    {
         if(filesize > 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                cout << filenames[i] << ":" << endl;
                lFlag(filenames[i], false);
                cout << endl;
            }
        }
        else
        {
            lFlag(dot.c_str(), false);
        }
    }

    if( R && !a && !l)
    {
         if(filesize > 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                cout << filenames[i] << ":" << endl;
                Rflag(filenames[i]);
                cout << endl;
            }
        }
        else
        {
            Rflag(dot.c_str());
        }
    }
    /*
    if( a && !l && !R)
    {
        if(filesize > 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                cout << filenames[i] << ":" << endl;
                aFlag(filenames[i]);
                cout << endl;
            }
        }
        else
        {
            aFlag(dot.c_str());
        }
    }
    if(a && l && !R)
    {
        if(filesize > 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                cout << filenames[i] << ":" << endl;
                lFlag(filenames[i], true);
                cout << endl;
            }
        }
        else
        {
            lFlag(dot.c_str(), true);
        }
    }

    if(a && R && !l)
    {
        if(filesize > 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                cout << filenames[i] << ":" << endl;
                Rflag(filenames[i], true, false);
                cout << endl;
            }
        }
        else
        {
            Rflag(dot.c_str(), true, false);
        }
    }
    if(R && l && !a)
    {
         if(filesize > 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                cout << filenames[i] << ":" << endl;
                Rflag(filenames[i], false, true);
                cout << endl;
            }
        }
        else
        {
            Rflag(dot.c_str(), false, true);
        }
    }
    if( a && R && l)
    {
        if(filesize > 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                cout << filenames[i] << ":" << endl;
                Rflag(filenames[i], true, true);
                cout << endl;
            }
        }
        else
        {
            Rflag(dot.c_str(), true, true);
        }
    }*/
    return 0;
}
