#ifndef BOOST_MP11_INTEGER_SEQUENCE_HPP_INCLUDED
#define BOOST_MP11_INTEGER_SEQUENCE_HPP_INCLUDED

// Copyright 2015, 2017, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/version.hpp>
#include <cstddef>

#if defined(__has_builtin)
# if __has_builtin(__make_integer_seq)
#  define BOOST_MP11_HAS_MAKE_INTEGER_SEQ
# endif
#endif

namespace boost
{
namespace mp11
{

// integer_sequence
template<class T, T... I> struct integer_sequence
{
};

#if defined(BOOST_MP11_HAS_MAKE_INTEGER_SEQ)

template<class T, T N> using make_integer_sequence = __make_integer_seq<integer_sequence, T, N>;

#else

// detail::make_integer_sequence_impl
namespace detail
{

// iseq_if_c
template<bool C, class T, class E> struct iseq_if_c_impl;

template<class T, class E> struct iseq_if_c_impl<true, T, E>
{
    using type = T;
};

template<class T, class E> struct iseq_if_c_impl<false, T, E>
{
    using type = E;
};

template<bool C, class T, class E> using iseq_if_c = typename iseq_if_c_impl<C, T, E>::type;

// iseq_identity
template<class T> struct iseq_identity
{
    using type = T;
};

template<class S1, class S2> struct append_integer_sequence;

template<class T, T... I, T... J> struct append_integer_sequence<integer_sequence<T, I...>, integer_sequence<T, J...>>
{
    using type = integer_sequence< T, I..., ( J + sizeof...(I) )... >;
};

template<class T, T N> struct make_integer_sequence_impl;

template<class T, T N> struct make_integer_sequence_impl_
{
private:

    static_assert( N >= 0, "make_integer_sequence<T, N>: N must not be negative" );

    static T const M = N / 2;
    static T const R = N % 2;

    using S1 = typename make_integer_sequence_impl<T, M>::type;
    using S2 = typename append_integer_sequence<S1, S1>::type;
    using S3 = typename make_integer_sequence_impl<T, R>::type;
    using S4 = typename append_integer_sequence<S2, S3>::type;

public:

    using type = S4;
};

template<class T, T N> struct make_integer_sequence_impl: iseq_if_c<N == 0, iseq_identity<integer_sequence<T>>, iseq_if_c<N == 1, iseq_identity<integer_sequence<T, 0>>, make_integer_sequence_impl_<T, N> > >
{
};

} // namespace detail

// make_integer_sequence
template<class T, T N> using make_integer_sequence = typename detail::make_integer_sequence_impl<T, N>::type;

#endif // defined(BOOST_MP11_HAS_MAKE_INTEGER_SEQ)

// index_sequence
template<std::size_t... I> using index_sequence = integer_sequence<std::size_t, I...>;

// make_index_sequence
template<std::size_t N> using make_index_sequence = make_integer_sequence<std::size_t, N>;

// index_sequence_for
template<class... T> using index_sequence_for = make_integer_sequence<std::size_t, sizeof...(T)>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_INTEGER_SEQUENCE_HPP_INCLUDED

/* integer_sequence.hpp
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
*/