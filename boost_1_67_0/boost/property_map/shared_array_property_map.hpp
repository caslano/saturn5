//  Copyright (C) 2009 Trustees of Indiana University
//  Authors: Jeremiah Willcock, Andrew Lumsdaine

// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/property_map for documentation.

#ifndef BOOST_SHARED_ARRAY_PROPERTY_MAP_HPP
#define BOOST_SHARED_ARRAY_PROPERTY_MAP_HPP

#include <boost/smart_ptr/shared_array.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost {

template <class T, class IndexMap>
class shared_array_property_map
  : public boost::put_get_helper<T&, shared_array_property_map<T, IndexMap> >
{
  public:
  typedef typename property_traits<IndexMap>::key_type key_type;
  typedef T value_type;
  typedef T& reference;
  typedef boost::lvalue_property_map_tag category;

  inline shared_array_property_map(): data(), index() {}

  explicit inline shared_array_property_map(
    size_t n,
    const IndexMap& _id = IndexMap())
  : data(new T[n]), index(_id) {}

  inline T& operator[](key_type v) const {
    return data[get(index, v)];
  }

  private:
  boost::shared_array<T> data;
  IndexMap index;
};

template <class T, class IndexMap>
shared_array_property_map<T, IndexMap>
make_shared_array_property_map(size_t n, const T&, const IndexMap& index) {
  return shared_array_property_map<T, IndexMap>(n, index);
}

} // end namespace boost

#endif // BOOST_SHARED_ARRAY_PROPERTY_MAP_HPP

/* shared_array_property_map.hpp
bSZHzQvIlSaVNmkc4CON3a9hslbobW3Ml23dntWrxXs5xgVHLbQYgqnqHCuR4ByWKE9Nh7Fs1GsrDpihkHhQHqqDGA+YJOcKe9zEqMeykzAmTXGOOhyL5YD2DNqSmDzd3j0ebBYI7rk9XUnzR/1aa0ILDRdSBgRUJIIhTe5nAAStZiOsYWj3NwMXBTK0zAWAem5etLRpVtJRK+TgiNc4CTbmmUHK5mJ/CY6aOt7Idxt4I1q6fxY8IBjnQ5pvnBriqDBsN5EUBU4e9fDZouptzvUeyiXk4e21eDos3k73rjD1372PfveCNXXvC+aopSK3tDUw3PK+6m3L9bbMgt9zIklB9nxkSXIJ0vTLFCMYlaFUKq1D9onOEKOUBRKgSgyImqDTCuM+1uRm1Q/eFvhQxVMXEh1wIwYcT/8AKDPcigPssi+Ufd5HtdL7hgRgVi0JXirnDz4E4CgnjlYxd000prHR37bG/f5vW+MghXT/TYa22b29JjANBCwGiEVLe2dpPkgwIJPoZRnfpBSGnoLdcS34siSzC4hT5bYk9xWsNdyFLkvI+fYGdXZjmOqU/ADkM4gBq/nm0B9dA8Z/SOqFd6hLF8keD/JLBvma02dYAgdtAnF8QoLXOWTwOm83g9c5/Dbqi10KokaKmHWdshnBhJpWNtuWho5T9rha3d16vkuCkvgJmPziywzwGCAl/VioGD9Wqwt3sFAp1Cnb9idCe5wgp8bwlmZgxVJqrSg9BP5p+sNJ+jGBg7yH1DEKAqh7OiWEswqK6MlLdPKwT4e2I0ehBNRMsw7DuQlo80hd/vUIlHs6o/UwZ6XlN3fuK7XHQ82GPskhKk0cOohGbH/I4EuKI+EMdnI0OHkyr0CtkXszaEFnzAIxDuynr3GQcBzOwVdZkYiEWMxcg+76TKeDjj4MWYJaB25+7lyiVFjVRQsu5vHRSYEH+2053ydcGjZ1a7E5JT7xB/iIlV1bjqIuxie6cCKHgNSA11n+uBbvAA7+x3qyVJ0WdOrPvJeNpoJhyhE9yst5ZGAYO0DwcRhcSg8hNE2T2K51abonCp3J3vUe1Jgkk/2D6yEJ9jOHraJ+UGC3HJFM9mV8zD4tiZD+8CEJc4jI+kxrCutOfdyPMsISNvjsa6hwcc0BTFH2AsDJ9PoZoDVuQQPirjCw8VSYYVU4zw9J5cHreth/gWejDiMgJ177CE4xv020R/SnGn4TEuvYFSzXCybJ9S5/SMr1goO0BTkQ6ZXeziK9I+o2yGOJAFhzO9fQ6XiuIR9ixLPBITplIr3wEASPOwrZVkMDQnwKImFCF9L+meoHiQKFazMYauF+kOVHkqresECvdqR7T/BCQhCp7L1oOp8G2hCdA3ogIeHuCmYwoOrQg1BO3nOQdtlcWcFr1dCh2BhtIXSvb2mIA88dRuG6rz34bHB3hY5S95aV9xkix+y7DXnHRvHKeMh+xcv7mYipBPtVH8JEXLYfig72vONgCvazfedfzeyCJCU0nIbiAgnNUgmUSDggYtmIdx/EaLSodcBqLDkdrm1iD/K7t8dlgLd1n6FMhyCa/QlAu9/eQMT6ahiOSlUJSWwSTHL0AZpi0fQd6KrLyA0JOPjth4CDdRIOZEjYDUr5eqW8vtGzlUW87yBMAoPDDQAHR805HWXqYnXngwbaVDyHJeakDZjBY5244TYGjz2u8hZHTU28tSCuF0hNBgwejpNh+Y5XNGtB+C5KT3CSwbtpdc4706Vrio+JbIOoz2w4KX6THtanBIeUwJ2vExLtH56BCNNmDi1Wwy2U3GlikReRwxOzXspy8mD62bHNbnFhD4eGvI5ay7PNQyGu/b4+2zLuxZvXSmH/X99llQax5gEAp1O9UAs1S0odRtbPzGHBsKMWSC72J5719XL8YhN5Ke1JGrfmHwPsSnw0auK3Q2gb8R6GRZeZmfQWXZPybKgRhMEW6lD1HskTLZc80apcz0o1tJ/ZomdzPcv5TGGlFloubqfM9M2Q06fAACSIAew47Zk4nw4fkgorzT52fKSBcmsQD13ayxzGSai9StgrfKdLK4GOj3jtDPSBDxNc5iKScL/BMs/vN1hLr+mBO4SDHJKnWa4paMTq4OptLTbAL8lK2TeOnUGxD6SDmu8uI/Pa/soy4f3VjQxAB5XytUQ50v7sKmdj8AbVe6ikpExckQ12oEF3UbCMMERshJomAycuY3xB2XBQ9PVIGvPQfrUqxxglvxyjeFhcR81FqOob3IBkBgLmJHaguRfHWatpir3sH2MGViLvY8x76r5HGu/nnWWwjhCZ9byY2MsmYi93S/ayRLKXCX+qLUSlDjQ8FsVyqIZsHWX88n4DF+sm4PfE2QLm1ULrY9epVbBdiOPDS/3i1rfjiK/MKKA/4tvXf3Yvr+g3u7/L5VPJEzAH7Gnv+lrT6vt+ATvAyvo/AgVe0pjCDg1Y6LwcejiEQG/HRz2SDFNCfWLEQdaWqFWs1M6lQIfuPaFBavnK9psZfTRDM0FLkXgm4dLrlYA8wWPZAxHejwakv5y1AJXSQ3E5YokSOiT3fCL09+C864CjBgbG0IlqsaM2R81E5M234hZRyqEk3ISYJzbF26R697O1kTZrtNqphFpAKZ42GU5kDohzP9JPa3i0QU9BFAoukDgnoBvpShvexGSWSpnlRl6I8mynYQvhkMRRz+tbcHp0gPYA8fz10OxuYcPj3YCR6wID5+TtLWY1nzepFoviXa94N8Dvu1wc69nCaSXckhCdoYYPJzvzzttLhbp3BIe5G+EJBbSY7vkvb6+aVlwACiz10wxVcZ3H9LSAAE+iVBcYFEi4yeSohUJ8Xo8u0GJcFxpSQrMsrri6R2ufitotZXjZzAwr7gC17VeajUd9HO5NUtGvr+83Dr/D42ZgH9rpRCM9wRFP3XUYkkPs6AlDYrBeoUrdm0/SmW4gFeGPYDDMVeqzMwxZynhyuImYm294ITesCKgbAUMpGIiHtV15dJM8CqqdxBTcpoUOU3X/GA9HYDofJ+O1Rt8AuomG6/G95RViZ3O9WynHhGLV25DrrS+GPs8+LVQPF0ustRQ+nNfjCjU7as/S4mr/kn7ExPuoG7vcn0qDHJ2QX/NDSrxw7lzqD207tL50P44EtHCl5P6USI/N2CJDw8vKzmM55Fy8yKcWM7nkF5JKnv7DxF7erIdT2BMc2LgU5wtm3qmb1aFlWBnsFAy7VbNoT+/VqNLX5Uqm4iR9fwpthw+gT4NVke28ZVcNUu/MUV4E8xoLiO3z9SAPV5tPajLGKytKnPgAu2sLIcyek11ame5Bjr0raUd8hotGuJHjYJxGujmRLiMi8Jn9uT+eSDoF0jbXoxdxKkzesRRlaL+xSpDdy8WmK4jsfnenPGq21rtuJjR3cAdIbskHdZpE9zyWMfnEPNNJTe5dSWeXHlRtyJiuPo9s80nKeu+9Ov/LBrxNouN9JlvFTbLe+u5fGtEexW3pX2uRVyejzMir+fjTmJaxKlPGdQS7RS2phC8dUXavjA5kCMBHUKsrp9MXYnn5NwXga4DfD+xIEoDLcsV4qtAQgz/FH/YzMurnNsOpB3eBWy4wfPPN8FgWMM0dSetxBpQUAkwDYBXdhTMkTZ1i/wsijlnCrTGLJdyGE1UAW4l47tNu3iYQV81VNxYQfbsfpygjhn0N1jFujMAK5qHLkhNyKGHoSyhZmZHdOCMHwxS7kBMiP8wxUWJsgFqHZJz8s/6ZUA8GrCWaL5swyAHhOUG0j2yJKBgj/ehKc2SM2Hne24HW2SEF294gIzujMIRHaq1UVopsQSdMwZvVaq5ZwSRaBi+/cISTgG8Zop/RYpRe3ceJ35YnhyXU2ZnT7X1aBaZ0Uv3fsN8WbIdAhMacePkHJA/66eU92qXlfdGlaDvH83pzdA8zoJeoB1iUkUPbXITDB5rUG0IDipHn7y1s0PgJ8l0otn6/K9kSkNaiCg3HntC/KG87pCYlosX2NUtctqq9InA5dvgC2tyJrbYjEBAI8TA1FltHaBDQpghtIkr4DoXgO9SQdzw2lSt4VrLDDK+7fxBXLxjNfhsPBoeLB7YgwoF6UG0WE6gASEdjaSVi7CZuz9tUPxaqcFILhHO7ZMnWUwPrf6rQ+Dy9DQu1LBr1gQ96C+6mxfT7urWyaC1S8o7TAK0DJ3T9u1JhluYSWKi/Dx3Mrbjwrq/gHMlVviFkUb3rSxIbRCIEKlcgN41iuAqbNUFSU+LKfboWCzdEZFITxEJq2676Q7+ilc22hcOkbaGxZVmJ5YDNfn3WC4YP/RORgxrcK0GNxIqsQYBZb6TKZgpmq0U2I8nd++TgpEfkcHI8Iriw82XjOcMUHK4WZfAzZR9o3Et1pHicVrXY6lcXWd1HgyNL1Dk294fBC2Dm6D4VHEDcdqr4OWG+ijtrPwheQFlS3T5baEDk+1aTMtUZS49830Y3GUph1jygC23q+Lg/f4KBY4gN0955lnVyg6POiz+ix6ORQxEaAqQg/QnSArUnH+azX34I0ZWp1piFw8oa7m0Sb5x4A7dRFmrMeW4lT9RqoVSxrwL41h4RpuCFhUFHYTC9MHSh+1RssKvKHrO5qmwxi6vKGrKqe2JX0DDmNeA8QQvZ/eJ1Vv2F6XUGpQ3gtF9TWpL/yv52WEOBIvMayvy+8/GI4j2kzbJHQx3R8GGCoLwG4nhaXZ4MIvFD3ZaQ3RJ2xi5QSzsspXbV6zTTZhxqUUoPE2UULW1jFWwhLXlyiSrx2tVSpzJIKbG6Q23h4dLbdS5lsjxmiVxuqt37WMqpkWpjLlHbHhEengud82blCetj1sjdVlPtB49ZTt1pZRSm7gIS27MkyVyFxtU91RoynOjGj88BnKFcwGNoDA0TBkT8nQeI6GM5QOJD+YxvK3bB9FV3SmH1S3th5FnwLyLsGkPjCYj5eb58zjHK3Ntv0IeILYky5SGH4SKmRBaddxwOtZTyXq4CPJUYzEUGzdNkHUNEXzsnpOZpM6gMTVblFG+AZS6izRQIhKaPa3SK1ZycIW7m5F61yJ7XQNvoeHczrYzeUJbL0xsa5u4Npro8fYjd2xe0UVLQQi2U4WRTfeLgE2fZq3z8XMGug2RslKtqbPAK2YRBJX5xXPbXoS7MgKcKV9Xo0CdKBTBELF2psMV69IP2hJ0/T0906j0xh3uqLWSLVoM6SsyVvj70+pSqbOAPHlsGYNQn60qld7E2A5g5SgKBvzaDstpEDNhukVmOSbpooUeLxB+Rx9gh/a2QBq8FEaBOnWBMdIZfrRrPH8TkB1xxuvgk8TnnpB2iwFrLUYKzfeKCwzwElksLrPKDVHEErWSrXZnlPx8aWWyy8WmRqmxTaEvCc1O/0yua4xOusN1R+wtshEXZwH9B2O0gtnMaW4QkGVz57Kw/t088dReCGVqJnUp1e2wheOCg+6sQdGS0WtqbW9rpD2TMUku7c0s71CYsyFCnFurQjRNi41xVRO1QF4BWMoIX03hQnaUCitXm5PMx+KyIkxCF4bgHOxqYDEKd4ZE9rKKMiGIwNrRycJp/xFG3nUHfa4NHDg88dqieDKWAoFQpym5Mm0x7ilJA/ygtSykY749WTVfSlRlWZYZNmWGPVsyG2557FIsyzapMsynT7OLHf+xhL4wAJDGfHiJFo+kaS9c4DQF2StSLoXqifRi5L9/kx58JJgS9m9dYkHM9hngPQNQp+0ADQBPgxg7fIVcY3ceDtFdhZfPLg3Kd9XuZQauNEjJdW2D/GBrseiwnKP3IKlX2hJ+ufpYQNr11mHb47YLlyXnmQfpM94u/+KE0MmAq70OCETGrF+2xqhez1ybPVmrHvWLHF4Z0ciABVCjVFd4avINZmgIrmFtZihHdayJ9Hy1tkPZIgA9pcuRpg4FrSyjN4iEKsw229PTciufdwOxFNq6r9NvrItAssOl1dfSry/ZtdUljWr0uOJfDc6deV696Mcz9pFZJC6SE6DsmaJy4Q8YxTtQ9gqkKPw5peY3s5/zyE0zbtSL7/E9G0uok7iDq3S8DGPX7yID4ssf7uarLATgTGndVZNN2ne2HwM2mzLMql9CsGNQavH+JjT08Q9B02BfMEWPajPFKdZXbgg6mnKQjRB6KIpnt3N/Pz2bTzzr1bE55tk2ZLxK3cchhmdPO/Wcvuj5ArR4kENku758tA9mEzGZ373PUwEezqI1XPIBPDCJYKQfE2zKAs1v1tLo9vU8iUruSjhDwCPaJO4E7Ae9BdnUJ9OZwyg2r6T6Lp41JdIIot6cPn/bRwjZCvPNtB247pB8h42thgVF2r8XTqqTHivvV278kgMK+YIaYziGAYavdiSzd/CqDX10Vf4UWck1xxQOeTo7nXpTtFylf8WyBjY7c202kKmH2S8SCvxmDYiXi0JizzsRkGAfTlHuEeJs9lnFWYzZ6pUFz57wKoxdAhWZqZbwjU63f1p6H4QWgyHZee1o/P689tv7tyejXntx+7cn4v29PdQeQbP/woDNpf2L7fSW0mvYptYk1xxXvs+LBUqjR17IVknedFlonaWXx7HCzSe3Uw3/KsMAIvXde1NCjqqWMudZ9sIz1PstG/WtKaY/bJ8b2gLhZok7Lcu9RPCvVTqLiDogL2CiE2ImFWUpoJTFhMbDEG6R8UvHURz0bEE2uh1BDGrj9DXKVc9kbfOIWlM3UaG1DVbraq3jWEy8efjM3vEEJr5fhWWobnkxTYVlNRa4iAp3et+UCX69HCDl65Cjq9E6duEHHVNoRaAMA1jwtNNCxYdwMJNpVNI4SqbBWNbQaTp5qaLaWUdtqmFuXOLHG3Ru2UGtUzzKXZxVuV8UHU/EuF3MzzabAPWrnPOJ+4CbWEri+ggbJ8pWUZr8KMcU0u6Pm11h7+8TpHpyArFO9y2mwZoiJmRzZyclT35m7w/HanudPwbuSt1fdAbvyo7lHHK/tpDT1ECXsVEvsuU9hZcLFZxO1RfG2xjziywyjmG5YQiYV041iOv5HMR0IPdyCDnpbLd5VgYEwXvW2WCBNbpOKOqp3tTqU+JK1UCogzP8MGy97V2McEOAYHgBeyeuR+rWUzbCf362EmkQJNY3t7WY63QeCfi20Wlz7taa13wtx8MyMvB73gdC/1Gk2yNwvNnO56tBoeD2CMKUQUK7XnoEY2hVaHyynbATxWmi9e09oiphQD/M7BC6MTVOnWamS6f/j4xzKYnxMdAG0gPNjg8R/NuuFIAZiO/uH9qzGE1oUsimhda5HMmAEDUfr6Igj6t2asIWPDaU+UL8G0jKMlm6dZUD0Vp9YMKtbcz1iD06KQ4M6zU7stVcQR6ej1x3SBpRIN2+b4t2fSD1MRIQ60+Y+4KiFmJUqaYeOG7fNxp3V2+b8321zfnvbDhfLtk2AP3vgtpnwhZKhYvU051bbeB4PETlEnCVMjQ8bafthfDzTSqVmIhylXjBbs9PEx0bJGi+E4UO0dK1BuG41CNeZdqbuclzhdXoBkkSIF5DmFwd/gijGW5nIkFQLyA4DB92JloeXOGpgR6N6VrobHTVDcLvA7j7lqLHgttCpLgLvkRmwlIgrOxkvDdBHKTYKtr5f0B29VA8KG7+WIaYj964zMdWx0BD5p6nb0G9gA7ArkfA6U3B8LSIa0JYYXkVjpK7gKaM11By7Df5Jwuthlh1PPRybIMvAV/QJIaFTn2GQ6/RBjmVYgN86kHrYSN3P3d3vE7k+Qot32muPw0XcWpw0MH20Lz5iqncldpK1s/I+cJWuczy7c5Zf891OeaXyHAFMnHa66CHpgUHf3JK9dsMEVLdTs0sVBN4R+oXJ4gDyTBdDwywfDMsog8rrkA4UeJNtw6bWzlrO4IccNd9DcdBgjUeVLbLGHgCbczvvg4nvM+Lf04Zy8IScmTUM90SE2JI9wwhHdC29yMVq6tRrs6G2DtM3arPpxTJGR+NfouIXcPHE4IK44VApxG3p3mJuld5ibqFst3K2UDa7nqFsHSqEKt2c7TJk646NVEFj2YBruXUd7tK2cFouVnSHwUDyXtok7irqZv28jDi7R1y7leg5GpExGJEsOSKGGNHg+GIjXFU2Wp9FNi3PGDAJAZb49Lof7Gf8itjhdjDy7hlEYAvT7UQbP2rNa3B3Euk5wxb8t8tjD1nUR22+MmH5N3dySIBoiX3iqw5JpvmpwQM72MNrvwBxxCvJ8NFiH+cMOWfwM5Gn+peqkxOI/xxrmGhI8MprQHfN+eiNmUEIvxn0G+k1O57GEbqrarzj6X08n3bioJ2uerBzQcxt7WZOzsI0sxfmomz31Mm6snMhcSLETSzKoM4Om0m0zweEPJ/dqb5L+CZVWQRh36IMyaE7itWiLJ/4IIYQ1NZYvuTV9dStnGqLXa0WOBOpDZzqJERdkEGpg2Xq7zlVZzzjvGbZljfzRzgbC/gwRlwyuEcD91mUPa+i/cDrmmYwuiys+I9kZPn+7yy4yKaS3YWTqbgDFe27z2lanHPt5wsmixWknfA1Tfi5VRxfcBKKaD88Cqrvd/DbELS5vPag5VS5jSWL7mOOX7OHTPiO4SAjVnVfLEXdxRLR4X4f0TzBQVFPN22M09VJsYEwIcDtIqtf9NHGWAKfbV10M3cuZIOpNMMxs198TimO1zzNc9mn24d4j1W72cy6qEAnLTxVkPkYTnMGsIBl9/npIU7nqcVRXxpsMg/AmTE0B/M5eJkGHhHaWgdkok98n2r0q81irmzZrtAwv/DSPfvEyOeWsfM2hLsAIsPyS4ULKaLk6CEjOJTbAGlLNy2qStaXYJ8rrnBLcAjUbkJ2qpYqjQ30872T2yQ03+T297itrWo5NRfB7dDexGu8iSejBJlMtTpqfm6AuKMG8RLZ6D8Z3ybQV9IIUT+CQ9yfBVPN1IGhZk9HzC6femMWM1GLRXYx8yOdKaHNvcAex4TyIH0+vA42iY9uhRJzq3adutDOLLc8npI+aUQco7QHgFHicYsn9XNXBfhj7gHhi3tYrHGsn2eIo9/CVBBdxT5UiDBkTxFwE0F0S5bhX+go0RZA1k0Gsib6ZgTRFExotEgPZE49A20SoNHwsewjfcyY/nD84wx8nMEfyx1mZoaeAR/b1SkYlXjdPjF1FQ/PpkIanmnxsaMXY+WLX+PFFMlbtHBs7NBUQphjYsZWIngfaFVL98PZB/aIS7FHiNhFxCzzuxY=
*/