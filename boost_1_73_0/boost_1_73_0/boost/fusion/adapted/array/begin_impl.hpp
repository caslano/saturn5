/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_BEGIN_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct begin_impl;

    template <>
    struct begin_impl<po_array_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    po_array_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
2VWsc82SkZkNzniYNLIhrlslM4BcmM4GkFA6G0DGpLMBJGR2R66RxlCjK2CaYJcKVi/YMsFuFOwXgsFuyFjQsdhjeMFYhWrb/7jmVQok+lIIMQtCzRu/U1q+ZFsAr6GEEeRMu5yORMn+T6BNQ5D8Ks3lUUmi5MhtOo82Sw55jiVKpGLNBXXfV6dgVOCgljDNsmg4R3lFQ2xo4xUNoYrimRDnjw62aKwx6QiXFfMvb9WAWagSoyS6BwYcQy7lgaE=
*/