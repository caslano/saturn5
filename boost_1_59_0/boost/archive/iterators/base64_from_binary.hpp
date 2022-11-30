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
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
*/