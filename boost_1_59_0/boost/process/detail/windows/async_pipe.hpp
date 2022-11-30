// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_ASYNC_PIPE_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_ASYNC_PIPE_HPP_

#include <boost/winapi/basic_types.hpp>
#include <boost/winapi/pipes.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/file_management.hpp>
#include <boost/winapi/get_last_error.hpp>
#include <boost/winapi/access_rights.hpp>
#include <boost/winapi/process.hpp>
#include <boost/process/detail/windows/basic_pipe.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/windows/stream_handle.hpp>
#include <atomic>
#include <system_error>
#include <string>

namespace boost { namespace process { namespace detail { namespace windows {

inline std::string make_pipe_name()
{
    std::string name = "\\\\.\\pipe\\boost_process_auto_pipe_";

    auto pid = ::boost::winapi::GetCurrentProcessId();

    static std::atomic_size_t cnt{0};
    name += std::to_string(pid);
    name += "_";
    name += std::to_string(cnt++);

    return name;
}

class async_pipe
{
    ::boost::asio::windows::stream_handle _source;
    ::boost::asio::windows::stream_handle _sink  ;

    inline async_pipe(boost::asio::io_context & ios_source,
                      boost::asio::io_context & ios_sink,
                      const std::string & name, bool private_);

public:
    typedef ::boost::winapi::HANDLE_ native_handle_type;
    typedef ::boost::asio::windows::stream_handle   handle_type;
    typedef typename handle_type::executor_type executor_type;

    async_pipe(boost::asio::io_context & ios) : async_pipe(ios, ios, make_pipe_name(), true) {}
    async_pipe(boost::asio::io_context & ios_source, boost::asio::io_context & ios_sink)
                : async_pipe(ios_source, ios_sink, make_pipe_name(), true) {}

    async_pipe(boost::asio::io_context & ios, const std::string & name)
                : async_pipe(ios, ios, name, false) {}

    async_pipe(boost::asio::io_context & ios_source, boost::asio::io_context & ios_sink, const std::string & name)
            : async_pipe(ios_source, ios_sink, name, false) {}



    inline async_pipe(const async_pipe& rhs);
    async_pipe(async_pipe&& rhs)  : _source(std::move(rhs._source)), _sink(std::move(rhs._sink))
    {
    }
    template<class CharT, class Traits = std::char_traits<CharT>>
    explicit async_pipe(::boost::asio::io_context & ios_source,
                        ::boost::asio::io_context & ios_sink,
                         const basic_pipe<CharT, Traits> & p)
            : _source(ios_source, p.native_source()), _sink(ios_sink, p.native_sink())
    {
    }

    template<class CharT, class Traits = std::char_traits<CharT>>
    explicit async_pipe(boost::asio::io_context & ios, const basic_pipe<CharT, Traits> & p)
            : async_pipe(ios, ios, p)
    {
    }

    template<class CharT, class Traits = std::char_traits<CharT>>
    inline async_pipe& operator=(const basic_pipe<CharT, Traits>& p);
    inline async_pipe& operator=(const async_pipe& rhs);

    inline async_pipe& operator=(async_pipe&& rhs);

    ~async_pipe()
    {
        boost::system::error_code ec;
        close(ec);
    }

    template<class CharT, class Traits = std::char_traits<CharT>>
    inline explicit operator basic_pipe<CharT, Traits>() const;

    void cancel()
    {
        if (_sink.is_open())
            _sink.cancel();
        if (_source.is_open())
            _source.cancel();
    }

    void close()
    {
        if (_sink.is_open())
        {
            _sink.close();
            _sink = handle_type(_sink.get_executor());
        }
        if (_source.is_open())
        {
            _source.close();
            _source = handle_type(_source.get_executor());
        }
    }
    void close(boost::system::error_code & ec)
    {
        if (_sink.is_open())
        {
            _sink.close(ec);
            _sink = handle_type(_sink.get_executor());
        }
        if (_source.is_open())
        {
            _source.close(ec);
            _source = handle_type(_source.get_executor());
        }
    }

    bool is_open() const
    {
        return  _sink.is_open() || _source.is_open();
    }
    void async_close()
    {
        if (_sink.is_open())
            boost::asio::post(_sink.get_executor(),   [this]{_sink.close();});
        if (_source.is_open())
            boost::asio::post(_source.get_executor(), [this]{_source.close();});
    }

    template<typename MutableBufferSequence>
    std::size_t read_some(const MutableBufferSequence & buffers)
    {
        return _source.read_some(buffers);
    }
    template<typename MutableBufferSequence>
    std::size_t write_some(const MutableBufferSequence & buffers)
    {
        return _sink.write_some(buffers);
    }


    template<typename MutableBufferSequence>
    std::size_t read_some(const MutableBufferSequence & buffers, boost::system::error_code & ec) noexcept
    {
        return _source.read_some(buffers, ec);
    }
    template<typename MutableBufferSequence>
    std::size_t write_some(const MutableBufferSequence & buffers, boost::system::error_code & ec) noexcept
    {
        return _sink.write_some(buffers, ec);
    }

    native_handle_type native_source() const {return const_cast<boost::asio::windows::stream_handle&>(_source).native_handle();}
    native_handle_type native_sink  () const {return const_cast<boost::asio::windows::stream_handle&>(_sink  ).native_handle();}

    template<typename MutableBufferSequence,
             typename ReadHandler>
    BOOST_ASIO_INITFN_RESULT_TYPE(
          ReadHandler, void(boost::system::error_code, std::size_t))
      async_read_some(
        const MutableBufferSequence & buffers,
              ReadHandler &&handler)
    {
        return _source.async_read_some(buffers, std::forward<ReadHandler>(handler));
    }

    template<typename ConstBufferSequence,
             typename WriteHandler>
    BOOST_ASIO_INITFN_RESULT_TYPE(
              WriteHandler, void(boost::system::error_code, std::size_t))
      async_write_some(
        const ConstBufferSequence & buffers,
        WriteHandler && handler)
    {
        return _sink.async_write_some(buffers,  std::forward<WriteHandler>(handler));
    }

    const handle_type & sink  () const & {return _sink;}
    const handle_type & source() const & {return _source;}

    handle_type && source() && { return std::move(_source); }
    handle_type && sink()   && { return std::move(_sink); }

    handle_type source(::boost::asio::io_context& ios) &&
    {
        ::boost::asio::windows::stream_handle stolen(ios.get_executor(), _source.native_handle());
        boost::system::error_code ec;
        _source.assign(::boost::winapi::INVALID_HANDLE_VALUE_, ec);
        return stolen;
    }
    handle_type sink  (::boost::asio::io_context& ios) &&
    {
        ::boost::asio::windows::stream_handle stolen(ios.get_executor(), _sink.native_handle());
        boost::system::error_code ec;
        _sink.assign(::boost::winapi::INVALID_HANDLE_VALUE_, ec);
        return stolen;
    }

    handle_type source(::boost::asio::io_context& ios) const &
    {
        auto proc = ::boost::winapi::GetCurrentProcess();

        ::boost::winapi::HANDLE_ source;
        auto source_in = const_cast<handle_type&>(_source).native_handle();
        if (source_in == ::boost::winapi::INVALID_HANDLE_VALUE_)
            source = ::boost::winapi::INVALID_HANDLE_VALUE_;
        else if (!::boost::winapi::DuplicateHandle(
                proc, source_in, proc, &source, 0,
                static_cast<::boost::winapi::BOOL_>(true),
                 ::boost::winapi::DUPLICATE_SAME_ACCESS_))
            throw_last_error("Duplicate Pipe Failed");

        return ::boost::asio::windows::stream_handle(ios.get_executor(), source);
    }
    handle_type sink  (::boost::asio::io_context& ios) const &
    {
        auto proc = ::boost::winapi::GetCurrentProcess();

        ::boost::winapi::HANDLE_ sink;
        auto sink_in = const_cast<handle_type&>(_sink).native_handle();
        if (sink_in == ::boost::winapi::INVALID_HANDLE_VALUE_)
            sink = ::boost::winapi::INVALID_HANDLE_VALUE_;
        else if (!::boost::winapi::DuplicateHandle(
                proc, sink_in, proc, &sink, 0,
                static_cast<::boost::winapi::BOOL_>(true),
                 ::boost::winapi::DUPLICATE_SAME_ACCESS_))
            throw_last_error("Duplicate Pipe Failed");

        return ::boost::asio::windows::stream_handle(ios.get_executor(), sink);
    }
};

async_pipe::async_pipe(const async_pipe& p)  :
    _source(const_cast<handle_type&>(p._source).get_executor()),
    _sink  (const_cast<handle_type&>(p._sink).get_executor())
{

    auto proc = ::boost::winapi::GetCurrentProcess();

    ::boost::winapi::HANDLE_ source;
    ::boost::winapi::HANDLE_ sink;

    //cannot get the handle from a const object.
    auto source_in = const_cast<handle_type&>(p._source).native_handle();
    auto sink_in   = const_cast<handle_type&>(p._sink).native_handle();

    if (source_in == ::boost::winapi::INVALID_HANDLE_VALUE_)
        source = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, source_in, proc, &source, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    if (sink_in   == ::boost::winapi::INVALID_HANDLE_VALUE_)
        sink = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, sink_in, proc, &sink, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    if (source != ::boost::winapi::INVALID_HANDLE_VALUE_)
        _source.assign(source);
    if (sink != ::boost::winapi::INVALID_HANDLE_VALUE_)
        _sink.  assign(sink);
}


async_pipe::async_pipe(boost::asio::io_context & ios_source,
                       boost::asio::io_context & ios_sink,
                       const std::string & name, bool private_) : _source(ios_source), _sink(ios_sink)
{
    static constexpr int FILE_FLAG_OVERLAPPED_  = 0x40000000; //temporary

    ::boost::winapi::HANDLE_ source = ::boost::winapi::create_named_pipe(
#if defined(BOOST_NO_ANSI_APIS)
            ::boost::process::detail::convert(name).c_str(),
#else
            name.c_str(),
#endif
            ::boost::winapi::PIPE_ACCESS_INBOUND_
            | FILE_FLAG_OVERLAPPED_, //write flag
            0, private_ ? 1 : ::boost::winapi::PIPE_UNLIMITED_INSTANCES_, 8192, 8192, 0, nullptr);


    if (source == boost::winapi::INVALID_HANDLE_VALUE_)
        ::boost::process::detail::throw_last_error("create_named_pipe(" + name + ") failed");

    _source.assign(source);

    ::boost::winapi::HANDLE_ sink = boost::winapi::create_file(
#if defined(BOOST_NO_ANSI_APIS)
            ::boost::process::detail::convert(name).c_str(),
#else
            name.c_str(),
#endif
            ::boost::winapi::GENERIC_WRITE_, 0, nullptr,
            ::boost::winapi::OPEN_EXISTING_,
            FILE_FLAG_OVERLAPPED_, //to allow read
            nullptr);

    if (sink == ::boost::winapi::INVALID_HANDLE_VALUE_)
        ::boost::process::detail::throw_last_error("create_file() failed");

    _sink.assign(sink);
}

template<class CharT, class Traits>
async_pipe& async_pipe::operator=(const basic_pipe<CharT, Traits> & p)
{
    auto proc = ::boost::winapi::GetCurrentProcess();

    ::boost::winapi::HANDLE_ source;
    ::boost::winapi::HANDLE_ sink;

    //cannot get the handle from a const object.
    auto source_in = p.native_source();
    auto sink_in   = p.native_sink();

    if (source_in == ::boost::winapi::INVALID_HANDLE_VALUE_)
        source = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, source_in.native_handle(), proc, &source, 0,
            static_cast<::boost::winapi::BOOL_>(true),
            ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    if (sink_in   == ::boost::winapi::INVALID_HANDLE_VALUE_)
        sink = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, sink_in.native_handle(), proc, &sink, 0,
            static_cast<::boost::winapi::BOOL_>(true),
            ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    //so we also assign the io_context
    if (source != ::boost::winapi::INVALID_HANDLE_VALUE_)
        _source.assign(source);

    if (sink != ::boost::winapi::INVALID_HANDLE_VALUE_)
        _sink.assign(sink);

    return *this;
}

async_pipe& async_pipe::operator=(const async_pipe & p)
{
    auto proc = ::boost::winapi::GetCurrentProcess();

    ::boost::winapi::HANDLE_ source;
    ::boost::winapi::HANDLE_ sink;

    //cannot get the handle from a const object.
    auto &source_in = const_cast<::boost::asio::windows::stream_handle &>(p._source);
    auto &sink_in   = const_cast<::boost::asio::windows::stream_handle &>(p._sink);

    source_in.get_executor();

    if (source_in.native_handle() == ::boost::winapi::INVALID_HANDLE_VALUE_)
        source = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, source_in.native_handle(), proc, &source, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    if (sink_in.native_handle()   == ::boost::winapi::INVALID_HANDLE_VALUE_)
        sink = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, sink_in.native_handle(), proc, &sink, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    //so we also assign the io_context
    if (source != ::boost::winapi::INVALID_HANDLE_VALUE_)
        _source = ::boost::asio::windows::stream_handle(source_in.get_executor(), source);
    else
        _source = ::boost::asio::windows::stream_handle(source_in.get_executor());

    if (sink != ::boost::winapi::INVALID_HANDLE_VALUE_)
        _sink   = ::boost::asio::windows::stream_handle(source_in.get_executor(), sink);
    else
        _sink   = ::boost::asio::windows::stream_handle(source_in.get_executor());

    return *this;
}

async_pipe& async_pipe::operator=(async_pipe && rhs)
{
    _source = std::move(rhs._source);
    _sink = std::move(rhs._sink);
    return *this;
}

template<class CharT, class Traits>
async_pipe::operator basic_pipe<CharT, Traits>() const
{
    auto proc = ::boost::winapi::GetCurrentProcess();

    ::boost::winapi::HANDLE_ source;
    ::boost::winapi::HANDLE_ sink;

    //cannot get the handle from a const object.
    auto source_in = const_cast<::boost::asio::windows::stream_handle &>(_source).native_handle();
    auto sink_in   = const_cast<::boost::asio::windows::stream_handle &>(_sink).native_handle();

    if (source_in == ::boost::winapi::INVALID_HANDLE_VALUE_)
        source = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, source_in, proc, &source, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    if (sink_in == ::boost::winapi::INVALID_HANDLE_VALUE_)
        sink = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, sink_in, proc, &sink, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    return basic_pipe<CharT, Traits>{source, sink};
}

inline bool operator==(const async_pipe & lhs, const async_pipe & rhs)
{
    return compare_handles(lhs.native_source(), rhs.native_source()) &&
           compare_handles(lhs.native_sink(),   rhs.native_sink());
}

inline bool operator!=(const async_pipe & lhs, const async_pipe & rhs)
{
    return !compare_handles(lhs.native_source(), rhs.native_source()) ||
           !compare_handles(lhs.native_sink(),   rhs.native_sink());
}

template<class Char, class Traits>
inline bool operator==(const async_pipe & lhs, const basic_pipe<Char, Traits> & rhs)
{
    return compare_handles(lhs.native_source(), rhs.native_source()) &&
           compare_handles(lhs.native_sink(),   rhs.native_sink());
}

template<class Char, class Traits>
inline bool operator!=(const async_pipe & lhs, const basic_pipe<Char, Traits> & rhs)
{
    return !compare_handles(lhs.native_source(), rhs.native_source()) ||
           !compare_handles(lhs.native_sink(),   rhs.native_sink());
}

template<class Char, class Traits>
inline bool operator==(const basic_pipe<Char, Traits> & lhs, const async_pipe & rhs)
{
    return compare_handles(lhs.native_source(), rhs.native_source()) &&
           compare_handles(lhs.native_sink(),   rhs.native_sink());
}

template<class Char, class Traits>
inline bool operator!=(const basic_pipe<Char, Traits> & lhs, const async_pipe & rhs)
{
    return !compare_handles(lhs.native_source(), rhs.native_source()) ||
           !compare_handles(lhs.native_sink(),   rhs.native_sink());
}

}}}}

#endif /* INCLUDE_BOOST_PIPE_DETAIL_WINDOWS_ASYNC_PIPE_HPP_ */

/* async_pipe.hpp
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
*/