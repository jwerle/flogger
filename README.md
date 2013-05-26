flogger
====

fast native logging for node.js

[![Build Status](https://travis-ci.org/jwerle/flogger.png?branch=master)](https://travis-ci.org/jwerle/flogger)

## install

```sh
$ npm install flogger
```

## usage

```js
var flog = require('flogger')

flog.log("foo");
```

## api

### Flog (name)

Flog constructor

```js
var flog = new Flog("app");
```

### Flog.createLevel(level, color)

creates a level and function on the `Flog` prototype

```js
var flog = new Flog("app");

Flog.createLevel('fatal', 'red');

fog.fatal("something went wrong!");
```

### #log (message)

`log` level logging

```js
flog.log("foo");
```

### #info (message)

`info` level logging

```js
flog.info("foo");
```

### #warn (message)

`warn` level logging

```js
flog.warn("foo");
```

### #debug (message)

`debug` level logging

```js
flog.debug("foo");
```

### #error (message)

`error` level logging

```js
flog.error("oops!");
```

## benchmark


```
  console.log completed 1000 in 15 ms
  process.stdout.write completed 1000 in 6 ms
  flog.log completed 1000 in 4 ms
```

## license

MIT
