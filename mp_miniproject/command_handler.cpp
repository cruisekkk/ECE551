#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "command_handler.h"
//methods of class command_handler

// parsing
// decide if there is a valid command (e.g. it can have unmatched ")
// solving the problem of escaping for "\" and "
// save the correct outcome into arguments buffer(so this method includes position conditions) 

void command_handler::parse(){
  std::string temp_cmd = origin_command.substr();
  while(temp_cmd[0] == ' '){
    temp_cmd.erase(0,1);
  } // the starting whitespaces

  std::string temp_cmd2 = origin_command.substr();
  int pureslash = 0;
  int escape_slash = 0;
  int pos = 0;
  while(temp_cmd2.find("\"") != std::string::npos){
    pos = temp_cmd2.find("\"");
    temp_cmd2.erase(0, pos+1);
    pureslash++;
  }
  std::string temp_cmd3 = origin_command.substr();
  while(temp_cmd3.find("\\\"") != std::string::npos){
    pos = temp_cmd3.find("\\\"");
    temp_cmd3.erase(0, pos+2);
    escape_slash++;
  }
  if ((pureslash - escape_slash) % 2 == 1){
    std::cout << "unmatched \"" << std::endl;
    qfork = 1;
    return;
  }
  
  int n = 0;
  for(size_t i = 0; i < temp_cmd.size(); ++i){
    if(temp_cmd[i] == '\"'){
      i++;
      // in the "  " loop
      while(temp_cmd[i] != '\"'){
	if (temp_cmd[i] == '\\' ){
	  if (temp_cmd[i+1] == '\"' || temp_cmd[i+1] == '\\'){
	    arg[n] += temp_cmd[i+1];
	    i = i + 2;
	    continue;
	  }
	  else{
	    arg[n] += temp_cmd[i];
	    i++;
	    continue;
	  };
	};
	arg[n] += temp_cmd[i];
	i++;
      }
      continue;
    }
    
    if(temp_cmd[i] == ' '){
      while(temp_cmd[i+1] == ' '){
	++i;
	}
      ++n;
      continue;
    } // next element, ignore the whitespaces
    if (temp_cmd[i] == '\\' ){
      if (temp_cmd[i+1] == '\"' || temp_cmd[i+1] == '\\' || temp_cmd[i+1] == ' '){
	arg[n] += temp_cmd[i+1];
	i = i + 1;
	continue;
      }
      else{
	continue;
      }
    }
    
    arg[n] += temp_cmd[i];
  }
  //int m = 0;
  //std::cout << "before var filtering" << std::endl;
  //while(!arg[m].empty()){
  //  std::cout << "element " << m << ": " << arg[m] << std::endl;
  //  ++m;
  //}
  return;
}

// using 'lstat' to search if there is a valid command in environment path
// mark is always '/'
void command_handler::slash_contain(const char * mark){
  struct stat st;
  int mapping = lstat(arg[0].c_str(), &st);
  full_path_command = arg[0];
  if(mapping == -1){
    std::cout << "Command " << arg[0] << " not found" << std::endl;
    qfork = 1;
    return;
  }
  if (!(st.st_mode & ~S_IFMT & S_IXUSR)) {
    //std::cerr << full_path_command << " Permission denied" << std::endl;
    qfork = 0;
    return; 
  }
  qfork = 0;
  return;
}

// the processing when command does not have slash
// mark is always ':', seperating path 
void command_handler::when_notslash(const char * mark){
  
  if(!strcmp(arg[0].c_str(), "cd")){
    cmd_cd();
    return;
  };
  
  // the situation when there is not "/" in the path
  if(arg[0].find("/") == std::string::npos){
    std::string dirlist = getenv("PATH");
    //dirlist = dirlist + ":/usr/cai";
    const char * str = dirlist.c_str();
    char * dirs_inlist[200] = {0};
    dirs_inlist[0] = strtok((char*)str, mark);
    for (int i = 1; dirs_inlist[i - 1] != NULL; i++) {
      dirs_inlist[i] = strtok(NULL, mark);
    };
    
    for (int i = 0; dirs_inlist[i] != NULL; i++) {
      full_path_command = std::string(dirs_inlist[i])  + "/" + arg[0];
      struct stat st;
      int mapping = lstat(full_path_command.c_str(), &st);
      if(mapping == -1){
	qfork = 1;
	continue;
      }
      if (!(st.st_mode & ~S_IFMT & S_IXUSR)) {
	std::cerr << full_path_command << "Permission denied" << std::endl;
	qfork = 0;
	continue; 
      }
      qfork = 0;
      return;
    }
  }
  std::cout << "Command " << arg[0] << " not found" << std::endl;
  //exit(EXIT_FAILURE);
  qfork = 1;
}

// processing part in cd
// only use the information in arguments buffer
void command_handler::cmd_cd(){
  qfork = 1;
  //situation 1: cd
  if (arg[1].empty()) {  
    std::cout << "cd Need a path" << std::endl;
    return;
  }
  
  //situation 2: cd ..
  else if (!arg[1].empty() && arg[2].empty()) {  //cd has path followed
    const char * toPath = arg[1].c_str();
    if (chdir(toPath) != 0) {
      perror("bash");
      return;
    }
    else {
      char temp[200] = {}; //= get_current_dir_name();//getenv("PWD");
      getcwd(temp,200);
      pwd = std::string(temp);
      //free(temp);
      return;
    }
  }
  //situation 3: cd .. extraprogram
  else {
    std::cout << " cd: too many arguments" << std::endl;
    return;
  }  
}  
