#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <termios.h>

#include "vrodux.h"

void error(const char* msg) { printf("%s(.) error:%s %s\n", HI_RE, M_RE, msg); }
void warning(const char* msg) { printf("%s(!) warning:%s %s\n", HI_YE, M_RE, msg); }
void info(const char* msg) { printf("%s(^) info:%s %s\n", HI_WH, M_RE, msg); }
void success(const char* msg) { printf("%s(|) success:%s %s\n", HI_GR, M_RE, msg); }
void unknown(const char* msg) { printf("%s(?) unknown:%s %s\n", HI_PU, M_RE, msg); }
void deprecated(const char* msg) { printf("%s(/) deprecated:%s %s\n", HI_BLK, M_RE, msg); }
void semi_success(const char* msg) { printf("%s(-) semi success:%s %s\n", HI_BL, M_RE, msg); }

void clear_screen() { printf("\033[1;1H\033[2J"); }
