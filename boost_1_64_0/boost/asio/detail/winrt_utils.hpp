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
TG6l4hrTYTQpCR43fEvIT9CK2ZU8nfU4p5fufjwsYaSbfuuKkN9zSZpQF13Xf+MC3IRM+mFz4iD7MYDFhMDrJLihkhYDVo3pX3CxUDce35YPwDtVYgAIkedfUiSWV/hQRhgXL3kG2uJvyy0g665wIN+zfao3379YANd4Wlj6DDGHNTpiw+SoKdFxJp669LZEypLhJabwoymWjM+M1luN6cFPWiezurfZDm11AgnkACuG2QSPRPEOHVowNtzt2RIOPD2wHuXzpqbuJXdt+xbUD0178ld9m+tkBR8QLYHu6gQ4RdGtv6gfRpvHglCBCA3h1d5nER72m4UQFm2BBthKdf1dJw6YyXSs/7wODXMjctm85eNGupRitKzI3TeWMgdY9IDpnPCpHaEw5G6z4JW3vhbf4+kxo5nFEVi6oM73IbLtZWOYxWsCO+lDxsEjkA0qH18HWo64LpqG0xkA3dMd8cI4duXdgY+KLhAXH8U8+/ZzGUq4Fr64YThFqTPY/u9p2+2i6j84krXFmNsEawlWM4n+Gy7b+rDpRsFZ6eAKpB/3Mxtev3BHpBhDyg==
*/