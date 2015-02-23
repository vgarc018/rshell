#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <errno.h>
#include <stdio.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <istream>
#include <queue>
#include <cstdio>
#include <string.h>
#include <fcntl.h>

using namespace std;
using namespace boost;

vector<string> p;

int cexec(char** cmds)
{
    size_t pid = fork();
    unsigned err = -1;
    if(pid == err)
    {
        perror("Error in fork");
        exit(2);
    }
    if(pid == 0)
    {
        size_t ex = execvp(cmds[0],cmds);
        unsigned int noter = 0;
        if(ex != noter)
          perror("Error in exec");
        exit(1);
    }
    else
    {
        int x;
      if(wait(&x) == -1)
      {
          perror("Error in Wait");
          exit(3);
      }
        return x;
    }
}


void parsing(string & x)
{
    typedef tokenizer<char_separator<char> > mytok;
    string backup = x;
    vector<char**> cmd;
    vector<string> tok;
    vector<string> tok2;
    vector<string> tok3;
    vector<string> lines;
    queue<string> connectors;
    char_separator <char> space (" ");
    mytok tokens1 (backup, space);
    for(mytok::iterator i = tokens1.begin(); i != tokens1.end(); ++i)
    {
        lines.push_back(*i);
    }

    for(unsigned int i =0; i < lines.size(); ++i)
    {
        size_t q, a,o;
        q = lines[i].find(";");
        a = lines[i].find("&&");
        o = lines[i].find("||");
        if(lines[i] == ";" || (q < o && q < a ) )
        {
            connectors.push(";");
        }
        if(lines[i] == "&&" || (a < q && a < o) )
        {
            connectors.push("&");
        }
        if(lines[i] == "||" ||  ( o < a && o < q) )
        {
            connectors.push("|");
        }

    }
    char_separator <char> s (";&&||");

    if(connectors.empty())
    {
        size_t i = 0;
        char** a = new char*[lines.size()+1];
        for(unsigned int k = 0; k < lines.size(); k++)
        {
            string temp = lines[i];
            a[i] = new char[temp.size()];
            strcpy(a[i], temp.c_str());
            ++i;
        }
            a[i] = NULL;
             //  delete [] a;
            cmd.push_back(a);
    }

    else
    {
        mytok tokens2(x,s);
        for(mytok::iterator i = tokens2.begin(); i != tokens2.end();++i)
        {
            tok.push_back(*i);
        }

        for(unsigned int k = 0; k < tok.size(); k++)
        {
             mytok tokens(tok[k], space);
             char** a = new char*[tok.size()+1];
             size_t i = 0;
             for(mytok::iterator j = tokens.begin(); j != tokens.end(); ++j)
             {
                 string temp = *j;
                 a[i] = new char[temp.size()];
                 strcpy(a[i], temp.c_str());
                 ++i;
             }
             a[i] = NULL;
             //  delete [] a;
             cmd.push_back(a);

        }
    }
    if(connectors.empty())
    {
        char** temp = cmd[0];
        cexec(temp);
        cmd.erase(cmd.begin());
        delete [] temp;
        return;
    }
    if(cmd.size() > connectors.size() && !(connectors.empty()))
    {
        connectors.push(";");
    }
  while(!connectors.empty())
  {
     char** temp = cmd[0];
     string s = "exit";
     const char* ex = s.c_str();
     if(connectors.front() == ";")
     {
        if(temp[0] == ex)
        {
            cout << "Thanks for using Rshell" << endl;
            exit(0);
        }

        if((sizeof temp / sizeof temp[0]) == 1 )
        {
            temp[1] = NULL;
        }
        cexec(temp);
        cmd.erase(cmd.begin());
        connectors.pop();
        delete [] temp;
        if(connectors.empty())
        {
           return;
        }
     }
     if(connectors.front() == "&")
     {
       if( cexec(temp) != 0)
       {
          return;
       }
       else
       {
            cmd.erase(cmd.begin());
            connectors.pop();
            delete []temp;
       }
     }
     if(connectors.front() == "|")
     {
       if( cexec(temp) == 0)
       {
           return;
       }
        cmd.erase(cmd.begin());
        connectors.pop();
        delete [] temp;
     }
  }
  return;

}

template <typename T>
void print(vector<T> &q)
{
    for(unsigned int i = 0; i < q.size(); i++)
    {
        cout << "q[i] = " << q[i] << endl; 
    }
}

void parsing_in(string s)
{
   typedef tokenizer<char_separator<char> > mytok;
    char_separator <char> space (" < ");
    mytok tokens1 (s, space);
    for(mytok::iterator i = tokens1.begin(); i != tokens1.end(); ++i)
    {
        p.push_back(*i);
    }
}

void input()
{
    string cmd = p.at(0);
    string file = p.at(1);
    int in;
    if((in = open(file.c_str(), O_RDONLY)) == -1)
    {
        perror("Error Opening");
    }
    int savedIn = dup(STDIN_FILENO);
    if(dup2(in, STDIN_FILENO) == -1)
    {
        perror("Error in Dup");
    }
    if(close(in) == -1)
    {
        perror("closing fd");
    }
    char *cmds[1];
    cmds[0] = new char[cmd.size()+1];
    strcpy(cmds[0], cmd.c_str());
    cexec(cmds);
    //delete [] cmds;
    if(dup2(savedIn,STDIN_FILENO) == -1)
    {
        perror("error in dup");
    }
    if(close(savedIn) == -1)
    {
        perror("Error in close");
    }
}

void parsing_out(string s)
{
   typedef tokenizer<char_separator<char> > mytok;
    char_separator <char> space (" > ");
    mytok tokens1 (s, space);
    for(mytok::iterator i = tokens1.begin(); i != tokens1.end(); ++i)
    {
        p.push_back(*i);
    }
}

void output()
{
    string cmd;
    string flag;
    string file;
    if(p.size() >= 3)
    {
        cmd = p[0];
        flag = p[1];
        file = p[2];
    }
    else
    {
        cmd = p[0];
        file = p[1];
    }

    int in;
    if((in = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
    {
        perror("Error Opening");
        return;
    }
    int savedOut = dup(STDOUT_FILENO);
    if(dup2(in, STDOUT_FILENO) == -1)
    {
        perror("Error in Dup");
        return;
    }
    if(close(in) == -1)
    {
        perror("closing fd");
    }
    if(p.size() == 2)
    {
        char *cmds[2];
        cmds[0] = new char[cmd.size()+1];
        strcpy(cmds[0], cmd.c_str());
        cmds[1] = NULL;
        cexec(cmds);    
    }
    else
    {
        char *cmds[3];
        cmds[0] = new char[cmd.size()+1];
        strcpy(cmds[0], cmd.c_str());
        cmds[1] = new char[flag.size()+1];
        strcpy(cmds[1], flag.c_str());
        cmds[2] = NULL;
        cexec(cmds); 
    }   //delete [] cmds;
    if(dup2(savedOut,STDOUT_FILENO) == -1)
    {
        perror("error in dup");
    }
    if(close(savedOut) == -1)
    {
        perror("Error in close");
    }
}


void parsing_out_two(string s)
{
    typedef tokenizer<char_separator<char> > mytok;
    char_separator <char> space (" >> ");
    mytok tokens1 (s, space);
    for(mytok::iterator i = tokens1.begin(); i != tokens1.end(); ++i)
    {
        p.push_back(*i);
    }
}

void output_two()
{
    string cmd;
    string flag;
    string file;
    if(p.size() >= 3)
    {
        cmd = p[0];
        flag = p[1];
        file = p[2];
    }
    else
    {
        cmd = p[0];
        file = p[1];
    }
    int in;
    if((in = open(file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
    {
        perror("Error Opening");
        return;
    }
    int savedOut = dup(STDOUT_FILENO);
    if(dup2(in, STDOUT_FILENO) == -1)
    {
        perror("Error in Dup");
        return;
    }
    if(close(in) == -1)
    {
        perror("closing fd");
    }
    if(p.size() == 2)
    {
        char *cmds[2];
        cmds[0] = new char[cmd.size()+1];
        strcpy(cmds[0], cmd.c_str());
        cmds[1] = NULL;
        cexec(cmds);    
        delete [] cmds;
    }
    else
    {
        char *cmds[3];
        cmds[0] = new char[cmd.size()+1];
        strcpy(cmds[0], cmd.c_str());
        cmds[1] = new char[flag.size()+1];
        strcpy(cmds[1], flag.c_str());
        cmds[2] = NULL;
        cexec(cmds); 
    }
    //delete [] cmds;
    if(dup2(savedOut,STDOUT_FILENO) == -1)
    {
        perror("error in dup");
    }
    if(close(savedOut) == -1)
    {
        perror("Error in close");
    }
}

void piping(string s)
{
    typedef tokenizer<char_separator<char> > mytok;
    char_separator <char> space (" | ");
    mytok tokens1 (s, space);
    vector<string> tokens;
    for(mytok::iterator i = tokens1.begin(); i != tokens1.end(); ++i)
    {
        tokens.push_back(*i);
    }
    print(tokens);   
    int fd[2];
    if( pipe(fd) == -1)
    {
        perror("error in pipe");
    }
    int pid = fork();
    if(pid == -1)
    {
        perror("error in fork");
    }
    int saveIn = dup(0);
    if(saveIn == -1) perror("Error in dup");
    int saveOut = dup(1);
    if(saveOut == -1) perror("Error in dup");
    if( pid == 0)
    {
        if(close(0) == -1) perror("close error");
        if(dup2(fd[1], 1) == -1) perror("dup2 error");
        if(close(fd[0]) == -1) perror("close error");
        string cmd = tokens[0];
        char *cmds[2];
        cmds[0] = new char[cmd.size()+1];
        strcpy(cmds[0], cmd.c_str());
        cmds[1] = NULL;
        cexec(cmds);
        //delete[] cmds;
    }
    else
    {
        wait(0);
        if(close(fd[1]) == -1) perror("error in close");
        if(close(1) == -1) perror("Error in close");
        if(dup2(fd[0], 0) == -1) perror("Error in dup2");
        string cmd = tokens[1];
        string flag = tokens[2];
        char *cmds[3];
        cmds[0] = new char[cmd.size()+1];
        strcpy(cmds[0], cmd.c_str());
        cmds[1] = new char[flag.size()+1];
        strcpy(cmds[1], flag.c_str());
        cmds[2] = NULL;
        cexec(cmds); 
        //delete [] cmds;
    }
}
int main(int argc, char** argv)
{
    string line;
  while(1)
  {
     char dir[1000];
     if(!getcwd(dir, 1000))
         perror("Error getcwd");

     char* login = getlogin();
     if(login == NULL)
        perror("userlogin");

      char host[200];
      if( gethostname(host, 200) == -1)
          perror("Hostname");
        
        cout << dir << endl;
        if(login)
        {
            cout << login << "@" << host << "$ ";
        }
        else
        {
            cout << "$ ";
        }
        bool noinoutpipe = true;
        getline(cin,line);
        size_t comment = line.find("#");
        if(comment != string::npos)
        {
            line.erase(line.find("#"));
        }
        if(line == "exit")
        {
            cout << "Thanks for using Rshell" << endl;
            exit(0);
        }
        size_t in = line.find("<");
        if(in != string::npos)
        {
            noinoutpipe = false;
            parsing_in(line);
            input(); 
        }
        size_t out = line.find(">");
        if(out != string::npos && (line[out+1] != '>'))
        {
            noinoutpipe = false;
            parsing_out(line);
            output(); 
        }
        size_t out_two = line.find(">>");
        if(out_two != string::npos)
        {
            noinoutpipe = false;
            parsing_out_two(line);
            output_two(); 
        }
        size_t pi = line.find("|");
        if(pi != string::npos && (line[out+1] != '|'))
        {
            noinoutpipe = false;
            piping(line);
        }

        if(noinoutpipe)
        {
            parsing(line);
        }
   }
    return 0;
}
