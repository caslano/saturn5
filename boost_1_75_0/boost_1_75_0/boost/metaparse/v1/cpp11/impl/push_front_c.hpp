#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_front_c;

        template <char... Cs, char C>
        struct push_front_c<string<Cs...>, C> : string<C, Cs...> {};
      }
    }
  }
}

#endif


/* push_front_c.hpp
bx8q0tFcdRavyWWyu1d4BuWX+BdmG8J6LND50wnf/5Twfan4rrpaM4l/W62No/ggqfZ6TMDyuhVkjVeguZrCMeESf60eTveugmvVKzlMxRWABmoKxoR6i5HGCqjv885gVlt0Mwp+5jb6MELqferkCg7nrf0FzvLYJGx3IogcNQV3wRbR343l1RRUh3O9kf3W8GhvzS/W8EicqzHCh4/yy+/AywJOsjLC+8ZogISvID88WHe9errR/1KLd3yTSBf0xOndhrFdzDUMLbVRMDgWqAB2yVLbwIUK4GXMsg0vz+Iml1piX9NTElkMGuXcXkA6Rkr3oRpTacztFSxrCSq9OIOqitnK38glR47sSEe6VIuRwpGOwVJtAX05Vao9h74US3XD6LBc6AioM/AcOA2dab4LKke8hYsyF54aIGnt8h3TlPSDuuvOUdTmHK++ERh6v/umzAVfwKP86oejreQBVUl+KzDNG7t4mpRhuXBEqD+t0b05vPbuxjCg22zAteqVdCOcYwDPU1AQOnep/9W2WngzEDmmhx6HhqtuxA6rr4MhOS9Wxh6M1ZOPX2zwO70tKTVYbqwItkw1QBm2TRTDUxt0lwXONTq2UHFjJMp+7SmLxcxh3636QQIP+sQnwINS2kTt/HTYuryLz6CvdBSNTE/MkyJ46FI5UojhbzJlow7difnrdVQHvT3Kyrv3RVoj1+dDhGfO68YNqkpP
*/