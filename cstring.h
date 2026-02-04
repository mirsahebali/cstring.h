// SPDX-License-Identifier: BSD-3-Clause
/*
------------------------------------------------------------------------------
BSD 3-Clause License

Copyright (c) 2026, Mir Saheb Ali
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------
*/

#ifndef CSTRING_H
#define CSTRING_H

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *chars;
  int32_t length;
} String;

// creates a new string with a inferred length
String String_from(const char *str);

// initialize a new string with a set capacity
String String_new_n(int32_t len);

String String_clone(String *);

int32_t String_concat(String *dest, String *left, String *right);

// join the given number of `String` elements from the list
String String_join(int32_t n, ...);

String concat_char(String *, char);
String concat_cstr(String *, const char *);

// Create a new single character string
String String_from_char(char ch);

String String_substr_range(String *, int32_t begin, int32_t end);

// clone the data from `value`
// WARN: cleanup value if not using it anymore
// may lead to mem leak
String String_clone(String *value);

// moves the data from `src` and frees up src;
String String_move(String *src);

char String_char_at(String *, int32_t);

bool String_cmp(String *left, String *right);

// Always call this after reassigning strings or being done after use
void free_string(String *s);

typedef struct {
  String *data;
  int32_t capacity;
  int32_t size;
} StringArray;

StringArray string_array_init(int32_t capacity);
int32_t string_array_push(StringArray *self, String);
int32_t string_array_size(const StringArray *self);
bool string_array_reserve(StringArray *self);
int32_t string_array_capacity(const StringArray *);
String string_array_get(const StringArray *self, int32_t index);
void print_string_array(const StringArray *);
void free_string_array(StringArray *self);

#endif // !CSTRING_H

#ifdef CSTRING_IMPLEMENTATION

String String_from(const char *str) {
  int32_t len = strlen(str);
  char *buf = (char *)malloc(len + 1);
  char *dest = strcpy(buf, str);
  return (String){dest, (int32_t)strlen(str)};
}

String String_new_n(int32_t len) {
  char *buf = (char *)malloc(sizeof(char) * len);

  return (String){buf, len};
}

String concat_char(String *input, char ch) {
  size_t new_len = input->length + 1;
  char *buf = (char *)malloc(sizeof(char) * (new_len + 1));
  assert(buf != NULL);

  char new_ch[2] = {ch, '\0'};

  snprintf(buf, new_len + 1, "%s%s", input->chars, new_ch);

  return (String){buf, (int32_t)new_len};
}
String concat_cstr(String *input, const char *str) {
  assert(input != NULL);
  size_t new_len = input->length + strlen(str);
  char *buf = (char *)malloc(sizeof(char) * (new_len + 1)); // +1 for '\0'

  assert(buf != NULL);

  snprintf(buf, new_len + 1, "%s%s", input->chars, str);

  return (String){buf, (int32_t)new_len};
}

bool String_cmp(String *left, String *right) {
  if (left == right)
    return true;
  if (left == NULL || right == NULL)
    return false;

  return (strcmp(left->chars, right->chars) == 0) &&
         (left->length == right->length);
}

char String_char_at(String *input, int32_t index) {
  assert(input != NULL);

  assert(index < input->length && index >= 0);

  return input->chars[index];
}

String String_from_char(char ch) {
  char *c = (char *)malloc(sizeof(char) * 2);
  c[0] = ch;
  c[1] = '\0';
  assert(c != NULL);

  return (String){c, 1};
}

String String_substr_range(String *input, int32_t begin, int32_t steps) {
  assert(input != NULL);
  assert((begin >= 0) && (begin < input->length));
  assert(begin + steps < input->length);

  String out = String_new_n(steps + 1);
  for (int i = begin; i < begin + steps; i++) {
    out.chars[i - begin] = input->chars[i];
  }

  out.chars[steps] = '\0';

  out.length--;

  return out;
}

String String_clone(String *value) {
  assert(value != NULL);
  char *buf = (char *)malloc(value->length + 1);
  int32_t len = value->length;
  assert(buf != NULL);
  snprintf(buf, len + 1, "%s", value->chars);
  return (String){
      .chars = buf,
      .length = len,
  };
}

// concat two strings and put it in `dest` and return the new size of the string
int32_t String_concat(String *dest, String *left, String *right) {

  int32_t new_size = left->length + right->length;
  free_string(dest);
  dest->chars = (char *)malloc(new_size + 1);
  dest->chars[0] = '\0';
  dest->length = new_size;
  if (left != NULL)
    strcat(dest->chars, left->chars);
  if (right != NULL)
    strcat(dest->chars, right->chars);

  return dest->length;
}

String String_join(int32_t n, ...) {
  String out;
  String temp = String_from("");
  va_list args;
  va_start(args, n);
  for (size_t i = 0; i < n; i++) {
    String_concat(&out, &temp, va_arg(args, String *));
    free_string(&temp);
    temp = String_clone(&out);
  }
  va_end(args);

  free_string(&temp);
  return out;
}

String String_move(String *src) {
  assert(src != NULL || src->chars != NULL);
  char *out = (char *)malloc(src->length + 1);
  int32_t len = src->length;
  strncpy(out, src->chars, len + 1);
  free_string(src);

  return (String){
      .chars = out,
      .length = len,
  };
}

void free_string(String *s) {
  if (!s)
    return;

  free(s->chars);
  s->chars = NULL;
  s->length = 0;
}

StringArray string_array_init(int32_t capacity) {
  int32_t cap = capacity <= 0 ? 16 : capacity;

  String *data = (String *)malloc(sizeof(String) * cap);

  return (StringArray){.data = data, .capacity = cap, .size = 0};
}
bool string_array_reserve(StringArray *self) {
  assert(self != NULL);
  if (self->size < self->capacity)
    return true;

  int32_t new_cap = self->capacity * 2;
  if (new_cap <= 0)
    return false;

  String *ret = (String *)realloc(self->data, sizeof(String) * new_cap);
  if (!ret)
    return false;

  self->data = ret;
  self->capacity = new_cap;
  return true;
}
int32_t string_array_push(StringArray *self, String data) {
  assert(self != NULL);
  String new_data = String_move(&data);
  assert(self != NULL);
  if (!string_array_reserve(self)) {

    printf("Cannot relloc memory into StringArray\n");
    assert(false);
  }
  self->data[self->size] = new_data;
  self->size++;
  return self->size;
}

int32_t string_array_size(const StringArray *self) { return self->size; }
int32_t string_array_capacity(const StringArray *self) {
  return self->capacity;
}
String string_array_get(const StringArray *self, int32_t index) {
  assert(self != NULL);
  assert(index >= 0 && index < self->size);
  return self->data[index];
}

void print_string_array(const StringArray *arr) {
  assert(arr != NULL);
  for (int32_t i = 0; i < arr->size; i++) {
    String s = string_array_get(arr, i);
    printf("%s\n", s.chars);
  }
}

void free_string_array(StringArray *self) {
  if (self == NULL)
    return;
  for (int32_t i = 0; i < self->size; i++) {
    free_string(&self->data[i]);
  }

  free(self->data);
}

#endif // CSTRING_IMPLEMENTATION
