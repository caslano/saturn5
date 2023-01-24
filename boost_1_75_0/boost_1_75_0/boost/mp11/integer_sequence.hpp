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
OfSU1XjPROclIlKTF8xvmtWts+OPUo6rAk9L73LahddpafpBa4yNHhPdEDY23KJFNEQ1RmZHeSJHRcSEx4fFOwbZM/uVRm+MGTtooBZXF984ODveM3hUXMyg+Jj46EH9Jlvp06XZ8c4oZ7xTl6+YCM+nr58MMt75ESW6PtuagjFQ3peZDmHRGXb+Hlt650sk/Y3EFHg3cUNAsy/REr2YUyy1xtvG272OOmdj2ASnJyzFscauhqZYLU8MpR1I1b/ao53dXveX/d8Z3F++DuGLM4x5ajs/shEws4ryaqP1OrSlbZj8RlAMNhX+Lz4vFD+Ywx8BIX+wnd9xEvgsrdpxagv8IuWgh+R3YdOsT0IFU+0tjngbPZY610ETJnq7SbYxrvVzDUG88d1+X6d5MO/3PwahJwb9OJjYoHtKDdXo+jITk1m9uRYrF9kLef1bYCWd3yjye/9QvbXgQ+1DiyaiY2iCwd3QlBSbyHtB3aFabWuyP+koRkeUgmrKd2aHn6FFjI1cHTW5X6ge/Xy/W7WYh7V+au8owkkd0gT6so6VN5TDCmgTNiIyMqbfqGgnffiic2w/DWNTv27H9pYzeWx/DMKHMM6wJSl8H3DgexWMjUU1kPuXQsXxG5D2ROt1jjvsm8N8zgvDYqByw+2jeGpVSCnTKXVGv3QG+qU49AWnoy+ICeoLkuN533EMhNJ40oU9G6zoeFYtsqD+SW4s
*/