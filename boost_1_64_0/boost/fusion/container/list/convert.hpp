/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09232005_1215)
#define FUSION_CONVERT_09232005_1215

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>
#include <boost/fusion/container/list/detail/build_cons.hpp>
#include <boost/fusion/container/list/detail/convert_impl.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_list
        {
            typedef typename
                detail::build_cons<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type
                >
            build_cons;

            typedef typename build_cons::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Sequence& seq)
            {
                return build_cons::call(fusion::begin(seq), fusion::end(seq));
            }
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_list<Sequence>::type
    as_list(Sequence& seq)
    {
        return result_of::as_list<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_list<Sequence const>::type
    as_list(Sequence const& seq)
    {
        return result_of::as_list<Sequence const>::call(seq);
    }
}}

#endif

/* convert.hpp
yFA/hTllDu1vah7fcqZJvRrH2aiRsfavoQ4HYBkuZRlNu/R5VLcFOaw781nrNZ+e714ssSsH4f7y7sXFav7K8hwO9QdL2yYPaL+vPN3Fn13rqbET9UUet/F57+3u9WT3WE+UyVCuM1KuEEIPeZZDqfujdxnK5fyxz1LStfjUJ2+GPHeR2kXGI5blD3D1+VOX7/WHixL7ls4sSeewpDNE0gmSclj3SDot/kD6lparTNau5mVKk7S8/HC2uUzbu5qXqbrldNpUpomS1llJa4ykFSFlapS0jD9qvi17mmsb6GZejvOmy3bm3te6cuafqTuBab+ksVfyb90raehPFn14vkfZp9LI9zlCEp/L1eXI+E4mx75ws2OfHPdu3qsd94zPyXX3Ui+SZ5MT3DbVyRFZ/mhZfrirTu6W5RtPmHxatmudWnuY5z3bfNnO3Pu4Tl1p1PQw38/qJA2zH3dftxvXvnzOSzmOtpBGW/YvV1nSeno5Dko6Xk6mfEpjlmt99/RyDNzXYhoXtG6svbwcAyUtLyevPqWhHf96eTn+tZzGBZXnvJfyNEpaXk5MfUrDVZ7MAPPyNLWcxgWV52iAeXkC6iUt04sB39JwlSe6t3l5EltMo23H9xmubVvS2kjoLWMPLOd4avdMaw2n33K2QuXltOW5XucxPaeQ72nnuMvU8zB1SYayJ/SR9/5K2aNd9XuP5Mf7hb7PYyJaTc7d5kr6B/uY132aD+lfyPEroK8aT4xz6ijlrZb0TC78tXJafFzHFX3Ny1TnNY22lcX1u3tK0gmTdEKkLEclneY3B3xbvqsciYFefte9Lr9t+8Qs1zYQaL5OrPuVdFq9UeXTupnvOt73My9TjG9ptfEY5rw2aZQ018o1cx6hZhDnGJ5palcnOaVteXbbcN3VfH8n1rgPRPd3LmSp5GcRIZP5z3vNT4ndl3Uq185maWvbVIOkHSJpBxMGBVAX93pPO+uq0hy7D+lr/Vsu1dI3nEd2GOCc2bWx9HKdh0nahpsgPu7zrn3RNsB8u2o0W3YbzoE/xbPKc53qM+s1D9z12nsvxMRsfuHKioKb7j/n7Zny795YAebP7nt/Ft/82Xfvz6Y/qC7HMWjrZ5sX3rn8+sildwfEdTnj7dn3tvdJMH9W3ntfhSS1nhO+CB+V/nnVDQdnLw8612nbtd6f9b9/hBK//+E7n33lxfVfXtPncGBU5y94kPQf6npsfHdZyB3ZD3W9vtuJS/p//sDjbe/z0NY+A+bP7nvr2+C9b8Bs9Vn/qt0rY9c9VfbG1Xc9f2fU6eX9Wh6joNYi9xPxgIwl3BOrZOfIa8ezuFiCwViKI7ESp+FGnImbcA7+APNwFxbhrbgeb8dNuBt34B14J96F+3APOvsMyD08ubd32KPPQDXPzPfAGuyP1+NgrMVQ3IoReCOOxzqcgTtxPv4Al+AuXIG34hq8DcvxdtyOu1HNJ96Bd+F9eC/+GBvwUTyIR/BhfBYP4Yv4OP4aj+BbeBqbsAnfwz/i+3gGP8L38FP8E/4d/4xf4VlsT9nfxx74AX6slkvuI8r9RaWexjrrRZ0+Yb4B+Dla8Qupl39LvXyFS9FCva+E9ngHdsB67ITvYhd8H7vjaJbdA+MwAK/C3rgJA/FZ7IfHMQi7kaeB2AeDcTEOwUy04j0Ygg04Ap/CkfhLDMN/4igco4xBgJMxAqdjJKbgGLwJx+IuHI9vYBw24VQcyfFqGkbjdFyPM7ACZ+FTOBuP4TzsQn2mYg9MRysuxZG4AtfiSizGHCzDVbL9smvKfVDKJvtTewx1jbsq228OBmOurM94wnn5XrB8rwNGy/dul3dv3YN98F4cgAdQ3W8sct8Sh8g=
*/