#ifndef CIVIL_CIVIL_RCRD_H
#define CIVIL_CIVIL_RCRD_H

#include "r.h"
#include "utils-rlib.h"
#include <date/date.h>

static inline SEXP civil_rcrd_recycle(SEXP x, r_ssize size) {
  x = PROTECT(r_maybe_clone(x));

  r_ssize n = r_length(x);

  for (r_ssize i = 0; i < n; ++i) {
    r_list_poke(x, i, r_int_recycle(r_list_get(x, i), size));
  }

  UNPROTECT(1);
  return x;
}

static inline SEXP civil_rcrd_maybe_clone(SEXP x) {
  x = PROTECT(r_maybe_clone(x));

  r_ssize n = r_length(x);

  for (r_ssize i = 0; i < n; ++i) {
    r_list_poke(x, i, r_maybe_clone(r_list_get(x, i)));
  }

  UNPROTECT(1);
  return x;
}

static inline SEXP civil_rcrd_days(SEXP x) {
  return r_list_get(x, 0);
}
static inline SEXP civil_rcrd_time_of_day(SEXP x) {
  return r_length(x) < 2 ? NULL : r_list_get(x, 1);
}
static inline SEXP civil_rcrd_nanos_of_second(SEXP x) {
  return r_length(x) < 3 ? NULL : r_list_get(x, 2);
}

static inline int* civil_rcrd_days_deref(SEXP x) {
  return r_int_deref(civil_rcrd_days(x));
}
static inline int* civil_rcrd_time_of_day_deref(SEXP x) {
  SEXP time_of_day = civil_rcrd_time_of_day(x);
  return time_of_day == NULL ? NULL : r_int_deref(time_of_day);
}
static inline int* civil_rcrd_nanos_of_second_deref(SEXP x) {
  SEXP nanos_of_second = civil_rcrd_nanos_of_second(x);
  return nanos_of_second == NULL ? NULL : r_int_deref(nanos_of_second);
}

static inline void civil_rcrd_assign_missing(r_ssize i,
                                             int* p_days,
                                             int* p_time_of_day,
                                             int* p_nanos_of_second) {
  // Always exists
  p_days[i] = r_int_na;

  if (p_time_of_day != NULL) {
    p_time_of_day[i] = r_int_na;
  }
  if (p_nanos_of_second != NULL) {
    p_nanos_of_second[i] = r_int_na;
  }
}

// -----------------------------------------------------------------------------

static inline SEXP new_days_list(SEXP days) {
  SEXP out = PROTECT(r_new_list(1));
  r_list_poke(out, 0, days);

  SEXP names = PROTECT(r_new_character(1));
  r_chr_poke(names, 0, r_new_string("days"));

  r_poke_names(out, names);

  UNPROTECT(2);
  return out;
}

static inline SEXP new_days_time_of_day_list(SEXP days, SEXP time_of_day) {
  SEXP out = PROTECT(r_new_list(2));
  r_list_poke(out, 0, days);
  r_list_poke(out, 1, time_of_day);

  SEXP names = PROTECT(r_new_character(2));
  r_chr_poke(names, 0, r_new_string("days"));
  r_chr_poke(names, 1, r_new_string("time_of_day"));

  r_poke_names(out, names);

  UNPROTECT(2);
  return out;
}

static inline SEXP new_days_time_of_day_nanos_of_second_list(SEXP days,
                                                             SEXP time_of_day,
                                                             SEXP nanos_of_second) {
  SEXP out = PROTECT(r_new_list(3));
  r_list_poke(out, 0, days);
  r_list_poke(out, 1, time_of_day);
  r_list_poke(out, 2, nanos_of_second);

  SEXP names = PROTECT(r_new_character(3));
  r_chr_poke(names, 0, r_new_string("days"));
  r_chr_poke(names, 1, r_new_string("time_of_day"));
  r_chr_poke(names, 2, r_new_string("nanos_of_second"));

  r_poke_names(out, names);

  UNPROTECT(2);
  return out;
}

#endif
