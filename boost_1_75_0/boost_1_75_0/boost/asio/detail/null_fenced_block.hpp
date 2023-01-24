//
// detail/null_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_NULL_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_fenced_block
  : private noncopyable
{
public:
  enum half_or_full_t { half, full };

  // Constructor.
  explicit null_fenced_block(half_or_full_t)
  {
  }

  // Destructor.
  ~null_fenced_block()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_NULL_FENCED_BLOCK_HPP

/* null_fenced_block.hpp
yjFD0ajh9zImasqIPKOMy9POZfEJKg+l21cngigSSdJ2hiph/3sOQrrdxLnHwl33MWE+1hQvhtfhjir3CJkMftFhF8nZQ99JIOaqAuHz0KlYITN37wZM6al0EYKLbYspdY+3UwM496sYqoZvZhkI94tlmLqHb9l8vRj+OX8VttUzPyaSutdDEINZO4lm+pFeCkaZuOYHrVgRtY32gXbdvAK8OucZDzGv6tmDI2MHS+4nSAQ3QX6BHMiXLedEWKXEspviXkKB1Eyf71UzrFdWU6ZPnNMyffWHnumjOlM2hzZs0Gzuq96Qls09R5n+pjQDFX0z/RSJrOCsFs7zhpbps3rZKvt8+Sp4nZlKQwJ7VgpWRiiYFK+xE/NUsguGlt3441o2NFLuAUr0n54YaRlxkb9D3Qkd2skElIKHQRL+PuT0T/jPSs2WMzo1VxE1yRONihGd8J+1pMu1kiDhPxFJ+PuQhwk/Pwgjy34cI/f36KTfSwl/WWofRk693ZDwM0NOyv++XQvIMOHPhV/pRzLIjwiXajSgD9QzftRjJ1AEqTCaMkz413WwXTpI/4KVPWgrhOHZDeRaKMOnZvXP8CkBYMHS/CKWDvjIaslX2zEEAQsTG/ZfHFEyTPn7dfJWHDeil+dGlVE8wdB9YUz5w1Ep/6V6yh+GlP+cwVN+9LAs5e+xGOK9IOZTZNGQindjDQDAPyxRAMB7TSwcSx2I
*/