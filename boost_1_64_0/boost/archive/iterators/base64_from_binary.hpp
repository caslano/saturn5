#ifndef BOOST_ARCHIVE_ITERATORS_BASE64_FROM_BINARY_HPP
#define BOOST_ARCHIVE_ITERATORS_BASE64_FROM_BINARY_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// base64_from_binary.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>

#include <cstddef> // size_t
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/iterator/transform_iterator.hpp>
#include <boost/archive/iterators/dataflow_exception.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// convert binary integers to base64 characters

namespace detail {

template<class CharType>
struct from_6_bit {
    typedef CharType result_type;
    CharType operator()(CharType t) const{
        static const char * lookup_table =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789"
            "+/";
        BOOST_ASSERT(t < 64);
        return lookup_table[static_cast<size_t>(t)];
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

//template<class Base, class CharType = typename Base::value_type>
template<
    class Base,
    class CharType = typename boost::iterator_value<Base>::type
>
class base64_from_binary :
    public transform_iterator<
        detail::from_6_bit<CharType>,
        Base
    >
{
    friend class boost::iterator_core_access;
    typedef transform_iterator<
        typename detail::from_6_bit<CharType>,
        Base
    > super_t;

public:
    // make composible buy using templated constructor
    template<class T>
    base64_from_binary(T start) :
        super_t(
            Base(static_cast< T >(start)),
            detail::from_6_bit<CharType>()
        )
    {}
    // intel 7.1 doesn't like default copy constructor
    base64_from_binary(const base64_from_binary & rhs) :
        super_t(
            Base(rhs.base_reference()),
            detail::from_6_bit<CharType>()
        )
    {}
//    base64_from_binary(){};
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_BASE64_FROM_BINARY_HPP

/* base64_from_binary.hpp
i6CUb0Ag2lh6YjDoednZaRO32RCdXfTgcWx/zweLIdg4ueyycXb5bm9IjvM2ouP3PUV267vx4L8u0BLVDYaIaoO+1yMtCdXvXsJhV9hRcjuGpcDVlUgwwNm5EjCYn9rBHfKz/B/26etEXDz1v+c5uzo56biaz9+T2uta44gE/N+b2Tg7u36bujNsFM5Oy9XeHHJI9TWRcmUHvC5ZISRHOFyiKjzybpsj0R4HcyLPR81bm5QHW4VYA7oJ2MPfC+btyQO2Fg97jMpHn5+bFJzv9yHgfv2P98gMfrATVE+q1o42FgRndH82v1kl4h+u5oeABzthw386btK+frUJIoVSSASSqeh5OhHQ92ScwDk5u9rhKGMJbA6Pmfc+lIuj7BGNKudv1kNW1dUBXRM9b9JQ6PPbS3D7mos+J3T+D+cKeY6ws8AfsibI2RLtUOv8ser8UZCKydfn/He7hr2hsCkoq0HqwkjI1fn7mpxR54MiHNouKWiHBeq4UPcklKMpS1lPKPKfwvyJcKYkP/5F32T9g/196xf+qwdPZ3SmpIfQHxwxGOOP9xgMuT9CJ984ifav31k7Hjb7uy1Q0GVKrYCrSC56fMhQtiISCN/boRtR6ledbBMgObma29lYwD3F89QhK0W48L0U8inbAcqHtb/XIuczyZ9s7efPkdIcwfQorZfyeaG3jFRffSc6j1TPFizmezmFrr73pwYcc8NRsidSex14WKm7IxH/i3iKZPvf71E6hPZ7dOM//X0x568vU5yzg9Q6i3/k98zm2+H/weeRfmsHPvQPPVf07+3c0O0ox6GmX+NXUyuCiyQ8+dTW+S/qfTUjUxu8qYW9E+aHBOOR1yfYQgM8AZnUX9YjceI384R6pInCBP6yHmmOv6vnAtW+YhhVkeL8XFDL+Kt6pGX85bjIMnB2Vs5/Um9eE2BJv91vJ3eoTzY6pX6dv3YJbvbbcieSi/1VP07Q0U924IxHXMTUwoVoh86HFlKmNjjnH+6hg+8LQ+eTByWoeUA5HIgLzsKagOYysk8/9IPopunXNwqmNg42LmTzRMUPpiSZRHcB6ac4AymnlO+GjtPR40P+38sRc8P8uv23aUA5+bpMSYH4D/kuRALO/u/3rg6k9yZk/EZPDofHY+fnhSUQiY5ECvEIFmcH/eI9sV+7Qs+GvJ41zhnr4IhFTpBS+fy4ZOMgv8uL/XocEKzaOCOcR1Uhq+eEI+Lgt6H/ugXsN/brQVuCyNmhSr/m29mYf69H2mGb73aFtbdxhpDPwvqHcliXC9bS0dUBj/kx3wXEhazJT+VI47+/TUTm9ct6pLerqGqU680bM7oSut7Pe01KX30QlYvcI4/4hhAbA4kEtu9VkCsWsOMC3ziDnY9SsCgnny//ah9fy+1hgTgrwnzwi8X9HI+R6juT+oOOKOZ/j0K+OgsGnWwc3ODQ8djvceTXPrB2BAcrF2tK9aD0W10wk7/bD3k98l7s8fDAc0fEyn7YxF+sEOtOdIR5o3qgVJ9CLXtnKzhJpJg0EIV8OMx5H4IloA6LvB6lSTgQYIscHQgkJ8d8S19NCPfNiFAsQZWj9phkZaR8UFR0PWTvcF8DQns4MbJ8l6+BvZMjEZ2PfBqGuof39lDj6ziWYAMu1jbO803B1FHjYOcRgLpHwxHu8QRLHDyWHju/Gd/rke6/2tb8PfT97YqF8RAGo8dBXBmskNSQLB9tnRjK7b6/ZyUrRx0VOh+trcg9Eu4SUM5Bykc7H9yTTg2uh11R8ySdNIn5qM6weEeCM8IOZKZYC0ofSHzrFDjgiCf8zI/vaycrmh8U3ScZMlH1yJmM5Nvb2BOwLgQPso6d4R0K4Wc3xPyWq+g=
*/