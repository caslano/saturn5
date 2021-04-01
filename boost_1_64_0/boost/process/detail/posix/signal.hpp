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
i7fmcLjZP+3VpWKqsa4kKGWmrkCuRO96hrM/go28ZX8lVll8n7uc1wO+gZwsDmIxSGFIAzZ4j7zglhnowXlTK0ho+EXYOv0rp+Ew/W3nZO/4p1QdjvsxEPC1THnA/GTBqBEE9O8kLgKxNbPF80yTUK3xyiBf6uZ2c0g4AQDmWqKuTezRiwB4aicsOUneEi8iTXKTsdeaU2Z4Fzj8M4kI7OdMJeCEe7Z3/MRYNnBuGUgemV65ux3DjzYu+l258uVvEBQz17AWHdx0WO0W0PmIlqgeFyQxrtGH+QBXK35mamIx4Okq8Z8RIX7OxqM3HhKyiaOgc10N+50dZD/lXcgcnPNof//qEOexg+MGB2y0CIK2oYUlxG9sH1G1OcmUZGmGo0D/VannGFZjljero+1Oue1eaPBrxv4Vo1C1OKV3Colz5piOCd9j+ISYwCbzi6tlb70nLb87mMA7llDxBgvhsQguW0N/HnJudBQLQAGOlyrK84u0QJaPLouTNwqcLcQLjGKTzMmK4O4m5F6kJpKTuSHzxEG4AJwvw+J60NLKIgONrWT26PC32+xw6g==
*/