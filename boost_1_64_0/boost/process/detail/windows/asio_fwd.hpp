// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_ASIO_FWD_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_ASIO_FWD_HPP_

#include <memory>

namespace boost { namespace asio {

class mutable_buffer;
class mutable_buffers_1;
class const_buffer;
class const_buffers_1;

template<typename Allocator>
class basic_streambuf;

typedef basic_streambuf<std::allocator<char>> streambuf;
class io_context;

class executor;


template <typename Handler>
class basic_yield_context;

namespace windows {

#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
class stream_handle_service;

template <typename StreamHandleService>
class basic_stream_handle;

typedef basic_stream_handle<stream_handle_service> stream_handle;
#else /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */
template <typename Executor>
class basic_stream_handle;
typedef basic_stream_handle<executor> stream_handle;

#endif /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */


#if defined(BOOST_ASIO_ENABLE_OLD_SERVICES)
class object_handle_service;

template <typename ObjectHandleService>
class basic_object_handle;

typedef basic_object_handle<object_handle_service> object_handle;
#else /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */
template <typename Executor>
class basic_object_handle;
typedef basic_object_handle<executor> object_handle;
#endif /* defined(BOOST_ASIO_ENABLE_OLD_SERVICES) */

} //windows
} //asio

namespace process { namespace detail { namespace windows {

class async_pipe;

template<typename T>
struct async_in_buffer;

template<int p1, int p2, typename Buffer>
struct async_out_buffer;

template<int p1, int p2, typename Type>
struct async_out_future;

} // windows
} // detail

using ::boost::process::detail::windows::async_pipe;

} // process
} // boost




#endif /* BOOST_PROCESS_DETAIL_WINDOWS_ASIO_FWD_HPP_ */

/* asio_fwd.hpp
4WXwM9gBnoad4OfwCngGDoVfwmnwKzgf/gAXwx/h3fAn+LjyT7cDOuFB6IJvQTf8VMnPw2gY72EtG1aFsbAhLAMbQw/sAL2wJwyH2TAe9oeJcChMgoWwHJwCy8NbYUV4B6wMV8PqcD+sAY/CmvAUrAU/g3XgGVhX7InV9x1hA1gBXgQrw4awKmwM68KmsBVsBtNhc5it5MNgdzgd9oB/gD3hnfBKeBfsBVfBFnAzbAl3wFZwD2wPP4KZ8EvYCRpe1rlhCuwMK8KusArsA+vDvrAF7Ac7wv7wSjgA9oFXwcFwIMyDOfBamAunwzy4AObDdXAYfAAOhzvhCHgGjoJfw9HwJzgGujkPjoXRsBAmw/GwPCyCF8OJsAmcBDPgFJgJp8I+8Do4Fl4Pr4fT4DQ4Hd4AZ8DNcDbcp9IdgM3hq/BlVN6B83z1gzfDn+AtMJ55ez6sABfA6vBW2AD+ATaHC2FneBvsDW+H18BFcChcrN5POepQ1/nqfnYXbEVgLpTfcvSi4CpYHa6GteG9sK6St1LyS+Ea2BOuhYPhPbAAnoAj4QZYBDfCmXATXAQfgHfCB+EG+Dh8UKXbAv8IH4EPwb3wGfiSin8VPgxfh4/CI/BJ+A58Cv4ZboORtGk7rAB3wDrwGdgInoDN4LOwFdwP28EXYLaK7wt3wxFwDxwD98LrVLpZSm8ufAmugS/Dp+EBeFjFH4GvwvfhQfgJPATPQnTk/ZQ3YTI8CqvAt2Ad+DZsAY/BnvAdmA9PwOHwdVgI31DzFLb1Yk/f85jrF23wsb0XW/vR6F1PWEJ4kPAy4QTh7LFSO/z/FTv8Uhv8X2eDX2p//8+1v+//vuN3tcEP2N9Hc8FY43ip/X3pr/RX+iv9/T///qn2/3lFo5sUtvS9AfAP2//n2dj/59nY/+fZ+P7Ls/f9h9ze91+eje+/PBvff3mmj7/M7N6dumRlit08cnu7+W+SsddTvvnClX+Dw2qt7iChgHSF2+URS25+fk5eQVHxhJyhRePG5Mh6gazjDEmQtbHi3LxR2uboC0nT3H69dLtaE9P2Ob5sJT9tfztTdArt10S329qwa19XKyV+g8QPk/0xocR3phZK/ENGkD20tg29VeIf4floS20zVWuHshnSafLGTRxbLPG+vpolaXZIfGKCeDgcYbUnPifxFwX8Qqn+6WaEI0vB9oZnFtis854CjYyOKIyOaG1v7xPQbY/udz7dsBkzo13hRsBW51yytucRvXz0vpc8Z+y2sfkRnXnoXJ2ATuSMRab9lLJJYjvMMO1hfgh86wq+pNbO3L9oq+KJr7ND2zPotTTfmEn2jxm9zi/2COZYkPWkFmodf4r6NmOWizwVvyWmp+Q9Q47qUXkTWqoXO0J+o/GSZ8SmkfXl7np9s+JOZXMrvhpVnpRQy2X6kzTl9u9qhIdIp+R241X74hov8fVdHtKZNsvSD6MnFJt2hSNEL8aV5vBqe8wpsi5QI9h3oV5PfVTSfOLc63QGj3dtr7pBdL52vopOJDp5Qe8QbJX4WSxNjbfzL6jfHdn7jLSDVeUoOW4/CPIpx07SdrPzJc/7HQfYwyJjq6a0ZbJvnpNy8uU4IlWOnlukPkWyv1K0fWJ/KfcIq/6NHZc6bjds/AVqv2kLVR9+JG3VbdFt9Ugd2hhO6lVBHbs3SZovnC5KmEG6rQQ5rs3+t/UDmKBsj2+W9ImulY7ejiDbcP2+0Q2ik+r6Vu2n1+NlX7acYLE1birt/tLYh0ZsiT5zm+Wbx4/ur22Sziv5HolTfWqZ7yZL2ZWdJ2mz2H7oPu3obGzc5Tji6Iqu36fhLNEt7/qKeqbI3B8oU+0kS753Srkn+K5QhJKZ+8o=
*/