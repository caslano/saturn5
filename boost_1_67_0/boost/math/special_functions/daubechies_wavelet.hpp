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