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