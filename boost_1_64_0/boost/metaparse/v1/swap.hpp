#ifndef BOOST_METAPARSE_V1_SWAP_HPP
#define BOOST_METAPARSE_V1_SWAP_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class F>
      struct swap
      {
        typedef swap type;

        template <class A, class B>
        struct apply : F::template apply<B, A> {};
      };
    }
  }
}

#endif



/* swap.hpp
y1QbMLDMcXmT1GMREuqmK5OeP2uoPtZi2b5UNiwYnDAEwYixmMKExHFfc+ZM+PgEBJgwt8I0tyv5iT+/MxFzBwkFBeWv1AdhX7mAlFobhaWTbfT039yFNYD/X03BB7bJgk0A5ZglKdiyPB3gc7O2Rd5rvI0rFOdsOf40llt5jnakAp4EpLIKu+mUfcIehGk7KCCwat7vrZPtFFHGt0RU04oMbXOm/7NYx4m9uK8kqR2Qa6hA2mknKaDP9A2z2WVQ1oyeUQaM83fjSELdcXFzj1XrFrXGsTa+QmmVo3irlNipKJJAiuZFUVSi81NbUufMls4qTwOD0bDsLzhJ0tL8HGRXRI8IZuU+rCRWHQEG+xCe/0tXVbliRvPbWAz5xduyXSLnUFOCvMM/DG+APAzGmf1cH9nQFD5I79vtc1rhwlOxsumR3r/MSiGp38ng2cEOx3QmFJVEeFM6Kuv606yLOQQL6Y2tsOpEwh8Ib0uK2t0mt45pDUgbNmxmyPrI/seWBGSQ8lMQTuIUl+0BEjTnYHdDeqqBEjI6HkcUI5eUO+vYhJNpZWaRbTgwbg==
*/