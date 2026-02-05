# Usage
1. Create heap allocated strings


```c
String a = String_from("Hello");
String b = STR_NEW("World");
String c = String_from_char('!');

// remember to free later
free_string(&a);
free_string(&b);
free_string(&c);

```

2. Create Stack allocated string

```c
 String a = STR_NEW("hello");

 // no need to free it as this is allocated on the stack 

 ``` 

3. Concatenation

- String + String
```c

String hello = STR_NEW("Hello, ");
String world = STR_NEW("world");

String *combined = String_concat(&hello, &world);
// combined -> "Hello, world"

printf("%.*s\n", combined->length, combined->chars);

free_string(combined);
free(combined);

```

- String + Char & C string

```c

// Stack allocated
String base = STR_NEW("Hello");

// both of the below variables will be stack allocated
String ex1 = concat_char(&base, '!');
String more = concat_cstr(&ex, " How are you?");

printf("%.*s\n", more.length, more.chars);

free_string(&base);
free_string(&ex1);
free_string(&more);

```

4. Cloning and Moving

```c

// Stack allocated
String original = STR_NEW("Original");

// deep clone
String copy = String_clone(&original);

// move (original becomes invalid after this)
String moved = String_move(&original);

printf("%.*s\n", copy.length, copy.chars);
printf("%.*s\n", moved.length, moved.chars);

free_string(&copy);
free_string(&moved);
// do *NOT* free `original`

```

5. Substring and Indexing

```c

String text = STR_NEW("Hello, world");

// substring [7, 12) -> "world"
String sub = String_substr_range(&text, 7, 12);

char ch = String_char_at(&text, 1); // 'e'

printf("%.*s (%c)\n", sub.length, sub.chars, ch);

free_string(&text);
free_string(&sub);
```

6. Comparing Strings

```c

String a = STR_NEW("test");
String b = STR_NEW("test");
String c = STR_NEW("TEST");

if (String_cmp(&a, &b)) {
    printf("a == b\n");
}

if (!String_cmp(&a, &c)) {
    printf("a != c\n");
}
// `a`, `b` & `c` are stack allocated, so no free required

```

7. Join multiple strings

```c

String a = STR_NEW("one");
String b = STR_NEW("two");
String c = STR_NEW("three");

String *joined = String_join(3, &a, &b, &c);
// "onetwothree"

printf("%.*s\n", joined->length, joined->chars);

free_string(joined);
free(joined);

```

8. Using `StringArray`

```c

StringArray arr = string_array_init(4);

// all of the values can be stack or heap allocated as it is *cloned* inside `StringArray`
string_array_push(&arr, STR_NEW("apple"));
string_array_push(&arr, STR_NEW("banana"));
string_array_push(&arr, STR_NEW("cherry"));

print_string_array(&arr);

// access element
String s = string_array_get(&arr, 1);
printf("Second: %.*s\n", s.length, s.chars);

free_string_array(&arr);

```


> [!IMPORTANT]
> `string_array_push` clones the string value in the second argument

9. Joining in `StringArray`

```c

StringArray arr = string_array_init(3);

string_array_push(&arr, STR_NEW("red"));
string_array_push(&arr, STR_NEW("green"));
string_array_push(&arr, STR_NEW("blue"));

String sep = STR_NEW(", ");

String *result = string_array_join(&arr, sep);
// "red, green, blue"

printf("%.*s\n", result->length, result->chars);

free_string(result);
free(result);
free_string_array(&arr);

```
