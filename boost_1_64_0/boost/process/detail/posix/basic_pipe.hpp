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
9Ib4jo3iKi+T/F60nbt9nM18L4bxvXiT78UbfC+KvxlK6t9D3iixHgvPqlnfA5YuIZ7zGRLPI02ZaU1vzN+F9dQuHKUFJbspv1KT96MpKbN6Tkap1wSlxXIBHBv77cjvxPrFHKdDrOMoetvmHh17+XnmHn2H91mde1SWcd3bNvfo2M/t5x71lXk8s8u5R13G3Xa3sM0y37vE9GUFZLfNNxqv5llrV1ZYdttcomO+dbdkVeznE73I80oGbeRGSc4xKn5D++rmGF2CRvOI2re3X5bt7B18tP7vHeUcmgf4/36RtPl8wnzEOmz/F3ZCyhGpM/+fJ72VPbW8DzDZW87ZI3/nRzxHm/z2BVqb/Dbxf0/Rhl5RxgrM12KBMjZRvL9p5yoco8WCbLFoLRZoi7XUYpVssfparKItVlWLBdhi5bRYBVussBYrb4vl0GLlbDFXLVbWFnvy9rNzJN7TYup+fK/F1P04p8XU/UjWYup+7NBi6jZ7ajF1+8xaTN2+XxOfnQ/xuhZTt+9rLaZu33Etpm7fXi2mbt8WLaYe59/mpO1z4UGM3+9aPwmel377r93/wLWXuHYQ9U3aNYbIe8EWl7+RySt+s4oytd+yIv7YFtd+x4r4LYM5EnMT30l8kIjb/02u7BU3J22/jVzzU5+f9JPXhLIuq1cuOY+MnD9hJGmxda6/hba5/gbFdGEz+S58rjpSlrOvt5H7qF1HFRF5ChrWY8nldXMKil9+6t+aCuL1JvQIMhvWa7G8fb2PQX2W3Xq8bL/vtOuz+uL1Nvw9Mj17T5jcllEiTz4lP9+7Ljz/WDdfbhdRd8H/Dcbscct43aZ6DL3T1EXIud6JeWr1BM/XL+c/1M8moIs1ficlT6EPksN/+SCycfHCPds8ctxn87/Sz+bvdp/Nr+J+GPEQv8PameUcXbr/L9f9/z3d/5ep/5f369jaPmR7UgLJm7RIlJ461rbVU5gTT2NZvIQV8AYG4HWsJJ8H4lkMkflayXgoXsB+Mh4j4wNk+aPwGs6W8USZb7N8fheHmGTdtGyrSMBSpL6yP1Io+bJgJ6yOnbEFdsE2GI79sRuOxe44ASNxDvbHjRiDW3AA7sBY3I9xeBD74EXsi5ewJ5rYhtGYG8dgYRyLJTEeX8e3sCqOx7o4EZvhJOyAkzESp2EUJuBYXIATcSFOxjmYgHNxFs7CeTgbF+ASXIZLcbksZyuuxg9xOR7AdXgY1+MJ3ICncDNexy34E26Tx/+Ek6y7lHWtHH9xLh2UldVNOATuGIKiPhY/wXC8hN3wDvbD3zAan2IMusn7nLLiQPTFOMyDg7EwvoHFcCiWw2FYCUdgNRyJtXEUNsbRCuchjsV+2AMH4i18C4PZr+lYD+difXncGuBqbIi7sBEexcb4LTaRx6cp3pLP72EzfIDjKf93nIiKmfcVfXAK5sJpWBCnY1FMwDI4EyvgbAzCRKyGc7A2zsX6OB9DcAG2xkXYGRdjd1yKfXEZDsDlOAxX4AhchW/hapyAazAB1+IsXI9zcQOuwI24ATfhJtyMe3EL7sNt+DFuxyO4A+9iOD7Fvehk4dxBdzyAPngQ8+LHWAh3YUX8EF/HKKyPvbE59sFQPIwx+AkuxGO4FI/jZvwM9+DneABP4jd4Cq/iafwOz+Bt/Aof4nlUOJe/xsz4DeZBa7wIfofl8HsMxOtYFS9iMF7CRvgjNsdb2Bp/wg54F3vgfYzGX3As/oqT8REuwd9wOT7BdfgHfohPcY+ck+QMmvBbtGAKOuETdEYnZ37Pog+6oj9mwWKYFWuiB9bFbNgWPbELemMP9MWBmBPHoB+Ox1y4AvPjGiyAe7AQnsXCeAmL4Hf4Ct7Dovg=
*/