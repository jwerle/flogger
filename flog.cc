#include <node.h>
#include <v8.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <string>

using namespace v8;

/**
 * borrowed from `https://github.com/visionmedia/term.c`
 *
 * thanks tj
 */

#define _term_write(c) printf("\e[" c);

Handle<Value>
term_write (const Arguments &args) {
	String::Utf8Value c(args[0]);
	printf("%s", *c);
	return v8::Undefined();
}

Handle<Value>
term_reset (const Arguments &args) { 
	_term_write("0m");
	return v8::Undefined();
}

Handle<Value>
term_bright (const Arguments &args) { 
	_term_write("1m");
	return v8::Undefined();
}

Handle<Value>
term_bold (const Arguments &args) { 
	term_bright(args);
	return v8::Undefined();
}

Handle<Value>
term_clear (const Arguments &args) { 
	term_reset(args);
	return v8::Undefined();
}

Handle<Value>
term_dim (const Arguments &args) { 
	_term_write("2m");
	return v8::Undefined();
}

Handle<Value>
term_underline (const Arguments &args) { 
	_term_write("4m");
	return v8::Undefined();
}

Handle<Value>
term_blink (const Arguments &args) { 
	_term_write("5m");
	return v8::Undefined();
}

Handle<Value>
term_reverse (const Arguments &args) { 
	_term_write("7m");
	return v8::Undefined();
}

Handle<Value>
term_hidden (const Arguments &args) { 
	_term_write("8m");
	return v8::Undefined();
}

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

  // expose term functions
	NODE_SET_METHOD(target, "term_write", term_write);
	NODE_SET_METHOD(target, "term_bold", term_bold);
	NODE_SET_METHOD(target, "term_clear", term_clear);
	NODE_SET_METHOD(target, "term_reset", term_reset);
	NODE_SET_METHOD(target, "term_bright", term_bright);
	NODE_SET_METHOD(target, "term_dim", term_dim);
	NODE_SET_METHOD(target, "term_underline", term_underline);
	NODE_SET_METHOD(target, "term_blink", term_blink);
	NODE_SET_METHOD(target, "term_reverse", term_reverse);
	NODE_SET_METHOD(target, "term_hidden", term_hidden);
}

NODE_MODULE(flog, init);

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
		// reset
		_term_write("0m");
		printf("%s\n", *value);
	}

	return v8::Undefined();
}

Handle<Value> 
customlog (const Arguments& args) {
	char level_str[256], color_str[256];
	String::Utf8Value level(args[0]);
	String::Utf8Value color(args[1]);
	Handle<Value> message = args[2];

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