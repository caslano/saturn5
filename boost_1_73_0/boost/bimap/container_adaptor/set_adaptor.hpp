// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/set_adaptor.hpp
/// \brief Container adaptor to easily build a std::set signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/ordered_associative_container_adaptor.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::set signature compatible container.

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
class set_adaptor :

    public ::boost::bimaps::container_adaptor::
                ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
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
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // Access -----------------------------------------------------------------

    public:

    explicit set_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef set_adaptor set_adaptor_;

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP



/* set_adaptor.hpp
itlU4gK6ZLW4XtyME3RcvESSpGZSO6ZlH6kfU/IhKnSStADc3yZ9ip6rKsfLIo7B9dRTR7m3fLt8L9X7OIzuFWbffqbeCfm0HKlUU2oq9amw5koP5V6ct4nKDPTBEpDoVWWTskP5iJpT1PmBEtqp3aT31YfrTY02eG15hgC/7I2Dk2Ftst7DcRtgL+f07nan4nC97Z50a3hd8DpS4ERpMMJB+AMf4CNFBDytLPd6mzBUGCW8
*/