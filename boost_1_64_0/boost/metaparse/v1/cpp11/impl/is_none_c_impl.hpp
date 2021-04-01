#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_IMPL_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char D, char... Cs>
        struct is_none_c_impl;

        template <char D>
        struct is_none_c_impl<D> : boost::mpl::bool_<true> {};

        template <char D, char... Cs>
        struct is_none_c_impl<D, D, Cs...> : boost::mpl::bool_<false> {};

        template <char D, char C, char... Cs>
        struct is_none_c_impl<D, C, Cs...> : is_none_c_impl<D, Cs...> {};
      }
    }
  }
}

#endif


/* is_none_c_impl.hpp
hw2CyOsvgcUCy/77db9Ht4/okkpTxuxQy97J9713kSRzngoc4RvpAxLYchxkLrf+klfiSKdQPMEcR3aG3mqOvxdzd+vAUNJowvz7Yql+AlHEYfYwWMJQrDjSX/6PdgFRx7RSx0fixjRaYLPTcDCKy0miz7IP2JAU3w626QY2g0Unt2hSIt0hDVj5RuyMCXqya2wCRhjv998ORvh5VlK59qxvIf0ttGvaZc5Q0Q+rmk+K+zdokXViIDbCHe28paHELyRw7VjTYMg2hDf8M69nC9iHah6nduicuYl4lS0UqQC0tq7169sqa3VimjtbHKOF/6qXZYEe41RnSg3NsfncOcn3Nkz2LSL1T3JYsZBSlcTGfyUmRxOo6rxIvREg+uXmGtugKeOk/LWpJANx2BnFV5s/ZRw57U04sIl9nbE/S07pUKTTZ0nCVJwh/zAVwLiKLig6AhTG7/qeCCAVHlkfp8gZeSE3dXHjHZLG5nRYHfiz9H4L2fLJ0mtOIHg6r0ZeHiFSiV646eAT2p4GIX3rBmsy1ZKd+WILS3P58ZHtoy7IVgRImgB512J4dA==
*/