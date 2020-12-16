// Boost.Geometry Index
//
// R-tree subtree scoped destroyer
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_SUBTREE_DESTROYED_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_SUBTREE_DESTROYED_HPP

#include <boost/geometry/index/detail/rtree/visitors/destroy.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

template <typename MembersHolder>
class subtree_destroyer
{
    typedef typename MembersHolder::node node;

    typedef typename MembersHolder::allocators_type allocators_type;
    typedef typename MembersHolder::node_pointer pointer;

    subtree_destroyer(subtree_destroyer const&);
    subtree_destroyer & operator=(subtree_destroyer const&);

public:
    subtree_destroyer(pointer ptr, allocators_type & allocators)
        : m_ptr(ptr)
        , m_allocators(allocators)
    {}

    ~subtree_destroyer()
    {
        reset();
    }

    void reset(pointer ptr = 0)
    {
        if ( m_ptr && m_ptr != ptr )
        {
            detail::rtree::visitors::destroy<MembersHolder>::apply(m_ptr, m_allocators);
        }
        m_ptr = ptr;
    }

    void release()
    {
        m_ptr = 0;
    }

    pointer get() const
    {
        return m_ptr;
    }

    node & operator*() const
    {
        return *m_ptr;
    }

    pointer operator->() const
    {
        return m_ptr;
    }

private:
    pointer m_ptr;
    allocators_type & m_allocators;
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_SUBTREE_DESTROYED_HPP

/* subtree_destroyer.hpp
vTWskD5T5/8qtw+5JFsuPiusPVV3z7bIa6JWWJuaGnYPuVE3Vx7rc54jjoRt7ev3Kq0fs8iMeVDxzBz7wZG0U7PfnXoXTdBzWjQsMc5idxZ7H9CsMHmztsi8a+k0y5ZPlvCpIeHXWvd4HTc0YMtgb2QVSJxDq8Sp63o0zoEiP1DXUAXjPMvsS2rCmvVITtgiI9ta8jMF+wKxd/Cd4gtEliMvGK4EuZ9EbpXX7IeqZeGfpJuLPcW0VXt7+/LiMg0/FflvRXa5CZ8ZEb4Qe1po+iX2Izwm/eWFpk1+KPKbTRw9I+IotULfeUltSthJyM4VuR6+YNisiLAznPQ1bDBpWfxg1lP9XeTvNOkPjYijQnVQOYfOIUu4Bc+TFdm6Pj+rqYJxZFfGIc9fFhr7JGRC588al/YR9yJDCN+PXo+Ja2xEfpZi1zk6fzpH1/7AJ21ondexB9ugL0RenwHonH2DxJvoM/7BOb2utXtI/OPQrznfqMB+c1ugeS5GZr7IdPI18YWmU5zHo3Dz3nuLyPzkta/jplxjwXdx79nu2M+3hnl7B8+gljy/7WnPm7O+mCWY2zGfYb7DjPT4rUsxSzGbMM9hgjp+SeL7yluZj6kFM8or1/c96uiRq8Jn5nHoUOqgWXD9hKSf5P0DfXWcpzv7WfSwbuWp93ZPFytDZEKv7bf4njzVM8h7Gk/DOfuaC+gYL9li7Gdlc0clDOEMnhacwtNGTAv23Uzw231iULZFx6DspoRhJ5DNRjZgy86rGRHvYDb1rBFjy7ZT2QojWxoZr0h7Eyr75vRqPMdz9pc1/abzvM64m/5Rn+8Zd+3jHPexxl37L40/NzyevKB7oen/K/udDNxLjXx4f5KC3wwTRvoJka8wbmHXv6Sx0DxfMte1uC817nqNRszBJ+he6O9ikjHPYtojv3RO5BjEoQzFBfnlwcXI2pdkOu978pw3RuaeQcNn6btqVmiK/VbG1DirkenHmN7klEzMuWxayfRSE7HeRwTjaGb6yIex616s2HG4xumHEng7bPrm8DXNOgYF4yolLPaQsDWs4S5hpbJ1TAoPWxQSlivYLaw0iNBxiPCmz2Nccc1rXkiYzIgwPU0/aZ59Gln8jGzEeM+fvVpb8mPekd0tsn+KkJH0zb3TBpF5BBnTN9MEcuwO2tyvbhGZwWrnjZ7opH6VeKkDM8Y+JGG2RMiornUMWy8yD5q2Rdp5knJI23pXZOJc21aGiTsveDKek4mQewy/5HWkW326hpcMhqwJryHyw93bkkt4lCthJyNaW2QHEhZ7SNjauLmFpfJM+08Q2TPc2v8J5w3BdZOZzjtJc702wz3d9Cvu12MGMk1MXxV2fYlfmyp+ojLxy6zqR5GcOHu6xImqzDtV2p72Z+F91r4eOpPjfrmHsqP9TO2aKH2WWuUsGfNOGzGzEsm0LY1jiDkL+lOx7/YG3y08Mw87/zIi+zCThOm/NK7eYi+2263YP/E6/iau4/ZddoH7Vsi9jWl/xBvWlyWJ/0ZvnPUHr95XRe/TNM6hEqaeXhPhcRa5xLnKNc7wviVOwmwO6/uI1/RNa4/T99XS+/2fRP7ekL4wPI712r/pe50SbcfmvvOvInvQ2zskHz0j4tgY9T5Y770j5B/D7n6vq/fZEfJbzb06f8E8Oo/yTF/4msh/7g2b22q72St6HO0J9okHRPaI2eN/8jyz5z/+fI0i9n5mnR9pmvfgDSSuVY7d1Guimds+oc9KsqP2HXrvYdY4hF83jfTeQ/uP8GtBwy49Tt+x6jh9x9rj9B3r3fsO6ec2mr7DtA9xfyzKPdLWyHsk/TYgpUL3OKofvr58vR6oqLB66BrMpddG9j+yCo0=
*/