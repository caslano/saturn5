//
//! Copyright (c) 2011
//! Brandon Kohn
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NUMERIC_CAST_TRAITS_HPP
#define BOOST_NUMERIC_CAST_TRAITS_HPP

#include <boost/numeric/conversion/converter_policies.hpp>

namespace boost { namespace numeric {

    template <typename Target, typename Source, typename EnableIf = void>
    struct numeric_cast_traits
    {
        typedef def_overflow_handler    overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<Source>           rounding_policy;
    };

}}//namespace boost::numeric;

#if !defined( BOOST_NUMERIC_CONVERSION_RELAX_BUILT_IN_CAST_TRAITS )
#include <boost/cstdint.hpp>
#include <boost/numeric/conversion/detail/numeric_cast_traits.hpp>
#endif//!defined BOOST_NUMERIC_CONVERSION_RELAX_BUILT_IN_CAST_TRAITS

#endif//BOOST_NUMERIC_CAST_TRAITS_HPP

/* numeric_cast_traits.hpp
UC/Sn+5jT1Ph6fPhpz3YUzQP48MceLg4TofViAGYKY0A+Mst+huHKwkBPXIia3TFdky52OTG96dkwfvXhjt/t5JQmoHHZxL0ogbPsPsOAH8PgeWmOJKhfvqHnkdC8sibEcF3s+aL/iAEb9yoI/jvi4m+XN8x18KVofAOK/AiG/8NuRcwQ7kezbvKEm0cpMoGdsqt8KuBEj+Llb/RBcgkv3PJSKLoRiqXvj1iG/uGZCW0Z+FhNJF+XfCPa+IFFjxacQbVLXOtTnFtHUOVZ28USOZOC42hw7SvCExbsQrE4yIHI+pp6k08n/VyHIO8xWuqpoRbpI7brhoXG4gr+u0SI1+ih/vScQ1L5CkeR2QeeNLbe7Mpoo19oZfw8cHdRkHdgmzh1YzKadankObCx+/GHJ272zBZWJFTsRuccn6bK7MBx5zBBnX7eP6RDJZQdXdPvpQZ6tVWQQib9wYAvysahXB21lCyIyBivjz/YEmudwfj0tmgzdYwKrTDfEMjNesw/T3U/YQ+A6mkYC8yFklwH1+kjnRD5Hc9jELEqJgA/AzeYPbETsHL0fbE3+43dAgfnMEVrSNP6snZBoWvemHYKuy0pJOUnSy7HX6qOyvaNbWhQq/fzIrhgixgXqdGyLsDN7Iqyb/IJ9mMh/eiGfM06ShpsCxgK7k/Gra5wcOEZ7vAUp/+3JPLPqxovFPeDmJuO5q2FevUz428VbeJ
*/