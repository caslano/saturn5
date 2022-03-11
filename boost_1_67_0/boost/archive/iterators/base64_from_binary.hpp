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