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
yCgBnvMhPzuENwLPtYCfhPkDjw7yuxLSvAP4Yoi7AGSeCPRqoF0AHX3mUR/gkSEI6esMDxt4xdEf4x0EMVOO/CQPf2dz0pEe5uGIM+jEwTtmWNPFQz/Sa4RkM4/2VK8dhEw58oO9NyD5/GN5tvc1CJx1bI736qCRTzrSE76DfJBdhnbIFw2dNHtw53wnAqtloKO+a4DJOtjTvgeAOXPgA7+/A9txR3fmlwj+ZdKRHvt5IfHEIztR2wBJq47Fkd71ugAbHMmp3m78kteRHK8VgiOuOPqzveNAzLSjOd6zgwDrYE/4HjL2ydz7uPYFI63hIzkR/MRIrTr0Q8GfIOGUIz8XHAej5MyjPRq0g5CcwZ8OnmOirfnoDwhfMtHKGdwZ4VfAPPfYHRPiB4qnHc1JoTmM+pIjOyy0hPVjwqGcFy4J66f5DHxkeHZYP822v1PDCyFh4VAPDq/oz2QDnR3eB4kLhnZ8+Gx/+Q3UQN4M66dxBg8sh4E5c+BzxGnh1H0fzVHifBAx99idJnpBHJdQ3txsEaTHyS0t9GXlAu51rt7tsAheS7vghXuLxd/msEgfxrLg4/Y+S5ut02GxubywTOu2NDkcboutuRkSWyzllMNit7ktgtuFkSwKMLvD4nSDNKfPwh4oBvYF9FlGSIOvxtGcWJTF5m7GhBblFQJI7PPjo/s+SSmak1+gYXys1sKWeBb2jLnF6myxuB0O
*/