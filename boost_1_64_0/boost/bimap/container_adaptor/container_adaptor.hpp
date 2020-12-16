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
FvmdCyPhPNgeXgeTYBnsBa+HY+ECOB7eAD31pSKt+nHH3zTu+EzjjqPqb1Otd1HNe64mXRw2Qv1JKfEi4QzYFM6EzeG1sBWcBdvC2TAOztH1ey7sDOfBbvBnsAecD3vB6+FAuAAOhTfAkXChruM3wqvhIjgJ/hxmw8VwGrwJFsJfwBnwZjgHLoVl8Fa4DN4Pa7r6cV2XV8MWcA2Mh4/DR+AT8Am4Hm6GT8JX4Qa4F27U9XAT/Aw+pevf0zCActsMG8AtMAZug7of0Xts5p3Q0+5HDge6y/MIbCm/tfy28uPkd5SfIH8+PAr3wM/hn+XvV7x3tfwjeAx+Db+ArnHLcRgLv4Rx8hPl95SfLH+Q/Mvlj5Y/Qf5k+fPlL5C/WP5z8ATcJv9l+bvkfyn/a/mtAtz+BPgVvEZ+ifxfyL9V/u3yfyO/VSD9ICyBX8O58p+R7xnnxmSrvfgZ576s87IDxsNX4EXwVTgUvgYnyD8GU7CV2t58ba8WNsjz/ATx2sBdMBHuhgPhG3AM/CNMh2/C2fLVn+mdKDNWOK0/20u8C+BbsC/cr/y9Da+EB2AqfAemyU+XnyV/s3wzR6Dz/S681On2h8kfIT9F/mj54+RfJT9Dfpb8AvnT5c+QvwVWwCSO6xBcAf9inR+9cwTz/Jyfx3Wf9wQ013fYFT6pfnwDvAZutLand3Pgcj/b+0Dt7EPYXX5P+TnwI1gCP9b2Uh16hwReqe0FYyO0va3EawCfh43lN5ffBm7TeXsBDobb4Uj5nvvBMm1/uJ/7wad0/E/DZnCz8rsFDoPPaDsO610GUxZmO82x49pOIeONUXAWHAdnw5vgfHgzvA4ug2XwXng9vA8ugKvhDfBpeCN8GS6GXZ30y3AAvBmOhkvgCngTXAtvgZ/DZdA1Dr0V9oS/gvnwNjgXLoePw9vhVvhrGBLoTh8GfwNbwbtgIvwtnAvvhD+Hd0PPfbF5VhpG+bkvbqHrY2tYB7bR9S7W6/58ndK39XM+2il9R1gDdoLBMB7GwgRo3Z9rO7X85GNkqHs7KTAQXqH77dHQcz6PKn1+wOnncyzxEuBVsAscB7vL7wmvhhfJv1jxB8m/UfEXw1S4VPE3wzS4D06AJ+FE2MQ1HoK94CSYCjPgLDgZ3g4z4cMwS+PdbLgN5sCX5b8i/w/y35C/R35ygNsfDKdY42M98wci/Yx3Wtd1z3PEwnAzv6h2G+j536Z5Vs+km4qNCHSnO6pyOqFy+gYuhN/CRfDv8Fb5t8v/jfxyeApu1fKX4HdwB3Sw/9flfyD/KHDCACd5hzWgEzaS30R+M/nN5cfAANhGy9vJ7yD/E1gDfib/qPyQAOPTztz+xfIHy68TSJ2GEbAmpEzM8hT5c2At+DYMhu2puLUh43jjJ8nvJf9i+YPlD4EhsFzLH4N14DYYCnfBuvAArAcTaWD1YQ/o8nvLv0h+svyB8i+RP0z+ZfJHyh8t/0r54+WnyZ8kP0v+FPnT5OfLny6/FIbBWVpeJn+h/PvlPyD/IfmPwnD4GIyAT8rfJH+L/G9gAxhKB9AQNoWNYDSMhDHy28jvKD9Bfjf5M+TPgY3hb6EDPgKbwpG16BPhKOjyx8o/AqPhF/JPyP8eNodhwfSbsDlsCQ8EMO7sH+LY3jHAcRiL7hTgSMHKsPVYBRbM3EUsloylYZOIt9Zl3ExuxQ5gSfEBjlRsFut3wBEXBTiOw+WwHNuJhSWwDxgDk7A0blSHwMWkyYNl2HJsHbaQdauxrfzejR3vh8EanQMccdgYbBZW3p/0cC12uHuQYxPcgVVgJ7GG3BwPSiYNzIJj4FqYBUuxddgObB92iuXRXQMcy+4IdsTDWTS2vjANy8M=
*/