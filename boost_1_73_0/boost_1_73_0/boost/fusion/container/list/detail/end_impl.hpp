/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07172005_0828)
#define FUSION_END_IMPL_07172005_0828

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    struct cons_tag;

    template <typename Car, typename Cdr>
    struct cons;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef cons_iterator<
                    typename mpl::if_<is_const<Sequence>, nil_ const, nil_>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence&)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
EILpFIVXgtC+WYkSdcyLqGp4MblgftYsuUMyiErKCgjDOpWZ2AdBUkfFj3f78DMKc3ISSjphEE3AShlcB7ehvizYElhMoRLVA/JiYoPN4XPOTOItpcjGdKiqqcdRmpVOMNIAZ1+Wh3TrWRupKE2t5TDyQ4vKRT5tgTraWQqONsWIKk9J7HF5oila25xME1HSNNlBgdONo/Kbk5QS7RDsN6Zc/IJMfCkn8utw8kwNNGjrD8xtJdArJSYz17Gq7WY=
*/