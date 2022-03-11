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