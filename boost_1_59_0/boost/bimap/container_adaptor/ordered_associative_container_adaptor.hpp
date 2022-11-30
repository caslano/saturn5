// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/ordered_associative_container_adaptor.hpp
/// \brief Container adaptor to build a type that is compliant to the concept of an ordered associative container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_ORDERED_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_ORDERED_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/associative_container_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/comparison_adaptor.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/operators.hpp>
#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class Base, class Iterator, class ConstIterator,
    class ReverseIterator, class ConstReverseIterator, class KeyType,
    class IteratorToBaseConverter, class IteratorFromBaseConverter,
    class ReverseIteratorFromBaseConverter,
    class ValueToBaseConverter, class ValueFromBaseConverter, 
    class KeyToBaseConverter,
    class FunctorsFromDerivedClasses
>
struct ordered_associative_container_adaptor_base
{
    typedef associative_container_adaptor<
        Base, Iterator, ConstIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter, KeyToBaseConverter,

        BOOST_DEDUCED_TYPENAME mpl::push_front<

            FunctorsFromDerivedClasses,

            BOOST_DEDUCED_TYPENAME mpl::if_<
                ::boost::mpl::is_na<ReverseIteratorFromBaseConverter>,
            // {
                    detail::iterator_from_base_identity
                    <
                        BOOST_DEDUCED_TYPENAME Base::reverse_iterator,
                        ReverseIterator,
                        BOOST_DEDUCED_TYPENAME Base::const_reverse_iterator,
                        ConstReverseIterator
                    >,
            // }
            // else
            // {
                    ReverseIteratorFromBaseConverter
            // }

            >::type

        >::type

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

/// \brief Container adaptor to build a type that is compliant to the concept of an ordered associative container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class ReverseIterator,
    class ConstReverseIterator,

    class KeyType,

    class IteratorToBaseConverter          = ::boost::mpl::na,
    class IteratorFromBaseConverter        = ::boost::mpl::na,
    class ReverseIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter             = ::boost::mpl::na,
    class ValueFromBaseConverter           = ::boost::mpl::na,
    class KeyToBaseConverter               = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class ordered_associative_container_adaptor :

    public ordered_associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator,
        ReverseIterator, ConstReverseIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter, KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type,

    ::boost::totally_ordered
    <
        ordered_associative_container_adaptor
        <
            Base, Iterator, ConstIterator,
            ReverseIterator, ConstReverseIterator,
            KeyType, IteratorToBaseConverter, IteratorFromBaseConverter,
            ReverseIteratorFromBaseConverter,
            ValueToBaseConverter, ValueFromBaseConverter,
            KeyToBaseConverter, FunctorsFromDerivedClasses
        >
    >
{
    // MetaData -------------------------------------------------------------

    typedef BOOST_DEDUCED_TYPENAME ordered_associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator,
        ReverseIterator, ConstReverseIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter, KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type base_;

    public:

    typedef detail::compatible_comparison_adaptor
    <
        BOOST_DEDUCED_TYPENAME Base::key_compare,
        BOOST_DEDUCED_TYPENAME base_::key_type,
        BOOST_DEDUCED_TYPENAME base_::key_to_base

    > key_compare;

    typedef detail::comparison_adaptor
    <
        BOOST_DEDUCED_TYPENAME Base::value_compare,
        BOOST_DEDUCED_TYPENAME base_::value_type,
        BOOST_DEDUCED_TYPENAME base_::value_to_base

    > value_compare;

    typedef ReverseIterator      reverse_iterator;
    typedef ConstReverseIterator const_reverse_iterator;

    protected:

    typedef BOOST_DEDUCED_TYPENAME mpl::if_<
        ::boost::mpl::is_na<ReverseIteratorFromBaseConverter>,
        // {
                detail::iterator_from_base_identity
                <
                    BOOST_DEDUCED_TYPENAME Base::reverse_iterator,
                    reverse_iterator,
                    BOOST_DEDUCED_TYPENAME Base::const_reverse_iterator,
                    const_reverse_iterator
                >,
        // }
        // else
        // {
                ReverseIteratorFromBaseConverter
        // }

        >::type reverse_iterator_from_base;

    // Access -----------------------------------------------------------------

    public:

    explicit ordered_associative_container_adaptor(Base & c)
        : base_(c) {}

    protected:

    typedef ordered_associative_container_adaptor
                ordered_associative_container_adaptor_;

    // Interface --------------------------------------------------------------

    public:

    reverse_iterator rbegin()
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rbegin() );

    }

    reverse_iterator rend()
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rend() );
    }

    const_reverse_iterator rbegin() const
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rbegin() );
    }

    const_reverse_iterator rend() const
    {
        return this->template functor<
            reverse_iterator_from_base
        >()                            ( this->base().rend() );
    }

    key_compare key_comp() const
    {
        typedef BOOST_DEDUCED_TYPENAME base_::key_to_base key_to_base_;

        return key_compare(
            this->base().key_comp(),
            this->template functor<key_to_base_>()
        );
    }

    value_compare value_comp() const
    {
        typedef BOOST_DEDUCED_TYPENAME base_::value_to_base value_to_base_;

        return value_compare(
            this->base().value_comp(),
            this->template functor<value_to_base_>()
        );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::iterator lower_bound(const CompatibleKey & k)
    {
       return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(
                this->base().lower_bound(
                    this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)
                )
            );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::const_iterator lower_bound(const CompatibleKey & k) const
    {
       return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(
                this->base().lower_bound(
                    this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)
                )
            );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::iterator upper_bound(const CompatibleKey & k)
    {
       return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(
                this->base().upper_bound(
                    this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)
                )
            );
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::const_iterator upper_bound(const CompatibleKey & k) const
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(
                this->base().upper_bound(
                    this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)
                )
            );
    }

    // Totally ordered implementation

    bool operator==(const ordered_associative_container_adaptor & c) const
    {
        return ( this->base() == c.base() );
    }

    bool operator<(const ordered_associative_container_adaptor & c) const
    {
        return ( this->base() < c.base() );
    }
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_ORDERED_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP

/* ordered_associative_container_adaptor.hpp
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
*/