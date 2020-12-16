// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/multiset_adaptor.hpp
/// \brief Container adaptor to easily build a std::multiset signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_MULTISET_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_MULTISET_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/ordered_associative_container_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/non_unique_container_helper.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::multiset signature compatible container.

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
class multiset_adaptor :

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

    explicit multiset_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef multiset_adaptor multiset_adaptor_;

    public:

    BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_MULTISET_ADAPTOR_HPP


/* multiset_adaptor.hpp
os/v2uKlKWbORd+m7nPxjM81Y4/0Bzvpnb5IeIQ8TWpqHavf99Z1LIrXVdcQlACMv5z375sxZoqoXkPDStvW0gi40fhBTk+5OFUu0o9R/B6UAb61rxJHI46oPTkYBfMwf31mJP4CE/874+da22vtp89Uf2jWf+Gl5+ES58s0Mh31pOdxnYlT02gQbQlx6zlmG/2pKab9efrGfJ2/ArFu1NnPpUtvKDPK0hs6r3GD59r2qYlrylHXtir9qqkbfaKsdlqln53lapyKXxdjf0afqCLKqhtGsIfF1Y0pFHcqbTSYEVMdawzctpm0yvxoEWkMrLSjqqQdfsa0iSZtipU2u0raFK+0fsd9Gn8cNWmvoAYHUhaBP7hvOV99G9c5CTH5pC9SX9rS8qu23306R010jupjrxGnrJl1jgqyr5X2g+qh9GKrPQZvTZU4Nmio61tr+ArbX1ll++YmqjCL9f7aLvVA8VtY5/9F44db+io+bdC6Ph408T42uhglmKudHeBAl9fjnszVzoJyrWP7XHoUnjib6lnXxSO+18V2+MHqV311SE41OPc2qvPt3c7M+fp9tP9r30qNNm7SObsWe5o4Mc2t8izKKJ2qAWO140XFj7N0WIYYfzxXw5omTZHG1Z5zMNxK09bSLBps/Az0BpxefWbJHGDiNIQDTJyrHBerDU21ttO62utXf7N+GnoFDf7p65fveHCIpWNujoll3vouJs+m3B8w++YdTZ9yf1+6kV+pjXyOvUqc3ZXlXlL9mKNS6+cDE/+QI5m/t2BPWdd1z7Ya+bvmWfeUfzFx3qFsgtERSNe5MWl97kczC4typQel8zWwBXFQi+hIWi8dHeu+M+MH6BNWdx3xvh5sj5AmtPqadI27w1paZTijKL04O6f6cTdxpQmvvjbG+J3NSNx7rBuhse5AaQfWcjT2vg9kPPvP9cW+41ZvHZ+0BqdreL/oGpe29NbwNuP5avTIFZctVPY3567PbemN+/TB2/3kayf5WlclX6YfLpiRl1fZH56DNritr/PTPw/z7kyTzzWpqzKbdIn8a/ypb+5usfjr//7nZE5wvJ66Nt1LFyfX63e2NHL+zO9jRutAc52QYjHr6njp9PxO2jbrYGNpmbSRlkl3aZn0gJvgRfApOBQ+DYdLC6VQWijT4bPwmInvmQNk29pvQ1iu/TahYUXAZtKuiZYWQnNpnbSUhk2MtBFawe6wtbQR2kjroy28FLaDKbC9tD7iYCbsIM2PTrAAxsMbYAJcDDvDtbCLtBS6W+9ka55M832+72S/ynGGwdega/lOldcfYE/4PuwD34TD4Lvwar1zP1HrJ8vPhhXSjjkEF2v9L+F+eCt8G96m5XfqXf8V0iq6R8tXwT/BB+Qfg1OtuSzOqY6jNkzzdOQcbys4WOV7KbwADoF9pH2SCkfAQmmfLDB9u3v/KfBeeIXKLdmhuR8Yqv0FwSTtL0PaSpNhLZgJg+XXke+pP121nabO0+tPP70Tf7G0mAbBJDhEGiEj4GB4GbwKXg5nwZFwjjSGyuBoeDscA5+QZtSTWr8ZpsLtcDzcD6+CR+HV0j5Ik7bBBNgATrQ0oTR/ojKZ6qMJ9aHa3Uc6jo9hV/gJTISfwgukvdBHvqc9V2i76b7tWZoz9aU50xReKU2ocWpfqdKEGi+NnKvg5XACHAPT4Dj5afKlUaT7edqSH42ia6XdMhvGwbkwAc6DveDP1H/MVzt4SPX/ejgF3gCnwV+oH7kZXictg+ulTbAI3qbztRyugbdL2+VO+Cj8DdwC74LPSqPgVWkU7IX3wH1wJTwE74NBTrcGVC24FtaHD+l8roGR8GGV/zKH7n1hqcq/PlyocmAb5rw=
*/