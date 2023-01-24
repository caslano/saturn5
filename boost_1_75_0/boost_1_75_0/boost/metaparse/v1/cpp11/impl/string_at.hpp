#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_STRING_AT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_STRING_AT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_string_size.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int MaxLen, int Len, class T>
        constexpr T string_at(const T (&s)[Len], int n)
        {
          // "MaxLen + 1" adds the \0 character of the string literal to the
          // limit
          static_assert(Len <= MaxLen + 1, "String literal is too long.");
          return n >= Len - 1 ? T() : s[n];
        }
      }
    }
  }
}

#ifdef BOOST_METAPARSE_V1_STRING_AT
#  error BOOST_METAPARSE_V1_STRING_AT already defined
#endif
#define BOOST_METAPARSE_V1_STRING_AT \
  ::boost::metaparse::v1::impl::string_at<BOOST_METAPARSE_LIMIT_STRING_SIZE>

#endif


/* string_at.hpp
9PPF4XjuAu+aFsxtIncBZQfI47ALLYhPIP9HsB9/XcPCIXLuYa/SsjR1RL0NyC7lvQO+ecjSlNqGcFRW0moKLKH5TRjnK+mu3w3nYd8orduEKH8VovxliPIzAOVD06j3s5J7v9QasO2Ac5W73jnvzN/oNm0poO/B2k3hp5owZRnwvrzBk+V9U6ebyEtitFjJASAJxFMu3mVs4St9RszYcieXmPKgfwhGycFeJlUUR8/4TsHAHPhTqo2iYHilVaq/GbiymouqgQezY7JRK0sOTzlQctgO56fLaslvr2vwSA9hhYNbjOu7XIRUDlRSNjGjj9Rsy6+8v6T6/sjtLYA9IdU+K4SOCgvnWIK/VdjK0rSYNOHaUH/d9dlJpPpcii4K+2OYpFKqO5e4yJM39cUeB1KnM7nTUyllm2rvl56CiYYX7KWIC+G/UaGtQim6PZQvhlRgDmlhqjnOA13GRazHgDBv28+2oMfSxAwPDiLGOBMVefzSD78YL40lHtV1lfHsxkHMJx8UFioLc75vmy/Y4l0/b178wYagnyjVTRFjgFFfQHNJgBOct2iLooYvy67AFh4/bLTwErTQNhbl7LedGCEQvgFzfMzsAWzvml7sLi/Ciiq0M+7DbHhS3UqbOWJO8Y/4PXqA1YJ5yXSprpoUQu3oiwE3vulvNabxz07gK9dQxvKEhRw4tOdCVtiM2XG6Xu8apM1BtK6KGKcn
*/