#ifndef BOOST_MP11_DETAIL_MP_VOID_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_VOID_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

namespace boost
{
namespace mp11
{

// mp_void<T...>
namespace detail
{

template<class... T> struct mp_void_impl
{
    using type = void;
};

} // namespace detail

template<class... T> using mp_void = typename detail::mp_void_impl<T...>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_VOID_HPP_INCLUDED

/* mp_void.hpp
weOTKCPpqaCS0gPfulR4pL2mJBDcrfnFQ03JrRrX4nH3KySDHr2J4pJWTmGNPGGuyc+KLlKsekvGlk0qhDPzPZbfDpMHqC3LFhWrCOau6CKHgQPHS9l3QIhDxfL3r5ri7RaZWmqBm/7Gd8srKZcDC3xFw495ZrmW8bCwrNq3v/qmP9d2LrE+h1u6OQOKLurZ8lC9HKE+NIsVjPtUvG/LGOSYQ/lEQAddyKq8GCuWHIJidkEKPgq8+mRVSwuBmpbOE/jlPmLQViYVuUyX3APyqmYKZmmw01p10u6OnF6J7YxG3FxmTFeGmDWfvam7LQgS/aO1qsPEoUymxEem1JL743TsJwYm1Yig0UdwbVLkBF50j4Uxv7CpXY4/XpuQSIkHzhdYQYvS4iED82IpWe7l3dYdIHyj/gTCYXTwRBxUBjaW9fkPQExyfSAiUlJwQgF7zkkEBtEoETViGJXZeU9S2M6pjiEolQhtB2ZycfsfDFIGMQb+GrgDHElCHejuXIyUpNX+ZmyilT0kDv+wF6iM0uU3PRgcVqRjN6EvoFxdorOLWqYMJ1L/1UnBwwBFmiENmnlUc/2uWm9ohRWREPQdadAQwDptMwl1e7r0QMAy6uW0RlGt1m3dNoYmKl8xwhYXezgzjsr+yuOYI2UX+bZNAJJi2tfbrx2i+V0BGyAlyJxiCXsp5eIZrV8XRLNJuwDotNfJ675vhmvtrZEu
*/