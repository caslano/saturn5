//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_12_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_12_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((a[10] * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((a[11] * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_12.hpp
GLEqbbp+tLzqUDQ6PYtQncQZlfdOad0FOXTaZEa0EzS5Uay29EM9XdZQJzecMahxDE76X//Rwu0LrmEZyYEM4xxhrzyIK/JVCzevZYurwFpndT+dqz/AfFcyNRQCGTxtPVmTY0M+1DxCjE5FiQ/VeH2+/oTA1YUysV5EzCD7c0fqPoY6QCFMlvPseDYx2rVqfx2llaXdptGlNPZowrY+M0ZlQ29KsdfJhXSen46Zmatb2Cg510sgjKKW4yHRIvS/a/boUHrMZ44LU7Cizhv/N2AfwFES1lC5RwDmV8slSfFEoRKdpjyaUZdQmoc4TMSzlmaC2HXYDRQqDcZbOFdh6TDgcxSgpUVOlQI0yFPnySIIYrl/Ry5iQhVTwrBTgIgj8tXP2Eflk+7vfsjuMcNJ+ODbldBWu9OanY1XbOGLwjosVoXCyN1rrC2zRRHRvL217maWw+M4sidBMrg3SIAXAbjB2PDm4tPmrrpBEREICZHLw1spe1hF0Z9xhlavay661Rve6rt2LPFbBh7WcngG6d06/B+akoDEScQiwKQWmDfBBJPY1KXTFuLmSQV2+8o2Hu2i6NnfA36/5iBsu/a6PFqxb68+vFtrANz4fAjlXosfddiaPou9V+hVPbpxSgoGAPv33Q0dkKxUNAyb8Mpw0XylQd5yMfh176cxHnM4fVtKSIEC26qNGdibv4fmpeEXsP9cp9Qb0NCmYI2BQSJqiF/Uud5zqTNPaI98yGrOMsTpyWYSyrPVquQkYoWEqFGvxBtfM/1jRRY+UNAzyMpUIjkJ+j+eARI4FFKII8y/432M0bBy1YMKHWkDmTd/VwzzLKXiRbKxnc7qOUNR81xhO7Fym8Bx0MqS22YNLPN1Q8+WrrQ8wwmnTJ/RhlPjvxdTqeRvzW1Giu0c7JR7I2/T9WHCNAVoMg1HxzkXn5IcpSWLfeOUNpC/2SC38dTTJSttZnAI255ZqiPK8qzIMwMLFNqRjcPZs/lBLCkkJJBFy0mHy32flKisu0kHCus/KKtonqKXyaG4aS6mclcmClzPw1oAxE0veqoIJUNbIWfJy68vICT5rKy7YDcXo8SWEgjmpdXWmEpRQKV93hqHX/BMckLSjcpHyrbPdhyyJ/+B3hevOB3VOM//l2GS0pT4Vfxj+JjA0qphUfkRoTnCEC8t0NoETTGB0k1iVS4AaMZphpwT1/2+3eapr0604Z6p58D9vEhbDBhOjWSMLra8eBbYQtxli4kPYrpFk+FUbb1y4hCZijD37UKlc7XJZ9JpGuz+Wx2KQaikhre1eejv1kTP1eNHZzca6bP0BlLsGUIl1Cc3OIdXEpM9a4F0xiNlPXONP5j0fbSWofcfXM3wvcbZScyr17r/S75qkbivTGXrOffaRIj3YH5Q66uIzPOQ18vbhPPY89PbK9bE4ZDXw/a4INx7Y2ydH2ESx+rGwDl09MYlBfJ/nBwvvUiRDxqFHyForm+uel/6o1Wq3MdViLXpVsFzchD9XaPMMwZ8yP8xhSysHGGpbFGJouQaVWeXjqz8o08JQf2+XRCJf4tvx2fBEOLNjGi6XidwzttasEnm50Hxjhx0nPX+bFlCvXrV7GgY5kOKJXfY1axB3v6aJgQ+xZBzjthj9x4kkK9ONIj01D4gXl/oZvWz0pGzIMo9+x7lnly+irSfL9ReDLvjM+iMeZTogRtu6ml54lBv5eiWXe8uZh8CfFqsGgonaHfVS5AFoe2z4TMM83halCQbUcqGxGstVxENovNQsLAGGElr+XXsw0SzoA2xCH3yDzyv32Ue0TaSTQmrf2JgBtP1AHBQbg0QRELhG0xWurSTEv4U4ipgzAmx2XcFM23F1RbzpRZFJflvvVNJBc7S3Wg2xQEFjW+Mhgm5mAju4eAYk56E9IZT5B7xlM+dky9y0wS88l0oqFwsTXdNaQIYsaEFdW7kwzL2FiIqYmOE/R00y0xrHEtOutZCTNSKox1EqE7Hgw1kbwPGH8t4DY31v/8M5re5wCCPdMxgiA9/eLQnxB/Mz3ED1d/J+eYWW/pyzkSVau9nh8bgTgdbhwPhrQ5DylJ2RtdK2Kgw1Tzl6qIcdmjNbwAOfkn3enT1wNgsJRamq23vxzUX8nYYwepO5WqvUyba/vUaqXVofDxGHLqMQAqO3WWmtE0N9uwF7i19snV7sK6g5VmDslmgBvTcOkUxb7kHs7ok6Vt4+Xbx4VAMvGiwk8IyNun3kSJkReYY937lomlgc4gi3JJ9GkXHNpTKVjJkEOIheoWlbKs3eHzht5wMP002MBlOQqdb/ZYEwEpd0xIpGHQpDR6FV1fFQImB0950W/TUOSqDb5htC8JKIAr4jAFnaFuHaFtx8tIhci7IxnG+8QF/GNUOnGCPNhpNApZN10l4zNkFg5IzY8q3gBTU1MkchgpjkTHu3383h6bsuQW2kvY/HP+gfqXQBiy7t1/jwLKW9yH3aV6KtWrzY37xrZvnRSYxj+mrgqpj6nNcUW5cbNZZpANuU+wF2fWhcKKmymG83kBHPYNmne8X6Yf3ckKezrjn0a02msPaZKKzj6AWnu4bjzU+AYrHdo7ng9K/P8ma2OeejUf4CRGz8Vk+iXEKeVcYDyq2bY3XASG8X52bngzGfIMXNbbckcImCcf3D/XDdYgmfmZMeEmb7zGN0PgoSEfCripm12z57A5WmQgN7eFfYZiysEgFl6nWfeWSeZTX9f5uQ/TuPtbdrsb1ZsxjCk16oYvd+k/oP1wfYSG6T8+Ttet3vxCykZFJP6TsVxZJe22iXd0kMVAqO6xS4R/v06nBnQn0VhoKzrzZ1KfUKT6KuCJptS/fv3jfW7OsXmnvbr8F0GyFvrUOdLhrNF8N4fU+dDQEeli9PneAv7nt++LJmEhRqEBK8HA2vZ3ShOjWT7XbXnHvXg/S1BIotmvka6vSkHvxMO7lG3spJd1IepOIb30iqzhrC6dARuECRghcHd2w4MRtYfNPMhWwHx545xXZffx1hxvh7xpxeeKOR+lC0YzRPa25Ha/zxY32guHLGAyH4dl+UxKT0zPCZWlpQhiL3hVrL8EmEWGQPKxV0GeupjRdx82GJkOXi3TNVEjyUvTpdE5DIyp90ZRCWpIkaSGuq+ubgUpeW1/9icaXOk1iLwjCGUJ6KlrqWRilotFEL+7MSyVnGPMkM5Gm51nRKp9lMQ0osnxL1fvVajfQlOJyWqFhu1B8RSv1wSGn5OK/Rq0DBIJokEw5ghtz1NB0j8qR65b5x7yUILnp5EtijD7o0ak+1o06TejzLi5qhAsn8HgCK9ZM/WpKSacyF/wp7ISlxAHD0Hfg2qElypA+1S5s16Nu5kPq7Yf6DGrHebPION1Hci59gb1Bbn7se3fRuYw8s8wwGJ0i6LoiNuHSvh8PjzkV2vEW8ocqTjTQwAmAjvvba/a4H3FjSQ1uOl3ifVNMfRdrd6sP49zdkY9fU73hKy8P+L4Lz3fjZ7CvMQjLpOncQRAcjja1O99uTpkvT09DbrOFn/FxdYz909/7VYucUMVN/IsscFCpMrgA1+nt1jQ4f902sxveghrs8Vb30uHs0BZXjhQ+mmpclsMyvtXWrC0FHRHh17VN35r57pab8m/sZ/lUZXncYz9UfffdgL304u+ouwXIcpvlsVY5jG+8VlM3Hk94D2+5Q0of2N6N34lFN5ctt4Ftj6jNh07JLWaP/JeXe7yT6wYS6U/XPC5pZRqdKOj12nFLOg4/8Yepy6sSFWS5Jp/UZmIdYpRYR+sdnNUo0xRbXGE0Jpp5siLoqvJetGe9/Dp/lsHh9Ngqze5BSGOPTte+hZenD7/LX5sQP7de70ZeMSlvlyvPr7jbQt6Tz68R0D53u+y7wFeGHTWjeHjZd9fwTmYeM8BykiTBtkdNRj8SYIieIRzoGCPgB5Es3XCIlIQIVaTPuJzEWMBe3L6sq+OMvaHC076N//B8d/xmIeUXI7Z3RJhHQK9C1CZGk6zPf3ONZyewRxUPKKMSRFw72VAHNfC1QBHJwY0EIY+9qXUKlmyqV/J+iSA3jgxxZD+2s+TCdy9k6K24RcQBPYUmFWpi0Xt2sSs2rm8YkfVrt3ZsgwiqKAMIKQQyqVcjRq80XUUFWkLgTEzFPepTx9N0S827h3dT5qPrun98WEBav1By4df6L7x7Gnvzzu/JAxACmfr2NzsNuDopGiiJjPLp0WirmAPg7X9NR96nDHJOyPgiPZnkHBeo+zqYL28fvQHuIEhwU5VSNuX+rVrWMXHwZD9L/DKM/g7xhvnJSUr1Op22GN3mPYc50Rl0BO8rPhdNFhTeFbJE9uLWQdth1EFrMLAvhZl4yfiXfRHz/8D0nGny+1ZQdtDvNTY0ScmKkQ4CH2/6K5uohRTJjezVnk1S++ClMuVNTY3/fMn5gW1Zd74Ed+pbyOrA0ZlGX/lx0aqVcs/ev0n3I/hbua6IPHoyfkzTXSBbEWcrQ1QqEPym1NpQyaTgcm/bcXrW8r7eGOLYIhfLjz8+acOPz9sdzbLl30uCpo5oxgn5zQwQzvBk7XlrtgT/PnOo+e0Z/zSxdUMZdRbva+KqZNY3sW//lo33oB5EjFwIw78XHTW5v4OHEq6Uj6BS/tc5FrDZxYnIPChw72jvCBBoRDoZYeISYHPf4uL8MpOSgl2TB/v97WEqNFP0UgmFnlySNqXvJIbLGL6FmOvR/0g2SBTTbHOv1XlC8iRZoxwvRIB36oLHoilojZ+s55xpyG+sAVEfJpGXDptSuM55fuV7+pt+0zbEJ0d5zZxo9+wMb2o3klDwcMRubtxh/QEbfulAeag041npNCR9uFC417xocX2jbMgYOkfSaOqtRU4Hk/kG7NvwS7qPqKZiwr3Zu3RyFWppKFgQKBNAiEsggb1D1YtcmqTDjFt6/ihsA4M+d3HoYQ05SNJHLd40wZbk/lVGKICoNq9Yc6yst+2tbYhpdQ5HsXV1TCTKZ4asXF9EnIJpusMEcLkynrJz4GSSPQAXnbBAQb4af4TIQciGqy6zgKefLIrpl6gRGJ3hnXNCXWtkfCKDkNu6QI5kjdX1Wa4rNbi126lYjRESwtSQs+6ZqUGqKHw/lrifr97TIiXnZ0VFkQ0n5La9B1aLM9d3jh3Ekaf3wPayFHBA/mRMihlWGuGQTWZdzcNV5A31nCIvNdLA88H5tIF+NOrd29b5TEHR3jG7tYqdNmMpnTqpRbOSs1UyNU6jOC0L7fbAZ2Ouu5urrlu5Z+3Dqtv0humX+0+5yu3Ys4r2cXE8rOllTijV8RZ8b5iT9z+en2IcWaQoVnkaVGwa2lnV5M95Ib6Avd7wtYA8MzoQ5NG23L64mYQuT7SyrkcSp60eXQ/Pt9KFoR66wTe2lpYsc+akYniFlXy7i08YD4NNVOocDUqQoQ6skmO6cp9LBpzEWzdT0ghGkh5w32Z0aUKvNxKYB//gEj92YLpt6ucALVAMzAHe3OFb49OsMDOb4b61VZK8X3x1vLHKseOBySksAqJZLTB+yUwPYqs6atYbB0Z8refzbYGPoWBXGPa0+NsYDYKaXQ0HJsk8sjQlIvKM7Xhx70Qp8XLpYrLF4j3r24X8/6AcFIP/WRkMngy58DNWFcixAn2Ax2FelfPoHvHHqxnhpcgQHoOEvnk2Pd4nFXRJvW2aGo56UKy+4AZQVgyPEGOf4tJtvCrhfWK+n4T5DpwAHWHIVS/9fMKJmzp1Yr8Id35lRIQrsyx/1HutiH8oFk5IeAToNWunAxFu0sdx2CzLgJR24gsjc6MlQuL2H4I2T+NSBmfPRAFNo0p1V48XOWxSGeR+epIJgoF8DniMq7nIpQsusQClUOR7eLrOqvIAyJCyU7CIFmYLfvbVT2ZyQCDqQL2WVS7nsxYs4DG8xMmfacJFdRmT/2b6lrKtjvqLHPZ70pWDvRiqJukbU7dIKnxqWSHnSGEcuhmNnR3OYeHvnVZYRhS3DVaYMn2qoN5QCswkxsk56RfEipgcMQUdaqEBJFa70Hk6uzLWTE95rtLlHcxmwL3gp2UzOp4BUEobKX8qDWDfxLycyDDOyDQdXNv52RiMUrm5tw2+eTw0viM6rlAfgdbOZAk+PgFf8ubecrVOxWu7CNE+iHkvKNQn3vN+3xo8cuu9nH1z4rNi0R4RY9Bz1np537vsMHaD33vKSLU8c3ZdfpgqXVVFWSquT0oVHKmSpqzn5pTnplvA5lJuEDtneY3P+3UwC/Y4IO0pnKwf5qiUHrlMA2qnjRHen1MsVvgVA6FKzkzAQwq0S4FD6NNB0vnLASCiVhVkzV+OSIFppyMD5CsDfeBz9l8yYWtYUPNjHBc6PmHACiQIGty7TNgwcNmHKaxqtAobuAly3We8ep7trz+dUHfIPxS+A/aW8YTd/+fDmzvbzsXUK9H0ieHJboDsLeV2c3zD2r+7b/rQ3HlVbmQNBQXuzPihQWwZbHNySyLsxltKpvwW4VizOvewTG4NLGorDURuYS76jh3bpkKG9DKFiguem0Udtsxqs4RcARsoxVqGJ6s754t0YnlAxoJbJV57XgQHYnDHbSgJGn7xECHW0p9++T15Ux2mLGcZEBdlnoSACUVw8/bfChg1jjZPaMrPYLx9BOkxviH57jGy+bAYGe+Ql1bYdKhUj64XK07glJUQc242/L23JTCH3m4F5VTlZR7ZgypKRMce4zAdGVJ4WB0oEXpFgOmAtIdUCz3KQ/YLG7uBhxhMAVZHiR3FVhk8Wqt+w2Uc4WPRRmi1IQYkHH38qJO/hNlR5d7VL/dCtNO6/GYgTf2rQx+kEqPAMgI55d66FqsTnXlJu3vlTfin1Cd7Eg712uCy8dHMZQQ2QjRb+ROXlznOSQcAxFpDlkCyT87lvyhhxa6NZVLMrIe2yps0DZrXZRrIeLu8BoBSxIL3MmZw7g9IYo5p0gTEep1MlmV1GI2MJZz22kTHst9K2PwX7wY9gVz7IrfXEuAsD4nf2k8xLVflYW9IEd1NjXkOF38ViJnTW0cPs1lkcMRq4EPE468FigZB/nWe54Y84leg0p+TQSaPsdiruz5Yyl6tp0xaPMZlKnXJtkY3gpqfMddObq+KtwiQ96sZpOcn1tt8iu4zmTimhU+4Hlx0y44SbjpuIG6zv72wj2D7HPCRYeg40GlmmIfMLK+h0VBKNulyu8kNrESeNZsADhHp1t6QVBQIvqOy58y85EE9rdXUlrX+1O1u+qIR8ADIdJ1foTS/oibmuUkgRYP63k3oT1tTT19ObLBJTefgDXHRbgp1CijXsSiV96nfh91+xAzjnSOsBlrkw+nlR9KNNk7ppBbrl8w/cZbx0XqRnjDmhe8KhltWWcXEdBYkZamE6d3rSZGU9BDMf9ywWpne2CQAgkRhTw75b3V3cbm8gLGEsguwO6Gocfg3UPaVEliKuwladRklGANH1cMlnRA+ItRyUs39CMBHG+fKkaJCb9fJAGq8ftDHuJZ7vWu0wjzZLpeGcEnRZquCUuhLI05e9cpggJ3J/5fKBv95mL5Fp+TxNoFWT9ZMwhbtkv9K/7HWV6wvEYneNne4fbr7Bc6olcYWwoAAsA2KUxoeo1aUN18QusepCsJRbVxkbK2F5xbSW2nNc2gIryECbALZFKrPoGFheOq8jfBXzGq3xMcZ7KtNOr3Lb0xAxHhsTc4D/uLXa/2inZJ95cI3qtZLHVy2aLn5PTlPYMLuX21duwavjZep8idLAjdmNn+4D3mCuMZ7Yt3ubBc/UbUE7Wu+6eOHswWRiLBnj/+snx25+okuzQFHTI4raYZsiTdvGkXtFs5gsOAMsXfpZd/VUGpXKogVRT7tQYykFaVas8SjEuZ89xE4AcRytepJEmXilXQnGALnnr/4tcUZWd2MruOnRjJhJspopLDaCaXEAYW+NgjEW1bU4hlULht5T4/VLq5VYtqyFr3tjykXVTUmbvoMJVhGH0G5YsLz4vKDBNTXxs/EfG8Z/gLsRMiI5gg2omz6uOs5uy8WXC5jtnUbdova+pH5/nFxRSsfrHYXXlCFT4EbwHSFqW6RBPM674XuHgVIWOh/uNgf0dJ3UMHbGS0DJdjPCNHSbqvZqt1oP65B/zCPmSkSMx8S3oTuNN+sJgIfaD9Z270EpwVsnhZTiloG9QiFDEByibRhYZ3i6Ip87Q33khJD0v8bF2RUMPR2JZFIwmP0VhPm4Hbn0sZPWYEuBFgcQkFJcDeMV5Am0skTWLXSbLBTpV2GsTh5vt37VwzdvMWMh2sAbd9wnLsEU2xznmy8qCGdkPBunlGWoEI9dLM24SoH84g5kPY4kCFrpiPpt/wxGkutfRK/grtGs/bxibcTjOH54mLOCKJokf+6iii1i3D6TYgU+bCnuk5ZrxP6btIweCYvS3HXrsapBq7TGXjDstV2WVyFSqOHrR73H3FEJ73rM7/vlO/GLZRNY/qMTvclJZmgvPHB7hnoD1Kf73wK7JlFHcIiz83BPv1NZZVkNYw3F78O3mnjQLZ1HCCpBtfa6nbdXsy4zO3TGo3HTmgtgU5ar6Ri/PlDcj1tjy+LKsHlcHkXvILVInkcUHRLntGVh+nPBbXbUyzmzrNn+EF2CphHyGVV9Mnh/TxjKR7xg0NJhne3/Q3hYrPRoySzCwC59WNwvtIm+KrFwLz5UAWdQ/qOdJOFhr1gQdQVCRnix52ZxjIltZbULARc1f7iwRhrDifoNHYierf5tSgK7ec70YklEe1MTWhBJiTtScpe4RZQYjDRJm5vRVTVyCU3YPKeCc1P1kb8s7d+bHSS8OjbTYt8AtVosPgeThrRUs+T7+Tur9wH63DfI9kXXlha7ZuI9XZss3ypG54/6xTk7JcGleNZSsUkyzWEM/sDechn5y/T+CxXw8LoruPBBKkEJPjmY9HmNL2BfXfHY7ESm9J/5zVqzmgIWFotjToyv7CfO+NK6XZc37axPZBTePB12KJqyqKjd4/jl+PLQKrG4gTAiPLXyQzF9lLU67CwRLxpDOo4LzmUPu6wMVrnyYWjMy4EuMPfPKoP3XzZWMA4AcZ5Lx5hYAznwqKCSsKLuqwVkxE1bWkaKEq4GuJnGqHWBugMy4nS85EwTB9kJ1RiNxtPgkiCPJbgoBlEitTinPz/QsJnLO1FxG9/tOLa7yzfPMx3BY+ijXZXTswaDkJRzF79jIMWmko=
*/