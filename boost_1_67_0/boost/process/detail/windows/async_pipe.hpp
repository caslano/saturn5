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