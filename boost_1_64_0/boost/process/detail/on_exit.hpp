// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_ON_EXIT_HPP_
#define BOOST_PROCESS_DETAIL_ON_EXIT_HPP_

#include <boost/process/detail/config.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/on_exit.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/on_exit.hpp>
#endif

#include <future>
#include <memory>

namespace boost { namespace process { namespace detail {

inline std::function<void(int, const std::error_code &)> on_exit_from_future(std::future<int> &f)
{
    std::shared_ptr<std::promise<int>> promise = std::make_shared<std::promise<int>>();
    f = promise->get_future();
    return [promise](int code, const std::error_code & ec)
            {
                if (ec)
                    promise->set_exception(
                        std::make_exception_ptr(process_error(ec, "on_exit failed with error"))
                        );
                else
                    promise->set_value(code);
            };
}


struct on_exit_
{
    api::on_exit_ operator= (const std::function<void(int, const std::error_code&)> & f) const {return f;}
    api::on_exit_ operator()(const std::function<void(int, const std::error_code&)> & f) const {return f;}

    api::on_exit_ operator= (std::future<int> &f) const {return on_exit_from_future(f);}
    api::on_exit_ operator()(std::future<int> &f) const {return on_exit_from_future(f);}
};

}

constexpr static ::boost::process::detail::on_exit_ on_exit{};


}}
#endif /* INCLUDE_BOOST_PROCESS_WINDOWS_ON_EXIT_HPP_ */

/* on_exit.hpp
VoFEWdbk5WoAUJotUB5Ckupx+QCrXpOIZtXfo/IP2rjj8vOLZugzjpILVIe1TSaQcDyXLKnZK4C7aYFw1P5yAlXsQQxG8SKq0dFpJn6CZdqOC0KK3Bf2oa/79vzIxSym1+FpOeV64fBwx5WheIYefqWpsbj1ZAk8f5XrAtK1KvRBjKEB5DliVKXuNIZkFFlM8jCxe1HsOGyq+Ii44TfOx3EC5epDU18WFTLvNdoKLbNi+UGyfYX+tuWmjhvQ8RFWVdN7rhQXPG7+DqPNhVQlipcEGjdA7LvLSC9LMwrUjLntTQ/m6L+g/O1LMKa8t+gSsDhjCnXUH3cYFJO5qKp9EyNP+brevPoNeyJ9izwhc3Ry/iyQeUXn5PMsS+TQSQR21MDJtQ/E0kAdw3nv1PXwlPMGyzR0zsAacP1e4qh8AHGSwWj2KPSf7uyzb6KXpvjMHShTIOfNz0RtPLcEJrdh+Qxyr1xhXY78xSHnmpBot0hRchrPy5+KAqIfwUqWSwDBOFabn6gMgzLICVKRS+eu+tLBR6sSbAZ7W2lzTk/JSjfQcJvJ/AZ1YS9PNw==
*/