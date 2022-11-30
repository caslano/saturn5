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
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
*/