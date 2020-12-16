// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_ASYNC_OUT_HPP
#define BOOST_PROCESS_DETAIL_POSIX_ASYNC_OUT_HPP


#include <boost/process/detail/posix/handler.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <boost/asio/read.hpp>
#include <boost/process/async_pipe.hpp>
#include <istream>
#include <memory>
#include <exception>
#include <future>
#include <array>
#include <boost/process/detail/used_handles.hpp>

namespace boost { namespace process { namespace detail { namespace posix {


inline int apply_out_handles(int handle, std::integral_constant<int, 1>, std::integral_constant<int, -1>)
{
    return ::dup2(handle, STDOUT_FILENO);
}

inline int apply_out_handles(int handle, std::integral_constant<int, 2>, std::integral_constant<int, -1>)
{
    return ::dup2(handle, STDERR_FILENO);
}

inline int apply_out_handles(int handle, std::integral_constant<int, 1>, std::integral_constant<int, 2>)
{
    if (::dup2(handle, STDOUT_FILENO) == -1)
        return -1;
    if (::dup2(handle, STDERR_FILENO) == -1)
        return -1;

    return 0;
}

template<int p1, int p2, typename Buffer>
struct async_out_buffer : ::boost::process::detail::posix::handler_base_ext,
                          ::boost::process::detail::posix::require_io_context,
                          ::boost::process::detail::uses_handles
{
    Buffer & buf;

    std::shared_ptr<boost::process::async_pipe> pipe;

    std::array<int, 4> get_used_handles()
    {
        const auto pp1 = p1 != -1 ? p1 : p2;
        const auto pp2 = p2 != -1 ? p2 : p1;

        if (pipe)
            return {pipe->native_source(), pipe->native_sink(), pp1, pp2};
        else  //if pipe is not constructed, limit_ds is invoked before -> this also means on_exec_setup gets invoked before.
            return {pp1, pp2, pp1, pp2};
    }


    async_out_buffer(Buffer & buf) : buf(buf)
    {
    }

    template <typename Executor>
    inline void on_success(Executor &exec)
    {
        auto  pipe              = this->pipe;
        boost::asio::async_read(*pipe, buf,
                [pipe](const boost::system::error_code&, std::size_t){});

        this->pipe = nullptr;
        std::move(*pipe).sink().close();
    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        std::move(*pipe).sink().close();
    }

    template<typename Executor>
    void on_setup(Executor & exec)
    {
        pipe = std::make_shared<boost::process::async_pipe>(get_io_context(exec.seq));
    }


    template <typename Executor>
    void on_exec_setup(Executor &exec)
    {
        int res = apply_out_handles(pipe->native_sink(),
                      std::integral_constant<int, p1>(), std::integral_constant<int, p2>());
        if (res == -1)
            exec.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

        ::close(pipe->native_sink());
        ::close(pipe->native_source());

    }
};




template<int p1, int p2, typename Type>
struct async_out_future : ::boost::process::detail::posix::handler_base_ext,
                          ::boost::process::detail::posix::require_io_context
{
    std::shared_ptr<std::promise<Type>> promise = std::make_shared<std::promise<Type>>();

    std::shared_ptr<boost::asio::streambuf> buffer = std::make_shared<boost::asio::streambuf>();

    std::shared_ptr<boost::process::async_pipe> pipe;

    async_out_future(std::future<Type> & fut)
    {
        fut = promise->get_future();
    }
    template <typename Executor>
    inline void on_success(Executor &)
    {
        auto pipe_ = this->pipe;

        auto buffer_  = this->buffer;
        auto promise_ = this->promise;

        boost::asio::async_read(*pipe_, *buffer_,
                [pipe_, buffer_, promise_](const boost::system::error_code& ec, std::size_t)
                {
                    if (ec && (ec.value() != ENOENT))
                    {
                        std::error_code e(ec.value(), std::system_category());
                        promise_->set_exception(std::make_exception_ptr(process_error(e)));
                    }
                    else
                    {
                        std::istream is (buffer_.get());
                        Type arg;
                        if (buffer_->size() > 0)
                        {
                            arg.resize(buffer_->size());
                            is.read(&*arg.begin(), buffer_->size());
                        }
                        promise_->set_value(std::move(arg));
                    }
                });

        std::move(*pipe_).sink().close();
        this->pipe = nullptr;
    }

    template<typename Executor>
    void on_error(Executor &, const std::error_code &) const
    {
        std::move(*pipe).sink().close();
    }

    template<typename Executor>
    void on_setup(Executor & exec)
    {
        pipe = std::make_shared<boost::process::async_pipe>(get_io_context(exec.seq));
    }

    template <typename Executor>
    void on_exec_setup(Executor &exec)
    {

        int res = apply_out_handles(pipe->native_sink(),
                      std::integral_constant<int, p1>(), std::integral_constant<int, p2>());
        if (res == -1)
            exec.set_error(::boost::process::detail::get_last_error(), "dup2() failed");

        ::close(pipe->native_sink());
        ::close(pipe->native_source());
    }

};

}}}}

#endif

/* async_out.hpp
i88RuuIuLIZ7sALuxUDch1VwP9bDA9gMD2MYHsUI/BR74DEcjMcxHj/D8fg5zsdT+Cl+gSfxNJ7Br7C0N79LsCJexOr4LdbHy9gYr2BHvIrR+D0OwRs4Cm/iW/gjLsbb+C6m4Ba8i/vwFzyHj/AHfIw/4hO8h0/xD1QsnJe07ZiwEDrh6+iCDdANu2ImjMHMGIvuOAGz4jL0xK3ohTvQG/djdjyGPvgF+uLXmBO/RT98hHnRWm+bDzNhfvRBf8yLBdEfC+HrWBSrYzGsizWQ393sjGyzle3tydiUxHnNg5i87s+LfpgPC2F+LI0FMBD9sQoWxKZYCNthYRyARXAoFsVJWBKnYSlZn1EG38EA3IyVcDsG4lEMws9xPp7EKngJq+ENrIlPsBaaTHzPoAsGowfWw2zYEHNiI3wVG2NJbII1sCkG43ysj80xFFtgO2yF3TAUY7E1DsY2OALb4mTsiLOxE87FzrgYu+BSDMfl2A23Ym/cg9F4HPvjSYzBm3J7bmF3fIgR6MZ7FIk5cT7mwoFYCuOwBg7GpjgcO+II7IkjMRbfxDgchaNxDMbjWEzEcbhGlr8OJ+AOnIiHcRKewsl4Wea7itPxNs5APhtKAmbB2eiB8zA7kp/fof98nthSq8xKyh7OT56X5flZbECsKymOlEBaQ0omnSXdIjnxpehHKkWqS2pH6kuautrsmEv2bzSXrGd74/lkN/8fzSnb5G80r+zK1eYXNrfsQ8f8si90ftkk3puzpMckH37slSWFkGJIU0lrSMmkC6T7JE++vIutccxJqygvff6/XuEDe1mnAPyX5v+zzqFWzUdRx5CeKts7csl98CM9sL6SOoda6lpTh4uxHy/GeBw/sZz9+C9G43dqefVzsRiN66r1V3r+PrxaX5/0+3YY9+l5cX100ut74RVmjbeOXO7X1C/xt8uDvSqZVu5JSq+vScb7KmW0T9LfrU+PcZ+Y9Pu+GPdVSr8PjXFfmYz3kTLuS5TxPkkvqi9Ren2/ONRKkO3zJj/rCfLzWorEQ9QHWc2K2dEDxbh5SB8OfhP/+W/oE/wNSJa/pfm95fj9+zf6/fvMb9//o9+9f5ffvC/q967jt+6/9lvX9js3xfGb1fFwPBwPx8PxeEGPl3v9z7Al1qv/f3H+f+t86xMM5vSfYDCn/wS7Of1tMbN+HnwZs9jP2y/jTmnmu3cjZjyve02tToIASfY1LCF9wCs1l6TWSXAkZI2EfZ2ENjZSD5G3gjp2iGWpvD9P3nP2gXjuY6rFsWujFDKqy2B9RnUZ2n37XcTrrxvUbWjL2o/rKuad//np02Xi9TBzZl6fYDeG6qrU17hLrr5+vNJBtjH9rrN8ZjUeqy73qdinYOpwXlXHefJcZo3N447RXOxlH4O5yBkTjPISxTp7mQ3HWiRPCnnGiDzDzUZzf7pb18MacqdzfE8oOQ3H4sttmytUlD3KXJklpplG0I+ghtgHP7Ws7IxP/5Yox26sO3V8nb6ijARzV7NnmjG8xLz8bH+ceH0i+2jbfnmzs25M4XiRZ4i5vtlLt55ulQIU7X2fLrbHm+dy3hCx71l0x7Z7r0HRfdT3Za3I/x5bznsl9zfZGuN5oJJdLaejKMed5+RRyy0lyu3km3a8/Mfsz2DqzfIq+rFV9GOjaOOW7CMV87aNE6KNf1HLh/0l/ojU1ou8aBvX5LKcBzmbzD9ZjsHiJedQ87PV0v352NzqmBUXxL7IcQSWqPfuq+MX/KDFKtliF7VYRVvsiBYLsMU+0mIVbLEHS9VYeVts/LK/Nh4AMfGZE/nk55CYeA86qfOv/73rHKuKOsc+B84OT1za2WPBsd9yl60wYKyjztFR5/g=
*/