/*
 *     [begin_description]
 *     Boost bind pull the placeholders, _1, _2, ... into global
 *     namespace. This can conflict with the C++03 TR1 and C++11 
 *     std::placeholders. This header provides a workaround for 
 *     this problem.
 *     [end_description]
 *        
 *     Copyright 2012 Christoph Koke
 *     Copyright 2012 Karsten Ahnert
 *           
 *     Distributed under the Boost Software License, Version 1.0.
 *     (See accompanying file LICENSE_1_0.txt or
 *     copy at http://www.boost.org/LICENSE_1_0.txt)
 * */

#ifndef BOOST_NUMERIC_ODEINT_UTIL_BIND_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_BIND_HPP_INCLUDED


#include <boost/numeric/odeint/config.hpp>


#if BOOST_NUMERIC_ODEINT_CXX11 
    #include <functional>
#else
#define BOOST_BIND_NO_PLACEHOLDERS
#include <boost/bind.hpp>
#endif

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

#if BOOST_NUMERIC_ODEINT_CXX11 

using ::std::bind;
using namespace ::std::placeholders;


#else

// unnamed namespace to avoid multiple declarations (#138)
namespace {
using ::boost::bind;
boost::arg<1> _1;
boost::arg<2> _2;
}
// using ::boost::bind;
// using ::_1;
// using ::_2;

#endif

}
}
}
}





/*

// the following is the suggested way. Unfortunately it does not work with all compilers.

#ifdef BOOST_NO_CXX11_HDR_FUNCTIONAL
#include <boost/bind.hpp>
#else
#include <functional>
#endif


namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

    
#ifdef BOOST_NO_CXX11_HDR_FUNCTIONAL

using ::boost::bind;
using ::_1;
using ::_2;

#else

using ::std::bind;
using namespace ::std::placeholders;

#endif


}
}
}
}*/

#endif // BOOST_NUMERIC_ODEINT_UTIL_BIND_HPP_INCLUDED

/* bind.hpp
z+A1VuhQDgoUXwuxjmiHfPHuOGc6lPZdZSdOifNb8+cS3nyOCYUwv9fqxeyqOjt3tolz4xX8a/VL4Bn5hUOcsz/lQGS7Xf04aMHWIhrJD+/R+h8OSKsqJxkECE36GJ8nmGpvf4u9tiU6X6HtEFVMiOKuge4pt9YyS/8xlJ2JnOAsfScc1AgiD2pStB2Mbh8UnTNIQTeZDb7QKg7hskHM81nEJc8VyyDJUhlDv/5VEQafCdBylc8FC5liEe04U1wCRvtczedE39Lu5rt6T0ZWc2I++1w9/1VidkKiCOlqgmdNCZJGdB57J774HhqgftHMqiaovwS8IEYiF+7nhdshPhbSWzC3pH5eMmfaf1TYxakV/7rPgsvx5DxweCTbVnuRcSi5dT7liPiG9AHZ7x3o92UB/T68itF59UUYBHjkQuyA2XE8Yi/jZBmjFaHMCrb/8GDe8DwHzkrSawSbngJBDjNlHX5x4CiZj0t/DyhpoATsr+YQUmQLTLCGewf1gz8RQJQlE73VBxSKKKQHdz2EsGHhdb4KsKuQtgBsg6pg1KnNRmzC+DURnm9Uy4Fqff8nmdVy6LfyXVTLIav1EXgQBqFJ++ubT/JlKhSJPu1T7I1wXQay0K4qlXo9e6hP/dFevSyw+2qyA6UtnZOc7Kz0zsqCd3YTQ1u0Zu6e/LNQqEuPY/PkhDTjn+z/MMajs1ohJS/kcNVjvg7SIFVQtG6Rl5C5wifrHbwASUKj6q/tH9Bf6WSjEbnJNW5tBrmzeqYS7IywoWISa7ivmJXzksudesdLxDUiLwXnen5yeQjRArVW5s08kx/AHLMPNqcaFIVEWNitNXo4cm1ErYjA4Ujg2hxFfOpD3sVDrGhmqY4KNF1yv7QhPucx9DR+pakv59dtw/Av1KaVXWJmFxuswrPlOAHQiyN32C0ARqxhYvWPyTEpIGzrHJzlyQKOABy1F6jOW7BgWMtGKZL2wmUvpSX6SBVkMmOhQAX9r1gw/OEbdmj+Im1lcSJb8xdoKwvluMfGoMQSg5cnOJvDVxtwiqF6cO1lorTaSrOotv1puSiSUappF1LjP7897M9eNUSYEH6ZVoWjRc21A/VXcLkWzo0crwpnxef9LGFfe2jlDeRDreFBcoREPV1+bBtlj/b8TkjTjMMNJeURQHhE2dLC8QDbOrVZMmGy2a5MdhAKdH4n9Ny3QHcfn5641e5uOW39i5FJfOXKEwiqjKFNAWdD7T1NMQ1L+cfRopiDi42NcqH3wxIjWyuDSicPtlLoJRysCiNXKqFJKqUl6oLbQBOnKLu+Ca00fJ9oJZF9UL9OkIcDWdjHl5Gb/MRvRW0xqcCwaz7MrO1aM9Z1MEMJFU5kJqFB9UeJsVBftU8qdxtciYdjfbRqR2ScFUH9U0ExC4LWglJrC08XDrQ2kpp5xe7eRJxXjUuugGF41QS//o1sMUuSI52ZhELmj+xdC3xT1RlP0rQNEEiQMKtWqIKKAhNtZYW22PJoq6KklCYgCOgmu+vUISaAWqEltBAuUfbwOeZjOoebzjcWZFAo0KJM0TmHYyrb0J1a3XBqKYLN/v9z7k3S0Aq4uddv9/e7957nd97nfOf7vvOdEdEFbspZwdfhFXrc9zxDwiuMnlGS1atkcCAV/9ZeJpIkD8NyPwFJ0l4lwwK98A/X3c989WyS/xS8BgH4pFdtCDeCdGdmZ0ZlFgQ4m0pGMI9IebZX9JUpe+TpnA7uKHPDdXfBVx3djS5A1l+SQSQy/QMEiS6YGKmrJgDxTNznJunjjdQtlT73xH1mS7CF4bq9MtOl6L9ZqEDc1K3sOsjiv1fGpkKHRRUEnnzoKqkEuMop4NHKY+3gspI3RpY=
*/