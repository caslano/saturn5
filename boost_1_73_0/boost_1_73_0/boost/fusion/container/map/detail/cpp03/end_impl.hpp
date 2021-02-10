/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<map_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    map_iterator_tag
                  , typename Seq::category
                  , Seq
                  , Seq::size::value
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

/* end_impl.hpp
BcyLYik+DQbhKk/Q+0GUhWIQbpZ/Oi8WLyuZoROL4BmyZQFFBivB+iA5+7DIIh7LOwYEicvVfcLFvL/1Bk2l0SDLQbAkkbpQjjNRuc3AW4enL9lgiR7zQt5Elgpp6sc8W+wwYhyllniVp2gI44BMUYZh7sMKt1ZeMpcr35hYx7QMcGdqtv5GkKXoDPSIB6bXg/tAcNGHO9O/tqc+3BHXJZY/A3sIxJpJZTempWPqORrLgT0tcybQeA58sUw4i9Y2f901OMDdD7//zwtQz6C5U65lFsI8iGUcwiyN+UNVmDGuhyz4Q2B7DZFKza/w5uCQx7I50qrNYaNBxSR9fjEcJ8Fjtsor3k2TJLcGJa5DqGkZPr2G811IG9ue4dnaDYIamRjjJoPhupbdlhsZmG/Pv5oRXXebYGlKDfj+zDG8tj7T1vzxPj9aDHRo2taVaTcZx+bV1xbNtkby06RPyHhsa21vJsbEdmdtOq5Lv1KSyyWblhKj5rBNtx3D8jx8c7kzx1cEeINj/LtBx5h0g65HukH56QS/vDv72EYddMVupdS509us2AJ0aox0Jd3ziT/1mpBnjA3Nb1P9vyZO24A3wkJSkM2RRVqlU1GV3JT49sTUaNtwWWktqu9qxDO0iaNA9KmKOvTNiaGgm2ol
*/