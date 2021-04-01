//
// detail/win_iocp_thread_info.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/thread_info_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct win_iocp_thread_info : public thread_info_base
{
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP

/* win_iocp_thread_info.hpp
1bcjoMPhBomk/m2xdylp/IHaaV2h+0JKBAgs/P614utgI/kIH5chqLH7KauWBtBPCR/fi1BcS655VJgjE85jWOltjvXacCc4DmVidbKw+peXdJaoDtZuWwkJqf4Onyr/m7UdTRkxEM37mRl5fLEVj31Q4Gd2twojhGQvmN+suswLFylBKTTCJVt3w62bgbxhQ0c9em0KZWgrijlXsQKVHov2RxwE+fDI0nmpS6cxZtJuNKM9IIS+X31UiAHOOxMlvfZmkRHtmh224Z3TfHRRs7VGWqxhR2w4WS3MB2AFsdjp2VJCwyx+FGylZaFLruEpUFX9KFQAqV3CQS8HL3fBCnvUW+/ecstI+0KEC+Ton39VhxxYo8ye4eeTPtxCOnmKJfuewrr02N3dswZ4Nqq04kEtYvs+QqZUO58Gq3Jr9cWOy6HhgRS58Y/HJCDEprWpf9TCR9p9l8Qgaorho4z6wi9XeBAYpWpIwP2dd8vROQ0yWDsvAozwTtVE7E8Mx0iAUa2o3bNkOBTg+VrXf2INnSDJQhS4R9BR8Hlb3/cbTanZrZzeMCzI8nvdvg==
*/