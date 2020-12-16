
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
9r3Ly+WdJdffYfuNK74x59/vGlw9gmbf+7/7/V037fd+1KhRl116ZUD31FuS90N7N2jVPOLp9Ft/f3dRJEvBbf9+1zEed/a439+lx03zu3Nv3/dOjIqfEcm7Jtp78a50/L53l6flxP5Z2H/HIamhxerActAva2ncLOEGRt+sVPIG+LrG8lvB9R74pVdfneDKBldx3dRf6xpX3999KVXud1zZKb2BP+HhXQG8867cfu9OSt7VVH/eFZTf793JIc6O+787JXl3dBW/q7zfuyYJnznwOb9uKq3PE/Lze19xZezzRFn6TTKuHOMW1009CF3GDbl6SG/e4Uu/jxNb+940yG+UvDtZPss7+vz7neQDZ3lwltRNnbNuX58WJwy5fMCg3qmyv7K/sr+yv7K/sr+yv7K//+m/9F6EfUiqqv6jutrssA/7k/QKnL1IKl99XlFbq0bQr0D/S69RWbOydk11U7tO7b//wvUn61HWpal6avPV/vsvXP+x9mNdmMpUe37QL1jvsf5jHZjKVdv2P/ul13Cs6VjbpTao7Rz3S7VIlf2V/ZX9lf2V/ZX9lf2V/ZX9lf2V/ZX9lf2V/f0f/RXeVD01VW2G/s+2v2hc9VQfzhR5poN+e/Lw/frnR8+z9Dxsv/EF46un0rt9ni/ieb/3jSZWT+2XNch9dVL1VOX9nm+eXD114H7P104J6OWmyv7K/sr+yv7K/sr+yv7K/sr+yv7K/sr+yv7K/sr+/uu/3/R3SIUTdxYenJH67LRUavQW1TwLfvOHSdtwec6+9rRtFfa1S5tm7Wu3n5Gbqqj2cvcf6P6Nb0reH1pSfl877s1k/PTXs/e1y/sn/darzpu22vzcfW3OlqQ9fmbS/4fHVP2qtnLbZNzXhyX9+/5QMcH3Q4K/ZSoZt/BJPcNf46R/8y7Jc/d8PYMHPuD79szUYPIR1yV4DnoGuOQenfA19ST1R/5HEryd9Nt75Ctm32I8tyV6mPSdWvDvUov8T1VIZaKPIcKH3KdnploJ0GZhgrfr4Wp5f0fSvvBnyQM966HV6Qmeo9yuPkd4GHev8V8rfng/QC18D1aLvu9K8LWfkej98zQf4zITfrfqPfyOlry8Xyc5sOuVSf/7XlY/9P2pWvR4quDY4Tf1x143S1/wu15w3vcWXfjblLRr5yZ6bvSinpEjN8E/Z4H4x663qgXPEo3HXvXVDz666Bm8fZLxg/Ez8B0ifcDXEWqxU9MEXueapN+ERglf825O5NrzUUKv2RGC41fcO0fe1yUPdswXHeyXZ77bqR94L7M/FgkveA7Se+S4Qf3BU6yWfkNEBztDF3zwz/Na4UfPPIO/UO+BN8tMzdN/VDvXfN5rfpYl+Cp8ktDd+b3sSlydJDnBc5L6Q3+n4e84DltIfvgZIz7RA3bEz/vQT3QGqiUeOtpeb2Xts/9o/dZdBfi/QfaD7sHlEn6uFl70v1j4GLdALXReVLUzfvSz+EOOTqbzSiLne+iT8cvVEo+b1KL3LWqxyzb70Rdq0ee3arFjluSGrypJOzJPLXbALvgH/obfFKgFT4ukfba9Wvjpqha/764Wf75KLXIvTPhc8rP4Jw4ekJ6hU5roo/6PapFrLHJgV+vnMbW8z6skPUkvMzQOvj62f7+TjPuoqVrir4L6w9f70httfsVUNbXXv6r38L/E88xd6gffVRJ79vpWz9j9TekBv3/O8fmA7IkcTUSX8W87TutIHvRXrGfsPNjzy7PCTzxZrwOHMp55RC3x84ta4qcFLXEsPtHvCaKHfTp7nmshfPhFa+HBrrPUD764uwz8MPGDvpmPGHej8GHnx/QefCv1jB/cIby0NdUfP81J8Hc6Wy18txM=
*/