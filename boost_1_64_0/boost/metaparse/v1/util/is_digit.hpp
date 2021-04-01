#ifndef BOOST_METAPARSE_V1_UTIL_IS_DIGIT_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/in_range_c.hpp>

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
        struct is_digit : in_range_c<char, '0', '9'>::apply<C> {};

        template <>
        struct is_digit<boost::mpl::na>
        {
          typedef is_digit type;

          template <class C = boost::mpl::na>
          struct apply : is_digit<C> {};
        };
      }
    }
  }
}

#endif


/* is_digit.hpp
vyoXE4jKyMFpYQH/1+3YCYQXIXwygvwtzfcJbm6YF1uHwE5IM4ZmNJxrhDXxV3sJCx9NmWokZz5yxetUfydf6ZcEC5aBXc8w48zmPID5wiKRV5rrlHccP+XPtw1JOHfSYe4xzKSwg1C0mYhSEAasoe+THL7hikRwq36+4qdBrjXglj0kBYt+mG5ACDhXbjYObJI1qS7FOnTGgDtnRWWWGYbjEoI5hr0LSw0NbcywHH8wHbRyurR+U8aTIxbi1tT7cGXv7EgalOisf3K4Uyt4lwn5gJO3cTNn6dF61yfwFoDnr3pi0FubHtINnOzETpSMXpUFoykXpC5pYu5b+mzu8CI9xHMBFJIaLJHoM60DDo+FREapYlGTsDys8FfGc/xgwEFT9usT9umpgn4bCysm82i6bKHe9nGZdd7LJ9So63Xe+fKwlF4ju0bYsGgx6AfMeNDdLdS4VayYomKdLVabtEcKaEDW3flc6QLTpH9rvJLkBeEUTftHsGm/o0Rs1odVVdLOSm5Axjxc+wxrmI64ro2PIj/ydZuc/BhK7Jr4T8iQ5oxEaFTsFS93/Q==
*/