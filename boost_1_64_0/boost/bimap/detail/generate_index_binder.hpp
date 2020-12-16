// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/generate_index_binder.hpp
/// \brief Define macros to help building the set type of definitions


#ifndef BOOST_BIMAP_DETAIL_GENERATE_INDEX_BINDER_HPP
#define BOOST_BIMAP_DETAIL_GENERATE_INDEX_BINDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/multi_index/tag.hpp>


/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_0CP(                                \
                                                                              \
    MULTI_INDEX_TYPE                                                          \
                                                                              \
)                                                                             \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef MULTI_INDEX_TYPE                                                  \
    <                                                                         \
        multi_index::tag< Tag >,                                              \
        KeyExtractor                                                          \
                                                                              \
    > type;                                                                   \
};
/*===========================================================================*/



/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_1CP(                                \
                                                                              \
    MULTI_INDEX_TYPE,                                                         \
    CONFIG_PARAMETER                                                          \
                                                                              \
)                                                                             \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef MULTI_INDEX_TYPE                                                  \
    <                                                                         \
        multi_index::tag< Tag >,                                              \
        KeyExtractor,                                                         \
        CONFIG_PARAMETER                                                      \
                                                                              \
    > type;                                                                   \
};
/*===========================================================================*/




/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_2CP(                                \
                                                                              \
    MULTI_INDEX_TYPE,                                                         \
    CONFIG_PARAMETER_1,                                                       \
    CONFIG_PARAMETER_2                                                        \
)                                                                             \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef MULTI_INDEX_TYPE                                                  \
    <                                                                         \
        multi_index::tag< Tag >,                                              \
        KeyExtractor,                                                         \
        CONFIG_PARAMETER_1,                                                   \
        CONFIG_PARAMETER_2                                                    \
                                                                              \
    > type;                                                                   \
                                                                              \
};
/*===========================================================================*/


// This is a special registration to allow sequenced and random access indices
// to play along smoothly with the other index types.

/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_0CP_NO_EXTRACTOR(                   \
                                                                              \
    MULTI_INDEX_TYPE                                                          \
                                                                              \
)                                                                             \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef MULTI_INDEX_TYPE< multi_index::tag< Tag > > type;                 \
};
/*===========================================================================*/


// This is yet another special registration to allow unconstrained sets
// to play along smoothly with the other index types.

/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_FAKE                                \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef void type;                                                        \
};                                                                            \
/*===========================================================================*/

#endif // BOOST_BIMAP_DETAIL_GENERATE_INDEX_BINDER_HPP

/* generate_index_binder.hpp
R/uthJXwJrgI3gqr4B3Sux8ugY/Bi+CTsh+1XeF74WXwNbgM7oc74DsK/wQulx23a2FT6A2nrprwzvAGmAR/BnvKPwPeCofD2+AoeDscp/Cz4B3wHPgLmC//MrgOLoJ3w6XyXw7vgdfDDfBGeB+8TeEbYQ3cAjfDh+X/HNwC34APwrfhr+BB2ZU7JHtyH0jfE8X9ELaEXv920OufBB+Hx8EnYF9o8gmfgiPh0/A0+U+Hz8KZcAcskj/1g/c2vcurL6Naz2e7VN9f0tilPTAd7oWnwJfhTHgYLoB/gJfCV+Ay+Cr8KfyT6sNrqg+vqz4cVn3YD5+Bb8EX4NtKF+HG3uA7MA6+p/N6UOfvMJwM/wIL4SE4D74Pr4OHFU+0/Y5IGSp/x/K7KbRkF7IDxN+018vg6fByeCa8Ak6Hy2AxXAEXwc3wYng1XAGXw1XwWrhGejdB0mLyewN8BK6BT8Ib4a/hTXA7vAU+D2+H78G18N+yZ+VN650wHq6DZ8BfwinwHngO3ACr4H3wClgDr4UXw43wEoifSfeHpl3q/QkW6TrXBpbqvKfiFQsHweNgOuwHM2EqHAIR60TVhww4Bg7V9eJkOAEO03VjBMzX/jq+3l0oW5fjl+i8zIHdYSkcDufCTLgIZsP5cAosg7mwHBbCClgJL4CLpf8T45b9MT37A47B8WXffoLqxfGy09kf9oQDYH94AjwFngJHwSLdF4fqvngSPBsOhufCITAfDlS6RihdmfBC7X8VHA1vgGPgbXAs/AUcJ/urWbAGjof3w2y4FZ6u++pE+AI8A/4OToJ/gpPhu3CK7HqeCf8Jp8me59mwFZwO28NzYCc4AybCc2EKzIdD4Ex4EpwFJ8ACOBUWqh4WwfVNeI6+7hjr0HXHNGjMYoj9NKftNNtm2tbNYecAhthJC2sjTXbRGj6+UTbQZOuM3/gthW72zZxjH7dr/KPsmGHDzGm7LPxYyOW1x0PKThn6slMWOj5Sdslkk8y2R6bxkuhtDh0zGWpzzG38pNO2mLtdMcZUYk8s3LjKxtkP09xE2Q0LjLncOVrjLmUjrM39UY22E1aHjTDGZdZvG6whcxmx/9Ug218roex9YecrYN9rLRJq1+sI3OclEjqes2NWYEznsCynva5gW11VF2JzC9mK7EUOI9FLWlqpyASkdElkDGhki2yRLbJFtsgW2SJbZItskS2yRbbvz3ZUxv/bw/+//vj/FYl8o9P8/+Xqj3wW6YA8jHzQi/7ZdZr/bw6cV+AfG34JYR7GHsy17DET0o23xxicatybrLkaa3KYfTS+wR5rMsPoXGdNJkUaA2fGFW0hVTPhjEbM0SdN9EuSJo2l8ectS9+gxiAdxP+wdz6AVVV1HL9vjI0/Q7cJA8YfB+NfiAWoBGY6EZN/6hAUBHIbbLDFYGMbMpR0IggIKhIa4h8WoqKRTaXUzMSwUjND0/4YJZUVJhWpEZVpn3fe99133nv3vm1AlPauHj479/y55989575zfud33gnm7T47b5GzKg/YeVM6P2P8nhzJq7HnyI5kuLEHInK0rZR1PxCT9jOV9r1Ke1urjb2L33XRaUfB4NCikurqotKSOurft44Urq1Jl9NMutrFl6mrL6KujdKjQEHrX/Hb6JGuBSXzyxKkSWFSDztN4bLKSI0vq4P4bYpLU9GsBUXzq0qLyuqrE6Sr6QjLKpyurR7p+ht+d8anazbv56K6MnNCvG+6dh5husJ1OLJtfLoO4Xd3fLrmIDRXW56grHYfpTS90Da+Xf0dv3s90lRZMrcWZ493VufLtrJd+b2DpWne5XQgLk3aIKUK9CurA0dYVqOVLic9Pl3/wK+zzT9dITUuvvU=
*/