var flog = require('./'), util = require('util')
var n = 1000;
var write = process.stdout.write.bind(process.stdout)
var msgs = []

function bench (name, func) {
	var start, finish;
	start = Date.now();
	for (var i = 0; i <=n; ++i) func(String(i))
	finish = Date.now();

	msgs.push([
		name, " completed ", n, " in ", (finish - start), " ms"
	].join(''));
}


bench("console.log", console.log);
bench("process.stdout.write", write);
bench("flog.log", flog.native.log); 

console.log(msgs.join('\n'))