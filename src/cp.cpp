#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <istream>
#include <ostream>
#include <errno.h>
#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <Timer.h>


using namespace std;

void instream(const char *input, const char *output)
{
   // char in[1024];
    struct stat s;

    if((stat(input, &s)) == -1)
    {
        perror("Error in Stat");
    }
    if((stat(output, &s)) != -1)
    {
        perror("File already Exists");
    }
    ifstream in (input);
    ofstream out(output);

    if(in.is_open())
    {
        char c = in.get();
        while(!in.eof())
        {
            out.put(c);
            c = in.get();
        }
    }
    in.close();
    out.close();
    return;

}

void readclose(const char *input, const char *output)
{
    int in;
    struct stat s;
    if((stat(input, &s)) == -1)
    {
        perror("Error in Stat");
    }
    if((stat(output, &s)) != -1)
    {
        perror("File already Exists");
    }
    if((in = open(input, O_RDONLY)) == -1)
    {
        perror("Error Opening");
    }
    int out;
    if((out = open(output, O_RDWR |  O_CREAT, 0644)) == -1)
    {
        perror("Error Opening Write");
    }
    
    size_t inp, outp;
    char *buffer[1];
    size_t bytes = 1;


    while((inp = read(in, &buffer, bytes)) > 0)
    {
        outp = write(out,&buffer,(ssize_t) inp);
        if(inp != outp)
        {
            perror("write");
        }
        
    }

    close(in);
    close(out);

    return;
}

void readclose_buf(const char *input, const char *output)
{
    int in;
    struct stat s;
    if((stat(input, &s)) == -1)
    {
        perror("Error in Stat");
    }
    if((stat(output, &s)) != -1)
    {
        perror("File already Exists");
    }
    if((in = open(input, O_RDONLY)) == -1)
    {
        perror("Error Opening");
    }
    int out;
    if((out = open(output, O_RDWR |  O_CREAT, 0644)) == -1)
    {
        perror("Error Opening Write");
    }
    
    size_t inp, outp;
    char *buffer[BUFSIZ];
    size_t bytes = BUFSIZ;


    while((inp = read(in, &buffer, bytes)) > 0)
    {
        outp = write(out,&buffer,(ssize_t) inp);
        if(inp != outp)
        {
            perror("write");
        }
        
    }

    close(in);
    close(out);

    return;
}

int main(int argc, char** argv)
{
    if(argc < 3 || argc > 4)
    {
        cout << "Usage: ./cp <source> <destination> [optional test]" << endl;
        return 1;
    }

    Timer t;
    double etime;


    if(argc == 3)
    {
       t.start();
       instream(argv[1], argv[2]);  
       t.elapsedUserTime(etime);
       cout << "time for put and get: " << etime << endl;

       t.start();
       readclose_buf(argv[1], argv[2]);
       t.elapsedUserTime(etime);
       cout << "time for the read and write buffer: " << etime << endl;

       t.start()
       readclose(argv[1], argv[2]);
       t.elapsedUserTime(etime);
       cout << "Time for the read and write char: " << etime << endl;

    }
    
    if(argc == 4)
    {

    }
    return 0;
}

