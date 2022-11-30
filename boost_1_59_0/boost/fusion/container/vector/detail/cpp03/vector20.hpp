/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR20_05052005_0205)
#define FUSION_VECTOR20_05052005_0205

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/vector20_fwd.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/container/vector/detail/at_impl.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/fusion/container/vector/detail/begin_impl.hpp>
#include <boost/fusion/container/vector/detail/end_impl.hpp>

#include <boost/mpl/void.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector/vector20.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector20.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector20.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct vector_tag;
    struct fusion_sequence_tag;
    struct random_access_traversal_tag;

#define FUSION_HASH #
// expand vector11 to vector20
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector_n.hpp>
#define BOOST_PP_ITERATION_LIMITS (11, 20)
#include BOOST_PP_ITERATE()
#undef FUSION_HASH
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif


/* vector20.hpp
16BIXLMqa/5nSB163Fgsn1pHzAr+jkGN5RtV/GFBJYn21rVsHFUNMuunzOvYT52NithL4n38vNl71NYO8kS3VMOzwWLTa3he6PIZu3j8vghMhuy6lJt9NHelp1Wm4/w4CHiNebpYw3PZZGlYcifWi2auNkoE95a/8/F3y5T5B3NSwhenPfXZd95lITBHasXEZgg+tieXSipQtcPlXK1fT7d2GRh0tRQg3/dAyWGXcvEI5BbXmBcudnNxwpbV1zPJ3TJ5/MWwr96Z2Ept/mUfMNV5NfqsWlhn+iVzbVBL9ElXONs0rhKP5BXpgjtHQ2OV/BUt/2vSb2ex8El7bpAJx9M4aUfzjMSW1Xse/Te++C4jpUdIejKeSXquMhaio6JXMVjih3JZTyZ0f1hTV/V0D3eVFXUupp882SZ3Lhasr+ZMp9BWx5YTVmfBMIq6POgG0eqGWTItpD53vMb1NLoJsutxwJ44OViMG2YzVRR1Th4Faw2E6RoXTnV0G8Kd6BJrOhs6YGQ8RYvxtg2ifbGeNiX4fLX4H2wwi7NNsZc7BS5kDxWh4EWGtU6qqKrJy3f2jO9LvGqTdJDisnx8o3PrjWe6jmes5hP/RdFPB0ZeKQC3Rs8IH0qMfCr6Rs+m+ld91xuY+zFnZ1oUW1vBE096kySkTnobqSvo4s7hGIC+zXDvvxiiXBzrEovwa2ofBp5KRYuj1Cpr1o+Br3MbCjTvah1UfoaoXX6sp5IzR3465P0N9g1sjJE56VLcUFaEZvF7Gl880iHhrSV2x/jglcOAVFjJ1v9IWzytrIJ1W+cx2lTROBVRvyFqV6CV2ae1FYZz02hyqQWNryYaH7YzUJDBmUBKjwbJmKyE0TiZ3JSf9jGYGyXu2E4Mycqg2UlmgeD8LbQLp3bojdRUB6PqIdL+Iag+BGmnj6G5symrdkoWQbFG07wsg8iTso750H3AOaqm2n/dKbi0gVEd7id9+cCECG+VJuZiSLnDoEP8LHon3wWpxHfZtOTePCe1G9kt/2uxLis3UYNNCiVn5qVj+vMo3zHpVtJD4/BnJoutTZL+rkALrTxU4p8P5DPAcVpmNMtJqtW94vobkZU4d++PlZ2Kx/q1Mt8KEUXblnaOGAQACYXctgSMwNHDVFpogtIhmWlVhx7hYaoR9XJk+u6ewFeQjBwNLKQCHh6TB2vyP3lY7mKfcB2G1EKXv8wkRxPcy4xXKn+4jXcyr9ajciYuJNtudodIY7Y8u6wy+pUaKOr6D6srhdtIA5NVxgHHlXRVw+N3SE/uqWuqdVQ0qQjQjhR7/LtCPi6PYbG6fOREZGA1U8Xw1SLqjZrFNlQvgz+OWXIsiNX7Br9qaQVstFndjaoZ3uGKEHszLG7OA0XhV6PZ3J2ysz4Hht3Hw7lhcfm3LiS7mxNKA9jov9txYUjZCOQwtNroGTYTeUev7Y5KuHAqb8SwILo9eYvZcmi0tZWi58uO/jCMOxSbst+IpWurqx8kdhdKa5/jslUZS2F9Lb9OJTa/59Akq4CJ1k/IYBmNkzFDybzx1rameBs7URWzJQ9Go2pZaoYT11aJXgoeOvGK6jFXFEFPWygJNKOpWZwjOMIUPA+ZvipEvspFn2KlgjE+RdnnmwcUkqcrx1JJsT2QZtdPKfDWVPFjqbSgGG4N58KCN+lhmWeqqRagwst7yrpW+bmj0cEqEyKnLOqYy/iNLLRRCZBkDqZlZtqKYuggtIx3QrJcNR4WCJuvIPHyWjLf0ykJX5wV9cB5jPftU/yZ5DY1As9hbBiBI2os/rtlPzf2cpKf65T/4zUy1gHXV4VgiKRfuzl0oJq+9gOWi2fQtUQSZyUkdcVj6oU63IoMgVPEBhid30rf2Gjs4uKSgpShSAgJCBIcB+TPnDAnQCgSX4AIXQChEFGQT6EIQvxNEZG3AFJEFGTiJ37b1ehJB3TxcbeT+rq/nbjbnsjE9TWVxWR6emUDcyQDjg3/7/eb7GcJ4AqEC9wFpn6AOtfvBzIHeHXRoSwkNZFPSB87UaCvDIMqRiIvoQx1Io+x5+E1EAZOfbvUaj0AsRpQaB8PbLhwgBdtR7K4e64KT8Qt8RB3lZIByUR4c7uOG/lyapMZB+AwgIqPu87LQ0qL+Ock3EpN2r0+B+GxPFCMsGDBUJERabv9AX8BFYAi1jQa6OWdgk7JDUsvGt4MwdJXBBQfABCCHwAIwQ8A5H+Xd77wl4xep6I3h4g76Sl8Uw+h7d+XHN/0m3iyT6GGnwYJfFen8ESfBlK+Ze+Dot91LXxVe/CBX/vAdjy/Z/EWgs8u/A707Lbnq98w4CRQB3xIJ97KJfhZz+AgT5jluc9P0Z+mVRl5aPlHMrtddBwgyAACAXFIfEkexQBP7LbdXH2H+VFkI4oeIrSjt2JFSYVQOBz5WFweeW1tbEkpKaFC0WhBZFJpfqVSWREmkyn+RpNpQQ4ODrP9gWByNjZ0Gr0e7GrNZqhqnU604+PjfJlM1vxqrdYOXGez0Rgcs9kcHrPdHu+zPn/gs7v9wbOhcGRyPj68bA5HsGwuVzhUFJQ8aHTavIEBQafzBRKn4wlUp+cLFaevd2enwxFYp8cTGafLFRqnjxdrp9MZHKfXGx2n2x2eIz4gp1wjUZLterGe2PUQwlddPEGZz25X8B3v3ZKPpNDNdUm/LZ7Nh1hHplQ+v+fP1+yBT24zAHJt3Y7P59gSEC8oedfZx8/PCmh1sLry3NDZf+Ct9Vw5fsmANHydEPoi/Mh1pPrufWh+tEKYhLudIBkf6lEXna6sgLlgzACVwBt+zp9WtRcn5ypNAxc5IlQo/nYQ+mR9gzx4uZb/N7k/kAHdu4Q5NBAvf1Vhc2XSnv8948/6RP5LddtF3/jBuO35JrnEe/53sE0ndnSEIuLZJ8593unHeIouoiAAf84jojPJiClS0HO3ieb8+BnX2bGDguAicL3ni74Crtd12kg7SZSbqud+u/pWuaNfGx0boLk0jRjOqMApKUxhBpCUEpYgz52UFYAkX2GJ5WlOv9b6x0qRzepyvQNRnwb8jad0UR6mCA+yOhyQcoeqE7nIMnjAgLqQW+/CP44QdUI2WBOJgBS46gKhNkd9NufmPPk179uOTqRqtYbZTK/gNPNakHjOxj1cXg0pCeEnrNUFbC5aHr6WribVxXA2h+5ZvH3e7zzuxsAdhPrYZI4OT5FuJnXUWqsklXe48tLgllMgd0Mwnad7a7ubW6IM9+gcZBXcrXw7XiKQwd6Tvs+b6U+RBsg1EX0E6SdrqCb9JwbCKx9OJYb8ZaGziAANAzncmRHE4rz+2D05fIF+jBMoJRKNvwNSt30E4NSnWA9CGdO+7zxhkGahw1xJzfc36fvoVX9b6Wer4etcIm6+qYIKORHQhHiwKuyz27ut48X9d9sjM85AqJfYzleq4g/55e2WqxYCGLebX4+nyDCBnuXYfgv3TKTlq5qv9o+PK4+w5+Hz7PLBDpEDek0sEcXvOwiKndlV7CcLFJEWFfVy+CmKJyBKSFRkvJrLP6fgJnLR93KQFn08Glp7WopaCpo6qS8f5yYl4rD6AwkrESMhIR02Oxb1wkNpEJpAj005mQwHiWh/b35PYV/jWSPGh5S4PqEX+wOk7SHvKPbq8PdkDGEVehYOJydNMHkOYRVxFu76Mw/UYN76D5zlIg0ls9FaoIfGH7jFuvw/BiFwHAtetPrl59ULhuCkJiOjJnAyoYSi9Dg1sNe5SX8+tD/Hypb6720Skf9q+G7sRhHcBw0vfucrNv3z9MR1yh/ufd036FrdDH0zFq68u4vR2Xi9Ov8h4wc/A8DJA3byg5sD5Py98S3UCdxt5q040HQD8UGnG92899FOUMaXozRg1ppetDETeop/Z/b2t587m+po9K/KfevRiF89mnbTsmxy3umwSEZhcAk63GG3m82wXvDHVfRdTohyU01JbXQY/ttZc8hl5TKbF3nAWxSSIEC0rG2d57O0NlXxEMmt4tSKPmYfc8u+0yx6sw93ZFoMhlNZo3RqFtosbRhcn6nCWvp47QW5xDW/Y5QbJ+8QRPfl4QXpK1YTL+BEi1NNq5R5+eX0dwgDXJ3jsUojc7e5SJ9RpuMbwIbLihtKjGoxqfnC+DkjJjrlhN4xoHknoq50I7ih/JD331VJpWiGBXAzPY/A7hRl2qn0yKVmbjjmS+WLdWfa5g51biA/OHfAZ57RAqITzHQB8rkRZ7TJomXFXEMTjWYRwzC7kbJpsTsZb2juIc4QSr1a0EbvOJSs7SlPa5aVHh/rgVYbCYYsb16oWRqnZPQy35zcRXPebfE074n0Iy5864iWFvXqfj9PLt/ZP210bV7Zgcp7fUUN89ItVbS5L6cKyWaQan6uylUGZqJ1cvoHDRklpsRpoEfqWkNz1QYV/ePIjBYTsk2hIzj3LQH2Ma5HWz/kO0ov5A2HhCwC0KK4K3nKMkTNlm/MzHE+1Mqtwe8UAd3dwXtibblwtZf5BQt464gWOTrrJ32lNXxHkNnWigines2k+NvJdUaxmdTcce126Zq4ymPOdDK28c6+Qfza2/1/aOa1W8X7FzTV3brpIvXaL+BaY7UD2pkmIhu3a6AuSu4zAl8BXR/02HKDnfeiDTlwakLNQpoZO0NrhtIG7lbIH/7WplLT0FuIdJsMDdR3i6u1q3cc3JlHcW9HTIxBJwuLTQ0eAplmS4ynjkpTzbedXxNQD16ECXfGCcJ0ld3PqO8OhsX1wTTMvmwfD+y8axY0I+EfhGs11NDG0Kb1j8WjQnqdK4dWD8jnRUkFSuSq8P3SckunWMlrf1TNekAe2bSpUVWurdy1RrjIycYyTT3vJRvkMaQmLdWaIt91iTaW3IEva55LsimUthtSQd15/8z/Q3lTWJd4XOrxUFNPnJ6i+XS0bB+rxwE/fpuw8M9MbJigfM/R1OuF/JSkr32oVqWO0q2gtvtoHezmAlgEG8lvYVQ5r85RQW72qibVGsJMe5xC9aKjC2rWGrYwaW4Z0Vysjq2yrWJaka+XYq4vvNp+Yeico6WynGzNcrfZjAF1v4VMk4mJYzam3RacXYyokOcqJ1puv6B8rvNQqS5qXoqxLG1ueQ99V/wze/vs9ZWlu0BuysxSxxDp3T9zb6Ka46yg3GjNNZJjMtvSuoF+jdTQbkUFPuZafANxCnya5TgrECyw0x1W0IapWh/uucdblzG6//yPnTeYj3RyjNUhuEqhhUIsORGqoL+JmEYKfs6cUKuLaAd9NPjWp/SDgSmZgVRdKmUoplHTRIxpEdvcho3ozaknJffA187AGoSWGXW+oDWNRrfJdCMz/1bt2tgheYvcNx782NxdYCdBQJajNAL5gNmpbDDbRda0NHVxVsKBMct+pnIGxjSlsW/cWZULK8t6hvY0LPH283zLbrRGEPGox535T2r/8r1SG69NCIaLHdcWxuvA1x1AFpC3J6jciO0B/D2ZG6JuyOp+9D+xLmS8EbJ7PPzXm/2/RdTl0jmksOKOBQkpRTzngh2JfxjjihIMjLjds40S041w37KoySrHSf/k6hyxJcBfvjO2i0RQHSdRStIU5yOVmEXIc5LrJJsdi5AoSCiFUNFRKSW1Jr0mt0+gT6ROYJLIrddcqcKRjyY/TqDGMYucITdRVstcLqApl7LCliI2gXuHjywS4MOOzqudw3BGnszJnas9Yb3jfPnf5IOf3z5Rd0vezhVYmDdnaIpVl7KqwKpUWBusPCl/VEBaME7lUD+zPMM+Az8bPjM5l3eofsV2qGwDUl0Eech+KXVXglkaN0luKGl6V6eLsohZljqvFDT5bADQiGBVdBfIrOws7SzyzqOZTzapbIhei1mXtuhxlX/l6yzYWAw/NXgYf0l0++9oqzlL2da6zndeej/5e1TwSuNV9taYXjI9c7yfvjt4N/cI7JbcLvguxp6Dvht/peCCOLZGKExCsAzwd0AVRs8vh7HqgmQnmsCw6bKSYthi3GI5RgePpI5gEs3+21mzxqaPwTKNohqxLoSgGq5o2KiitRxwMmm0e8G+7Nf9e0+PLFZnf6XCmj39l+NKqSXIe7AH2P0FmmvMx9RUg6BzMCKjeDrCBKcxZ31JWdq8hYUrPd5EjwnQyLMk3bjHpMegx9LHyseElkUt44ehNYNryvsEck7PN4NtSl83RA0IRxevif04q/Uw2x3ldhr8DoU3KXY/8S3zk+cbUW8o9V7lU+ubaHf89bGwDpP2PhNbw7h6YiVxhUnVUaqZOg5Bp+pGFY9qRbI5xL8pzcxYi6maYwXIsr15YwOgwyL1OdN5itNap8VGQ6CgqIzQIlx+Xt1MMIz1QENdiy6CnUEdBp0uUuIvZtVc+998deqVMO777n8a2H6onqLaKK0iiJ1JOv011qvNmWsgR8JtX1nb0z7jMa2JVzCe2GbH53kkDldy1yQvqy+uL/AvdC+6H64f1FXrly4KGpqqSSxGPOvKlAsg7QsSohPoRgHSKekOTV4yPYAOJqxmZcUOxdp0rQGiW2SxY44Pcu5CO6nGWZKyMuqH010sO1Arbihmt9+yEUxLGIfSdjsgMt/xTLsaJ1UOPc6sXFzZXzMKp0mO4+2QH4WEZX08WX0kdsafxD5gbEDrxvsrbUQ3cA9UaPADg3fq3Ihyw0z32F0ApwGsu36te7l3tv/+8EbT9c3ghyURH0vQIEliIkuDmAvlkMwmoktgY0gvjE8aIaWL7pA6jgs2pFXhux95PjC9JWODw/ogvoiKJClKghZ3KKqZFyAEU+xPOEqyFaOb3RCTCGEUd1VIq+0o8CrzqqSQ61FdJuEl6SV1TxgcVymWaavdUBSbi2gG8spkKgZnNJFcCxOdQzOHkC5Kc2bElNrOuZ5bccbSFlOde3SE3+R9nCFmyP0UsZ15a2pXF60oCy2FUKq0b0he54mWdy9/WxRwKuMUysqXlt2W45U/LtPxG3pV2qi2Vn4sF15QPHd5KIloQl5DXktcY1THrwg2Nq1oitEIXhYOWwQ2EWyoWxewqmTmT8+jmbVvqG2Ardl/FV3Px/j3tOfpLAc8JXi4d2fgVrCt1NucWT+ZPp8+53hk8arLhX5dE6/t98B+VAW//52TthRg+6r6qcBbmD1Df7Z81+lOUugvs+E2ZmYI64cZdZs5M3lifMeQEA1hmHAbTrPpMvQy8/pLzdDDuoKBFa0X1T1icFikYKbNdoMxrC6iGsgzjUkfnJ5nvtEo/gIU6d/tRIo1PdK4ut5pxZo5ymtKte6x1m5l+LGGmDILtQbrkovKNpnOMo3QmI9h4tCYvN5/ZfHC+pEZbpLBMZKlL8uwy8jHeJqpl6aXsZuRKeB6zRqbUTr1eIKKfI/0CambzDeIdY+mfVrtLobb73mnzhsGv0/0T5g3eXav8R9QzmTvwe4dzSdZTyjeUekb6Jrj9j5J9YMqS2XM8tpAioHEpcale2Xp8iqmVbEWUTX1WmK3tbe+txVNi6q6ZfWPOp9Wr2ZoFfKKyCXm2ZS+goAyulz4ewAEKfa8rBNytzAfA79RmMIBKgOG033oAXK9uBfNSnj0gdgaIh4a2TDeQUcbWcS68TXmy6ILcGe79QbN9YsL+gfoGjpMk9L1/IvbhzMXlgvE49Xs9fGLRx1oy3rnFZEL75U9
*/