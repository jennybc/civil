#include "enums.h"
#include "utils.h"
#include <cstring>
#include <string>

// -----------------------------------------------------------------------------

// [[ include("enums.h") ]]
enum day_nonexistent parse_day_nonexistent(const cpp11::strings& x) {
  if (x.size() != 1) {
    civil_abort("`day_nonexistent` must be a string with length 1.");
  }

  std::string string = x[0];

  if (string == "last-time") return day_nonexistent::last_time;
  if (string == "first-time") return day_nonexistent::first_time;
  if (string == "last-day") return day_nonexistent::last_day;
  if (string == "first-day") return day_nonexistent::first_day;
  if (string == "NA") return day_nonexistent::na;
  if (string == "error") return day_nonexistent::error;

  civil_abort("'%s' is not a recognized `day_nonexistent` option.", string.c_str());
}

// -----------------------------------------------------------------------------

// [[ include("enums.h") ]]
enum dst_nonexistent parse_dst_nonexistent(const cpp11::strings& x) {
  if (x.size() != 1) {
    civil_abort("`dst_nonexistent` must be a string with length 1.");
  }

  return parse_dst_nonexistent_one(x[0]);
}

// [[ include("enums.h") ]]
enum dst_nonexistent parse_dst_nonexistent_one(const cpp11::r_string& x) {
  std::string string(x);

  if (string == "roll-forward") return dst_nonexistent::roll_forward;
  if (string == "roll-backward") return dst_nonexistent::roll_backward;
  if (string == "shift-forward") return dst_nonexistent::shift_forward;
  if (string == "shift-backward") return dst_nonexistent::shift_backward;
  if (string == "NA") return dst_nonexistent::na;
  if (string == "error") return dst_nonexistent::error;

  civil_abort("'%s' is not a recognized `dst_nonexistent` option.", string.c_str());
}

// -----------------------------------------------------------------------------

// [[ include("enums.h") ]]
enum dst_ambiguous parse_dst_ambiguous(const cpp11::strings& x) {
  if (x.size() != 1) {
    civil_abort("`dst_ambiguous` must be a string with length 1.");
  }

  return parse_dst_ambiguous_one(x[0]);
}

// [[ include("enums.h") ]]
enum dst_ambiguous parse_dst_ambiguous_one(const cpp11::r_string& x) {
  std::string string(x);

  if (string == "earliest") return dst_ambiguous::earliest;
  if (string == "latest") return dst_ambiguous::latest;
  if (string == "NA") return dst_ambiguous::na;
  if (string == "error") return dst_ambiguous::error;

  civil_abort("'%s' is not a recognized `dst_ambiguous` option.", string.c_str());
}

// -----------------------------------------------------------------------------

// [[ include("enums.h") ]]
enum unit parse_unit(const cpp11::strings& x) {
  if (x.size() != 1) {
    civil_abort("`unit` must be a string with length 1.");
  }

  std::string string = x[0];

  if (string == "year") return unit::year;
  if (string == "month") return unit::month;
  if (string == "week") return unit::week;
  if (string == "day") return unit::day;
  if (string == "hour") return unit::hour;
  if (string == "minute") return unit::minute;
  if (string == "second") return unit::second;
  if (string == "millisecond") return unit::millisecond;
  if (string == "microsecond") return unit::microsecond;
  if (string == "nanosecond") return unit::nanosecond;

  civil_abort("'%s' is not a recognized `unit` option.", string.c_str());
}

// -----------------------------------------------------------------------------

// [[ include("enums.h") ]]
enum adjuster parse_adjuster(const cpp11::strings& x) {
  if (x.size() != 1) {
    civil_abort("`adjuster` must be a string with length 1.");
  }

  std::string string = x[0];

  if (string == "year") return adjuster::year;
  if (string == "month") return adjuster::month;
  if (string == "day") return adjuster::day;
  if (string == "hour") return adjuster::hour;
  if (string == "minute") return adjuster::minute;
  if (string == "second") return adjuster::second;
  if (string == "nanosecond") return adjuster::nanosecond;
  if (string == "last_day_of_month") return adjuster::last_day_of_month;

  civil_abort("'%s' is not a recognized `adjuster` option.", string.c_str());
}
