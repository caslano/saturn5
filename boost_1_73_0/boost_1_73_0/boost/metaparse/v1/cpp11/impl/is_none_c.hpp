#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/is_none_c_impl.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char... Cs>
        struct is_none_c
        {
          typedef is_none_c type;

          template <class C>
          struct apply : is_none_c_impl<C::type::value, Cs...> {};
        };
      }
    }
  }
}

#endif


/* is_none_c.hpp
dxLDwrZU7aE9VEpC7My8ee/NGBHQByU9DpnQJrf0s8bDzrrMD9l4uZy1D/jytIwvtbP7A8ttWdpdaZUM2hom+DlH8AjDPsMC3RZd4nWGTDisywN9zmSQEZmnvRTu+yksC+2BLgk71C6zEHAfoELv5QrB7/yb3RiFLOINoKGc+HbBc7lGNjkSGQDn3la4K9BhD/eyqkvsKVvxtjpP79MH9mhNQBOSCZpVKAZwf9dsGVQRQZXWI2NzzLSjPQhEpyAWskJ4mU9ArqQ2n0hmFBIFpReK7vp9sGud0f1rxj+SeLjGobL2WCc9FVIFqvV/YN8/deNoguDHmaJReyx1AxBHTbULCog1hqwIoabw0xKEoW5GF+EsPg61NityknOadMz1HjPYuJJSeMwBQX5U0mQRdcB5rp0PdSnVR8t20oTWMUgmkOzhGN0dTxfL59mg2xSfTedL4vWOKHKUYeOQjlE8Z4KfdyjuqIv0vqLT+QEaN0DmAV07pI2xUEgPb4gGbnxhww0T2zaWAAgzWGXLIaPjDH9K/9TKDhtbH8imqwkd9kL2JqMVMaSWkWe8+/o0XzxPv3XYSCmsafuW33bYrFGWXDb4K2KdjEq9xQ7rXHL73TD+xO1qwt+jJvjZQsHffeXn/9DvUEsDBAoAAAAI
*/