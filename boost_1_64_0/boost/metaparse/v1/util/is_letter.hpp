#ifndef BOOST_METAPARSE_V1_UTIL_IS_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/is_ucase_letter.hpp>
#include <boost/metaparse/v1/util/is_lcase_letter.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_letter :
          boost::mpl::bool_<
            is_lcase_letter<C>::type::value || is_ucase_letter<C>::type::value
          >
        {};

        template <>
        struct is_letter<boost::mpl::na>
        {
          typedef is_letter type;
          
          template <class C = boost::mpl::na>
          struct apply : is_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_letter.hpp
eeYCbn6nVirlAyAv93uTdqsjvLBw7db2YHlYQbXFJ5QW81JE/jFqVi/12GDegxmHsVILB3ZEJJsLl6yCFU6UwJubDZs7Ju8mUIUCRCNQmIyjQy/Y+2tDriLxGitmx3pYhTsBFdlZo8eE8U1dc8C48kDOwuk6DvlQSfgPM3Tev1LfY4rVoLjtGH1WTSd4GDj8QH4hZoSeYs0gK1HbGNQvpeq5HDqmWneltDOaVW2qyXpKMvWwYcOYH+6N8BBssZj2Zc5wd+mKseGQJ5hcqmCaHy5S9kh+Ib/Gjhtj7Psz6mzfLx50eGWeJwoyQz6rMMpqSc8wMQLrPYB0YCeQo2ub7EMJeZJsmyW4Z/DqFdB7wEt05h5ebU/S7Dlaeaf9KLBSAc7pjFPlD4CN+WvUFKvQnwjwdfjM6pyCsY7OW0GN8LTD4GBmbfj1wchYgBllDUbhlCtKqDiJziThZeMEFZ0YCXTNzf5NrM6QvVHg+1JxgiU7ix4EOAW8SisqXYPqhLLXD8Xyq5INy/rIEuuR5HRm5VZPzFd9JKO6/w9YbTb1BY0Tia8oExGV8SXudw==
*/