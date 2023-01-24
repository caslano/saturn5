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
ijKv/yoFYeFd7RC4v7IPNH1sq5kYxiHQJx64Aj/wIRGSTWHcqutpPF7MzFvfiMaX0cv2J8cLjBJWdtrW8LuFftvvFbd3iNu402ix+fYScXuvuF2Tyrc1vr1c3D4obhO+w+8Ovh0Vty1iHoj5+JvnZV8qbjuTdgksL99WxO0sanRtdg5ffkhczqPLr2cX8OWHxWWPaIzBBGudQvV+yqVFtdnFImNNA7mpAMetXJZ9LRBaayPGkUl4UcMURxRTE+lyzHXJ6qDLubCWWPgvNnbqBsr2QNak7fa/7jNtci/+sZeW773J1oSt/jH88tftr+qPwzJ4k6W+eE4cIOUD/SKxRR86o1P9IvV3pUiHctgn0qHMgckmxDGZGVHeJZ3sAOZ1n3mbeV1koYDXLehRPUPbno+FMDbBX20j/nkH/rBZ+bYmXdce2gqsZIv2cDN839goahs307XFzcy+mrGYj3GUVIRyUqnTa+Sy4lRYy0M/EsU5iS6Lu3DHp96NX4HonnQjfGp9qOLR9Hrd9egkOmbJsiXro/8KPxPkd+AOqzKD0UoQE0scQWV3ULmtIKjsCtgyZcXrKcKoZc6kGSicXjEvNRCdXhFQJgOHf2mFrOSRW1uTDJvf3XrH7ahbGOxtX2/FiPWGUDl8TUHHx02ha2R1wnV0ZxDekTC9be7H0FCxvLMr6qQHz8MHz4JrJXIZSBGTgQQ54AOY69RL5Ghe
*/