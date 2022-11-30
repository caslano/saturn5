//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_MOVE_ALGO_BASIC_OP
#define BOOST_MOVE_ALGO_BASIC_OP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/utility_core.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/detail/iterator_traits.hpp>

namespace boost {
namespace movelib {

struct forward_t{};
struct backward_t{};
struct three_way_t{};
struct three_way_forward_t{};
struct four_way_t{};

struct move_op
{
   template <class SourceIt, class DestinationIt>
   BOOST_MOVE_FORCEINLINE void operator()(SourceIt source, DestinationIt dest)
   {  *dest = ::boost::move(*source);  }

   template <class SourceIt, class DestinationIt>
   BOOST_MOVE_FORCEINLINE DestinationIt operator()(forward_t, SourceIt first, SourceIt last, DestinationIt dest_begin)
   {  return ::boost::move(first, last, dest_begin);  }

   template <class SourceIt, class DestinationIt>
   BOOST_MOVE_FORCEINLINE DestinationIt operator()(backward_t, SourceIt first, SourceIt last, DestinationIt dest_last)
   {  return ::boost::move_backward(first, last, dest_last);  }

   template <class SourceIt, class DestinationIt1, class DestinationIt2>
   BOOST_MOVE_FORCEINLINE void operator()(three_way_t, SourceIt srcit, DestinationIt1 dest1it, DestinationIt2 dest2it)
   {
      *dest2it = boost::move(*dest1it);
      *dest1it = boost::move(*srcit);
   }

   template <class SourceIt, class DestinationIt1, class DestinationIt2>
   DestinationIt2 operator()(three_way_forward_t, SourceIt srcit, SourceIt srcitend, DestinationIt1 dest1it, DestinationIt2 dest2it)
   {
      //Destination2 range can overlap SourceIt range so avoid boost::move
      while(srcit != srcitend){
         this->operator()(three_way_t(), srcit++, dest1it++, dest2it++);
      }
      return dest2it;
   }

   template <class SourceIt, class DestinationIt1, class DestinationIt2, class DestinationIt3>
   BOOST_MOVE_FORCEINLINE void operator()(four_way_t, SourceIt srcit, DestinationIt1 dest1it, DestinationIt2 dest2it, DestinationIt3 dest3it)
   {
      *dest3it = boost::move(*dest2it);
      *dest2it = boost::move(*dest1it);
      *dest1it = boost::move(*srcit);
   }
};

struct swap_op
{
   template <class SourceIt, class DestinationIt>
   BOOST_MOVE_FORCEINLINE void operator()(SourceIt source, DestinationIt dest)
   {  boost::adl_move_swap(*dest, *source);  }

   template <class SourceIt, class DestinationIt>
   BOOST_MOVE_FORCEINLINE DestinationIt operator()(forward_t, SourceIt first, SourceIt last, DestinationIt dest_begin)
   {  return boost::adl_move_swap_ranges(first, last, dest_begin);  }

   template <class SourceIt, class DestinationIt>
   BOOST_MOVE_FORCEINLINE DestinationIt operator()(backward_t, SourceIt first, SourceIt last, DestinationIt dest_begin)
   {  return boost::adl_move_swap_ranges_backward(first, last, dest_begin);  }

   template <class SourceIt, class DestinationIt1, class DestinationIt2>
   BOOST_MOVE_FORCEINLINE void operator()(three_way_t, SourceIt srcit, DestinationIt1 dest1it, DestinationIt2 dest2it)
   {
      typename ::boost::movelib::iterator_traits<SourceIt>::value_type tmp(boost::move(*dest2it));
      *dest2it = boost::move(*dest1it);
      *dest1it = boost::move(*srcit);
      *srcit = boost::move(tmp);
   }

   template <class SourceIt, class DestinationIt1, class DestinationIt2>
   DestinationIt2 operator()(three_way_forward_t, SourceIt srcit, SourceIt srcitend, DestinationIt1 dest1it, DestinationIt2 dest2it)
   {
      while(srcit != srcitend){
         this->operator()(three_way_t(), srcit++, dest1it++, dest2it++);
      }
      return dest2it;
   }

   template <class SourceIt, class DestinationIt1, class DestinationIt2, class DestinationIt3>
   BOOST_MOVE_FORCEINLINE void operator()(four_way_t, SourceIt srcit, DestinationIt1 dest1it, DestinationIt2 dest2it, DestinationIt3 dest3it)
   {
      typename ::boost::movelib::iterator_traits<SourceIt>::value_type tmp(boost::move(*dest3it));
      *dest3it = boost::move(*dest2it);
      *dest2it = boost::move(*dest1it);
      *dest1it = boost::move(*srcit);
      *srcit = boost::move(tmp);
   }
};


}} //namespace boost::movelib

#endif   //BOOST_MOVE_ALGO_BASIC_OP

/* basic_op.hpp
1PesKDrXb8U1NjJZoLwiIkjQip2QOzhjRp7PG4b9xdkpTFXIo+wPpBCwiEpStqQi3LxYP36tAnZwqeCQb9Xe9H9C/m9gdBFBin3VTRtmMXhmD0MchFKhoZtL+O9WYurLXvoTbdEXc0NWHf7peM1orO6XZ5TdI4LsBEuhWLrKt/XtwhgqZAQUMMgELx2eO4K1+zadqRf2hMNfbF2Rs5VjBAmi0ey9tnAL5m31q5j+PfYLFhynvkvt53fhsjy/Umu9/8npnlx6cPLNchxxiuhJVyE0w6MmP0vjQ4XWHWFvcIOTI23JAOfGH13dHsEhkYbaElxzqg4A61W1m+B/Yjq4dlSgGFy8hBVnAEh3GY2vsFGx4J7q/nyxCQP1g3BJOpYbX2F+Stpi0t2pysLXLoKnMy7Vax60HgOEXKbcII2NWcBxZBbHcTPr0dG51EOpLSpCF2EmsvkMP6f98PGeHnJbdPI5XlFrACXKRVRr4IVA0US6H4pudZ64Bid6p7jTRwrtKk7yiPzLU5DortGKYvGFCGSJdlTTkJFPcQ11eHzEZ8U+aHXvx9XnrYxkwSfzKCFsd6Hou37AFNpw4yMbTEXxyrllbS9bLcK/CXJyLM3rfBEYt9NU1Jpz3wi3zAT00uZUKWP3Ef5Smo9fMSOOhlKLDL3QHFlFYG3JBBKEYVvpPtMPO2+O5xCuMsnHcRl+ZtBRaX6fCjFs6HkMD/tnO8L7YqQLecfQcvJaOVo5RhuV8inEyNjB5VCFkTcf0MGxbCSgJT6Jf4iXICL0Q4/JA70hy4UWZ0xic/fU8OVgGIRGJKGPeY+yfrqtDMnFcReO1tk5+CcQgkwmmOkwkP8AACz/0z9StmY4GKGFoVk1prAVt9eCRQTfwWWSJ5Er6r0FuFwOeVSGuOXU4FoMXT7yArqJRtlxH4zg782HT/Bm5wKgmb/jIJ7y9bAuqAoHRnNsDNl0r/oBdSiIY6PdddFhtyeWA76yaAad7lgVHZ2vmvSBwKfEg9f5rfzjQcQkZbaG2uDfbm5SkMZmvQQFJeqPDZfywDN+7l9oY5lStlYnL4vd2RnlyLVD0xCrpkl11JJjggxNsfSY38HXqU2dS5H5grfTaZ+f7ekM67pCOv4anAXllbc/YW8Wg+64N/Zmx7QujDC8ABQV8nMJqwe7HnUAPiLmFeO4bSjD5lvN3SU9TYdKKwi8oupfKjYaQ0YUzlWs3G0mdN8M5AA/nrT+BuOqFOiggzKVZJTXwN/6DkmvKjPWJ9dxwsoS7rJ2dir/LETwFRZiQnuWMK0ET0paYYwoUh1NRnXgvYU5dlD5AJw+WZZn9D1DxE9QaqeFnlID/W8bOLIGfW3jVUdh0dvjZlhJh5GTxMpWpzBcTFrUQvn209v6METQJzt/Cc47y/2afItQH/SxrBZVmimJIvt/R+EmPv6MxyQe8t1P5ZW93IKluGPa1dAxcdXdJNqkATomXW9GLFPmXTEwRIWAPYN+651z8oTc+gufM4xVZJBpNTCO57eWCm3yAvgYBS7BR+RIcRIBMTjHJ0zR7vfZ1JxBo5Skm8yiyMI1TND89KtiZzBFgBRTuZFAZL63Y0EG6qJw7/vbUnXekXi3/mM8xyC34VZVGqpxhJJ2pUikUPZnRLwFknoq3I3Zp7/StMVJ7gOg07TwgF8iF8qTL6K479j2Jf31PZKpkEUMLjB24XS1YndmO1FVCskRxoBLvSHZ9NfAAhh9A81bOMwO2XVksY75sQY6i5nxnnkIRhkmBcZaM7W08D+KJpLXEQzTjECMcjW/Yjm5F0EKyxn829fgACJvbWXTm5Z2QpfFt+RU9HL77n6vaDpr4Esi49x6R6qlYZ1TBSHLqTDiBUGcPwYbHRD831GsS/c/XeoH+TSjxZyGZ2Dw0M0+KjTMc1z6Ig5YEYi1DZTGZD1HxRtF2Keg3EgpJuGfTYerkK5uwvw8z/P+bXZaVmJM5r9PWULdsKd9+DqI0lLPufOK5shDGrPiHWkt3oAuMbu7MzdzVWM4/tgY+PYY1AIWHy9BKUzkJJJ6X7gBPwr14Vm4uhynEc2gLpUXYhDG2/d1N9KvREEQVNH/Vh8BEBT2G4cDkQCcFx+ZxCnFs2brlTn1m9HGkwCg6nkZFg4ln9QGHi+0MZVsThhNcC1J7dgMvlbWk5V+yZ1Z7SS++VzsJ1rvl8QPr15p/M6LmNv2xIKBj/kxjyn7b8P+Ln6fs2xcbukCSHLip3igDjYG6PsZsXlVqDmdUu6x9vB+PPw2JW2q09tPCutXwX/OI6SApCnIj2GxfcQhAHIgGmbtzzEuX0nlUwGO71tBBRFuN07uhaeFUSCeflzrT9yKdmIpzc4/EREh2rrUSBFOS3jAB2RtuS2Evr0PPk8P60m0grXp4y+RNrHYBOgjxJTwJDl6JSrGkr77ZKaiw0D39jDAYbQXtWNjytVh39y5W9QNhjP8VA36IHgXPxBWCH8r7X5BQgC0hr/HJ0/JQ4qnxwMpoHeqYl+4segQpsv3ZI2+Sc8Fl+Vi1Oo6paoa+n1udHBPvweLQKL+tmsjSdcOV1j2WCmIuCg+Q1pNHQy8Bv6Ub5cC13LyozP/22vNaWJQV5/wOFVD1uwtkL95HpVKrWmlERe3gLPONqRvXZ17EV4ayZLAfRscy5Jk5mm/JP/3ltFbmhQjgUeohSjozTuBYfzy1z+3LNWfAqA1C+r5KXIOwkjUM+Pfuvq7fmN6bdjVyrozGI8igoByUv7C0tpYa/rR38vMoo4u/aUphruy4Ndf6zhGkcaL1/rsRBJwO9qe5+jqOYVa2iEQ+bewMAuK3ftFOaP2IuqOmvW7BZcz0P3u4UXdY4xoq5nKLk4Ow6/uwxFPNYZBH5CTvxam/tL49II6iiz/GOfqH9hHl7kCQsFx3yNtuehVVxX4DxBhQaCts62f2rmyo7uDj0gZKWcRr92R20MP+GzDpXFWDJBCzqvtXS3UB5pcgajxCMnNm5iidfG93K3rzq0KWJQR3D+LaTeF/abZ8YTpx4i7KUrQskF/+6AONCExPf144UG+2H9m7ec0zCHPvk9FPktS2a8AOo7yYuKfQnw4CSOYvuaRkr0y3na7xRacjUDe7kP7OMTJR0BwDyqWG5q5GFv4H5Xgcsi82DRvgH7Cyz3PKr+ia7KquiB/EA4eBK4x3sUFuQS2SfiOc6g0KvhrDQEvGzApj+UQjnVF3H6Ahl5SOTLBwmoPXnooWInUfpAsO++1xmgwMBlGc6+KLu7aQuLTg6SquQJ99ngUk3hN6ycZ2sYkiXh1kEDyamHG/1GYW/zcC57evE4F+vw5chhusSz2nXzxicX8wPUaXX8AypTIHfr9zBsN1RdzVamoOfrzqKXwbopMUI2m0y2dHb0VK0/LX/33w73RSAGHNh7vNxHdNlK2cXjoMxojq2RAQ07ftwkzgowqmUaa//KTaH1fj37MKnkyDFSGW9vX+aLceHjiHVettau/Im19L0wy13qjC9k3kmjAt9DiDRB3sIgwU/UOUtCWn9/SUOOX7+ILpfAiSjJNpUNwgXJ1VeuL7uut3Yik5pNwNGlKnI5y3W1on73duHHJikymRBqiZHyxjUO0W2vsf2Eak+SdfdOkRCqxhCQYUqeFDqLxjsuwI5V1I79KsCmMp6L6v30UD5mJLvylJ18trcVaTpuvZd15NA3+wH1Vl6KX7k/eyItPwhoqssyJuoh+K/x9Ga2YNTYMSQEuCAdixSEoInj7nqqfRRR3SA2yOAMdACo8wSqar/8iI/Ov9JjRM5wZOzMySzHge7o3EztTEVdFpA+JNBEaecO6jvlaWDalLewlnZxK75jiDgX0UYMk0ia3KMjZ6ZX1BE1337bWT6JZOI9nQzlDt+d0mzhdSEEdPpEle4gajYWOScagJqqetJI+SE642XlOhE4LoM0mhpNN+ygdFTa9fgc7uAlpLDv4jP4DZeAXQOfbvspOn12KgYUWT1nNr1DbUA4GgRXvT/+NsCUcbFrBQDZ/Ek1UNPCbmDXIwPix/M6xehJkCyDw/RpuYINLVlrCw4h4anYVxghUDgwb9wOkBNBNh6cDpNY5biEa21VP3thQTa3MVkWPFIGvnxhF2D4MsfGF+7ElZ/8rmXfjxsggYfeH2ZaoRTH27/zIHVuamk79hJiH6etlS+8Um9aPakJT+IHX5wDgsZ+IWnQQAhPrrkoGu3XdUKsiB7Xp30ccu7H5df1G+hneE+17fcUaAk0oHw34kmo4xAMoficr6lS05ClKUUlcwe7YYpjt3q5hyQn7b1GCINqv5CYLT3cxd6lRe/wULxNRr73MTctFL4u2fH7pCnBctgyBEAmf9FaXncQWl+GmSd9bJuNPVP4MAOhbXwa+UxeUnGubf1RIpSE4K+sTNhJj1NMB2adI4dfbydLX8P+1aQucSAE5x8oWqvZ1ZnEkzZHeyXqlYYWu8MgmTp5Yw6waST7F0nQrY7d8lraOz2z0WWGv8gfwYls1AhKxcUJCDGymZsSwCHWq0PlOl/sycaCiu7nnW82OeCPEOuz/QwoLR2Hm1UEyZfwyeJL65ZMIF5x8PXOMShzrU108x7RotTB8EukgUQE6+AZsmIsjOwV00PPzmxYW2UbLn9o4hNO2GhXwmblr4I7d51VqEoobx8e/t3NblvVFHyfP75yeQXmybzi9ZGcclQ70OjxC5bWWOSi6oG3ABAD6rlloYBr7LvWs81m9naRf59kctMkQUYjvEm70GcDX+YbgU/YonfdwI6IJkWQfCSF97XnRFMNtlGzB94IsQROy8SVCUSqBVgCGEJIY3IhmfooiJx2rgA/R2IpDlCrtxYWzCp68ajh6h0mvKZWpRhxuw7Wr2PS9Fc9BcnTLhgTj/zd/K3usoTuTeOHxl77Oct/xRb8iU65Xcdy4MB2U9Ic6Y9R7OTRWJCDyusC+o9cjhRlq24URNQED+MY+AM3KxifFpl1erKJBhgJozyMBR+EIogzTaF1TZ9jo9+mnheziD+R1/EjJbcATWpONmI4RmP5XaXAo/l+Iy18MhjEAbt6vbANqah1s5SF1DaweLBiCD7pCCXVjTNeXk21kyVihAW4G31U1luTFJ/5jK39lGLpUAUOB0fIhSJHp6qVOWihBP0AF0dAsA3uk04FcSNWQVOdE3bpjWulAihdHWUHXejbpfGYfxRTLIcVOuoNtixbcBcu371Q/VnCBUW7RIc5jRNLEekLHkaWVY414fo8jPY9v0/gcqHp5xhf6pkWne2m65Q1xrq0z5liVYVJsT/KpFOVPl5j5p4ntWViEeG5zk9lA4ejL9GyedKGZaR6SgUeSWA/d16hH66Fzk4eeXb1Rrduczd9O4yeELG8UaZ2rJU/w0yBsuAtf17gEhyliraW/cbLCk5iQVS+4ZhUQpMiAVZak7nzHF0OOH5QxXAo/NMjEmO/7is5Njz61f49P4nHIb9mDTbTkHMcSM8EstoPtbCtMPamT0/XkSUKOCzTnjl9mE6UZ4BI0KKnRl+y7Z4ViV7Snb4Wc87s8aSnUZlHrFUtpwgx7oFPDHD787sqUew4OPWBcgQUHo3UlNaLtuvEJldqY4iEzshVuCW6VD1MvBesvckjqP4npTKSLpBGPKq4qIZrvqPi9qOZVGy7dyep2FhTpiYu/CTYxMCYcZ/8lsTSxr2t6LpZ8ya3AOCPb/5pqfFF1TjoWSfusw1IuKfRGDWH2V6k/omT506Es8QvYDDTulBo3wl/lGlFyaIJIihDH8gfZBhDYF2HlAXTPzIqCzGAmc6lS2KfJJyCIhoFbwN3ux5tp3s8uBvIjdcLCtbEPDHiKP0cNhSauAx2fphGUnPM2ZUISn03tpsEMf3jgyqzTrYTJ+lFMBQTHbOdIF1ZnXMVyYhm8RbdrxHu1uxIozj4zTny9qkNwXcg0lqyOZitR+lnc8Kbpx4fGlreRoUdio+Ob/8mANjQX0cNznUszn0BhXiJlAEVHUr6YYMoFVLPKJnwwARKYnL65jsIbseHj3/N3OMCEvqzqkmsABz+TfD3NcNWgudQufYDsvFzcX6czBT9FT+wthrwkihD0w3zhFdOwBphyhG7co2jZF0VGeSrZ7GiKnv+3zcbBJtkp41LIb7SB858YmnA5besJQMb+sNm1MWQ7QdE2J0gfIx9282Cv0Pi5ETAxqxA+KlPZEDjqcRbCj0FvZMZ0FHY8le3cbBH0FzAmCJuUEYtRPQpHo9vbHfOMPMUFPT5hP327L1SIv6YA7dKM2EEVn2GCRqRobSCm296OzhqQlEhoFt7MBFhfvWKaolCTaeJ9xt5AW04MhyjR+vf+hTYGczVqqbkFZ95KsE/1iCj2vrcV3xGVKJNU5B4Q7hUevJUTUaznB+CD8E8BTJvVqJmEfbIJHv+7hgASQ1xTwF93cM5UF/98OgxcOvnurAjmUwmhw/Jv6o3IGg/PlyW98qx2hoxsrHfQtzKov+XwUQZoc8bJ3K1VcUY0Ah2eBzPLKM0LFCHaq4GYUIF02qluDx8AxzDy+Ohv2UFolgxuBybf37s1l9FJp+fvzQ6ko3cAhcmwo4XYRKkg4gG8DqzIlr6OtQqvyO02qzl5iGMXiuShz8CCYaluhaJazT7nDlmKHE53aYU4XVRCCFk4PgIKQMeyKew7l1b8LgxPA2lJFRdjIbXBTfZyVVf2Vjv6CvgGkNb3wl3KcVZxpZcR3YSlfaVdWIFpv4C2CIEezqFAIUL+nQ2wVFss4S85rEsAMGirDB46YuvwEY91B/ibk3rmSvUqfdIDCrrPH+lCi1So7/JSP+E0FCm1sBLZOVw0t340ynTzBaqK11/ZtK6LHeYvxi4cuWLfCZZJ7y1qnLdOMLBg0aFNjNJF1M7jFRc5+6GOFDg5+FFX/e2uaW1eKpErRNSRUKhtVPFxkj/4KUtPXLFINVvBdUrN3Hp2aw+1mjo04DHq5XT7Oo2zWHgx8GVmPzbgYBAvEhVhxF0YL7Ux/j8weAnkymIQ3UiDTnJ+0Wn1+xO2ljpVNIY+R1VqlWRw7/H3zlv+AxcLFwJFWhtKcEKSBpHLuUfYqnFfjBZKi+IRJ76yfqOUehDmzhODV0adCG0bYM4C6xj4jZzciaEGpnCshv0xkgbPQTe/UeEjfeAN8M8mPj4tKTXlWO3q+7v/zHAfVIOgq4ptg15PcT7/wh6mN0Z8Y78dNdrr68KXMboFqhuPfHAWBfmcFHr7aTdRDvTlULpwt7h+U/46DECR08UUMPGBOB0M17HlBBw9w55huVnXQMt/6xfIC+UrpBPlK4EM2Hqf2CqbbsP7kLF0CC5MOjyFmmABYAoompEcTtKlqgtcPGBTfCQhn9NVpjdxBM4vXXkbX4VehDcIt0ZBLDiAOlJ18fbZmFh07cgskv3dfXf5/kQuiT5DLiHdnQoojPtIjbssobGbNhvgDpxosKlf/PhRQYQ3/4b0Rl5bIllA/GDBtFzTvqsz8DKbcIq3rLr0HybER7mV1hN2mWPWigo4gx6CkQ9HEaVn3O742P6nNOZSjsm6Oe0GszWNTI+H+MO7dGCBDyd8K6gizllYWregb/6yanYvZqrnZOHBA7ir/bnFJZir+1phm9jeXTezqwOjcsAb2cs/JyYNr6GeAf7QFOioVo6BYF0zy1e1
*/