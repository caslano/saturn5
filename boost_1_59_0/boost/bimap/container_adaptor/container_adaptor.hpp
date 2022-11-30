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
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
*/