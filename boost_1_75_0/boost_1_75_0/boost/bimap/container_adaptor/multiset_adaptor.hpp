// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/multiset_adaptor.hpp
/// \brief Container adaptor to easily build a std::multiset signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_MULTISET_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_MULTISET_ADAPTOR_HPP

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

/// \brief Container adaptor to easily build a std::multiset signature compatible container.

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
class multiset_adaptor :

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

    explicit multiset_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef multiset_adaptor multiset_adaptor_;

    public:

    BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_MULTISET_ADAPTOR_HPP


/* multiset_adaptor.hpp
GNxbQ2Ja8jo4LLYWjDBRZcL5ZLakdz6Jdg2X9A48Xu0ixJg0MDWoZUTUwuXr++5mi6G6O/vx+mYL+k/2cfeCJ/aa1OJKh1fN6uk+EFAav2GQJkz7fZeaYOoWvYYHnVgP7MW+3qMd1MMHJcnEz+uEcc+7rS1a9neCs0cEZ3+ytUXfKQrR6JT9dDAPBte85NYIPNdHfxo7/bYBreFY8N0D6PPiQdg9k+0J+E3brlx4FVBVh7t2uPJaj1bRWrxSmbQS4l1HCsO4AEL9tBcTtDr6bReiLGpdb7J3Vfcj/0Lml6okvQaDT/Cn84j0sFBUzzQy+PpaelkMVV100btAvE7jYYLSRHSIIooKoaJtwm4NbfBB2REehLbUKDxFPfulhQdISQku8kpwkdZRQZieg00GWFBgyezwAAuKb1pZ0HSiRsXu4lcAVQdcvnmAVBdaNXGMIpY+h9kjz4PI6op1BWAYf0sUsZ7ijQgsj4wjLL/USjODcLJ3VQ/5wXzNjU5drPmvG2h6kIlBK35VClK6q0SFl8QB5a47EM49h5NJiN82lLFZNj2uhF7KO5VZr+A6hMBzhLi4m1iI85k4w6jrMBT45GXssKgQd+IAn99W0pKN711w9y95XQ88dzkPtfVbtxTGHO9tiK22Nf9YQCcC/dUiMu7tSTOcN+Jm4s5WNsM3wgy/jc3wPe7hLvQBDFZpykeHyOgvFVjuHy+aAedo
*/