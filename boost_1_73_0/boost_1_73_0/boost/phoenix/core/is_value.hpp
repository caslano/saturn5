/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_IS_VALUE_HPP
#define BOOST_PHOENIX_CORE_IS_VALUE_HPP

#include <boost/mpl/bool.hpp>

// Copied from is_actor.hpp

// Note to Thomas and any future maintainer: please make this as
// lightweight as possible (as it is right now).

namespace boost { namespace phoenix
{
///////////////////////////////////////////////////////////////////////////////
//
//  is_value<T>
//
//      Tests if T is a value. Evaluates to mpl::true_ or mpl::false_
//
///////////////////////////////////////////////////////////////////////////////

    namespace expression {
        template <typename T>
        struct value;
    }

    template <typename T, typename Enable = void>
    struct is_value
        : mpl::false_
    {};

    template <typename T>
    struct is_value<T const>
        : is_value<T>
    {};

    template <typename T>
    struct is_value<T &>
        : is_value<T>
    {};

    // This does not seem to work.
    // There is an alternative in value.hpp which does work.
    template <typename T>
    struct is_value< expression::value<T> >
        : mpl::true_
    {};

    template <typename T>
    bool is_val(T const & /* t */)
    {
      return is_value<T>::value;
    }

  }}

#endif

/* is_value.hpp
lMiuROYrkRfz9anT6fRq//A3oHHwm6A0T2Z+UORTCyx+VTAQxzAzFyqP0wkNR4N3pDBKxJqKJ+kacMSyPkxFSq/3X52+eXV6OHitoyXGcSoiD4i+ZPgAw1cSejQQcyl5QuUiiDgHmQgSuo7TyziNWF4UiBlCPBUJ8ky9QmU9vOpVNq4b67WY6zhJKAhDAeBhhfKaVYwUloMwz4ESYOkaoYerCPzadRbnWJ/E2YRPKriyKwxOUhgooUeb/f5P7Fuv0/nR+EL7w91Xg31/7/R48NF/f3w4HB00wsxO3iC+1AP0MgvJeRZfBQA4ggD8ZNRKzETkvDw5J/UkFmdis0Tl5EzMInFZTNanlAQwsiWlfunUpg6O3hwcDvbJSeSkx/n1OXZPkmgdE6ALERU4Ow1gksEH5hn92yU8jgGXLOVIoi4kMgwY9pfFeIyE6GDCtTTXhSITjGeBJy4snM84nRc5S7EMUIeI5xrymRU8PB0MeB3JQhcouCGzW6aMYl2fdOwVywytoZVG1zwDL8XYAx7/JfwcOhORTvJpt/O5Q5YDskGyXT2n4to+WyZM8KgxA5a7Mwh2Ri+o35iNPZJmqgr62/2P/sG7kX8yOiZyzvo3T/qbHy+c1nu88wf7Q6Kfq+nh0egtik/JZh8bfCWB
*/