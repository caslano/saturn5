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
zQ8p4NqSee7KYxlSMs5YPh8qOd5bkSOpBuoOMX5SbJ8xKmFN5BRcbSF3vruVibNNuRtT9yAenYLEeAp9ZrWBDJeK4L318Z/xh1VnWkf9h0ZxnKaAM5l+BgPbXUefOOSBZ1yX6ulZVvniAIEch6YXPkJl/rMVH5TkOxg9CiqqrAHA3C76Etiv275sisb8/N6jVqvizTJZ6diTk8EwpCDMelE27cyqcLMiqYApsqvqcAaze7BU5zTlNGW1uQ0v+0UAGMOzu7r06LdQqso8bqJYRgl/RHTNyQMI1A8I8FTU0YLaCT4OyYU+jxbz8Mnwdi383cv1TfQ0uvFH1nWp6ITm+sn0LR3XD0mbe12GzKB30QTv4iayV2rSfqJkACTuh/Hu/1qCOs45HUVIxvAJkXWsh7eJDimaN2vNuHcvR/P282sHaIJ0QUhUMJ8p6pZLjxE55OOLlarBGY9vEjtHtje3XXSQrIIocJRtiSaCCQtlxcy71kTKBMcZtBP5kLaMhEXcoXceiLcFKJcFXN7rqe7qtcFnEgRss5C4V2xfKabiZhQWjYf7VQxoYvrbRw==
*/