// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/unordered_multiset_adaptor.hpp
/// \brief Container adaptor to easily build a std::unordered_multiset signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTISET_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTISET_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/unordered_associative_container_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/non_unique_container_helper.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::unordered_multiset signature compatible container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class LocalIterator,
    class ConstLocalIterator,

    class IteratorToBaseConverter        = ::boost::mpl::na,
    class IteratorFromBaseConverter      = ::boost::mpl::na,
    class LocalIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter           = ::boost::mpl::na,
    class ValueFromBaseConverter         = ::boost::mpl::na,
    class KeyToBaseConverter             = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class unordered_multiset_adaptor :

    public ::boost::bimaps::container_adaptor::
                unordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, LocalIterator, ConstLocalIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        LocalIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses
    >
{
    typedef ::boost::bimaps::container_adaptor::
                unordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, LocalIterator, ConstLocalIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        LocalIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // Access -----------------------------------------------------------------

    public:

    explicit unordered_multiset_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef unordered_multiset_adaptor unordered_multiset_adaptor_;

    public:

    BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTISET_ADAPTOR_HPP


/* unordered_multiset_adaptor.hpp
s7Bd96+MfEcqO6ebO23l/nJTq2TcdI7UY9zHdBuP+zXuN5U3ue5frTMVIu4PMXdy5f4FpjaHcjxR6jHuY5q1IrlPqtbOXhya/ot+B367+TM8cGwgxWtu0YywMaUdfTNzLyn6bavJgwobNVXyXH3Deau5e3rgLr6PHRAgJtSVFg7lIzRWz42Kyz3yy/j9UVZ9cUz7A+89CX3zTZwj33xbGS5061utvnPW3HWKO74h9UXKa9E+t7zaFppoHcM9ldU5ZmadymnETp7kpMC7yPnzfq/PmRZW9y8ys5c6fUiLTOR/a0k65eBGa77d4XfLVvGicftuWsR8110reaS+zrbvO28wv+mjumffqy30WX8vxUzfd920sG0v5dUVs6vLfdsdzDZufTS+XfG2IWVac28nC20RM0Jtclw4KJVqQ2LCIHPtrAy/0AW9uDI8xt+M6oPuJ4maaXRc1J67c1e4i9z129QxInXXv5i4z0t376uxpwBRxr/SuLjXLKjwi7vMdUXPjZfi7Ke3QHH106vQN7Su3kGnA3JvOiD3xn+ByfNdeUXsnid15XrqvdxVZ/OsjUmHEr3k3Re8+x5u1sGhPzDR+gO1S1FI9e0PuOuiG83dzIbe3Wdmx72nd2bU7zvMwr8dsWEsX6p1YJ/6IrPZnvf07LKlUO9p6ee58ZrU+sD9C9X5mHf2ILcNwP24eJRm1q/3FaE579h4KNH847HvEOp9pC3epnC0VXoeicgu4N97kXDYdgilBfodDpwW3niO1tr7N3XG6VpYifv5Me4rnjrP5rUcBz21eDyKr+zkuudJDDT5pYGR/F+PiJ4/rjNg9M4Ya+ZmB3oSrosQudyl9BjxvvQI5lOJT9LKzdyf1KyZpxzb/Uj9kR+hfRfFiM9ahjkdsZnYZWEuG3F+67D63e0PrvzvtHBlHnAtP/RuvfX96Ls1V+9W0on89KQT75kVmNN7JmYd4jPlw0Tl8Tj1uft+4ObDwvKZi2pn1y0Ld755fNo6mW/j9sNGmXww5SlF+xSiZzHktGn8uxN/6r2TRmiNe7HK53TEXMK8wRtmvZO89cO949jMjeF8lyMUftlFRX0tv/eUzHR14/i4yYuwFZC92HeXe+eymZvgdCQOauPlVift5VWf6qD7FLzf1J7gd733W6HUE73fNmiN/RadH3EVoir0bv/Qm456v3nbGaVjqZmbrzSM2MtXv9nzvpOe986UKpNXyKzef0qvOXJXaSW7PWVW70PlwUzTu1Dvx4jZLpEyR5p+/rRF7k1b9V0l1ztztOTx78xBWfXPs5tP2mZ95E3b+Hemd69bSMlt42Qv/YBteuxeN3Mjpt0dkF3/PbkAs/mecB3gPYnZBt+T0s9D7u7tqq2QfpHse9+jMw7Te1R7m7TnCz/j3jn7FHd3P7LG8oWxcddI3jfuMpucaCyPfuP2KTd2LB8Je9+WmtPWXrXxiIWEvSgm7CpHfmcvqc5WmfmTFJ+I/Y6+5W6Mq5/n1rc5Jh/mmsdFNqlF310Vpp8jecBZZvIMN69vPYi73uPP1RsUW67tvbb4I/e9ZvL1Hrm3P1On9fYSlfupes/t8KTf7AvKY+ZBlEYyk53w7p2eH1t/K2ZsmSO9t83uYMpaX7eMHP1xdF/V+1ZK7DoRO88pX3lX2cHUF80KyUmWItetM2Lep3txkKBZmo4+QHkr8oy7c9Tfx3/k+O85Pwe/UTO/Y8tg6/pzYYtCZTD6DU9d+UJVIP9+AmYbnguTfqPrz9S2jZsL26uwD1H+n6gz1EqjYWcqrLZ8llvvY8qAzOX5zh9cLD2VceYPDrY9qzc34O6t2Po/fEaR/10r//qzi/z3ehz8npFC2xvyzB+6zDs=
*/