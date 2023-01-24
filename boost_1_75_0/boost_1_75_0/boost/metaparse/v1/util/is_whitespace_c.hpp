#ifndef BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_C_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <char C>
        struct is_whitespace_c : boost::mpl::false_ {};

        template <> struct is_whitespace_c<' '> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\r'> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\n'> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\t'> : boost::mpl::true_ {};
      }
    }
  }
}

#endif


/* is_whitespace_c.hpp
ntyQJ7g7/LwZv6mV4dHH3lsJn2aZ/3KZOr9blFwwRaOhlIjclNyv+PjexHlzloTOSZA3+VRGWGrUfDLSlmE8+hNmebW/nXxif8uJ7/0hlpL7C6jOVuEB0EYuD0jCtoH5zrZBf9LTeP1Pc0ncu8TkqCdhYeQ2b++9kvmwmxYS7M0ZiQIfPi4x6bj7eePj+pVrtEHhdJAhmJIxSu8+k7j7C/kfabqljDqla8Iz3o7PDvcEbFlvWB9Hmsi/DGDTxll61rDhaX5CDTbDPKNzE9S9oAgp+wecmsO7UUO77/ltvghkgz52nV2Zid0jbNLJOvskC6clxlVVKG3o7l6oxz3NlfBUSBt167R7mV/KNiW9ku10sNNX26bixB3bL1itbEPjXkbCHPNNcqiGLpaLZMIs9L0kA+ep9Oke/+ngOE1cRHVKZuoRifvNXU/4asqRqWHVU5KZySUFtn5HBrmcgQn5zMk9+pHC85rs4luJdBLbe6/SJ7+qxr1V5ktUL37V+CZEElo8HkFH039S5Dq4+ZNfDLbq2876djkMj+wmaPXVRJJuPDnp88XW2Sn4NJS4lzharv9yLezzS8vnN3tyHRjqdpwLHeikEPiW3o4VipjQ60MvtpNxuaaTNODCHD9UWzYrS6q/b3ix2sd9L+CrxeHH7GZZ0SO8QvoVk+Xvd6bPU+W/R9UK2xzeDRq8E0AeL61EOqH7EPsfAAgs99M5
*/