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
O/ItHsb3eSS/ZRcWJPIoVmR/1uQAHsqB7MlTOJiDOJaDOY2n8joO4XwO55NM4+tM55scUYr3uiP6FYwf2X/6Sd0nXHpujQa1Og4b2P+JsmeR/6nPIlfI6L526CwxXUzZtbB9664i4+lf9nxyW21a79d8a+9Vw/tKzhXRe8jEd6wVWv7896y/1jvWwver235uuvm71W2/U018n/rYgLJ3qmWfsk/Zp+xTrty/7/d/WnZG4c//
*/