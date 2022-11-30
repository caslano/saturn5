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
// of the Airy functions airy_ai and airy_bi on the negative real axis.
//
#ifndef BOOST_MATH_AIRY_AI_BI_ZERO_2013_01_20_HPP_
  #define BOOST_MATH_AIRY_AI_BI_ZERO_2013_01_20_HPP_

  #include <boost/math/constants/constants.hpp>
  #include <boost/math/special_functions/cbrt.hpp>

  namespace boost { namespace math {
  namespace detail
  {
    // Forward declarations of the needed Airy function implementations.
    template <class T, class Policy>
    T airy_ai_imp(T x, const Policy& pol);
    template <class T, class Policy>
    T airy_bi_imp(T x, const Policy& pol);
    template <class T, class Policy>
    T airy_ai_prime_imp(T x, const Policy& pol);
    template <class T, class Policy>
    T airy_bi_prime_imp(T x, const Policy& pol);

    namespace airy_zero
    {
      template<class T, class Policy>
      T equation_as_10_4_105(const T& z, const Policy& pol)
      {
        const T one_over_z        (T(1) / z);
        const T one_over_z_squared(one_over_z * one_over_z);

        const T z_pow_third     (boost::math::cbrt(z, pol));
        const T z_pow_two_thirds(z_pow_third * z_pow_third);

        // Implement the top line of Eq. 10.4.105.
        const T fz(z_pow_two_thirds * (((((                     + (T(162375596875.0) / 334430208UL)
                                           * one_over_z_squared - (   T(108056875.0) /   6967296UL))
                                           * one_over_z_squared + (       T(77125UL) /     82944UL))
                                           * one_over_z_squared - (           T(5U)  /        36U))
                                           * one_over_z_squared + (           T(5U)  /        48U))
                                           * one_over_z_squared + (1)));

        return fz;
      }

      namespace airy_ai_zero_detail
      {
        template<class T, class Policy>
        T initial_guess(const int m, const Policy& pol)
        {
          T guess;

          switch(m)
          {
            case  0: { guess = T(0);                       break; }
            case  1: { guess = T(-2.33810741045976703849); break; }
            case  2: { guess = T(-4.08794944413097061664); break; }
            case  3: { guess = T(-5.52055982809555105913); break; }
            case  4: { guess = T(-6.78670809007175899878); break; }
            case  5: { guess = T(-7.94413358712085312314); break; }
            case  6: { guess = T(-9.02265085334098038016); break; }
            case  7: { guess = T(-10.0401743415580859306); break; }
            case  8: { guess = T(-11.0085243037332628932); break; }
            case  9: { guess = T(-11.9360155632362625170); break; }
            case 10:{ guess = T(-12.8287767528657572004); break; }
            default:
            {
              const T t(((boost::math::constants::pi<T>() * 3) * ((T(m) * 4) - 1)) / 8);
              guess = -boost::math::detail::airy_zero::equation_as_10_4_105(t, pol);
              break;
            }
          }

          return guess;
        }

        template<class T, class Policy>
        class function_object_ai_and_ai_prime
        {
        public:
          function_object_ai_and_ai_prime(const Policy& pol) : my_pol(pol) { }

          boost::math::tuple<T, T> operator()(const T& x) const
          {
            // Return a tuple containing both Ai(x) and Ai'(x).
            return boost::math::make_tuple(
              boost::math::detail::airy_ai_imp      (x, my_pol),
              boost::math::detail::airy_ai_prime_imp(x, my_pol));
          }

        private:
          const Policy& my_pol;
          const function_object_ai_and_ai_prime& operator=(const function_object_ai_and_ai_prime&) = delete;
        };
      } // namespace airy_ai_zero_detail

      namespace airy_bi_zero_detail
      {
        template<class T, class Policy>
        T initial_guess(const int m, const Policy& pol)
        {
          T guess;

          switch(m)
          {
            case  0: { guess = T(0);                       break; }
            case  1: { guess = T(-1.17371322270912792492); break; }
            case  2: { guess = T(-3.27109330283635271568); break; }
            case  3: { guess = T(-4.83073784166201593267); break; }
            case  4: { guess = T(-6.16985212831025125983); break; }
            case  5: { guess = T(-7.37676207936776371360); break; }
            case  6: { guess = T(-8.49194884650938801345); break; }
            case  7: { guess = T(-9.53819437934623888663); break; }
            case  8: { guess = T(-10.5299135067053579244); break; }
            case  9: { guess = T(-11.4769535512787794379); break; }
            case 10: { guess = T(-12.3864171385827387456); break; }
            default:
            {
              const T t(((boost::math::constants::pi<T>() * 3) * ((T(m) * 4) - 3)) / 8);
              guess = -boost::math::detail::airy_zero::equation_as_10_4_105(t, pol);
              break;
            }
          }

          return guess;
        }

        template<class T, class Policy>
        class function_object_bi_and_bi_prime
        {
        public:
          function_object_bi_and_bi_prime(const Policy& pol) : my_pol(pol) { }

          boost::math::tuple<T, T> operator()(const T& x) const
          {
            // Return a tuple containing both Bi(x) and Bi'(x).
            return boost::math::make_tuple(
              boost::math::detail::airy_bi_imp      (x, my_pol),
              boost::math::detail::airy_bi_prime_imp(x, my_pol));
          }

        private:
          const Policy& my_pol;
          const function_object_bi_and_bi_prime& operator=(const function_object_bi_and_bi_prime&) = delete;
        };
      } // namespace airy_bi_zero_detail
    } // namespace airy_zero
  } // namespace detail
  } // namespace math
  } // namespaces boost

#endif // BOOST_MATH_AIRY_AI_BI_ZERO_2013_01_20_HPP_

/* airy_ai_bi_zero.hpp
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
*/