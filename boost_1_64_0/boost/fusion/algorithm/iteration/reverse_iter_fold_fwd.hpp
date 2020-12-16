/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_ITER_FOLD_FWD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_ITER_FOLD_FWD_HPP

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct reverse_iter_fold;
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq
      , State const
      , F
    >::type
    reverse_iter_fold(Seq& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_iter_fold(Seq const& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq
      , State
      , F
    >::type
    reverse_iter_fold(Seq& seq, State& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_iter_fold<
        Seq const
      , State
      , F
    >::type
    reverse_iter_fold(Seq const& seq, State& state, F f);
}}

#endif

/* reverse_iter_fold_fwd.hpp
8/1pyniBTRz7NrvcG0Wr76ft342sZT2v5vg7vhulXldTD4TKuP/BfKE+tsWnOf5BzTXHn/H/MxI9m6NRVXdLnG1/x+uW3WjiHkJc5inPZZZ9S13syKM4k+ZeluOqLt/xzvd/fSSNWySNQXJOtiZU68Q9xE2aNNL4PTkhLpMJ6eIykzx5vrHF0cdf2tPL/gfKvlPq8B+Jb2NCGuEZ5ZmzhH2nJ1pf8cWQ3aWJw+/8QRyS4uQ+O1TyXNrcsx3nua/iUlLS7rFVQnGpE9RzZMyta93BInlWzsY1xDs3wBJv64UsLTWTfWXY4pjlpj5IkvpAnoPlPDfzejKVKMm5LsuVdPBeU/oxaM8fSZ+cz2Z7vRDtvIx8UJe1CeryI3N7OZ61J9ifUQKdlrFt1fxzCfWsCRsnc6hEY76SNzc78iYxyxyXmuD59YtrkOa+Tt4hOfpiaK9L9jR7W5ZPTE5JsT63LSAPY4nnI8o5c4ucT5IXBMv1LmOK87kix10u8J9XtpbXQ/icch8TKGlzPUkoQZnKXHsp1rQWlJRW+qg0CLJsJyAhzTFPY6Hz+SPLtuuU592q8mw8d2CErCdlSJ4n1deGEKc6ROpi6YuSZcm/JKXfVX3qQpbXbePIv7mOumaC1DX29c+x/ifKim0d60ep1pfj5VhmttVpmY7rkGqbAaTjZaVN962Obea4fJ/1LXMJ9m1lXacGdZvy97bW6r8Xt1H//WJb9d9b2qn//pl9yt+qa4Z/Q+0YM+uVa0awfYwZ9TvcUjzbrr2KMWa268RrI9vL0cZL3iF6Hq8NVxGvqBu08drE9oq08ZJ3Qp6/vy28inid0onXVrbn30EbL0usPLgW2eK1uQzxsl17VjSybrCB1K+1cRvbM1vjxcmfHsc8RFTVStXseR2rfUbQPg9E6TwPRLt59mvcWDu20UvK8Q2xjW1U9vNhd12jsY3UccjTicNO4uDX0RaHspf9bXU8i0PAjdo4vEwcouxxKHs5z/EwHwp04vAqcci1x6HsZfqIYRzU5TenKf9RVObFFg/wXdPlZtY4pMc4/37owTzL1UH5kAanv4/+wfbkulqV/+86V+u5K/Zl9nnMP3csC7LP38oy1zldNzqWhdqWLWeZ6zyv9zmWdbItS5BlMver9MPUnwsuC70rqa/pOS7zpNdTz5edmuB0vxiFr3VVPxcHuTxbrKdMZHNMaPZvGm49BnIMte/JI/SeleW4ZvnLvTwb8Mc0fFM5zylbclw17/ZL8w7DNc0Rcr+nl+Y32K88I+u8F9N/PzCrKX+z8EYi26ATcXZ6B/aAo27UzBke20zmDJQ5OLbgW+y/sLM93XHWVHv2HBArzwHaYy33WDrvbnLV97jyPK++R1bf16U6/f5gWD5U522RpLMboSahE2G/cl/TzZJOa+XPu/q0qZ69D5P7bUdaXPujN7eu/AMbb4Tf4tvsL8e6v6n0uHattD2ad29cD76vmq9b++4lSSePza7vUSX+73SVPtEGvyUFOb/HUL134TsyB7ZzunffZI3wUplrcBG+yz7O9nCkWwpUlOXltEfvHCrWTO/lSLc8L8n9EZuaxqyFLu/8JD8M34fXU6U1PjlT0qJ+pxM/PTNR+Qejd+WOdHdvIXMsynUhH99X0t1Lk265NHk2B//8vup0mw3SnaVzv5Ojc78zV/ucqU2bXh3D3921vzVb6p49HPNLZOZkZS7d3o73U6Euz2FB9ufTeCXv7N8NJe+ylWfCPvJdnWe49urvqvL+kuR9MznXGmORcl8Q7sh7a4xj0tKtr5/dlrmr/Y3C5bcHzbnkuPZIR2s+6yoQd/FD4m+6zRL/dGubp6S0aSkJMfEkxfPzxnov0SY=
*/