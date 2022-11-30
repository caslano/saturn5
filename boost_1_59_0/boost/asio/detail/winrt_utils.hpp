//
// detail/winrt_utils.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
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
*/