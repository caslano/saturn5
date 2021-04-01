//
// handler_alloc_hook.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_HANDLER_ALLOC_HOOK_HPP
#define BOOST_ASIO_HANDLER_ALLOC_HOOK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Default allocation function for handlers.
/**
 * Asynchronous operations may need to allocate temporary objects. Since
 * asynchronous operations have a handler function object, these temporary
 * objects can be said to be associated with the handler.
 *
 * Implement asio_handler_allocate and asio_handler_deallocate for your own
 * handlers to provide custom allocation for these temporary objects.
 *
 * The default implementation of these allocation hooks uses <tt>::operator
 * new</tt> and <tt>::operator delete</tt>.
 *
 * @note All temporary objects associated with a handler will be deallocated
 * before the upcall to the handler is performed. This allows the same memory to
 * be reused for a subsequent asynchronous operation initiated by the handler.
 *
 * @par Example
 * @code
 * class my_handler;
 *
 * void* asio_handler_allocate(std::size_t size, my_handler* context)
 * {
 *   return ::operator new(size);
 * }
 *
 * void asio_handler_deallocate(void* pointer, std::size_t size,
 *     my_handler* context)
 * {
 *   ::operator delete(pointer);
 * }
 * @endcode
 */
BOOST_ASIO_DECL void* asio_handler_allocate(
    std::size_t size, ...);

/// Default deallocation function for handlers.
/**
 * Implement asio_handler_allocate and asio_handler_deallocate for your own
 * handlers to provide custom allocation for the associated temporary objects.
 *
 * The default implementation of these allocation hooks uses <tt>::operator
 * new</tt> and <tt>::operator delete</tt>.
 *
 * @sa asio_handler_allocate.
 */
BOOST_ASIO_DECL void asio_handler_deallocate(
    void* pointer, std::size_t size, ...);

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/impl/handler_alloc_hook.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_HANDLER_ALLOC_HOOK_HPP

/* handler_alloc_hook.hpp
ggrOAtf8ruSca3aLpBpolUCHF91kYiR3bPsZ20BQMnH2CY4LffTHoe6KHUW2Ko95fX/5MNAJy9sIMRbWocRsD0PsaVMFbownkU/gs75SfXDWwH6Ysi6wj0QBBkdiYOKunH7zbPPUhKg9TJzem6pPImM4I1BBSgKGsxbi4Qn+LeGa6Y9JNpgxGJgZQSHe1lSBZTFYUeW5WZbNz0T/cDa/NKQCDRrLCgFpwJNJLz+zWLo5eHXsA2umUgIQJ1B1FZID4buPVAmd+YOZJAsncfuE9kPF9JpB6vm5U0aZ18pT70P0Ikdd0aHruXZPhbcI9W1dcqk0v/jqVBZWSl+ICaz6tmirEX3nRNscLVDbJc7f1z5ZSfwpN5ztGilXmce/7YGqCD1eiIGagavn/KyVlNSIUlvZeQvkQv7mtCterU5wrYXz4I67X9FUxQYQ76qrWkPZxYmzyE4QL2xu6810JGnnxFflCdIXhP+cQ+hU6qf6sUQEeMMZBiP2KBCorgk58/mn7AkLat74kMfru7PO79OENJ7oghmU2mcqVJzwQEtp1bGO56YvZgJujVKkzA==
*/