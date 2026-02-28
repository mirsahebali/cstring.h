#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CSTRING_IMPLEMENTATION
#include "cstring.h"

#define TEST_STARTED printf("`%s` started\n", __FUNCTION__)
#define TEST_PASSED printf("`%s` passed\n", __FUNCTION__)

void test_string_from(void);
void test_string_concat_char(void);
void test_string_concat_cstr(void);
void test_string_cmp(void);
void test_char_at_str(void);
void test_string_from_char(void);
void test_string_substr(void);
void test_string_concat(void);
void test_string_join(void);
void test_string_array_join(void);
void test_string_to_int(void);
void test_string_array_from_cstr(void);
void test_string_array_from_cstr_list(void);

int main() {

  test_string_from();
  test_string_concat_char();
  test_string_concat_cstr();
  test_char_at_str();
  test_string_from_char();
  test_string_substr();
  test_string_concat();
  test_string_join();
  test_string_array_join();
  test_string_to_int();
  test_string_array_from_cstr();
  test_string_array_from_cstr_list();
  return 0;
}
void test_string_array_from_cstr(void) {
  TEST_STARTED;

  StringArray expected = string_array_init(3);
  string_array_push(&expected, String_from("Hello"));
  string_array_push(&expected, String_from("World"));
  string_array_push(&expected, String_from("Foo"));
  string_array_push(&expected, String_from("Bar"));

  StringArray actual =
      String_array_from_cstr(4, "Hello", "World", "Foo", "Bar");

  assert(expected.size == actual.size);
  for (int i = 0; i < expected.size; i++) {
    String exp = string_array_get(&expected, i);
    String act = string_array_get(&actual, i);
    assert(String_cmp(&exp, &act));
  }

  free_string_array(&expected);
  free_string_array(&actual);

  TEST_PASSED;
}

void test_string_array_from_cstr_list(void) {
  TEST_STARTED;

  StringArray expected = string_array_init(3);
  string_array_push(&expected, String_from("fizz"));
  string_array_push(&expected, String_from("buzz"));
  string_array_push(&expected, String_from("foo"));

  const char *items[3] = {"fizz", "buzz", "foo"};
  StringArray actual = String_array_from_str_list(3, items);

  assert(expected.size == actual.size);
  for (int i = 0; i < expected.size; i++) {
    String exp = string_array_get(&expected, i);
    String act = string_array_get(&actual, i);
    assert(String_cmp(&exp, &act));
  }

  free_string_array(&expected);
  free_string_array(&actual);
  TEST_PASSED;
}

void test_string_to_int(void) {
  TEST_STARTED;
  String input = STR_NEW("-1");
  int32_t out;
  bool is_success = String_to_int(&input, &out);
  assert(is_success);
  assert(out == -1);

  input = STR_NEW("-345");

  is_success = String_to_int(&input, &out);
  assert(is_success);
  assert(out == -345);

  input = STR_NEW("34583");
  is_success = String_to_int(&input, &out);
  assert(is_success);
  assert(out == 34583);
  TEST_PASSED;
}

void test_string_from(void) {
  TEST_STARTED;
  String input = String_from("Hello, World");
  String expected = {"Hello, World", 12};

  assert(strcmp(input.chars, expected.chars) == 0);
  assert(input.length == expected.length);
  free_string(&input);
  TEST_PASSED;
}

void test_string_concat_char(void) {
  String test_str = String_from("12345");

  String input = concat_char(&test_str, '6');
  String expected = String_from("123456");
  assert(strcmp(input.chars, expected.chars) == 0);

  String input1 = concat_char(&input, '7');
  String expected1 = String_from("1234567");
  assert(strcmp(input1.chars, expected1.chars) == 0);

  free_string(&expected1);
  free_string(&input1);
  free_string(&expected);
  free_string(&input);
  free_string(&test_str);
  TEST_PASSED;
}

void test_string_concat_cstr(void) {
  TEST_STARTED;
  String test_str = String_from("Hello");
  String input = concat_cstr(&test_str, ", World");
  String expected = String_from("Hello, World");

  assert(strcmp(input.chars, expected.chars) == 0);

  free_string(&test_str);
  free_string(&input);
  free_string(&expected);
  TEST_PASSED;
}

void test_string_cmp(void) {
  TEST_STARTED;
  String left = String_from("Shawww");
  String right = String_from("Shawww");
  assert(String_cmp(&left, &right));

  free_string(&left);
  free_string(&right);
  left = String_from("Poshanka");
  right = String_from("Shawww");
  assert(!String_cmp(&left, &right));

  free_string(&left);
  free_string(&right);
  TEST_PASSED;
}

void test_char_at_str(void) {
  TEST_STARTED;
  String input = String_from("abc123");
  char out = String_char_at(&input, 0);
  char expected = 'a';
  assert(out == expected);

  out = String_char_at(&input, 1);
  expected = 'b';

  assert(out == expected);

  out = String_char_at(&input, 2);
  char invalid = 'd';

  assert(out != invalid);

  out = String_char_at(&input, 5);
  expected = '3';

  assert(out == expected);

  free_string(&input);
  TEST_PASSED;
}

void test_string_concat(void) {
  TEST_STARTED;

  String left = String_from("Hello, ");
  String right = String_from("World");
  String dest = String_concat(&left, &right);
  String expected = String_from("Hello, World");

  assert(String_cmp(&dest, &expected));

  free_string(&dest);
  free_string(&left);
  free_string(&right);
  free_string(&expected);
  TEST_PASSED;
}

void test_string_join(void) {
  TEST_STARTED;

  String one = String_from("one ");
  String two = String_from("two ");
  String three = String_from("three ");
  String four = String_from("four");
  String expected = String_from("one two three four");

  String dest = String_join(4, &one, &two, &three, &four);

  assert(String_cmp(&dest, &expected));

  free_string(&dest);
  free_string(&one);
  free_string(&two);
  free_string(&three);
  free_string(&four);
  free_string(&expected);
  TEST_PASSED;
}

void test_string_from_char(void) {}

void test_string_substr(void) {
  TEST_STARTED;
  String input = String_from("Hello, World");
  String substr = String_substr_range(&input, 2, 5);
  String expected = String_from("llo, ");

  assert(String_cmp(&substr, &expected));
  free_string(&expected);
  free_string(&substr);
  free_string(&input);
  TEST_PASSED;
}

void test_string_array_join(void) {
  TEST_STARTED;
  StringArray arr = string_array_init(2);

  String one = String_from("one");
  String two = String_from("two");
  String three = String_from("three");
  String four = String_from("four");

  string_array_push(&arr, one);
  string_array_push(&arr, two);
  string_array_push(&arr, three);
  string_array_push(&arr, four);
  String semicolon = String_from(";");
  String out = string_array_join(&arr, semicolon);

  String expected = String_from("one;two;three;four");

  printf("out->chars = %s\n", out.chars);
  printf("expected.chars = %s\n", expected.chars);

  assert(String_cmp(&out, &expected));

  free_string_array(&arr);
  free_string(&out);
  free_string(&semicolon);
  free_string(&expected);
  TEST_PASSED;
}
