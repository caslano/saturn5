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