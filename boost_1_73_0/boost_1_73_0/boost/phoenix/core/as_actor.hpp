/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_AS_ACTOR_HPP
#define BOOST_PHOENIX_CORE_AS_ACTOR_HPP

#include <boost/phoenix/core/actor.hpp>
#include <boost/fusion/support/void.hpp>

namespace boost { namespace phoenix
{
    template <typename T, typename U = typename is_actor<T>::type >
    struct as_actor
    {
        typedef T type;

        static type const &
        convert(T const & t)
        {
            return t;
        }
    };
}}

#endif

/* as_actor.hpp
Vu9vqfcY3ltUd2C/dlVtaZV1z2KWPNdkOJk70Xj/FQDnlCQTQwbxpc8cFW+z9p5nyZ2JfHdYeX1ttYL0+4n3hMhTeMIQ1pkGWeYcD71bT+dtNnn+2SNatrbauC2desfQ5ON5JUuefZAnWjAqcO9z4PyUiDNKvrLoizrjhPeJ1aot8+YIE6MDvK+Lt9SrYxJ8Of/Gwhs+e0WXvVfB6BizRbIq+nbOkEEpsdJLAVm1/ZKJlYp3LU4SdUXdA/pqoK4=
*/