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
8N+MGIYjnl6S7zezUXcU+ZHKl+Ugntmo11NaXz0M5dHWdpTPBGHE8C18T1wk2VfJ5TInYB+YLfVhcw7azEffsJ4N32sR70q0f/8S5HwV+gPdFviYno96/eFrKtrMQjnEui/8beoFX0MlvyOzUuO2BfZV8P1wpjyG8FsD3HlSu/dDvwZ1F+SBauR3EnxWoo9o+6x+0jIg9/PG8ShLdQTkGbYjsFyH+iuxXJ0lrRelS8tDhkj6
*/