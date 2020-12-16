/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_27122005_1117)
#define BOOST_FUSION_BEGIN_IMPL_27122005_1117

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_array/array_iterator.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<boost_array_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef array_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
3DiMnBVuVnaFW5Q9YVcYh3CrsiNcUM4kZP7KgdQnjiMXhJPKSWnfpJwSblEuSfu8csj5KqelfXDcf+f9PZM/wtKvj32y/v+bM8iFr/L6JIfkNrJ+vuBssjNTeIzWs/0acuJM4bXkRnJe8yHPIXvkFeSAfDm5SJ5L1s/Xu4TcSb6MXGL76ZrPaOF55BT5IrJ+nl2OnGH9fM2PfKnmR16p+ZEXkfXr+fFk/frbI+vX36vIXTx/NbmHvJjcyvYTdD3H8Hmn/ZEnkXPkyWSffBa5nTxF8ye7ZP38uqnkEuunaX7COx9eQvI5Xe934RyYzwPJRzldK9efckY4rLYXLimn0F+lnOxKfYNyKP2nlANpn1H2pL0rjEPae1WW9m3KPvNTLgh3Kifl/JJyRs4vK6eFE2do/tI+qZyV+pRyWerTykXhFuWktHer9ZKPrxwKtyuX5PxilaW+Szkt9WVlR9h8VVnGSyoXhNPKvnBW2eV6KmeEg6/+dz4/3+kj88x+8vkBL4h7T4v7LA9YXhLf6Qj3G9hbLvdP/8p+jv2b7zcq9d1j//H68/1VvLLtc/R6q69wo7Ij3KScEs4ol+X8nDAOqc8rl6TeV85IfaAcSn2HclHqu5QdqS+D+Xpf4cRcHW+XCjcol+X8lHJauFnZkfZZ5aSwq5wS9pRDOb9NOaitcEG5KPl0gnn/S/7KGeEe5axwwzyyK9yknJH+W5Szwvlqe+E2ZU+4Q7kg3KXsS349ykG9jD+fHEp9WtmT+qxyUfprrbbn/JVLHE+5zPGqLPUNC8iB1Dcp+xxPGIfUtyo7wgXlpHBXtT3XVzkl9Q0LyWnhRuWA661c4PVcZV7Pyp6wp5yR/tqUs8Ltyi6vh+r5zFe5JGwW/c37V/ZzGt9PkUPyWHKJPI5spgvnyPr36hPIDayfSG4iTyK3kCeT8+SzyD55qeZHnkLuIs8ll8lX6vgzhF0dnzxfxycv0PHJ88ht5HN0fLJPDslXkPXnEyt0fWZK/fnkJDnQfMhnk5vJ68g58tVkj3wBOSAv1/zIa3R9yBeTe8hryc4s4QvJjeSLyGnyQl0vcp6cJ5+r8yePJ2d7/55drlfWTyUXyYvIJfIcYbwREF5N1p/HTlNm/VW6nmSPnCEvJuvnBS3R/FjfSm4ln6f5kqeTQ/IMsv7/2jPJZdZfr6w/PyY7eb7/0fUmX6P5ka8lu+RLyT75MnKBfLnmQ15F1p+HzdZ88v/49fnd4z/g8GSf0vF+8vPWGvEC2Rfe+aiVcqe23zu6zx7zSe0j/ZYP7Cfcj+MMYH6DxE89QH5+Gh7J+k/2896Rz7HiUb5c8ml5Q+6/NL2H5S65URwP1O3LHXpih/Ke11nP8laWl1jesEN5J8uTO5QXXn97/w9RatBHDx/8sY9/oumIoz579NDPff4Lzccc+8Vhxx1/Qmb4iSNGnvSlL7ec/JUzvnrm6DFjx+XGT5g4afJZU9yp06bPmDlrdn7O3MMG7tRhqbZS5t2gXw8J+8I46iocKDvCReWkcEk5Uy9jtJPTwknllLRPV+uFs8oZYa9aL/kE1XrhDuWscKjsCncre8KJGzV/yadR2RVOK/vCLcqBsKtcEG5V9oQD5aRwR7U/Gb9LOSvzKyu7ws5NZE84pewLNysHwjnlgnCrclG4XTkUDpVLwt3KZeHEzcKIZL+UHeG0clI4q5wS9pTTwu3KGeFQOSvcrewKN2zQelm/JmVP6luUA1nPnLIv9a3Veo6vXOD4ykXhsnIo7NxCLgmnlMvCGeUix1cOhfPCOCR/X3j7Q74+lfxYfw65SD6fHJIvIJfJo8n6/dNFZOdrUj+dnCKfS24mz9DzyWPIHnksWb/fOVM=
*/