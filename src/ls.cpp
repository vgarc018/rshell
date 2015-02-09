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


void colorOut(const char *filepath, const char *file)
{
    string black = "\033[30m";
    string red =  "\033[31m";
    string green = "\033[32m";
    string yellow = "\033[33m";
    string blue ="\033[34m";
    string gray   = "\033[47m";
    string teal = "\033[36m";
    string white = "\033[37m";
    string reset = "\033[0m ";
    
    struct stat s;
    if((stat(filepath, &s) == -1))
    {
        perror("Error in Stat");
    }
    if(s.st_mode & S_IFDIR)
    {
        cout << blue << file << reset << " ";
    }
    else if(s.st_mode & S_IXUSR)
    {
        cout << green << file << reset << " ";
    }
    else if(file[0] == '.' && (s.st_mode & S_IFDIR))
    {
        cout << blue << file << reset << " ";
    }
    else if(file[0] == '.' && (s.st_mode & S_IXUSR))
    {
        cout << green << file << reset << " ";
    }
    else if(file[0] == '.')
    {
        cout << gray << file << reset << " ";
    }
    else
    {
        cout << file << " ";
    }
}

void notDir(const char *file, char flag)
{
    struct stat s;
   //:wq cout << "in not dir" << endl;
  // cout << file << endl;
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
             colorOut(file, file);
        }   
        else
        {
            colorOut(file, file);
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
        	char filepath[1024];
		    strcpy(filepath, file);
            string slash = "/";
            strcat(filepath, slash.c_str());
            strcat(filepath, entry->d_name);
 
            colorOut(filepath,entry->d_name);
            //cout << endl;
        }
        if(errno != 0)
        {
             perror("reading file");
             return;
        }

    }
    cout << endl;
    cout << endl;
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
        	    char filepath[1024];
		        strcpy(filepath, file);
                string slash = "/";
                strcat(filepath, slash.c_str());
                strcat(filepath, entry->d_name);
        
               colorOut(filepath, entry->d_name);
               // cout << entry->d_name << endl;
           }
        }
        if(errno != 0)
        {
            perror("reading file");
            return;
        }
    }
    cout << endl;
    cout << endl;
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
                            colorOut(filepath, entry->d_name);
						    cout << endl;
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
								colorOut(filepath, entry->d_name);
                                cout <<  endl;
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
		
		colorOut(filepath, entry->d_name);
        cout << endl;
		
		if(S_ISDIR(s.st_mode))
		{
			dirs.push_back(entry->d_name);
		}
	}
	if(errno != 0)
	{
		perror("reading Dir");
	}
    cout << endl;	
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

void aRflag(const char *filename)
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
       	colorOut(filepath, entry->d_name);
        cout << endl;
		
		if( entry->d_name[0] == '.' ||  entry->d_name[1] == '.')
		{
			continue;
		}
		
		if(S_ISDIR(s.st_mode))
		{
			dirs.push_back(entry->d_name);
		}
	}
	if(errno != 0)
	{
		perror("reading Dir");
	}
    cout << endl;	
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

void alRflag(const char *filename)
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

				cout << ((S_ISDIR(s.st_mode)) ? "d":"-");
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
                colorOut(filepath, entry->d_name);
				cout << endl;
			}	
		if(entry->d_name[0] == '.' || entry->d_name[1] == '.')
		{
			continue;
		}
		else
		{
			if(S_ISDIR(s.st_mode))
			{
				dirs.push_back(entry->d_name);
			}
		}
	}
	if(errno != 0)
	{
		perror("reading Dir");
	}
    cout << endl;	
	int vecsize = dirs.size();
	
	for(int i = 0; i < vecsize; ++i)
	{
		char filepath[1024];
		strcpy(filepath, filename);
        string slash = "/";
        strcat(filepath, slash.c_str());
        strcat(filepath, dirs[i]);
        alRflag(filepath);
	}
	if((closedir(dir) == -1))
	{
		perror("Closing Dir");
	}
	
	return;

}


void lRflag(const char *filename)
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
        
       if(entry->d_name[0] == '.' || entry->d_name[1] == '.')
		{
			continue;
		}
       
        if((stat(filepath, &s)) == -1)
        {
			perror("Stat Error");
		}
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

				cout << ((S_ISDIR(s.st_mode)) ? "d":"-");
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
                colorOut(filepath, entry->d_name);
				cout <<  endl;
			}
		
		if(S_ISDIR(s.st_mode))
		{
			dirs.push_back(entry->d_name);
		}
	}
	if(errno != 0)
	{
		perror("reading Dir");
	}
    cout << endl;	
	int vecsize = dirs.size();
	
	for(int i = 0; i < vecsize; ++i)
	{
		char filepath[1024];
		strcpy(filepath, filename);
        string slash = "/";
        strcat(filepath, slash.c_str());
        strcat(filepath, dirs[i]);
        lRflag(filepath);
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

   // cout << filenames[0] << endl;
    int filesize = filenames.size();
    if(!a && !l && !R)
    {
        if(filesize >= 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                if(filesize > 1) cout << filenames[i] << ":" << endl;
                noFlags(filenames[i]);
            }
        }
        else
        {
            noFlags(dot.c_str());
        }
    }

    if( l && !a && !R)
    {
         if(filesize >= 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                if(filesize > 1) cout << filenames[i] << ":" << endl;
                lFlag(filenames[i], false);
            }
        }
        else
        {
            lFlag(dot.c_str(), false);
        }
    }

    if( R && !a && !l)
    {
         if(filesize >= 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
               if(filesize> 1) cout << filenames[i] << ":" << endl;
                Rflag(filenames[i]);
            }
        }
        else
        {
            Rflag(dot.c_str());
        }
    }
    
    if( a && !l && !R)
    {
        if(filesize >= 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
               if(filesize > 1) cout << filenames[i] << ":" << endl;
                aFlag(filenames[i]);
            }
        }
        else
        {
            aFlag(dot.c_str());
        }
    }
    
    if(a && l && !R)
    {
        if(filesize >= 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                if(filesize > 1) cout << filenames[i] << ":" << endl;
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
        if(filesize >= 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                if(filesize >1) cout << filenames[i] << ":" << endl;
                aRflag(filenames[i]);
                cout << endl;
            }
        }
        else
        {
            aRflag(dot.c_str());
        }
    }
    
    if(R && l && a)
    {
         if(filesize >= 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                if(filesize > 1) cout << filenames[i] << ":" << endl;
                alRflag(filenames[i]);
            }
        }
        else
        {
            alRflag(dot.c_str());
        }
    }
    if( !a && R && l)
    {
        if(filesize >= 1)
        {
            for(int i = 0; i < filesize; ++i)
            {
                if(filesize > 1) cout << filenames[i] << ":" << endl;
                lRflag(filenames[i]);
            }
        }
        else
        {
            lRflag(dot.c_str());
        }
    }
    
    return 0;
}
