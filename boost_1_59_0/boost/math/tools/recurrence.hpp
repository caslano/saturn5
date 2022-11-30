//  (C) Copyright Anton Bikineev 2014
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_RECURRENCE_HPP_
#define BOOST_MATH_TOOLS_RECURRENCE_HPP_

#include <type_traits>
#include <tuple>
#include <utility>
#include <boost/math/tools/config.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/tuple.hpp>
#include <boost/math/tools/fraction.hpp>
#include <boost/math/tools/cxx03_warn.hpp>
#include <boost/math/tools/assert.hpp>

namespace boost {
   namespace math {
      namespace tools {
         namespace detail{

            //
            // Function ratios directly from recurrence relations:
            // H. Shintan, Note on Miller's recurrence algorithm, J. Sci. Hiroshima Univ. Ser. A-I
            // Math., 29 (1965), pp. 121 - 133.
            // and:
            // COMPUTATIONAL ASPECTS OF THREE-TERM RECURRENCE RELATIONS
            // WALTER GAUTSCHI
            // SIAM REVIEW Vol. 9, No. 1, January, 1967
            //
            template <class Recurrence>
            struct function_ratio_from_backwards_recurrence_fraction
            {
               typedef typename std::remove_reference<decltype(std::get<0>(std::declval<Recurrence&>()(0)))>::type value_type;
               typedef std::pair<value_type, value_type> result_type;
               function_ratio_from_backwards_recurrence_fraction(const Recurrence& r) : r(r), k(0) {}

               result_type operator()()
               {
                  value_type a, b, c;
                  std::tie(a, b, c) = r(k);
                  ++k;
                  // an and bn defined as per Gauchi 1.16, not the same
                  // as the usual continued fraction a' and b's.
                  value_type bn = a / c;
                  value_type an = b / c;
                  return result_type(-bn, an);
               }

            private:
               function_ratio_from_backwards_recurrence_fraction operator=(const function_ratio_from_backwards_recurrence_fraction&);

               Recurrence r;
               int k;
            };

            template <class R, class T>
            struct recurrence_reverser
            {
               recurrence_reverser(const R& r) : r(r) {}
               std::tuple<T, T, T> operator()(int i)
               {
                  using std::swap;
                  std::tuple<T, T, T> t = r(-i);
                  swap(std::get<0>(t), std::get<2>(t));
                  return t;
               }
               R r;
            };

            template <class Recurrence>
            struct recurrence_offsetter
            {
               typedef decltype(std::declval<Recurrence&>()(0)) result_type;
               recurrence_offsetter(Recurrence const& rr, int offset) : r(rr), k(offset) {}
               result_type operator()(int i)
               {
                  return r(i + k);
               }
            private:
               Recurrence r;
               int k;
            };



         }  // namespace detail

         //
         // Given a stable backwards recurrence relation:
         // a f_n-1 + b f_n + c f_n+1 = 0
         // returns the ratio f_n / f_n-1
         //
         // Recurrence: a functor that returns a tuple of the factors (a,b,c).
         // factor:     Convergence criteria, should be no less than machine epsilon.
         // max_iter:   Maximum iterations to use solving the continued fraction.
         //
         template <class Recurrence, class T>
         T function_ratio_from_backwards_recurrence(const Recurrence& r, const T& factor, std::uintmax_t& max_iter)
         {
            detail::function_ratio_from_backwards_recurrence_fraction<Recurrence> f(r);
            return boost::math::tools::continued_fraction_a(f, factor, max_iter);
         }

         //
         // Given a stable forwards recurrence relation:
         // a f_n-1 + b f_n + c f_n+1 = 0
         // returns the ratio f_n / f_n+1
         //
         // Note that in most situations where this would be used, we're relying on
         // pseudo-convergence, as in most cases f_n will not be minimal as N -> -INF
         // as long as we reach convergence on the continued-fraction before f_n
         // switches behaviour, we should be fine.
         //
         // Recurrence: a functor that returns a tuple of the factors (a,b,c).
         // factor:     Convergence criteria, should be no less than machine epsilon.
         // max_iter:   Maximum iterations to use solving the continued fraction.
         //
         template <class Recurrence, class T>
         T function_ratio_from_forwards_recurrence(const Recurrence& r, const T& factor, std::uintmax_t& max_iter)
         {
            boost::math::tools::detail::function_ratio_from_backwards_recurrence_fraction<boost::math::tools::detail::recurrence_reverser<Recurrence, T> > f(r);
            return boost::math::tools::continued_fraction_a(f, factor, max_iter);
         }



         // solves usual recurrence relation for homogeneous
         // difference equation in stable forward direction
         // a(n)w(n-1) + b(n)w(n) + c(n)w(n+1) = 0
         //
         // Params:
         // get_coefs: functor returning a tuple, where
         //            get<0>() is a(n); get<1>() is b(n); get<2>() is c(n);
         // last_index: index N to be found;
         // first: w(-1);
         // second: w(0);
         //
         template <class NextCoefs, class T>
         inline T apply_recurrence_relation_forward(const NextCoefs& get_coefs, unsigned number_of_steps, T first, T second, long long* log_scaling = 0, T* previous = 0)
         {
            BOOST_MATH_STD_USING
            using std::tuple;
            using std::get;
            using std::swap;

            T third;
            T a, b, c;

            for (unsigned k = 0; k < number_of_steps; ++k)
            {
               tie(a, b, c) = get_coefs(k);

               if ((log_scaling) &&
                  ((fabs(tools::max_value<T>() * (c / (a * 2048))) < fabs(first))
                     || (fabs(tools::max_value<T>() * (c / (b * 2048))) < fabs(second))
                     || (fabs(tools::min_value<T>() * (c * 2048 / a)) > fabs(first))
                     || (fabs(tools::min_value<T>() * (c * 2048 / b)) > fabs(second))
                     ))

               {
                  // Rescale everything:
                  long long log_scale = lltrunc(log(fabs(second)));
                  T scale = exp(T(-log_scale));
                  second *= scale;
                  first *= scale;
                  *log_scaling += log_scale;
               }
               // scale each part separately to avoid spurious overflow:
               third = (a / -c) * first + (b / -c) * second;
               BOOST_MATH_ASSERT((boost::math::isfinite)(third));


               swap(first, second);
               swap(second, third);
            }

            if (previous)
               *previous = first;

            return second;
         }

         // solves usual recurrence relation for homogeneous
         // difference equation in stable backward direction
         // a(n)w(n-1) + b(n)w(n) + c(n)w(n+1) = 0
         //
         // Params:
         // get_coefs: functor returning a tuple, where
         //            get<0>() is a(n); get<1>() is b(n); get<2>() is c(n);
         // number_of_steps: index N to be found;
         // first: w(1);
         // second: w(0);
         //
         template <class T, class NextCoefs>
         inline T apply_recurrence_relation_backward(const NextCoefs& get_coefs, unsigned number_of_steps, T first, T second, long long* log_scaling = 0, T* previous = 0)
         {
            BOOST_MATH_STD_USING
            using std::tuple;
            using std::get;
            using std::swap;

            T next;
            T a, b, c;

            for (unsigned k = 0; k < number_of_steps; ++k)
            {
               tie(a, b, c) = get_coefs(-static_cast<int>(k));

               if ((log_scaling) && 
                  ( (fabs(tools::max_value<T>() * (a / b) / 2048) < fabs(second))
                     || (fabs(tools::max_value<T>() * (a / c) / 2048) < fabs(first))
                     || (fabs(tools::min_value<T>() * (a / b) * 2048) > fabs(second))
                     || (fabs(tools::min_value<T>() * (a / c) * 2048) > fabs(first))
                  ))
               {
                  // Rescale everything:
                  int log_scale = itrunc(log(fabs(second)));
                  T scale = exp(T(-log_scale));
                  second *= scale;
                  first *= scale;
                  *log_scaling += log_scale;
               }
               // scale each part separately to avoid spurious overflow:
               next = (b / -a) * second + (c / -a) * first;
               BOOST_MATH_ASSERT((boost::math::isfinite)(next));

               swap(first, second);
               swap(second, next);
            }

            if (previous)
               *previous = first;

            return second;
         }

         template <class Recurrence>
         struct forward_recurrence_iterator
         {
            typedef typename std::remove_reference<decltype(std::get<0>(std::declval<Recurrence&>()(0)))>::type value_type;

            forward_recurrence_iterator(const Recurrence& r, value_type f_n_minus_1, value_type f_n)
               : f_n_minus_1(f_n_minus_1), f_n(f_n), coef(r), k(0) {}

            forward_recurrence_iterator(const Recurrence& r, value_type f_n)
               : f_n(f_n), coef(r), k(0)
            {
               std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<boost::math::policies::policy<> >();
               f_n_minus_1 = f_n * boost::math::tools::function_ratio_from_forwards_recurrence(detail::recurrence_offsetter<Recurrence>(r, -1), value_type(boost::math::tools::epsilon<value_type>() * 2), max_iter);
               boost::math::policies::check_series_iterations<value_type>("forward_recurrence_iterator<>::forward_recurrence_iterator", max_iter, boost::math::policies::policy<>());
            }

            forward_recurrence_iterator& operator++()
            {
               using std::swap;
               value_type a, b, c;
               std::tie(a, b, c) = coef(k);
               value_type f_n_plus_1 = a * f_n_minus_1 / -c + b * f_n / -c;
               swap(f_n_minus_1, f_n);
               swap(f_n, f_n_plus_1);
               ++k;
               return *this;
            }

            forward_recurrence_iterator operator++(int)
            {
               forward_recurrence_iterator t(*this);
               ++(*this);
               return t;
            }

            value_type operator*() { return f_n; }

            value_type f_n_minus_1, f_n;
            Recurrence coef;
            int k;
         };

         template <class Recurrence>
         struct backward_recurrence_iterator
         {
            typedef typename std::remove_reference<decltype(std::get<0>(std::declval<Recurrence&>()(0)))>::type value_type;

            backward_recurrence_iterator(const Recurrence& r, value_type f_n_plus_1, value_type f_n)
               : f_n_plus_1(f_n_plus_1), f_n(f_n), coef(r), k(0) {}

            backward_recurrence_iterator(const Recurrence& r, value_type f_n)
               : f_n(f_n), coef(r), k(0)
            {
               std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<boost::math::policies::policy<> >();
               f_n_plus_1 = f_n * boost::math::tools::function_ratio_from_backwards_recurrence(detail::recurrence_offsetter<Recurrence>(r, 1), value_type(boost::math::tools::epsilon<value_type>() * 2), max_iter);
               boost::math::policies::check_series_iterations<value_type>("backward_recurrence_iterator<>::backward_recurrence_iterator", max_iter, boost::math::policies::policy<>());
            }

            backward_recurrence_iterator& operator++()
            {
               using std::swap;
               value_type a, b, c;
               std::tie(a, b, c) = coef(k);
               value_type f_n_minus_1 = c * f_n_plus_1 / -a + b * f_n / -a;
               swap(f_n_plus_1, f_n);
               swap(f_n, f_n_minus_1);
               --k;
               return *this;
            }

            backward_recurrence_iterator operator++(int)
            {
               backward_recurrence_iterator t(*this);
               ++(*this);
               return t;
            }

            value_type operator*() { return f_n; }

            value_type f_n_plus_1, f_n;
            Recurrence coef;
            int k;
         };

      }
   }
} // namespaces

#endif // BOOST_MATH_TOOLS_RECURRENCE_HPP_

/* recurrence.hpp
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
*/