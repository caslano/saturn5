// Copyright 2008 John Maddock
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_DETAIL_HG_CDF_HPP
#define BOOST_MATH_DISTRIBUTIONS_DETAIL_HG_CDF_HPP

#include <boost/math/policies/error_handling.hpp>
#include <boost/math/distributions/detail/hypergeometric_pdf.hpp>

namespace boost{ namespace math{ namespace detail{

   template <class T, class Policy>
   T hypergeometric_cdf_imp(unsigned x, unsigned r, unsigned n, unsigned N, bool invert, const Policy& pol)
   {
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable:4267)
#endif
      BOOST_MATH_STD_USING
      T result = 0;
      T mode = floor(T(r + 1) * T(n + 1) / (N + 2));
      if(x < mode)
      {
         result = hypergeometric_pdf<T>(x, r, n, N, pol);
         T diff = result;
         unsigned lower_limit = static_cast<unsigned>((std::max)(0, (int)(n + r) - (int)(N)));
         while(diff > (invert ? T(1) : result) * tools::epsilon<T>())
         {
            diff = T(x) * T((N + x) - n - r) * diff / (T(1 + n - x) * T(1 + r - x));
            result += diff;
            BOOST_MATH_INSTRUMENT_VARIABLE(x);
            BOOST_MATH_INSTRUMENT_VARIABLE(diff);
            BOOST_MATH_INSTRUMENT_VARIABLE(result);
            if(x == lower_limit)
               break;
            --x;
         }
      }
      else
      {
         invert = !invert;
         unsigned upper_limit = (std::min)(r, n);
         if(x != upper_limit)
         {
            ++x;
            result = hypergeometric_pdf<T>(x, r, n, N, pol);
            T diff = result;
            while((x <= upper_limit) && (diff > (invert ? T(1) : result) * tools::epsilon<T>()))
            {
               diff = T(n - x) * T(r - x) * diff / (T(x + 1) * T((N + x + 1) - n - r));
               result += diff;
               ++x;
               BOOST_MATH_INSTRUMENT_VARIABLE(x);
               BOOST_MATH_INSTRUMENT_VARIABLE(diff);
               BOOST_MATH_INSTRUMENT_VARIABLE(result);
            }
         }
      }
      if(invert)
         result = 1 - result;
      return result;
#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif
   }

   template <class T, class Policy>
   inline T hypergeometric_cdf(unsigned x, unsigned r, unsigned n, unsigned N, bool invert, const Policy&)
   {
      BOOST_FPU_EXCEPTION_GUARD
      typedef typename tools::promote_args<T>::type result_type;
      typedef typename policies::evaluation<result_type, Policy>::type value_type;
      typedef typename policies::normalise<
         Policy, 
         policies::promote_float<false>, 
         policies::promote_double<false>, 
         policies::discrete_quantile<>,
         policies::assert_undefined<> >::type forwarding_policy;

      value_type result;
      result = detail::hypergeometric_cdf_imp<value_type>(x, r, n, N, invert, forwarding_policy());
      if(result > 1)
      {
         result  = 1;
      }
      if(result < 0)
      {
         result = 0;
      }
      return policies::checked_narrowing_cast<result_type, forwarding_policy>(result, "boost::math::hypergeometric_cdf<%1%>(%1%,%1%,%1%,%1%)");
   }

}}} // namespaces

#endif


/* hypergeometric_cdf.hpp
Wn1a53+0Lrq1tdfFNGlrvGMwaPaAa+ANyMw2dbEoc2GOzq1a3keXMV7dKbIzo1pp2V4uxxlRQ0lFncAvnWMB9jBGRWvZM1uQGirZaMdql4FrV/xeupLr3Sfnz40Kv/9eI8dTo/owYDUNuO4kvVaSuVaCXsuyr97UkZl7lOus4zrr5NyCqPD9aoUctzJ1+GQ7aYOBqc6zbrgfH0yV2Ox2oSppU824ZiHXPEXi/CiAljhvdsnstWht7pe3SviW1vGJuO3znPpcfEDO7wnsc3a7tvu1N3yxmZ8Llflq0vWonD8zKsmcX5xTmLHwQn3MlfF6HnKnS/p3BerxvKzPPiqbvSicz1Lk6orcVwF5l8Cd5zSKlCfucLzFyPcW+ZcD5Mfbn8x83TtyvmGgP89TMYFoSfdawu0T/5RAMF/RiSEbHd7520btg+d/qHUabi8Npb1oPYmdpIyCwmLvWsszwXg50vcSfsyQahvdyHUdifdvLnGEBlSHVVl9h2umcbwmMpOdAPXcgisymnnKP8ukMxG+0c4zL2HaWV253ubgvIScbx/Q+jFlnuF7vyiRa9aSesgnXIKE+4T6inf64M5ymmu+fXMRGv6WVMk3aQ7Y3mOM3NLQddwATTH8/niDtKHpUWlc/QBnDgVCcRxqquWj9w7zXSdv+bOV2Dv/cLfE77qWfi5l2CdBwmmb029rSZg/OgPojefgLnaK/XMnppwe0vjk2MQfpXnW9HrKtimsLzK1ve0mP1srIEnT8Lyk4fty5+/gtFZ/Rk8Je70Tw7kryMNgnmMbBMfSVPYLkqBJuMsby7HwCtzZ+KXjyhLJG4UyvomcN+ux66v4zFvV+0sDvb/omoM+K/jvN3abbshKnVLX+Gld672pV/vI59GzfMetUyOP81Pt97KRqWpfi5O94eXwWmSOdtB7mVmcsjxXaP280DG0n76v09DM1XUUv3FuPv1tjbPdvtbewX7PCt+jEiWObPd3tNDPqOUxboz1fqTx2OZsTBqjJK5id5dzs/T/OBOum4lL/SqdO2nfKWQfLknHmL+KfL7bxxnKXrNLrfcZE6d5r5PkmTijJW11TbpayfEs+qmujXjnxgjjwo9FphthQu+Sf6GdVDZHUizpruOE56WbSPgMtxtPMIfosyPcuua52hHZQIVzpB9ofdd3Vmj84TC1bevmEuZJCRPthNdA6srxI05nnuivoleHx7vrxH8XpZGAbz32nzY26yMb5Nwezmw37wxcV8t2uPTNtiIz3XMPQeeGxzGvHco+ItPMzLsua8/YkBpyV6aeeM6nqn1fny19c0P2OR9kpQ4LHc9cqPb18R0j+3Km77hpp8jjCeY48ntBK/Ujk101M11w1yCzX+RXLsYyVsYcyU5mERe3vgckwIMin0wdubZ+TXx+WwzcxG1r0z7Z4hN870ZlVdeiet9qM/VynK0G0uafs9Y0eMtuZ8dQpN008lO17FI6m7Jj9V6LrpKyay/yzSsqO+KretmldK562aV0PqE9j3+6vGQeRffk39+h3P7FxkBF9hSq/22UaweIXYlJt446fF9+n7K01/Z88u0POlZsPyKxftB/9T23vH3ohR49Vr0wuTTvB3cfqdiuxDtiLyO3eZ9N9S//xZzZQ2/vteLUmyecPHsZdnsT1bejUd1vAJ2sb/FUZEdjn5Rz+tedOk75atnlW8fMSD5S5+oV7HcX/+JmV/5x1dk3z7isy9Tb4vvUPVh9Oxp2uycnz75GaA+16jXCZrgtvj3UafqNiFPhKbAbDIc7Wkm4Xhqut4bro+GuMDpwjM0argFumYYbhFw9OBgmwKEafjhsAUfANnAU7ARHw1PheJgFJ8K58Gx4ATwHlsA=
*/