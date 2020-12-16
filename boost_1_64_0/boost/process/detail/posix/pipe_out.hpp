// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_PIPE_OUT_HPP
#define BOOST_PROCESS_DETAIL_POSIX_PIPE_OUT_HPP

#include <boost/process/pipe.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

template<int p1, int p2>
struct pipe_out : handler_base_ext
{
    int sink;
    int source; //opposite end

    pipe_out(int sink, int source) : sink(sink), source(source) {}

    template<typename T>
    pipe_out(T & p) : sink(p.native_sink()), source(p.native_source())
    {
        p.assign_sink(-1);
    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        ::close(sink);
    }

    template<typename Executor>
    void on_success(Executor &) const
    {
        ::close(sink);
    }

    template <typename Executor>
    void on_exec_setup(Executor &e) const;
};

template<>
template<typename Executor>
void pipe_out<1,-1>::on_exec_setup(Executor &e) const
{
    if (::dup2(sink, STDOUT_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

    if (sink != STDOUT_FILENO)
        ::close(sink);
    ::close(source);
}

template<>
template<typename Executor>
void pipe_out<2,-1>::on_exec_setup(Executor &e) const
{
    if (::dup2(sink, STDERR_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

    if (sink != STDOUT_FILENO)
        ::close(sink);
    ::close(source);
}

template<>
template<typename Executor>
void pipe_out<1,2>::on_exec_setup(Executor &e) const
{
    if (::dup2(sink, STDOUT_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
    if (::dup2(sink, STDERR_FILENO) == -1)
         e.set_error(::boost::process::detail::get_last_error(), "dup2() failed");
    if ((sink != STDOUT_FILENO) && (sink != STDERR_FILENO))
        ::close(sink);
}

class async_pipe;

template<int p1, int p2>
struct async_pipe_out : public pipe_out<p1, p2>
{
    async_pipe &pipe;
    template<typename AsyncPipe>
    async_pipe_out(AsyncPipe & p) : pipe_out<p1, p2>(p.native_sink(), p.native_source()), pipe(p)
    {
    }

    template<typename Pipe, typename Executor>
    static void close(Pipe & pipe, Executor &)
    {
        boost::system::error_code ec;
        std::move(pipe).sink().close(ec);
    }

    template<typename Executor>
    void on_error(Executor & exec, const std::error_code &)
    {
        close(pipe, exec);
    }

    template<typename Executor>
    void on_success(Executor &exec)
    {
        close(pipe, exec);
    }
};


}}}}

#endif

/* pipe_out.hpp
+5yK4Jh4ossvWB9NgKipv+y/xzj+bu+w2Yes8ejzUJ/LZbAdch0KftQbwT6h+jARHgOPh01hH9gMDoHt4XCYAUfCjjALdoLZsAvMV38z4Qnwb7A7PAu2gFfAlvAa2AbeAdvCe2BPuAWeBF+EveFHsA/cA/vD7+DJ8CA8BUofMqwBB8BkOAi2gYNhFz3OhEPgGDgUlsDT4UI4HC6CI+FFcDS8BJ4BV8Fx8FY4Ht4HJ8IHYC7cDCfBF+Fk+DqcAt9R96/hVPgNzIc/wOnwECyAsV6uDYyHMyD9iPRP/Xq/Wuy0YD9WE5j0O/uyDqcf63+5D+v39F/90X1X+UgFfVZu/VVufVUV9VH96X1TR9ov1ZmySN/Uf6xfSvuk/i/7o7Qf6i/fB7Vp+uH1Pe1CQn1PI6f9b/Ql/anf/5NzC4pLsgItAP/293+2y/c/usjvf3QR+/+rLipoN7DfyQP7WA7baNMGYOtiRDek58Detv8qohvcc+hQsTX6WNH3Onlw/9De/bHo3dsRRiVbZt5xlBaPOXodZiNT8Gdtk6G6knPshTARjfk2pSff7A8VJXb9rNTQ/jZy3I2Z3V7rKKQpYtoUjLvHEVaB+xxutYvH7sKjZA65+351EWEWSSqyZe0FT8Be3I61qhKPZKQhEoprTXHLQ1NN9ptKJdTQvPDRBF6WKDTzwi33n37rOb+ziuQ41hwXmLUCSAvHpMX2g7XowvYialBVwua5gZ3ye1y2p3js66ItPBHtO+77Zaa4tuWYtSB21w64et2uhfEr+yDURkH8x+dklWaF7zVm2l+cbQpVJdzJvq6+aOfaxDOnq9/t+HVrf9mPfoz4TfZxXfUeYzdXje8EcUvwtSCULuyvNIhUjuTvibTGLOIN8wuup8/zsSc+tAYH9uH75jCfPtdej2dm3YB7H/c2Fj3nk2ITy3Fw/exkCXOMz9nmUpzFl7hjr4AfJe9m+boywHAkUoCc6Z3F/NJR5faLSFc/GXVkvQ2GIta1GpO2LrSPrfdEyXlf4LyLxX2zJ3RvWFqezLrvEq+6Zo+HwWK/hladlfgJri39mcTrPF8gjDgudKAJYbKjve5jcb/Qd653gVXNN8rse/2V5MHppo3sC7FbJOGcL+FQLh37sBwMpsWK5l+qtnftFz/zfFVJYS2v1zrVF2z38gXjEVzzhLBTHPvRlJSQRxRZqTM1H+pKOkf4pnmmeRIjbcP3GzXr0M/JdayxJGlZUD5tZr3zSRmSr7rPkF/ON95Xfv9S1mHB/YCka46470sI5mm2Y126x6hbWnE8hnSurMV7BIxsm9ro+PtR5IxEu73qCV0LeTOc7Wi/2ktYT8FTE0XHTki2+xmcYxwyHpmA1MRtD/q+xL8fgo1Zw/gHwrkRZmE3VNcPTkFwM/sSZxxGe1f/VLu967Ha5dcNfQBdZBvYWnSRbWCXoYtsAzsPXeRaovPRRa4lWmLr2oTaykbUCem6yHEXc9xZjr+q+/vWCQ3Uf9SL6Ox6EVup28S/1nfU91KuKefocsXvR2a9S7vc4lfKyz45j5Qh0z5Xx8dYXWnfuuiF489u9lX+3f+4LXNQnYVbX/nj1ohwb4erqJ2v4na4ZRLPJ65MHFU77qNuA87ptqHuKfXbV9wu6N7OV3F7oXt7W8XtfO7tcH9c+19le56051XYDufenldx+597u13F7X8yPjv0Pqh/r4kYn30fb+8BPgirwYdgTfgwTIHr4VFwA2wEH4FN4d9hN7gJjoCPwmL4GJwNH4f7YAOvvi/pO9sa2BNh/pT8OmvbXxdYC3aD9eDxer4TYTPYGw6A/WAWPEXPlwkvhAPgCjgQ3gJHwjvhKHg3HAMfgmPhejgOlsE=
*/