#include "types.h"
#include "user.h"
#include "trace.h"
#include "syscall.h"

static char *syscall_name[] = {
  [SYS_fork]    "fork",
  [SYS_exit]    "exit",
  [SYS_wait]    "wait",
  [SYS_pipe]    "pipe",
  [SYS_read]    "read",
  [SYS_kill]    "kill",
  [SYS_exec]    "exec",
  [SYS_fstat]   "fstat",
  [SYS_chdir]   "chdir",
  [SYS_dup]     "dup",
  [SYS_getpid]  "getpid",
  [SYS_sbrk]    "sbrk",
  [SYS_sleep]   "sleep",
  [SYS_uptime]  "uptime",
  [SYS_open]    "open",
  [SYS_write]   "write",
  [SYS_mknod]   "mknod",
  [SYS_unlink]  "unlink",
  [SYS_link]    "link",
  [SYS_mkdir]   "mkdir",
  [SYS_close]   "close",
  [SYS_trace]  "trace",
  [SYS_t_toggle] "t_toggle",
};

int
main(int argc, char *argv[])
{
  if(argc < 2){
    printf(2, "Usage: strace [on|off|run (command)]\n");
    exit();
  }

  //adding option checking
  int i, j, exclusive_flag;
  const char* j_str;

  exclusive_flag = 0;

  for(i = 1; i < argc; i++){
    if(strcmp(argv[i], "-e") == exclusive_flag){
      for(j = 1; j < 24; j++){
        j_str = syscall_name[j];
        if(strcmp(argv[i+1], j_str) == 0){
            excid(j);
            //for testing
            //printf(2, "value of exclusive flag passed %d", exclusive_flag);
            break;
        }
        //else, turn off strace
    }
    }
    if(strcmp(argv[i], "-f") == 0){

    }
    if(strcmp(argv[i], "-s") == 0){

    }
  }

  if(strcmp(argv[1], "on") == 0){
    t_toggle(TRACE_ON);
  } else if(strcmp(argv[1], "off") == 0){
    t_toggle(TRACE_OFF);
  } 
    else if(strcmp(argv[1], "run") == 0){
        int pid = fork();
        if(pid == 0){
            t_toggle(TRACE_ON);
            char *sh_args[] = { "sh", "-c", argv[2], 0 };
            exec("/bin/sh", sh_args);
            printf(2,"exec failed\n");
            exit();
        }
        wait();
        t_toggle(TRACE_OFF);
        
    }
  
  else {
    printf(2, "Invalid argument. Use 'on' or 'off'.\n");
    exit();
  }
  exit();
  return 0;
}
