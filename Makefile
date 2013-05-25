all: clean build test
	@:
	
build:
	@npm install

clean:
	@rm -rf build/

test:
	node test.js

.PHONY: build clean test