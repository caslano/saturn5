
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

{
    typedef typename F::template apply<
        
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap0<int>
{
    typedef int type;
};

template<
      typename F, typename T1

    >
struct apply_wrap1

{
    typedef typename F::template apply<
         T1
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap1< int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

{
    typedef typename F::template apply<
         T1, T2
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap2< int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

{
    typedef typename F::template apply<
         T1, T2, T3
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap3< int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

{
    typedef typename F::template apply<
         T1, T2, T3, T4
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap4< int,int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

{
    typedef typename F::template apply<
         T1, T2, T3, T4, T5
        >::type type;

};

/// workaround for ETI bug
template<>
struct apply_wrap5< int,int,int,int,int,int >
{
    typedef int type;
};

}}


/* apply_wrap.hpp
hP0A5ZidBM0IdyNmcy11+N6rKB28Wuhaf/kAHy/f9V0GfkYlgOPv0GH6syVdoLfHYPYhI/nOeWN6ucQhLNH2JQN0yJ1llqFD7N6O8yyQuakjnbbsAZSrgJr2nFpmn13iPzAMqr1elMFebOoIOFG40DjgJLl4V//wM32i8bYKbv8F6N2+l9B0gSByz2gmZf4B/fpSDtHf7hCuaWJqOmtiNoHjV6TsU2f2FbD3jEGPp3jZjf3k6S8VC20X/O93ja4uKE/FpSYe7oQ0QmBoSVeQ2BDhvwhRcIylkuCMeAmCdv2S/MRyorfqGguJzYvZfapirpJAmdbgZf7zOnJ1RV2NRUnKipYIAXmEf4JyNSH8MTY2v5mJu4Yp0PwLM3feq72O48DXf34e3r4s0yYzG2a4P+qW1y+6ms/2qG1SLsYkMTsEOrTZS0I0nH7IAifhRNU0nUR8zedW3hXQiH1ch+gfUGq6MXaedrYnMBLQq7Fjfy6Uhpl03aA3YEffVT50NwDfRiu69Hb7VFCg4Ye1EP+w//2jKOgudaICwEcCDIjx84dT5yH2IQXAvxDPBaDP6PYWAD6RNXDdw2EFcy+l8rZSo/sDsdUf/FUXeofos2rwJi4TsammaESj11V5A6JP7qz3B4T3sDQsKFB/dz+VqOtal/JThQSoFaIjS1C2bv6lG1HnzKaS5ykKJPyoE1GA7naocfl+XMWdYO1WxZ2m9impRrD+5+TCo27lPZ1iBKpyFCmhqiXq8qVW1CYtkpOhR7W94JPqHsy5zz/WYjsw3mDQ5UL5qw7HqdAJgRnBX81C/czy4v79z8h03rhQgPze8ozed7Uv0jRuuPBJ7UGuj0diFu3eeuEKeO8yvQA66fwOwODEjEwvMjQsJKyyHO3UICW4P/2RGfs+s7/BOQrJ8KXSSGrs2G2jTcRdbwei5SP1GY14fYPtgJoMzKCYyeP0SU/FYcX+kKMPmsg5e9jfZwQGrHoy41VgY9bRSdsp6i7DFumSQp+clg7n0OsNonQQxTCY7YLHhR6NTqpSPx+d5401qXGMfM058I1EJsIhsG27DM2PA0LuFgsA7pR1yrc6ffsdyb+jmFuPzcqS1io+G6IVmp8HhMQpmA5KMaU1SR01Py5GmGYxDS3lU1jMq6ysqwrVP071Gu7G4WlPvsSF+w0tYxza4qSoA1QQx8tUnh10tbl/OZXJzaOHDkaax0x8VszhdRQcKOUT9FLt7PdtK8vX7FS0sD8k8KQKWcv1k3nsSkGsPWRMCO1b8yQ31tRLWvFgfb4xz6nZ945C9aq6lqB1oUNdGjTy39C0aADtAQGAfgH/AvkF+gvsF/ivP78gfkH+gvoF/QvmF+wvuF/wvxB+If5C+oX8C+UX6i+0X+i//v7C+IX5C+sX9i+cX7i/8H7h//r3i+AX4S+iX8S/SH6R/iL7Rf6L4hflL6pf1L9oftH+ovtF/4vhF+Mvpl/Mv1h+sf5i+8X+i+MX5y+uX9y/eH7x/uL7xf9L4JfgL6Ffwr9Efon+Evsl/kvil+QvqV/Sv2R+yf6S+yX/S+GX4i+lX8q/VH6p/lL7pf5L45fmL61f2r90fun+0vul/8vgl+Evo1/Gv0x+mf4y+2X+y+KX5S+rX9a/bH7Z/rL7Zf/L4ZfjL6dfzr9cfrn+cvvl/svjl+cvr1/ev3x++f26oglnJ+Bzu32ZnIwDkOfAuuZkjudNXntio3kRxLhihO3kVhcl8JeICHLdEY1KKCwgzhF0wV4bzfw2f9E+k02tgWYUiF0QbNO5p+kSnpflJIo+UkkYvNzScHBzZjiGWHoE3doRI3hyudcNMi54mefttFnSlCLI6isg9tbo1Ej36ixVjVY5aPIyfGXoz9HtgsXIti9xpiLMiN+CdEX8ix7ok3LP6SeHbO2IzdKPARzVjGjhNUW44IzfGG24bjpGHW88QOU+RZf2gmNQQmoWYhUdWOOreUt4W061OjPEc7z2o7wHoehx2kocSJX1HIHe/Wz+qKkXv9ohZa3KAl/P/vHmEwXjpdQJ8Yn/kUuS+B2YGBhK2xLmIFriV9GtBcnjAsTjMn8F4t18vqdQ3W6+oN4myDYq8feL/NMylkouKIeF1ruZ7NNSZtdkI2XfJIMTWapfxtrznWv6cY768yNUPDucnC+34duwRrinhTyFDK/+8zFlzCxEWY3tBdH4vnQpEtPtmgUChMpGSljW1GgXoBx6PzC3BKhoyHg1hPPDIii3xB7jXGZZGnGKgqcYR4Uz2d3lsHdI7UQ6kqf2/uBoIgXzvXZz1LujxW4NvLejRuhqhqzTY2awQ7i/Y4lP7bODdTvKWnwgIA6KbAJLyiH7Zg/342rOk0BdUrKNYD6r3lLyEMriKjQTzI7OPQZwkDtok34h+80AsgA8T+IqszRBh2i7XR2mEm/ek06lgxLdyVtXjjtdJIL//mvHHgCha8OSJ0Pb8APaq5HSAsQefsJpUjAaNQgLBpIt9xz/tZSNqMZrZbdRoeGKtTfQRod3+w5kV/WZP5rZqPrQUjnBB3UguBmEuXGM5OQZMliNCqw/eJvaJW5k09FeBCdDH6LjX4yWDQRcOCfzEmLzESNj+eEo8KFGj4fwF6AV1hSHe4vQZVWIF+UKPpgbEFJj4zvw3nQmWKeQ9ztBy9DjD9JFLk9eMkEQSraF8kFW8VKlPB1XKFPMuDg2DqFP16IRwhb2wJH4OxDaSNtMPcm66fs76pSoThWkqslpRUcbpCMNyMjEqpEdIVofFnn6nTDMU+CAwr8m2ETGaif1Roj7MtxZhCFQ1oorY8Bpx2x70HgSpudyE+y0NmA87UjzXffWEaUfevtOG2qVNkhviMFRIb3JJ+NnIGqHSF1xE8W3U1ihDV/teSoZbQHWJSuXJZ5oZk+tTxCia7vbPmQaHJ3ITs6yxybFfHZ73u9nEesGDkOdG/qPzJQg9r2twEdNmczoMAYhP9GDRn0CB6gYgQ+MrG6FSRdotArYNNCcgYJJi75K3lzygcqc9lJ/E5t21pWcJXPZUrWGCvvJf3APFtMlaqOaW1I5DUdCBHgiuqZapeHuyh0szEaES/x+x/HUa2x/F6S8HMv3qlsaeSwRgspZLYVnK9fV5wNKDyi8D68ZABxC93AWq4/iDKBu/oC4rgnxKXdCETzg4yzXLLe3HYc5p3Fm+NdPihg+qYNhh5A2TmyxayPUgCOdNf+bkhJvFTC0j2mY8gOd9JsjaN92Ubx4+bzSk6h+g9vpMfruMvxykLsmLB0z4wVEmzGH97qShl2SqjRZwcA5MoQ1EMpycnoD0UL1o0RWqRKkhnLIscfgLPMdvn1ZQnTLaArxIMro4VDWwH46iJAouFyrxvvHqcAVgNxAHgtSsTFZQZFeVJEowf1IVqP9AXUkeB6apFTClLgTroOV+30bWPheUqqVYOBqXO1l2qFWZHAkRDF1PEe3Tlj3A4bVv94a2miW9jp6Wpof4dwuk0FgtRckChW2GoAhZpsdA4R6+gefjUnLfepvF9jYU8G39L9ytePEPcBDCxrIXXPPfYIlJTrkGDTQQkz5btygKp3KAgo+5yC4za4tRAqbHueK9NwFet5v7vW5HIrLFevwSUHw5FtXgoV7E3Yvs5b67wc9CaX2ODXhry8slyeNO/Vnl+OVOYeBM6+HM28Fcp5ow58yiykbsei5c6/MTnpkNhuYnRP3KgrCl5hLOnS4VtMc5iSox/RFkQ7yaPzk8rukUkKDf+H51pBt54pkt334bK82aPj8P0kUjGxglSRczBDZKH4ooEYU3NPjbiZDb5QrwS3/4BK9BF/7mcLFCzXr163G2MS8ik9VZDVsCpj7FZKXMlB3bspsTYmyIUtQY6NvngsGtd/eXE7zI6h5mpKpwco+ck2JSakaVabFieShyRWm/dSOTB7vrWfr/yk9rSlQNzn2F4nqqSVD1EEdXvA4aFDL7WhOhZ7sHrBLCPJbnsO3ITAlPkh+U0bQWiFXmVkfuVjeMQnJ8XJqySYv0aWjBVfIq/zzUK8MQ4AtlRZ2LV+ih0ZrYCoebHmIc2TAFVubV920wRcmYCZOVTITU6LLOcZCG3oWH2ogOtgwSe2/AA3aoJpnAjOiF4zA2qq6BNchjfnez0wYFV/g6zE10HTyKaLZdtFyunFAniHr+lTkjIDjQ239Mt9Vys5ovleXmycuhaFzIbpq7nIf+9tPmc85RFfvA1Ki+S6uft1Pth2wuL1CLC6N4IZoC8KR0IU29+1aiBSTehVTw2vWf9Hm80N2nrZA31y2fZdsnW95jqKFd/kT/SxR4s4j8nP1KYrpRM3Kna1K+C9ka+0jAP0Iwb3JM3GdJjTv2aaFUBef3oGcPCqX0ukVPOUQ6/rAivzY6n6i3uZlo/jsnlqTUpO0eKDtOZVbFZk7d0fg8RP/C4fdm/zJI7MxYW728d+dJTYwI+BDfviwkFincM37VS8J1yaVj0Dkew0lagiRJkZZlsEcsTBUyYS1UzWMHMpmmzGHdfAPMf2E7wcdayPyUPRabBYs63Bm4fsp1t95dAspKbSHPgfLJLdY78BWPQKHYPIXL8XDqVyejIihQSnHIoKsgwRPLserkH785FzuNFbKHVi4ggEnQ9YEHGL1V1406WqXmSbB9Up3bTCmVxQWdBGY+zldcqY/j+a1yZiRJWAPs3gVUKXINvBlZ3WBK+G2L/4LA7m5ah39VmcN3mInNmT+LdiCZ/6iwkzkgyV6EbanD6j/SPoLoJzU04DAx2HAMzlzySNw7Of9CQtsR0ct+/YUwpUKhywKLFCMz+KFZkgUUIVk/jVFUO154uWP4nZMla+1GJm1TIB/h1jsba0mtqROeBh5RvAaawerckMaWv/lEzLLnD5zkyhNGzK0RVKU4AObIqG6V00GfashxzjC6KOd14UoETKvoFon0dXmLoxwgomBKR+PM6jGENC0StKCPaDxOt0Zn6YaQ7jFu9MDX7bK1jJZyv6GZLS5Fwesn77B5/bO1jIuXamubT3HBTlgn8F5eiLGCSd9yMu0qeeU2R2p0gp3lA6vZ0L73payrBbM8nBj3Sf+21j9R9p82IPXWsdj8Zr3vMI4n5g5hzOcsHkuHkZIiUykIwxKmv1PuiembJgwt9cROpARj1TqdkIE+aXcT17unXajoQLCvFvegUB+IegZBfcE7M30NsVn1X7EZTrYxvdli5XII20Dum5TB8ewXyFIREUxRtoGrTdPqpXcAlF/VnbYlCBvv1r4/rczstxmYYdUWeuEecmk1+PVpQbsFCpblv0zFceXVX4P2aPKvA7F11ZOfuVvczfEnMYYnvJgES2CTTr7en+2nICGcq8rZaOpI1BwTD8AMTo3EQw2vFaFDIczteaeSIXmeHj4sN+2rUDp1Mez5LQy3aWZHCNjVB0DoZQ3qtqLIbtpuDAocEZ/a0vZjE2xsSH5aGJidOGamb3jiBqIzz7g2C1hgwqq8rnYi6DcqbkAAyz80whcFjP/AcdToPKasQa7E23Qs8/4a94bxQvi5npPuz64s9TK1ys6yiv2z+2lgBBtPGexlkzwRexGpPqdb5ROdQHV2TVD00nVBl6DnSr+TRA0cim8ZaTykqLVvMQzN9jEON7DBklvaQw2g1RA/u8bZZy64jYoQuEOIBssmq3937QrQYEjrh1amYC13y2pczVJX7n/0+d5jYz7Er8R2QsLdMOkxjVAmMK6dauqocjYbcUsC2g/43KU7zt5k2zuabhnNuXmAxGXkDjaM7JOT3RcWqkwyAhFNBGNqWszqY+rxJC5mKEFqBy+dlk1A8PX7iYwqPPc0RimEOKIlciShetSLsKDwlZ+OZO1StL2j2RoVBNS6A1BekmCByD32W+GzozpROsRdSS8J5Z4r26XwbvsgaDFF2N/Tz8EUql8h247Z7bLohg8CwurosvmypEhtggd5WlqTC9qjjfM+iwUknM4Re5MfTeND33i5EB4Lkf+d2p/KLjuS7JHkbSlabQQMoas6foMTd0Y+GjCcXBTwqKT9nkcPbG/QpIKzieiXijsLyLKDT+YUJmKN5ut25jav/AvraNshT3vG54O82TpEWlsFYqrjPTw9wzk5dakMCVLlJOUtKVCMhLhEANhkAwOMoOy2KDAHVClZcEwwPxDsrczdylRSTNLHvLDiqSrzbJZoi5muT50I/3MxECBC06oCLzTCF/rRanquIUIg5LD00JMDZXK+A5ceVG5wchyMDaFQ3hgBdk/pz5n0zJwgAbyWmHYR4bmK8sT4XHaJz1JPe378sO372qh4p9qogEJ9BG87ANlLwuiBuPZoyaDY1jUEenKAN/ulXyvSnAZ9DQ6xA6VA4ayShUTpNlToQk4O+0tzo0z9zl4/Llm1uSESOCfFu/w4L1bRelYhbCf+WuPjwWSEEK0Vz03PR+kzXVWdsttCjWSrCay5VQ2uNdH4T5RVVyeut4pHea1zFdnV7tXlcdItqvmgELKF8Q5UA/Dwe1X6h0jYdY3AXgSl4px8gVGRi2FNA71zyBBKFjmIsQNGsZk3Xuol4irXx3Kd74C+JM6t1u0cgJ9vi5m5r2/WN16ULXp0Vfwp08yHzt19zwZf6z1kns9ZpVCCu+yP0RnXTFmXfRRGmAc7RdFXNOaS43mJzzyu6n84OtebsrK+4rkfqSPYTw50uhcj+yMPRye7qXc34wrZe3osNatfXwF16nt2FyGLDQyUXyXIYv3mrpx9nYEsRZyA6/pmkE0wDSBGFydn4JX58JASKz+HKWvNw5bK6lPoJPMSseLxC5Q/k3TuOEjX0jWbTSkyGLctRNM/4OMx1w0L/cQKQQjNsEnC7OlilWZeH1ioELyTym2fb2LcpvZC257JS7eATXjSwkJ4UNmR/8x6ud8CI7iSMgQTobg88lQ257Qfvjh7+fgQl2aSDm28hRC7E/dptVZK9M8bR/nm6s1XuOWo7kiv85Amw573MfRUF0Jc30vTux0kaymfIr4E55D9vVEFOnr+w2IJ2hEDyEv90goqjFjUZsZFd+GBbZ7lUL29pdf3sqjIgzxWCgpVsNytXmStmZNVs1K8lkT1NM6+ON6yOP6uOkQv3kbLCpvl3OddodgzVL6fXmbpfsVvRecA0iCiT3VNHIjiAPlzzPpi4nCZ3i3yL0JiY/z3cnf6WwehJIA/aBHLq5PCMtZt64n9RZtDqGaLu2aLPNOTK0o6VD9cw+M1j3ub8vjGYHPtf6ckdcEuFeuye0rs4OZZ0G3Ne+lnoQjBPWdtSKdLB9eKgqnUHVkSnNjoZtm3vXPOTgaIivixXe6YOq85ZNU/Sb3HrVyZwGqjstnbdki9rKbIYktu3DFVHyS7ju/uRSsJ306W+fjzCdO9ubndFjMqJpvyyfsbZGRZVfBb9K9zb5VBEwJnC3VZ70khKwUOaM4uO8z4IOhJvG35CnhltvcTGBs2LSfUMx1evb7A/fs291A+upxfpAzn27e9KzhVXdq6i+0B6RSRv6cundde0O4+lD7IkM72WvYgBhFivqfdGhpmVuMEXDjwrZznwlUQIaeOy218UBkIVv6+UEsAtII68GafFNkv7lBROJpEVen8ghNuM3NwJfytXzVHAkulelSN+7tUc6Gc4RobaOisWs83RMEk9A8jThiTi2QYvAzRm8S
*/