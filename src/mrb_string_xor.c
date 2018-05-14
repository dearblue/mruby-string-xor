/*
** mrb_string_xor.c - String#xor
**
** Copyright (c) Seiei Miyagi 2017
**
** See Copyright Notice in LICENSE
*/

#include <mruby.h>
#include <mruby/string.h>
#include "mrb_string_xor.h"


#define DONE mrb_gc_arena_restore(mrb, 0);

static mrb_value
string_xor(mrb_state *mrb, mrb_value self)
{
  mrb_value s, str2;
  mrb_int len;
  char *p, *pend, *p2;

  len = RSTRING_LEN(self);
  mrb_get_args(mrb, "S", &str2);
  if (len != RSTRING_LEN(str2)) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "string length does not match");
  }
  s = mrb_str_dup(mrb, self);
  p = RSTRING_PTR(s);
  p2 = RSTRING_PTR(str2);
  pend = RSTRING_END(s);
  while (p < pend) {
    *p ^= *p2;
    p++;
    p2++;
  }
  return s;
}

static mrb_value
string_xor_clamp(mrb_state *mrb, mrb_value self)
{
  mrb_value s, str2;
  mrb_int len, len2;
  char *p, *pend, *p2;

  len = RSTRING_LEN(self);
  mrb_get_args(mrb, "S", &str2);
  s = mrb_str_dup(mrb, self);
  mrb_str_modify(mrb, RSTRING(s));
  p = RSTRING_PTR(s);
  p2 = RSTRING_PTR(str2);
  len2 = RSTRING_LEN(str2);
  pend = p + (len < len2 ? len : len2);
  while (p < pend) {
    *p ^= *p2;
    p++;
    p2++;
  }
  return s;
}

static mrb_value
string_xor_repeat(mrb_state *mrb, mrb_value self)
{
  mrb_value s, str2;
  mrb_int len, len2;
  char *p, *pend;
  const char *p2, *p2tmp;
  int i, j;

  len = RSTRING_LEN(self);
  mrb_get_args(mrb, "S", &str2);
  s = mrb_str_dup(mrb, self);
  mrb_str_modify(mrb, RSTRING(s));
  p = RSTRING_PTR(s);
  p2 = RSTRING_PTR(str2);
  len2 = RSTRING_LEN(str2);
  pend = RSTRING_END(s);
  for (i = len / len2; i > 0; i--) {
    p2tmp = p2;
    for (j = len2; j > 0; j--) {
      *p ^= *p2tmp;
      p++;
      p2tmp++;
    }
  }
  while (p < pend) {
    *p ^= *p2;
    p++;
    p2++;
  }
  return s;
}

void
mrb_mruby_string_xor_gem_init(mrb_state* mrb)
{
  struct RClass * s = mrb->string_class;
  mrb_define_method(mrb, s, "^", string_xor, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, s, "xor_clamp", string_xor_clamp, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, s, "xor_repeat", string_xor_repeat, MRB_ARGS_REQ(1));
  DONE;
}

void
mrb_mruby_string_xor_gem_final(mrb_state* mrb)
{
}
