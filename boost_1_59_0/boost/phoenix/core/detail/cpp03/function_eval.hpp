#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/core/detail/cpp03/preprocessed/function_eval.hpp>

#else

#if !BOOST_PHOENIX_IS_ITERATING

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/function_eval_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif
/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

        #define PHOENIX_GET_ARG(z, n, data)                                     \
            typedef                                                             \
                typename boost::add_reference<                                  \
                    typename boost::add_const<                                  \
                        typename boost::result_of<                              \
                            boost::phoenix::evaluator(                          \
                                BOOST_PP_CAT(A, n)                              \
                              , Context                                         \
                            )                                                   \
                        >::type                                                 \
                    >::type                                                     \
                >::type                                                         \
                BOOST_PP_CAT(a, n);

        #define PHOENIX_EVAL_ARG(z, n, data)                                    \
            help_rvalue_deduction(boost::phoenix::eval(BOOST_PP_CAT(a, n), ctx))
        
        #define M0(z, n, data)                                     \
            typename proto::detail::uncvref<BOOST_PP_CAT(a, n)>::type

        #define BOOST_PHOENIX_ITERATION_PARAMS                                  \
            (3, (1, BOOST_PP_DEC(BOOST_PHOENIX_ACTOR_LIMIT),                    \
            <boost/phoenix/core/detail/cpp03/function_eval.hpp>))
#include BOOST_PHOENIX_ITERATE()

        #undef PHOENIX_GET_ARG
        #undef PHOENIX_EVAL_ARG
        #undef M0

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#else
            template <
                typename This
              , typename F
              , BOOST_PHOENIX_typename_A
              , typename Context
            >
            struct result<This(F, BOOST_PHOENIX_A, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;

                BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, PHOENIX_GET_ARG, _)

                typedef typename
                    boost::result_of<fn(BOOST_PHOENIX_a)>::type
                    type;
            };

            template <typename F, BOOST_PHOENIX_typename_A, typename Context>
            typename result<
                function_eval(
                    F const &
                  , BOOST_PHOENIX_A_ref
                  , Context const &
                )
            >::type
            operator()(F const & f, BOOST_PHOENIX_A_ref_a, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, PHOENIX_EVAL_ARG, _));
            }

            template <typename F, BOOST_PHOENIX_typename_A, typename Context>
            typename result<
                function_eval(
                    F &
                  , BOOST_PHOENIX_A_ref
                  , Context const &
                )
            >::type
            operator()(F & f, BOOST_PHOENIX_A_ref_a, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, PHOENIX_EVAL_ARG, _));
            }
#endif

#endif

/* function_eval.hpp
G6syJTudPltiZ03kfJVBspvYA1T1/L9O6BJ6zX9kijUCLcCLo1IRiuWESwkiZLCVhkQJHqM5CZZki0MNqRIJlaB19T8L1+1CpltKGwhPwxdX+4u+eAdNWsdraK3hI060MdTUQGhlfB6OyyC7YJVVVRja2NjLa/vAGItphloebYCdzOpvmp/pIqajyUfiOy6n0H4XH27VyNiCepF4leXbSBwb2A/MPr6M//Qrs5trCk/gi49lutuiNWrw4BreeOs00qzlhXac7yNTlQpMgpUg3GhH+zyK/BY9tl7KQtNzj55HT0thnYh0STG1wvUpqVbIpaa2ogqUzEwWyyND6IbL1Iiu5xyTkQgb7oagMalwomWMhYFD1cP2A4O5+PAx0N4yp3W0skpBErrfIc39bWmjxxclaRnR4/p9R80SZGybUrR4M3Oy8B8GTbQY6LKE0lFLNvnRGMhCEF9QiJ1fPiuBxC74gaWgerUOFquLv6YszGv2jUQJ0ODi/qXHCtWlS13960fFN68W7HcZk/Lzc4xJAijPMu1Jh5e8lxTZMYPahVkAFZty2N6P1vyo12YqlgLPFgdbSaOu4RiX9vQAeFygxzq6f6dtBnBgznGL1emeEvOMTaWpET2Pt5ZJQ0chPiOYc1kN8CBQWLC7Y7eqJfj6aoHh4eHJGg2Vpsx1lY+KiJA4ZBX5EdnGlK7i5dTBOz2p0SnCjYoI9BpBrORquT9ZWCj2RLJxJZdI+f3MpkfNJ6pCq3Ljatr+3uLjGHxC6xYBD9/t69PhailhicjNyGXtGlJ4vb3AGa79rtPxyJelVDZ+dJi3m8xYFwFM6mLw9n0521hZ0LXYromcZ+XwGagXDTbPRqBKOz/lVjinf6tHjfJPjPDHhEKQ4K1PMgVYLVWjc0dhcBFrEp8RvN3khl4kbYNOSOTYsnkrsMR0q0BCQ0Lbwxg4v7y83aA37/qS9Ro+R7rDwOFFce3rYm4WKp4IacCNuRgdHqtcjRE/VcjXB3orVxGZiEBDHKuXU1PU7fmcHprJYdg597Jvzi3iHQ6+M53SP93sLtDNZ9f+u7CNwFg+nEcsc3DYVAHZy5zSmtk+lsgG9OOURTgUXNwmssBUaD8XTRCwJZyoxK1CpkWsoDyx/VOOeWHBzNWSSIvnSxSM9uQu5T/xkfIj6B0TphH78jELH3zQsHL3WRdWSobhZRz9lorx34VWwzkBN2G7OpcJCJHIVqz1Wo/LjdSOG7aXqofO8FltyIxugLv2iH1QXFTi1JmX42hM2Ew12+cUpwiApQPP6Dxr1VqjFa1tZiC6VEsWGmm403Uizs77RfXj1eiB3aj0ILtwanDobivuJE8wfK6429wXHW/FS1r2979FchNCc4zKu/nQD3nZ11FAIxAoouYSuL0f0YBeOWdJbNL4jVizwznHt0GpUsHZeOF24QpILLi9pNxAVNSy2C0enNeSsiO+ycNYEYTY/ePGr0rsJ2zXY0jHzxS6QJUqy3LYKpbC77elD3ygowPz6sg57PojEgiBarwkdiKpm3siumBjY7XE8VilynYgU4m6r1HDsx/bxQbnaHvqujBfvHiyfIbxd5Mvxs5GnNjOr6T+DKbQCYYIt8JC3B4WkS2uaJ7x+SQgF/AW3b160yDKSJxomLHKVKjskfk/fNxTjCjRti7gdvdqG6ttW6tt27Zt27Zt27Zt27Z9e+/cm5zzcpP5pf456rGSmmM8VAlnB4DE8czwWevu8m8fTD23sbOcvIDW4BNC22Kyit+tz5nFllnHdxXDi0KlxnV+lQwAOLuxMALlJ4iq9JxzYL+qiIVeZcEHxcf8eL5k/3xYLvoaOi98dtmK4AAt0cFxWAWPZHIn6z1YL4a3qVv6Z0W/a1VkhiyULbrcM0iCDsAb8vFThKrSnKTTAQ3nh+GHdYWbDtNpbqS/PkdKnJ9r65oKXk1Ce1ssXvdXobHFzEs0QzhX+SWvoJ3JiBRt8btnm3F+e0GdoRIY0hXrFKRD8KPF5fHLyw69e9eXdanL3I4hp2VuF3IAWkv4eAQyZyzA55i07vCcupczVpd/mGnRtLWED+7dJwPluVZrLMVZ/1hYVBdxyWefvc4F4ytOB532xk/6fUll8P7lhjQWDA+fr8tY9jKEskjYB/5byNO0e9nEV/agC3ozXMyatJNwL8FViDJp2HGEs1lL6qkJvTHN8BAcIoLybxFaI7R2Km5ZRmjzU/HiUjsHFkpahjGqQsjJMNV+PlM0I0ZKxUUqrLFi/Hbp3bPLRHwwZDvy3T7BoavQF5LsvXrCgnIABiz50+iRfmQMbkoV+egbm7SGXgLYnQb9kraZXUAcY4cQjAg8lO4IlH7HAnzB35C6qB/lH5eW93CoKzdt++2XyjuQheAmXmrXxhK3+QHUk8D9aRDa7CiPeecu68yRN8duYNedbYrI3H19lX9+UXF7j1Qkweb9pTs92Rp7l0x4ONFnmk2TSsBwePWxWb3vFMa+XPZ2AIoBaLxB9DcZKFKNzzyolqSa00wg5dBuCQiqc86ZRdXrcTaP94CSrQlxA3bWLKlEjxu5r/zf039pwIBXioFy415hCD8vW7yxeNVTrykqd8xQyVp35ZTaTkMV1a5LKDXt+0oqnefhKv8tPu0MVPC2/ExVFAc1boD62W5toFgp72ZPuwXHCsYt22C/pp/hoZRC2miQwustlZVNZueqln2ItGvYNeYSl1zqbXfRI30qJ4P34xlLANywNxAj/iEA+an6JrU1jrKCXG0C8rBkaWNUNFO9sXj7zObE7MHi0WdWq+DozVee1IK5ipbPk+qm2Qjp9tspcYuWFizoWzbX5Hl0dwzXSRQz0fjQp5OW+U5OGppz4MakeY45/fIVZkw6IRSWO4iCHUIvUZML6IXNloUMik+vUap+RGnYH/aO0PjLfPWh1H3bfmcqE/Ng7rq2DkVwKlicSnLbMxJW8Y2NDm03dHR7j4irm/wmWExEj/OG+/i91LGk4v7zU/DyA/r91ehRiPOfb3iuslwUkafaazwAxjBAiEwEE6nkxuTC4okCxBFjMwcAEEGIwuKJTfjiDQP56uPjiPriqOwg+vHoHER6OlbWPqq9nltmeDy8Tqqr1be4tpSWtLS+qq9PVGykWEc/8G4COuHuuf9f+PbxfykL+HneOgdQWVhSOQ0q3Ro74iBPFqPit5aWYzyUVuTsytuIs1ds1rpJNRatirpz49mSmOjIqNf2FEh5xW5Afp4KVJux8wZz7++/grupnhGGh+oKdLEweuLGyOGT35UTK6ntfJ2Tbp6FVOJYLT1kJDZSR1TrZjA0mWbaqHOxZ7ls8GCfPOpqEb0vB4QSBpIEfKFVEwNyYfVM9tMLBfmDRWoIYj+I4EG1dpk42WlYKsRHG1Y7pu/y5EMC+XpMPHVA5cFjZF8wT5Y31Yt6o0PakMZ70v5kW1HJvAzpczXC1WIHqVbCOB00WqcdRtNGW32Ve/6hH6J+pVp9GnWJmegomFGM7PFUmKmOdd1lQXAIT62E5QHQ92Ev9GJeYF53Tt0fdONetGoXkB2MBiRxmneNhc3Ci1UR9ucYVBAoWxUTns+e6rjTNEuijckeCz8QAKnW9Q/9bLB9lVM4w7YLKlzVOOyMN20KSelR+rBXIIQfgGNl5foH7n2G4wSxI6AfV2YbtfIM4/tSYZkC0cQ68w1M5RB2GWBBFvlKeAkwgjvcQP4gv/g2oC86p/g3wDC5kVQDjAriDuWtO61DSYH5d3MpQLrIG122nN73H5O5YoF2J9zkMOGfpyt1zQgITd0A39y227R+KKU8JSVjbRCf92sLrTlGAZHh8YFKX1Wix7NuFjRbjNUhhy5sArBLoUB0rkrwbF0VhVGxEFVhO1JO50Mxp2tWiM6+0MhEk5m3aSGywiP17+bvcyQv7nL5L32sOwzvs062nhe/0jC+8+gRmSO4bSUoH5RJxh/d5zd7lTRZtQnkksRryAD9bRVrkJNNc5wwphw252gr+vo0vVrbY0BKVDG0w+dAXw31/Lo+pqkIjeACGe1zNUfU09SEvytLxEu8jN1TGc4FQXps1B9d0Ip2OmEONYG7J9r+U3Kc1edXQSDzJhDhwIyBdH/5KQLkF113tiaEbbRj/vIrvUo0xpt53imdc42y77XE6xsMJFQHJSqStbH5nODNk6ekZlAJYD/CHKFJbhuR8SwcUi7A7D9F0a+OkbfVyDmMPd3hMcs8kLoUdSOzOoT31QI95EupQUV9icel7ueYha3zXD/+XcHkagw9VUognKgkY5edqHBtXhSNJOSrCrn3HpJ/gLZCAjMKwRMTSAWQtyyUFY3Kid8V4AWb7fNnBFbnlcXoCfQMj8y6pr4iHIfoKfXjkALZHhiA+lfX9+Ybpl7oMbNqcsUMV51KvWI/ohezFOdYZEahXoPTgydWkCfKA5d3eQc35KlHwURUcvI+lu68AzbwL3zWHS6YiwASYQt/q4Jvc7HWEKJfSmwk+zU+kKuvMnrcTJgI9XrDRMKQeEoa+VTm9fQjlkQMSxFAl/7W1/GNwhd7P7PkejjHW1eci99Jg7yM6u29JHKg3CSSnZ0xkAtVR8lsEQx6oDInk8Yh5uu029HOJr89eAuh6WCwsthSIhDr9cw4+3E+TMKfNUDIl9EffCi7uq/gkt4p+1ZOHNxk+NjIgI5SMiuFS/FNk/cw80CehuOJfqGWbt49IpbSOSX1Ys1ZivejK3uM1qVsxbJ02iQi+8/4gVBGT9IqlpikWvPbP1d2B46R1YesoZOJi9THc3w+jQ+RPIELTo1ynvB32IEeXP1xnlA7PXFLcwfIBCPRb8N6v5xv7kvd+0PpG/s5CUfdVSsmDoonSAox7GTgs55APHBIjcIqwbMbaSV0XHWjqJlrTuo59ysfj0tjSW4AQ0PjbICl4iQFqnGyxdqtuw6AzzzU+u8pF9mo00JpBoH17n/1a3g7L17k4DqSKtSnpS+sx+ppGoabMw/2z5krbl1o9pzN5UhdB9uM/4JGmyvhdo9yClJIQbZBNb07e5tVMyIQa9RwiiCpTyHYq9vCcf7+jR+Sdqxk1aOXE5jpz2WAmck9NOUOScAFeMtf4twaMUiL1Lo8oYBbmppCs+bg4Gg5jmlZWfnIxMJuOqIWy0Hq16fvgGcty5wH21VwTnZoH7zaEbyfosm5xlg5MFUhVrVl1swNXd/sLhx1pOjUXPdYwzFLRzrcDCn5ckqHf4VsEh5hLO6wDFU5L1mXZG8HcwWdIaQtCs7tOTF9uyoUbldpxQ0DyyekKZRLDWbx69Uw+sLKJwgVwiiDhZYGHewmbGwZT3EXYcp4OSkdh82yPtFBqLEI3RSoQqZ34nVJKB51K0tuHEvijkxUVnIKjYhgheThA6d1gkp9kNmA8plSaK7n1Z/okjobyi4+C9voSJXNbkOH03B26+XYwZv8PD40ofcEzSDTRhV9INh2ihzrq9bXhzjbJ7/kQ1unXU6l2kiA73O+RWMlniCYUTrA+DLcBKb1/p69DjtBdGM809nY3PQ0OIqFhD+02HErJyLM5zeJXaxT70TQ8ggt7Xb2LSGb8cPEVq08fAaxSYQ3/XPHBvVCAn+mTm4kUpKYMaVRvxn8CvLGWFB0FUUGsVKJrD4AToZ+IYvzam1SbU84s8MEc8YW5WOQJ6P2va7tc3XHVk7vbUbadpHuzwlzjFpS8rhwTWDeM1cYb3KfKfnRtAjn8yw9Eb0L1RUUFMTYZaqKR0Aq/ehvz5Gaa5Atz2hoE79+TtcgSAuG2hoDflsbSJTQpzSUBII8qMD4giAn45ZUtR4nJ7BTugsBtLPQZZbUWhNcHEfjMe1So7eER3oL4zV1t8vWiHEiBgexK4zesZuwJ+ZlhKxMXMDHlenN3W9vF2Xw1YWo8VZxOpUXt8X2JaLMriIzMbOJe0Fa0LN1OK9VPV7MKCuslOHTrTlLa/XqXSKiqamgwEhLWaSZLK5vD2ruscJYZTRRfrfOp1h0JN/Uv7zxjOulJB2DiyIi1a/2V0e3Mp7gmSBMgHkjFHiiQMH5kh7jAhvrHX3M5eH9ztWwcOVOjtnGOkSziOwIW2sYC4GtY5oPGWwqxzDZI8xmmUKcZV9xecnOu/4H9kzgNKUsuIGVb7w4szCdgffZ+B5qyW9H4biI/ClKzcvoWE1abZcNhdAlewvuXlhvL3ps3IYxe3zS6Ivt0+MwSu/5b3U0IrlYSVKqSFdK2BWu2Cm4Q3I/eL2lkxm5CrSS3V+Cl7FKHSIh+FpRzL8Yb0SRazq4uXxJ5HXFlglpafIL2m6BUd6D0t4vrtO2VTIYLqgkH5A9H0NCHnZuCjwXKMgmql/9F4upD4WmVr1y/GvdUjRRP+NlW2PK//hQO8jAhFgqN0HpMJGJW80owYbO7iY2q0+6fRrjBRD9rPhDdEgGAwn2+907Y8zKbZ4rFZG//pnKON+7auqFy8IM3kTZJ73ufRAjtxg/U7eqlFNQHLdsZXgMZRqX38DO4bz1lABFdyjF+z7L5AG5RMgBf53WCV5mIHxv8DC+cau8q8uCND7SYASnV3K39veWp+xPxDisPwlXT5bIBkRJHKyxoKEtvtgvZB1duBDmDl2G7XSq2eTi7Oh2Fg5GbSglXUa+uJWVvwRUbxaA+5/IN2zb+6SIHkW+ABpYr2U8srsEALILDz9UjAEJCwtHsbIj8I5SBC+S9FNbZ/NXchIQQeUOjNT7Ie/rp2NmdaoSgxyGzo2efM1e0eXLCOikJ1ZeL+VsCilTwyZCxrEBQ9uOoXui9xTQcbTPzEuWdZN+OhXrYYhYGOso+UNO2G6Rureb8FLQI7funHcVnP5s69tbfWdQ1sXl7SW8UoGBEyvTINOdV5OK4TYMy6gXE4n4E1TsJ61AezFEzkfA5vGE9C7YuDK7cVAZO5FBKuzSWjhszuTTqbOuLDz8C+jTlXshRr+tHEaG6hBXX3WJ1smafvXwgkrg/PPHyHjlUqWjJ+P7Ewt9yYdzlaeLEtNTqFNlRrBWeRohZ+K9KeYWkMVyNHRYmLiTPk9kKZjOetGKEysMuz88p2szpZY1d5+tvfY2G1TZ3B52bMpjeSk1vg1nD18yDxUUhYpSzhP9ythPPDo5gf1E9NmELh9nPf64EBpFkKs8Cnu62+t5sFf3HozBwCMvK0WO33Cnoq3mxXfuzOpnKMXh1D3YVhclnC52fGwccjspLo5+pS+GO9K4pimb06pM3/1dFC1k7BYwVwN5Kuf8tTpX142ZgQGxpqjoqNUFxtbF5ceVZyh3+yYo6lA1k14uNMOXDI3mG8Gu2+/GhOb13B6wb1us9hTyUs0+h/jlwx45fq7tCpiLMpKsOjYq9y9Bh4LsLPP67dV4MFfR3DqMvg4putopofQTWhtnps54Yj5/3qiAp/5+Ky0tAdmqdYNT8qlseTnCZQwyJjo6lewwwPsEG2vzKReOvrUHQVd98fb2QZ1cfWSAo2kJLdsVRlcUKYzmFhsFBCVKgCfQcupneTwiR2n2NoiIDqcCQA2dtr4gpS4ANCvSYzfVHTaiHPsIXykUboGJnY6IM1QoBlkV0PbkZBeQ/GdAg/eaBEKa8sM3/d49uBmcm+6e8JaD86Yik19k1S2cVHntYFB5TKMX+4ciOzg+8Qsm9RPSzfDqet27AVcK
*/