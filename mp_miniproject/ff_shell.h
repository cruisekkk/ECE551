#include <sys/wait.h>
#include "command_handler.h"
#include <cstring>
#include <string>
#include <iostream>
#include <unordered_map>
extern char ** environ;

// ff_shell is created when user get into ./myshell
// it cludes another class as a field to manipulate parsing part (command_handler)
// it involves an unordered_map to save variable-value information
class ff_shell
{
  // all fileds should be private properties of the object.    
  // we cannot call it internally.                                        
  // it is a well-protected mechanism.                
 private:
  pid_t cpid;
  pid_t w;
  int status;
  command_handler * command_h;
  std::unordered_map<std::string, std::string> my_var;
  std::string shell_pwd;
  std::string shell_fullname;
 public:
    // constructor, init 551path 
  ff_shell() {
    shell_pwd = std::string(getenv("PWD"));
    const char * PATH = getenv("PATH");
    setenv("ECE551PATH", PATH, 0);
    my_var = std::unordered_map<std::string, std::string>();
  }
  /* void input() is the entrance of every object of my shell class, the only p	\
ublic method in my class                                                        
   input() received stdin from users and it can receive pure whitespaces to c\
ontinue wait other commands. It can catch 'exit' and EOF to exit out.           
   if the command is qualified, the method would apply fork()                 
   and then it will pass the command into print_exit_info() method to continu\
e operation.
  */                                                                    
 public:
  void input();
 private:
  /* private methods, only input method can drive it.                           
   print_exit_info will receive the commands from user and print out hints ab	\
  out the status of the program and child programs.                               
   when cpid = 0, child program should be executed, so it passes the command \
  string into execute method below.
  */
  void print_exit_info(std::string full_path_command);
  // receive the command from the last method, clear memory in the heap         
  // execute the command accrodingly.
  void execute(std::string full_path_command);
  // variable manipulation and filtering
  void var_set();
  void var_replace();
  void var_export();
  void var_rev();
};




