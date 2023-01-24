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
qXOQS86f4f6okQezVV7OVkTu5XEPCvwaeLD+XDNbBLlvzzupHa7nQWCCSmJJHQ/mOn2yXIPc5NOWv8JredDoEOc3EbnqW3KUvWp40FBv/6wS0e3qfkZLF7kpvT9fP/zBg+1t17XEkEueNHi2rYoHsQ7DlSMqeeCldP0cDbm4fWnHrgoenB8ZuyWiHJVHV4wcjlzj1Z9kTct4IKfwetejUh4UuL4Ma/nOAzepm12LkTuuWX/RsRIelPRF2CV944HotYePRyD33PufX9YW8wBETvw6U8QD69tzJiZ/5UH+lk8MMeT63dFeQRTyINVKf6NdAQ/i1zRtepLPg4suVeuK8nggHi2rI41cV+e1s7RzeRB3f/+ovV94wPusW3sxhwca6u+iorJ5cO/gxRPlWTzQ6XupOyyLklN5/4xMHuToib1c85kHy6Kr9Pdl8MAzeVvziU88kI9a6h2UzoN9brulI9N4cPL0Td/PqTzobHmNVabw4MqOUwc6knmwc2xlmiRyTaoCJssn8WDhIm/ryYk8sBq99/msBB6ESiqWMeJ5MGPJoRGL43jQ5jVPnYzlwehJWot1YpCcB0BHh8uDKau9jnA+8mD+iTN4KAfVI6YTd+s9Dx7kiCt5RvBgwXymzpa3PKi8OW2WxmseOF6bXtwZhvSgzHPT+xAeFK+09bF/wYOWp1rHpj1D9HR0L8p8woOlCq0vDz9C+jAA30c8
*/