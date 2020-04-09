#include <ctype.h>
#include <grp.h>
#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// ***** Some examples provided from 'man lsta't are referenced in functions *****

// Conversion for Step 1
// Input: one argument; stat mode number, type->integer
// Output: file type should be printed, type->string
// **This function converts the stat mode(from printfunction) into file type names
char * convert_ftype(int mode) {
  char * ans;
  // File name mapping between 'mode' and filetype name
  switch (mode & S_IFMT) {
    case S_IFBLK:
      ans = "block special file";
      break;
    case S_IFCHR:
      ans = "character special file";
      break;
    case S_IFDIR:
      ans = "directory";
      break;
    case S_IFIFO:
      ans = "fifo";
      break;
    case S_IFLNK:
      ans = "symbolic link";
      break;
    case S_IFREG:
      ans = "regular file";
      break;
    case S_IFSOCK:
      ans = "socket";
      break;
    default:
      ans = "unknown?";
      break;
  }
  return ans;
}

// Conversion for Step 2
// Input: two arguments; stat struct, type->struct stat
// Input: empty 10 char's array(unfinished permission string), type->char[]
// Output: (converted 10 characters) string
// **This funciton converts the stat mode(from printfunciton)
// **into description of the permissions
char * convert_permis(struct stat sb, char permis_str[]) {
  switch (sb.st_mode & S_IFMT) {
      // First char conversion
    case S_IFBLK:
      permis_str[0] = 'b';
      break;
    case S_IFCHR:
      permis_str[0] = 'c';
      break;
    case S_IFDIR:
      permis_str[0] = 'd';
      break;
    case S_IFIFO:
      permis_str[0] = 'p';
      break;
    case S_IFLNK:
      permis_str[0] = 'l';
      break;
    case S_IFREG:
      permis_str[0] = '-';
      break;
    case S_IFSOCK:
      permis_str[0] = 's';
      break;
    default:
      fprintf(stderr, " unknown mode");
      break;
  }

  if ((sb.st_mode & S_IRUSR) != 0) {
    permis_str[1] = 'r';
  }
  else {
    permis_str[1] = '-';
  }

  if ((sb.st_mode & S_IWUSR) != 0) {
    permis_str[2] = 'w';
  }
  else {
    permis_str[2] = '-';
  }

  if ((sb.st_mode & S_IXUSR) != 0) {
    permis_str[3] = 'x';
  }
  else {
    permis_str[3] = '-';
  }

  if ((sb.st_mode & S_IRGRP) != 0) {
    permis_str[4] = 'r';
  }
  else {
    permis_str[4] = '-';
  }

  if ((sb.st_mode & S_IWGRP) != 0) {
    permis_str[5] = 'w';
  }
  else {
    permis_str[5] = '-';
  }

  if ((sb.st_mode & S_IXUSR) != 0) {
    permis_str[6] = 'x';
  }
  else {
    permis_str[6] = '-';
  }
  if ((sb.st_mode & S_IROTH) != 0) {
    permis_str[7] = 'r';
  }
  else {
    permis_str[7] = '-';
  }

  if ((sb.st_mode & S_IWOTH) != 0) {
    permis_str[8] = 'w';
  }
  else {
    permis_str[8] = '-';
  }

  if ((sb.st_mode & S_IXOTH) != 0) {
    permis_str[9] = 'x';
  }
  else {
    permis_str[9] = '-';
  }
  permis_str[10] = '\0';
  return permis_str;
}

// This function is for Step 4
// Input: time argument, ns
// output: time variable in heap
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];

  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

// Input: arguments for processing
// Output: none, just print!
// **This function implements all print tasks line by line
void printfunction(char * filename,
                   struct stat sb,
                   char * timestr_a,
                   char * timestr_m,
                   char * timestr_c) {
  // *** first line ***
  ssize_t nbytes;
  char buf[256];
  if (S_ISLNK(sb.st_mode)) {
    nbytes = readlink(filename, buf, 256);
    buf[nbytes] = '\0';
    if (buf == NULL) {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    if (nbytes == -1) {
      perror("readlink");
      exit(EXIT_FAILURE);
    }
    printf("  File: %s -> %s\n", filename, buf);
  }

  else {
    printf("  File: %s\n", filename);
  }
  // *** second line ***
  char * ftype = convert_ftype(sb.st_mode);
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         sb.st_size,
         sb.st_blocks,
         sb.st_blksize,
         ftype);

  // *** third line ***
  if (S_ISCHR(sb.st_mode)) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           sb.st_dev,
           sb.st_dev,
           sb.st_ino,
           sb.st_nlink,
           major(sb.st_rdev),
           minor(sb.st_rdev));
  }
  else if (S_ISBLK(sb.st_mode)) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           sb.st_dev,
           sb.st_dev,
           sb.st_ino,
           sb.st_nlink,
           major(sb.st_dev),
           minor(sb.st_dev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           sb.st_dev,
           sb.st_dev,
           sb.st_ino,
           sb.st_nlink);
  }

  // *** fouth line ***
  // for Step 3: implementation on group and passwd
  // initialize empty array to load permission string
  char permis_str[11] = {0};
  struct passwd * pwd;
  struct group * gid;
  pwd = getpwuid(sb.st_uid);
  gid = getgrgid(sb.st_gid);
  // invoke function convert_permis
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         sb.st_mode & ~S_IFMT,
         convert_permis(sb, permis_str),
         sb.st_uid,
         pwd->pw_name,
         sb.st_gid,
         gid->gr_name);
  printf("Access: %s\n", timestr_a);
  printf("Modify: %s\n", timestr_m);
  printf("Change: %s\n", timestr_c);
  printf(" Birth: -\n");
}

//** for reference **
//the stat prototype is as follow:
//int stat(const char *pathname, struct stat *statbuf);

//Input: two arguments; argument count, type-> integer;
//Input: argument value, which are file names, type-> pointer to string
//Output: exit flag, type-> integer
//**This main funciton can handle file errors,
//**invokes several functions to execute print tasks
int main(int argc, char ** argv) {
  // File error handle:
  // Need input file(s) so that programe can get stat info
  if (argc == 1) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    return EXIT_FAILURE;
  }
  int res = EXIT_SUCCESS;
  // Process all file(s) with argc and argv[i] in the for loop
  for (int i = 1; i < argc; i++) {
    struct stat sb;
    if (lstat(argv[i], &sb) == -1) {
      perror("lstat");
      res = EXIT_FAILURE;
      continue;
    }
    char * filename = argv[i];
    char * timestr_a = time2str(&sb.st_atime, sb.st_atim.tv_nsec);
    char * timestr_m = time2str(&sb.st_mtime, sb.st_mtim.tv_nsec);
    char * timestr_c = time2str(&sb.st_ctime, sb.st_ctim.tv_nsec);
    printfunction(filename, sb, timestr_a, timestr_m, timestr_c);
    free(timestr_a);
    free(timestr_m);
    free(timestr_c);
  }
  return res;
}
