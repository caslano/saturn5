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