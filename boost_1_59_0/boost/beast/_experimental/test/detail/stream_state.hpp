//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TEST_DETAIL_STREAM_STATE_HPP
#define BOOST_BEAST_TEST_DETAIL_STREAM_STATE_HPP

#include <boost/asio/any_io_executor.hpp>
#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/_experimental/test/fail_count.hpp>
#include <boost/beast/core/detail/service_base.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <vector>

namespace boost {
namespace beast {
namespace test {
namespace detail {

struct stream_state;

struct stream_service_impl
{
    std::mutex m_;
    std::vector<stream_state*> v_;

    BOOST_BEAST_DECL
    void
    remove(stream_state& impl);
};

//------------------------------------------------------------------------------

class stream_service
    : public beast::detail::service_base<stream_service>
{
    boost::shared_ptr<detail::stream_service_impl> sp_;

    BOOST_BEAST_DECL
    void
    shutdown() override;

public:
    BOOST_BEAST_DECL
    explicit
    stream_service(net::execution_context& ctx);

    BOOST_BEAST_DECL
    static
    auto
    make_impl(
        net::any_io_executor exec,
        test::fail_count* fc) ->
            boost::shared_ptr<detail::stream_state>;
};

//------------------------------------------------------------------------------

struct stream_read_op_base
{
    virtual ~stream_read_op_base() = default;
    virtual void operator()(error_code ec) = 0;
};

//------------------------------------------------------------------------------

enum class stream_status
{
    ok,
    eof,
};

//------------------------------------------------------------------------------

struct stream_state
{
    net::any_io_executor exec;
    boost::weak_ptr<stream_service_impl> wp;
    std::mutex m;
    flat_buffer b;
    std::condition_variable cv;
    std::unique_ptr<stream_read_op_base> op;
    stream_status code = stream_status::ok;
    fail_count* fc = nullptr;
    std::size_t nread = 0;
    std::size_t nread_bytes = 0;
    std::size_t nwrite = 0;
    std::size_t nwrite_bytes = 0;
    std::size_t read_max =
        (std::numeric_limits<std::size_t>::max)();
    std::size_t write_max =
        (std::numeric_limits<std::size_t>::max)();

    BOOST_BEAST_DECL
    stream_state(
        net::any_io_executor exec_,
        boost::weak_ptr<stream_service_impl> wp_,
        fail_count* fc_);

    BOOST_BEAST_DECL
    ~stream_state();

    BOOST_BEAST_DECL
    void
    remove() noexcept;

    BOOST_BEAST_DECL
    void
    notify_read();

    BOOST_BEAST_DECL
    void
    cancel_read();
};



} // detail
} // test
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/_experimental/test/detail/stream_state.ipp>
#endif

#endif // BOOST_BEAST_TEST_DETAIL_STREAM_STATE_HPP

/* stream_state.hpp
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
*/