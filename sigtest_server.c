#include "netlib.h"


int *argc_;
char ***argv_;
char ***envp_;

void
sigHangupHandler(int sig)
{
     err_print("sigHangupHandler(%d)\n",sig);
     if ((execve((*argv_)[0],(*argv_),(*envp_))) == -1) {
          err_sys("execve");
     }
}


int main(int argc, char *argv[],char *envp[])
{

     int sock;
     if (argc <= 1) {
          err_quit("sigtest_server <host address> <port#>\n");
     }

     argc_ = &argc;
     argv_ = &argv;
     envp_ = &envp;

     Signal(SIGCHLD, sig_chld);
     
     err_print("Signal():end\n");
     
     sock = server_socket(argv[1],argv[2]);

     accept_loop(sock);

     close(sock);
               
     return 0;
}
