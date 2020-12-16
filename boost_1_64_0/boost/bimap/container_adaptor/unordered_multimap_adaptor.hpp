// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/unordered_multimap_adaptor.hpp
/// \brief Container adaptor to easily build a std::unordered_multimap signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTIMAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTIMAP_ADAPTOR_HPP

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

/// \brief Container adaptor to easily build a std::unordered_multimap signature compatible container.

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
class unordered_multimap_adaptor :

    public ::boost::bimaps::container_adaptor::
                unordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, LocalIterator, ConstLocalIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type,
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
        BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        LocalIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // MetaData -------------------------------------------------------------

    public:

    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::second_type data_type;
    typedef data_type mapped_type;

    // Access -----------------------------------------------------------------

    public:

    explicit unordered_multimap_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef unordered_multimap_adaptor unordered_multimap_adaptor_;

    public:

    BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS
};



} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTIMAP_ADAPTOR_HPP



/* unordered_multimap_adaptor.hpp
zjzlt8qnqbXzLTOj0X/R9NsqvhHzuZYmNdb+8lW6/I30ed81M1OcfvzPIf+T0NuiM32mH0TeR9NKeR9XHpT32mtQP++vwn7NX+PSKa7P45/3sodruegPMH2vLeW/mfv8+Z+n/B9gal73Y8tA2xb147YGOyt94qZ+U4J4yY7K9EDTlw3v9/6HEKdImR5oanI7Lj67W7jxcPdTX4v5tfHxaUSfK2wnI2H7Jf3PFZccxSW+vSEeOn/BP182+MRD/bRE8ZCdTOSRfDEb0fOtDyFPcmLyxNyNHcNk+cdjk0881LdL3GbWK1+y4T3j5BDiElu+5HZc+RqdXT8+azG/zSc+qnIJ4iM7ik8/05cN79l4hyE+/UzNdTumbeuQUz8+X8X8jvj4xPUp/eMke4rTSabv2oqegX8Y4nSSqblux+TRmz5xuh7zu+PjpL5f4vjIjupOj8h+cE9cdh9CXCJ1p4epmbsxebOtZf143IDZff7xUB82UVxkT++dXoqLa4vHPZvtEOIUee/0Upxc9+Pq0dpW9eO2DjvOZ/Xipn5wonjJjspcH9OXjWicMPP54xQpc31MTW579tFVBhLvQ/Pff3Xw+6kOdh/dwe5PS7QPrfnSkPqSHcfl3T/n2J8MSrt66/tHvtHl4Pfp+e+jS7TvLvH+NJ2PoLlQ0hGxE+E9H6GfzsnoD3vDAbCfzskYAE+ES+AguFznZVwEC/V9/WB4i87HeFjq78HRjuYk4Qj5m4oYgnB0zkKIPWFLyXNhL53P0BsOhX3c/SWaK4Qpcs+7v2SG3JsJk2GZx16+7CX72BsueyNgEhzp2kM04N/tsvdd+XeHx15hA/Yekr2HZW+bx15RA+E8T/YmK5xTPPZKG/DvPtnbIv/u99irSWgPuey9JHsve+ytbMDeDbJ3o+yt89hb24C9X8reU7L3K4+9DQ3Yq5a9+bJX47G3qQF7F8rectlb4bG3rQF7q2XvStm7SvYqETtk717Zy0QUy14b7R9rC4+HeXAQ7Agnwk5wMjwKnq9zSebq/JKVsABukLr2u2nMiz/yz7vfrULhrFQ4Z8MMOMcT3m2yf3V8eLXPsx08Q+3BGJ0fMhaeC8cpvJPgTFgEl8Lx8EKdz7FS+govY7TE4b1H4f2+wvsDhXeTx/7KBuw/KvuPyf7jsv+Ex/5a2c/wsV8s+9NUv74E02GJx/6GBvzfKvs/lv8/kf8PePOrAfuvyP6rsv+a7O/22N/WgP1vyf4tsr9B9r/tsb+jAfvPyv5zsv+87L/gsb+7Aft1sr9I9hfL/hKP/X0N2F8l+xfL/iWyf6lrn+ezxPavlf3rZH+t7H8FbsDSlu82fg+hd//gXoT2DGqPYP39gZO0L5D9gOwBjN3/dwdiU2S/X6HOJPHZ11eI0H4+d//e3fADRHSPnvbn1T//w92PV4Rw99/53e3gOZ9jbAP76opHY+5L3AGLKEIsRdyEeAyxB9GshPMzEEWIOsQ6xFbEbkRyaYaTjxiNmIe4HrEVsQvxGSJ/eoYzAlGJWI3YNL1pH97hfr6g9f95s2cc+v1/nZ1mNmc/6Iehd21Z+azpi+bVlUSGNfPpyoXPAEjtQH8wcmeX9gjkee7HLyxA/MUdE+kca925FfcNE+Zivr3cfhD3AuBe7DePClOB1sZTZSkFUUKYSt0w2XUFtZpMw2/3+yqFS2YTrwNIP3jAsVmL2O8zE86h9VfYn9fC6zLC0F3sQNhromEv4+OwEfQLPPeY1bpz2neaucJA60Ce4hKxe5LFpWcr7bfwfJu9PqRPaAYHktzv+dKdCnddZIPpD+Vc/CvcM4iveAc1vv7I5XvENorwl01tFu/186RuhUNmZ2C6g8f9BdE=
*/