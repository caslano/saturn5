
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct minus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct minus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct minus2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus

    : if_<

          is_na<N3>
        , minus2< N1,N2 >
        , minus<
              minus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct minus2
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, minus2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {
template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  - BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* minus.hpp
N/Oy627PFdX99x413p2A5gfjC/pftBw8PkKM8KHvAdyfy3hDCvuNB9HeFI6E5oIPBtYgNNujJsCLGFcZqlJJbMxF9lLlvvaTqlaQKx6DU8/n9sIoDhHBDxoM4hj3qImC76dozMUAKMSATRwUfImRhOMD/6779lw/H2mJ4KPrm4SPDpwkEA0i47HLxbnKD34z1QLSmmaQjuo4lp8k7UUeL/Q8bo/HNa1KwZsOF9YBb9u624N+ZOpHE2/zCzKdQSo2y6YXmVl59woIRn5SDiD+AdT4qLtZ/mLQ+BWZrBgauAmQhMMnFb4gOdcHGyuhEFTx5L804p59XEVEM6GtG7aDum9EsrdopZMSqXSSQ4nKysfBE/F3i+tpaJtouPIz5CQ70sI5d9i+FBruh/lpvSi5W0KzND5x5m7xDjzaYVtZWfse+H8sZZGxS3L0EZF4PxGJ+5FIvIlb/ABmmGJnT/volPglP3R1n/EwlNDPjT+hYqT3EOu9A+uWsIpK20lBvg/HMn+5vExFNrgyuLMdFmSM5MsKEkzWE7aChAtwlSS8cBCsHt1fpev61bNkeTFi4M6jZ1Ws+VUcGPdW3A+/eQanJTdifsOCfAUpufPNLK1VNoH76ispU+7+tR7SpK58Bi0aILwQ+yEnQDWOQDngtnJeAlLvOc4oaYsops3c1YY87R/KTHrk/l9ht7sOV+WKM8Bv6fE8XmCQCBQJXjorp1gvBuJ3woAFvDikAeJyCjZWjRu48daCvFW5zFQqexeQpC5LVp7fAd5fD7TPmws1z1pjFrw2uAjGBUmaw5TGwjPfw8d+nXbPvcPaBr3RgLEjssTtQl0DXex01WZ5kIrJ5Y5iDkSCbHBqOiURYGQv59paj1zajYuwU5aaS6EnlVd/H1Lxe9LZmVeJU6WNAn51UhyKHmZPQvUvOXrVeVvzKfzEHCZ2ZolDoIEKe3knWdugMq74LLHe9R2ojeDdRk1OLsVPV8rFZ8OhZzbQZ90sz06saw0uUYgYZ0QS99tgBsrzvyZRMootYL/sJcitqM57AWGnuB/wpAWgd4+lcI/tcM1smxioTfDU7jS472RP02y4E9UNxTcYtKsfo4igwYd2bcYoIJQGRDrG/x/B/4tDFrGfy8SLl2rr7Mr6j86qzL0VJDIPRBI63fcQ1s65A3B09ipOgCs7fKUAqPuCom/cEsKY1YYt+mqDlyb7RAsOlS9GLjgEnT49riiX1iNHzhILWQ5O+WYXsZB9C8+U/4wLjm2N2V0EXv3CyPBvurG0Qul0GS+w16Etknvn6V3w1/MNpw3EmEHPUzg2HB7D6Qa4RrJC/X4d3vtjGfObGrkG5/r7uTci9Pfw5Hyi6IRelrzpRPnJ5UvwLp8J0rMys0z2Juuq/f6XpzL8m5vGG34eEFnyZmPfqfVXoBsrw0SjSnJtmBOjKrUBsVgd5yJDMoyqTS+/BE/Wh5/MQGKdRfLTnMYO3K+qfUF8p17ycsLSgM4C6M3lLEX16rxW4tvDK9zaxorMdjCLhoONWhj0eo6QPE9UGoSGCiOq9OUsGdWzow0ZJ7OTJEcPq8gwkoY2Hra0c9bTAe03FhS44dHdYEc0jklbVUvTS7wlPshZY0xSrPXES4VEg3ZqVPqgVgdi5tKA2nxObgnNtPNAuL4wP2G850A1j5293i7USUQuim/ycFvK8293IIVIAjISg0WupkIb5A4oNBXDpNspL63QBFmuDheKeUdVgojxeLZ8tBQXmD5GChfnm117+gA8PU0ucWFdiUz6rlS5WaZ68Chg4YrsLdErMjOqIuZJK0LWGtVEqVbi+cf0emjZ88d/xMfjEn/wmKANsi+cfxx1vXbDB4lK2livxSDOJJYmyYvaGe8XyRt7aTWBnqZhEfk1uAQfgtzD/uZsAB9lJsm7EN/KMUtesnje5USmewf9LoDf1gFwOxsz8b7RTtYrVwMn9H2TGA7DnzgJknyqU+3jN8RG0zRsHfeMKKnuHDWasUTuH1E9lFe3gg/IZZfDb4wIzY4FNB7W9ZqKbMbJT+fJb2X5lbaOdVmseLlnJG7dP7MlJtuSFFcioCFcypKacdSymrOJ0vUTPFEurmf+9s9NEqnI0GzlOw+DcvgRPve2PXrOll9ZewanWlIqYO3mdE7oSqhoiFCRwspw8rGb8ZLmnuWk5BxkKzOMJ41HKGDQkK1HkB8yYmioX+hR1ItgcoFxgSk+8mNkVR0CCI7yaubkd8rN6wT+dLCUvqPgLcZTGaSQE5dAHTERV2HsmFjBW27ZNvq47br0KZksbSWmGYcZwPv8oBcHGb3iSD/OcwAFwID/LiDZbItyCCMn9yzSRNrNbMgyXcvSsSkWhdlznMJMyz9dy1/cHsMtFV8hh7PKRFSpPkDT3k20boLOpecAThrQfE7Eds334sTSEmpbgdGf5JSlha0lugc6D51l9EJ9mhfK36mPzDROaDCPzbRez2uZSb8C1/e0b0x9ZggNH349QX3kZeYwh2qr/VoqBLmu/XrCCoVzhUEal2u9lmuvdasBFaCu1T4rIF2XBClK7EQFf0u9ruf+LlKzhQ1SXdgg1Y0zSAzEm4C/xbsU9QguyJ+xdFAsKgVsqAN9RkYqAzzHDsnZB44rBmFqh0SF/ba+2vlcWi0HLR3GdnIwMYBM/+p0REqSM8BujVWDsmqd73V2WCGGRXJUVWpKlFt9RtOay6hHXJ/oP+7pqOZzXf/Wc1MU+uIpdQCWTMpvAamzSAyWqmGw/o2AwQir6zCs+Y5wYi7tox+VxhRUcC0F/XxsQYzMdbAZc8nmpt5G4EXwLUGuWVLxpP9dApnrtAhzzWTdbHAzEkaOZI9udwmGWNBtBYtYduX4bSgSv+Gy90T4zWnG3Qh3SFRfcAy+G8xfGGN5Kkl4p/CEJGNdQ7O6qc5UsbWZ5XKjAtO0FBHe+qapEN4eORrhgb4dBXm4e4e6kiVIXHnl10gyWjvrRdwI0EhGcW8q9sUbvxQMkjeDHmCfkV8rFyVvku2q7WPB9wbgT7ay0vaRIL+ClxXLbV2CrwkubR2CvBEf3TtnxHbvHLNrtqc9OdtzubqmM5S4lBtuii0i/1IAe4OrCKvwtZXg3FTM5PguZRErTrM0+ciwk0WEKX31G5zSX60VeFqLlrZ4ASSPTqscg0SeruQczzfVNds8B7DNhm6a4jgoQsNMKP8PuMXzvVVkHLOpnQvJWAj1x81adXrMvIjcRUmsONWuZS83Yk1KlWq9Ji9HJkvXkyk/xkq8z5d/qlkjlsGo9fK9M77Ccn6ml7NKy+BL40W2fDiJmYbRJF74Bk0iz8ukl3WnmTqb5Z5PYgXnzeHCgo+AjFILWDMvCVub7elI9HRVS3QT2UwbyYHgu4Ec4Qx6jboOfL3frkGriphfZ5C3nghzyFsPEYu8xiDf3k0iQpJ+XtqbQkAqib6auuazueQMdJIzcATRWQbxOdcAzuZDwp2ayIG5NdGgqSLegNEwW/LCyNv2/zJ106yn74U0qz0HFpOxvU1T/pEzjGfJP+96H8ZJhibXeiiLawfSGUJju0QwBAnue0E4AAIJckcCDY2R4821GRiHMhoGjS4OnZFNN1rajeIZ8IQ3/ioevJHzQb/xHCFhjusk9xnuBNFKjiwvJQOkoYq4rL3YdYIX6dyy9mLz3easvdhK12KtdYL3HYPeQ7KMELVk7HbHzbhp2nOgnEy8F2Gz50A6+SVUBVdiVfqpzYZQfFUy/OEukN51K7SMCamPhTVLINMHMVP3v+hoahycueVBT+0rce75VaZTepPf4x+BaPmbHqjz9kCR6EibQKS4ndc6gmOBxTomo0LGfLWISs8BgZarBlf6SseiAy0xfS3wDqIS0R9xOxuRGVs2auwdisUx6PnCZGvEdwS53Di+J+9ooJ4cCeo9CXI/p2o4uDnc1pEw2Ilo41SNEPtO9+IxhgM0MdwzPQdI1F13haXg9VEpKFw/TgRkEoHaDTD+TxmmUWu9zyt1TDsuXsfdkN3bESO/KdbIP4cjP9r4SUZ+1ozpjHzbtY182+Qjf+E6Rv4CjTwGY42YxPpIC3UXRjvXNbdqaMywhxbLhHWgHEQ5Vf4gLgP4XkUAmoR+b7gBmq8dxxNyGHfNQjNV+69eR/vxndpV49p+7QLdZp+kbp4DZpLPfJfbCK4i+xYrrbGvjlsNlV7KUflgSRl+lCecq7/Ivypz+FYQfsRlZ1rREJoRV0WjzskgMaXWPPxYSLW9DpHq/7X2PeBRVWfeM5khpDp1YokaK1raol/q0JY1VMFBNxBugsKEmYRJYiWgFtk0xdZ+Jm3UJCLJYK4nN6ZbYqWC8vWh+9H9+Aq6uE0t9EsAzUSyGGi0AySadbPrpUm7caUy/JHZ9/eec2cmYYC0z/f4PJi595xzz9/37+99jzNZUs1j4ZZbYf6Rybq/3YCEZWeG5uiSlrfG6FR3y52n43xbcmyLS49F6QVz18EIUZgswZyUTt0VYppfLJwtb9+8UHD9+TrLgTgYMRc85E7Ir1/9ZZL82nwJ+2MwAybIjxobym16sNnd+nNY4IqWi8czPPNgCLd44WK2xPnMMiwWsUKRXiz81UDntQBMMeQACNJ8Knomluc3imaRkr4RCn3DAI3sJchIp47fcFzeKUIyi/lCpVvCC6piJfKpeZQe6fVtJDi1IhX+SLrMR2X4diQ4KCT7bAj2oIIr+FrxzUQti+3Aim+cqP6j0B12Dg7YnYcVCH0F1ycikGESd2mss76/Pf79NKW1blcEjT4O//HG1KQMxfh4VM4coPOV4vyiBB9ebbufxwnHcShWc1Vly/MvypGD0NAXBoNbL2la3xoH8q27oKhlV7etd1sl2a6+UZrjtsuDVdhICnrLVZCC6ttOvGezCDg6MWGwqTg2ikla0HqS2cJF2TVKYtCTu9Fk3f+nwTuenjD4UMzd3AHv5l52IRg7cBrYYsDZ4l2/jpNtOTieI9qf3rPulspPSaUiVaLh3lCs9geyhfrvinauXbQ2IHzNVXbD+TrM5XW4QAYWMdZPlX+4Bf5h+GCkf9h7tu6f47SOD0PDw6lV1X+qs1RVM7DSHc/P7k/gBY7+CQjawYpOxg1onUbDXA5y2tOthTkz9w2tDDH/ztE/YdtSQaNokfUuZvC7ZWXYrQAb/Kn5chrpl56iY6sd0IPh9x85IFdy4MZdtk026WV59kOGb3Kqf0fqVP8V77ExTWh7Gmu5nC3FHR+AWfYmrgRQFwJIlGluD41T933CLncESFmg2xmtybGCYXPoYyZPGBuRCiJP7/8e1H47IBwZuhs+vzJ5mV2nCHbCdViYIdEtB3J7EsAb8baZ/hLfvVC0iK89Wcx3eCyNe/M/+2QC2NHRR63/VXjM20ps8Sth0k8CLrkhU10Mddl87ZfHX55Mwl/OXXlx/KWFd8yM4x0z/2K8IxCU5v++PzXecWRSeMebk/LD33jfZe+7af9lEr4t72L4tuN6xTm+zo8OSP1ugAQlvq3inDRg+AaSnwHPVjBXlOaJlUvhFQae7QBj2/ZUttk3UfGIHuzVtY6Ev8xsfYRd61dV1soCSh7HnetESw9MhGNJ4NGAAh5xeRbevgHayRTDoqbvgpIOJGGQAGA2gv3F5sE7LAHUQTs1yc0FCAOoGMAug1qHDOi57LdZOkv1VdzqgvazLOEWNRLWygHl2OlORcZGfxg/IFa+sKqYOF1lozN5+AG37RSbJ9gGEWrHSS5Yy6iFAlGQUbkZjidkmHsAmTkyKpvgJ6Pffvwuzah8lH5D9sjDbyrf/8kLXH72A1aibtRarmp9XtWar2pdoWrlqK+cWSW/glZQ/g+r4q1QrWxVq3+VrOVStQ6oWmvVV3bHa8n7yifgcTEBfiSkOVTEeNxD5h+JuouIcoDtiTvANBOeorWlkJYldHwMuDCG2kd0bQAxe9ow3POP4sJvlOsjLkTVlIW0hNr+EdpeNl0UZouyGZDlCmcSSRDPsZUjeFJIWxu1iSBdv3K1rEwFeu2uA9CWBL+VGK8vKqIBAXDVmPCNFotSpz9QbIFeTVHAoFdECs1elQR6HaoZB3q9IF6Xb+aY4QF2eKanaPomz74yEe0oDQaDp04oRPGxrpEvOI4pZFfpzMMxdk+NObodB4ENQwDUSQQYD/3xDE6jq1sbljAec2SaeZAe0pyBrZgjzjbMlW/YWG4/rQf7ANnHpfIAid3WGHXU3AqEGn9UwdKCUfE88/TfAzY2ajivpw+jeLrQGIhW3xerKRWIDBliR8JJT5ceHIAjobRcRA/HHKd1X8TQ+o0iv79Yrx8yr3zxWAxTyXA0Eqt9Q3Ss6S0Adgsyiv3mH35KBep7RzKTsWjv4KGssh8Ajzj4jMaD8G3kE2mZkQw5q6xOFU52gTyB+Wf4IRCnJBEMrLucRJBJh9sot4sCF0kdkMHfQcTkynJ3CPdAlJHg1NlwAwlOXm+0/g46JML1a3PNO2djVKHQG637d1EwX5TOFUXU7QO0KkFi7WFd6/dG3K3PIgxBi4x81iwJum0jDvZn9oc6a//TW1Be/wdRsNyhRapwO21wlBWXMTbinYQRT2G6o6KAEV5SEnvrVIQKJYO7C1y5x7mLT6p8uLHav6eOttJpF87XITL5Ebr9Rr0C9FQvAcqb1jw4gJC+4DAAiF0ydpYkxCwFKyzNMZwL3Tv3A3A4JIpyHGEphgwAWO/r8+ebH5+JT4GA4Ah8jTbK/jAc3MmJy7sGtc7BYO8lxeXeuLi864KilrjcX+O2SvLtf/0kEjVqEVz91+/V9rhbQsS1V1mR9zf+z8RW4v2zaEI8VxntoYa5Zbg7CnvohYbL7aHeatyVq/XPK6Bt8zkg21rPMW5q/JWnJDREWKJBmGL1NGmR3pCwSNORUfd7k7KphXVfLx3qefX97tYPGAZrihj0ANxs4m0odxtg+7yJTOi+47dQaQ7tIsdhyPdVduyjdDr8dNKCYdKEa7GDSia/TnsGtfBgcOCS6zQQX6c9FxS11mlWtdsqSevUqJmZgxXhQi+NsOXLfJHvsK36aqFFxtsSjKK6gDho/gJyFBR/bVgm3xWl02n0pOsXB5i7HzTXrpRFSCe3ScNAwUwRyPDj3b30jg0euMr3cbfCW4Z6amu9ReX1j6Gl5XOd3tLp1Xd5+PCJg8Uiay42vd+cBh7kM1HyHlG6XCy9zulpRSHDeR1NeAAfOFHBZRY0dmfSJxpjj9b9TGjDgOn9Z3kSA3n5e5YwYd4VcKeMf+G7Bc1//RDiP7LFGL6T4Mq270H8t+6znsv3Wc+17rM+KepPJt9nHU3cZ32y2Jzy9xMVgFWkAaTI0NrRaf9r5f9Cm3Vf07AdQViZHIQFb6R5O8w0YfOxgFs9Nzd+HEMM9oP8JGsSgVp/aX9kL5TsLmNzJtxflKmismSg0ISXVshW4jajfQGbLaX+InSO6bKLvOkVsaGJ9+VYL/0zYh+o/H8IZ8ICD2lWz/B+dhkp3K1ZSb9SJeSftP7yYVFq/cXzF8drVSy9TP5cGk+m+CgUq/5m41MzbNXL1QWZZSV+865V8SFeLRbOqbKRfGf91DJEcQ4VSh72HL4o2PoZzBB5VKI41nf/KhXp9nQXrjsn7tdH3M+STzOtKFwc99JZiLgvyqGRi4LZpbrv
*/