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
      template<class T>
      T equation_as_10_4_105(const T& z)
      {
        const T one_over_z        (T(1) / z);
        const T one_over_z_squared(one_over_z * one_over_z);

        const T z_pow_third     (boost::math::cbrt(z));
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
        template<class T>
        T initial_guess(const int m)
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
              guess = -boost::math::detail::airy_zero::equation_as_10_4_105(t);
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
          const function_object_ai_and_ai_prime& operator=(const function_object_ai_and_ai_prime&);
        };
      } // namespace airy_ai_zero_detail

      namespace airy_bi_zero_detail
      {
        template<class T>
        T initial_guess(const int m)
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
              guess = -boost::math::detail::airy_zero::equation_as_10_4_105(t);
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
          const function_object_bi_and_bi_prime& operator=(const function_object_bi_and_bi_prime&);
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