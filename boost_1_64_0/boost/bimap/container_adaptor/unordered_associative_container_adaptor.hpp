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
sFCTi/EiCQjt82e2ypdqQCFgtN4wlJUdwhYCHzCHk3Frc3xPWbe0m3ZYk9KeVhcw0WpBwBPZdW+eiIZsV2WuxMmc7NRDCbBKCd5zPCPw5ua/Hgy6tt7GPfojydgKES2m7LvR+NEFWLpCtQlYgQ5sF/8VHy1WJgJfiNSAdP4exyAI4Jwyb7smmJaDR1vjzeD6FJzWMcfJs99r6c+7ooWCDhsz4MM1s4ROhYiIC/M7JQqh68Iph1B4k+pLlXHpo7wonmA92nW9TRfFukj/9yipz8gdeXsh2E3QDr9rKBxYt3wKh2//Eb6oO2F5SnG8B+B4Q/ZAfwr4ZZaznCxVNVE5bV/pWon1Nf3U/4HEkBbiHb0CQslaG9z0FQe44G87eMkYwkrPdOrMQVukSLDXKxaY1LP36hZawBHKIGzCr2cdSWVZwhmX0xXHn72mCiVcIqIqrNS0G6T+PrAA4oaZ81PteyaFvCtSFF9J8wg4QY/40x+/yjxlikhaeaOo3LjipPTrRohzA1RSEDg9cJC8H+ui3tMEKIJ4YaHFMPBjpzdRGMUSGcNc2/bnbZAtbA==
*/