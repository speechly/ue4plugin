# Please note!

The contents of this repository, including the instructions below, are no longer up to date. They are provided as extra documentation for those interested in Unreal integration. To get this up and running, the very least one should do is to [update the gRPC protos](https://github.com/speechly/api/tree/master/cpp).

# How to build gRPC

Run:

```sh
GrpcPrograms/$PLATFORM/protoc -I . --grpc_out=. \
  --plugin=protoc-gen-grpc=GrpcPrograms/$PLATFORM/grpc_cpp_plugin speechly.proto

GrpcPrograms/$PLATFORM/protoc -I . --cpp_out=. speechly.proto
```

This generates a bunch of .cc and .h files. Copy the .h files to
`Source/Speechly/Public` and .cc to `Source/Speechly/Private`.

The .cc files has to be modified to be able to compile with Unreal build system.
To both files add:

```c++
#include "IncludeBegin.h"
```

to the beginning of the file, and to the end add:

```c++
#include "IncludeEnd.h"
```

# macOS setup

The plugin currently is not production ready for macOS.

Since macOS Mojave, Apple requires special permissions and a premission request
dialog before accessing microphone. Unreal Engine 4.24 doesn't do that. The
plugin asks for the permission when starting starting speech recognition, but by
default macOS terminates any application that does that, IF they do not have
`NSMicrophoneUsageDescription` defined in the `Info.plist`.

Unreal Engine does not define it microphone permissions for the editor, so
microphone input does not work on macOS in the editor.

To make microphone work in the packaged application you have to edit the
`Info.plist`
Add `<key>NSMicrophoneUsageDescription</key><string>Speech recognition</string>`
to `Additional Plist Data` found in project packaging settings. This has to be
every time the package is recreated.

Even with these, the support for the dialog popup is flaky at best, as it's a
system dialog on top of a fullscreen application.
