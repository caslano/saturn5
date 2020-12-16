//
// ssl/stream_base.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_STREAM_BASE_HPP
#define BOOST_ASIO_SSL_STREAM_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

/// The stream_base class is used as a base for the boost::asio::ssl::stream
/// class template so that we have a common place to define various enums.
class stream_base
{
public:
  /// Different handshake types.
  enum handshake_type
  {
    /// Perform handshaking as a client.
    client,

    /// Perform handshaking as a server.
    server
  };

protected:
  /// Protected destructor to prevent deletion through this type.
  ~stream_base()
  {
  }
};

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_STREAM_BASE_HPP

/* stream_base.hpp
uieoG7PGUhfs+pax3HvWQmnKoXlK1pGmec5aFCjNLmjW5EOTXJ6ZmpqZPJ3/Y2Pox7JwCWnuN89t3Rn03MPQXGan2asx9lxi9Ln4U/H3IY2vq8vs5N6eXW/Rk2u+V2zqrakrgft9E7VuHpcy0fd4dXPPpP/YJHVz42Z75NG+oZhwzhmtdLyXKF1ep22bkAZyaBr0oRWb3PPCc1WuteO9dlvCZ9EfbIrZbZlTumySbUR4wbxoi6lvqauz4mXbCXsrzj77DZ/nFdr2w/yf17JZdTJkmqc/g8dt++VjnZAlph/SU9svbn0cOcMrXzb62OcrnzFiIzK+5mPDBj5jwyac5WvDBpqu27B5zceGDc9JtGFj9L9vgjd/OeTvkH/+WiI1gXlTnlz8xq6ZeV9Y4og3bbaL+dK5sdook2e48rT9TG+ehtv2aH3zdGVFXUt1UJ2Cx3kPgNsmcD9Q4+N9zCnkyVnn3HaB5RmuseykT556wB+uc+Xp4pXnzyhduYIhrRttM1b3D030PjONZxYFPdNRP16Z4tUlfEaXxd76QXzX6wfP8+iy2NQPd76Kz/LmaxD5KjH54nh4bKrYDT3G6mNOkfd5A3leo9/zHDp8watD5cnVcd2rw8Zu6PAFHx3yDNWh+11zn0+e3rDte8XzdElJ2YXznTa9fj3Vp89OkLc4u/Pykp7K69b3oEle2U5Cuy9RNlO0p162MT085vOs0dNoO55nMXSpHkZ6+xnouz52kZ7qwS3bjsle2f5onylyy6ZVLrCMlD5X98S9de5EN+ocz/PUOZ7hW+dWTfHmZ6zdB25250e79CBdQ99un0581/v0kZ3o02P1dMJUb34GwF9k8rNwwbIFK+YsLVs258IFUkpB73LKk6vvkp4yIr7rZcTzPHniGb596yGfPL3EOFKyOcDun6NdHJ7oyRd8XW8XpOc7p9szzSvjEWgbg2SU+hQsY2MH9amxG/Xp8MSO69Pk2Lg23Zuv44X0se58oXFt64U+/XE39E16vv1Q3tleuR6Edp9LLjN51vdmr2zQm7nzV/3tP0LT9bkzz/TMnb/qtf9o8nXMJ1+vkK9D7nxp7QnW+aEO6s+hbtSfXxd2XH/Ga362zvC+kz6TQ/8ezY/9RioyHsrxvI9Cc2rvo6Theh8N1fuv6U19S5R7na79X6rfRITrozJF4nv+lXxoWN/SGHwWarjwXKAyx9LITtjr7PBevYBzDe668aTKnadMA1TuXR65ZckpcH0ZeqNXK1ie4G8QVB5rdpR4P2naAXvBPvbZCbc8lTXVlZvMlxHBewTwub+F+pb47w1NsZJjNpv5M+ftTBlkN9p009Uf4vt7Sce97qVrp+MbZJ0rlGvswnvtx68kzb5CN0/WWC/KErqqsoq6jfww32wOFpoioYHX0GC+W2gaoBkrNFNDsXlOOjQQmjXgIomfTBrzZP9VxjvyLfe4SlhIwkJCVxFabfUQXfSRMdEo1azVHxDeGmuG7NyLPvQZU0JDWPG+k/W5F9BVblQe/vjYoam6vplP25znKRYJT5rR8TLx9/OkmWflx9KUNbwDb4kanvm2fPvT2qr9i1lvy1WasdB8J7redltmch/PetoQpdsF3aNyniE944K0lOSctPTMwn6W3/ePgecmvvIP9s4EvIrqiuPzskCAgEkIYRMIGFZRAkYURQ2yKltYRQuSQKJEAsQkICLUoCgoWGmrFosLIlpUVLSiWKlNrbZYaaWVVlRUqtS2trZYl1qLbX9z3nn3zbyZSV4A9fPzzffd93937jl37j13m7nLOZLW0Z764dx7cKVjz8EnxNWRdCzD6T3BSzqqP461JF2zCGw7xxaqbrIk9DGCZWCmrfs=
*/