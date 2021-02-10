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
kit4xhJAwWzOHwusHrPQgM8Flh9/zIQsq0JfHCoHuKOQ+kPq3JaJL9nXgkuWgx8GHhwOwtA7gvVhRn6ZohkHB8DnYG03J+eKjkLr1eUb54NPe64fvL6s7xXYpdz+vUep/zPMYHo9Gt+NdDf9CY9WVBMFGPfXEd8aql265UvberkiWJs74z9QSwMECgAAAAgALWdKUqhJ/P7kAQAAbwQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDIxVVQFAAG2SCRgrVRda9swFH0X+D9cUvJSUJSUMVajGUIWltARh8Tty+iDI1/HJrYUJOXr31e267gwtg7aF39I555zdO5F3KKxIjYYEJ7LVLnXDi8npRMTkFkULesH/JxGzcdeq/OFcNaBOGvqyA25gTXqI2pq8gQJ17gvLg6QxDYGqUSGYve9d0HTa6jZaDCCu+EQwgfyuJPqJGmGcYLah02hDxsyUdKitPQXyq3NfPhKCE2Vok6z4nSa3NSCokwCIpSUKGyuJC2VzK3SDvdmn7NXQ7XTSZFX1I1TUf8ELV1AMmv31+qAAJdx6SJaIT2YXG6hywI6WUiVBntSkORpitoxQqaMharWOA7WkAAXqixj6SxR2nBUcj5j/Vm4juZLv1/RL8NV1G5U
*/