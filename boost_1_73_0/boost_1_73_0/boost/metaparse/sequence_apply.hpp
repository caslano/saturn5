#ifndef BOOST_METAPARSE_SEQUENCE_APPLY_HPP
#define BOOST_METAPARSE_SEQUENCE_APPLY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/sequence_apply.hpp>

#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost
{
  namespace metaparse
  {
#ifdef BOOST_METAPARSE_USING
#  error BOOST_METAPARSE_USING already defined
#endif
#define BOOST_METAPARSE_USING(z, n, unused) \
    using BOOST_PP_CAT(v1::sequence_apply, n);

    BOOST_PP_REPEAT_FROM_TO(
      1,
      BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
      BOOST_METAPARSE_USING,
      ~
    )

#undef BOOST_METAPARSE_USING
  }
}

#endif


/* sequence_apply.hpp
qUET7ctOZ3B8OTnGTyWobM8I+GH9mNVTOX7sGt5Ukm/NNWqtVWPN2oTbOIeDvA4lMaabeBgCiDPKSSI1kqpghdzM4D3ZO847+pkjfVRNpMHqPZhksPsQqG7PTzCpPi8gapfF2Sa1uw5IIcNnkioNv1cI8CtsKgG/Vwj4wSmFQgDUtuApKbUhdK8SaOepVEodYRiNSe3CTMIg+T5IY6z4oS5jfATQIHUO6RjEEuw1ee1AmNfudbRem9/hL71iXwo=
*/