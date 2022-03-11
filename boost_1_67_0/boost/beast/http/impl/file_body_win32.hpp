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
    class WriteHandler>
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