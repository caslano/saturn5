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
/raffby8R9FbBbd//9JEd6r8+840SnSXy62dQ+rf2bz+kWd/sWD/hTlbW/VK/3jc4TsDyXNXjI2n1oXOtnHvitF8vfoi6+LOdpmss2GmwGw4FbaW3N0jIfupsu9d0x+hs2FGQoKiM2l4InPYmg9XmKhrPJ67NZ6GPeEz8CT4a3gafA6eCZ+HE+GLsBL+Bl6ms1+u0tkvN8BX4G3wVfhz+Dv4os4eQjhvwT/o7KH34B74KfwD/IfOImoTIC3hUfBj2B3u1xkxn8AT4afwVPhXOAp+Bs+Af4OV8C+wDr4vfzY4miOF9yn9suH1njtvQlwK20ieBy+Ex2lvxUC4Cg6HF8PR8FI4Hl4BZ8Ar4VydrVMH18AVOmPncnitzqBCrFwH18J74FfcvRuax4QpPvk8Ufk8SWcAnQMje5UKZa+d7Hn3KnWXvR4qH8fAZrCnylsv2Bb2lnuTEaVyr6vcS4dj5V5Q7iXJvWS5lyL3UuVeGuwI02EBzIDuXga539OnPnTQWTsdYTvYSWcW5UPZZ34qcX16QPZ/CrPhg7C15JF03tdAOg9ReTgFJsOhrr+aEwJtffztIn8L4JGwK2xpcvkbmb/RXBD2sYM+jNwZlQtPg73hCNgPjoRnw9NV3mphMTwDztQZZvPgGLgAjlU5Gwc36kyz22VvMxwPfwUn6kyvSXAXPAfugefCD+B58CM4RfV0KvwMng9TCHMxbAGnqd5+CXaAJbAHLIU9YTnsAyug9avhTDgXXgKr4NWwGl4DF8C1sFbpVuRozgVOVLqnwRFK921K70d0xtnPYCF8DI6U/Ez4KBwn9cjewg1yd7Hc9ewttDPGOsEB8Dh4AuwHh8Fh8ER4OhwEx8CT4NlwMJwEh8Bp8BQ4Xfbeg6sdjd3hLfK3BVwuf5thrgvMkXst4UTYGk6GuXK3jdxtB2fBPDgftocLYUe4FHaCq+BR8DLYGV4Fu7jvF425YbpPfWij+tAWpsF2nvqQ/1HievhD1YcfqR5uha0ll78aQ2LPx9+z1M6cDZNgEYzkW5HsFfvkWw/Vuz46q+s42A32hcfA/rC/zhQ8GZ4Ah8KBcBQ8EY6Fg1TfToJqFzU+ooz7tIsbFN87VI/vVPv1PZXLe/Se/YHO3tsMp8L7vHsoP/Z/z8efAZcCx3ja/1LZG+LT/l+vcN2odFgHe8Cb4bHwJnii5Nwh4J5nVjAjo6Ezzdx7n1Y3ePfTv+fep7an1rv76Qu/8yn+rLTE9zw1/o6n/TDuHLVEdzzpfqcDn6t2uO54+q+/2+kLutdpNPWqFLEScRNiC+J5xD5Es5nsWUNMQtQh1iDuRjyF2INILmPfGmIsohKxGrEBsa2saQ9a09P0ND1NT9PT9DQ9TU/T89/7fEH7/9kncuj7/0N7+4MdHHftsDgQu4fwaK2/rd3r2ddWXV47va48FIBE95TIfE93rS25EfvO6q0na0/U9/fG7YnS3SrJOneum/amdQjoviXM626VUELXza52j2xIFF7Z6eaun39k8l3x95+59+MF/hzSf9ez1jx/riP9avTvNf0MyblNzOQn+e0ld9f8PzE/P2twH/n7ZuZN5FF35nruDawwfyY5J5Pu5J/dv9OuVfTOnXclnkVegojfK35x7oHPpgntZyM+MfeDFcXlW/TuloNft/Rfhzx863IHu36YaB3yBVtXrL0p7YVnZ/Qt//n3cz/Zs3/Cy4nX5fzXA//168b+640Hvz7sv9578OuNh2t9WPOHamtos3y+dW+p+cNWME/zwZ1ga3i05F1hrruup7ZA7cpOiD1aAh59O9wWtof5sKPmZY/SfGxnOBx2gZPgMbAS9oJ18Fi4QvO718EB8EbN396keds=
*/