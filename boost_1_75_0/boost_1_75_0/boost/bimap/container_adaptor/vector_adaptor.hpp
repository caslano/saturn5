// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/vector_adaptor.hpp
/// \brief Container adaptor to easily build a std::vector signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/sequence_container_adaptor.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::vector signature compatible container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class ReverseIterator,
    class ConstReverseIterator,

    class IteratorToBaseConverter          = ::boost::mpl::na,
    class IteratorFromBaseConverter        = ::boost::mpl::na,
    class ReverseIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter             = ::boost::mpl::na,
    class ValueFromBaseConverter           = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class vector_adaptor :

    public ::boost::bimaps::container_adaptor::sequence_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses
    >
{

    typedef ::boost::bimaps::container_adaptor::sequence_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // Access -----------------------------------------------------------------

    public:

    vector_adaptor() {}

    explicit vector_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef vector_adaptor vector_adaptor_;

    // Interface --------------------------------------------------------------

    public:

    BOOST_DEDUCED_TYPENAME base_::size_type capacity() const
    {
        return this->base().capacity();
    }

    void reserve(BOOST_DEDUCED_TYPENAME base_::size_type m)
    {
        this->base().resize(m);
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

    BOOST_DEDUCED_TYPENAME base_::const_reference
        operator[](BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().operator[](n)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::const_reference
        at(BOOST_DEDUCED_TYPENAME base_::size_type n) const
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().at(n)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::reference
        operator[](BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().operator[](n)
        );
    }

    BOOST_DEDUCED_TYPENAME base_::reference
        at(BOOST_DEDUCED_TYPENAME base_::size_type n)
    {
        return this->template functor<BOOST_DEDUCED_TYPENAME base_::value_from_base>()(
            this->base().at(n)
        );
    }
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_ADAPTOR_HPP



/* vector_adaptor.hpp
6UdNO4C0+m3prLFqM2tp+Z/UknDTe1QAlYRBdkO1VhVzDiZYK5xgUecEI1DXgRLOYzw8EAZgx1uSxbKbkLt4rMhfznyXt/EzYC9tNHbzXmhudS24MnzyHC2d/ExWPcX02Yp9XF2tO5sTfe2lFdHOIzFNcVwpweRVPJ47iAuaGepegmX24sYIGeVm+gYBX+XNfGeDX5P5xvBDyqALookbUrNun5Sh7p4y1A1YLfA0LU4lv3imL9XInitat+eqDmeiHGy88LYgSpwTvqt/zsz3eJV+mwRfad9FnRFHpgGbLhH5YkRG6MgXdP/tRb7/Wcj3Vvx5YiHK6YfpsZ8eu/jHCkpu4MlV/PkZf75Pn9+kx6v87fP8KfNn75fo2R2eimcUSfCPU6Gx7LHKBBuGXQvg898czOH0ecjCUPGFCBemgQ8GOLgA3xaozAZfe0zKdyTVplGYFrdOxDd9ayY8FpQ6MaYA++lI9rAVcyYeK7j5fQswlfi4Pcj4btA/fxmDzAS+wlnPe0hJQxIlkPMlVc6nO42VUmg5v0yT88eAkD0rGmZrCVY4EiuclQxMMlaNtAmpdlpKPc8F8nSSI/ksqKMzyTA9DggZ5kv0FzLLUv26i5vS8ElDjNDmL+IXNdPgMiZNyEJtQooi2mE5pqE58dEu73RAtN7bI9TJrhcJcELeHEEYzaHIVagSB1HeE3tB5/Wxr8qYSAKxRkBAs/Ro
*/