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
tj2fKckXAnf5ED7q56vAHOBxAr77gDk0hG8E91FgnpPgO+ll4F8ezrf5ZaVyNfH9NnD+ED7CzUny9YC7ToLvDkm+e4E7OIQv63+SfMeAe17i+U5+RalcTXynAXdmjm1rj22SfCFwlw/hy/ofMAd4nKj/AXNIgu8oMC9K8K1/FfhX2/moPba+qlSuxv4HnC/BNyfJtwTctRJ8t0vy3Q3c/UP4RnB/VZLvGHDPD+HL+t9PlMrV2P+AOzPHtr3vNkk=
*/