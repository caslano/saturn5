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
Ye38TbLayNMJM6bLg4qQRhq6o4HzGq1h+DEa0l51flqr6tOC6YFoHPglfE9kJPrEajxw6BZ4ATsOlwLRP9kAA8ror/Xz5UsZjJ2zvvL3smV1R/82KO8fvgRQLrfhuGDHoNYYEi23bfPVsg/BrPCj6eMh5Sm7LM4tazAbk5j2JBpVlvYmdHu0izap+6+Qw6ixiBkuR62dgo5KUxcZ/PLYPkSxX3pUMJXTTGq9CN0obtMBSUjDFCjeZMhyADHjjrqvgoH5de1chyAA2hVpYwPSGFHFQAHZpkm+e6+vy7h68fvjbu2DQs6u3jmDmn/nklx77dkuBuDZNOKAtJN58fprGxL+0NK0TW0F5xL+t/RkIaGNDBo/OyZseRcP9NwDCZiTQE/LCvM3K8cN01S97LOVL+ZjZfvCCMMtz9x60xo43FysNmryn4Nu6NtZ/jWURQesGqWF7XBtalno0RWqj9/bf9YzIvwSGKPTSi7CduCEBOfgRP1/+Ip5KLAQpdX63m7Xzjc7YA86PlSleag9fXs1m52bJsJey2UKzVKNdalFtXXQ/E9YNnrqf6XjlA==
*/