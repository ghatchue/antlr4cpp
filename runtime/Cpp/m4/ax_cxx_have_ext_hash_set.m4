#
# Check for C++ namespace support.  This is from
# http://www.gnu.org/software/ac-archive/htmldoc/ac_cxx_namespaces.html
#
AC_DEFUN([AC_CXX_NAMESPACES],
[AC_CACHE_CHECK(whether the compiler implements namespaces,
ac_cv_cxx_namespaces,
[AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_COMPILE([namespace Outer { namespace Inner { int i = 0; }}],
                [using namespace Outer::Inner; return i;],
 ac_cv_cxx_namespaces=yes, ac_cv_cxx_namespaces=no)
 AC_LANG_RESTORE
])
if test "$ac_cv_cxx_namespaces" = yes; then
  AC_DEFINE(HAVE_NAMESPACES,,[define if the compiler implements namespaces])
fi
])

#
# Check for hash_set extension.  This is from
# http://www.gnu.org/software/ac-archive/htmldoc/ac_cxx_have_ext_hash_set.html
#
AC_DEFUN([AC_CXX_HAVE_STD_EXT_HASH_SET],
[AC_CACHE_CHECK([whether the compiler has <ext/hash_set> defining template class std::hash_set],
 ac_cv_cxx_have_std_ext_hash_set,
 [AC_REQUIRE([AC_CXX_NAMESPACES])
  AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  AC_TRY_COMPILE([#include <ext/hash_set>
#ifdef HAVE_NAMESPACES
using namespace std;
#endif],[hash_set<int> t;],
  [ac_cv_cxx_have_std_ext_hash_set=yes], [ac_cv_cxx_have_std_ext_hash_set=no])
  AC_LANG_RESTORE])
 if test "$ac_cv_cxx_have_std_ext_hash_set" = yes; then
   AC_DEFINE(HAVE_STD_EXT_HASH_SET,,[Define if the compiler has a header <ext/hash_set> that defines template class std::hash_set.])
 fi])

AC_DEFUN([AC_CXX_HAVE_GNU_EXT_HASH_SET],
[AC_CACHE_CHECK([whether the compiler has <ext/hash_set> defining template class __gnu_cxx::hash_set],
 ac_cv_cxx_have_gnu_ext_hash_set,
 [AC_REQUIRE([AC_CXX_NAMESPACES])
  AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  AC_TRY_COMPILE([#include <ext/hash_set>
#ifdef HAVE_NAMESPACES
using namespace __gnu_cxx;
#endif],[hash_set<int> t; ],
  [ac_cv_cxx_have_gnu_ext_hash_set=yes],[ac_cv_cxx_have_gnu_ext_hash_set=no])
  AC_LANG_RESTORE])
 if test "$ac_cv_cxx_have_gnu_ext_hash_set" = yes; then
   AC_DEFINE(HAVE_GNU_EXT_HASH_SET,,[Define if the compiler has a header <ext/hash_set> that defines template class __gnu_cxx::hash_set.])
 fi])

AC_DEFUN([AC_CXX_HAVE_GLOBAL_HASH_SET],
[AC_CACHE_CHECK([whether the compiler has <hash_set> defining template class ::hash_set],
 ac_cv_cxx_have_global_hash_set,
 [AC_REQUIRE([AC_CXX_NAMESPACES])
  AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  AC_TRY_COMPILE([#include <hash_set>],[hash_set<int> t; ],
  [ac_cv_cxx_have_global_hash_set=yes], [ac_cv_cxx_have_global_hash_set=no])
  AC_LANG_RESTORE])
 if test "$ac_cv_cxx_have_global_hash_set" = yes; then
   AC_DEFINE(HAVE_GLOBAL_HASH_SET,,[Define if the compiler has a header <hash_set> that defines template class ::hash_set.])
 fi])

AC_DEFUN([AC_CXX_HAVE_HASH_SET],
[AC_CXX_HAVE_STD_EXT_HASH_SET
 AC_CXX_HAVE_GNU_EXT_HASH_SET
 AC_CXX_HAVE_GLOBAL_HASH_SET])
