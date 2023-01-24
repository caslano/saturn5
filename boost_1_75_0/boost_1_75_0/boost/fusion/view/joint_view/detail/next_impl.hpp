/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07162005_0136)
#define FUSION_NEXT_IMPL_07162005_0136

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    template <typename Category, typename First, typename Last, typename Concat>
    struct joint_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<joint_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::last_type last_type;
                typedef typename Iterator::concat_type concat_type;
                typedef typename Iterator::category category;
                typedef typename result_of::next<first_type>::type next_type;
                typedef result_of::equal_to<next_type, last_type> equal_to;

                typedef typename
                    mpl::if_<
                        equal_to
                      , concat_type
                      , joint_view_iterator<category, next_type, last_type, concat_type>
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i, mpl::true_)
                {
                    return i.concat;
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i, mpl::false_)
                {
                    return type(fusion::next(i.first), i.concat);
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return call(i, equal_to());
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
/TvDWjVGWmGbvP/6oHlkSPutH+Az/+i876ve+U0ha+UtJZ7X/P0WtrBPQ3QykdAd8c6LUsCqD199LGg4/ygkqeZ4bh3xPaIT4HhLGJqBN/+Kzl+g4zOaky/IkSHtZUGk1Lirye+4qwFLp0HfIzw2BPwJLPI4kUT2EvWz2FZTzlZh18oY9iyPSX6PuRWrcYrWYXy+KkwPqRcZz89QXrmI8GIZAo9jxT/RTFj8PThsz+slWJ4sPtNVBsAed3gsPARdqGYemY3op6MaA8uXZubbWL90rrhWtsB/qaKHsXMPID3IYHROUJmDj17HNFCMXFVUG9oSbaFIoRQrxaVQ3KG4F22RQHENbgFSikMgQJFSvHix4l7cSXC4uLtLcAjBIci77/v9vM9z1jprnZmPmdmz9t7e2VXUzMlFkftmAkSSqTZiCbrTp2SCtPyPwumyU5J0TZPTkewEVffCko9yP01V7otvqgUr9H4jfkbWdhxmco+8WZLRdk6gUj6l9aeqSf3n3W5F284wlG4Iee99vK80nUp6JKZfzMt8Xtez+2YEwrKp3IQKfRVcZOCZ7es0QTB3BRE42WdpBiWviuea7zE16uZC4e3F5UkPWFsvvJ9M1ayKWdItmaDXPx0M6Bprq6Gm7+MvUDGv5ChVF4OusMNfgi3Ev7eOc00NSD2GjhEadK7ch12jbIsyhr+HYhoSaoDpT50ZayOs62SVfcxj
*/