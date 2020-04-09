# include<cstdio>
# include<cstdlib>
# include<iostream>
# include<string>
# include<string.h>
# include<fstream>
# include<sstream>
# include<dirent.h>
# include <unordered_map>

unsigned hash(const std::string & str){
  unsigned ans = 0;
  std::ifstream f(str);
  std::string s;
  while(getline(f, s)){
    std::stringstream ss;
    unsigned num = 0;
    ss << s;
    ss >> num;
    ans = 107*ans + num;
  }
  return ans;
}

std::string Read_file(std::string & file_name){
  std::ifstream f;
  f.open(file_name, std::ifstream::in);
  if (f.fail()){
    std::cout << file_name << std::endl;
    throw std::invalid_argument("Cannot Open File");
  }
  std::string curr;
  std::string s;
  while(getline(f,s)){
    if (f.fail()){
      std::cout << s << std::endl;
      throw std::invalid_argument("Cannot Read This File");
    }
    curr = curr + s;
  }
  return curr;
}


void dedup(const char * name, std::unordered_map<size_t, std::string> &map) {
  DIR * dir;
  struct dirent * entry;
  dir = opendir(name);
  if (dir == NULL){
    std::cerr << "Cannot Open Directory" << std::endl;
    exit(EXIT_FAILURE);
  }
  else{
    while((entry = readdir(dir)) != NULL) {
      std::string dir_s(name); //initialize
      int i = dir_s.length();
      if (i > 0 && dir_s[i-1]!= '/'){
	dir_s = dir_s + '/';
      }
      std::string dir_name(entry->d_name);
      std::string fullname = dir_s + dir_name;
      // symlink
      if (entry->d_type == DT_LNK){
	continue;
      }
      // if dir, need to find regular inside 
      else if(entry->d_type == DT_DIR){
	//"." or ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
          continue;
        }
        else {
          dedup(fullname.c_str(), map); // convert
        }
      }
      //regular file
      else if(entry->d_type == DT_REG){
	std::string file = Read_file(fullname);
	std::hash<std::string> myHash;
	size_t key = myHash(file);
	std::unordered_map<size_t, std::string>::const_iterator it = map.find(key);
	if (it != map.end()) {
          std::cout << "#Removing " << fullname << " (duplicate of " << it->second << ")."
                    << std::endl;
          std::cout << "rm " << fullname << std::endl;
        }
        else {
          map.insert(std::pair<size_t, std::string>(key, fullname));
        }
      }
      else{
	std::cerr << "wrong file type: " << fullname << std::endl;
      }
    }
  }	
  closedir(dir);
}


int main(int argc, char ** argv){
  if (argc <= 1){
    std::cerr << "No path!"<< std::endl;
    return EXIT_FAILURE;
  };
  std::cout<< "#!/bin/bash" << std::endl;

  std::unordered_map<size_t, std::string> map;
  for (int i = 1; i < argc; i++){
    dedup(argv[i], map);
  }
  return EXIT_SUCCESS;
}
