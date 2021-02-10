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
ZXN0MTA4N1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKsD1lZsQIAAPAIAAAfAAkAAAAAAAEAAAAAANcZNABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMDg4VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUsni54VCAgAAzQUAAB8ACQAAAAAAAQAAAAAAzhw0AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEwODlVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS5d9+vkIBAAAzAgAAHgAJAAAAAAABAAAAAABWHzQAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTA5VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUqlJ0+NvAgAAHgYAAB8ACQAAAAAAAQAAAAAA3SA0AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEwOTBVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSGcvpGlEBAAARAgAAHwAJAAAAAAABAAAAAACSIzQAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTA5MVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKhHh7GxAEAABcDAAAfAAkAAAAAAAEAAAAAACklNABj
*/