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
KC3qBv4B5zHj7kXHeqiWuMetPilzjGgdhU1E9eB7YH5Hz3C6a9IqrI3NDuZL5X6w64DL97QG7Q1vIVW5CztYdntb6rPG0V8Q9PDHJzEc/XG0Z2vjz/FXp3Wkc5zf8RTefR1lRbDdaxzF290sys2CqFJVjV0wMC8ltm/Xz4r2qQqj2ybfu1khG9X1K5wODCuTV/ZqPSm6Kxz3D68eYt2ukTrP6/C7UR2aRCeljqphHvLnOJ0t
*/