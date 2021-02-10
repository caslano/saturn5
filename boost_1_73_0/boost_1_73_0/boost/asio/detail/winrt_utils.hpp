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
GXYP40jJQ+uhnTUwJVJFj+BAdvSPXemZBoTdb5qRJ9Jd89lzTw7NUs/gZja5wQN5r1G9reR1ScBkbXKRgfYJpqOJVnSM/vVxlWrn8A9QSwMECgAAAAgALWdKUsCra/enAAAA8QAAACcACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9kaXNhYmxlLmRVVAUAAbZIJGA1jjEOwjAQBHu/Yh+A84C0UIBEgUSb5ojPsSXHDueLEL/HSUQ7e7N795KnHi5WeiU2z1BEe7zNldPS43JgdOMqSUZzJuWpyLfHBoy11tw81soOVKGB4aNUxUJCMysLSt7xWOaZskOKmU87GfztKB38o8XZx8n42LY+MSXkongxhKk1N2+b6PBk3l1rDwG+CBwrxVT/S449rUnN/2KrrEwyhvaVhs78AFBLAwQKAAAACAAtZ0pSJ8/+pJMAAADDAAAAOAAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2Rpc2FsbG93LXVzZXJuYW1lLWluLXVybC5kVVQFAAG2SCRgNc4xDsIwDAXQPafwBVLBAlI2BEMHhkr0AlFjWksmjmJXwO0hoqx+/+v7KnkOkEgjszz9qlhzfKCn7NfKrkcuAS4bw5+BMjQeqphM
*/