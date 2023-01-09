# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <unistd.h>
# include <time.h>

static int flag = 1;
void create_daemon();
void sigint_handler(int sig);
char * quick_write(char * str);

int main(){
	printf("%s", quick_write("daemon_test: main(): program start!!! \n"));

	printf("%s", quick_write("daemon_test: main(): create_daemon()! \n"));
	create_daemon();

	quick_write("daemon_test: main(): start signal! \n");
	signal(SIGINT, sigint_handler);

	while(flag){
		int fd = open("/home/zero/daemon_test.log", O_CREAT | O_WRONLY | O_APPEND, 0644);
		if(fd == -1){
			quick_write("daemon_test: main(): open file error!! \n");
			perror("daemon_test: main(): open file:");
			exit(1);
		}
		char * str = "这是一个守护程序test的测试文本！！！ \n";
		write(fd, str, strlen(str));
		close(fd);
		sleep(5);
	}

	printf("%s", quick_write("daemon_test: main(): program return!!! \n"));

	return 0;
}

void sigint_handler(int sig){
	printf("%s", quick_write("daemon_test: sigint_handler(): start!!! \n"));

	printf("daemon_test: sigint_handler(): sig = %d \n", sig);

	flag = 0;

	printf("%s", quick_write("daemon_test: sigint_handler(): return!!! \n"));

	return;
}

void create_daemon(){
	printf("%s", quick_write("daemon_test: create_daemon(): start!!! \n"));

	pid_t pid = fork();
	printf("daemon_test: create_daemon(): pid1:%d \n", pid);
	if(pid == -1){
		perror("daemon_test: create_daemon(): fork:");
		exit(1);
	} else if (pid){
		exit(0);
	}
	printf("%s", quick_write("daemon_test: create_daemon(): fork 1 success! \n"));

	if(-1 == setsid()){
		perror("daemon_test: create_daemon(): setsid:");
		exit(1);
	}
//	setsid();
	printf("%s", quick_write("daemon_test: create_daemon(): setsid success! \n"));

	pid = fork();
	printf("daemon_test: create_daemon(): pid2:%d \n", pid);
	if(pid == -1){
		perror("daemon_test: create_daemon(): fork:");
		exit(1);
	} else if (pid){
		exit(0);
	}
	printf("%s", quick_write("daemon_test: create_daemon(): fork 2 success! \n"));

	chdir("/");
	printf("%s", quick_write("daemon_test: create_daemon(): chdir success! \n"));

	int i = 0;
	for(i = 0; i < 3; ++i)
		close(i);
	printf("%s", quick_write("daemon_test: create_daemon(): close file descriptor success! \n"));

	umask(0);
	printf("%s", quick_write("daemon_test: create_daemon(): umask success! \n"));

	printf("%s", quick_write("daemon_test: create_daemon(): return!!! \n"));

	return;
}

char * quick_write(char * str){
	int temp_fd = open("/home/zero/daemon_test_running.log", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if(temp_fd == -1){
		perror("daemon_test: quick_write(): open file:");
		exit(1);
	}
	write(temp_fd, str, strlen(str));
	close(temp_fd);
	return str;
}


