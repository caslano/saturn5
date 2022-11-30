/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_PP_DEQUE_TIE_07192005_1242)
#define FUSION_PP_DEQUE_TIE_07192005_1242

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/deque_tie.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/deque_tie" FUSION_MAX_DEQUE_SIZE_STR ".hpp")
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
    struct void_;

    namespace result_of
    {
        template <
            BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
                FUSION_MAX_DEQUE_SIZE, typename T, void_)
          , typename Extra = void_
        >
        struct deque_tie;
    }

#define BOOST_FUSION_REF(z, n, data) BOOST_PP_CAT(T, n)&

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_deque_tie.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_DEQUE_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_REF

}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    namespace result_of
    {
        template <BOOST_PP_ENUM_PARAMS(N, typename T)>
        #define TEXT(z, n, text) , text
        struct deque_tie< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_DEQUE_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef deque<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>
    deque_tie(BOOST_PP_ENUM_BINARY_PARAMS(N, T, & arg))
    {
        return deque<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_deque_tie.hpp
LDL957b+TLM/6F+nO/lMYORCpBa2Haj6SUbtvS37al7L0SKgtXf8NRNYIDsTYc2JvrBCXDV4m8ATIpcf24Zp3ggmaaVWA8/gbTCnE43vrZOzI0cQNGkwvKobryKXKyLgXi3fPRTN/aisQhWWB6XXlxN+PpVoGeQ/1WHNUUJUqLdRwVxe4VZpj1HFu0UNdiGQvSibIyNVfSjylSLWOnx2PkhW27dLXMu94ErtYS9cYU85PZwmAi52hzvjcZuTBN9b9lYoZypwDN45cJkpr1mvUwAGdxsYzKJYjE7K31TpSSYFamNH/zYR9I7K+y7vXsC7g7AN6GIzJsmtq/GEcgZ7V4U8PZuomsbHva3bTbG1LLMsouecjYxVFxS9dQsx8wqmIx+LR8zedZi4k8IPnP6NExqW5p8Iv0yAOIIlh2Ela7wtomiUZLRlOOJqRKh204xA5J2wQB00+X3GN94y17POk9cl7VP5fEuUcuAU5QbvsLJ37zzc3SIr/oF3eGs/qWCZxbLYbghuopeLiJKM1OoAeawGeeRGfbp2FfTypoctxs/JGal5tFlCG3ahDVPH6KCdw2X9FIIQvRicYmew66DfyjDZfcmhONYJXJePZBxxkrgpmT48r/lh3IiOuuX1B1hq2q70oTVI7+kRSm9oCkzHCSR1wjLTWcLXwy6DtGZgPdbpv3qrkoeVLIpoScaCJdrZYJvnRspLQmf26pGkS44xoWCzjLkniCjgFlPngCvWW4Z103qzan5CN3PnbYeOukmH5JpPtPf38FxzO8T6YHjrx6dkDCHbmOqO+PQqfj8cMzp20N/18AXxThv0ZaXZLz100MFhzXVyYTttwIhuw6hswoATQ+gAfnlInnlNV4dT2hozQ7xxePu5/maEZdOxuggKfUFtAOdefcfggKdlMvP8YTfOwpncTckk06R/zpUHCfOY7QB7TBQJei/ZSWCNL77z+5hpxw650HGB6wbuX7FCSt0Uyqh1lEv6m8ArGrr7HoqCliMLFbant0AAU/nzYkj34EMa8CTPYOqT9FHvUxQU6RA/Myo4ZEANGpyB1fml046TafW6zGXdKNkyekHOptMSsT39rDXi1T8+LmFzqHjeIlXQLp80d729OTB3ne0YR8uKV6O7poWOWa25JEw+5h9Gl5E1W27nG53KtGx+oqJ/4oPrGiNX1yTTANhmCtw9sXYskCToGfJG6BH1Cb6u582FDH8tMxMn2NoxKeMk25vlzID9l/58put0XMLpJGK4JYBD4cntcCcPcyzN/3q0g2hnhfaVU9VbEaFBz7LtGFRzDAdmR2lugUPr8a3SDiIMjE+jTKAvB+6UBwu+FluaWmys4ziJjYeFRqtZoaQgVuZiG8vy4J+YgUSH/4s5LdNM3pPm1Q3jis70g0gee/HtIXuxQ/ecViBan3u8qwZNRCDR08zHKdGLBbzp3fiDIMU89QKR9PuiF35GsDwLPnbqQwhyolP/LIiRFnYC3Bz6OhL3mC1VZSDNwqT+hXV/pH1pB0u9d52ExWK9actwns9fnkBU4IYCBowhIYYS1jx0AzObSAdZ6oAOMpHow+LCUAo4Q9I8nsrcvYF8oNOAv5Th3MQZtj7La1Q2MHJQVXZ8M75LrRxegkfY7R0hpxcJDdLbq3xPGfQu7yFgHFl8JeSCjySRJmcVIlNsFqjwrY4X4uLLMKYfRJHe74Telv0JBJPb1VPA1pts0exXyr/JzBPOIYC8GeK726Itqa9rtHfxtFXMkmSo8xZ2G4w7mejwuNbf603Z7CGe7QE8TmbTc03qTftQVNOO6uqUZbY0al+wv+F7S6vRr0MNWoOdtRQ/o63fIa6K8NGzqJ5joNWlIyd+j7iwqQbm9mvdK/8e+OtDPNKTH+NecX/Bbb36Ska+LU0BIxCyFh2G+HI9mlH0Zt35VksDR9tqpfnZotsiw0tmo0krshMhyHMFDdKhKUK24Owcs/jGuBeF/2nuxaINL+DzJcHYjsN0JjlX/9lyJuEmzUhi00qzICyO7OBVna5oeCnaw9Md1xELY9ejZRR4p4ObK/dmC6liY8X2Kieyf3eAFOxaMCZ91YDYDtg8L+xmCw8twxiiXVhpk3RlQ9J6fnlbr66jdUfPwm5QDdmcxqeKoOY2NOlAKzw1W4bl7I3/QPIb0q3fwRDRWybn4oRU2eG19XBwWNj4wNPL/5Puhvrdhv7Bk79aTYeT3+GueR11MA41ozgP++7CoR0wdJt2GVwLJlcHp8lIiktnNPluIsASk/U0QGx+FynElLk3KAqNiAGR6CKEp5JmY9yiuxjWMH6ZMrsPahaWNfauJ3GONZbIgdxVLNGtGiKODwNh1j/raQtlGByRqXICHF/5BNTsXnZ3uS6XNMb8Nx/S90a1FB/KxgeZk1bIOfdSUv71qXIYCQWbtnlpbJC/BKvhmlhoSYez9/GBlZ908eY/+44MTQTTFssYDbmoEbHzbiPOAse67MilHbLLGPUwRXaLIbb/Z9MWHSqdV0PkbLlC4FwZXGwx6PkEs9I52iQEfLaNQvRBvTV6AsS5+eWIL4Mx7ituJjLKoQ6vhl7TCNTgcJtwT8Pf7VFqyaiMXL1YXy+SAbvTdNrP7N9RRI7x3TVSSidj+ennrc3MkgAALP/TnUFbdJ3KI0btUkj2Fyldjwn9KnEqdr55GoOaHJqqRuSm/lS+2yIW5nsJHWP/or7R3kqwOofswOmjJ2UjdZdN1lowo+En4FMkxXX7UyS4z01z1/tq/IGgQ5TtL8PAEQU9bLxW65xj9qWAJrFH44bxvBWDRnRO8N1L0FCvYzdSbmlJq/Pf7qEeA9gX7+2DEKXaBmltxSAFBqivEY27UWuqnRXrLau1C3N1QY9i7NYO8dtvXCThUYs5U8kVkJj3asO+JKZklHGFw0snj1nZ7CdaeLVrQRN9UTgfwakmLxIrSrcmA+0xorsC8co4mG/51D7R1j5eZqCeKUfADT0PEeL2Cs1Ww/ahZGN7n2dTk39DaO8YCDuN4D5RNj4fFNO9P/UT4hk8jRodcWzniawKHMVwOz4rMwsuNAwdRvaR5Ws81tyL4M+2zrLz2K+XoBzPnonQnPY8NNaCu8ZfSo3YkV2+7RVgHieSaEibx2aPW4saoN0xuRWLxtwwU4sHb6pCoGGhoYjWTW9/AOZMJnnguo+Ub5FM4H84+Vj+ohNNXZz+JK7bMKGxokbPu7y/4oV3OqegRUpFsaGVqBrBXcA8L8eUfCVAJkwEBxewyrWbAQvTwZL+jdG1zEWBpscmZxVlsKP/3FcZwsMM+Sw2XQMMD+xoOV3ze+emf0NUcTTOvdS4nwkKODzQpt80pMV+/zH447Olbi/4tS9MO0uqAJO/Cxd6yor97Yu2YoEE45wdEX7xcsisdvZD2qdi5totaJ2/2q0Fw4NypIrAwYCXhBeDXlK0MiY7Y9Aqd3YMfD305vNjrZpm8+fZ5YuTkO0L31CH48V044uvdwQt0/RitLUvHLt1HEmy0BnHPyPSOXstGLJZgffszhl0ig5i4m1z/y6aIz9B0jJGjfXcsolngifvVR1eHtaLYvYY/Ud2NH/xyDwQX0pHmXQSfltbpeXVMWaVDZGZ4vwryibL5vAfPQkDUy4qfRm+p+JRb3vgW7AN6u3dftSQtIPlevjkciXXjSdnGt2O/QzrDtLhy8+sp0Z7MnQij7LVJOsU65Zn3kOVYezb8efw2/Pb0+Pcmzy9w9QnGZGa2aXDT/CyOA2/XT9OUu7rKg6viW6z0PaNuqE2saHTnqO8D3MWkoqKKRmzVO8PSoxANbnXzh7BzXlVYaqXYc/bTvajT8mUNLdjxgTv8FsPwBfhOthf1v+7lBu1vBz/CSffXIMAYZwiCELk5ItEEevTcSDlE8kj+YO5bhHiGgXmBkIAgg+tYGTxYXRsFCo+AkiAbSIHbtmdsJlwc5YG7gZb+jMgGDJjGi7PodmKiuiQXlO7H9cCA621vygveXz1hXB2/PCddJVrPFlvtTvZLNVcJ8lseKsP2OHvUwLgIf+ZEpQc+TZsyaTAb8ngdOOwKxs1XtPOMQZsTSUNy7BEYhBf581VJG6AdM6PAdxCP+pjkvAUR3v7dKWZFGEYk2HbWB8CdLpCieiZTr/IjxxR9YCXRjpO0CgumotCWT3EbDUXuBoZmfX5E80tnooRQfJlkYAtmpkFjePprGZpZnLQKJmj2QWv4WjGx7vEgKZkDuRC9fDex3bctOBTIt3ooIbcQUnPk+J51b811jAi1gUEbIy/SABJwAkWTfsuO92sfTwgt206z89LkJdqzGSZK5lZUvXKBbPLDG6+E16dOsLWlGQN/FFIsBl9zaO9I//izDQ7eTYy+G0DJYjsENxQxRmq3FzzBRs/oQ7y9mp7jtHwdEci40MSWk4/jOmK8rKcKy+aY8woe/r6WVqEG3VWzGsynPKS5SGXsypTvVZCuhNqkumB76fSdMF55Kfg6rkdhsNODXpXcqDkYSEQHOSRpzPjBerq7cNvs0V+bJFH8zC2ueerjeK4onNi0ZOwKn8aW6/qy7kfyLCPxmGVRiSDNkPk3/hDS+3St2TeGgaYWx6Lv6A2uFnyxyjFK7bpT2Fy0/WwUa/iqJIPdBmA6ajW6TwIJJ1pDaeIApD91UCEIQu3IjnylAfrQHZ4QxtUaW20P+7mlUWOSA7q4CTOGHFBesXNCHltRiI+yPtPKH1EOW4xESCEy7XgIi3Z7ZOK5xIm5ffiyBTUH+RTaoAaIX3U9qI8xaMyaiZ8bHIlV2202dpk2heViPgAiDsYlpX96Ogn3wa4HsYkGW5orLPvzJNUIN8/SZ2MoOBPUsFs+s8e+4BbPSlxo/5VctU+rb2FCDyJ8KcDjVWApvvg/lUQWiJ7kPlyCM7Nupx7ASmlSbw2vl0rL4+i95F9L3AMqjN+ugT7to28WrVasiFsvIM6ujYHHaPb9IUPSvftfRoQedlmQ+8+D/Weptsr021rxoz3IiJHnLgz42SImZy1JDCxV5Phw3yyGMg5YBkvfTH31DSrmxgipVeKeiBr55+81+jPwXoTVbQwAfU8UgH6ntsTbqEl0pe6zyH73p4SBuleYPo+ddZ0tyIYz3m+mYxMXyK78J/X+FJHgJ7TzcBu+MMJB+3VlJHkj4m6DdFXVshXZ4oZzQiGGf19kUN3EX0WBh4fWXnwNrtdhJGsD8dMwd9hvLxiopLNgjxuwi+6umt2Yq/uIj4EgbxEBDMq0WMASlKY8SaRopGcW7tx+NALgVwWKc+P73C67Drrsnl+89jNu0F5j0u7QS2D/C8CWtXgA3OuehgrVAdBVDgpueSc5Hf9C+VeForVMGgy4YIx5BS1t5aFhTt/O1Lh3XHWG0/vXJ/vsevwY3JopvseT0j6MBeXsMawEdwBIPA/hAAC81Ijumdfs24Hdh3/8ALYtKpDIUALDRmXhgLolSL2Yx6wqAsNyQduQEJj1GC89t5G1A3sP/51JuffTWehtu2YghogX7fF9rEOwCQO64JTAdEIwwg2LxmPixVNcXvN4hyjDEC/QjvjBNz6Uhm8Vc6fuffjBhrwoDlkcjAzEjmDvvd/ovlsWt/wQJ2RobTf7Byt+luacAbGafpqoN8fj7kejst28GjAUVXKTgpXkUIjKSU25t1irGA6QUBea2n0p7C3y6Jha/lf5j5n7PHNvE9s2JufaO2boqJgkSI9r6176WP0v+eNXnnugBTb2rzUyxWjyjViIm60UjSjz+hQ5zxXyw5cVe6oeaAZm/ev978478zT3AGCDw6KaQFIyA/atS6APX+wSqMiwd1G8Y+/xJ0yCp2Iv9jiZfQskAKqtvzpRSE3o+p/QgXDJ7YhNtD+IGlM52TkVQ/dexohZEKhwuUr5nkQeNqN0GOdL8FRMFeSgwLO6syqUmGkcvKLg90J8+dgmi+Y7iCbTIoiU/ejYljPGQMBwDLTAJxia1TlR0bLgk9vyOhhWxxIvT3y0slIuARKvWDQgCqn4cEPYRVCMwB9u0M5DJBFCvLpyahJV42YVqYwZCorOySMlFapAGHjQXvTVlpUPsE2sG6v4ZWNe0Q2bAEUkEsYwAIJxgWwOIZxY5QHBf2LdAX41uVO3zi9Rlt27OeThyrLkdPHIxuqQtdEYgUEVmwbGXQPeOWwTdSdm/yHVmTvyBOc11SqYXJgAzbEjr6ZAIN0Gx7rSyN3ZjIzx0cF8GSvCFobzXpb4CH+UQt/4FtCsoyrTy6RDeyLpUjdVkmXsd9CE3DRc5efT/2IwgLmbsSwycwUx+ZQAny0pSqLD0hYhbccuYHRRkNetQ2pLB4U8UfMr9jmB6Qdxdq7QDumRmnkm3Fnvhdp2/daAYqQwZvKpbhWc4puCuMLSKivuZQ0dchlj7p6QG2zvg8OQAYhFTiBPP60QTpREXgKtVO6G/etz+miCR1AgGYVzvJOmUKtPexj0m/gXcgXg32jWaaPbZP2wMWJ8tvBKJjiwJ0FdSaS8luywdU6OF0Nd0MMGEcUrSnunqfgL6rXHU+5e5y4IRmA2tQBAxdp14yopHs5srEZzciUpEla0Y5CkdmT1vjGFNIVz5+NpX8dyGHzpmvXYTnkEmTdDY2myQVoL6lHz3zsfAuO0GcWDWNJGNSQJhvRSG0VbVv1vLpLOTkcXyfzbUp1UJXhZENjpxMnk0nY8ASJlCJ323Ag+4cFEcMG2X3Aygg/xca1fNgtMOB159DFVMQ794Cd1ZE0zKOCowK2CoeivjSJv+cfe+2H/IdlEz5cFNYHA7P+L/XcsOns67XZYU27HAOWbfQ+h/QOKO5u5zObrpvPrdvQxdRhszzkTVNncSN0Q2aWA271t8WK1gi+cZoISJxYPHGnddE1PraR/MuDqF+0xsHtIkoKZg4XmaSJu7lxEmbI0o5Zdno8w0HWSeI73szFGwfiXvmJ5MDflfLZDONjWCnZyYft/Q6I2+U0N/Ss778LlizfE9ePPslgd3F/0AHsM2wSF4fn6Wyb9ikOIvjPemaBnuHNZut9B/G4oBus8Os+cL/B0Wgsyfw8s3hPNbKKhztucawl1KcsQB+Tq7THeq/FWgv9uNmHX2MM1EYUNO0gw91MQE4n4FuCMdWnQPE5voZC6YDl0+toEj8Vzf1ijfqWaV9x16MicKESe5OicCLHwtVd9jKy9JDll3nJseSP4aGF1rbp8FJmPQ1ege8MNUiyYbIWEMQ6UGWbCaVc6630wsgWTvgSY5EYmiBEl3GT2erL7A6UhgQTrqAkmTBjnWECc0luZjCdE/dU3oBmJfn0LoVu0LuH2vTA8sec40ZzBAHWpmtBYsNukF/p9eWgkQJZoXidAXDtDCFllPzwM0z2R3TFIHidu8LwP9iz/xKSyHgJsoHxHkeF4AfodaJ4W2K/H9PoheFz+lq7eKGKiwn5wrsOpZfJQ90idtv7xuwMDoQFkchYQtuDreba6usxDouygZGhKdPz2OpZ5tG/gmaLhQKyhxEq+pbA8IokcVDa6V/gEVeI6A3G5tRh0GMsqkZiyJFGrsrSWCPmmgeayySVt1UjyjHDUjRyAqk8BNkPC/sTc4b2gxfTgjymGF9YTU8LwylnqiozajCyXDA88nPwuMsxLo+Jbgf6sZslHxnDnNocizvaPTwhKsFfrQiH
*/