/*
Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_POLYFILLS_DISJUNCTION_HPP
#define BOOST_CLBL_TRTS_DETAIL_POLYFILLS_DISJUNCTION_HPP

#undef BOOST_CLBL_TRTS_DISJUNCTION
#define BOOST_CLBL_TRTS_DISJUNCTION(...) \
    ::boost::callable_traits::detail::disjunction<__VA_ARGS__>

namespace boost { namespace callable_traits { namespace detail {

//polyfill for C++17 std::disjunction
template<typename...>
struct disjunction : std::false_type {};

template<typename T>
struct disjunction<T> : T {};

template<typename T, typename... Ts>
struct disjunction<T, Ts...>
    : std::conditional<T::value != false, T, disjunction<Ts...>>::type {};

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_POLYFILLS_DISJUNCTION_HPP

/* disjunction.hpp
NLsm/ip9y6Kpo6oaQ15FUrIw0+bkh38yTQxli0Q8shA7F3bkVB3RT42ACxOqrL7vguaZvSIxTqQplAtZDOYKRl8dXcdUqG4uIbovf8srTCFC2qS52w3RYHIXsZ9DbMyIdVh+zx5WRSHtQ42aL6lTArrgRlg6ss5Ex6iC8njuuZvOdiggHmxHfMlnCEOuPjk4DxWOOCz4bzYRLUSHZ9T6cAAtwJ6M2exF8Osxz8Lx0/Q01FrKmRexYOu6utLRud9gA+5fvAs37cAArARlpJsJ7b8WZX6UjSs3/X+ypAXcWvqGO7k+YdKNNs2d44c6bZ8dWHJSlrEguytpUlM3YKwcHGb4EvO05t+Au4acDDVxDnX2nx7vbx5RmHjL3p8b7jJoAma/8v6MMy1h0ymPr2AeOqrfn2+BvPEFsccclC/fDI6h7as4ylYXakaO8/VrkSGFEJgrI/pIRAMMefBaW4Ou3hXty4aeNriBCI0pJhTPBflljQJMatccxadFLr9yr2AV5hJu+YCrkKjeJGF5AFuvdBVxuxvLyaXei16y5FfRJzs0AZsznKWy74AE0Q==
*/