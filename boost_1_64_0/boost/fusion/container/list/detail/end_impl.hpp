/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07172005_0828)
#define FUSION_END_IMPL_07172005_0828

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    struct cons_tag;

    template <typename Car, typename Cdr>
    struct cons;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef cons_iterator<
                    typename mpl::if_<is_const<Sequence>, nil_ const, nil_>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence&)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
/BV/ohf+V/sb8xHQx2WXsS3ii3xIWPtfXA/U+3Fyer3awO3lPtylO8uwg6teDTZRd0q6Z8lc3xlIEBcXuaUbH3Zh5OgLwqPiw8fFxI85r97319EdVB3idX0F8Zuk7QXwdekm6/o13Q26JvnVtif5iVLX6Cq2QJ2P77jI2KjzI9QJgfrbUFxgYqtU6k+5Fw26VPnVtqO5h/CBti7muqi34KF16SK6fCR9g3TFHLFb2ml9zcshwVPaDbQd25ByqO5buxw+I3yRR12yM7MaYG9T08UtXfspte1ofsm1lZ7SbaBt2C/862dP0/uohp8bab5novnsb+ao8c9be8+OzzYHBs7dfGFu6sI1exkzaK34v/R23Nfr0nrU/LWoKOKDPo//wDtT9S/Zc2nvZQkPtr3h2K0tuvy09smG2/Fcp6ab0/3mA3PH333ZDf6XrOgQdEy1Z/ueMWq6u69PunVN1x831nSe9MmWec9T7mv6KP73P3b3C2+/duXBOR3LOp3a5udx/77zKs3P//RkX7Xhe0Eaeo5luHr/hPzcv1/sT3k3rR97mfder/nXNtyu6DB1D8r6ispebcfdsW7+J+s+tp0W/HTjzrcsQmQdono/VbrZdRyAPTpfeCqMhAEwFQ6E2XAwvAUGwsVwKLwPDoMvwSC4DY6An8Ng2JZ0TocnwBB4GhwFR8KzYCIcDZNhOHTsRZC1gtBH9NTvRRjLdT4wCo6GZ8NkeA7MhNFwHjwProLnw80wBr4OL4C/wlixr3mRpFtjkzV8sEDS7a6MS0u6n4gdvj0wAFbDYfALOB7WwBnwS5gH98Kl8BtYBL+Fa+E+uAn+AF+FB+AO+BPcAw/CA/BX2AI9foPHwz9gb/gXHARt6H1mCwDPhUfBJNgKTodHw1nQC86FbeD1kDqRcz1lfSBcgFS6nevZnes6wh6wO/SRcu8JT4O94Bh4EoyFvnASPBnaoR+8CfbV7BzKWkB4vKSnt+u3kOtaw1the3ibLpy9jnAFEu5mCXeLLlxhHeHuknBLJdwyXbiSOsJdL+HmSbgbdOEqJVx7k3DZEi4HHgdn6Ophn4RbZFIPSWKHcirsA1PhCDgNngWnw3CYBsfBdJgFM+DNMBMuhHZ9/mS92RATPd+T81V3wgD4PnSG2yfhAkzC7Rb7jx/CfvAjCRdsk7Va0F/CtZI4bGIn83h4FewJZ8MBcI6+/iV8N5N0FynvGXgH9IaL9fVfR7hrJNy1Ei4fOs/rLZFwSRJOf17vZVIfV8AAOFHqIx6OggkwHiZq9Svrg2CaSf0eJ89Ze+gDj4eDYQd4OjwBjoQnwgtgJ3gx7AwnwS5wKuwKnfZcyyW9Y1qSnps912I53/dB6AMfgoPgehgKH4EXwEdhEnwMzoQbYAEshXfDjXA93ASfg2WwEj4FP4VPw/3wWXi02Kf1huUwEL4Ao+BLMAFWwFz4CiyEm2ExfBWWw9fgTrgV7oPbYBvy9obcZ7k2WYsEV0o5t4Npku9Qsc8ZBnvAcHgKjICBcAyMhGNhNIyCE+E5cDYcBxfC8+Dt8Hy4DMZo97msF4KRJvf5W/L78TYcAN+R8t6uOyc6X8KPNLnvipTfAbgSdoX3w75wFRwIV8MQ+ADU3kcSn4/J/X9mS+4DGAJ7wJFQO196v+dwwyXcaRJuBHTqHyjhokz038p1x8NtsCt8A6rjVnAYrIRj4Vu6+ArriO9xia9U4tso8T0h8W2S+Mp08e2rI77nJb5yie8Fie9Fie8lia9CF1/MAc/xPSDxrZH41kp8xRLfOonvQai9lw94LvdBUu6DpdwDdXpUSbgwEz3OEz3OFz1iYH84HgbCC+BoeKEuvtCfPMcXLvFFSHyREt8=
*/