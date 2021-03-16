/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FRONT_10022005_1618)
#define FUSION_FRONT_10022005_1618

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/front.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct front_impl;

    template <>
    struct front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply : 
            fusion::result_of::value_of<typename fusion::result_of::begin<Sequence>::type> {};
    };
}}

#endif

/* front.hpp
yNyqeYJ5onpi9TWnEt3iqqj15lRs9uaUn+RcTnvNTiRn4dlaiKt/9WmJ/1pXeJS9TJS+akvHeOh8c7nKU1kzs1X2Ol5sHW1zJU62YpNLZ6FuzLRlA7pJamUU5q/Rw5APr+3joeg+siu21KEMchWugVkDqsqy+laVpev0qUU9n9cwXkCX0vtlbOU1jO36ZdRkvCfXqwemV9ZkJw/aXjUwPad6YJaG/dKr3PR5ybPzkzbLWTs6DiVUSBa8nDyngrQ=
*/