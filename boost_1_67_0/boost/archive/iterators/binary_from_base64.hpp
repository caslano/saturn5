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