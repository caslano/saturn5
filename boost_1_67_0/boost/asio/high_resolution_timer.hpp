//
// high_resolution_timer.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP
#define BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_waitable_timer.hpp>
#include <boost/asio/detail/chrono.hpp>

namespace boost {
namespace asio {

/// Typedef for a timer based on the high resolution clock.
/**
 * This typedef uses the C++11 @c &lt;chrono&gt; standard library facility, if
 * available. Otherwise, it may use the Boost.Chrono library. To explicitly
 * utilise Boost.Chrono, use the basic_waitable_timer template directly:
 * @code
 * typedef basic_waitable_timer<boost::chrono::high_resolution_clock> timer;
 * @endcode
 */
typedef basic_waitable_timer<
    chrono::high_resolution_clock>
  high_resolution_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP

/* high_resolution_timer.hpp
woBNEAJggaPjDPA5NA1QB1umuAUEA4wBKtc93AbVsS2tDBVUHDNvbU0ZY5KIz2bnwpH8EvlOVtXnnJH84Bxg2hmrd2Zd+yiAEMdoHq9gHJBW/Rz0Kwtm3C3jUiPYzLQF3RocjmCYYA1Y210CZMBM6oJdtdSTFiFpPBOaS1GpGqJ8jlZ5+stoqNOStVPUX8DvVjN6PkZDwTNw3NuNGAd70lYE5vr2N23CZx3KLHvSBnxm9CzIQEzw7S/RgQSltKkwoDSVm4DqPo7DC1zBYb5PjW8iT9vO49JnP9y0ups471cSNQo/atuU77dbRDzwuoYM09WfK5EYXaJI3Yvr3Y1zdOkvc5Hi0nV6pevErsscwMAVy7AnllyTI8M9RhHs0p/DCp6tIYzAgZ8UgVmXLaOXL3NcIGO1F8fbmEurOxHMcDbusCY+4/htLCBQGr+G3wyZu70XCfIgfpj7rSjP2xF3yNRKqPIKCPJ0FRL0c1dpDLtvX3vSZ77jJ0h/P7JX7X1Xab761TwLL4OkCUC+m2UuGJnxRjrjDfznNW5YA+72eIA3WByAOeEYErFtqsGss5aonThgD/QYHELFpG8fQhnk4qbeZE1W+s3tjru954Pw5/m6ElVqbHif5sbV4vTuVGZx/BDJxSXEBAbzFb3WS+GPrGp49rmayD8yrnpPNEXDLQ9R3agtkQkccdZlZh/n+d3JWtx0l3MaqrYvcSeEwMtyFOMkmsCjYrQodQUXitiR4twO9dpnGt3iV6sOXT1bnDkmxa+VkXee5o+rlyoWbU0E/aaPx5e+++BRNDK4420u3Tsc8xwxDPkWrYhjOBEOLkqC2V5ziXHUhm8u//isfGnzxfGxcYnF9tLhGOcIemfEfmeJSv4bZxWmUvB8w8Z5/jbSm7v1I7NtzBnhdOQdJCt3o+MAlSLw+w8hzhef4FqUTOQtbKLdkCZHCNLgKd9xTDQEtyQmDpiY1qAq0eXVTyj2qy7Q2iaaWaGxSdjmfiwuLy4ulaZRDluwMXZyAAUs+tM3ZATXnX09UhVLN6/e/8k5xTc43PiycKCPaWIsAdm8sxdrfA1RfoS00/wO1w9vxZNsulfO9mV6uIVI/JrJTVD2O8mKNbzEzS/vHCrWEAdSNigr8i7jqGMW25Nsc006NiNZLc3TV+o+SZ1tygZN9OzoL830fBtt8xhAnyjuzhYqg2bDmeP8GEq0xgxR0YL0aOmK/a3VcOv0LB5vpiZzwmBe9PNjwhqietR32dTmsCdRf6ow+2yBBYuBTVkf4scik7T0UZiegtc4rbFyTgMoRI8oA296HnYTlA2N6gZRMhdIVI/vVBrKT3kTDozIqAosc0uUy0vyubbIrZK1tRfzyFvrZLAKXssQFbkOTNVdeg42L2EMuBztJ1hWBTUfJng2dKM2ve4ULJBsclPIFeEpgLUVWeASWxhnl4uVCnl/2UmK1SjG4MLp6FX4uknlQ+m3PWbNpk+vK35cy3sqVui5PAKVzWRpqU90mHOcpbjaI96FYw7bTlea5I/Wu82g37+reLMznMJlXR4pM4iX78IQzTG0j/+9jM9sAcVOvtqeaJKrNek17Qcmz6OajvObRmP4aOo9HdzMz36nKQY3THpYjc1vjaMU5rGbPmcNWzvcwNZ3Xh99Za+oHKa1ucDV4ZxbE8MnIGLxLJN+n48uL7N2NTQmpG9ec8SZVyg20vEm6pxwsmr6gy1HYL0TB9BL1pKJB4vNBGyu/q7rrutQmyn/UDuSmAfPvpb7IiXKlmOy6UwNyYTjWEfUa3p6diZejQLjbKpN6wZC0/Wqrl15Vq/2xyXMcSIrelKP9QEszvKY88PpOyHjAjm9EqoYnk6/vHdPe7ydVPMpPsyJ81jM94sf0pqgjprB3DLyDb+2fffnWzfyRqczjC4vCCawIChK78DjfpHZ3o7+OgX+hNt2f3N4VWZ+UuQI3eOr1kL4TP5Bu9n3fTElS6M2Z9z9/VhhzSkSOT646Kl8sfWnquDpwUQN3Qq9H8hHUF7IpnYmzi5Opoa28KCcvZEVPJCLmIn4OcPLyygCMrhY2tuJGrqYElOJcjMzMXEBmZk5gSys7Mys9ExslExMlNS/FLN3IqYiFgJVYUqsYGHvYu9sYe9ALKLMSixraGxp9yxTM8ram/xeFZCJiZOJDcjJzMrMTs/E+ktVCk72Jq7GpqC6/lqVGegCv1fFz/9be5mZfm+vsqWXKTEzkFHJ3t6FGAjSKzFK2ZnZE/+8J1BeVJuXk12MSVSEXZidmUOcFSguLiTGzizGJMTBxC4G5OJi5+An5uUQFeYU5QKZRcWYmZmFRYWZOcTYmJiY2TiERURZuYD8uowqng6mjBpKpmaM6tpAYmZioC7ja1M7cxcLYk5WUNN+7VEA6AADIINSyB9gAN5nEcTtAWBgKAAwCFTQrx0ABikFAIPBBoDB+QLAEJIAYEj8ADDkMgAYCh8ADBUOAIbGBgBDB5XNigOAfRIG/NN4ObsYOrl4OJmawbMCmTmZ4SkoxOTFKRRExemBDBzwFOsbo5PwwN+7SMHQ3NSZmOVnf/y8CxFDF0Mbe/PfO5TlD+Nv72oH6khGGUsTZ22253N+vfWftfx+Ctvvpwg5uQjbe2g/DwqQmYWYmUUXVIudi6mdizMx+8+rypqaWBr+tYyCoROoyK/tUjJ1tnd1Mga1k+P3dj5f8vcrsv9+xV87noWTi1Hc0sbF1IlR3AbkZKKmxvYmpr8PhseCbQKfUyfxy2D5dgKVAsnraNO9yVyXRIhCKRLK+HsOMMjQWpZrjSGOd9+vz8Tb1jiIz6C3JonuW5g8oFTAYhH1nEdgiRdbxmzSxjw+SeR9QN1sHqsbyFdTh7c4b49RYLH31qBOQYG/YqHEaM+uLOMGSPZEykoEHo08Zl29DiCX9BNIoOg9dMGcIahloSQ4RpbfSUseSex1zvC+gc9kXONp9l0y9P4BVx+yOmiPKkPvITiEbflJtUdS80A6OI6fydxXwd5XSQ3SFkI+HT/nc0r98vxxyZhlU102vNS3J+aK7gg5c8Ny+MA7mtfcO80u5bxJNC51P1J3gMa9FG6vIpntOJIWrX1nyaUtPw0rKMV+efqOXmA2gYrG5C2OkmgI7a70GkW2FoaDmgLd1lE+HTckI1D+l8YfvQ2b7jqxd8ziTg92lWD5Ih5y3znJtZPnvHWWtrPg3vi2nrlheyG+MDboLlwcB0NtQXh9AlBK4uiJQpyZ7s2/ppF7k0Czon0DAUF5w/BP3svx+ziKebhIKLuARg6Ul1AGglLQU+/i5AoaQ37+54nBWNnURZsR5NmMKqYeLoxStiCPEP6FifzCpHQZNeSNrEyNXUBnS9kyEXP+8tzbAol/nQFsQc8q069ZFmLgzzniuf7f2sP5e3t+ecZ/qY5R2dXI5Vn+eRlGYUsXZwVTJxF7Wwd7u2e/5QQ5uY29k7KDobEpo6ipm6WxqZKE8G/+KCqi8os3/uarxMTMTJyM6pYmoDzoCWCUNLU0t3ABPQi/u+uPuR/HAKSfkyDABPBz6lgEiABgoaFhoKFgYWBg4OBg4V+gI75AQHiBg4qGjE6AS0RIgIuPT0zOQElMSkeGj0/FQU3HBGRlZSWi5OLjZOZlYGFl/tEOQIEFYAG8IQCgOQgFAI4C+NEFksEAEIA/HZBQMCAD+kswwF+OHwuAFxDP8xo4ACAAGFShJgb8ywPix/w/jTzX/1BPs7Iz/Qf1NPZzT4P9paehwUEWopeg9QAC6o8WMHA0CFQldAxSxU9/7vVW9tjU3YAIUUgjYjIUMOxQ2C5BcVJw4EuU0H9Wosg2q3zNSLMieo/q6RLoURTIhxuyHpgsyfE+hWW80I+K6z9HqaxH96rj7ZlBMNT6V3iE7rfoWOGQVIyYsAp6dC+zmjVIhDwqhf8bs8jfeBmQ6X/IzdjYuf6z3QwKGgYSZCEGuRk41F/cDAIVDV0RA9MwdvzPfjZHW7NUIOL9AcotbOz12ybR3VdCutkuaMTl49xwMeoW6ZB9tDVyb00wFiiFmOGP0LL+rYLosqNELxv1JfkUbyy7XZoRf0rihQ+suowQzr1dDMnjxQKIWDLtS2dnCHmXVtGdYhOnHLw+wnu+uDmn4/8xJygxEMW1qXaZHGMh9xWv8QR3ntN8kVtzeHhfjvZFR4C0JOj/juHvfBr4P7VIMbP/B/k0Jui9+S+rEey/tUatLN77/2Z5CQ4QBADAfwD0Dx5+0wnCPleA8OhfcfrbEwEghgQxgb/rfOZ/CY+YmZlYWVlY/i14xPbfwSMuZg4gEMjCzPR/AI+ALH+BR0DWf4ZHzP+AR6ysbJyiIsKsQHYOIVZxLmEhUSALGzsHMzubGDsrh7gICB4xgQ52ES4xUWYgh4iomDCTOKeYuCgrqKgYEzuQne2/hUds7P8GPAKsgeakItByyAWCRzkgeASCQXDfQPBICwD2Av6/g0AsTP9RCIgVSMzC9U8ASMLJ3tXh+QX159sto8wvTJlRxcnQztnhGQgZe/5ykZ8lQS+/f4JMv1b6f46YWFk5/iVi+mqFD3zxLrP9ZNVYeVc8jkKm9V3umLFBVvJSfgKqm/bEdwGVDJxo28ZqBPaV0jz9tponWKI3wLf+SvNJV5iEbd+I+X+cqTsIncM8dOclZL9At5eTRYzbfKOXjokpjucfjlUovz6Qgvpedggdiq2XLQK9HzaYb1tSKEGR+ppX38C/5esry4CDLP92VRpY7QnekNPEIIuBaU1l1Ry3BdAcWTO9gOYqf+zZ+E5/7X7ntEkrevpudthnQA+tD3MsxZFDH42mT9LaiR6KeVVQNy03TfWgnDg3iIUs63C4AspVOq46sSVLbrzrxcFtRi+ioWxtRHlhlavSikXkXrD5MFO6xAgsD8+Fywy67RGvpbJ/+p6m+ejk483K6LhHo3mzO36Y+wbc/D2P0ornWshrgGjPh8gJeW6pExW+PXYMPnkSJVrTJL9KV8LgQLscA9IgS257FaoSWU9o9qgOqQLF3cvS6p09vxc5DpVX5Zmzk9dTNv5ab3u27D0e3l/FhQ7KC3z4PEWdgBrtT3O40OvLfNJGHj/Mow9Wu4wdF8xmfKawzN+2mES0Npma6ek8SrR+TqiXVBzgDvXki/gDQEP7WPq/j7XEQf4KUokDf8FP/9voi+sf6OsfmIv5V8z1C/z6dd6xZSX+OU39V0hM2NDZ9LlNjCpqyuqKWrRCTpaGNrIqoDXM2RhU2tDO5dnqrA389QEVswM5sqWdOaOUCegRsXTxpJdklDO0NQXd0T/WyOcnhIlRxV7VzvLZ64mB7L8/OM+1/d6Q/ymgwgYE/rrasgJ/W2xZuBiVZQ2drUGz9i/98z+y8lICqP+08uL8fJv80yoLAQUN+bz4kr0EgEOAZmmw398oIcDAQZAGhQQIeqkkY47981r8/WJl1J9afxrfiYOHaMc4HvgiuNj27F8r6Jn38oeuvNbPtL3CZ2t+ABBeN1pW8+l9aVZbzr46EuiYZPhoM6pezohRX9jiLX+akpICagk2HeY3At3Rx/KHhoMr62UCvQv+F5gIdlHlO0+zfjpXd7UnSBWemdAIUPUS6s4/ANZtDF6PWt9D1JtHA+3jZuusZHDrVupTK6b66/utF9koIrXtF4dn900WN2uPPsb1lNUfbR9cMb9+/Rp0KfidUx29dCzvyvyjtiPPaGZ1gbfrl7tN34I5bEEVD3nGNTxgYRWILR9SN9nf6xkPpX+opiQ15JpVLW8t0VdwMxtKCwva0VVrvCvzFZpPZXZ6hZbuqnWwX3sFmZub9Ze3G6L/lziHlY3rb7z0/5Fj4oJeCf/smZDP6AYCFmQjB3kmKA8J8SegA4mCis5sSAIUUkQjdfyza94+PP+Fgo4gpdqEtQxdrDfoZaac5sliq7K0UiNITrvNTpZnLPJhH31en/NGo5KSktTNpBco+ona1hZYTunHElmbL+Sp3qJ8nusZNCagj4BFy3iBTUp6zL8wyYBW2HijF7KoZdrhiqWPMD5eWz0YLB1+tOaFzWQZZmtGUZuSNAMJNwobbw9ZZYhqu5pEHyhVF6dR50JfpspLyV99tburrVXsIedrfjA+UVujMpE2w3LaAo9OFxohYw2kL+2qqySW8yzLCSK0pDOxtliD+ShzaG22N+mZ29rJ9nLTLBs/ckok7p8oXisZZeD02FppnUuPYNhKp5NMBl9o2+CCSfPD/0vgwcLJ9J/jZDjPuONP0AMCAA4JBvMLmAYHHX/0QDBwFFQSCCCakKHiX/zrZvysehOaiFzZ2q0V2ydW6SerUnL8Vr6HKzf9EUTyFBYTanu40t/IpLRzaVQKVYoUxjWK+fj4ABBpGH6aU3FPb/Cbq4so2sx5nS6cVOJWqlRrWqqSZg8I2Se+tQWKc1bkPP86OCvyI3FJiQFcQ1/Emiw1k2Hr7WiGWjk57Gi6N96+b8SKgqf99OXLlOq0HyxxkKioIMA5NcjePsch8ujSDqWlNeilEinogAb2B2Jvfo1wMnbhEHER/Xn4/wtE9P/vAskC/E+aep4nnj96BWhyAQP83DWl+nXqAXnGP7wCAIECiQpkUUQjEXJkVsL4BIX+l5XxNpZLiLLrNge/WOqM30NOQeqM/CE4rRDXgdw/pjoRQg4y9AeAFOI547T+LWnVLycZ87Ae4oowpc70C9FuiqN8+68/X0inVlfEISf+n4kL4tCcQpbqor0CzRFHIYbb4tR50fbB1EC7+wXve8/GK+bPUU/mkfIc1zRbrnpPpuE+2ZtEStOtik7IRV76lE5wm0IW9FB5rOxBJcg1FBq+sXh4eODli15v1C1bBEvqlnPBP6I5ZV+Moo9HDrw1T5/IH3YKSNkCU2vXkKCCrwPv4EOnmUOApYfKqsl/N5ZoeA2q5jOZsbHBFFZ+uyN0Vgs7RCgb1F4lvqRogCR0VaDk11yLCQQhC0SabNhcRtqs3xIcHBxul73sj2jfRNdk4Y6z3WXhGhRfKMsXvqPOayXFzk+6CXv30Ve0U5Y/Gy4/+Sb01Yv++AL5v3NWlv+pvRMgy3+Os/7N1gn0v7V1MvaxUw0AwCp2lYQl79AAAPSKpomJ4+EMAGBeBSoBb19TBACg9tOVfp75t7slrP9Wd8sauriYEmuDcMLzVsG/0/kSToaefwNef+9/Lvb/tvs9FowNsN8FxOoPvoB8ndBwRmsyQ2tLOzI8LOuORZY15mZUQqn4asHNVBplQxwVXbh0BsOcJNehp0M6yzzbhavIjLSM1zi/e1RSZWgTepAFBWMWUhYfKscAXQEHANiRI+T4555g+9d4RkRKVNnT2cXU9nlXBlRO3snE1AmEY4h5WbnYWdnZ2MU4WNm5OFg5uJiY+EGY39wSdA1PkBUIsoqzM7OzPeuVXR0cbExtnzuOCQTdQJWq2EtIicoaOvwDD/1EOM/oycnS4XlnCvjLrsFvgwI65bnA84Ax/x0iAv7zXgIzC9u/2EvQjZG16mR6GbzX6hyimeiCspmC2ciUTZI3Ff6kUA8Tk1dFVkgBTMJqlZNfCENr3g3AlD/x7Yyf+uRXHDhayM+58I7ZjZ8zHyhnA6e97xugGzay6KMoHWNGyILoukuqglEoD+wZYrG7ZqhzQdhPJ6hC5rNrRY7cNZPeC4GGx0EYw8V3/bw7ncvB8rIYanFGzidzp4zpy6vWbVENBi/3coOcHCCOjI2wvAIGM26JOQ4i+pLAD+HadD7cJIdbQBzD+ybvsTj+FcYlA9TyvMMuOt+kZEYxOQyfrCtnpddUU3vtV8MnG4PTROKmtjT/PPR/AN5Cz4jVBYSHmdgZhdzMf3FRNnYgo4ihw69uygFk/xXZuhDTszCzPXeouTMx689BEH7eBaJnZ2f7aSJmZmJi+lmZ7k8raARMQQj7l6+ez4qfqPcvXiblYmhjaSxkZ25jSswEevQ8fmkEM6hSRmWQ86kRc3L+Puq/ewmjxq8NZANy/cEXOP/5SzwbGzvzrwKQGOSrXP/qy/zRI0wautgFJ5J7SoaPw+bQUSxLfbU3HmDt2s6+nws2tOMrgYPD0hrUSzLxl84dESkYkygqXQFc4ShosCkQNNuic/7DNkdLlesbF4++/ic7vis/YLLyi729Gr2KS0CHN6YwHElkn1NHf+knNEosP5f+0rOYC3qSo3Icnqq2RFsCfRHJe2di+5k0MYrw0TsXbX9Jf3HJ449cMla+HPX+9owkgaOkohms7mfNYoyEzohL0W0yoTd+et2fGwhaK1KF+kLN125PdpITE1q/r5tHozI7QeSKXJDkWGZ1k0j6Q+0xXGBNZ1wuwvU/BkUww8G1KiuyFQSl8B0Tm9wSSra1FW7mdstKhH0L4v2CM3BPI4OZ+O2i2QUid4UyV+qiW5WtFo3om9nLc96aH9lr4SWDmO6+7pdqwpRbaEa8Qofu0/24jVGhcftx810c5pquUB9YKxptSLgM/eYPrT5nZefWxaVB5u1uwjkS7UlKMkuhe8iRQVsKf4yl44HypJnKR4tnfSUr5RyTJU1OZbpCwiAG52wpbhIDnOKxmmAi4o1vZFzjE/osFc7ljEn/ajD9wHPkSnincaGh3LHcPVEtYZQMbztJPSlmeOQq7HzgXOu81Nm3oTm/+G3zms5K8FsKkwLnR0hyTaFWp/IVRhpaeso2ztm24jV2ihHVd2bcR19p3amg1Ztczw25ENGDOeorPu5YeZQX73zcaqAZYVONPm746GEr3BjDTy4JHcuJI/YqFic3QSVGy4mGK0RHspycI2Yx9PXRZ1pl23xZZQ3+b3umxW5BrFBLUGeJp0gBV8BrjNNXBS0qK+88zOHN3V+vmeGtcrWXoVIvefkVZ8zIgzMWtl3hpTy9WMmmFqQMcTeOeRGoFv1KFCfrhYOSbJ5WESb6hsmeiXDeYB4trDLCNJyoUkGxshTClcmVyoQSnwhffM3zv0t/dTSNsX+bG+hV5AVxVnQ/lSmpn1MwnnoTyUsWDRlpH2kv1XpbeosP94ExhTFGUi2+NIn84zR3CRuOcKGGgTX6UddbXhJZiqN+gJKkeAycCfcHWcwYKydmLgRyd+qGd6UU7rFe5y893/LK18W69zOc40Q86feB0Sgqe4Y6bOlt8W8ZwqxU2LidQgyQIZWr1wFakQslCHwyz1MCT9QJ3UFqtGc1KvSNlOQ35LxMp1PfgUmkVn3Pnq8=
*/