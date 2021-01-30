#ifndef BOOST_METAPARSE_V1_DIGIT_VAL_HPP
#define BOOST_METAPARSE_V1_DIGIT_VAL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/digit.hpp>
#include <boost/metaparse/v1/transform.hpp>

#include <boost/metaparse/v1/util/digit_to_int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef transform<digit, util::digit_to_int<> > digit_val;
    }
  }
}

#endif


/* digit_val.hpp
3fafKLK5HrLPS9sOtZt9cZ2HzlsKf7uH7CVPmLL9HrI5Twhb8p5Qxr8L3XVue0KUiwZFJ9VDZ4diU2jh
*/