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
mcmJHMLbOZRTmc3ZHMZ5vIIvcCTf4iiu5Wh+zKtYwif9NSzDcazEa3ksr+cJvIlNOYnpvJmDeQvv5K1czNv4FO/iJk7jFt7LEuWs7zyQi3gsH+UJfIot+TTH8RnewOc5ky/wfr7G1XyDa/k2v+I73MF3WeIQ6znLcS1r8gPW54c8levYiR+xB//OvtzAS/gFp3A7n+E3fJ7f8lXu5Gp+z7XMfaZQw/LWVzZlWZ7BcuzEQ9iV
*/