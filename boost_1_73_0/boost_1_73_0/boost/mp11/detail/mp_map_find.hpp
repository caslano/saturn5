#ifndef BOOST_MP11_DETAIL_MP_MAP_FIND_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_MAP_FIND_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/utility.hpp>

namespace boost
{
namespace mp11
{

// mp_map_find
namespace detail
{

template<class M, class K> struct mp_map_find_impl;

template<template<class...> class M, class... T, class K> struct mp_map_find_impl<M<T...>, K>
{
    using U = mp_inherit<mp_identity<T>...>;

    template<template<class...> class L, class... U> static mp_identity<L<K, U...>> f( mp_identity<L<K, U...>>* );
    static mp_identity<void> f( ... );

    using V = decltype( f((U*)0) );

    using type = typename V::type;
};

} // namespace detail

template<class M, class K> using mp_map_find = typename detail::mp_map_find_impl<M, K>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_MAP_FIND_HPP_INCLUDED

/* mp_map_find.hpp
5rVufr7ud3Uyb+rL4dZ9u6vaapEcq9PNXKqmvZr2pW5qUzXdmhRfzlNd3DE+Hvb1qVXGU3/QLbj25EXy3F661cORmZ+qY93vyDyu/zQ/9u2LkWjNbt+YQ/1aH67dmhSLzPzpfOy2sespH9L0/R+fN9uH1Yf33emrz+ttet+e9KPrR9+PoR9jP2b9mPdj0Y8lzrL4wNmC0wXnCwACggAhYAggAooDxekeQHGgOFAcKA4UB4oDxYHiQfGgeP0poHhQPCgeFA+KB8WDEkAJoARQgl4RUAIoAZQASgAlgBJBiaBEUCIoUS8sKBGUCEoEJYKSgZKBkoGSgZKBkun9ASUDJQMlAyUHJQclByUHJQclByXX2wxKDkoOSgFKAUoBSgFKAUoBSgFKoWkBpQClBKUEpQSlBKUEpQSlBKUEpdTQDanT2FnNndXgWU2e1ehZzZ7V8FlNn9X4WeW9xVh5Q5CHJA9RHrI8hHlI8xBnzbNooMUNz4XyNNOioRZNtWisRXMtGmzRZItGWzTb4ocHTXkab9F8iwZcNOGiERfNuGjIRVMuGnMJw5OrPE26aNRFsy4adtG0d82TdoyuoN6apptqhXXV9qVu9s83c+88Uz23dXOvQnOvWvNSXc33uj6Zd9eXc/sumb/2azvApTm3
*/