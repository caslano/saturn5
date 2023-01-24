
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
L5PZxHPn8wwHdAXWnE+9P/iAGLtNPA10NqXX8XNPJyRLAoKOob9UIpQPUqrRi062hV+lqIe5hkldAd8VAf9C8ID6/bSMw9MUARpHZjd3TT+PiXg3q332XMvN1HduG3uV5l00dZqrAaLLkA9tSSlKIba0cpz7P8uLPqE6W12pZ+9yq0/AuFSfFRbnSS62xR2ynfGb1/nZ1j2Zg4uZp3POZzzRSdzRSX8ocPwCxzO0eHYIKyVH1iZ8M/FZr21ivCNU3RVX8ZR0JFQ9EVch6ZsTWxF7gvpD+B5bcbxSLrfbFFuxv+IqW/1OZSUwyEch3lbmXvNkHNLFXcR4QVTMM6O28bVPo42VSF9ABVRerHrkBGHo09YBRRUnGC9wi3nS9+mVQc8+4w0VR8ugHTYLNg5MP1eOgT6koXn1Hhxx5TirERzrtrfCHk9TtUIX5HNb19rN9nlSgDav5XNXgXW1vG0uJyBbuRZ0cvR1x+/p9zEDmQUH74+3XPs6ctnObDakE67apQ/ZjP5331NpUhZTblClU81QNVGyu3ju3N8UYH347dE3Aaimd1x+eq8Hhyp9J0MnRadiZyPGBHjXI8Cur4F5s16fVjFjdYhnZHQpTHRWXuSeSw7FzNSe3uwAKf8b0odl0r125poBxffbcot4d+U9DldoG9kgNLAnb3QNNqtxLTiGuL4Ukn7KdnDcLA4RToXrJfXN/UYbeRpfoFG5
*/