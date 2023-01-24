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
h2DjBPcwgDuDlP7EtPPbNwfgeUUNAbxspwD43Z3B57oA7HWLmiG/m9s3SA2z8DCXDl6628kismQN3Sx6Eq8VFexxT2DyfQaXRuRyfzFkDxKNX2vXnH6+WxhawN9aKXpZCr/w3YpKwed1dg+O19XupgbFLI2H7sYDLDHtuDs1rbvx1F1rwQmx6f8Juwxez3zraLFCu4dkvKqZA9xkpwFWkv0IvJLxOvgtsxbs5sUSueNBhmRb6eUWjTO9gZLRPC68cVuJRDUuVBE/4hEe3dVQiugBAqAf0dYinLvSOU2/tgK1ibR6Bu86UgG1w+YE2hEQEiftEIh9eAexlvmV9JxTiaqoXEjy+L87Qp9/TyR7xq2vqmss3F2gS1BkziefRlMB9F4gAquT7Tl0qCga1PxHQSkjPjvkk2nJMyVrwbF4Jul8acRXm/kJJ1CXkpt1wV/s6kcn4Nb8XaRAf+IaOoQDUcnFo46kFVKYICgKaWXUEVKmF8dTJgnhfw0/4uo4K55vSCiMBhvByI0W3M3gCD4aD5V+RJXmlS1EK3QI8wXHzPyQUt6m1CbDkhsJh87UAmnX0ezwqng6JMQPcGanwYHrStXU3lqP4W7GqCx0ZyxeZCklI6H/cPanvR2nTL6Lv83R3uYoPyKueAsaHiGl5I9CPE6Py7bm39ACkXhFYjOQmPo9IXF8b8q0zEChkpKFwdDdvVU332TDattQqjuh
*/