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
YRDmgNjPyqO5bMo/j8tu7AqhQS8mIG+rO5aGr9fSRYVl4npAoc7JCFM260GxvHMR/t74pwtONZwfdFePnl8c8IBMBdAXvd7GV0ErnL64Ii9Q7EOtoJLdcou3dLcT3xLu7OIyPoE/qBthH1A9fm2pkaHer97DGfYIjEiQYWRXaN93LiDCfgN0JOQ0/T9nNX5DbxMqxvheFI1eQIB+GvU5mVy7D+NqNxdrN7c4kNbB2r3moO5Ur90y+MO1WwW1W14aSOt47ZYbtVuGtVseX7tlptrt6yCpmXppn7E7KEo5KPpvCZupt3iG8FZo/HPTKp6Dnf36RDiKJyLFWJv+gs/xwP0+k8v1eCircfFW0LjBLlEWi4IWc/UX01pv1P9yl9D4hdMqFlJjW9ijbGjkPOAuThBygrF81XSlJMyN7K8n26kjydLFj+1J/us8itYzI+wbpe5niHmyfxL7Dfj1Z5ea0eJSL4c7BPftcD8M97Nwn/QL7L361aVeBbey0aWeCPc6uFdA2KdwD4fwQ+HuF3Wp38K3F+I9Dt9fQ1gRPNsItxd65Dz4PwrubvBb2cqxFVwIv6W5t4q/POlkyCgsGXPzuvfI32pLrp69lv9//dsvY/8XrGPwHmkfiHZw3/Cex7TBc3J0qE7HxZLjf6UmPG4IjfgXuDR9ip71FY58WgNPi2JJ7x0yrAM7xAz8r4T0byb3gqt64WfZ7vDpLhsAn1ll/eDz7LJtIn3BZgwdqZflwo8Z+CMLfhTuAD/ADJJKjTgtuzI17P9KuL64Rca7ubwH64hADtWplKbW7tQZG/hXMeBfaScS/nV2G/yrJzKUzOICBHb5SDFVUwOImP+yOLyrgN4/lHeUPoFhF3tsI7WjclU2rUEMhFONcYMIBPJI00I+z5KPo2rsSBPZEbpFfYjBOcggfBA7xqB5zuBq3Er7IIO15BgatYZq2E8eLt5AmgPugysKV/R8ZcRIvzJgfFgcedxEqmkTTp6bBxSFaSdM07Dx6ytUfe2ymd5wBsQdMHo9xCWjgUEwgFFlB8NWDlr2GASbL67qTktQg4aNbiovoVWTwbCn7oqDzilqYlqbzSN5NOhOyA59JM+JHTVOsihinbrM/nP3IXtLFX3Baxq1XwAdB/UiEWPguyMHIhnr/7CzmVr5bcebjJlpJI72KMvCLcmtBch5FX4M4vGbn2hCm+r8wyKzfArBzNAE80r0EXTOIYPwbdA7Gxz/ZkZH22qQEt6M3n6KiszzX5TVzXnH1G+voihXj2+Csk6Af7BnYhdlyv5rqorCUz9d9/y9jhDIYFEYjFun3HYHUB4uhRjQ4oej32dYn44POBzQozsXZCrcgrzoWI8mnF2Lt3DCafT/sNccZ+NnIJWxWMUCjDChNrfq6kvu2B594dKooGFhXUabzRmwL3IOMdtmoEj8uJ1lcwaj/zss9ny3k9snrltC4spGxRN35t5mWwskbpx14mLOPztMm393bUg4/37Yun2Fj/B/yM8A/ik3hA6rR2VuZrsiOPZx8p64TN7KBaymAvBM820WOIgH2JL8i3wqHGBPHpzpAPvWyJvzKXgZNowl7kzF+OvzL3JnAiv8yM/wIfVaRaKdQIaM9a9DTetfPnbzT/vpolMropVkH/I9q/qwn25Umhv30xXAlwYdEOgV947zYt8xexxy6Jo9yA3WK69qJsYSXk/JSRxLocMC4BA5PRZtQJSD0IaW5GhDZDcdaoj0NVyI9RRYrppkO8nubrd6Ctwb4P4R7la404AF18D3C3APgTsH/isZjgy4WF/PsO3ypCd+7sUPx/J/5gJ5SrqKbF61naIPVMnHv9Fi/NtbvONesQLWXRewtkMhlmDhACc=
*/