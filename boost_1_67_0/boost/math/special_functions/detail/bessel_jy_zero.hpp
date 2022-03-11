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
        const equation_as_9_3_39_and_its_derivative& operator=(const equation_as_9_3_39_and_its_derivative&);
        const T zeta;
      };

      template<class T>
      static T equation_as_9_5_26(const T& v, const T& ai_bi_root)
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

        const T v_pow_third(boost::math::cbrt(v));
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
        const boost::uintmax_t iterations_allowed = static_cast<boost::uintmax_t>((std::max)(12, my_digits10 * 2));

        boost::uintmax_t iterations_used = iterations_allowed;

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
        template<class T>
        T equation_nist_10_21_40_a(const T& v)
        {
          const T v_pow_third(boost::math::cbrt(v));
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
          const function_object_jv& operator=(const function_object_jv&);
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
          const function_object_jv_and_jv_prime& operator=(const function_object_jv_and_jv_prime&);
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
            boost::uintmax_t number_of_iterations(12U);

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
              guess = boost::math::detail::bessel_zero::cyl_bessel_j_zero_detail::equation_nist_10_21_40_a(v);
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
              const T airy_ai_root(boost::math::detail::airy_zero::airy_ai_zero_detail::initial_guess<T>(m));

              // Use Eq. 9.5.26 in the A&S Handbook.
              guess = boost::math::detail::bessel_zero::equation_as_9_5_26(v, airy_ai_root);
            }
          }

          return guess;
        }
      } // namespace cyl_bessel_j_zero_detail

      namespace cyl_neumann_zero_detail
      {
        template<class T>
        T equation_nist_10_21_40_b(const T& v)
        {
          const T v_pow_third(boost::math::cbrt(v));
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
          const function_object_yv& operator=(const function_object_yv&);
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
          const function_object_yv_and_yv_prime& operator=(const function_object_yv_and_yv_prime&);
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
            boost::uintmax_t number_of_iterations(12U);

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
              guess = boost::math::detail::bessel_zero::cyl_neumann_zero_detail::equation_nist_10_21_40_b(v);
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
              const T airy_bi_root(boost::math::detail::airy_zero::airy_bi_zero_detail::initial_guess<T>(m));

              // Use Eq. 9.5.26 in the A&S Handbook.
              guess = boost::math::detail::bessel_zero::equation_as_9_5_26(v, airy_bi_root);
            }
          }

          return guess;
        }
      } // namespace cyl_neumann_zero_detail
    } // namespace bessel_zero
  } } } // namespace boost::math::detail

#endif // BOOST_MATH_BESSEL_JY_ZERO_2013_01_18_HPP_

/* bessel_jy_zero.hpp
wAMVBAwFBeuGuVJDYb1z2dFgNiHnVKxmeQcHvt1eILcYWMUpMWkiF8BItk+5odOo3XF+IMBQgIHhBEUlwxwZHqQUpvDjozxZKyXkg/ye62EFTHKB1s+2kcqzWUIRqzI+7FaZW2dRRNfsfYwsSacmP/ObKtAqZubPfzYxovP9x98h17r5aFdaPqXRZ1/RhRT39C+rUOoi31hBXLi3PYtlIeBHicKe98ws3O5WU34MLhmXTfxnXdiAXtu4px2fW0SzCM+jF1DK6JYRyrxQzNMqvsfui8e7PF54fEH0p+hpGbVZ4euUfiog3yLSoCMoTO/Uz+XlCRPliSWRqsiBfr4Guu/cZxkN1Ph8OrgSEBaZsX4WWtHY98aPPWwITOMQMeFmh2E5G5n94DjVT0TqPTFvN5gPU7dU9udZ9IrD8wQ6sBjVi4Mm5lN9m3hNxA0JGRlRn63Hk5fjVo+pEU8F77VLKhw+06CcFYpr3Bw8bRGY1pqmjXqQCMPRbkraCDjuYtAOcJBMmFdUupVeuSoNFZiaT5QDttGNtj/+V8pqECHmlxwCWZTw7iweiGvONQIh/kZi6zhHEtYlIpdnjpumUYDGDRu+hguIcZBlsfE1RpmwpaMwgI9ltiqsYOTqy8hmj77dH1XXIZbQG0tzrI1r+DzyzWOB2PAG9rOrApV1VOEBpwCVtvEK7gXCJo8EmfTKeDM/zb8EoZ0Y9NHV7sb5rOROnjSKgh5lujHaFKaITjznenS0vttYV0srtsYYLkjTgkyfCDODfPnA+9E/MIgP/bLuX207JUAIsqOV2VM83Tg/Wdm0mhWLRe5ON609MK/ObJu9B0dRU9Ic7x2yc/Gx5SQG7Ysl4fanTKqaLhSkXZb1FGvh+Xe9deHoZoBg8ZKuJIBbr5zMSbVXJxGiHVrAYAlFkGj0tfwQopp3IBF2HnJTvAptj7/OPNSfKNaSSH46x1Xe9z4vuAICj7qyvb+8vm2Ca1RKs/wNJE7Evouyjlz470XIUT4Sb4pJrefbb7cEvnn0Jj/kJKCmFB3ccG+/AQsBuLXSsQNwM+8DvwHWY2joJXNoDwz/12IkktouKhVvk6AjG2+PZ5IbIpYXjPE/CPDxS6wuUMd74h+9W212HZ4ev3fGmeoQqSvrNPP8W7fZXIZ0rB89onm8O9lrJtU1RojXtkax32IxUmRPyYpz7TZKza0zie+3UrxPc80N4rURDeRichpNyNmrPuslY7DK8PEENo4hbm7zSkW3YxYaI//Xz+bTAI48leYAepNUpVzNtGzNK9nFehS8tdaapIT4/LvBUWhDjfuer0rdiQs15KnkO0vjoiXj5so1uKd9qU2EuMbXviTl36bgDRq25lfuqEj7Zw3m11fIPfpPbStPnREVhhRc3iAVS70WbYuYCk4td/VVi/0f73s340xKZf3uXKtaQNygD+YLiXD68LmtS4D80ZzjO6nb1vn64FhEUdntlOyR2ruM+dx4Kdmtoz6NeoE7/bzqldiHDqBF7nCBP+dfZ48SwYCz9XNBg1Nd2LZGayYJhlGV9o31LfczmdZf3sP2M3wMxMcutIvU3p3RGwyy9w3nZxyyVE8NfdkRZ2Hf38DUhOFuaEvu5WYOE3ReJ2LP9qarPQcBfh8Br5+LLtu8WRSnTt2g3OSr2fY18eUuLz4GD5dZOjPH9n+s54xl/YQjwsAr3oCyXc++W1rxCEgdXPZNmNwxN4vPNSB5HHykGhqubSWnMC7lnNstdnQ3nIa4p56ffYctzgVoI2/jChp3cz8/XB/HBWZ/u9tKRJ8zuIZmmcgFrtpZEa6vTtzTOd5aXAM21IFeRcks2z+/lzd8/KrM+Chq06oEZuHdJnQ/TrR6tAB1jUksPFuYXPN66rXcvJnKlTa1LSSbUUb7ybn+afeX/tSOO8sayie8DxFoMzatLkGWaDhGtwGczUc0t7X8PFPvhjhe6ixKnDvfBUeyOL6fgW0wVYEM/4Y5pYJ5iSVNtm80RphQ2oBn4TnhXmyq5dQnvcjN3tlOLmazwOf3V9FzTJ8fYXNq2tCF5lG7BZNxU/qNQh1uXcbuaBjkoR1bNevvmXPkG3cyY6s9stQ7XlGh0egjcJQNTySl8XHq0ljr7UzwtCeCEuTFXTbn8sObrclO4diBLzCjpv+3fL61YHzMx5y7y7eBpoLr+xtom5usf9qj19ivx23XSeL33k57YLfdzEcIP6/Ni4mjCYSPyU6PaqhVYZEpL8LJvU5e2sXu2Frcd+25Yjljo2SNMyFNNsc9e7URqb3czghz8VSEG2j+nnFF8GmbnPpru2fQ33Rz7qoNS4xVg5c2sfLa8iX2Qzi5W7S6qqxNrSYZ+autYN/AahtBOHTw9nTIwv+8GV/mp0v7vwNC7qqrm5zFOFl3d5iZ8Yy+q4kPHo+TVXNjH1dFGXuQg0O+9eBTMDhs0LpB7YsvYPmg6DSRWglDM314ppwNb6llMufK57h02IyMixXnXy7HynPxIuoYzb0j/BS1223ar5PgfpHw7HyaiZ1ZxyTpj8WRo+eg0IONPbamj+6SQPvs8/QKg/d8L8toyBicPJFI6/nQxPWAcbPxHyerCEQFwjP9hDZYtJ617YTb3vr4q079EwjkUig+7Tfq0tbfxoTEi6kMvLEDS2ewMunvZ5Jjp0H0Mt///XkpE6vbERcus12rXagbntfa1YCvPvDU2I6aiHicSc+H8H3Q6dy7BX71RgkEB/EfF1gfW1j/w00YuRrA4QMQkqEgGUejJh68RYKf0yMWnwvVFRXJXLuM2rqbki1evu5nReT17Fod9tnf/prLhvvqXwfUB6OUCdP4svnIP6+h4iuAlYfP2P0FxT87FhpJczoCQZYRSs9t1qN/eIP4d5g1M665YqSOpA2SLgET9oM+IBIvN80J+CifYvmXC5mV4dn6dD4mLgxb+vH7NtcfxdmxKip7OZO+/iQChJpIJ7sNdzeR9ePwNecl0uQnfIQhILYecg6z9KQpYerieuvDcngbG2GzoRvjbpuoufeTwERvGV6bKGJjdzcgMs2cNj0gh9gPuuJ9qz70eYCIB1+e4OYQEOD+Oznc/2JpRHWy6IBTN63oNaqH/ufj+zRWyX9R9WSJ/R054EPs8qP9F5+0XFktnPTqKWZt5PKrwW9fv8+aviVEiyrc293d/LpoDDXTp4l8pd/j6u23F8ppbWrEz7jozXIAVaI/LqymLJaNhZjb5LbOBfpuIrYp3LxN7Z2c2YJmmsgdjpoYfngeEbfQ0Xej7oqwuR9zJzgN9Ao90re52YGlQZv3s2z4UV8ugCgol/pIGliRmra4oFNQ7+w5tS42bC4W/5O4Np2LhB+AOv4mYWmX5XcC5OHV6UUP5L5ac4eJGsmpiy6JJonn28D/D4wmQFuBUvzbQ0Jg8/4vk5LhBpj+pDPxnv6lokpASLe7mf60/+8QXPm/ygWtTf4nosL8B9kaJfzf228n2gfcl3boR627UiB/6QJqVZTvxmCnEXuRlhg75tTJHwB2h+ckJDULyFSZmrr1TgRkt/ZVyPv8K6dNEPrVfFGM9+zQH73qsYgsvmksM5t/teoCi1fbjTM8BCvBWoCRV2iQASUA/iHu9qGwkGgWEISlRx25VyBnQU6IqZFwrtat23PWv0u+lBVdmr+Tfn7t8tws5wb8v/zg/fyAQWnc5xWqzmAW47ZPGyHigM/nGV9yNbUnFbymboVFUXYmeOIER0TBl7I4euCBpv8ODyagq6oNC6Y11jPkBvejRJrPTIpB0OubsPoFBkc6sKPHn6tuvkqWRiuylkWaFJ7n1dEANk2VTOjVt2YXYbEN/ZyEW/QVfphR8CC7eHwx+0K8YGXQqGsvcxNlvvvdTrTxvU23cBPFqtqj+NSwqgCSh2vCcf93uuxonTMhmQsy91uz27cW+CpS560nTGV4mOTIqlH57ejmT3rSDH1uaSLoW2XXmfOP8aclTVAKeCeAkKS2WWJY5UvTePcINuAQwnp7raFNoLwnE9YXiZgeJTHcNJsjDIbg+eRvW1IFAaIZ0Nsy3A1W03y8UKJbjWQxEgISZYSVVCWid90vsLHm7W1zwrYPriX0x/VfmW0jJp/uQ2Dd7SUTWi4xfAH1/SjUm/s3qWn2QsKenY/qunso3OPxz7Tq9LqTm/wVkIcvamNVj+u8hnkipsH/vcpvGzqeUEEtpoohQ+LaRZGy+v+Sgkr4Yi9cViaVoqooQ9LTHdQokr0wtLmZVxcQwkKjXWFUiiSfR2eHETXjKvAi7A44X/jLoZoynuiNY4UIJlQ8S3UaR1TRisxxMfqrHW3yEBq+X3UX/AvUSS9iOrVB5ekHtjAFb6rXIS0c0XilP346Tz1lSSzAODFlYvGDUeYTX4DNshdbX4Zg5zloDc0xVSKnRwTWZNqtGRT17HZET8G5GVuMVDmj3AWCVhPpM3BTY1C+E4vZJlV9YrGt2i1n86713mArLoYN8MTvLga0H0SDyOcikTz7dfdVQ6y5LeuETflUB6paBJz6BNS8EcPRttN42tBJlyRGm3gwg8A6rXR6T360eNGQ4lJLAWYFuxCbaR3dNgSLpgEUuENvTLlYmt0B1bzpBXw376jPj9NTxF4Pmw9WzQ3E2obGiA/vVX67/PlXPh2sk+E8bymElXS2KU3Zc25CXOGb+3hr/SrYU/S2HMrOPBTzGUyM3BqVxBEpbRFtjMzZtGUJqyfkSYHPBVQ7iIHFFrrSovyZ75l1HcMgoXiGQLl2bTiGie82bvTROYjI8N8rCAjsVGkulxeTqQWQ/RtM/l+HKZC82jnvhCBSJMfb8wKn+RzYOqcfN/t52Y6CecK5ok4XX9Ogb6P3LTDJL+NEWTkXJZos8P07elayu+UlLOcpBhfe30q7H9aeX3SEMFbxwllLH2DEffzEvPfJd5sMwgtHwcVjUwUfPjetnQiyhHXp5x596sB3SED3fPQwyb8bl03tA39HLQ6fRQhu0EqSsi3pfGn2xa4UipQBAIdmLApr8kQtLSF7Za2bHZV4iAl/SXkYqRsiGU4Xlr8Sb7P9np26tiszTr9VUxtO1LAxfcWuNLXkXZwmBcfPoJZdeYt14GQBLxy/gaogJuvz6A8Jt/rXIADGzjja8SfXHJ2zOeObelm4hX+mo/HtGY8s6TGpuXfC1dq50SKrtVg7bBtvgcL1RnithfQ6oIWRads6ebP8/X9aNStt/SYAk5jXuqN0jjR1bdeDieCq8jJs7UJwX2RexFazNpChtePXKCyrV6h12W/a2vvyBtNAbs+6NiL1DbdrxOO8GrVJ6ywyhUqHmPM3b4n1SZ3OVYhsAN6whv9Y24EQyYml1iLiKtaZ5DynxGiih6oz5cjmIFAD6koF4ASDI/nQ/0m95n+nkbz2ZMH97piP42IcNj5RtLIGQvlJxoeYRmO48rWTVOuCa2KLVLi7gCOgKfFMX/GFBZFo9jgkHz3zwPBjMHlgOgwBV01Il5LOCYoh2knU6JCoxOuHcXsxAhUz0HfPw+i3ohjM9e8Ya1wKA/xz7rkQ6FeaNEgKRyb5LDmVKXS40UadDZd96hl2W2ZeqJcSjboqV4nhOfi736ckWuTofsCX+CKyZ4vRbz+dsZ3onnmeZJwJSFPhawm1zLMo7QwKBwZMwXTX7qdYtO5TkRko4HMTU7LUbMbVOWOhiPIT3k3nPPmKuzYhdLaI14GLBZwD3N0p7nyvZGbPyYaxCaGD0wzplw+d46ncj+gapoWg2XVUidiHwMF8nt7EgfaJZx6FTkJJZE2QPw9TYdZwMcivUdvoDxSQSZT/tcz2FVSnynoIa34m7tz8d7j71QBls7ZGZbW0K+g4/RthfOobTAC7XkMGjSSkdXfi1gsgRogjW/pnaBCLo9hrhBgWU4TIHsEGVVj/WEF74pUF6qHkIh+Tw8SD8iQfXG/VtL9VTcNXlyZ+y5qBEuw4pgQybsqgjcCxaOz6JoBtWIKFg2Z8zZq3C7ICQZ6WVVcjKbvQTjCjw3fdWYdncmn5n7tS772FtfQ2DXvY3cEAPnITTwHAq3oRYLKq0+uYPOrr1nUQnOrjFPDs6WLS3NvpfAqeElbtxBdVdANJ9+/7WQemjeKLdplT5Ys3og8Qgr65hAdTkLNlqZTAO4qvyU2v1C8cfNWIGEAQGuaeXdERkLjG5WWoQeFj33PD1GaHNEdxIfpulOIGv349X/3jk/KaO5yWNC8Evbj65G0ZPpTcf9eRzjhVKMBtuUghk/guuBQiA/89MkqrfctDcFKr4ieBpORQX14bV591p8LPdHLGVMtavgEJmB997aW8Qu19L41m6O+tN3LCKfISqV2eeNvm2Swz6qcvLy6fm98803bldnu3BbgJwdrKZm5StMWVshGbb/PbkNG+f2cT8hGW1h8vz5LSgZhhT8LyZa9VkqJSSzogea48Z/UdCkJymG5+QRWn2eHGhGst1n7EKQ7/uXspPw0O0EIPCUOhU03l7dsWyCXsPjQ0zaI8BMuKvU3MuoSBKwP18ix5bFOr+eVw60vdPo/C9RJHnrqnu5+YXc39QAGuEk/ajDCnImRr1xsz+L/gIfP5p9661tPuYffL65SHKoyCdMcZTsYMFWyxH6eM7WFtxMdahhW90yw2FbgFXu6UqmkNo+O2fOzQV85oAH01fvrMGZ4kIzsgkUAyMANu8Um1g2SL5CCvdYOqynUZ/RgoNmdA/ORePfxlNvvSbSMDQ2z7yPP0S0yDWNSne2e4pjg3iL2wbnAm+7VPp0XJLz0X2eK/EgiKp0aB5SZWsT5G/5fyenYCicotu/PmRZRBwgsuENEzI03KZYpa31WJ3oB4gph8xHdWy9K6OPc//b9kKrN6N+zTPr/ULAc/uh9nb2tXy9AUniG5JMTnGSZgV1H2lv3J6x5w2V20dqQ3rfad1/86LdSEXxD4wbyvfbolJIZKAgAugvoNBcN89dyotxL9x7AQI25ZofWhdmo7eI7yrVYktD+TzygOtXpEDlHwsF6FNy/bZcvBAdxfx5fivMos5j9WKRPYwabCIJvqqOBAaNbqLk/vXX49bLn8X39Sc8L/84b8m/vxzOjs1zR4gg3uGm+RMXS1EMfMD9BKUabBMEUePddNEPeRDTHzQjY/pw9X1ajlI7/5EbfNR3pc6PbDyRVMm8CgPIg0ULjJ3TsBVgGYI/uR13+XvIkfMpXim5lXdMyvTBtMFbmwcPASsRALGsRFgqU70pnVCtDFUUCxr35RW354aqVlQ/D9yb/4xzJIxX3XiI+r0gmV80x/UFYZqyAYr/RGnx43vOIvrPJAaTDYryZD5bI5I7DLLMr+/5unEs9NFrhuqK3w475f4JHR628IXnThD9pn5ZYeyl6MizOucFmpz9bbPCUyNxA3/bDZBi1/Zqoez0dGukNtHNvmCl+aFQOD5dZ92jRSW82jvN4FahYjfq5FzCH/OAXPdP/9t/PbPtV0oRo4lF5zi30ktSaB2/5Rm2vRvn71/X2i3bnuKJj4KbaF+FB4PY63NF1eDZnsomzO502htUlsAg9rDGET2zu5pL6ORpMF9EOCgWVaxPhvHjGtSYlVHSMPX9Jp0M5mqKImusk5Pf+yt+qH24jRd+YAT7FYQYGnm5cTS6A5wal+fW2tmdGR18XLwYBTgcTLrVHf/k3rKTrDvMC7OCA64NWmEvdiCFJdOPtLXNyiq2cyfM3aU7SfkXtcyoirLJOJ2ALsbvXWvM2LKvMMhPdP3UDYDsshP+g7xpwyIO7Up9062hi5W46FthLpfvqDaTVepiiBan2b6imNeCRcdIYDCaoM9/JMSK+UkkfRgxWa5oadSsff7mr26n0+fYedKlP5s2BnJv2+qddtBNlcr6hMYtViMqDXpRkwrrDq2ylW2AORBfZBLc66sEIYpJKIfga0kP/7g/SnV7kMChcZpni74cc+W4R4q8WSqcBpfP6ob0/IeK9Tq+lKUvWAu27frUZJeYCnZ9/Z7OV+dOd3BleysxIB/85ysb8qChAOvzYL3rqwx41Ci8tfE+a3nL0mFOSpDGEyG5w4r0UIDajqJY9a90+6gBX/tRPkkP38H2FxD/qYNFyjxtwKXqGgqgyKrmiLpAVRk8QrNVkilhlYgP0FILL4gthRjstvPkRU8but9wD14ngyGO4i6GlZOHbb5shCx2K5THEVL34XAPWW9ssAssxPyFfr5U8nmDExoiWoVlOp8J2hVPaH3CeO3Y4m8WkXO0+yX8u+fo/vRud/eXUwq2/z5EIeQQuoFsHr7lIPQPIJ0pjq+zsYD85ZnUocpU/z8VKAKvCPZO9nPXUUse9XdhFklKRDUVDiFi51+9X0Np5hNp84ymfDKueHgZx8ao24+G2+7BK5nl9WJ6d7WyMxRdNmAWZqrYKn9oP03EDgVLqlEE2BrtAZh0aVQWJ7lDuv/19fIPyBG69ISwTqPJLGNOpqgyYvi2pK91JOlUntgtlhdc1zawqrsPaKSYdDN5UX4vAT0cvj4oo3q3+UJb8o5CBaWGrrraH8n27EOkdXw8arh8kekxP7hFuSkxaaQkJf3faIuTSRY3CGwRgnzISgnO5W3DS1DHMe16tt8LHtVtKpgnDVuThGf9OFS/4Uc0S1yxY70HGxgKhZFFjq99QiqaWCKUhUeEcuJb6K+6lki3F+gzdaoTGUSFwQt2QSa4lGSPEk8SdKsKBpX5ejcBuUIgghXjQ30ddVOfSQLcmuR4Z2cDPJ+q5314ZRil6yuDWudzkvtGhCwrf8gCZbv0F9aZMx2h+sSOQ/+7G+jTSfkVd6McAJmRO2MF77TZWEO5Gg9yreYqJwZNFlrjQCIwBE+7p7Ik0s5OAVfBVho+BmCuie9HKpThBYowLRMIUJusB5prPKEfZT8zQnLaS7DbHnGvjcSlEh4A7C3+YjqjEcRHU/59w27NW1sBRoDv/tsvuVfdOrXcaUi4IN9ddONN3kw2k/jY6W+cHmz8GnmLic5zsGnmtTDXniVMsSLls1x03RqWCBp/qOe6TWrChZfMkWaDNaGtflbYrKAj2j1641bTCTNejfPY8JJNWVu7ttDnJZBh1ovX+aWSo/FQZegYoRWeQbfRm9tf6SB9iRXz3A7lOh2pxZs1zdtiQiLUrXilMbL2Wg736H4ZqfWAnJ3s8q1sQ15m+1fN6A1y2YMF/VTFmiZ1ULR2yUW9ejzlGJ8RCD1nL9jls=
*/