#ifndef BOOST_METAPARSE_V1_CPP98_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/one_of.hpp>
#include <boost/metaparse/limit_one_of_size.hpp>

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
      struct one_of :
        impl::one_of<
          boost::mpl::vector<
            BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_ONE_OF_SIZE, P)
          >
        >
      {};
    }
  }
}

#endif


/* one_of.hpp
GKvyVVbjGu7F71iTVaSrNvdhHTbhPmzK+iw8X4R3gczzv+TzRVPT1eP+bMQDeCAPZDs24+FswXS2ZBZb81y25SU8mJeyHWexA29jR+5guZ3Zm115ErtxOI/mCHZndJzl7L7l4+x401XmiWzKk9ic/XgY+7MzB3ADK5rRkjC/F8L67y2+D/MbYrqGHMr9mcpWHMZOHM4eTOMAZnAIM5nDUZzI0ziFYziHY/kIx/El5nElJ/AN
*/