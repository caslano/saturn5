/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07172005_0836)
#define FUSION_NEXT_IMPL_07172005_0836

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::cdr_type cdr_type;

                typedef cons_iterator<
                    typename mpl::eval_if<
                        is_const<cons_type>
                      , add_const<cdr_type>
                      , mpl::identity<cdr_type>
                    >::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.cons.cdr);
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
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
*/