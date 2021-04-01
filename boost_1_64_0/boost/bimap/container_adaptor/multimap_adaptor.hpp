// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/multimap_adaptor.hpp
/// \brief Container adaptor to easily build a std::multimap signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_MULTIMAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_MULTIMAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/ordered_associative_container_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/non_unique_container_helper.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::multimap signature compatible container.

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
    class KeyToBaseConverter               = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class multimap_adaptor :

    public ::boost::bimaps::container_adaptor::
                ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses
    >
{
    typedef ::boost::bimaps::container_adaptor::
                ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // MetaData -------------------------------------------------------------

    public:

    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::second_type data_type;
    typedef data_type mapped_type;

    // Access -----------------------------------------------------------------

    public:

    explicit multimap_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef multimap_adaptor multimap_adaptor_;

    public:

    BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_MULTIMAP_ADAPTOR_HPP



/* multimap_adaptor.hpp
uovYN5PqAUJjTFlGIbjQyC2HXvW2hgn08FzsAryggQkQyY06doPMdO/zluQAhJqAjuH5GDnX/UgKCbj3+M+rCVjwGCaWqAUvrjMgO4XKddonm2px+jxX4Pr1xtgX1le8qjf2NyrN7I1urEW3M21USFeQDaVqjPeLt7Ida8bZQlDjayoGkxLbq9Sad81Gop0DEfBckIYb/137v0WOCOo7x8yBuHUoEuhm9WKOo0k2Z6DhHjcrjpP5q7ylgiTDxiKi6Md3sBAfemtfqArXm0XCXFBuKof3/FpvzhElOB26YJSndPzP8bJWgEZXveShDsnQRENHoUkAL/74lzwBNg/jhQ3x6fDkPmSlvVCvkW4nmprlbpFIvL9sYdfpgF7yfJ1rwYuyKtXoxkPp3LutAbUYB76Xq3zVzrUh2s475qJFuHdzE7XbDM1XEmh9q+iytRDQNO7r+TqKc9tKORWxDS0ohMwL8IOeVGOlr4DV9dKVcDKHhe6VMACkOAiu1ktSafTkdzE0i/DnnbDb79C0ibtcYQfYSK/ijZ5mb2sQlgl/2QOwf9ALCmfVTJXLHw==
*/