#include "r.h"
#include "utils.h"
#include "enums.h"
#include "conversion.h"
#include "resolve.h"
#include "civil-rcrd.h"
#include "check.h"
#include <date/date.h>
#include <date/tz.h>
#include <sstream>

/*
 * Adding another template variation of `from_stream()` that parses into a ymd
 * and tod directly. This way we keep the precision when parsing large dates
 * (i.e. with year past 1970 +/- 292) that have nanoseconds
 */

template <class Duration, class CharT, class Traits, class Alloc = std::allocator<CharT>>
std::basic_istream<CharT, Traits>&
from_stream(std::basic_istream<CharT, Traits>& is,
            const CharT* fmt,
            date::year_month_day& ymd,
            date::hh_mm_ss<Duration>& tod,
            std::basic_string<CharT, Traits, Alloc>* abbrev = nullptr,
            std::chrono::minutes* offset = nullptr)
{
  using CT = typename std::common_type<Duration, std::chrono::seconds>::type;
  std::chrono::minutes offset_local{};
  std::chrono::minutes* offptr = offset ? offset : &offset_local;
  date::fields<CT> fds{};
  fds.has_tod = true;
  from_stream(is, fmt, fds, abbrev, offptr);
  if (!fds.ymd.ok() || !fds.tod.in_conventional_range())
    is.setstate(std::ios::failbit);
  if (!is.fail()) {
    ymd = fds.ymd;
    tod = fds.tod;
  }
  return is;
}

template <class Duration, class CharT, class Traits>
std::basic_istream<CharT, Traits>&
civil_parse(std::basic_istream<CharT, Traits>& is,
            const char* format,
            date::year_month_day& ymd,
            date::hh_mm_ss<Duration>& tod)
{
  return from_stream(is, format, ymd, tod);
}

[[cpp11::register]]
SEXP fn() {
  date::year_month_day ymd;
  date::hh_mm_ss<std::chrono::nanoseconds> tod;

  std::istringstream in{"Sep 20 2300 at 5:15:37.002 PM"};

  civil_parse(in, "%b %d %Y at %I:%M:%S %p", ymd, tod);

  Rprintf("year %i\n", static_cast<int>(ymd.year()));

  Rprintf("second %i\n", tod.seconds().count());

  Rprintf("nanos of second %i\n", tod.subseconds().count());

  return R_NilValue;
}
