// Copyright (C) 2005-2010 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Douglas Gregor
//           Andrew Lumsdaine

// One bit per color property map (gray and black are the same, green is not
// supported)

#ifndef BOOST_ONE_BIT_COLOR_MAP_HPP
#define BOOST_ONE_BIT_COLOR_MAP_HPP

#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/detail/mpi_include.hpp>
#include <boost/shared_array.hpp>
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <algorithm>
#include <limits>

namespace boost
{

enum one_bit_color_type
{
    one_bit_white = 0,
    one_bit_not_white = 1
};

template <> struct color_traits< one_bit_color_type >
{
    static one_bit_color_type white() { return one_bit_white; }
    static one_bit_color_type gray() { return one_bit_not_white; }
    static one_bit_color_type black() { return one_bit_not_white; }
};

template < typename IndexMap = identity_property_map > struct one_bit_color_map
{
    BOOST_STATIC_CONSTANT(
        int, bits_per_char = std::numeric_limits< unsigned char >::digits);
    std::size_t n;
    IndexMap index;
    shared_array< unsigned char > data;

    typedef typename property_traits< IndexMap >::key_type key_type;
    typedef one_bit_color_type value_type;
    typedef void reference;
    typedef read_write_property_map_tag category;

    explicit one_bit_color_map(
        std::size_t n, const IndexMap& index = IndexMap())
    : n(n)
    , index(index)
    , data(new unsigned char[(n + bits_per_char - 1) / bits_per_char]())
    {
    }
};

template < typename IndexMap >
inline one_bit_color_type get(const one_bit_color_map< IndexMap >& pm,
    typename property_traits< IndexMap >::key_type key)
{
    BOOST_STATIC_CONSTANT(
        int, bits_per_char = one_bit_color_map< IndexMap >::bits_per_char);
    typename property_traits< IndexMap >::value_type i = get(pm.index, key);
    BOOST_ASSERT((std::size_t)i < pm.n);
    return one_bit_color_type(
        (pm.data.get()[i / bits_per_char] >> (i % bits_per_char)) & 1);
}

template < typename IndexMap >
inline void put(const one_bit_color_map< IndexMap >& pm,
    typename property_traits< IndexMap >::key_type key,
    one_bit_color_type value)
{
    BOOST_STATIC_CONSTANT(
        int, bits_per_char = one_bit_color_map< IndexMap >::bits_per_char);
    typename property_traits< IndexMap >::value_type i = get(pm.index, key);
    BOOST_ASSERT((std::size_t)i < pm.n);
    BOOST_ASSERT(value >= 0 && value < 2);
    std::size_t byte_num = i / bits_per_char;
    std::size_t bit_position = (i % bits_per_char);
    pm.data.get()[byte_num]
        = (unsigned char)((pm.data.get()[byte_num] & ~(1 << bit_position))
            | (value << bit_position));
}

template < typename IndexMap >
inline one_bit_color_map< IndexMap > make_one_bit_color_map(
    std::size_t n, const IndexMap& index_map)
{
    return one_bit_color_map< IndexMap >(n, index_map);
}

} // end namespace boost

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / one_bit_color_map.hpp >)

#endif // BOOST_ONE_BIT_COLOR_MAP_HPP

/* one_bit_color_map.hpp
JmxTQIlKv45Dmv4+z7BW6je6bsWyXnz+6i3i//2Jn5gtrG1wLDthq2QP2euzd+Co9jn0+V1ps0OqhqSwl4dssOQOf4XdMDqeHRgdFRDPny0eoX7bwT4PY9lTlgFsc8gwKYHPjS6ncWxoYDqLkdZI37KVliGmmMBI1oSOrfb5jAax7KylkTXPdkdEC+v70S3Y7bHLcN1D+dr4xtdD4DpLZYZFBjCM9/za2Ia4rBm/WppsFWuznZ+rRH8vTZd1vzeNxSqAo1Kg1JnGUWiHyvKJ16awZqY80xeWCSH3sQRbc/Z1iwz2UOsMdus1GWx2u3TWtgPWWnb8uzRGna8cRNfs6ObsbulVKUtKNbdkD5j7m1oFjGBPBK5hU4Ki2Z1Biax18FL2SvAeabdtBOsYuoa9FxrNpocNZObwO9kT4UOYObLGdLbOQak5H9eP0Bhjn7iOpeDKdwLXgXos1pzYYWjn5KDHerVooM6vnif7fUl9fD8NciUsnvqW/hoeH4RrOFqi/nsK2vxkHLB5gqz7QbPRrLAZv6cR3Gt5yghi+PV9M9lvSsB62H6hdTOXa3YNgPRm66YY9/mBw2W9NwOqkH+wtbMUxfNHkPx1fH7cmFebY/xmvKzTQFxTC6hdrA9cjJWqraSRuLMqNwcG5vF7JFxZSP8FcyAbiH0WGebm/HqaTfkWRwYhx3pzA/aqdYBUFrjEHGJrwQ7al1m0MY77DMnPpUEyhs9tPCVfP2hHU10w1ZVFkRxXb7p+FKCGfcQ4KfYAlRUuzM+aKs7lcSqjLZshx8XYsHi8nR3PDBlazHYOrW864khmnYY3ZQuGl0u/jmjAuo9sweaOfJFNHRXIZo/KZS1Hm1i30TNZ3TGBrN2Ylix3THdmGRvIeuED4aeB0rhWrMu43uz0uEDWfLzJQ51yRJ0WUZ1CxXPkSop/hzXEo3R5pxXmF+VRVqab6643WdatK9Vn34tvrfSj/LFMnrM91wP39Om4PsjzudZlBzFZGxBsxkyaPZTs/Wk9Bt2SnMLSMqbOQ7SIkPP3lt4GzzEkQ98j2ceWQJZnuduSSHO1TXj59sG8/MDlP+IzIPIhgvghmOEYYp1jQSS99/Cp/CJR/s238vLreiv/Zyp/l0/lvy7KX3GElx/lrfxedeTy3nJT/jCX8vOGqOWvvIeXHynKF99MoXcq4l3D+XAaD6zunrE82S2crjfTWToL96le/TLUuXx78G1VNputGZ/MR7vyNp//KjC4vlz2ELaa4tq91nxpQcj7uFdMDstkC8MzWXpkKTsclcni4Ux9RnQm+2NMJguJy2QT6mWy++Mz2Y/1M9nghpnszoRM9kWjTHZt40y2ukkme79pJru+2Xx2U4tMlt8qk/VtncmaXpOJwTaTfZqSyV5MzWRr4Jx9Vvd09nqPRPbeqB0W+fxSVbtmqO9bbovWv29prb5v2bPd7/ctFX219y3IxlbKccQM4zjxrPY/nCq9f7E3uPUA6oBXMI3pFYy79y9HUGfQxN+/3JYkl6O32cVMzWZVJ/232fgGcv0y3djsVdu/yl5pnVp4tFnlUNVmVflubba7wm+bbTPY7GEfbPb6UNVmVRHebLYMuocQFJtVlRtttmeYZrP1Kf7bbG9DxWY3u9isXui/xl5DPdorxaHaa93jbu11X4bf9nrRYK+jPthrsUO117psb/bqCN35CIq91r0kl6Mv65yDf9/KtP5+W3NbSxRkCbEH2T193yokgerD4xJbQHGb2+9dxQHtlB7vNBYfGq61kQ2/+d9G5jcy03qwpS5t5POwK98+1ntsH44RavvYsEy0j6BgWxv55CLQPnY+73f7COzn3D7i+3lvH9tG8PZRf0OKuWE=
*/