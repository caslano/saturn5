
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

      template <class T>
      struct bessel_j_backwards_iterator
      {
         typedef std::ptrdiff_t difference_type;
         typedef T value_type;
         typedef T* pointer;
         typedef T& reference;
         typedef std::input_iterator_tag iterator_category;

         bessel_j_backwards_iterator(const T& v, const T& x)
            : it(detail::bessel_jy_recurrence<T>(v, x), boost::math::cyl_bessel_j(v, x)) 
         {
            if(v < 0)
               boost::math::policies::raise_domain_error("bessel_j_backwards_iterator<%1%>", "Order must be > 0 stable backwards recurrence but got %1%", v, boost::math::policies::policy<>());
         }

         bessel_j_backwards_iterator(const T& v, const T& x, const T& J_v)
            : it(detail::bessel_jy_recurrence<T>(v, x), J_v) 
         {
            if(v < 0)
               boost::math::policies::raise_domain_error("bessel_j_backwards_iterator<%1%>", "Order must be > 0 stable backwards recurrence but got %1%", v, boost::math::policies::policy<>());
         }
         bessel_j_backwards_iterator(const T& v, const T& x, const T& J_v_plus_1, const T& J_v)
            : it(detail::bessel_jy_recurrence<T>(v, x), J_v_plus_1, J_v)
         {
            if (v < -1)
               boost::math::policies::raise_domain_error("bessel_j_backwards_iterator<%1%>", "Order must be > 0 stable backwards recurrence but got %1%", v, boost::math::policies::policy<>());
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

      template <class T>
      struct bessel_i_backwards_iterator
      {
         typedef std::ptrdiff_t difference_type;
         typedef T value_type;
         typedef T* pointer;
         typedef T& reference;
         typedef std::input_iterator_tag iterator_category;

         bessel_i_backwards_iterator(const T& v, const T& x)
            : it(detail::bessel_ik_recurrence<T>(v, x), boost::math::cyl_bessel_i(v, x)) 
         {
            if(v < -1)
               boost::math::policies::raise_domain_error("bessel_i_backwards_iterator<%1%>", "Order must be > 0 stable backwards recurrence but got %1%", v, boost::math::policies::policy<>());
         }
         bessel_i_backwards_iterator(const T& v, const T& x, const T& I_v)
            : it(detail::bessel_ik_recurrence<T>(v, x), I_v) 
         {
            if(v < -1)
               boost::math::policies::raise_domain_error("bessel_i_backwards_iterator<%1%>", "Order must be > 0 stable backwards recurrence but got %1%", v, boost::math::policies::policy<>());
         }
         bessel_i_backwards_iterator(const T& v, const T& x, const T& I_v_plus_1, const T& I_v)
            : it(detail::bessel_ik_recurrence<T>(v, x), I_v_plus_1, I_v)
         {
            if(v < -1)
               boost::math::policies::raise_domain_error("bessel_i_backwards_iterator<%1%>", "Order must be > 0 stable backwards recurrence but got %1%", v, boost::math::policies::policy<>());
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

      template <class T>
      struct bessel_i_forwards_iterator
      {
         typedef std::ptrdiff_t difference_type;
         typedef T value_type;
         typedef T* pointer;
         typedef T& reference;
         typedef std::input_iterator_tag iterator_category;

         bessel_i_forwards_iterator(const T& v, const T& x)
            : it(detail::bessel_ik_recurrence<T>(v, x), boost::math::cyl_bessel_i(v, x)) 
         {
            if(v > 1)
               boost::math::policies::raise_domain_error("bessel_i_forwards_iterator<%1%>", "Order must be < 0 stable forwards recurrence but got %1%", v, boost::math::policies::policy<>());
         }
         bessel_i_forwards_iterator(const T& v, const T& x, const T& I_v)
            : it(detail::bessel_ik_recurrence<T>(v, x), I_v) 
         {
            if (v > 1)
               boost::math::policies::raise_domain_error("bessel_i_forwards_iterator<%1%>", "Order must be < 0 stable forwards recurrence but got %1%", v, boost::math::policies::policy<>());
         }
         bessel_i_forwards_iterator(const T& v, const T& x, const T& I_v_plus_1, const T& I_v)
            : it(detail::bessel_ik_recurrence<T>(v, x), I_v_plus_1, I_v)
         {
            if (v > 1)
               boost::math::policies::raise_domain_error("bessel_i_forwards_iterator<%1%>", "Order must be < 0 stable forwards recurrence but got %1%", v, boost::math::policies::policy<>());
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