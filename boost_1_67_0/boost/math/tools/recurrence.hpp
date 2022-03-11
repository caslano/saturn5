//  (C) Copyright Anton Bikineev 2014
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_RECURRENCE_HPP_
#define BOOST_MATH_TOOLS_RECURRENCE_HPP_

#include <boost/math/tools/config.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/tuple.hpp>
#include <boost/math/tools/fraction.hpp>
#include <boost/math/tools/cxx03_warn.hpp>

#ifdef BOOST_NO_CXX11_HDR_TUPLE
#error "This header requires C++11 support"
#endif


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
               typedef typename boost::remove_reference<decltype(boost::math::get<0>(std::declval<Recurrence&>()(0)))>::type value_type;
               typedef std::pair<value_type, value_type> result_type;
               function_ratio_from_backwards_recurrence_fraction(const Recurrence& r) : r(r), k(0) {}

               result_type operator()()
               {
                  value_type a, b, c;
                  boost::math::tie(a, b, c) = r(k);
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
               boost::math::tuple<T, T, T> operator()(int i)
               {
                  using std::swap;
                  boost::math::tuple<T, T, T> t = r(-i);
                  swap(boost::math::get<0>(t), boost::math::get<2>(t));
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
         T function_ratio_from_backwards_recurrence(const Recurrence& r, const T& factor, boost::uintmax_t& max_iter)
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
         T function_ratio_from_forwards_recurrence(const Recurrence& r, const T& factor, boost::uintmax_t& max_iter)
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
         inline T apply_recurrence_relation_forward(const NextCoefs& get_coefs, unsigned number_of_steps, T first, T second, int* log_scaling = 0, T* previous = 0)
         {
            BOOST_MATH_STD_USING
            using boost::math::tuple;
            using boost::math::get;

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
                  int log_scale = itrunc(log(fabs(second)));
                  T scale = exp(T(-log_scale));
                  second *= scale;
                  first *= scale;
                  *log_scaling += log_scale;
               }
               // scale each part separately to avoid spurious overflow:
               third = (a / -c) * first + (b / -c) * second;
               BOOST_ASSERT((boost::math::isfinite)(third));


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
         inline T apply_recurrence_relation_backward(const NextCoefs& get_coefs, unsigned number_of_steps, T first, T second, int* log_scaling = 0, T* previous = 0)
         {
            BOOST_MATH_STD_USING
            using boost::math::tuple;
            using boost::math::get;

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
               BOOST_ASSERT((boost::math::isfinite)(next));

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
            typedef typename boost::remove_reference<decltype(std::get<0>(std::declval<Recurrence&>()(0)))>::type value_type;

            forward_recurrence_iterator(const Recurrence& r, value_type f_n_minus_1, value_type f_n)
               : f_n_minus_1(f_n_minus_1), f_n(f_n), coef(r), k(0) {}

            forward_recurrence_iterator(const Recurrence& r, value_type f_n)
               : f_n(f_n), coef(r), k(0)
            {
               boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<boost::math::policies::policy<> >();
               f_n_minus_1 = f_n * boost::math::tools::function_ratio_from_forwards_recurrence(detail::recurrence_offsetter<Recurrence>(r, -1), value_type(boost::math::tools::epsilon<value_type>() * 2), max_iter);
               boost::math::policies::check_series_iterations<value_type>("forward_recurrence_iterator<>::forward_recurrence_iterator", max_iter, boost::math::policies::policy<>());
            }

            forward_recurrence_iterator& operator++()
            {
               using std::swap;
               value_type a, b, c;
               boost::math::tie(a, b, c) = coef(k);
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
            typedef typename boost::remove_reference<decltype(std::get<0>(std::declval<Recurrence&>()(0)))>::type value_type;

            backward_recurrence_iterator(const Recurrence& r, value_type f_n_plus_1, value_type f_n)
               : f_n_plus_1(f_n_plus_1), f_n(f_n), coef(r), k(0) {}

            backward_recurrence_iterator(const Recurrence& r, value_type f_n)
               : f_n(f_n), coef(r), k(0)
            {
               boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<boost::math::policies::policy<> >();
               f_n_plus_1 = f_n * boost::math::tools::function_ratio_from_backwards_recurrence(detail::recurrence_offsetter<Recurrence>(r, 1), value_type(boost::math::tools::epsilon<value_type>() * 2), max_iter);
               boost::math::policies::check_series_iterations<value_type>("backward_recurrence_iterator<>::backward_recurrence_iterator", max_iter, boost::math::policies::policy<>());
            }

            backward_recurrence_iterator& operator++()
            {
               using std::swap;
               value_type a, b, c;
               boost::math::tie(a, b, c) = coef(k);
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