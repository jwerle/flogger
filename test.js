var flog = require('./'), util = require('util')
var n = 100;
var write = process.stdout.write.bind(process.stdout)
var msgs = [];

flog.on('error', function (message) {
	flog.warn(["Caught error:", message].join(' '));
});

flog.createLevel('fatal', 'red');
flog.createLevel('message');

flog.log("log");
flog.info("info");
flog.debug("debug");
flog.warn("warn");
flog.error("error");

flog.fatal("fatal");
flog.message("message");

flog.break();

function bench (name, func) {
	var start, finish;
	start = Date.now();
	for (var i = 0; i <=n; ++i) func(String(i))
	finish = Date.now();

	msgs.push([
		name, " completed ", n, " in ", (finish - start), " ms"
	].join(''));
}


bench("console.log", console.log.bind(console));
bench("process.stdout.write", write);
bench("flog.native.log", flog.native.log); 

console.log(msgs.join('\n'))