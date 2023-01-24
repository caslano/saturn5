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
/zEV0+KNzgF86tA5/81dYxwT9DiTrk34wQU/sVIutkXnp0/4rszyOLP9iO6o4qcXAq+bOxjH2q/mqbzeJC7epmAAz4/4afUf1zSfhlBUDr4qgVF87gpV/52n0+gb2B/7szUB8FtVxrQbN6pStPPVqzFj9JhyVyYAc+BLd1snj1lgZv7Yb45K/WdJdt1taozDd3KbMudym/LUqjxpmx/LMBaKi13xDFspfRLsEbyu+HOA7PHwaWsmjav2pGvbZBjtR9SfJZwhf1U+nk8fReMrs7PdSpXbDNmKBNM/KOmwNuBeqdc/yMfbof4MSQHmZ4UPLTZ8LAaq2Ku5VdZ0c0RNEyMjGZ5noCs9CJ8ulBeTNGpk7fCvOFAAPjpvKLR+ljh0feiWpRO488bzZLWUT41Zf/1a8kyghyCJ6FOciWS1IyZGy/7Z5SSOIVsTnKJ7JPdgUnfBXnPuqnNy3Ca79qtUcvI/wHqENvGeKjWVh6Z1WQnQHb1jHei+i+m1InssUemycUp0iw4+l+yI6QbmCX1Z5vwUC8nybXR5AmAgEwn9I9Nx8ohQIvKFQEC804YOyw+jf3bEf4k+lr5iaII9mj+npMR+8RpFsHkPLNmUy62UrTGERCcKqKZP30yKJcifBjuXtvr1Nyy3fuwQTVub4ufu4GdYzjTno/jlmMIqjXItJzOIVxJ6vhVOoXe6ln3K9LyrTNvt+dNYQw99fMFD
*/