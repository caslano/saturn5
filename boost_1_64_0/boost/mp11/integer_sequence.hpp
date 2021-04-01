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
VQAwKJ73qgLYhzN8CyjUQxtaP0Rmjhq9nqcfNi5+sy6KNG9PBK067bFNLgnUnyj74xvdk2E7mtKp5Q1W5rtPm5j8v6LFwN1ex8JXgmAWxvBcwlBPE1yg0/dbF5mgb/b9KNNACFrLS/Si2GTZhBl13r/UsK1/XWcX5wGISm70tmVJlpuWC4APdadId0fnmE0QaiQhvJlmycM5IqIAxSmpO9aA8RsEwUfnQb2IqSePaIsZcgMUFLauuOh/7hlImqnT3a16Km6fZup7ef9MbvOZqk1cFCSUgutuBE3GP0+TCofcvc91Ttsw6fB26USHEztdbvXNWwbDl1ZtXMIbKgvLYhuEIluZr0IQ6jf/0i4FA5CA6twCSB7lcDr/CnhVuSGhvT+SoEW4Hgdcz/slJEZzwqQ15GEhM2BeZCenFtPStbTE27yEIinZ2/45oFsb+fmZ3FsUDpvwZih3+KD0g/j13jgvKhHNNjbXs1qELDVO1iRBIcWjpu7TUrzeLePrMyuhm7B4MacgiSS0HJU10EFsAyEK+bqsNlQSJu5Ba2VbmJG2D5KGNWdcKH65zQ==
*/