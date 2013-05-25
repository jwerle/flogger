/**
 * Module dependencies
 */

var nflog = require('bindings')('flog')
	,	stream = require('stream')


/**
 * Forms a message string
 *
 * @api private
 * @param {Flog} flog
 * @param {Mixed} message
 */
function formMessage (flog, message) {
	if (message && typeof message === 'object') message = JSON.stringify(message);
	var msg = flog.format();
	msg = msg.replace(/%name/g, flog.name);
	msg = msg.replace(/%message/g, message);
	return msg;
}

/**
 * flog terminal functions
 */

Flog.term = Flog.prototype.term = {
	write : function () {
		nflog.term_write.apply(nflog, arguments);
		return this;
	},
	bold : function () {
		nflog.term_bold.apply(nflog, arguments);
		return this;
	},
	clear : function () {
		nflog.term_clear.apply(nflog, arguments);
		return this;
	},
	reset : function () {
		nflog.term_reset.apply(nflog, arguments);
		return this;
	},
	bright : function () {
		nflog.term_bright.apply(nflog, arguments);
		return this;
	},
	dim : function () {
		nflog.term_dim.apply(nflog, arguments);
		return this;
	},
	underline : function () {
		nflog.term_underline.apply(nflog, arguments);
		return this;
	},
	blink : function () {
		nflog.term_blink.apply(nflog, arguments);
		return this;
	},
	reverse : function () {
		nflog.term_reverse.apply(nflog, arguments);
		return this;
	},
	hidden : function () {
		nflog.term_hidden.apply(nflog, arguments);
		return this;
	},
};



/**
 * Flog constructor
 *
 * @api public
 * @param {String} name
 */

function Flog (name) {
	if (! (this instanceof Flog)) return new Flog(name);
	stream.Duplex.call(this, {allowHalfOpen:false});
	this.name = name || "";
	this.format = function () {
		var fmt = []
		if (this.name) fmt.push('(%name) - ');
		fmt.push('%message');
		return fmt.join('');
	};
	this.buffer = new Buffer(0);
	this.push('');
}

Flog.createLevel = function (level, color) {
	Flog.prototype[level] = function (message) {
		message = formMessage(this, message);
		this.write(message);
		nflog.customlog(level, color, message);
		return this;
	};
};

/**
 * Inherit from Duplex
 */
Flog.prototype.__proto__ = stream.Duplex.prototype;

Flog.prototype.native = nflog;

Flog.prototype._write = function (chunk, encoding, next) {
	var len = this.buffer.length + chunk.length;
	this.push([chunk, '\n'].join(''));
	this.buffer = new Buffer(chunk, encoding);
	next();
};

Flog.prototype._read = function (size) {
	if (!size) return this.buffer;
	var buf = new Buffer(size)
	buf.copy(this.buffer);
	return buf;
};

Flog.prototype.log = function (message) {
	message = formMessage(this, message);
	this.write(message);
	nflog.log(message);
	return this;
};

Flog.prototype.info = function (message) {
	message = formMessage(this, message);
	this.write(message);
	nflog.info(message);
	return this;
};

Flog.prototype.warn = function (message) {
	message = formMessage(this, message);
	this.write(message);
	nflog.warn(message);
	return this;
};

Flog.prototype.debug = function (message) {
	message = formMessage(this, message);
	this.write(message);
	nflog.debug(message);
	return this;
};

Flog.prototype.error = function (message) {
	message = formMessage(this, message);
	this.write(message);
	nflog.error(message);
	return this;
};

/**
 * Module exports
 */

var flog = module.exports = Flog();
