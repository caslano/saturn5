//
// handler_invoke_hook.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_HANDLER_INVOKE_HOOK_HPP
#define BOOST_ASIO_HANDLER_INVOKE_HOOK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/** @defgroup asio_handler_invoke boost::asio::asio_handler_invoke
 *
 * @brief Default invoke function for handlers.
 *
 * Completion handlers for asynchronous operations are invoked by the
 * io_context associated with the corresponding object (e.g. a socket or
 * deadline_timer). Certain guarantees are made on when the handler may be
 * invoked, in particular that a handler can only be invoked from a thread that
 * is currently calling @c run() on the corresponding io_context object.
 * Handlers may subsequently be invoked through other objects (such as
 * io_context::strand objects) that provide additional guarantees.
 *
 * When asynchronous operations are composed from other asynchronous
 * operations, all intermediate handlers should be invoked using the same
 * method as the final handler. This is required to ensure that user-defined
 * objects are not accessed in a way that may violate the guarantees. This
 * hooking function ensures that the invoked method used for the final handler
 * is accessible at each intermediate step.
 *
 * Implement asio_handler_invoke for your own handlers to specify a custom
 * invocation strategy.
 *
 * This default implementation invokes the function object like so:
 * @code function(); @endcode
 * If necessary, the default implementation makes a copy of the function object
 * so that the non-const operator() can be used.
 *
 * @par Example
 * @code
 * class my_handler;
 *
 * template <typename Function>
 * void asio_handler_invoke(Function function, my_handler* context)
 * {
 *   context->strand_.dispatch(function);
 * }
 * @endcode
 */
/*@{*/

/// Default handler invocation hook used for non-const function objects.
template <typename Function>
inline void asio_handler_invoke(Function& function, ...)
{
  function();
}

/// Default handler invocation hook used for const function objects.
template <typename Function>
inline void asio_handler_invoke(const Function& function, ...)
{
  Function tmp(function);
  tmp();
}

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_HANDLER_INVOKE_HOOK_HPP

/* handler_invoke_hook.hpp
xwjxlX6o8rT6C4/HaJnyjhL9rJfax8ef+KsXsvG/SHlnKd0oG99zRL/DrxX5lc7xZ+2rVOnKlkfXE6l9nE/0Ly4s3b5a4qv2q/aFGi5cXjOlO8jy20b0R1+rST5rf4L4LQuIz9o/zNJXqnGg+lSVqc/BMu2/mejKvrk+HSW+flVp/Ly9TP8tovA047+K2qsT/y7ic3sMNUr6lDL2Mf7EieEHMqP2ULhBprv7euKr+qqQ+Kq+1RwHiL+m392eWuI3EZ+3R19duj1eCkOUjuNLL9HrGN57LzK/NV9kfmu9yPw2vro0HoYoHN5Quv8PEf0lDy+N3zeBz/G90tHsI6z/K4h3ZA3TbzZuxygdvwI0Hyo8mcLxi9INX8vm97UXwa8N/13rqslLXPI7EJFw26ZOX8+W7qBNF+dffepzC5o6Vyl8jq3gKClFh09LkFV+/mB3D33/Im/scn4ght5fow/B8E/VqPRdncHu4PUqvZDMWkXb8XbspIlfKifKB5m0dW60XLaFPpMKpf04PP38fTdnui1B6QlWH6Cho6cqrsSVfDjUsr2HXPiaU069EcjpLXvwBMmZvqszLLp/KJoaNFb1kT/ajtPL/La86t/i1wWcb3MSnQ55R/FmH6vv1q7NwYDqG7ucgWw27ozLz/bEi3HyWjjHOdwDzUHD6VlUmxCme2fbC4mkKT8UJuMZOONV3NYLexiZfnZuag+KVrN+jBdfCIbnND4Ygy+4QHz2PRWK8xLs/gzgyCnpCYkqH68t1+ILt/mFsPLJprbkU1aoPiIn7tVA2OnwxEEMl3reAG1m9hfs3trmD7Z3+Se274uZOeufSCzF93yOL6vpRdsRh+70Amkw+TfrkxEri4z4hg3DA+ujOMJdVhcx7THkfOF8L0W3ztvvcdKFMkSSceFDU/Ky+uJjNpE43roVx8BJczgfCc3SdPWcUpVDdKhqMo5HOrZ8WryWQfLJuC2PF0JNIzKYT7H2UcepFnI6tdCmK+WK4IMgdbIXVH6yiEShkIPrLmMU/cfyyYNu5KkBuMGx6mRGF4YxaBmGLj/swfjCkMryRWnisbHdpDRaLSiiH0RzLK7jBVhHcX0GDoAadgEkQnLZgm41TFeNVXTd8QjaFDWMJei9beKrBDo9NVJ0Ahe9QPai6KKaOMKPb/TZ+K6jfMmgBhczFS/WojwTEroNeo6ySD6LDGJRKx/rG0WUkXj6icJUdmJAlHWW5KOHmRTJ0TyCUcEb3giJLu0Hrt8cvQDipovq7DEKutBZweX8QjarZ1OK4/Abq/eFpR5N0F9UxA0MOgMOv3w/2SPmufU6jjGp7wReIxJ4aBhmz1Ry7UZmoJBYr18dnz1z9kxNu9rU8X9rT0/oGhQ5e+Zl+bOK9Uu4qhfCswQRilPN1xJtpZzWrr20fN3ec2GVImzyynsBM42NDSXrfbtfrm8rKH6a4sX9NsWrKD7uZ/ubgIxPpWgNxdWlU1zRaile3M8+a6FLvonJtzL5bRSvUm2leDXFRyiu6jfK6neM4tNVewP/2PreHLQ+2tQ/mCJciqbEcXMjTppFYuq9hpSyMDzzT0VBcthZnt6mInsQr49hmfosSVArGAIX57zoetwOdPGLYwNZAKSw1ZjPFdWiOOaQSloW4E/gBIPKCtBoAAHiKi4aZUl19XeBw4/PO8/ntJIhE36ls0PGRhQov5N49eNN1xmcwHqYkKSLlbVeXIuvlzvvmWDIgzryzLwQIhbnY+nI2MQX34bByxnyYxfErd3Submz6ymdK0hOfpyOQFisiKheOi76hglAIDWo13qHr04NryjmLwQoXVbWkUooyRfreZkzXarIsLUu1PmyTfE5g+pLaK0qTJc=
*/