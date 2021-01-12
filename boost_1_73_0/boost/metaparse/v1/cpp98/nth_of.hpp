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
53CR3NfVPjtZDn/L2mzA+mzIxmzC5tyPLdmUUR8rq80X3p9v3sdKq3C9aM1GbMPmbMsOPIRHsj3TeChH8TCezU68mJ15BY/kAnbhvezGF3kUP+QxrGTZPViDPVmfvbgvj2NT9mELnsAOPJFd2ZfHsB9P4snM4gBO5kCewUGczsG8mEN4NYfzGqaxqC+1CvKHY0Ry32ejTVeH2WzIHDbnWHZhHodyPAv3l/DeG2dttr8YZ7qa
*/