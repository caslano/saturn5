/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_PP_LIST_TIE_07192005_0109)
#define FUSION_PP_LIST_TIE_07192005_0109

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/list/list.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/list_tie.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/list_tie" FUSION_MAX_LIST_SIZE_STR".hpp")
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
                FUSION_MAX_LIST_SIZE, typename T, void_)
          , typename Extra = void_
        >
        struct list_tie;
    }

// $$$ shouldn't we remove_reference first to allow references? $$$
#define BOOST_FUSION_REF(z, n, data) BOOST_PP_CAT(T, n)&

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_list_tie.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_LIST_SIZE)
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
        struct list_tie< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_LIST_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef list<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>
    list_tie(BOOST_PP_ENUM_BINARY_PARAMS(N, T, & arg))
    {
        return list<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_list_tie.hpp
6Q64IlYpT64sRKUyDysZSy0l4VX3bskttgBqHn2mCnfeoMsgcGKQAhAHIWYHPyD2yWLYR+QR4QLKQo+EGftXdmOZrlPZ5Zp1FG7u9oYzT6/MCR98oFpLjqvRHI0AiUEjE9BI+TbaUhNMZSaSEsCGJoLc8QIVgt7Ro+DG4vjxNh8VBAc6gSWZOfF0V+Ebn7GUOdPHgRDAokIDzRfrxO4M1sI/JnnteJu8iW1SBnmpFZb9NZ6i2YOgW5doVHQOOgiYi/1QgRbp+O4/WtrFECAJIcGgcd4YzIEgdv/4vtBoDGOQ9vDHxtzMNvVYr6eYy2Uh2R4MkyAdSS5Jsu0vIl8meHkt4eQ8KQRwNi2vUdQNmZVeT7iGQ40B8bEx5aTLkOUSgrEiHkQwRHl2khiUpXq1Q9GOswqBVXSGLVIS2RFwwHSpCoY5N160vP7pTwBxB6INMo7UjPK4kMuQaN8cBt222rwbfQL2TGx5bhfEh0J8MTkufibrGx6YLCuDwA9CLXVAcjalFt5ioVQBoLkOulX7ZKEHcGHjCnYBHQY6xMkg/b295yNhO1NPO1c53b7NluZiTQo1GJOJiqTmUl+c1TIVNHmJ1/PwcGroPeiStkeflw08Ds4Ir/4ceFpAz43PwoQTQqibGZAeMVHLsi8SvJhVBMB6HOGKRjbEyDS6uQe3SO4i4hU8YbizbOEg8KgSeMTe+923l0PLXLzUGpPjDaL5n8balnzrtdErGTwY9pT0RQ8ckkv8+L0rZ5rdyAApdcuW7uv064ihiavtf+y7scx9ODLMTnBKoPS9qSYZMhdpw0T7SQLyZ+bFiSx2bCP2xXlFIBPqGewkAvo99wPRzd23qM++vWZYPY40FPGRkX8qr5BclmXJPy8C6sleff40lDjHczsR9GcLeMA/kZPHr+xvKPpOszJL7CyCyJ3VUBxAQSj6/LmsoDWqrYtX/aAkvqJ6R0y3AeeKHuoeR31W8t22gIT4QmNZHlfFvngOZGNRnjCyrDQyNXAS3lCt+HP7lkLXouzN6yDpMkiboZVC39Iu5VBxxHCM5p2laRqBRH28TBqiGbPkgb+OEWLKr3mCNjHtrGc/94qae9LxrCxyj2nkWcRgzNzRLV55Q2g+HcUq6LExJuqexlLEklcLpuFygOX1b8Y4ZDLhDisjowIpdPuzQoPgHAX1AGwj94l3cCDoeazUw6cXH/YJo6npj1Xk02doC0gQgDVEIJoGxJAOC211rtJFJLr6nKSaf5JmaRpL6eZlY17NvgiGZCnChiIkuJ2JBCPOzMilFK4PWkcwTR2RJbG5fsvdfDi5NLWzmxxNGW76hdmJkeVi8IIWsz1o98amD40dAQjIv8cuuHZmk7L9Unmqeye4Rd0ZDv2qASNT3G2YZb1dAa4LuWmwapdAJ1d8TEG7yoGM6vNvk0qvVX+gvqrtAsRiwlMHxMtrHyMsnpeEEP/4ZhfZnfYfjYBbZiMEa058I6jp9+huMjqSfqhKvdNSQV8Fk5ORN7aGTN6PVH+tfKQ14RqDP5uEPTUs/VsRJ9LM3YzRWDpwH4St07j9ls1eM5q9FaW8+jN8tCVv9g/7emeeiW1cw9dkhQkMQRMYlzNJbdzDFfdlrAFwBOm3qy1x0X4f80iHzZXrwf0TJVWthoLZG9LKbNIxdnbo/najfGdGsBDDFLIHVdvFmM9Hd/Js3MOEpc4W8ukjrlJkTQhujgiQPWf0zddI4GADZh1Ae6wOCp5ZoV1zN3si1YNbkeRzZB+R9NvUOvLpBT9gCPM+Ig0tk314Yo4BCS8STUM+kgFI2Lc4veeX3Ie6RqeXVZXRts+JaZ4FTAkj9cFo9D0RtXn3TKG6afh68DZkHmzIG2vh604elc5ef9U7+mnXBFkHl6qzENedLhkHh1+klB3UCLbO96XABeCgCZf91pnDGi0YTVWsR69RdtxFXPycu2JI1OD/5Gk/dzAPaGp2FDtoDYlYGCl0fHesvvhEwZNZJK2jdij3pLcfC1GvkIIel2Mm1/qoEZ0f4hcgqDJZMcM6OPHLD6+LeuFClN4mU9BTy4cGfDU+hv/VDZ2yTZA5xCnkThJAz0joi9LJPaVFGXFIH3l9ZvN3TpSdhrXacpxq69IKenaGSjFJpwKZTM1DQMFGy9l1KAaUPY/Nmh4dGm9CSTV8srsOIBNXxj9pLrI38A06nyQUd90Z+sopshc+vo6uydJM8+Rw7ArYzEaM9ODcfS4MMd7u28I7OnNF19sGjiIxG96jxFEud3VRvHnn3TWjcZewhMhchoOzuwlzenCiHvD550Jn78RksG3uJsUl7Zlpa778Ly1HOSJHGVQWBLg145RhvHyUKt/b40ThoaF05yzSBf09iubBewdPnLdr/JypqzuW0ZiJXfokJXYh0dApvRsJXnp1pk0J5GMsXGLG7y2YIGsKQXb3tr1uMiPzSzohwGWS4kEYNtvLZ9fWy0d7hWnkjxRnomVEOfybxfyqDfclDXbxKCUvfPdUzSXGTfV6C8tCMfxA66nrZo+3VfSWB3hGxMQ31j+Av4cSMZ3pXPc4rCapB3ZN3zOCiWtuJhvaAkYOS3slniIGFCHjTb7jzkqmw+Ax4kG0QCMqf9i/j63eRP6CorrgPbJp4b+J5LbneZ/SL5FvI1AOI3GzzNFo6wepAdl73c7UuTWUVl0QWiBQ8dqIH9jXUEbdLcVhb3+UuQL+lXALRhCDn4qRy8oMhU7/bGWwfH/Uf7MLmq3MTl1Z4oV5E6BHOTasu5eKQpXeZ/TszEgyud2h+HRhEFL9S/Rqs0XJldSVVZU2bJsLBK2raHWFoJx4uamYztTrzCrfDHRDQ4kplzyqs1gUD2hU9sElPDYJnNdLCtE5aHTd0Ekc8kNL/+lEV50JiQapah0HsKE/ZP6iJNkbNy4p3puRpEIEWHkvgVTbef8hxsd/9BLvezg+Id6bg/51hXT7mfBHDxXfQVImoDMi+fadbZdpe2kyQRN305KUlY5W1z5gXLhvqsOovIpaI5EHY1/PJp9F1yIhwKE188xF8lPb7v7dSzBY9zyC3pNE35N9z+sQD95wAes7UYx4eAi53M0j0+MY3TZvU0qgjLdYQVz1kMbL3UwgspM/OER/1i/5eFz4nZZWa3WzosIQinoM4gaO5Mns9QrhZeXT8wZ9LicbDfnH5eZ1KPbnmMpDqLuAEOPz+S8ngrKiiMuBv58iJ7m1de2bhati9nEZRPB3OzCLlsxAD6BBiITX4M9F4Y8zAFBcxO0OYeBrnuEyjNLyDXbYztkjb1Q00j8jQoKB9DzcKNBcxFHr+oBYM9HYncsauqzrIQ45LBAPMmPASZABVHQ0aVLBtVq5wvsCJiJ9FdspAanTlZ74dYdm1HCeOlIxmFLMo78R5gAZtf86VeIGHklT8WeNNuvljsFxyKgZXM/ssInQ+t9dZuwHhYRP+vk/jwip+HiYFqrtiZ74WLJKE1VRh1knXttfpUiPSqtCRekP7SEgTga7Zk8urflF9geI6aFVuNLln8inF7tX5I/xxYzZyhPJ5BnDdRjYEffqLOrrIl1q676M/XMH9RBelycBUPxkB7LRSOdHjC+rGpwXL/PH5A6bR4wcPyEw1n8GSTDNvb+dPFZEPbsHcyo8xRwFI+DAbg3E1+XrszyMi2FqvVyJkAqtEgWP0AX6anpJApsEYNsCYaIbAnfX1Dc6McJsmnSyBl8wDrKJIV/4h+GUCcFEZO7cOw8V7cikb+WoJtmWs7ywBFBkhxCG0ufko9A6U0O63a13Dsf7dvKIPcaAtgvc0hrlZ0AxOHQntfgeCtfXWKjSXuDWFiEY9A6tGEz8C4Gqh1pB79nnezH3WcBoQtMJV5lSOmrw/QBxNaSBwwtzn2RMtSoG/bNam/AzZGn/ncbeG0Q7nhzVy+rREEOgI4Fka0xzI39wRY/Xbl++0PwRhzBVhk9v8QZDD+89g5ZnHxUiLeiC17CPPaJVCoMXgqsPk5y6fSr1MRH4riPxCS3x6ZDN/4YFg8tMDHfZEf/XadR3bEBmxPbgE2BCXpkbQ/iiUtt2QWxZ7U2rkIA7SK3DMk4Bdv/4Kqd348xnlJHdf5tUgwazQyHYJ5NqWJKpt+mRGvI8E+EKf8Nouczkl62gqpZi11dgGSUqN1h2W20zZxQMpxJQhzuDtt8/e0ZvlafWj7bv+Jbh8yi0KoAupXGqYQZ9p/BkfAEBlR5E4m6V79M5KNAwyGkKLV3v1lBWJeULsrCiNpmHo0Q4K7ZHEae1/af8UbAPTntp7RkNS7gz6Ye2BUvYSLkgtOdLqPvpuIEP/Tiv/84imD64cNzPK5G94qNwsDg5jlZVCVSS+rjrvNfvKFNqP9wsFaYY6P0sFWNXQZUgZxzEeUB4HQGq90XoJydc4hhNUkBG4GR45tU1gwouGeVFttRZh/O8H1MzQM+eQ1Pd3287wdHX00Q6Po9GBXI1y7tVY0wkSTMhFkmq5vtj3oIA3cNOf+G27VPlYLPPC6EgaErmOavJQ7R++8sHa17Vu7zuNAY8orvxCf19mqOzIMtKS910usxonblWzOVvn1b4d4anCXKngfllnrHpOi4lB2jsaI8pHTnFl3iUcAkc2tfcMP4DvBHwsYKKRQ2dd9fkJEKOQp9ZB9fwYQ+SVhyu97x9HO73RNKpJ1XxULWPedl46GHGU7cwV3SEkUN+m2V2uOqO4uG+2jsrLEfcHYYF+gIcwrTRzrY4ivS+z6rH+il5OfVHhBymentAHCAMkS4av1yvDIE0+JhKCIjpKTExv0C8mp4By3mkaYsvAmnatVi5DuXw0msdZ2nDRfbbKqPJJqpQTD5uASQSCBguPG1kvkixPQcHv+oVnbT7TteNkpMKmW/0dyp7h7tvdblKzXXHzovXZsQTwpfGXsIbHaNtDAc9PT9l6jgZaaRCHwoLvfw+7zV9XBAh8HLY5A8cgEGO1jCPByrKjRa3EZInPM+kri98iZmxUPIXdw5iXWOnPWReaJxRezK1J+/VSv5UInoLiULixKwXxY77p4TXIpu7qjrcrgCaHEksNEnCVywwSMtzAm1uuNI9BmkcMV80gdtjghg8nmmoqEC+VxeODwPGLUKvPvWRxxEgKkS5A+ex67NvFSHnfN/OupfwviYS6VNT4NdMgacVXPQRoe18a0/VlfmucNc+rI6E0dUaTkn99wEU5cVJgdKyXMWDZcwDdNU41j7lRfq6ZGkloZxaW4VSEvPiAZekUrJxMR7q8ihpVT9WPpTFB3tU//udcXUtw0UTFBWizw7Iy46YDmY3tpfR7vv5FeWiSkqD8h2tARC6hGkc59yfApogQxBVjboHpgpX6KcBVopgDNwAukbh66kxBe7K5ByDaMXH3Vmzgzbl2IRP6pXw8ygrGeUD6Meb2Rt9eRGONRc6Wu82qdq4yS6WJZ0K3AUdquiHFU3aJfz2o4wPC7SVos+mH7Wqu5XtiDcLL7vv9bml85WX4c8mnaE3i56wpleyIZ0OPy+L4dTvdZkj0BveWK8QzE87m3/TJiDkTZc+qUuriSrlNqsoLpewScan0YDvVK1EYE8HMeMmLJH2g86RPxsvPdFL3pw/F/XjlaYDR4lpJkOq49RzP+pynOpZX+8OURwexckVDe3SO8M/71TzJuhU3+Offwd0rn1wSz/hPmtq+DN+Xnq+Y151Fiq6s36c1mLrGj7tCQ1UtlUJC5T1rtbpOHRx8GbJK3mtdqEsdKZ2mn+KBiOq53tGf+q9gX8uvmFTbnvC64UhvQPjxY2iV8MY1U8lz1J5lx1zea3bq/FLLuKz7Bacpkgs7Wmls6o/6txF1Xycf0uLOWNiVqNy+5jaPtI4QdzC5FUrm6LEuKIklVofxT7K+C7OaQA+P49gcux4g1hG5DhnQ32h0NnBtWxdTFihZqljSt89uhuAoiG5EZxe9yzUQ1AzkbvVN3QFUCLfNJhmWZUqWeaSuo2vPV9sGmx56sMS5tsBOECI3mCeCakO8x5jKiqoBOwzkltKRtapsdJGXYSCdzQaR1JK8PBpCKpPCpkAr+pt9z/tyfc60Cv4P1jO9eVPJNas/cGgLUKTZ8Q7d2cYWvegWSkPfdJD63f3ZBaYppVEoNlZKJN5cxb0vFMhaccny9r6ZwBDT6bCUpo1xxNU11BuQ5hRg7QVh0gWg2KCvkPG8wFKLA/LDMbyFgpAXfN+2t0D629ajBTg4UVKCDcoBOmj4XMFnGPnyxGqhdqbAUdXZc4fCCozmWXJX/oYMaWJ41dt55fEhfq0FbFTQxzdR0RR7ZKleVLmwUkmK+SVmjvG/lYPrB1JsH8YzzlvZdLdTfJbbSD0AJewy41dUTDRHyc9bBbdx0+VWCyy7QP6U013Clk0yfUblugqtVkEqwa6VK90dE/ttYUD4mWD6Ama8iKrdJ92YKCr0H4YVX3Ko1HSMXkX2R878RSkObJv+TUU2PCdQ6eC/bdHf0tKle+kggJ9yP7DMg5qTpD55aL9pgPsmeJwRXIMDEmYR6rYKAYTTJ5z/BiU2BoIeaT7DWlWwOo+ExSs0fTZUGx2SLBCkVRnqjhVQlbGGhoTlWfTKEjfBhvMwiYYGBmsKoeuja5Z2OehPTPpOwSSwHiJckH/09xu6FHxo/DZrIbjuavLlaFOAT88zDMkK0WmIBF+y3ycC1Ecgty/utbza4p93+PhcArV55o02bvF3JwVSbjeXKoxQAwnI8gLvOmi1DxaGsgJYRjS8EB7ex9A6tWdaKW6d/YmLzFRwepQFxxwGquGRVCvw6VbyiAVCwsx1p63sXK2Kyl3NaMNoop9FKZln6nlC6Z6Y5IjRVdhV0pzByEzCF27IgUVfZCLrvCPbdw+3LtblxPIylQ3V5AhxO9tYM7xyyVjyQ/OWjDdGpmHSqJVyBmrATiUG5eivuSBPSNKZD2KPrRlBBeu2quw2VixW8xxupDE4+2rwgeM4/hVd6rxqlQhm2F0/GudMmJB8yr6MGagGi342SYhbkmKwA4GKiNOnw6E/htafwPHFxR1p3unceTVvbeIFNjzDQB5m4kyxCMu/h+I41aLv8ORy6ExMm6BWTGxdafZSbARr5x836VGmHryNzmEdh1tEhJW6JzgeYWO5qOTwiEzNnwTHEB65I+BCu3gMSt9AXzZfAHhfyagwa+qHSU78NHf/JAe2iOnHe1DicEVktW7Fkzl6Cnk8nXOlz3I3tthunP92sm+mnVNN5v4dyAfocIXZcbApAAfrLnoUcq3BOCGKB8im3LUeUXK8ZdD4veXEwDBY2cO8oIll+Q83ByV8YN8UJpH9XvVtTXG8jA7tleT6e+BcYXmBDgG1um/VLY1AO6prv3az+lei0qnfZej7RuE04MSuANe8Rpj9Meh7CRyDQUWRt6VW8pYRQHS3/yN8ccBSOgbjT1iSp/qD6DRzgyEzs0qjXEAOXAjciQFL0+MYw3GaReBV4+fmvya3lEfRVJxLrHoYv9Of3E+Mdah74gOO8yYX9b74HQKeo3QpPIykqDjzhHNmxOen7b/ZaZj1rXKmk+PV7w8bX+B9gcm/QBT8pU4aoNTSqf+1lnwS3lCSXe8J/bukOtdI3HPIexbMUC7+5KzT9vs9B/ZZovPBEqa07BEp8clVzRPpQdktMtDeJMTg2H/o92n
*/