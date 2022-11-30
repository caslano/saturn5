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
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
*/