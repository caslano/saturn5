//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_FILE_BODY_WIN32_HPP
#define BOOST_BEAST_HTTP_IMPL_FILE_BODY_WIN32_HPP

#if BOOST_BEAST_USE_WIN32_FILE

#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/buffers_range.hpp>
#include <boost/beast/core/detail/clamp.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/http/serializer.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/windows/overlapped_ptr.hpp>
#include <boost/make_unique.hpp>
#include <boost/smart_ptr/make_shared_array.hpp>
#include <boost/winapi/basic_types.hpp>
#include <boost/winapi/error_codes.hpp>
#include <boost/winapi/get_last_error.hpp>
#include <algorithm>
#include <cstring>

namespace boost {
namespace beast {
namespace http {

namespace detail {
template<class, class, bool, class, class>
class write_some_win32_op;
} // detail

template<>
struct basic_file_body<file_win32>
{
    using file_type = file_win32;

    class writer;
    class reader;

    //--------------------------------------------------------------------------

    class value_type
    {
        friend class writer;
        friend class reader;
        friend struct basic_file_body<file_win32>;

        template<class, class, bool, class, class>
        friend class detail::write_some_win32_op;
        template<
            class Protocol, class Executor,
            bool isRequest, class Fields>
        friend
        std::size_t
        write_some(
            net::basic_stream_socket<Protocol, Executor>& sock,
            serializer<isRequest,
                basic_file_body<file_win32>, Fields>& sr,
            error_code& ec);

        file_win32 file_;
        std::uint64_t size_ = 0;    // cached file size
        std::uint64_t first_;       // starting offset of the range
        std::uint64_t last_;        // ending offset of the range

    public:
        ~value_type() = default;
        value_type() = default;
        value_type(value_type&& other) = default;
        value_type& operator=(value_type&& other) = default;

        file_win32& file()
        {
            return file_;
        }

        bool
        is_open() const
        {
            return file_.is_open();
        }

        std::uint64_t
        size() const
        {
            return size_;
        }

        void
        close();

        void
        open(char const* path, file_mode mode, error_code& ec);

        void
        reset(file_win32&& file, error_code& ec);
    };

    //--------------------------------------------------------------------------

    class writer
    {
        template<class, class, bool, class, class>
        friend class detail::write_some_win32_op;
        template<
            class Protocol, class Executor,
            bool isRequest, class Fields>
        friend
        std::size_t
        write_some(
            net::basic_stream_socket<Protocol, Executor>& sock,
            serializer<isRequest,
                basic_file_body<file_win32>, Fields>& sr,
            error_code& ec);

        value_type& body_;  // The body we are reading from
        std::uint64_t pos_; // The current position in the file
        char buf_[4096];    // Small buffer for reading

    public:
        using const_buffers_type =
            net::const_buffer;

        template<bool isRequest, class Fields>
        writer(header<isRequest, Fields>&, value_type& b)
            : body_(b)
            , pos_(body_.first_)
        {
            BOOST_ASSERT(body_.file_.is_open());
        }

        void
        init(error_code& ec)
        {
            BOOST_ASSERT(body_.file_.is_open());
            ec.clear();
        }

        boost::optional<std::pair<const_buffers_type, bool>>
        get(error_code& ec)
        {
            std::size_t const n = (std::min)(sizeof(buf_),
                beast::detail::clamp(body_.last_ - pos_));
            if(n == 0)
            {
                ec = {};
                return boost::none;
            }
            auto const nread = body_.file_.read(buf_, n, ec);
            if(ec)
                return boost::none;
            if (nread == 0)
            {
                ec = error::short_read;
                return boost::none;
            }
            BOOST_ASSERT(nread != 0);
            pos_ += nread;
            ec = {};
            return {{
                {buf_, nread},          // buffer to return.
                pos_ < body_.last_}};   // `true` if there are more buffers.
        }
    };

    //--------------------------------------------------------------------------

    class reader
    {
        value_type& body_;

    public:
        template<bool isRequest, class Fields>
        explicit
        reader(header<isRequest, Fields>&, value_type& b)
            : body_(b)
        {
        }

        void
        init(boost::optional<
            std::uint64_t> const& content_length,
                error_code& ec)
        {
            // VFALCO We could reserve space in the file
            boost::ignore_unused(content_length);
            BOOST_ASSERT(body_.file_.is_open());
            ec = {};
        }

        template<class ConstBufferSequence>
        std::size_t
        put(ConstBufferSequence const& buffers,
            error_code& ec)
        {
            std::size_t nwritten = 0;
            for(auto buffer : beast::buffers_range_ref(buffers))
            {
                nwritten += body_.file_.write(
                    buffer.data(), buffer.size(), ec);
                if(ec)
                    return nwritten;
            }
            ec = {};
            return nwritten;
        }

        void
        finish(error_code& ec)
        {
            ec = {};
        }
    };

    //--------------------------------------------------------------------------

    static
    std::uint64_t
    size(value_type const& body)
    {
        return body.size();
    }
};

//------------------------------------------------------------------------------

inline
void
basic_file_body<file_win32>::
value_type::
close()
{
    error_code ignored;
    file_.close(ignored);
}

inline
void
basic_file_body<file_win32>::
value_type::
open(char const* path, file_mode mode, error_code& ec)
{
    file_.open(path, mode, ec);
    if(ec)
        return;
    size_ = file_.size(ec);
    if(ec)
    {
        close();
        return;
    }
    first_ = 0;
    last_ = size_;
}

inline
void
basic_file_body<file_win32>::
value_type::
reset(file_win32&& file, error_code& ec)
{
    if(file_.is_open())
    {
        error_code ignored;
        file_.close(ignored);
    }
    file_ = std::move(file);
    if(file_.is_open())
    {
        size_ = file_.size(ec);
        if(ec)
        {
            close();
            return;
        }
        first_ = 0;
        last_ = size_;
    }
}

//------------------------------------------------------------------------------

namespace detail {

template<class Unsigned>
boost::winapi::DWORD_
lowPart(Unsigned n)
{
    return static_cast<
        boost::winapi::DWORD_>(
            n & 0xffffffff);
}

template<class Unsigned>
boost::winapi::DWORD_
highPart(Unsigned n, std::true_type)
{
    return static_cast<
        boost::winapi::DWORD_>(
            (n>>32)&0xffffffff);
}

template<class Unsigned>
boost::winapi::DWORD_
highPart(Unsigned, std::false_type)
{
    return 0;
}

template<class Unsigned>
boost::winapi::DWORD_
highPart(Unsigned n)
{
    return highPart(n, std::integral_constant<
        bool, (sizeof(Unsigned)>4)>{});
}

class null_lambda
{
public:
    template<class ConstBufferSequence>
    void
    operator()(error_code&,
        ConstBufferSequence const&) const
    {
        BOOST_ASSERT(false);
    }
};

// https://github.com/boostorg/beast/issues/1815
// developer commentary:
// This function mimics the behaviour of ASIO.
// Perhaps the correct fix is to insist on the use
// of an appropriate error_condition to detect
// connection_reset and connection_refused?
inline
error_code
make_win32_error(
    boost::winapi::DWORD_ dwError) noexcept
{
    // from
    // https://github.com/boostorg/asio/blob/6534af41b471288091ae39f9ab801594189b6fc9/include/boost/asio/detail/impl/socket_ops.ipp#L842
    switch(dwError)
    {
    case boost::winapi::ERROR_NETNAME_DELETED_:
        return net::error::connection_reset;
    case boost::winapi::ERROR_PORT_UNREACHABLE_:
        return net::error::connection_refused;
    case boost::winapi::WSAEMSGSIZE_:
    case boost::winapi::ERROR_MORE_DATA_:
        return {};
    }
    return error_code(
        static_cast<int>(dwError),
        system_category());
}

inline
error_code
make_win32_error(
    error_code ec) noexcept
{
    if(ec.category() !=
        system_category())
        return ec;
    return make_win32_error(
        static_cast<boost::winapi::DWORD_>(
            ec.value()));
}

//------------------------------------------------------------------------------

#if BOOST_ASIO_HAS_WINDOWS_OVERLAPPED_PTR

template<
    class Protocol, class Executor,
    bool isRequest, class Fields,
    class Handler>
class write_some_win32_op
    : public beast::async_base<Handler, Executor>
{
    net::basic_stream_socket<
        Protocol, Executor>& sock_;
    serializer<isRequest,
        basic_file_body<file_win32>, Fields>& sr_;
    bool header_ = false;

public:
    template<class Handler_>
    write_some_win32_op(
        Handler_&& h,
        net::basic_stream_socket<
            Protocol, Executor>& s,
        serializer<isRequest,
            basic_file_body<file_win32>,Fields>& sr)
        : async_base<
            Handler, Executor>(
                std::forward<Handler_>(h),
                s.get_executor())
        , sock_(s)
        , sr_(sr)
    {
        (*this)();
    }

    void
    operator()()
    {
        if(! sr_.is_header_done())
        {
            header_ = true;
            sr_.split(true);
            return detail::async_write_some_impl(
                sock_, sr_, std::move(*this));
        }
        if(sr_.get().chunked())
        {
            return detail::async_write_some_impl(
                sock_, sr_, std::move(*this));
        }
        auto& w = sr_.writer_impl();
        boost::winapi::DWORD_ const nNumberOfBytesToWrite =
            static_cast<boost::winapi::DWORD_>(
            (std::min<std::uint64_t>)(
                (std::min<std::uint64_t>)(w.body_.last_ - w.pos_, sr_.limit()),
                (std::numeric_limits<boost::winapi::DWORD_>::max)()));
        net::windows::overlapped_ptr overlapped{
            sock_.get_executor(), std::move(*this)};
        // Note that we have moved *this, so we cannot access
        // the handler since it is now moved-from. We can still
        // access simple things like references and built-in types.
        auto& ov = *overlapped.get();
        ov.Offset = lowPart(w.pos_);
        ov.OffsetHigh = highPart(w.pos_);
        auto const bSuccess = ::TransmitFile(
            sock_.native_handle(),
            sr_.get().body().file_.native_handle(),
            nNumberOfBytesToWrite,
            0,
            overlapped.get(),
            nullptr,
            0);
        auto const dwError = boost::winapi::GetLastError();
        if(! bSuccess && dwError !=
            boost::winapi::ERROR_IO_PENDING_)
        {
            // VFALCO This needs review, is 0 the right number?
            // completed immediately (with error?)
            overlapped.complete(
                make_win32_error(dwError), 0);
            return;
        }
        overlapped.release();
    }

    void
    operator()(
        error_code ec,
        std::size_t bytes_transferred = 0)
    {
        if(ec)
        {
            ec = make_win32_error(ec);
        }
        else if(! ec && ! header_)
        {
            auto& w = sr_.writer_impl();
            w.pos_ += bytes_transferred;
            BOOST_ASSERT(w.pos_ <= w.body_.last_);
            if(w.pos_ >= w.body_.last_)
            {
                sr_.next(ec, null_lambda{});
                BOOST_ASSERT(! ec);
                BOOST_ASSERT(sr_.is_done());
            }
        }
        this->complete_now(ec, bytes_transferred);
    }
};

struct run_write_some_win32_op
{
    template<
        class Protocol, class Executor,
        bool isRequest, class Fields,
        class WriteHandler>
    void
    operator()(
        WriteHandler&& h,
        net::basic_stream_socket<
            Protocol, Executor>* s,
        serializer<isRequest,
            basic_file_body<file_win32>, Fields>* sr)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<WriteHandler,
            void(error_code, std::size_t)>::value,
            "WriteHandler type requirements not met");

        write_some_win32_op<
            Protocol, Executor,
            isRequest, Fields,
            typename std::decay<WriteHandler>::type>(
                std::forward<WriteHandler>(h), *s, *sr);
    }
};

#endif

} // detail

//------------------------------------------------------------------------------

template<
    class Protocol, class Executor,
    bool isRequest, class Fields>
std::size_t
write_some(
    net::basic_stream_socket<
        Protocol, Executor>& sock,
    serializer<isRequest,
        basic_file_body<file_win32>, Fields>& sr,
    error_code& ec)
{
    if(! sr.is_header_done())
    {
        sr.split(true);
        auto const bytes_transferred =
            detail::write_some_impl(sock, sr, ec);
        if(ec)
            return bytes_transferred;
        return bytes_transferred;
    }
    if(sr.get().chunked())
    {
        auto const bytes_transferred =
            detail::write_some_impl(sock, sr, ec);
        if(ec)
            return bytes_transferred;
        return bytes_transferred;
    }
    auto& w = sr.writer_impl();
    w.body_.file_.seek(w.pos_, ec);
    if(ec)
        return 0;
    boost::winapi::DWORD_ const nNumberOfBytesToWrite =
        static_cast<boost::winapi::DWORD_>(
        (std::min<std::uint64_t>)(
            (std::min<std::uint64_t>)(w.body_.last_ - w.pos_, sr.limit()),
            (std::numeric_limits<boost::winapi::DWORD_>::max)()));
    auto const bSuccess = ::TransmitFile(
        sock.native_handle(),
        w.body_.file_.native_handle(),
        nNumberOfBytesToWrite,
        0,
        nullptr,
        nullptr,
        0);
    if(! bSuccess)
    {
        ec = detail::make_win32_error(
            boost::winapi::GetLastError());
        return 0;
    }
    w.pos_ += nNumberOfBytesToWrite;
    BOOST_ASSERT(w.pos_ <= w.body_.last_);
    if(w.pos_ < w.body_.last_)
    {
        ec = {};
    }
    else
    {
        sr.next(ec, detail::null_lambda{});
        BOOST_ASSERT(! ec);
        BOOST_ASSERT(sr.is_done());
    }
    return nNumberOfBytesToWrite;
}

#if BOOST_ASIO_HAS_WINDOWS_OVERLAPPED_PTR

template<
    class Protocol, class Executor,
    bool isRequest, class Fields,
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
async_write_some(
    net::basic_stream_socket<
        Protocol, Executor>& sock,
    serializer<isRequest,
        basic_file_body<file_win32>, Fields>& sr,
    WriteHandler&& handler)
{  
    return net::async_initiate<
        WriteHandler,
        void(error_code, std::size_t)>(
            detail::run_write_some_win32_op{},
            handler,
            &sock,
            &sr);
}

#endif

} // http
} // beast
} // boost

#endif

#endif

/* file_body_win32.hpp
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
*/