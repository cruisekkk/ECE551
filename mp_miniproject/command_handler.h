//#ifndef _COMMAND_HANDLER_H_
//#define _COMMAND_HANDLER_H_

#include <cstring>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
// This is the class I defined to provide information to class ff_shell
// This class processes the command user type in.
// It is in char of parsing the arguments, searching and changing path 
class command_handler{
 public:
  // qfork is a variable representing whether the program should fork;          
  // if qfork = 0, fork; if qfork = 1, not fork                                 
  bool qfork = 0;
  // absolute path + command 
  std::string full_path_command;
 private:
  // the exact command user typed in 
  std::string origin_command;
  // arguments buffer
  std::string arg[200] = {};
  // working dir
  std::string pwd;


  public:
  command_handler(){}
  ~command_handler(){}
 command_handler(std::string cmd): origin_command(cmd){pwd = getenv("PWD");}
  // parsing the field of the class: origin_command, then put the correct outcome into another field: arguments buffer. the buffer size i set is 200.
  void parse();
  // when the command has slash(/), shell only look in the specified directory, and it could be relative or absolute path
  void slash_contain(const char * mark);
  //search each directory specified in the ECE551PATH (in order) for the specified program.
  void when_notslash(const char * mark);
  //changin dir
  void cmd_cd();
  // ff_shell class can easily manipulate the object of command_handler
  friend class ff_shell;
};
  
//#endif
