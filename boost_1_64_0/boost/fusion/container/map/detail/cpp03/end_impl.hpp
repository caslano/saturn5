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
qkFfQ7BiWOjz//1kf1No/7Ac+VWwzAR+16L/jjbzDR+PrDn4xQDiEhID6ylx+cPExzgK8VKubarud8ybVkQ8zxcoyiuVNZDs12oIr+FVqK/VkHd0gBWZygzrnW2Rqu8/sLyirCAg+3PhOihm/+hywpxe2T8e+rvp+/etmDKapZiCceGdSoP+0OLB6reGAuuKJfyyN+wP9e/jB4+frH1Crthb6o9ljS+r71ntbfr+/z7yfvse8v5GS5n5/Y3wWaT7Yls/KiOsM0B5dd2YSRLbP1j0jkS21uK6PoNeURnr+n4Z6rpsso6Y5EvIt+7Gy7g4GjkBff6gPhkVa2ZMZFuc+zRl7ay8o7yV+gJ7Sh/dIzafKjZPQx7S8h+CNkvnhL5AH/84SJN1Rx7Q47bBaozrP9WzX9YKlLUSlbXw1PUwJU6/rcSmBsl372rKFVs9Xj6QVX5y/LYadb0kurzSL/nIrehqMekqmYK2JPrlZr39wWri7Zfw2mwSkz9fbJ2FLKG822+0VUleiGmst68nxqUSGn82OSy5NvkY4+1yWGRsLtDrKgmvCZYNm3tJ/fK91KJgO1xX91PHw3JZt+8ZGQ+PI6XafTh4fIAulYGrLzoZc5uVvueZoPX7PfozgbUU+aEf+8rQs0zfZ9TQfvwK/Xf+8kr5Jtpz9EEz9l7MzxufiH0wdH1e2Uu9Nmij0s6G7i71e3zSTldFuJ0yEBNvp9amO7bkXTjdbqnN1KaXDH0Q2vecqZ0raGMd9k7g5/5B+8LnenlvTV+Zx9hGxrDyzcHH5F79EOLTnsWGNhqf1rGsL6jZ04gt2dR9OT+/WaH2+7GDI/pdWdevTmwaIjZlhZ5bldY2he48sX7zL3R+s3pYth0NRj2iJMZ2N2B7Ro9gu/sHYmv33mLPrB7W7XZVKfaojY6zzcNkrb1cuWcditzJvcZt1FEYVBLL3x+hnLjl1EHbAtWGNa8y9PtPeVXAMPa7mO47o+BWsl5qqen++p3Y+qDYei9yO3qaTbZqV4aWHhjLt5BlDeAIe8eHbaMi2Zffbu+0kL3F4eeB11co98lXqqzvk9Wyjt/Osm7C9kiNZv+0dvv1v3ZZN66gNPa+Psy6r+UaV21Y3bN9TPWWMXUK5dvMNmidGMNYirRB1Vcja/bthaRLXsBpHJtzkklflZ/nUezfzrZqczf93FBNgYyv8FjSP0Kt/M3dXdbP+1KurU+Qlf2xV7WLiUds1/lZVNKFOh/l50tPUu+3Ewbb32+LU6yv8eZqsx2x/z1l+E6lTY6YXW6dXe6bXe6VXY6bXe5Y/Llg1jlxdjl3djmGdjl0drl4drlydrlm8b9nHW8OnXVOXPy5kHyHm/0PvTD+s2tK+6/+c37TyDe2upWEnV/0/c3vH5u5IP/aHmdv+NQ6aT9cfaddbqZdTqVdzp19ruWrf7F3JuBVVFccDwoSFTG4ALIGiGGHsC8iBAl7gBiCRECTkBcSICSP5AXCalQQVNCo0FJFiYqWKv2a1g0VbahoEZdSa1usWHFHRaUtWtuq7W/m/d/LzHvzsoG2/Zz7efzxJjP3nHvnznbPmTPnm/3/3qOdEveM+XP71PFp1zb5RadIsZZ1iNEznv01J0CxxcyVEcrQCV4NJ8BrINsR66ZnbRirGC66gz70l1nB7+ZB5Q1rCa+GbeE1wfxRepaGoxzyR92i0+GtsBW8DXaEm2AnuBn2hLfDQfAOOBxuDeZl0jMznOiQl2mt6r9O9a9T/ethF3g97AdvgBfBG+EouBEmwZss+ea80kObKPa8WqNP9dubBHvCsXAcHAenwfFwOpwA/wq9yGHVt0J2nwk9gViwRv76OsLusBMcBOPgCHghnAw=
*/