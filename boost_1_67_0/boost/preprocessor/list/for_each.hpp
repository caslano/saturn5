# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LIST_FOR_EACH_HPP
# define BOOST_PREPROCESSOR_LIST_FOR_EACH_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/for_each_i.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_FOR_EACH */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH(macro, data, list) BOOST_PP_LIST_FOR_EACH_I(BOOST_PP_LIST_FOR_EACH_O, (macro, data), list)
# else
#    define BOOST_PP_LIST_FOR_EACH(macro, data, list) BOOST_PP_LIST_FOR_EACH_X(macro, data, list)
#    define BOOST_PP_LIST_FOR_EACH_X(macro, data, list) BOOST_PP_LIST_FOR_EACH_I(BOOST_PP_LIST_FOR_EACH_O, (macro, data), list)
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH_O(r, md, i, elem) BOOST_PP_LIST_FOR_EACH_O_D(r, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md), elem)
# else
#    define BOOST_PP_LIST_FOR_EACH_O(r, md, i, elem) BOOST_PP_LIST_FOR_EACH_O_I(r, BOOST_PP_TUPLE_REM_2 md, elem)
#    define BOOST_PP_LIST_FOR_EACH_O_I(r, im, elem) BOOST_PP_LIST_FOR_EACH_O_D(r, im, elem)
# endif
#
# define BOOST_PP_LIST_FOR_EACH_O_D(r, m, d, elem) m(r, d, elem)
#
# /* BOOST_PP_LIST_FOR_EACH_R */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH_R(r, macro, data, list) BOOST_PP_LIST_FOR_EACH_I_R(r, BOOST_PP_LIST_FOR_EACH_O, (macro, data), list)
# else
#    define BOOST_PP_LIST_FOR_EACH_R(r, macro, data, list) BOOST_PP_LIST_FOR_EACH_R_X(r, macro, data, list)
#    define BOOST_PP_LIST_FOR_EACH_R_X(r, macro, data, list) BOOST_PP_LIST_FOR_EACH_I_R(r, BOOST_PP_LIST_FOR_EACH_O, (macro, data), list)
# endif
#
# endif

/* for_each.hpp
uxKSbnkh9Q6O3rfe6+WmygftZK91MWrf1+0ru4tzSp0d4zpzUIDq2qOvaFvju1fElp9eNX5O7jhxPMRd6uXa5tGf928fuk9SmCE2kh/We4mk185awZlK7EUsE5s3Oa+cKxVdMokW2croVs775++PG6Nt0fJ7yLjT7n6LvJjaddRboqvKv3kaZ1/uSBnfunmS/YsMOmR9ZfQe0wdL/Rmnod4pxQfHvpVYHXnOTDU16iAhMkxxMmVI0iYKI3XmaslB6M2p6cLOD3lv9R0f8Bfhm/f4+F3Mzv5ksmEzeOLhu1vfLr0uysrN+GR5C0++GVbezy38UKj2QpWPffFT5jyBvW4CRdO0P5smIAnRWz6qg3keCc6zu14lci0/OcLaqJBIZ72Q734ho/n6fsdxjkMD1Tg7Fx5qn5LX7LfKdKkt+ebCyVDvE3+y7LcPNb2vcWbZlPx5ebmv3LfUiyzsPK+jT+E+X1bKjOQLNdUsYpE84+1apPzq6NZ9+atyxYqc/bz6zi0GMdlFFOLjacc/yD+ej9q/kKLAcE5Ic2DhwSh2fD6iL+PRA03jaIawfoM5A/OK3gMamDSn96xuznShb7WOKY4KpiIF5Lm9PFWmegpe4qtF7l+J+I5+JFH/qUhBSU5szClDYVyMjLePP1JF49E6juV5XNfGdfMvYlnjo1/CLy3peCXNxExE3hyK9EvfR7WP2cuW9xjD5CXRpPWFD1ccPN97IK/JBRw/RaokftLYQON5DtebVP6AKbrJx9ddafqnvKfWbo7ri41Fa3scHBJ3F37hvmv+yHFBn72vAjTNh09oPLvcJPRcdB3irQ1RuiWY1ChwD7Hx891VEoHQdenG+O6rHw4FjwrXye+q+yr9YJelrtbGs3mWFyyWufeLXj9sOjLxUSweq8vPChW/n9cgF926PBDJjn3yXaT/tP/7QDPGmaihNxdJfbNp7xzpod10Dhc5Kc71szhde+8Z+tYMjZI9rmk0iG8lLDftnuK3Rj73PBeiqeYq7R3WfZkfwVtdnHf+MeOeyZvzFuqy5aXPho3dTl3sUHv4EUWTbhin4S/NXrMqjCWpbqGd3yI/T/4NVXirpeTzIfRgbdglpoPfDz8Q+X5XyKUax8M33zDgfSHLoCXi3pdJGkghoJ+pjRb3mPfp+wl59+UbjNLVeV/zqhNf7uqZOOC40FT1iYXh7aodOvyF2ZxvzXgQU4qte1DaUd+TXRxlQvSVvFiWnvIeYzKXVxndo86+yZVVwvxcFxowLa65h8QulHJ/3ryOwLT2i3M/0y+h070vdObJwRiFn7Mde3+8bixs8Jp5znXyS3mzi97IhDLPYet2um7/j3edxK4/t+jKe8YgdONnRzbL6EXtCKUjzrSNsufEswc6ldvX7J5/6Q/2QPhLiV+37yDrSi17nlwdsvj/ARyA4399xcrOzfk7dyBaLNRY9CuXqRdlS5m6lNiX35pUwlrUnIspghbqn1P9crZvA+hb547lVG+/bzkOhkm3bwAJTJ1SvuVUI/KgjF8frYcEf7lY5B08LJF4dqscCISvZxhvJt5oT1NY3nOk5w3P1Bea/eFmEZ/0rabZia5TpxEzvTp8o5Xb8G3QfBu8vpXy12+kimhJpHwbxHVgINyNWbdlbwOhedREwchIiCiCQuDw1QVsM8oxiymG9SvR+2RrODD0kRmIGOFlYlFRFanfcuw6HiStDqOozKz7WU5YaQEhe2e4rt+3UsCs3syZNCs+Cy4E7desNbP3rDVjZki2bg6ki7t8r13N4fbzDN9mC8Dq5nCj6GI8Y6hHLRhT9OdEtLyv6bX40M3ynoPbDsIdlQnaEDDNOiEzN3zh7PgNNcxjWyB63PEh4/ENZkZ1dRZixLLGf7XR4lqdwtRfa4Ah1PaVuBzUarEvI5JfODvYVGgcSfqOE593Gh3c5BK7C9FjDW6H3HEhzuwGj02rLaNyyoWRaVCF31QsFMgjBUnfS1YEdOKTvoGAtmZB+RrizR5AdDxNR8cToA4bFpQ3lEa2lvseYHMAJjm5Vf0zx7LyLOb1I5LVH6HudGOpo8nlN+NSDSV+TYrkNqfqHU7R8FMeyDnGJeXzETtHPM09OUHnfR2NFLr0ln8CnYs3lDp8roiTPsri+qRKoOVulY/kYFyskK/V7gXtGovFJGh4JH2vGUfC3d3dZmiQySr+PAFsOogGUQ0sDLQmV9J3CC32aDeWpAqLb0otP9d2U50/3mNvFp6AoFNgqK9xAMUWgDWY/ayHBXiwFRhGNGvu13ZzLzniCCJ8o3V+MyC6zm36RiISxaujZsGM+Xlkojr6nNRJXyYiNfo137Co7VWqoW4ieISDVh3x6HFJEDJUrNw3ojUNwxplxcjLVEmK9lS8x+FvpqzJpnEoy7xKIKCZoPHGu+3NqDDpOwb1fRH7cbw7z4w9Tr1qcgkFYyK0REdcVIraPmZ2hIIf+2GIwGP4ZO5WV+r6idzx3o8D2azqoexwsZ5XKcUwjLAWsqEOZNcwLXynmkuZPEoBlgsnLBSTZJlI0CzjHzaK0LO2Z4LdMrdcxUFvD4FA3n41xVU3uQPm3lM8tNn91i7TBiHjNrkvArmb9qC4Xt+fg63on7QXD0tiLyoLxG789F50nb0XM3xmu3vSHq1kRzFIi3PlPQ0LU84EBBAQH+9puEwrScDIiFm24oAwnMEO5A6ltpRYWo1QkjA7eSIUyTU2YUnLqXrXpA2k5Tl842EamhSgdMTrwZdwXhZyvyHanATyzFkgX7vqbwJdQBZymrb4vdNccuJH1PX4vaVELuW2aXeWpnP24dBoS4zJHSmc4Pv7QjRAl4SDxFKCAmRYD4qyaZm25F1CD2rLRakv5KQCl8h7xrqus0FtyU4k03VG5xJb3xK7FH/eGe9x3qj+SVM92hxTaQnqtLn6t4nOaKG1dyUTuNBRShxdq+RBksl53EJJKeulqDEXuBf3UJLiiW0lRjE/ttVO++henICrQ/pFR0zhUmOI6K5TjPxYVIfBhfRLArCxD1EfSgtx2XTOETCuLYqbibiQdXpzQTMk78sL+rWT+uVLBX86g5t1s+DoATqxWzrz4GNlPkWvVuem7rJHVgf17x82uzE1KxtMO1IbbUiL/500Ignljp8RvAPI1XrYusvJ5tMGHa8HzhoViN5rLlOndzWA0ffXXKbmxrbYJaXBokJnhfQ/88KBPeC8ap9b9QgVaMVV5RtJ+UbUXDOrKRmwiFX3r2lizMsucBQCIo6TJgV2zWq+JSWu008n6Ko14jK5uXksp2QTxIHBkPJVMGEbGln942kIOYmNHW/3a5UnEOjb2qAVIa/WV95TF3/TjjsAu6P74ZO1/o0U+zstk3JWs61CutjbOq5sYIXpqSG9+DfUM8dg2u74o/f1LScsaf3O7dCHiboqxsByfjZWc42kLOxyLho7JO/u9utvLRO3q85r/Prv6bvFO8glWtS8hljNIkn9Nf/7U5RTf1zRnf43EOUPbRs+wIIfpbFR7qjLoR2jF8gdTvq41EYJyvmNcqI6R1Bt6kbhpQnKRRfnmDemGwHDmdDOq4V6jj6Peq9VQoutJWIjMiXiCCV9y+nXHmJSXStoxzhmd+Pweln4Zunz3ZvX57vLeWfJWE+dVrDhHkyflnxU4kvpGzYS2n81PZ1OaJpCaoqyOyi7YydqIt46NHbApszciWJa59M4b2Jw3ppeqB2Kv1m306yu8yHE5Wqd2+k38QrFxB4RMbEH6LfZUJcTE4FTcCVIq1fT5VySONkcrW5DOmfvCSbu1OXGqzhL1om+xG65N+dM013clYqD8eMl8YwzWTAMv2RlRLMrxfGMW3HHMx71orBtKzU3M2zHjzvswE9O2LkVbRdlqK5dKGZUPr0RG/XV8DsOQedVFrLcYj0YV1899WA9YYH/JCj7lpX76mnlUwyRxJrPX+5rxBBYATTSGPmiHxAvgiKoX96dM3A7E6cLoOU5CO3HyBWhk0d3jdIghYICDXVtqulEcwRiHGB3irhx5/hmdKrkbqHNNR8eyXKeteNUGE35iGhqPSE21qPQiez0nRZmL4/z4eCPLKLOTWrCqMS3NlvYVBKUw343qlqOkUUMMVYG7jjLBZZzJvyjrhf6mylfqZ8Xlj+kl9LOl3c33aX5FpT7SpNNdQSMG+QnB5jMqH854xggGGmD5b/3/i6am3JOT1JooPyF8qbVyabVWpO/vKlR+11568qxHExfSbJ1peKJP18c7y6O+1YXJ1fUU4GI1Fz+PAG98SbuQjt3oR64U7jB8mutNA2N5a31Dt9KR+tqGjTREo2GWh8SueXdvnvjt6yXiAOz8WFaozWtpy2kHXr1Ta2pJvGy3HGRDcp562n3V3TTrx33OXUQN0FrGABL+jZHFvkFCMUa2BzSL3yR1kDvwyejdRCvu7UB+cmm5WJRmHa01dH1NFDVHYve5VSL40OFFEL9ZkxuvAcx2Nq8ZKy21vktt11V5m3JYyZXYhRJ3INFfivOumM0c6wTLq5o4czUfIvKCd5N9al2lzNhRO0VxIlUibk1Zx8VCmXnRsxGtD4iOaLLygeataaVIXjTUkXnAEbDt5yQjeFbTwNwyNv3QnZHxHRI/8LzjP4j8PjnRGXwQncNYXtXIS90I3F0y+WwiHBTuHbdiCSp5/N2LVs3xp5dc3AzAz96RR7KsdR7uv1lYfOU9qV8j/kZ7RVSyk5sTxrZNH/EHSFS8jGjqJihYeYpoUDas3NUIA2Y8uGIpxn9Vdj01RYfXi60TCCIz64gPZILyxFhqlVxNGDz6aa1FltpDSebRsqbdJhpDcNVpABHSP/FQcOono3d2SJ3sCtU1e39QMlJquPp/H7fOIy4NHW8eo7gWwMB2u7JOWINeXuVzammJ87a6V/hDXx1b7/v2YU06Z2+XqUxdBYuyfxNXAJ3gyOhk6+LqRSYAndBSfUJ09ZSHU/5njBxAqzr3N5edVb1bHRQqQiFY4skECY6bfh0mYa7vTkam6CZSbvwLdKTHD/p8tqlf+4F3DiqC7QR6ACqpZNdReL+2LaYzsW+Na1sfAGXAjDA8AT1poO8bOiIX6N6dsJIzMsGYVsdpjc1JsdqTDI9MRZSS6DsxWbML33SMEd9ydQBkjugkGCRM5m4YZe3A5rBVOKA2C+ACEWrM0xVMzMaREdXoo8CqWfwL7u4yxN6Tx9G7CIfKxD59bp/shwgTK/KVQrSTnjDM7MKwmUnbIgT3X25RCKkmg40p5r0ZlxOplKophkGXtigo7Tmeo6f0zOUP7Vn6BssQjhGwyMWmtUbQMib3WsUm3q9eaFZC0/ed0xv+5FhU6f26FMozvWynl6K3x49P31NbAuRkDJLHpvqiRiJ63W4BE01HW/26wUvmvRhEXGOVESnvxMP/xzb8OQpoSJq6tcthwUY6wYF9ZsHTHpRWQUOOKhXfxb0qtyB87wWd8FyfBvENeJGGNcX0zmH8lWh8zHiZ5CLdP3dKzjtJpGW8Yd1Ot7Ta0UqXy2jht+IXAvFpYOYMqzlw1aVHBI17uC87Fgu/WWubnLWzOSsd4isBQRj2qlTnCecbNTppvnQml1Jj9bsTvqdWnNp0u/SmsuSfrd2w4JkIzFXGW1KsrEwubKYMJSQuLuENgybKihlTv3AMToU9xRU0TZsDjvPza5T3MC0GTmI179/gHktGtk+Ydcz1jDfqUw1Ni02ih7zsEbmpkX67wcgUrxIWtO7U6f1RPyUTQqsIMo3X+hmNxanL3+8TjlPWB6UF0DvW6t85C4i+AtW0ndaeIGhfI5Gd3mBG8RwJa7N98c65kjpQsJykXxYRORrA1rfw2vga8L7m616xTveD1VHxViD9z/h/AHGn8lF7D3apfXc1r2+4pWTYxWvRNav7RqUd/fKT/adPFnxSufsZdRkOVW0b4BWwckx78AdBbHT6+90nekVaVfP7oAzwq+/Qsk74SiuLwcRRvXjA8R0yR2/oPhIVYWhDayqvkQpqL51gepa6ngxbpS2v6udvG2sqnphrtwBnwIrQnrip4bBlcDf9c/PmIFAqhN1NTtGgnp7pY3Pp1U/ZbWMyJw1+x/INVt29FcvUGYG/PHuKr8eqOTtfGP56bvf1AqQnGqw3dZdFT8zJ7nQpU4xu5me3VWAYUTWy7tfXln+fGTu2ofLz5w07D3/inS+PWPjLXmfS969beOE40V59zdXI7Q72Ug/tgJkcjwPx4HagO4m/HmDmhFFA13F7G/xdKES1Z8kxodju4pjpx2KHDvtVHJipwuyrhZP55quFs+Lnc5Tp3Y12mJvOGKn7NH82Gk7ssLfYsdRtVje7bdpL/QM5cZPOVTnvJe1F+Kn7OCvTs9Q3VwsN3bKeQc7Z4zHqgrFHrJjifeu2LthHiGmDWUP6N8lTBIIRUATQA97pX5JnelgKq/ftxLElVYLo1T2r5Bs3WAcwb3Aarnjx+zKlC1kw4/yjuAbg/VyxwaIXNiLg5xYZ4MFz7k40VYbh8Mx8QWrqfBG8Z304cZsnRUIi2qWE+MEX7WtYbnjKv7wyx2X0QfuOC7C7U3EbqxYj6zr5I4iikilFhi4FO9P4HcBRDxHEt3abFydyh2/5oHgHjoe3UAM6D4g5sQy8wZsXT9uwBJjhD5dqWcQm7Y1EESC7AeDAIEhSWH/uXyTRZP8D8Yzi1DWRX1g2mh1KuFkhriff+Hn1VgRTl+D1tSaeHSlTb2YKkwlyhj3ow6PCH9shrPNWDUZK5ZT7D7WPMWQmBJc4YfMvMqABJqI+KHzAevWdrljBgastovpWS+OzHCdmJfwQobuegZ7ofgWVzynGdL/KaGSdUJJCu6mhfQ+7A9Dg4b6847ZR7njXwHH1nBP2j4EBk8AE5If4+kdyBaRwh6oaReVsd1bwlA2TK7oDywhWbGOhr9cU8M9f7Wnb2AQNbBqgJgRv/H0M8gZYggoCwh6Zoqa59erjzBtstmfVSuwAHfj3U9/Xk7eyrAhrmLldLHq+GON5tswIZ2PDxeGKgxhhr75OWHU3g+J3PYXga+mpZqG6Uj9nUiJZ6YJK+22bdHh65rkxL9IfHn413jv+8HU9fl+UES7eqDIE0jdlR+Efum/cNFCosm+0qY1OOPXuNuSeepc+s5lO0DtxvyK7rb4qWLFUffqcXnPQMp9Q/pySnYhOX5NGeWYdkcuRZRiy7bRKKeeXaDnDbt2juPlZMhJJVzpqejEfacINBXGmlV8U46Fz0bvkLHweV9xNAhjdOEqrX7RuLdvkyf8rDjNTLennw8FAkF9/bOmfibR7QthYp9PjOELz5rgsKsygSK/6YtZZ10h0VraCle3jq9VQttq9xLeBQUS/TzzPPr9lxPdWITYFjrfNsK655s78asVIDJoLO4Uh+5OBEWWgLF4m145TJOawwVbspe42OOmGm0VHTVw02LRWPr3M4bxKB9QOaNcSs2PR102IaWEFvu/Iro/ZzthKYhj4d0D37lS1nxHKPqZOrlg0bi+jm7lIsiGUr7B8IEJQoCCfrOI/p1rcfYUmsHwQ1RtX2KWAQdCQqoYA+uOe/p64aQHC9Ifj7plpXxb1A0rLDkBn/gsXteLPxBcGb73PA1NU6q8Lt1mcT1PgesBLxXZIHy+a4NC9MGI6XKm0YTYg+0gaSZrxUwG2XfRaECwXERfn5iJgXB94LuIJYDSnum6uoq9hbqo1YqjdWHQqn5aTNC59Ln0536EGp0EggG+OG1/mdWn+Fu/xFQWle97kaF7nlPSoWZetQMZduFJC5G3pS05G69AaCNyx6OMsIXa0YW0+A9Wt2bkB3uSTRlYNFwHNcjaVAqKYumpXZ7YRxcqjs7pS+q8fXe8Z2quyXv4nQ12VIc2Os8lHEbEGiKJGGiomqM+5u1Trha13Cn/z2upnp2JwCycIOgqwmpCkNf/bDyiICd2YxKd+neIW4ks3IU4XVvI/loLEEjaxGMLUn+d89fftnmyIdexSSEp/zuTkkrGJodKmx6aFCr+0sOTQoX3TM7pGfVIEyH3sclpZd+cXMuCVqqlerbrNoxgKiTkLv235TwCxOkHy2EXi0/qP37QxzdmUO0isP8H9J3c7DSD+/4DwY0uK2ude9XMbF7q5enJIc9XJofKXiycFFpwVqjUMTlU/MFEuUghQQm16nMnerrE7E6dc3Jf65zZftKn1UfKU+d+NVt9nZP2CnUNVVbPlhgsxxnX6P7wSzhNi8ZZ0Nf+Wa3SWYQtNO7fj6czQpFZAfZ2d7gWb2Wo05ASiuSZkd7eqCs+YAzB0Fw4Mi9CNVFn5Ez6c/DQ6QqjtbBuvsJRgJD3RWWht7fdTUwPOmdrNvxukdeJvINWXifnVV2Rj1cOgXanMpeJ3PRVthNVaa5IPj8M4jeaS62YXH4SBDHAN3/+AXbwH3+A4yCkH8HvSPlJ2j1+/Xnqdgh3O/p3rrZJKeVKe1D/d4qDAAGZD8y3STudXGn8wILUioGbAnyjzk6uQtRAodWknQPYXMJs9LqLoJynupKzEadXXAQt5EsR2SIsHS3Vl8ecptsu0Pdyxx150FTXaoWRPhNDsNFv10aMI/KTI/G+PGKIIi5ijhDJrunqUjV1PccdL7+djJYlfYtxodjONCiRuMnWRcxXaE2LUott1XPkjjE6HarXLFRlPnXG6urtcuJlsDl7Gsq0gfgb9mSTG79183HoJZsWJn26erOWq91YnFpmy082OYXRfbynsdlQw/HufL++4wTBNDfsYRHtao7qElHrIbhW2znqrhPs3ibigC5CUQwDdDBtg08iDLSGsmTrumRrY7J1WbKVEPPKfh+OR6lHzyvLq7F1+r4m33eNIBGTrQuMIgw+Fv2aUwuWaDeWEjGYXFGSbDpxZ4HWQGxMckVV0leXnqo1FDoI5dYkffXybt/XcJ2BR1salfWNymcb5cQPKMAevbWmxVSg/HkY3FDhh0+eoo7IT/Y4fCXJhpKUc0rStzJ9D+US1fvqkBHyOWq1tYoylh+iTCd/9/IbyWAJ1I6alqU/bzoHry/vSdVXUW4DPWltlJ/sp041lKac16bLRA999VaO1hpKhrPDa0/+kWaVhhZtJA5Di9aXR2s06qKvitYeJnm5UQSfg6CqWQoH+Sk77zPUGvh3gFi1nSjE5TBZWUeHowcWIguV3OSa0uSaEs3XeHIw6SvUfMvwW4yOUDvsx9CPUfpW+nk=
*/