/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_NEXT_IMPL_05052005_0331)
#define BOOST_FUSION_SINGLE_VIEW_NEXT_IMPL_05052005_0331

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/next.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef single_view_iterator<
                    typename Iterator::single_view_type,
                    typename mpl::next<typename Iterator::position>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    // Workaround for ICE on GCC 4.0.0.
                    // see https://svn.boost.org/trac/boost/ticket/5808
                    typedef typename type::position position;
                    BOOST_STATIC_ASSERT((position::value < 2));
                    return type(i.view);
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
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
*/