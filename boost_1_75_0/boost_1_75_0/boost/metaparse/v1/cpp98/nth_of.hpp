#ifndef BOOST_METAPARSE_V1_CPP98_NTH_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_NTH_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of_c.hpp>
#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        class K,
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct nth_of :
        nth_of_c<
          K::type::value,
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, P)
        >
      {};
    }
  }
}

#endif


/* nth_of.hpp
WuUcatm8nrW89y7W8mboWGh5h7RV2uX0mZ8dyZq2RNQScygHumvf4sBErh0YPtAqN5+hDzTq6QMx+fgBp7TZxj+wCywv+MIj/Av5+AVeQBjTBeEXQmJP5ccphtXcn7WmuxtbE6EdKixgnoKtsA2MB7qBq4jhLRLiFgbX67HU0s67wxEHBZzgOjXCoCXITHJI96awjGwHGWBBuI6Tp8q8V0etJd8RDtezI84JF6iOe9R4i1b5HSqGZNYxwMyzOME0wBAsCRtE2p13n6SqfY6fsLFPvB1Nn/j7PUHcobu1jzyWpTFUmOeY9UlknUD51z+wUSMWr4JG1xAnidLX0F4NFjnwGX/W2mOttHRt4z3WRilrwzOjSxsHhnfbRnDMOLQxczu1lbiatbV4BqNj+JjJzTrfMWOh5MScd6KpafM3Z6jpJ/I5/WzhvLNr+Pnx9BeniXeWstYyJ4XzTsfV5+Sd1NCxdt9pgisxhvr1znuCYy20X89c/T/1a19q1PiukRr95p4uffL3q/9LnwTl2OZTTI79SagaXd3JsWuvPnufhOwNKKGmjDmsqfV2bCoUqqbMSKi6X29yqP2KBMygRs3f/UGNvjg+SEAxlILvZ56dgmH0AzibOwnOZazJK8UQ8hGchWeHsyv9JGos8TsmrR+6pTv6zc/8X+aBIO5XUdvmBaztb6ZFMvVWkeaClVf9T3NBqjVUtm3uoG8ksG9Y
*/