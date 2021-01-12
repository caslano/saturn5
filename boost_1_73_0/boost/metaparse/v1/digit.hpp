#ifndef BOOST_METAPARSE_V1_DIGIT_HPP
#define BOOST_METAPARSE_V1_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/digit_expected.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/change_error_message.hpp>

#include <boost/metaparse/v1/util/is_digit.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef
        accept_when<
          change_error_message<one_char, error::digit_expected>,
          util::is_digit<>,
          error::digit_expected
        >
        digit;
    }
  }
}

#endif


/* digit.hpp
13IDP+BurmP50j7DWZefsCU/ZWt+wfP4FYdzC6/kVo7jTt7F7ziX33MRd7HIgdZzHsEiuX1Gcz/+gUXZhqXYk6V5MQ9kNg/i0yzH93kIN/Iw/sgK3LeMz0F2ZxVewJoczFocw9q8hnV4A+vyL6zPxWzA19mIK9iY29iE37I5z3Stbkuey1M4i6fyAZ7B/cpaj1mCnVmRXViVXXkCu7Ex/8gW7MMzmcbO7McL2J8ZHMAhHMwr
*/