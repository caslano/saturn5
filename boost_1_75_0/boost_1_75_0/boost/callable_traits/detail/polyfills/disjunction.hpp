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
EhmnRNyNs0aklZwmi+TMz5JNw1Qoh8utCN9DL2b65Olp6Lk91lPWYi0pzJNT8sr3lsTJP4e7SmXrYLbXTPJk9Zxccli+Ob0sbC29wjf+N698QlqxL84bq2bfbS9J9o0fbPfKmyXZkRdbrTxTF2fJ2AjYcq26Vio74MTlPg3YgPhceY0PFlop8Qmw+tE8nV2AJyM5xeRDwpmboxVJ41dJsdUe2VebRHtVwC6vDK/TeN6yLFw1fhcbGABfrLoGXIjgzLaUhPVYOgVkIRicjJZWYwBMtvM+REK5BnhZ+wcoIEhNDdLVFgD/vf2k4Gy8AbbZIWXX3ddJWtbIkaUcUtkeYC9XKFloftdvT9h26Y6KMZZwEl1UVydot5JCaNmljHXKD88jFwmtBSc6RQ5PEddK8NMvfWCYI0vy3wj1E3HhlX9R0gmzmN8detrC/rATOfQ5OxKw+XDQNWC7jY2RkbAJA+WL6Fk9PiMjSLRkzK4D5rdWOHIj+wg7VLSNI+6k6RS4LFuzkYXamhV0KF+FrMC0OKnsXItgyQQHTTRR2C7//pwWnEfMoBtjHkBVE6MXSLKZjSu7LRk+G06G0f2l4I3NvmCXn8uOqj459mMnnie3UL09pBXfQwdW2hGDv38O48CU3ZYWsRApNpG8ouwWWDTeJHVVhO+dKa0LGu+lvW+SZI5ixl3yn1V4G6DIlVZkFvdi+jHHUik9MCzdd/ak
*/