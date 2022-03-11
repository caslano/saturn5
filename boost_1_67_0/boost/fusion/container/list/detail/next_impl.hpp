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