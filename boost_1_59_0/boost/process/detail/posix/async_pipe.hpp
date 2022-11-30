// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_ASYNC_PIPE_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_ASYNC_PIPE_HPP_


#include <boost/process/detail/posix/basic_pipe.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <boost/asio/post.hpp>
#include <system_error>
#include <string>
#include <utility>

namespace boost { namespace process { namespace detail { namespace posix {

class async_pipe
{
    ::boost::asio::posix::stream_descriptor _source;
    ::boost::asio::posix::stream_descriptor _sink  ;
public:
    typedef int native_handle_type;
    typedef ::boost::asio::posix::stream_descriptor handle_type;
    typedef typename handle_type::executor_type executor_type;

    executor_type get_executor()
    {
        return _source.get_executor();
    }

    inline async_pipe(boost::asio::io_context & ios) : async_pipe(ios, ios) {}

    inline async_pipe(boost::asio::io_context & ios_source,
                      boost::asio::io_context & ios_sink) : _source(ios_source), _sink(ios_sink)
    {
        int fds[2];
        if (::pipe(fds) == -1)
            boost::process::detail::throw_last_error("pipe(2) failed");

        _source.assign(fds[0]);
        _sink  .assign(fds[1]);
    };
    inline async_pipe(boost::asio::io_context & ios, const std::string & name)
        : async_pipe(ios, ios, name) {}

    inline async_pipe(boost::asio::io_context & ios_source,
                      boost::asio::io_context & io_sink, const std::string & name);
    inline async_pipe(const async_pipe& lhs);
    async_pipe(async_pipe&& lhs)  : _source(std::move(lhs._source)), _sink(std::move(lhs._sink))
    {
        lhs._source = ::boost::asio::posix::stream_descriptor{lhs._source.get_executor()};
        lhs._sink   = ::boost::asio::posix::stream_descriptor{lhs._sink.  get_executor()};
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

    inline async_pipe& operator=(async_pipe&& lhs);

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
            _sink.close();
        if (_source.is_open())
            _source.close();
    }
    void close(boost::system::error_code & ec)
    {
        if (_sink.is_open())
            _sink.close(ec);
        if (_source.is_open())
            _source.close(ec);
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


    native_handle_type native_source() const {return const_cast<boost::asio::posix::stream_descriptor&>(_source).native_handle();}
    native_handle_type native_sink  () const {return const_cast<boost::asio::posix::stream_descriptor&>(_sink  ).native_handle();}

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
        WriteHandler&& handler)
    {
        return _sink.async_write_some(buffers, std::forward<WriteHandler>(handler));
    }


    const handle_type & sink  () const & {return _sink;}
    const handle_type & source() const & {return _source;}

    handle_type && sink()  &&  { return std::move(_sink); }
    handle_type && source()&&  { return std::move(_source); }

    handle_type source(::boost::asio::io_context& ios) &&
    {
        ::boost::asio::posix::stream_descriptor stolen(ios, _source.release());
        return stolen;
    }
    handle_type sink  (::boost::asio::io_context& ios) &&
    {
        ::boost::asio::posix::stream_descriptor stolen(ios, _sink.release());
        return stolen;
    }

    handle_type source(::boost::asio::io_context& ios) const &
    {
        auto source_in = const_cast<::boost::asio::posix::stream_descriptor &>(_source).native_handle();
        return ::boost::asio::posix::stream_descriptor(ios, ::dup(source_in));
    }
    handle_type sink  (::boost::asio::io_context& ios) const &
    {
        auto sink_in = const_cast<::boost::asio::posix::stream_descriptor &>(_sink).native_handle();
        return ::boost::asio::posix::stream_descriptor(ios, ::dup(sink_in));
    }
};


async_pipe::async_pipe(boost::asio::io_context & ios_source,
                       boost::asio::io_context & ios_sink,
                       const std::string & name) : _source(ios_source), _sink(ios_sink)
{
    auto fifo = mkfifo(name.c_str(), 0666 );

    if (fifo != 0)
        boost::process::detail::throw_last_error("mkfifo() failed");


    int  read_fd = open(name.c_str(), O_RDWR);

    if (read_fd == -1)
        boost::process::detail::throw_last_error();

    int write_fd = dup(read_fd);

    if (write_fd == -1)
        boost::process::detail::throw_last_error();

    _source.assign(read_fd);
    _sink  .assign(write_fd);
}

async_pipe::async_pipe(const async_pipe & p) :
        _source(const_cast<async_pipe&>(p)._source.get_executor()),
        _sink(  const_cast<async_pipe&>(p)._sink.get_executor())
{

    //cannot get the handle from a const object.
    auto source_in = const_cast<::boost::asio::posix::stream_descriptor &>(_source).native_handle();
    auto sink_in   = const_cast<::boost::asio::posix::stream_descriptor &>(_sink).native_handle();
    if (source_in == -1)
        _source.assign(-1);
    else
    {
        _source.assign(::dup(source_in));
        if (_source.native_handle()== -1)
            ::boost::process::detail::throw_last_error("dup()");
    }

    if (sink_in   == -1)
        _sink.assign(-1);
    else
    {
        _sink.assign(::dup(sink_in));
        if (_sink.native_handle() == -1)
            ::boost::process::detail::throw_last_error("dup()");
    }
}

async_pipe& async_pipe::operator=(const async_pipe & p)
{
    int source;
    int sink;

    //cannot get the handle from a const object.
    auto source_in = const_cast<::boost::asio::posix::stream_descriptor &>(p._source).native_handle();
    auto sink_in   = const_cast<::boost::asio::posix::stream_descriptor &>(p._sink).native_handle();
    if (source_in == -1)
        source = -1;
    else
    {
        source = ::dup(source_in);
        if (source == -1)
            ::boost::process::detail::throw_last_error("dup()");
    }

    if (sink_in   == -1)
        sink = -1;
    else
    {
        sink  = ::dup(sink_in);
        if (sink == -1)
            ::boost::process::detail::throw_last_error("dup()");
    }
    _source.assign(source);
    _sink.  assign(sink);

    return *this;
}

async_pipe& async_pipe::operator=(async_pipe && lhs)
{
    std::swap(_source, lhs._source);
    std::swap(_sink, lhs._sink);
    return *this;
}

template<class CharT, class Traits>
async_pipe::operator basic_pipe<CharT, Traits>() const
{
    int source;
    int sink;

    //cannot get the handle from a const object.
    auto source_in = const_cast<::boost::asio::posix::stream_descriptor &>(_source).native_handle();
    auto sink_in   = const_cast<::boost::asio::posix::stream_descriptor &>(_sink).native_handle();


    if (source_in == -1)
        source = -1;
    else
    {
        source = ::dup(source_in);
        if (source == -1)
            ::boost::process::detail::throw_last_error("dup()");
    }

    if (sink_in   == -1)
        sink = -1;
    else
    {
        sink = ::dup(sink_in);
        if (sink == -1)
            ::boost::process::detail::throw_last_error("dup()");
    }

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