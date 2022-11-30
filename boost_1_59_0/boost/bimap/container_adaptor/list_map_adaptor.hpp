 // Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/list_map_adaptor.hpp
/// \brief Container adaptor.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_MAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_MAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>

#include <boost/bimap/container_adaptor/list_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/identity_converters.hpp>
#include <boost/bimap/container_adaptor/detail/key_extractor.hpp>
#include <boost/bimap/container_adaptor/detail/comparison_adaptor.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/if.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class Base, class Iterator, class ConstIterator,
    class ReverseIterator, class ConstReverseIterator,
    class IteratorToBaseConverter, class IteratorFromBaseConverter,
    class ReverseIteratorFromBaseConverter,
    class ValueToBaseConverter, class ValueFromBaseConverter,
    class KeyFromBaseValueConverter,
    class FunctorsFromDerivedClasses
>
struct list_map_adaptor_base
{
    typedef list_adaptor
    <
        Base,

        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,

        IteratorToBaseConverter, IteratorFromBaseConverter,

        ReverseIteratorFromBaseConverter,

        ValueToBaseConverter, ValueFromBaseConverter,

        BOOST_DEDUCED_TYPENAME mpl::push_front<

            FunctorsFromDerivedClasses,

            BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<KeyFromBaseValueConverter>,
            // {
                    detail::key_from_pair_extractor
                    <
                        BOOST_DEDUCED_TYPENAME Iterator::value_type 
                    >,
            // }
            // else
            // {
                    KeyFromBaseValueConverter
            // }

            >::type

        >::type

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Container adaptor to easily build a list map container

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
    class KeyFromBaseValueConverter        = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class list_map_adaptor :

    public list_map_adaptor_base
    <
        Base, Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyFromBaseValueConverter,
        FunctorsFromDerivedClasses

    >::type
{
    typedef BOOST_DEDUCED_TYPENAME list_map_adaptor_base
    <
        Base, Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyFromBaseValueConverter,
        FunctorsFromDerivedClasses

    >::type base_;

    // MetaData -------------------------------------------------------------

    public:

    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type  key_type;
    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::second_type data_type;
    typedef data_type mapped_type;

    protected:

    typedef BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<KeyFromBaseValueConverter>,
    // {
            detail::key_from_pair_extractor< BOOST_DEDUCED_TYPENAME Iterator::value_type >,
    // }
    // else
    // {
            KeyFromBaseValueConverter
    // }

    >::type key_from_base_value;

    // Access -----------------------------------------------------------------

    public:

    explicit list_map_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef list_map_adaptor list_map_adaptor_;

    // Functions -------------------------------------------------------------

    public:

    // The following functions are overwritten in order to work 
    // with key_type instead of value_type

    template< class Predicate >
    void remove_if(Predicate pred)
    {
        this->base().remove_if(
            ::boost::bimaps::container_adaptor::detail::unary_check_adaptor
            <
                Predicate,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >( pred, this->template functor<key_from_base_value>() )
        );
    }

    void unique()
    {
        this->base().unique(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::equal_to<key_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >(
                std::equal_to<key_type>(),
                this->template functor<key_from_base_value>()
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
                key_from_base_value

            >( binary_pred, this->template functor<key_from_base_value>() )
        );
    }

    void merge(list_map_adaptor & x)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<key_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >(
                std::less<key_type>(),
                this->template functor<key_from_base_value>()
            )
        );
    }

    template< class Compare >
    void merge(list_map_adaptor & x, Compare comp)
    {
        this->base().merge(x.base(),
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                Compare,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >( comp, this->template functor<key_from_base_value>() )
        );
    }

    void sort()
    {
        this->base().sort(
            ::boost::bimaps::container_adaptor::detail::comparison_adaptor
            <
                std::less<key_type>,
                BOOST_DEDUCED_TYPENAME Base::value_type,
                key_from_base_value

            >(
                std::less<key_type>(),
                this->template functor<key_from_base_value>()
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
                key_from_base_value

            >( comp, this->template functor<key_from_base_value>() )
        );
    }

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_LIST_MAP_ADAPTOR_HPP


/* list_map_adaptor.hpp
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
*/