// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_DECL_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_DECL_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/none.hpp>
#include <type_traits>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/handler.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/handler.hpp>
#endif


namespace boost { namespace process { namespace detail {


template<typename T>
struct is_initializer : std::is_base_of<handler_base, T> {};


template<typename T>
struct is_initializer<T&> : std::is_base_of<handler_base, T> {};


template<typename T>
struct initializer_tag;// { typedef void type; };


//remove const
template<typename T>
struct initializer_tag<const T> { typedef typename initializer_tag<T>::type type; };

//remove &
template<typename T>
struct initializer_tag<T&> { typedef typename initializer_tag<T>::type type; };

//remove const &
template<typename T>
struct initializer_tag<const T&> { typedef typename initializer_tag<T>::type type; };

template<typename T>
struct initializer_builder;


template<typename First, typename ...Args>
struct valid_argument_list;

template<typename First>
struct valid_argument_list<First>
{
    constexpr static bool value = is_initializer<First>::value || !std::is_void<typename initializer_tag<First>::type>::value;
    typedef std::integral_constant<bool, value> type;
};

template<typename First, typename ...Args>
struct valid_argument_list
{
    constexpr static bool my_value = is_initializer<First>::value || !std::is_void<typename initializer_tag<First>::type>::value;
    constexpr static bool value = valid_argument_list<Args...>::value && my_value;
    typedef std::integral_constant<bool, value> type;
};



}}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* decl.hpp
S+shHKL7f2Wr5zrc3R10WGkwsIylvNoKY3wtIG2ZrcLDk563YArxDI9YgfKRo7kdWbGmIft56PwHlKnwUNT4/O3pbAPUj3ZMRNW40QaoEVNYcIDFm9qpu8ZNKawNvL3CV+vaBm9cQ6Os7kB5lRw1gSetU8BUXnWQTk076aDLXk1LkkzUQF1GWF/nBzOyS5wqV9FW17s+YIs/YwBIJrLRPkv2fGYLELUcb8HYXKd1SuU+JBViSmLkTRgbDi4HYGmlM3Nh9tIOX4n6l4vqUXIBE/CUYgZJseedd4YolMErvFjMjar9cZpsNnuL4q0x9R22SHtNjOZXnt1Cv6G963Kf5/Nux/hn7wwMhz4yePibdh9YI/PvByMNcUwKNW9n06oIBPbZxydUvHwCKxLushP5vG68+oKEFusIuqG1hcoN6WHhq8rVCrTZAG+D/NyBSKXM6xXrfUXAvLT6TSBAeWkHzBIqSR1TahTSgw4ASkkbzMq3S77PnzHtinWkoW4jwvYfxbOkpPSkomt6xCbMUEjFXww1Qy2j616Y6ENMz2RbT7PIeb1bd0MbAm4NMA==
*/