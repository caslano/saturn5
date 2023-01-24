//  boost/filesystem/detail/macro_value.hpp  -------------------------------------------//

//  (C) Copyright John Maddock 2001 - 2003
//  (C) Copyright Jens Maurer 2001
//  (C) Copyright Peter Dimov 2001
//  (C) Copyright Darin Adler 2001
//  (C) Copyright Beman Dawes 2002

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//--------------------------------------------------------------------------------------//

#ifndef BOOST_FILESYSTEM_MACRO_VALUE_HPP
#define BOOST_FILESYSTEM_MACRO_VALUE_HPP

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <cstdlib>

namespace boost
{
  namespace detail
  {
    inline const char* macro_value(const char* name, const char* value)
    {
      static const char* no_value = "[no value]";
      static const char* not_defined = "[not defined]";

      BOOST_ASSERT_MSG(name, "name argument must not be a null pointer");
      BOOST_ASSERT_MSG(value, "value argument must not be a null pointer");

      return strcmp(name, value + 1)
        ? ((*value && *(value+1)) ? (value+1) : no_value)
        : not_defined; // name == value+1 so the macro is not defined
    }
  }  // detail
}  // boost

#define BOOST_MACRO_VALUE(X) boost::detail::macro_value(#X, BOOST_STRINGIZE(=X))

#endif  // BOOST_FILESYSTEM_MACRO_VALUE_HPP

/* macro_value.hpp
NfCXndEcMpriE/A33ndR27gkpWW81GdKC3hpSWO8tKT1eKlva/HSkv9PvFQ8uTV46WjvVuClDvMQGt5fgJd/L+C27Ub53896+V8DyqcbySi/eiDEZtieOa7AUvE+7Ez/kFLI5+FnBx8Pl0o+mjEOHl6EQ4PDN6043z+tBI14T7mvRuoLLafxrTyNzUsUqhStHzV0IrIcBZ93BdDqt41aVsV9fR9ojQPXhvQQaRLOzZ9zcFIWzhc6XxvnS2BSlv8UOimNJaI19zcZdeYRGNw04DZmSGxqlM8XJpBw+uJhZx68v1X+L9fRVirFMWncQeocsZFS1Lv4OXo8EG/wf/kxRCqtN9I5dp+GyGG9f8flfh0hewjulrZB6+r7MGNhqRhaW0w1yVfIsPSSPtUhJjkUpUqMpUrUubj3PkMgpPRGqBHn4sdrG2cro9noWNHI1toQXmD7D92MgWPPYhYAUGHDTKjq3O+LSXxQqAlZCjPHuiwVe8OQ8rSU79Pbs4SaZnxcjMruhfPEI6W3n4wXS4QBAOmquAWA3zr0jk48PkDwWc1+Mb2R/WIxV7f1Lub2iyPC1K/ewJ7ZN6DZZy47+UrIGJutdGlLX94jiS9XtOrLqyfxL/9g1sbLnolvVrbim9kDxTc7tOqb/cU3p2nfHMiesaZihlJTNmXrM6Cp9PGwB7pcLwy4bMgCoO1gX7OG/IcAnAtv9WLWWsLRTiYS
*/