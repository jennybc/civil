.onLoad <- function(libname, pkgname) {
  tzdata <- system.file("tzdata", package = "civil", mustWork = TRUE)
  civil_set_install(tzdata)

  vctrs::s3_register("pillar::pillar_shaft", "civil_rcrd", pillar_shaft.civil_rcrd)
  vctrs::s3_register("pillar::pillar_shaft", "civil_zoned_datetime", pillar_shaft.civil_zoned_datetime)
  vctrs::s3_register("pillar::pillar_shaft", "civil_zoned_nano_datetime", pillar_shaft.civil_zoned_nano_datetime)
}
