#' @export
local_year_month <- function(year, month = 1L) {
  args <- list(year = year, month = month)
  size <- vec_size_common(!!!args)
  args <- vec_recycle_common(!!!args, .size = size)
  args <- vec_cast_common(!!!args, .to = integer())

  day <- ones_along(args$year)
  day_nonexistent <- "last-time"

  fields <- convert_year_month_day_to_local_fields(
    args$year,
    args$month,
    day,
    day_nonexistent
  )

  new_local_year_month_from_fields(fields)
}

new_local_year_month <- function(days = integer(),
                                 ...,
                                 names = NULL) {
  if (!is_integer(days)) {
    abort("`days` must be an integer.")
  }

  fields <- list(
    days = days
  )

  new_local(
    fields,
    ...,
    names = names,
    class = "civil_local_year_month"
  )
}

new_local_year_month_from_fields <- function(fields, names = NULL) {
  new_local_year_month(
    days = fields$days,
    names = names
  )
}

#' @export
vec_proxy.civil_local_year_month <- function(x, ...) {
  proxy_civil_rcrd(x)
}

#' @export
vec_restore.civil_local_year_month <- function(x, to, ...) {
  fields <- restore_civil_rcrd_fields(x)
  names <- restore_civil_rcrd_names(x)
  new_local_year_month_from_fields(fields, names)
}

#' @export
vec_proxy_equal.civil_local_year_month <- function(x, ...) {
  proxy_equal_civil_rcrd(x)
}

#' @export
format.civil_local_year_month <- function(x,
                                          ...,
                                          format = fmt_local_year_month()) {
  x <- as_local_datetime(x)
  format(x, ..., format = format)
}

#' @export
vec_ptype_full.civil_local_year_month <- function(x, ...) {
  "civil_year_month"
}

#' @export
vec_ptype_abbr.civil_local_year_month <- function(x, ...) {
  "cvl_ym"
}

is_local_year_month <- function(x) {
  inherits(x, "civil_local_year_month")
}
