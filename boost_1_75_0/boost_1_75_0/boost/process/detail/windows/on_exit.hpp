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
+IiSLihSgGG15F31/d4JEmvyxj71z15+xDQMUT5/JxFJ9ia7nHJxHdxD3wAInU0BNfw4rU3PioWm7jG94zZin9w6guiQ2Bnmcjb0EJIV61WwkePsKbnlVrlr+3Apy3GPeIvmZbXblRIPG8R11/b3RM8YR1JOGY6asG/1fL+MLlnm//mgZ++bshoveYrCtRTRfuQ4w4E562ZwkDMVYyTPaDrDCR19Fwpijb9LBUMZJHjw84LKpnG4+/DP2d/YL8T7vfAFWHUadLU1j5yCidmJ+M8FLs2kNCs/FxfJRxtueUObH6nWaEwOen/94a7jvXyQUoGx9Oai8jOin/y8f1LrUv6d/CQmPlPuUTW5Ic/ct874R6ycqVZuaPddp+y2Q1332gf6pcsccOmdxSl9gJM8OAGofp+zvv8HSP8T3pZXkBNJAODerg+OvRq08RwnaAM5GLSBfokFuRMnROSeE5w//Skt8BjNd/40UIcB0UJQnPsO+hBBfO2exipbhDce3rbNeUX10M412viPJQ9MfleCt1nTdVPSzkxkJyaQ6HDVLD+NG8uoJ1FdEjwI6F/wef/oUjB+qzuTa9KHFbh6TbMjKFFYmwRPhDA4xcNJubsIHLiR6YgQRDIiBpGN+I4APuBequ+k7ZjMoNCq64zwJKIRp1H0puF0pzKKNeiDE/tHcq0Ud/ZCNctrGx8L5sixD7aGORogMKVdf60dLdeU
*/