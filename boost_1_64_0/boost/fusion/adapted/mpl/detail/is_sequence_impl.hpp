/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_31122005_1505)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_31122005_1505

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<mpl_sequence_tag>
        {
            template<typename T>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
uyXj3Cp+7HvWlDdw0x3WlOe+7/10p3s5yX3hjB+5R16rWyNJ8dRd6fAy2YtnsUtKvIgflKW8gndIhjdw3x+bNx7hRMnxPF4kE3gJr5MCr+H9MoeHn7jmVuPnefy0LDXOGu7zU3MY94nnyQpewE/IKF7Fh2UqT/0sHU6VRTyPV0jEy3iblHkd97/bPPMIp0ie5/EKKfIyPm27Pcaj+9Jhz1/YGzyLz37QHuO5Hfr+tX3Fy/iD39hXPLMzHc6Qq+K9jW+Ta3kZb5EKr+OQh8wnT+HxUuY5XCwreAk/Kg1ewVulzuv4jN/aZ/HY8BTZGV8LL5VtvIyflxqv4l1S5Q088Hfui2fwHLmZl3CXRBPd4650uPFh68gzj6TDl0NLyPDCkJZQ270lbJvAm1r82+0tocFr+JDM4amntYSXSZ5nsUuu4kX8oJR5Be+QpbyB++7ZEoo8wlfv1RLqvIJ3yM28gfvu3RKqPMLznt4ShhtPBe+Tgnp4Rkt4hZR4Di+TCi/jD6TGG/jFoS1hJw/7tISjZBHPYr+s4EW8Rq7lVXxQbufhmS3hh5J13WjflvAFGcXr2Ei1hBTP7tcSvrJ/Swi8MKwl3PjslrAXj57TEsbItnjP4AWyk5fwOmnwGt4tE+Jx4n7P1T+P8BSZyvP4NsnxMt4iWV7HIcPNCU/h8ZLhObxADuUlvE4iXsMHJPBwQEt4qaR4FrtkL17EfZ9nPMafw9qB1pFnDmoJ26XCo4NbwkQp8TxeJEt5Cb8hK3gd93++decRHiN5nsV2yfECvk8KvIJ3yhzewANe4N55Bs+QRTyPl0qR1/AhGX2ye4/sPRnJs9glu+Lx4KdkB6/isLR74AX8oGzlFbxDNvFCiz5aW0LHyRzfIRvVy7jXIS2hWz2DTS9sCdN4FqvSxuu494tawkE8wlfJMJ7Dy2QcL+MPZHN8j3jYofqK+8HXSysv4U0yiddw9xe3hC3ap3CsDI37xEtkBC/haS9pCRfyImZf6vnkBdwgAzyMcK3D9X+KecDuI+wxHh1pHWW7Nnm8SLbyEl4nQ7Wp4f3SxMNR1kKWxf3jJ2QHr+LDMkyb1EjjlC3qObxEdvES3iQHxX3i3bJRvYH7vbwlrOMRniKbeR7fJpt4GW+R9byOv5E1PBzdEpplOc/gubKWF3ClrOIVrEvWdRt4zDH2/yRjw51SVs+MMvZj7W2ew/fKVbyCdanyBi47zjuBV3HI8d5RPIopNR5G6/MVnndeeqU+s87nFbxfdvIwxvtKGjyHF8gKXsJPS5FX8V4p8XCC51SW8ix2ySJexKslz6v4PZnK6zhkrOeXp/B4mcNzeIkUeAmvkxyvYeuJrmtOqnjiSa7FS3idzOE1vF/yPExoCZ0Tncur+JOTXZdnTmkJ58giXsB3SIGX8QHZi6cmtYTnneq+eB73Ps37lmdxt9PNc+z45Zw55ZkzWsLRk805L+KRbdaFl7HnTOvFK5g72/zzKt50jvnkuVe3hHmS4kW8WobzKt4lEW/gAed6T/IMniRZnsN5kuFF/LhM4FW8R0bxMM28nWcvnep+8dp298hrM+zJmdY9vhf8Ya8xqKf6W8IRsi2u4/mykxfxamnwGj4kk7SPBrxDZBzP4WIZwUv4KWnlVXxY2nhqfks4VUbyPF4h03gZb5PRvIFTFng/8AKetsie5jV8SC7kqcXepTLAs9guHbyAK6WbV/BNr/PM8ho+JKt46gLnynKexdfLGl7Cm2Qtb+A73uB9cpo2F1mHovcMz+OlsiseM35JdvAaPiDrebi4JbxYNvIsni1beB4vlk28hNfLdl7D38lWnnpjSzhWNvMcDn2TfeO6VTz8zfYwz+G33mKteWY=
*/