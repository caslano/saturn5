#ifndef BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF1_HPP
#define BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_one_of_size.hpp>
#include <boost/metaparse/v1/cpp98/impl/one_of.hpp>
#include <boost/metaparse/v1/repeated1.hpp>

#include <boost/mpl/vector.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_ONE_OF_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct repeated_one_of1 :
        repeated1<
          impl::one_of<
            boost::mpl::vector<
              BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_ONE_OF_SIZE, P)
            >
          >
        >
      {};
    }
  }
}

#endif


/* repeated_one_of1.hpp
iV3Yn10ZPZdYFJZ3TwnPJXqE5fRkA/bi/uzDFjye3XgCe/FEHsd+vJT9eQUH8AaewvkclLC+OTW3vL6pYX2HsQ6HsyFHsikz2ImZ7MZRPJqjeRKz2Z85jPpWXB2W53qyWd+KE0xXmxP5W05iU05mW57OI3gGj+bZPJZTeQrPYTqnM5szOJkzeQHzeS1/xz/wat7N2VzGOXyV13Alf88feAN3kd6buRcXMIW30nppQzV672Jd
*/