//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_10_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_10_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const std::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const std::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x) / ((b[4] * x2 + b[2]) * x2 + b[0] + (b[3] * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((a[0] * z2 + a[2]) * z2 + a[4] + (a[1] * z2 + a[3]) * z) / ((b[0] * z2 + b[2]) * z2 + b[4] + (b[1] * z2 + b[3]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]) / (((b[5] * x2 + b[3]) * x2 + b[1]) * x + (b[4] * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z + (a[1] * z2 + a[3]) * z2 + a[5]) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z + (b[1] * z2 + b[3]) * z2 + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x) / (((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((b[5] * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6] + ((a[1] * z2 + a[3]) * z2 + a[5]) * z) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6] + ((b[1] * z2 + b[3]) * z2 + b[5]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z + ((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z + ((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / ((((b[8] * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + (((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8] + (((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8] + (((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / (((((b[9] * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + (((b[8] * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z + (((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) / (((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z + (((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_10.hpp
l6Jbwc8ud5kCIMQfd4iD4FCWg1Pryb9B7v23TuybF5IC2py/bIny2H0fwKP0gRZQwecXdvA0TuEURobrCgNJDCzIgvvQIqa2kgAg36D2SwvH0H7k+f52K+0h3PvCKvaXrHzwVcUruUVDzkfwyJasXQhH48w4Bw6/612TcyCF5aoKAk5uJlj0ZNqdNzX2cz26nK/GKtGebByLyAK60ogs/BacLRQYEzKkxetwXnaHiJc0UnjDp4i8KnM2C+fvlhGFLmHwd11pElzcQFge4RmFvfcl1jlaxrkHYPN2c6mkB0BMh8uharZfvOOzP/JU5c9qCRonpcL2YQeAceD4faQ/PWtu9Au9E+QGYEh6ltqQW7TV/z9g5g4H7z0VtPdWIwbyIwv5aM7txNnVhgqdCXYHOyP1WaVW0bRn5ZJs/piDxmMX3d/fq6xDzfoXe1KHbIPw1gxE1FiK7CSGI4Kh2RzGlNCMkzJxCbHnjQc5ZPw5A3TUxgAJLPbTwIfchdj45N7PoPTNpeAa/AaHzhCekOFy42E9HkHhF96pr2kzFlKRTjWRu3vZfsHiBsfco4ovu0Pz0MvEmaXvxUWVxBh5CpVhs2CJJYSiQ/brsPdudPCHVet8KCWf2Ppn3KRTzAgWfOWV4hYCJtnBeS11fvoczomRlSEjrrBD++mpQsG4gAKEzRIyJ9/RyudqmVg+Bot8WokAqa91BFYBmTtYA4txD+511A4yp8RZIBE1Ib6EeCifakrFoDFukuL4Qmz5JV1LWP2QeiS2xs80oddVcgVaZCVLdvUP1tkF3wf4vnRftKvk4imaoYE4Pu/2UdJWPHqU/j+eOkY4CICXPpTg/YxXPuVp7gTFLr5LX86gepS7+kTir2WH8Bz4pm1+delGLVJ1EJNfDXiYvJbdkNPLSnKqlgp6dAuz0GR7g/VStuM1Pdn3rI6YuTjXgFARa6L5w63XpLq82EhFstMe2YBx1VzLGw7zU+ymeJspUcwYXWdMMd39hDlor/7OlKMup5PSq3UcET4qH0FfqzAnxudUtu3e/HoRzfDMc6rkZtCMPfwxkT5QqSJfKINzplM+LM14mzrY4GKnOPfSajcy869dyyqt0wrvn3pG0UwyFD1wbpi7dKbu70T5BcdTikh4T/bO0OjpJzRFLHzqq6p+OEW4/JndlMaQoCQ4klLnxiR8fF5twDH8xLq2HfC8n6QUQ7xku4C82hRvBxiOiHaoMF+FTzOS4L1l27z37Y2d0t7T8YKBZfmJmyin9kV4QlpwDNIyzy4CAgXNWWVMvrnpwcVWJIPJZTSaJjr+lM8gM2BYfAEvtQmK0h8w9DQPUMaRXqZ+PUtLfh18lbthx87fObD4h5pl6M/v8QcF//2FTOpzo+iY90SE2fsogx5DsOqkCGpAiTlrB0vkVH6/XP7FvR+qD/tJbEA8O+Ecqm4y1VkgvJGAZtYVPtENll91Rzkk8ncVgcI6AcnyHfxw7ESnBQqD2fUNAbqAuifo3IB0fx6DfBG/h+yD3T7x+67AoDk3tjJyd5CJ4YGcg/+Q7/dzj36nSQQNs7V27FvepsVjEmExlukXPGI141AJNlIEXShWgw12e6nUtsnUyhEGbcCKg9ZO6ENn0tv2oxwkoGOLK5Ib7S6pLW5ZjmR2hnHaN2cvWlqpNUdWYTpwgetnLYXzu02AHrMQL5hbQdlmN807ruz5mvU59ONPT7RHLToDepUa/YRgdriCumQy35Q1VuEruXlMSnegv9xs/ib+zn3WQu6pHXiDDMrq841kWo18ERGckzDIpTBbtFKlRD3C5Q/LmxhQL59P2ATOMpPb6Z7qZ5La9KhQIJnC+LL7T1CiRTG5cyKetF1AiyHxQ5lpUxjSSbhq7H74jXf4sXc8ZsN0KH0uiamMVNQ/6VToETnHAAf2tWYq6Xrq3KfudAAWjkS2LG5QkKOio+yg3R+PSZVgJ0CKCUMaLPTa7H0FjIbRXudlzM4h0kQnZp+Z4gMdwu0CDxv5OVL/S32hPuS4/xP3GqX+mp8EXnVbyCMb2vMaOuu2ALwrRYUDnPRjcmhUJXhQEfM7XTz341L3XSGmGjfI0eWgnxYHe1ZGu29IvaEapdTzSr2sRgK5U94vHUATzer1lVPu912udeWYETepZpmGCKtjRgKSJYVhdm/h5zeG0MWGEpHRUOK/MGaUEBulfc2sglrQbkiq7dDhuLT536MyXHrRrR2+s3HTLbZSv8BHhDJR1uMpLKvNGFlIXU7EYGE+vWM71ft3YZHDBu/ZumibO2xWe6DeG+Wr5advKNsP30GCF50DfcYHZkBrLJ1H4NCDPxLe4ty2Wqquff94CjsZSLkHBeT0Gy09bLW+73kPSW8Pi0+xCivxOSaSeTC1+5F6kwfhykGcIWfQfs3w/8sJlGvqabmkgN3sVpTyCKqL5mSIE58eCwfxC2MafZJjRjvAIHKcrBVgP9kLQ6IPaYjKwUHoPdnSNX2DUlYlUdndQQ1/10Cu5v4gVQIDCwuJC4ZdfF2TKB4IIvuLorsNMmTRtnmxXyShMrNHTPAH/GAdKr8VcauM6Iu5zCC52C1Rs6dWQZAhJNabixKgbTcMf5GHB4m/wJOQ5v5+H9B0TjzWyhVnPonFgs+02pl/A1gDomXwAkFBu/4AVFXB72Dk/e0oVIGw67mbnwmZD+1Hp/F9PX/+QO9vGNFLDvkMxYPDMGisvczIf1VKDXNriCC4BJMsoNyPMBk6D5JQtEZ/Zm40qVO8voyhmoil2IGGh2SoVXh+QLcRYQ58dO2PXF1J0QUJxh93mOYaVwbPcP7Mv/E/MOV0fXlxDlpNyCgOMCqURDZzrp/rzDaz1oHWoEJ74Z6YKF0yCpYcMvTazUAxyco50TlP/6fZaP1E7Nc0zDMOLXLYhRZRaX0EkgucN1TohiDWuyQ+8h86iSE0NS7TX0qvnltzXsnPqiusKjoLtEl95TMUb570OBax3AUPjtu9yz7m1IzlB4Qn2OuEjHdvVLdn3cSDCejIRcnFx8Tv3zHK8rzRhi9jDD42d11qdskOI/UtjfW5kWXwUdJ2uxD0112J52N4sRNX1w1b0I+9aU1JcvOHWGfwLYV7WskS6+ODUjzouiDc93BlQUm4/O8SfeGbNV52ZyMKNVL4BpsR4rdTWm3evVFVXF6mDaEKTvwwDOi8FV0/c37zM652I1471TRYHFWSI/gUTdaW827dMwZMD+Z5gZxd06PCxHpcuZgqtCqkaBl6bSUINUYjaw77snJzPt71cWGVj8oVTsMmALdxrtYxmdILTnNEkKMzK5bCbntIPiJOwR2iZxvfIjTerINE2iyXZn5Pekull2Ze7Yde/lt6oLo+M8VJEll8PuCfpLadDo+X7F73wsdjHlOCS0Ts4wWm5Nc11NvlokRDPAl5oONjH++nf/pAThMO+FxBt+vybu7apnD01HZUJ3Jv4FUUtoMkAO9rZGlBYE4hZz5evYJgQM5gb58KMsSBPpTOaeRHgGga8mTHE46kks54TyYFJZfhBe0AEMx+zXtGZml6tCoCuilGVgQ65OZcsBTEZ6c4yLQiShP/KLSjX0XpQ55vZOLywNTOxS6GBDfg0Dfmql2QDVudfyAhWziQVREZiRLl93rK6zEWUX1IaOx9bmXCFxgT1FqgAwEsJ/KiDH0apbg68d6GcyGK1znH9cMDtdgne0+JN9gSB8I593+cns9J2PAfiQBIkJceWIjpXR7v5djB8l5Ve/riFrwtk79gAJXv8/GB/hGFbzCxGJAcumrouwrwS+pqqjR/6F1fVicL7zroqr/W6+iHSQfySGjnLhITKJD1oznNwZNTx7Xv9qOJdp2+yzoKOY5v+6p51jVEybJWHPVGNNl+7eE0jo6HkTIwKoXcj8OQAbqcBhsN2blPszHDWkhPRygt5Ynxn3Tx8azZaIBbOzcmfZNfYYfH77C/RaNdLZ5bN0PDzPbVb9ToBL2bUq8oKv06sH9R3l4f/f8M/0EcGFyJkJnwamBETaM0HVEo0pQxL/euMpACXTvdh2dKc0CpXBuxocq1odv5Z6/GLhXPddm6uXzBjV30GRJGFQwkwU3YATzyhMMetH3YGtZijX/U9YF1ZIg7U/RgnHYeHY6Mrq0cJvqhMk8t6yGiDWK6Qy2gGxZfWTYmYo976LUYbEhy1UEg9tMGMgRbp36w7Hcr9q8C2XjF/xmj5ncR9V00nYjBsZScSO/l9238acBmxQoNE9S6lkVvzWNbvPKAbueliadyweVW6EKgnBgnLNR3lfP96S3YPHpz0+k5HWof8R4LmKSeQVP23Sx2xp9oiHoEy8BUOjiYi26F37zN5a4cFRx71jo7IOzBCoxkWooPJNR7IMHGAeEnHpXCu/vRboCO2vgxE8bL2E3fPAjvTezCLEFfHMOMitM3Du6OvDzsNJjJ14DXwakp19905wdMUv0sSTJJwiG3548GaAxaPX/5hCmHqESPrzrhUjMh0rkwJrX24qBUqqOn5BE69QTdaVnI9RUPnE4MeFDshYQkuIgsvLz1TQPWWX2+HsVdAndtZVZ+FmIYEseUBUXUxexcaaw83WcegyllUaiR1RHX7mNehSOBzdIgoRfr1wqPTofGkpE2B8CUafOiOaRWQeEVfvbdI+jOfi+DUZNID0thoad265nrwYT1R1dH6cVS7gmgRTVT2XqfG+ZA7/uoUYu8mEY+s4DvI/43DbDj2cgSwuEE0cLiTC22o+4SB3sa90qEn5WYxD4XREv5kA5oem3S7qxeFi8WjCWVCQiOdrBFbwGuDwHtJpM0XJWmLYqHm+KLarrMadI0yWEnZYhfL9Kpt3KOZcYOflWWQdg4ykbUgnLll80MhyQPKYWi8GXPrPYpJ+CT1H+9hxVwB5vFG5sJYH+C5HiVptJVn3R60FLJyFfRTzJOUWgcKSo3uPUW9svPtpdtbjZ+JBqTCb8uNfTspVzZnwbzfbWH6omuM9TOVl3Ud4T0UEo95tEMMOKhFLYKj/VnM/0+ZSIOVpPmwpwDA0aAywptJE1+K3DW2oq4anAVNxbFXKNvGsPZe/FwkFSTiubr8zoaDHcx+6aI67mpn0yptR4aisotBDHoEo4AeTel9FoPDrO9UZo+KQPtdVUamWtxjVl7N0qy4DIV0daAND6kQPXONUNske3XvuXy9O1uEsh1K4VWgwKndbXrYp/MxqC0DNY29mIH/AdR/d+eC8H3dZnsfq/i2/37mmg32XR+/eUok6SEEz0OQaiKX5uGrOg6i2V9lGSiwG8qI0puvepA467ENoa18Q+fLS0U+J1z+YsPzSabLjz7jaOHQPzftT7579scPYslGPE4wD4wkwV70TFe/o/uEbICkRQr+jvwgebA4jC1X2Cn8SUlRKT88LMf7T+arm5myQKokA7nfWVI6XDuWJ+Tg4P5bYEagG8meEock2E33be7tmVYYEWOmvrCfLodo7HqxmcXm95f7+KIjiDPmCYR2bAtsqaf+g4IvSTx6evo3GC4ukRcpjv2E4kbzHX1HSg4uMfC1vT2A2TkqSB1ZaoJqbSzfOqzjRZyeUhpiCe9q1EL07EjgnGyPVO6B5kW3f/i9y7Bm+KASfErEM2ZmNtGhOqZeEXn9v2IXe5ZcZJQ30ob+qvU/CQe1DxYKmplDxi6n4xEUSsA1yaXdzPRjbndRTSAYRArtjey4A5yGtLpLWrSzGbvKta+TXHSqt0rTKt3WixEfRcbdqwx5llZdFSOTxTYmrrNBWOJuW6+2Q7hADiezZfT6WRO9wk0kIdcDCr3qG8Rr/CainWjxkvuDdGkgwc8SACydpStVgODUUbjDyYIohT2BQXgGQzlmxJ0Ay75zUnbanc/lV1YromNRTz4rseBLzZ/0/VER5FJmaFChAUU1N7YDOPQQuV8PIAMSW5t4pLKG3X3Ku+bnHZFjzEcZoH8X/ND035bVGcfH7EXfODvDkSK0lfeclMHqrkuduDrXoc5FqmCC94KZ3BwmS+7eZy8L46c3frDEDzbvcaXHiUItqLXpxDfF9CJZCKUAah/0j8OF1QUmalUKWUKmOsigY5EFTYcil4W36z3revK3NSBJutCulZIiA9nCVmNqMLJMt5pSqWuZlDPAKqp5kFB5lWuUR37+1nUUmU+z9/EQKd5iUQy1uySbIR6QV0IMctJZtrFZ9MCy7GKi+td2fh1pUBrHOXF07lsmeG6PnEmQC+lrJZsaW3OR85o+DTb6xqIWi4h1venh+lysM1HTOGhSZCFx2TzKjPfLxbP0cFOjnfUA9VdyWShR+aOoeso4467zqsGAUs2G1+93J1u6zwgMkLhnz60YYOD77Flmqstdy+JMbUbCuyjNbgGfbnjoTgD+ign7f5A3Nf4wQ7fyK12UKji4+xYUcFCBRmJB3ezfLU0O/vJuk/KnCmRxpVZzd82IV3vMNJDSc4pWkuznRQC8TwULgipW6bU3Vd6OUzj57YjBzfCYjyWCSm6LX/xyCxlwlEtZvPc19qXQR7vUY9ChEfsY3FgReyv0f+z7h4xh7Amo1C2IEM5IdNHjPK59ftXXOgRiOzfgucOFXwm0J8nN9SjuxKRKewCC+2Nlg3tyUsb2V4U/Hx93wesB20HQt29k+FjEh0fGFbdHULUyhVkXDao2slvDHusy9N0ffKRwz3VDvmK+cCHrdvDnf9VSoCVWulY48TWPw/R0H/Hg+VzuqzoOPLdfp9/719V2e+IcSHXruLPXTeaoLQ32OSly3HrkhOtu60twBWncyCJpd/0PNk6cdxhBaMTl/A5r/BkGs5jOtBn9nyzR4ixEWxH5ftQLwKvJtnNQz9nUaGq/T5XQBORn4oz3x6cKi5vUJxp144Ak6TcQr1z4EfuK9o6gctlJ702iJp0doBvk2zwmvaRdWt9JqfSsPtEhg8GwwLnPnBuo7VbtUA6ns/M/BvkJnVB1dhHP06HybW3M34N6WFSXhq90yxy8ojLVGoyn4jMdpdd8yKvdjekRisedPveGJv1GOoo4x+pjjGpYv08SahiJHy8KjYzCCChtaaEQrWa+cQXwEmprCPAvUyS2ZFQ2axSXHtZqkVqx6uyAHJAZMsU/nq19aesT/7hLxH1f8yLmrEo0XB7/fm/tYNwZaLM4JcRgoFnF1srMK9DYMBFBYVKtnIJoIbbDmwgwBmsNclKXSJagQMtzHj/qZEdWx1FK4mdKsHOfVVfnioTIpEBbed5/+FkDW75vIaeS/83Izg1qwC5Va2JuCZJxGVG5+o2So22DcX74TZ37KvgvrtMyul2H0KN4UjqTQXouv0BjPzdqC19hW5DK5BXWr8t5q7lFFODGgbxD9PtClN/SwKVZbTRiZF8NHYjeaHogwTofLuYTWKeLtYSGtuTRzdofS+8eaonW15uY/vzrTMRtIzZd7MjhoqJsQvjU20ldouG1VVbsagTjnNLxWKKD5xrr32Gy70pJ4Q81+5FsEPAd9m3/ukI2oX6jwnVvgrl4Zq+qmYwcBkKMb59m0fsR8WmmoIiyShPSNVnMi686226rqdC0xa+mz6bkMhA2+3tC27hcL7UqLToUnYrXDiwo1t07TgUqOgTvejYajFS5Ylu/piP6Hnhq9koKg1kvxhFMdfNScNO2UvfqM3syb3w4uKxXidvl2p2
*/