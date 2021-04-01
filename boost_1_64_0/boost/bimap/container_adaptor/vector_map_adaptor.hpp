// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/vector_map_adaptor.hpp
/// \brief Container adaptor.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_MAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_MAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/bimap/container_adaptor/vector_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/identity_converters.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class ReverseIterator,
    class ConstReverseIterator,

    class IteratorToBaseConverter          = ::boost::mpl::na,
    class IteratorFromBaseConverter        = ::boost::mpl::na,
    class ReverseIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter             = ::boost::mpl::na,
    class ValueFromBaseConverter           = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class vector_map_adaptor :

    public vector_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses
    >
{
    typedef vector_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // MetaData -------------------------------------------------------------

    public:

    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type  key_type;
    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::second_type data_type;
    typedef data_type mapped_type;

    // Access -----------------------------------------------------------------

    public:

    vector_map_adaptor() {}

    explicit vector_map_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef vector_map_adaptor vector_map_adaptor_;

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_MAP_ADAPTOR_HPP


/* vector_map_adaptor.hpp
B2/NgSibG0pzwkXbv2NCQwy3tKOx4/vovNaAxRHLBPKs2hFQJqPTfHtZgc775v+4P5gzWVfVGPMgxbKi3HsxX1M8ZQ9ESwjnC4RSWqdqspdS6/z2MFoD4wk6Lo1swT1URqD6g51knQIun3JQaSlWk2wULreBUD4UaBfEfjh5SGQ6x4kscb2YaE4tARGXGjf9Ic+H+ISwYYgMyNqfZUiofksq1TR0Snct1fOevDTT5QD8xvpZdj/RwYVaG8JCPN6YgFdQlVpTp7TLI+8XNbTlbss/2tYlTwxTXMkh+SnzeIUlGXfVO8x05zvM0xuNkEkdk6kcQkvM/TGmssYvH0TjvlAfQ/uCkxLlScFgPQVhRjh0H57vrrmcwo0W/YRscDD4EFLVWij3+wenliOHbrn9xJVRBcc8M4ooFZKjd4Y2a6Sz6ncZP+8+GklRW/3xqenc9m01ZYg80isBx5luKpY8MHyGFpJJkOvjf79wl+DSOm5IG/EzdsJEVXiAqPKvDRPyFa3XDuJv/N9vSLBAnl3FtpTTaGtlWpxa+boWWLq0XYMRa5wTLaS+PW5aPA==
*/