#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_IMPL_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
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
      namespace impl
      {
        template <char D, char... Cs>
        struct is_none_c_impl;

        template <char D>
        struct is_none_c_impl<D> : boost::mpl::bool_<true> {};

        template <char D, char... Cs>
        struct is_none_c_impl<D, D, Cs...> : boost::mpl::bool_<false> {};

        template <char D, char C, char... Cs>
        struct is_none_c_impl<D, C, Cs...> : is_none_c_impl<D, Cs...> {};
      }
    }
  }
}

#endif


/* is_none_c_impl.hpp
MLcZLyKhiRbgU76oJRA9CRnCPnogcoNDKPEc8VSgXGI3Ogla29B4fJ9Knu5unGsAK4TsCigXHH/GRcrkCjRiUpbpAjl3j7zzqB9jhMl7V/KSS/JmWrLGGHQY2WubYJNqcQ+0b7CGhiJv05vqKj1DDzXJuc0AuNiI9g0pUu39jHfiCfLnUNbHPgMhXE3PCbq33DGvCPoahC3ZEbtvhLcYtFdPU4fPwOsuvO4MREcEcxsRsgApABE+99uQLeDnGbKZArJF0T4JkEW4OhG8c7IzZTPjsYCsl+LoLgEwri9S+uAwr5SVQLFc1h+YvUuC7k3z7F5plRX68HjkSIElVOBt91Smhs8NKHKF7IaDYZIj4N50+ymBqAyQTglEU+TcFngacKMzCgP1gHjowBbQ0Y1jzZxkbxCFFEkr7MVU5Pn7pVWfrNN189i6UFamZkIft59f7v4xlF7uvuRYqFf71MqUcHZkMxeXGgrnYbn7MBKIqdhReXRoueT7XFrVGLNhgCmXuZiD0nGI/V5nNW6NjyHB5pHV7q1M8UmrMDLDS2OV6m6wYthBuc+9IQxTeLftCjpSvdAY7i9YDwdQ0em4cUbJ7k/mjaAhLbzIinQzT1Ynp2A6awBfU9twehNmo/wcVLJWZ7GAgTP8MZD7k7zzmOw+ODdPRqdR/aJ5Q2U19QIZg3zwv0UU03OIFIir+fdBKdJEhHY4EgctLdapy7b2
*/