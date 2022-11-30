//  Copyright (c) 2013 Christopher Kormanyos
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469
//
// This header contains implementation details for estimating the zeros
// of cylindrical Bessel and Neumann functions on the positive real axis.
// Support is included for both positive as well as negative order.
// Various methods are used to estimate the roots. These include
// empirical curve fitting and McMahon's asymptotic approximation
// for small order, uniform asymptotic expansion for large order,
// and iteration and root interlacing for negative order.
//
#ifndef BOOST_MATH_BESSEL_JY_ZERO_2013_01_18_HPP_
  #define BOOST_MATH_BESSEL_JY_ZERO_2013_01_18_HPP_

  #include <algorithm>
  #include <boost/math/constants/constants.hpp>
  #include <boost/math/special_functions/math_fwd.hpp>
  #include <boost/math/special_functions/cbrt.hpp>
  #include <boost/math/special_functions/detail/airy_ai_bi_zero.hpp>

  namespace boost { namespace math {
  namespace detail
  {
    namespace bessel_zero
    {
      template<class T>
      T equation_nist_10_21_19(const T& v, const T& a)
      {
        // Get the initial estimate of the m'th root of Jv or Yv.
        // This subroutine is used for the order m with m > 1.
        // The order m has been used to create the input parameter a.

        // This is Eq. 10.21.19 in the NIST Handbook.
        const T mu                  = (v * v) * 4U;
        const T mu_minus_one        = mu - T(1);
        const T eight_a_inv         = T(1) / (a * 8U);
        const T eight_a_inv_squared = eight_a_inv * eight_a_inv;

        const T term3 = ((mu_minus_one *  4U) *     ((mu *    7U) -     T(31U) )) / 3U;
        const T term5 = ((mu_minus_one * 32U) *   ((((mu *   83U) -    T(982U) ) * mu) +    T(3779U) )) / 15U;
        const T term7 = ((mu_minus_one * 64U) * ((((((mu * 6949U) - T(153855UL)) * mu) + T(1585743UL)) * mu) - T(6277237UL))) / 105U;

        return a + ((((                      - term7
                       * eight_a_inv_squared - term5)
                       * eight_a_inv_squared - term3)
                       * eight_a_inv_squared - mu_minus_one)
                       * eight_a_inv);
      }

      template<typename T>
      class equation_as_9_3_39_and_its_derivative
      {
      public:
        equation_as_9_3_39_and_its_derivative(const T& zt) : zeta(zt) { }

        boost::math::tuple<T, T> operator()(const T& z) const
        {
          BOOST_MATH_STD_USING // ADL of std names, needed for acos, sqrt.

          // Return the function of zeta that is implicitly defined
          // in A&S Eq. 9.3.39 as a function of z. The function is
          // returned along with its derivative with respect to z.

          const T zsq_minus_one_sqrt = sqrt((z * z) - T(1));

          const T the_function(
              zsq_minus_one_sqrt
            - (  acos(T(1) / z) + ((T(2) / 3U) * (zeta * sqrt(zeta)))));

          const T its_derivative(zsq_minus_one_sqrt / z);

          return boost::math::tuple<T, T>(the_function, its_derivative);
        }

      private:
        const equation_as_9_3_39_and_its_derivative& operator=(const equation_as_9_3_39_and_its_derivative&) = delete;
        const T zeta;
      };

      template<class T, class Policy>
      static T equation_as_9_5_26(const T& v, const T& ai_bi_root, const Policy& pol)
      {
        BOOST_MATH_STD_USING // ADL of std names, needed for log, sqrt.

        // Obtain the estimate of the m'th zero of Jv or Yv.
        // The order m has been used to create the input parameter ai_bi_root.
        // Here, v is larger than about 2.2. The estimate is computed
        // from Abramowitz and Stegun Eqs. 9.5.22 and 9.5.26, page 371.
        //
        // The inversion of z as a function of zeta is mentioned in the text
        // following A&S Eq. 9.5.26. Here, we accomplish the inversion by
        // performing a Taylor expansion of Eq. 9.3.39 for large z to order 2
        // and solving the resulting quadratic equation, thereby taking
        // the positive root of the quadratic.
        // In other words: (2/3)(-zeta)^(3/2) approx = z + 1/(2z) - pi/2.
        // This leads to: z^2 - [(2/3)(-zeta)^(3/2) + pi/2]z + 1/2 = 0.
        //
        // With this initial estimate, Newton-Raphson iteration is used
        // to refine the value of the estimate of the root of z
        // as a function of zeta.

        const T v_pow_third(boost::math::cbrt(v, pol));
        const T v_pow_minus_two_thirds(T(1) / (v_pow_third * v_pow_third));

        // Obtain zeta using the order v combined with the m'th root of
        // an airy function, as shown in  A&S Eq. 9.5.22.
        const T zeta = v_pow_minus_two_thirds * (-ai_bi_root);

        const T zeta_sqrt = sqrt(zeta);

        // Set up a quadratic equation based on the Taylor series
        // expansion mentioned above.
        const T b = -((((zeta * zeta_sqrt) * 2U) / 3U) + boost::math::constants::half_pi<T>());

        // Solve the quadratic equation, taking the positive root.
        const T z_estimate = (-b + sqrt((b * b) - T(2))) / 2U;

        // Establish the range, the digits, and the iteration limit
        // for the upcoming root-finding.
        const T range_zmin = (std::max<T>)(z_estimate - T(1), T(1));
        const T range_zmax = z_estimate + T(1);

        const int my_digits10 = static_cast<int>(static_cast<float>(boost::math::tools::digits<T>() * 0.301F));

        // Select the maximum allowed iterations based on the number
        // of decimal digits in the numeric type T, being at least 12.
        const std::uintmax_t iterations_allowed = static_cast<std::uintmax_t>((std::max)(12, my_digits10 * 2));

        std::uintmax_t iterations_used = iterations_allowed;

        // Calculate the root of z as a function of zeta.
        const T z = boost::math::tools::newton_raphson_iterate(
          boost::math::detail::bessel_zero::equation_as_9_3_39_and_its_derivative<T>(zeta),
          z_estimate,
          range_zmin,
          range_zmax,
          (std::min)(boost::math::tools::digits<T>(), boost::math::tools::digits<float>()),
          iterations_used);

        static_cast<void>(iterations_used);

        // Continue with the implementation of A&S Eq. 9.3.39.
        const T zsq_minus_one      = (z * z) - T(1);
        const T zsq_minus_one_sqrt = sqrt(zsq_minus_one);

        // This is A&S Eq. 9.3.42.
        const T b0_term_5_24 = T(5) / ((zsq_minus_one * zsq_minus_one_sqrt) * 24U);
        const T b0_term_1_8  = T(1) / ( zsq_minus_one_sqrt * 8U);
        const T b0_term_5_48 = T(5) / ((zeta * zeta) * 48U);

        const T b0 = -b0_term_5_48 + ((b0_term_5_24 + b0_term_1_8) / zeta_sqrt);

        // This is the second line of A&S Eq. 9.5.26 for f_k with k = 1.
        const T f1 = ((z * zeta_sqrt) * b0) / zsq_minus_one_sqrt;

        // This is A&S Eq. 9.5.22 expanded to k = 1 (i.e., one term in the series).
        return (v * z) + (f1 / v);
      }

      namespace cyl_bessel_j_zero_detail
      {
        template<class T, class Policy>
        T equation_nist_10_21_40_a(const T& v, const Policy& pol)
        {
          const T v_pow_third(boost::math::cbrt(v, pol));
          const T v_pow_minus_two_thirds(T(1) / (v_pow_third * v_pow_third));

          return v * (((((                         + T(0.043)
                          * v_pow_minus_two_thirds - T(0.0908))
                          * v_pow_minus_two_thirds - T(0.00397))
                          * v_pow_minus_two_thirds + T(1.033150))
                          * v_pow_minus_two_thirds + T(1.8557571))
                          * v_pow_minus_two_thirds + T(1));
        }

        template<class T, class Policy>
        class function_object_jv
        {
        public:
          function_object_jv(const T& v,
                             const Policy& pol) : my_v(v),
                                                  my_pol(pol) { }

          T operator()(const T& x) const
          {
            return boost::math::cyl_bessel_j(my_v, x, my_pol);
          }

        private:
          const T my_v;
          const Policy& my_pol;
          const function_object_jv& operator=(const function_object_jv&) = delete;
        };

        template<class T, class Policy>
        class function_object_jv_and_jv_prime
        {
        public:
          function_object_jv_and_jv_prime(const T& v,
                                          const bool order_is_zero,
                                          const Policy& pol) : my_v(v),
                                                               my_order_is_zero(order_is_zero),
                                                               my_pol(pol) { }

          boost::math::tuple<T, T> operator()(const T& x) const
          {
            // Obtain Jv(x) and Jv'(x).
            // Chris's original code called the Bessel function implementation layer direct, 
            // but that circumvented optimizations for integer-orders.  Call the documented
            // top level functions instead, and let them sort out which implementation to use.
            T j_v;
            T j_v_prime;

            if(my_order_is_zero)
            {
              j_v       =  boost::math::cyl_bessel_j(0, x, my_pol);
              j_v_prime = -boost::math::cyl_bessel_j(1, x, my_pol);
            }
            else
            {
                      j_v       = boost::math::cyl_bessel_j(  my_v,      x, my_pol);
              const T j_v_m1     (boost::math::cyl_bessel_j(T(my_v - 1), x, my_pol));
                      j_v_prime = j_v_m1 - ((my_v * j_v) / x);
            }

            // Return a tuple containing both Jv(x) and Jv'(x).
            return boost::math::make_tuple(j_v, j_v_prime);
          }

        private:
          const T my_v;
          const bool my_order_is_zero;
          const Policy& my_pol;
          const function_object_jv_and_jv_prime& operator=(const function_object_jv_and_jv_prime&) = delete;
        };

        template<class T> bool my_bisection_unreachable_tolerance(const T&, const T&) { return false; }

        template<class T, class Policy>
        T initial_guess(const T& v, const int m, const Policy& pol)
        {
          BOOST_MATH_STD_USING // ADL of std names, needed for floor.

          // Compute an estimate of the m'th root of cyl_bessel_j.

          T guess;

          // There is special handling for negative order.
          if(v < 0)
          {
            if((m == 1) && (v > -0.5F))
            {
              // For small, negative v, use the results of empirical curve fitting.
              // Mathematica(R) session for the coefficients:
              //  Table[{n, BesselJZero[n, 1]}, {n, -(1/2), 0, 1/10}]
              //  N[%, 20]
              //  Fit[%, {n^0, n^1, n^2, n^3, n^4, n^5, n^6}, n]
              guess = (((((    - T(0.2321156900729)
                           * v - T(0.1493247777488))
                           * v - T(0.15205419167239))
                           * v + T(0.07814930561249))
                           * v - T(0.17757573537688))
                           * v + T(1.542805677045663))
                           * v + T(2.40482555769577277);

              return guess;
            }

            // Create the positive order and extract its positive floor integer part.
            const T vv(-v);
            const T vv_floor(floor(vv));

            // The to-be-found root is bracketed by the roots of the
            // Bessel function whose reflected, positive integer order
            // is less than, but nearest to vv.

            T root_hi = boost::math::detail::bessel_zero::cyl_bessel_j_zero_detail::initial_guess(vv_floor, m, pol);
            T root_lo;

            if(m == 1)
            {
              // The estimate of the first root for negative order is found using
              // an adaptive range-searching algorithm.
              root_lo = T(root_hi - 0.1F);

              const bool hi_end_of_bracket_is_negative = (boost::math::cyl_bessel_j(v, root_hi, pol) < 0);

              while((root_lo > boost::math::tools::epsilon<T>()))
              {
                const bool lo_end_of_bracket_is_negative = (boost::math::cyl_bessel_j(v, root_lo, pol) < 0);

                if(hi_end_of_bracket_is_negative != lo_end_of_bracket_is_negative)
                {
                  break;
                }

                root_hi = root_lo;

                // Decrease the lower end of the bracket using an adaptive algorithm.
                if(root_lo > 0.5F)
                {
                  root_lo -= 0.5F;
                }
                else
                {
                  root_lo *= 0.75F;
                }
              }
            }
            else
            {
              root_lo = boost::math::detail::bessel_zero::cyl_bessel_j_zero_detail::initial_guess(vv_floor, m - 1, pol);
            }

            // Perform several steps of bisection iteration to refine the guess.
            std::uintmax_t number_of_iterations(12U);

            // Do the bisection iteration.
            const boost::math::tuple<T, T> guess_pair =
               boost::math::tools::bisect(
                  boost::math::detail::bessel_zero::cyl_bessel_j_zero_detail::function_object_jv<T, Policy>(v, pol),
                  root_lo,
                  root_hi,
                  boost::math::detail::bessel_zero::cyl_bessel_j_zero_detail::my_bisection_unreachable_tolerance<T>,
                  number_of_iterations);

            return (boost::math::get<0>(guess_pair) + boost::math::get<1>(guess_pair)) / 2U;
          }

          if(m == 1U)
          {
            // Get the initial estimate of the first root.

            if(v < 2.2F)
            {
              // For small v, use the results of empirical curve fitting.
              // Mathematica(R) session for the coefficients:
              //  Table[{n, BesselJZero[n, 1]}, {n, 0, 22/10, 1/10}]
              //  N[%, 20]
              //  Fit[%, {n^0, n^1, n^2, n^3, n^4, n^5, n^6}, n]
              guess = (((((    - T(0.0008342379046010)
                           * v + T(0.007590035637410))
                           * v - T(0.030640914772013))
                           * v + T(0.078232088020106))
                           * v - T(0.169668712590620))
                           * v + T(1.542187960073750))
                           * v + T(2.4048359915254634);
            }
            else
            {
              // For larger v, use the first line of Eqs. 10.21.40 in the NIST Handbook.
              guess = boost::math::detail::bessel_zero::cyl_bessel_j_zero_detail::equation_nist_10_21_40_a(v, pol);
            }
          }
          else
          {
            if(v < 2.2F)
            {
              // Use Eq. 10.21.19 in the NIST Handbook.
              const T a(((v + T(m * 2U)) - T(0.5)) * boost::math::constants::half_pi<T>());

              guess = boost::math::detail::bessel_zero::equation_nist_10_21_19(v, a);
            }
            else
            {
              // Get an estimate of the m'th root of airy_ai.
              const T airy_ai_root(boost::math::detail::airy_zero::airy_ai_zero_detail::initial_guess<T>(m, pol));

              // Use Eq. 9.5.26 in the A&S Handbook.
              guess = boost::math::detail::bessel_zero::equation_as_9_5_26(v, airy_ai_root, pol);
            }
          }

          return guess;
        }
      } // namespace cyl_bessel_j_zero_detail

      namespace cyl_neumann_zero_detail
      {
        template<class T, class Policy>
        T equation_nist_10_21_40_b(const T& v, const Policy& pol)
        {
          const T v_pow_third(boost::math::cbrt(v, pol));
          const T v_pow_minus_two_thirds(T(1) / (v_pow_third * v_pow_third));

          return v * (((((                         - T(0.001)
                          * v_pow_minus_two_thirds - T(0.0060))
                          * v_pow_minus_two_thirds + T(0.01198))
                          * v_pow_minus_two_thirds + T(0.260351))
                          * v_pow_minus_two_thirds + T(0.9315768))
                          * v_pow_minus_two_thirds + T(1));
        }

        template<class T, class Policy>
        class function_object_yv
        {
        public:
          function_object_yv(const T& v,
                             const Policy& pol) : my_v(v),
                                                  my_pol(pol) { }

          T operator()(const T& x) const
          {
            return boost::math::cyl_neumann(my_v, x, my_pol);
          }

        private:
          const T my_v;
          const Policy& my_pol;
          const function_object_yv& operator=(const function_object_yv&) = delete;
        };

        template<class T, class Policy>
        class function_object_yv_and_yv_prime
        {
        public:
          function_object_yv_and_yv_prime(const T& v,
                                          const Policy& pol) : my_v(v),
                                                               my_pol(pol) { }

          boost::math::tuple<T, T> operator()(const T& x) const
          {
            const T half_epsilon(boost::math::tools::epsilon<T>() / 2U);

            const bool order_is_zero = ((my_v > -half_epsilon) && (my_v < +half_epsilon));

            // Obtain Yv(x) and Yv'(x).
            // Chris's original code called the Bessel function implementation layer direct, 
            // but that circumvented optimizations for integer-orders.  Call the documented
            // top level functions instead, and let them sort out which implementation to use.
            T y_v;
            T y_v_prime;

            if(order_is_zero)
            {
              y_v       =  boost::math::cyl_neumann(0, x, my_pol);
              y_v_prime = -boost::math::cyl_neumann(1, x, my_pol);
            }
            else
            {
                      y_v       = boost::math::cyl_neumann(  my_v,      x, my_pol);
              const T y_v_m1     (boost::math::cyl_neumann(T(my_v - 1), x, my_pol));
                      y_v_prime = y_v_m1 - ((my_v * y_v) / x);
            }

            // Return a tuple containing both Yv(x) and Yv'(x).
            return boost::math::make_tuple(y_v, y_v_prime);
          }

        private:
          const T my_v;
          const Policy& my_pol;
          const function_object_yv_and_yv_prime& operator=(const function_object_yv_and_yv_prime&) = delete;
        };

        template<class T> bool my_bisection_unreachable_tolerance(const T&, const T&) { return false; }

        template<class T, class Policy>
        T initial_guess(const T& v, const int m, const Policy& pol)
        {
          BOOST_MATH_STD_USING // ADL of std names, needed for floor.

          // Compute an estimate of the m'th root of cyl_neumann.

          T guess;

          // There is special handling for negative order.
          if(v < 0)
          {
            // Create the positive order and extract its positive floor and ceiling integer parts.
            const T vv(-v);
            const T vv_floor(floor(vv));

            // The to-be-found root is bracketed by the roots of the
            // Bessel function whose reflected, positive integer order
            // is less than, but nearest to vv.

            // The special case of negative, half-integer order uses
            // the relation between Yv and spherical Bessel functions
            // in order to obtain the bracket for the root.
            // In these special cases, cyl_neumann(-n/2, x) = sph_bessel_j(+n/2, x)
            // for v = -n/2.

            T root_hi;
            T root_lo;

            if(m == 1)
            {
              // The estimate of the first root for negative order is found using
              // an adaptive range-searching algorithm.
              // Take special precautions for the discontinuity at negative,
              // half-integer orders and use different brackets above and below these.
              if(T(vv - vv_floor) < 0.5F)
              {
                root_hi = boost::math::detail::bessel_zero::cyl_neumann_zero_detail::initial_guess(vv_floor, m, pol);
              }
              else
              {
                root_hi = boost::math::detail::bessel_zero::cyl_bessel_j_zero_detail::initial_guess(T(vv_floor + 0.5F), m, pol);
              }

              root_lo = T(root_hi - 0.1F);

              const bool hi_end_of_bracket_is_negative = (boost::math::cyl_neumann(v, root_hi, pol) < 0);

              while((root_lo > boost::math::tools::epsilon<T>()))
              {
                const bool lo_end_of_bracket_is_negative = (boost::math::cyl_neumann(v, root_lo, pol) < 0);

                if(hi_end_of_bracket_is_negative != lo_end_of_bracket_is_negative)
                {
                  break;
                }

                root_hi = root_lo;

                // Decrease the lower end of the bracket using an adaptive algorithm.
                if(root_lo > 0.5F)
                {
                  root_lo -= 0.5F;
                }
                else
                {
                  root_lo *= 0.75F;
                }
              }
            }
            else
            {
              if(T(vv - vv_floor) < 0.5F)
              {
                root_lo  = boost::math::detail::bessel_zero::cyl_neumann_zero_detail::initial_guess(vv_floor, m - 1, pol);
                root_hi = boost::math::detail::bessel_zero::cyl_neumann_zero_detail::initial_guess(vv_floor, m, pol);
                root_lo += 0.01F;
                root_hi += 0.01F;
              }
              else
              {
                root_lo = boost::math::detail::bessel_zero::cyl_bessel_j_zero_detail::initial_guess(T(vv_floor + 0.5F), m - 1, pol);
                root_hi = boost::math::detail::bessel_zero::cyl_bessel_j_zero_detail::initial_guess(T(vv_floor + 0.5F), m, pol);
                root_lo += 0.01F;
                root_hi += 0.01F;
              }
            }

            // Perform several steps of bisection iteration to refine the guess.
            std::uintmax_t number_of_iterations(12U);

            // Do the bisection iteration.
            const boost::math::tuple<T, T> guess_pair =
               boost::math::tools::bisect(
                  boost::math::detail::bessel_zero::cyl_neumann_zero_detail::function_object_yv<T, Policy>(v, pol),
                  root_lo,
                  root_hi,
                  boost::math::detail::bessel_zero::cyl_neumann_zero_detail::my_bisection_unreachable_tolerance<T>,
                  number_of_iterations);

            return (boost::math::get<0>(guess_pair) + boost::math::get<1>(guess_pair)) / 2U;
          }

          if(m == 1U)
          {
            // Get the initial estimate of the first root.

            if(v < 2.2F)
            {
              // For small v, use the results of empirical curve fitting.
              // Mathematica(R) session for the coefficients:
              //  Table[{n, BesselYZero[n, 1]}, {n, 0, 22/10, 1/10}]
              //  N[%, 20]
              //  Fit[%, {n^0, n^1, n^2, n^3, n^4, n^5, n^6}, n]
              guess = (((((    - T(0.0025095909235652)
                           * v + T(0.021291887049053))
                           * v - T(0.076487785486526))
                           * v + T(0.159110268115362))
                           * v - T(0.241681668765196))
                           * v + T(1.4437846310885244))
                           * v + T(0.89362115190200490);
            }
            else
            {
              // For larger v, use the second line of Eqs. 10.21.40 in the NIST Handbook.
              guess = boost::math::detail::bessel_zero::cyl_neumann_zero_detail::equation_nist_10_21_40_b(v, pol);
            }
          }
          else
          {
            if(v < 2.2F)
            {
              // Use Eq. 10.21.19 in the NIST Handbook.
              const T a(((v + T(m * 2U)) - T(1.5)) * boost::math::constants::half_pi<T>());

              guess = boost::math::detail::bessel_zero::equation_nist_10_21_19(v, a);
            }
            else
            {
              // Get an estimate of the m'th root of airy_bi.
              const T airy_bi_root(boost::math::detail::airy_zero::airy_bi_zero_detail::initial_guess<T>(m, pol));

              // Use Eq. 9.5.26 in the A&S Handbook.
              guess = boost::math::detail::bessel_zero::equation_as_9_5_26(v, airy_bi_root, pol);
            }
          }

          return guess;
        }
      } // namespace cyl_neumann_zero_detail
    } // namespace bessel_zero
  } } } // namespace boost::math::detail

#endif // BOOST_MATH_BESSEL_JY_ZERO_2013_01_18_HPP_

/* bessel_jy_zero.hpp
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
*/