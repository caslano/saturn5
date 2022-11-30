///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_1F1_BESSEL_HPP
#define BOOST_MATH_HYPERGEOMETRIC_1F1_BESSEL_HPP

#include <boost/math/tools/series.hpp>
#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/laguerre.hpp>
#include <boost/math/special_functions/detail/hypergeometric_pFq_checked_series.hpp>
#include <boost/math/special_functions/bessel_iterators.hpp>


  namespace boost { namespace math { namespace detail {

     template <class T, class Policy>
     T hypergeometric_1F1_divergent_fallback(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling);

     template <class T>
     bool hypergeometric_1F1_is_tricomi_viable_positive_b(const T& a, const T& b, const T& z)
     {
        BOOST_MATH_STD_USING
           if ((z < b) && (a > -50))
              return false;  // might as well fall through to recursion
        if (b <= 100)
           return true;
        // Even though we're in a reasonable domain for Tricomi's approximation, 
        // the arguments to the Bessel functions may be so large that we can't
        // actually evaluate them:
        T x = sqrt(fabs(2 * z * b - 4 * a * z));
        T v = b - 1;
        return log(boost::math::constants::e<T>() * x / (2 * v)) * v > tools::log_min_value<T>();
     }

     //
     // Returns an arbitrarily small value compared to "target" for use as a seed
     // value for Bessel recurrences.  Note that we'd better not make it too small
     // or underflow may occur resulting in either one of the terms in the
     // recurrence being zero, or else the result being zero.  Using 1/epsilon
     // as a safety factor ensures that if we do underflow to zero, all of the digits
     // will have been cancelled out anyway:
     //
     template <class T>
     T arbitrary_small_value(const T& target)
     {
        using std::fabs;
        return (tools::min_value<T>() / tools::epsilon<T>()) * (fabs(target) > 1 ? target : 1);
     }


     template <class T, class Policy>
     struct hypergeometric_1F1_AS_13_3_7_tricomi_series
     {
        typedef T result_type;

        enum { cache_size = 64 };

        hypergeometric_1F1_AS_13_3_7_tricomi_series(const T& a, const T& b, const T& z, const Policy& pol_)
           : A_minus_2(1), A_minus_1(0), A(b / 2), mult(z / 2), term(1), b_minus_1_plus_n(b - 1),
            bessel_arg((b / 2 - a) * z),
           two_a_minus_b(2 * a - b), pol(pol_), n(2)
        {
           BOOST_MATH_STD_USING
           term /= pow(fabs(bessel_arg), b_minus_1_plus_n / 2);
           mult /= sqrt(fabs(bessel_arg));
           bessel_cache[cache_size - 1] = bessel_arg > 0 ? boost::math::cyl_bessel_j(b_minus_1_plus_n - 1, 2 * sqrt(bessel_arg), pol) : boost::math::cyl_bessel_i(b_minus_1_plus_n - 1, 2 * sqrt(-bessel_arg), pol);
           if (fabs(bessel_cache[cache_size - 1]) < tools::min_value<T>() / tools::epsilon<T>())
           {
              // We get very limited precision due to rapid denormalisation/underflow of the Bessel values, raise an exception and try something else:
              policies::raise_evaluation_error("hypergeometric_1F1_AS_13_3_7_tricomi_series<%1%>", "Underflow in Bessel functions", bessel_cache[cache_size - 1], pol);
           }
           if ((term * bessel_cache[cache_size - 1] < tools::min_value<T>() / (tools::epsilon<T>() * tools::epsilon<T>())) || !(boost::math::isfinite)(term) || (!std::numeric_limits<T>::has_infinity && (fabs(term) > tools::max_value<T>())))
           {
              term = -log(fabs(bessel_arg)) * b_minus_1_plus_n / 2;
              log_scale = lltrunc(term);
              term -= log_scale;
              term = exp(term);
           }
           else
              log_scale = 0;
#ifndef BOOST_NO_CXX17_IF_CONSTEXPR
           if constexpr (std::numeric_limits<T>::has_infinity)
           {
              if (!(boost::math::isfinite)(bessel_cache[cache_size - 1]))
                 policies::raise_evaluation_error("hypergeometric_1F1_AS_13_3_7_tricomi_series<%1%>", "Expected finite Bessel function result but got %1%", bessel_cache[cache_size - 1], pol);
           }
           else
              if ((boost::math::isnan)(bessel_cache[cache_size - 1]) || (fabs(bessel_cache[cache_size - 1]) >= tools::max_value<T>()))
                 policies::raise_evaluation_error("hypergeometric_1F1_AS_13_3_7_tricomi_series<%1%>", "Expected finite Bessel function result but got %1%", bessel_cache[cache_size - 1], pol);
#else
           if ((std::numeric_limits<T>::has_infinity && !(boost::math::isfinite)(bessel_cache[cache_size - 1])) 
              || (!std::numeric_limits<T>::has_infinity && ((boost::math::isnan)(bessel_cache[cache_size - 1]) || (fabs(bessel_cache[cache_size - 1]) >= tools::max_value<T>()))))
              policies::raise_evaluation_error("hypergeometric_1F1_AS_13_3_7_tricomi_series<%1%>", "Expected finite Bessel function result but got %1%", bessel_cache[cache_size - 1], pol);
#endif
           cache_offset = -cache_size;
           refill_cache();
        }
        T operator()()
        {
           //
           // We return the n-2 term, and do 2 terms at once as every other term can be
           // very small (or zero) when b == 2a:
           //
           BOOST_MATH_STD_USING
           if(n - 2 - cache_offset >= cache_size)
              refill_cache();
           T result = A_minus_2 * term * bessel_cache[n - 2 - cache_offset];
           term *= mult;
           ++n;
           T A_next = ((b_minus_1_plus_n + 2) * A_minus_1 + two_a_minus_b * A_minus_2) / n;
           b_minus_1_plus_n += 1;
           A_minus_2 = A_minus_1;
           A_minus_1 = A;
           A = A_next;

           if (A_minus_2 != 0)
           {
              if (n - 2 - cache_offset >= cache_size)
                 refill_cache();
              result += A_minus_2 * term * bessel_cache[n - 2 - cache_offset];
           }
           term *= mult;
           ++n;
           A_next = ((b_minus_1_plus_n + 2) * A_minus_1 + two_a_minus_b * A_minus_2) / n;
           b_minus_1_plus_n += 1;
           A_minus_2 = A_minus_1;
           A_minus_1 = A;
           A = A_next;

           return result;
        }

        long long scale()const
        {
           return log_scale;
        }

     private:
        T A_minus_2, A_minus_1, A, mult, term, b_minus_1_plus_n, bessel_arg, two_a_minus_b;
        std::array<T, cache_size> bessel_cache;
        const Policy& pol;
        int n, cache_offset;
        long long log_scale;

        hypergeometric_1F1_AS_13_3_7_tricomi_series operator=(const hypergeometric_1F1_AS_13_3_7_tricomi_series&);

        void refill_cache()
        {
           BOOST_MATH_STD_USING
           //
           // We don't calculate a new bessel I/J value: instead start our iterator off
           // with an arbitrary small value, then when we get back to the last value in the previous cache
           // calculate the ratio and use it to renormalise all the new values.  This is more efficient, but
           // also avoids problems with J_v(x) or I_v(x) underflowing to zero.
           //
           cache_offset += cache_size;
           T last_value = bessel_cache.back();
           T ratio;
           if (bessel_arg > 0)
           {
              //
              // We will be calculating Bessel J.
              // We need a different recurrence strategy for positive and negative orders:
              //
              if (b_minus_1_plus_n > 0)
              {
                 bessel_j_backwards_iterator<T, Policy> i(b_minus_1_plus_n + (int)cache_size - 1, 2 * sqrt(bessel_arg), arbitrary_small_value(last_value));

                 for (int j = cache_size - 1; j >= 0; --j, ++i)
                 {
                    bessel_cache[j] = *i;
                    //
                    // Depending on the value of bessel_arg, the values stored in the cache can grow so
                    // large as to overflow, if that looks likely then we need to rescale all the
                    // existing terms (most of which will then underflow to zero).  In this situation
                    // it's likely that our series will only need 1 or 2 terms of the series but we
                    // can't be sure of that:
                    //
                    if ((j < cache_size - 2) && (tools::max_value<T>() / fabs(64 * bessel_cache[j] / bessel_cache[j + 1]) < fabs(bessel_cache[j])))
                    {
                       T rescale = pow(fabs(bessel_cache[j] / bessel_cache[j + 1]), j + 1) * 2;
                       if (!((boost::math::isfinite)(rescale)))
                          rescale = tools::max_value<T>();
                       for (int k = j; k < cache_size; ++k)
                          bessel_cache[k] /= rescale;
                       bessel_j_backwards_iterator<T, Policy> ti(b_minus_1_plus_n + j, 2 * sqrt(bessel_arg), bessel_cache[j + 1], bessel_cache[j]);
                       i = ti;
                    }
                 }
                 ratio = last_value / *i;
              }
              else
              {
                 //
                 // Negative order is difficult: the J_v(x) recurrence relations are unstable
                 // *in both directions* for v < 0, except as v -> -INF when we have
                 // J_-v(x)  ~= -sin(pi.v)Y_v(x).
                 // For small v what we can do is compute every other Bessel function and
                 // then fill in the gaps using the recurrence relation.  This *is* stable
                 // provided that v is not so negative that the above approximation holds.
                 //
                 bessel_cache[1] = cyl_bessel_j(b_minus_1_plus_n + 1, 2 * sqrt(bessel_arg), pol);
                 bessel_cache[0] = (last_value + bessel_cache[1]) / (b_minus_1_plus_n / sqrt(bessel_arg));
                 int pos = 2;
                 while ((pos < cache_size - 1) && (b_minus_1_plus_n + pos < 0))
                 {
                    bessel_cache[pos + 1] = cyl_bessel_j(b_minus_1_plus_n + pos + 1, 2 * sqrt(bessel_arg), pol);
                    bessel_cache[pos] = (bessel_cache[pos-1] + bessel_cache[pos+1]) / ((b_minus_1_plus_n + pos) / sqrt(bessel_arg));
                    pos += 2;
                 }
                 if (pos < cache_size)
                 {
                    //
                    // We have crossed over into the region where backward recursion is the stable direction
                    // start from arbitrary value and recurse down to "pos" and normalise:
                    //
                    bessel_j_backwards_iterator<T, Policy> i2(b_minus_1_plus_n + (int)cache_size - 1, 2 * sqrt(bessel_arg), arbitrary_small_value(bessel_cache[pos-1]));
                    for (int loc = cache_size - 1; loc >= pos; --loc)
                       bessel_cache[loc] = *i2++;
                    ratio = bessel_cache[pos - 1] / *i2;
                    //
                    // Sanity check, if we normalised to an unusually small value then it was likely
                    // to be near a root and the calculated ratio is garbage, if so perform one
                    // more J_v(x) evaluation at position and normalise again:
                    //
                    if (fabs(bessel_cache[pos] * ratio / bessel_cache[pos - 1]) > 5)
                       ratio = cyl_bessel_j(b_minus_1_plus_n + pos, 2 * sqrt(bessel_arg), pol) / bessel_cache[pos];
                    while (pos < cache_size)
                       bessel_cache[pos++] *= ratio;
                 }
                 ratio = 1;
              }
           }
           else
           {
              //
              // Bessel I.
              // We need a different recurrence strategy for positive and negative orders:
              //
              if (b_minus_1_plus_n > 0)
              {
                 bessel_i_backwards_iterator<T, Policy> i(b_minus_1_plus_n + (int)cache_size - 1, 2 * sqrt(-bessel_arg), arbitrary_small_value(last_value));

                 for (int j = cache_size - 1; j >= 0; --j, ++i)
                 {
                    bessel_cache[j] = *i;
                    //
                    // Depending on the value of bessel_arg, the values stored in the cache can grow so
                    // large as to overflow, if that looks likely then we need to rescale all the
                    // existing terms (most of which will then underflow to zero).  In this situation
                    // it's likely that our series will only need 1 or 2 terms of the series but we
                    // can't be sure of that:
                    //
                    if ((j < cache_size - 2) && (tools::max_value<T>() / fabs(64 * bessel_cache[j] / bessel_cache[j + 1]) < fabs(bessel_cache[j])))
                    {
                       T rescale = pow(fabs(bessel_cache[j] / bessel_cache[j + 1]), j + 1) * 2;
                       if (!((boost::math::isfinite)(rescale)))
                          rescale = tools::max_value<T>();
                       for (int k = j; k < cache_size; ++k)
                          bessel_cache[k] /= rescale;
                       i = bessel_i_backwards_iterator<T, Policy>(b_minus_1_plus_n + j, 2 * sqrt(-bessel_arg), bessel_cache[j + 1], bessel_cache[j]);
                    }
                 }
                 ratio = last_value / *i;
              }
              else
              {
                 //
                 // Forwards iteration is stable:
                 //
                 bessel_i_forwards_iterator<T, Policy> i(b_minus_1_plus_n, 2 * sqrt(-bessel_arg));
                 int pos = 0;
                 while ((pos < cache_size) && (b_minus_1_plus_n + pos < 0.5))
                 {
                    bessel_cache[pos++] = *i++;
                 }
                 if (pos < cache_size)
                 {
                    //
                    // We have crossed over into the region where backward recursion is the stable direction
                    // start from arbitrary value and recurse down to "pos" and normalise:
                    //
                    bessel_i_backwards_iterator<T, Policy> i2(b_minus_1_plus_n + (int)cache_size - 1, 2 * sqrt(-bessel_arg), arbitrary_small_value(last_value));
                    for (int loc = cache_size - 1; loc >= pos; --loc)
                       bessel_cache[loc] = *i2++;
                    ratio = bessel_cache[pos - 1] / *i2;
                    while (pos < cache_size)
                       bessel_cache[pos++] *= ratio;
                 }
                 ratio = 1;
              }
           }
           if(ratio != 1)
              for (auto j = bessel_cache.begin(); j != bessel_cache.end(); ++j)
                 *j *= ratio;
           //
           // Very occasionally our normalisation fails because the normalisztion value
           // is sitting right on top of a root (or very close to it).  When that happens
           // best to calculate a fresh Bessel evaluation and normalise again.
           //
           if (fabs(bessel_cache[0] / last_value) > 5)
           {
              ratio = (bessel_arg < 0 ? cyl_bessel_i(b_minus_1_plus_n, 2 * sqrt(-bessel_arg), pol) : cyl_bessel_j(b_minus_1_plus_n, 2 * sqrt(bessel_arg), pol)) / bessel_cache[0];
              if (ratio != 1)
                 for (auto j = bessel_cache.begin(); j != bessel_cache.end(); ++j)
                    *j *= ratio;
           }
        }
     };

     template <class T, class Policy>
     T hypergeometric_1F1_AS_13_3_7_tricomi(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scale)
     {
        BOOST_MATH_STD_USING
        //
        // Works for a < 0, b < 0, z > 0.
        //
        // For convergence we require A * term to be converging otherwise we get
        // a divergent alternating series.  It's actually really hard to analyse this
        // and the best purely heuristic policy we've found is
        // z < fabs((2 * a - b) / (sqrt(fabs(a)))) ; b > 0  or:
        // z < fabs((2 * a - b) / (sqrt(fabs(ab)))) ; b < 0
        //
        T prefix(0);
        int prefix_sgn(0);
        bool use_logs = false;
        long long scale = 0;
        //
        // We can actually support the b == 2a case within here, but we haven't
        // as we appear never to get here in practice.  Which means this get out
        // clause is a bit of defensive programming....
        //
        if(b == 2 * a)
           return hypergeometric_1F1_divergent_fallback(a, b, z, pol, log_scale);

        try
        {
           prefix = boost::math::tgamma(b, pol);
           prefix *= exp(z / 2);
        }
        catch (const std::runtime_error&)
        {
           use_logs = true;
        }
        if (use_logs || (prefix == 0) || !(boost::math::isfinite)(prefix) || (!std::numeric_limits<T>::has_infinity && (fabs(prefix) >= tools::max_value<T>())))
        {
           use_logs = true;
           prefix = boost::math::lgamma(b, &prefix_sgn, pol) + z / 2;
           scale = lltrunc(prefix);
           log_scale += scale;
           prefix -= scale;
        }
        T result(0);
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        bool retry = false;
        long long series_scale = 0;
        try
        {
           hypergeometric_1F1_AS_13_3_7_tricomi_series<T, Policy> s(a, b, z, pol);
           series_scale = s.scale();
           log_scale += s.scale();
           try
           {
              T norm = 0;
              result = 0;
              if((a < 0) && (b < 0))
                 result = boost::math::tools::checked_sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter, result, norm);
              else
                 result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter, result);
              if (!(boost::math::isfinite)(result) || (result == 0) || (!std::numeric_limits<T>::has_infinity && (fabs(result) >= tools::max_value<T>())))
                 retry = true;
              if (norm / fabs(result) > 1 / boost::math::tools::root_epsilon<T>())
                 retry = true;  // fatal cancellation
           }
           catch (const std::overflow_error&)
           {
              retry = true;
           }
           catch (const boost::math::evaluation_error&)
           {
              retry = true;
           }
        }
        catch (const std::overflow_error&)
        {
           log_scale -= scale;
           return hypergeometric_1F1_divergent_fallback(a, b, z, pol, log_scale);
        }
        catch (const boost::math::evaluation_error&)
        {
           log_scale -= scale;
           return hypergeometric_1F1_divergent_fallback(a, b, z, pol, log_scale);
        }
        if (retry)
        {
           log_scale -= scale;
           log_scale -= series_scale;
           return hypergeometric_1F1_divergent_fallback(a, b, z, pol, log_scale);
        }
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_AS_13_3_7<%1%>(%1%,%1%,%1%)", max_iter, pol);
        if (use_logs)
        {
           int sgn = boost::math::sign(result);
           prefix += log(fabs(result));
           result = sgn * prefix_sgn * exp(prefix);
        }
        else
        {
           if ((fabs(result) > 1) && (fabs(prefix) > 1) && (tools::max_value<T>() / fabs(result) < fabs(prefix)))
           {
              // Overflow:
              scale = lltrunc(tools::log_max_value<T>()) - 10;
              log_scale += scale;
              result /= exp(T(scale));
           }
           result *= prefix;
        }
        return result;
     }


     template <class T>
     struct cyl_bessel_i_large_x_sum
     {
        typedef T result_type;

        cyl_bessel_i_large_x_sum(const T& v, const T& x) : v(v), z(x), term(1), k(0) {}

        T operator()()
        {
           T result = term;
           ++k;
           term *= -(4 * v * v - (2 * k - 1) * (2 * k - 1)) / (8 * k * z);
           return result;
        }
        T v, z, term;
        int k;
     };

     template <class T, class Policy>
     T cyl_bessel_i_large_x_scaled(const T& v, const T& x, long long& log_scaling, const Policy& pol)
     {
        BOOST_MATH_STD_USING
           cyl_bessel_i_large_x_sum<T> s(v, x);
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::cyl_bessel_i_large_x<%1%>(%1%,%1%)", max_iter, pol);
        long long scale = boost::math::lltrunc(x);
        log_scaling += scale;
        return result * exp(x - scale) / sqrt(boost::math::constants::two_pi<T>() * x);
     }



     template <class T, class Policy>
     struct hypergeometric_1F1_AS_13_3_6_series
     {
        typedef T result_type;

        enum { cache_size = 64 };
        //
        // This series is only convergent/useful for a and b approximately equal
        // (ideally |a-b| < 1).  The series can also go divergent after a while
        // when b < 0, which limits precision to around that of double.  In that
        // situation we return 0 to terminate the series as otherwise the divergent 
        // terms will destroy all the bits in our result before they do eventually
        // converge again.  One important use case for this series is for z < 0
        // and |a| << |b| so that either b-a == b or at least most of the digits in a
        // are lost in the subtraction.  Note that while you can easily convince yourself 
        // that the result should be unity when b-a == b, in fact this is not (quite) 
        // the case for large z.
        //
        hypergeometric_1F1_AS_13_3_6_series(const T& a, const T& b, const T& z, const T& b_minus_a, const Policy& pol_)
           : b_minus_a(b_minus_a), half_z(z / 2), poch_1(2 * b_minus_a - 1), poch_2(b_minus_a - a), b_poch(b), term(1), last_result(1), sign(1), n(0), cache_offset(-cache_size), scale(0), pol(pol_)
        {
           bessel_i_cache[cache_size - 1] = half_z > tools::log_max_value<T>() ?
              cyl_bessel_i_large_x_scaled(T(b_minus_a - 1.5f), half_z, scale, pol) : boost::math::cyl_bessel_i(b_minus_a - 1.5f, half_z, pol);
           refill_cache();
        }
        T operator()()
        {
           BOOST_MATH_STD_USING
           if(n - cache_offset >= cache_size)
              refill_cache();

           T result = term * (b_minus_a - 0.5f + n) * sign * bessel_i_cache[n - cache_offset];
           ++n;
           term *= poch_1;
           poch_1 = (n == 1) ? T(2 * b_minus_a) : T(poch_1 + 1);
           term *= poch_2;
           poch_2 += 1;
           term /= n;
           term /= b_poch;
           b_poch += 1;
           sign = -sign;

           if ((fabs(result) > fabs(last_result)) && (n > 100))
              return 0;  // series has gone divergent!

           last_result = result;

           return result;
        }

        long long scaling()const
        {
           return scale;
        }

     private:
        T b_minus_a, half_z, poch_1, poch_2, b_poch, term, last_result;
        int sign;
        int n, cache_offset;
        long long scale;
        const Policy& pol;
        std::array<T, cache_size> bessel_i_cache;

        void refill_cache()
        {
           BOOST_MATH_STD_USING
           //
           // We don't calculate a new bessel I value: instead start our iterator off
           // with an arbitrary small value, then when we get back to the last value in the previous cache
           // calculate the ratio and use it to renormalise all the values.  This is more efficient, but
           // also avoids problems with I_v(x) underflowing to zero.
           //
           cache_offset += cache_size;
           T last_value = bessel_i_cache.back();
           bessel_i_backwards_iterator<T, Policy> i(b_minus_a + cache_offset + (int)cache_size - 1.5f, half_z, tools::min_value<T>() * (fabs(last_value) > 1 ? last_value : 1) / tools::epsilon<T>());

           for (int j = cache_size - 1; j >= 0; --j, ++i)
           {
              bessel_i_cache[j] = *i;
              //
              // Depending on the value of half_z, the values stored in the cache can grow so
              // large as to overflow, if that looks likely then we need to rescale all the
              // existing terms (most of which will then underflow to zero).  In this situation
              // it's likely that our series will only need 1 or 2 terms of the series but we
              // can't be sure of that:
              //
              if((j < cache_size - 2) && (bessel_i_cache[j + 1] != 0) && (tools::max_value<T>() / fabs(64 * bessel_i_cache[j] / bessel_i_cache[j + 1]) < fabs(bessel_i_cache[j])))
              {
                 T rescale = pow(fabs(bessel_i_cache[j] / bessel_i_cache[j + 1]), j + 1) * 2;
                 if (rescale > tools::max_value<T>())
                    rescale = tools::max_value<T>();
                 for (int k = j; k < cache_size; ++k)
                    bessel_i_cache[k] /= rescale;
                 i = bessel_i_backwards_iterator<T, Policy>(b_minus_a -0.5f + cache_offset + j, half_z, bessel_i_cache[j + 1], bessel_i_cache[j]);
              }
           }
           T ratio = last_value / *i;
           for (auto j = bessel_i_cache.begin(); j != bessel_i_cache.end(); ++j)
              *j *= ratio;
        }

        hypergeometric_1F1_AS_13_3_6_series();
        hypergeometric_1F1_AS_13_3_6_series(const hypergeometric_1F1_AS_13_3_6_series&);
        hypergeometric_1F1_AS_13_3_6_series& operator=(const hypergeometric_1F1_AS_13_3_6_series&);
     };

     template <class T, class Policy>
     T hypergeometric_1F1_AS_13_3_6(const T& a, const T& b, const T& z, const T& b_minus_a, const Policy& pol, long long& log_scaling)
     {
        BOOST_MATH_STD_USING
        if(b_minus_a == 0)
        {
           // special case: M(a,a,z) == exp(z)
           long long scale = lltrunc(z, pol);
           log_scaling += scale;
           return exp(z - scale);
        }
        hypergeometric_1F1_AS_13_3_6_series<T, Policy> s(a, b, z, b_minus_a, pol);
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_AS_13_3_6<%1%>(%1%,%1%,%1%)", max_iter, pol);
        result *= boost::math::tgamma(b_minus_a - 0.5f, pol) * pow(z / 4, -b_minus_a + 0.5f);
        long long scale = lltrunc(z / 2);
        log_scaling += scale;
        log_scaling += s.scaling();
        result *= exp(z / 2 - scale);
        return result;
     }

     /****************************************************************************************************************/
     //
     // The following are not used at present and are commented out for that reason:
     //
     /****************************************************************************************************************/

#if 0

     template <class T, class Policy>
     struct hypergeometric_1F1_AS_13_3_8_series
     {
        //
        // TODO: store and cache Bessel function evaluations via backwards recurrence.
        //
        // The C term grows by at least an order of magnitude with each iteration, and
        // rate of growth is largely independent of the arguments.  Free parameter h
        // seems to give accurate results for small values (almost zero) or h=1.
        // Convergence and accuracy, only when -a/z > 100, this appears to have no
        // or little benefit over 13.3.7 as it generally requires more iterations?
        //
        hypergeometric_1F1_AS_13_3_8_series(const T& a, const T& b, const T& z, const T& h, const Policy& pol_)
           : C_minus_2(1), C_minus_1(-b * h), C(b * (b + 1) * h * h / 2 - (2 * h - 1) * a / 2),
           bessel_arg(2 * sqrt(-a * z)), bessel_order(b - 1), power_term(std::pow(-a * z, (1 - b) / 2)), mult(z / std::sqrt(-a * z)),
           a_(a), b_(b), z_(z), h_(h), n(2), pol(pol_)
        {
        }
        T operator()()
        {
           // we actually return the n-2 term:
           T result = C_minus_2 * power_term * boost::math::cyl_bessel_j(bessel_order, bessel_arg, pol);
           bessel_order += 1;
           power_term *= mult;
           ++n;
           T C_next = ((1 - 2 * h_) * (n - 1) - b_ * h_) * C
              + ((1 - 2 * h_) * a_ - h_ * (h_ - 1) *(b_ + n - 2)) * C_minus_1
              - h_ * (h_ - 1) * a_ * C_minus_2;
           C_next /= n;
           C_minus_2 = C_minus_1;
           C_minus_1 = C;
           C = C_next;
           return result;
        }
        T C, C_minus_1, C_minus_2, bessel_arg, bessel_order, power_term, mult, a_, b_, z_, h_;
        const Policy& pol;
        int n;

        typedef T result_type;
     };

     template <class T, class Policy>
     T hypergeometric_1F1_AS_13_3_8(const T& a, const T& b, const T& z, const T& h, const Policy& pol)
     {
        BOOST_MATH_STD_USING
        T prefix = exp(h * z) * boost::math::tgamma(b);
        hypergeometric_1F1_AS_13_3_8_series<T, Policy> s(a, b, z, h, pol);
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_AS_13_3_8<%1%>(%1%,%1%,%1%)", max_iter, pol);
        result *= prefix;
        return result;
     }

     //
     // This is the series from https://dlmf.nist.gov/13.11
     // It appears to be unusable for a,z < 0, and for
     // b < 0 appears to never be better than the defining series
     // for 1F1.
     //
     template <class T, class Policy>
     struct hypergeometric_1f1_13_11_1_series
     {
        typedef T result_type;

        hypergeometric_1f1_13_11_1_series(const T& a, const T& b, const T& z, const Policy& pol_)
           : term(1), two_a_minus_1_plus_s(2 * a - 1), two_a_minus_b_plus_s(2 * a - b), b_plus_s(b), a_minus_half_plus_s(a - 0.5f), half_z(z / 2), s(0), pol(pol_)
        {
        }
        T operator()()
        {
           T result = term * a_minus_half_plus_s * boost::math::cyl_bessel_i(a_minus_half_plus_s, half_z, pol);

           term *= two_a_minus_1_plus_s * two_a_minus_b_plus_s / (b_plus_s * ++s);
           two_a_minus_1_plus_s += 1;
           a_minus_half_plus_s += 1;
           two_a_minus_b_plus_s += 1;
           b_plus_s += 1;

           return result;
        }
        T term, two_a_minus_1_plus_s, two_a_minus_b_plus_s, b_plus_s, a_minus_half_plus_s, half_z;
        long long s;
        const Policy& pol;
     };

     template <class T, class Policy>
     T hypergeometric_1f1_13_11_1(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling)
     {
        BOOST_MATH_STD_USING
           bool use_logs = false;
        T prefix;
        int prefix_sgn = 1;
        if (true/*(a < boost::math::max_factorial<T>::value) && (a > 0)*/)
           prefix = boost::math::tgamma(a - 0.5f, pol);
        else
        {
           prefix = boost::math::lgamma(a - 0.5f, &prefix_sgn, pol);
           use_logs = true;
        }
        if (use_logs)
        {
           prefix += z / 2;
           prefix += log(z / 4) * (0.5f - a);
        }
        else if (z > 0)
        {
           prefix *= pow(z / 4, 0.5f - a);
           prefix *= exp(z / 2);
        }
        else
        {
           prefix *= exp(z / 2);
           prefix *= pow(z / 4, 0.5f - a);
        }

        hypergeometric_1f1_13_11_1_series<T, Policy> s(a, b, z, pol);
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1f1_13_11_1<%1%>(%1%,%1%,%1%)", max_iter, pol);
        if (use_logs)
        {
           long long scaling = lltrunc(prefix);
           log_scaling += scaling;
           prefix -= scaling;
           result *= exp(prefix) * prefix_sgn;
        }
        else
           result *= prefix;

        return result;
     }

#endif

  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_1F1_BESSEL_HPP

/* hypergeometric_1F1_bessel.hpp
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
*/