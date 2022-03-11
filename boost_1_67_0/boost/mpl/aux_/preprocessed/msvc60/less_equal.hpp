
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          less_equal_impl<
              typename less_equal_tag<N1>::type
            , typename less_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less_equal.hpp
ZmalDekFRg0s1Sf7Nh3kCHsD85qIhrFaYEu1xycFEKxfU1d3flQUXQu2M7O7z3C8bfLm1b9QAgGx4kAhzIa3xXKQHc4zldMsHecKnBdyp/hLUt2PWkl3n3QwZuW0ozNFmfW0JJt6/+PsGatwElWzHRoR4fOHbkkBxLfdbPPIF5ZV7kptsrKchLpg17ecQE8TYm7Tm+YDK9/O0QBCwu15Nqp5o0L7+twSFwoHr+SSALuWCFCu6waNd0uMlp/98Wky5VFhK6a8qronMyFRbdm0thqDmmLYUmccirr6wi+5sIrKEoDK+YdAisYouZzX8vL+QIp3sWSjUYwGcNgo0Vb8nJn7SKxKTjFM7/tKwwtTaed67kn1yIblj66alp//qFpfHn75dc30ZutR4jKzu7Zx5MG2tcMJVj08c8MihlehVthOP/JWlcx9yi/lo1lhCrSmrStbnY+1K4W4+Ryj8lhTUuI9W653OsNwbm2Al3nhZ2MZmvy2m9NFfQhapK0IgRtYKjO0PLmMW5NGskG5up9uWQefShqJFMvh4g6H4MTNVd1oPcIknXCsJS48+Zn1oyVF9W2PSpJLaoqxX2ztM4sf1acH2j9ahUEjHmpkaHh+vtll46hSTypcPmmReAjQl0PFhGCUTCeMT+LYfESQ1G3E+KeaSEDlNBrO5wUXSHNPui/sDbzjKyjj1Oit5Gf/ZzHfsiI0DjnUAN2oNzs+IrbGs3tZhF2Hj1wdOdPNA344pHd/7gGeps89OZx7/j8IQswnQvvSivyV5Ft2snpPc23SBYYukLiJpdPaJClirZE18EXhyXsLzWRegezf8wNqpNjDIHLqSWbQBGBr2Mfvl6gfcY3Ob2Z2cFg3zv0F1OFHNIAUo4/XGm5NXIwCm5oA+1KBvp4z9a8POK4YTMgXyaVZTBdkBO09Zwh55Mae3pX18bIfy/15WtLCkudTXp3Vmxd3hM/VQ89F0dvZm35wgbfw2/cqMu3AzqWF2Pii+Oj1XeurUF30VfD9Kkx9FfibZeLqY5IPX/lZZePqbWR/+wKHLqxK/xJqMY2tvJ1keV0KeWrZIip89CmN8TuTnedT7FfvIAW8JSC4CwgD+v3b62Zu+Fn+8d+UVqP8hf9GWGjCp91fbBx8yLolW6GAxRrsyTtMx/j8nVRq9OX8QKWOVoToHuOGHFR9H6LbIphl3v0nXAOuZP0PRICCOM1ufHLRwXcMEtYSG1B+OD3da/3cKw6wI4RkA1DzUrFWUIhLmDbNNjwFtU7G98rUWh7VTidW+92wSCjdWkoXQSpXxRWIzB7w9EhJKtl6b8PAgmrcdwArQ1NPuVGdYY3viosRsuXpkWBRrL6OsGr/qDDUcMuysS6y88M0fZSI7mPux1DYG8S0HFtMud2DKg+33p1Et0HCFUl5CZOOE5PnfK1xPba4lIDGXiW8LRnaS3si/vie4SVChCcdApFcNR/sYP7VM3p/XpwtDi7OP/uMORHoo3JlN+vuMtS+Me2WmLTTzKq2YV51DDbVjE1XN6Bs9eyLsNpavo8wRx0dWmASmFR1tfzhqTzmGMxP73n4kBU1kwCAfFMYv9muGeYlRkv2aAQ+hXfs+5m0hLBTCv0nZBn/97Le4dRymq2ggOuSY/uw/Nc1LeXCzvRYggyCJdkY1GQoXG/M0H+6KCNWuNLlmsddwTbsWYRq8YkVRHrB8fJTbPX4UbdsoRVPD+rzDRUSSln+vlQBBO4xl6xSd019f/QOV6UrdOdbdsSy6uQODu7c2+7dJ5g9CsB27vURLViLVuU2d9sC4w2IJ4ojJVBqbkvIzAbtPcREV7yyuAUvCPiJbsOev/RE/dzH76bkF1MT8mDPfMqf2AOM6aeKlQ/FeiHu2xUvzAWrBT1/kt0kqa28x8E1f1P4y/EC8NOaK6W97kOtPmEkdxAJzuevtWzjmnDsyl7Oza1hAHlyEGJG5+e/c37wpQmXTQRAM9uKLOAibiq17984rgDi+5xuX0r3DoOxOLn7Aey2fMaO/z6qZBH2Mw2JUC3NqYV5a6RK7hM68cXoLyGAnuI7SO9aEvl2p8lYo5bsuD5x4joATqkNkQmcZ2wBZWR1te3ZYwTH1CvSreqXJYZTdmDIo6Cg1C5Zq0gom6swphhKs98zgcnxL9yTquMxgfxhJkusrqhy3kbe1ahHNpqABPloEy12VxoltfolEjYi2Gbj8ui79tzY6NTJVXHxXwgOQfONGsUiRZpxpNpbJ34oPX4GjvSeNl99IlacV0tiuDLmaoI2p/b5r3gyyvYOhByHl8NXuelJBmw13UksnxCBeKuApg6QqFoNENohO/vQxiypSRjsDSvss/+1ql9yby8G5Ab20P/dNPFn0z1jJdEAm1cwxl7A8hJqgWboGZoxpvXY5Oku6py+sZzT4bdwtDfUa8kkl8I4NzJwkYzMLyCSqNPaXTSaaf0gnB0AHrL3TxPyfFpwi/R2t4WT1f+g5xswK+RVWiJC6Tl+YQdnLkt3V74dU/l139GarxHeu/lN4ImSkvZBY7yN+OzI+Y7a/z14Drhwuwqvkzt9X6IuBVOfvb6cvW5ZCr/PcNxuDUQwqvv81Z0JNRS2j7iqGOJvrXe4lkwQRzMDWxU599Q4cHYiSz6G7gqs8HTJjCfC4dyMM9hDPqtMFKMbIf7jCBEiAqgtX1M/dXyeYU/lx2ZdQVVUB3ciYkFvAQL05UibF/ttIE+iozo/WJlt/fTXD/V3hN8kyU0w/KKt07LGF88Q8UlMz0pT+j3/vM22Uf22hzhpRbTdaQvpeYU2Y1W4u2nv4xffdPKIsVk/IKRDy5nZ207DnM/3aMjCCL8TljWPg1uCPOad0Otmg2f8AHgqw9p1a2YaeyZuzrjT23G9/tpUlCMlJfh1sKIBpXYSrOdVUm+t/lzdtl9zdEfoz2Ms1EVipdym9dCMVmFV/V9br6asV0IWHtMjSpSGtsMpWtjHXCR2r9vsT5HPNlMwI2K2VgVAJQBYFHL47rZLuVY/QbV2U0h09D7Tp1pnjF6fr1cfOmZb8m6wwbA2tEW5Vix+dHdPVpE81fdZ2O5F4tQXFL9s37bIspR6ULJqC1Sw96J0Vzuv9De/1th3Ll5JXh+Xpkh3LV9cqea7MN0xmq6QXMFzDK5LkSi5EMEquasM4f7DJel245k0HWKxAxPSd/WnCv0BhxhtLWypPmDL4VQAQYYkXPggFBy/9knW6SHxMogomJepOzNz6nIszP/0DaGLgrgam9pp6hxqaRFSfujq7EprjrjzMwK4lVliNzDjCFwX/sZASfgfmC5qK5n/Ax/hw0Nq5vI9u3S3/qL/ZMw0AMvWSD4pW9IWcif0lWTcKeyTMLd7EQDoUDq/USzqcyIuHxFJuBDLS1gee23mNbhT7x4N7/lrcDftJ+M2LTIkdGbWPJBcVMB5yHYmmF8RE096/JYdoHI8FMErtgWW7Qdx6DjRMjwk4x4nHC38UFIEkR/iiYLoNXdnJv/cpyYwhCz3REHeTU/8liWVrp4eErRu/GUlzEUcGH6BifKC1Knzd3roFhvFBq1k4xXCJ5epvU6x7+M0dsxFMvYWfBf04SEEksqXHswVCoLWR+trqB+rHgEZf28TvzOTYt8EtNaEx59UgodLyib+S9ZoR/sILGMgqmoTX7m967zYmJ382+u+uqMxE3+cvuV7fyXlLjeh02KAQOpQteqRJe9clVm/zxbYj/zMXNAXLeUC1LSPUdiK/gggvDKcLxKm3tx0Dr9YGvzW1n7nJ22XvB4xbQjpx8yUWq6f8aCaGKd5X2wpcJtvMDNrvz4RmFt4gB1QbfnPIIAZaWe3jAyPinu3de8K+kZDPBD81wiqL6a1e7nsRuK68ZaqwZ3W+mGJpbTbsOZVsrWXbEVceB9hQqRsYqtxZ1gL/B+LSTfgh9YFeM8ykJeCoh/8IyBn+gb9s5JQBPHT99ZnH/qzJwrHgGrER/Jr8X4ZO+KInEE2zHh1ZjaLh3I3gFM9ySvRi3g/V3VvON2t0TI2eRCO3wK9WFZMDTTpXvUftQpvCDSuJnjF+l4sSkDC+jk39Ds9GoTpvT2/W4luhPwP0h+oOO3y54VxtUfh0qMrjv4DEP/9AyDn3/NbWILP2Kdm8z+w1R93cESCORaTQwzSX2Pdt+Bbp+QiOuXVkHNNW28QshAt3WqAs9xHa7PBbPn9YdR15kvkj58MR8jpT6Z/5uYfFYN7v58+xK7USXOdeHAsIQ3WG87aDj3BVyPXmJt/rBs7a7WdncDXLWw+kcX6wxw3V/UoTg9M9aSuMIwJlut0sLpH4/jU/XYVobw3lB9m1+TLLxkfkzuq0aHHdUPiXtJluwo+a2j0265f5hutTZgR/tmUt56vi3ZG+LhIovfZBY3FxvYy+g3swjHGwy781WaWQ7jzZOHCS7A/xCNOo14Awzrt5xBQ+h8ZgTQKSLXgLj3kBjZAoaZNJGH47Wl6cqs2L9PSH+e9b5QMxX/QeRo89v1zXDjND5p7ULl4Pkz0x4+fy2sjSSm/r39QvkfIy4IDjLXJsI+cRxsTD11dW3CefkAOUPz2xbb5iWUbK8Ff1qMy84Oei65Y/Sf9wGrLeUVhJY+kauI4TG3ZGrIlvvmU5bIGxnQlXUEgTRRhibX1sDelwvpqJRe3XJGBd9+O1cvOS0826Onyxk/Y/WXX7/lg4+S6ak7/+GgVmRs8NC2W4WUZNyIifsHcztkPxRrlNTjibN1Lk6P4ybQjvHokrnMVulLCN9mnaWRWgmJBy8UhLA7mrATb+jlYejxHGOVMi30z/i9+H1g+xbIjN0aAV4b66/ygNkbTNdLN7l7ebIfhan4zNpuvnkMNiSrC9LA889zvmXTk47Gxznzn2Ge4Va4e3xvytNQifESbUbgYC97fLlYT16v1YfZXVJMzTyUw/oe5oQPeSaz8VRoBf0a44T7sNBhQ9lE3Edk1zTgoBcXauxM3BW0w3cAba4Y8Gvod1Gl4yWIE/vx9qkrsGt1Bzgq6sEIfnjNp7GewdO0yDRBOP4JyQW61MBpGK2rWKdaZinUOkkbe+AbiIhhhrtZo7FNE9F0sq8roZ+yN2ccvRnnRou8CcEa7GcQiXZ5I1WnZ4PvUKrbah6ga7JQpmkuY1fozau4ElFB2xij7ysKNRPiG7DNbtq7Y3bSalv7QFThUB/nbaZ3ftL/NWj68/cBaXTMYflVOvwh6TBcNjWI9lcSGvWeWy0vF3eaITzKSEQpdJlukylE2yvh+7wvIpnYyn+Er6/43NjZVbUr8B0ydSCJ2CJA/HKa5Z4lqKpY45cXs+K/08/61+vi/jSVrvX2aQ5Hyic9/G+B6krMy9+HsTfaJ5Tj2MvdPj5zduAFn7RnpuDLsUPv5OEWb448gWx4N9PuXKhR8Itabhf1Cu2HMF9voyYDQxIr4RHBG2T1Z/CQpcex/wjoVrifiHiyufTLcuWiEum8/HMDacU/GNrBW5u8RWvIMPQEi1TGIP3+smrt/erZpXAbuC3+/luF+0Z5pv7pstVVw9X+Wc2v3Ct6uvLQPymVZ181gWM3fqXFMWt3dWQcz3p1QgND3ky18/DDU5NRTxAWxcwzHA1wXX9fdecJrm6MCpzPTvBNP0qdnB5pdjc8DBEv0YFY8cqpinJjuxMECBgCkHrnrRP+23pEmBjJPA55BaHm3hpZpgra+k7fv2qTqlbk2zE9NP6xKtXHNuS5ShdkrBYsZPL/hIBcEJ2Jf+JfHpQr/mhBpoB8x4YAaS78DqZ8+EJvs/tKLRxoRXlyyn8A7C101s76SQ+wS6aiVqnS0e3ss87KCZ0oZHERTH5w1n8EKOb6U5C1BE+fnofEFeQGZ/NuTHQzFOKlA2nEOCQgiDZPRNIOABfZ2ydcQvrQu8fhypoRxtBR6DJBjDo2cK+RpjuR4hVUs5hMkULfox/RiLsib+dxTrgi5YAjzDt+iVhIpsIpGD6ZFs2hElIh6EpohzZovQb+IssAg6tau2z5IkiiQg2YzduK2LfZYkXU+Qj00pvsKzyeiR5IxypHmnWHhSTJAyZVmAaqIFX2G5t2v6CFKWIwr9pSpCLUIQMmfd8ob6e+mNz8XBXposYw/yAgzpP4513qI8AZtlyidJsKzvHGVB5+iyBFmlQwBV101qSnupK+pCVvikRcec79/pV71V6n67+/YcYgKxaS8NlZExgeAeO34mv5duMx9BvwOw6H5vLUjE0Is+UDMiqevvQ/y7il9yJj0+68QD/WDO2dj61t+LtKXYCm4G8PYMb9Bm9uqrzABEc4pd/QAxNGtcHfPTfqS91viposw/kMtaiBmzXO7GZeom/0r1P034T1BJGhz+3eNmcOTzFrwOkQpxEPywDk+x+T2+SvMHxIe2aq4+9v+jN9t+fVA3dyeUO3dX7o1/G7q2DFg5/SelJ3g9ZEUXPwbMumLV/pAV8XdK3JCodBecr/VLYx3/0mQy6atwQaNVl4f7bipHy3knTjyBYA26mmr7n5ovd5bhA3+cDf0MYuR4qxUloN0c0KQm5f5BYD+IMrETc8kvDAp5+olMtuX4BTxmR6FsT91pCrm779DbNmRHh+8i/A4S2t7VyzIIjJ8vlt/sqxPvq+8EsoYmYbB7Ne3a79GFP9jbyVhZ+XfVaWpRx/p0VYRcd2NFYsjYK4JQSCKFrP14rkxwGWk+hXNlkFK0XhO4y7cbxuEjpSDfkWkR7sJkPqbbM2oCkCcmrX8juox3/B+PY1wR/GhLClYcBkaibaOUE8jmMT6H8U/ikF5xBfMWYpt2R/yTvCzQ2HODKB4XEu/4FewwpR/YSoJctxv4D/aKgDzJSzCC0+UP6oTnnOGkvfupoWX0xAn+o448xjmsuctO51TfrymixBa9tSFnaUlcXvTt/bIqRoag8HKeJQTRCHef6XDHtxhYx08swmGQFhC05uRFxEsySrfj9MKPoObYBkUyVGa0KsIe/uKRJ5WHtz8G27WcKzCTdgV+TtbEXsAACz/03PjwzsUJIFFHSfhNQMPctHblwRf5oktnTDTALO8ERDGuJUEKL0TOECG9CFf89wu6o9yiDca4+sucFw5hSZB5pyKJCVt3sM067vAGGMeW25MKt2IPnJs5X24pD+WKnrjDBRlSUIrIrl/8EePsSBv6SfDO3wh9qoQ5EJbJsG702YlA+DpcP/7VmQpKc/9Idg3ipTsYfrbzSAD7Lm+A98AGPv915/MxfnDjymmIdmaUrVrF0TJbpQnhSMvgqJ5Z53z1puYz/lyy+B76R2C7x3CFcqKeU3uHW6tHqIVpq6x4CR9+U2zm1OiS+S5qQMttC+VG0GkihxsKP831JpC1SPE0r8y0HKrNeHo5JdkBsCnNxgIIX/4DnnfB5GtsP6TK/p0nD2GTMC0D+E5k0q8e7DjIZwvwNaC3z0yQYRA1V+6T7cX696Doo8x6XP82f+B/EVUuBHtRER6/S3+RJ4kCvNNzep366tomica7NKRiuE3Aa+GB8WIZ6DMSxxR2ofyeKpY3Ei4Xy9vhsc5xRTwhssNLIByQ5wVEFX6NDyU8+E8c9Oa0+wMuV6EnV2AH7hfpuMi2D8U/grMSod9/OCuSKd/UlSJ74i7CRjWO37hPz56X6lRWpM2IJc+E0H0w3u82WJ+j9CNqouoiFI8gy3fP0b2ZnaPDriWuL8hIxvw2sbL69JgLot/UC+FFWHyNDWNyd33gictdcEGNYXyCYsvDlis9tXm944F7i0WPew8kkTovoIk4As7R9bj6/BLCpYxD2OAkSrPDxSu5C3P/XrKXDZ/7x7hFzdlhJ99XupVIi9G0LNYVduIPnoE1NAqnmUntegNRvuQBOSsJAp6SCKm1X08kK9B80sAxbV9iqEaCr0bp80IyNr8KYFH/961uhdOq47duacObxHl2DhbIOP1/If2b+Ub4wGhnoAYcO1LvVfebl/WhzeYcBMt6uFy3dG5d/snYGxr0wmV3Z8fFg8SLApaa0EAnJCYtPWsTb/gGllTA/o/RZgHP/fqSnHpzOCFwVHZKT0pQXN2OGEEY78oA6wLIqCSdPWokx2WeWH+ey1XKUTCiVNAAaFJ/bp5ymD+39m8S0MfA42VXrLUsYKCkgL8Eo1tYoHjRheFRpkeQ8UrszihxmUZ5gWuHttoXnW1u4RI3UpFUsWLChWvbyOOOhnfK3SiI6EpC+I4xmuIkyfhhXlyngx96oXsboSGVOeE8n3AP8D9ej7+fTfeff4XLx/MIQEQa/zsPWSk2Esu8VhLdjXsZXTuQUNXjXei/IyDqUCBJf8Tfozp9f3zLDnHrbuHLLmQHSlvH2HXXbisCbEFUqSTlRThdUs3FN25lpaejRU0eGWn2xaU9DkixyTcd9hk9dKafsHSF7JAuDOYurO9KgTOV+Xbf+DByyG8nxXoqA/7VBKX/Bc3gSnYZ7ThXpcSSbQ4dmvJFgncgTXGGbx+h71knH7b3osuao3k3UqftQroRiIj5uhGPgsbl4GSRUpLkpckXM+z4JJ7qpmnQhUmiawoEs+ARlGt+1EJK+fW4D2sMKsObkCw8hxhzdvPiPvre+z+KsjVAfXAxwF2Le1yN++dyw9RO2EJm4vNi08/SR1DN7snLab0rUL9IBARiR8Dtg5sIXpR7FnwP9+gXaaPB3fBMXSLE1qop6PnQe9cLlX7Ee6+FBv4B4v/amHWbjZ9FsD1dFLqOCi+WJvAMEjpIx385rGt0lOBTfQP0Pod7eU6a1809oxcdJpxSl4Sinw3d5/6K6OJBN50gMuAUl1jbw09vcAD99KhlqxJac9CHwWMv/BLOIeiYIVQuOrgf3mISGYfAtoMeLoYXKvxYNyFzFEjoprPY3EFb5W3GV+62B79OboqGUKf7DGz4v/AwUWR5hcim+L3gbb3XRLd+SsAfVGTncpaW/C3Ol3uH+DQyQfp1jFAf6Clpp7YSyX6CogKZkrwVSsiOvY+ilFiNX4YDLVyJNVJiH6EzajxlybQBcpRpsII5NBQ75KgjTfQ25Hgepa+ZMHFFSQKpIDIysVGN9zoAtr8hOOqn6jgMeY68+M3QD3mc4E3v0Eu6Gszf0+Gj3Jo9p2NImW4KC1xSGP1lUj1bLr/eJzhF0pGYTi3LSiDfHpzfwdm1nH9Lcio4IiDLMb6Y7g5caUpo/Do23+J3elPfTGiZ/iPLIqKEAezWHwbMfJUbzxgy5tEeSI=
*/