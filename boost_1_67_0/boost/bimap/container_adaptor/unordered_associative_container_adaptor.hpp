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