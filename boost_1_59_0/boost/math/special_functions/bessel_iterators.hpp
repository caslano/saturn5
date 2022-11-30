
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_ITERATORS_HPP
#define BOOST_MATH_BESSEL_ITERATORS_HPP

#include <boost/math/tools/recurrence.hpp>

namespace boost {
   namespace math {
      namespace detail {

         template <class T>
         struct bessel_jy_recurrence
         {
            bessel_jy_recurrence(T v, T z) : v(v), z(z) {}
            boost::math::tuple<T, T, T> operator()(int k)
            {
               return boost::math::tuple<T, T, T>(1, -2 * (v + k) / z, 1);
            }

            T v, z;
         };
         template <class T>
         struct bessel_ik_recurrence
         {
            bessel_ik_recurrence(T v, T z) : v(v), z(z) {}
            boost::math::tuple<T, T, T> operator()(int k)
            {
               return boost::math::tuple<T, T, T>(1, -2 * (v + k) / z, -1);
            }

            T v, z;
         };
      } // namespace detail

      template <class T, class Policy = boost::math::policies::policy<> >
      struct bessel_j_backwards_iterator
      {
         typedef std::ptrdiff_t difference_type;
         typedef T value_type;
         typedef T* pointer;
         typedef T& reference;
         typedef std::input_iterator_tag iterator_category;

         bessel_j_backwards_iterator(const T& v, const T& x)
            : it(detail::bessel_jy_recurrence<T>(v, x), boost::math::cyl_bessel_j(v, x, Policy())) 
         {
            if(v < 0)
               boost::math::policies::raise_domain_error("bessel_j_backwards_iterator<%1%>", "Order must be > 0 stable backwards recurrence but got %1%", v, Policy());
         }

         bessel_j_backwards_iterator(const T& v, const T& x, const T& J_v)
            : it(detail::bessel_jy_recurrence<T>(v, x), J_v) 
         {
            if(v < 0)
               boost::math::policies::raise_domain_error("bessel_j_backwards_iterator<%1%>", "Order must be > 0 stable backwards recurrence but got %1%", v, Policy());
         }
         bessel_j_backwards_iterator(const T& v, const T& x, const T& J_v_plus_1, const T& J_v)
            : it(detail::bessel_jy_recurrence<T>(v, x), J_v_plus_1, J_v)
         {
            if (v < -1)
               boost::math::policies::raise_domain_error("bessel_j_backwards_iterator<%1%>", "Order must be > 0 stable backwards recurrence but got %1%", v, Policy());
         }

         bessel_j_backwards_iterator& operator++()
         {
            ++it;
            return *this;
         }

         bessel_j_backwards_iterator operator++(int)
         {
            bessel_j_backwards_iterator t(*this);
            ++(*this);
            return t;
         }

         T operator*() { return *it; }

      private:
         boost::math::tools::backward_recurrence_iterator< detail::bessel_jy_recurrence<T> > it;
      };

      template <class T, class Policy = boost::math::policies::policy<> >
      struct bessel_i_backwards_iterator
      {
         typedef std::ptrdiff_t difference_type;
         typedef T value_type;
         typedef T* pointer;
         typedef T& reference;
         typedef std::input_iterator_tag iterator_category;

         bessel_i_backwards_iterator(const T& v, const T& x)
            : it(detail::bessel_ik_recurrence<T>(v, x), boost::math::cyl_bessel_i(v, x, Policy()))
         {
            if(v < -1)
               boost::math::policies::raise_domain_error("bessel_i_backwards_iterator<%1%>", "Order must be > 0 stable backwards recurrence but got %1%", v, Policy());
         }
         bessel_i_backwards_iterator(const T& v, const T& x, const T& I_v)
            : it(detail::bessel_ik_recurrence<T>(v, x), I_v) 
         {
            if(v < -1)
               boost::math::policies::raise_domain_error("bessel_i_backwards_iterator<%1%>", "Order must be > 0 stable backwards recurrence but got %1%", v, Policy());
         }
         bessel_i_backwards_iterator(const T& v, const T& x, const T& I_v_plus_1, const T& I_v)
            : it(detail::bessel_ik_recurrence<T>(v, x), I_v_plus_1, I_v)
         {
            if(v < -1)
               boost::math::policies::raise_domain_error("bessel_i_backwards_iterator<%1%>", "Order must be > 0 stable backwards recurrence but got %1%", v, Policy());
         }

         bessel_i_backwards_iterator& operator++()
         {
            ++it;
            return *this;
         }

         bessel_i_backwards_iterator operator++(int)
         {
            bessel_i_backwards_iterator t(*this);
            ++(*this);
            return t;
         }

         T operator*() { return *it; }

      private:
         boost::math::tools::backward_recurrence_iterator< detail::bessel_ik_recurrence<T> > it;
      };

      template <class T, class Policy = boost::math::policies::policy<> >
      struct bessel_i_forwards_iterator
      {
         typedef std::ptrdiff_t difference_type;
         typedef T value_type;
         typedef T* pointer;
         typedef T& reference;
         typedef std::input_iterator_tag iterator_category;

         bessel_i_forwards_iterator(const T& v, const T& x)
            : it(detail::bessel_ik_recurrence<T>(v, x), boost::math::cyl_bessel_i(v, x, Policy()))
         {
            if(v > 1)
               boost::math::policies::raise_domain_error("bessel_i_forwards_iterator<%1%>", "Order must be < 0 stable forwards recurrence but got %1%", v, Policy());
         }
         bessel_i_forwards_iterator(const T& v, const T& x, const T& I_v)
            : it(detail::bessel_ik_recurrence<T>(v, x), I_v) 
         {
            if (v > 1)
               boost::math::policies::raise_domain_error("bessel_i_forwards_iterator<%1%>", "Order must be < 0 stable forwards recurrence but got %1%", v, Policy());
         }
         bessel_i_forwards_iterator(const T& v, const T& x, const T& I_v_plus_1, const T& I_v)
            : it(detail::bessel_ik_recurrence<T>(v, x), I_v_plus_1, I_v)
         {
            if (v > 1)
               boost::math::policies::raise_domain_error("bessel_i_forwards_iterator<%1%>", "Order must be < 0 stable forwards recurrence but got %1%", v, Policy());
         }

         bessel_i_forwards_iterator& operator++()
         {
            ++it;
            return *this;
         }

         bessel_i_forwards_iterator operator++(int)
         {
            bessel_i_forwards_iterator t(*this);
            ++(*this);
            return t;
         }

         T operator*() { return *it; }

      private:
         boost::math::tools::forward_recurrence_iterator< detail::bessel_ik_recurrence<T> > it;
      };

   }
} // namespaces

#endif // BOOST_MATH_BESSEL_ITERATORS_HPP

/* bessel_iterators.hpp
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
*/