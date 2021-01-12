//
// impl/system_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP
#define BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/system_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

inline system_context::executor_type
system_context::get_executor() BOOST_ASIO_NOEXCEPT
{
  return system_executor();
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP

/* system_context.hpp
5KbwSG5DUnJrcRWt7FhPwzdr+seVdCmVQbYWuuym3oPNeEr/8EYbdE2IWtbn80VsY7xcZjKOjOCpey1VZEHBrL5DREfs+g7RyW03Vl8CTIdgC2s1UymRERFqOLQ4s6YKnRLM0fHtsUgx4VGvk5Eyd4pI/DxLOQ1eYlJfP3U9W7PIIxKvXeJ5kkrXy43aCaJQW2/WKeueYE6/fKmaLLra37TsKmD98cc3PYYMjZ9Cr0XraoLK
*/