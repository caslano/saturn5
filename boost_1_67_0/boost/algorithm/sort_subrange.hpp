/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

 Revision history:
   28 Sep 2015 mtc First version
   
*/

/// \file sort_subrange.hpp
/// \brief Sort a subrange
/// \author Marshall Clow
///
/// Suggested by Sean Parent in his CppCon 2015 keynote

#ifndef BOOST_ALGORITHM_SORT_SUBRANGE_HPP
#define BOOST_ALGORITHM_SORT_SUBRANGE_HPP

#include <functional>       // For std::less
#include <iterator>         // For std::iterator_traits
#include <algorithm>        // For nth_element and partial_sort

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn sort_subrange ( T const& val, 
///               Iterator first,     Iterator last, 
///               Iterator sub_first, Iterator sub_last, 
///               Pred p )
/// \brief Sort the subrange [sub_first, sub_last) that is inside
///     the range [first, last) as if you had sorted the entire range.
/// 
/// \param first       The start of the larger range
/// \param last        The end of the larger range
/// \param sub_first   The start of the sub range
/// \param sub_last    The end of the sub range
/// \param p           A predicate to use to compare the values.
///                        p ( a, b ) returns a boolean.
///
  template<typename Iterator, typename Pred> 
  void sort_subrange (
  	Iterator first,     Iterator last, 
  	Iterator sub_first, Iterator sub_last,
  	Pred p)
  {
  	if (sub_first == sub_last) return; // the empty sub-range is already sorted.
  	
  	if (sub_first != first) { // sub-range is at the start, don't need to partition
  		(void) std::nth_element(first, sub_first, last, p);
  		++sub_first;
  		}
  	std::partial_sort(sub_first, sub_last, last, p);
  }



  template<typename Iterator> 
  void sort_subrange (Iterator first, Iterator last, Iterator sub_first, Iterator sub_last)
  {
  	typedef typename std::iterator_traits<Iterator>::value_type value_type;
  	return sort_subrange(first, last, sub_first, sub_last, std::less<value_type>());
  }

/// range versions?


/// \fn partition_subrange ( T const& val, 
///               Iterator first,     Iterator last, 
///               Iterator sub_first, Iterator sub_last, 
///               Pred p )
/// \brief Gather the elements of the subrange [sub_first, sub_last) that is 
///     inside the range [first, last) as if you had sorted the entire range.
/// 
/// \param first       The start of the larger range
/// \param last        The end of the larger range
/// \param sub_first   The start of the sub range
/// \param sub_last    The end of the sub range
/// \param p           A predicate to use to compare the values.
///                        p ( a, b ) returns a boolean.
///
  template<typename Iterator, typename Pred> 
  void partition_subrange (
  	Iterator first,     Iterator last, 
  	Iterator sub_first, Iterator sub_last,
  	Pred p)
  {
  	if (sub_first != first) {
  		(void) std::nth_element(first, sub_first, last, p);
  		++sub_first;
  		}
  	
  	if (sub_last != last)
  		(void) std::nth_element(sub_first, sub_last, last, p);
  }

  template<typename Iterator> 
  void partition_subrange (Iterator first, Iterator last, Iterator sub_first, Iterator sub_last)
  {
  	typedef typename std::iterator_traits<Iterator>::value_type value_type;
  	return partition_subrange(first, last, sub_first, sub_last, std::less<value_type>());
  }

}}

#endif // BOOST_ALGORITHM_SORT_SUBRANGE_HPP

/* sort_subrange.hpp
sW22bqVGbgx+1fT/wNhWUrOjhofYZkpp8JK62+042QVH8CCMtLWl34iYSxlblTmpvi75Stk81UeT4EINkWDuKdO2s14JJKUfHWXMxf6d5Kqzf1Bw+kqaCfLu1pMqXIH3IGxVaenwEuaHW19VyssKlIBgSr9J8UnoilRisVkXuw/nnLnG13m8jZfNLyfK3e31OPgdidM4o3d6EBv1HpwS23vIvKSwezJpreLg5c5Wk/krCIxLES5NkPm7yeGM4vKvTe0p8YOWncI+MWo33L8z+uzuvT+DZ7nPYYD2VghJDuRVbnOebfv1xlEDE8ZmGRA6bTJJVjUV+v45WEr8nnbh2evlsjHyosdgPE/7VqEPzooWmY/yClfHLEvR7Ve9YTgOlFaL1Dcfbhkmt588OB5BaKSw1/8XxPi/ecDB+A8GMYB+n7sDAAH+ZYJ+KjgAECgADAgU+lcQAwD8w7NhjS9rswpKSEfPoBOZWdk+dvKH6a1vn18/k+PxY6IiLnteI5y1fGXv/6/q3XZ13onhrzGna2tCdq3A6F9zMJdYmKGPL0MZcjhZqc5PP+i1UmeoXYRdt36wmmZfu0WOb3XqJjGI1MZolaRoOeumZacIBkydmhgcp9IGzum/BS+LFtvb27OtGPkwZLm9LfZvFXF4uJ6AUwEnL/yA6bapgAC9Tmd8Dp5IATOtvU4B2jWOyNe4IpmMZRfWFbWixLAoIO13fOt65lESrykgfC4/dHfPESZwvIWFOISm58UxZAJ+/WiNDUFkaExw0P2Jf2WYIH2jeAjUPWH2hetNpx1WbPliHwjjQJBf3rxj1KylvlfSZhe//CF7nzkzHc+QzVpGwWXKRmlpaUCQ1HX9/asHUva19a/s59nHweGfjscFj/NOYDsJNW894e75fmlQME4aJR8sGO9wHOqUZnFsGy4I826bvbRH32ZnmmeDZVfwSsAzZp9KbS7kGYSrxt4b0VTENXyh+urCqIwsKCggIIfQ0nb+koOhGj6/Zf/6r1pNSJY6zrY+yeuGH6zFK4S2UONZWIeZjJWRfhsQEx7bGLBzLvlkeYex51KAIxxNObZVB9R0YFawl+3+WqJOOGkR/LiiNK/wvEzsPPPXjwb+3wlO0LH+Q8CJ/x9zmc0U/VUAgENL7b0FUF3JurC9gSBBg7u7w8Y9uLt7cIfgDsGDO8Hd3V2CE9xdAsGDO0Hyh8g5M3PnnHP/r766M1/V3dZvd++9WECtrtVrv08//z+0GQxPyS3gT6sw/+4SJBIhvzwyCuOzJ20GMbOAnU/WuoJi9B/zjS/Enu7mIHPkpv98oeOU47ed9IWJiHuh5Zjl+6kMFh3X9FXnnh8EghQGg9urrq6uvjDoz1gM1KWm78uryO0wiOSa1vhbxZcDoeLonMdtkJwJfUlh0i6wu07JVBZp5zS1pvL0XGKprdA+l5WbTVa2isfXhzrOzjHvqZnLrOqe6BVxuXp3BuYebn0FQDAmm8OE+yuBSRxjjLCA93VRgeQ5hxkn+37SQwVMtvRGiCaG4kQyonHg6ZNzSA4a6eT/vkBTh7567auE7EtoFFVhAkXKz070jyZiUOrW8a62j15dDEQtI7DUq5AH/2xCM8ztoiBM0YyAyP/zEAdmdXmB/sj7xUedq+0P3vY3QaDXDaySdxk9KtSo/glzWiyKgs9pyxvN8wORNLVfz0jD6l3732reh/GeZFB7RwetIm/ZnD33IllL9Bb4fYHCArtQkPn+Aj9RbprJON0PbNxLT1BuJNkNFoH/NiiuflDObbJgFk9hiZL/s0SGmqukZR5kGZXnq8TZiiQCKDKWkm0x0Ofh5rcxgGBpa53XqR6sRx0JfaQsTa5dtidLzY+aGHGzWzvP+7utP99a6keEDZeHgQDCQmarREWMVUUAb0SELdRycpiocwAviYnqSi1rqdRqQNXmQKOrx4v0h58baEGLDAnkhTKQhr+mfN7pDm0Lnt8Bb3/p/7EtgN13SjeI40vXa52uVH6ziu7UB/0J01p7Ynvc7NN1ya6M6aUH4iTsxEP0SGgdlMf8tT2cgeV+01YXhZOCS9avALEnIwYqZCHj+EsCXyoEOYMnM4YSXmY/G7Sz8QlPbsWSgUB7IEejYgubzyGp1xIW6gXjSFfaQiuCGfXV/HhFll96XGNyDWlaEizORV7PTBLNwcCrnTw6stIPJsaCkHwkG2pJDAeFr3Y2UyWRyXDjYXHuY4P1Dburs97kPk4F5/hRK0G2rhaIQcsesiezA+teuo/sO/y+a08ZKksJkAOA+q/BX8pCMDD8rb4iAQOA/UEuDgCB+HnWAAoC+uwpFe+3SoxnSISM4Mgo/EABeT1bpnVinycY4vSPNET8MQf1qp3CcvyE8AjtB20UrcnvoUyX0zniqWJlWmuPh9IBuQ0jPmpITUViRnKv+tyw7Ih+6edt8u10/zRMS7Nd8YmEvh9hE+W3O8XCtLXpz6cZUP8FsB9PYcf9Ci8/lowQjMZ2i865Q2//dx3vplM2a13Pt9rrFy/ac9dIc8YyaC/r5/IuyW5p8Txubcrq25iY0ysfA5OSZdW8BaVGyEv5srJc0xmTmoS0QMGPi+pghk/DRgaJPr6g95Qu1DEJM7aWRwf4uO9bKVFnjWNlacO/mYHedYBoOiIPJxPXVyysrPucvuEyaZhAyhkKo/Ob5n21myjRD0OIy8hZWNNVpwSRsQnEjeQCLEUGG/z45DSir2X8LdQYS4gHMZZNIL31/jzkJ6NkFiJhch52wB29QNKPFRIQZPPo518+/l2HAX5a1zZ342HT8kNhHx9XwLCr7ZJ90518mJczTOLZp/od+6sShlaBm8Q51u0ZY/S3ushY28uLpV2nMBsGWkspSqmSUA/2lQul5jKk/l5N85azLORIXXxaB6wWWD6VkdNkj2iPxRBdfHIpN5pfCrGhHgRs1m32q7mpz0nXevh81PFQb2OON/Dfl0ZC339wPkX4KBfGBEZTYNSID3YswDAMW52W8NEDoQ2qmwE46KTpc8J7YfsqTV/OuW5sBEeNXC0O99D+XBTt+SwppLvW/YwLLHaqpWglG4sOGMQONuIB3Ijqm86mvh53MHttmhvDOFCR7Gb1kyfIQdihZj1G7jlWSIgUdE1JTnEU1LSu91l2LGjp/u5+LigL+tp9Ye77Es5mziJAuPD1VwC17cdoGLRXw33bXSsl/yIuMgnywhYd0Qp8lHa83/vXlQcanenHBHpzb0n0OnkIVOIWkKJigq5c51csLEIYShEHEPmhiaZNgaGJZsgiukqWZXdYQhPvZrCpvfqimY0uRQbXqgozSgUvhtyL/liWkavt7MVfk9WmGWTkqy4nT37XX9iZzxtQloYntUHMWDLGzYoMr/qZ12MMWhAb2/DXyQ+ziDLM/NX6C9a/WabEv+QauF98GwPBoKCegYM8/+c49yPHGF05bhLt2yRJyTZ2AplNvoZVQM+uuoqIGMik/23Y+8Mp2f10rDhTU68YgqhF3VE+EivZWLexFGZxqXru2LeHWeJ+1B68Iwf51IflI7eU58TIJus1J+rFiMaxPN8e+Qa7TIGv2wxlF6TSZamYgfz5xeYk6yjRx4Rx9c9vvalhhyiGNXquO1CDjOJUzAyOI3iT3cErZYdu1YzVBWbJ225KuWiy8iLb2b+YHaB18tFv6SUZwailX29UHlQHJvDefNorqNR8dt8RH2gUR6vvvhbSXT2IpXb3KTI/vdMS+exRBTNBri742Isafoji1+YZXAu/3CW5i0GrnbOcjryrfZOWgSzJUXBKGIRRw9NbK09pLCIuBSf6udFfiMggA9G25NlsGUL+QPAs1qNfxepXgOgNI0hp2zNKaSR5znx52mgkEje4Xobb/LvtocWXCwqjzVIe50aHBJpjoCwyHGZoU0U3Ud3ohGG0lf7gRPDFxTeGb+McMWwY/KXex0goCsiLXoVegEAIV9rVm03HRc+q3KRnX4Jwye4KZlMNlpwRPyRGE49bU/qNiM4tP21/sj+pIsKyLRemaOGUuSbZGwnD8xP6+Ytsvh3yQ74bYlcfKwbR09pt3Uy3RLdEXx4rLLxD4Qd/H0tcJmkVQ9EGbwYkTuyQV+fyl9fAqyhWh6pti08p9Gag+04e0jTbGT2BOPrDdSGkJCNCuYVvB0lLswFCpM+Zk8NGyUxwhUFeQOEQIvYHNgeGbCl9Ovv87Td/A7jDJZmoPfKaBJvYPHSgbA2vqjlZRHYyK4MwI542J14U4a0Tc3DlzLDf2zx15gxvjX7qdxmewmASx8uRx5tkLEtlcv1M6zVohORKWRYzwqKsTYpBEuoalhc5NhSglqAeqP9hp62vVJCmq0ZozeP5JfIyjZeXFlVP9TCaLM8Riz6mMRyy5wn5tOzrqtvb1yVIQwzq3NeNM2+NEpmlr99nyPN09e9sdZVK0nQanq9+UiFMeDXBtgbqKXQNg5/xDrqKpgY8dsw9XC1Q3e/n5v9a6wXT3wqc+jcQA+/3BFdwcDBIaMh/nkf9hBiQnygGom8zPeW4qprO7ySDgL6df0wsmsK3ESZn/Q8cQ7DLO/dNdj+WBElyaP2+Thvjeb06oxIzcoUY51jEDVZinQ+4D0lDRjX6vdExqyNtoeZDKpMyeSTHZHD0wrupQ8e45UNG9QkLlgVUTmbMxfwbXB/VMdq8lzll42W8ySyyIRZ6Nb+cHoyhyhiPzkmZLBwrb9eWVNkwY09rCPPIs/em3Pad0Dyqp79tTJVqf+9U8Jm8+dv7TLPducEamNV5Rgjcs3DUOzzoQfu3knb9S6Xae5xMPkO2f3sP6ZiJvxNZKGRbLr6DQKt2x+FxBlXqo9SckKI7Kv1n8jpueZzetPLEsdrVlBFjnhJXyo+Zk5T7bx9dKo4zZnaHL3p0ud7tjBVfODXrd5yWrZ8HP+R6ELfqiniop5EfsxxEI+nXCC8rpxJ4Myk/5Ao1VPmZttf39SOFpB8E+xCAvpR45UkJl0sIEBCTpJSUBtHRCmJCUERQbJGYjboTnqNFTmHVOZwJqHDgs2jmPOuwv8Mwgg55ARWhwkQSAOBfw+FE0SR8H0AyjliqaIvNEt3tb8Q72zuZjkMMPWfCaiEQ3e3CM+4ZStRYxsNzcEfCf0SW35jDw20+/hWgQJB/0pB+NQK1tvn+gfLNenucj09WvoawEk7xhxqowvJAvPhSdmmJYvbuZ+Bl77N0xi+h9BP1IwDmeqlmnIQE26pYaZDsOrtKRQUg8BCORnNEfB/e0gruJxYwyrxVxZ3IYBfLkfxU6BemxifJ1HNO607Cn09asqfiFGFUYfh2Ob0U5jOj5UNp3MNzH6EGBQJH2qt+n7dAVwcv5KNgpNkCsXha8zL2fquGLdx7wWlCtIZEq3ezymyCRvkzU42m3JAPETBKiJ3mwS+iZkXec+0pfkKxcqMgT6h6B1S1otgqCnMd7HNawgGXwto4pex1nQw8yW+LIWhAjZMPsQ8ocFHU+YCY4x6XfxxeZcZMkBk5nohXg9IepfBSbpWYbqB2UQHFFzTwIjF9cN8qWGJJTmKSQkFYfx8jdPdVSGwRo2s+tD3qC4lwBxT/Eo4s1KkuTBWDuJAQFyHjwdYAzD5F3ZryjlmqRQlMaeWONyEJvdnDCwoRrZDsgfPnTiqDCY4f08kYcUktqLiG4bmzP4doNCSi19LKchagtiZeSYl1Wyzx9GDmjmpS0M+v0R4sL9WnTlsR7CrBnxjMMSLAHysdPUptA/fkvQZObYy3F2pnw3NxoX1WYTFXNWvYGlaptYtHDOiA1anFo9EaJPDkzRBLXZJXi76xxHLcvXnlhfgW0MctEtBSSWbEb2tZZlCwmu2v4lBSkGKyejgzwnRt4CrOwFGJRj6ZWhQzJzeqnlYJi4Pe636rLMbrMENTdaFv1N7rLXdb3FcJDVTfaGDtBzmt6/aGkIkhf7zTljsaPMbqRdaT4EbLCJNzfk6/FEKlFG3OPfLtB4+4w9B3F1MpJX2rZpUXDrvty67KKxyYKzS9Uzx9i+p3fXAUVTKpsR+y36V55Cw2swfnKOyotXC68oqvMTLM+69EFhjZ/16yyD+M6N9G7SfhxROyIPDLd/Ec8nfGtCdkgVHeFhIVjV9Zzy7227x4YhIZnYiYhEzJJ0ZAP7q6pmsdyKygaPAnxguJ7+BCYqKKqXAi5maimQpzaq4qB9WUe4XDlaYbbb0kbmOXD2wNDHcKHNW4jAJzfMmIcf1n7lFmCvmTbisKBr9W9njvUeHDdfthwZNC7VUda2TuKW7qSBsyXSSvwGviX105zu9S/MeYx6BZz4xOyXdt7Lg3dVbRuXv4oJ+8FlLnUic5//Ej4050rVOhnVjGC3mVi8/Quhn2+xrgbFUZsECbD1z5kmU2hp/1TRu8lQ5U32WpLafaBnupCHziFnY3JtDxXiwagiZd0HwFGPoc309p8U2Z5+tWHed2a/IRK0nt1aX03zqCK5FMg6SppKWy1NLxQDNuBkEAA3ZkTsRVjT9oTLCWl1FQaziQ6QdrMVvTqFkkJBUnRN4Vzet7Th8gduzcoAS9GDSN+mRa1C0UcVaKkfYmxCemWaWisuEaOV0Kr6GMWN9H7FxHin659N0r+as06UNl7RhNzVtmMKlvu1Kh24euc/sW84PJpvlGejd9ogaYfbIjuLJpVv4LVNvsiG4/OLtN+fGlgBvuKCN+DqiXpqQzU/M+sBxjz2yuCPgt1lDYlfQhM0nsIfRST3MdyDZNIQoigZaSXEDGzCAurwKCNcrX01OubaQUxuSKBw25BVAua0F0UJ7kNxrl3WCL5NyJPDYavL360fmpibpNauUfcw6xUhaL74givY3d1h9TlOCuUdvRHizvw7WmVGaNsLemUZUi1VhQtWgvy6bdUexTDmk2W6rg8GLrrgjLLtYqql4sfTawC5ITf5SZiCbAn33AhPxAgMJogDNSiBV0ljo7kcURlgNYW5MNQHhG5pcezzmbVzlwFdxPhqA5G1D1OtesgAz/SNEORFR0enWm2/Mo7ouRB+1VC041swW3wDAilqagCDPOjphWQ/nh6E+tBVGv79kyvRkKsymWguaBytv6+UhDco78OKJkVJdl6kkxImkcxfC2fcQ5zpN3oKTRPpjA9WMt2fglraumqLcEiHFgGduB395HJZXMQR7etms12gpXBBzoidU6PBbi0K4K6B0PpmNhBjjlH0FcjIcXRAr2rSFZf7KBR1opCxX8cCy1GOoEhgDy3uLKbuu24Ajp4jVtzr6N28Wy/1eA7ycv2mOdO22LrwDBZjS/Kg9fC5JwJiZqFEmGkHm9xIGLopCmSAxVLh/yRInsJyrhBpTAGFbIKJ9qm9tcRNE43MRBlxq2PlOhgyWHujnuH+uLw/ylTALT32rRfpCnC4q/HTa/DZqgYE8TbZZvoyYYGCgIFBQkyG+QBHBECCR+ZBRUdEIi5QlIRiWDmNi4SXlFPVt7n6o/EF5rI/dr/wZIgEXX1Ckxu0wbpShHZWSJySbGZopGbk5FlLJRWTH/OKN82qstj61OhlgWPxC8IoNJ3YD1rr5t98Nyr/kn3OJUPoXnzb5tTCl5+sV317dRh20q+c5a5vHK3hyrJkKOEdZbHkd2xTtVyojwPHy2fZwqNfij918BBXhJ5Ytle1Sp9G1O3lMVqUNV6qNpdfZLSxl3sSYXRqq01tHi+cniaaMk0pM8Wq3sRSWm0ElUF4OSJBXxyy1T9svlOjhKlRpbW6bX1srHVEZKTWh+iwAGK4tMR6Mp9RXqQquIhAQz+YmOhHA2smlZhRZuWBsV0xFx2xlVrGYu99yCBCEHmy21JOnC9DyteK604k88g656PtrYaQnlm/d8dmAluDYfj768bd/ALnnQXLe+nXjoj82yXh3twPboV+Fc61y5RPTs/tXV/bNnJGUiPGFLb/K5sGOBGpVrT+R8hUVLSRidvDKc4sRDcftIPlLMFmi3/FDbkvLAUW8fl7xS9fxeQV6DnSPsEtmllhF6zRc64dwYvr/UZsH697ZZgD7NEH+tkwj2/Vo75O9YBCRCeVtkxqwqFFQiBTuf9X+LI3wYrvpMOfF2ZSE2yWBWMQexpYYc2F9aIELsbCy6tRw6P29n6KU90BYeRPazKvrJ6sbzrt7NJfpmyQvf6zA9ncSLdS1orcWk4G1Gkvpdxh7yOTWf/QORl5HJkXdu3M7iAQqT34O4jGd5pyA73/SvBpmfOosMpoI+Yzcwxqmd4b3T70DC7TnVtq/bzhhsSfLzzxncwHJT8nKPk1HNKZORxzsOG+kMtruDrTZWj7Xj6v19ODEVLNKZaayoUmbJkkIWQjXTqGW3aHHKy98XwdI8qVV4kKukzFd2PS74LnFTC0OIHz13dMOAb3h++7ppBxEfPYClIkpgpp48PZNUJv1UxGp4+ZDVPoBKm315Jqkq4yZU57CT+xSISjRnIk6WFz5zKCkGYZkEZpI1iyg9mxMbfBMQoskg0EubSKifMIxUUDQP38jTN5he8Irz4zU2lVvam89+y5ZIBcrdO/OGvy8UhQMaRLzxryizu5Zy+CLvUCb0rCYy+h8SPJj2aG5MJtVPxnLrIOgwzWG1gNMYjQYi4f/4Z5L/rSgD4H9YvMtl8XB6Ad6X4QX4uJ6ZsFLukTsKVKOe/+PXjg/TmWoTYcGRy0HP46YmEyDekEnz9lwFvLAC0NU6fPbcsBslfTlYl1rGab2tFmrHWEsepIF/0+HizgVWvJPCznWZeRF/y2QJBJ7PVHhcYVSf6CiRiVfx4JgfL7GPfW7lFDVDdyR/sytL5xSyOtusFhHa2OycoHat8hCEmnQ0w+vYLdvPb97eoeJugNwWrW5EHpMRVhnL/PaRzp2awE3WatRH/iG6iAUwkaJamsYyc72z/8qxkFcvkl7krFrh+Sp3CY900epCkX28XBtb7yJ0+62a/pFgc1MzJjPfFtnXYTiRcoz6v1OSP+N/+jfFxz+v3/yhlMAn+CixmIUUZHqWYm8egu4Jq0DIDUuDZIBC5i9LLD9iyhp8i93R/MYEdEFzFK9UIIUWHi/qAZR98sh200AqhTShYYB9w/skhnX4xjm9QK6DWlAQ9j5IACI/iJpiDpU0IFR+hLr8mW5EiCWerx4jdtOqypV7jXIoPIG1dlmESXv03NVbpNXbwFk1Iek9NJb9YwGmwCtooBYcNZx9ksrZUUYKPjRDiI8=
*/