///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HYPERGEOMETRIC_PFQ_SERIES_HPP_
#define BOOST_HYPERGEOMETRIC_PFQ_SERIES_HPP_

#ifndef BOOST_MATH_PFQ_MAX_B_TERMS
#  define BOOST_MATH_PFQ_MAX_B_TERMS 5
#endif

#include <boost/array.hpp>
#include <boost/math/special_functions/detail/hypergeometric_series.hpp>

  namespace boost { namespace math { namespace detail {

     template <class Seq, class Real>
     unsigned set_crossover_locations(const Seq& aj, const Seq& bj, const Real& z, unsigned int* crossover_locations)
     {
        BOOST_MATH_STD_USING
        unsigned N_terms = 0;

        if(aj.size() == 1 && bj.size() == 1)
        {
           //
           // For 1F1 we can work out where the peaks in the series occur,
           //  which is to say when:
           //
           // (a + k)z / (k(b + k)) == +-1
           //
           // Then we are at either a maxima or a minima in the series, and the
           // last such point must be a maxima since the series is globally convergent.
           // Potentially then we are solving 2 quadratic equations and have up to 4
           // solutions, any solutions which are complex or negative are discarded,
           // leaving us with 4 options:
           //
           // 0 solutions: The series is directly convergent.
           // 1 solution : The series diverges to a maxima before converging.
           // 2 solutions: The series is initially convergent, followed by divergence to a maxima before final convergence.
           // 3 solutions: The series diverges to a maxima, converges to a minima before diverging again to a second maxima before final convergence.
           // 4 solutions: The series converges to a minima before diverging to a maxima, converging to a minima, diverging to a second maxima and then converging.
           //
           // The first 2 situations are adequately handled by direct series evaluation, while the 2,3 and 4 solutions are not.
           //
           Real a = *aj.begin();
           Real b = *bj.begin();
           Real sq = 4 * a * z + b * b - 2 * b * z + z * z;
           if (sq >= 0)
           {
              Real t = (-sqrt(sq) - b + z) / 2;
              if (t >= 0)
              {
                 crossover_locations[N_terms] = itrunc(t);
                 ++N_terms;
              }
              t = (sqrt(sq) - b + z) / 2;
              if (t >= 0)
              {
                 crossover_locations[N_terms] = itrunc(t);
                 ++N_terms;
              }
           }
           sq = -4 * a * z + b * b + 2 * b * z + z * z;
           if (sq >= 0)
           {
              Real t = (-sqrt(sq) - b - z) / 2;
              if (t >= 0)
              {
                 crossover_locations[N_terms] = itrunc(t);
                 ++N_terms;
              }
              t = (sqrt(sq) - b - z) / 2;
              if (t >= 0)
              {
                 crossover_locations[N_terms] = itrunc(t);
                 ++N_terms;
              }
           }
           std::sort(crossover_locations, crossover_locations + N_terms, std::less<Real>());
           //
           // Now we need to discard every other terms, as these are the minima:
           //
           switch (N_terms)
           {
           case 0:
           case 1:
              break;
           case 2:
              crossover_locations[0] = crossover_locations[1];
              --N_terms;
              break;
           case 3:
              crossover_locations[1] = crossover_locations[2];
              --N_terms;
              break;
           case 4:
              crossover_locations[0] = crossover_locations[1];
              crossover_locations[1] = crossover_locations[3];
              N_terms -= 2;
              break;
           }
        }
        else
        {
           unsigned n = 0;
           for (auto bi = bj.begin(); bi != bj.end(); ++bi, ++n)
           {
              crossover_locations[n] = *bi >= 0 ? 0 : itrunc(-*bi) + 1;
           }
           std::sort(crossover_locations, crossover_locations + bj.size(), std::less<Real>());
           N_terms = (unsigned)bj.size();
        }
        return N_terms;
     }

     template <class Seq, class Real, class Policy, class Terminal>
     std::pair<Real, Real> hypergeometric_pFq_checked_series_impl(const Seq& aj, const Seq& bj, const Real& z, const Policy& pol, const Terminal& termination, int& log_scale)
     {
        BOOST_MATH_STD_USING
        Real result = 1;
        Real abs_result = 1;
        Real term = 1;
        Real term0 = 0;
        Real tol = boost::math::policies::get_epsilon<Real, Policy>();
        boost::uintmax_t k = 0;
        Real upper_limit(sqrt(boost::math::tools::max_value<Real>())), diff;
        Real lower_limit(1 / upper_limit);
        int log_scaling_factor = itrunc(boost::math::tools::log_max_value<Real>()) - 2;
        Real scaling_factor = exp(Real(log_scaling_factor));
        Real term_m1;
        int local_scaling = 0;

        if ((aj.size() == 1) && (bj.size() == 0))
        {
           if (fabs(z) > 1)
           {
              if ((z > 0) && (floor(*aj.begin()) != *aj.begin()))
              {
                 Real r = policies::raise_domain_error("boost::math::hypergeometric_pFq", "Got p == 1 and q == 0 and |z| > 1, result is imaginary", z, pol);
                 return std::make_pair(r, r);
              }
              std::pair<Real, Real> r = hypergeometric_pFq_checked_series_impl(aj, bj, Real(1 / z), pol, termination, log_scale);
              Real mul = pow(-z, -*aj.begin());
              r.first *= mul;
              r.second *= mul;
              return r;
           }
        }

        if (aj.size() > bj.size())
        {
           if (aj.size() == bj.size() + 1)
           {
              if (fabs(z) > 1)
              {
                 Real r = policies::raise_domain_error("boost::math::hypergeometric_pFq", "Got p == q+1 and |z| > 1, series does not converge", z, pol);
                 return std::make_pair(r, r);
              }
              if (fabs(z) == 1)
              {
                 Real s = 0;
                 for (auto i = bj.begin(); i != bj.end(); ++i)
                    s += *i;
                 for (auto i = aj.begin(); i != aj.end(); ++i)
                    s -= *i;
                 if ((z == 1) && (s <= 0))
                 {
                    Real r = policies::raise_domain_error("boost::math::hypergeometric_pFq", "Got p == q+1 and |z| == 1, in a situation where the series does not converge", z, pol);
                    return std::make_pair(r, r);
                 }
                 if ((z == -1) && (s <= -1))
                 {
                    Real r = policies::raise_domain_error("boost::math::hypergeometric_pFq", "Got p == q+1 and |z| == 1, in a situation where the series does not converge", z, pol);
                    return std::make_pair(r, r);
                 }
              }
           }
           else
           {
              Real r = policies::raise_domain_error("boost::math::hypergeometric_pFq", "Got p > q+1, series does not converge", z, pol);
              return std::make_pair(r, r);
           }
        }

        while (!termination(k))
        {
           for (auto ai = aj.begin(); ai != aj.end(); ++ai)
           {
              term *= *ai + k;
           }
           if (term == 0)
           {
              // There is a negative integer in the aj's:
              return std::make_pair(result, abs_result);
           }
           for (auto bi = bj.begin(); bi != bj.end(); ++bi)
           {
              if (*bi + k == 0)
              {
                 // The series is undefined:
                 result = boost::math::policies::raise_domain_error("boost::math::hypergeometric_pFq<%1%>", "One of the b values was the negative integer %1%", *bi, pol);
                 return std::make_pair(result, result);
              }
              term /= *bi + k;
           }
           term *= z;
           ++k;
           term /= k;
           //std::cout << k << " " << *bj.begin() + k << " " << result << " " << term << /*" " << term_at_k(*aj.begin(), *bj.begin(), z, k, pol) <<*/ std::endl;
           result += term;
           abs_result += abs(term);
           //std::cout << "k = " << k << " term = " << term * exp(log_scale) << " result = " << result * exp(log_scale) << " abs_result = " << abs_result * exp(log_scale) << std::endl;

           //
           // Rescaling:
           //
           if (fabs(abs_result) >= upper_limit)
           {
              abs_result /= scaling_factor;
              result /= scaling_factor;
              term /= scaling_factor;
              log_scale += log_scaling_factor;
              local_scaling += log_scaling_factor;
           }
           if (fabs(abs_result) < lower_limit)
           {
              abs_result *= scaling_factor;
              result *= scaling_factor;
              term *= scaling_factor;
              log_scale -= log_scaling_factor;
              local_scaling -= log_scaling_factor;
           }

           if ((abs(result * tol) > abs(term)) && (abs(term0) > abs(term)))
              break;
           if (abs_result * tol > abs(result))
           {
              // We have no correct bits in the result... just give up!
              result = boost::math::policies::raise_evaluation_error("boost::math::hypergeometric_pFq<%1%>", "Cancellation is so severe that no bits in the reuslt are correct, last result was %1%", Real(result * exp(Real(log_scale))), pol);
              return std::make_pair(result, result);
           }
           term0 = term;
        }
        //std::cout << "result = " << result << std::endl;
        //std::cout << "local_scaling = " << local_scaling << std::endl;
        //std::cout << "Norm result = " << std::setprecision(35) << boost::multiprecision::mpfr_float_50(result) * exp(boost::multiprecision::mpfr_float_50(local_scaling)) << std::endl;
        //
        // We have to be careful when one of the b's crosses the origin:
        //
        if(bj.size() > BOOST_MATH_PFQ_MAX_B_TERMS)
           policies::raise_domain_error<Real>("boost::math::hypergeometric_pFq<%1%>(Seq, Seq, %1%)", 
              "The number of b terms must be less than the value of BOOST_MATH_PFQ_MAX_B_TERMS (" BOOST_STRINGIZE(BOOST_MATH_PFQ_MAX_B_TERMS)  "), but got %1%.",
              Real(bj.size()), pol);

        unsigned crossover_locations[BOOST_MATH_PFQ_MAX_B_TERMS];

        unsigned N_crossovers = set_crossover_locations(aj, bj, z, crossover_locations);

        bool terminate = false;   // Set to true if one of the a's passes through the origin and terminates the series.

        for (unsigned n = 0; n < N_crossovers; ++n)
        {
           if (k < crossover_locations[n])
           {
              for (auto ai = aj.begin(); ai != aj.end(); ++ai)
              {
                 if ((*ai < 0) && (floor(*ai) == *ai) && (*ai > crossover_locations[n]))
                    return std::make_pair(result, abs_result);  // b's will never cross the origin!
              }
              //
              // local results:
              //
              Real loop_result = 0;
              Real loop_abs_result = 0;
              int loop_scale = 0;
              //
              // loop_error_scale will be used to increase the size of the error
              // estimate (absolute sum), based on the errors inherent in calculating 
              // the pochhammer symbols.
              //
              Real loop_error_scale = 0;
              //boost::multiprecision::mpfi_float err_est = 0;
              //
              // b hasn't crossed the origin yet and the series may spring back into life at that point
              // so we need to jump forward to that term and then evaluate forwards and backwards from there:
              //
              unsigned s = crossover_locations[n];
              boost::uintmax_t backstop = k;
              int s1(1), s2(1);
              term = 0;
              for (auto ai = aj.begin(); ai != aj.end(); ++ai)
              {
                 if ((floor(*ai) == *ai) && (*ai < 0) && (-*ai <= s))
                 {
                    // One of the a terms has passed through zero and terminated the series:
                    terminate = true;
                    break;
                 }
                 else
                 {
                    int ls = 1;
                    Real p = log_pochhammer(*ai, s, pol, &ls);
                    s1 *= ls;
                    term += p;
                    loop_error_scale = (std::max)(p, loop_error_scale);
                    //err_est += boost::multiprecision::mpfi_float(p);
                 }
              }
              //std::cout << "term = " << term << std::endl;
              if (terminate)
                 break;
              for (auto bi = bj.begin(); bi != bj.end(); ++bi)
              {
                 int ls = 1;
                 Real p = log_pochhammer(*bi, s, pol, &ls);
                 s2 *= ls;
                 term -= p;
                 loop_error_scale = (std::max)(p, loop_error_scale);
                 //err_est -= boost::multiprecision::mpfi_float(p);
              }
              //std::cout << "term = " << term << std::endl;
              Real p = lgamma(Real(s + 1), pol);
              term -= p;
              loop_error_scale = (std::max)(p, loop_error_scale);
              //err_est -= boost::multiprecision::mpfi_float(p);
              p = s * log(fabs(z));
              term += p;
              loop_error_scale = (std::max)(p, loop_error_scale);
              //err_est += boost::multiprecision::mpfi_float(p);
              //err_est = exp(err_est);
              //std::cout << err_est << std::endl;
              //
              // Convert loop_error scale to the absolute error
              // in term after exp is applied:
              //
              loop_error_scale *= tools::epsilon<Real>();
              //
              // Convert to relative error after exp:
              //
              loop_error_scale = fabs(expm1(loop_error_scale));
              //
              // Convert to multiplier for the error term:
              //
              loop_error_scale /= tools::epsilon<Real>();

              if (z < 0)
                 s1 *= (s & 1 ? -1 : 1);

              if (term <= tools::log_min_value<Real>())
              {
                 // rescale if we can:
                 int scale = itrunc(floor(term - tools::log_min_value<Real>()) - 2);
                 term -= scale;
                 loop_scale += scale;
              }
               if (term > 10)
               {
                  int scale = itrunc(floor(term));
                  term -= scale;
                  loop_scale += scale;
               }
               //std::cout << "term = " << term << std::endl;
               term = s1 * s2 * exp(term);
               //std::cout << "term = " << term << std::endl;
               //std::cout << "loop_scale = " << loop_scale << std::endl;
               k = s;
               term0 = term;
               int saved_loop_scale = loop_scale;
               bool terms_are_growing = true;
               bool trivial_small_series_check = false;
               do
               {
                  loop_result += term;
                  loop_abs_result += fabs(term);
                  //std::cout << "k = " << k << " term = " << term * exp(loop_scale) << " result = " << loop_result * exp(loop_scale) << " abs_result = " << loop_abs_result * exp(loop_scale) << std::endl;
                  if (fabs(loop_result) >= upper_limit)
                  {
                     loop_result /= scaling_factor;
                     loop_abs_result /= scaling_factor;
                     term /= scaling_factor;
                     loop_scale += log_scaling_factor;
                  }
                  if (fabs(loop_result) < lower_limit)
                  {
                     loop_result *= scaling_factor;
                     loop_abs_result *= scaling_factor;
                     term *= scaling_factor;
                     loop_scale -= log_scaling_factor;
                  }
                  term_m1 = term;
                  for (auto ai = aj.begin(); ai != aj.end(); ++ai)
                  {
                     term *= *ai + k;
                  }
                  if (term == 0)
                  {
                     // There is a negative integer in the aj's:
                     return std::make_pair(result, abs_result);
                  }
                  for (auto bi = bj.begin(); bi != bj.end(); ++bi)
                  {
                     if (*bi + k == 0)
                     {
                        // The series is undefined:
                        result = boost::math::policies::raise_domain_error("boost::math::hypergeometric_pFq<%1%>", "One of the b values was the negative integer %1%", *bi, pol);
                        return std::make_pair(result, result);
                     }
                     term /= *bi + k;
                  }
                  term *= z / (k + 1);

                  ++k;
                  diff = fabs(term / loop_result);
                  terms_are_growing = fabs(term) > fabs(term_m1);
                  if (!trivial_small_series_check && !terms_are_growing)
                  {
                     //
                     // Now that we have started to converge, check to see if the value of
                     // this local sum is trivially small compared to the result.  If so
                     // abort this part of the series.
                     //
                     trivial_small_series_check = true;
                     Real d; 
                     if (loop_scale > local_scaling)
                     {
                        int rescale = local_scaling - loop_scale;
                        if (rescale < tools::log_min_value<Real>())
                           d = 1;  // arbitrary value, we want to keep going
                        else
                           d = fabs(term / (result * exp(Real(rescale))));
                     }
                     else
                     {
                        int rescale = loop_scale - local_scaling;
                        if (rescale < tools::log_min_value<Real>())
                           d = 0;  // terminate this loop
                        else
                           d = fabs(term * exp(Real(rescale)) / result);
                     }
                     if (d < boost::math::policies::get_epsilon<Real, Policy>())
                        break;
                  }
               } while (!termination(k - s) && ((diff > boost::math::policies::get_epsilon<Real, Policy>()) || terms_are_growing));

               //std::cout << "Norm loop result = " << std::setprecision(35) << boost::multiprecision::mpfr_float_50(loop_result)* exp(boost::multiprecision::mpfr_float_50(loop_scale)) << std::endl;
               //
               // We now need to combine the results of the first series summation with whatever
               // local results we have now.  First though, rescale abs_result by loop_error_scale
               // to factor in the error in the pochhammer terms at the start of this block:
               //
               boost::uintmax_t next_backstop = k;
               loop_abs_result += loop_error_scale * fabs(loop_result);
               if (loop_scale > local_scaling)
               {
                  //
                  // Need to shrink previous result:
                  //
                  int rescale = local_scaling - loop_scale;
                  local_scaling = loop_scale;
                  log_scale -= rescale;
                  Real ex = exp(Real(rescale));
                  result *= ex;
                  abs_result *= ex;
                  result += loop_result;
                  abs_result += loop_abs_result;
               }
               else if (local_scaling > loop_scale)
               {
                  //
                  // Need to shrink local result:
                  //
                  int rescale = loop_scale - local_scaling;
                  Real ex = exp(Real(rescale));
                  loop_result *= ex;
                  loop_abs_result *= ex;
                  result += loop_result;
                  abs_result += loop_abs_result;
               }
               else
               {
                  result += loop_result;
                  abs_result += loop_abs_result;
               }
               //
               // Now go backwards as well:
               //
               k = s;
               term = term0;
               loop_result = 0;
               loop_abs_result = 0;
               loop_scale = saved_loop_scale;
               trivial_small_series_check = false;
               do
               {
                  --k;
                  if (k == backstop)
                     break;
                  term_m1 = term;
                  for (auto ai = aj.begin(); ai != aj.end(); ++ai)
                  {
                     term /= *ai + k;
                  }
                  for (auto bi = bj.begin(); bi != bj.end(); ++bi)
                  {
                     if (*bi + k == 0)
                     {
                        // The series is undefined:
                        result = boost::math::policies::raise_domain_error("boost::math::hypergeometric_pFq<%1%>", "One of the b values was the negative integer %1%", *bi, pol);
                        return std::make_pair(result, result);
                     }
                     term *= *bi + k;
                  }
                  term *= (k + 1) / z;
                  loop_result += term;
                  loop_abs_result += fabs(term);

                  if (!trivial_small_series_check && (fabs(term) < fabs(term_m1)))
                  {
                     //
                     // Now that we have started to converge, check to see if the value of
                     // this local sum is trivially small compared to the result.  If so
                     // abort this part of the series.
                     //
                     trivial_small_series_check = true;
                     Real d;
                     if (loop_scale > local_scaling)
                     {
                        int rescale = local_scaling - loop_scale;
                        if (rescale < tools::log_min_value<Real>())
                           d = 1;  // keep going
                        else
                           d = fabs(term / (result * exp(Real(rescale))));
                     }
                     else
                     {
                        int rescale = loop_scale - local_scaling;
                        if (rescale < tools::log_min_value<Real>())
                           d = 0;  // stop, underflow
                        else
                           d = fabs(term * exp(Real(rescale)) / result);
                     }
                     if (d < boost::math::policies::get_epsilon<Real, Policy>())
                        break;
                  }

                  //std::cout << "k = " << k << " result = " << result << " abs_result = " << abs_result << std::endl;
                  if (fabs(loop_result) >= upper_limit)
                  {
                     loop_result /= scaling_factor;
                     loop_abs_result /= scaling_factor;
                     term /= scaling_factor;
                     loop_scale += log_scaling_factor;
                  }
                  if (fabs(loop_result) < lower_limit)
                  {
                     loop_result *= scaling_factor;
                     loop_abs_result *= scaling_factor;
                     term *= scaling_factor;
                     loop_scale -= log_scaling_factor;
                  }
                  diff = fabs(term / loop_result);
               } while (!termination(s - k) && ((diff > boost::math::policies::get_epsilon<Real, Policy>()) || (fabs(term) > fabs(term_m1))));

               //std::cout << "Norm loop result = " << std::setprecision(35) << boost::multiprecision::mpfr_float_50(loop_result)* exp(boost::multiprecision::mpfr_float_50(loop_scale)) << std::endl;
               //
               // We now need to combine the results of the first series summation with whatever
               // local results we have now.  First though, rescale abs_result by loop_error_scale
               // to factor in the error in the pochhammer terms at the start of this block:
               //
               loop_abs_result += loop_error_scale * fabs(loop_result);
               //
               if (loop_scale > local_scaling)
               {
                  //
                  // Need to shrink previous result:
                  //
                  int rescale = local_scaling - loop_scale;
                  local_scaling = loop_scale;
                  log_scale -= rescale;
                  Real ex = exp(Real(rescale));
                  result *= ex;
                  abs_result *= ex;
                  result += loop_result;
                  abs_result += loop_abs_result;
               }
               else if (local_scaling > loop_scale)
               {
                  //
                  // Need to shrink local result:
                  //
                  int rescale = loop_scale - local_scaling;
                  Real ex = exp(Real(rescale));
                  loop_result *= ex;
                  loop_abs_result *= ex;
                  result += loop_result;
                  abs_result += loop_abs_result;
               }
               else
               {
                  result += loop_result;
                  abs_result += loop_abs_result;
               }
               //
               // Reset k to the largest k we reached
               //
               k = next_backstop;
           }
        }

        return std::make_pair(result, abs_result);
     }

     struct iteration_terminator
     {
        iteration_terminator(boost::uintmax_t i) : m(i) {}

        bool operator()(boost::uintmax_t v) const { return v >= m; }

        boost::uintmax_t m;
     };

     template <class Seq, class Real, class Policy>
     Real hypergeometric_pFq_checked_series_impl(const Seq& aj, const Seq& bj, const Real& z, const Policy& pol, int& log_scale)
     {
        BOOST_MATH_STD_USING
        iteration_terminator term(boost::math::policies::get_max_series_iterations<Policy>());
        std::pair<Real, Real> result = hypergeometric_pFq_checked_series_impl(aj, bj, z, pol, term, log_scale);
        //
        // Check to see how many digits we've lost, if it's more than half, raise an evaluation error -
        // this is an entirely arbitrary cut off, but not unreasonable.
        //
        if (result.second * sqrt(boost::math::policies::get_epsilon<Real, Policy>()) > abs(result.first))
        {
           return boost::math::policies::raise_evaluation_error("boost::math::hypergeometric_pFq<%1%>", "Cancellation is so severe that fewer than half the bits in the result are correct, last result was %1%", Real(result.first * exp(Real(log_scale))), pol);
        }
        return result.first;
     }

     template <class Real, class Policy>
     inline Real hypergeometric_1F1_checked_series_impl(const Real& a, const Real& b, const Real& z, const Policy& pol, int& log_scale)
     {
        boost::array<Real, 1> aj = { a };
        boost::array<Real, 1> bj = { b };
        return hypergeometric_pFq_checked_series_impl(aj, bj, z, pol, log_scale);
     }

  } } } // namespaces

#endif // BOOST_HYPERGEOMETRIC_PFQ_SERIES_HPP_

/* hypergeometric_pFq_checked_series.hpp
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
*/