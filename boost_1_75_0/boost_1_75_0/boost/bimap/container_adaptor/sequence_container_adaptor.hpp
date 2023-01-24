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
S0y+edCw4n8ulMy0TVnpQZnp6y6Mp9SG/Ycy000VQZP85b+DcBYVjnxh83LBF8zBRcYGF/k2rJkyU5+/A7jWG2HBMtNjz4aUmbKEzPS8TmY6Ym+crSzsQngeE6axFbnLP5SZsrqElpkuMQfITMOebVRmOj8lWGZ6qrghmSnfGCwz7SeZaRnKTFvVCQxF1jYkM4lrbEs6B7KyVKe30u/0l40d3K//JE+to6DW3Vf5xofSUQVn3lmAU6pxHjSq2PaFB1Ti9NsOGxgPsCu3p7Kx4HOhAbK/vHNoclYmkzgU0ek/4vIqlrnXySxl/u1Q0X/N/O/o1AwpKSuklDSsU5NS0r6O/6GUdLY2YMpM8Jthdp5cIWbnI18FMcGK2qDZmUJF/lwmitwQXGRBcBGL3xxaStrma1hKQsY39JaGpaTrYmhC7rloVidk7xhNSgrr+H8tJa39KwB511xETPz8qcBEn01BrE3+KwgTFy9gkZVqkbMbg4pkBRfZdsEcJCUteKZxKQkxF31z4+wsvCNh74ULGvZqL9GkpK9s/5+lpIRLGpSSKs6bG5eSqr6pJR6cg5LMqRY6EeUIyUjLL9Wqd4mJVMg9M/joaqySVEYy0h82ykTmBq9xzxCMux+3qZo6fvP1nk90mrodNpKRoFK24NOi8yDciNuOitdtivPPC34IgQ0DQiE3t3PnJAtthI5lHEAKlh0JbIF+VvqLi7lA
*/