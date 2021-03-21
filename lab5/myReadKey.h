#ifndef MYREADKEY_H
#define MYREADKEY_H

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
static struct termios stored_settings;

enum keys {
	key_load,
	key_save,
	key_run,
	key_step,
	key_reset,
	key_f5,
	key_f6,
	key_up,
	key_down,
	key_left,
	key_right,
	key_other
};

int rk_readkey(enum keys *key)
{
  // rk_mytermregime(1, 0, 1, 1, 1);
  string buf[8];
  cin >> buf;
	// read(STDIN_FILENO, buf, 8);
  if (buf == "\033[A") {
		*key = key_up;
	} else if (buf == "\033[B") {
		*key = key_down;
	} else if (buf == "\033[C") {
		*key = key_right;
	} else if (buf == "\033[D") {
		*key = key_left;
	} else if (buf == "\033[15~") {
		*key = key_f5;
	} else if (buf == "\033[17~") {
		*key = key_f6;
	} else if (buf[0] == 'l') {
		*key = key_load;
	} else if (buf[0] == 's') {
		*key = key_save;
	} else if (buf[0] == 'r') {
		*key = key_run;
	} else if (buf[0] == 't') {
		*key = key_step;
	} else if (buf[0] == 'i') {
		*key = key_reset;
	} else if (buf[0] >= '0' && buf[0] <= '9') {
		*key = buf[0] - 48;
	} else {
		*key = key_other;
	}
	// rk_mytermrestore();
	return 0;
}
int rk_mytermsave()
{
  if (!tcgetattr(0, &stored_settings)) {
		return 1;
	}
	return 0;
}
int rk_mytermrestore()
{ // TCSANOW - changes works right now
  if (!tcsetattr(0, TCSANOW, &stored_settings)){
		return 1;
	}
	return 0;
}
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);
#endif