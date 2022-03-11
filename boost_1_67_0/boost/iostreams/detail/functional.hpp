/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/detail/functional.hpp
 * Date:        Sun Dec 09 05:38:03 MST 2007
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com

 * Defines several function objects and object generators for use with 
 * execute_all()
 */

#ifndef BOOST_IOSTREAMS_DETAIL_FUNCTIONAL_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FUNCTIONAL_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/close.hpp>
#include <boost/iostreams/detail/ios.hpp> // BOOST_IOS

namespace boost { namespace iostreams { namespace detail {

    // Function objects and object generators for invoking
    // boost::iostreams::close

template<typename T>
class device_close_operation {
public:
    typedef void result_type;
    device_close_operation(T& t, BOOST_IOS::openmode which) 
        : t_(t), which_(which) 
        { }
    void operator()() const { boost::iostreams::close(t_, which_); }
private:
    BOOST_DELETED_FUNCTION(device_close_operation& operator=(const device_close_operation&));
    T&                   t_;
    BOOST_IOS::openmode  which_;
};

template<typename T, typename Sink>
class filter_close_operation {
public:
    typedef void result_type;
    filter_close_operation(T& t, Sink& snk, BOOST_IOS::openmode which)
        : t_(t), snk_(snk), which_(which)
        { }
    void operator()() const { boost::iostreams::close(t_, snk_, which_); }
private:
    BOOST_DELETED_FUNCTION(filter_close_operation& operator=(const filter_close_operation&));
    T&                   t_;
    Sink&                snk_;
    BOOST_IOS::openmode  which_;
};

template<typename T>
device_close_operation<T> 
call_close(T& t, BOOST_IOS::openmode which) 
{ return device_close_operation<T>(t, which); }

template<typename T, typename Sink>
filter_close_operation<T, Sink> 
call_close(T& t, Sink& snk, BOOST_IOS::openmode which) 
{ return filter_close_operation<T, Sink>(t, snk, which); }

    // Function objects and object generators for invoking
    // boost::iostreams::detail::close_all

template<typename T>
class device_close_all_operation {
public:
    typedef void result_type;
    device_close_all_operation(T& t) : t_(t) { }
    void operator()() const { detail::close_all(t_); }
private:
    BOOST_DELETED_FUNCTION(device_close_all_operation& operator=(const device_close_all_operation&));
    T& t_;
};

template<typename T, typename Sink>
class filter_close_all_operation {
public:
    typedef void result_type;
    filter_close_all_operation(T& t, Sink& snk) : t_(t), snk_(snk) { }
    void operator()() const { detail::close_all(t_, snk_); }
private:
    BOOST_DELETED_FUNCTION(filter_close_all_operation& operator=(const filter_close_all_operation&));
    T&     t_;
    Sink&  snk_;
};

template<typename T>
device_close_all_operation<T> call_close_all(T& t) 
{ return device_close_all_operation<T>(t); }

template<typename T, typename Sink>
filter_close_all_operation<T, Sink> 
call_close_all(T& t, Sink& snk) 
{ return filter_close_all_operation<T, Sink>(t, snk); }

    // Function object and object generator for invoking a
    // member function void close(std::ios_base::openmode)

template<typename T>
class member_close_operation {
public:
    typedef void result_type;
    member_close_operation(T& t, BOOST_IOS::openmode which) 
        : t_(t), which_(which) 
        { }
    void operator()() const { t_.close(which_); }
private:
    BOOST_DELETED_FUNCTION(member_close_operation& operator=(const member_close_operation&));
    T&                   t_;
    BOOST_IOS::openmode  which_;
};

template<typename T>
member_close_operation<T> call_member_close(T& t, BOOST_IOS::openmode which) 
{ return member_close_operation<T>(t, which); }

    // Function object and object generator for invoking a
    // member function void reset()

template<typename T>
class reset_operation {
public:
    reset_operation(T& t) : t_(t) { }
    void operator()() const { t_.reset(); }
private:
    BOOST_DELETED_FUNCTION(reset_operation& operator=(const reset_operation&));
    T& t_;
};

template<typename T>
reset_operation<T> call_reset(T& t) { return reset_operation<T>(t); }

    // Function object and object generator for clearing a flag

template<typename T>
class clear_flags_operation {
public:
    typedef void result_type;
    clear_flags_operation(T& t) : t_(t) { }
    void operator()() const { t_ = 0; }
private:
    BOOST_DELETED_FUNCTION(clear_flags_operation& operator=(const clear_flags_operation&));
    T& t_;
};

template<typename T>
clear_flags_operation<T> clear_flags(T& t) 
{ return clear_flags_operation<T>(t); }

    // Function object and generator for flushing a buffer

// Function object for use with execute_all()
template<typename Buffer, typename Device>
class flush_buffer_operation {
public:
    typedef void result_type;
    flush_buffer_operation(Buffer& buf, Device& dev, bool flush)
        : buf_(buf), dev_(dev), flush_(flush)
        { }
    void operator()() const
    {
        if (flush_) 
            buf_.flush(dev_);
    }
private:
    BOOST_DELETED_FUNCTION(flush_buffer_operation& operator=(const flush_buffer_operation&));
    Buffer&  buf_;
    Device&  dev_;
    bool     flush_;
};

template<typename Buffer, typename Device>
flush_buffer_operation<Buffer, Device> 
flush_buffer(Buffer& buf, Device& dev, bool flush)
{ return flush_buffer_operation<Buffer, Device>(buf, dev, flush); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FUNCTIONAL_HPP_INCLUDED

/* functional.hpp
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
*/