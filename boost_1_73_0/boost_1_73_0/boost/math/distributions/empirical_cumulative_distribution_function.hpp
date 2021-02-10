//  Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_EMPIRICAL_CUMULATIVE_DISTRIBUTION_FUNCTION_HPP
#define BOOST_MATH_DISTRIBUTIONS_EMPIRICAL_CUMULATIVE_DISTRIBUTION_FUNCTION_HPP
#include <algorithm>
#include <iterator>
#include <stdexcept>

namespace boost { namespace math{

template<class RandomAccessContainer>
class empirical_cumulative_distribution_function {
    using Real = typename RandomAccessContainer::value_type;
public:
    empirical_cumulative_distribution_function(RandomAccessContainer && v, bool sorted = false)
    {
        if (v.size() == 0) {
            throw std::domain_error("At least one sample is required to compute an empirical CDF.");
        }
        m_v = std::move(v);
        if (!sorted) {
            std::sort(m_v.begin(), m_v.end());
        }
    }

    auto operator()(Real x) const {
       if constexpr (std::is_integral_v<Real>)
       {
         if (x < m_v[0]) {
           return double(0);
         }
         if (x >= m_v[m_v.size()-1]) {
           return double(1);
         }
         auto it = std::upper_bound(m_v.begin(), m_v.end(), x);
         return static_cast<double>(std::distance(m_v.begin(), it))/static_cast<double>(m_v.size());
       }
       else
       {
         if (x < m_v[0]) {
           return Real(0);
         }
         if (x >= m_v[m_v.size()-1]) {
           return Real(1);
         }
         auto it = std::upper_bound(m_v.begin(), m_v.end(), x);
         return static_cast<Real>(std::distance(m_v.begin(), it))/static_cast<Real>(m_v.size());
      }
    }

    RandomAccessContainer&& return_data() {
        return std::move(m_v);
    }

private:
    RandomAccessContainer m_v;
};

}}
#endif

/* empirical_cumulative_distribution_function.hpp
+zf+Tgyyt9VeWQqQW5iXooK8slSvCV9XF+KkOcRhjSiUIRub9zgOuhlXhUPHGJk8nxXMrm90KCoUaW/mkAJRLEeLujrUA7zL8rz6CM1pMyUbRx8OQaWDgVsKFRzHa9W2dxUpoRubDmyUUIqk5v1VY8nl9CafVIxOyH3kqZO/fv31F6fzbJ6SYwgce2drqhJH8QKQIQMhoigit8G3c4ZRxHRERpmPXWMrm5CxveQeUJGt3DUztdgoPxgPJ/l7sRCVetV6AA1CmlIpY7urDEV/Oo4VhAkqhXbG9xHneN4AQa2u9taZOUH5bz2Wt+z4vRnCA4WBMoWAHg7Fy8ZXuCC9tpXh8CHo81s2ts+GioPtOARFWCl3Ocz4BrRdfQDRUEABjcOiJ5iZsw65wEESHcpGgJNnVLOXtG6WE+W9MJz18gzJnKvk559zzA7/kzHWS6gECZveNnV8ZKNcjCtfk2koDqy78xT3tHJ25BbmUrEKtkuZYw1hIIvUeY2U4L99B3EjRrF3gCl59yMDR9/in85UdmsrRvXI/qEzII9SV3YOQH+it1T02W2TS0Ac7mpAtejC6XTwSd6/CUbfDgCwtSFmaGT1am+im9H/6ur7pfoAFdcLveb0CuYOqZLTK0ujuCbgCCn7dRRqQvDI2/dy
*/