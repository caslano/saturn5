//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_ERROR_HPP
#define BOOST_GIL_IO_ERROR_HPP

#include <ios>

namespace boost { namespace gil {

inline void io_error(const char* descr)
{
   throw std::ios_base::failure(descr);
}

inline void io_error_if(bool expr, const char* descr)
{
   if (expr)
      io_error(descr);
}

} // namespace gil
} // namespace boost

#endif

/* error.hpp
tVpRDU61wCM3n3CBr9bAtEm6PSqc9LiM2C/73qN7Jz0KY/Oc5yjfkpdPcB4wwpFyzcRNHnSc1bZbwDmdjjxlPPK1E4VyzT77RMEo6Dk6ctVF56p0yrN66ytdb4Z9WoaCacvVpj3ZZRwcr14gEDWr3R02T5EoJsTT/rCD3fWg23szJE9TE2V5RMdb39J4cKJdrM1S36Lz3ys1gMxoNUIhKkZJ8q4iVRn5+4uTF6Y7We0utIuqk0wJ6EB1ZH5byrkI/b6eQveTuI2OL6hbuGXq7s2GOSa+0i18IxkZIal1TftbacrkLGJqf2Ky9yXCFTYLsTJZpVf94G9XdWezEslOmypsUzzt9Fr9Np5DVtohXTgt1LhONShTrOyYr4cE6DdArdtKn8n9bJspN3BctKgtJFXlcWZ+bfSmAtemCXVjJW49GPDrR9mN/4VR9v+ny/+a6XLjv226/G8a7m5OS7nZ7hGVQ+LXo48Fa40Nc9+j5dx3fbHxnx4K68yoj+l4+UQefEnTegTbMuJu6lmP8j0rfTb1rUf5vlUhHOYBwhzATvZ0Dj5mwPWTh/WxS/CCXjaTXwoQ7mtnc9mpqooXrF3M2Kc5Gg0wUbYv+13MmKfdHiXMoVK9EF46G8HjZAImUTADgebt+4xefMEgcj3F
*/