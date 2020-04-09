#include "ff_shell.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
extern char ** environ;
// main loop when user uses myshell program, get every stdin('command') from users
void ff_shell::input() {
  while (true) {
    //if (!my_var.empty()){
      //std::cout << "**************" << std::endl;
      //for (std::unordered_map<std::string, std::string>::iterator it = my_var.begin(); it!= my_var.end(); ++it){
	//std::cout << (*it).first << " = " << (*it).second <<std::endl;
	//}
      //};

    std::string command;
    std::cout << "ffosh:" << shell_pwd << " $";
    getline(std::cin, command);
    if (std::cin.eof()) {
      std::cout << std::endl;
      //exit(EXIT_SUCCESS);
      return;
      };
    if (strcmp(command.c_str(), "exit") == 0) {
      //exit(EXIT_SUCCESS);
      return;
    };
    size_t n = 0;
    for (size_t i = 0; i < command.size(); i++) {
      if (command[i] == ' ') {
	n++;
      }
      else {
	continue;
      }
    }
    if (n == command.size()) {
      continue;
    };
    if (!command.empty()) {
      command_h = new command_handler(command);
      command_h->parse();
      //set!!!!
      if (!strcmp(command_h->arg[0].c_str(), "set")){
	var_set();
      	continue;
      }
      
      if (!strcmp(command_h->arg[0].c_str(), "export")){
	var_export();
	continue;
      }
      
      if (!strcmp(command_h->arg[0].c_str(), "rev")){
	var_rev();
	continue;
      }
      
      var_replace();
      //std::cout << "after var replacement" << std::endl;
      //int m = 0;
      //while(!command_h->arg[m].empty()){
      //	std::cout << "element " << m << ": " << command_h->arg[m] << std::endl;
      //++m;
      //}
      
      if (command_h->arg[0].find("/") == std::string::npos) { 
	command_h->when_notslash(":");
      }
      else{
	command_h->slash_contain("/");
      }
      if (command_h->qfork == 1){
	shell_pwd = command_h->pwd;
	delete command_h;
	continue;
      };
      
      cpid = fork();
      
      print_exit_info(command_h->full_path_command);
      delete command_h;
    } 
    else {
      continue;
    };
  }
}

// this method can print important status of the program about how it returns or whether it met problems
void ff_shell::print_exit_info(std::string full_path_command) {
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  };
  if (cpid == 0) { /* Code executed by child */
    execute(full_path_command);
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

// invoke systems call 'execve', preparing all required arguments for it: arguments, environment
// free the arguments buffer when executed over.
void ff_shell::execute(std::string full_path_command) {
  char * arg = (char *)malloc((full_path_command.size() + 1) * sizeof(*arg));
  char * newargv[200] = {};
  int m = 0;
  std::strcpy(arg, full_path_command.c_str());
  while(!command_h->arg[m].empty()){
    newargv[m] = (char *)malloc((command_h->arg[m].size() + 1) * sizeof(newargv[m]));
    strcpy(newargv[m], command_h->arg[m].c_str());
    m++;
  }
  execve(arg, newargv, environ); // extern char ** environ; 
  perror("execve");
  //std::cout << "execve error" << std::endl;
  free(arg);
}


// set the variable in a map and map saves the key-value pair until user quits the program
// this method deeply manipulate the fields existed in frined class command_handler
void ff_shell::var_set(){//modify origin_command
  //command_h->arg[1] keep
  if(command_h->arg[2].empty()){
    std::cout << "here should be one more argument" << std::endl;
    return;
  }

  int found_arg0 = command_h->origin_command.find(command_h->arg[0]); // erase 'set'
  command_h->origin_command.erase(found_arg0, command_h->arg[0].size());
  int found_arg1 = command_h->origin_command.find(command_h->arg[1]); // erase '$var1' 
  command_h->origin_command.erase(found_arg1, command_h->arg[1].size()); 
  while(command_h->origin_command[0] == ' ' || command_h->origin_command[0] == '\"' ){
    command_h->origin_command.erase(0,1);
  }
  command_h->arg[2] = command_h->origin_command;

  for (size_t n = 0; n < command_h->arg[1].size(); ++n){
    if (command_h->arg[1][n] -32 < 0){
      std::cout << "invalid variable name" << std::endl;
      return;
    }; 
    if (command_h->arg[1][n] -0 >= 33 && command_h->arg[1][n] -0 <= 47 ){
      //qfork = 1;
      std::cout << "invalid variable name" << std::endl;
      return;
    };
    if (command_h->arg[1][n] -0 >= 58 && command_h->arg[1][n] -0 <= 64){
      //qfork = 1;
      std::cout << "invalid variable name" << std::endl;
      return;
    };
    if ((command_h->arg[1][n] -0 >= 91 && command_h->arg[1][n] -0 <= 94) || (command_h->arg[1][n] -0 == 96)){
      //qfork = 1;
      std::cout << "invalid variable name" << std::endl;
      return;
    };
    if (command_h->arg[1][n] -0 >= 123){
      //qfork = 1;
      std::cout << "invalid variable name" << std::endl;
      return;
    };
  }
  
  my_var[command_h->arg[1]] = command_h->arg[2];
  command_h->arg[3] = "";
}

// replace the variable value in arguments buffer, which is going to enter 'execve' systems call 
void ff_shell::var_replace(){
  int n = 0;
  while(!command_h->arg[n].empty()){
    for (auto it = my_var.begin(); it!= my_var.end(); ++it){
      if(command_h->arg[n].find("$"+ it->first) != std::string::npos){
	int find = command_h->arg[n].find("$" + it->first);
	command_h->arg[n].erase(find, it->first.size()+1);
	command_h->arg[n].insert(find, it->second);
      }	  
    }
    ++n;
  }
}

// update the varibale name - value pair into the environment path
// so the third argument is alway 1: it supports overwriting
void ff_shell::var_export(){
  if (command_h->arg[2].empty()){
    for (auto it = my_var.begin(); it!= my_var.end(); ++it){
      if (!strcmp(command_h->arg[1].c_str(), it->first.c_str())){
	setenv(it->first.c_str(), it->second.c_str(), 1);
	return;
      }
    }
  }
  std::cout << "export fail: variable error" << std::endl;
}

// reverse the value (the value is saved in the second argument buffer in my data structure)
void ff_shell::var_rev(){
  if (command_h->arg[2].empty()){ 
    for (auto it = my_var.begin(); it!= my_var.end(); ++it){
      if (!strcmp(command_h->arg[1].c_str(), it->second.c_str())){
	std::reverse(it->second.begin(), it->second.end());
	return;
      }
    }
  }
  std::cout << "rev fail: variable error" << std::endl;
}


