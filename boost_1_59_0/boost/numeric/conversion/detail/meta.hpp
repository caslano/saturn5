//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_DETAIL_META_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_DETAIL_META_FLC_12NOV2002_HPP

#include "boost/type_traits/remove_cv.hpp"

#include "boost/mpl/if.hpp"
#include "boost/mpl/eval_if.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/mpl/not.hpp"
#include "boost/mpl/and.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/identity.hpp"

namespace boost { namespace numeric { namespace convdetail
{
   template< class T1, class T2>
   struct equal_to
   {
   #if !defined(BOOST_BORLANDC)
   
       enum { x = ( BOOST_MPL_AUX_VALUE_WKND(T1)::value == BOOST_MPL_AUX_VALUE_WKND(T2)::value ) };
           
       BOOST_STATIC_CONSTANT(bool, value = x);
           
       typedef mpl::bool_<value> type;
       
   #else
   
       BOOST_STATIC_CONSTANT(bool, value = (
             BOOST_MPL_AUX_VALUE_WKND(T1)::value 
               == BOOST_MPL_AUX_VALUE_WKND(T2)::value
           ));
           
       typedef mpl::bool_<(
             BOOST_MPL_AUX_VALUE_WKND(T1)::value 
               == BOOST_MPL_AUX_VALUE_WKND(T2)::value
           )> type;
   #endif
   };
    
// Metafunction:
  //
  //   ct_switch4<Value,Case0Val,Case1Val,Case2Val,Case0Type,Case1Type,Case2Type,DefaultType>::type
  //
  // {Value,Case(X)Val} are Integral Constants (such as: mpl::int_<>)
  // {Case(X)Type,DefaultType} are arbitrary types. (not metafunctions)
  //
  // Returns Case(X)Type if Val==Case(X)Val; DefaultType otherwise.
  //
  template<class Value,
           class Case0Val,
           class Case1Val,
           class Case2Val,
           class Case0Type,
           class Case1Type,
           class Case2Type,
           class DefaultType
          >
  struct ct_switch4
  {
    typedef mpl::identity<Case0Type> Case0TypeQ ;
    typedef mpl::identity<Case1Type> Case1TypeQ ;

    typedef equal_to<Value,Case0Val> is_case0 ;
    typedef equal_to<Value,Case1Val> is_case1 ;
    typedef equal_to<Value,Case2Val> is_case2 ;

    typedef mpl::if_<is_case2,Case2Type,DefaultType> choose_2_3Q ;
    typedef mpl::eval_if<is_case1,Case1TypeQ,choose_2_3Q> choose_1_2_3Q ;

    typedef typename
      mpl::eval_if<is_case0,Case0TypeQ,choose_1_2_3Q>::type
        type ;
  } ;




  // Metafunction:
  //
  //   for_both<expr0,expr1,TT,TF,FT,FF>::type
  //
  // {exp0,expr1} are Boolean Integral Constants
  // {TT,TF,FT,FF} are aribtrary types. (not metafunctions)
  //
  // According to the combined boolean value of 'expr0 && expr1', selects the corresponding type.
  //
  template<class expr0, class expr1, class TT, class TF, class FT, class FF>
  struct for_both
  {
    typedef mpl::identity<TF> TF_Q ;
    typedef mpl::identity<TT> TT_Q ;

    typedef typename mpl::not_<expr0>::type not_expr0 ;
    typedef typename mpl::not_<expr1>::type not_expr1 ;

    typedef typename mpl::and_<expr0,expr1>::type     caseTT ;
    typedef typename mpl::and_<expr0,not_expr1>::type caseTF ;
    typedef typename mpl::and_<not_expr0,expr1>::type caseFT ;

    typedef mpl::if_<caseFT,FT,FF>                    choose_FT_FF_Q ;
    typedef mpl::eval_if<caseTF,TF_Q,choose_FT_FF_Q> choose_TF_FT_FF_Q ;

    typedef typename mpl::eval_if<caseTT,TT_Q,choose_TF_FT_FF_Q>::type type ;
  } ;

} } } // namespace boost::numeric::convdetail

#endif



/* meta.hpp
fEXckVbYoj0RhanCnvgKLeyh2tCyHNnKmlG1gOmreRx8oZXHpmOiB9ljUw6+n0eidE5Mn7OE/SVGHHxjWubAwKJWDQEJijhCGGpkWdokxH8cK+57qJbrT0Etc8E6Tt8MBERIV36fpk94XKeFuIBXA13DNSwWcHfwXM0DxNzxBdxdt2ApNz3oCzi32lSCplF6iguY8ldSpThPnGUX1k56KsjdykAksyqnhM86GTLf2sx3p7uqBjv3SBveQfVRyGstLVYeNekSAg08667Eil02/UUi3R71kJIE+TQjJp8a7KVlIPOqzoj/BtR4cEnx4AUi+ofZ+q38PM4+oE1yHfx/UK5DGRUWES6hbJIKcZqdrqHnxjFK2eB0D9btR+kr/1dcE6OsE9UNo8dv330t+SuwcM2WA3zPhZV3RgapsOEsjjbA7Sm+u4lbnWOkAQtO0XYPG/3rXIV3Q2DhIkxF4k+NuAYBcFI0hXlzQIpR/Llckn4BTfToRNrNMKGFC4OFMmKOipmI196sIsRq2LMGygCj4zctc6m2Ja1XcEt6T+2i43E6NbLaKchqqRVI7qQ1lLl0YPicZcPjnIhrQKUzTFTfeHTOWjKfs5wDgbfR00GyN2wmy1SCbeV/ajhxZ7MvFYW8acUjbBgetmwdZ5UTaX0/ZgcJvE2Uylel3HKHJuqfFtpSX0lcT5M0bVLX7f/PbUZvxQ9n0IfDQOxhS8VneA4swHBsDIYJh0Ss0kOnRbx08JJfd0izSHRynhQ4wMd2M5OFy0Bm4GnAuRuUT6YlI3olySlCVxjTPA6LT3elxcWnZ2DGVLeC+tJxyPieszeYiQG2N3xGjdgb/qJHpxcDQlJmXpIhavkyY81EZwGJaAHKriFu+ZLdg7L3IurBcWX4v5AgsvGnmRXlIus5rffOP+SJKHI6talDmdiVd5WI94rcE8bY9Bf0r+v3JDhf3ifbWWkhj3UvWJ5bcB9GuZd6cuFZfHy7W68jPr59nv58uH7PmxYYsAZP+sdRWc7zaXZW3zyiC3mRJZQRo4XnS0lCadBlk72Ulp+KAqEIeYeKi3hMd35YsI6afapmknPDcoBU3XgmkwbbsoEUy48dz5OG6xuhvN252FY3lt1vFSVj/mRA7zoGrqnfUO46S+6EWgrWlErYQLjacTR3Nqw/suE+weXo/kHIIv3LH2PxxT9+N++q8cXkD1fpH4/xBazIWqxsAu4sXp+0pPwloz1uJP6ogCxwP9MscIh5oYK1cXZgKZ4CwMY6zE6Gb6oNxjAqfvrzqKx++q5Q82nycNAMxnpdo3xRMx5HtNha6lF+dt/H6vUa1OIChTk8Y/YPYIfG0ykguHlXQK3lw87LBHjdn/6yAV6jeeQNCKDh8cwEtBDccNfDceR6aG98lvQrngPdmw5ISvahMyqSg8cQHzWHwxuhEnRnTHUunmVvfBCF9cXZ9oYlJuGVn80WIsObf66kpIqR6P9BMFxfzB4Cbrik6iVMUoFPfLOZpxJ2RGdRpf8mTscLBR23N/w3cVcNtAUFidt8iIRqqrBoqfqBs7v2TTyUNZ3bymgXZKfJT2Wk+de9MR6MMzsgq/Q/3Mtigk6pQcf6AfQXd/gBTwlpVWHEw+b/8Eh8VKBDvYZAw+f7gpGfybzWfC9LEvP9pSRJ542RM7YHZ+OTgsp4JJiSZECCaWGOBElJBiSYCN94lOz3VXr1sYlEQLbaWi0FVV8Z68y/pHxl8gQ65XcbChZvvY8noFlD9+NZk8rQlAkga2VRajYllaiFlQxjgBEgAHoq7Q0vEh6yzgJlGtTjHKyNRJez96DaYw9gtfX34tlO6xrsSIFvhbo8Sgk04VHePhqrrbCSeQecD0BtBby29wqU0ANUWzurG2BjhJm6Uz2puelcFXlW/P9GHhjCX98EUKTDVtYt0JgNwmu5Pktg1dAB3FbKHpPdPTxfFWzneDgngHlsFebvVn60l3skB+ptUv0YPKnZGk3KP1ptCnl7ipXpH43n7L2rBwhKDyW8slVLpejko6z/zQQpOgZ68bl/ABks5tObcJ0q/5EPTRuGnzlfvIb/eRUylsp/HBnu0429A8bgSGmaZHTrBm4GFQWAPT+02iRDzjv/csTowpi0t4DXXabVbRVcK9Vtwrqr4usG9s/qQX05VHwtdxYcXxk6gxCrBjwc/qnASCHgurIo55PN/Jhs9o1bRcwCvSplP99K8pi94SDfbQPhv9IJlJTdKSe4bvdjUqAuA4jdaxLZUJVJe8ZJi5yNyBHULmA7iIH4zsUk4grrW1LRdmKCZpSnf50nlctLravyw9QU1uJfjTWc+tdxUmHN7Zg0b+cnJHgXHEgl5mRctQmAcG/Cl2zLTnLFmZ8FLOi0X2hNpCuTEwqWr4oNmqnq9x+TDoj/8P56/PlxspSfHxo+9+OqUS3t+OSqHv0j5dO4Dn5H1KZ89tsYp2I+JDiVUdOFaP4OSEh9tyCTPwM562qUAhTpbSSN/nFIDOHnP9l+qw5LWIT8eZ0VUxNt2DqGe1OwDetTdL+Kljmlif71uIPDRgDNyo0Pk3PjSsrXl3+Us2cyoQVhPSBEWb4qNxWSb6SHGwfaHiWH7zWksq4U3FqkEfNDJZFzuJ4gMy3iGrJz/SxauaLjiH0Vh0lNR1d5PGUHz74ONaJ13yM3rSPPS3Q1U0+FmjbR5nZKbttJTR6h6yt0fZ2uu+m6h64tdG2la5iuHXQ9Rtcuuu6l6z667qcr9rki0qgIP/5Ej3Vhf/cADzoRGNoA1Sz5sgzg4tAhoHEYlcfngwFGHadYJAqdhieOG9xIAExfh8cZH5CxoLyETUe2rCzURu4O6ilysAS2D3MKl4HAzTUBcwNtldSRVOHags4x3MdlfKiREgPRpzay9YimKlaVjxQPTf4xrVTJdGXzr2ktp2nTL4geOnkn87gG0d6T8PTbAYpVkHxfD1BAAnYb2y7z3aZzl24tSWqs8/fAeHOgnehUvVT68FIiuypGYh1LwoWHXakoH74fFAkd0HKBdv7seIptb6CQyoJKXF5PQ81+1vi6iSvovVYAODZYxgivigAziwUyotKY4C434qtiHa5OKlohUy2r/MkO1xXfTTHrGfrbCzf1cehttdVCeQ9HikbX5ZtJxOpALfF7zUStTQ1Oc/SqMxE8E9m2zRaKFLZ6Ssmtxxrz8+EOcgltClhpjkDkyBvf5nj8zVGmXD1ffvjYiPiCCwmAthDPBPDdwhp3k9DvMwM7Ll5CRY17Yk/JB+W4cgzQH4iPgyiPP9tBtMefyTZySkTtbllJSwmvI9E7MQQFiRMapo8GVfuL7UW8+36r7u/U2EXubJ9+ioxbUlhj3NKFAwd39aoQZUX/xwOoC58+IGmP+QD8/Yy8jZAZDLRsxdHVZwVV6HYzdji0CbtarPReGaN/yL1z7Q3f5AddZ7O3sAwerf0ockGbVo5Bl603Y1+89bB4v4DeF6bg+yb9fTz9Ji8/PrxpNLxbDmrDm4JrJo1tQ/AUodtMueajuJ9mZVp+2OGy2ht+iIY+Gl+5fXtY+ClqYMgWe8pbNP5L/iQ2mB+Gzm0P67XxSIlFMKX3HyfcvT3/ZDE2/CLQ+Pyj6ORXVIrZ1bAPsOt+9z/OqOJjrl0SFUFD/gwOHWriJa0JDpH4Z1o+PX38eF76ZQTAzW0YbIj25YhvBq7bNJQWt6FiGugDeg+xd8QKdNCuYQ/+HiFAUPHZHLSH2IO/pmc4Nt8XYGjf/JWqOiP2hmPCnieGV4QqtoRaYTmWOCPQ5i4cSjSF7cLuO/+zFpYsKZ87fVmOA4g79Rn4tbLkO+OkVYbvSafu/MQ/ERbzKnm+XGPRDuHJPwp9eLGdXcYFNG4IutRdOxVLVcSZ00TpMrHSljihfsw1qY2aRjrJUWfz34ghIcYWWrJx3HU2X3JLGu3QmDcS8+rNwfTy/iHZfcWxsHszLPX7P0zugr9nwvopcc/OPeca6j7KjwjraT9zVJn1YR7mt2ODH737Ubty44fo0QgtVshz5EKLaPHD7sQnsf3SxNZn8wR/1RLqtNQuPFjIFqixSP4U0mzxYES84fzZd37/ytXlAeH8LdDW79VsK8u1DX2pMWwCuP78UUMDhvuKa5y8APzXO3XFl1Y6Mirfr53fmU0sxoRTnDlo1T02fBMjjUcEj6WvvT3cMfeIcMy1B60ogXMnZHvwM/LM4wr24B+5YwcthLJqkeYaFiQQUHyEDt+9RDqFk609eJ7g9Dr/8X4MaPZgB8Uj8OXjz+QIZW94hZYMLZ8GRHTCIP7Sn0yIFSDUkfjhcyGXwuYjVtUhVvmcw/HptkR86j7L8WmI8Onds4hP0STAoEZU4eQW1DqHnsvgVrpcst45333Okq9GkymfJdCifEzlMKik/QT5ad+9QTWaF6gbNEAQk7FflHy3amV7lYvfuoBl0zWMGRubhgDxoVKF71aEIgpNZCE5HnGhxUQSZz3rhPcA/ipqSeZxOsjfKjt45d4EJusO1khWxcmBsJ1OIVNAcL9I76HSZDJpaqg22cBK47GFWkG9RIL/qN9WBhh2Wen5DfGZKZyRYlMEI9pJuOaJFKTNR3yFx+Ek7bHfseEhtFcuKqlaWfoGTxRBVkAoNSDpH98QeCjDWrXcWGJVRcwzO06eevga8vtlthH5cmh7svLMKVUdFh5Q6Lun0JeeoC3AF1Xo9az8Yr9B+BPC+edhE/qjGyTz23iZ5v0jB3zfuDxeM3C9/s4xZ+erBanT/pUpWJiuJMGxTkl0jdBoubbcfCgDwM5NqGd/MSybPNF0vuoADd22iMlEAjV0rM7Kns8W3e2K0f+S/HO45OquOHbR9ubELK3v0M49R9vXqk2lhMq4Y89nKy360kF76eqLSuePSCCtESvAd1ugDTc7qXa6RmKQwiicwqBYJ7uHZO8V5h4KHgU2GZb7dDx5RRI2gVVokrxSEdsCAm0PU3VT9OpMenXYH/rYxD+WV1pgl6wYIf9kCUlbaOTfNpvgQBJLhDxCqeWpV/HJ0Q50UE/yqOuK8lWJ568D/s6dfx32j3Z+cvKVSMorpZrpQ240CIuNHrqSyNvoo2sNXWvpup6ulPm16TTdb6LrZrpupSvqMZXChg9JRRdqQsqjXK45r5KH7nFlwuDIKR1iOMn9wy/nX1K2dXA2jnUqTx2h2wzHumyfHZbEj1rReW/D7zDZ8ScfTbsU+J058M4ERRqPRmfiinqTkdt0W0vLirirdry95fI+Q/zT/NH80dCiqFmMaLZYE0aVM2+m7GplrgzuOCby2bqzZLeC54U2IqUolL196J3mHbA3XIbXhUIVZsCjbsKjQF03UfseyYceUCp6nmkOwn1oKVzdk9uee5h8x39Be+DOQ4AuD9xySMMnc0fIMpWt7kWLJSARYC95sSmU/Weg2gRoRJSifw/tFVe4oft7qDPsHIcA62WZRr+5sWhVRK93hbzeB9Dr/bvoMxf9qrKLPpiFqT8zAby9xVf5ZDN+cqfy+N/xySb0zCuj5Y6uflnoIOAKMxfAsYNNlt1HZNcxo6YCGHVgTpbrv+0Nf+BHU2NmJPINpBq6cw+Z2wN1syTZfVr29siuLh4+NbN6gjoJD3NbUPlkOutq/711/aeVT6a2K2nwICn/nCbEi+3wFuW1sXwsgGA9JNFWS0UlaBzrKqJeRx9n45G1EDyEAmJx2pn2tydAY91n6BRTXzI1HVi4EzkQ30ws8RG9Sn5m3NvoVR21f3jmw+63UR8ZteCtcvtYsvwTTmNTJRqIumRXB7mRh6vRtZwOmyXMmSmcysOe0bwVO/H7Vu6Vfj3eiimdI3or6v5dsf1zwwDSj9GW1Gor7qWUVuLVY3/jqxoNE4ou/9sbHrdgmDOXJn8VRWHq/X3CWRdVyhRQSA6iPOqKldZyJ3uxELmbVPA0ppJeViuHuuFG3t6FP/mhHgW1bAv5VJG5X97eg6920Fdk+mcbN4mlOptTOZ7a7mrZ2VgIB8PpNAtSWyHqwHZqHVoMYiuiRe5gwPtMtffXwGYXOMhF2DuA4DUeJEtTwxp4jlO/1YxTTxnqisoo+KTfha+2kHx81B48hTzuFiE7buGyIxGcLVu5emZh4ADXE8zlqg3mT0NtTQtqssr40OYwf4a8zsL8mfI6K/NnlcjrbNAQYjoP/0bnieP4y5WZ60qzNxzCe38W+3WuN8PesB9/eW3BkyBzbhQyJzWFyuOpIDefZN40YBW05tKYN4PcfzJlj5V9F6UdaJAFCZLQbqVWny+NbSSNarDjb5xZlEMddNAcj+PmMqLG1AcJ4gTuEN2zTDw1/dUwPT4CV59rOI8/51wQC8Sx+ReOA5tPX7Bu4vR74QGvArn9wMEwJ6VfwR0x1AuPlbYLY3TPpe3Yx1BoL1zRpYuOhg+1UrcacIjVmUXiZPjt+JTNw8ORi9Vfs2ALQeDXjlc3wY3/LkZNOoKb8VdO/iX51T4ai4LH5h7cR+KAS/hz+Rfkh6MLA3U2qc1EHgIzNRF6OFyIIQpRXduxrui/t/BkIwRnjxjS43+DIQX3wK3EfezGshDB5HDUgkpnIIFQ9BUcpfji6b+MoYTZrjS+LKqlKlXi1BL+Z8JrsUcrvPbcGCm0HT8vFk+e+fEYnSTxJ3v2jpGiK5FMkL9NZ5tZC5hPB2ZgF/DN/NiD5LZ0fB8UhMUM8y76SnNRSvQa1m8JZqnWD6geidxNeZeTu0xJ8/ewIOUnRdYAqk+5Jmu08zguCB4vqPoyNW0m9XdsjOtTimNVSslalRqTF38eR47R38lWIg6gAHln2xVKue/q82B8nZwiF1jwQJICm8PV5091uBR7wx9RHqyoLYlFyuGCzj/qcKehSrsPOAvWxTYiSTrxae6haDIzB8Jj5RTmUvDVDqRPJ4Zyu9DTWi614Nnnbgqocw/x7EIodi0SMhtwRDDKeqBgp9toqT7hoNwYPqtjI2oD/F/B0i0xUa6EuXpZYQ3Uyjy1sneQbSIK6b7ItjbQUQrQqHdIVzfnYPGtWQCu3K056A7oRrcp87s8tM49lNuBZw+OEVJsJ8IcfnX6PGyrR5uDG9lGbKMQYMW24F6V6+4zj+v/AQ5hqc281EKV5boULMDhswOLnRgyd5nT5cn99Vhya4uQlXzZgYNcdzMlcJA0Hv4JfAeB7/vvMXHptVUfsm+m3gpqoRDIJy6f4D3vR5e1wMEjXL2BJhBRpT34Ex78W/dLQu10Q0+xmSgV5RkgbmNLrWazqL6Pipy4DNVPiP8GcyrEcOKHJMQMmV2DfG+kUs4Oe+gFir/YRBrm0Tse/Yazo+7r4qF49EjguRrJdzfltJuJuKrJYz2c/ZByXX1sXOhhq0WezAEGMA8ogMCW6Az6KnO0kQhztM8SKLAksclm4LULLGaYsVLEfZTh2DsUorjinbyEIy9j+vo+jYhoQdgloXJtmZA0bUcrhvLgIVVdxVXiaCVLEr6X8ymQKWYzm6WFa4vfmVyrj42Uql2rYg6MqJH715+TWm3IyMvaG4I4iah+Hm884u7bWPGAFIuYauKEBdBa2fLNZCmhXVQDKzvSUyWjoU0P3kvn0To5VRIZMslVH6T4RrSgVqxCdTp2UUSBb9irR4E/uZeiwL+4B/4stbBxCUYww/DYBm6Y8Jvzw4fZemSf
*/