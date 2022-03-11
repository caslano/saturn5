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
#include <boost/math/constants/constants.hpp>
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
    auto c = boost::math::filters::daubechies_scaling_filter<Real, p>();
    Real scale = boost::math::constants::root_two<Real>()*(1 << order);
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
    for (int64_t i = 0; i < (int64_t) phik.size(); ++i) {
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
            //if (delivery_idx >= (int64_t) v.size()) {
            //    std::cerr << "Delivery index out of range!\n";
            //    continue;
            //}
            Real term = 0;
            for (int64_t l = 0; l < (int64_t) c.size(); ++l)
            {
                int64_t idx = k*(int64_t(1) << (j_max - j + 1)) - l*(int64_t(1) << j_max);
                if (idx < 0)
                {
                    break;
                }
                if (idx < (int64_t) v.size())
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
+wX/C+EX4i+kX8i/UH6h/kL7hf4L4xfmL6xf2L9wfuH+wvuF/4vgF+Evol/Ev0h+kf4i+0X+i+IX5S+qX9S/aH7R/qL7Rf+L4RfjL6ZfzL9YfrH+YvvF/uvPL45fnL+4fnH/4vnF+4vvF/8vgV+Cv4R+Cf8S+SX6S+yX+C+JX5K/pH5J/5L5JftL7pf8L4Vff38p/lL6pfxL5ZfqL7Vf6r80fmn+0vql/Uvnl+4vvV/6vwx+Gf4y+mX8y+SX6S+zX+a/LH5Z/rL6Zf3L5pftL7tf9r8cfjn+cvrl/Mvll+svt1/uvzx+ef7y+uX9y+eX7y//X7hhs9Qvgf2BJibZ/TuhH+1CS/pEwaa7G/0BEBu1KPIwfkMQuHUJWD7+ALTAU/jRpquMBSYMd/eE54l2qZ0hYTP4BtQ79phxd67tO0NTFZq4c/coOIuN7T87pbme+50iPTkRD698nUoVSUo5XYSYge5cT1xQUm9B/HzbJNrB+ToGxzvFN5HkwXnaqjsDin/jbqjP8Z8quutg7KfC3AROJD5cLcB49Ii0x/Gx+q7VDk/meM4UO5i7XQPGAvi5DlGyhOchtPRtEPdMUchqUjW5ryatAbL4A1SQWcdb2xAmpLGtST+IOQ75+/s2x4s0M1Gd7H1ErRKnpc5bDQN8Hpe8+pROvs/dEYvbEyioMOrPIFmRs1fTFwkEMABy68xQb98p+TJPtCros4dha9BkQoNLjuAroslVucNpBhcCY9MObOb6wmxsSzRi2dDj5P/9hJTjsxHkhNfgZFoFthwX8hleQCFKRHrpfUi/g5ogbls5EWLSggYys1bdw83Ed81grWb4B27O+8C28Kbs4P6BG2gt/OrFfOGAm9cA8uZtdfocEq1xOSxC8AdvGmVQZnD//kIS5fvnwKZUwaYRsEInruiSKQRWfBiDJl5rIIuJdlqCEsWSFJOefsP8/myvTPtHGGqfRXIFfX7kSRBvnMHteAHfUVCBvfgd/VTVp3RCCrXASdz9JIPfkPz5T75De8ds0X6Ws23pkDX9tPuynZAFpnzWcJpUEsMQe75Sz/MEbCiDpT8lBKihE4o4FIy7XlElx614wcofEzVN+x8siqwdGTgqlgoeVbp/79ykryPqmHRR8OY+bFsY9rkOxJ8WVU0MdWQxO9ihYogR/c2BsBgaJFrh23l/3CO3h6kg5zYuzC/YSbs8nECjptg+TgxSffC5w88QtbGir0yWEMFewL1LAurGkj2u/p7lgXTlIR1zhawvn+6b5Fzgcz+TRsZlE+xnmSbSd0B+NwjLLcgRsFsXe7N9L6eBaS48d8+0D4sMV2iu4GRqkY4FqT6Y3zpfAEb7P3Ymmh8QnV/NWgffrdB3xuAM/vBkdvcOzqh8ODZeOIpyhzBFgKa16YRnCl19SWZKjf8LgvepwHVf3n8BWJ2AvBdZ13HePxzl9OzHq1KbbAnruIbuNf36pG3m2S991ff3x4yw7D2sYWA5niP9eNBcsZI/GhxVNYQWK0+stvQpe5YvEiK3JwlHLu/3xskRArJw6CrtShaIyPAJ10zBmiyrunXs2F5/1gICLOu6dVKNy5hhCm2qYEMtRBsEAVXNxtyoSxpida5qRrjEOsfgEAe/y0FW8jpxqBJYbDRiDTXRWGa3LDegr0KxtfoDZp+BWKgRpzzQZkYlXB7HM46uXbo9GgUUY8iFmmOmeII+9MSTTr09ibukkkHcNTVCy9+FRwuMgYElmde2lmNgGtHQfUukJf5w1YFfD8zDht2b1kpeO1WxzT+eMC1Hic1cXm5XcOmwrcj4JogtF5vn5/Om9xaQy9blrTrf3fYIBGC06eCxBbYn+EiQB7/4DPA1msDsHSBX00EIRDPmBA/a0dKrfn6UWxBdYnFCXBjcr+ix3BQCfOchvXW/3vaS8FlmajNjQgKCCgW7b29WYJeRn4xtZIESfrUdTHUDdpYURA7vfMVkrTjZeStuP2zFg8vKqEW/vmt9wJIaWFkFr0Ht5vv3x9/+rGDPgQEuVWN4RrN3cyT7KnfHEPlkB/+dtzO7/BkrD+IPO2imtaejHqjjEtpZ88FiSXQZop1GdqOSHjPPLAswQQwTSPmjbC42nV5XxrqlAOiCT+vranPrtPmj2yLyiLTL8ZqmdnWA7ZNOYFreOj6DQmZn375bd0IuXuMh3Lyz/WudXPia9EDl4/283Nkyc50i/oFt8YC5doUjvvW5DxmdCV06gvuaP63W9kHLy8S0mRSMN0jeJPTLAFpjTneRacaHoClxyoLrcVLJ2Vl73l5pafESo16yB3WW5FzSSaQ9LczxOS6ZkKu7awVn/uEDj66BG6LwN8GE5+Tr2PNOAp7sa7/Ea89fxYSkUU+5S938J3X13Nyny5ZkgO9C3ab3xbVaKS28OIO9fKkdPZWI9FXdshBF7OVcrDsdBJVEEJ82Q8CBhiW9NSkL8TCMPE3ygXwp4l0gUT4w4qgw/+PYrhdHqQ9THR5c6KwWVNAQSr6kUtlyx5uEgfyB2CLp5D/DdENiDDZV2AL841gwXtvyb7Qqd766NTfK6zsedTAcVy4T0w1vJ61BLVeu+kHsK897a6NzT40t34O666P5EUfpfPvrMuuXb/dmAlqerW7Mj6HZUZsmG45OTExuVCwNKXLq9CzEYGPtpd1yPl+V2a+derrsh81G2hnYTbab+8cvBtYPc89sqqpFpFmlzHFNTvDaXJQOL92l3sorU5oUTVrunfPI01utFEURxGgYzzFtQnZx56jrplJFs74IwXhQSJvPz9xvLInO+FLuvG+PsapJ8nlCSZO2fFUi6NfPkqaNOC4ZjK3gyLqfKDeNyhM04KuTX+3IMZ/Jtg8+uZf3rv4sT0dTdrUe2rL1rl0RGv3Z6i3exbCRKOaxOFxgEL0tsQyGN4fAsphHwAyQP7wzRhtdB5NHG21TtDFpiu5cu4c/1/oLlL2eBcGYxTxwDUzFtmVZcD14f7k1jUPETNF1eg6EkqVFoK17aV+6XsEhLrQvfnq9Hoeih63eTe0lQwcUaq92AWtFvk63WLVyc66aoOWg/ZGrw9+wVyD4n1/gtvfeY7obIt497nV7upRdyTKXIq6F5LZ9E/uFMLu336lo3r++98n1xrpnHIf6vUXSK5s4ixVSuMdIMjJMO2sR5ebMej6MOKkO7xSK+gv4KRBg1iCM+UVQXXTLi9szEdW+RGvaQrGsKCoZeVa3DpfvMMDF+M54Z3S1M5Z2i708vw953yybvX2ZRZlq4dqYtS3ZCIlvl0U6gVEQkERtWjTLoTBLjx+oa/FksmTeEY5HwDpNBynJDE4JBUfNCIyCsSq2yeexqBOo7w07LSR1+BZB107fFPxmkYN319mMkTw8ueFdzVZyhQAC+JbwpRSmsWiQXhQsqAYXK7dRW6zVNYV6U5/RBjFoULYdAXP+qqrWIgnLs+hTBkcORppgWjBFrm0rb6ze3Ob2/aAMosnTtQvElvOgilP8qWlbi+gf4I54Rq/FYoJx+ZsJ6gEMRA3m1gWXupOzcUDgs32iIgB0kRmjFgatm8htmTkJMsyEpq8zfar/8fLVnHm6yswBH4/b/yTq2Z8MEUVUu0HQEVigUtRNmrGjw3OcsWUo5qw6Zxm0LsOZOydzVqk34JLT/ES5sFYuJrl7AJ9IBuNEGZN+j+7GhEmcsL9QDM1VkM1sF27Hd87IEVGP02WFmSFTD0OgJMbAW5+UHY9c1IHWINlD3dbbE5fP5Y5kuIAmRWVRrl558/2xfLQijg8JsIalWK0G/VbCgJeRYDnoltzisfACAhgh+dCP8HEO5Z4B4Op7sxXBFEOg6xfdLUNnWq8QVAmjuhxc65s0UBx3WfSH4IIfeB/2GF0rkVvBxZ8s25Lzkc11jtDEwZQGLrJTB6WekbEnK8Ft2sic6BwmtmZv8cgOPzE6FaoKxgpD9qU8/4MTaO4WJKE9WMUDNfIseOQC6CPSzyGVXe1CoOdcprb5+L5d/tYbicfdf/bB2+i5d9oIjeDdh0sBu62Sr4/zkK9wXx4KZ2+CMdCBGGzXKyLvsNEdua4WfYhH7c+sb1q6f3ehrHNjrWz05G5t4GGw7L3rPFgnNoTYaw+z3r33cc8YAkea+42W+MDRQEnNYu1gcsoimX3luvDA3CB5QCpZ1wcS/Bu1hfrJ13Z+Kq4rK9sBPVTfv8C6wCTm4q2WJ8Mds94BXeGBxKMAgoTJVqaAGt37Mkw5sDcNP9G1PTCrKtQlr+Or9J6oObiOykRW4hAl94P3Ktf1EWP5HGk5S1jXCK6bQFL/BlfHo+9sfHaPvCViiBOrzd52mE4vnK0D1tSHKLK5z2decvjuxaLiXf9puqucpTZIdso8n+TNl6X1tp5t/tS8W29PgzejGOKTu3a2g9rVVI8Lj1bouQnelpIki45iMeN5+OoNuvO5IjD6TOSZ9038F+Ci+5hxNJBuHtrcPrGgjJX9H/NpJ+NU57vyRoLIIFHP4p+iYSuFcF3gYdjImQ33y+OIgju0Z8puCWxdWPdHTDgf8p245kNh+BSlIozqkl1tnkW+JnNtx9S9LJ3RHPuu47QT9XR1n1LaH+3KP66uFO8uOf+2exkxAK1KL1H/3clWquhyE8unOrhDnO1wpI7zM2ermPqRBbtZsUL+A2QaFyHu5Mgy7icY1Dtq6LK/QHsYYj2GFlA3GxsXlP00gvT5vUpg8NpsbGc+EzsxaU/pQ+ZtGjJiTB71bzY9UTJ/DqXFvfevv7/YJWS3w5/q2Ex+TBpxtDLrLdnXL6xIvvA8Jjt4tcDk0mUWC6P74nkS+n3cq83VY/G56GI5z4qP/Fo1Kv4WBvyh/gmkIdpKAkWOImtxbhED3WdIcMZQFH5z6S0ME4KkI9QPH0GyIahwB56W2j4nPcONqvluwfFd/RCz99ueauyXiyvNMbPvaHE6bk++547s/Amj/qFBEzahKkUUmuaGxaYuO0Vr6w+J6uGu688Vv/XAroQ0lgul7yyUwrrBlfYhdWvCd8cGOBZOeaulWP66UfRh4JLoPHUqz7HsdILG9IW8PNnDkGDoNLcKejSIEnKcL1049xjyFb88m0czjfIwVhim6HV/3/N5YXzleBjRdqFOVL/peba8yHIVFnL2sc/2LOkFikj8uw0zVg29Si5aL9s+jOU1vk5Uf9Gyc269kE3RgZ3hXPHG/Oo4Nr/xJRAH/MAPKY3EPR8D3LHmEId3A1UpkgOckaIZrJmXphAolzoqFd8LAsUk7eK+RgRVtbmbd5++sD0YDQmzBpnbBTLWrfyOuvOFwwndQ+5wKUf1/CiYiPfTSaghPt17/G9tmO7u0sdYLpvM/OSk8TkZvMfiesO/cwkKTs0oG+tlkeUQdmmlGGxHzuG6cMn1XAffvN8IWbSA/cv8qpAr7daS/+Y9ZnGo5NBEI9jdvdoD07GpGjtmq3hrKfhvc5BqTkCuxR9f01dPB6FZ+8tV92ydgR0REeXq/d7Bm8sbWIt/V/KEC0KdxtdL2G1C53VrsW8na6IL7ZsV3fH3oPCNcEHP54uwoYEhI8J5tXpfGPI9kJC8vItKa4h/dUbS/E84Audn8+eR0wU+AoE0Jn137x6/sc+/vvtTo4X9Hv2/UotYvd6AOn2ctBF4xqf430NHOIGCPTTTtCVbIL4x6WsTd443NMdeyEvOX4kO0DUj5uZUK0++OT63gxo+WvPA9jrsHegAmEsGfWBZ1tHRE9mrKNhFVDvry7ATYVzX+KqSUS6wgJ8d+CIEhY2TJhGpkbwVG6rtZcnyO7ASKDGwaWnD4/8GKSHOjL70vCcRB2nfULw29IWVXlzEzJZM22rCmOVUabYt3cdqIE7gEuom1d3eej39wCZgKHquJvLULKAldWc6JqsMBfMbo2WaLe0oSjhijdqx0GJ3CSres/fiCLnYZ5W39Lm7cOGKtC/luW1EyzD5eKJOMrcswDxWd3BkUarasJVsrLCewt5/iHZLP8yAL7o2LOXZPJ/pCgMOxT5xsd++C2rv5JiQokXCX1DP1GntI5rlR5erly1MM/VLB4/P9QTkEoIs0M/lKVbyEtt9HRY1AQNJOk2R/TV6XFEWrUSqn4dzvyu0roWeoOBtaiHQVlCKln1HzlLzYDvLKGf9/iNJc+/RK3nvNVDZLts4JAlWyrCkAYpdelVlzDTSSm4NYAPd+vPB/WN4t9sRt9RAhbrobJ/YRuvhgkDd057AmkEwNXfBSKeJUrklpOKkXdEFdsLP9pMxWvjhRZ4UbN7hrbcoRKAVsyD2jXArI+Cu50I4MmrAAmEjIDXaF3WggzXWZc7ia9x3Sw1YL+3kXuQFZa4nnY6pd6T4odNEIrpk85q8E+gCeKatOEhPv+Ss0L26jOlNEXg3aZqQm6ynUriGedbqh+/ufnindrF213l1FNUVeuxlBDL+t5DKlsI2RvyBRoRjwyrVys12FDs/nwVXGiB9++pik8/JI0gFa4be5p31iSJjsB42TcZ/eqrwuP8rC+YwBofUmi0iLcNKp0QtDya/ONqvYGGqDGyosE/KJ22uA2X6pK/qyhaUF3UbaL8Cqo+6bO/RBUYFAJ9Xxby7fZ0I4jcURjEn0C9m0dC+wwevzz4ayM1ODRVLuKufcId+qk7r/vyyVxIvUBIaRE8N2G1JqNUgR+PZKiberlceuYkrykv96MbUYUkWSNH4rmvAvXFrQ6Ny07JLSxFGyC/SFhIqDkryI25RHf2WW9VYUzxDQVKUqRCw37jxwdbuICYWCe8daU3lBVuGcpV9hyBd1KYwWJ2yTSHyxF5Acmkv9c/kh6fQjW3UXUK6sQWC64WQM7K/Kinh+CiQP/zN9sC53FT8R5PR2jSM2URwzfDciYrDyGPCCxQwt6WmP/dYAXhoVwhqiJu4ME5HtbMY/nP6XwaMYRmRzmLDVM6ragesY+c0aWalMHi/WFAszHtvoJDiYYPIO6a5wN4KdHbb6z7S6U9ObkNw6cBOYA3iaQkZaWTtptYlLG8Clh4M2CM4VFA/9EqHaC9cyBN/Ef42wSUbz4de5EftZgnLUwXuyKiP1HucjNxRcOCM5azLxsEwSQCkA8BMONgiIgTGh2Qgv4xhFpRPHH18L1HdwW2lje0zXhrbpnPx+xyTTLX5HrsJQcAxbHV5+k3yoqFANXN8hD4aPB1K1frRqdgZ8YYQAiGEEfYJpB+l2moCjOwGTfjk9dmJsyhfQdZmZRu/TA9ekdjMBTQlUh1ERBEEY/ghmNTqTyTGxdGNS00T1kmXyyl97ekwSFYqq6a3292JHrO2OAksrXJ3BAb/FWIS97BAChPSsykcdyTX0/Fsaed+cQzQS2fjAuery90b7iXhex4kyoz/QeeC3tHutl18LRaBxQPIwbJBg+Coyzud0oxVKAPzVYfWXUe3muTLa/Kd8kgDjZks1EMIpkrtFh7KpcngPqJUgeYiSFaay1EJjh1aSFtp2ZGsCc0VcIxq8XBj9Jop2smPfBh/Ya742HkD7Ah+gE1re6NaIXksEmv0bv1ZbvObNYh5M90nriqUJAv28tsaIG42RONySUCRlzS4uJimUOGb3bufl8M2l3M7CL5r3RQQgUeMZ6bk4/K8qyfFAvcpd6M5MIRT+42ZdPNQpXmtRF3F9Xh4lusVbsfWnJ6Qw9w5ATlpYRzfZrv6ZnXJSKQjal/+tkXkZYIgTNy3kFDrAeiqR9MgDT740XdWrTimWTpSJXgG+GSTKV39mTbnjvCdkLkTi6u+uZVgaRqtWobuYqlBhJNOZci+JiQ5ynsvkMWFZ0AoR2TntkVRkpbOn06/hI3nrooZgjZ63kCakFw/qlSpF0Ngp9w9M3G5Owh0iIcGMly0MH2X845OlPa2Ul3jvhVPY5tPoFhbImOkEHCpOMQOhPqdmhpS3LqLhnoaHSMNUEnRP29MIPnWC2Y88CSlbhg6MNM/r1P/xs5l4GK01YGa4vBVyAw6cdKP/IzALEHwu4pjxaYsLTO7ENdGyqxhKmqc2JUGnagec6u6PTIymKlclK6hKIKcxQL/cEOR3k9QRLjmvURM3wpTjS/lSrc/RcTttccC3dq2yOE09Po2sFUH1nQkub+OoqLUd1Ez3eMM37YOKCmy167sgDUR8hqa/ZHHRZpP82QiKTy3XEhFTX7+BJ0xUXbTWQ0GJYTIhzF/qltFPc9nqKyOaeUmVzjlh98MA7fKLeVuaWh9BlzBW9e82B3NLtDBPUeypMDrjgrfKnyYrPyntl6iev/lHauTknTkQapgMkTQdDgaIyVP+mgrEkNWet2dhD6m7bZkz26JIRDpd3kcMB8UwHIf5MnyFxpp8kEeSQN595jelW8zq55sPQK3GVuOKie2/Phu/qDDM7a6zkQoQGiHIJbfs/lwdTFFk/groHnOtadt/KmCzHbvr4GWVnmDG1CT54dqv/XSmlqrKIYmDCoUHDuNqFcBq52sujFWoBIWZiwNJcMAUgs6PwVg9JFP+HPPxmNmiF7rAf7HWDIq+3b2IcsH5aM0TbdRrDuC/uaNBNKJnnx+kln5R+DBfHvnSfbfLzTECYJW4OFh7urHRVGDTjLJSz/AVrtNDEIT8z2k18RZXlRvDUroNAf65UHsdFuYVhnIhyh6iNgLJklB/Gq1fKQlFBKqpdfKudWi+cIGvqMUsSVcrVxSCg7BWx1RoanloBzZgj3DT/anugTFqggZShpREwRdxxX9UjC5xPfQkgeF5clSt9kjNjIueWsy2xk9hWbWi5aZIpgI5iPXZREP78DGL1hOOktIp8B/hXoVkJtqVzwbaGAh22U8/tTnHLTaJSXqtYAG2Iade6XA5DnSbQMCJzBrMhnBNPzvuwn1N9w7euIAI3D/7qILEg0YnOfX/PNHiUKm3IjDeKL6LMIUxlS6GOYmF1osrj4TDlSpYqB0VDjgVkllUBLhAawnlt3jvaZ2O3CINEisEEAftMtm3492T3Rw/sDkLwoWFE+enemtIkrDdj5GZtCRTUR5QplsvfMMTGPMJpweETorGATtwtiLMIwAAiz90zibLXb11ICIoBj8tWjvonH7UhZFC5we4sFievH1GQGc3oXoCkIQSyatV7SBX479ThYdzJXAof6xAqlagR4FtrWOFZaK/dvefnGXEc6ors8UuUFpnCEKMJz1IYCpLGuHsjoFBCbruJoXBXf3UED46vbay5P7cihxFqIttsdiyuq8nYw=
*/