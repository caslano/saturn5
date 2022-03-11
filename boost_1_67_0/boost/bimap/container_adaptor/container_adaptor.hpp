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