//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BIND_HANDLER_HPP
#define BOOST_BEAST_BIND_HANDLER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/bind_handler.hpp>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {

/** Bind parameters to a completion handler, creating a new handler.

    This function creates a new handler which, when invoked, calls
    the original handler with the list of bound arguments. Any
    parameters passed in the invocation will be substituted for
    placeholders present in the list of bound arguments. Parameters
    which are not matched to placeholders are silently discarded.

    The passed handler and arguments are forwarded into the returned
    handler, whose associated allocator and associated executor will
    will be the same as those of the original handler.

    @par Example

    This function posts the invocation of the specified completion
    handler with bound arguments:

    @code
    template <class AsyncReadStream, class ReadHandler>
    void
    signal_aborted (AsyncReadStream& stream, ReadHandler&& handler)
    {
        net::post(
            stream.get_executor(),
            bind_handler (std::forward <ReadHandler> (handler),
                net::error::operation_aborted, 0));
    }
    @endcode

    @param handler The handler to wrap.
    The implementation takes ownership of the handler by performing a decay-copy.

    @param args A list of arguments to bind to the handler.
    The arguments are forwarded into the returned object. These
    arguments may include placeholders, which will operate in
    a fashion identical to a call to `std::bind`.
*/
template<class Handler, class... Args>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
detail::bind_wrapper<
    typename std::decay<Handler>::type,
    typename std::decay<Args>::type...>
#endif
bind_handler(Handler&& handler, Args&&... args)
{
    return detail::bind_wrapper<
        typename std::decay<Handler>::type,
        typename std::decay<Args>::type...>(
            std::forward<Handler>(handler),
            std::forward<Args>(args)...);
}

/** Bind parameters to a completion handler, creating a new handler.

    This function creates a new handler which, when invoked, calls
    the original handler with the list of bound arguments. Any
    parameters passed in the invocation will be forwarded in
    the parameter list after the bound arguments.

    The passed handler and arguments are forwarded into the returned
    handler, whose associated allocator and associated executor will
    will be the same as those of the original handler.

    @par Example

    This function posts the invocation of the specified completion
    handler with bound arguments:

    @code
    template <class AsyncReadStream, class ReadHandler>
    void
    signal_eof (AsyncReadStream& stream, ReadHandler&& handler)
    {
        net::post(
            stream.get_executor(),
            bind_front_handler (std::forward<ReadHandler> (handler),
                net::error::eof, 0));
    }
    @endcode

    @param handler The handler to wrap.
    The implementation takes ownership of the handler by performing a decay-copy.

    @param args A list of arguments to bind to the handler.
    The arguments are forwarded into the returned object.
*/
template<class Handler, class... Args>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
auto
#endif
bind_front_handler(
    Handler&& handler,
    Args&&... args) ->
    detail::bind_front_wrapper<
        typename std::decay<Handler>::type,
        typename std::decay<Args>::type...>
{
    return detail::bind_front_wrapper<
        typename std::decay<Handler>::type,
        typename std::decay<Args>::type...>(
            std::forward<Handler>(handler),
            std::forward<Args>(args)...);
}

} // beast
} // boost

#endif

/* bind_handler.hpp
Q79Ceip96HYWDrJc38x0Q30jf3oq3ai+NQm6aSucYX0juWGG9a2J7BGL+tYJu+5D/tmobwOkASmhIeF9MecwtMd9VFcVezzMwkEXvJ7OItu02XtsMpDobdiwhWyzXu7K86orS91lxWx0QGU/wq5z1XrBLiQTLfR7bj6nzBTixXuhcb+XsFjs946w64r86Fwa7wuRh0qnsgitTu+Ct11XJ/TUxjqRTLRwT+ldmcXyRUVqy/cOeLt0ysc8INEY7C1WvkI8DsFTF15GyKnKuMKCXZW57FusjDxNj3ZzRqecp8Bvr9Upp7vC7cWWJBfNdPkti5cF1tWUF/I6wnn4/dmCLjr25nPy37JzPB/hOoB/iH7dd+jqV1NVYqwbZEzrPo/nzyB6qZe3ul8SpV/3XXo6VVVUVpvo5FKV+b5ellks3+yh2vKdBK9br3y1BWU1xd3lO6EtH8lE98znhfE5Li2P5+NqH8p/QmtzGt8iD2GPxoQ+xnsBPpgsn+/zvdLEpE0fXxZ7NjZi6JNrfwefwiny+Vdvfu2lz/5+15mbdo4a9kTj6lD4/wiSz3fNWxZXM+HOxp/FzL6zX+en+Cj/DsYf+3x947kxuc/eVrf48e3PPNbm+94Q/T0Uxns9nhjF0in+9eHSJY2XPXD6sjdfmHoDzjesYnsi1s4q/2vopf0j/tj28UMzfrkV9YXp+/0HHlpwS0jwp/MKZz5a/t7MAuzbYeU5d+yFsHs2bWm68s2PC0pXj+3EHGaKfP5UY8J3Ug6Vn9vy0Z6ntu4Z9UPwMzu42zds/3vX+Jde+/r8uMnvpz1ntPfEaM+I0d4N470hnzE7X/vMzXvsb0Q/snjriWvKzuY+gO/fs3KOfKNwQNm1mbf8vt92d1Ky60E8W5wkn3/o2+uy94f8+e1nvzfus3t37fge9k0xOyxcWhj7fu6Zyf3ccZ2bZ5xF+T+WcC1BONicr4PWoC0U/mcJ/9OF/0uE/5nC/yt7/rMxbRf5Ccig/9GgbPqfCFpE/yeAPgK18+fK7Nk2ixsGgvnYkU/f+l8LTKY1wLOBRcC5tHZuPnAjcDlwHfAa4HVAN7AEWEPfnP8GcD3wbuANwAdpjfweYDnwEVp7+CjFPwGsBB4GVgF/SXti3gbeBPwQ+BXg34H1wH9SOfgawspuvZJ1vjEfLa6FNOGbQHxNoBbiO0h8g0HbiG8S+BKBqWQnBzANeAlwHnAqcCFwGvDLwEuBa4AzgduBs4A7aa9CE/BLwG/Sms17gVcAHwA6yV5zqVw7lGcpwJeoXIOYPbqPBeAbDVwEHEtrNp3AJcDFwKVAkLQMWAB0AdcBVwHX09rXSuAa4I3Aa4C3A1cAHwfmAp+k8x8xeWW+jrpJ5ekLWiCsmR8I3A5MAO4Ajqc1nVMpPBP4VbLb7ZRumkTzZsBoSjcENFlZe0vpbqH6uhUYR2HI43qASN5G8sGgJJKPAB/r64EhqjX2Ti5nUI8ofRfxDdJJfzilH0vlHEFyTpCb5IaRnA00neQSSC6R5MYAB9Ma4mjgOHGNK0/HqB7T2mTii9ashQWKa3ot8nVZ5LPXWuNzWORzWeRze+GT30ftnYjv2INOgeImYS0kqAG0H9QJKgsJlbaB8hG/G3gAROt8+RrfXFAHzh8Bymt3zwBp7S5bs2tPQfrABOB0ENbnsrW5ZaAG0C5QCwjrdNka3dYUtkYX63NBQHnd7QRQDqiO1tzuAO4FHQAdAXWCzoKipniurc0B7gUWAatBLaAjIKynZWto4xxYuwmS18rOBq4BlYEaQHtAWA/L1sIeBTqBp4BFwD2gc/gffgnyAuWA6kGNoEOgs7DHUeBx0BlQyFSUDZQEirGFsrWtuaA=
*/