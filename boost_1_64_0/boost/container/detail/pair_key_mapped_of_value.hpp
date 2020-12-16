//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_PAIR_KEY_MAPPED_OF_VALUE_HPP
#define BOOST_CONTAINER_PAIR_KEY_MAPPED_OF_VALUE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

namespace boost {
namespace container {

template<class Key, class Mapped>
struct pair_key_mapped_of_value
{
   typedef Key    key_type;
   typedef Mapped mapped_type;

   template<class Pair>
   const key_type & key_of_value(const Pair &p) const
   {  return p.first;  }

   template<class Pair>
   const mapped_type & mapped_of_value(const Pair &p) const
   {  return p.second;  }

   template<class Pair>
   key_type & key_of_value(Pair &p) const
   {  return const_cast<key_type&>(p.first);  }

   template<class Pair>
   mapped_type & mapped_of_value(Pair &p) const
   {  return p.second;  }

};

}}

#include <boost/container/detail/config_end.hpp>

#endif   // BOOST_CONTAINER_PAIR_KEY_MAPPED_OF_VALUE_HPP

/* pair_key_mapped_of_value.hpp
Reovv4e1igzr2EuG0f47HqxesRYyC8bfNUfm/I22ZzCvd80lpQSQYT+dS/eGnnvXXHJiJFnA/+1lun+wYsGy7zDWqWTo3yu0HAQcOZENyyWzmIUfTh4JKyYzmdn3F8AqyPyZbY69Y83/a5nURIYxW0nLJDu+Tm5hlkdjb48nrI3Mycz+bjXM2UJ1MruppH8yzJ/MZGZ/8xkWQsbb47WEiTj73BcWTcZrsddpWDyZrz4kKu2lCLO3g7A0YfYzW7AM0ffxbz/3EyxP2N4/HlwLK1GsSrEGX0brTRur81Xa9tl9h/md8m1OYfZ2HmaRmcwOPJbVCRZA5mJWF3DhK7BwMiezbcnX3w+LFnFB+yfPgyWRWczuHhM1C5YpailMuXEnLI/MzWzP/LFTYWWivfNXdN4DqxV9t7e7sHrRHrYTZPEtLO414/bYgG82j4K1CbOXM5jfaeofM/v7xTA3mcnM/n4xLIjMV84QYWxu48OUuAhRy6b+d4TB4kQtS3ctzIWlKO2liZw35RmhsBxhz1UdTIUVifbOvSMkvnc5a28Vbc/sPsAqFatWrFaxesUaFWsWZi9LsFbFjN99m4OZbM9UzKWYR7EAxYIUC1EsTOlfhGJRisX4bC9pehwZtj2vG//uaD/3CUsis5jNq5n/JixT2MGMMcdh+WQOZry9QjIPs9H9X5p81mYnV7Gcq43+wfY98rAGMn9mK/tdvBzmbKX2mNntwSwynvPcb4oTJwSyuDeMWTPtOFiwYqGKhSsWqVi0MHufCoslczKz7w+BJZK5mNnvS4Blipz2MgHLVixXsXzFCsnczOxrVrBKJa5asVph9r4DVq/ENSrWrMxDq2LGH7TdZTbi1fQJMIuMz0PqnePugQWJOPs+AVi4iAsacOgHWJwSl0Lma3lJI/O1vGSR+epfjpIzT9Rp31cCKxX2eu3MWFgNmcXMfs4N1kTmZnZt3aYYmPNP3xZIxvs3JWXLy7BQMl5L6PFFUbAYMpPZXc+OWghLJON9b99PY6zJeB/yDl4UAMsSFrTgWCKsQLEyUcvUV/2PYv9ezWopwHEI9sXM1sh9sWKNijUr1irMHheYcYb6wMw+74BZZE5m9nkHzF+xYDIXM3t7BosS7dn3n8HiyfyZrTq1tR8si8zNrHpFzD2wIpFz7OXfz4KVk1nM+HvvaskwLm8aMyfy96rUK9YozN6ewZoVayVzMuPvJ3K0eRu/PuhSLECxEDKLGe97lGIJSs5UMjezlx8d3wWWS4a+vyXfWaxYoWLFwvg8lCpWzk28V6xSiatWaqklczLj49JIZjGLuCp0C8z4L60PMPHOBzcZb4+/e9+fzM1s1sjZB2DhZLy9TVPeHQqLJTOZfZO+fRssiczD7Li5xAnLETbly5FrYKU8p3jvT5Wwc+v08x3rWf8K6ZqSPZ6wRsWaFWtVzPjLtzkUMxVzKeZRLECxIMVChNnba1gYmcnMngdYNJmTmb18wuLJLGb2+g5LEzn5/GWLnF/tPbIRli9y3vVBz1BYqbCl351KhVULiz3z5hBYo6jlzLhnH4S1KTmtv31boGLhZA5m9nYCFslMzlE0GR+X9m05xpqZnIcUJWcaMznvGaIP8/6avROWJ+zghjXPwkrITGb92g71h1WKuLf3jD0Kqxd2/srnV8Falf45jE5eFnA86CDMReZiFpq2Px4WLOzo0ncLYFFkvsYlhszXuCQxk+OSqeTMVixX6V+h0r8KpX/1ZD63kYo1K9aqmHGeb3Mwk+uDSWYxO5lZNxkWIGx4bbcesDAyk5n9TUhYNJnP9UjE2d+wh6WS+VoGM89T5pbM17auQMTZ171hRaJ/O6IH/warEDbdL3szrE4=
*/