/*
 * Copyright Nick Thompson, 2020
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MATH_SPECIAL_DAUBECHIES_WAVELET_HPP
#define BOOST_MATH_SPECIAL_DAUBECHIES_WAVELET_HPP
#include <vector>
#include <array>
#include <cmath>
#include <thread>
#include <future>
#include <iostream>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/detail/daubechies_scaling_integer_grid.hpp>
#include <boost/math/special_functions/daubechies_scaling.hpp>
#include <boost/math/filters/daubechies.hpp>
#include <boost/math/interpolators/detail/cubic_hermite_detail.hpp>
#include <boost/math/interpolators/detail/quintic_hermite_detail.hpp>
#include <boost/math/interpolators/detail/septic_hermite_detail.hpp>

namespace boost::math {

   template<class Real, int p, int order>
   std::vector<Real> daubechies_wavelet_dyadic_grid(int64_t j_max)
   {
      if (j_max == 0)
      {
         throw std::domain_error("The wavelet dyadic grid is refined from the scaling integer grid, so its minimum amount of data is half integer widths.");
      }
      auto phijk = daubechies_scaling_dyadic_grid<Real, p, order>(j_max - 1);
      //psi_j[l] = psi(-p+1 + l/2^j) = \sum_{k=0}^{2p-1} (-1)^k c_k \phi(1-2p+k + l/2^{j-1})
      //For derivatives just map c_k -> 2^order c_k.
      auto d = boost::math::filters::daubechies_scaling_filter<Real, p>();
      Real scale = boost::math::constants::root_two<Real>() * (1 << order);
      for (size_t i = 0; i < d.size(); ++i)
      {
         d[i] *= scale;
         if (!(i & 1))
         {
            d[i] = -d[i];
         }
      }

      std::vector<Real> v(2 * p + (2 * p - 1) * ((int64_t(1) << j_max) - 1), std::numeric_limits<Real>::quiet_NaN());
      v[0] = 0;
      v[v.size() - 1] = 0;

      for (int64_t l = 1; l < static_cast<int64_t>(v.size() - 1); ++l)
      {
         Real term = 0;
         for (int64_t k = 0; k < static_cast<int64_t>(d.size()); ++k)
         {
            int64_t idx = (int64_t(1) << (j_max - 1)) * (1 - 2 * p + k) + l;
            if (idx < 0 || idx >= static_cast<int64_t>(phijk.size()))
            {
               continue;
            }
            term += d[k] * phijk[idx];
         }
         v[l] = term;
      }

      return v;
   }


   template<class Real, int p>
   class daubechies_wavelet {
      //
      // Some type manipulation so we know the type of the interpolator, and the vector type it requires:
      //
      typedef std::vector < std::array < Real, p < 6 ? 2 : p < 10 ? 3 : 4>> vector_type;
      //
      // List our interpolators:
      //
      typedef std::tuple<
         detail::null_interpolator, detail::matched_holder_aos<vector_type>, detail::linear_interpolation_aos<vector_type>,
         interpolators::detail::cardinal_cubic_hermite_detail_aos<vector_type>, interpolators::detail::cardinal_quintic_hermite_detail_aos<vector_type>,
         interpolators::detail::cardinal_septic_hermite_detail_aos<vector_type> > interpolator_list;
      //
      // Select the one we need:
      //
      typedef std::tuple_element_t<
         p == 1 ? 0 :
         p == 2 ? 1 :
         p == 3 ? 2 :
         p <= 5 ? 3 :
         p <= 9 ? 4 : 5, interpolator_list> interpolator_type;
   public:
      daubechies_wavelet(int grid_refinements = -1)
      {
         static_assert(p < 20, "Daubechies wavelets are only implemented for p < 20.");
         static_assert(p > 0, "Daubechies wavelets must have at least 1 vanishing moment.");
         if (grid_refinements == 0)
         {
            throw std::domain_error("The wavelet requires at least 1 grid refinement.");
         }
         if constexpr (p == 1)
         {
            return;
         }
         else
         {
            if (grid_refinements < 0)
            {
               if (std::is_same_v<Real, float>)
               {
                  if (grid_refinements == -2)
                  {
                     // Control absolute error:
                     //                          p= 2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
                     std::array<int, 20> r{ -1, -1, 18, 19, 16, 11,  8,  7,  7,  7,  5,  5,  4,  4,  4,  4,  3,  3,  3,  3 };
                     grid_refinements = r[p];
                  }
                  else
                  {
                     // Control relative error:
                     //                          p= 2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
                     std::array<int, 20> r{ -1, -1, 21, 21, 21, 17, 16, 15, 14, 13, 12, 11, 11, 11, 11, 11, 11, 11, 11, 11 };
                     grid_refinements = r[p];
                  }
               }
               else if (std::is_same_v<Real, double>)
               {
                  //                          p= 2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
                  std::array<int, 20> r{ -1, -1, 21, 21, 21, 21, 21, 21, 21, 21, 20, 20, 19, 18, 18, 18, 18, 18, 18, 18 };
                  grid_refinements = r[p];
               }
               else
               {
                  grid_refinements = 21;
               }
            }

            // Compute the refined grid:
            // In fact for float precision I know the grid must be computed in double precision and then cast back down, or else parts of the support are systematically inaccurate.
            std::future<std::vector<Real>> t0 = std::async(std::launch::async, [&grid_refinements]() {
               // Computing in higher precision and downcasting is essential for 1ULP evaluation in float precision:
               auto v = daubechies_wavelet_dyadic_grid<typename detail::daubechies_eval_type<Real>::type, p, 0>(grid_refinements);
               return detail::daubechies_eval_type<Real>::vector_cast(v);
               });
            // Compute the derivative of the refined grid:
            std::future<std::vector<Real>> t1 = std::async(std::launch::async, [&grid_refinements]() {
               auto v = daubechies_wavelet_dyadic_grid<typename detail::daubechies_eval_type<Real>::type, p, 1>(grid_refinements);
               return detail::daubechies_eval_type<Real>::vector_cast(v);
               });

            // if necessary, compute the second and third derivative:
            std::vector<Real> d2ydx2;
            std::vector<Real> d3ydx3;
            if constexpr (p >= 6) {
               std::future<std::vector<Real>> t3 = std::async(std::launch::async, [&grid_refinements]() {
                  auto v = daubechies_wavelet_dyadic_grid<typename detail::daubechies_eval_type<Real>::type, p, 2>(grid_refinements);
                  return detail::daubechies_eval_type<Real>::vector_cast(v);
                  });

               if constexpr (p >= 10) {
                  std::future<std::vector<Real>> t4 = std::async(std::launch::async, [&grid_refinements]() {
                     auto v = daubechies_wavelet_dyadic_grid<typename detail::daubechies_eval_type<Real>::type, p, 3>(grid_refinements);
                     return detail::daubechies_eval_type<Real>::vector_cast(v);
                     });
                  d3ydx3 = t4.get();
               }
               d2ydx2 = t3.get();
            }


            auto y = t0.get();
            auto dydx = t1.get();

            if constexpr (p >= 2)
            {
               vector_type data(y.size());
               for (size_t i = 0; i < y.size(); ++i)
               {
                  data[i][0] = y[i];
                  data[i][1] = dydx[i];
                  if constexpr (p >= 6)
                     data[i][2] = d2ydx2[i];
                  if constexpr (p >= 10)
                     data[i][3] = d3ydx3[i];
               }
               if constexpr (p <= 3)
                  m_interpolator = std::make_shared<interpolator_type>(std::move(data), grid_refinements, Real(-p + 1));
               else
                  m_interpolator = std::make_shared<interpolator_type>(std::move(data), Real(-p + 1), Real(1) / (1 << grid_refinements));
            }
            else
               m_interpolator = std::make_shared<detail::null_interpolator>();
         }
      }


      inline Real operator()(Real x) const
      {
         if (x <= -p + 1 || x >= p)
         {
            return 0;
         }
         if constexpr (p == 1)
         {
            if (x < Real(1) / Real(2))
            {
               return 1;
            }
            else if (x == Real(1) / Real(2))
            {
               return 0;
            }
            return -1;
         }
         return (*m_interpolator)(x);
      }

      inline Real prime(Real x) const
      {
         static_assert(p > 2, "The 3-vanishing moment Daubechies wavelet is the first which is continuously differentiable.");
         if (x <= -p + 1 || x >= p)
         {
            return 0;
         }
         return m_interpolator->prime(x);
      }

      inline Real double_prime(Real x) const
      {
         static_assert(p >= 6, "Second derivatives of Daubechies wavelets require at least 6 vanishing moments.");
         if (x <= -p + 1 || x >= p)
         {
            return Real(0);
         }
         return m_interpolator->double_prime(x);
      }

      std::pair<Real, Real> support() const
      {
         return { Real(-p + 1), Real(p) };
      }

      int64_t bytes() const
      {
         return m_interpolator->bytes() + sizeof(*this);
      }

   private:
      std::shared_ptr<interpolator_type> m_interpolator;
   };

}
#endif

/* daubechies_wavelet.hpp
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
*/