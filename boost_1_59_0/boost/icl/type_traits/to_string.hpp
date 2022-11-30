/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
Function-templates for discrete Datatypes like int, unsigned or
    any class that provides a ++ operator c.f. iterators
-----------------------------------------------------------------------------*/

#ifndef BOOST_ICL_TO_STRING_HPP_JOFA_000712
#define BOOST_ICL_TO_STRING_HPP_JOFA_000712

#include <stdio.h>
#include <string>
#include <sstream>

namespace boost{ namespace icl
{    

/// Static class template for the string representation of values
template <class Type>
struct to_string
{
    /** Converts all values of types to std::string that implement an operator << */
    static std::string apply(const Type& value)
    {
        std::stringstream repr;
        repr << value;
        return repr.str();
    }
};

}} // namespace boost icl

#endif



/* to_string.hpp
lyD9/44qar6Fvj5QRv51o5uNN08DUhy5Qhg5PAewYGeRPKAdqM/cLG2HZKii/SSVW59Qxqr9wDoJaGG3mIhj0yj7Wm02dWntELCzjQLTPlmzRYnONXbKKKM4IpYkfKiJ+uagZQV8dKMNu+x+vBmX8qpopsw7jcbhsxHvfErTrfKdunIKV6edKc/zymYhqNiXp3yp4VGhx5bvHBP+IY/rNvP1lNxm4dRISdRrage3YeOtJjCJvL1BHN3oIlukWMfRdqS8NwwVuiynUksiXEfJbPY9GJlcuX54UwDlIGZ5SLqDIyT9BXUaEjZ56GAKU6UmLkTEtqUuHjc9oVdICIn0BVp4x1CljXcro6Ssgn9GfyPnn1teF+vAwKMeQhfipPZgfF9JHcAIN5ppvIcOR8eFv5XXhbVZWsBLkg0BkiEDKFbqSln7dAg+ZrmctikYMh/ejYHaW0Mj46TExNH3o2qUIfsb+4NOh/wbVeq6procu9W6KFxjyOJ6CW6jLEeXU3QnSNoTw28eDX9D+U0ATFImM4/bhNsPlM7XGX2l7ZC8A4yUu1JOpMpHEjzUCAstU6LY4XoX4kcvZbJEQQdL/0oP7N7Tnu4Lt4DAfduVkYVs63Cv4S15fOVSGAEnhC9vbQ+poO2kFL4DCo+y0GCcg/8OEsUKknwyVUKJmFyqMgv/sB0V3HEUczr48UHiW4kRejffMmtdf/Mi90s7oGzILdHmliiAMw80yHOp0JID5eTuE8ssxwhJQBCuARH32J2PL9bGRBswtRdGzJwuhvxJGJgFHl4Chs8Dw39m8aeHg67hPDRGk5UTbQl6ZUuzlwMHeftmAY1LwNTij563gMksfm02uuo3NfFU5O7W7nQ35oCTEgtv0g4EtKFeYQ+DdUCSVtRM+dMjBCkn2RAcGkw2cZY9sOEZtl9djt0B4vGpQ37fpP40YKRnRsp9MufZZuvNTX6dk4deEKQhK63lWE7w5s8zHRi0jvIScLRjG7V3CBDxHAJMQoePweOSdrj9mclhQG1Ev2pXcjh8M/5aOAov0dMjseZaQQV+R32tB8zV6vo962eelze3k8OGM5PJYS6NqlIvyVORJ+7Xv4+riTEbcMkaote3ff9Kr/+lxID92TqjZ7GdrmfRWnr/IqFPpux6gtiF0Wr1xJkqxcSZVP5L24TcIh+GQUmck3pmU//RJV+1vRFSV9IJ9jZKaHzEoeVRFW0/bgouE8ifYXvlOdjtGmgN4RtBPgrKLV1mKVj0A+WmC8BoDFfifybqd8mCUdoapzUUm4tWNukH8oIDf81Ut1+TbwJTzfLpEUVYAtRoZtTvoh3Y0gBsGcEpaUjaDyrvp6JB5muTk+TcpJZqirMxQHycD/BgnmUcDfDcjdoTAptK6Y2Yx2aj/S5fH3PNIE2qTlzF4DN6OQliLZi9ZqNJ0GQoAVuKnffvZlfqpgE/HnH/0vDWzM9X/lcRrZyQsD+RPbkwLepfo8aTda5H2/XJPL64g10pSCdZNO0cx/wztW78iChyaHlBPQna9Nh9MTtOSlCc+TSKvB/MVsYypHv6XWPpjNFpSNiPz9xq4wLUMx2OX0Z30GfTqmheTPNlzHBi7hVyhXLjQorVXFfRFk6jLzkcr/7kmGYT2YqsXLlyn/5QJbPux9+Bw1NdkeWXv/qG2eUGy2Sqonb8WgDu3qkwP7vkymnmGCndcs4Yt3UsVCtEZ43M67oCkIAG63WSSKnYDkzEq+lJkVBuqV0MjvEj/rFXNMXQi/xkvW7iX3Eeo1NrareBtDos6gcyevULDUn9xXWN7mbx/+TkIjiCArbV3G3DLRVZZ9KHyOW/tTFhlkIPhu2faRYO2Ueubfxx8zu23/70tPCrYBPB9czoYDn+iT9GI9aoQyHWkqWVIYnzLKo5BjCBAFlRVLPJ7uOYMIPldkNHuN31EHFJj02g9j0HkFsGgoS3GyelBTGoqy7Eb/nLLAfhkMfy/cv/m6u1R8n3+L3llLW7ljpbftbbdC1JO9rB+8BWMjvA+GkwrZQJ/hkhdUGXEfs5RqtPMBfunz9ohgvmnVr4TvhGjCLAg3Mt4+rXknPlQ5Mph+1dNm6tmq7ix19x0A2KBzHnGmcyrsz3mSugcafoFPdupn1IMhU/eWjMY8S1aUYAw1M4OlMWBd0YLsM2PexmlUzHjr2mk+pUdpYPTWc+/bdndLbKjrAzpLdUFT7mWXd6eEmZjN95TyeFWQHL5WmqkYX/4MBy6BtmqQI75PdT7tkjyyalblb2tGFk54Wmt4BCG3B6s8t4hlx5OR4q83s0KQmM+UcuAYpv/08wLFNvXYyyi+QuxlwZzM1gDZczNAlx2JT032bMYkZLEJ91M4gSK7tgFiVJI00K7wO9y2h9JDSk8ht5zWJzbPRrO8Ax5DbxV5HeAmtqkVLBGSOunvw7b1Ycs0ttk8BEwBcGtjOIkDIIDg2KYc4cWw8fk55AayqTUOJ36wHIc27JXpUwN4VceeUDYQWNgyghPFprooWaJx9YLoOs/AzQn/8GDqXsaDeFi/tc4cfMh6iZFDO9M/+suMCz69I5RG0XwO/4jsQrrIPsJr10Wb08BSrELCPPa21C0nIWAHPI6NqWs/AmcW2Ll/jmyGZX+yNi4p1NZxf3bVj5ey5RloES3o2HxzHPOcssZ1gIN+A5VIFHiZMd/Z4LD2bz7TbddxhN1u6z97vLGHaO5abLGgPYaR/RmwD5XAbHr6gKK32KqXTIEq2T6Vp3zAezAZXd7jvmsQ3jkwGv8g6Ifkqzr9r8FXCrKjTB+6edZuP6Yno3DvXYg2bvc6lpLrx5PtO4avXXfb/ztV8l5jZur+TZqHoFv7EVQz+w1UFfZqLEwPJpxl251Bc1Gug4V+UOe7d0tuROUdErf8EeE3UbHoQituPBeibHT5ejMfyQx4dosQpE9sP+XuNrUr8VvDi/TvdMJRDp7aGbPzElwsBoxxaxdeu/rJKXmBjaB8uW3yYfblY3fjG/Q87rYBL1fbg+A2DjpIsQqlAZFnUuRAvag/k2k07n+281ykkFEeNTwYORVcD5KuDiIv3I7VfI7Di//qT7PXHbg+vnTfW1XMQsddD342WynU4DKj3uPrnUq8fCvHymIUsCBC+ydALpRf9yTcBDP25WXiaqafAq4ZpEq4OWAGbSsbRH5tTST0XHrCA9M4BougiofwHIIwPttzK3z5loNwp6W3S9dm35GWzS9ZqsxJGvNgSM5LbtfZ8uOjUKHrDM9K7zxtjKZ7takk8GHpUrrQm8jNtXZUM7QrbeTSPNHp7fnjS8JTG2v48nyBQMKdhMYG6KLU98DJOdfv9aTfCwZauuKbX68iI0P3fCr/0M1gjRwbH3RpD/ztr/bMMHg9sqIfrJ2lM2jsNlncsd9UULANFyG6CXcjtVZ+0hNHjwv7gYn3DdN/RCx0z7wSKA9/2GBIS7X4UlNT3A58N7Uo7k4YgPMF6uxL3mDAV4ZCYefr9DPfwNKPeJPGh52sancXAyqip7dpfPu3zmmn0ZQPGaAtJKsxIY+/Q15zGBGfbn0+TKZjV8sTpwxbwHP+kDe5aEOm9SHWNW6n1p/BT5Q2VL9Zz89BhNqHubWlXG1UxgEVvvP01swxuAn+UzGzK1rZwOHEVz2bAuLw0wuUyXsBk3OU3zOgkKEEqN8wm3fEMPccwEk3mU1HsWdd88nv//SYCbd3GUsJfcXJ8Ddziw9RU6yQA87ykNXtU4GcePK5xbrrHtwfEwR+dYNxQB6V0NxB1hRZNTJCEGfM1qqLOtLB2FHgn3efx5F65MI9vS+f/1Xr1wcCrk8hoZtprzxS6amvMr240rc28eVvUTPjpLcvaxpziPCWk8CC2xyTu2cphn6NGwq/Ko4IP+Rd/Me/N4s1TARJjmdR2U4mGVdybEdoRuc3XzZwmbhWZRv18HGmZQfySBW5n/HscSI5aGH4pidypGNm4/DUQM/2iVZoFnZLWyg/5847uVmdlYXqBCcNN/urkc5EI0tvTI1BCU2SA6DsDiju7cCE6MIBdqLAvbRUNhgy7EnzUW8M/TBlGElTdTkNOYI+oJi7E+5vA3F1QVEsaKML8UO5glrmucwgazffCCtWU/J/gHkRDaYjnZIayQnDjdHkHYKZqCPOHtefU5ht6jP8oPXA55rPKIuHnAghhT3kEFslqogDCkeHL9JGb4TBnWSGfz53gM1F61DDnWI40HeOAlflH0s8HsCOym03IBcDokXekxHNtqAX85LexzjAQ6uf8WiT1Eyl2dnDaXfV2Jl4IKCTs/aZxhRBdAPkqVCM5sVKT5bKqJu8LN+TeL3B03Pslg9u0mw7dAYbHj/MtuwL4Qu6dg4pjxEFpn+J6LPslAvT89AVtzPkjs/rxc/fc9VDm9FPtUsRB7d/1T04xPwxr3BdY8eF7ZiTj9ePnBaCa0ursYkyMEhrHDVmDtOPh5mqN4f4y02IBpEF9m0aQ3m6EuG+//i0S2SrsrHScxNVdH+r/tD8F4tmOGrR9C3wkl00mv1QDl4JpfM1IQnodlUrWXQhIqHeHdQxZo/QJf7mH4o4Ipzl4wULHwjauSkh0X3uwN7n+Wl6GSGytp7OQ5cPWjbX1NTOHB855n49rintPmHPvF3xj0f2pWSt5rsNLw5Ht03a9VDOPR+RMZjm8UVFQurZ/lcfzZd+ukqdOL/R9cRl2EhlTY/PNA187jhIui4WkIcprrYwxP+EQ7pj5rubrsNVSn1p/4cbpaJZJNmFx4Rf66Zr76GO2lGnLGZpnV5/IOuCPDIirRst102C/ICWvsJUdi5mtogfwoXReny80LPjDF8m89jppESEKC/EYVMzsxBMQyItn1HdB1mUU8QpN45fovRnrKjegKD9IK6aE6EOOhp1joaeFIgliFOsB4TYfDemCcXJKHPHmDP2R0Y1UmcK7qag/MdI7N38KSclcDGDPsCxD5cYhJyfhy7Klvrh45LSxXC3XgVz/EIxgdhdUJjuId9cO/haJOlbqW3WaO3YOkuK5zXdbY/xAvTbnJnyKZlm4lGDYHmeeGGJLfM0vUf6K6hbetJw8dgv+IgEqgujHG4pvvkf7EmOnq/WinCW9gD/HCFGLyBCJXfzY2/zxcdhDaTe/gECCrsCMYheDWudAVfnoFvMsyLbXk+rhiQbDepE/LkY1ra5/mQpNjWX/k5ztl5jsLQ5COhgD8CAd2gDi/Z6DpSAzTRj5kFTFKX/snxE68F5qwH8zWxUkvz3F/mclB4nlG+33fQl07R/2qbZj7BOHEf1dhR8VhELHGpKtC9IDbXZaRqSW84zNxMhyYDwNoPrrOgzFqVDQ/N+0QGROdfF7cYhHj0MIfIfVsjX0Afjv43+hR+rjDZqh9C+ZR8ur61Ssc2OtgwEqpWSJY/BC858Smp2YjRmxwef3+EkYozvU0pvgQqGRXm2Bxy3Iy1X3zzdA3KYu8kHrjyxtehwbwlzwXfQ4MLfIn7h1jrms/KabOJB3fSdSSGlQo3s40J3zP+RC2f+vByo63bDEz7OdzYqWzGk+k97GTmNqK815FgginrDaRJdkhILGMm/KNexRzJXgxUor8JWl7vVIs4B60N8FpOkTjcSk3qWMb7siROko+Gyx3kNiyHUBMAsLxlRMGYb+H0eWuW1Ut25YQ7eDpA3AJiGUktlS7eenAiRJ4THBYoyMH+34ju3EbPjowF33LNvxgAKvx/nAbfaiX8gmf17voalliTywEDKQ3qN5P7VWa97zpr1r7SaOr1dHpai0mZeRyydc7aJc5rpMwU6JTxefGG7OTMwzTVFu8aumSNn8tJtNxOMNsW039d8eOlE39d2Nbu1Rb1pRyin7V+e5QuZrRn6vbKC0e65GNn7pBkYKW8DNMcOKIH9cTPwt5YVFKrIgLW/0+QjaxHkM9fr9DPLIKU1QBVA3f9MNPY+0jZKhHanl7vhUWxdtmPd1Wi3d+z4RXicqoLMGrnjVtRHvXAAAs/9M9dRq+I1J7cmX5z0ROrYblezxQ95KOj/eQfRP++xo1hH+qIszLcEtreTbMy0mKGmJdM1KJNyIxr8ss7UxcDo22eLq693yu+LmXyIiDtXZB61XGAetVLcSyJfpzrWcN9+cAPM4RjOyCh1OEcGemtmV+4bB7AuMDymX6imvHHsyB1kOFeYzwXBjhiSRPqyfw1ZHVtNjbR0NWJ8lMqyYVWO//vaU3zIZI5vJ4Z4zlnzhzTsk3I+N47vmIy4eqr94yELhenaH3JfZ6tYepr6W0bv73wLLip92lLamjj6X+nla0/hFQ9JRdxnpKpk+wbEqY5O3Ao2jSTBBXnTDjU48m0P3GwyaGd5D22WcB4G4bkER+sfv6LbX5Uf6IlSRREBUJKJWYMgssVS2yABiXiaIBKHZQMesGzVmRWP2IYcOrB2/5lwERPN8OHMb0z5YivgbCpREdaeTI4x/wRx1YfyNlUbV3adwQQ2YwNB/hK4DxmC1wxnx43etUfhCapdM3I3xlt2nhrA+iJhCeZa6Bvu1CLs9ZDlV5n0WMKqWPXjPgAm7j/Jvf59WxayOJBAzipVCelKcC0kJWG047acDF41YRN8SBmoqQsbaZdsjVlDLuw45tmcwNy6qLgHzw9JI7RpMX/g/iZhr5jhqyJzKPPONCKXgg2Q5kLIiLKHbzu1nUSsVBfLrKuQhGMwSNSUkpD2vwNeDar82+JeRiHDnn4Cr0I69vEL8cZASX3IA384I3xaz6FGAR9wQw92jvFYlNgrLo8sQ5H4tSSM+V3ZaZF+DE7biNaEhyF33+CuNnLS9UokgPvuFuwNEJG5+xt6dnWgQvin7cIP+zo3ndo7fc5SgysP45Zlro4gbfUX+iGC1Y+W7Rf69yaPDoU/S8ioSc7yu/eO8ecDb4vMgTTCEvWgQBScNOvaa40c4jHxbroJc0DNiku0wrpQGIw9Hd9yWAAv/RYIw9jMZIDOeRRy8bsC8E32uj35iKPQ8XpV/Uy5G6xAtdEOk1q9c+CSidnM7WEwCU/nuM7zHmhUjfTNkJaJ5KjpR/0kXuCQi23ckJt/uoUw+kUiWH3CPJYIvGY34oJG4RbGJQXdJc02DcO2wiYrXlUfgs83QXWmmkixaecWkdPVltKJ7SGrdBPlsM4+lzEnuN2SylLNTsh85U3p7Obr3J7k+dlogkfIBsds2UCUIv/MglKB6Ddk5fXEdHHgfeEkg3d3/Sm4Rgz/QpyotDc/72ljtl7HZp/ZQAcBmyZ/aQC6Ytpa983YXR/FQfzg00YNPfHAcgOutExV0N+HQlJT7HNB2itE+8wPAF3Z6WaEjSEX8tiaNB2rTHVF0lBja7dbsqEFKrZpUrzYjsqsO22CBhZre2sc0GHjVxyy9fuaAuS+6e5v1rcCY0lUkp52F2N/H3lZ/tGzEZNGYE1twRJ3yuCPnaZtYEqUv0J2aTVhazBw7Wa6q4y1tjmWegfcYB8Ltm3Waf16zEc+m9OhS373zDC593vuGLkvoUlR7cAx4VhHxtn/F4UEt4AenpottdR8pdzCMb8iLD4e8GYAcxT4y6/cym1s+hJeieo2jMyk5f0vs4jOq9Sxt83f7o+6AR9xUFwtUQQ9eJI3spad7/QPv5cl3HtQ04ryYNLqAf0P9AD80aPMZIRvc6BRyErhzL
*/