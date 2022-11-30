/*
 * Copyright Nick Thompson, John Maddock 2020
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MATH_SPECIAL_DAUBECHIES_SCALING_HPP
#define BOOST_MATH_SPECIAL_DAUBECHIES_SCALING_HPP
#include <vector>
#include <array>
#include <cmath>
#include <thread>
#include <future>
#include <iostream>
#include <boost/math/special_functions/detail/daubechies_scaling_integer_grid.hpp>
#include <boost/math/filters/daubechies.hpp>
#include <boost/math/interpolators/detail/cubic_hermite_detail.hpp>
#include <boost/math/interpolators/detail/quintic_hermite_detail.hpp>
#include <boost/math/interpolators/detail/septic_hermite_detail.hpp>

namespace boost::math {

template<class Real, int p, int order>
std::vector<Real> daubechies_scaling_dyadic_grid(int64_t j_max)
{
    using std::isnan;
    using std::sqrt;
    auto c = boost::math::filters::daubechies_scaling_filter<Real, p>();
    Real scale = sqrt(static_cast<Real>(2))*(1 << order);
    for (auto & x : c)
    {
        x *= scale;
    }

    auto phik = detail::daubechies_scaling_integer_grid<Real, p, order>();

    // Maximum sensible j for 32 bit floats is j_max = 22:
    if (std::is_same_v<Real, float>)
    {
        if (j_max > 23)
        {
            throw std::logic_error("Requested dyadic grid more dense than number of representables on the interval.");
        }
    }
    std::vector<Real> v(2*p + (2*p-1)*((1<<j_max) -1), std::numeric_limits<Real>::quiet_NaN());
    v[0] = 0;
    v[v.size()-1] = 0;
    for (int64_t i = 0; i < static_cast<int64_t>(phik.size()); ++i) {
        v[i*(1uLL<<j_max)] = phik[i];
    }

    for (int64_t j = 1; j <= j_max; ++j)
    {
        int64_t k_max = v.size()/(int64_t(1) << (j_max-j));
        for (int64_t k = 1; k < k_max;  k += 2)
        {
            // Where this value will go:
            int64_t delivery_idx = k*(1uLL << (j_max-j));
            // This is a nice check, but we've tested this exhaustively, and it's an expensive check:
            //if (delivery_idx >= static_cast<int64_t>(v.size())) {
            //    std::cerr << "Delivery index out of range!\n";
            //    continue;
            //}
            Real term = 0;
            for (int64_t l = 0; l < static_cast<int64_t>(c.size()); ++l)
            {
                int64_t idx = k*(int64_t(1) << (j_max - j + 1)) - l*(int64_t(1) << j_max);
                if (idx < 0)
                {
                    break;
                }
                if (idx < static_cast<int64_t>(v.size()))
                {
                    term += c[l]*v[idx];
                }
            }
            // Again, another nice check:
            //if (!isnan(v[delivery_idx])) {
            //    std::cerr << "Delivery index already populated!, = " << v[delivery_idx] << "\n";
            //    std::cerr << "would overwrite with " << term << "\n";
            //}
            v[delivery_idx] = term;
        }
    }
    return v;
}

namespace detail {

template<class RandomAccessContainer>
class matched_holder {
public:
    using Real = typename RandomAccessContainer::value_type;

    matched_holder(RandomAccessContainer && y, RandomAccessContainer && dydx, int grid_refinements, Real x0) : x0_{x0}, y_{std::move(y)}, dy_{std::move(dydx)}
    {
        inv_h_ = (1 << grid_refinements);
        Real h = 1/inv_h_;
        for (auto & dy : dy_)
        {
            dy *= h;
        }
    }

    inline Real operator()(Real x) const
    {
        using std::floor;
        using std::sqrt;
        // This is the exact Holder exponent, but it's pessimistic almost everywhere!
        // It's only exactly right at dyadic rationals.
        //Real const alpha = 2 - log(1+sqrt(Real(3)))/log(Real(2));
        // We're gonna use alpha = 1/2, rather than 0.5500...
        Real s = (x-x0_)*inv_h_;
        Real ii = floor(s);
        auto i = static_cast<decltype(y_.size())>(ii);
        Real t = s - ii;
        Real dphi = dy_[i+1];
        Real diff = y_[i+1] - y_[i];
        return y_[i] + (2*dphi - diff)*t + 2*sqrt(t)*(diff-dphi);
    }

    int64_t bytes() const
    {
        return 2*y_.size()*sizeof(Real) + sizeof(this);
    }

private:
    Real x0_;
    Real inv_h_;
    RandomAccessContainer y_;
    RandomAccessContainer dy_;
};

template<class RandomAccessContainer>
class matched_holder_aos {
public:
    using Point = typename RandomAccessContainer::value_type;
    using Real = typename Point::value_type;

    matched_holder_aos(RandomAccessContainer && data, int grid_refinements, Real x0) : x0_{x0}, data_{std::move(data)}
    {
        inv_h_ = Real(1uLL << grid_refinements);
        Real h = 1/inv_h_;
        for (auto & datum : data_)
        {
            datum[1] *= h;
        }
    }

    inline Real operator()(Real x) const
    {
        using std::floor;
        using std::sqrt;
        Real s = (x-x0_)*inv_h_;
        Real ii = floor(s);
        auto i = static_cast<decltype(data_.size())>(ii);
        Real t = s - ii;
        Real y0 = data_[i][0];
        Real y1 = data_[i+1][0];
        Real dphi = data_[i+1][1];
        Real diff = y1 - y0;
        return y0 + (2*dphi - diff)*t + 2*sqrt(t)*(diff-dphi);
    }

    int64_t bytes() const
    {
        return data_.size()*data_[0].size()*sizeof(Real) + sizeof(this);
    }

private:
    Real x0_;
    Real inv_h_;
    RandomAccessContainer data_;
};


template<class RandomAccessContainer>
class linear_interpolation {
public:
    using Real = typename RandomAccessContainer::value_type;

    linear_interpolation(RandomAccessContainer && y, RandomAccessContainer && dydx, int grid_refinements) : y_{std::move(y)}, dydx_{std::move(dydx)}
    {
        s_ = (1 << grid_refinements);
    }

    inline Real operator()(Real x) const
    {
        using std::floor;
        Real y = x*s_;
        Real k = floor(y);

        int64_t kk = static_cast<int64_t>(k);
        Real t = y - k;
        return (1-t)*y_[kk] + t*y_[kk+1];
    }

    inline Real prime(Real x) const
    {
        using std::floor;
        Real y = x*s_;
        Real k = floor(y);

        int64_t kk = static_cast<int64_t>(k);
        Real t = y - k;
        return (1-t)*dydx_[kk] + t*dydx_[kk+1];
    }

    int64_t bytes() const
    {
        return (1 + y_.size() + dydx_.size())*sizeof(Real) + sizeof(y_) + sizeof(dydx_);
    }

private:
    Real s_;
    RandomAccessContainer y_;
    RandomAccessContainer dydx_;
};

template<class RandomAccessContainer>
class linear_interpolation_aos {
public:
    using Point = typename RandomAccessContainer::value_type;
    using Real = typename Point::value_type;

    linear_interpolation_aos(RandomAccessContainer && data, int grid_refinements, Real x0) : x0_{x0}, data_{std::move(data)}
    {
        s_ = Real(1uLL << grid_refinements);
    }

    inline Real operator()(Real x) const
    {
        using std::floor;
        Real y = (x-x0_)*s_;
        Real k = floor(y);

        int64_t kk = static_cast<int64_t>(k);
        Real t = y - k;
        return (t != 0) ? (1-t)*data_[kk][0] + t*data_[kk+1][0] : data_[kk][0];
    }

    inline Real prime(Real x) const
    {
        using std::floor;
        Real y = (x-x0_)*s_;
        Real k = floor(y);

        int64_t kk = static_cast<int64_t>(k);
        Real t = y - k;
        return t != 0 ? (1-t)*data_[kk][1] + t*data_[kk+1][1] : data_[kk][1];
    }

    int64_t bytes() const
    {
        return sizeof(this) + data_.size()*data_[0].size()*sizeof(Real);
    }

private:
    Real x0_;
    Real s_;
    RandomAccessContainer data_;
};


template <class T>
struct daubechies_eval_type
{
   typedef T type;

   static const std::vector<T>& vector_cast(const std::vector<T>& v) { return v; }

};
template <>
struct daubechies_eval_type<float>
{
   typedef double type;

   inline static std::vector<float> vector_cast(const std::vector<double>& v)
   {
      std::vector<float> result(v.size());
      for (unsigned i = 0; i < v.size(); ++i)
         result[i] = static_cast<float>(v[i]);
      return result;
   }
};
template <>
struct daubechies_eval_type<double>
{
   typedef long double type;

   inline static std::vector<double> vector_cast(const std::vector<long double>& v)
   {
      std::vector<double> result(v.size());
      for (unsigned i = 0; i < v.size(); ++i)
         result[i] = static_cast<double>(v[i]);
      return result;
   }
};

struct null_interpolator
{
   template <class T>
   T operator()(const T&)
   {
      return 1;
   }
};

} // namespace detail

template<class Real, int p>
class daubechies_scaling {
   //
   // Some type manipulation so we know the type of the interpolator, and the vector type it requires:
   //
   typedef std::vector<std::array<Real, p < 6 ? 2 : p < 10 ? 3 : 4>> vector_type;
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
   daubechies_scaling(int grid_refinements = -1)
   {
      static_assert(p < 20, "Daubechies scaling functions are only implemented for p < 20.");
      static_assert(p > 0, "Daubechies scaling functions must have at least 1 vanishing moment.");
      if constexpr (p == 1)
      {
         return;
      }
      else {
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
               std::array<int, 20> r{ -1, -1, 21, 21, 21, 21, 21, 21, 21, 21, 20, 20, 19, 19, 18, 18, 18, 18, 18, 18 };
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
            auto v = daubechies_scaling_dyadic_grid<typename detail::daubechies_eval_type<Real>::type, p, 0>(grid_refinements);
            return detail::daubechies_eval_type<Real>::vector_cast(v);
            });
         // Compute the derivative of the refined grid:
         std::future<std::vector<Real>> t1 = std::async(std::launch::async, [&grid_refinements]() {
            auto v = daubechies_scaling_dyadic_grid<typename detail::daubechies_eval_type<Real>::type, p, 1>(grid_refinements);
            return detail::daubechies_eval_type<Real>::vector_cast(v);
            });

         // if necessary, compute the second and third derivative:
         std::vector<Real> d2ydx2;
         std::vector<Real> d3ydx3;
         if constexpr (p >= 6) {
            std::future<std::vector<Real>> t3 = std::async(std::launch::async, [&grid_refinements]() {
               auto v = daubechies_scaling_dyadic_grid<typename detail::daubechies_eval_type<Real>::type, p, 2>(grid_refinements);
               return detail::daubechies_eval_type<Real>::vector_cast(v);
               });

            if constexpr (p >= 10) {
               std::future<std::vector<Real>> t4 = std::async(std::launch::async, [&grid_refinements]() {
                  auto v = daubechies_scaling_dyadic_grid<typename detail::daubechies_eval_type<Real>::type, p, 3>(grid_refinements);
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
               m_interpolator = std::make_shared<interpolator_type>(std::move(data), grid_refinements, Real(0));
            else
               m_interpolator = std::make_shared<interpolator_type>(std::move(data), Real(0), Real(1) / (1 << grid_refinements));
         }
         else
            m_interpolator = std::make_shared<detail::null_interpolator>();
      }
   }

    inline Real operator()(Real x) const
    {
        if (x <= 0 || x >= 2*p-1)
        {
            return 0;
        }
        return (*m_interpolator)(x);
    }

    inline Real prime(Real x) const
    {
        static_assert(p > 2, "The 3-vanishing moment Daubechies scaling function is the first which is continuously differentiable.");
        if (x <= 0 || x >= 2*p-1)
        {
            return 0;
        }
        return m_interpolator->prime(x);
    }

    inline Real double_prime(Real x) const
    {
        static_assert(p >= 6, "Second derivatives require at least 6 vanishing moments.");
        if (x <= 0 || x >= 2*p - 1)
        {
            return Real(0);
        }
        return m_interpolator->double_prime(x);
    }

    std::pair<Real, Real> support() const
    {
        return {Real(0), Real(2*p-1)};
    }

    int64_t bytes() const
    {
       return m_interpolator->bytes() + sizeof(m_interpolator);
    }

private:
   std::shared_ptr<interpolator_type> m_interpolator;
};

}
#endif

/* daubechies_scaling.hpp
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
*/