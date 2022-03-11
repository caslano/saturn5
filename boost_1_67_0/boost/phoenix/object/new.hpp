/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_NEW_HPP
#define BOOST_PHOENIX_OBJECT_NEW_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#ifdef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION
#   include <boost/phoenix/object/detail/cpp03/new_expr.hpp>
#else
BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(new_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
  , _
)
#endif

namespace boost { namespace phoenix
{
    struct new_eval
    {
        template <typename Sig>
        struct result;

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
        template <typename This, typename A0, typename Context>
        struct result<This(A0, Context)>
        {
            typedef typename detail::result_of::target<A0> target_type;
            typedef typename target_type::type * type;
        };

        template <typename Target, typename Context>
        typename detail::result_of::target<Target>::type *
        operator()(Target, Context const &) const
        {
            return new typename detail::result_of::target<Target>::type;
        }

        // Bring in the rest
        #include <boost/phoenix/object/detail/cpp03/new_eval.hpp>
#else
        // TODO:
#endif
    };

    template <typename Dummy>
    struct default_actions::when<rule::new_, Dummy>
        : call<new_eval, Dummy>
    {};

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
    template <typename T>
    inline
    typename expression::new_<detail::target<T> >::type const
    new_()
    {
        return
            expression::
                new_<detail::target<T> >::
                    make(detail::target<T>());
    }

    // Bring in the rest
    #include <boost/phoenix/object/detail/cpp03/new.hpp>
#else
    // TODO:
#endif
}}

#endif


/* new.hpp
793QuM71MEF7nioqPigzInGzx/xvTj1tCealPzAK9xvogg/CTpAPu4yu9EaU2E84LJsrXhVwApS8Jiif9uYFwozU5XBoIn/FeyzIBxQrLfIg/oPczipTDoSl8KCsYiBSl1+Gg1opeoyrT7dBi53whW+aSGbBHN/xeTZYqn/qH63pcoZEATXsikTT8AXT5ykbdembobozP/YMhVT4xjj0sl1yhdynVHAAAiz90z5fBZ2SbgxjfGvDB+A7XFmPEfM+mVseqyPOmDSU1Umtg46cM9vZLx8cOthHJpiSb6BaRal749wjdu71+85UeyDkHUAekht2vzhx4cOyup5qOc6BNkObzOeFViGg5sxY5hjiYKUzTUNYaqaMsv/XRdUc7ezeM6zaQdbJhE4KTYKoXjwyH113WY13VyAlOWs4mkA/yTp+6J5I4mTrkpRyf7oiSNhNWYzUejkkFwTSefWTg/hZNZw0L3OYRR+xNtMj5QyaMaPLhfl24ksXnHPZTqIaRHalYDZlQNekWuuW5Ntc7LD8BtQdEIp0HO3APK0ICJHj1ZClgVnjj/KSDOCQDNl3D9Y34C2FGe9wonjYYNj5AJ2Fn9PYHscAAzwdnaNczTVRlep0gmo37Damm5JuP+QXzhJxb/RuoMcRJYLlmMcjcigHv4EnbzfoCdPnhFruoBfbOAj13aWptk7qnJrJSWzdVzwJ2f0NgH9oxlzozRVbHhF0WD85oGowELrVEk5FERJBHvkOtY7AgoU9lLjlUDURt998dGs0c+Rm3OKWEcZ6eB0q1eNeHrXxCUNkGOzOpvJ/KLTCYpiXKvgHxkqy1FKZE5YsgdrRDUKsYO3zfIdWzvwuSEWbi2WMXjqmNfc8wwcHAir508nryuBjmYEUBxlZkRCubOznQg760UdpkUvMCpX56ygH03407EmT8G7sgNQ1cdOAfI94fqMOe1d4JhxhwbD3k7Pal2KF0OaJ/SROyY8s9k1sHyitqUO4ZKcOS5no85mMmBUIwf/Y5MDovtfn39UHHXLQJQhsyZ6tSiBPH7EYzHRzGgnKSjekIa5DkDzFGNSFX8sO6DSuGDIErmWoePreTylY+VnFcHL/FXiPh/GP+IP4AN/r7HtJrimiYLBmfHCteFcYLEiTaBX/4yx5cNlgTLhUbjjTYKmuO0A/AIyIdMITeXh5125OeDp33QPVqp44+LwOApzyELQq+TfaA9ieSA2NhioCCXWKgorIpIIHAls+q3qdJt/cWEehroae7e9K7Gx9QGMRCf6kM4DvW+E4Eze4jo9qbUjSD6hWoNE0dqi2k0RZ+D3xEKVPAkm+pq0mZ7JXbPKctXLWbigSWYNRzK3WAUPWg5J8qVAQXDkmrKTUBW41eFRYt+KGX2OQvjmXmr/737AXZ2laeeWchNq7xRYwS03zuCf+4d6xN7qShEuPfrgXTD2SWhqDGX7rPqQLNQAz1eyq9ExV4/gn/v3veZPe4z3LOwdZVyMvn0EMUJklWDnSaFq48UWaD8YgUcg7BaVObCSB7EuljkoXAOKw0rAUmctbvK2SdFVIhlQJqiKiEY5Idk+OBn1pEmBD25bQVGUIB2ZARy5BHda5v4p9EZpG7mbwfA05vYozVwaZ81yrhrfiSwanGaFi+OUujt1rHfp+gcLaMEFP3l4B9v1Rq0wXBrv3xBE30kVtgXdZ9K+YsJP7+MdaUY1pU7YXVMOzCsHUl9oPQ06K2DR8VZDT7JnCZkfQd+BYoESYEQ4wbEm8V4ChPiqADEr/PoWno9kxyTvbeqyjSsDWZcmTWhrpf7vJ0Y5jey4xyfzEQfAOgUi+/CsGRtIXMtCM1VSjk75R+v9k/A7BJNQy3+D8lCwa4ZLWzDZJwCwTbUOlAmmtmDU9rbfyVmO81yimWiChNGdSNIc87wUAB8wy+TBAfKVBNNVJh3pkHvM8/WJCseQ/Cy4/US6ce0eaqVpzYFvptG4BhdXh4pc/+RLhPvbbnr/4etM1b3GubKtCOQSqBy9oAdR4W926PfN648GoLvl4W3WKi4lWC2m5jlXefZFHHAt7qtDoNuzY1XZgRJZsCBCozNFNtnXWWvAXJazYoHZA9SH47Kb8qVDrQku7aW0DQImcxvf5ThDvAIqDdLu8+ege+dx7cg4/37FGl2y80LQgNGFY1QQuYDtYJ6cUo615SgSIaWCXwkjqQbtLF/5joWfPFWEJTtZzBY6gJ6i6lWK+CQaOsuXbl4v9wv/XRDUDQg1bGQl03VCVCqePZSWPqro/rPCvE0skFUTIfijSDS1ABbtw1YZ6SnCOlyyhERo5rhCSTG3FMSldRYUrIozmKv2Ev27MFuyMAQReWf5+knxsVL3q22JRIq5oWWtmAo5RPUfjGgh2hqOTM3OjJeiVc+kH0A+aOzndWo8WSh2tmGOouF/vYogzjLEKCMd/1dhilgVsiY/MX3XGQdSvTBlYE9GDGrl0V5uhe4p/MKokAB5LALuHozN4r/TKptILeFDRkwcw16TPh26n+FMtvlxjpqnvQM9CghuwGm6pEAtNgIsjuIhRKZY/Z69b37e1FOsbx1SEJUvoEHTCo3qnZMnwVzsk+ZAJHpjf05oWHUsPg6GPAYLyemLkNRsPfpbPyy95JAx4Cmys7RYOD+EBABFRIFBMyu8LCIdP1TVWLdzMYvImpePkLIPfSkdVTt6BKESYPQpOgg7KcQbBveVoD1izcaimuAjAkkVPOryBeEJCiUpevsAivAKRWXIpqUyzoEZoEBGGOCPFjGK+QUgyvIV4Q0P8VJcYu6aoEEAbc065wBQC1Kn3ojHTAbQU/MbRjncjcW7Q1RwS7T2mwhpaoCEjKB8BShj9oU4kKB96UhC9oI4hKB8sUgBdoQ4nKB9Qkh8dsA4ySJ4Tig/d2PE6SB4hVRh92E4YImcwj8bQLWSUhDcVdrZd0F22LTsY7SketZQOY7YIiJVaBr+/AQQbg50t9em0URw217kLjUvWjs0e65d7Zm7aJoKHGagJisUImvadeV13pmSA0uf6RYd80CnsNL1bWaNjn9nh75EnPZaQr0k6CpC9n8PNMXyPf0MmfUGipBpiDMC09xWlexlCZU4g3uJ9ef7xJ6dXZktAqEh5NmEhBAZm2UQApMjUD/LrOmET4DN8NINY1+jvsNzh62YcRpJLoO/S51W1m0bzSnpjfR//5Bv5inBjP4WvHOkMlj9vNzFY/E7n/h7FNgnwWOHOwWZw0uHZI3oH0YDw2Gdh+N9r+ywuCDesZffC9HXWRk7KdU83kRar2uh47h3BBiLMSQa9qEMkLzFUvMx/FDNrWFCVDsDiJ2IC74Bvlh/8PUP4QXEkRfjk5ol8+E/g+UxxC0GEfIHqjsFBSUVPeKKbY9+xrydq1Q/xF59NtjvPs5w/n9+2PJEaY8BAFzD/ZRNZ3DIDLVX+12wCA5rE2HjCJBbUfLwoNO2wfESiAtr3WQCvShHWDkz2H7SC0fBTfzXkRy6VBbZN4l+LT11dMqCh8eVpvjpechc7Kma+NXMRI8VH72MBqQZ1oubO9VIMh+hQjPedGO9CYIG2EeG7IdJJ8Iv7mMWsL43k7DXJnqIv2wGY+Mxw4H1ARn+hVe1k0nFvH6emb+gXK0J7kbrZDYgUHn6rWIUfwiq2X04KZFhODjrEQCbwgQYR4jo/b1cxRgHARpkGnw2lThNYlawNAoS1326YqS2XiK5Nml3SzmJQBgFd078eGT2yfy1aj2JQKi7A55OFnhny4/rSVAH5aVP1qBv1aZM1t1xhzlYXM7Eob5dmI8dmAil8O/IW+WyyKAOgAsNMwRFxea/WdlxA9mOY078WOe5Vdi/mM1cUgK5egNvjNPoCyZtiNaYdScmG5kSlcotr6rlSC+xkpWzLa6pauR0kjVP+GDUH7EUwiFsJupWJdwA6zql0S7iPanztTkSUkIqP5SY6wbTInpNFZ32Orcg4b0/s0H3NTVnwEL1Z5B8tFra0uEob9Qik7JLgeFKjpM2IyT6gAzFdsYgihvlYDyhBP2g8nrS6+P6mAbJPAQ6Cqrjf2AINjAMJJD2GgBTgUFGAGKAlYekyL2FY5XPYm0QyQzpyeK1KXCKiWoR/N0hfn1wwFQDhd5TxCga1ZI2yw0VPCrFs+eluE9XTE5+J8FW/wBTO1IwRHGrGWuB6GrcbyOiDMaL0NT9hsqtcvVSxZCRsymHfWFJjDUH7l7AZQXTSDpq0XOfwWmKR7+YPY0O5Oj3iOL8NECr2woRHXvKwU4gTrr6JLw6kH7M3hHDDadiFyVP0Xk3R9YyWAcyIjdQx7E+eMCPYXAxZkby9tHMCm/M37SJjhJ0sT6GWVeosWfLJhGkS0eMRo8Qb7HvUgHePl0h7Dx9P4ZQaWa58F1oCQ2BBd1wCBnIOSCiDYjumXZJDXTrw3fBnvts0AXQ8AuaiF140JDhIY1Xor+QeLnAUKFkh/mwQ8TxO8O9t/2/sXu+vdLQQRXk80lBtjiBKzy8xDSnOI1UyVz+x0OOs4jhrXVEHCBDARtLX8L+9qpjmE6QwSxzyrG/cw57KgJ5ie/x0ZABabQqi1IMrHvx1ZFNX8BPFjyE+uoGFf/jrKK3kkOO1bJv5StA+2hq1PqlLMkvPVRHnLStogDJeIA5AtT8va/UemAx0fJmwJQS1aUIcGry5gxL0Nc4YoMDnR76lvYnOORwETaxHKPEpdClvbEeLSsriciCmCgFxTja3gPt/NbqKXX6raEreHR/y8UDTpsUNBem09pCRBDUN2QBm0LF/G7HjYkPnR7CwDSCXFpHHmrJ4Zj4+g9kNYtlkwWmgkslYFF/vTijAnRUEm+HLHZ92Q7Eq2S7iLIAwEre/c2t9MBT0KoqhrnAhltP7UnQfHEeXQap8i1NiUt6Bc4cTQck6L94ycaDii7jBFeBdclQqQ5h1ieQoOYsWy7YS+c5yxDuqbtgHKpCugcKlxjSHR62O5qkEK14HYw5B7Wu/vloq5gRyKqGOwOwzkFuRYrzKOomUK/pR+6uv8M3DuPQC3yY68xxLgn9LPPdWc/Vbwe+Jo80E+s9vXHDtqotopctoBU2UijZ65Qe8yreGindYhQ9h5U2UyjZGpQebxrOdGkpWIo7sjwCW87W5VWdoXENXHDmbNS2eKwBZkC7haOnwaIZ64CxjovBx54UVqCkqrrYKQwFXf3LBRyoWvf9LPzwIkTPpvny23QQSIgcq4jEsALyLpKXfFqpvMFknih6aMUw6GH8yEkYAswtHw5PscCAn/OjLgFuqiLXJluyGUmBH6qq9hMIKOXWd2EhA9AckfWRbuBn9TbeWrLrxHPJBW6uSZk+i/S3BcZjPfHaMaCbgEnnV85c+dMqHx5GUI/EDxsKzI4K2LxJ5SKbArp0KDf13QgN4kyczK/QzjM1RLgAthjDBGzun7T+jH3b69NxM8ZPcRaGTUwKG3b+8bnZeikfv6QsA7J2Y3Tc8VO3s1Lj0VszjChvxKgBVot1Blez1dqNHZlMQzV7fuiFC8zD2DEtZkIuW3cx0CgH+943ou4NkWzuNehTJmS9z4plrrEeQT8yafR/c/WzRBzCWbbSHP1TDhs4E3p6J4txTe+usU2qzxqcW216ZgnfdPA4VKIMeeftZrCOQ+I2a5sxqsxHC6RPnn/YGqMIXhkeuP3Jvudi9G4HwRq4kgE05wg3Vtq/cwr5cFqx5V7MugAzoYfAI3D7RTkjrWH4hFJJd5llMeV+YAtoBWd/8xOJp40oZBg4Z33LviPLUJRd3WmDMfWCH8hTaIIN0ij2AyPyDBrYZqCZOdl8S6KFiQSAB6csOslgealI0MWbOj6ph6dVtGsIhx0Mz5AJ2+6G7YMMA0jwM/3a9SX/llvtyaHzuM8sggOB+H2EQ70AugWtdqF6sPpsKuW3/TVtQHHSvJJhzOVevfeCapmSfQoFbWnaXjmwof2Ca6jcqSEE51gwOefwhqVeXbeAjAEoB06gMIkax0P4HzqLjRWPCDjjZvFRmbadw5Fle5rJIjCPdWRIN8Rjv9d0cFm0AZ0qWafyV4tKzCl01Bnmzn8IheRwYlspZXsQQddUn9BlRLIHR5dxPTI/OJLcWJYDTry28a6raI2xib1Cje+U3HX2zRqxFAEfqMXYJ22IT8yvde7+mdNrpLoG2J3ujDW01puR8bTZ9oNqMZJNwqwXoqMPAI/50W4YBu/O1T4TBIkOz8l1Efe9gOSb74jTxxz0ofA7ePCQHatWeeBOf35BvLSzjootMG3slEyshw8pov8BjL3ZbGEMKa4C8Foa9me/tvELqMa5wRo4xSoQ2eWVdFaU+Csenif8/tBdy/IEETbJEvx0Irt6CYi1VTpertAcYfaq7x7LLMedUKCtTq9a6K0a9ah4JTjezX60linHCc3BVmgwz3q0MorRWXVn9XTpVVlKJwfGoO9xB4ps+ddeDy0Q9Uy+wiJxuSsIu7jkz9iv9WSyotBooKEXYERg6qjNZSeJR2v/8xsB9lG+71+g5uw21+XQrcxioMzDHkqKUlUwRcj9aSF4UvdbeTspCSGLdWCWvrSOlWiecMCtNkdISFvzTqflFCttSJgPbUJHXIeTkszZEZMuJSzzzVpmQuGWsXeVM9NL1BdZxaKMs8LXNHaCyPe4fVSJs902xAnQ4cTcezXDj/wkMXiKnjZz8i3UWtaoicf7xjaEE5Ar7hFEisprWhtaQujGYC3hYg94AZ2ZLguCDdFMFekrxErJdH8AZo14AYh+KGcHnMEyst1HAz7LgT77z2On+y5DeMUPXqsk+0bdGo57Yo13/ZYdvJjHah3mHNCgGcIaLkabKi8/ZukHeKlDt9exZeTsOrnfkCtUH/+hnLSRFetBzGj6FV8MQz22MrLj3k6FXIknsArGHcOR6oTHiyKsReQ989VQ/eBcBF65+3/Bxp+SjJ/fZdis3Q2U96HcqKCBHNBjna3YHgLarwTLM9fmKqo57l5zHfxp4GPmQcDvoInEz4M4TJv4VCz7Ln5HEchlZSDB4e+D+dBF5sUCgaf0AmflvflVjGj2biFDY4IMwHfGGBSMYFGX0ei2ZkgRpRbyiAXPUkIz//eTWM4ovviKbKYj6+0hfA13s1HBiBYEgf1phcNTBj1lkXvZC0GKytCYHt1fHXe63ATlujtERUZzoGa1R/ltYxdsn3tpvYVML7X/ZLUDo79Edo3DIp4zSKtvToGsqkbYXRhxhQed7y2Bxi11GdZfXTGTH+wn8KM/2M91x8Znj/g+6jbQ086rmv2HPRC2hV7/FEETR0rwyTfWPComyPA38KhyLTJvGsmqzxrZqnCbrwhE5airMePOqZhCEkGDwpWZS4TH6RJUx+npZDvPQr/ZpGViFPCFMD3SC0g9dtYAd1aWyZBrQuubl3tH2njgPXmkZnOvW9BVrcPSddWYWNB33QXOFKevUc1ipXDY3jg/yGFzNAOm7dEgx/pytmoabI9jnsHvFmt624G9gKkMTsBeG2BauTKoCDZRjSHVhvvEa6OhyomD88FHdIJxkQYYpR05Rv6swUR19clUMJoMaVYYzkhwRdsXOkUE2Squxk/os0mpTuA5q8ZU2BPXGwDf2n5fp/ZWAz9B4xVN79s0RJM6l9ZEzp0w3ppHJrXS3dTMknZMRq4PS/O8MDHcMPnunwDEqa6D5GZZvQKthvLIoWPkabbZKSn20mnNKw/hlHgIYQ9FWgqgJSflqG3pzdpXKTEZnqKEiSB0GCHxQxhKi9ap2yVJrOld6hqSNfCIIDZJgMfvovH97lvRrfbMzSxCuH8CFcTwuWJ7rI7xh6noTJju1evM6eivo9IBudvShnwqRis/3keRj9dNVL61iuUH+9CsbflEIgFccSFJMoYDiTXU+1mq+3obfAmKyRR4Nb/njDhHj+czCAonRKFVIgmpLdEHFhd012chvsDtxk+Cew8gXtvHQIB918YT2ZJE++hBo4kejIuDol48RPUXIkR8EcaWv47Nobe/k9Yg79C3/fM6y7KBVn0Ky62xwlqotFFqhxDEvYM8abKqihgMbJAXv46y2txEpd6g1WZHhJle87w8Yje4j3O7TEcUE79Ubnrfv46PGDmTN6g+4/3dEZ/3jhy2u0fje8P6AN274/U3sZfzg9aBuNn54NxaIXTWmKP8Nzvgyh+1Kfr2DVccrx8oavf7g0fgy5ABqqe1wGG1iBWYYTXzHzEIXdEs99E0584mgZn30PunMZElQjvYLbEy7Q8i7x4CYwxjXtNTKuN5/Q7epv/NSRkxg/lC6q+W/Nwir8Jj1jeg3HgXM3/r5aCHD8A8tOimZd7s4miAXYt9KQhYbeRwI0PO6wrK6MB0AwIfOBdFvooHDtFYDopNqzouE/Z4FXf57mzPxSyPZf4/OzqHF7XBxZs4kvbg6TXKrlAQ+vcDb5Bq8QFKswjnDrWoBM8Ab9f85MX3Uv/Hs/xy9BkvqL7F8xM/b2pjZmj3tJ0XppAcDpC+XFsGDTDcmLARS8dozD3PPKYIUqp6fv1za+WuJ1vrExjxIqpoKPefKbbXHbFrYlStr5NaXMZlCXspSbJsMT19gPLYc06WQo/lWyipyNarPpLOAl/uOuAP5uLu6VxerIPtgnGf61uXMqLldpnY/jkOeff1N241SeRd82Y1crUywRyrglu5iI3gjptbywcur9GXflNmdxwb4RW8Am8HPdhY+QPNmQZh+H2a40G764b64xS0e3MhtrhHnLCISf5vPtbPSEBlOSwZqgawYrC2Yu0+l6Rvs36bhFxD2lPwnYDPuf1Q9mUodt48gYMnf/k/E5xuN/1kaoneqdG4rhtrWLPrC0UQ5u01jZ6nM2vD/ep5LrEWbFrW/U2VEutrVbZenA2MfN0dsZAOgA0TnQE2vbJQOZhRRfGrJlQA+9GDAjSnS+7KOGv6oAXE0+W6rn+FTSrGgV3aNYjZl+1a8tBVhfzn6jKxpLs2z4vfEcsd+c5XyxGXgiG9iCi00NO4iYYlbjhKaV9/xlB3aYVnXIrDHelW54FYsiPqTb9uRV5zC6bsgN6berx+pGF3zDjWOTxZ+0F/Cn5VuT3EMMR8BCoIs/RJ6IJf4onCpHa8XeDBqvLAkvX8ec8Mrdvr1eibRU8pcY9B2fSyDi4NYz6ToU/03TDLG4HdcOh827dEz/hmD7D6dav7IWtY2LqzxKqPgH1YzJ9qdfGpfrVA=
*/