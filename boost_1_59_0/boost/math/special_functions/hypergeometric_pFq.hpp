
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HYPERGEOMETRIC_PFQ_HPP
#define BOOST_MATH_HYPERGEOMETRIC_PFQ_HPP

#include <boost/math/special_functions/detail/hypergeometric_pFq_checked_series.hpp>
#include <boost/math/tools/throw_exception.hpp>
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
            timed_iteration_terminator(std::uintmax_t i, double t) : max_iter(i), max_time(t), start_time(std::chrono::system_clock::now()) {}

            bool operator()(std::uintmax_t iter)const
            {
               if (iter > max_iter)
                  BOOST_MATH_THROW_EXCEPTION(boost::math::detail::pFq_termination_exception("pFq exceeded maximum permitted iterations."));
               if (std::chrono::duration<double>(std::chrono::system_clock::now() - start_time).count() > max_time)
                  BOOST_MATH_THROW_EXCEPTION(boost::math::detail::pFq_termination_exception("pFq exceeded maximum permitted evaluation time."));
               return false;
            }

            std::uintmax_t max_iter;
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

         long long scale = 0;
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
               long long scale = 0;
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
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
*/