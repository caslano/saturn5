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
YHu+up9NpPlRaybzG4YQCvO+Da3fcWw/YuXHein+eytPb7bTpG2xuysjiNVhBk4NBo0a8qL1lT8uKuchkwkp1UD96gIUo52f6J3sWLXB4t9UUuW0DSSrVtVGR3EsE5OTwJQc1lMFodyhfPEkWjLi3SDS+Q25zIhrxVI+SyEMO3h7yqIBKLaIOwtPVEUZlF51JqTa96xE71l8OHoEnHakcjwU6nIB1oBDEUeGFOS1FgBHZlsHsIu3zm6rmzWcMBiHm8EqGeBMmcHKTsNd1r/gSrWnA986ZijbVpMiNaN6GjgKewL5/S2nzQa5BiMvJbGf3J+UrwMe6V7zF5BnBfkpAHnlRBsGangt2q3uVRbmmA3g1gJ9k/hL08NLSYwKr2RtKk/lmGlJmfanmStwi8h5uSeGoeyhTyzcD1aSCheB9GENgMRwOfATcCb+Wk0wWK/8CVxNQYiy9BDB2IXXA2qoL+oqkJ8/thiUE09yoH76A4InHuJO54dEpyXndHJfwX5ZqltLKTnRntawtZdTLfjhFwm8GhGBVNEmiX1k36Z28pzE6HtM4KvArKer96E2wQ6hGA32koKWBs1Ni6/1yJOMPl42RqKnwnADeTGJTyMHD2fxIiMNLKO/pD2K3xKpv52e+AdyZ6Hm6PGHOYC+rII0dZMkQ/8tI/Bbtv5bduC3Ev3kKtFJfkdPQff5YSaYDhwy6IQ/fkz7aftmCH8P
*/