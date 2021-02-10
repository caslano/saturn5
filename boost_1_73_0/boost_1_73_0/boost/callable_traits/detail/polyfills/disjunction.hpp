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
3lrlgvQd8HszHl+OQvxWGsq3VgQm1tVlidC39VysLTh+3n1Oa+OYXQQzprlZLVwML1OZmdbxLQ0Hu0eEc+fHUDLahFgul12Nc9ZWXW2mITHmmXrePege8sP3vf7VzeV4mKp6nrKW1mcLcwlSH2U/VfVi2jKGHcplnLPMuEaW9gKL3ltGNz04OCzGHkU4qJXS63S+KkQplaDr0Wk6vDy9YJvgFEjklbOLa+/mPNeGCatVIJIqr+pC0LF1hdTd2autpcZZu4scC6FAYHkt9OL67ZhedDgKliKUJV+CppWeZBVnZIVCyCG5jsEpFkRmV6wTpwfOINGhlGXr8zZUUh+6KXYY1syYbHXEepeQvG3rloqNp3oeNW9Tw/JOy8LHUNpqEUnluGKh2vCTWy24js0yQ/scjGG1goVx538doog5xLxztH7jXX6TZcSM6Bk1oTAY9n+JicnonjGsQvQsWhv0juXexjGz+YR/UVnxIGGtHif91GlNrZWVUyXYXDWlhoksgsrelt0TRjjASnynlxTtbMatEijYZeRF4RjKbaDaCPX4SiVdSIEtYQyj9ALWmrOYz3wcN95M53CQzqP7WRXFnLR/87Lyv0KX94UFzJCRkYQqB0ckjz+XhtVvv33YiWznjifkbZwgEQaDxhn4
*/