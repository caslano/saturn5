/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_09172005_1156)
#define FUSION_ADVANCE_IMPL_09172005_1156

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    template <typename Vector, int N>
    struct vector_iterator;

    namespace extension
    {
        template <typename Tag>
        struct advance_impl;

        template <>
        struct advance_impl<vector_iterator_tag>
        {
            template <typename Iterator, typename N>
            struct apply
            {
                typedef typename Iterator::index index;
                typedef typename Iterator::vector vector;
                typedef vector_iterator<vector, index::value+N::value> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }
            };
        };
    }
}}

#endif

/* advance_impl.hpp
q3FyBTbeFxiNu1x6WeMeh1c/oFTQB6mb4gdCajttWd7eHap1Au//VZWj5Ti+JR3qqlz0eIxun9G+kUbZRBWd4qfRyhvwMGN24fz7+pt7eZzVPmep11nhdxz8d7vUeuq6p/pvp4v66uz0x3s0N9bu9G09pxHf05X1nER8vee6yxFmh0/rOuMj6/D8OHbPhO5U2ekwfXNsPy2jSOa/nh4dvHh+8fLl0an37ngifhY7v9lzf8OJ/ovRzhlz951iXoMUFh+W9ZeF6U25KAxpElZlw42D/e6KF3PBCWvT+qcBZ8ev3h+/P/L+eXB6jDdnh/irLgBhI2XzMy9PXSVgpsNOYgGXm4PsQdMNnsx0V1jro+f6RofhBd3e5vro2jXOAGJeMzMvOertIY0nwpTSTNGd3i4d7eazliG5pALQ0Nl6I024s0i+DO6sNNZX20PJBVX8k2Rasx4vEVoLlH4f0/vzzp59honeqqZuiHrVVf6lAjHnnj9BPPkYq90XWkZlTA6RfiZ4ZUszC2Fwz9UCurP8PQvI3/UwiX9VZu5V6yKU+GOetb3nHNQQqXtV5akv4Poz463FqPK+EdnCLh9qsblW3cazLqonboPt3S9wW1hW/PowEw/D32Bp8yOjEUMGR0f4I/X6RlRvENI5tVMj
*/