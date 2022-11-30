//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TEST_IMPL_STREAM_HPP
#define BOOST_BEAST_TEST_IMPL_STREAM_HPP

#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/detail/service_base.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/post.hpp>
#include <mutex>
#include <stdexcept>
#include <vector>

namespace boost {
namespace beast {
namespace test {

//------------------------------------------------------------------------------

template<class Executor>
template<class Handler, class Buffers>
class basic_stream<Executor>::read_op : public detail::stream_read_op_base
{
    using ex1_type =
        executor_type;
    using ex2_type
        = net::associated_executor_t<Handler, ex1_type>;

    struct lambda
    {
        Handler h_;
        boost::weak_ptr<detail::stream_state> wp_;
        Buffers b_;
#if defined(BOOST_ASIO_NO_TS_EXECUTORS)
        net::any_io_executor wg2_;
#else // defined(BOOST_ASIO_NO_TS_EXECUTORS)
        net::executor_work_guard<ex2_type> wg2_;
#endif // defined(BOOST_ASIO_NO_TS_EXECUTORS)

        lambda(lambda&&) = default;
        lambda(lambda const&) = default;

        template<class Handler_>
        lambda(
            Handler_&& h,
            boost::shared_ptr<detail::stream_state> const& s,
            Buffers const& b)
            : h_(std::forward<Handler_>(h))
            , wp_(s)
            , b_(b)
#if defined(BOOST_ASIO_NO_TS_EXECUTORS)
            , wg2_(net::prefer(
                net::get_associated_executor(
                  h_, s->exec),
                net::execution::outstanding_work.tracked))
#else // defined(BOOST_ASIO_NO_TS_EXECUTORS)
            , wg2_(net::get_associated_executor(
                h_, s->exec))
#endif // defined(BOOST_ASIO_NO_TS_EXECUTORS)
        {
        }

        using allocator_type = net::associated_allocator_t<Handler>;

        allocator_type get_allocator() const noexcept
        {
          return net::get_associated_allocator(h_);
        }

        void
        operator()(error_code ec)
        {
            std::size_t bytes_transferred = 0;
            auto sp = wp_.lock();
            if(! sp)
                ec = net::error::operation_aborted;
            if(! ec)
            {
                std::lock_guard<std::mutex> lock(sp->m);
                BOOST_ASSERT(! sp->op);
                if(sp->b.size() > 0)
                {
                    bytes_transferred =
                        net::buffer_copy(
                            b_, sp->b.data(), sp->read_max);
                    sp->b.consume(bytes_transferred);
                    sp->nread_bytes += bytes_transferred;
                }
                else if (buffer_bytes(b_) > 0)
                {
                    ec = net::error::eof;
                }
            }

#if defined(BOOST_ASIO_NO_TS_EXECUTORS)
            net::dispatch(wg2_,
                beast::bind_front_handler(std::move(h_),
                    ec, bytes_transferred));
            wg2_ = net::any_io_executor(); // probably unnecessary
#else // defined(BOOST_ASIO_NO_TS_EXECUTORS)
            net::dispatch(wg2_.get_executor(),
                beast::bind_front_handler(std::move(h_),
                    ec, bytes_transferred));
            wg2_.reset();
#endif // defined(BOOST_ASIO_NO_TS_EXECUTORS)
        }
    };

    lambda fn_;
#if defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)
    net::executor_work_guard<net::any_io_executor> wg1_;
#else
    net::any_io_executor wg1_;
#endif

public:
    template<class Handler_>
    read_op(
        Handler_&& h,
        boost::shared_ptr<detail::stream_state> const& s,
        Buffers const& b)
        : fn_(std::forward<Handler_>(h), s, b)
#if defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)
        , wg1_(s->exec)
#else
        , wg1_(net::prefer(s->exec,
            net::execution::outstanding_work.tracked))
#endif
    {
    }

    void
    operator()(error_code ec) override
    {
#if defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)
        net::post(wg1_.get_executor(),
            beast::bind_front_handler(std::move(fn_), ec));
        wg1_.reset();
#else
        net::post(wg1_, beast::bind_front_handler(std::move(fn_), ec));
        wg1_ = net::any_io_executor(); // probably unnecessary
#endif
    }
};

template<class Executor>
struct basic_stream<Executor>::run_read_op
{
    template<
        class ReadHandler,
        class MutableBufferSequence>
    void
    operator()(
        ReadHandler&& h,
        boost::shared_ptr<detail::stream_state> const& in,
        MutableBufferSequence const& buffers)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<ReadHandler,
                void(error_code, std::size_t)>::value,
            "ReadHandler type requirements not met");

        initiate_read(
            in,
            std::unique_ptr<detail::stream_read_op_base>{
            new read_op<
                typename std::decay<ReadHandler>::type,
                MutableBufferSequence>(
                    std::move(h),
                    in,
                    buffers)},
            buffer_bytes(buffers));
    }
};

template<class Executor>
struct basic_stream<Executor>::run_write_op
{
    template<
        class WriteHandler,
        class ConstBufferSequence>
    void
    operator()(
        WriteHandler&& h,
        boost::shared_ptr<detail::stream_state> in_,
        boost::weak_ptr<detail::stream_state> out_,
        ConstBufferSequence const& buffers)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<WriteHandler,
                void(error_code, std::size_t)>::value,
            "WriteHandler type requirements not met");

        ++in_->nwrite;
        auto const upcall = [&](error_code ec, std::size_t n)
        {
            net::post(
                in_->exec,
                beast::bind_front_handler(std::move(h), ec, n));
        };

        // test failure
        error_code ec;
        std::size_t n = 0;
        if(in_->fc && in_->fc->fail(ec))
            return upcall(ec, n);

        // A request to write 0 bytes to a stream is a no-op.
        if(buffer_bytes(buffers) == 0)
            return upcall(ec, n);

        // connection closed
        auto out = out_.lock();
        if(! out)
            return upcall(net::error::connection_reset, n);

        // copy buffers
        n = std::min<std::size_t>(
            buffer_bytes(buffers), in_->write_max);
        {
            std::lock_guard<std::mutex> lock(out->m);
            n = net::buffer_copy(out->b.prepare(n), buffers);
            out->b.commit(n);
            out->nwrite_bytes += n;
            out->notify_read();
        }
        BOOST_ASSERT(! ec);
        upcall(ec, n);
    }
};

//------------------------------------------------------------------------------

template<class Executor>
template<class MutableBufferSequence>
std::size_t
basic_stream<Executor>::
read_some(MutableBufferSequence const& buffers)
{
    static_assert(net::is_mutable_buffer_sequence<
            MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");
    error_code ec;
    auto const n = read_some(buffers, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return n;
}

template<class Executor>
template<class MutableBufferSequence>
std::size_t
basic_stream<Executor>::
read_some(MutableBufferSequence const& buffers,
    error_code& ec)
{
    static_assert(net::is_mutable_buffer_sequence<
            MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");

    ++in_->nread;

    // test failure
    if(in_->fc && in_->fc->fail(ec))
        return 0;

    // A request to read 0 bytes from a stream is a no-op.
    if(buffer_bytes(buffers) == 0)
    {
        ec = {};
        return 0;
    }

    std::unique_lock<std::mutex> lock{in_->m};
    BOOST_ASSERT(! in_->op);
    in_->cv.wait(lock,
        [&]()
        {
            return
                in_->b.size() > 0 ||
                in_->code != detail::stream_status::ok;
        });

    // deliver bytes before eof
    if(in_->b.size() > 0)
    {
        auto const n = net::buffer_copy(
            buffers, in_->b.data(), in_->read_max);
        in_->b.consume(n);
        in_->nread_bytes += n;
        return n;
    }

    // deliver error
    BOOST_ASSERT(in_->code != detail::stream_status::ok);
    ec = net::error::eof;
    return 0;
}

template<class Executor>
template<class MutableBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void(error_code, std::size_t)) ReadHandler>
BOOST_ASIO_INITFN_RESULT_TYPE(ReadHandler, void(error_code, std::size_t))
basic_stream<Executor>::
async_read_some(
    MutableBufferSequence const& buffers,
    ReadHandler&& handler)
{
    static_assert(net::is_mutable_buffer_sequence<
            MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");

    return net::async_initiate<
        ReadHandler,
        void(error_code, std::size_t)>(
            run_read_op{},
            handler,
            in_,
            buffers);
}

template<class Executor>
template<class ConstBufferSequence>
std::size_t
basic_stream<Executor>::
write_some(ConstBufferSequence const& buffers)
{
    static_assert(net::is_const_buffer_sequence<
            ConstBufferSequence>::value,
        "ConstBufferSequence type requirements not met");
    error_code ec;
    auto const bytes_transferred =
        write_some(buffers, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<class Executor>
template<class ConstBufferSequence>
std::size_t
basic_stream<Executor>::
write_some(
    ConstBufferSequence const& buffers, error_code& ec)
{
    static_assert(net::is_const_buffer_sequence<
            ConstBufferSequence>::value,
        "ConstBufferSequence type requirements not met");

    ++in_->nwrite;

    // test failure
    if(in_->fc && in_->fc->fail(ec))
        return 0;

    // A request to write 0 bytes to a stream is a no-op.
    if(buffer_bytes(buffers) == 0)
    {
        ec = {};
        return 0;
    }

    // connection closed
    auto out = out_.lock();
    if(! out)
    {
        ec = net::error::connection_reset;
        return 0;
    }

    // copy buffers
    auto n = std::min<std::size_t>(
        buffer_bytes(buffers), in_->write_max);
    {
        std::lock_guard<std::mutex> lock(out->m);
        n = net::buffer_copy(out->b.prepare(n), buffers);
        out->b.commit(n);
        out->nwrite_bytes += n;
        out->notify_read();
    }
    return n;
}

template<class Executor>
template<class ConstBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void(error_code, std::size_t)) WriteHandler>
BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler, void(error_code, std::size_t))
basic_stream<Executor>::
async_write_some(
    ConstBufferSequence const& buffers,
    WriteHandler&& handler)
{
    static_assert(net::is_const_buffer_sequence<
            ConstBufferSequence>::value,
        "ConstBufferSequence type requirements not met");

    return net::async_initiate<
        WriteHandler,
        void(error_code, std::size_t)>(
            run_write_op{},
            handler,
            in_,
            out_,
            buffers);
}

//------------------------------------------------------------------------------

template<class Executor, class TeardownHandler>
void
async_teardown(
    role_type,
    basic_stream<Executor>& s,
    TeardownHandler&& handler)
{
    error_code ec;
    if( s.in_->fc &&
        s.in_->fc->fail(ec))
        return net::post(
            s.get_executor(),
            beast::bind_front_handler(
                std::move(handler), ec));
    s.close();
    if( s.in_->fc &&
        s.in_->fc->fail(ec))
        ec = net::error::eof;
    else
        ec = {};

    net::post(
        s.get_executor(),
        beast::bind_front_handler(
            std::move(handler), ec));
}

//------------------------------------------------------------------------------

template<class Executor, class Arg1, class... ArgN>
basic_stream<Executor>
connect(stream& to, Arg1&& arg1, ArgN&&... argn)
{
    stream from{
        std::forward<Arg1>(arg1),
        std::forward<ArgN>(argn)...};
    from.connect(to);
    return from;
}

namespace detail
{
template<class To>
struct extract_executor_op
{
    To operator()(net::any_io_executor& ex) const
    {
        assert(ex.template target<To>());
        return *ex.template target<To>();
    }
};

template<>
struct extract_executor_op<net::any_io_executor>
{
    net::any_io_executor operator()(net::any_io_executor& ex) const
    {
        return ex;
    }
};
}

template<class Executor>
auto basic_stream<Executor>::get_executor() noexcept -> executor_type
{
    return detail::extract_executor_op<Executor>()(in_->exec);
}

} // test
} // beast
} // boost

#endif

/* stream.hpp
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
*/