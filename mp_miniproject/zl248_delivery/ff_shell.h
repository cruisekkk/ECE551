#include <sys/wait.h>

#include <cstring>
#include <string>

class ff_shell
{
  // all fileds should be private properties of the object.
  // we cannot call it internally.
  // it is a well-protected mechanism.
 private:
  pid_t cpid;
  pid_t w;
  int status;

 public:
  ff_shell(){};
  // void input() is the entrance of every object of my shell class, the only public method in my class
  // input() received stdin from users and it can receive pure whitespaces to continue wait other commands. It can catch 'exit' and EOF to exit out.
  // if the command is qualified, the method would apply fork()
  // and then it will pass the command into print_exit_info() method to continue operation.
 public:
  void input() {
    while (true) {
      std::string command;
      std::cout << "ffosh$ ";
      getline(std::cin, command);
      if (std::cin.eof()) {
        std::cout << std::endl;
        exit(EXIT_SUCCESS);
      };
      if (strcmp(command.c_str(), "exit") == 0) {
        exit(EXIT_SUCCESS);
      };
      int n = 0;
      for (int i = 0; i < command.size(); i++) {
        if (command[i] == ' ') {
          n++;
        }
        else {
          break;
        }
      }
      if (n == command.size()) {
        continue;
      };
      if (!command.empty()) {
        cpid = fork();
        print_exit_info(command);
      }
      else {
        continue;
      };
    }
  }

 private:
  // private methods, only input method can drive it.
  // print_exit_info will receive the commands from user and print out hints about the status of the program and child programs.
  // when cpid = 0, child program should be executed, so it passes the command string into execute method below.
  void print_exit_info(std::string command) {
    if (cpid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    };
    if (cpid == 0) { /* Code executed by child */
      //std::cout<< "Child PID is" << getpid()<< std::endl; // for check
      execute(command);
      exit(EXIT_FAILURE);
    }
    else {
      do {
        w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
        if (w == -1) {
          perror("waitpid");
          exit(EXIT_FAILURE);
        };
        if (WIFEXITED(status)) {
          if (WEXITSTATUS(status) == 0) {
            std::cout << "Program was successful " << std::endl;
          }
          else {
            std::cout << "Program failed with code " << WEXITSTATUS(status) << std::endl;
          }
        }
        else if (WIFSIGNALED(status)) {
          std::cout << "Terminated by signal " << WTERMSIG(status) << std::endl;
        }
      } while (!WIFEXITED(status) && !WIFSIGNALED(status));
      { return; }
    }
  }
  // receive the command from the last method, clear memory in the heap
  // execute the command accrodingly.
  void execute(std::string command) {
    char * arg = (char *)malloc((command.size() + 1) * sizeof(*arg));
    char * newargv[] = {NULL};
    char * newenviron[] = {NULL};
    std::strcpy(arg, command.c_str());
    newargv[0] = arg;
    execve(arg, newargv, newenviron);
    perror("execve");
    free(arg);
  }
};
