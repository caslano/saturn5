// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/container_adaptor.hpp
/// \brief Container adaptor to build a type that is compliant to the concept of a container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_CONTAINER_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_CONTAINER_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <utility>

#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/bimap/container_adaptor/detail/identity_converters.hpp>
#include <boost/iterator/iterator_traits.hpp>

#include <boost/bimap/container_adaptor/detail/functor_bag.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/call_traits.hpp>



namespace boost {
namespace bimaps {

/// \brief Container Adaptor toolbox, easy way to build new containers from existing ones.

namespace container_adaptor {

/// \brief Container adaptor to build a type that is compliant to the concept of a container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,

    class IteratorToBaseConverter   = ::boost::mpl::na,
    class IteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter      = ::boost::mpl::na,
    class ValueFromBaseConverter    = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class container_adaptor
{
    // MetaData -------------------------------------------------------------

    public:

    typedef Iterator iterator;
    typedef ConstIterator const_iterator;

    typedef BOOST_DEDUCED_TYPENAME iterator_value    <       iterator >::type value_type;
    typedef BOOST_DEDUCED_TYPENAME iterator_pointer  <       iterator >::type pointer;
    typedef BOOST_DEDUCED_TYPENAME iterator_reference<       iterator >::type reference;
    typedef BOOST_DEDUCED_TYPENAME iterator_reference< const_iterator >::type const_reference;

    typedef BOOST_DEDUCED_TYPENAME Base::size_type size_type;
    typedef BOOST_DEDUCED_TYPENAME Base::difference_type difference_type;

    typedef BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<IteratorToBaseConverter>,
        // {
                ::boost::bimaps::container_adaptor::detail::
                    iterator_to_base_identity
                <
                    BOOST_DEDUCED_TYPENAME Base::iterator                , iterator,
                    BOOST_DEDUCED_TYPENAME Base::const_iterator          , const_iterator
                >,
        // }
        // else
        // {
                IteratorToBaseConverter
        // }

        >::type iterator_to_base;

    typedef BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<IteratorFromBaseConverter>,
        // {
                ::boost::bimaps::container_adaptor::detail::
                    iterator_from_base_identity
                <
                    BOOST_DEDUCED_TYPENAME Base::iterator                , iterator,
                    BOOST_DEDUCED_TYPENAME Base::const_iterator          , const_iterator
                >,
        // }
        // else
        // {
                IteratorFromBaseConverter
        // }

        >::type iterator_from_base;

    typedef BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<ValueToBaseConverter>,
        // {
                ::boost::bimaps::container_adaptor::detail::
                    value_to_base_identity
                <
                    BOOST_DEDUCED_TYPENAME Base::value_type,
                    value_type
                >,
        // }
        // else
        // {
                ValueToBaseConverter
        // }

        >::type value_to_base;

    typedef BOOST_DEDUCED_TYPENAME mpl::if_< ::boost::mpl::is_na<ValueFromBaseConverter>,
        // {
                ::boost::bimaps::container_adaptor::detail::
                    value_from_base_identity
                <
                    BOOST_DEDUCED_TYPENAME Base::value_type,
                    value_type
                >,
        // }
        // else
        // {
                ValueFromBaseConverter
        // }

        >::type value_from_base;

    // ACCESS -----------------------------------------------------------------

    public:

    explicit container_adaptor(Base & c) : dwfb(c) {}

    protected:

    typedef Base base_type;

    typedef container_adaptor container_adaptor_;

    const Base & base() const { return dwfb.data; }
          Base & base()       { return dwfb.data; }

    // Interface --------------------------------------------------------------

    public:

    size_type size() const                    { return base().size();         }
    size_type max_size() const                { return base().max_size();     }
    bool empty() const                        { return base().empty();        }

    iterator begin()
    {
        return this->template functor<iterator_from_base>()( base().begin() );
    }

    iterator end()
    {
        return this->template functor<iterator_from_base>()( base().end() );
    }

    const_iterator begin() const
    {
        return this->template functor<iterator_from_base>()( base().begin() );
    }

    const_iterator end() const
    {
        return this->template functor<iterator_from_base>()( base().end() );
    }


    iterator erase(iterator pos)
    {
        return this->template functor<iterator_from_base>()(
            base().erase(this->template functor<iterator_to_base>()(pos))
        );
    }

    iterator erase(iterator first, iterator last)
    {
        return this->template functor<iterator_from_base>()(
            base().erase(
                this->template functor<iterator_to_base>()(first),
                this->template functor<iterator_to_base>()(last)
            )
        );
    }

    void clear()
    {
        base().clear();
    }

    template< class InputIterator >
    void insert(InputIterator iterBegin, InputIterator iterEnd)
    {
        for( ; iterBegin != iterEnd ; ++iterBegin )
        {
            base().insert( this->template
                functor<value_to_base>()( *iterBegin )
            );
        }
    }

    std::pair<iterator, bool> insert(
        BOOST_DEDUCED_TYPENAME ::boost::call_traits< value_type >::param_type x)
    {
        std::pair< BOOST_DEDUCED_TYPENAME Base::iterator, bool > r(
            base().insert( this->template functor<value_to_base>()(x) )
        );

        return std::pair<iterator, bool>( this->template
                    functor<iterator_from_base>()(r.first),r.second
               );
    }

    iterator insert(iterator pos,
                    BOOST_DEDUCED_TYPENAME ::boost::call_traits< value_type >::param_type x)
    {
        return this->template functor<iterator_from_base>()(
            base().insert(
                this->template functor<iterator_to_base>()(pos),
                this->template functor<value_to_base>()(x))
        );
    }

    void swap( container_adaptor & c )
    {
        base().swap( c.base() );
    }

    // Access to functors ----------------------------------------------------

    protected:

    template< class Functor >
    Functor & functor()
    {
        return dwfb.template functor<Functor>();
    }

    template< class Functor >
    Functor const & functor() const
    {
        return dwfb.template functor<Functor>();
    }

    // Data ------------------------------------------------------------------

    private:

    ::boost::bimaps::container_adaptor::detail::data_with_functor_bag
    <
        Base &,

        BOOST_DEDUCED_TYPENAME mpl::copy
        <
            mpl::vector
            <
                iterator_to_base,
                iterator_from_base,
                value_to_base,
                value_from_base
            >,

            mpl::front_inserter< FunctorsFromDerivedClasses >

        >::type

    > dwfb;
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_CONTAINER_ADAPTOR_HPP

/* container_adaptor.hpp
pWagUzk8pLC5kiZFHACNVedcjUppQTuUdWzezN/nXOUmWLv8isB2SAWKQzmZWpOFcdsF+Ukb9mV02zny/HmoF1uHYujGT/MW67mJTtDtct7gdWPogF6uMKmb6rBo0OCGxYCvG5atkO57q89mq2wYtxxy/6dj2pSvKVaysDP5H7t7NcJSjXDXZf/7IgGmk1kHHTyYz51UeNN2JDy87/0FUEsDBAoAAAAIAC1nSlJcWhm6gggAAN0XAAAkAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9tdWx0aS11di5jVVQFAAG2SCRgrVj/b+JGFv+dv+I1p83ZyAG2UqVrSHJHE7KHSiBKyK5W3coa7AGmMR7qsUly3fzv9958MTaQZFcqu63N8L5+3tfZdvPv+zSgCW9+Qv1fiB98ao7rTP7Bo3w/dRh+BfMHub7g8y0lbdiwfA19eJvlK3iaJbRaTug9DN9S9IVso/+1ifNLSK94gmzEeS5XT5mYL3Lwzn14//PP/4Ij+LHzYyeAC5YKnsBtztMpz+YBnMT65D8L9vjYUvwsAJ4DS1pW1GQhFCg5yx9YxgHfExHxVPEYmIKYqygTU/wiUsgXHGYi4XA+vv48GH0I4GEhogUJeZIFqIUskhgWbM0h4xEXayNj
*/