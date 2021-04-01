#ifndef BOOST_METAPARSE_V1_SEQUENCE_APPLY_HPP
#define BOOST_METAPARSE_V1_SEQUENCE_APPLY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/letter.hpp>
#include <boost/metaparse/v1/sequence.hpp>

#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/mpl/at.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
#ifdef BOOST_METAPARSE_SEQUENCE_APPLY_ARG
#  error BOOST_METAPARSE_SEQUENCE_APPLY_ARG already defined
#endif
#define BOOST_METAPARSE_SEQUENCE_APPLY_ARG(z, n, container) \
  typename boost::mpl::at_c<container, n>::type

#ifdef BOOST_METAPARSE_SEQUENCE_APPLY
#  error BOOST_METAPARSE_SEQUENCE_APPLY already defined
#endif
#define BOOST_METAPARSE_SEQUENCE_APPLY(z, n, unused) \
  namespace impl \
  { \
  template < \
    template <BOOST_PP_ENUM(n, class BOOST_PP_TUPLE_EAT(3), ~)> class T \
  > \
  struct BOOST_PP_CAT(sequence_apply_transform, n) \
  { \
    typedef BOOST_PP_CAT(sequence_apply_transform, n) type; \
    \
    template <class V> \
    struct apply \
    { \
      typedef T<BOOST_PP_ENUM(n, BOOST_METAPARSE_SEQUENCE_APPLY_ARG, V)> type; \
    }; \
  }; \
  } \
  \
  template < \
    template <BOOST_PP_ENUM(n, class BOOST_PP_TUPLE_EAT(3), ~)> class T, \
    BOOST_PP_ENUM_PARAMS(n, class P) \
  > \
  struct BOOST_PP_CAT(sequence_apply, n) : \
    transform< \
      sequence<BOOST_PP_ENUM_PARAMS(n, P)>, \
      BOOST_PP_CAT(impl::sequence_apply_transform, n)<T> \
    > \
  {};

      BOOST_PP_REPEAT_FROM_TO(
        1,
        BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
        BOOST_METAPARSE_SEQUENCE_APPLY,
        ~
      )

#undef BOOST_METAPARSE_SEQUENCE_APPLY
#undef BOOST_METAPARSE_SEQUENCE_APPLY_ARG
    }
  }
}

#endif


/* sequence_apply.hpp
Iz4l9IDFe0o8mvtnnRpUxouRCmt2uVpEp2cDQLKew1keq6+F1P+GZ14VXrdnE2d3Gu/EdEWQd7xqGxtrtCnL7SuJyH1n0WHNyVPYcgjdY6DqK1EEamim3GhNAtMCSPLGB1yh8dF6s1Mu5MYSeMzqFlIDwpn9RiNaX+Dtv94g1nSgOAEQfh0ssS5a//WIQVyef/GkMrw4gVAL+QYnE2MusGR4246uyLf8qxpuWpn/10AompJx68ZsrnTvV9Tj4Z2SSC8ctiMUd/7dd4gBAiV397pGUYvvAKaExYVR5UUrivqgqcQbN1V/SZWIGPJXNSBLJ0yCfcWkUZLlk1OnPNvWKuPbT/H8uEKmTUHdyF6fhXm9ZtlHzdRgQQH9UijFTg+p2mfUMNSIPYf7CDE4tP/sXB3hP5nVRK3iSSMiWiSTKA8btZ+/QcC2HYpDUDlAzsVxWABL8Q3askLxtzkKu9l5CQRRoTWTfW8N+0xyI2TL3TQEEmZgoATWXPs6oFYokUYatss8L/p31g6qRhckSOpRa8n9Od7IUtDDAf+nwTTCXW1fSq46JpAqHVHvkw==
*/