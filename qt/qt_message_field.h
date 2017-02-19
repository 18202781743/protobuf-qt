// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// https://developers.google.com/protocol-buffers/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Author: kenton@google.com (Kenton Varda)
//  Based on original Protocol Buffers design by
//  Sanjay Ghemawat, Jeff Dean, and others.

#ifndef GOOGLE_PROTOBUF_COMPILER_CPP_MESSAGE_FIELD_H__
#define GOOGLE_PROTOBUF_COMPILER_CPP_MESSAGE_FIELD_H__

#include <map>
#include <string>

#include "qt_field.h"

namespace google {
namespace protobuf {
namespace compiler {
namespace qt {

class MessageFieldGenerator : public FieldGenerator {
 public:
  MessageFieldGenerator(const FieldDescriptor* descriptor,
                        const Options& options);
  ~MessageFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GeneratePrivateMembers(io::Printer* printer) const;
  void GenerateDependentAccessorDeclarations(io::Printer* printer) const;
  void GenerateAccessorDeclarations(io::Printer* printer) const;
  void GenerateDependentInlineAccessorDefinitions(io::Printer* printer) const;
  void GenerateInlineAccessorDefinitions(io::Printer* printer,
                                         bool is_inline) const;
  void GenerateNonInlineAccessorDefinitions(io::Printer* printer) const;
  void GenerateClearingCode(io::Printer* printer) const;
  void GenerateMessageClearingCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateSwappingCode(io::Printer* printer) const;
  void GenerateDestructorCode(io::Printer* printer) const;
  void GenerateConstructorCode(io::Printer* printer) const;
  void GenerateCopyConstructorCode(io::Printer* printer) const;
  void GenerateMergeFromCodedStream(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizes(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizesToArray(io::Printer* printer) const;
  void GenerateByteSize(io::Printer* printer) const;

 protected:
  void GenerateArenaManipulationCode(const std::map<string, string>& variables,
                                     io::Printer* printer) const;

  virtual void GenerateGetterDeclaration(io::Printer* printer) const;

  const FieldDescriptor* descriptor_;
  const bool dependent_field_;
  std::map<string, string> variables_;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageFieldGenerator);
};

class MessageOneofFieldGenerator : public MessageFieldGenerator {
 public:
  MessageOneofFieldGenerator(const FieldDescriptor* descriptor,
                             const Options& options);
  ~MessageOneofFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GenerateDependentAccessorDeclarations(io::Printer* printer) const;
  void GenerateDependentInlineAccessorDefinitions(io::Printer* printer) const;
  void GenerateInlineAccessorDefinitions(io::Printer* printer,
                                         bool is_inline) const;
  void GenerateNonInlineAccessorDefinitions(io::Printer* printer) const;
  void GenerateClearingCode(io::Printer* printer) const;

  // MessageFieldGenerator, from which we inherit, overrides this so we need to
  // override it as well.
  void GenerateMessageClearingCode(io::Printer* printer) const;
  void GenerateSwappingCode(io::Printer* printer) const;
  void GenerateDestructorCode(io::Printer* printer) const;
  void GenerateConstructorCode(io::Printer* printer) const;

 protected:
  void GenerateGetterDeclaration(io::Printer* printer) const;

 private:
  void InternalGenerateInlineAccessorDefinitions(
      const std::map<string, string>& variables, io::Printer* printer) const;

  const bool dependent_base_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(MessageOneofFieldGenerator);
};

class RepeatedMessageFieldGenerator : public FieldGenerator {
 public:
  RepeatedMessageFieldGenerator(const FieldDescriptor* descriptor,
                                const Options& options);
  ~RepeatedMessageFieldGenerator();

  // implements FieldGenerator ---------------------------------------
  void GeneratePrivateMembers(io::Printer* printer) const;
  void GenerateDependentAccessorDeclarations(io::Printer* printer) const;
  void GenerateAccessorDeclarations(io::Printer* printer) const;
  void GenerateDependentInlineAccessorDefinitions(io::Printer* printer) const;
  void GenerateInlineAccessorDefinitions(io::Printer* printer,
                                         bool is_inline) const;
  void GenerateClearingCode(io::Printer* printer) const;
  void GenerateMergingCode(io::Printer* printer) const;
  void GenerateSwappingCode(io::Printer* printer) const;
  void GenerateConstructorCode(io::Printer* printer) const;
  void GenerateCopyConstructorCode(io::Printer* printer) const {}
  void GenerateMergeFromCodedStream(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizes(io::Printer* printer) const;
  void GenerateSerializeWithCachedSizesToArray(io::Printer* printer) const;
  void GenerateByteSize(io::Printer* printer) const;

 private:
  void InternalGenerateTypeDependentAccessorDeclarations(
      io::Printer* printer) const;

  const FieldDescriptor* descriptor_;
  const bool dependent_field_;
  const bool dependent_getter_;
  std::map<string, string> variables_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RepeatedMessageFieldGenerator);
};

}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_CPP_MESSAGE_FIELD_H__
