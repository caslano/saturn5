
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
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
*/