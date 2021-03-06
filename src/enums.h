#ifndef CIVIL_ENUMS_H
#define CIVIL_ENUMS_H

#include "civil.h"
// -----------------------------------------------------------------------------

enum class day_nonexistent {
  last_time,
  first_time,
  last_day,
  first_day,
  na,
  error
};

enum day_nonexistent parse_day_nonexistent(const cpp11::strings& x);

// -----------------------------------------------------------------------------

enum class dst_nonexistent {
  roll_forward,
  roll_backward,
  shift_forward,
  shift_backward,
  na,
  error
};

enum dst_nonexistent parse_dst_nonexistent(const cpp11::strings& x);
enum dst_nonexistent parse_dst_nonexistent_one(const cpp11::r_string& x);

// -----------------------------------------------------------------------------

enum class dst_ambiguous {
  earliest,
  latest,
  na,
  error
};

enum dst_ambiguous parse_dst_ambiguous(const cpp11::strings& x);
enum dst_ambiguous parse_dst_ambiguous_one(const cpp11::r_string& x);

// -----------------------------------------------------------------------------

enum class unit {
  year,
  month,
  week,
  day,
  hour,
  minute,
  second,
  millisecond,
  microsecond,
  nanosecond
};

enum unit parse_unit(const cpp11::strings& x);

// -----------------------------------------------------------------------------

enum class adjuster {
  year,
  month,
  day,
  hour,
  minute,
  second,
  nanosecond,
  last_day_of_month
};

enum adjuster parse_adjuster(const cpp11::strings& x);

// -----------------------------------------------------------------------------
#endif
