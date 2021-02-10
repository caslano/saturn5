#ifndef BOOST_MP11_DETAIL_MP_PLUS_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_PLUS_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/config.hpp>
#include <type_traits>

namespace boost
{
namespace mp11
{

// mp_plus
namespace detail
{

#if defined( BOOST_MP11_HAS_FOLD_EXPRESSIONS ) && !BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )

template<class... T> struct mp_plus_impl
{
    static const auto _v = (T::value + ... + 0);
    using type = std::integral_constant<typename std::remove_const<decltype(_v)>::type, _v>;
};

#else

template<class... T> struct mp_plus_impl;

template<> struct mp_plus_impl<>
{
    using type = std::integral_constant<int, 0>;
};

#if BOOST_MP11_WORKAROUND( BOOST_MP11_GCC, < 40800 )

template<class T1, class... T> struct mp_plus_impl<T1, T...>
{
    static const decltype(T1::value + mp_plus_impl<T...>::type::value) _v = T1::value + mp_plus_impl<T...>::type::value;
    using type = std::integral_constant<typename std::remove_const<decltype(_v)>::type, _v>;
};

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class... T> struct mp_plus_impl<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T...>
{
    static const
        decltype(T1::value + T2::value + T3::value + T4::value + T5::value + T6::value + T7::value + T8::value + T9::value + T10::value + mp_plus_impl<T...>::type::value)
        _v = T1::value + T2::value + T3::value + T4::value + T5::value + T6::value + T7::value + T8::value + T9::value + T10::value + mp_plus_impl<T...>::type::value;
    using type = std::integral_constant<typename std::remove_const<decltype(_v)>::type, _v>;
};

#else

template<class T1, class... T> struct mp_plus_impl<T1, T...>
{
    static const auto _v = T1::value + mp_plus_impl<T...>::type::value;
    using type = std::integral_constant<typename std::remove_const<decltype(_v)>::type, _v>;
};

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class... T> struct mp_plus_impl<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T...>
{
    static const auto _v = T1::value + T2::value + T3::value + T4::value + T5::value + T6::value + T7::value + T8::value + T9::value + T10::value + mp_plus_impl<T...>::type::value;
    using type = std::integral_constant<typename std::remove_const<decltype(_v)>::type, _v>;
};

#endif

#endif

} // namespace detail

template<class... T> using mp_plus = typename detail::mp_plus_impl<T...>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_PLUS_HPP_INCLUDED

/* mp_plus.hpp
YKVW70/bOBj+bon/4VW5CagoKRwnnUqolrYujShtlKQwbpqqkLrUWxJ3jgNXne5/v9dOSruN3RVdPiSO/byP39+2rViu4ihnbbIPHfzOQGSgJ39vNonNs7loE/sLWz0LOcvbxL1xPNJNWCQhZH+qPdKnYXdAGo2EP8SFTIhtbcC2VcqTfSQPmHxispHzGSO2ZMtkhYBZpKI26UuRtiBl73ORsucFk2yPhKIF8+gLe5+JamaPPIjZSn8bjT0CsBKFzCHnWYzLCS7YVklnWxW92bebcJapat/Y/CAkN9q0CU+jJQqsf8HOohR98WIPzIUEbTQYQ1HJPI8eGQKtEolMimVPbRIEw2mX+uG07w7ppeEsF+xYpGmUzdrkQO/Wsqx3g3EQul7rnSb2xn5onZ6fNa2LG8cduqMe/XB5egCNAgpUq5WzWDIFG40S8WjpAGmZkxg3euHHYWWfsfyWST5fgXYKRHPFJKgFM7GFRZTDA2MZ1PKFUDViPxksUiylUCIWSZs4zeYpdB3P6aBW4f2enjiD4fjKHRnNoNTMzP8KAR3SbghaKTNzXjnsFDrj3v3HT2byNy0+noQ6VpuN7DlPGGh3Xta+Na4GqZjhrMJUq7WJVV8/EETpEoViXIZHljEZKUzdh5Ux0bip8gok
*/