
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HYPERGEOMETRIC_PFQ_HPP
#define BOOST_MATH_HYPERGEOMETRIC_PFQ_HPP

#include <boost/config.hpp>

#if defined(BOOST_NO_CXX11_AUTO_DECLARATIONS) || defined(BOOST_NO_CXX11_LAMBDAS) || defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX) || defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST) || defined(BOOST_NO_CXX11_HDR_CHRONO)
# error "hypergeometric_pFq requires a C++11 compiler"
#endif

#include <boost/math/special_functions/detail/hypergeometric_pFq_checked_series.hpp>
#include <chrono>
#include <initializer_list>

namespace boost {
   namespace math {

      namespace detail {

         struct pFq_termination_exception : public std::runtime_error
         {
            pFq_termination_exception(const char* p) : std::runtime_error(p) {}
         };

         struct timed_iteration_terminator
         {
            timed_iteration_terminator(boost::uintmax_t i, double t) : max_iter(i), max_time(t), start_time(std::chrono::system_clock::now()) {}

            bool operator()(boost::uintmax_t iter)const
            {
               if (iter > max_iter)
                  boost::throw_exception(boost::math::detail::pFq_termination_exception("pFq exceeded maximum permitted iterations."));
               if (std::chrono::duration<double>(std::chrono::system_clock::now() - start_time).count() > max_time)
                  boost::throw_exception(boost::math::detail::pFq_termination_exception("pFq exceeded maximum permitted evaluation time."));
               return false;
            }

            boost::uintmax_t max_iter;
            double max_time;
            std::chrono::system_clock::time_point start_time;
         };

      }

      template <class Seq, class Real, class Policy>
      inline typename tools::promote_args<Real, typename Seq::value_type>::type hypergeometric_pFq(const Seq& aj, const Seq& bj, const Real& z, Real* p_abs_error, const Policy& pol)
      {
         typedef typename tools::promote_args<Real, typename Seq::value_type>::type result_type;
         typedef typename policies::evaluation<result_type, Policy>::type value_type;
         typedef typename policies::normalise<
            Policy,
            policies::promote_float<false>,
            policies::promote_double<false>,
            policies::discrete_quantile<>,
            policies::assert_undefined<> >::type forwarding_policy;

         BOOST_MATH_STD_USING

         int scale = 0;
         std::pair<value_type, value_type> r = boost::math::detail::hypergeometric_pFq_checked_series_impl(aj, bj, value_type(z), pol, boost::math::detail::iteration_terminator(boost::math::policies::get_max_series_iterations<forwarding_policy>()), scale);
         r.first *= exp(Real(scale));
         r.second *= exp(Real(scale));
         if (p_abs_error)
            *p_abs_error = static_cast<Real>(r.second) * boost::math::tools::epsilon<Real>();
         return policies::checked_narrowing_cast<result_type, Policy>(r.first, "boost::math::hypergeometric_pFq<%1%>(%1%,%1%,%1%)");
      }

      template <class Seq, class Real>
      inline typename tools::promote_args<Real, typename Seq::value_type>::type hypergeometric_pFq(const Seq& aj, const Seq& bj, const Real& z, Real* p_abs_error = 0)
      {
         return hypergeometric_pFq(aj, bj, z, p_abs_error, boost::math::policies::policy<>());
      }

      template <class R, class Real, class Policy>
      inline typename tools::promote_args<Real, R>::type hypergeometric_pFq(const std::initializer_list<R>& aj, const std::initializer_list<R>& bj, const Real& z, Real* p_abs_error, const Policy& pol)
      {
         return hypergeometric_pFq<std::initializer_list<R>, Real, Policy>(aj, bj, z, p_abs_error, pol);
      }
      
      template <class R, class Real>
      inline typename tools::promote_args<Real, R>::type  hypergeometric_pFq(const std::initializer_list<R>& aj, const std::initializer_list<R>& bj, const Real& z, Real* p_abs_error = 0)
      {
         return hypergeometric_pFq<std::initializer_list<R>, Real>(aj, bj, z, p_abs_error);
      }

      template <class T>
      struct scoped_precision
      {
         scoped_precision(unsigned p)
         {
            old_p = T::default_precision();
            T::default_precision(p);
         }
         ~scoped_precision()
         {
            T::default_precision(old_p);
         }
         unsigned old_p;
      };

      template <class Seq, class Real, class Policy>
      Real hypergeometric_pFq_precision(const Seq& aj, const Seq& bj, Real z, unsigned digits10, double timeout, const Policy& pol)
      {
         unsigned current_precision = digits10 + 5;

         for (auto ai = aj.begin(); ai != aj.end(); ++ai)
         {
            current_precision = (std::max)(current_precision, ai->precision());
         }
         for (auto bi = bj.begin(); bi != bj.end(); ++bi)
         {
            current_precision = (std::max)(current_precision, bi->precision());
         }
         current_precision = (std::max)(current_precision, z.precision());

         Real r, norm;
         std::vector<Real> aa(aj), bb(bj);
         do
         {
            scoped_precision<Real> p(current_precision);
            for (auto ai = aa.begin(); ai != aa.end(); ++ai)
               ai->precision(current_precision);
            for (auto bi = bb.begin(); bi != bb.end(); ++bi)
               bi->precision(current_precision);
            z.precision(current_precision);
            try
            {
               int scale = 0;
               std::pair<Real, Real> rp = boost::math::detail::hypergeometric_pFq_checked_series_impl(aa, bb, z, pol, boost::math::detail::timed_iteration_terminator(boost::math::policies::get_max_series_iterations<Policy>(), timeout), scale);
               rp.first *= exp(Real(scale));
               rp.second *= exp(Real(scale));

               r = rp.first;
               norm = rp.second;

               unsigned cancellation;
               try {
                  cancellation = itrunc(log10(abs(norm / r)));
               }
               catch (const boost::math::rounding_error&)
               {
                  // Happens when r is near enough zero:
                  cancellation = UINT_MAX;
               }
               if (cancellation >= current_precision - 1)
               {
                  current_precision *= 2;
                  continue;
               }
               unsigned precision_obtained = current_precision - 1 - cancellation;
               if (precision_obtained < digits10)
               {
                  current_precision += digits10 - precision_obtained + 5;
               }
               else
                  break;
            }
            catch (const boost::math::evaluation_error&)
            {
               current_precision *= 2;
            }
            catch (const detail::pFq_termination_exception& e)
            {
               //
               // Either we have exhausted the number of series iterations, or the timeout.
               // Either way we quit now.
               throw boost::math::evaluation_error(e.what());
            }
         } while (true);

         return r;
      }
      template <class Seq, class Real>
      Real hypergeometric_pFq_precision(const Seq& aj, const Seq& bj, const Real& z, unsigned digits10, double timeout = 0.5)
      {
         return hypergeometric_pFq_precision(aj, bj, z, digits10, timeout, boost::math::policies::policy<>());
      }

      template <class Real, class Policy>
      Real hypergeometric_pFq_precision(const std::initializer_list<Real>& aj, const std::initializer_list<Real>& bj, const Real& z, unsigned digits10, double timeout, const Policy& pol)
      {
         return hypergeometric_pFq_precision< std::initializer_list<Real>, Real>(aj, bj, z, digits10, timeout, pol);
      }
      template <class Real>
      Real hypergeometric_pFq_precision(const std::initializer_list<Real>& aj, const std::initializer_list<Real>& bj, const Real& z, unsigned digits10, double timeout = 0.5)
      {
         return hypergeometric_pFq_precision< std::initializer_list<Real>, Real>(aj, bj, z, digits10, timeout, boost::math::policies::policy<>());
      }

   }
} // namespaces

#endif // BOOST_MATH_BESSEL_ITERATORS_HPP

/* hypergeometric_pFq.hpp
P5SfZsLHjguHBz8vhqMyWqvTOxbtwuvg6kHifuVSPKO1ukwxf5ogj+Jf1Xh60mt0h5Pgsxnyx7dw2TLrIdJz86913b/oaqPhIvyn7nY84S687FTx/TF47gn7XTzKrsfDT0neczCccB29c5/6DVxXoe6WehK/H9xKH6b7l7LvZXhyDnw+D7673Lq1+vizxf3Erd7vOTpGTljdCy4ZYX8K8TOXvpF6CD2a/y9/ke5bqC/kFvXKl+iaeMWmHLreC/r5ukXrVv59AH+TDzLsq9N4Hzypntv4JT9+tY3r0WuHROgFdJoLxUXrXabhIyUP0v9vpZP9FqfOTZ/cz89e5BeleGR/1z8qYp1k4wKvNmd5jwfg7kvUN++G2/9HZ/2an91Gd74XH3OsEo8ydsiHa9T76DxJEd8XTedXU+Uh+n7GCPOkvp56iWMZHB2Cz9RlKuGGavWDbr3wnp/wi876457Rj3KL55c/2xfoaw2JuzexYzy/vTpOVpz1yIbiy6vgx2H6FE7y70hCcN/d5qsYT8ymZzbBkdvgtW/EsUvwpIu8Bz0lZwPdphs8cyj8QCdetIcOMME6AB3E0+PbqifSbw83r5fhHeavqg5++8E4ut/qm/B7utCqN9xvlTw7St7wneyg9fo47zcOe7znlda3Eh/yJusTnkWXUXecaj+ASv0jmR/Bk/TXmmlw9mTfLbzfhr6jTrSNDsVvm4+Gn6bRQ16HR+6hs61Ql23L/hrtZ3BtjPWl6IHv4HlP0D/Y94YT6X1d6ZDb5es/xFnzmTXMdX5TP7uAvpQAb1+gLpRF578jTr2XTlUFJz9hP5W/8PdPxf0SetsEfYuHyH+V8Lt5T4GPQgfh8Sl0jAZ9YVfRL+K9R5Z4/AAd9s244PoH8HD9+pXD6dP2pVhMt606AQ99zfPM06dxJP+9xRE/q4uuJzaIPUX3TUiwfkyVOsZN5vtMvGCi+J/LP77Da06Bc+m+/20rE7zPDvUEOLG5Xr5t0A+t/7RzMfv+Wdxr4kcH8Pwx/F5fVOWb7eAgOt1IuPBmdZRRnu8T7zXB/L/EL+C0qfF4o/Vf0t7Q5/A0fJ7H/+hCq/Ht/S/gyT/GBUf7rexfhh8N0Uf7knrUTjpEPp4gbtVONh5HwbdH2r/vev3t5+EX7G8zXTgZfst/mF6bhwefSy+Bn9svpYtdFa3j4EFD1dF/C84vrKZjn6s+tABvTNYXqi+jere+4jn2q1kB5/0k31QF1ysSxyI/s6N74aQn5eOH7UPysPcT3+sHe89i4xjhp5n6sm4xj8fCMd+ow9j/qvIt8/MY3eMw47vWd9WZ7Mr62g3sL2cyPTnL87XBv8TZrJvx4YfFl+h+ext833YbHvxnDL2ObvZjRN2EfZ5Dv52mvyYb7vxF3OjV1nX0ScSIM8fgzS1w00r9nPB5ZQ/zaVxa7rOOWr54b7+nuTd5zrC8tli+gWPKyo0n+5jQTFcslkf6i8Mh/CYdrh8oj92NT29lb/Gt7L8K99NZS62n3IB/VjjGT5e3T4mupwp3Pw7vvGs8D4Nv09ynEQ5bIS6cp34iTqXsomt/x95eZ8en2qdwjL54fVnza+WZR43nfzwiiJuuf7d+GvtFNbSlr7Gz0nH6DaLrOr5Dv+qtjpNnvGPYZcd4+7fJ43DZcvOZuUsdOqx+dRycpg4+O/rd/cPiVwXdwDgtLo6oI9L55sDjt8bY/0f+nEN3j7MuTT94qR87/JoOepG4U0InwC8WR/kmnpcyh1/X0mfa2XcMP280v6E97O0vfVnF4na5evkUcfhvfk5nb9lNV/qDXwyhNzzIjvbgyW08T3QfrlfD9kGAL1f7O/GuxPWrS3xfKK4U/CC/vos=
*/