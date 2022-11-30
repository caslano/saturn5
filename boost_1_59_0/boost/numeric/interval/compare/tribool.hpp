/* Boost interval/compare/tribool.hpp template implementation file
 *
 * Copyright 2002-2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_TRIBOOL_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_TRIBOOL_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>
#include <boost/logic/tribool.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace tribool {

template<class T, class Policies1, class Policies2> inline
logic::tribool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y.lower()) return true;
  if (x.lower() >= y.upper()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator<(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y) return true;
  if (x.lower() >= y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() <= y.lower()) return true;
  if (x.lower() > y.upper()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator<=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() <= y) return true;
  if (x.lower() > y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() > y.upper()) return true;
  if (x.upper() <= y.lower()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator>(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() > y) return true;
  if (x.upper() <= y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() >= y.upper()) return true;
  if (x.upper() < y.lower()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator>=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() >= y) return true;
  if (x.upper() < y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() == y.lower() && x.lower() == y.upper()) return true;
  if (x.upper() < y.lower() || x.lower() > y.upper()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator==(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() == y && x.lower() == y) return true;
  if (x.upper() < y || x.lower() > y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y.lower() || x.lower() > y.upper()) return true;
  if (x.upper() == y.lower() && x.lower() == y.upper()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator!=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y || x.lower() > y) return true;
  if (x.upper() == y && x.lower() == y) return false;
  return logic::indeterminate;
}

} // namespace tribool
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_INTERVAL_COMPARE_TRIBOOL_HPP

/* tribool.hpp
O0UtkF8NKjEzXdKj/KNkIU6XQOHs6vK2kLOMunxvVOX3lpE7/fYF0NmoOkQQGFEnDIqZl4Wo0Z9Zo+eHsmnOqndf0ByVs/N3Z4hUiikIKjbBvxKH2K707FO1tXRi3mj75Y8ZlsGa1e2CKZnCbL7z1gvyX8tSj0cafge9GJhxieRGWB74DSPPImHWuhxEWTZ0JRp+OTeQpR9CwWy9tRTFZ3IWFIjYE+94W44yj3Lj6nHiPhfIPgQ1Aq53T1OxY0vqviNXdxFGd3cSZ2wSjtIOvTLn1wkbr+2NsNKvw7bVCBsPzTZQ0rMRO8Vjp2ait43eYFls+g5OAJd2pVi1eHe5Z11dnE/RfiijNfc6qXomE1zLlQ8eE50PIHh5/tMj3N0WkT7uDNQvm8s91fTk2s02M1+OWi1zJBxF6NZ9PBZ1clogd8HzPbIwu8B+J8Qt6A2SGthcLMtZeaqXaOogtNnVg/Ofz5gXbG5CkdWzu9FYg9X1JH17gEF0vLuD8X63SUKjqWl6L7AGhNkrPBhKDb8snV9OG+hxuqjcxdvdmzucd7NBI7jVYLSqXRzX9Grc0ZPkdF/o//fCsJRjf8o6yev6uXSom0s7c4l4iENqJEejkzWSM6BZ/wuYKrIL4xUqE3e2uYJjyYxl/0zcIuHdwEU+LcMs83k7YNhOCI+TM3Y1DBRnjYmkTIq+cndTBhTTA7IpVetq1zXZ48/nYPZbe10q/6nX8/HkYZOPQy0X2IBKamsxuqN0vyMAUwBLec1UdEAlRqMR6Xg3/F/l6oh7+Z6yw2r5x2Uu1MB38q5kwyKKKE9Qyyk+jsDJfRmT5AicBmNHOfghKctiDMlqxBvtA4oLUwtQZHpiaYeUsH1Rnas5FAwa7GThaCk5oJ1I7Cm8R5L5ZI2InMaz04PcsVRoJhclvufzOvu+tfXToLK3htsH00wvhxd31sMU7K61xGKS2YaVbYRy82iht7Fp78ubeaNgyygr58JczlfUxmVTiU3s5E7GUs5SbxHrQOeI4iLBfjgz5uuvUXRAoLVM7TQbTnEzNvb7ejBmk8aR1KXlep4z9Ilpu4kS1UgpYyPN4ES6OCVppLXUJvPiCFNS8GfMmvccSk6ioSSTEcupofODlx8VM0WMaKH4x35KZ8/4e8rMqYzNFJQODpkjYmxGe3jo3NbQofj2WCAxPjOYDPbJiIwHD0crnLcZ/KSJ2r7YQgoFT62xeIDPZxi1fC83Xzd2uFTePqasqGiaKXm1PwfXoxCBultzJ37mJ7RacqUpa+10CJgel8HjGCmhivFoc7JWseQkiUxzpcCOByE8ag7MO/5qikr+zW4noSZwyeGm1LuGYnPPzlzvCmtZIankUNM1dysLXm4yeO3lj+r+cyIiafDqhhiUjqG0m7R7EW/XD8Y5bwNOhQNe104nNbpO70ctkRt2DzW4zits2fMpqQxMrXKoQt9lL2hsZg8HOZfKTm41FPrhJTk6yu3Wbu+qaI8EcKS3v5FaVSc3OMonoHidGkveSkitDEykXaem5LjtUhWoTnstKYa2nZNTIaf6j97XGfNHVDPjREk79TwXu0msBBRMqfO8as0xYDZ2P65aAJcMc53uKHj0Vv137vh7GxUPLnm5/rxdYHJzWWB+bWO9sfO4W0ctnUkPBHrfWDm60/epSsq/s2etDnQYrG+D2HYwBhp5lhQ2gVqy8eByjm9jRWdbc2H2+830RcYmmljf9Oy7H+VashyvLvEypUMpdtEV+wSIntPpOQQ0l3X0e4iaoQ/1qFwciVWufy3mMTvZ+cVnB3w+dHChsbdE/2kYCVcNBLAm8iVJvhqPvFX/N0+6+y9sx0wJT+A9ALscWIgdzWwnpwuQ7rB0Xz8sRiE3dfQ1FgBDNx5obp2W8r9jgjSH5m49UTsq/sFR3RM6OS8ECkau77yGsPyGsSCJuLvqUdC8L0PxkJQKyfHLa59Kk5xWJ6DTvp3fiBuo5FybBCh0wawDXl7hoZPZtZuiDXyUtec4eCxijDsgNsSdROQesfV+BRhU0MXhOaR6EOQI0PjdngCwEqwZaUc4hdCP5rMXhmcQ1gvDNQo030/BKbqZnKPfQ73sm5ouwAXx8hu7s6u78Ka5uIngeEpqL69QWTWB3ZQQIjshlNsj5tBW+97A0kjlrW2vsCEVrKP/UK1J7UUTftAUfLIIGYYaVquxxh3CsS/qEV7a/GpamnFki5ozZmz1e+KLy59fOoW+zsQiYDF1nU9y1kp7o8Tyqq+KaaZzEdBU5Q1eC/GRa5YpI+ubTe9pUO6gYKHwoybidSUnowuBBvvc8xB0cDdlTSjv1yxtOxELQOqvLGkU7Q2FAX36PNs3C7wurwpwZuMQsk+TdsfIjccfsS1Elh+bVZ69dHy49XCyvKt8mpH7Lx+WM8rXq9KHLTVYLCvSF2VfXPSfah+WBwphd5LynxlLYh8Lx369GrHfc79drPO6YfclPa26HzUm7tB4KVoeTybFltYBcSRJzfqp5Ln44XItByuoc+AaD1MfOUs+xxUXfFuDKq9VTLWD5N1R+g1LdtuOUhWWeGj5yfw/YyD5po4vUhQh7lEnpLucOCBNv6+aMNKxo+KHCxVNBKbn26SqwpWUSxJif59wY3MXePchAfAffcA80qjMzKkv9Bvfz+IupPSr795u36YdNVIFjUI0aavvPrQ3Wc2O5+MxLhEHOBt7RrD1/Lqh7jfCUKPxzuJRAwf1nK0KvTVsSGuwwfkisevs5ybX2vatA77WGS1d6E0xmgnUExgWjYV3Iq0dSImAiHVXT2RgyoffTj003YH3s5wMV2zXEySkajhFXFPntd+EmJxC2jLz5FGhY5BsI20XK/OD969bAlZwfQ2iRkAlr53n59zsm7M9Ul33HmNrqdwuSQkJW3Ltu8LLn2Z8jNvWVe5WYnn9GXrG8k8j5T1QQFRSlNvlcBl4+U2Dj7aqN46uxYatD5G2YbxTuHd2VSB3wiutndpgHzBke89WamSDyr98Vsh7cpPfvqXLe3WdIm5RiX18ZX5vk31F1QW4Nnx/Piy/OMu+XhEnfn8wk2CJk2K9tN3Nu1VQuzm325wbNSnVLGonoIQIGalxDlfzXwu54GG4TS2NIXyJg31rXODFD2ajRUsl72S/bscEadezyGC/z7YO6+etPHe8K7C6DyA0K4EB+krx1wy/QXqSzCc0GQ1s5ZTv3v39znt3HzIeI6+O6Xi/1KZy5jSyJs1M3ILPkCfVQ9dU5jCq8lTX/lOS2t2YEs8iwXNbbmAqt8RT4qiE+LetSmvo6IdT35ACbJ0bvkzZ7ibTN2Hh0V2l6qads+DW8t/Z8rWvE+nx7LR4Q6mAoZMJ+kJS2ZROHfdZPsnzMqeyLFWxgXN1k+sn7hMQdrutLYQPmbDvWvWLBXGeH89ifOM/0Wep5dVVZvOXN17gqd5dqencbA3dEcqrdV3opVRo48SO7ZHqX7biGaphH8nZMFAzidB8ZqlwhRPLuJ/s7JPxX902RQeMLVWIFJIF2tQ0b0e+xw9RNYN/IxqXugocRG44COf+t1x03cnoq7K/zFS1NiajeO/65hWwoDmupSGoTOoj2r1S1bpej7i6pbpJGCYGQZSVCA6DeJhF9bMjJZ504QQg84Bj/JWn8KoyxolbltYDpqvgvWr1RDXOQZmg+Hta4rjOg27/4bZGIn/n0z24o7mkx9gSbBZGVGUZgyrzsGaLr+cECYGJeQ2Ew5UdqMeMTQ3jHLDDvYaYMAm6lXgkLzpfuHnmlZ7NYS6o5UNrkFxTMKJVn5uh+NzTSRW/0nOKG07Tq+CXnKN/U5NMEtIauENgV+ZtvU1YLEdJqyz21VNrl2s3AqL8Ispy5dsXUK1RNhWZQxre4wsYPmaEAzmq2c4zBtT7HCN4t6vIbEmtVOvwjxF8FVdT8H4Zf3grDiyza5wN2BneiLV0+CCDh9jOi47LA1ElSDKkwHVWoW62b7bT3zvZ9H6z3uTY5uUyZND+UFRgcTFTAs0q+67loZc+iyQzcYA2LHrenvhtmucZZOLZLGeWPDhj6EKeY6iT5s7uXVL16IyqwuoGegVv8SmceXBDUUSh3k7o8RMhNzoaIPTMHF5CuyDtTPXinl4qem2PrUq3paxFn5XqOrQ5X2gW5XMn4tQMNQmrNGBpVxJI9KW9zTKt5MqnO4EFcn8oeYdDt7OlsBUVp0CNx8xGI26bUwi07edt+k5qdvo+Nraa/8yc2iwCqIzoxIfobBjqGC7YtEaw5gSPsz86gmzDjeehcd/e/8dICM3dfteaZIsdH7JF7/S5OsugxOQC2Cr7G70LUwj4xmR2Z7w4IxZ46XSUnNiqHh9SboiPqzu8C7Oa+dLxXxxLqoJy0KvQI8yZ9PWcN1O1SZvrwy1hFQH928a0LMfbxuDq7FtEmryHIO4vyGox69t7R9pl+ugq5ltHWC3ro9aO/yVGziEzFaZFxcElQ8/KwzN+j8zeeObQ6rhX9sBquVf2yKpAz8z/T+SqcNsKY6QyLEplsw+9Nmwd/xD202XnVQzcUYNe6HMIxU93VG2zl/b46ud1nQ9aaDop3Do7sjh3Sg0obx3S++jhQyi4cjcOQmTy8OGzB6qrAQCsD0IRyzQTFk6eNVSNSw/HW8bw6tai/fT+Lqw96YoEXpSwqKshxOUhovjZ81GJzH51mQ4kDAKzmXVoPDp3WdyipJyRU0kLawdpPw7+a9E7dKMRBCMHfLqhuZ/WPM1O1TseBvVSV0mzoSkVV+JUILBYSOaaYWFzj2K2Y7/WoSgpDImw90yZu+IiA/WPuaee49J+Mg77aomwocVQQ5afioa/mwxZxbpXHsjBiL4p73RNA+x1mH0FdoJiNfdVlSAMVyG/5CmeiGVufD48AIra+OvGQnNN+cgHddbkUBvruXH/pZNPjs2VF01mrxaZ7ofmZX2o24M7q3n+ukFTG8I/vhfBJSJsJRrGm18K/TgDXu+MTDMygyOuwqjkDpHJPts6qvdJ2ulQc8AhVypCd6POosqGJK/mE8zp3dGRElMDGhhR2/o6A5Zbu/4YvZfT4ESmarlDP2rDHBnDhk4cNqkqmyUprxPX57GmdA2VL2CfT9JK1Bf4e9S3a90hWjOCJ1UV2MM2VfU2HuaBJAL+mrCyZey6s+Snfl8zjHA7e25AyOaYt6cYwjK7qgaww7AHiMPdIP2hvDsZUOh8NHPZmrvAoldiEjPCicB3HEavRsUSU0ihyehmJfyBFVePc/Lt2i9iDaYn1QzHuXEWvYXhVMlPttzZ3isKqMhZf6ho5uiHkw/YxaLhTP2pkoVvVN0L9C/Fxk+j91WLCmxdhfWKfOZlF7cq5fUHGKfi3okoaWg7l/Yz90vdfVhq4FugyQsYoMXBzsWOqv2ZWicfSin17/anGypd4R3/LkOnCM+Kp2kraSc1WyBo3fJaYGBe3+8bMP5ji3OQUgE50rv4ghGbZQSkmIKS0PFduY8Pl3plyWHbkM5R0pFXk8MDiMWOtBN63w9V+SHhCT66BGM2ojXI/CRyCSPxzqWy38itCO5LdoMF9wl44ya3O5M6K6tbqwzOSGt6x1OPOfSCf0+haoNPovKtZaDgAOeQk1pRh7ppb3aFBCsChw+X9nlAs3Q/WH9FWdERSCRIVhAKEbxfdHsaTOKVApq8A4uF6fU/6v6frn+gQV7yrcnRrUVB9NRJ4oK6b8SLya3Hj+AoWOZfdnyBQaJtlwH0PXoGEkx0/5RdgghHPoY4oMwNKp1Dm4PtqP+J0p7HvQwZYxeDmUZLCZ+VnCnjkxzNeFyRt6YYyclmDma2hqIdhmoOUJvr/C7en02QQLKWk4+bYL0Q7VezucMDBccQAMhBC7aRTbo1pIoIPiIVBBKIHoGwra7ze4f9GGb6xGornV68si0RyicElq7CSduWlhZU1Sq9cU2lEJsDSXlqV6pxB0ar9pT9d3wbWQVQvIbRkjkvMtPODfjh42R1LnxsANnk0yQcWRivjI31kXLWv3v1Lel0gJKUrwKIsnvlcPi+Q1sISXlowo+Q20J8sEhO2l86ugA9tOe3s2/Y3cHuxO9GxpuH3ZJnewn/QS6f5fs8eslc+Pg6lUt+5Sen9H7JV8Nm+VovTiqHgeDcQtA+zpXa2DI+AIF1Xid3NoF7VOUJczvSLz+g/krESX71kiZuVttpWTnlWY8ZE3eVJ9eA6mnVumXY4ze8ZQA8mt28Wii/IUsXE4F0fVRWOgG3Vfhxk9aFHzPlImFUoiOeX9NIw7niHGt/3OgkgLFapbj/tL/YHR0rGmeocQfQ1JLa7eZysRvLPJaBWTmeRdM5SCC4oYqW2+KL/ow2mqvnjDIlPLuThM1p2a20/gBO8QVsXUZpduQ+3XdUHP4kKmCy9j3y4O0bQeBKZT14mmPniDFXwEJrsSPEjSpFHMGch/Gcyy9SFOrq8MpPaqFcWqvrdQIiJJLfydfi7ucZ1a6UDBDRFGi7UmuX9XDF82VxEILAXBZP+OR3PKkyMvZT3/KT8xv+0BcbPRuWJLImEjv/wxYYFvIcSYqmaUIyVFmwPYYfV9syr1J7F5GPvaRcu3FA91NNJYWCUTN6QYGKS9ioUqDPVBjkPVK9JJQQJnCTGv5KcpU6ThqNe7O+gR6IRChneNYlddFFeIu2oEprFxQrKhhoXtOBO0gR4U42ZjSgnqc1EtZgo2teVDbK+xMN7QdH9Lyfra7dzpSPg6vfh+OLCx9XfJKJxb1UHhrjJ0xNW4ps8LWVWh6OE+8f9igMw2xtDBPbtkBsbZvVjKc3FPFp/JO1MIzzu8ONacQ3gt+EGKXe+YNgDIm+wzryPJSev6UAAiz907T1iasgPEzBE8UYZGr/Bhi5qlucIypxcJLVcteCVbJCG4MXt0Jx8unz7BIysm8Yck4MkprCzVQWGvn1aMRsveUTTtgvEMrBcjqm+2ZE3ejpLWaLSV2S2BKar7qQXqSdmt7kmUDlaiYgcyMG/8ha1NwaEgMvntV7N4sof5iam0Z0wzRA06j982SUe/pzX/wxSTg4NWae/3NTglp7FVnB+LNOfZKDnwG2FFk7oI6abK415MSzBaf51CyazgbaAdSocHDn/t0cNd/Wqo6bFRbi6ZjV3Ls/1+hiek3LhJ5a/AKefleL1ByEI50ku48niudQT+KDEOlBQjPhMYSBIg1HYR5numdKcIjRXZRqBp1+29d+3ea4GQCf5sbTWS3MLSdej5tGn4PxoEyHn//VFYCqMmPrZDfmi/Nqq0M/qs3O27UZNFJYXxpBRF6f6jDUasZ9VZJceiarg753lbzXO44HqxPb2CwgUHfCVvY2ly5FB4dmozvpr9FNL7vwtKqFO5rPBFpr3hIWcJdeIAWzzpgLH0H/Ld+aooELf4OTafGT3fx5HDQylnwjmuCJF5xgEJ0FwI6dMHEJP5V2abxtAE1ikKLzgE60UEhHOIlp7DXM4ghihAEHF4hZFiy2Hr+wUkCowGom9v3ibDIRSzju49YfGVXDPBS8tD26Y0GYej+Bye4T/oAhj7j0qWAV8IKuiCZHlXPrZd6XNPaWroLzSyO2HX37zelvCNW29r6HwctmaID6e4f2eTOBrnhFwIIhLbaIYZKZIwLOLDpbvZ8cVaYjJgD56wf5XigVaW/rIF1BU0NO
*/