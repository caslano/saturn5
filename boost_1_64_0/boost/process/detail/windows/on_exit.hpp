// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_ON_EXIT_HPP_
#define BOOST_PROCESS_WINDOWS_ON_EXIT_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/windows/async_handler.hpp>
#include <system_error>
#include <functional>

namespace boost { namespace process { namespace detail { namespace windows {

struct on_exit_ : boost::process::detail::windows::async_handler
{
    std::function<void(int, const std::error_code&)> handler;
    on_exit_(const std::function<void(int, const std::error_code&)> & handler) : handler(handler)
    {

    }

    template<typename Executor>
    std::function<void(int, const std::error_code&)> on_exit_handler(Executor&)
    {
        auto handler_ = this->handler;
        return [handler_](int exit_code, const std::error_code & ec)
               {
                    handler_(static_cast<int>(exit_code), ec);
               };

    }
};


}}}}
#endif /* INCLUDE_BOOST_PROCESS_WINDOWS_ON_EXIT_HPP_ */

/* on_exit.hpp
ai9Vq6Sm55xx/BA7HMQ9iAzZ5C9C7Qip11Ynw2hDsseP+zfKJgjR3fW/BUPeIPZabvrKwXLkwi9DDTKgPbn6iuDP1miNMkxkEjXPSFMxa0s6zVI1CF2lkorfwAwir7doIUfzObTceSmZ60aJqNl9mL0i4yrtLQq6SZLe7wafzqQ8iYPER7oNKDsagS807bHuT9jwx+D+anLA/jmCHV4fS21X60ZRDCY7lRxjwkdGatpCW7iO4VVIt1CgQRp6Dq7Zvc8mjcwLzmLDXvYOw9yYAxD5lWJnXu8zN9+C+Xg1LY7npbRqEavOsaQGMsM9j2yfSmHLnVBDYvA2tZBPMIbZpDFck2+fccOlsDcS+tZwCQWkjdOl2UL8kzLIfDoOchFPOfe76L5JaOCkT983V0JbLiqynL4TAXeakBP4z/B6AwQ3ugqdKeT8WF0ABG0MVAU7XDPWxNA04d6LxJbIK6E9OGVGcP4Mcz3U70/+A6bA4+AUn7npcS1fc0PqPJajFCYsI66oDDSz7FemTEphmXarEHwasAH0fcDo90wFgLXr0Qkbj8oY2sVAg68vuQ==
*/