// Copyright (C) 2005-2006 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Douglas Gregor
//           Andrew Lumsdaine

// Two bit per color property map

#ifndef BOOST_TWO_BIT_COLOR_MAP_HPP
#define BOOST_TWO_BIT_COLOR_MAP_HPP

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

enum two_bit_color_type
{
    two_bit_white = 0,
    two_bit_gray = 1,
    two_bit_green = 2,
    two_bit_black = 3
};

template <> struct color_traits< two_bit_color_type >
{
    static two_bit_color_type white() { return two_bit_white; }
    static two_bit_color_type gray() { return two_bit_gray; }
    static two_bit_color_type green() { return two_bit_green; }
    static two_bit_color_type black() { return two_bit_black; }
};

template < typename IndexMap = identity_property_map > struct two_bit_color_map
{
    std::size_t n;
    IndexMap index;
    shared_array< unsigned char > data;

    BOOST_STATIC_CONSTANT(
        int, bits_per_char = std::numeric_limits< unsigned char >::digits);
    BOOST_STATIC_CONSTANT(int, elements_per_char = bits_per_char / 2);
    typedef typename property_traits< IndexMap >::key_type key_type;
    typedef two_bit_color_type value_type;
    typedef void reference;
    typedef read_write_property_map_tag category;

    explicit two_bit_color_map(
        std::size_t n, const IndexMap& index = IndexMap())
    : n(n)
    , index(index)
    , data(new unsigned char[(n + elements_per_char - 1) / elements_per_char]())
    {
    }
};

template < typename IndexMap >
inline two_bit_color_type get(const two_bit_color_map< IndexMap >& pm,
    typename property_traits< IndexMap >::key_type key)
{
    BOOST_STATIC_CONSTANT(int,
        elements_per_char = two_bit_color_map< IndexMap >::elements_per_char);
    typename property_traits< IndexMap >::value_type i = get(pm.index, key);
    BOOST_ASSERT((std::size_t)i < pm.n);
    std::size_t byte_num = i / elements_per_char;
    std::size_t bit_position = ((i % elements_per_char) * 2);
    return two_bit_color_type((pm.data.get()[byte_num] >> bit_position) & 3);
}

template < typename IndexMap >
inline void put(const two_bit_color_map< IndexMap >& pm,
    typename property_traits< IndexMap >::key_type key,
    two_bit_color_type value)
{
    BOOST_STATIC_CONSTANT(int,
        elements_per_char = two_bit_color_map< IndexMap >::elements_per_char);
    typename property_traits< IndexMap >::value_type i = get(pm.index, key);
    BOOST_ASSERT((std::size_t)i < pm.n);
    BOOST_ASSERT(value >= 0 && value < 4);
    std::size_t byte_num = i / elements_per_char;
    std::size_t bit_position = ((i % elements_per_char) * 2);
    pm.data.get()[byte_num]
        = (unsigned char)((pm.data.get()[byte_num] & ~(3 << bit_position))
            | (value << bit_position));
}

template < typename IndexMap >
inline two_bit_color_map< IndexMap > make_two_bit_color_map(
    std::size_t n, const IndexMap& index_map)
{
    return two_bit_color_map< IndexMap >(n, index_map);
}

} // end namespace boost

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / two_bit_color_map.hpp >)

#endif // BOOST_TWO_BIT_COLOR_MAP_HPP

/* two_bit_color_map.hpp
xgK8iifwF/wSf8Wf8Tpew1JuWt7v6Il3sDS6erLdoieWwWAsi6Hoi5HohzUxGFtjeeyAITgAQ3EYhuE0jMQ5WBXfxOqYjzVwGdbCFVgb12JdfB/r4U5sgPvwISzARngMo/EkPoKnsSWew1Z4Gx/Du9gR3b3Y/rA0dkE/7IrB2B0jsAdWx15YD2OwIfbB5tgXH8XHsQs+gT1xAGbhQJys0jMwDmdjIi7EJFyGw3E9JuP7Kr0TU7EAR+LHmIGnMBNv4Bi8iWPxLxyPf+ME5NxGy0VvfAbLYx6G4bNYDadgPZyKDfF5fBhfwDY4DTviS9gTp+PjOAMH4UxMxFdwJM7CLHwNJ+AczMM38Dl8E2fifHwD38JFuACX4SJche/gZlyMO3AJ7sOl+DEux2O4Er/A1fgNrsPLuAF/xS34N76Pbt5s9+iLH2AQ7sQquAtr4IfYCPdgM/wIW+E+bIcHsBcexH5YgIPwMMbjJ5iOR3A0fopP4TF8Fj/DF/EEzsSTOB8/x7fxS1yOp3A1/oDv44+4Ey9gAV7Eo/gnfoV/4Rn8Gy+h5k49oAv+iq7o50M2BqErhqt0HfTAplgKu6EX9kA3jMNn9P0PliU9H31xAfrjCgzAVRiEWzEYt2EF3I8V8SCG4tcYhmcxHH/EyvgzVsHbWBs9uTCvib5YG4OwLtbAelgXG2AbdGW++6M7DkT9uPIU3sXZqJE/Bx34Jt4gfzH+hqvxFp7F23gF/8Draji+ZVk/MAx3Y1X8EGthAMOri4EYhZuwGW7GlvgNPoansT2ewW54FmPwHA7G7zABf8YMvIxj8CpOwF/wWbyGS/E3XIm/41bUzxf243Q8jK/gaZyF5/B1vIFz8TYOpr9S5TgfQh98h/wKuBjDcAlWwUZ6fWNjjMZW2BoX0b0nvo2DsSn5CdgMk7EFpmNLnIiP4mTV/2xsg+9iW1yH7XAftsfD2AHPYEf8ETvhDeyCt7EnuviyX8YK2BsrYx+Mxr7YAvthL+yPffFxTMABOByH4Bgcis9hPL6Eifg6JuEKTMa1mIpbMA0LcAQexVF4HrPwNo7Bu5iNfn7snzEYx2MlnIgP4yTsjrnYG5/BWMzDFHwW03EK5uNzuBKn4zqcgYfwZTyCr+EpnINu/uxvMRDfwkhcgDVxIbbARdgR38Zu+A72w8WYiktwEi7FF3AZvoLLcQ6uwhW4Do/ieizETfgTbsbL+B66BLAfRh/chuG4HeviB9gOd2Bv3Il9cRem4R58EQ/ifDyEb+MRXI5HcQMew514HD/Bz/Ac/gOv4Em8jqfQJ5DzLayF32IbPIP98CzGYyEm43kcid9jHv6IU/EnfAMv4ny8hGvwCr6HV/FD/BW/xhtYMYj7HhiBt7A6/okN8Q62xr+wL97FOPwbU1DzYH1AFxyLpfBp9MQX0AvnY2lciWVxC/riXvTDAgzAo1gBv8KKeA7D8GeshI5g9stYBqtgZayK1bAaNsPq2BJrYR+sjclYB0dgPXwGH8J8jMJPMBrPqfxfsQX+jo+gR3nO07AydsBG2BFbYG98DPtjb3wCJ+JgnIZD8T1MwD04DA9hIn6HSXgLU9CzAtszhmAa1scR2AgzsDlmYj8chYmYhaNxNE7DMTgXx+MSzMH1OAF34VP4EU7Gj/FZPIdT8Z/4HN7C57FsRc67MASnYWV8CR/C6dgCZ+BjOBt74qs4Bt/AafgmzsT5+A4uwOW4EHfiIizEpXgRl+EtXI4eIZxPoTeuxkBcgw1wHTbGDdgWN+Jg3IwJuAVTcSuOw934FnqX4rwOQ3AP7iP/FB7Ab/Eg/oYfo2co2y1Ww8+wKX6BPfAMxuNZTMNCHIXf4Vj8AWfhT/gqXsA=
*/