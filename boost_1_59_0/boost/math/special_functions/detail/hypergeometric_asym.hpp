///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_ASYM_HPP
#define BOOST_MATH_HYPERGEOMETRIC_ASYM_HPP

#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/hypergeometric_2F0.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4127)
#endif

  namespace boost { namespace math {

  namespace detail {

     //
     // Asymptotic series based on https://dlmf.nist.gov/13.7#E1
     //
     // Note that a and b must not be negative integers, in addition
     // we require z > 0 and so apply Kummer's relation for z < 0.
     //
     template <class T, class Policy>
     inline T hypergeometric_1F1_asym_large_z_series(T a, const T& b, T z, const Policy& pol, long long& log_scaling)
     {
        BOOST_MATH_STD_USING
        static const char* function = "boost::math::hypergeometric_1F1_asym_large_z_series<%1%>(%1%, %1%, %1%)";
        T prefix;
        long long e;
        int s;
        if (z < 0)
        {
           a = b - a;
           z = -z;
           prefix = 1;
        }
        else
        {
           e = z > static_cast<T>((std::numeric_limits<long long>::max)()) ? (std::numeric_limits<long long>::max)() : lltrunc(z, pol);
           log_scaling += e;
           prefix = exp(z - e);
        }
        if ((fabs(a) < 10) && (fabs(b) < 10))
        {
           prefix *= pow(z, a) * pow(z, -b) * boost::math::tgamma(b, pol) / boost::math::tgamma(a, pol);
        }
        else
        {
           T t = log(z) * (a - b);
           e = lltrunc(t, pol);
           log_scaling += e;
           prefix *= exp(t - e);

           t = boost::math::lgamma(b, &s, pol);
           e = lltrunc(t, pol);
           log_scaling += e;
           prefix *= s * exp(t - e);

           t = boost::math::lgamma(a, &s, pol);
           e = lltrunc(t, pol);
           log_scaling -= e;
           prefix /= s * exp(t - e);
        }
        //
        // Checked 2F0:
        //
        unsigned k = 0;
        T a1_poch(1 - a);
        T a2_poch(b - a);
        T z_mult(1 / z);
        T sum = 0;
        T abs_sum = 0;
        T term = 1;
        T last_term = 0;
        do
        {
           sum += term;
           last_term = term;
           abs_sum += fabs(sum);
           term *= a1_poch * a2_poch * z_mult;
           term /= ++k;
           a1_poch += 1;
           a2_poch += 1;
           if (fabs(sum) * boost::math::policies::get_epsilon<T, Policy>() > fabs(term))
              break;
           if(fabs(sum) / abs_sum < boost::math::policies::get_epsilon<T, Policy>())
              return boost::math::policies::raise_evaluation_error<T>(function, "Large-z asymptotic approximation to 1F1 has destroyed all the digits in the result due to cancellation.  Current best guess is %1%", 
                 prefix * sum, Policy());
           if(k > boost::math::policies::get_max_series_iterations<Policy>())
              return boost::math::policies::raise_evaluation_error<T>(function, "1F1: Unable to locate solution in a reasonable time:"
                 " large-z asymptotic approximation.  Current best guess is %1%", prefix * sum, Policy());
           if((k > 10) && (fabs(term) > fabs(last_term)))
              return boost::math::policies::raise_evaluation_error<T>(function, "Large-z asymptotic approximation to 1F1 is divergent.  Current best guess is %1%", prefix * sum, Policy());
        } while (true);

        return prefix * sum;
     }


  // experimental range
  template <class T, class Policy>
  inline bool hypergeometric_1F1_asym_region(const T& a, const T& b, const T& z, const Policy&)
  {
    BOOST_MATH_STD_USING
    int half_digits = policies::digits<T, Policy>() / 2;
    bool in_region = false;

    if (fabs(a) < 0.001f)
       return false; // Haven't been able to make this work, why not?  TODO!

    //
    // We use the following heuristic, if after we have had half_digits terms
    // of the 2F0 series, we require terms to be decreasing in size by a factor
    // of at least 0.7.  Assuming the earlier terms were converging much faster
    // than this, then this should be enough to achieve convergence before the
    // series shoots off to infinity.
    //
    if (z > 0)
    {
       T one_minus_a = 1 - a;
       T b_minus_a = b - a;
       if (fabs((one_minus_a + half_digits) * (b_minus_a + half_digits) / (half_digits * z)) < 0.7)
       {
          in_region = true;
          //
          // double check that we are not divergent at the start if a,b < 0:
          //
          if ((one_minus_a < 0) || (b_minus_a < 0))
          {
             if (fabs(one_minus_a * b_minus_a / z) > 0.5)
                in_region = false;
          }
       }
    }
    else if (fabs((1 - (b - a) + half_digits) * (a + half_digits) / (half_digits * z)) < 0.7)
    {
       if ((floor(b - a) == (b - a)) && (b - a < 0))
          return false;  // Can't have a negative integer b-a.
       in_region = true;
       //
       // double check that we are not divergent at the start if a,b < 0:
       //
       T a1 = 1 - (b - a);
       if ((a1 < 0) || (a < 0))
       {
          if (fabs(a1 * a / z) > 0.5)
             in_region = false;
       }
    }
    //
    // Check for a and b negative integers as these aren't supported by the approximation:
    //
    if (in_region)
    {
       if ((a < 0) && (floor(a) == a))
          in_region = false;
       if ((b < 0) && (floor(b) == b))
          in_region = false;
       if (fabs(z) < 40)
          in_region = false;
    }
    return in_region;
  }

  } } } // namespaces

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_MATH_HYPERGEOMETRIC_ASYM_HPP

/* hypergeometric_asym.hpp
cxHAsV59liFJzGM2hVwTnsPfsLlqTDU5QdySmFABrR2PsYsgoU2JZDHQpV985hYAT6Ejg39tU3Ln7Hwa68MZo9uFI+Qs7/XgxtSK1UvrSpvfUNOUbRf27qiLZmvdPTnG/+XHK99dxIduXGJc/6cAHDAvJJvTmMwOz+Y09wQtPCpNTLdZagDGvifwLc60mduvur3c4Z0zoNjPkFpKJbXnE3pAoWwqVI0gs6pPyOAiXybePx0HcCPOEA9nvBtsj61TXkyvsuRCKRFgpHH6KlApxuyhrr2R+dpgWb5tG5jJskp8AiDzlV3OnHlO+dJ+VeOJ0BayD56Mql2nyTDZfN09WAExz0u8DiyWsLP4liqJmMR7qCDHhZJe0u+0oYclX5TfyQp3PqnF5scbXOXKn/zfJ9X3q1k7scnc1MbOveBTMIPbM4hLX13DYYvTNLC9ZHv6TsA//Ee67dcQQDeyD8PZb90y4XLfukbw4q/NPdE5y7aIfnLKt6q1QYg9uvbapyhQ0wvDcp2wCajHw7HBJSU4Cprx57Hwm15Bl8FaTIoib3C9rVgODW5qb35pZqhOaffodkL7mTbA6D0zgbjfwsKFToa3HuebsNi8Sw7r58tY9v6YBDoAmso3ZCTJgrGDtxWkViBy1cyzCteLnY5BuJf81G9jbS4pmQzPZASjCV2nJN07trZaVPfDEY3lVIMXWwW5ph4PhPYRw0EMDoabiKm+LMXPoX0zy7hoVMv/EJhTzW9SsX61xN1XhN9JX2vnnfMtTmwoKtHk0RUHgm2Z51WNlfFpbaC4YGv1L80z8t2UQ6Iqq1TftQ0KmeZ1EQZvrzTTn/d3F/FHhKOwqf20QUUQSE84V8tn04zcl53RPoZXVuIiRCUyJuGU01dT2BTgzZsPQSsqWabqbCHM/pXQBzQbDHtPtwWV8iWKjDqAfocbain1+R7NoOn5vNhvsTRwZsKDgyFfHQWR07fd3DdNQRSSdQbTzEM+ykRrAMAna9iEfEwDkVUR284ATvnmKQpqyQA+jqPUtHpBVmzWvYERO8RFMoyTrfjzXtxeHwOn2CfABtAySWpwXqCItEExGpkqXagntwBFM3uCVyUMRZFjuIcEDV6K06vO9RKbua+W3uap7fhLtV4saHSvHbU+MHH7iwbdHVWNHR8kie9UXufk8GlN7CJT3cQ9RziL0e1av71S723pE07m2tu29A8pD929RJimuAoocFNmfFl2CnhY4dV/353I0Vn+t/yhsXmla5165Jly7WwmV4lYbICqjBdH3IBMOC6E2cKHvCq59DiiFXFowvDDKODq/WxLO77XtV7FLpWVA4P8tKW5+sx/3aVDO9/3iUeCZzhpKOY8t5Yq07zoTzr9tHlKVg1SnR4Z3D0YqYSsitZmVjiDKP3+ySyIdPCr44hj3YL3IZEToINA4fRLkG7a2azG0N/WYxPFTE0vcs9RSnV/IgTfHDCfVz0o5eFh40EG6O7UlYtoLdyB+KFr8nbzgc31SjNsS9EoYd9kEWNGySChT+NKKq1QejxRy+QviHpDhy4/uBzhQhzYOIvtadHYTMR4s4/87c4moJbQ1GWwnhcuOSPhylDa+lz74f/Sz5bb3q7v/R14wPcIxZa34d/RXjqh+xR41dMjDfZ93/WI90QylFtY9F1KnvX18ktAm3mWd5PyjVC8OS389CV0mz12KyMQOTZodlX5VhSW5+86THFP24KZz9G+Zrkje8vNsHoVLp9wKq6Q4Wd5PhXuzAYBhCRjy1gRX8PhfLwBIue/Vl3GMwaZQ6IRxpBm47HQFisAtZpYIyzpBzBnwunZ6ACV8eDDhoNezE45iqtyYM7E51Nqz3pntrcel/kqcY1ykTksHF0xzxcXPzi/NSr5gN62IM6hRxYLF0gtMVACXQHuqEihcU5GJ/lwQ58nYWNJ3wLjEnngJq1ukD8FycS3hCB3yoNWrLtjFZiJqSZ30uOlENm3dMqihQoLqe/fZ+fcd82k6lBELT3qnCBqsoWPAb18ixtQ7Hhw6nMALonS1h36uTKOLhxB7/wLIduKp07LxMu+eKJ6+QqJKuiT/rJ1YlJaqO+lG89SzRLMHA8QcK4SE/CDwtcPTNVuF8dggXtMnJXNEs93TFD1fVwP643UBWGR49SoRBpPEO9raCj1vUq5S48608mgRnQyECXgCnQrt1aD+ys4eMnejvnFD06V9LTIs1PqksfB5QdOD9/CCGhqtnY/90OirUXqDKMowCiojmMHNbKkm0xaT1P/zasxtqJtE693TlvOmtEKmlAQbW4C1Fhdw5XnHPAp29CVDdyJhbcKHfAcwVFAxutlr5CZEMxZhUdRsYzZ18nzYX9aiQhaDBshA0ObZ1VPDmIRSoMwd31H6bF7b0USdorl1+IgqUibYGmko3zlDhvgrvAPk1AjBMhIsQVzr9bDed6tOwD/Q92v95fmhoGJhkIo80rJREWWI0RsEEr1vBAcSx+WLQmNCnnvmjeHzac+RGeXBgZ7TifGJt3SwwjABntHuokTJvVS22SD6PhL7PX9VPWIgdB7BgzfZfLf+jqiT9DzXYab5UIBb3PcJogv4JOU+LBSqVTtHrIa50TynPAwHBSDztmFDf377xl38gHm9z3XbF7u7BZPeg1PaMF/j+nSwm/vEaHOBfJ5VnzUlA+2XbFUVIn+MFD/rccRhddk3GWWD/wwgniJ70oivIav+TCNm0b3yo4AKEKlPNsJoDg+bRJ87c72lvJyqbiOIiktqPF89SbBcZo89FyZw1cSja+Wdhw/wSLsJbCEpgrCpqddbJLpUMzTwg00FcBDMXMltSVtybhxdIqkAowV3iLF3ELggfZnS8jZQcjAD7bov7oY0zCIiBt55Xl4Y+cRr0/IGh29kDPOe446aHHI39MVSwDme2Wy1STEsQ4YBUlKDpof3mOY7JmNcBDz6iUTmyEbU3OkdrBnriVB8ip3ICPnIhYhFUrT55W0YdEvcYF4JvcS1U7GKdcobGx6f76vTWCkWaYFwx0obCfF3OeKvU6UmkgXZ4z6SAlXJ41E4e7gBvOjn2uKALaRlIPLHg84GSPPhWsAQDppIZ5tkzTQpnf3sOWr6DBVeccyqqCj8k7D/TDsAp1GvPBxIzuj9pSWqeDtKtYoMSmRvatkW0RNANKYHt1SIrZI/4fqO6biPplSuMGoN5ExA+WlUFm3GK9QVJH7OO07PmOFXRfr36u87SGoPL0wXHoZGPI4GR4wT7h2TfZf/gbYLCYKUPTDRyvexvRTWgk08eZa8BL+07hiye3YecgsHFANRH15ioYEQ7djw4X0/GqtNKokRHKRYNYF/7mTmsUZKsBJR7ZPNnjIh3vcRx1rL3epKl/rl+g6ibbIxKqwx9gmvgTCx3HTRZk4L9CKvqcYoFyTDfcvhdBRfYczphxUq9+m4imEM0MpfRYSKCxX6rtUxomtMA7fklhA9Uc52+0WLy274rTsyS8H6JDDXKTMwX9SDdkGln6sxfbXEVfthArLUnulFeGiWVFN3+frH4U7yYHCEuLiXBX8qsUmy0tvGKbxJ/xU/M5MEoRaD4DFlJLKww9Fh4wgHvKpfSE97LDralZju2Y0foB9ipjCTIU1w3Rzke5tswLoZhB0hG8AgFjlsMZ5bRARV1mQ4jVUO5Cu8XzJbZTy0i/B9A9a8WdDfoVIfe2gKkFUe15EdD9yB76CBPmUHaDXuvB+QfzncWuqXE5sZ2Sd3fVk77tFPh+7pYIKCBrDdi/tg1pxxy3nhqK13UQobvE8TyiA3bo9GYNLqBZrY17J9ycLgPjwB9W/HLIzpdPvRg0vHR+9bV2Sld/fV3TRSWFavi1W18DEo+3gSc7NAGDsJ1ppOjTkvfrxdCCuE/pYbnY4uySuFeLWWxxOFL0DPzYxVHp0jORJntbvLr+u5IyS4J9KAr80vsWldexMV0ZgDSCJjLLeKib2k3yXQEV1du+/D3Yfv/AnUdH0xUVcNXxkZG5a44vwgPU7ivetSN0V1z3cTPu5DHdH8SImnl0MO5SZGOCag5ZpE1fbx/PB5CM/IeTRc0KedBP3v+j7WvBv9G0uE8F0hT+2T3wbcR7cXzIZ0emRVzr9fl7u3zYLvW+7T7K9m+9vuwE81kzATlXhy75wPVI5T2eL9eZfGTj+pL9Ae795eHUAAX39vQGQNM5fiFFy+HZ67WtedONZVaeyvL9nBN+XPHonEQOdfcGtuFVUC454VL5AW3DkcMqgCxx8KaH6qT+UUDLYYWOOTOopKvtKDxbOA5v5j1PAdIhEBVYC/3h53CV3C7bvfA67n7pNOyO7rjlZ17Eaq6D8AuUmoIUy4tKGfIf5+5hDDqtSIBHK2SPujWEIRVeYkuVhPAZQ2rgI392Cg26HzcaLNunQ2XXeah66n/JCdVl70LI1eaZrVVAPfiBVXZqr2b6xK+8YWkm4wHAfbpI9+vwWxL0QEAD+BogfAAUAgAkgWVmzWHUArSm4mbv8XwgV9+ii5qUiJH6TRciK5k4QBfdTkFxT6it3eEGz8Jel6UwlAAAcwDagXgGCc2JaOwDwz9vqErI3And54HNzXDcAyET98zUZO+jCxtm0Xf6/1JVT8qqCqy12SoTaZAi8Y45RgFiFSK4leyxg+/KoA/4YSY7hfrIiCLJkez9gfwYAAAgA1GlY/9tdNzkvrbWfLWiIyEkmFbTyJppwUInAaFbIECThGQAgwFhiHOd4IAgOKHfw8x+6GyS/951v0ziQhJ8sMpF8jns3zeYz+ecZdvlVNoWxHtgflo+tXNLoXjrqAI2ANcmJENzbyLcBI7q67MlJLzK/pmCTKyGB09wfmVCn096nRnO+PKfSXYqOG4Kf12pSCmC1lk5pMjf8uXdURU3QVJFfzmXyV6reg012KhFgvCxLbvXmsRQJO/iLrFcVvlMzWE+8d5uffYBbRRrDGYVjgFdcfy0QlkL4Q2egrASEEPwRUpZ5zz2kyISm5s26gS2kU4+1gw9jBCUvnPFevHaZi+SDqfefLTIMnVGzOM8U8FZi67AIdh2uLdm4XvKyAwJ6Lp1SrrknyesXIpv6DGhfCyheK9XwihahxWNzjUhKqsT+GfFUJ+gFYUed2uzo7FS9Q/vpRQ/llpTi4GySyFjWxLLrhdo+TWl4Lzd+JOY8ntWw47JhZ2dJjgfpcdZFONSVl8FO85biLq+Y2domR64vgAS1s0m+KnBZrfF+rWzWx6OVDnH+e04Gd5nHInIX5CkGe6i0rLxSH6iZ7TzB1Lbu3xC1bSYNn62Zsws03Nk8OBe4IPkckudlnZuazk8dUOuowaLdmzxy/O3JV/mb2LYlF2EftPkNKTkd5owhcVAIUd4Q4lFZJiPMGjtZwWleYW/ugUfe3wd19dOBpLMgAZDHk6Z9KutHxfar7yIiL8TwwlNF5h0RmCJDcNQDKaTCNofCjJWSRteSKYL0O2oGJ29pubZa2pItJ+lihqu3L/HRFQBP6LzpyGRvT+ala4Ye6osVlt7CxGRgiNBxTFvYXO2GwlszXefBqbrQM99/THfUdf234uTSHU5KILZzcK1VzMLBwHTdMyluOAdjjxaLIrsjT7G8oOjCRNcmeTnQk5zoXz+cPw9dRNYPgUmvZ1ZqdHxJ9IXc23N3BcCXXswyN/Jj9+dhavjKcfo7+oOKzhUN39bn3GjembiFvkL41x6MMqIssr44vleUYa1m+y8L5QWa+4iI717SNcPDd094uM69WVe3/dy7lr9GKqmScT7nUToWdvVWWDu39xQpu5bKO2VS27/hMvl3F6uuYhnv6tsSYrmujZ7uanFzSvQX4FF4+a0j4f3tt2Jb2Es6hT9t3Gc3qir3A0/J1g2l6/5EDSBSdgt5Z99yEuDdJoFLrO5JdjvviDSfgu985vJRXnbrYGRjNujPSWvDsgbZ3N3eH2fiGXK0Uv4Tu+He3GD+v0wWIAkbSyXugOiK7q6NEcWhA9TDZnqlx4UaSka/UM+z++x3/Q2pOJypNGzlzpGITu+Pq6JQq6Ynd2jQY6lqxwnjzbh6Q6g730lt2py+iPuVwmfcFJtrPH41rA/el7ztzLSqvza5iLiF51FLxl9OIcDHt8fvz7K/aV88I7+NsT7LfGfoA989mD92petqX6TfDxbfrxG69Lu13/v6wqPO9gleeBNwx6e/fnA3fLMQFR2o3Y++etGfiv3kpedfzxueM9vXvTiQcCd8D9IIH2eeyWDDIc7bYoiC02b/bEzwrli2DWoqQKUJngV2C8CnB6+ux586ZdxzRRcRDa7C8I6AnRdE4Yv9nvi+X1r3ZzE7R70LqSVAdC4It+hnBwmrNqHxtAYe+sjB2ktt0tRwM6uTtkR+i6yBXy9WW9FdsjsKvitiLXoNR8KzUdZ+4ySmz6MPcLzhLp3dodX/gbrz46pIy4jXW0Q3fcauJ0yca6aCkd4OzTOeEwAV2mjdX/iiH+SXjk+73bpAGPjmaWIIrSd/IfJBjNHKn8mymKxIbb2d/oCG2tJEf5a7VD6ffdjpSCzPflR0u9XsrvKcq/pV17fkl0i+tso3jls91v88fqn95t7XQf8+/Pdq+Zv22i95ptCRiC0oDaeM+Gov6VWOoID0c7EPd4KoK/cPbsfJe2jhWNHGzJZP+DFRp/JUpp3GIwteAuqtwyb0O/1fLx5aahWfMGBezl7nMU1rX+wBp3tVUUQReK1S/XblrS2KEGsdyWlG0tQYw5FW/+AhKPtZnWqRjZvP13Pz5tMI+O27crhHA83kCq4tpJhZRaGlwbXYCZ+L2Auyj8qTLhiApLhvdyTbEJaiM0kP4fyDJwlyNjDcGcU21APIx3EbUvICmLSPHnANc+Ng4n5m1BGpGbkTv2cDNGsZ9y4jzISQVHd/9+RA4rpy3gJGtNoTml54esol4TZoICRg0+nwVYG1d/oPRSQVOGvs1oqnalwqw/tci9pr4zawLIbY7m6GyZHBA3RdyNFOnodzrtD5DY5DnHJ2MfWEdwMQR6IQRMBKKx6Zpv/GZqm2UCcmTIHVTgISiQmvkZ2oMMb0uuwKIDUBfa2i4jO/uIeJyuk71c1ot5XehhWlhzE7WkhJvsHG0OVjVbF8a7eUgm/PoWMi40E4sbREcWbtbsIFv7Opvv1rKWdOFzL+FLUVfghp3MSbtUHY3KUy7pghE6LHBfrR7sDE703kd+RTLBcYbYc2UXBNIb2GiOKAlYKAOnETXpJX4Jh/fuyUjK3I3ROS9xafDiwNYqVXgrEzPskalZPZ6tLXU16ns1HsVIzJ4XmzI4b+/EY6bt6X53dyA/dXtXQHxwPZDkXJ2hi4o2ynaawCYq3dwKjRzNTDA6VVkaSMD/hCm1ph1s9nHlqay76Yj2yZAloz8uG1THbIcvQT1pLVx7GrAuW5x5wfSTh0XGiBWiW4GWGs8Ujz+0QCSJ5KmNVmk1LfMaLmydJOhf0wPPti9NuolDdHtU91itOKVEjNbvLtlpfIaNVvK6z5Gx9RMopCy1HcaU1mmeLZT3tACkio+QLxf3yrfR1HuLwf5cCiOhiHeGQB/pB0xWAmrHnz10+Pvwsl7GHFHird8HpZzJczDwUY9E6W3Vf/VQD/G3roRhhkv6xH3ZUsFte7y2vOib4+SerTA39gYst5BxyzmwmQz6va
*/