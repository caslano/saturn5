//
// ip/address_v6_iterator.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//                         Oliver Kowalke (oliver dot kowalke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ADDRESS_V6_ITERATOR_HPP
#define BOOST_ASIO_IP_ADDRESS_V6_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ip/address_v6.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename> class basic_address_iterator;

/// An input iterator that can be used for traversing IPv6 addresses.
/**
 * In addition to satisfying the input iterator requirements, this iterator
 * also supports decrement.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <> class basic_address_iterator<address_v6>
{
public:
  /// The type of the elements pointed to by the iterator.
  typedef address_v6 value_type;

  /// Distance between two iterators.
  typedef std::ptrdiff_t difference_type;

  /// The type of a pointer to an element pointed to by the iterator.
  typedef const address_v6* pointer;

  /// The type of a reference to an element pointed to by the iterator.
  typedef const address_v6& reference;

  /// Denotes that the iterator satisfies the input iterator requirements.
  typedef std::input_iterator_tag iterator_category;

  /// Construct an iterator that points to the specified address.
  basic_address_iterator(const address_v6& addr) BOOST_ASIO_NOEXCEPT
    : address_(addr)
  {
  }

  /// Copy constructor.
  basic_address_iterator(
      const basic_address_iterator& other) BOOST_ASIO_NOEXCEPT
    : address_(other.address_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor.
  basic_address_iterator(basic_address_iterator&& other) BOOST_ASIO_NOEXCEPT
    : address_(BOOST_ASIO_MOVE_CAST(address_v6)(other.address_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assignment operator.
  basic_address_iterator& operator=(
      const basic_address_iterator& other) BOOST_ASIO_NOEXCEPT
  {
    address_ = other.address_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move assignment operator.
  basic_address_iterator& operator=(
      basic_address_iterator&& other) BOOST_ASIO_NOEXCEPT
  {
    address_ = BOOST_ASIO_MOVE_CAST(address_v6)(other.address_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Dereference the iterator.
  const address_v6& operator*() const BOOST_ASIO_NOEXCEPT
  {
    return address_;
  }

  /// Dereference the iterator.
  const address_v6* operator->() const BOOST_ASIO_NOEXCEPT
  {
    return &address_;
  }

  /// Pre-increment operator.
  basic_address_iterator& operator++() BOOST_ASIO_NOEXCEPT
  {
    for (int i = 15; i >= 0; --i)
    {
      if (address_.addr_.s6_addr[i] < 0xFF)
      {
        ++address_.addr_.s6_addr[i];
        break;
      }

      address_.addr_.s6_addr[i] = 0;
    }

    return *this;
  }

  /// Post-increment operator.
  basic_address_iterator operator++(int) BOOST_ASIO_NOEXCEPT
  {
    basic_address_iterator tmp(*this);
    ++*this;
    return tmp;
  }

  /// Pre-decrement operator.
  basic_address_iterator& operator--() BOOST_ASIO_NOEXCEPT
  {
    for (int i = 15; i >= 0; --i)
    {
      if (address_.addr_.s6_addr[i] > 0)
      {
        --address_.addr_.s6_addr[i];
        break;
      }

      address_.addr_.s6_addr[i] = 0xFF;
    }

    return *this;
  }

  /// Post-decrement operator.
  basic_address_iterator operator--(int)
  {
    basic_address_iterator tmp(*this);
    --*this;
    return tmp;
  }

  /// Compare two addresses for equality.
  friend bool operator==(const basic_address_iterator& a,
      const basic_address_iterator& b)
  {
    return a.address_ == b.address_;
  }

  /// Compare two addresses for inequality.
  friend bool operator!=(const basic_address_iterator& a,
      const basic_address_iterator& b)
  {
    return a.address_ != b.address_;
  }

private:
  address_v6 address_;
};

/// An input iterator that can be used for traversing IPv6 addresses.
typedef basic_address_iterator<address_v6> address_v6_iterator;

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_ADDRESS_V6_ITERATOR_HPP

/* address_v6_iterator.hpp
8ODHenC30kl9DqPrT3k+8XjRLRD72DYALfBe9yHyXuMJFu+x+l7RD9UnAzljdXkf3mfVMAeunc+oZtsXzA2x9dVwUIQ9UmTuLix2gDqva0M0tOMryt1HeF6l22BFT1j/M2TddSMiEmLq9sgzgdzQ+6kn7MdeWtmQjyfihFEfgOpVd6jrgIQ4TI05ZPZK0b4TqehMDofFTskxzeq1JocloaGlfDPH0kmDdo/jzUKr2k3/h31wtQiL8McYiccb4s/rvaIw9b8KvJxNL+Ly+77H4vDaXqfV7w4qpfEc3o+oleSwnPYnlkzRkLJbJadM5LC3+m0+RcAkayAq1dSUV+s13SepKfE/R7FP8fmO8AJzPF9gsJkMPGZAkcxt1w1jtT9AFZW1bR4D7ktbn8nbwCnJrTXtp7f8Z53HZ75nXU43z09f4Ih9fgRMrLofE69cHAwqZBL7PoVTt9r7RwhcnbhO9VzsyDP3gI7s1gwDgzvBi2vn9oF3gqCfofweAU12d/U4o/+PKDAmP2yiCFPEzhnVhtKdlBFeNgD+IjkaNZm6p+F8Lc0fOude6p3YGSXqrMtFeWtc6SFq/y0x9xeUThndOJ423M5tu2FVssTyONcPuHCBMAAjcT3KpcTubWLXoKW8k8ttaieqCZsxwNI2u1Hv1vdSJhKdIvLweNZtGyM5aYrjYY4GPb7YbyPvL3qwZylHRkbGErQoz99VL/cbfSKigLVBznlmAOmCfC8DXKgPkZX0ETMaMw2LBcUQgsbQabwR70+4QRiUGVmJT4i605ACd0thElIJSweaixi2zORGsynXSIbvmtfjq5SEEItXEzBMCD+T3zeB3ViOSUoopamMyCe+hD6fbiCbM0YFIZMkUg+Hzn8Upjj/9CKiG29oTtM55dMQ7bgXipLjao0m8ykoqT2RZr2cTOnXwy7yRXauqcavj1jLA3MJ53El/UpUYnbnX6h78nr6PqG48gYaylEgykLHjSW3NI24bo+1wuaacmS/yxHD1BupDEcgeL5o/ahJhx1/nH9rsN1sDxELcA8IdetpMnL0tFZqgLyWwXbBqMrO+YopJn9xYHfQtl0eMBqx7JZmJPR7SeZO1omWctK7HqYup51Ykzja5ltMMfV02zVS+0epLeTtux7RHlNWri8ToemWTMLpwqSYv7YuVaPdiKzvB0BaoVTEPrfTmaEBSrojiCPa06GueTdLvyrsBQ9GjrflA0Q8EpXKgtwVoe/tahmpZud+n+sYszt6avIdfxnDv8Z44Lw365l9vp2huWhdXRbCeJqwWLBnHY/n7vvRIn3beqK0+dXzG2vyFNwFbSeCbnOSEWQg8W9i+eripZ9jrdvnCM7047h3kaUDqA3lWZXoNwvQngQnzp+XSF2sV/IxQxeJdHOf0jiCheyRVYdJofNuKC88ia7vEKZ/hI6s1bHZwQtOB6MUkYuwzR0K+LAJwlB4C1UdnbmsvqBVNRoGY/YKWbtiefl5ZD4G1WoOS/VtJWrj8uPugyuXfW6ZHiPpWag5ABNeqEJpucNjXozCybXbN08aaZHCv3suoS+4aQ9VY+ZVjshukmDl54r5bIqv337TYBeBrjqp2MPYvx6A0pRFSOqDNGbJGD/7tvI6CyfrGDmWD6Vj30ecQb7mpQmLMZm9xe3Lgw55U3OytMQjImorXW64/Ik1Vtn9tC6Bi7kxZMIyBiKLU416PxEPpqRnf7sJpA894exa01XDcoj4fPejFkQ5b0G2FZLkOtSxz7VPaE6qo7nwiwHKCoLpAeLdmXSzDuahRX2jV/weqMTQuhffOJQ/URHeTwBIA9gEEwV+RcDP3FWmBhHFFlT+ZPqUh/UcTA1vVSgS+etJTftuyuq876kujYF8aUbVBqUt6t0Bbl1OD76UpKcKPFYdrn94svyYDkZ7DsuhkFcHTZV2m7XcZCk1CH/P/wRae6iH6dAcOxBC95XPNyw2KQBt90AfB9IqAfHtnHUdLjdtuMbKhp67pZjVWYVePEVylCWEyEXWtMBbbkJmaecOJgy7jI+bQ+ewencwIFGHxv1r6zj82Re2tPfAHmG3I8Ge/HgP3p48nRxPuY7vm0wtAZ50CdU5FTcFMG4UoFHEvRxcPMKeN+g7AgS4uDB3bU8fmpPaoJJbYROSop+4x8vcWo6twNkL6Dmbv35t4u/LeMG/f0SjgI0YGnY5FGTLQZIzTFhHWd1AZjhBNqfChaW/hgH4brN8c6L8Il64nGH+lfnb3YbCINW57L5y9riCZtwMwNkllUwmfBbj4UdON8y5Lx+t2W5Cc+eJMu/wb5c4MUiZSpSTKUkYSQzqfgRYZAFHkdeAGRkeYZy6J2//x+uzhUbpO0eDDrezpLX6YOZS/44WB91W25UC78YSBTzuUcdlkjEONwUNc1JnKdnanfV+JCP/VNwb1dR1UnGftcN19GGaS/PxsjtRzZ1htptuXEXWrXhKxDzASVQCTHkCjKNsxim+COz12R795M1CD9bUjUOR2pAi7MOs19lHo2dPFMHZ/NrPBwx5/G5BcH4DjMBB/xu377U/hOqtz0A7uM5ljtH52HtYyYddvvGc7ZBFkOr+keshdtaRX+ZJtSN3AuxwVBrzVG6qXXcHbqpddj0Qj7yBOwmzD6xm1NhDa24HLMWetT66HPSeloIjjFVOy3O0YhEEXDcuKl07dZfJa07iTLfVh83uYEr8xpFxXMGJ2fXZBJvEY++Rj5nShTm93IZbO01TukSKYnvRkVTMN5sOfanYrQx3KyN7Y6kPR1rR2Sddaz+7FdOh3Hsbq1xNB0Hv6rrffePx60T9UY9Y8qmmFBtCPveZ6laveLOWoXV5Mp11Sqt2D2t/0kDICdZN4Xjvxny9nHCxxdGgjrYttInpljGXhbdV/DmPq01NbsdhiYNybCi7vUbjS+1CvKfPnW7iBg3lMicyHpmJpXc4212OOO+Ag+09j1bDvKPKmbJymM8WA3GTuQtTp1p/d5LkMEjnAw1sYImyV0X3R5+iTkP6jHqBjtxsJ2EjZj4r4EPKq5wItEvP4+1wFvp4PL/Vq5z97CKG1sJ2QEbN+UpjtzSqnmQS2YGa9a4IdfZWx1JBNAO3p0kLKlpYbBTkSsqnwyXs/q384I2f2E4MJOykKj3mJwD1VWnLFh15hIfbLNUpy2XPlpJzjkzrLZ2E7l0hIXJsDu+uxsLFKsPTnRe7tI1O2cv1gJsmcOAPg5R2YT+/s4t6NerHiNQpkRWU3M8SdO7CO5viFd2yM+ab30kHVj8DmWj2OFrrstPsF+Wzf+ee0LgfSknCVLu5lDGr5AqayRzxSZ5P/+7xszYDwT3SwhEGIGXqbNUC4w9fpItirXPassSDTSoIhEyOQHsPH+5EFlSRQsmgoqkxqDwvMBcSw1nY+Pt6okeqP+CXNJUzQ8RjrsCIvKrqpAkUGOMXlfYS6/H73skF5et1C8QfyzPk1neam7mMjOsbeZyBFE5sbq9BIQPssxGNrG3gHa6bcPmSoKr92QAWGhxa/UT51GgDNZHU6Fw+bzUu0m4LDKpaiyTMCZosU8QETIW0k1NBK5lPhwo47ut6JtJHmGJ8HEfTZez6J8RsfNu7eqgfl02ccpsWNqO7cOX2ezPECq1qbOxFdhGvqSa+2so38mYOc1P10B0Yq9HtrpeWKWBKWiAAK6hYS2gr+v0bGLioegy26kgz3/crwUhpYilHK8zJvhpOr7IAwnckckX9B3HMvtdPa0PRy2tcqZiyj0FZCll/Z+bPVPiWtZWVQfCr5n1YDwJSBxvZCqbow91NySFa4McDHR2R7LK73NkGq1snQbVAxRPe7e2gEwyllwFFpGEhniAkPBZrkV3rJK4IqVQ5fx8mwasVzgbGdoVv1HcCtlwIFUI/4nIES++vfG6LBEUFlyphwmk6XxaRw8t0jYtl6Cvc7DEt8BM7uJqgZuXiPRxrxLFw2lSKRdWCqDweUpEVguxTydYgV8apXrXnGCIYi2klTsaSRAohHD5aJ8njbzxBWWUa8XyWsd8MjHG7NYK3GXmhLFdw/8lktOnrunWIDPdU0aJC2LNzq9TB1+EzJYNYe3/8O9i1IdyWzwh6ev5c6EMBkgBHxEeLxB6il+Omk77Mq3tqeqNBhjVqiTKr8/jEIrxZJOOy2RgGrMRh8/akTxaVI7hcFx5FIj5B6uIrC3ExkJv2woh71FAnsDgQLPB5nPvR72ggcZxK80+oHnXKzPINYoPthtU5Q9XDZUeCe51CvL6Mw2rDX5/OlgIMeeWwRB4UvRwjJWSWmaCnquK0Eo9JXy1/CCOCNKFykA7XgnJgp/ZIq2lTf7XjsQQhgTfycyIv/TtApTIyFbIBSOdsMEcEsJ9JL3CgeSBZCEY5IPXf1yV1i6TMYCe09vn3AgS2e+Yn4cLIiaBu9CHu4H66ZpP4E01X5xOybX+HIIRor4eTSeKkjIU+QzwP9DvqgjQkcT319NiCX411eOAvWuVZR+y9gg/Sx1IIQNG+amLEmBwLyhcQSYHIQZ2GNWbwjWaIk0JDALWL+in+QM7zbMnygCSgTk5QqfA/IJcbjLwBSPEjs8x+yQCIHlo2RLyKkX0+5/CG6ZSmHcbXpD3hnk31l/cZyx5ZyTNyLnslCEpWBmrFCCUlwPf2oG4HXbcVimND6UN13hbvmY/BzgJFemKgDeFOLiGmYuFwkJ4b3uX9ckS9OLcbWz/z5DtU/jgaAGtRsgIBZiQI8mx1nw0YDCA6Oory8Xo0+eQYypb6Vf8OIgUiY8VBJrjQ6v3nc++yUswgpGmUPNReIEQr9DjcARwLQR7+BVVvKv8DAp/ZcUkhcR7+DkwcadPEzMo8f5XbAzunpWNfu70QIQBu2O8bikf2rVe9O9ZqA5VBq2CJfbasmXQPkN/ntes5p0WxDWcwpykVqWVtO0p0upqjZYiwaYUIlb6Xgxnaj/zg0rtlcvVU3kyPqaWGl+0L6xevIKDBVRYrVBpGQmR7gCFeqcXvnTaAYpnrdwEM+1E6NomKEPfZZPOSa+jwq7Oi2OFgAS9iGr2p2wRnuqr8PGZp8YfvSH5dyKMefEr2IXedxIC27HUoNkGd1Uk+ubVytDvqHqxv3RRnVla811ufqaary325Wn76ngdmvAZCnRg4Cy+PPyZuhZ2OUHROadymKd/OCkAY4Ym/6AZRQgjO51z7uAttlH2iWGEj7YFQl4UpyqUhMfmMCis70TvZpx30FL5j1hBiJMeU0EItnCc/jN6SrV/GQU5Zt+hgfWV6nnBlX3cM1zldKC0AESzu032gX8JU7KxrxF7vcKVS6gIxxvLSQur3/QK/tzZPuk+UWm/FNdghNxsMac/RG0Lrr/CydwSUBzD1YpfesIsrAa0OStPLU9OX0/V6u0uHaJt2C64f125nWpxboptOsxysZvfY64HgPXvOg3qHUCNyNWd9TwkcWIend0NCyyYH57uJsrzxndKGuZ2p3Iqb9HoiPagkCXe9vrk7k+WJiaGfhU5zcuTVwP0yU4VkIlh5gh1z9dzC8XZZ3m4Jc0IKAWlZjLfiPcHIbqsdCEMkwxirgkYZkGw98fpQ5zMRzCGX78EQc/bpPP6iMvK+hnVAiQDG4ZWcSCZK4CXhNvPyFKwMuVU3jkRMaEsPAPAzy9aMX4lAyTH1Dl0+432LBz1t8+NoAGqHoMdWpTuFvAOshyn/pfydaLqlRKhLJQHuxzhfgq663GxUFMxhsXTJj9MrKsqDNedcwHSoWZw951JyRKD3haQ9YYsFpPvoxDDPUO6yvCMmxsgly3dHtZS4tV5yShamsxC+s69AqlWHL0Bd/qubZsA7HKOxXi5G6ExxgufcjPWp89A7XpgTPggjKLb23KaP8iLfr7I9Y+Vp8TvmiYT9OA9Nj8P8GJdN1nJ/pDCk+iSYegu1fQQxwdT24F904YAmQy8z4czuyLyE4E65IDexRbufT0jWUuv93/l20sAUhXf2X0KHzcGuKUG+PNm54BNLpXwhGpq3E0XBjtvsB88oPS4ZhwvDKD4wfJNXFVHrgUp++DKNIpCZZQNshPBG5MH5RnHK65bohkKbSvUh8tHkhIusq5jbpOpF1nEHecTt0MIlsSle37S0mKoIP3QB3Qi1uzj7lQ/XDNjYSuIvmE6HHARMjZez4Sv/bSdyt0nazoH/gJeDkfolx+0rMPCrz4eDUnO63Hdmx2J5r5+EjFNdvaqUiJyCOb5de+RcBc0tcpg3pSOHtuLB+iOcNh+SryI6uK+lO+6qrAI7Sw2YBaxS4x3JoEUU+SH5Si/y609UXYR76W5JaXfIR8qvNwGWcXZk0N+95lSFBKHzYpOUiGB44A4Mg3LfefEkw24x5p5A/IA4CkC44PM1MIampyDFF9+UCzqGNJTduvo6AbQGG6I5JGTGyghDuSJDPFO2rXwfB5EA0S4QZYcoudcg2nnGYcH2s+o6EhmgmrgtopwxmUgulhwi0mwe2ZcXJ4cHJYhAkIALw0W3WbswBPcrs3Ep3KN9lCs0eKvp/PVdXuAULM9M/PldkY5cqAz0g6ML9bbstUHCxLEIHCTJBv6swizo0x0GwOgUYHVNfIBQb5GTnps+ebIUKN/obt6OPeuzfdSnYZ6HPEtCgxqXrmlEBu0QlxvsO/UsyLhxxcySfL3NveoARXjycNckkOHW/MX9a0tLS+4XVrjtEiM4fEjjVPecKbJgh7qhGmR7waoliPVHcNEybKy+eIs+OLr88fBF9k7e8lXkEaHIwZxmmymoMGgImihlcJM1k9eR/Wq2BWBtwTYotSm8AH5VgjADWgRhQ+S8vnIxy4loQTZAArK3Q5GghF3476mp467e875vAYgYBXX8RFGAeCIC/DzxL+MXwZqOJnFC2dZ7v/JKP70Q1yMII0vVTFo5XWsP441/oYN5jJ/rE/Aa+e3pBrG3rxx4VwubBncdC8GSe/76/kItqDYUtNXrCoQO4HN/3XaTYYbyIpj1JTWAZME9oIfghl5HzIMXMfMKCEFuEQa1uh+8uvtd3wwFRv60Soc5Ha83MwyaGtYXf1ri2ch9/cq+hHf48sp9Eo5rvp1EYDxxDX/vf7PZPBWou1vEeg0kZZbBSIT7WcrhILx6a+HwunJJ/IH/mHsoFqb7G4eC2Zpny7PWX6y3lZcV+neTVUHXpOdqyNX3pZZZo2G5IPsgrjCgeLqwzhKAC4gNhK+C0+p7gO0FvxK8T0/6Cjhm8eT81uaIuLxhBNkDe+gRFKgwZWOz9sCN/8jsuvp6ev3qFvMknKbG+O0Q90IJbBNGgtRM6sr0kvurZ2LjdcgVLDw+s+n9EJipOHVlMw2LPgZbTPLmrp96rp0CenuKXiemnnNL2J9jXp35+phlS9l/O92xuzOfTjVRVRsM43i+qtUtYc2Sh/q/uuGzDdXzb7Igs9HdQi1/ceQJ3US5hXp6NeeHeAykaUMATaqiosn7x2nHBbyD2J8Q34Jkaj6H7E42tB1qTYQj9WcqaixeympI/CD3qpDLfrN4O0X4ima+v/yT/uQ2sRviGRIPugpSO+7MzhcZvlPYmOV49VjfxhakZYMv8h31vpYnNwvpgqQIX6yddHmnxIW8bg0GQMRPhKoNVxXsT+zLM5gqQJO7n4S7359iN4JWd5U868F/m+y3GH5ISIaMObcizYu6P53lloUyO3GyHLfTuEs5Eo2Tm0n6+u5q+5KF2PZ2HdKPmtdX7IqSP+YRo+07PkUMK6DkULuBMLcBSN+GKmA2xNrpDFAKN8qQ2oEI/pxrW0AY+DuX35dT/vQHP7Ek0dBztY8/p055l4hmRTFFfs7pCXf1NnfiFcm55R6bS+P63IpRelqO1invJU29MH/Kymq0zQ6/1cM7xceS+A8eAoNj3M9ZGUFt19TUKMkRZi+RTtCuTy5Bs/MBkqDWwiH+xFrTdVemycvIdV5hdkXh6Kg9q5/tzISJXfgXHQCKQzGIJGdLvdlOESa41xFsuUcqEeLz/gfVR0EPpIpwK2Km38Ngu9Ke76v+VA3GSNxNj8Jt8HdAhGK1PAHy6iJ/iPLlXdX1VjuLIRIHY3qTKM1f2pCESTUetxeT0kENIx3ZQDrVR0uQV5DodM1Kr1Vzl2cSrMtPE5kAKgWKMcLPO7YjazpzAKrehRNMq9h60jOYlgSmLwE5v/uL53y/MhY7Kq63Z3JAQjwQb6vLeLpsEtaTV0J51ZBWHZ94Npm5+me96svuPbNKRVgkS8uK0UL4c8qIVZFne2HeM+v9XGwO6caHfV6NyxoSJj0tfp8+gB+vim9N1hZ9BoOU0458gj/8CnGRHNdyF7BFTl18t6B6adOw9SX1pxZEb5c+/qi9caUN3Dp11le3jo/I3ioNP7+4EVaObBAFuYwoQdw22gV5ktJa4H8ZorNGvPi9wvLCBpGTHj6NDEZKiQll9aD4aAElYLfbnQ4B5jrLgk/b4sMg2RoMeYMh0jZDwsmPpR5PagGpn4KemF6xVy+VbvYtoQDAl9Bb5Kl3w8QvwtZDwiNtalQiAaWv0zEqb80K2dYgb+EX60NzQpsPoYO2hsAvdr3kEMG3hD5Y1tpGFFZmD/4MnoQQVYGJ3BC9urw6YRBczDa1X1KhXrAgFhdG6kN/T8sHrZVMmhSBKWphDyBZaAfGAm6nzWg3UUimxI9Vp4j90NaOZYltUS4kI3L71lq6MiGBUOthe5f8O+I35S3E7Q+fvR+7n2MmXW9CSUcgB38+E/TuovblS6vG+cFeiEN46F/DBGHHO8aC6rbAKh01fR5fnvZOMFd8+Vm06CvhnfdP5kbeD+13B/TrJ682viStHy/zP3IzwqHJT0IJA7BUrR+RW5CxLRTBkZK04wrvnhJlJwM2/WxQP8y6FiXfZ31KpZPNcoLo8WJZ1tv+fTImstGy0eKPEvABF377RIPPV+x2c4TWvLx789KoIf+T2qG89TmyOWLVSsrKo1WLoNaDyAOCV+raMO2Om0tGe5B9fGBQiyN1o0n3aHxpYhlPKpJsrcMejAQG1T1MGLKcpY0D6ZZQ5gVMuJ38z1rf4CjI9JC5TgNemiJawFZ2RC0B1Ajh127haQzjb3OW1sz3JuhV1ZklU8hhGKJUxYq+Ury+incf4BcPJE6C23xpDkust31vKMeaUsyTn/A7Q5E6fXwmEZcfrytlsS1QLiOLi+R9TpkCYV1yRK45Wu52Zy8hLjYcE/f5Xkw=
*/