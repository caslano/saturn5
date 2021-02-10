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
aWBoTTzwR3qZxd3Gc10G6VA5QhBtnaNxGWc5D6vH3j6ZfuMvp63KbV67FBf7DqfgbZP52B6SREaeEv/jcuY5Pt+vch6dGVUowflR8VykIrdGeQRvAIclXwWTwNnbrQquELRiljNUUTU94zk2jM3RcwnXWorYep1IhThNPTTISCLPzNur4OwHxDAenZE1ZOos49xzsOxYgOMgz+TTnjDt6jPGoJXaYq9ur/8SajUfdw1gcRy6CiczFWbpgmXQRLaAGgGkxdLCQOdU+Clb8t9+6vxO7l0Ohn1o0il9o8Jw2OkAqHSVoZCZ5/gC+AlH6sG7uOW0HgRahSbXw/AUS3zF0wrLwcP0QMddzLwf6NjXtYP0VjrWNM8yJOxnGbYHYqfG9k59SVG8E6RFuKSg92fSaaylxCGkOFNPOiU9v6xCfaZ4jmPQc7CSp+PrSfjpZjDpX/QmPaPm25iubwYfe5P+97DgAyddlmyoTfun+Blar9KOAuuVpt4BqRfH2KfLvv5OwdGZw0qHvQLYdsUseHRvVVP/9ei0kh7NWKY8RCEuG67UHJpLnIxsrjOEMgqjE2N4NgmjHd+0vmpO4VfcidA7zwpxgdrYEGKni+veH1oVvu8yRT2IPFo4IUdnSzV3P0VMcWPr7YfwYjzqHzfs
*/