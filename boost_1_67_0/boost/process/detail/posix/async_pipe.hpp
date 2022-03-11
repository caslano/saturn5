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
        lhs._source.assign (-1);
        lhs._sink  .assign (-1);
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
        if (_sink .native_handle()  != -1)
            ::close(_sink.native_handle());
        if (_source.native_handle() != -1)
            ::close(_source.native_handle());
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