// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/list_adaptor.hpp
/// \brief Container adaptor to easily build a std::list signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/sequence_container_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/comparison_adaptor.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/call_traits.hpp>
#include <functional>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::list signature compatible container.

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
class list_adaptor :

    public ::boost::bimaps::container_adaptor::sequence_container_adaptor
    <
        Base, Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses
    >
{
    typedef ::boost::bimaps::container_adaptor::sequence_container_adaptor
    <
        Base, Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // Access -----------------------------------------------------------------

    public:

    explicit list_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef list_adaptor list_adaptor_;

    // Interface -------------------------------------------------------------

    public:

    void splice(Iterator position, list_adaptor & x)
    {
        this->base().splice(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()
                (position),
            x.base()
        );
    }

    void splice(Iterator position, list_adaptor & x, Iterator i)
    {
        this->base().splice(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()
                (position),
            x.base(),
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(i)
        );
    }

    void splice(Iterator position, list_adaptor & x, 
                Iterator first, Iterator last)
    {
        this->base().splice(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()
                (position),
            x.base(),
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(first),
            this->template functor<BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(last)
        );
    }

    void remove(
        BOOST_DEDUCED_TYPENAME ::boost::call_traits<
            BOOST_DEDUCED_TYPENAME base_::value_type
        >::param_type value
    )
    {
        this->base().remove(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(value)
        );
    }

    template< class Predicate >
    void remove_if(Predicate pred)
    {
        this->base().remove_if(
            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                Predicate,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( pred, this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }

    void unique()
    {
        this->base().unique(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::equal_to<BOOST_DEDUCED_TYPENAME base_::value_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >(
                std::equal_to<BOOST_DEDUCED_TYPENAME base_::value_type>(),
                this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()
            )
        );
    }

    template< class BinaryPredicate >
    void unique(BinaryPredicate binary_pred)
    {
        this->base().unique(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                BinaryPredicate,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( binary_pred,
               this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }

    void merge(list_adaptor & x)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >(
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>(),
                this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()
            )
        );
    }

    template< class Compare >
    void merge(list_adaptor & x, Compare comp)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( comp, this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }

    void sort()
    {
        this->base().sort(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >(
                std::less<BOOST_DEDUCED_TYPENAME base_::value_type>(),
                this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()
            )
        );
    }

    template< class Compare >
    void sort(Compare comp)
    {
        this->base().sort(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                BOOST_DEDUCED_TYPENAME base_::value_from_base

            >( comp, this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>() )
        );
    }

    void reverse()
    {
        this->base().reverse();
    }

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP



/* list_adaptor.hpp
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
*/