///////////////////////////////////////////////////////////////////////////////
/// \file empty.hpp
/// Proto callables for boost::empty()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_EMPTY_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_EMPTY_HPP_EAN_27_08_2012

#include <boost/range/empty.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::empty()
    struct empty
    {
        BOOST_PROTO_CALLABLE()

        typedef bool result_type;

        template<typename Rng>
        bool operator()(Rng const &rng) const
        {
            return boost::empty(rng);
        }
    };

}}}

#endif

/* empty.hpp
31WiSFI57AZJHYjr73haAvaXDEfZwOKjwW6p6dlBE8Vs4eqyItr3biY3CeQkxxGtfzular3EY2mLWZOr4rbvGeg2Basq4vT+/sNSJXMsfXo6oqRwRV3uWP4GX1l8yBHC5C3M0frywuBQKXrtTdu9nNct9vFezCJ9R5TjmrYhff2BAd9y5Lnx2r2MjXa1tw9mZmKGrDeGUFMy5ePXRAZv/W6dF+Cul08OZKKrnsEfamWDTaX9doNqw3McKVyj7y6H4vbUsq0XI9MO6MRUEJ8kgMdvZPf7MN95F3DMfoSbkZeZA+/+Qtep0CepPqvtjWk/H+0jiiQg80ta4CMz72P6ecw5P8UjdRBzXw23h2cJevR+sNZP1IT0f4dp32cJHNc6hnCPAXoNhwHmBCzIiZEkSmyxyt0ie58zWNB6YW8N4lTdm7JFaexj0Mg3lHXfVu3uz2if4L3j+6OA4tBqBAYVpLtiN5fzFR/KByLCmcgcz44zVQMUS6iaFo5hrKnIb3gnE3mZqOazIOqpOCZy8B1obng/lOVGBk2nYI0XSVgapRo1sv7ZKCeq5PcdM8aC/RHEta0MKqkzXyQLqhwgLWZofMMH8lh9RapO5ionJLr4cVTIWkA1vR0RIhd9edZSu5BBXXZHgdJHLRCbkbZT3/9AHThY21V+fTPQ97HZTLBw4gdGYL7QPhIFk4GtPHPeg6Pros1e8c/sAP5glSi8
*/