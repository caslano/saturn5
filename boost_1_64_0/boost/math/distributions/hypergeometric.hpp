// Copyright 2008 Gautam Sewani
// Copyright 2008 John Maddock
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_HYPERGEOMETRIC_HPP
#define BOOST_MATH_DISTRIBUTIONS_HYPERGEOMETRIC_HPP

#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/hypergeometric_pdf.hpp>
#include <boost/math/distributions/detail/hypergeometric_cdf.hpp>
#include <boost/math/distributions/detail/hypergeometric_quantile.hpp>
#include <boost/math/special_functions/fpclassify.hpp>


namespace boost { namespace math {

   template <class RealType = double, class Policy = policies::policy<> >
   class hypergeometric_distribution
   {
   public:
      typedef RealType value_type;
      typedef Policy policy_type;

      hypergeometric_distribution(unsigned r, unsigned n, unsigned N) // Constructor.
         : m_n(n), m_N(N), m_r(r)
      {
         static const char* function = "boost::math::hypergeometric_distribution<%1%>::hypergeometric_distribution";
         RealType ret;
         check_params(function, &ret);
      }
      // Accessor functions.
      unsigned total()const
      {
         return m_N;
      }

      unsigned defective()const
      {
         return m_r;
      }

      unsigned sample_count()const
      {
         return m_n;
      }

      bool check_params(const char* function, RealType* result)const
      {
         if(m_r > m_N)
         {
            *result = boost::math::policies::raise_domain_error<RealType>(
               function, "Parameter r out of range: must be <= N but got %1%", static_cast<RealType>(m_r), Policy());
            return false;
         }
         if(m_n > m_N)
         {
            *result = boost::math::policies::raise_domain_error<RealType>(
               function, "Parameter n out of range: must be <= N but got %1%", static_cast<RealType>(m_n), Policy());
            return false;
         }
         return true;
      }
      bool check_x(unsigned x, const char* function, RealType* result)const
      {
         if(x < static_cast<unsigned>((std::max)(0, (int)(m_n + m_r) - (int)(m_N))))
         {
            *result = boost::math::policies::raise_domain_error<RealType>(
               function, "Random variable out of range: must be > 0 and > m + r - N but got %1%", static_cast<RealType>(x), Policy());
            return false;
         }
         if(x > (std::min)(m_r, m_n))
         {
            *result = boost::math::policies::raise_domain_error<RealType>(
               function, "Random variable out of range: must be less than both n and r but got %1%", static_cast<RealType>(x), Policy());
            return false;
         }
         return true;
      }

   private:
      // Data members:
      unsigned m_n;  // number of items picked
      unsigned m_N; // number of "total" items
      unsigned m_r; // number of "defective" items

   }; // class hypergeometric_distribution

   typedef hypergeometric_distribution<double> hypergeometric;

   template <class RealType, class Policy>
   inline const std::pair<unsigned, unsigned> range(const hypergeometric_distribution<RealType, Policy>& dist)
   { // Range of permissible values for random variable x.
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable:4267)
#endif
      unsigned r = dist.defective();
      unsigned n = dist.sample_count();
      unsigned N = dist.total();
      unsigned l = static_cast<unsigned>((std::max)(0, (int)(n + r) - (int)(N)));
      unsigned u = (std::min)(r, n);
      return std::pair<unsigned, unsigned>(l, u);
#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif
   }

   template <class RealType, class Policy>
   inline const std::pair<unsigned, unsigned> support(const hypergeometric_distribution<RealType, Policy>& d)
   { 
      return range(d);
   }

   template <class RealType, class Policy>
   inline RealType pdf(const hypergeometric_distribution<RealType, Policy>& dist, const unsigned& x)
   {
      static const char* function = "boost::math::pdf(const hypergeometric_distribution<%1%>&, const %1%&)";
      RealType result = 0;
      if(!dist.check_params(function, &result))
         return result;
      if(!dist.check_x(x, function, &result))
         return result;

      return boost::math::detail::hypergeometric_pdf<RealType>(
         x, dist.defective(), dist.sample_count(), dist.total(), Policy());
   }

   template <class RealType, class Policy, class U>
   inline RealType pdf(const hypergeometric_distribution<RealType, Policy>& dist, const U& x)
   {
      BOOST_MATH_STD_USING
      static const char* function = "boost::math::pdf(const hypergeometric_distribution<%1%>&, const %1%&)";
      RealType r = static_cast<RealType>(x);
      unsigned u = itrunc(r, typename policies::normalise<Policy, policies::rounding_error<policies::ignore_error> >::type());
      if(u != r)
      {
         return boost::math::policies::raise_domain_error<RealType>(
            function, "Random variable out of range: must be an integer but got %1%", r, Policy());
      }
      return pdf(dist, u);
   }

   template <class RealType, class Policy>
   inline RealType cdf(const hypergeometric_distribution<RealType, Policy>& dist, const unsigned& x)
   {
      static const char* function = "boost::math::cdf(const hypergeometric_distribution<%1%>&, const %1%&)";
      RealType result = 0;
      if(!dist.check_params(function, &result))
         return result;
      if(!dist.check_x(x, function, &result))
         return result;

      return boost::math::detail::hypergeometric_cdf<RealType>(
         x, dist.defective(), dist.sample_count(), dist.total(), false, Policy());
   }

   template <class RealType, class Policy, class U>
   inline RealType cdf(const hypergeometric_distribution<RealType, Policy>& dist, const U& x)
   {
      BOOST_MATH_STD_USING
      static const char* function = "boost::math::cdf(const hypergeometric_distribution<%1%>&, const %1%&)";
      RealType r = static_cast<RealType>(x);
      unsigned u = itrunc(r, typename policies::normalise<Policy, policies::rounding_error<policies::ignore_error> >::type());
      if(u != r)
      {
         return boost::math::policies::raise_domain_error<RealType>(
            function, "Random variable out of range: must be an integer but got %1%", r, Policy());
      }
      return cdf(dist, u);
   }

   template <class RealType, class Policy>
   inline RealType cdf(const complemented2_type<hypergeometric_distribution<RealType, Policy>, unsigned>& c)
   {
      static const char* function = "boost::math::cdf(const hypergeometric_distribution<%1%>&, const %1%&)";
      RealType result = 0;
      if(!c.dist.check_params(function, &result))
         return result;
      if(!c.dist.check_x(c.param, function, &result))
         return result;

      return boost::math::detail::hypergeometric_cdf<RealType>(
         c.param, c.dist.defective(), c.dist.sample_count(), c.dist.total(), true, Policy());
   }

   template <class RealType, class Policy, class U>
   inline RealType cdf(const complemented2_type<hypergeometric_distribution<RealType, Policy>, U>& c)
   {
      BOOST_MATH_STD_USING
      static const char* function = "boost::math::cdf(const hypergeometric_distribution<%1%>&, const %1%&)";
      RealType r = static_cast<RealType>(c.param);
      unsigned u = itrunc(r, typename policies::normalise<Policy, policies::rounding_error<policies::ignore_error> >::type());
      if(u != r)
      {
         return boost::math::policies::raise_domain_error<RealType>(
            function, "Random variable out of range: must be an integer but got %1%", r, Policy());
      }
      return cdf(complement(c.dist, u));
   }

   template <class RealType, class Policy>
   inline RealType quantile(const hypergeometric_distribution<RealType, Policy>& dist, const RealType& p)
   {
      BOOST_MATH_STD_USING // for ADL of std functions

         // Checking function argument
         RealType result = 0;
      const char* function = "boost::math::quantile(const hypergeometric_distribution<%1%>&, %1%)";
      if (false == dist.check_params(function, &result)) return result;
      if(false == detail::check_probability(function, p, &result, Policy())) return result;

      return static_cast<RealType>(detail::hypergeometric_quantile(p, RealType(1 - p), dist.defective(), dist.sample_count(), dist.total(), Policy()));
   } // quantile

   template <class RealType, class Policy>
   inline RealType quantile(const complemented2_type<hypergeometric_distribution<RealType, Policy>, RealType>& c)
   {
      BOOST_MATH_STD_USING // for ADL of std functions

      // Checking function argument
      RealType result = 0;
      const char* function = "quantile(const complemented2_type<hypergeometric_distribution<%1%>, %1%>&)";
      if (false == c.dist.check_params(function, &result)) return result;
      if(false == detail::check_probability(function, c.param, &result, Policy())) return result;

      return static_cast<RealType>(detail::hypergeometric_quantile(RealType(1 - c.param), c.param, c.dist.defective(), c.dist.sample_count(), c.dist.total(), Policy()));
   } // quantile

   template <class RealType, class Policy>
   inline RealType mean(const hypergeometric_distribution<RealType, Policy>& dist)
   {
      return static_cast<RealType>(dist.defective() * dist.sample_count()) / dist.total();
   } // RealType mean(const hypergeometric_distribution<RealType, Policy>& dist)

   template <class RealType, class Policy>
   inline RealType variance(const hypergeometric_distribution<RealType, Policy>& dist)
   {
      RealType r = static_cast<RealType>(dist.defective());
      RealType n = static_cast<RealType>(dist.sample_count());
      RealType N = static_cast<RealType>(dist.total());
      return n * r  * (N - r) * (N - n) / (N * N * (N - 1));
   } // RealType variance(const hypergeometric_distribution<RealType, Policy>& dist)

   template <class RealType, class Policy>
   inline RealType mode(const hypergeometric_distribution<RealType, Policy>& dist)
   {
      BOOST_MATH_STD_USING
      RealType r = static_cast<RealType>(dist.defective());
      RealType n = static_cast<RealType>(dist.sample_count());
      RealType N = static_cast<RealType>(dist.total());
      return floor((r + 1) * (n + 1) / (N + 2));
   }

   template <class RealType, class Policy>
   inline RealType skewness(const hypergeometric_distribution<RealType, Policy>& dist)
   {
      BOOST_MATH_STD_USING
      RealType r = static_cast<RealType>(dist.defective());
      RealType n = static_cast<RealType>(dist.sample_count());
      RealType N = static_cast<RealType>(dist.total());
      return (N - 2 * r) * sqrt(N - 1) * (N - 2 * n) / (sqrt(n * r * (N - r) * (N - n)) * (N - 2));
   } // RealType skewness(const hypergeometric_distribution<RealType, Policy>& dist)

   template <class RealType, class Policy>
   inline RealType kurtosis_excess(const hypergeometric_distribution<RealType, Policy>& dist)
   {
      RealType r = static_cast<RealType>(dist.defective());
      RealType n = static_cast<RealType>(dist.sample_count());
      RealType N = static_cast<RealType>(dist.total());
      RealType t1 = N * N * (N - 1) / (r * (N - 2) * (N - 3) * (N - r));
      RealType t2 = (N * (N + 1) - 6 * N * (N - r)) / (n * (N - n))
         + 3 * r * (N - r) * (N + 6) / (N * N) - 6;
      return t1 * t2;
   } // RealType kurtosis_excess(const hypergeometric_distribution<RealType, Policy>& dist)

   template <class RealType, class Policy>
   inline RealType kurtosis(const hypergeometric_distribution<RealType, Policy>& dist)
   {
      return kurtosis_excess(dist) + 3;
   } // RealType kurtosis_excess(const hypergeometric_distribution<RealType, Policy>& dist)
}} // namespaces

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // include guard

/* hypergeometric.hpp
ZLqFkzmGTKotU31Fw7Dpr6bDqRlOJgOZ1IBMXjiZUcjItZ4OJ7MUmToqr1fcH5Q55Ur7hmrB/Flxe7j8KUJG8vnTcNc6KjKsc/COW2Yo9iTsdWVtj3qwPsa2JznW+2ggv7dgIMZ5ruJjtmSfx9nzHe+zTi1wkzpf3mfudcZV/fRBJm5Sr6lx2PLe2it7yr9MApvAh2A8YRZf63hv5autOt1tNt2eqnOdLXujJ8O8FzhhhW+jpcAE5X+t53xiaHgnaf+G94Fu5zVWYaxg7GeKu47UY/zWK5nf6ffOvOvVO0TJT22i6p35vO0DbbPPnfUR73u5VhLspvx1t1KkTkrCdpdyi1V14I7q5GuC1IELIq8Diz8PXweuvM5RB+q411N1YFQCacNIHbjZWAeK3J6EYB24oNw60E7H8YTgc7D8LtOzggwlSWTil7cKJ9MlUYeTYl5HTZ4n/YyEthP1c5Lw47cB7XvN/cdN3f+Qdt2UFEsdF/oYZwVb2OT5yLjB8Xw4ekVc7TpdPmcp+W+806yapmeE8AzfvfI9sI80jVXnU/UaQQOVPVn3NfzuRuzsILfGekOX79eVTIzxmdLX0/GdMTV/auB6e7nejer8X7wpUuaHKPt8bx67kfb3Jpvag4RZ9nfTIvs8vUx92AF5ruc66++el4zf3xIObnoP9PzLc7MnM9pWjweec5NqbzH+KNnwXW4KI9uuI1UYpm9zp/xTiYGx8FPnEHmO4Fo7a5TMeypPauI+XNl/4p1PnvSRPKnvCLe+CtfQnpYw9xDmHHXep+/rpYH7rMJKc4SV5oyjHls8N2/WZDtrSvaIHq9kDnrnUZqvpDS4yoKKB4PQOKbNXzRvhnPdJAlzuj1IXMWvCPfNyt9+r/0c7yOCZ7jI7FT1Dp7kbu8sxF4P+xsp6rtOm5fx17BZqFsjsZtMgj5XvoxdJ/S0zqZO4PmMqJ9EPRfGfpIU3JK1my6jyj1Vu0u5E/f6uFG+cJfyJddLM7y37fti9cBN7pVzjscU2dO+rodyBlNgFLI9V5XscU4Nl7sof7JKgOndmwqvVvKrGadXxTzvY5WpnjD2xyFrrsN0HeGQkfrDVFeoPB2m5GI904nFHbRWPoGGuoLwjM+X/i4ao85/b43n3fwM5s9WtLG+cIazqYWdnrypC2chQzGqLXlxaJWsy6bcPMqtWLk1JG0JId8xn6j2x9RFSx1re01Wsn+zhhH6FXyDH8RHkv52phlgF0nHd+kZJZ+gv82c1yq1Tpnk21FbhrtZl2dR7RuTWtKHwjsUe/n7moftTzQ8E37ns1OBPmbcVF6R17ipvFZzAraq+LP3Z2bAfkDbQ8fdL5UBplNk/uBE6O1BOm/R5V9ey3NnT+dBQyRsH+FvlJ8WnqqeasZngDDN7wbHc/S4kungGWC9ZXo2dBgp+r7lTF2cze49P5k3f4ljncZdSq66nrv0jLL395T4U6miF3Xu3KmONvRzSu4CT0tPtHE+1Qvq/IWeFp4olQ/T7YTL/I/gtWNWy3waaWOOVPYt1iRSNJ/Rz1fKmr6ErfyqSs2RB1+ra3xLDjRyl0/93m6swuxkJRJWw5DrbA+5zhaYpOcfcQ9RK0g/lJpjZM/VmkEduKGevI+iqvs9Mf64KkzXivNXMa//K3724Ocy24+3nz861irVVm6NvYoVaHtmYgop36uTA+8x9oeC2qhnKc78LOn9oY6s1vtDGZ4tWf/V/V4Q99N6XV+dB+q5aKTCZOx8h9C5fwcaWOq4XXR4azDfZ/Kc3KqeCxRUgV5I+wHhlLu9qnU09yn5oabngbAi3y9KZI39Yclwpzrfy6hDqw3nqfMrrWb8VffFoEP7sKb9+4fo0UI=
*/