// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/sequence_container_adaptor.hpp
/// \brief Container adaptor to build a type that is compliant to the concept of a weak associative container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_SEQUENCE_CONTAINER_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_SEQUENCE_CONTAINER_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <utility>

#include <boost/mpl/if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/bimap/container_adaptor/detail/identity_converters.hpp>
#include <boost/bimap/container_adaptor/container_adaptor.hpp>
#include <boost/call_traits.hpp>
#include <boost/operators.hpp>

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
    class FunctorsFromDerivedClasses
>
struct sequence_container_adaptor_base
{
    typedef container_adaptor
    <
        Base, Iterator, ConstIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,

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

/// \brief Container adaptor to build a type that is compliant to the concept of a sequence container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,

    class ReverseIterator,
    class ConstReverseIterator,

    class IteratorToBaseConverter           = ::boost::mpl::na,
    class IteratorFromBaseConverter         = ::boost::mpl::na,
    class ReverseIteratorFromBaseConverter  = ::boost::mpl::na,
    class ValueToBaseConverter              = ::boost::mpl::na,
    class ValueFromBaseConverter            = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class sequence_container_adaptor :

    public sequence_container_adaptor_base
    <
        Base, Iterator, ConstIterator,
        ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses

    >::type,

    ::boost::totally_ordered
    <
        sequence_container_adaptor
        <
            Base, Iterator, ConstIterator,
            ReverseIterator, ConstReverseIterator,
            IteratorToBaseConverter, IteratorFromBaseConverter,
            ReverseIteratorFromBaseConverter,
            ValueToBaseConverter, ValueFromBaseConverter,
            FunctorsFromDerivedClasses
        >
    >
{
    typedef BOOST_DEDUCED_TYPENAME sequence_container_adaptor_base
    <
        Base, Iterator, ConstIterator,
        ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses

    >::type base_;

    // MetaData -------------------------------------------------------------

    public:

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

    explicit sequence_container_adaptor(Base & c)
        : base_(c) {}

    protected:


    typedef sequence_container_adaptor sequence_container_adaptor_;

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

    void resize(BOOST_DEDUCED_TYPENAME base_::size_type n,
                BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                    BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x =
                        BOOST_DEDUCED_TYPENAME base_::value_type())
    {
        this->base().resize(n,
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::reference front()
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::value_from_base>()
        (
            this->base().front()
        );
    }

    BOOST_DEDUCED_TYPENAME base_::reference back()
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::value_from_base>()
        (
            this->base().back()
        );
    }

    BOOST_DEDUCED_TYPENAME base_::const_reference front() const
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::value_from_base>()
        (
            this->base().front()
        );
    }

    BOOST_DEDUCED_TYPENAME base_::const_reference back() const
    {
        return this->template functor<
            BOOST_DEDUCED_TYPENAME base_::value_from_base>()
        (
            this->base().back()
        );
    }

    void push_front(
        BOOST_DEDUCED_TYPENAME ::boost::call_traits<
            BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)
    {
        this->base().push_front(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x));
    }

    void pop_front()
    {
        this->base().pop_front();
    }

    void push_back(
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< 
            BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)
    {
        this->base().push_back(
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x));
    }

    void pop_back()
    {
        this->base().pop_back();
    }

    std::pair<BOOST_DEDUCED_TYPENAME base_::iterator,bool>
    insert(BOOST_DEDUCED_TYPENAME base_::iterator position,
           BOOST_DEDUCED_TYPENAME ::boost::call_traits< 
                BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)
    {
        std::pair< BOOST_DEDUCED_TYPENAME Base::iterator, bool > r(
            this->base().insert(
                this->template functor<
                    BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
                this->template functor<
                    BOOST_DEDUCED_TYPENAME base_::value_to_base   >()(x)
            )
        );

        return std::pair<BOOST_DEDUCED_TYPENAME base_::iterator, bool>(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(r.first),
            r.second
        );
    }

    void insert(BOOST_DEDUCED_TYPENAME base_::iterator position,
                BOOST_DEDUCED_TYPENAME base_::size_type m,
                BOOST_DEDUCED_TYPENAME ::boost::call_traits<
                    BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)
    {
        this->base().insert(
            this->template functor<
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(position),
            m,
            this->template functor<BOOST_DEDUCED_TYPENAME base_::value_to_base   >()(x)
        );
    }

    template< class InputIterator >
    void insert(BOOST_DEDUCED_TYPENAME base_::iterator position,
                InputIterator first, InputIterator last)
    {
        // This is the same problem found in the insert function 
        // of container_adaptor
        // For now, do the simple thing. This can be optimized

        for( ; first != last ; ++first )
        {
            this->base().insert(
                this->template functor<
                    BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()( position ),
                this->template functor<
                    BOOST_DEDUCED_TYPENAME base_::value_to_base   >()( *first )
            );
        }
    }

    // Totally ordered implementation

    bool operator==(const sequence_container_adaptor & c) const
    {
        return ( this->base() == c.base() );
    }

    bool operator<(const sequence_container_adaptor & c) const
    {
        return ( this->base() < c.base() );
    }
};

} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_SEQUENCE_CONTAINER_ADAPTOR_HPP

/* sequence_container_adaptor.hpp
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
*/