/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_MAP_07222005_1247)
#define FUSION_MAKE_MAP_07222005_1247

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/generation/detail/pp_make_map.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/support/pair.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...Key>
        struct make_map
        {
            template <typename ...T>
            struct apply
            {
                typedef map<
                    fusion::pair<
                        Key
                      , typename detail::as_fusion_element<T>::type
                    >...>
                type;
            };
        };
    }

    template <typename ...Key, typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<
        fusion::pair<
            Key
          , typename detail::as_fusion_element<T>::type
        >...>
    make_map(T const&... arg)
    {
        typedef map<
            fusion::pair<
                Key
              , typename detail::as_fusion_element<T>::type
            >...>
        result_type;

        return result_type(arg...);
    }
 }}

#endif
#endif

/* make_map.hpp
ZML21t/wehf3uK44Qjx5lxf3mCzflFDyupV1FPccoLCDLq8j1HnUW7G4p9QSU0rJvdGdKyk5e9b1vnuZSuIYx+PXmgycE/CX7m0EeoBcbkkG5FJv9G7ABkY0W7SM3caAd/e2Yi4Eh2MLVFGscVlxicl7guXYvGXux7CJXaaS9oW8joSg/zIDJSc8LG2ghQnkmohyHV6+FLj49LlJessTgAmI/TN/ggIT+C5PIXEDd3DmMB0K/qt12O/TwTQzSIfW/jiYSTsfAy6aQ+52VSzUStlzrvcd4z2Zl5eymwlEc5x7H3q1HkJkkI3QO8trKkRynOuS26qSOiYsB3WDev1+qJcp2AJgGXcz4MfzpD4GUuUG7vUZFFWxnJggiEblEA3nfVLGeABdSuZyQW5ZCSRNfiPJ2ouhib2rAF2ouByMMuC6ImtPBCDP5gvoYqwTcUuBDzuGhw0ArMTIFc3wI32FSOwgl4VIV6/+jUAnXrF8C3DnZ6Em55HvuTuwrVklv/gpCsEMF+I4NVwI0FXW/ifKT18qwGEQcWemU5RnqyoWAliJBZc6b/R+oODJUSkMdZSlA4h6Nqu00Fzsjd670j+KcsD0lKmUJSbuD9N5y4MDNl7tu50V1VEGT4FKWcxtmU6QFCXsWW/0iyjX+w6Rp+l7nsQklIBjpvslmgL1cq4aqVnBo0CvPjnmB656vd6+kAM4HqZgT5qFHWDoI7HLZlUyDA17ZEXF8qUwWv8xPTBaOD+c/VLw3oT3M/LPNauEH0R2glp/bTTI9uSohJEY5N05KvE5q0r8UbNKzPLPQuchaY+mE/Oh/gXB/ct+cv/icnaWCgQ3gufXUaW9YF0MS9732AHnDS9T67rCmFtvUKBQ03LLw0DcsgfdWuARv4wrjIFbHOubyCEVK5Yv7vEsFBcbS2t6wyhRjXut0PuebsARxXfsxvnFzY4lMkl5WC+B3QYw5w352iVMmvMLITMFMscKtgxsnZVcsaK3RS7m1zGUH3iQeV2cDDUptLZhK7o8tuRAS76/pRVbxHwLrwOTCiVgMxNuoq78T6kr/il1Cd9yPPBz9lvBkuxgHahluBNUzVPWWcFnJQYTl3cnxvUNEXuvgd9UOA9Ze5yDVpnrDM+b1qMaTLhzUCBzoa2cMGLwuIdvlgAuEw4ebOIG7yCxTQtkxe4iVW9eLA5ZbyjJ88jmgXvyB6/XnadAFO4sPDs3KkCWmL24JXCIoMW5MYY8xIAlyoCaavWpamBTMLNAFcPqy8AlSgzF3r9A6yJojYVWaFG68+SAZOCbiuSuY+68qA0hV8+54bkTHs5CnSxpRL29V/2KBtmnwB9Mc1Q5peWaS+XlJgiNMdxU0KpOWG7ixsMDANmznAxBY0GHGNBaAhXd4Q1jifWWLwWhcmA6VQPUeagALDnWEdXarFL85a0jv3ZEgB9HoRh9sjrB1bMG5KDkOqeh5wKHPfgwGkKBttgEFuCem4akm3/vHBwtc1WCp9WAktoaPSViIiCHQSgAoGxPmSpBdMr5HSClCsmgJOl6GKGoE1aUKN2HMNRum8ptk7ttErctym2TMlrZwRzVZNnBMtVU2UEw38wT7lAEqWZ2uYvEsj0FqjvcRok7T+ouUvTmqdCb+qTueLdN3JunwKGqC4UwlQ+xLIKIKGtvBq2cg6Ey1z4BL2Z+DYLNAuISObq3ZO2LsUUvFTpW6T6UucYL0KxgQznY8JAKewtlLiSDgki3QVuBSq7pLp7ZDbaQcjv9KIsDKJrumd3uPAkwy/FEUc7vImTtJ0A2Tw515eIBCpmNFDrMPKFiE1fhpzBuGAVoL1PJS4BJFJfqR/mGGs5ETphIKee1CCYSokwZdQWUD0P0IpW4b1mNXiRwzA/o883tPjp/8tOB2cPIwUAbQ5yDko0R0EvYJ4ZcECAsYcYSwoMlfWGenPDv6gRA6Pe3k/GUOzsFzsEIcE15UzTYvkCVDwo9eDuxvasd4nyKTeIY2ZsnaRHiXJOeR7vnSXSH2SIpSO8uiuIngVz3Fj8t+NkQcNeXb+fdFaoFuByQGcI94YPC/GDzUnGN/DPO/0GBI4nN00J8H4HkWyUwtfvCWfCWDnxk85KhKYI0SXE9wZaHyRPYxORI9vfdKHX/4qa+xdCLJQQNJd5onO0BMhU9PGG+nzTQj1AuYY1Stg2fIAIM9ZP4+vklA9gjRJDj5Wy/88Kgs19byi6XuN43mhxST/blihVL2U+Xd4spNlviYVRR3OHvIEQNCtDwMtcljHjZ0t4MMUO2CtLe1hxfJGdLpRiretvyfUEf4lMse5k7DEPDZse5OvnQxUwErDhALjawbURLCFd3+QRls2nAY1Q0Mw4wjAafPj4MfEYuOao4d1uZmPB3/3kRDx1aDkA+tgMrsheIys6uKV0XRc6Pr0MdSbg7FHwXy25Y51q7Y6BWF4W2LqbQyWNg9R2ywn28FT7irSBzXQhYQPZTLdADQf5KjipZCJrFObKCjTEOdERxycCDmqVSd1vAEIFWaVArMUK21P3iIr8Byv5LDUAmRbAFAusDO09RWs7vDRbDFHtdwO98L08BWnAscISSDXSP0cTdAJDmSspa+UYju1ABmw4T9xVizZODRWI0x5ycQDcg+2UXrtol7Jk6gdF5UeD8WHL1rxNPOf9+3dktHvGG85ioGKypLAVvLlNpWc75g8ARJhrQrZU3P2Pi/gj0eFnsIEsptx7qK/BoMLSe+f27gM2VuDpLjSb/Dsoxcu9lXP0CY0xZcLhgAeeMKOag0+sFnK+DccAJ4rh9V31OMFNMYnoBbJNNnHgKGWkDL84fQBxnt7CkLouTYQPs490MHBdGm7gQqOORyk/TyF2bjNsOnFqOqSbu08l+nV4EIkbu48nD8cF9DK4r7NkjORoBdUSsoZjbW29478cdrD1kLz4YwNL3EZobmZkDorNwwvuwTgjAmskkGjtkLTrKEdFyn4ByiAWwWzBxjZP58Arq+DQ4KcQQwjVM5nePcNiRO1YCb6mRKw9IeIZImA51z7yrAQl1jKrAETod5OzrMHHRSIH0mxTod4T0C4M6vwMJ6FamkpZw306CHrkS595lsN4KHKkmdoBzDYDRD4n57h9Dd9x+rJxEBsC3Vf0ETxrcSwjrCVDkm/qgiZxS6wTc/En8eDho5Ma3f4FnGG7tJL98XyIDTgB1T96QXiATbCTkBs7yDQSzDRKQABQs69PHjTvOeWI2X84apHWK4hLCxcilTcLVR4t+Bs3g2r0ZWpwp3Ezkftb5vYDJ5ll9T0zRGROsyQ9EEy6GeJSch90gItpihmnHzst3dTrw2JDDLhS7M/PZeQU+QD5rElvAtpTRnVXA7YtBLpiTSbrAyO2O8Ss7UkQkjiEe4JNALsKjQw0vlU+CUSKUqn/icHesk8AZXQlRDI8ncEDxRsfgomOUw2JTR5UYAKAIbo0iSxIgQGtxCQDk2CqCByk8wJY6imLGY0iAiQhACQBLwcox3mhxoGdxCRKDLUacwRu9EuM1mAn2AjGEIBWgMxXoKIbo4MGBV2U2UWXPxGADJ4jQwJETg82gJWaomIix5SFsWShnTVIY0WJ2YTLssdkbXD8uCYfkRnDHyol+k84lJu2bMGywSPD4DboOnNwgfJBTJ2wewUom7vAEMksK+P4LROh5QgOEjxMTfMFBKms/+D10PlrMHZ3Aj6MbvNFxh4l7aQKh5BO6jCjyzITh4+S6ciRnMgaMyRR0i5K1b8Ed4nzq5tjBnkWjQUhIIYw3jtadZYRsD4SJqJk4a97pw8NIvu4rJh+0YLLxSHKS0w0wKaIuyDXOGxIm3sRNmeCf9XdO8FtlPbHKqAk3z3qIFAWoO04uHKM6IcTTfeP5WDUWfaElmXJEtqyDeBXmPCKESFpg4l4HBFhPDQImy5P3xUnOOSj23DXanniQ3K7sKRbXuE4xd9a0fgcbUmlNyvpQR2hNb2aohGJH6brZAbuQ/XrmEewkLW46gW6AmvCC7kILGrhd433T5Q5ek+Xj/Zo8RTSZB3VPdlB8aFZJTdwc7OWQOA/w0SuplNvWHxS7XhFh7BrgIgLE9ojQvf6gwFG4KW51iobi1iMK3zmeHgoUPcSPDyr8pA4RUksVw+MxmydmDXI2AwJUiYG/rON+o/BdbbrnadkiMRzAMrXcgwqyqQVnUzCZPMW3ROT8rwh2sHeIg80PcD1BuH46jswcRRBbCE6bYEFhIq50hTLhV7okDB+qjGJ3Vj67psB1hRmJTSHQBEHrSB/fXChhi/nYZcLYdWMcioA5Cdt5cL4e52f9GRGvbVzwpOXIpH0mgHORiJc37ua4ZQyOW0Zf3CITHCOTMThuGX1xC7YuC6HVUGz0xy0jH7dKoYzF6yXC8Rrh+O7YYKN9T4wWNQ4dJ2ccWeD4VaOYzReXsIbk4hJuxxUSS9A9ogPiC8So4hNjh7mHiTsAgAr2yC37M6MJnYT9auMsT5HIkyWY+bXsleIfOgxe2StRoR1yqHg7DALZK6M6DEJnl9jZKXZ+KXC8X7GiJ3i/1NpPdrjlklIjO6B538Re43UH10hls8TuAlVy7bH+cFjkclSx6EZQxlnRnZapaEhaSBmQctiMfIxd22Z2nxwUdW27ClOkzgoQ3I6xGbBwFrBd0Ah2yqg9hQQBrXvb1WvoBPPFQLVMmVuYB+Ui3EwDxZU1kFVjhqkRSBnYzHxPVIvolLtMxbCZBWy51CNuEXXCghAHzev24o1ScYm7XdWOArarOng5GyEx7u2qzVjdrnqYL7biKj0lGieCVeZKxevoXGkdnEJ688RScoszitziSPAugLsSBSfPPLHMNQYRC6V1/M4ZouXKGsiqjcXQTU66YWf3Col7hZTr9Pf6UEh6BXBGoNFNARrLkMbKOrnbKGHnSY3FePxv9/fdiX3Lb+VYEqAWMcSxyN9rNd9rOIdAj3CyX5EDxzwJjLaxxF0k5Ub7+84WEunYtbHDu0MP2QvzFB7ty3jP5SkINbi3qnYj862q43zRjzHM4NmqepIit4tRMAznKWJb92YVhiRgVwKBPcp5xGDobVfhfUExPyK7+QJfvALufr52iC+O8sVxvjjBo7yLurSrPvC9iOvlWaFs7t2qCzxqP98wQN7eHcdeeNPB3TEGB94gc2ULgjdkPXg2EhRzkWMwCOkuOyICoaSnNzSWjJrUbRTzZxu0Xk1vnlRA1bALo2rcRSPdxij3Crl7hcK9IoadF+vOU7ILY91FKrYQdo+xzi6JxxgLImxHEXTXYZGHsAGmKTEauK2j/YHgLAhhxK0Qt2U0L1xKAZ7GH4NemlMpFXLwf6nsIXx/A+sPu0YyfJRgYcZLt5EUuVmPkj30CSK+zTqkp8/XyUuQcqxH7IryTWY5P1A0JBUnG41mkcPSc38s207kFHlFXpPByH0D00HX6xhbJ4b5Flts5D4ZhbhiWfvz+Pbs+8BC3+N5nOJPw1IUr0jsXE+LIep390nYTPnMbjgOsuVwEDQqIGEpL6kTGNhcucFUzD6I74W8J8mxaxMxtwJaYOrAJoy7B0WYp3BswTXA2SnQzZNjzGneevEq3jrkSg+gUsYSA0z4WEhx4Gc0JBU3B3sekbnKQUowhBNsJagTlBq5JGgoLUWbVHMz4LnOitEEtAtB7Tjr1bMTO53nvwNmPuWC70/LTbATWKS5pPvBMaLCk3t5ufNQAYRo5/0ZAoeMfYeb/ynYxAeEee0cZEqNMlc8etw8iXNQwkQ7BxUyl4bcJEo2hrUuJG/R2TALvt+1CAW4vr0k5w8SXll7moDfmcIUxAs8A0RnFTge7FEleJGmUpXAVpk2kG3rQ1YRGf/mEoP3JJ7DyWbUbZLLNtcLAofpEHR3C16ecxPkxOW/dWjIlR6YQQGExYQs+6tGpJajssLx/FQpNwNwVyytgLnh144/UkYZ8BBvKTWxR7jt18gaxzNqC8FXVRzXJSNCyUvIyyMQFNioQNhGXlgrClvKvSkj5OF87zPooEzm+oskYDYlmI2RAcbeT/EG2o8UZMFxQxYs4RplPgs6SJ+vh/rgNDYpyG1pCfo/Oy8KhEJjolggEF0CpysD+wtizAJVc3GJ9wRb4Dcmo1K6F8o3JPxrja6NJC+elvq9gbfKgSDzPz4yYP5/Se3ZkbeafyXM5Ry8cq9xW1X5mC3ArEC2xyCtgYBRVAO7kBrwGANA8ms0xxBYAhhlCFwE/HJqNBJnJ94NL9J1E6D9ErnzzzeUclci0UfHMrOJsfg3diYxNMKq/ItG3jpWtI5vuwaaXfwklNzyl3InI/23/Bho9uLiU1xaAwKnQuQEUBo+Z1AieMxCofP8KhRwGwnf0cD3X1jFd3hGvquRr6Q3lFzSjcV3YHlikQByOBOA0ipueiQJqwpPVLiuG0j/C3/nSY8GqhflkLFdEGWT2NAUkH8tXgyk1kX0huLXG+xIntkIYY3bFlqDbx9AUG6flERDhUc6Wtf1UzWJRXY7gaqgbDgznhWykQpx3PlxLQoFDvCcJWVH1kWAGLA0Eeb6f4d5GjJX/QhzZMjmx+LLDbwQ9OSEh7hDUZarKFEoJQKzghTFsTW4lQFkzbEUS+zGFftgrfPOPIPW3/cNefTkSaGm6JP2hQbWCwVrVclFJ0Sfa05tcoQ7uwSbyiNq3IYb0KTim2pgczujxo2L70rY0eoWxDb3ai6xoexR0bFiYylZw+4a8W9ovBQ1ThDfqnENrBVzBQF3CuVHWEtGmLD7IOLfcKZ7kB0e6n7EmUJ7Q0VBzpRIkXF0RPwbWrUjm2WifzaOCtYQe/Ki7AVwIGCULcMhVOJASo7DvLRFeHKKp7pDcUjhmA1OZsTLeHjOl+JeBzAAZhuNYyHbkwXPeVE+XGg3joU2BaQJQC8mFulNDuqthPrUoJ6wybfdAZhwxvDRgP2UEYbaFgcpHmFspkL2QiYi010cFgnQooWUBCkZ0lwffXC+olSop/noQz0vA+pZWE+pi4XAothofrUb/fBtNO6r+8ijJy8ParGeJ8kneZpTnjgBXoptYqaHg/epRNymqOn4Bpa4JLijJ0oA/lg2IwIqCr9THhagX/JMml9js2KhUenJoaaKOg3EQbXcMxDvdbAJ+6nO8iaO4qMCMv4rnffKKf/NtuxB3O/65AUKZKMVimfzvgjcasEDbrZA1HK2QQEpCpK8HHdbeKVWAj7Db7fIdbvM9St+Gq5ksxT8Yl7K3QjjQboshaMBKYsO67Jw16VofpAde7Nb1YUafc4bT3wX1rXXw3BtmEWB0274aU4bAj0u/hGIvP49+aoDRGO2/rSuA6F46l4WhqfyB8KGbyIE1pumQJkqro4qKeU0YWR1gpGBdW4kETdoiYPF55ZVjrnTv84pwsj9XygyjOYZkp2wj6cfbRpBO0TQvgjl0cjbSB4Nq1eHelmaUym5N1FRjRdD+DnNw8WQtUDGbQaTeqcRoJsgRSESfs9j2RFAWkWQCPA9giRHJPxkx/JiACmLIBHgUYIkRSTy9U5nAGkSQSJAXiYJIuFnOpZ3A0iD6ELTEMh6y9n+YtisO83XqfnGdUtgI5h7nd0g8WgFbG7UyRus+EVRrnzTlE2n5yocE9pPMaM3VQigskjgkM6bl5HRfsrxd01nXwjsuc968TMGT5G3T7Jx
*/