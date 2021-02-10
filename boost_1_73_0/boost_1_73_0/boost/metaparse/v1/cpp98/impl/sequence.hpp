#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/sequence_impl.hpp>
#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/mpl/vector.hpp>

#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        #ifdef BOOST_METAPARSE_SEQUENCE_CASE
        #  error BOOST_METAPARSE_SEQUENCE_CASE already defined
        #endif
        #define BOOST_METAPARSE_SEQUENCE_CASE(z, n, unused) \
          template <BOOST_PP_ENUM_PARAMS(n, class P)> \
          struct BOOST_PP_CAT(sequence, n) \
          { \
            typedef BOOST_PP_CAT(sequence, n) type; \
            \
            template <class S, class Pos> \
            struct apply : \
              sequence_impl< \
                boost::mpl::vector<BOOST_PP_ENUM_PARAMS(n, P)>, \
                S, \
                Pos \
              > \
            {}; \
          };
        
        BOOST_PP_REPEAT_FROM_TO(
          1,
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          BOOST_METAPARSE_SEQUENCE_CASE,
          ~
        )
        
        #undef BOOST_METAPARSE_SEQUENCE_CASE
      } 
    }
  }
}

#endif


/* sequence.hpp
jDhvPc2WyfM8anl189ki4b5vXpoXOAUC5zmKzPow0RzQiYe0ujChY1aiKaC1XExIEy/kyk8bV5rGRVpnb8oiwByHglAu7hLkobGh5e9o5HoP4QWItUMTmuEBIRcWVogKmjbXrsniXcj1Uox2OtXFmPny1g6O76XBnogsgj+MNtgbNahzvyFymvfKFLz1/rBYPs9eG+w+TbGk8DW/9kNKik8UNAPUmB6EQW96Y57vP3ihwfbRf//C/2k+/uEi1Pb7R/uDC/vWZfTADv7rvIHP46f55Oe/ht9QSwMECgAAAAgALWdKUu229Zt4AgAA9QUAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzQ1VVQFAAG2SCRg5VRRb9owEH63xH84UfEykRpYN6lpiFRB1VbrCoK0e5xMchCrwY5sh45/v7MDBWn7BdtL4jvffffd3ZckDq3LhcWUJVKtNb3ecP+uTWFT9pBl8/CA+7uMJfx0k/A2mF2wxGBd7clVCCdA6bzE/G3c3aPttgh8eDmE0WAAs28dNhUOY8ga7MPgGp71jm6GAxhexVfXMcXcf886bIlmhyYGzy2yweBr8YYdNtHKoXLRE6qNK2P4GlwKcye1iiGvtD2LyvY1epRfjpduW50uptLW
*/