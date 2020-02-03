= How to build gRPC

Run:

```sh
GrpcPrograms/$PLATFORM/protoc -I . --grpc_out=. \
  --plugin=protoc-gen-grpc=GrpcPrograms/$PLATFORM/grpc_cpp_plugin speechly.proto

GrpcPrograms/$PLATFORM/protoc -I . --cpp_out=. speechly.proto
```
