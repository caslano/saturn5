//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_POWM1
#define BOOST_MATH_POWM1

#ifdef _MSC_VER
#pragma once
#pragma warning(push)
#pragma warning(disable:4702) // Unreachable code (release mode only warning)
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/math/tools/assert.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
inline T powm1_imp(const T x, const T y, const Policy& pol)
{
   BOOST_MATH_STD_USING
   static const char* function = "boost::math::powm1<%1%>(%1%, %1%)";

   if (x > 0)
   {
      if ((fabs(y * (x - 1)) < 0.5) || (fabs(y) < 0.2))
      {
         // We don't have any good/quick approximation for log(x) * y
         // so just try it and see:
         T l = y * log(x);
         if (l < 0.5)
            return boost::math::expm1(l, pol);
         if (l > boost::math::tools::log_max_value<T>())
            return boost::math::policies::raise_overflow_error<T>(function, 0, pol);
         // fall through....
      }
   }
   else if (x < 0)
   {
      // y had better be an integer:
      if (boost::math::trunc(y) != y)
         return boost::math::policies::raise_domain_error<T>(function, "For non-integral exponent, expected base > 0 but got %1%", x, pol);
      if (boost::math::trunc(y / 2) == y / 2)
         return powm1_imp(T(-x), y, pol);
   }
   return pow(x, y) - 1;
}

} // detail

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type 
   powm1(const T1 a, const T2 z)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   return detail::powm1_imp(static_cast<result_type>(a), static_cast<result_type>(z), policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type 
   powm1(const T1 a, const T2 z, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   return detail::powm1_imp(static_cast<result_type>(a), static_cast<result_type>(z), pol);
}

} // namespace math
} // namespace boost

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_MATH_POWM1






/* powm1.hpp
ITdtBMQkU+AlutEVPbmwCIjMQ7Y8ORAo34/NfhZFVW7xmJfrSunbJHSfMCp/um1afhcmK7bTKA4T8dCdkAm+tXb2x0p89ANyVGfMWE1WXkLD31PmoFSfODdiDo6P3ASaA0koCp/buEjlnkpy3YIvUu8JONQsdRLPdEJKSfUzSm0f+YwDNXRXDIM/q9yP5lxIvXymfUsibit88c17UrrYhZvW+MAQVRo9kZ44DmAX+3IoPzJuMkuPbd7Nhr6TXHYwQA121RJU9i2QgssVhpPtzBceC7WUyiGuMXvlZzRPlMcrD0sVM4jc8392TOYOP/E3LkFoi52sGAcVc+9LR4u6g/X3UB8xuZd8M2/MN+QRaRguEvWdesa7Aw1P5R8QCPT62oDj/ymcsqM8PK3fHN7qB7tspj2o19p/7WFaWLa4VPuAP60s8nFlZU039Iyie9+N/mGSSukBDl26D+hiZMSFhN0jJ7aa/ZssHT4wTjIBSFLtWtlItHOd1FZs7JtyZ+zuaorNc550CyC5Mf6niDV21xeFH3wo5e9iI7HtxzK/Nkh7n+1FbRbrt8jOpqiRKfi18zoTtXZpHDa1rGSfXCg6Oc6aoAK0elYWanwMi60MtCwoK0aZG1/yti582ue3ymkR+y0S8iS4DBsKUTHm/77W8PApu1wcKKczl3nL75RnUE2tT1/L0Nd6TPC9PhwYVayIYiZfCTSM8NzAWpksJfEtZJB0r9llbn1/f3KBGqg605YRCO+EHdEgJBTOr8IRcqWXQ8B0fC93Kgt+14ESr1+kurf3Rme71QJhmb3OUvJp/pdpoW7jNGoqnpZ7TM9fBfllxVyB3sdrmL2ZJlvRgPbhBIVxH9jf2NMT+ZTdIpUte2RDgN3I9NVhOPLNhf8ut3y1N897ZM2zF2bbeMqEyDocay63xEU9mgzAQObswsT3TKPB9+ckvuqIuYq6ztykMtPFO1ktEgevr5m1yvxONzg0BSyF/iAdtu48XW5Aoj2TfCE3wLhr9Nv+ASBULi9p4g+3t8OliJt7U1KzDdvhi4RvM5gjwRM5oWCALJTi2RrvHj85aVBG1BAksFGvqPi4rpHTP2tqAqycyIVvWCKmTV5llfSx8p/VHre2abhv3JmeF2YJBKnA8wlyQsSSPDIX+17ApPLnkVv7VXfaYRGqwzltfa0ohZQLBXKcDJ2v7pq6oKs2lrYVaipJo4P40ZInoDTxa84XnuaN3xQDX2a/aW9qYkemj5bvhW+rkD9gcN1h1Q3T373Tgqzqph5tek8gDSnaUhr4XHIHHMDTZXlo5gqyAU9FIiuK2MpYlB0htAHNZPTBVi5wLdIGCx67etOUx8sgHfLMtzt+L7XA6rPXIZwB2IcA54R1/iHtknT1EZUBeMP/Pck7cxC8a7nA5bjQD3A2eHlW/sK3OrjLuf0bNwqnx8uAXlzofYFHGY7f+vQ+PY9+l46lAphfnNSmKRQpcToNxDousPPhbb8wJwTZKez6Sj7Mq+hFTq1+XjTLm9NHbjCSjEUrEqnnRW5E6QCgXX4aVfGdGHoVtIZyiCKZAhtrcLeLWqrN36tzJQ3r4Mo5J5pyACG7/NJpzfy7OphbMJ1ClMEocCzvkHyRSaD8od8jhZ5p7pFM008vdDUFsacE4vMZ93oh8zVLecB+fOEFb46/ScOU5NsbUDAD0ETvkl/TwntcNA0WXjUsMGIHEjKPr6IOoLuh5bXSObN55WZDYqO0hsYJVSDZOK+z+nIhHpG8K7pRQ9C5y90+WDHccfP+e01YgROVhJw6v7cFvh9mpREsp/+ZEaHWpxVU3BtW0D4UWpyVpqE/cFrfnYyTmWVPZVKUzPsa1ZFC6hZp1abm90rgYJNPec4RqFhKs/IaD2E/gKfuJq6ftoz6rDq7/ofQVS83a2/MRkHmdMhal5usaIep0KunvYddMdHU4XHyWBvQghbZohGby9Rjl1ESS6Vni6HHltMl/DGvFhoBpeapy6p1A0F6lKODLyMiMEUlYy5ZPJJefj+p/dioHOao3CJCHjoVbrIPyEczmV1ro2WXlLxWJx7+8R8GlvQnZqC82jEi9Krvy3XVQkXlW4Ck0C6lnURAnuu4TtHCRqayVgLmYAvtPc3HBs5l2WL38BeHkml4wiMIiorWRBSyuJbyHSKLEI62Ck2mKUCij0fijHFoe29oMGuMtoGmOnbf9L53eMenMCoE0l6L9qce5LtXrE49BOORtfZagzbNHsnxhOY0uKa60mtbfc3bIpI/rySbZmLzJGQLoLI/1tu32kxZp4lcNkEJCki3h/cR6oGR7OZnjegTGbiVD4lGn7n8R0GX5fxuFnarRK5Sow/vSAV6rwMHSJmh9zuSLaofJekD/bepYsKL/ruesfUnCs7Z+k/PzVlyo4kNCAVvLq4L9kuZ9IxNLtNF/vy84Hxd9YLDx+4Ltb88DNRDcCgIEATQ2LZt27Zt2/ixbdu2bW9s27btZHN4VXPtmpl+hyl9QPXDsjGWQIIGDGjshp8b+81LIEFf5NUKJdng7vuVzXDNPz/omBtkpZomJkx4DEIknVmXKzFL0Prp1FuBDPw4Mee4vK6l3YUv3wM400KU7d2csLm4XJyiFB+qFYGBYQjcH/5UjPu55c32PpJ+jGVd4kwZesDvnd+COBjf4a8wWt9Tq9pvvfWE2lYmALECeZWqbkEuia2ltmLVKmfspLlYfgfWVKXAhqfCNx/rwxURVgRA9mzwBFgomLk3CBEaWZjH3rOMlgaRyRw5ImL/fJCs0d6ivATwj1R4gub8D9Xfh9/fYhYvwNEv7ETrGiFGWZdgy61wQPVfRG1OgmiiHmAm+BG+MvJpCcT666NELp1a2UhQ7X4XYZW8h0dC6MZlmNN5LWFsry9XH/MasXhId4upQLbZMbvuJVNn62lJOEAunqfgq5SzYYYhxC8U7pLcUm/ebi1AXhd/I/DyCnwPxG9QjP7P/beWHQfDPTt/T/gd/ADvmNnP7/C6nXga0VHvtFbRq7Ce5qJIU+VG4maUv9i5a+VufSwn935Ou2eP+ICxiXsE48MGrXoBWUqKr8t4oRsJ41Yu6bGViGElzxnYzH4AtQYsyJH9Kn5fmo+nZH3F0xYge9xu9D35Y+9rztjfN3587YLCrJlUG1LE2tLX4HHrHuLJALlE6Fwnj04XXWmSXMZDMiL/ymUOcnMT+7RQ2Y4259WLO0cWBGXX/Ibl/i4ghrivWkd99eViYs4If/e1vH8yH+3UnKhU0iNRVQuHYx7XiUxbCHOM6XXtzwC7/e6Oe1aKi6wr+bGVArYVtLFPpQNfH024tG9ESqG7fbByo4x+YxGRxcXWjhy2YRbU7bXQLD9CKUJa/kvIRUByfCtqnqq8YtPShsD+V0Gp3HJaSDogW2dsgvaP4qNno4HA7bFtrwzDJjvO6sBLaaG3b07VsJMDa2bdph0pSPeHhCtxc6IQjubGr32ZGyp/YTw2Km3ku7Yinw8wTQvP8T+Qy7oJRemQNPy8Ken603zk8smXo4UBu+ZVX26wTd2V0OsFh6zBZMx+eWJFrX7jt8AQhfCHdRNkkeS+i6Ly26Y95UKldWzTPtn/dHGPuqlfPhmTFKPE4+5qgaOg+0pLkplzhECMlRvyY3y+J1ZwJixjuPTZrjE5x0Udxy48Jt3V68GXMxe4izRZA+nyCI6oWQulrDWvaHrjCCgKIiW/qHsbJ3G1vt3N2SQmQg5/8A6OBzi1Z35kmbYGqh8apTBrDx5AZwI/Cx1zvvqg9P6LskLGd0UdFOQiIB3/bGciYo1YqGausMuPvg4gm8zDqIog1yer+/2ON3sn8INsaKLUejCDPA4fulr7gUOc7in6mREFvXwYr2JcyVWDcvvccudtsJH6qJz1mxf2TEq/kVXOJjDI9nfWp0lp1GdjL+GTbQblanc+kHn4iB4VU6E5ZekINAVqAoKSyM0DvIYzKwgEWP5nBsd4BVy2pMt9wB/KuhdwpjffnX+nRIV3L2if7kbhSPCkVHc06vxk4112Ee1qode0cn81HxxXgm24v0VhKPu24yRGmBlx5Hmu/hNwc9MavyNJLd8Dkae/l7knBPCYvcd23y3OuokXYd+i4TqnaNBZ6vA6StWZykdLv+bx/haxuw6e8dC2FOFHbPXRitL81vtG3nJG1NOAD/iVdc688nidyqA07OPl1H7VU6EJZJt0rAxyUvixnn1tU9zn2hoH4oRu+orZvwSd7MvEnGtdcLDlCdKgkel5eTJ/h8+CTIkbMmD1pD5omeZb9QbbMUsY+3GluHhbA4gpkqRssVSLksVhrLCIUKNrUj0FBXqpc6BqVy2G3uV/lASuHUN2Yldmg8opqCY4uxRgtu6Mrhe0zb1bQUhXEj+H6UAbb03ky1tL3K/WoiZ73pLGkwNha1wTwjUSs1s1NL9QqIffvEmraTyxWefuEmQ3DSvcx4x5yoBBtugnCrkkcjxYe3ehMLySqY0bHYscfYWVBNOLXNpWWkbG1L/Pci7xhoDp4D1QlYuL74BnLvGbocqJE65//6Cn/ApZzBRVtjgL8e4xGdVYZvcSikQLPXHisVp8oqVWj5bLTHBtR3G9ZkznGcvRLLJ8XNoPpiwO6OAuAE9+fwS2rnHFTz23IZ4A3qSc7PoDhBOiliFLb72WWISgJxYiERNeJPEM3OhrDqohV+pGTmQbVHXLau6M34WvZK+vZ7ie3JjdvEyXCRSJzJXfwQ/ErGZi2SemGEyX6qyeUZLf0U5Lp/8jMP9JyYJDloWdcd3z6FHQzNYOBdmRFfBWJMKvUZmNvZztFdW46++Fe/rL2lEnIgl2lOz6dvWJ8P4mrtLjHxliFMXMWznh5nr0HkdvUPpcqZ1Obfy7NNv9w4eepnyf5dD1cFO0Mc7DDyMf+3PF4F+8Sy/ojoLz4W/TBIezd3GrE/fN+O6n1feYfj06JzRy6xR2ThUMt4idB6X9K7wO4I+AAAAgAAAMAIACAEAPAGts1tTAWFmhGtSqqFykqloJdlVQKVtekLkhH/NSJLwMrqq6vCv89WshUm4B8B8AACAMw2p3HGc4QeM9uh9uGbLjgX0xQMP4jG44aTnGxUoGM4Jg9diOPdPJipcko5lXnzRj/sscAjwmmEEGrj46nIYC7hJlHxidkknMBnVdQkCxITgXBvAPghMAKAABAAAzsIKwArDP5bhn5/yCJKFQdP0/7HAwmvj/AtEIjBRBEIY18vwfDfzCX9z1YXQNRSZFIKfhimDYi5PHfiYhDdz0gGce4acQ8MVGhV96kD4vdMPXajR9Szk/l6+DgVfSCXyxK3N/lbJUcY5parzW9wSjo9pvo51FNji7+dYfOG2+cMFUhwbjMau/eehnW53c5+T8/dfeXkVz69C8O444udsJiEMiEMzu7T7m2XGV60i9y16arHomjRRHKPkVmDlzeqftaIF5JMaahP2GhiGXhxmLAoIeTHl0j2CILHm1vZZD9F/lDJ+WcJCom5CQzd+SEjeLiN/qjt/W2vE3W3GRX6jQzQU9QlLq2RO9NBYlNWLMps/HE/smcKEsJAXSPrqYffRAQ7lkWdBDdhq6Fr2jOUE/SpFKNtF/7bB7CTdgvWt2lF5EXLpy/0vEem6PKPXJXSDjbeZZJTc5wpQoPfGEEpD9iKtHqU7slR23RPOv2oyIYw6IvUQMYMywyWjpOVXjqgvbdbmrv3ppyzQKJYo1nh7ibL2OXA2LnS0Gtzmigdbzbiknbed4qnLCGeYCzY2teaIoMS9RR+jsNJNvjn24xaMS1qE3CxRZfGfNayTcuiQZfSBI+1TJWeeH3xV+m3SxEvcsodWVi1urYb8r56PavSqp6l49WDIUJzlgax15KfjKwOT2HtD7dGRG4oMd8cqKo+cz8mSPVwvJO50Xy/Z8coY22oO8q+m/p3VxVa2NTvklPD3pfNyq3vaK7s/nH3ko3pD0XSgSPJzZg3+bKUp/r4TaAsruiEBuxvjuEjqbFOc/WED24rX0PofkmqjsGmlKNuSBYXdjOCxddXZkzVV31xzqNNTnUXTuX2OkXMl0NGtaUudYulSPSF8sKEYv1rJE19nRzAxcn8e8jNBEljlcFMvRf7MWmNoJ6BlTtCUIMDxdSGnrlDalG+ncZFi2d8OUXkaU5EatiYLEFlRlo4qzYJOaoSrFJuOGeHrj2sBoxcpVRHhPzPe+y/h3Xw2H0X3xQWbpQ1LaCr/4nyXnCE/fQfOYKaFS+s3yxiY6QajlfaPL/RVVZxXzeVwm10gbpOb+1gioeD/3aL9+fjFva3wbO1fSiEtvYqPzqORE9YCHykWAxpm/YJpdwrOn1XtIiMw8v7KOqF6qcIixuHeCBsQu+53+uTRXMFQkHP3aqhCIB1BKck+tYWqhmkwSfrFnWJlexrzFtOCoCr2cbo2xfk/s1Wp+MyH9JoHlq74nroawwyLFlIMz0CySmme9AAAs/9PxAfkFQ/ADytahe2gsm3n5ViED5j2c1wvEcG7kD9k/9c1hzq4sceGFyu22EnLPrFbKVq0WtQWLWJaI0zEWq6ef6XHi2OlF9rFF7p2df7UaWOI03LluyorLGVnKBWsPb4X8QLcq1v8FcuvuFVu5WeOH9OmcSo+ejTsoCp0Pwp3MrZh68IjlbXORKrY8ubFmZReKEm+BAuE/V43p8s6Gx3byZ2Dh2ohazrzAGkVSmV9s4HS1sGRxnXnLoPeE9GqtYriEzmZTVlJOwGUCfReEQCWp23K8l1t7LNKml5iqJCD3h3yZhyxGiGgmlbN5OJ+UX1+sFCntWitoofWWQ1fX6dMJQIKvBJfZKnOZ1n7iJj7BJdGNNdm8OXkTDF67CE4sT4ap1pc95NYZthacKxDKdZFD6IK9czXB8Q5vrqO6BcqrN+EWW+/bcZlMcobtbXtoldJzuk8/ps2PObwx3s+D884XpBhKnoSopho1Wx9iH/+wKQFMCI212Q/geQvRbTvktghV1NKWitdb57wQw2o6M53ACD95js+B/XMdUnwh5RiQ5z00LJ+VQjImJY/VS9xzduFuGqNysS8565K/bmH2vO7g4ZJJM3tLgCxTvjtxnte7zwzgy+h+lfSmPMIFw8ewF5/G4hAS3Kcwlr2f5lD26bQGtUyKnZoZevhXguhKJbVhR5W4qiZfPkb3ZP+Sn1FqXVLC2kPrnuqDBnObZcPKvWj5khNu3Sinj5yHmyWQND0sLgLaUcw+sZn1uYlQJ2sXOoH/sO89rbXPuU9OqQhJfhYEwpPbb9LrN9Kt1Mws0XDqCm2hxc6pL6oODLPrPm5rv1WnuEbN41VR2UXkJ+pZseghmFp+2eQ4woAdbj33vPROmcnQi+dLmlevAOV1x3pwa3NDMrVjBpn8Bh+DC2kbtmqOprQrin0//xqhhMuT8qY94DRmResQ2zgzaj9PYmpceWFqTsuLD3sI16AuGjfEcsnCLKvVk9l5tklYeA/0NLtV5W+zKA1Arg8gbxRgNg8fudpwXKtIT/9E06J8hsOVUAoEUr/wILEqnoiVC4VDs+wJJHupDQl3VfXjoj0Idx2rPUnlt8o/bevTveYub9ceDBknf0hV2T8ppwKxL/AqQtnZfsQfuPA6r5q5hVEz3ycfHIAtHbpanjnpAtKlt5osq4mGqH/6frsPkKno
*/