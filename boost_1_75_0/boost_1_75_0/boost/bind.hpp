#ifndef BOOST_BIND_HPP_INCLUDED
#define BOOST_BIND_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  bind.hpp - binds function objects to arguments
//
//  Copyright (c) 2009, 2015 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  See http://www.boost.org/libs/bind/bind.html for documentation.
//
//  For backward compatibility, this header includes
//  <boost/bind/bind.hpp> and then imports the placeholders _1, _2,
//  _3, ... into the global namespace. Definitions in the global
//  namespace are not a good practice and this use is deprecated.
//  Please switch to including <boost/bind/bind.hpp> directly,
//  adding the using directive locally where appropriate.
//  Alternatively, the existing behavior may be preserved by defining
//  the macro BOOST_BIND_GLOBAL_PLACEHOLDERS.

#include <boost/bind/bind.hpp>
#include <boost/config/pragma_message.hpp>

#ifndef BOOST_BIND_NO_PLACEHOLDERS

#if !defined(BOOST_BIND_GLOBAL_PLACEHOLDERS)

BOOST_PRAGMA_MESSAGE(
  "The practice of declaring the Bind placeholders (_1, _2, ...) "
  "in the global namespace is deprecated. Please use "
  "<boost/bind/bind.hpp> + using namespace boost::placeholders, "
  "or define BOOST_BIND_GLOBAL_PLACEHOLDERS to retain the current behavior."
)

#endif

#if defined(BOOST_CLANG)
# pragma clang diagnostic push
# if  __has_warning("-Wheader-hygiene")
#  pragma clang diagnostic ignored "-Wheader-hygiene"
# endif
#endif

using namespace boost::placeholders;

#if defined(BOOST_CLANG)
# pragma clang diagnostic pop
#endif

#endif // #ifndef BOOST_BIND_NO_PLACEHOLDERS

#endif // #ifndef BOOST_BIND_HPP_INCLUDED

/* bind.hpp
AHciToG8K9l5TbCuzqP0WLohKvHYOHpuxHlu7bSuek2UXRKMTJKSNEmAXUnythEJ9WbCvzhvo5LujYppv1pWEJ9dftGG3GtHc35+ewcCfWdnSU0jMZFOJw1VOzNdOePsnIKKm4/bo44eUe3DJGN8W3uop9zd7sN36RXLHbzTq/nl622yM4LaJEzYLK1kHKIUInztBrouo4SZDjputjYNWgbp5N/I+Ga89n3zBH4fzuYLy/FZYGOjsTbPS8AT0ugB0qiHOEsh4mRD9q6AzwyX+PZKNumOvvbYoD8ospPgwHNl8qFJF/+QU31jusDmPI79e+H3OYmz4OvtluehmhAPYS2PMrnsVHRU5Rr+MjNPq6OVxIDooyO4uoTtCZa0cu3YD5GWLD5rP7v62096WEKdCsiM0bPYudHfUK97Dyhy9KSWZ1Y1XF1yL7btwIP+2dL9xYxZxwS/T47VGlzK8HDZEBsj0llEa9vqjkdGxYxd5NrEyKTleZIdOWn5icvMlGWOaCuP/LioD09Hwv4urc/DU5fg5CyUz2GkiXNXmyDCGmnQxXRFzIGYyOvnMwznq6j3poLtRfCfeqsnEbydPS69Zkv5vF2rixq1F92UFlWqqxrLpBEGF0aeuSQl7cXK2NlUk/UjIiYReSyWqyYR5qDhHpoaW9uOPpKYZnpD0E919S5Dd/W4auHW/ry1PYUzSsnOUF1//BG4BCqk7tE/
*/