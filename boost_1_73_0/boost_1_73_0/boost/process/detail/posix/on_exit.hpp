// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_ON_EXIT_HPP_
#define BOOST_PROCESS_POSIX_ON_EXIT_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/posix/async_handler.hpp>
#include <system_error>
#include <functional>

namespace boost { namespace process { namespace detail { namespace posix {

struct on_exit_ : boost::process::detail::posix::async_handler
{
    std::function<void(int, const std::error_code&)> handler;
    on_exit_(const std::function<void(int, const std::error_code&)> & handler) : handler(handler)
    {

    }

    template<typename Executor>
    std::function<void(int, const std::error_code&)> on_exit_handler(Executor&) 
    {
        return handler;

    }
};


}}}}
#endif /* BOOST_PROCESS_POSIX_ON_EXIT_HPP_ */

/* on_exit.hpp
+cYuAGN1cmwtbWFzdGVyL3NyYy90b29sX2Jpbm1vZGUuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJrEySqiwIAAJ0FAAAcAAkAAAAAAAEAAAAAAIfJLgBjdXJsLW1hc3Rlci9zcmMvdG9vbF9ibmFtZS5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUmqgzoY8AgAA+wQAABwACQAAAAAAAQAAAAAAVcwuAGN1cmwtbWFzdGVyL3NyYy90b29sX2JuYW1lLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSktJvbTsLAACCIQAAHQAJAAAAAAABAAAAAADUzi4AY3VybC1tYXN0ZXIvc3JjL3Rvb2xfY2JfZGJnLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS7Jt3bmsCAAAxBQAAHQAJAAAAAAABAAAAAABT2i4AY3VybC1tYXN0ZXIvc3JjL3Rvb2xfY2JfZGJnLmhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSpMIAm08NAABnIgAAHQAJAAAAAAABAAAAAAAC3S4AY3VybC1tYXN0ZXIvc3JjL3Rvb2xfY2JfaGRyLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSzzyCZH0DAAAICAAAHQAJ
*/