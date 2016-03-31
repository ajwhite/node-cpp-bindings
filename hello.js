'use strict';

var hello = require('./build/Release/addon');

console.log(hello.stringReturnExample());
console.log(hello.stringArgumentReturnExample('hello world'));
console.log(hello.objectReturnExample());
hello.callbackExample(function (value) {
  console.log('called back with', value);
});
