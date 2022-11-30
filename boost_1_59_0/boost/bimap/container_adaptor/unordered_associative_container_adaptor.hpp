// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/unordered_associative_container_adaptor.hpp
/// \brief Container adaptor to build a type that is compliant to the concept of an unordered associative container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/associative_container_adaptor.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {


#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template
<
    class Base, class Iterator, class ConstIterator,
    class LocalIterator, class ConstLocalIterator,
    class KeyType,
    class IteratorToBaseConverter, class IteratorFromBaseConverter,
    class LocalIteratorFromBaseConverter,
    class ValueToBaseConverter, class ValueFromBaseConverter,
    class KeyToBaseConverter,
    class FunctorsFromDerivedClasses
>
struct unordered_associative_container_adaptor_base
{

    typedef associative_container_adaptor
    <
        Base, Iterator, ConstIterator, KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ValueToBaseConverter   , ValueFromBaseConverter,
        KeyToBaseConverter,

        BOOST_DEDUCED_TYPENAME mpl::push_front<

            FunctorsFromDerivedClasses,

            BOOST_DEDUCED_TYPENAME mpl::if_<
                ::boost::mpl::is_na<LocalIteratorFromBaseConverter>,
            // {
                    detail::iterator_from_base_identity
                    <
                        BOOST_DEDUCED_TYPENAME Base::local_iterator,
                        LocalIterator,
                        BOOST_DEDUCED_TYPENAME Base::const_local_iterator,
                        ConstLocalIterator
                    >,
            // }
            // else
            // {
                    LocalIteratorFromBaseConverter
            // }

            >::type

        >::type

    > type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


/// \brief Container adaptor to build a type that is compliant to the concept of an unordered associative container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,

    class LocalIterator,
    class ConstLocalIterator,

    class KeyType,

    class IteratorToBaseConverter        = ::boost::mpl::na,
    class IteratorFromBaseConverter      = ::boost::mpl::na,
    class LocalIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter           = ::boost::mpl::na,
    class ValueFromBaseConverter         = ::boost::mpl::na,
    class KeyToBaseConverter             = ::boost::mpl::na,

    class FunctorsFromDerivedClasses     = mpl::vector<>

>
class unordered_associative_container_adaptor :

    public unordered_associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator,
        LocalIterator, ConstLocalIterator,
        KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        LocalIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type
{
    typedef BOOST_DEDUCED_TYPENAME unordered_associative_container_adaptor_base
    <
        Base, Iterator, ConstIterator,
        LocalIterator, ConstLocalIterator,
        KeyType,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        LocalIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    >::type base_;

    // Metadata ---------------------------------------------------------------

    public:

    typedef BOOST_DEDUCED_TYPENAME Base::key_equal key_equal;
    typedef BOOST_DEDUCED_TYPENAME Base::hasher hasher;

    typedef LocalIterator      local_iterator;
    typedef ConstLocalIterator const_local_iterator;

    protected:

    typedef BOOST_DEDUCED_TYPENAME mpl::if_<
        ::boost::mpl::is_na<LocalIteratorFromBaseConverter>,
        // {
                detail::iterator_from_base_identity
                <
                    BOOST_DEDUCED_TYPENAME Base::local_iterator,
                    local_iterator,
                    BOOST_DEDUCED_TYPENAME Base::const_local_iterator,
                    const_local_iterator
                >,
        // }
        // else
        // {
                LocalIteratorFromBaseConverter
        // }

        >::type local_iterator_from_base;

    // Access -----------------------------------------------------------------

    public:

    explicit unordered_associative_container_adaptor(Base & c)
        : base_(c) {}

    protected:


    typedef unordered_associative_container_adaptor
                unordered_associative_container_adaptor_;

    // Interface --------------------------------------------------------------

    public:

    // bucket interface:

    BOOST_DEDUCED_TYPENAME base_::size_type bucket_count() const
    {
        return this->base().bucket_count();
    }

    BOOST_DEDUCED_TYPENAME base_::size_type max_bucket_count() const
    {
        return this->base().max_bucket_count();
    }

    BOOST_DEDUCED_TYPENAME base_::size_type bucket_size(
        BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->base().bucket_size(n);
    }

    template< class CompatibleKey >
    BOOST_DEDUCED_TYPENAME base_::size_type bucket(
        const CompatibleKey & k) const
    {
        typedef BOOST_DEDUCED_TYPENAME base_::key_to_base key_to_base;
        return this->base().bucket(
            this->template functor<key_to_base>()(k)
        );
    }

    local_iterator       begin(BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<
            local_iterator_from_base
        >()                          ( this->base().begin(n) );
    }

    const_local_iterator begin(BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<
            local_iterator_from_base
        >()                          ( this->base().begin(n) );
    }

    local_iterator       end(BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<
            local_iterator_from_base
        >()                          ( this->base().end(n) );
    }

    const_local_iterator end(BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<
            local_iterator_from_base
        >()                          ( this->base().end(n) );
    }

    // hash policy

    float load_factor() const
    {
        return this->base().load_factor();
    }

    float max_load_factor() const
    {
        return this->base().max_load_factor();
    }

    void max_load_factor(float z)
    {
        return this->base().max_load_factor(z);
    }

    void rehash(BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->base().rehash(n);
    }

    // We have redefined end and begin so we have to manually route the old ones

    BOOST_DEDUCED_TYPENAME base_::iterator begin()
    {
        return base_::container_adaptor_::begin();
    }

    BOOST_DEDUCED_TYPENAME base_::iterator end()
    {
        return base_::container_adaptor_::end();
    }

    BOOST_DEDUCED_TYPENAME base_::const_iterator begin() const
    {
        return base_::container_adaptor_::begin();
    }

    BOOST_DEDUCED_TYPENAME base_::const_iterator end() const
    {
        return base_::container_adaptor_::end();
    }

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_ASSOCIATIVE_CONTAINER_ADAPTOR_HPP

/* unordered_associative_container_adaptor.hpp
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
*/