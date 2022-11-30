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
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
*/