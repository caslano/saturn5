#ifndef BOOST_ARCHIVE_ITERATORS_BINARY_FROM_BASE64_HPP
#define BOOST_ARCHIVE_ITERATORS_BINARY_FROM_BASE64_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_from_base64.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>

#include <boost/serialization/throw_exception.hpp>
#include <boost/static_assert.hpp>

#include <boost/iterator/transform_iterator.hpp>
#include <boost/archive/iterators/dataflow_exception.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// convert base64 characters to binary data

namespace detail {

template<class CharType>
struct to_6_bit {
    typedef CharType result_type;
    CharType operator()(CharType t) const{
        static const signed char lookup_table[] = {
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,
            52,53,54,55,56,57,58,59,60,61,-1,-1,-1, 0,-1,-1, // render '=' as 0
            -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
            15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
            -1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
            41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1
        };
        // metrowerks trips this assertion - how come?
        #if ! defined(__MWERKS__)
        BOOST_STATIC_ASSERT(128 == sizeof(lookup_table));
        #endif
        signed char value = -1;
        if((unsigned)t <= 127)
            value = lookup_table[(unsigned)t];
        if(-1 == value)
            boost::serialization::throw_exception(
                dataflow_exception(dataflow_exception::invalid_base64_character)
            );
        return value;
    }
};

} // namespace detail

// note: what we would like to do is
// template<class Base, class CharType = typename Base::value_type>
//  typedef transform_iterator<
//      from_6_bit<CharType>,
//      transform_width<Base, 6, sizeof(Base::value_type) * 8, CharType>
//  > base64_from_binary;
// but C++ won't accept this.  Rather than using a "type generator" and
// using a different syntax, make a derivation which should be equivalent.
//
// Another issue addressed here is that the transform_iterator doesn't have
// a templated constructor.  This makes it incompatible with the dataflow
// ideal.  This is also addressed here.

template<
    class Base,
    class CharType = typename boost::iterator_value<Base>::type
>
class binary_from_base64 : public
    transform_iterator<
        detail::to_6_bit<CharType>,
        Base
    >
{
    friend class boost::iterator_core_access;
    typedef transform_iterator<
        detail::to_6_bit<CharType>,
        Base
    > super_t;
public:
    // make composible buy using templated constructor
    template<class T>
    binary_from_base64(T  start) :
        super_t(
            Base(static_cast< T >(start)),
            detail::to_6_bit<CharType>()
        )
    {}
    // intel 7.1 doesn't like default copy constructor
    binary_from_base64(const binary_from_base64 & rhs) :
        super_t(
            Base(rhs.base_reference()),
            detail::to_6_bit<CharType>()
        )
    {}
//    binary_from_base64(){};
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_BINARY_FROM_BASE64_HPP

/* binary_from_base64.hpp
ciQTfY/sP7o2uj5lo4f0V3yGzznN/8beUYBFlXXPRVQsBLt5BoquQVlYIKKoiCiomOQgSMoAggUGBnZ3/Pbaa3fH7toB/mJhKxa4dtzzn7nvMT5Gdn/96/vrDofzTt1+N857cyeMChApidKFDNaI/knlyZGHRkQOilB14tz8nAFF7HCCw7+S04yq0F/uFpWvlAxVWyMDPfXcAXnI6X7+A3vDMdRANQ99pY+oUzSU6wd3lYqiNyjaL0puaxWtHvREyHNIVAVVLCLQ2jAgVLWe0q2DaO1jLZZgalqfeR/V/ZenXH3fGurZGDpFDeWqeCgHecgNxmtat3zh0yDjRbeLYbrq1R7pG/jJaS+gUW71POViSexDk57h+p3ijVItRQ34ygTXRhnW1PkRN4gB3VZ3d6jo9pSoIldvqtS0WP+rWiNPubo18pZTBAblapPbR+dDd24gbVLi4Y/1VBWVl55Sm4GRPmIkUOdHyHPvDZT9PI21OT3mi75yz+n1DP1veWSE7Aye06hqNU85pfLHcnXtK3JlCDToVqp8quTqTCpyZQg13Iqp5YYbRpGuuj5JT94Mq2YcnwCVN1xlJ/TU/Vdtr1EEPqqBSC3XZ9aAH613/qqSzcNeXmLl4tNCgLZ6cm8RN3Xu/BoMHUoFW+vtFbm6I+WxH1e1e95ydbvn6b/w+0b/hZ/Kf/FNeorT6Pv9V1rt3+T3CokUZuq8fZOdLsd/i1+P9pd/Uz6jBv1t6Wn/Rj+iWHMZmAqeyu3RXbWPdCDaitZzmqDaen26sX0GU4F9gsJitcHwFV/88K+aps4cqKapzOr1p44nUQph1OXlVFX8kIi8+bk2Ed9Qfpr3xD+5pb693iIjgsQ/H78odUO5uHcHP5pGo/WLEU2ggxQXJ7VoIbl3o19dyiOYfMUxo4+MvyWQlpEjJAEFI7qSmUZfPgy+/ggNvaYRfP8HQJKtmSMY/w0fYSuD2f/25x/R/mCsb/Vvbf/Cf2/7y9YU2V9t6/+3/+9/vrGR/4OCcl5FjhNG8Hq0d7ez/a5xlaxV42o0uWnDQiI0ujGnt6W2r2SpbWGplbtwbx2jb2G9rrtzZ/e2PmGRfoE+QVF6Wpl8KJBvXLdfMfBb6vSFp0erLE8pPdqFB/hF6KYUf9rxx4bJK05y8Wp1mgFhkVpypg2M9YvWSP7RfgGhGv3qSK2nIY0wSZlHVXzhyQgiz7xurlDbRQbGhmn0Xu3Bv+cHj4gUWZDT1uTmUw0a0hIVklawIeQYDBduYVrS6BwVaj2tRpUZouNUz0dVfg15GSpRlaotDP0USjki/JTtqZIgzdnxUeQJJCuKK5IqPkK/VlTrKQ8RDDJBQTRnYCzN2dS8FPTNLaQqWi0nb69WQ5O8amNKPUyoGdLKDkVpB3lPoqKFitJL1Pzo2Ah1/xMZVGIy5Kv7JS2DfSLEizk+opBqvrpy1XzqwdSBvu7vhjSl/63Pr3PuO4N1kGi9FgD9oyNjo1rIPCUGH536t8dLtSTiNezncqSW9Zro26GuFK2J0W2DlfSi/GKCxbji4eJO44poEDUdRAzVepPsdRaKsUpPVy2q/NcPUO6RBjn9pmtPD6/O1EBRPpp4xWOh4gdFazRqgcIXDUJsuhkoZ4GaeCFTycM14RTlF5oU84yfNte5+W3be3jqqo3W4GJg0SXkFxFILRsQqi6Xf2yQbbAmnjpF7vLKPFsSE9Og/nzk9hH8oJAoraRLJ6/FM4WQsDBNfxrBKD6db1K/Q48MDJTknitFBsmSXBtfH32CugVxXEjOGOUJGoiGOAiBALqqB9YQn3tcg0haW2ohBvxIIxRa5bQjRIGGpJ70EQvpPPkOZNsWnMCLQK1FfUw=
*/