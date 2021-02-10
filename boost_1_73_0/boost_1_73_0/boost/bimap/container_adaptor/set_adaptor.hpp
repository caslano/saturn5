// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/set_adaptor.hpp
/// \brief Container adaptor to easily build a std::set signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/ordered_associative_container_adaptor.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::set signature compatible container.

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
    class KeyToBaseConverter               = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class set_adaptor :

    public ::boost::bimaps::container_adaptor::
                ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses
    >
{

    typedef ::boost::bimaps::container_adaptor::
                ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // Access -----------------------------------------------------------------

    public:

    explicit set_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef set_adaptor set_adaptor_;

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP



/* set_adaptor.hpp
NQuiKOA7ZzEVmiZANCRUx4rN8Q8TYDIKKeMUesPR7GbwawCLjMWZdbKSJehMljyBjDxSUDSm7LHyURBlQKYIR+cJ0wYdloZJcYKxKRiqcm192PCEawnkkTBO5hiIGMiMKfR5GMal4ph9mMhYh3FT/klm8nUlM0wiJyuQhQEjodQ0AGsZQC4TltonEoKLRTnnTGfBJhsMJZJQKtCUc+sLcYzqKm0Kk5qewJpBgRkzYx9aCm1DLTKZ7xgij9ZLWiqBgZAHNEok0hxAKRKqnLGrvAlRc+oIfrU1m3wTkAKTgaPuBG4mRzAnmukAvtxMr4d3U/jSHY+7g+kMhp+gO5hZZ59vBlfYeobBFNBloajG4ApYXnBGkzrm97tCL2xD56o/6V3a8FJQWGBzkAiN+rMlCxSJ1kStYFhQMZncApfxVyYeICacz0n8VQNLnbYWRJiKQ+srL7lhxyZTlCSWW0WETrEbsMDq4Ho6HU3CT3ir/nM2t+KBecl4I4wmoq0aOmGTpc15TTx+hcSTglpAiihqRBts/zHhtha6JHa1aVW3NJlU5/AbVTRfwS9KLoRz6L1hIuZlQqGjTcLkSXa5tVRURewuSsxNax5SpeyG9yahKcOQv99N+39E09moX8+IGh3lKIhlZPYMJ/3p3chf
*/