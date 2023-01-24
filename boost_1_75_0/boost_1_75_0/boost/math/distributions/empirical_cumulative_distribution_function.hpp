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
D+GvfFE833YBZ8z17d++QEdj+1oNv3+itYJSE2G3j3oev2ORkF1y9Y5ErZhLfK/ROgqzh45GRpW3J7glfxmBvaMAPHg8jNuaRBhReemWKiDvlL2Q8Md2JKK92M8X6N/6AoX8ZH1CL2x5/hwjlsWap48lYinZ8kUSnwzp7eo6810VMQ2XaI15RTHoABaMhl3CUkhehX59q4ab8Ko+SMMUn1M37VUi2s14HdGlE1cfyB1EWvWrN+cz017hG/9MDM3kYJt11NEYiI8jTfiYJQ6iRclRZdzuxfRww0QOOHoqElC7t68pPFBCQvimDjD1J9z6N7uA+swbfGW6rjR7eTsVPgcgqZ5j/DYbGOJwbmtwZnAyBoZEOvItk2bT+Bv/YBHH/vxjZLNju8wv06pf2Bwm+NCF9WjQgUznf/ALyZI795uu98UQ+sy9f9P4AQBjCWp7IYRRVHknQ5TEdu1iRTFhawFq9iPIMCuZG9vFRSO6LD+jqHTEgFGmJgvxVzETgijXWCRW3qPffBwo/PkthOgikJ//SJqImxSZiXUNe05PRwUlu1FNusOzOVY+LiLRuyu7Jbf4TN86CztjdhfD322pxLmZMqlhsaIloXmhaHdj77ill2C0ULSE7/kVEiOYTXnVMAVeMdZglGCeoy+g4nUL5bzVI7B/xYeaHnHhEMGHBhgXMrpcD8Tcmo3lMACgiBGydcO70Sw3pE8VtxrT
*/