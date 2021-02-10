/*
Copyright Barrett Adair 2016-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_CLBL_TRTS_DETAIL_POLYFILLS_MAKE_INDEX_SEQUENCE_HPP
#define BOOST_CLBL_TRTS_DETAIL_POLYFILLS_MAKE_INDEX_SEQUENCE_HPP

#undef BOOST_CLBL_TRTS_IX_SEQ
#define BOOST_CLBL_TRTS_IX_SEQ(...) \
    ::boost::callable_traits::detail::index_sequence<__VA_ARGS__>

#undef BOOST_CLBL_TRTS_MAKE_IX_SEQ
#define BOOST_CLBL_TRTS_MAKE_IX_SEQ(...) \
    ::boost::callable_traits::detail::make_index_sequence<__VA_ARGS__>

namespace boost { namespace callable_traits { namespace detail { 

template<std::size_t...>
struct index_sequence { using type = index_sequence; };

template<typename, typename>
struct concat;

template<std::size_t... I1, std::size_t... I2>
struct concat<index_sequence<I1...>, index_sequence<I2...>>
    : index_sequence<I1..., (sizeof...(I1)+I2)...> {};

template<std::size_t N>
    struct make_index_sequence_t;

template<std::size_t N>
struct make_index_sequence_t : concat< 
    typename make_index_sequence_t<N/2>::type,
    typename make_index_sequence_t<N - N/2>::type >::type {};

template<>
struct make_index_sequence_t<0> : index_sequence<> {};

template<>
struct make_index_sequence_t<1> : index_sequence<0> {};

template<std::size_t... I>
using make_index_sequence = typename make_index_sequence_t<I...>::type;

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_POLYFILLS_MAKE_INDEX_SEQUENCE_HPP

/* make_index_sequence.hpp
aRii3AL7TdDtwkvRfhzF8dpHnnyLkiUgY7fIPc6Baiea48+c8Yesqkec8ZiUtSV/CaIHAMI844xe3cco9pJbP5dGiM2+N+AroTBB7OR4qF5bKR4q4m5lEsYon+2dM2iZjt9cnZ68RnkYnw8v0svm9fzt5QAKfDlSmXOaawXVq4gZ9ceDdHQ6bvn1fxoFmNvStwVxvNYddXCA+YEHjuurgS9uvtt1Ud/AHDuhyFB4QTm1725f+jjb2246TQft5nre20vu7R4+vv3949sv7m9/OtqNnf1FDcu0EinUCzG3j6cAUx9m0T73Ae9OPyG89LeUi3rIDh8+mzWEGcbFiBcSzwC+SXFL2H5/FrD5ttEODoUWVn3jCGMAZkrfP6wwePvGUi6Mk6XMMyea4RgjZ4YZcSlChZj7mX3CXJaom75fNuNCaTBDYqLDPKatQ4uEW57UlMP119Or859vLk9PrxI6GPwV+zZUb4aj8QNUGG2RYXNPhmQCBCgNGhMjIaA/Vy2vYGS9aI53NrWY89UHpm9pmVS+t2VmmrcdbR8vd8F9baai5cniHXfv26NNZWhbGxN7jZYMIjsCQxxwWzFbP6fY8K2y5TKv7pr8zmsIDm9rhDkHhcwqlOP1VDkRMD7wXI+GeEccGh68N8aHSSLE
*/