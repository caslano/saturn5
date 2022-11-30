//  Copyright (c) 2006 Xiaogang Zhang
//  Copyright (c) 2006 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  History:
//  XZ wrote the original of this file as part of the Google
//  Summer of Code 2006.  JM modified it to fit into the
//  Boost.Math conceptual framework better, and to ensure
//  that the code continues to work no matter how many digits
//  type T has.

#ifndef BOOST_MATH_ELLINT_2_HPP
#define BOOST_MATH_ELLINT_2_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/ellint_rf.hpp>
#include <boost/math/special_functions/ellint_rd.hpp>
#include <boost/math/special_functions/ellint_rg.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/workaround.hpp>
#include <boost/math/special_functions/round.hpp>

// Elliptic integrals (complete and incomplete) of the second kind
// Carlson, Numerische Mathematik, vol 33, 1 (1979)

namespace boost { namespace math { 
   
template <class T1, class T2, class Policy>
typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi, const Policy& pol);
   
namespace detail{

template <typename T, typename Policy>
T ellint_e_imp(T k, const Policy& pol);

// Elliptic integral (Legendre form) of the second kind
template <typename T, typename Policy>
T ellint_e_imp(T phi, T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    bool invert = false;
    if (phi == 0)
       return 0;

    if(phi < 0)
    {
       phi = fabs(phi);
       invert = true;
    }

    T result;

    if(phi >= tools::max_value<T>())
    {
       // Need to handle infinity as a special case:
       result = policies::raise_overflow_error<T>("boost::math::ellint_e<%1%>(%1%,%1%)", 0, pol);
    }
    else if(phi > 1 / tools::epsilon<T>())
    {
       // Phi is so large that phi%pi is necessarily zero (or garbage),
       // just return the second part of the duplication formula:
       result = 2 * phi * ellint_e_imp(k, pol) / constants::pi<T>();
    }
    else if(k == 0)
    {
       return invert ? T(-phi) : phi;
    }
    else if(fabs(k) == 1)
    {
       //
       // For k = 1 ellipse actually turns to a line and every pi/2 in phi is exactly 1 in arc length
       // Periodicity though is in pi, curve follows sin(pi) for 0 <= phi <= pi/2 and then
       // 2 - sin(pi- phi) = 2 + sin(phi - pi) for pi/2 <= phi <= pi, so general form is:
       //
       // 2n + sin(phi - n * pi) ; |phi - n * pi| <= pi / 2
       //
       T m = boost::math::round(phi / boost::math::constants::pi<T>());
       T remains = phi - m * boost::math::constants::pi<T>();
       T value = 2 * m + sin(remains);

       // negative arc length for negative phi
       return invert ? -value : value;
    }
    else
    {
       // Carlson's algorithm works only for |phi| <= pi/2,
       // use the integrand's periodicity to normalize phi
       //
       // Xiaogang's original code used a cast to long long here
       // but that fails if T has more digits than a long long,
       // so rewritten to use fmod instead:
       //
       T rphi = boost::math::tools::fmod_workaround(phi, T(constants::half_pi<T>()));
       T m = boost::math::round((phi - rphi) / constants::half_pi<T>());
       int s = 1;
       if(boost::math::tools::fmod_workaround(m, T(2)) > 0.5)
       {
          m += 1;
          s = -1;
          rphi = constants::half_pi<T>() - rphi;
       }
       T k2 = k * k;
       if(boost::math::pow<3>(rphi) * k2 / 6 < tools::epsilon<T>() * fabs(rphi))
       {
          // See http://functions.wolfram.com/EllipticIntegrals/EllipticE2/06/01/03/0001/
          result = s * rphi;
       }
       else
       {
          // http://dlmf.nist.gov/19.25#E10
          T sinp = sin(rphi);
          if (k2 * sinp * sinp >= 1)
          {
             return policies::raise_domain_error<T>("boost::math::ellint_2<%1%>(%1%, %1%)", "The parameter k is out of range, got k = %1%", k, pol);
          }
          T cosp = cos(rphi);
          T c = 1 / (sinp * sinp);
          T cm1 = cosp * cosp / (sinp * sinp);  // c - 1
          result = s * ((1 - k2) * ellint_rf_imp(cm1, T(c - k2), c, pol) + k2 * (1 - k2) * ellint_rd(cm1, c, T(c - k2), pol) / 3 + k2 * sqrt(cm1 / (c * (c - k2))));
       }
       if(m != 0)
          result += m * ellint_e_imp(k, pol);
    }
    return invert ? T(-result) : result;
}

// Complete elliptic integral (Legendre form) of the second kind
template <typename T, typename Policy>
T ellint_e_imp(T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;

    if (abs(k) > 1)
    {
       return policies::raise_domain_error<T>("boost::math::ellint_e<%1%>(%1%)",
            "Got k = %1%, function requires |k| <= 1", k, pol);
    }
    if (abs(k) == 1)
    {
        return static_cast<T>(1);
    }

    T x = 0;
    T t = k * k;
    T y = 1 - t;
    T z = 1;
    T value = 2 * ellint_rg_imp(x, y, z, pol);

    return value;
}

template <typename T, typename Policy>
inline typename tools::promote_args<T>::type ellint_2(T k, const Policy& pol, const std::true_type&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_e_imp(static_cast<value_type>(k), pol), "boost::math::ellint_2<%1%>(%1%)");
}

// Elliptic integral (Legendre form) of the second kind
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi, const std::false_type&)
{
   return boost::math::ellint_2(k, phi, policies::policy<>());
}

} // detail

// Complete elliptic integral (Legendre form) of the second kind
template <typename T>
inline typename tools::promote_args<T>::type ellint_2(T k)
{
   return ellint_2(k, policies::policy<>());
}

// Elliptic integral (Legendre form) of the second kind
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi)
{
   typedef typename policies::is_policy<T2>::type tag_type;
   return detail::ellint_2(k, phi, tag_type());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_e_imp(static_cast<value_type>(phi), static_cast<value_type>(k), pol), "boost::math::ellint_2<%1%>(%1%,%1%)");
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_2_HPP


/* ellint_2.hpp
HAJgTJNZZ+tjQr4pi0HSiYehcq/knEUL7zKz5515D42n9y4AXauW5kuPlUcvdgK2oHrtrzW+VHYfBp2BTWkq+JrMr87xDzeD+AQZJtDfgBX2xAx6MInw1YPXzUu6foPqxjkmjHgQYQRB3HBYj8RGFluc2VwLX7t/ZNHUYgDQxNJBJI++Jvvd2hugIM9qBTxLFDbjADq4KqaZVZaeXwMe+0FDRpNHuVBQBaCz0elsOfNUUfyA+OXVkQRm+Jcm+fuU1KtJPCRcwMg7CVtniblw9caAVu+VYazsCB/S7RYYFbF83etJK/Vcp7F9x7eL+GSWDdz9ztrXZMZWh2JE9UNyWDOFvEVD1Yk0QjKsNbbZDwwBNF3FwMJhhiH+Hj+sFaVRc5xs7p+aVW7CEg6MK0n4JGsQKoanRT3svoD7HlbnZzPra5LgF/AbSxybR3rp78fLr7n5WssJAyUUufgWa5BKoglO3/ZLK4r9Oj0XnQtFNwnf0IU+5eWUKfQOBn/2lpc/8IoMOB5p3gdviEDnDHpLoMlTfU+aqp7KJrfdo5KzwqId8qu8LgQ/Zg5HzpgHVktitHvcNcoMyM9N0SRuJUB3nqnmPZOfFA9voHxjpEJyduddf9hvfH7PerVGMo6qfmVbvbas8xjK+7BoUGm4zL+A/LCtA/lVfkuP6Q9w341rzq0UZZeAWgl0Ud7EcdH+D/EOcQTWH6j7X7ZSzxhQYPrdhZCsD5PbjfPdMyG6yHrq51UEkbotGzpUhMyPTt8TIo0fGS84bfGlLJqaGeIZIngQ20MAa6AGK41W3NaGPlXyVNox5UnbdYIRmLZky3jaDkQiUkHZ1AG7lnslHFh+NR5QF4jNl6HOP2uLRjOwNXIS+V5wKqqV4a6HolLaK8txNA+SK6sSYZr7iSDlavfaAUvvUX92dOl4zrmck8H2BfBjPdA9er23PmQaFfHSkVWb+P/ACHyGGpXqmitiU29m6LyLz7AGNcjs08tI0AovPe/Ugb760uyhduDLlDHmRYvz5DGl9Ja7HD/lBEZiR07j8wWPawnAsuMFgxY7Uwzg+2ZPD8vIzWDQRqAjkmwhois0enve/CJ6a5ibof+zIyqMWIuySOrl9VHV6ukgQalbXoP7B94HxmGehVii4weBVlAjGHM4lRkk8C+TAvUERiwWFSCAYSAAiUS35FeqN+qJHpzvoPgUoMpluihdeEP4aTvlBR4PMesLTA//KVLgmu2dI5SUHFzkSYtxpeRJagdMCCQFSgrnw782Yok6QQDj4zBqXxxA6aPIUMXaDSMAgNRlHW1YgH1BJVhT9ExhDvBRNlDyDEK0xxMlItfzP9qzzLCfVJ7+H3Ckp/mve9cP3lejR4Qtw68+UhnI13cINqBrTo5/V9dVUfX1gQfrNLNNKTtPySfQWtQB/lpiZr/GVGprQhA3AAF40wWvhsPkfihhYNLvL9a2/CH4AGSzjENT2Rt+OoYYNaRV/ndAc1ZaUYvgvpa0YIBvMWKjFRn8XmRegPIFO+HybAQOZLFF+APrIMngMFNYB6OnACjXw464Wa3yrdtaOV6vhP9E4GkhVarFsM4BARA+LcY0UtDCqSUGX8K8xySUroIktpDyCCAGMT8fkbVp0kv8WiVKoxjD+L8E4nATXvVlbBMg43j7xASstPVbmqEBUBOmPIO+VkPga28ViUDJnV9bu7Pwu0eAQEANJ8WcV1uR35J3YoHPQyJ6J9kGPsyApPnDYi84Oj4HMvXLvLW47HnRxACiUfcHK9h8/capFuaCh3NQviCw5lAwmgkpKsLvTY3DK4sq8rSEzBe9D4uh+I7FQiHU/I8MER3M8Q81xb0xH/Kh9A5/F/jzp2i7Xd6vuhG83tR0RKCHUD4hfBTLXv61+fAhgMYdDotQA70/B9jofS1OpkrigSmh5GvSSOeFxhU2uJBzn0Oo8gfH5uNE1qADhLCILr5utIo3J+S5QWkvgpesQ8PoalB6YvD0xNYZZfj2/YYKZLQvP7JZ484ST0qqIZzFzgsK89MZQQWyRPfMG9aBf6H8g27z/oFnW+6DMA44zrSB+nhit5YzKNNGIBvAAHGosOu4ekgX6ovX1vi34LvccTpsF6z2CQHvN0TOZ+2Zzv7YoPfFnyUu3h0zSBBWrwnuAsFMvhL/WwIh0FPqgxjwfrFeD5M9BCQjgGwDMQIdlXmCJGK5eS4gayn8atml4RCq/eGtvot8srELI73xfniEdvYVYMpQSBwseT1z9CIunEeuK5qgRnbFZKmZzPtAEQvomSlQfsCsgK+j9q2m+LLl4XSf9JK08GPPGjBrj8GMP19wa0eGEGlqw5MoO18F0LMtG9/EpVIpVCNPftAkeFH5VK1Cmo8gYg+4B/4fXoMPhZx4N6KAp+kAlmctCslSZtoPxcyGncZCVGHyI53v9zHBqDhqd+Xnbzzs2Xms/vXNZ8sQ4ZJuekD1/o/G98pwG9iHcMKRfBwHdwfwgkO9fYbqXrwQhsm8BJWHkmbG4CZ9hHXtuZXzwqqVTdajP9i2gwYW5rYmDetj2c2xZ/J3UavcetJ8s+irdstCthBDxrmOswD3ANs27yMBjhCHzKtxLgsLYy5iu0qxhryx7/t8khwasW6EVLGEfQTj3PsQLo4pUIylxOaUo1ecdPqRC1PRVBUfG9qphLnxnGf4LSG7ZcPKdUTt3traz17fBUbsb25Qb5TJ23lwzd2HkN26Wzf2zX/hT8MUuqie+Y0ixzY5HPDZw9khlIObQrKirIZqPpiiOaob2r4UIRrwGIrvz2qwGOdjamu2XBE4vizzlBHcNySb3ZTmFLoloqJKQhRSaAPUuLl54Q0ZteJBr+PMLkux5cdys/+pYW1Lcm4F3dbQSmFvk/Em02yJ9kiFaQbIwTFDlwrGlk/MpAh+yovFnhxRWJqZK6gKBkveMQQb5ed6Wmx+TxuVYXUvRSzDWrhkNZrgFpFBA3lqQjG/RSb8BOzx8B810En1u103K8I5UwwiPApl49xnwWKVwx8TfX84TH3+aggqhZRya7p1TWiyuodRvr7W/+4cf5k6peZ16/6sd3xqIQAzxo6UU3q3R+SZiJ8PvHrlKHce0anIxOA7ClyvyLruxXfmbYyRQWUY2mH05RrbapYnFTcEjptPkE//w2cQJM0ibBlZS4guHpusLLJoikCV+7dEbpXUq9uoW9aBLrnUQZ9shV6NcmJ5oteDuiy0daZvoXkvZ/kbfuzv62vzRYCe/gAg/uP+MuO9UJAYnerudEKfLCoKvvwsbA9U6Wq/COmFxfe2kp7/rrLuDO9bA57DykfPA+d+mDW6TgZwmyupNQsknf+BwBnVK3NfpjnKO/DRT2paX7T2BbkTkW6+8tlPig3gdEScpzGwj6XlpX7zW+EJV7mi71n+Un0aJgY51hcLINpfGrcR9trqFNzHewZfnjmRUPtcqnXNcd2Xd+Gcse1uoNzKCCJn4hGyuAwRTK0PE9KTNKyrQSh8uc+hHOTxfIEkc68Rg9uNFZDnQj63KHVh1LVKRE9nAAHgdzAGlONHvXjlH2RYbE5BmecAVaHfIw4kkmurGKGmisJuZPZimRXrZufnuOkvidvtTMjhvWiNqgxzS8e+tFwHilOOTejT7ZA37B7zH/uPNilE5wLg6ARF4+COUAbJoHP+uTL8eHX+GnY2vtSN5gDzyhOSEvU2oMSrNXaFLmAvX3EmWWC1wTLQgtFn21NF0k28F1OTyK3pP89Bkv+U/u36XjePdpsGhHPn9YAXJ/hsxR1KnqPfSMGUtjvDnkuVXDO22rbNZoMn1kiqZ4GqNuhcSwcZEGmL5b3rLc67As5A/1dDE6ca4PtTXGq0hLezwKhxwv+z8fZ2SEQWVlHNjdb4O3M3yK1XcH3r+SQ5ym2yHOeuobZe334baz9isasjfVUG4Tjvog6qvvOC9U8a2FEoAH8Y7uzVTe9DLxYXP2Alq3I5+k2VXPASJagRqrsGDOZrvRuyboV8acqEsy9O875eN1F+pU8anMepqu6nFHbkt5N/Q/q516sR15d9lexbOddx8nv3I/SSGGYDxnXOVZVu7tTiqkALcOREN/6q9pWadvvVSejbyyo79jzBg6lw06GvgiTcHZJL7YVLOGuoNLNPwDpV8/ESE/OFyH1OkorbW3+5hzSQIXceo8dDw/vl89QQ3PW2M/TiJOvvXNtVbWKW6DJQzrIZJN0qX3EDW7GLiUG39N5bBsHdkU9y/wEpEonZACBeYP79EFbw2o2sF201krvSRoGTLtVsBesC1duob1479mDbasNTgm/jA2ba5KEMu835sG7fKkRzDmS6XREOjfeu67s7I/rlexW/49wrEX4yW7tZ/ipzvSnU2V6d8HmAtTzU6UslHUe4vvTufogAOqci8Xi+/LxjqmyV5yq9VgANvCaCuEX7CCm7f3FZb4fW51t2gtt5pdklTZgW3lXcTBHZcz0wSlnG4WU0AalyKyi/7HsGRxS9mdbduG4LC9sq6oMxMvli5cbegUh2eRTBlE9MAW2nejBn8/fBus+btSnjs3RWicofjhpgqu1PY01k8dsW4faYxeVHxiwGkdAIkusGDDHjlL0SzcncOqRX0L2C75bw+qsw64ZO3B27Lycq+zmks2J86Pr2QWNprePHE5c2aGLV4AWA78P9xukDvXHO5JgSIK4BDwCFoeUci2lVfjPN1qw20pPMQiZ8BhfPZ+Xw0wCMCrvyNhnfrsNsNYe83vVvoKNG8MnLsL7w2JBGnCH+vWItnsGPF5Yyp6FJvnC/ZzFqMzgRPw4/TiDk2GPKID8wzqKTWnIpv9NbehAjWDYZm4N3ZmQEJW/BAKhABs58P2ClDw/gXyJj2ntJk0nXjVGQ658eXaAeC1G4nFzigxRNfKo7fI9PV9oG7tBVvSTiZF7gtBpgB/DTIddetozOX6Hz0/LwLTjB65UP/boVbtlf5X8d+JGmp6GFfFetvtLbeHliB638tT8ymhH10/2I786fDX5znw9Q3A8A//zOewBkHYJ9fR2+CH6SxY5Jd837J3loCQigceZ6Hc+iEg8ReY9QTm2E0ZQ6q8NHZOBtRnIWWpa3unOEpQJLbsyrX2znkys6xsH9APwEJQEB/H59n1WXk/q05beo0lT14nEc/3NsPqOiKrEOgiw22Z1jaqafY+z5N4BfXksxCDAOIgEWPZPBYs/A7SLbEuwqeHG4gN6nv4oqKRg7dGO4U1p8ZRKcVeuCViIm6Zh7OBO9Y348USt0tZGRM7/xRNzCxcKMhpKUhUDwKzXugATYYuGNPAxVpMisYufe8ZsAFkXNm58YtFtupjgMOxgTkt0oOEvCQ6zgcusBWKhKK9SdAcbsUNMEnGXWLFuqO14vo/FgxrvdlpO5szGXhPW0HVupCvWRbjv+xZoWiZn8kxwWHGXfibP9AmEpcUmNjdW9+QSfshlcAJYleh1IhmiSR8cKTRFWghshgr7yX/8IFOIOLobhfRik6FeIwuRzLMsaGM9kWfaEGysRLVsSUaxlboA+C6eXR1fmLJ0tkQv4jExzjxnuJJS9xDRoRchNAD4wTxTL4goVT9cK6nul7tWE/YHtQ/DDilFhNEdKKM1VCxdnzzOUY42nlWiO/0z61ECvsJCKUbrz9meoOeFqfG8IztBAtCsvLN/PfSeM8YF66I7qulWIv3Ui7WhpL5ErTO7eGNKEXMXhrAhFneXHAyQ1DlXvsFhLkJzSawzDDG4wLHtJMTWkBZXAYYxylEdL7QybSIQMzcNiGLjov4TDEEiS/z4i9GFZLGvR1bs2IW7ZeZA5sk3gOZY0Pc/T+5PBj/IYl5tNm5fLtDtEU7JEizQH4qtqWOIPxjElxR2JyCkbnrhVH/ppZ1a9gIvESt8p1lpENwYmiarF0tOQ4Gq0WEJDUQsgLu/t5lMrFY+H1dPZv0q4ylciuUTh7Fgs5qKXjqrS1alrRxMY3qrtrUlh5WRLXWbPyI4eXUuOg35Y39P2x2gJxzPggbknCbg2lAIQnrTGw2qOo6tOKKFtctZIlSBm1BquKNcZDXbGougmplSK1ZOStpOHFFySsTLuxdWyJqo4xU+yCrqEZL0XJe762fwYNSAzSOTRloU/FQQPASSWXRTkdvRy6uI/a1cKmRsa0vwjbLLYqmPA8MGnI0RpOdnvKpu1WitfGbW7f65h3aRHOi+LjX89THwyXQOSRbEbpFUu3OUdqwin65ACX2Y7k1ecmgw7FDH4nTxjVROfTLu58h2Ye0X3vb8nvxYeIsWUdyFkH3TynSWYbiZUMamGzlDZAKS28zzDzz5yfD9EUOyXOYv5HHgLFx9nYlEcNcf9G6383lqoTeC6mHquzrpyMgRematFnd4gfbiqDT/l24iIPS6pCWRyTH8EycO7bXCpobNWaGUIsm4/fCzXG2SqauEvK66+NcIISvEQLhhifVbLui5dTTt5fHgFl2M4FH0/UchPv+DCoX6Lv9GhkFmX5vNYNJJ5/uu2f6WWpg8iG2MZFA1Bd/Mgsk10/fRPwEWeiZ99STpXsROQ3ZcxZpiddWHMlKziqkl9fQVpbG0X7Y043v19LYw4NB2f9/jiK+HF4e7nOjMdXOh/vE1GK/cNgawDfa4Xaave7RgcfQQg+L3gOX4d8/T1V70LrxZ97KxGWtUtanL98pOSZE/g2SFy9+C4Bqirg3XdH3Rwe/NRoTeDpCH9AUwbhfkMJ6pqk4Y50CvIaaaJMYb1Sz6hf5v2saBfYPuxw5gshgIu5txP9/Wn4xIWq+J5/MH9dzV6rNfdMWtRy/7D3cjM617V8kUzT9XMs4pV0mzj9vkg8k6VRtmiQ8fr4UhZFcef2ZXtvq5K7oA/9J9t5lvXP5vrLX3yHC/SsurxqLlC82qGHpQjCsN++antOxVU7XAr/W4wc/EeeLMIq37dOkMsdAjvbUkV0eAzJpGXFVQqDGvm3lZoGRTO/BzLyTY8WAttTH53xjqhC+lSCPmxN9lyw1R/NRC1efhd8Ac7YISSZVKlzQR17zPHtUX7sYBmI4cjTtEzpDRnS9mXwxwupH9uYUrokq/mcguVAmR+jSU23gy8SQDqv9PcUw+JUzaTN1wpHBQtgTP590TDa1caPc56YgfO7G+nNLN6mVFv/g6aZ4pnZ+dxAXK8HXKxdzLCsVaGrwyO/94Wk68ZjnOMQldUIE/TduLzOc70UlZMBmDQUQ1YveYzkf9xfBztTHhhtk9rttxcledoIwV7v0pngHttnYNpovhZDf3sIKF63dX01HHNqvrO0DI2L6kGiAa2pww33fbgPgqYHidOcNPvg4n55/ml4dCbZcQRx7DYFZN5ZoFC3MPv4w3ClKipBY78IiG57KHzdeEhAmmPhoHLYwXp7DIeNDCjKauB3LEmAzGMKJYq2TQVYSO1YVZ3BrKTgYIJAxMr4qFnG2ILA21UUME8v7tpkO+IHr8tkEuDfQFD1VlHZ9r8cz1AgWydSmWx5SuwqgyAcvNa/Om0HGSB3jcemeEQayRsKrIVj5Fq4l5PUiyxXO7liW19BsCI+XnI/V6ermqfSba91/MWnrlAD7q33gWhswyFlZxSCr7zLTZ5My4wy3vcSR/DpobYqw9jqqkUbYdtbO+8yKdLdnmKDcQPeD35bl6vmjKnEXXGhgmx
*/