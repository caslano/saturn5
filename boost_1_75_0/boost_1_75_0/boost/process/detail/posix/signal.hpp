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
QH85SPmM2o/sMtv6zI0Nz+qeQ4O7GflolYnnHKeMh4ghWe1tgp9Hu7n6tvC7BMaQG/tjuLlTCNdn9iMI7e0WkYzJCrIgbwtPhOITVSdhIP9+BhrzmEROQPkvtKeA3/523E/Elam9Kj1Fiyv627OCy0hjOggpZj4S9e/fAEk40PDK/yuKvf+vohj3/8Xq9ykyouxKcfbVNmkJ9up0JLny31PkdyVCF6NJGBTrGDSUzBWq0F5CzWmjtA1D494OlZLpOe7/znI+mpQ+Dn+V+F5FOLt0bUQZGXSnxDyXFigvfJbK78CUXSpsQ1TQ1QbjrHmlELH9m0Yk0e+wye9f5fWB3QvA41NKDvL4aQj5Pfn314qogOxqK74qoYQaDV7UcBZg9hQ46+QRMkf6/onk0nSjccQDuju51E5SgnoSjJ5LYP2SHwX0IuM7dg1Ht/aKl/AFaPTvh+mzzFh/DhCRmCmsq/BrkGONFlGNGyzfrAMc+QRWbgHEE0+Om6DD547z1GPgb1tj7y/zPnoxFssM8n888E2Jvr6Nt1nSHRcX05NFih3qkbgt8h66mE7TX3fMNPnuBoSHhBecZl/XzfeL9MNQt+hPF4BUy32UT6IbOT9ae2H0FIsmV48YQSDsG8hxWhxDbzUVwuV+Gt1+uh3lKTxojI8R3pZK58dflONNuSvWYPwkEvBnZgZp5u2EzNvG6EHsxG2/CUCSrOrMsHia
*/