#include<vector>
#include<unistd.h>
#include<signal.h>
#include<iostream>
#include <sys/types.h>
#include <sys/wait.h>


int input_to_a3(void)
{

    while(!std::cin.eof())
    {

        std::string input;
        std::getline(std::cin,input);
        if(input.size()>0)
            std::cout<<input<<std::endl;
    }
    return 0;
}

int main(int argc, char **argv)
{

    std::vector<pid_t> kids;
    pid_t child_pid;
    // create a pipe
    int pipe_from_rgen_to_a1[2];
    pipe(pipe_from_rgen_to_a1);

    int pipe_from_a1_to_a2[2];
    pipe(pipe_from_a1_to_a2);


    child_pid = fork();
    if(child_pid == 0)
    {
        // redirect stdout to the pipe

        dup2(pipe_from_rgen_to_a1[1],STDOUT_FILENO);
        close(pipe_from_rgen_to_a1[0]);
        close(pipe_from_rgen_to_a1[1]); //Close pipe
        execv("rgen",argv);
        perror("Error: Execution of rgen failed");
        return 1;
    }

    else if (child_pid<0)
    {
        std::cerr<<"Error: forking of rgen failed"<<std::endl;
        return 1;

    }
    kids.push_back(child_pid);


    child_pid = fork();
    if(child_pid == 0)
    {

        char *arg1[3];
        arg1[0]= (char*)"python";
        arg1[1]=(char*)"ece650-a1.py";
        arg1[2]=nullptr;
        // redirect stdin from the pipe
        dup2(pipe_from_rgen_to_a1[0],STDIN_FILENO);
        close(pipe_from_rgen_to_a1[1]);
        close(pipe_from_rgen_to_a1[0]);

        dup2(pipe_from_a1_to_a2[1],STDOUT_FILENO);
        close(pipe_from_a1_to_a2[0]);
        close(pipe_from_a1_to_a2[1]);
        execvp("python",arg1);
        perror("Error: Execution of a1-ece650.py failed");
        return 1;
    }
    else if(child_pid<0)
    {
        std::cerr<<"Error: forking of a1-ece650.py failed"<<std::endl;
        return 1;
    }
    kids.push_back(child_pid);


    child_pid = fork();
    if(child_pid == 0)
    {
        //redirect stdout to the pipe
        dup2(pipe_from_a1_to_a2[0],STDIN_FILENO);
        close(pipe_from_a1_to_a2[1]);
        close(pipe_from_a1_to_a2[0]);
        execv("ece650-a2",argv);
        perror("Error: execution of a2-ece650 failed");
        return 1;
    }
    else if(child_pid<0)
    {
        std::cerr<<"Error: forking of a2-ece650 failed"<<std::endl;
        return 1;
    }
    kids.push_back(child_pid);


    child_pid = fork();
    if(child_pid == 0)
    {

        dup2(pipe_from_a1_to_a2[1],STDOUT_FILENO);
        close(pipe_from_a1_to_a2[0]);
        close(pipe_from_a1_to_a2[0]);

        dup2(pipe_from_a1_to_a2[1],STDOUT_FILENO);
        close(pipe_from_a1_to_a2[0]);
        close(pipe_from_a1_to_a2[1]);

        return input_to_a3();
    }
    else if(child_pid<0)
    {
        std::cerr<<"Error: forking of a3 failed"<<std::endl;
        return 1;
    }
    kids.push_back(child_pid);

    int check;
    wait(&check);

    //send kill signal to all children
    for(pid_t k:kids)
    {
        int status;
        kill(k,SIGTERM);
        waitpid(k,&status,0);
    }

    return 0;
}
