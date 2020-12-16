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
H+fLIk7/lO/YW6st50jJN9L6ObiuGo4yq+yST9GzvKTyONSXZnUkNmEcbVRhG3zJ1HqZ1c/3uC/RoTcpq5widZ4KV6vfaa7tNlaouEkxn1v5DETvar3pi+e3OEfodbYs4THsptKSfP5EPp9U8okxLWrTF3nmDyv5h5E+1JSGc583+kztPnPzlMzN1jbWmdS11KkdRhm3tbrzC3dY+vewLMmSsmxQebnUF2clU/tjrJOtGF+69I+jVfyRvouo69+tEaTrrKvHdV2l2vKEnKLa8CCuoE76t0hF5bEVf2Wq9ErYiy5e/UYmYVeosHa+k/mifcIaRfmQdfQHJafT7mulUO+9+N0WtfUgcdgD3U6Lc204TuP4TpXPNjHfWsXWGbTLR5QyISaO/HCeMx8q+TfYP+dW1TbVtM1DKk56TG3bV6iJ38H8rlbnH/K9Rk1Vkma4/JGe2u/tGSXf3NHWU3SbrVC/fxFriRwqbRZs6+1929Bmk2iz4P53n3OBfUCkI/D8jf5N9sRzUnRylF27ZMP+d9Rtnf3vpiDYWu5DQT1drxQVVuGcC++PI0zuI6mh+ztykYXuv5kkCsHnZS7oOvzKHNJ4UnSi4+u7H3Is/XC5kp9tuj9KWj7VH34M2lNJ+1eqc09bifzfG/8YPp1qSNDxLrU68yuVxA6mKedc97vATH+Rce0BLeu8lrOkr8xQ51ZZzcjp7tTMw/j2yKlKiyt0lb/jXnsV7sp/xfo+85OKv5PzutW62aXq3Cn6HnGDOr4Qf77Kd1U7hILtJGW+VMncSFtRXvpVLGFrUrQXfW79fWfPp+rvOy2l7/woOt/QfRNVPSKTpOrAj2CsVaz7G3mWvuW0IQuv1zXrJ8Prdc362/D6zOuVnrbsxiXjhi/+dkj1M1f/us/nHU5sOj1ttPrYpprv3lT6WLN+O5w+PHo9bVPqY5f65N1E3s9mwN3wi+0A2SMtCfaCveCesC/sD/eHA+BBcCAcCfeDR8D9YSHMh8XwAFgJD4KnwCHwSjm+Do6Bt8Bx8HY4AS6HxXAFLIGPwTK4Fk6Fr0I//ApOgz/C6fBXOBM2owyzYDI8Dm4PZ8N28GS4GzwF5kFbfjA8DQ6Dp8PR8Ax4HNwTzoXl8GJYARfAAFwIj4e3wxPhE3A+XAuPhu/BY+DXsBT+KOd/hefDVtT7BTATXgjbwHlwR3gO7AzPhd3hfJmHvzx4j4XPyzz8NPyS4DpKYvuXLu2XAZNhN5gCt4V4pTfvCbPhnnAn2Efk9oFtYD5sK+2YA4+H7eGJMBeeIbaB98NO8FFJ5wlJZy3cGa6T4zzPhtCzIWyEDWE1uuTkyv+fPnlzjP9PLigpCzTB+v/2t//7uZZeH4l1fnG1awozdqe+/fs+GvrtP2jIqIMHDe/HQlCRff8TP+z3fwYcrM7vaPr+J67p+9/4Hots5N/4Lllc+XSnTmK0Or+tXqvpg9yG5xVsyu+Qalmna1/Ry0DVNnNcbTN4yMhB+w8aHlG7ELdevcw16nwH/S5ftUp9V5rtNMK0U/A7vEqd3yXma56OF/jmmtdAi6L9kK1XR+N7zD67wteCHWOPtbppHc3oVXV1NIlKtkWIjqa1Crte6WgmWu9aY3y9rHT5vk5R527zzbSesY7zZZn1NJKP1SqfR/pirOG+YD0+rsLStC7iXXVcZesiqJ3PwupsXn4sVGezWMXbLuY7q8g6wXe09R2/kC7fUrcr2Veplz68v43R3/J3qDgtjXqbe1WcRcQYqNO5W4U9r/Q2+aQTTnezSMnNR3dTIW0QzMNH9Ofu3BMrjLqbN1V+1ovuZpZ1tdVF625OUvEzfedyT3vF6llPfSGv27a7U2+j9Spbq7Q=
*/