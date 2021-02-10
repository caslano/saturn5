#ifndef BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_HPP
#define BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/iterate_impl_unchecked.hpp>
#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class P, class Accum>
        struct iterate_impl
        {
          typedef iterate_impl type;
          
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<typename P::template apply<S, Pos> >::type,
              typename P::template apply<S, Pos>,
              iterate_impl_unchecked<N, P, Accum, S, Pos>
            >
          {};
        };
        
        template <class P, class Accum>
        struct iterate_impl<0, P, Accum> : return_<Accum> {};
      }
    }
  }
}

#endif


/* iterate_impl.hpp
Q+lK8ClspfcWziamwtTaCGewD8EUjC2oTUwdQZzr3S5TBejaQca+0gH1673t05dQudwX6HfyEee92WKdzpdRzwkvF6uUh/ePD05d6g2njaWQ2JWmEJDKiZ6EyIVth5OwGhsJvfVqMp2vuBQfLmiuNCUljDV3tWzZHA0xXO0julMsbWDv2IjyCO3gs9JiA7bCdmpQZQY+EBX4ptLWZ/GhxTobjbY61zJhLrbO/vmaeGxGYhH8c0qP/abgg+cNidOY943kvfeX1Xq+ePPYc55jTeVbfutGTI4vEixu8wCX9dj/KyJK9Xwd2tIZPryCd9M6of+729wZHzrj/BIw//6lvwBQSwMECgAAAAgALWdKUqGtg3YkAgAApgQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzY2VVQFAAG2SCRg3VTbjpswEH23xD+MWOVlFda5NdKyBGmVrDartpsoofvOwhBQiI2wScvfd2xyU9sv6IvB4+NzZs4MBBqVTmKFIQsKkUl67LH9KetUhWwZRWu7wOtLxAJ+PQl4B2Z3LKixKlsKpbGOQcgkx2Q/c1tUbsfAhw9DGA0GsPrqsEWs0YeowT4MHuFdHulkOIDhxJ88+oR5/R45bIv1EWsfTG6eshuexXt0
*/