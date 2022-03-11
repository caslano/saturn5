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