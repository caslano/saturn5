/*=============================================================================
    Copyright (c) 2010      Bryce Lelbach

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <boost/config.hpp>

#if defined(BOOST_NO_FENV_H)
  #error This platform does not have a floating point environment
#endif

#if !defined(BOOST_DETAIL_FENV_HPP)
#define BOOST_DETAIL_FENV_HPP

/* If we're using clang + glibc, we have to get hacky.
 * See http://llvm.org/bugs/show_bug.cgi?id=6907 */
#if defined(__clang__)       &&  (__clang_major__ < 3) &&    \
    defined(__GNU_LIBRARY__) && /* up to version 5 */ \
    defined(__GLIBC__) &&         /* version 6 + */ \
    !defined(_FENV_H)
  #define _FENV_H

  #include <features.h>
  #include <bits/fenv.h>

  extern "C" {
    extern int fegetexceptflag (fexcept_t*, int) __THROW;
    extern int fesetexceptflag (__const fexcept_t*, int) __THROW;
    extern int feclearexcept (int) __THROW;
    extern int feraiseexcept (int) __THROW;
    extern int fetestexcept (int) __THROW;
    extern int fegetround (void) __THROW;
    extern int fesetround (int) __THROW;
    extern int fegetenv (fenv_t*) __THROW;
    extern int fesetenv (__const fenv_t*) __THROW;
    extern int feupdateenv (__const fenv_t*) __THROW;
    extern int feholdexcept (fenv_t*) __THROW;

    #ifdef __USE_GNU
      extern int feenableexcept (int) __THROW;
      extern int fedisableexcept (int) __THROW;
      extern int fegetexcept (void) __THROW;
    #endif
  }

  namespace std { namespace tr1 {
    using ::fenv_t;
    using ::fexcept_t;
    using ::fegetexceptflag;
    using ::fesetexceptflag;
    using ::feclearexcept;
    using ::feraiseexcept;
    using ::fetestexcept;
    using ::fegetround;
    using ::fesetround;
    using ::fegetenv;
    using ::fesetenv;
    using ::feupdateenv;
    using ::feholdexcept;
  } }

#elif defined(__MINGW32__) && defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__) >= 408

  // MinGW (32-bit) has a bug in mingw32/bits/c++config.h, it does not define _GLIBCXX_HAVE_FENV_H,
  // which prevents the C fenv.h header contents to be included in the C++ wrapper header fenv.h. This is at least
  // the case with gcc 4.8.1 packages tested so far, up to 4.8.1-4. Note that there is no issue with
  // MinGW-w64.
  // To work around the bug we avoid including the C++ wrapper header and include the C header directly
  // and import all relevant symbols into std:: ourselves.

  #include <../include/fenv.h>

  namespace std {
    using ::fenv_t;
    using ::fexcept_t;
    using ::fegetexceptflag;
    using ::fesetexceptflag;
    using ::feclearexcept;
    using ::feraiseexcept;
    using ::fetestexcept;
    using ::fegetround;
    using ::fesetround;
    using ::fegetenv;
    using ::fesetenv;
    using ::feupdateenv;
    using ::feholdexcept;
  }

#else /* if we're not using GNU's C stdlib, fenv.h should work with clang */

  #if defined(__SUNPRO_CC) /* lol suncc */
    #include <stdio.h>
  #endif

  #include <fenv.h>

#endif

#endif /* BOOST_DETAIL_FENV_HPP */

/* fenv.hpp
sHsSBUCqSJ2FH54zT7ReCJXFV5FvgDh5JcRov7VSOojJiUWMsWEUm72Zulp3mq5vsQYOZ9dBwKowgZ6GR5r/czhK9K3nGl4wVeHfJGisMzIHYRJx8FbaL0ulHh6fajL/8zJPO1giu6VIWZX4SYyTwZ2qGw8bACuJxQxFfQjZgjyNPMih9KFFwP6og3Ab7Mh1AxsBTy6RxMAUW+tIWPX1ffRit4sxVH1kZCuziEFmuaHLxL+0IFnu/bpdSTdnEWCyXEw9uq1uofTxlngQsvAvb7eywVZ0PcRUyrfAvuozrXUrVpSJ0pukPlZlnAZEvOjVAQxyCZ6ggpfFrd3ZWGUI8/c5rZCTfWpJlpXBXGRmHz37VHRcvruedOYCQYr2Xe4gaclCf2oOIjW99fw2QeDj9tZVb7wtrSxJ4Thdu+hKpMnAzVn2hV2BJ7gQFAcG77EJ/vGuc5jLTjCWnvSl/0qH9SZZIrpY+sCiGZwVFAKMf0jxLfbCd6b/dYXeQJyUG2ww7Gs8On6PzWre4fAJwZSsUJ7k0K5+ylD+J0yDFbuzaSkXhoyjn/cKHErdvgX0yfgUnNog2iHGMGT/vDlna+UrYT8ZM8lIpyCdZu0ZCZh9IFnccO3uMGvQpAEyzoYb8BbOD5j3A+aUgLtCLCYNlRspuY6SDdl9sx39xhyf6RUXKx+NRs3wpulWu1updUP77cC9Ri3zjmQjGKwcs87ua2yERS2tDrX0zS8UYvVQm2VphmrdkDFe6Axy3+n8cA8RzXklIJrW/dQiZlBWqRtKzwWOCqFGOGN1zg+ZzWAsK+D1IC0Zto7Qui4K+/wqRruWnGuPwDv5TQDc9JKLNlbGx2Sn5Sk7Aofn4Q4WAZ3DClS2pgFK4rTLGox1o30aWUd7MB4ysN9J0Gf/CGAi+9kBsBYAKoJGTT+vBJDe8yIyQnRhjsKGlQqMRQEiNzdct4g2gfX0U2W95dn52AaWJhqKg4Ig8JMz/C8q59KUrhsHIUN4RV9X/QrHQ3exdhGgDfeHCg2dek/OBWiHazKE1YYF+MhLxEZkKHi/VPlTWtghGMstvFyvnmUxiJoqgIggte5hFdhl+oDLbSxeWt/9HYA3VRkcNXEtOZnGdyx8x2o7Mypmf7Z5wVOF0EGHw3QnR6DbmVS1bcX3zecqFrn/Tu9JA72zDwYlZ0yDqR3RshJsAyk5D0uphaSCprmUkmjmgQUFnxl6SzkAAiz903PqNVRHsaDmslQlh8R9pOh1sXYgDVChbuVzBvpzgU3qKtAl7wpk+9PGfGRLzNWmcKJ9FYMY+gdgsY/p6zQytEqIIQby0+m/PEqRKi4fT+1wgvZCRverHMXfW3dIjQsiG3q6S+M3gTEsLh/Ojy1VyKFjOdpUmaYMkzAn2ni0kmTq0k6ujiZnBRTiLB9ylKj0Mw6qcdZErUWLAjDAFxUOUJki7mj8Istuvi2JK6ZsEWHjXd8hoI9IRm/JVaqLAnelah9XFqRjaibKHwnEYK6wZVCuo7PM1cTZC5VunfATbIbI59evjOawMCBuiXtzbXZptlT1pBA7rxb9fVlZRQuZvERedLjEQikZo1Dan/tlulOx+kuwHr7HfwYMZi8jm0PdzNEbOEOoqWcZ4i0K0bb+JQUXfALo44mdjuD6fT5pR6xbSdd4FkuvDAQlaG+/3dNwCfC0rWZi/s+IrHwvD9rPoKzHfHFKtOrWAPc+7dy10fnl2o0vIrHJGLxbETW2V8yPnOyhYTOMnaVC2bZRzcNU6O2ZPyt5x+s0l+bRfgNo0ZeKyOwYh+UTgwCZqDuayGXWhvMlssDqyQu4IBBujbpSUUwwQIBWsozKJgcXq7VyR/8FHerkzgpldz45Kmd6aeJ01A3600vcwLcDT7jxwLH0xdi3g04LXapLv5biIwo1Ez4DfUWwHZaDokLMuaF03l5Y6FQY28UHQcwxamCQJ1uJgEa/r+phrwL21PHt52eGDn+gCGsujRpwfQe1ns0ygofbECl5eNva7x+Yon/xTuobk4ehV3KsMvSXdqCHBq6k37u/12VHOAKoPaAoqGyerK3EcxuzYtFfqeGZdg+YqImlFtsD6zpOhBzcnk+J7APdtoGbSg85/0yxBQEMGHtNBZMAr7zZt/SsJ7PmBZSC5DEKiHCJijABfBFnChXIdPF5GKVbHPtwJql1Tz2nHdGz5uU3umcKs2Gx2LU+5YBoD855u1TpxsuLOvh0FQtWwGxm53UATeGd6N5pOzCyi17DRuFTXpPi7Sha32TnlkDtSITB0V41qqzFmp4swu9DxxVHBuaq4UqxSTqXaKxapss26l++K6lyfQ0V1CjWeTajUXiSbXdo9aN/JTwo4ZgyGWz8CxldH+Boub2YcqySjwaJSpqFGt7hCO+m2xU2oTjuT866h0z5d7/ZZTpvG/JsEMmQcGQaWDAZqbIPeUByPubROoRkrx3NiLxnZ1aAoJmFRetoqVZmtD3Kon1RV4Rw71bE+MHPfabTExpAzJzphn5OV0ziUbuS4T/yDpXxSGW/xEmQB8ApGPL+dsj7HtqpHJQnJB3bvxzZh3AAr5AES2Rsjy9BYGa2iajZjQa/PlyIR4DjUap/kDiSTpPGU6U3X7rPwiADUlLOfbHEx4QqswEA70cheNWuhbpwAMlNtkp1eHkt22S4NQNKtzhYCBouM2kMPQ/rQFsH21C1e/fVbAANBueZys1m4zdbBvZgWUDjSo817h+RS4G+voRXLhhvx3rH2mf5+SSbPH8AO87uDimSrO3yme8ka8HEsVZzeLcMY8pgI88c39pdmTLdUCAhLOSE//r58Gbd7IXQTO72/emhuVVJHchfxQxnFfDraJaYDk04eH/SZkMYsNmwUlzRufwyzX6R/1p0EdEAL51RF2hf1UzrxL+JnVPYIL7VQcmwlDnAtTvK7YLHEeIJSE19uiXN4VKkitk+3PWiS2diqvJrm+ZS/Xqy6iAyyfYjiTfp9R1fcNDjo0lpVvbfWoXsj0RN6466ShWrejqehUz8mcVp2tGFMY04iN9IyylCG4tGYGbB0qTzKdrHjg6s+OpiINs+fgGZmDbwKU1KMtsaRgy3KjWlC7g/gL+QFCCA/6+f+zvGDnBt+fWyTVlVdGWT42b4RYfojqV6Cr62x81PzZs0dGnAENEUCu91DvxKBm4plkLpsbC4txPzzk7vih6erKQDGo00Uez8U3OXvRFlB81OapUwRlYIuEb4hILXIpBbQUZaIzGIi7Qj1pCJipzXNqw2WFS0hYmtCHLO1fsT0PisBGkCd7cDsx94y/wOiIPuNoSh9lM8PCEls1tzSINsjPhvYbKx0PhiJvFzZZ9xmGJswSpdQgorYykdLEIsSt5BFZe1p7D8RdDok+At7uNnDzDjh6odwE1Sd8sry5AM3hXIVQLJpqmF6S06sBPB8TIdhdOacrYG92KFbDELOPG6aYrrsBQ+ta+22y0ZGSIV5ilDu3gu1s6/sdC8Tu042yE9//d2hSd1DRYkRO5z3qwlJKpqSMThOaVN28buVfbSiG0A2nqfMl/ogJY2pCCgskuSDYsVfOxC92DBsdmd7rwfetzFR3AT9zf6tLUVnBBipE0oz934UoEmOCCpqqYZYsuDC2Fqbwd6XUv9AQ++HhX+JyddqvT4MQeLDa+365KJQkxWTrXRz9V4xhBXaAqv+K+w/qi6dV648aSK4/AHqDiSVp67Vw5UtE7EGydSC61SUxGU8NS9PNWEp8/+34VdGHHgI4iih9anz5CU6ER64fwzJ7ht/0UQciVbVpwz2N9y9l3pOsQ1kL7pf/qMD6y71oIex0Nvz1NEWGB+d3ji245nisq3+bEMGRd6zl9qpfwdBtYdO/Rib1Mf4PeUQtKubFY6XSh+R1CS3QFHRrePzt1SlM23QmTH0ZF8/MRCRndgewE9gHTLUXZdJktucG9auiaGEUz6C0acljTnetHT3U0//cp5PbVMuBCNZGHrbnqIXxRTIU3U57YwgLLasMtpnJTjKQ+Eqy2tJns2ET4k8ozab1JJhONQ871POLbU3tNtKZ2+3mFdMBFIAxuf7+VJTwJXUI9nwnI4hOC7ZWXL5KazLyeI8VY+a3sTLJrmXcx5Mr2m5kQKlRuw6D5mj9lZ8UjBekB0NU2v5jdYHvHUmOXYmp6j5V7/2eI64X3LIl/yG93XY8zDRHcGVMS8Wxu4WpDIq5igFknJxHMlR2R0P6UOgI44dxTDTAGIvx+AgxiS/BRwxSGyaQfS84crOBxdutC7IhVlabCcxCDLEg0PvWWr2TREDg1qLcCNMu0LXHGBcDatV2NBbBxydPJkPFFT71ht7rwtrRfaNARzaJYNuTP/IM+DNpNOQ3Muk5gTA2r3LuYDSXAx8Ipht1TxYzSbfadjbRsTz4th3YJjpXAQ2MWDldlLUnCfOnzk7qewlb9kx+dC8W4wjqlWRqL5VY+rIShgJtxPiihDEDXMMNF/z4Ttt1N2vPY4gEBhqPR+1R0JopSUbWYRKbkHjvHzd6gDD0AoDE0SNZgVb1i/9AoE9aU0RI0N4mP1XPaKTI5/hfgR8f+kZ+cr/jBCRmr8q9yNp+9enuUwgchpCdLiDlvCVzs3H19oL2YyOHDi+89DgsHrThfzmjf/68lU04rRyEZ0sKFjbDe9oaRS+OMNe7ALM5EbmHe9UpQeCiXr/DHuPExxZBd4pjnn3s0QGnYpf7DyMQjvn4UDaLTQzOj2Lu0nPdDIspP3dp3s8thyVxxaYm+iP0uV9Mn2XMi+vxdjHsjWCaSjVCkRrEzcQO+Uni7/BXSta3aOCTkFnVVJ9FdnN4cHhx/XS9hTHp1JxCXcoiyx/GGfXKUCZ5Ul6/7wptbATTtKQcl/R+YPuo1WwUOlhmn/SSwec331ysEUHZeuEkxdbvOPG8Q2/X7h6VPPuI1P1qilXEvCG7ncVRoommQf7y2WAxVhlA7g3Nl5/mSSqmrugb/Gn4wTtkMRdYLYr1/89+4FfxUoGaHRiFBXtLgT8ZNh01ZT+vBCkEWsegaM36yEedbNNkvnhlQBgx3/ya60Ob6Lm1fqmDVerTWK9N/RcE9om5hZ5GOWcp3bEa0+oBVuau04gp0gKY7EOZcb/MCNYk91aYfFrXmpQzVLR0taWG3JcoMq0QuWrqyObqfqwsTO2L42u/81eHtSnLyGm90BJ0GUAyb7f+G4WDO8SQBJUlxf9dEZwyZMci2HdCKdkE799d3MGHCI/XSe32/4JTn8lmI2KXn0HKcsqwhS77KkfevfcHJMgU1NZ9xcg9cDnucDoEhTBqwgtyDy0B4WbY0E/ggfZhbf2zhRF1zA6mrBrr2QGQyK0cGEbbLgU3Jb1rmsgoHz9BXwqSks5xYiKhCvNL4u9J/Zd//ypNmMg6b/AbKEvLTOMVsohCtkHc9MdhskAXS/vMm+c7e9Y3eX1LOy6YeVqBUrWNpdQuBB+J6bDT1JEVy1xnhjpCwsoR/OD6xX6m+UYYybWjNcAxOLwcGHzZXpGS2P0j6kOdIqwPmGiVVUiIQ7Bz6c9xg3zC0UNbrlOj3HJpGkFFjU4Jefu9XvBAzsspoMKTxxsIDx9k7NqCV3QJUABE76xO8Ak6CGSDa23aOPPfkiMe/ZufSgcJ4lDdY2uRXFFl4lTh+uuJ7tT33UY13Y5U/814tN20Ac7pqNfr16OPVI0+GR3/ua1whAnPOjNQBZHDvhPp4OCZ4KDvpc/nrO+KPx/a0YynGubEJo0U8qHkmRbaznxjz1A9IgxZ4juRBtAVYor89Spn7ce1LHGq8q+342K3XDow2LD32oaQPFRUzzWP5s/aIvW77YSUUN6n0IBb2b5hMUphJ+IdQEziDKmIZaBnLKnuy8kn1cxRFUnpUBWixWfoS4oiO+XaXqOgfnm7r0RPmarJnYLRvpVGvf0YXBIVOm165Cv8umdD7czNHIIMxFf4cgKHqW5yMKbWeIJmKZO7p/i4oL2XcoMIXoiWZDDxNBjdqyyPeQ4rXx/r6o9r7TdNJloBn28dK8Dd0wUM1mKr/idESs1ro8wS7RMilQxbSZtXQ0fAiN2bTU5oe6s4d56NlxqSK1u+FDlyPwnVgw50HtUwqjz256+g95ad3qE7r0YX+QkK5l8ZiN5hPTDLRxyonk9qjcXPoXJ8m2LpfpbCYVZ8Pnv7rJ0p4q88QqZnYIMsZP1uHqdl8RLmlEKbeZrTbpUPVfheTdzJinqMxV9XvS6IjQ+47fK4xUREG0yqihRajIYDd53CiOoi+7f8/uqi+/b166lZtxy+3vu5AQvs+FMKBBvK9g43vpRE76INpeJ7EPLEjVTet1ry3kE4eV4J9gpneWUI28hL/Np1LtdrD55Y7aCWkrnzpAMc66vap0FzmU47XdW+Brnc6nrrh1KrfqL9NXFCZzd47X/hil172GgUs2zMoLPfWmoYZevmmFkg7t/z1pseRIgbu/WQ6ebL0elNKCCqBftrL+TDmkz8u9byEyoohrsZrjPi9l5LPXhH9bC+rvGYyEZhjj1d4IcdA7RUeZHd1pl4J/tH4GYTbqLOvGCKVgsxjnhZsKPNHu7QOng/7jgyCDcfGsS2YK1iWkq+RRnbNrIGzLJULGtCnE4ap8iDk12CyN+j7VvTowhuvHAmbtty3k97gTNCV6rxk2AxLDD+rdxUYFtsbpdObN3/POn8aFSbOpbamx8vO4j3TVw+dZSJQkBqe4jEGN08GzaaCKSx47FkqvIt987TPuMBhQxez/FwNTM0SyKj08Od1mQXdCw/0E+poI725pWEi6+25k7Csuui7TeI+4eVnEC2MqzDHKBE4BMTf9UBYkxkYW3PbbFsTPs//hZQIocAqdFTjgnpCHJP1UUJcobzUeLmAnOQA/MXv1H4jrqxPbvM6YF8mzgrpf7bckr4EekDKicNdAjAuP5pX3hqc0WQO8An4yGkMau5TbFs0qtpTZuRBVbx9yzWbEP+zTE+qhInz0H3U0v00rkmayUMotGvD8Br+s+x6vwBNin9fUT9JuazOtYZUAwR7UFXrdYrqFyAVDT7Og6Kf/LuQe7fJEtNGD68Y1SnHejZFHnAeS2Q/XnaLBNcJk2lL9Pu6dYF/F/UOfMdrd8hAU6zBGIgsYv6m1+dbqVZxFz2SIq4w8w4U5ooy+aF0L2xylTZ7Hip0A746j6jAOVJYP3d9zy+iguNhDo9eFcnQkld94iIO+oQztZT3a1gnNtiPWGYZufnRfhceKk/0NlHFhSoYYVHf0X80kt0ZFfCwYn6wCwdd6/KGa8xVL4M3QahVcH8lEaoOUo8GqoHZBU7LWicO83rrZKKhKRGVihIgijm/M+C953mKHtO46mygRkKYptiIWIQdDlxhpNhsMuPrhRoEOTu1Geqxv9n6cmDb8kslvCaQZFIFUGhL53on2IL1K4gf4+DQd68kV/L40B7wCjtTYmK9ugoCC6JI5EipUg9y5C1PV0UtPMQqsYKI3dbXTr7jE3J2UF4ZtjCp/tSFuBCFGdfBqe9fiQ6cquDQDd/Ej842eJY9zSpqDWplLFR16SUgdOgRek9gA9/qg3NIOfdEUHVkg9t9/K/m6dLODaUy9v+jTFFCY8URodCb0KFBM7skyejnbroHpCLQURL1IU0SrZYfhBvoBemkfkbLQ
*/