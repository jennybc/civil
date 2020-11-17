#include "utils-rlib.h"
#include <R_ext/Parse.h>

// -----------------------------------------------------------------------------

SEXP r_syms_x;
SEXP r_syms_class;
SEXP r_syms_names;

// -----------------------------------------------------------------------------

SEXP r_parse(const char* str) {
  SEXP str_ = PROTECT(r_new_scalar_character_from_c_string(str));

  ParseStatus status;
  SEXP out = PROTECT(R_ParseVector(str_, -1, &status, r_null));
  if (status != PARSE_OK) {
    Rf_errorcall(R_NilValue, "Parsing failed");
  }
  if (r_length(out) != 1) {
    Rf_errorcall(R_NilValue, "Expected a single expression");
  }

  out = r_list_get(out, 0);

  UNPROTECT(2);
  return out;
}

SEXP r_parse_eval(const char* str, SEXP env) {
  SEXP out = r_eval(PROTECT(r_parse(str)), env);
  UNPROTECT(1);
  return out;
}

// -----------------------------------------------------------------------------

static SEXP new_env_call = NULL;
static SEXP new_env__parent_node = NULL;
static SEXP new_env__size_node = NULL;

SEXP r_new_environment(SEXP parent, r_ssize size) {
  parent = parent ? parent : r_empty_env;
  r_node_poke_car(new_env__parent_node, parent);

  size = size ? size : 29;
  r_node_poke_car(new_env__size_node, r_new_scalar_integer(size));

  SEXP env = r_eval(new_env_call, r_base_env);

  // Free for gc
  r_node_poke_car(new_env__parent_node, r_null);

  return env;
}

// -----------------------------------------------------------------------------

SEXP r_eval_in_with_x(SEXP call, SEXP env,
                      SEXP x, SEXP x_sym) {
  r_env_poke(env, x_sym, x);
  return r_eval(call, env);
}

SEXP r_eval_with_x(SEXP call, SEXP parent, SEXP x) {
  SEXP env = PROTECT(r_new_environment(parent, 1));
  SEXP out = r_eval_in_with_x(call, env, x, r_syms_x);
  UNPROTECT(1);
  return out;
}

// -----------------------------------------------------------------------------

#define BUFSIZE 8192

#define INTERP(BUF, FMT, DOTS)                  \
{                                               \
  va_list dots;                                 \
  va_start(dots, FMT);                          \
  vsnprintf(BUF, BUFSIZE, FMT, dots);           \
  va_end(dots);                                 \
                                                \
  BUF[BUFSIZE - 1] = '\0';                      \
}

static SEXP err_call = NULL;
void r_abort(const char* fmt, ...) {
  char buf[BUFSIZE];
  INTERP(buf, fmt, ...);

  SEXP sexp_buf = PROTECT(r_new_scalar_character_from_c_string(buf));

  r_eval_with_x(err_call, r_base_env, sexp_buf);

  while (1); // No return
}

#undef BUFSIZE

// -----------------------------------------------------------------------------

void r_init_utils() {
  r_syms_x = r_sym("x");
  r_syms_class = r_sym("class");
  r_syms_names = r_sym("names");

  new_env_call = r_parse_eval("as.call(list(new.env, TRUE, NULL, NULL))", r_base_env);
  r_mark_precious(new_env_call);

  new_env__parent_node = r_node_cddr(new_env_call);
  new_env__size_node = r_node_cdr(new_env__parent_node);

  err_call = r_parse("rlang::abort(x)");
  r_mark_precious(err_call);
}
