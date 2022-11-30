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
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
*/