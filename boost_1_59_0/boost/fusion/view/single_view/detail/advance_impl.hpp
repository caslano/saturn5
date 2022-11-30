/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_ADVANCE_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_ADVANCE_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/plus.hpp>

namespace boost { namespace fusion 
{
    struct single_view_iterator_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<single_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef single_view_iterator<
                    typename Iterator::single_view_type,
                    typename mpl::plus<typename Iterator::position, Dist>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.view);
                }
            };
        };
    }

}}

#endif

/* advance_impl.hpp
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
*/