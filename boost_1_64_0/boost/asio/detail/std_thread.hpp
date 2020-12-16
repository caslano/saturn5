//
// detail/std_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_THREAD_HPP
#define BOOST_ASIO_DETAIL_STD_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_THREAD)

#include <thread>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class std_thread
  : private noncopyable
{
public:
  // Constructor.
  template <typename Function>
  std_thread(Function f, unsigned int = 0)
    : thread_(f)
  {
  }

  // Destructor.
  ~std_thread()
  {
    join();
  }

  // Wait for the thread to exit.
  void join()
  {
    if (thread_.joinable())
      thread_.join();
  }

  // Get number of CPUs.
  static std::size_t hardware_concurrency()
  {
    return std::thread::hardware_concurrency();
  }

private:
  std::thread thread_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_THREAD)

#endif // BOOST_ASIO_DETAIL_STD_THREAD_HPP

/* std_thread.hpp
g6qLO1d8nOe3Np5Tln1lu3LsK7l/tR3b2ZbuS8zfxn6u2N1u8Wz73pi73e0gz7LbQYYRX3dcicQ3UORifXmRMZg6sA1sLmMv3dR52Bu2t9sxFodnn7glDLlSS54F8sxaHrTXfiex/+sGG4i/kfjPgd3hINhD7DQvg1fAXvBq2BsWwj7wJvHfIv4VsC+8H/aHW8XOcI+EL4HD4GdwOIwVu75a8FJYDw6GHeEQeBUcCvPhKLhQ7P/eD3OMKu8g34cHf/nxqV0Hf1tjVBE7vpM7TnUyx6gidnwnZpzq0EGu/09cI24wrgC3FLfjT5Gxqsgv8ov8Ir/IL/KL/CK/yC/yi/wiv8jv5/mdRP3/lLFK/X+c9v9n+PT/F2j9//D00ZeIEs6Y/lutRKbYJtOrz/ARmQOG9k23bWlgnyuQ1ZrxS9GJb3SwFbhJrSG0S+v9XCO0zxmYE2irTdgK2QwE2GLPsc0Z6CnX2MJlbb4x5VxjReYOWJ1C7AZMGa11sBtYyHXmlZN+ZecQdJJ0uzjMIbiZdFdLuvYGoatD6uOaoPpYfRz1cY2/Psw+lFuinesjLfS6KMsK2G5cEFIHJs16DnMJblG29w5pUuwVLnNfXTeJDU3nVtKxdpt5G6717Sv/xQHlL2Fd52/Ieff5G5yv/PyNxZWYv+Er87S40LIoUn1DUFlIueu83xbcF5ST9zbl5L3NceT9tkrk3dcOvnPI+53EN8ZnuzOh/HYQ2C9KWPc5LJyv/ByWOW5zWILqtLhKaL6WErYoKF9Sp479SVE5+Sg6jnxcU04+jmkdZMX19M563IrbHzjry9307u764Ort1PHnov71Vt2EB3qM6rQh5shj32xx16876+/d9dDOenF3Pb2z/tvNXsFVHy+6ankHkHZWHLSGSxe7Dlrk4h3kOtnk8sKMb3UZcu2MHK6MdNva5ErCjM/aHd71tdkdXnxjwoyvqJz4tvGsbvYmupc3T8wchkD9cKhu+AjOac6Csy7Yrvs9MXpf0fna9L12Xa9dz4vrbtftOs89eBQXoMcN0eEG629DdbdLnqWcYZDuFp1t+fpav662bD1tFn67frZYyYouFj1skP61YnpXZ52rX9964NlgnWuonlV0rPY5AOhVg3SqFdCllqU7HWx0pj+vvrQ/zq8fddaL2nWivfn7ujfJI+4QLuYtrgXXGzcBV4Tbgnv/rYhu9Of4nczv/xMx/199q49tzfNIbHTHyLf6qZKfBri/p3B8m353U7u88yJ73rkctu1Xy1FjkyuyslfrDCVoe9+uCcfp8/Xlm61sG+N4s1cpacj7WSuu1b6u/Re4eriDuBu6qI9HM1eaUipzbrTItvfbpJt3aoL63zdF7nRjr3u69he7zo1upM8/rf0ZJnwj17nR9WADLfOyzI2WMNSAfb/k3b79kYXf+//W5dnGKtt+vrvLHOn+5v2efMuxDIc50qPL2f/1U3n338l7XXN4L5yr3v297Sdveu74ifn5ql7Eap2f2ESbfbtTpQz36jDfx8zn639z1ADP6pi6Um+++NqJrMfq96TyR7MUbNuoGdGPsi5Ab13WO07R33tjcybPYOq31KcJf64OfzH+P2j/TzE3ktbKqEzPGtKqo86ZuH+MqWLVifHFm19Tt5GxBVm0bds+xG/reBp7GlsjpO59afUTGXYp1v702BHWWzG2uHKzp4y/xpL8DyHcG1rurzH5XNMq8l8k+R9m4uwtsr5rtALyX8fYoauRm0xvAhJ/LsLv6jg+i5lG/PcS/y3E7z0n8VH2weXp/V5nXf7MCWMLxvrXOP6Pln8++hrPPOvKaOIJzivxfB+V65kr8aRYYgOf6e8bToFxTyv5BHM/hqY=
*/