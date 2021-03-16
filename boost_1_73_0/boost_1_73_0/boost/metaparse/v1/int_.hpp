#ifndef BOOST_METAPARSE_V1_INT__HPP
#define BOOST_METAPARSE_V1_INT__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/digit_val.hpp>
#include <boost/metaparse/v1/foldl1.hpp>
#include <boost/metaparse/v1/impl/next_digit.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef foldl1<digit_val, boost::mpl::int_<0>, impl::next_digit> int_;
    }
  }
}

#endif


/* int_.hpp
C7cbWtg0jY6UqZtJPW1kM4aesc7GAhWNtbQYaSNh6ur901JTaD1uhDOmHqxp1KU7esIwokYU8IxAfaPekYwaeWhC9ckWd4aLa8zGTEOvtNDmcFSPSGdaDd1axnX1iA+X1bvY3A/SNzObToiE5i5dltF4s8ywddfAEm4f6GVdadM7w/GsJdza3kp/Eq1mm7piRCJ6xEib9i9qOVY/Ozpx021GPA7NLM7iCDNccd1MSScMj3C8c0tGknG9U1Z4aDE=
*/