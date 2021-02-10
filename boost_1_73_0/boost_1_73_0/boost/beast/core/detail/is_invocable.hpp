//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_IS_INVOCABLE_HPP
#define BOOST_BEAST_DETAIL_IS_INVOCABLE_HPP

#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

template<class R, class C, class ...A>
auto
is_invocable_test(C&& c, int, A&& ...a)
    -> decltype(std::is_convertible<
        decltype(c(std::forward<A>(a)...)), R>::value ||
            std::is_same<R, void>::value,
                std::true_type());

template<class R, class C, class ...A>
std::false_type
is_invocable_test(C&& c, long, A&& ...a);

/** Metafunction returns `true` if F callable as R(A...)

    Example:

    @code
    is_invocable<T, void(std::string)>::value
    @endcode
*/
/** @{ */
template<class C, class F>
struct is_invocable : std::false_type
{
};

template<class C, class R, class ...A>
struct is_invocable<C, R(A...)>
    : decltype(is_invocable_test<R>(
        std::declval<C>(), 1, std::declval<A>()...))
{
};
/** @} */

} // detail
} // beast
} // boost

#endif

/* is_invocable.hpp
SGIkojILnBspQmjnunBrMXpbf8hSni7dxvf7k3lZQ5hKztJW4zOqiExDcYIPiURO0Cf8DkcnDTwo8EmpgGWRYzw3d6Efw9MkvMqaLjxDrRaZEJFTtAyMtuMYe+0WVM7QGIpZw1xjdRrwyLgBf9L4avjCMgtYEWLFrjLKGuYnZJp9S1MluD87D4RuFFuod7L+YL8++T5IFKlg0V231fUNQBIy6IKYFT+C7mw48qAdURLWoGodQyOyjWVbyMKJWpb1CnP/fDbyZ15vcHY+7vu9d5PZwihQaiPC5azRuLX/qIVR0sl2hjITcR0YVYqN1iEP0KZCj7EtJabbZUqDjbXgqdQ8Zzp+qCa3JRMZsMQI2vLTIuWy1PWnAhvhDhnrOrU4eOivCxZM2IHEa0iFSx88//1k4Y8niw/Y3k6qWg9MgERrJHOeOVsQmsWyWdfxEyTks0GfW47H56OR+XLNjnH6lawRET5n6s5XXOMMcLaZISST6cI/n44mPeyDL8nM3kqzEXWsms9WnfiKKJv2vSxh78OamE8n47nnL4afPGzWbk34AYg+YF15M6qsxXAydh/sV4anA6wNeosetpHtpB6A6GI2XHgbQFud4QAj9XWxNurLu38gpG/DiKxX28zMLpEzpXAloV2AU6PYP2NT
*/