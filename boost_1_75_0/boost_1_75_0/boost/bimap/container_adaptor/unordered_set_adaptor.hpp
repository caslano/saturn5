// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/unordered_set_adaptor.hpp
/// \brief Container adaptor to easily build a std::unordered_set signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_SET_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_SET_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/unordered_associative_container_adaptor.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::unordered_set signature compatible container.

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
class unordered_set_adaptor :

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

    explicit unordered_set_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef unordered_set_adaptor unordered_set_adaptor_;

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_SET_ADAPTOR_HPP


/* unordered_set_adaptor.hpp
IRttH9RoWN7GD0I3yvaehuqikIgbh7ePzCTxyS/wDAIbZVAQo3WSB/MPEcgHGFCeqQ2Pw0IzCZIhkf/h8oaR/7BZj/y2x8yBnqWYyHHhKGzW3OBFG+dtIk6vdBMIIDD1T7DvdGU0B/sEDoLgSO9jBLwnAL4ZhDfyMFfpL7ZwZP4ZiTEJhSeqSOHWDTOBMulmuGDkuV7No8d8ZN7G90Nj/m1WbTX6lHwDG+hHhd0bgoovZcWr13PCAC8gYKHFOJYNd3h0ScKa/3Ik9CIMtkkFT/PdUeghSIlsZAjiP294CFpGBtD/kcAhsObn49XVJ9j7qqnsZ54/AqHJ1G3lj3Kx6QB/1pD49OgZUiqQ+0G8/LFfvR5xzduasAkZlOJ9XP2Rqw2+4QiKqKuKdc6C694KKnhniILlh7Fgrr7g+uCC3UIUnHfYrKJNytsgdgu7aLfgepyz8a4BBz9i241GO2EGddu9MkLDUYlBO63ViZiDawlHS/mwCGDb6YBFm7ZJ39QH9tgh7OUr83W9/PbNoILJIQouPWRWD9ngZPAptEnTiEOUPf91gFnaJCzGT4x9BDRsA+bjNuDq8VCY7MmeM+ioUcVPLq7oX3PsvMHF/UFYK5VbAOL+ZGG5z2md1/+v8fhb6CZIySxuszABQel2qzFAErbm34nqh9XfM9p14X6sV7e/zKhlEuKwEOnZxmBqwMZgJ+u2tjHQjx4btWV/
*/