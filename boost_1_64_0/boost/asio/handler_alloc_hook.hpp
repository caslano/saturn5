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
8vQydgoOt0dFLkPfVt5OwS1vp8TjdngButwg8npQXmXoJe20jDxVqxy9pJ2SPLNHopail7TTMvJUcDl6eTulLMvYG7HK2pvN5/ZCibn+E5HRS7aX4IDLw/EsHk7T8yqC//J82255O/xtgaQpF/k8H7HzEs8t/MKrR1RaR2E1ZPn6sgN4ruqSTyeFClrrnDxcWFgIJYEq1npejwoOyx8ufLnSOp/uy+yx4wU4w3bW2/HYEMnjQVhSrsn1IVTM8QSPr6M8eXJOK7pfZJSImgnoALEUXa61xK6Hy1vtIvxyydMQDiahUoLB+AXryT8WuoyOUC3pOF0sVPs5PbTpKdtj0VwUuxy02zA534IZ55Kc862OpAbwdKLBTF56avy8RMEXu0NLQ51xqp9jv7VHbB/0AajA7ugevUTdXfnxehBd1AOVsOWTVr1YdlLeGmg4RXsS2N059QC6Iv3AvDxPsGOrFGP0Fm8oT5vnkvXx+Ld2lKT31JeWx5Tlpm8iAxugUwa0TzG4gZE8MoY3BPHiA17dMg0d5TE5y3NfULolYxhRW563t83vx5xJdET0bF4viG7QTXuzyPsB1hswhkSziC73TXFDPMtxJuT7Ek+br8fnwR+nB5LoAfN8eR9MD9adwRMauf9n/OvgYXXGtyZNqeNMrgMeEKHRyjXB+Z3ZIcfWPgB/qz/QsVHF4/C3xuJpYZfqOVeXLxiyH36Egz2K19azxSMiycKgR5n4dV1tnT2etnCXh7jKf5DFQwlP0sx6SFrpuXgulCG3g8fphaA6qrKccnpXWbm0GU5DEWJofnsWT37P988X+SniU7otoU6XHHb/QxgolBaCiw3HFXDn8tlwf3wd88fXMf858cl/TnzydxPf9ncLPsu/ieXfxPJvYvkTn/InPuVPfBp/KluNvyrbwW9i/CYnPxgINqhMBN+IGw2UiYvfxPgibgpvTkGFtu8rZ/nCyIlP5wVy8IZaD9sEKNNZgJCI636Ht4A/63Km90QzcMlmBgaLW2fMwnpKUWy5ZCYBayz4Uimlf5KgR4mSgSbwp23O52Vg65zvyj9u5OCIw9RB+TMCHjiKB04YKrLfRBT35R9FknxDU2NRHvcXlV9dV1+Ux/1F5evr7fxxX1pe1VvIiJDqJeJWSOWKuBVSvpQn9ZOa4uM2KFD+tn8olk17cIBAxHdj8qTQs5tcAtTfJR41itMSbtzIZlqIRn75nDueY/FYfS7TV7emYaiOxetZvMEZX7vGli8gvq6Ox1V6FbfTZ2W8kcVXO/Kv9zbtduYnnmvyeD2L2/nLeCOLu/JfWy/zp3iDt9FVXsNqKk/x17jr09hQl0ec5tFcXV09Re14vTNe36T4Ku7mr/HuJL6Kk7wdd8oDF13yUDYed6WH8rr4DU1u/ur6Ome8UFfXwONUPsVF81ncyYe6qPJUnORVnOW3jvHXufn1DZSfHSd5FV/n5jcx+Sa3fKOX5O24i796bZ3iq7jiK7vEQcM0ng3DKncXUiYxy/IbLsJvvAh/9UX4ay7CX3sRftNF+Osuwq/zXoRfdxF+fZGPiY3W/vKieUhMb046nSPpiOZy9FDCJU+y+vl8TIjJPkyIqhiWrk2yzy+vK7ozZezB8YD6Tk+DRufCG9z0RkXHTQwTZyqVjBYPRdBl0+nwAqerQwZ0+fE4rr29zacOX3B5+xAGl0f+JM/LLSkvyiV5Xp+S8rSY4/K0qCtdH5Ln9VHyvD5KntenpLxavJapD9F5fUie14fkeX1IntenpLxa7JapT1OZ+nB5qg/J8/rY8rw+XJ4O45Qer2yZ8SJ5Xh8lz+uj5Hl9lPyWzkBwI/HpfFnx+F/xETbZ6iCWkP1Jeihl26c=
*/