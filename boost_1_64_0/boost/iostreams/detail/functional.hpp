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
32f0p9r/8qdaV+fYDrkI4ZBv1ZvhDOTj0r/lm8UuWIwMc/39mUvnc9ffX5i/5f5X/p6EOPfOc+zgurqA6+8jyEZb5wDqnMt4O7hm8gZoqa0PH3wXJsADsDV8D7ZTGyTt4UHd7/BDOAF+BCer/xT4Cefnw0/htfAwvF79b4BfqI2Ro/BR+CXcrf5PwmNqO+Eb+B48Dv8Ov4V+0vodrAId/arQgmnQhh2hD3aFftgXBuBg1R8CK8EJsDKcA+PhxbAavAImwFWqfy2sAe+CNeFjMBE+AWvDV2EyLIEN4WfqTprEPQBTYD1YF3aGzeBA2ByOgi3gWNhSbZPs1XlkOn9O6qkufMLiUNsSNvy91tNO2AI+ovX1Z9gW7oI94GNwJHwcToTPwnPgn2Ae3A8L4OvwAg1fDJ+Cq+HT8BfwGbhJ3e+HL8I/wJfhy/AV+KqGf02v8w58Dkr7M3Oc6Cuar1rwhtADlRVsf4NhAA6FdeEw2BEOh13gVJgBR8GB8DQ4Bp4Op8MsuAROgpfBM+GVGm4lnACvVf+b1H+9+h+B/W2dq6NzkuKRlkHbGXIs0vK/BFaBl2r5L9Xy3wrbwMtgJlwBs+DlcLz6T4BXw2lwldbDtXAFvA5eqXpXwZ/DG+AauAVeD7eq//3wJvgY/AXcA9fCF+HN8E9wg/ajX8Hv4EaYoPt4JsK7YCN4E+wA74Gd4VbYBd4Ne8MtcKC6D4K3wanwdjgT3gHPVX+1GaTzHTi0HN02g1KdIoMNYAJsCJvCRrAF7Adbw6awG2wBh8DWcBZsAy+BfbR++8JVGu5a2B6ugafCTbADfFjP98Au8CWYAUtgN3gQ9oDHYU/4vcan+yjqt2yZM0B+wvdRzNf8FML6sEjb6yKYCe+EPeBiOBYugVPgRfAseKnma6nu87sCXgcvh7fClfC38Cq4HV4NX4HXwP1wne67ezM8Bn8JLR/1DhPhrbAlvAN2gZthD3gn7AU3wf7OueY30x/6BijfeiW/M51yxd05XkCvKnwV1oGvw5bwDdgf/hkOggW0h2Hwr5xPgm/BhbAEFqj/BfCA1td78C74Pvyd+t8PP+T8Ufg5fA0ege/AL+AH8G/wKPwaVnd+J2BT+D08BQaIJwPGaXuuDIfDeDgLVoEXwKpwMawGb4SJcBOsBR+BdeBTMAW+BuvCt2EqfA/Wg0dgGvwG1od+p73AerA97AE7wuEwHZ4JO8EZsDOcD7vAhbA6vBI2gatgHlwDz4Wb4Fx4H5wHH4Tz4aNwIdwN8+FL8Dz4GiyAb8AG8DPYCFbxB+OvAZNgbVgbpsJusBHMhN1gL9gP9objYR84B/aFRbA/vAIOgCvhQLgKDoF3w6FwKxwG74Mj4RNwFNwLT4P74Bj4lvp/qv7H4Vj4HRwHa9Iux8PWcALsASfBgXAqHAGnwWw4CxbBs+CF8Gy4VM+X6/mVcDr8BcyGN2v4LRr+QTgDvgDPgW/CvzvtDn4Dv4YFtvYf846fstXfuwBsb3Ho/uIOZ8A0mAMbw5kwFD77JOFna/g5Gv5cDT9Xw692RMNv0fA14QqEQ/b9lnc20HF/CDaD22EHuAN2hr+HA+AjcJLq5cKn4GXwGXgVfBZeDf8Ab4RPwHVwN7xb/XU/dX1PKc+q3KOG76ee7tJbGqPeapfeLsStV+zS2xij3laX3uYIvUkuvV0n0Zvh0tsbo15JjHqHY9Szsk6qJ/tDs09tmXvgbuPOLPM0X5idjcnLSm1tHIbzOF+NlNrdgMuxP4GE9rvtvZx48J8cse9tNu6Re98egwmOLQ78bkP2IG/i3h6348vxuyxov6MJPHF/XIh7aI/cYv6eCbdzXoJs4Hwbsg85hmSuQA9pkUU=
*/