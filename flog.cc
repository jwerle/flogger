#include <node.h>
#include <v8.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <string>

using namespace v8;

Handle<Value> 
log (const Arguments& args);

Handle<Value> 
customlog (const Arguments& args);

Handle<Value> 
info (const Arguments& args);

Handle<Value> 
debug (const Arguments& args);

Handle<Value> 
warn (const Arguments& args);

Handle<Value> 
error (const Arguments& args);

void 
init (Handle<Object> target) {
  NODE_SET_METHOD(target, "log", log);
  NODE_SET_METHOD(target, "info", info);
  NODE_SET_METHOD(target, "debug", debug);
  NODE_SET_METHOD(target, "warn", warn);
  NODE_SET_METHOD(target, "error", error);
  NODE_SET_METHOD(target, "customlog", customlog);
}

NODE_MODULE(flog, init);


/**
 * borrowed from `https://github.com/visionmedia/term.c`
 *
 * thanks tj
 */

#define term_write(c) printf("\e[" c);

// aliases

#define term_bold term_bright
#define term_clear term_erase

// display

#define term_reset() term_write("0m")
#define term_bright() term_write("1m")
#define term_dim() term_write("2m")
#define term_underline() term_write("4m")
#define term_blink() term_write("5m")
#define term_reverse() term_write("7m")
#define term_hidden() term_write("8m")

int
color_value (const char *name) {
	if (!strcmp("black", name)) return 0;
  else if (!strcmp("red", name)) return 1;
  else if (!strcmp("green", name)) return 2;
  else if (!strcmp("yellow", name)) return 3;
  else if (!strcmp("blue", name)) return 4;
  else if (!strcmp("magenta", name)) return 5;
  else if (!strcmp("cyan", name)) return 6;
  else if (!strcmp("white", name)) return 7;
  else return -1;
}

Handle<Value>
flog (const char *level, const char *color, Handle<Value> val) {
	String::Utf8Value value(val);
	if (*color == '\0') {
		printf("  %s: %s\n", level, *value);
	}
	else {
		int n = color_value(color);
		printf("  \e[3%dm%s: ", n, level);
		term_reset();
		printf("%s\n", *value);
	}

	return v8::Undefined();
}

Handle<Value> 
customlog (const Arguments& args) {
	String::Utf8Value level(args[0]);
	String::Utf8Value color(args[1]);
	Handle<Value> message = args[2];

	char level_str[256];
	char color_str[256];
	sprintf(level_str, "%s", *level);
	sprintf(color_str, "%s", *color);
	
  return flog(level_str, color_str, message);
}

Handle<Value> 
log (const Arguments& args) {
  return flog("log", "", args[0]);
}

Handle<Value> 
info (const Arguments& args) {
	return flog("info", "cyan", args[0]);
}

Handle<Value> 
debug (const Arguments& args) {
	return flog("debug", "yellow", args[0]);
}

Handle<Value> 
warn (const Arguments& args) {
	return flog("warn", "yellow", args[0]);
}

Handle<Value> 
error (const Arguments& args) {
	return flog("error", "red", args[0]);
}