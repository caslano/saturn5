// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/vector_adaptor.hpp
/// \brief Container adaptor to easily build a std::vector signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/sequence_container_adaptor.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::vector signature compatible container.

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
class vector_adaptor :

    public ::boost::bimaps::container_adaptor::sequence_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses
    >
{

    typedef ::boost::bimaps::container_adaptor::sequence_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // Access -----------------------------------------------------------------

    public:

    vector_adaptor() {}

    explicit vector_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef vector_adaptor vector_adaptor_;

    // Interface --------------------------------------------------------------

    public:

    BOOST_DEDUCED_TYPENAME base_::size_type capacity() const
    {
        return this->base().capacity();
    }

    void reserve(BOOST_DEDUCED_TYPENAME base_::size_type m)
    {
        this->base().resize(m);
    }

    void resize(BOOST_DEDUCED_TYPENAME base_::size_type n,
                BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                    BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x =
                        BOOST_DEDUCED_TYPENAME base_::value_type())
    {
        this->base().resize(n,
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::const_reference
        operator[](BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().operator[](n)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::const_reference
        at(BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().at(n)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::reference
        operator[](BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().operator[](n)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::reference
        at(BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().at(n)
        );
    }
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_ADAPTOR_HPP



/* vector_adaptor.hpp
aOMNqSF1iTd1sKA/OtpxY1/59DuI8TnxHxZYwZfcOLp3UaiufgNKNt5MDb7IOLnOS6vWJc53LM9s0YUAETegDiP6RYdqzNE6Ui94Mv3HBlhhfaXpVGHtCfjoJxT7u7WeAC1Guyox3ahWjwBDRmGqd9l4DDqDyhJSTUIoHavjqVOVXHyMF14AE+JwYQ++ZIz6HOmJ1ooTR47r0dZEBaffIyzMMVGRQUqAc4kjBffJ1X429CNVBBkKm773aoFbgZ9ff3daKo3tDaxi96KKR52fYIwAXiRfGlf7YIRD5XpT4HESFzKziRMK5hH7t6hCTi1RR1EishHbtNDh3MVBx/hs6ZDnwGkPeBUnC011xqk3cQZElCmvX8apEMtw9PXUE1NQ02UhxzN4AaF3LAJo2F8hVPdTFreF7qFW9KWt0oCdkjs5kGppi5Z3MHut3/06whpTpLP+mO/cDy53dOBChAKomjMzHcmKydRrAw5sn9yP28jyvF794MJprImvu856/Qqnqx+0OOpPKdNSMxBSn9qPvbPt5BYPMV1CSREfJxt3jZK/3DqYAKLW6gZg5Q==
*/