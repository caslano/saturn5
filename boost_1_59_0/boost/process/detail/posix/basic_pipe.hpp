// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_PIPE_HPP
#define BOOST_PROCESS_POSIX_PIPE_HPP


#include <boost/filesystem.hpp>
#include <boost/process/detail/posix/compare_handles.hpp>
#include <system_error>
#include <array>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

namespace boost { namespace process { namespace detail { namespace posix {


template<class CharT, class Traits = std::char_traits<CharT>>
class basic_pipe
{
    int _source = -1;
    int _sink   = -1;
public:
    explicit basic_pipe(int source, int sink) : _source(source), _sink(sink) {}
    explicit basic_pipe(int source, int sink, const std::string&) : _source(source), _sink(sink) {}
    typedef CharT                      char_type  ;
    typedef          Traits            traits_type;
    typedef typename Traits::int_type  int_type   ;
    typedef typename Traits::pos_type  pos_type   ;
    typedef typename Traits::off_type  off_type   ;
    typedef          int               native_handle_type;

    basic_pipe()
    {
        int fds[2];
        if (::pipe(fds) == -1)
            boost::process::detail::throw_last_error("pipe(2) failed");

        _source = fds[0];
        _sink   = fds[1];
    }
    inline basic_pipe(const basic_pipe& rhs);
    explicit inline basic_pipe(const std::string& name);
    basic_pipe(basic_pipe&& lhs)  : _source(lhs._source), _sink(lhs._sink)
    {
        lhs._source = -1;
        lhs._sink   = -1;
    }
    inline basic_pipe& operator=(const basic_pipe& );
    basic_pipe& operator=(basic_pipe&& lhs)
    {
        _source = lhs._source;
        _sink   = lhs._sink ;

        lhs._source = -1;
        lhs._sink   = -1;

        return *this;
    }
    ~basic_pipe()
    {
        if (_sink   != -1)
            ::close(_sink);
        if (_source != -1)
            ::close(_source);
    }
    native_handle_type native_source() const {return _source;}
    native_handle_type native_sink  () const {return _sink;}

    void assign_source(native_handle_type h) { _source = h;}
    void assign_sink  (native_handle_type h) { _sink = h;}




    int_type write(const char_type * data, int_type count)
    {
        int_type write_len;
        while ((write_len = ::write(_sink, data, count * sizeof(char_type))) == -1)
        {
            //Try again if interrupted
            auto err = errno;
            if (err != EINTR)
                ::boost::process::detail::throw_last_error();
        }
        return write_len;
    }
    int_type read(char_type * data, int_type count)
    {
        int_type read_len;
        while ((read_len = ::read(_source, data, count * sizeof(char_type))) == -1)
        {
            //Try again if interrupted
            auto err = errno;
            if (err != EINTR)
                ::boost::process::detail::throw_last_error();
        }
        return read_len;
    }

    bool is_open() const
    {
        return (_source != -1) ||
               (_sink   != -1);
    }

    void close()
    {
        if (_source != -1)
            ::close(_source);
        if (_sink != -1)
            ::close(_sink);
        _source = -1;
        _sink   = -1;
    }
};

template<class CharT, class Traits>
basic_pipe<CharT, Traits>::basic_pipe(const basic_pipe & rhs)
{
       if (rhs._source != -1)
       {
           _source = ::dup(rhs._source);
           if (_source == -1)
               ::boost::process::detail::throw_last_error("dup() failed");
       }
    if (rhs._sink != -1)
    {
        _sink = ::dup(rhs._sink);
        if (_sink == -1)
            ::boost::process::detail::throw_last_error("dup() failed");

    }
}

template<class CharT, class Traits>
basic_pipe<CharT, Traits> &basic_pipe<CharT, Traits>::operator=(const basic_pipe & rhs)
{
       if (rhs._source != -1)
       {
           _source = ::dup(rhs._source);
           if (_source == -1)
               ::boost::process::detail::throw_last_error("dup() failed");
       }
    if (rhs._sink != -1)
    {
        _sink = ::dup(rhs._sink);
        if (_sink == -1)
            ::boost::process::detail::throw_last_error("dup() failed");

    }
    return *this;
}


template<class CharT, class Traits>
basic_pipe<CharT, Traits>::basic_pipe(const std::string & name)
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

    _sink = write_fd;
    _source = read_fd;
    ::unlink(name.c_str());
}

template<class Char, class Traits>
inline bool operator==(const basic_pipe<Char, Traits> & lhs, const basic_pipe<Char, Traits> & rhs)
{
    return compare_handles(lhs.native_source(), rhs.native_source()) &&
           compare_handles(lhs.native_sink(),   rhs.native_sink());
}

template<class Char, class Traits>
inline bool operator!=(const basic_pipe<Char, Traits> & lhs, const basic_pipe<Char, Traits> & rhs)
{
    return !compare_handles(lhs.native_source(), rhs.native_source()) ||
           !compare_handles(lhs.native_sink(),   rhs.native_sink());
}

}}}}

#endif

/* basic_pipe.hpp
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
*/