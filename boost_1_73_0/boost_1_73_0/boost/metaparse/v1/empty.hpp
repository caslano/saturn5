#ifndef BOOST_METAPARSE_V1_EMPTY_HPP
#define BOOST_METAPARSE_V1_EMPTY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/end_of_input_expected.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/define_error.hpp>

#include <boost/mpl/empty.hpp>
#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Result>
      struct empty
      {
        typedef empty type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            boost::mpl::empty<S>,
            accept<Result, S, Pos>,
            reject<error::end_of_input_expected, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* empty.hpp
MGOLIHpZQRDFS5jPbyBQFluniKQx5RZedYZw1vf9rD8nin8+IpNW+sxZgKTH6Bph3VGvpNufCT7yEdRDVaKyI3Y6LCZun+W2mar7DISSNQ6zgVyW1dCLhn9jGnhdBxdgdqVNi1ES3cdLSuf7fBCprmupssHglvOT57c4CaPbE6ocvS0SPptfX5PxJKNwRCPkJU0i78D1AjKnubiBgrtMKKSBNaKCI1Noe8TEdtBSgabVVqe68tlHHCxA0oV2td4YjxFbDMRxh7+ybiq8Ilfa/Xz0mGtnENA7WUUBhB6Lw68AHJ9Hd5QsxvD9I0w8wjzYCD5588OP9gdQSwMECgAAAAgALWdKUo2DCakQAQAApAEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjM0VVQFAAG2SCRgdVFRa8IwEH7Przg6fJTMdU8jFkSUFaqVWvcyhqTtacvaZCSZQ4r/fWetupcRSO7yfd/dl4twaF0uLQZMVGqn6fjE4482hQ3YvtZZVqk9a09QV9ax+SSMNsmMCX4nCX7RPcAazQHN0FYFMmHwqz6e0T4gfFpXqFyP511CBNupAqa0omt+TUEo2ZArmX1bsgDtaXizA4JfQBC5bhqpioB5g9d4nYarl8EyjsJ1Oluu
*/