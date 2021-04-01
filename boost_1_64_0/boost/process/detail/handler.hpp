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
wcJ3nWZBX7zQAJd7PB+E2ZVHy51Huq/sDehvQFN0ZEmr+2JdhOVKav83LOXgx5XHEm2FCsfmaXso3pgGvv1HMzFnKR7gQ7kxBLRdrC9rjpFFkWtGt9tdEG3tYtPhF4mRt2ZVNjI9mJdb1WDZxxdKlXogdAEDJhjVLL0Hw9Gw5zNeVMRtcCLmlT3WYtfON+R4zFoANKpIfFS+5iupwavxNPcN1f4vAUv/tIo2gOhcRJB5Q9spK85bgdWHoBwLf3ZPMslx1xZqSliJ1EOR/KuQrqpipIBmuDZGbtJcfUNvAzoOm/AdiLUfP4+g1IYWO/642LdExGNIMf6SD49HqdiNAIja6FZQazFSz5v0Jy3u3sFN0XISvqcOrPSI2nF9sam/HrN/+0933BnjapZ9CJhZ+4FbzDA7/gP/UcWKuS7zlrdE5fPYG6v+1ktuVHZTMchsizyWBZo7Fyop4kySxSQ6Z755ShdbufkHN395XMdSUqe4B+2IJfgp8TWp6ZhHK2gLVg48+/Qras2m4+3Knpe8ua4HVQ8JlacJYfOOqhGh+jg/752i0r708jEPoA==
*/