// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_SIGNAL_HPP
#define BOOST_PROCESS_POSIX_SIGNAL_HPP

#include <boost/process/detail/posix/handler.hpp>
#include <signal.h>

namespace boost { namespace process { namespace detail { namespace posix {

#if defined(__GLIBC__)
    using sighandler_t = ::sighandler_t;
#else
    using sighandler_t = void(*)(int);
#endif


struct sig_init_ : handler_base_ext
{

    sig_init_ (sighandler_t handler) : _handler(handler) {}

    template <class PosixExecutor>
    void on_exec_setup(PosixExecutor&)
    {
        _old = ::signal(SIGCHLD, _handler);
    }

    template <class Executor>
    void on_error(Executor&, const std::error_code &)
    {
        if (!_reset)
        {
            ::signal(SIGCHLD, _old);
            _reset = true;
        }
    }

    template <class Executor>
    void on_success(Executor&)
    {
        if (!_reset)
        {
            ::signal(SIGCHLD, _old);
            _reset = true;
        }
    }
private:
    bool _reset = false;
    ::boost::process::detail::posix::sighandler_t _old{0};
    ::boost::process::detail::posix::sighandler_t _handler{0};
};

struct sig_
{
    constexpr sig_() {}

    sig_init_ operator()(::boost::process::detail::posix::sighandler_t h) const {return h;}
    sig_init_ operator= (::boost::process::detail::posix::sighandler_t h) const {return h;}
    sig_init_ dfl() const {return SIG_DFL;}
    sig_init_ ign() const {return SIG_IGN;}

};





}}}}

#endif

/* signal.hpp
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
*/