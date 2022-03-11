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