// Copyright (C) 2008-today The SG++ project
// This file is part of the SG++ project. For conditions of distribution and
// use, please see the copyright notice provided with SG++ or at
// sgpp.sparsegrids.org

#include "text_node.hpp"
#include "json_exception.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace json {

text_node::text_node()
    : value(),
      isDouble(false),
      doubleValue(0.0),
      isUnsigned(false),
      unsignedValue(0),
      isSigned(false),
      signedValue(0),
      isBool(false),
      boolValue(false) {}

node &text_node::operator=(const node &right) {
  const text_node &textNode = dynamic_cast<const text_node &>(right);
  this->operator=(textNode);
  return *this;
}

void text_node::setupInternalType() {
  //    this->internalType = InternalIDType::ID;

  // try validating as bool
  if (this->value.compare("true") == 0) {
    //        this->internalType = InternalIDType::BOOL;
    this->isBool = true;
    this->boolValue = true;
    return;
  } else if (this->value.compare("false") == 0) {
    //        this->internalType = InternalIDType::BOOL;
    this->isBool = true;
    this->boolValue = false;
    return;
  }

  // try validating as unsigned integer
  // try {
  //   std::string::size_type size;
  //   uint64_t asUnsigned = stoull(this->value, &size);

  //   if (this->value.size() == size) {
  //     this->isUnsigned = true;
  //     this->unsignedValue = asUnsigned;
  //     //            this->internalType = InternalIDType::UINT;
  //     //      return;
  //   }
  // } catch (std::invalid_argument& e) {
  // }
  {
    std::stringstream conv_stream;
    conv_stream << this->value;
    uint64_t r;
    conv_stream >> r;
    if (conv_stream.fail()) {
      this->isUnsigned = true;
      this->unsignedValue = r;
    }
  }

  // try validating as signed integer
  // try {
  //   std::string::size_type size;
  //   int64_t asSigned = stoll(this->value, &size);

  //   if (this->value.size() == size) {
  //     this->isSigned = true;
  //     this->signedValue = asSigned;
  //     //            this->internalType = InternalIDType::INT;
  //     //      return;
  //   }
  // } catch (std::invalid_argument& e) {
  // }
  {
    std::stringstream conv_stream;
    conv_stream << this->value;
    int64_t r;
    conv_stream >> r;
    if (conv_stream.fail()) {
      this->isSigned = true;
      this->signedValue = r;
    }
  }

  // try validating as double
  // try {
  //   std::string::size_type size;
  //   double asDouble = stod(this->value, &size);

  //   if (this->value.size() == size) {
  //     this->isDouble = true;
  //     this->doubleValue = asDouble;
  //     //            this->internalType = InternalIDType::DOUBLE;
  //     //      return;
  //   }
  // } catch (std::invalid_argument& e) {
  // }
  {
    std::stringstream conv_stream;
    conv_stream << this->value;
    double r;
    conv_stream >> r;
    if (conv_stream.fail()) {
      this->isDouble = true;
      this->doubleValue = r;
    }
  }
}

void text_node::parse(std::vector<token>::iterator &stream_it,
                      std::vector<token>::iterator &stream_end) {
  // create new text node
  if ((*stream_it).type == token_type::STRING) {
    this->value = (*stream_it).value;
    stream_it++;

    this->setupInternalType();
  } else {
    throw json_exception("expected string value");
  }
}

void text_node::serialize(std::ostream &outFile, size_t indentWidth) {
  outFile << "\"" << this->value << "\"";
}

std::string &text_node::get() { return this->value; }

void text_node::set(const std::string &value) {
  this->value = value;
  this->setupInternalType();
}

double text_node::getDouble() {
  //    if (this->internalType == InternalIDType::DOUBLE) {
  if (this->isDouble) {
    return this->doubleValue;
  } else {
    throw json_exception("node has not a numerical value");
  }
}

void text_node::setDouble(double numericValue) {
  //    this->doubleValue = numericValue;
  //    this->internalType = InternalIDType::DOUBLE;
  std::stringstream stringstream;
  stringstream << numericValue;
  this->value = stringstream.str();
  this->setupInternalType();
}

uint64_t text_node::getUInt() {
  //    if (this->internalType == InternalIDType::UINT) {
  if (this->isUnsigned) {
    return this->unsignedValue;
  } else {
    throw json_exception("node has not an unsigned integer value");
  }
}

void text_node::setUInt(uint64_t uintValue) {
  //    this->unsignedValue = uintValue;
  //    this->internalType = InternalIDType::UINT;
  std::stringstream stringstream;
  stringstream << uintValue;
  this->value = stringstream.str();
  this->setupInternalType();
}

int64_t text_node::getInt() {
  //    if (this->internalType == InternalIDType::INT) {
  if (this->isSigned) {
    return this->signedValue;
  } else {
    throw json_exception("node has not an integer value");
  }
}

void text_node::setInt(int64_t intValue) {
  //    this->unsignedValue = intValue;
  //    this->internalType = InternalIDType::INT;
  std::stringstream stringstream;
  stringstream << intValue;
  this->value = stringstream.str();
  this->setupInternalType();
}

bool text_node::getBool() {
  //    if (this->internalType == InternalIDType::BOOL) {
  if (this->isBool) {
    return this->boolValue;
  } else {
    throw json_exception("node has not a bool value");
  }
}

void text_node::setBool(bool boolValue) {
  //    this->boolValue = boolValue;
  //    this->internalType = InternalIDType::BOOL;
  if (boolValue) {
    this->value = std::string("true");
  } else {
    this->value = std::string("false");
  }

  this->setupInternalType();
}

size_t text_node::size() { return 1; }

node *text_node::clone() {
  text_node *newNode = new text_node(*this);
  return newNode;
}

}  // namespace json
