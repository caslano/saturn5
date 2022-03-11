//  Copyright John Maddock 2007.
//  Copyright Paul A. Bristow 2007.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_FIND_LOCATION_HPP
#define BOOST_STATS_FIND_LOCATION_HPP

#include <boost/math/distributions/fwd.hpp> // for all distribution signatures.
#include <boost/math/distributions/complement.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/tools/traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/policies/error_handling.hpp>
// using boost::math::policies::policy;
// using boost::math::complement; // will be needed by users who want complement,
// but NOT placed here to avoid putting it in global scope.

namespace boost
{
  namespace math
  {
  // Function to find location of random variable z
  // to give probability p (given scale)
  // Applies to normal, lognormal, extreme value, Cauchy, (and symmetrical triangular),
  // enforced by BOOST_STATIC_ASSERT below.

    template <class Dist, class Policy>
    inline
      typename Dist::value_type find_location( // For example, normal mean.
      typename Dist::value_type z, // location of random variable z to give probability, P(X > z) == p.
      // For example, a nominal minimum acceptable z, so that p * 100 % are > z
      typename Dist::value_type p, // probability value desired at x, say 0.95 for 95% > z.
      typename Dist::value_type scale, // scale parameter, for example, normal standard deviation.
      const Policy& pol 
      )
    {
#if !defined(BOOST_NO_SFINAE) && !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x590))
      // Will fail to compile here if try to use with a distribution without scale & location,
      // for example pareto, and many others.  These tests are disabled by the pp-logic
      // above if the compiler doesn't support the SFINAE tricks used in the traits class.
      BOOST_STATIC_ASSERT(::boost::math::tools::is_distribution<Dist>::value); 
      BOOST_STATIC_ASSERT(::boost::math::tools::is_scaled_distribution<Dist>::value);
#endif
      static const char* function = "boost::math::find_location<Dist, Policy>&, %1%)";

      if(!(boost::math::isfinite)(p) || (p < 0) || (p > 1))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "Probability parameter was %1%, but must be >= 0 and <= 1!", p, pol);
      }
      if(!(boost::math::isfinite)(z))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "z parameter was %1%, but must be finite!", z, pol);
      }
      if(!(boost::math::isfinite)(scale))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "scale parameter was %1%, but must be finite!", scale, pol);
      }
        
      //cout << "z " << z << ", p " << p << ",  quantile(Dist(), p) "
      //  << quantile(Dist(), p) << ", quan * scale " << quantile(Dist(), p) * scale << endl;
      return z - (quantile(Dist(), p) * scale);
    } // find_location

    template <class Dist>
    inline // with default policy.
      typename Dist::value_type find_location( // For example, normal mean.
      typename Dist::value_type z, // location of random variable z to give probability, P(X > z) == p.
      // For example, a nominal minimum acceptable z, so that p * 100 % are > z
      typename Dist::value_type p, // probability value desired at x, say 0.95 for 95% > z.
      typename Dist::value_type scale) // scale parameter, for example, normal standard deviation.
    { // Forward to find_location with default policy.
       return (find_location<Dist>(z, p, scale, policies::policy<>()));
    } // find_location

    // So the user can start from the complement q = (1 - p) of the probability p,
    // for example, l = find_location<normal>(complement(z, q, sd));

    template <class Dist, class Real1, class Real2, class Real3>
    inline typename Dist::value_type find_location( // Default policy.
      complemented3_type<Real1, Real2, Real3> const& c)
    {
      static const char* function = "boost::math::find_location<Dist, Policy>&, %1%)";

      typename Dist::value_type p = c.param1;
      if(!(boost::math::isfinite)(p) || (p < 0) || (p > 1))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "Probability parameter was %1%, but must be >= 0 and <= 1!", p, policies::policy<>());
      }
      typename Dist::value_type z = c.dist;
      if(!(boost::math::isfinite)(z))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "z parameter was %1%, but must be finite!", z, policies::policy<>());
      }
      typename Dist::value_type scale = c.param2;
      if(!(boost::math::isfinite)(scale))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "scale parameter was %1%, but must be finite!", scale, policies::policy<>());
      }
       // cout << "z " << c.dist << ", quantile (Dist(), " << c.param1 << ") * scale " << c.param2 << endl;
       return z - quantile(Dist(), p) * scale;
    } // find_location complement


    template <class Dist, class Real1, class Real2, class Real3, class Real4>
    inline typename Dist::value_type find_location( // Explicit policy.
      complemented4_type<Real1, Real2, Real3, Real4> const& c)
    {
      static const char* function = "boost::math::find_location<Dist, Policy>&, %1%)";

      typename Dist::value_type p = c.param1;
      if(!(boost::math::isfinite)(p) || (p < 0) || (p > 1))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "Probability parameter was %1%, but must be >= 0 and <= 1!", p, c.param3);
      }
      typename Dist::value_type z = c.dist;
      if(!(boost::math::isfinite)(z))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "z parameter was %1%, but must be finite!", z, c.param3);
      }
      typename Dist::value_type scale = c.param2;
      if(!(boost::math::isfinite)(scale))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "scale parameter was %1%, but must be finite!", scale, c.param3);
      }
       // cout << "z " << c.dist << ", quantile (Dist(), " << c.param1 << ") * scale " << c.param2 << endl;
       return z - quantile(Dist(), p) * scale;
    } // find_location complement

  } // namespace boost
} // namespace math

#endif // BOOST_STATS_FIND_LOCATION_HPP


/* find_location.hpp
Aphpgh4kn1HxorvDu7O6zef5hU4x8YcU8+IhmOf8+yGscUI61d/nElr+EfobqlT0SAc7+jscRfPsKcbo+REm9XUkoLhe6avGW1exB608x/E399DQK/zQY/FdfJM1ul+CNMWQw58KizDHkHe9blYe7PeHstSHU94ZhpvRSiOQhNK9cZwpZdCMKv2QgTZaTzOzKR25DympNlJEgKG6qPO60Wa3E8pDpHyw7ciWE6LVI0rNnCU9q+UE2mAvR7Lq+Psn4h/mgmuDPTKJ29ANtKzkDoYcINiqmUdbSRl3kLEUpV6mdBrUN/uCfDRl42Lpdf6y3pe55wvmxbhVuEHHRETcmL2aQCwK1R4OVkqdhC/K0no8fuD65CoAa8s8y54h1qJu/Jgyv964w5XKlLVAyz5pZew49/3lbXtWTXNajVckBmBx/ZEgCrhngT6xvAPfuiQRsVQinSMQolCBiFzaRgAUPpBqw7mXIpycM9HymMbQocjhbifqTk6oqNCnRJ1MIf3SUpWv+En8uLT6hxwzSE+yGPJ/JJG+J5A50h9FSOvn7IgXgdrlhryeo3q077XuuICjmCfo4yBtr3uhJegvZmtl6Kr9zySv7OpWVMyW58l9BoRlRFcjhlLHLruGHCYeqsk2rS3VbOmlb1We6yD5ZrsBnGuu6SCeVsZ6ZoZpMe7iJULvnbr/9YCISpgzQHHJ3NyPSHgiKHgbgGSt8pglNDqQFNx1UEOGIa9DsU4fA0SbS9dakfsjt3LyBl2mZvOMBV2ht1B0OQIH0PXO785126DhxmUDeemkHDNs/C++wiIEaUUfrReO7Hkkrjb+dIYiGs1IcHjhZPnQbjXQhBUHuzvF3pumQhkEcNlShdlf76gk0XrnIb2mogglQIHDICqu9uJ+4Sy34QHf0b/dXb7JaPOVT9mqteUkApT/J8++gl+t+Oxdo0JHZwRBFwcZU61DpWdLPkRBzEQ05FCGeKV0jitdL3LDLUIZbVaBNoIuaVAdwjj8WjefThxbl/PyPoE8Tn57Z0gLGpc//Z7pFp0EeYVdn81T8lcD6fGGAetXHWXBX1dTL2c1gUkHlRXd1fQHAMPPQoD9UJ5YC1MB6k2ytaax4Pa2aF+yNTREN7DxU6ZJ2pEj/7RXIhF07c02oFUmgyFe6/XPUqueBl942AwPaIlagoMSjwDTnkokalTyuiK3sb0TS7fIsTK35AdQ9bpfWyoGPAKPklbYOI93wfMXM3A6JM9Vd9TvZch7ZxWJygf+FO5JlccTbhS7CXhWAxKDaFPB+qKJZRzkJxrp8p1wmzBB32jqLig5cFjGEJC9ECdcLebAv1W2tucY15gxDb5blsCTx+RKHa0TVX/FbDpFYt5rDX2+lj4TVYBhT3XoHCvvPsw89rYRhL2V21PTewlWddacvUImizj/fORVlUTiLSDmZkRVhmExm/CW/KrXDqe9GVh6I7g/kN7ZgEXdE5zOZuT2C+5ZG1RGZM+CP0E4eZO4BmAn/zI30mgZ1/QxQ2BfGPYcR4LZCJvcMqaRtvrb67zpKB9y6bAH1zBaQPpUSemcNqDU6as4NKGmsxSF1KojpB2G5Jxs+8VNJoa4NqK4Yr9DvymT0QQBSk9131B9+UhzvWIAFwuwmmPXHgMqVj3oRzgZDomxdByeWpqkzDcPH8HLzu4u1Tfovm1f8ZH3PYGPJ+FadOQNLpF2GU/wRZ8szet8LEG0mVGjzUVYvn8baxiaMS1w4X0I0fjCGMFErJlfHtjWU+4UVPYMC+BojvI9jnPm6ix9kBSDDT1kGzLoeVaf4Tsj6XAg0zeQ6fWRxChf6thTGUfu3XYhQs6Bd+H9p/ZucN5HnnsuzpauQZfKWT49LgV2/1arcLyKX3n6mDno81pCn8lhLYQ5w0M8GjEV0+64ls8LfmiJLXA6Gjn0ddi/JeAjcmvYW+ZYiefXfTgtBVY/G6WYdRV26sq/ksifoI4UvH+iPBgDqMS6m5U1KmTG18gVyhMyFATBOuBYH+jG9dOOKRID0SFMi83aeQljadFnjQi9a6O/13XJbhPu2Op5eARNZCC1pj0KXf6fhJyt99YyVW4geVltcBi9G/azG9+ZSI11WmzxkOR+ojPCxPLkCpfym7YG/2y+exojAIfzdi95IC5sOJPGcbz18ULo5lhxXPbQe+ksy/28+T1LUVwnmHogyAPUgRWCU2EfVx8uQZpSSHSyGvKyMUcRxhFXDk0K2G/NWqOjg8HYUKlmG+wtBuPLVAXyZynE38nWF9hY6/ZA0xzkC/NyOJy2FJYZcwBo2Ixo0isBiaFVl3J0AltXH6xCKzci2VRtnOga/fvPq+Npb5nOOEKh2X9HRU82dsuYKuUnZQu/iGdHYsRZPyz1SN7R2fZGFHAuSc6jYTWwKJWRJIm2R8c+Hlwos2hSp4FBIWtxv8H6jxEG4BHsFKDeqCeutozXX06DRVRyTK0mm2f59GDbQhHuzq9J9tgPpp+jRWO1KBBd2mSu+jdQvDsJQHdIsDI8tQbpjc4sgOOoxZfQPYHgsKW0u8sIjw9iO+UIcj71EiyfEdd+a2qnUPKE/t6gpClJKoDmSxy/WdkIp6C3Ickteo8W4nX1/qHtECZspGTwVMAuGWXwdkqKcfVmHhb8KjymyY1wfdw0BZXWHuJx9x1eu2YIjVEFu+vSo0Q58025tAEJBCJh9/FMz26/9MDYWEPNRXqEX8lZLW6uZoR3UWOLa6iNEZoRre1y7kDbbK1F/aXHwS60YDxTl3rliN4CBJk0IfYGJShAnnyj6A5Il7iCPihH8kuC4qsm6yxdL84CJ32emSuISEGp5BxXz3rsFyW5R2vR2qGS9nyj8PQqXCgkIk8DsRjauFoY/IwdvwH4iAINxJuujAPlnCcEGIgrtHYWJQvDBN1n8CuvuE/ygCWqOSe3qEyphAPikPpaNF/8k1tagwrIjvjcWddkCB9IvBxXyvhRB5/ZdYDuCq+fq/LAUQOPvHDreyABkKHBxpOKqjKjoS6hXSSSmx/jRDvjeIsZpagPxpCQQBDJQgY6dZFIvZuogA/vqn3iwqqOW9EIrqisdFCuHKFV6UwtPtI8foNO+tptrJ0E7nYWT62oet3rrmvFYXTD3OFi89Um0EkWh5dYoFJ6USz459AGnafBfEXziamywz0E+cjA7gLJ86W7e7TSSKs/KqyQ6H1yRePQduV9Hn9w4EeNRJNSJodkyFCE7s5JB2uIHMx5oG7IVaM836imHtScvp5OLr2RPhVf+FVOn/svXJjbceUc74w70ptdtpAWwY2PiytoxiEsRF9yotoEsm7ZFDwOebC8dB3/DHIP7ELUf+IZ2way1j9nacY+Cr57UI3gXldtgDf487yg6b3SyEhws7w45wq7/U59vDotlbHAFgcnJUZ5Ge89S2Oly4iQ1H/iHpwPyss7Kl16bwmxgstyQ8wAROsU8wARTksXCcVbA7VjC7arIDJbZ40SwatKV9kmTlwspmQAbOzEC2BqZvIpGhqY4F2d0gYNURW+I9UYABEs7tP2LD2wczhfKhTvnDeelZJAPFwFdIStS9A1qfHBaj/rrv9kSDWsFIiYkPJbrDRjrlLZ1IdpzHjv/XKTVe+ymX+pdw29IwyjnaA7RbfGnwufKoS1aTrRe+H1c8mfFuZB8SDpZIJnbEFoAu8kW0LLyQ3DqxITl7QSIQk35+hG0C8oM21ak/JD2Ppx6hNt32YNCoUoWvoABVvDKw6gCd49C+lSaGSNyCx5UQUSnkY3PTZigRAAsuijxAooEUA27pKh/sNk1C6zLQl5OhmCYMpnxiyI5rABEp/KTB9QX5IGv/gnB8LDxmJGbYsQ2q3R9oi1MPVsQ2Wuk7a2oio8i6HJNhanlqO2C0PcdGEufGG8s6bFgpfLjq9gNEa8ZEMc8NCIDXqN3/6JiEGnG6bJsYEvVUzuinmaRz0qEaEJ/n2bnQISTsYc7AmSYr5zYSF58BjfvNkNQp4HpUI5WRyop8L1ugM1vtbHe4OZuH207cxTwfniwmIPJrZ+QOhCOUmciwtbE9FaWc1wh2luhhYzKbG5ywgb9qvyPlOhlpHslkFeWValvwfnVs59wFKaAkBy1/2uMVRCfu8AZ1jo8vDXy+g89UTL5jcsW1lFI3RVM2IO3XHgvcsuFX9jvC6LEZgD74B6nBjBlSlr5RLgqEyB/CzJcfrhyHwxN30Ytnq7LAOefE0c7s2NDy9jFzpNPLr9snqGQCi6TgFeNk3TqGJP5vUURSUmgUy/rscmLpXFqKV+f8aWseANFmHLonQje9UGJBhhwSKTYSqDSHR3DxzBBL8v3LfvUmL9ZjnPfvZK/k+yYHj9+ruYu1MD+OavKm0OMdq8U1Lx+Z6C2PrvaYb2NHsrqKO4TFkNeROKbZxGJvDJUP3iST+ZD5sgPoO9xyE2e+JkrJIy8Pel6drV9EZsDG1lGWxqO7wkkl46O2sXlXgOJ7B8QBdhyEynNNxKIAFMP8eyk2V7mzM9cwpOB658uQNpgvNhryaezVbc2mKb206sg2PybFdli0VsqigJRokyKOnPk6SzWLDgQFQ4XPSay20IBk+KQ4KvkVFCPB9WLNbvNvX5JMF64pzIILkiF2jGS2HyFaeja/klFdbuql6YKZdeME3LjUR4k41kD9tGiv3jTtZj3UbKa9WXDAbre4ThIkb0VYL9PLck+//TwWn6EWKTa4TQqcdyYpHWu/h6N72zUk/ky+TgnUY3cf8SUZ2MYss2SsrE2SSzaHjobChH0HyCAFaRKzjbaaJYy70vuNcUhL8oIFOYqGzQN1QiOcFO70J6OCf+tXvguVJHyByj1JnLEI8LtuuycGMqgIYyPh5SZhK08CcYJ6VF3zAAJF55bU3sOFzmSyRBhtI7nQFo1IsJpTyLbFkvhXx99GT0UJKnt4ZNb8ml8VCHfbgif874Js+OIvdyRXqWIs0kbfyOscd22tamd68a3Ssr7TR++ACY3dzZvl3x47Bb44W1U8zDuW6muhTC4/ot2tEsoexj4mdsMLu37/BsX8z+LpwZcsujyBMvDCe9ok2kqHqebEIgtjEhQbv0n7M8Mofjpb/EfA7jqYzAF/DDRUOtdwJKZKllUcoFB/lOtImsPt1MdOqesLvpz/oZT/m7qrKZTf1buZK9gPpUvss40iwKXe8sebxwFi0+NlDodHwlkSR8BNN4p6Krm1Idc53wMhQh/XBhn73ApuX4nN1VviN/aNqdDmoRahGNorCz74WYe6rpNbTJVx5TKB6HeFmGFrJQ8CKyu7suZwmvodyBrU2gElEF8/7J3oG9J8sF4krdTaFs6ymxWeNUVY2aEaDZCqtcPHZD0Jl6ZC2M78mVDDhvOXkx+IvR6OH4cE34YCgXT6nIM93dUEtxBnPSPQo3vPXaBCunM0ZeichrILHzCw0TiVXSKq0eoQ7Xhs5oU6N+CFSn31MD/ex2gD+cT4WcSc3BzMLlQGGrJBNhH9OIMRZhUWq/Nqutux+Yb0w4LqdAkn/XEVijv012S3DcMbwkt+LWWNncEuD9CA7ii+/x+LeNFgU9FyLvcHbL4fuwRwhUhrfgx4rDLj2DOiofCpxXjxuySMCHOVI7Y89va/WPO+HogTuzvZ7Pxzk5AjRkGIX2QF/H5q8V5wQ8RISfVvT7REgsDOfMa4+GZrSfoNfjowy6WfJkJMuBBUpe5jqPJp7BC3j8T8qLRoTBw8cGvaglP9Tcc+bojYGD6BxXAPhWvY3hLJEoZx/ANi6yEDS8vCk05vP3+p9MRCwQSmiwARVPqCn7NH7VEM/x6guqIiBLEPWw1JOmfMf2DWfjmZsZ3uiI7n/R3rMP801iskQASlsujeKDqmdL3uAOQPMbkqaselEityCrVyNpaKm7/j3P53ZjHyP1+falNXPmyFu9hr2cbUqV9AtuiRZ/ci4Pslx5RuYHW3qeQd36onDgFdjC6Omq1Xvda/9fOuEu6L+sypqPYI1yfjNmXujMOvEMweGRX5thWBvn7IRmZtsGC1uIfOnehQ9tA29vKHWvxAJVqshruhn52m4PBEViCkvj4XpIv5XyUTm+UevwO2SDOfsXTrbwTFfvLnF478OJLZuUMbuO75pDSSf7ncdu2SpN1e8zVdbkrKib5DBExJ6wNjyZU1XAb633sR657SqmH7ItHpQqzMRddNKzAxqehEyUN/UXK5ITirkc0PgowIG1JuaTETqpb6V4J8onA8/PqAZgvNwljGVLX3+jPkibv83FoleWnYvz05/N9HI3YY5AzdnacjVsljsI8iyc+ealhNI7Ps+rJ3nle/qbBTnc/4S5YQBDTNkJOoBDBythH01u/vJGZriZ0Wa8X+d1eI5VsBsLqPCIpBPLBg3G+mNWGnLIwJvm/pXy53154n3gzPA8IPF+scp4vXq9Bs0IVcPUqcrJ+7lZVt7cnGCsfFozGarmpBNhhBUxk5e79Wqc0MCuGSh+sHU3YhBbcuPzCPsU8rh+v/wXKTdqB/SiDiWv80Ll6/xSNWN92YCa1kW2MamrFW968y8JERBeuVKlYJfq0CnQqRWgg8et93bJAwfgFjMBN5G8ob9NUxq/HU5CKoBCSDl5vpy7FQCw3MaCcIsPgkqY4yEnqbB65/KfLkTiN28s0ZHQzSaDLJy7gwdLdhetK20SK0N+DzOAevG7P1y6mUsCwjTbBy0IqDNBnu8wgag/QO3vzSHD3u9T+GUQx0ObrI5SVxRVkg+ETXz7uVuYnR3X6FO5Dq4C/x15Z948wijLMbVLZHLq1IC99PLKmma0uJJpXrURzpN7C/Nm9iQnuFLYfnOIW1XXiKK3kzTZcWw+mXbKmvGAyhGaufWFnpzW3+pknoYHDze5r822X/1BM6+u1e14jm/Z3ThuvayJeIGVdEkWVI/9OczjPasMZfx9bubFBVA3s6ZmJFfRVuIIMPVreGolSbPe/7vKy7mpdZsMygl+F89VdHRu8HVNP7slF2spyoycQkvPIMbvE4+SpPBSRMv2D22K/CK0azw5kp8bUj/6rUjoq+hTOxA3OpMOj/FTUQ/4TOlJhzJDu83dV4J4kmBxNp0X+3DAWbtA/SG4IKThJiM9cblB5/xonNqSz9QXJBaBa+MbLcAtHgeL9rU+zvPZsZdajQ/ie9iPK+bSvciCsuLx6CbuPrzAhvo1etmnqfDoknY2IJyyesGxMmWM3RsbxbWG2tuUbTbqI4tNcfZj9YRmgH6XI5XzdoaX4AZ4ITWOv7335+bNlQ5rBw42OnVWGJ5Pa6DnXyluqeRIPpabqXbsxssHVPJcbnI3vuhKcKIQB0jfS3t5rNcn87qDp43Ml955USg6BaVjBCnxyBhzQUJVi40/LSBE71h0vypxofF4w1Oqd8RPTtSbul5miNzX9ryi+ippXr+kagncObJ40Mum047IJyPrBQ73ufyrjt7cTt72yCct9hpFqIJV8P6NXbL9s9D+JYVL57SUAZdpPiow/Y2AGnh7Du5RjWLe4PuGxuZVzhSTcugTADyZaZDjz+zjKXTbZq2MEaUQ2M5cGGFjo7Ci15dKG45OWN6UPGv4lU3RzdEsPDyLX33jG6OUJo1dVdiGl4Bw3lHK84ZcOkxAFHegA+fn7NBwzisTpoMIhIikHfpINnIOPy/C0n1JeAdbSggLPgKqiGyv1T1ogOgCXb4DifrIrs/W0gtRtFSsecIYI3fg03HSG/I6TNQ4owyi/6aAYRx77GOKt+ZJKn/wMItKxOMU+nmt6AeJ3j7hnmoh719CgRlbWFqTBupCmXMqT5S47dlx98v2RI1EctrPRrDBitLNNDpQW5SeB7JXEzvT9ouHa4hlXUiQxjYiV7w6k0XvCqHDvYcMnunk9GrGxFHGG+n51sTHHCNLnQ6MRJ5obwx/ARzPyV6duahoaSJ5cD2CjEpc53KEX2HA0whW0DAN/ryCYVuuwli9wEfrf3czYQdAvFy8Hrgv8aEnqHbgzs/sntKpEz6iMZ3+IVOMk47VTHGPF2bwxePiTYR3Jk63x+dsl7BtxRBZjRbmy8jrHYfmXbE0FltQ1fOB7sSTvALuc9TTX/K39t3fEOKSTKNEEE8G+lY+eZLE1ZlflqHyYgDlQlcu6vFWUTyaJSHA7bGMbwUm4GDwRPM2SbE9rsjDcfVWh0p6zrnUyCziQCNrgcXG4AEiZvUjXw8KKItexKaVTmaqWD+YXt4iRf118injbp7bImMNXLP2QchN7XZn/jre3UQ9nCt7X/PYrTPdvw1z6/gkbaDMgzctiKuX7+XSW2g3aRpcA9ntsbttbow7Cl6cY3mejV9IOSYweN/od/LU9fiylzRF3vjv1VuGMpxD1e2bHhjXpSWkJx5ehKXj7ZO9JTw6FxhT4T6sWRRxwWmTeolB4rLLEhny4sr84JZI0/2Se3HLlAxkfX6ekeU8J+NuLQn8cWRyV8DSt22IwY8Lm8Xo5m7cnGLKW7jP2CRrcW6FDXeDhB44+ezY0D3vuTmuj7v2Qxw9vtmsJMlsu2Qc4kPagxgZflf0TDDUJevadHYhwcvwCJ5o0c3DU3zE8UM1rU/ILT+okCaxcY7oiaRZrttrbZHHCH96Sbkx+ZG2eLvERAGkVK9TyFS/nNncPv/0q3t5sR3ZkC5bi3tYUY+74F0OlJWQREqMenBspPyTSL5dx701WnzDpxZ9HLYhD2Xb5etxskW500+uTRSuXRWjhU1JxurTRh4WZg+DOokZ6cT+DuGKTRN3JqEp4c6LVne89dLMNgdqyiRpMbhx1zmZbV0ksMqPD0n5tcST9jzQ7TIXNGLb+4NoMGRzckuJBf1snttVbxw60KalaHZ0KWtpGhSudHyn9J5v+cywhOdCG3hrew9N1hd0rSyKFunhJRuHxDGwFUHly8WVSu3BhmUjgynpUootcZQ3aFkd/OkNvn6dO5wEX5I2zHCXDemWQ8qZ+6+pUMrlXVmCUkrF69O/Ylq5ZCWIzfh3Kg5LAqJi1+Xcj4joid6GqDsJgfGX1Khjcm53JjoDgluHS2ZDT3QXPaVf4rtUBEQe8BhTheqWIncTc5+SC/pASTYsRNnogtY0/Ar5PiNxQazYrdgepx3yidgZEmYNgoHE15NNiXresVnzC95An5Yj7Yw8Gc8jfhndNUIqEu7cei8Px0jH5S4zx/q+3Cg5e7QM5H++j4aSSZp+5jL8K/zUsag=
*/