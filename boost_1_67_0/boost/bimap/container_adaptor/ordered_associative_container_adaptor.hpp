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