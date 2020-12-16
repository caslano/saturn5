//
// detail/winrt_utils.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_UTILS_HPP
#define BOOST_ASIO_DETAIL_WINRT_UTILS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <codecvt>
#include <cstdlib>
#include <future>
#include <locale>
#include <robuffer.h>
#include <windows.storage.streams.h>
#include <wrl/implements.h>
#include <boost/asio/buffer.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {
namespace winrt_utils {

inline Platform::String^ string(const char* from)
{
  std::wstring tmp(from, from + std::strlen(from));
  return ref new Platform::String(tmp.c_str());
}

inline Platform::String^ string(const std::string& from)
{
  std::wstring tmp(from.begin(), from.end());
  return ref new Platform::String(tmp.c_str());
}

inline std::string string(Platform::String^ from)
{
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  return converter.to_bytes(from->Data());
}

inline Platform::String^ string(unsigned short from)
{
  return string(std::to_string(from));
}

template <typename T>
inline Platform::String^ string(const T& from)
{
  return string(from.to_string());
}

inline int integer(Platform::String^ from)
{
  return _wtoi(from->Data());
}

template <typename T>
inline Windows::Networking::HostName^ host_name(const T& from)
{
  return ref new Windows::Networking::HostName((string)(from));
}

template <typename ConstBufferSequence>
inline Windows::Storage::Streams::IBuffer^ buffer_dup(
    const ConstBufferSequence& buffers)
{
  using Microsoft::WRL::ComPtr;
  using boost::asio::buffer_size;
  std::size_t size = buffer_size(buffers);
  auto b = ref new Windows::Storage::Streams::Buffer(size);
  ComPtr<IInspectable> insp = reinterpret_cast<IInspectable*>(b);
  ComPtr<Windows::Storage::Streams::IBufferByteAccess> bacc;
  insp.As(&bacc);
  byte* bytes = nullptr;
  bacc->Buffer(&bytes);
  boost::asio::buffer_copy(boost::asio::buffer(bytes, size), buffers);
  b->Length = size;
  return b;
}

} // namespace winrt_utils
} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_UTILS_HPP

/* winrt_utils.hpp
sfv2mqRodio9z+eJ88l+Merq43cTkM6frjb0i9J3O+rrCYNvBu3/kFZ57wyXCTcFrhDuUpTvGsREHtvwHbkVhR2rZqBshEjNC3s3SvuO6kcZOtPvlVy2dHUkly3zd0mpCXRITHCjfaydKvJP6Gd/0YHLFn/KEQN3Gu8r4DCdZX95m2PC31vNVALs6ksOEyP7y4MpTAZWuXUa60rZX96KbAaq52j1pDxOpOU7ZwHZv2Cs/2Rfekfan6Smm+s+Waa3kM1V/J0JOUP+u5FnV9l+9zlJNqFyPfZXyd+O6s9juJE39tDqz86m+jOObfb10OrPhe6AKNR4tfb9EBEc5kgPrU7zVFuuZ8527kSua9t5PpB1rcEmPVH7TlQVaqpn2WZWoqxnT5jqWfiduvtkgnwuaLwuRV751KV5ivU7dZHFPVBmrktlea9jvfgbubxfo5X3z2R5x7pmFxQuqaAC33h5/8xQ3j8X/gr78i7DxMiyHExhLlExjstU3rlsc5hIeY+0ojCV6jDcI1Z9WXNof6xqW95pf6lteZ8gyjvZ1Mn+HQ/5TyDP6mzL+8gvfMt7JPxaea9HGalMaqS8s83uJF1574Dy/lUj5Z3DHExqurwLu1NJWnmv6mkq72wTnyzL+1xTeWeb0clc3qOqBhvLO33zNLQL4/0s85Ff/LRl/rgo745/vZZQczWDmqsB1FyNIWttIzutn59OY+gp0hjaOXzK4+Oco1ZPP33giyHPP/6tnTaQncZQ87WirDWJ/nu0h6y1hGw1iUhjaItCfzRGrgx2b7De0FapN8S/SXtC/qa+9yKaW0n3Oc31u1Ohvn75O0z+pvpK/h6o+z1F/qa6gI6JueOk+1Mmx/rSOGTalyqeQ0Dxdy3r/lSDg1m3ZwL4NDiV9STmgzeCRbx9BW9fy/oLV/L2jbz9JvB28F7efj9vfwz8Lfgab3+Tt3/I+gyneLuqere7wXvAWHAXmA6K/Zm8PxvcDY4G94DTwPvANWxXyXZXgveDV4N7wd3gH8D94B/Bg+BD4FEO9yWHOwU+AgY5vNvbgGJ7FPgE2BN8EuzH+7N4v8j38QqPueVxu6JcBIIke8l6GYJvgA7WzWjDuhmRrJsRC77Nx5unjSvlMbVF/B4yWbuOQm8H/BXYV1xHcBp4PXiuuH5gHngTuASsAS8HbwbF9dsGbhTXE9wF3gruAe9mvaJ7wHpwF3gc/B34Hfh78AfwENhK5C/oBh8Ao0T+gl3BB8EUkc/gRPBh1rN5BFwC7gNXgU+AvwCfBDeAz4LbwOfAneDzIOJE+kJ/B99knZtDrHPzGqg4UE+DDvAlMBF8F0wF68F+4Husn/Q+619EaWMLeVwkrSMj+sQ5fweyvs8gMAEcIo4HDgMHgcPBUeA5PP91NOf7GLAQHAeWgJPBanAK6/5MBXeD03g+bA74ODgdfBacAT7Peh1vUznwzos9F/wYXAB+wf5v+fhu1v1pDy4Eu4Dn8XWYDfYB54B9WRdoJlgo4guez9djKVgIFnP+7FZ4fBvnVRGvQbCdyzOqcip/x8B0EGFIX+QE1yf/AKeA34MrWDfJw7pJVwuAN/P2WjCQ9bOCwL2so/QU6ABfAZ3gAfAk7N8HT4GHwa9BhIW9piPD45d43FWRQUcmyeG9rsmsr5ICpoG9QZJbBieA6eBUsC9YAmaAHnH9wQ3i+oPXg9ngveAA8AlwIPg0OAgU13EozwdHWB6HgzLM8WoDVnC8UNdQOWsPDgbDWIckHJwGRoPzwBjwQrATWA52Bq8D4zg+8azr0RV8COzG8emh6cfIMSFox7heEX23/VW5bjTlzzhwPDhBp0NQCk4FV4PTuD2YCV4OzgKrWIdgGzg=
*/