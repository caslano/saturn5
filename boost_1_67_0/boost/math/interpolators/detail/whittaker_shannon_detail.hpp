// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_MATH_INTERPOLATORS_WHITAKKER_SHANNON_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_WHITAKKER_SHANNON_DETAIL_HPP
#include <boost/assert.hpp>
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
            BOOST_ASSERT_MSG(floor(x) == ceil(x), "Floor and ceiling should be equal.\n");
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