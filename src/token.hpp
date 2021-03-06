// Copyright (C) 2008-today The SG++ project
// This file is part of the SG++ project. For conditions of distribution and
// use, please see the copyright notice provided with SG++ or at
// sgpp.sparsegrids.org

#pragma once

#include <string>

namespace json {

enum class token_type {
  LBRACE, RBRACE, LBRACKET, RBRACKET, COLON, ID, STRING, COMMA, COMMENT,
  SINGLELINE, MULTILINECOMMENT, MULTILINECOMMENTSTAR, NONE
};

class token {
 public:
  token_type type;
  std::string value;
  size_t lineNumber;
  size_t charNumber;
};

}  // namespace json
