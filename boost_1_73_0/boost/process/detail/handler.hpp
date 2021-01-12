// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_HANDLER_HPP_
#define BOOST_PROCESS_DETAIL_HANDLER_HPP_

#include <boost/process/detail/config.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/handler.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/handler.hpp>
#endif


namespace boost { namespace process { namespace detail {

//extended handler base.
typedef api::handler_base_ext handler;


template <class Handler>
struct on_setup_ : handler
{
    explicit on_setup_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_setup(Executor &e)
    {
        handler_(e);
    }
private:
    Handler handler_;
};

template <class Handler>
struct on_error_ : handler
{
    explicit on_error_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_error(Executor &e, const std::error_code &ec)
    {
        handler_(e, ec);
    }
private:
    Handler handler_;
};

template <class Handler>
struct on_success_ : handler
{
    explicit on_success_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_success(Executor &e)
    {
        handler_(e);
    }
private:
    Handler handler_;
};

}



}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* handler.hpp
a69Qs1+4wtAGmzAqGkxNdYMeJtZAQQ+ODrM9ODos6gEOPF8XrYajI9TiAjEinfpEdRzykl2BdPDIArOAEoybtjpKszGFbVFaIM8rRACwymBs9fjNUdOom4B1iWXShImLlhyN2/1tq2JgxdcJmR4Qhar94akJaCfUM4BiHidQkoyz06yz2GGVlFLjxft5ni06wOH8xo0mEFs0n3Ee5zDO4yLGaeJpWD++6t0DG1urFqvFdi47
*/