
#if !BOOST_PHOENIX_IS_ITERATING

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/operator/detail/cpp03/preprocessed/mem_fun_ptr_eval_result_of.hpp>

#else

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/mem_fun_ptr_eval_result_of_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_MEM_FUN_PTR_EVAL_RESULT_OF_CHILD(Z, N, D)                 \
            typedef                                                             \
                typename                                                        \
                evaluator::impl<                                                \
                    BOOST_PP_CAT(A, N)                                          \
                  , Context                                                     \
                  , proto::empty_env                                            \
                >::result_type                                                  \
                BOOST_PP_CAT(child, N);                                         \
        /**/

        #define BOOST_PHOENIX_ITERATION_PARAMS                                  \
            (3, (2, BOOST_PHOENIX_LIMIT,                                        \
                 <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_eval_result_of.hpp>))
        #include BOOST_PHOENIX_ITERATE()

#undef BOOST_PHOENIX_MEM_FUN_PTR_EVAL_RESULT_OF_CHILD

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else // BOOST_PHOENIX_ITERATE

        template <typename Context, BOOST_PHOENIX_typename_A>
        struct mem_fun_ptr_eval<Context, BOOST_PHOENIX_A>
        {
            BOOST_PP_REPEAT(
                BOOST_PHOENIX_ITERATION
              , BOOST_PHOENIX_MEM_FUN_PTR_EVAL_RESULT_OF_CHILD
              , _
            )

            typedef
                typename boost::result_of<
                    child1(
                        BOOST_PP_ENUM_SHIFTED_PARAMS(
                            BOOST_PHOENIX_ITERATION
                          , child
                        )
                    )
                >::type
                type;
        };

#endif

/* mem_fun_ptr_eval_result_of.hpp
x0Ibf1+5/EZh92zvZpgI3dGA4dB7qUJIaHXWJPL1eDFSuTuOOYmUZhpgbEWd3+8tBz/j8IsPfmIdEJMje9p4FwY8oTgBkw7YW372Ur9OkfZ6HgAWbBhmFvh/LyYK9JL6/3pVHsuTAqncHdvbANOvfVfd9gjvnCM/qg/MyQVoXj1zP3wWr7wF0Q9Pi8I1Rhw5v8LQD3wNgYCDQUfCB/jS5iN7MzBh3zNFK2IXMY5AZWcYA51I6gD3mUovrnB+1B9KLyntevG2NHeXYdviXNm8NrY7xQOShbq7B9c2nQtPLQH8lYa3yPUv9hrV9RqGDQN79zYT3vbuemiNM+jLRH8e4c4xlmmqnw0+Q74JRDE6cvA7IuQp+Ajdwg5T0u+j5WG94DXwp+79CnPAGFZFV1fUKdlJgmlGRk3hVEBGOtj9DYZtfVA0ek/E0Zy1tkrYiKsj9jSeG35zYgdZ7dfr9fWa0VvTB4NU22batRoeQfpXID8udeULK8fsCIyJ5yXD18ZftPt12zRerdJeJMSvT8v1Ngzwmt2J/l+kqWxPA77/96XvS11fG1VzHPCjkpaFICpaDBiH3HlNhpUMSSbN4iNamXljYyjFLAt1cTzdbs9hMs7OytJkXEJDAz0yuJ11TSeA3keiodmFroTRxNR2tJionnHkROp0lI7mcv+6/XnjacNZwKuXG46390Dy2nn6veuYj/L4k09++7lrJqruVmCYXDrVYKvLM9CRj2B7QYcos0p4n0mXtMqTmxbEiF1K4TO3K2MaW8Fyj87SNLDYAKHpSWzy6tIEYOTzXr548bLza8tlGdT1V3t6+dqN/3jRILvnI8j3vYwO7XRfQbXCclHzmjE4P1kkiZay9ybbQdK1J6UrQ749pzGykT6y2mn6eLQB8QA5AhD7U4tg8djqk1j7rjN+m1Qkjsd10vXgPnZD2pM/1zaZO7Xz6tLzLXrlwYMXGG/BNaWO2kE5RSy4TVqxutAL65s+G6bL5v2mWsAgu5bbo3mSRp5xfN0q3xwbX9PDoveuQODFcLvVO8uDNcWf2nbJbNHLK/vePlate7eu77LM42K0hz8QqDPoPECuxYvVCq+13NZjMUeSbwFT34yb590Iq//LeqCuUtzlkk6qVaXA5Pxr8oUfMrkqxKqPz9AeS9Cul6gdNgW/AA9Cwu3ugya9zHN/Wk5SUtEcOtjkPTucmYaD44duCFRGbT4Lg4DATM17qSw8j4Dx0SSOnW7W3j10jaRA5CzoWjgvmn4seuZUbegU7pWTHHbNmBbeySmx4rws8jcwyq2Y7sFaCJySXC7bp9ff+xAntM1J8ZBjuMdfZjpqI3zTLGkrNCPpL97MQ2i0aV1ooPnmWqCPDOdPaU0UX7IkKHn4pl0ZfCuq8MKj6c2gZOVfOcMgLJFrvjcDOOOt8lNe8t39Rv/UFUfcu73GYvilxj67r9e9KzgIuFxU4kTDre8LdY1fFwTe8+b0akOZSeULqZw/9AA4oYXGEvbB6Npic25G3k/BMDmAbF2a8waaznNHSvXR9y5KtwVxn37H4gd06SFb+kOk8WhrtGKSpn16tLRCx6EzDNbmbYf0T/kHXPh9VWpKYvcmDnsW1sqc/dy2emHIHqYB6o9ARF2PgDDc9+6WmSUeJ+KPhOPBbE1X0N+B87r6ET2A7YHaHODtDvJV/1YYZmHvHo7EuaKEPUcxmORgknrZG/v66p3SazVV+NFVo70Q+3DYvei8fZSp0hTmnXjzeM7bAllO7QPqsyzTsbQKPovdrm8cBqvI7JHP4rj7cdFutGSl0rG28pstHqEgEN70Js8g68VHvssPH2+lDv5C/rYuZVt8XzmEU+mJdLGmB/4wBLBbsu2DZa6NZNDWDcXM/Q2885MbCGzwv7az0dGO7BW4Zfm4jDikoulBFtV/QYezzwi502cYam8NeskvYqsX1/LXJ6J/fCqsaPgax/eAhk7XBhtlPz54NNoT4kx5zujTiNP7eTjY5t9f5rhN97p69+LuUNnzDWLUiml2O440Jqw+8tnPv3+q7XkZR6Ppwi27llZcWJdOTaDjG/L2rWiXxgcfQi5fjLF41uy9n/vPmejh5xVyUNeTJeBtVCCl1rGE4PvVPlspdFIqpL+3Uip6CHMq5NKfGxdyKG4e71GPgd1ZOT19VxdKxbEPqIL7XBlyqK1/R7/MwD4d3awMeYMd843+LY65/3fzmKojqjkd8swmEec0D/L4PLvEZeH67emCyTKfkDtHKaFAqglTRX4hzb89HVG+LTm+rkSP2mjN6kD7evC1Mbh3CMRwAR4A6ScE2BIeZh2kSjlJC7SL/qUTskNxmsCVX7OU8+ye0UyOq6QrifRZEu/BJdeHfZX6q27tyQs0zap7FqYmo0xNQsMbi0A8GGJ3MiLickzOpjoQIaasXbH2XNf4/UrD9cLK5RGPT3tgQAwDz/UCx6Xxt18IyS/2sNR7/RNHivq1J8pHQKgH6647/jrEh+HAm3gb/hVERJuGd4jjm+VXEul3iPoZOVv3/VNKoWMG3jdqFvDdd6IRe8aD2leDxnf1h296+PqzG/x/rQn2f7CaxHThL+P/SvF5+OP/ououw+IGGkZhl2ItTnEvxaG4e4ECxYs7FHdd3J3i7u7u7u6yuMPii7vrt32e95zzfj/uyZCdzGSS7MiVTXgtmNJF+P8HiYPVXXGdLUGdy3Kg7zcTwv8Nxo85P3vWTXG+swW9muDB8/VxZafZfTi9+7TzQadNBxcestQjvEAZWyfs0wElVLFuuMRcipHsIOu1k4ZzBlzCWaHeXbygUrnINUQ+hpsQG/Fdkwyy2jBnusZdjsue2ny+w/D0NlEUEHpMvtaR4SoiSuacQAidLDH3iu3e0D3j/9aeC6jtMln+uSDSPAh2mFReZD/wKLPpY2q0WsVOFpznVryeh+tD5gTxoMjZ/WlFdDMNPcxckHNwz0mJnBKoCJG8ua0YrIPzJ4XNjEDYq7edcDRMv+Mzv/hR29rU+fdYtJ4KL+DhajRJ291ILmx3fuptSUNsDB+IjxQksbuMdG2678qFlRkxUFXzsOCy8IdJmhg4uNVy0MrYelbBsv3lEPNXqsmQy1yMrLgD47cIveD98HMJBwoRvrJjvXATZLid5WMi68wKYglpFnYBCz4LJlzgxi++MoNKzyEfYsEpZsKRCjdpoFmKdATwX5mDdZxfgEfJFmxeEYNNKfhZ7JnsuOEmNv12/ijibkrmH7zhC+BxVfT4eLeBaw/lE/54kC3QZ3V45h0qDu9ey3v+NFNuL7N1JsmkUVHdu2s8e/3bY6jMDC3iVzSXpc4sdlykxZtmX5tv/FuBcDXbe3OI0j3nJo5nY/+qlhkRRYhTmJu5wRM4Qvw/RWOAV37tR3zdDr+oZfQTI1NnZ4/swN+p+3dALy0VoE7j/9p4HgbUkTw9lF9CiudLe/mX+zqO9r0Knl2IA4LW/Avcr2gTqww/yIcWj8gKYzZ//h2FcBMqzi7fy5P43neoKra5Slmk/4xDtBBtMZWxO/TUviBRegRSC38lqW37BPcb25DUTgiN/BOBxEdqXHlodBwF2BolzJICBHVfzAOEY4UfWGjfsnJVBMKULtWxJb8PCKOroYV/JPWJkRt+v75rTzocOa5hXbeJ/TTtXDop7Qxyfp6873QHpZi9qrE5ZL7C6oB+gNWRkZEzTG5vkdnY2M6y+VZzA9UfzM2fn57g8PHxZXIzK4bOjY4zqAju7+v/u875R6bVGt8T666epyc0MnIEZYf11Lg16JIE+ag06ZXkgvXVKxG8xEUDnLSwftW49hgFnI52kttb6b0tfgPa85czvcOst3rEWmtzw2YW5paZFB8E1ylp2UaGeo8XxFqAFEduEeP5C3mtst6oEzaG805cFWmOC8jdPIU/dsTdYZ6OSea1V6TcaE8SrnQZ4leQOAombIwX7aqyUDOTRWyzDk7/DcdM5XbmoPe2gaJ3uVd289pXW+HL4UzA0smZqhAvvt2Xo7YdIzZ/24JC0HIO1yh/DjV9Bc+xH5PUc8PuWGsXGOsqfSHSm7tCy3MKHi0Z8q5SAL3vzvi8UlEDboVpGWmzqe7TC1LcI6euoppm9tfpDi4mOQ+PrQ4djvpCHO5sUBVcL9mfjEEKrZ1gZX1ena93VZf9HFFfG9/09Mv0D45e3C+aifNDYwn6USZIG3kjlho/99uLoWviBDN7/n3l96vsnE5svLArCFSqscGeZA1ZGozpX0AhvwNm9m8gUjXW82unEfwkGBKTN1JHrzjB+ZEWS5w9eqVfWkpdUDrKUlpZ+oGupLU1VM2xIfOezRpRa6G4oUhTqFauyc8wy/hj5AXvSOZ/FkkvaLps1jrly7Dk7zjS2am8I2/tWOTu5qVjt4TBY+zs7AkKsOTu9rV0Rr39EnKCrK6jdSMj8d+/LmN80TLIJOQ9A4bIRchJ/sqGgRoRcCi2WDLoE+cTsJ/DyAtGKcj5GPsaI67l/8bl8kvrJc/76PIv1MhGUVSZTVcw8dl7MBS0+82hiCcMubt0+HFT17MnEN7t1ouJgzJIH7IuiaGycmu9VfynmOj9wUxg66dfd3en2kRnh0s0JxvPPCDQho+hzWxhha+TFdKvuwXK3xMZhqjsvuZn5Ly4X3pt1vp1fv017FqFIdxyju1I+MzVe07uXo1F/qytEn1CX/F12b/867K3AWzSznlW1x/pcWoouLbWkCSuTc2QoPWj5PvLr4d85QytepWKvRZH8QuTJILm8Z+YiLRWPu2CI6pDQGlRoqf9+GGyO3kCpral/eIRM5vx26whC5dltK+5HtY2aRovCF2mkTaN8+hZI5cdVsUEKevMZcyDdinY594ZQBL2Ml1Mu+Pqkn7x9bVNpVBdFfKDx7M7xAeadY65x8zLl/TBRk7lTu8DdpiBu051JH54EWDPFIDphvB/RTMv+TprTmUKHig4YUQZeNiCczj1DyJw3ciCNv7+v+gwq06/s4274t6t+DnlcNN0H/ONLRI/oU7wJSQUQQ0eQuub+rfufwpN2MbB+nRldZOC5EkpkjUyZcLy/6LfvGyALrpKIVHEatE2eTjGB4F4bnpBOsk5/zeq1s85eA3AX91Qcn2fLkOE5HOCxM8rApycqmP9/0UzL791uq+m0V5K2ewjXp1Cvrpq+mL4YUDcITHD/OoUgEnd3jn9H8QNzwR+QUC5y9ugCzFo6a5Q4YXA1c+D131DKfFW4Ys7pD1wpzqlaWSki9izmjAE7Y3rPSdJGxyLr5/jnYfRnntD2hG/ZYPWVfvnG3H+HU95mreG89dvgibaHAkPA4L7T6Jek62WHNdVJiD+yb5tP4DfxpDH6ZgXnPJRVC7J5JPo49oGR8GDKvBBVNGDMW30/nwhYRZZtuGhCD9d8pIxyxJy6hnHBac3HdB0b7zZL7usbXn+koyT9J0evXvRF5MjRC8vT6hscn5BbptnPt8RmnGlPc6+5RHtO6bxwBJbUOKIjCjUZowqn1axvIlHzusLPNMvKrL0bM2a0j65iaePe0JYH5CV20oNq8hUUPpTVmQ7MSArteUWlhEZy1oZPKXZHNnLTlpZ8jCjAGm31fhFZRjt+lp0tt2mYeJ0vnxRqOuWvbLndb2JRUOMzk9SWxYpREg+YVisI2RQpX3JKptWMXRWVajVlPf1DPVZztzEVtLXI2H8I9CVU2T7bApVtz6l+Ac15gY7ChJp9q7YUCAA5RV165Q1za3wuyGcNLhJVaznFf0Rn9FEcq/I9COSsKnxeKXoGJhhOKYnxhvIL3I5pNeQM/vNH5iE/PxKbsYvekwD+VuJXzQoYeIseR63yE1SRERZzgyp+IDGyTa36OLW8PGRd14xnQ+Hyg3BDVXRo8gtdPah0W00v3P/AcEtNO7ByS3U2QOLf0DCg5dfNBKYk1vEFWJTVOQi6P0v6T1IVu5RwiP431ZObqMLRc8p2//yG2yaVeQIR+F8/FfQEhfHSmKbDrHZlfy0Ij7Ze9kBTQS6rrJcTZpcxb4xFaB6QbE+M/cWs6LIlH8gJVMB5IgAKRD8/mECI96rD9JDejkyvQGH3sUrhI/fNRfL4YfYq9w3HBdJZIeH4BYN1pfqsS3n+FUsTDnm3la6SF8GwE3Ebz1nwDrdtybdaLHGC/+3OcD8/LySiooYlVwm5qJDMr9740PGeFGWl2RBQYEDZGYqKSGRc7beNrvR4X64P5E2V6JIpVFvio6FhTUdQyZO/e2bHwoh148iuazCmxsHfDZTtNONjjS3u5ORBv5Wr1eef/c0ent7Dy62+uITEkTHEun/PdjzBrJv9XhkqdBuSwxCJZGFhkPKDg1FSGU2gHM8WYpxOlkSAk9m5N2DvLO+YGAEEhOjof2o6rjDx8LBmZ3OEze73B7AJCaWJeJxyA5ExJkpkEoqLi2VfLkDL9UY1Lvdmo+Oj+ePxFEpamkRIhNyRW/v7NAwMkb9u1mS5XmHd7rWEsdhtfJztdFqlr0yKMjX+qUw635aZwO+lzBDHKqR6ibwT4FbZb3FqeNouMXhMFtkmAWfg3IVGOlrFJzfvZ9nz1DPT1skLtzwjyI9xo4PcP4d3TSbwrbI9ssCu7Uiw0buNV2fPJCQoNPcHxthDHqQbKHt95qG25Q3rkmuwFhLrD2yVzvdTpxMyI/OGFfnyLoAansAO2Ru2655FQWfRJoF5k0JZjZR0n/5NfKON478rpIyxhxFyKEDvwbs1roWxPJ+e+o+J25612Vy3itZwLgg2LyTqyh6N0iW6lK4dOwKyrH2flt2Ux0gATwIHd52IXrgXr9wIkR5Vu+SdAuivgB8VrZioUHLAp2CMS+slnvB+Hvfo7aOec+9vtN349rGPrvHoQjMqdE4eFMbXH/sOGr4gIjPEb4n0CIyd9xyutoU5nacFyWQy26x8Lc1aJGrfXLnFu/9lLXq0IVo6JhQZ9XM1NT0RWEBfJTrQW9DV7oAwG+CTx7KZYq6VSHdb/817ppLObD2ALM/OELbz/fEtT/tzhwF9yeSaG9oJfbr/v7vVxSOWz7FIRurj+Z1IYzFc4CEhAQlNbVf3Nzc9R6P9vKrl+xVen1Bl+/MU5CzT83Lm/Z0fy4nLy8fn5YmRadaufvumz08/IvH+61dTVNKUjI3BINKQUgIiojP5Xf53h4YfNzAgBxRGDG1IGMh2JzgKsg0XJhZ5qWYcVsBjqZa/SaHIpwZLp55UvxU+PXcSWzDE87VmezqjEfZe/eycniH8WuUdySfl9izxXvhblTrrsAcxUixlICQtr3GfNbiSDFAXx7sEc4Dzi8VPKLEOSpUKU4bzLN2G1lcmuHEK0NVPuKulLpqaNJuc5qOJhUJGHR7ebB72vRHpWZiina7PRLd29u72UvSnQnFojuoaNr4YuHcbr3DTrDIY2BgQENN/Tfxu7rwNRhYBLnqZ1ZtumROVxowWukX9Zssl7+xaVcW2GfELUa0LsxOmaYeGG5YLS4sWkcvWo8NrlAUzDPPuml+dvn88lELGaWkZPVBUOVxnukxAY3Rd/Fs6pa7E6V/MS5as+9BK7B9Q3ogaTFpeNY/pmiIVG7oqxyvG2UQY5VUzL3Jt3Og0MY7lCtIpSvWk9l5vHeNGef61+f9uDzazmR/FibGDnkS3XHHAgGPd9RIjIYhNOL/
*/