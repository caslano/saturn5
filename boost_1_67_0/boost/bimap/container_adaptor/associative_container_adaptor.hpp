// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/associative_container_adaptor.hpp
/// \brief Container adaptor to build a type that is compliant to the concept of an associative container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <utility>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/bimap/container_adaptor/detail/identity_converters.hpp>
#include <boost/bimap/container_adaptor/container_adaptor.hpp>
#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class Base, class Iterator, class ConstIterator, class KeyType,
    class IteratorToBaseConverter, class IteratorFromBaseConverter,
    class ValueToBaseConverter, class ValueFromBaseConverter, class KeyToBaseConverter,
    class FunctorsFromDerivedClasses
>
struct associative_container_adaptor_base
{
    typedef container_adaptor
    <
        Base,

        Iterator, ConstIterator,

        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter   , ValueFromBaseConverter,

        BOOST_DEDUCED_TYPENAME mpl::push_front<

            FunctorsFromDerivedClasses,

            BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<KeyToBaseConverter>,
            // {
                    detail::key_to_base_identity
                    <
                        BOOST_DEDUCED_TYPENAME Base::key_type, KeyType
                    >,
            // }
            // else
            // {
                    KeyToBaseConverter
            // }

            >::type

        >::type

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


/// \brief Container adaptor to build a type that is compliant to the concept of an associative container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,

    class KeyType,

    class IteratorToBaseConverter   = ::boost::mpl::na,
    class IteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter      = ::boost::mpl::na,
    class ValueFromBaseConverter    = ::boost::mpl::na,
    class KeyToBaseConverter        = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class associative_container_adaptor :

    public associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter, KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type
{

    // MetaData -------------------------------------------------------------

    typedef typename associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter, KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type base_;

    public:

    typedef KeyType key_type;

    protected:

    typedef BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<KeyToBaseConverter>,
    // {
            detail::key_to_base_identity
            <
                BOOST_DEDUCED_TYPENAME Base::key_type, KeyType
            >,
    // }
    // else
    // {
            KeyToBaseConverter
    // }

    >::type key_to_base;

    public:

    explicit associative_container_adaptor(Base & c)
        : base_(c) {}

    protected:


    typedef associative_container_adaptor associative_container_adaptor_;

    // Interface --------------------------------------------------------------

    public:

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::size_type erase(const CompatibleKey & k)
    {
        return this->base().erase
        (
            this->template functor<key_to_base>()(k)
        );
    }

    // As we redefine erase, the other overloads need to be manually routed

    BOOST_DEDUCED_TYPENAME base_::iterator erase(
        BOOST_DEDUCED_TYPENAME base_::iterator pos)
    {
        return base_::container_adaptor_::erase(pos);
    }

    BOOST_DEDUCED_TYPENAME base_::iterator erase(
        BOOST_DEDUCED_TYPENAME base_::iterator first,
        BOOST_DEDUCED_TYPENAME base_::iterator last)
    {
        return base_::container_adaptor_::erase(first,last);
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::size_type count(const CompatibleKey & k) const
    {
        return this->base().count(
            this->template functor<key_to_base>()(k)
        );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::iterator find(const CompatibleKey & k)
    {
        return this->template functor<typename base_::iterator_from_base>()
        (
            this->base().find(
                this->template functor<key_to_base>()(k)
            )
        );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::const_iterator
        find(const CompatibleKey & k) const
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()
        (
            this->base().find(
                this->template functor<key_to_base>()(k)
            )
        );
    }

    template< class CompatibleKey >
    std::pair
    <
        BOOST_DEDUCED_TYPENAME base_::iterator,
        BOOST_DEDUCED_TYPENAME base_::iterator
    >
        equal_range(const CompatibleKey & k)
    {
        std::pair<

            BOOST_DEDUCED_TYPENAME Base::iterator,
            BOOST_DEDUCED_TYPENAME Base::iterator

        > r( this->base().equal_range(
                this->template functor<key_to_base>()(k)
            )
        );

        return std::pair
        <
            BOOST_DEDUCED_TYPENAME base_::iterator,
            BOOST_DEDUCED_TYPENAME base_::iterator
        >(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base
            >()                                         ( r.first ),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base
            >()                                         ( r.second )
        );
    }

    template< class CompatibleKey >
    std::pair
    <
        BOOST_DEDUCED_TYPENAME base_::const_iterator,
        BOOST_DEDUCED_TYPENAME base_::const_iterator
    >
        equal_range(const CompatibleKey & k) const
    {
        std::pair<

            BOOST_DEDUCED_TYPENAME Base::const_iterator,
            BOOST_DEDUCED_TYPENAME Base::const_iterator

        > r( this->base().equal_range(
                this->template functor<key_to_base>()(k)
            )
        );

        return std::pair
        <
            BOOST_DEDUCED_TYPENAME base_::const_iterator,
            BOOST_DEDUCED_TYPENAME base_::const_iterator
        >(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base
            >()                                         ( r.first ),
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base
            >()                                         ( r.second )
        );
    }

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP




/* associative_container_adaptor.hpp
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
*/