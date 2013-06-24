#
# Check for std::tr1::unordered_set.  This is from
# http://gcc.gnu.org/onlinedocs/libstdc++/manual/backwards.html
#
# AC_HEADER_TR1_UNORDERED_SET
AC_DEFUN([AC_HEADER_TR1_UNORDERED_SET], [
  AC_CACHE_CHECK(for tr1/unordered_set,
  ac_cv_cxx_tr1_unordered_set,
  [AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  AC_TRY_COMPILE([#include <tr1/unordered_set>], [using std::tr1::unordered_set;],
  ac_cv_cxx_tr1_unordered_set=yes, ac_cv_cxx_tr1_unordered_set=no)
  AC_LANG_RESTORE
  ])
  if test "$ac_cv_cxx_tr1_unordered_set" = yes; then
    AC_DEFINE(HAVE_TR1_UNORDERED_SET,,[Define if tr1/unordered_set is present. ])
  fi
])
