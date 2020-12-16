//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_RANDOM_BERNOULLI_DISTRIBUTION_HPP
#define BOOST_COMPUTE_RANDOM_BERNOULLI_DISTRIBUTION_HPP

#include <boost/assert.hpp>
#include <boost/type_traits.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/function.hpp>
#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/literal.hpp>

namespace boost {
namespace compute {

///
/// \class bernoulli_distribution
/// \brief Produces random boolean values according to the following
/// discrete probability function with parameter p :
/// P(true/p) = p and P(false/p) = (1 - p)
///
/// The following example shows how to setup a bernoulli distribution to
/// produce random boolean values with parameter p = 0.25
///
/// \snippet test/test_bernoulli_distribution.cpp generate
///
template<class RealType = float>
class bernoulli_distribution
{
public:

    /// Creates a new bernoulli distribution
    bernoulli_distribution(RealType p = 0.5f)
        : m_p(p)
    {
    }

    /// Destroys the bernoulli_distribution object
    ~bernoulli_distribution()
    {
    }

    /// Returns the value of the parameter p
    RealType p() const
    {
        return m_p;
    }

    /// Generates bernoulli distributed booleans and stores
    /// them in the range [\p first, \p last).
    template<class OutputIterator, class Generator>
    void generate(OutputIterator first,
                  OutputIterator last,
                  Generator &generator,
                  command_queue &queue)
    {
        size_t count = detail::iterator_range_size(first, last);

        vector<uint_> tmp(count, queue.get_context());
        generator.generate(tmp.begin(), tmp.end(), queue);

        BOOST_COMPUTE_FUNCTION(bool, scale_random, (const uint_ x),
        {
            return (convert_RealType(x) / MAX_RANDOM) < PARAM;
        });

        scale_random.define("PARAM", detail::make_literal(m_p));
        scale_random.define("MAX_RANDOM", "UINT_MAX");
        scale_random.define(
            "convert_RealType", std::string("convert_") + type_name<RealType>()
        );

        transform(
            tmp.begin(), tmp.end(), first, scale_random, queue
        );
    }

private:
    RealType m_p;

    BOOST_STATIC_ASSERT_MSG(
        boost::is_floating_point<RealType>::value,
        "Template argument must be a floating point type"
    );
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_RANDOM_BERNOULLI_DISTRIBUTION_HPP

/* bernoulli_distribution.hpp
pSsHfp1plcU8ZRtTe10E0ThTkn7PWR2bB1JceG32FBvZIk4tGelLMblLPvoGcsdZpqVKEjVrs36ahf1Vp5uPu+DPB3MuSKKyZGkVxR2WIQeeKxtvNlWa8ji2DevHk8iZdHKYz7uoGp5kcSXYxUtrWPc2Ozmpw+JtYtHKqk5S1nLpNHfFXto+exFy4CP/Bvqdjc1Nd63HUjskbumrRd1luBtHbE8iL2EZr+s8qxO2c2HiBuxEdHnDiox5DH684yT8GVOVnuCqilm1ub67Pd1+tR4lK9+FNp32ddjr+ucLfhnPLngjE55ErNWTVp2coZe6Nn6btrEt6qJKZcK0LWh6UZ8C+pTxBwp8K32e2rzbLLjmw2Q44Q0bco+SdklWyDwrpEpsZvrX6yhbygn0stTD5zgYQ730lCKVFSYBFfk45Grcp2s8r1TctNnsvG2Ua2eye2nNZI/LNvRfep86wTtL+BT7ZZQsy/SXSNTcba6He8plIlNPliSJ8jxuWOtk6QaG0rBHI7yC1UoraSVlsJ/295T9N9DnrVgVxyqJasVmhtjkymaf03UHOZN9npUmzhLRVJVuGte5YOEmfIAh36bD432wyvMk1Up64Yr2GteHzlhv8/XjqDBn7mcIX8xElsYR97fKWqD+GyI929w1n7dhRcR5W7R6OukldA2XTNTP+vp+oC+aoY2KQresj3cJYV4cBCqr1ctRnDhZzav1KWbCt/eDvNX/2Kfzlcf2Pj9G42iMTUjl3Rr7Rp+/ZELW+jOlJ9POxTdOTQwWMdna1A963zirgLnRwnxHbkBSRsyyImr12mtPgGsjLe74WsIXsTqOkjzRSrunA0XsXNQWlNpPmos6XwzqLKumapTgvp5G4+3GuL79jVRfK1Hxtqqs6H0qdh22Sp+nZnlWpkVVVnZYtUV0Da7tmqcbn884HqwBvJZ5LmIraG+yf0ZPS5OGOpyTsBMSfsVUIessS/22OuFEf8H/Z8Kfs1pUFRcRZ69eW59uXtrcmpwZ7Wy8m3gT0UmRiqzKhR3ZdlunMHpjL7SGfedNtG+bOEpFmbP9EydPkBmjeXAm9Xl4yvS6o9IyDoZ0JtJvacefEv6MNVEa81LKLnj77DHa5qqoSTOhixcJf2TOUkWd11K3dHW6tWoftXvKv4s7QceHtaUsm1xovt3Ja0wi3/BGDHljCV/OkkrXtopKr8Grq6X+S0tGPPIwbywpQ7G4ilQtm8acPPY2Z23OLm9ses8XJt3a+3ufd4VHpVBplevWmpsjrYpO1ib0KOjfqqiqpsgitqP9gya7upndQlFNdEz6jTBn9OE307VbxIonWRN57fUlo43HHB++22kUx02dG7lTjbaNpEoVwa/C5zWvvWLO86Jw385V85wR8Xpwv0jkVaxOc9UkusGIFBTt7Gy5i7XYXLbjfqu/XyRlNKwoCvPaSMy7l6I1OcDwXssv59mpUCKqs0Tfs/cKHHfjuX8fchfJi1apxNrYzvobvc2u7E/4ZS+lMuN6XRFMvzXD3IjwjsbHLhdtFUsprZbtw2poysY308cb847MK9EqHZpia9Ksr1/ZWYN+rXX1uU7qU5vtlSjtRgn9gv3l7y0WZ6E8krXQbZ1O9Nvo6Xawp5kskDlSNVKvYHY8rVeN3sSGS+8VfI9pO/K0qmu94rMrOsZFS3M5T1T3PQ7GPivb/1B23bCZLVUYEAUFBamgoKBACCGEYFnDWkLayTmBSaIBYxtscML2gwci55xzzhmJkoKCgoKCnDMUFBQUSFBQUDBz/3vPP2d+L2G1b5+1O998cybdmXPOnJOyTQ7OmTsr3vn4PHLDWeehL8P7kZKSWxnURN7NnpnfwvvdHneLccs=
*/