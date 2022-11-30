
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
ucUPcbwQslf617ys3KvjOFHde1xVm4G6nP1mZBL8T82rx13ucgbe4Vaaqxp9mArIDFG/HHYLo1zciafozqeFVjfd7eZ3gxiGNLYaLcModXQyVozKgOAAPcq8O2yYLlUVuyy+JJ1OozwfS4xSJod+lyf0twlh/3oSoQ6wVv3NNDrRtC1RD8RRcd0rze6g3jhILLquUZhCXjAbIpHPP6iHRJIGvAQq/SnnR9hb742AAR8+uEEK8JyxUnvPphynkSDWxbJm7xCReKcvVSTzvRJyPn8qy5gJ09hhvHWPExotqre64PflrOui7M++Q44n5Bs4eHo69xvr7AE8TDfGBmJHNzUe4x+t21bMvITs9jW3I6e7MfTlXDn797r8j+jIgaIQ6l74WvMIHIV3PdcJaYbr77Lb0xkAGSuFNDOMIk/mSNWVnjp836sRZzDNcqzSO2gn5aKQBfPImucztwYuRm5qlDgEPDdNbfJ1vGAo+MM4efM0RwClWRv565BfXEA45MPSpVLOE72QL0+feo0IduFrkies3TMaxe1D8aorXvZYNg5+IcKHhMATY2UPEoGoq6Y3F/HTF0fawGJYIr8QBdqNyZlLuehWvQ46gUnUwunhk3GGj8lLzFbVg2CNodODbaIgA+wM2WlOLjR7YEq24h3xXeU+y7XiFq7IT27xGxR7meeHMu8uYkd54n2Ek7IdzOOfv75sHMCRU+0Eac5sr5/p4QkBbvxMvZlM46NITSXW0fioQ0vwinxZZ+m4QGHXESEKRMwXnlZwI357EE1sixVtDr15pYFeLLlb3QXxPWoib0m6/Eppxf+EUPihBnja8gz4/9KPdS8+4rJlEAv40I9wHahWtHZwSe0B0IHYlHTa/WV8u0LndfWbvfJSHSA3XyWGmcR1y53KcHi6g+EXRdSNsZmdO+xVFi+Vef2uZ7/gHh9Uh3E9Y1SUk37paQXzI8XUggFBzwPx5TFNiNp3dQD6RPCCGIVGUeaQtb3H01v2hCMOLhrgGcAwD/gzGc3I5yKK+u5Q+/zCc1KFaFrYIJuPl6gyUPa8AVODZG9QkOL6/aqxvGDCb2arQAwUH3bFcuFeyOQiZtjD24/PC0ZMVO14e6SE9hTeFEnGXaKnL2RfQlx9BIAAO6D+NZpOQvflwlAXaqx15i96CWcf91W5SogS0ShZDkSFpdAd0qJZqpdFyWp+Gy0ldfHFBOdIFolqTrs9uuiQgNS9NESfLMzbTb2KHYkE8kl50spq7dDy4tjeQ8JUnL2jaMBLoGEbjtzsWKNrscIU+QiiwnSJn+n2n6ODz8pVhKwJmJFepAMOnMoGpTRxtxA4ZiHIgeU7jNFHPshv850yInE4H67AdlSle1FwFlMTeKCZpG1OIgVQGPNex/3ZAJvFAb4YR4yz0pcZyoZjyfgHNhb6DQJ9lOp0qUYfuPolgoe+mHkW4ob4BI523TjZqq1Ev8FTW533l48+YTJG/sU0Ar3cP9wNRJfk1tXQ+M7/2g2BJCpMui4ZEa50EHl5d8SdSFFvZxCUKyFCd8G2lNNPQ3o3v/H6QtCn0u6eRUVzzYziX5oMxMqkpbCPNe26cfcRz1ryrVqF3PpSNoDaSDczWwBiTznqbzEKrbMC+mC5uR37Les0mIu2m20nvDJyv/dcX2e4nDnXMrqGQyBGtH7lw0Cb9fLryuUL9p6pf1QQ8gMoVVfOWZEF6FQwylH3DnjDYRDi+ugIt3pSs9IcNoXGnxGUZKXWkxQdVKm74f+0BHsWxV5cVdhl6bMkySaCuKw5+ex2m6UAPq5ZHU7KCl7sUYutFpaC8S0n8njreU4qjEL3imZDBbiOTGGVSdeWULiYDPZlqCKHi6UlEe3+yMgJMpAfMgJHjR1pSFk7k1Sr9cWoklrzet9ByUYTicc/Tw8P8tDkkq5V2KJbmAVx0BhwYYX0GbiH9ZyG1i1TaW/uT6QbGq81TJOUoNXJopWq1SpCRVIAF0jsY2aQCKhMdZNBhk+RQX2/O8cb02eV1RanDFNfWaY21PRJbHJ4R+LYRrTkXI4BPPd6ABc4nuhhO08pijGrwt8FIMRVGdQ31EBHSaiYSjtUVXbyPMp5TwjL4qeGGvGjuMJ155Pvep7U/tOcT1EQrT+TxKcHnP0gyH/qOxvzRCWUOTvG1SMJkrU8x4ndMVyV1KYQiX6hBU5Juc+iJk/olhQyIU9qPg4G5AXJQbBscsLUN4hixdYimEojh0q4R1hV3NI8Ue/uLSi2zrjBODbgNr6/gLfMFQF05SsAucOOU82kwPw9XfhUg/NyZAFNIu2gFdXvyEdTm33ElE909aB0KhEWJRobXPwq4KRakSvlVSmExZPK3XYKfB9kMpxQ2jBs0z8ZhxBGUVSah0DJkCTUSzbOKBtO9i6Ezl0C7QSH4gUScChXkdCRhkFygJa/YRo+C5nv5qi9kUEhuZ+G3BJbwRqVjvgorlIThgpPlnDIzV5iXfQQuWuv5kmeVpCROWtTbtn4KSF1qKjaxqKWnQitWTsFjEvqGtyU/OaoqVG8r401ldKwUZrmlI0lUUgIgUOPDt7dGFdTnz2NqcMMFVQoBvIukotgbYk59iMw12FThUDwEiVQdWlbsy8iQk0J/jTjmlXzgP4EU5GQSgXUE5azTZGkzVPVq4G7l3eM+IFZmt9Rwgu6jb4QV/YkKpsv1OhXU7I62MnBzqkJmOgy1vJMKXsJFsYZauCT++v7Z2WGrG1YWxRbISjIPRXxATWtPjFItlZWfYX034ctDVt9mVxoJ/s425kfeNILNsjmdBUArQD4iJ7jAryL7X6BqKijK+Buizx3wMKoq+k4brzIx+YKLhzoew+E39gPGF0SGf8JgaQhiL9XO/3VU+sg8y9y+mIE3wG/b6mY9vP4LL957OjH8iiIky1c9utay41dkdavgOH38DsNYxaWswBzHzdFLTwF3pG3uqpRQgFZMvHMIt6sMDDYRFJt+XEBpF4LrpKIBqfLosqPGFCRphKk/VcBLcMCo7G86NSJrhtr84+7wtSp/g7fKsgxS8z22PUpxHqT1EASAQmk3Se9BGloimTDy1fyZ2si0tO1+aF7WrzIL/0ijynKncQI+61hfT1s9X1TohafdMdxKEZemUwm4eG2nkdoq5VgUCZ9xiS8qxMLZ7ZldLEniVJEnE0y2NsCb/u40/chB/tV1px1aimCQ5vnO0wyJo62oRopJ9dktp8SGwFZ3+b0VlntSmhjf6VzOgVZEZWkG10CQNTjIuD6ZKI+JV4H8MB2pYaKfMLfJIuHu9dAvz9Vfrx8c5LuzdCs/roxAax//71sxWdKikaEHx8mVmd3C2BFZ5squJxj5BpVsGX/Zm3nVKO+jxcTkN0XO2pxclfYF8qmpN3ycxpa75zi/E5bHXMO06kQpOFTCInfWHo0XQHFKmtlRDA75mOg7Rvf95QFVNLo9GdEF5lPT5YZ3Z43gw6Mp+DQfKMykn2xzYhTMaCdpFF/KrepHqm9nF1iqdiSDusiTxc1Kl8ReQxIMfJjj6vfzyj4cGCvwjHQw4Pz4apQe1EWBIzagwyNfxdp5ISujfDsx/tzcJHkqwHdtZraLZTcPZb+KSgP5aN9gGRFIZNiRiTDjCyIZG8v2RgKzEDCFZztncJOxFHVgCOfOWJ34Cpn/D6nFWng/vex5jnjEamofKe79ZyUxuWRLdolf7aDsPMhRIr9I7cy7XvncxO5drPwZ9ZbrkD0foFb7SwVoMJfbdMwtw3KRy7d7il0kZOfQrbJsWOtY6FmxCMHSxwKRUokeJ03zIzYx8axYQSeD16JE2DC/+LAp++MpzOcvbceeBhtaPcsONjvyA8Dy4rwYuZ9wBtHy3dGZrjM0drLBfgc0X4gTHhQLDh3RtaxIO5jFnXrRb5AHoDeXw+fPy07zTTuftTT/F6TARdlvrqbgJhqQ4jTA/JjfRwQx38DgO30kwp3RLjAas68C9uqAN2c0EaGGNvv14tzYTdbsl/gwZyh/fJwlr1JzvzWTz9Ckw6E6kvxrHxZW5ZpkcByPOc3BNxXyIJINSgdTgFneCOEaHg09YJyD0RJrxYbfOVvB9xVQr6aDelwfKd4LQLnBrk7s1Ca74C4LL5cnbUW4WrAymDpgnGwzZguhQIjZqZkgK0htU5SSL0bcIOcL30RdQAqd/J/dz9UPbkK44U0XmeAe94NX0B4PsKNRM2LPma/9dlvu/1LBx5MUJcu+R3gfsd7jGE7on4G3vjhn+A9EfNbsaaiF4BKlfMVc/hNLagl1kh+cl1p+HZukRjg21QkV2cVV/a9ZyYrWkjrHCgCty7qNk7P6GkKFRzFhlQFN67ZcJjvkPTYldKXnEqYXFcQpR+TNNc4fZOoUNlzByTGimLheFNDcKcphZiqQkLhenljswtAAX/6EygT5HtbiWo4CQk1rF/2sCX/Yng1jT6W45nP0szSQM2C34VmEGrOl4tx4hd89OPc9t2Zcm2XCHLwkzgCDub+ntYcfhHKe+UV/jg16jju4akUdiCYC28MbvXbHLNZ0V3szw8nl2BbjdMzzidXz1XpLjOCt3EdaHg3zPrVIae2X2bdryy3Z/PetBEfhONGGGmqT+q37aQLrrp+okuI0vxOLAs98TBInF8hdqNyTD1MlZlqVyVkERl4/RQQEcQGp1w5Nicd7u1F7eCx3q/IM09RMud2jw/I75/uppQiijJACyTEy3Z2z3Zzo8aBylwlopo1vVzYoGooTU5nCDhAVZDWdSBr0JYvzETvl9i2CBq0EBsYwlu6fnu79NnLfap0YopxoMJDcSTF7riLh0npAx4LzwF3UwDP34Kvt1WsCwv1889SJTVzkGKUPTM1BPu6sY5etjRc3KYGyFQdw7BOc7tAIGD4DoISBZG0FBGHuSwmDrldQ9bUnnaLmFCjZMvw/WIycEnzpjvVl1BOKLoplJ11LaXSw5R2fcDvJeEB+fnaZ137K3/xhbU0/Le9/bZdie7Oov7rTBhIv3Ty8G8fnEIpe2vPMggNKVP9CsIMtzGVWiGydtAyIbOf/rZNQKf0hjmBDC1gL962178NA71MrQ04QNnojsHrPzNg3ZzctKDj5zecNI72x03crXeeKXpOVuTDic22yMIljMU4DawOvv8/1rBFZEz/0PZ8B/M0rUQP7rfC+EvhC6HwsdV3g2CcFKsNyy4rZc5lWAbl2pvOcX0XoiPOm35F74IB/Ieg8sttIVaqgh7eFr4heB2vBxsFyGeceIFbUayUcEo8aZv3XZ4g1EmFY+to635DYQQLu/uSz5UiJFemgBcY3XoBkygBO0Kv5HH5FN/fA36itJAHzSAx1ncrgcy2crAV2L7bDn6VjCZdlqJwUXSzc3fNmF4Xlvp/T5KoMwgIyJevTmZXZLiC3xd8KcXRAxYawdb9wedVvJG1ttZWuvUUiCpC/Plp09AyB18TWOs641qtsA0gISpqRLvELfFSSH9FtwCMdwDM4Jg9hadMP9Ku2z76NNHHQ1YE33Ynm+kqaZnRWF1krsxsmSN7T7Lb/VXiCZpY5zFWZmnD7VVI4lObF6at0Qb4Or+KP6sMTPzgy+6yAZhKNQhnev0Gwqtgxrg4mm8vlQx2wIwLxRjAgdO034RuXwXFfF34TXrmdN3hrz2VVisygqD6g/BwDopU24fnZb9xDWnvNSTqcDtuI1B79RaJfn/7uWcB0smSvRILAKQT9wPt35GC+QsVsMXXduBd2gcN6mCRkaddDiTVr8tI0Pl+aRUnBH5RxTGXP0m3Y7fsP8v/RGGsCuYGGFHUBQz+M8pwaPzjExD2ytiAxICLEL/f+AXqyhczS8Ul3/3pxjDT6BRIWC9D5Ap6rY6jNdcXgmTeIgvKp2Ald2PseYM6FRKDDRI7HMItxCBqC2Evc8HE38jI+d0fmTfOrdNAEmTqBUEWu0aMmWa2HmtejA1MrRF6JwYSUT/4kSURX6AAH8S3BbSJixC+NC2I/1ygEiHcyToQHZgOqsUCdsHXfaBh9BP8j0YbEog7jxv0kcJGigpiODDiH0eMAbVp+2O52iZksXvdnfDzcm9eZc8HAda1DpccwlsVPDTQqsnwSt/B7B/4eVHl3l/KVS5/5swxfH+GrBudtNwcTfvn5IxT2CaT/EfhHNFRV1xD/BLtinO7Pl+Ky9AD+Dg4XUf0skBg+ae9TAzntrLyOXdhzngEpT30OQOmmyOtbpOXTuXjfMYRsRxa2up+5EJOLzChGJtiPBOSF4R4aZRPNCUspLu0KS3QUjBfhfUapNz7X/PtIVM9fdJXfyFMZ1AC7gV8Z9NGui2ha+QvW+bdNsT+GK/eu1+wvioycO4tepj9hCcdOWiRf6xuKtbDaCP4AjByeUphe2cFM3JiQglLbRgRl+vSMTIUNRxE2K5pTe/MSAdnqVtJ4CfTDCeBHkjISoLLuLf3uszX7zCRC0iYjGzuqBJnCNJhd2uGvsG+5L6thJKQFucHU/RFrhS4hObXdUM/4IhWmdCo3sOxvbC66f0XIzmAvmpmOB0ujV8r/2Cjjf8GYMqR/TKCQbcJ2TU+w5mIKf2rrjn6M/0tEv77M6+wnpAZ92fkh8oz/u9PyJej05bj0E7zoYV05iJs/CaDmjfIxtBjII1DOKngasx7cWRprLDKtJ2icblJVImQKxl27QsA8P1XC9/RHiI52Klokt2jZKo0QEdgsKxu+E/EpOoZc+9/7zDVlr1uRBiSggAYXwQV/oB3lAtbtAXaW5ps5YkM4SAwaOHDRsoB4Sn0wLdF7Z9MDzR9lofKQYhiA5qS5xrbEg5ENCQdyivXD6wjciBqkvbhuUka8QYQc0hrlcohL1oVx5CXMXk0ZL83ioKoMEXiOJL9i0FUGztSd8KkEYkSB29B0RyzOkWodNoNaUi0x4Y77OVYAnkh1MzYR5SiR3VjMYWOXWJWcfogr4OMHxI7T82JRmVe8xnH5JpTbvlZilmonDBT1cjoTN3AbMpUnLx8Vc8x1xsz/oeLWk2MjnFmInOWORRmRmY1baYLLcvtMlHG7xHVcsNC/hQiGmYOF6q/TPKCcgxMwiixF3+3id/v1TrBHacr/Y/Zn8bLSz+zNs8viDTsrbf3g358zvH/WNDnqyXZqbQM16p4GzJjsqvMitvWWHjUXmEIEuYyHnF+J60OAPS4wAIOF3pWtK8HqeenEvd08wA/VOutD6aewWGqof+H7LQPylVTrCxEL81hrLHmBqbWdh667+WwvVODdCZDvzNYJDYYUcgXopf/N7AXk0O/+MHsUO5QCHz1cVoMh4lMHJ+ekzdQLwvcxsmmOeaYcZs8zewYd7OM8aKGm/rhk3nracxpjl1soXevxehm2nusaM4gWh8BSe/mHQhLMQuriwfYZZvm3gOXv64I1odAgLt5BcLLblrlWRbqjbWIr4zMo/UUXCzifxfBMstdtBQFyhorN7q4oW7B1kbMq1+6wscl5MPGGkZTW9UDE8lKq5YDyjEeOM266LFoMc00xxm6pqNbfIVyZitlCpylRUUbL4DOPO0Z7hjJgm8D9O9/MEgZUyEpIary8WDyNf0TJtgskFt6yqZaCxTt90HUfgD8sbABlU1brEKWNhMOkiaEyq+xph/zkqlbx08j7916r268Xqn9iwvLWll/xzIZbs3ALiU7
*/