//
// detail/macos_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_MACOS_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_MACOS_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__MACH__) && defined(__APPLE__)

#include <libkern/OSAtomic.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class macos_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit macos_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit macos_fenced_block(full_t)
  {
    OSMemoryBarrier();
  }

  // Destructor.
  ~macos_fenced_block()
  {
    OSMemoryBarrier();
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__MACH__) && defined(__APPLE__)

#endif // BOOST_ASIO_DETAIL_MACOS_FENCED_BLOCK_HPP

/* macos_fenced_block.hpp
+Vigm/z5d51Lhye/5xp1uIrxurDeOxkrHTP8+fddow7vg6x9KnzCB+bE9hr/E7VHe9iz/G/PrA6vQr/Ob/BnJfTq8G0YrcOv/cea0+HPfeh51OE9MEs3eKv/Opbzhi/BRh2+BYPt0+JHN3qn2Z7+l0k/xKxlPZs8DzUdfh6LdTj7kfuow8OwWpf5z6g/1rPJ53xsTejweWjp8BabdacNOnwqsst7NvnnGKbDs9Cnw9dhrC5/ojs9htzjPZt8yubdaW8d/hGKOnzJgO40UYf/gYoOD/hkd5qtw91YoMPbYalu8h4Djc21hPvRZZzhl9GrwxcP6k4FHV6HcTq8+ZbdaZIOd6Oiw5/HXN3mb3YYm2sJv4OpOvwe5ujw4K7uVNfh87Bch2djlQ7fgLYO344u4y9lXEe3cevcp7rTftnulFxLhV/BOvc6beU6MOgJa5VvwBD7hO/GcB0+7tPdaaQOn/uZ7jRBh+/BFF0a3J3uwvqYN577ue402jGzW3ennw7pTnnd4q7Pu7+6xodtZ8y6wVv0dKfpTxonb/cFn7e9xHdv757aXtyhO/12mM/qwo7mcyfzrIucen3W/mX+3JfNpy7wZViow2/sbC50eLNdzJuu8DqUHSc7vDs1MEu3+YBdu9NiHa6hocMvYpXO7dadSligy/wu2jp8yu7GtKJnky/AMJ3y3Wky+nT4y3tYnzp8IibpBn93z+60Ulf5PXQ91bPJf9/LvdDhjzBShzN7mwcd3gplXeF+VBwn/ORXzKcOv46GLuzjWdvX9esGD+0zhz4b7vyqa9bhHbFUV/jlrzlu9Iju9BJyT7uu/bvTgQX33fbiQd2pil7bm3z7we67Lo7sTtOwWIcfxXIdXoOWDr+HDTr3je50LbqeMTY+eJRz6TIf9E3XG8cf3Z2OOsS91uG/YooOH36oZ0eXxhgP9vbZGrcwUrf5msO70xidjvAOwVjdKLo+jNAt3vrbnkdd5p8c5Vy6wVuOtU+zZ5P/iKIOv4aJOn+0tY3FOvwAGjr8BPp1uIm2TsdYFxjwrLniR9Clw6OOde06fAz6dI3/hQ3GEz55nP0dJ3w6hukap++4fvvkeDrm6PDVx1m3Ovwemrr8XXOCis+GO8d3p5k6/FnUdIFPxipjaPIazNJtHnh8d1qis7wTVus8j8JcXeSTMFWXeQYW6irPx3Rd52WYrJu8BvN0mwd+z/tOZ3knLNJ5PgrrdYmrWKdrvPv3u9MKXeIlWKpb/AHG61TyrsAYneN9MEkX+BhM0CU+B2N1hf+F2kpzzkf80P3V4VPR1G3e5gTrUOd5xwnmU5f5Ssx9vodtP9G16/DuWKFLfDPaOpw/yTv5Bcfhg9GrK3wzxtkn/JWTrTcdPhAzdZnPm2j+nbfBh57anTbqJu90mjXwXM8m74aaDt+DxTrcj5U6/DbW6dKk7vSZ063PP5sffgcbY95+1J2eRZft6QxziME6PAlDdXh42TOow3tigq7wykCHjzzTtetwA13OG34KvTq8BiN0+K0fe+50+F1M1s3JrvFs8+Z6w7shq8P3oFeH+zFSh9/GeF04x9rETMep8gpMMZ5wGxUd3u4n5lCHF2ORLkzpTjv81DHdoxJve65x6go/iLG6ydueZ73pPI9C0f0q8knI6zLPQJ+u8nz06jovQ0E3eQ1G6+rU7vTJad4POs/nY62u8Tto6fr5nnGMd97sz6wTLNJFPh8TdPhPmKTDZ1c8jzp8IebqJv/tAsfX+Z93p++g8Bdj5msxWtd50oWeN/vU+JTp7m80v4Fkn3RRd9oeRV3nZcjrJq/BEN3mgTPcO53lndCr8zwKOV3kk9CnyzwDg2Kfi7170dJlvhT9usY=
*/