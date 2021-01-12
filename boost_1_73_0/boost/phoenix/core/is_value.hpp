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
PglbWIZcv0C3NsETqWsO+LIVX/fh69g5Oan6Cva9ETsAf2cRo9fA5reAN6aB5Lfx73b+Pdee3DQTNPEy3CoAThMMH2Lc4ytgL7nker+Hx2A328ihF4LZ/vD6wbXg1mfRm970n/HOYa4eW0A8kA7fYY0ggzn+IYV4JB/+hxx/s2ETtJ+2GY7iA87gy8+G0+4GuFkveEcbMLA3+0KwpVUC3dwBJn9JHqeiJGTyCvFl4A7lyM92
*/