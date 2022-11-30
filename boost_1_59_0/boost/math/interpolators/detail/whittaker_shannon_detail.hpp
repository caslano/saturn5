// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_MATH_INTERPOLATORS_WHITAKKER_SHANNON_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_WHITAKKER_SHANNON_DETAIL_HPP
#include <cmath>
#include <boost/math/tools/assert.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/sin_pi.hpp>
#include <boost/math/special_functions/cos_pi.hpp>

namespace boost { namespace math { namespace interpolators { namespace detail {

template<class RandomAccessContainer>
class whittaker_shannon_detail {
public:

    using Real = typename RandomAccessContainer::value_type;
    whittaker_shannon_detail(RandomAccessContainer&& y, Real const & t0, Real const & h) : m_y{std::move(y)}, m_t0{t0}, m_h{h}
    {
        for (size_t i = 1; i < m_y.size(); i += 2)
        {
            m_y[i] = -m_y[i];
        }
    }

    inline Real operator()(Real t) const {
        using boost::math::constants::pi;
        using std::isfinite;
        using std::floor;
        Real y = 0;
        Real x = (t - m_t0)/m_h;
        Real z = x;
        auto it = m_y.begin();

        // For some reason, neither clang nor g++ will cache the address of m_y.end() in a register.
        // Hence make a copy of it:
        auto end = m_y.end();
        while(it != end)
        {

            y += *it++/z;
            z -= 1;
        }

        if (!isfinite(y))
        {
            BOOST_MATH_ASSERT_MSG(floor(x) == ceil(x), "Floor and ceiling should be equal.\n");
            size_t i = static_cast<size_t>(floor(x));
            if (i & 1)
            {
                return -m_y[i];
            }
            return m_y[i];
        }
        return y*boost::math::sin_pi(x)/pi<Real>();
    }

    Real prime(Real t) const {
        using boost::math::constants::pi;
        using std::isfinite;
        using std::floor;

        Real x = (t - m_t0)/m_h;
        if (ceil(x) == x) {
            Real s = 0;
            long j = static_cast<long>(x);
            long n = m_y.size();
            for (long i = 0; i < n; ++i)
            {
                if (j - i != 0)
                {
                    s += m_y[i]/(j-i);
                }
                // else derivative of sinc at zero is zero.
            }
            if (j & 1) {
                s /= -m_h;
            } else {
                s /= m_h;
            }
            return s;
        }
        Real z = x;
        auto it = m_y.begin();
        Real cospix = boost::math::cos_pi(x);
        Real sinpix_div_pi = boost::math::sin_pi(x)/pi<Real>();

        Real s = 0;
        auto end = m_y.end();
        while(it != end)
        {
            s += (*it++)*(z*cospix - sinpix_div_pi)/(z*z);
            z -= 1;
        }

        return s/m_h;
    }



    Real operator[](size_t i) const {
        if (i & 1)
        {
            return -m_y[i];
        }
        return m_y[i];
    }

    RandomAccessContainer&& return_data() {
        for (size_t i = 1; i < m_y.size(); i += 2)
        {
            m_y[i] = -m_y[i];
        }
        return std::move(m_y);
    }


private:
    RandomAccessContainer m_y;
    Real m_t0;
    Real m_h;
};
}}}}
#endif

/* whittaker_shannon_detail.hpp
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
*/