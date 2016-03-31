#include <node.h>

namespace demo {
  using v8::Exception;
  using v8::Function;
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::String;
  using v8::Value;

  void StringReturnExample(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
  }

  void StringArgumentReturnExample(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() < 1) {
      isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")
      ));
      return;
    }

    args.GetReturnValue().Set(args[0]->ToString());
  }

  void CallbackExample(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() < 1) {
      isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")
      ));
      return;
    }

    Local<Function> callback = Local<Function>::Cast(args[0]);
    const unsigned argc = 1;
    Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "callback value") };
    callback->Call(Null(isolate), argc, argv);
  }

  void ObjectReturnExample(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Local<Object> obj = Object::New(isolate);

    obj->Set(String::NewFromUtf8(isolate, "foo"), String::NewFromUtf8(isolate, "bar"));
    obj->Set(String::NewFromUtf8(isolate, "hello"), String::NewFromUtf8(isolate, "world"));

    args.GetReturnValue().Set(obj);
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "stringReturnExample", StringReturnExample);
    NODE_SET_METHOD(exports, "stringArgumentReturnExample", StringArgumentReturnExample);
    NODE_SET_METHOD(exports, "objectReturnExample", ObjectReturnExample);
    NODE_SET_METHOD(exports, "callbackExample", CallbackExample);
  }

  NODE_MODULE(addon, init)
}
