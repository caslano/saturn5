// Boost.Geometry Index
//
// Pairs intended to be used internally in nodes.
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_PAIRS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_PAIRS_HPP

#include <boost/move/move.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

template <typename First, typename Pointer>
class ptr_pair
{
public:
    typedef First first_type;
    typedef Pointer second_type;
    ptr_pair(First const& f, Pointer s) : first(f), second(s) {}
    //ptr_pair(ptr_pair const& p) : first(p.first), second(p.second) {}
    //ptr_pair & operator=(ptr_pair const& p) { first = p.first; second = p.second; return *this; }

    first_type first;
    second_type second;
};

template <typename First, typename Pointer> inline
ptr_pair<First, Pointer>
make_ptr_pair(First const& f, Pointer s)
{
    return ptr_pair<First, Pointer>(f, s);
}

// TODO: It this will be used, rename it to unique_ptr_pair and possibly use unique_ptr.

template <typename First, typename Pointer>
class exclusive_ptr_pair
{
    BOOST_MOVABLE_BUT_NOT_COPYABLE(exclusive_ptr_pair)
public:
    typedef First first_type;
    typedef Pointer second_type;
    exclusive_ptr_pair(First const& f, Pointer s) : first(f), second(s) {}

    // INFO - members aren't really moved!
    exclusive_ptr_pair(BOOST_RV_REF(exclusive_ptr_pair) p) : first(p.first), second(p.second) { p.second = 0; }
    exclusive_ptr_pair & operator=(BOOST_RV_REF(exclusive_ptr_pair) p) { first = p.first; second = p.second; p.second = 0; return *this; }

    first_type first;
    second_type second;
};

template <typename First, typename Pointer> inline
exclusive_ptr_pair<First, Pointer>
make_exclusive_ptr_pair(First const& f, Pointer s)
{
    return exclusive_ptr_pair<First, Pointer>(f, s);
}

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_PAIRS_HPP

/* pairs.hpp
3vTyQinby8jw0EnTIgs5pZMLZuYUTdA48GduEOpfVpBvK7qs6KoC1c/OdJnXk46mkVdcRLMw+psOm1wodVhUZic/Iadgaj6RlU02/i3C/PFT/2bq3ybCn0yKAF5GpkOYjJTRyKRYsSIzaNS47DHn5Jxz9qAhckbE+ymVZ0QcidHnLH5aqXIfZcsu5JmM7qU6LHvokFE5EwrK8qcV6ZpoWVe5xPkWRpuWWVepYRtYabpXU7HYZ/szeWPxsC/G7CXPN4TTJ2q4ESZcfbN2t0js1/i7UcJHfX7XtbuFJlyahCvGPlHs8/y9+f9JX+g+tldIRlOQOw+5gyL3va+Rr16IDNWgMucic0BkfvB97z0dt+D3GHnFl0l1IKfrhd8TufFWS90rMB3bjCLdf9rEnUdwwuh3ekclzGFfiq9BRNw0FX5lIFcHbhG5U/3nec7n+foInnW+Tpz44XruZNsvNiK8lEH0UQ++5ujHv8zbm/UaswiLOy7vSNjIcsllIjJpuLwgYZ8LKYPkzewF/Fsp4zjfeG+XEBkuR/6665rzdJHZRU3UsBIwdajP+rAZJewPz8RkY8ZhDnkbmDNI+yXz3pa2Okm/ocvFLfr+WomAZzvFpBVib6H2FPbf+sTOB05nnc1+t+r2bqVbZtDtVePWuVfQbXulW8+g2zOVbj2Cblsq3boH3TZVunWT6wS3g8atq3zXUIH7EufbKHM9peC+EHKt4M61om5Lw9cXEz5R9D5D+rSJJdOm5OEdfqbFdt2/vzEmuO/U32i4SVMjr/OJRXyq6ro3P9e2ytcR/zbiXxr6TZP6N672fiNmn3516wnbiJvGyzrpNhIn41F6+F7+T8bq2kuNuBvmc2SyqpTpsoJyp2uUzcXiK/suLVcwTKacU7ETXS0k7o9T7PXtVkL/hGb2x8QBu8xfpNvhZEAxZT5bwrYJ/Y7P7A+cLX4t0Rg94om//3fasn57oe0hbC/z+XHmm1azzelX9rjoWubxReVlruVFXr9lNd9zc+078louI3PCswsi85uGPcl8+2zilXIM1HJsjdd1ABpRltbdRtdy6BgrtedaHg3nM+cRbBZ7Ar2vz+wl8ZjK2N9TLkSPi+O1jn0J1K+3ZkIbUNNvValnTWO7hG+rdhNf+PebWu8viV9T+jkP8rgZee8vbgNB3T2W4N7uk0pcdKf3UtF1p+G07W9DJ/MTqt/2G5VEb/tNSn7dtj84Ue/lNYAPc5A85bqWO2p5Vd5/0u06tO/pWdO9Dkpd8zJ5RnT9axjV/9BEylez+vqfcxz9V/zK+t+mZU7RAMmYQ+Rpq2uZ5Zs9t/KqfMq/pf/cWo5gfx3Pumle9rrmRfcjcNe/hmlqvtn/MOXE+2XZecuMoqcDmrd4DRCnbSOzNDJvRWU5eQV5E9zzpfLxv0hPZ2hedmrI+4kvFa6Fh+0xMiQv54zMzsmbMCF0dqlTLyvknrsIm9kHR8Onm3vMsWK/0bOPtNM9zj3+oBTnW/mQb0UJF/499fliX+H5O/839nicuYE0MDs3ld/83oscvp4beIu/lRpP4Vo5hJ4P1UbfyCfGVvw+WH8+3Q85KFMHHXwpMnNrBWUSVKY79kTsX+F/ENMv2eEhzMok5/cqZYidOhktc+Q56QSOqTJHNnuvvCH5nsu1kl/t80+cezv0rW5DIbrETXQZ1tZyk6ueMfV9Ou7TwuuXqyBTL0nRcRnhPKpj0y9OO7nzo4iDPEkcYW3ukOapg16brTH/sPvGqnlyaXNlUrcTiGMn5pBdb6k1zbX5DXbpx6pxzlrw3rciRccLFfBifrTvNVzyg9aj6Uflfb9YP+YsvVRHuJnqpyHmJ7sfdcmPVpnk6Wh6lTw=
*/