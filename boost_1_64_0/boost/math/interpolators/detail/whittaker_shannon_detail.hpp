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
FmHhfjqSso9KsPzxUv6SgYaisXJdbWFQNnq6OeK6iig1aMj4XYxcL1kPqre0GZHX1M1R15ToS827i+Cj4WMSqK81rijPXlpEX/rUX9YQcIqJ0o618drR2NC+cg3EbY8804FHmPmcgp32ZFsbJX/labotdbTC1xj5ofURFFpTeSj7EEq2+6jWqDw3MNtBeuIInaji+pF+l4yl9M0XaOZYtW7a3ZnUz5luralOJP4TOLSmqou7ppqh8hspYcmfkHkvNNk+hluFM6RP7JbQfSP7RPkqXqLyShd/1w5xY4wu+m6q9J0zy1B0vMyVi+BrkH/6iIi+w9u1sWEOg142G1w1oUek0DOkzMEzlA6CLGu8wSh/ZPKLGo+yhlBPsi5JY1uHOBeEdJUfft6XR315YLTL5ivZnHA/7qDC/dAjzyUIBDNZy6PXpPSU/klpA7ZLcTrTaGvEc9Pxove8KF/TyVG+pq+avqbiXzxpQaRf8sRwuHKs1SeVEic+56Szx40Jrz3RnWgu8pny8ayO+wfXoY+5C+z94/f6mNujnykzbb7i4q1s7xPyiOyT8DNkN+aFWL7Q46Xur2YbioZL3cvgG6pIY6979LwaTNzH/fyI+tvbW+tvPMjcRrPtC0TJO2332BMSnAu78g13ym/h0kUfG4s+puUairYSfYyF30B+RUgfMi2G2vFKmWpHc4Osb+3tRj76WpL5TiZWtaxun+s+UPK59K+Dv7tkrKJfVpHZibTZmZ7kdGQhS3wdca/CoX223Lj7bG+q/Pp23IORee8d9ftg3jjhCM91lq5PIu+T4UT2314OldNlv1hjEZ3ZNCb7JNYe5iBDUaXofhP4wI0MY1DoHSARe6+GjKVX4/cB6RLrA6stI5V8ntLzdMbBtEGi/8wkFbeGuOpBlu6z4uq+vKXzPc4R6vf8Dno/pRt6H9rSPb2/atd71JgPyoSaI3rPEr1PE72rPewE9I18zLmqLYHrtpN6ij3eP8/urk+5GT8z+Z7x1/103qjKaWvvdzzVdpG2x+tpe7zvjLDfrdpPyQN3mxq6DpcwLt6HzT2NMeCh8HH83ybrlhNF5iv4WPn/Z1h8EeUsQ60L+S3SF/FLFhhm+CswE1wLSjrZx6cvYqRbJ+l+BgeDSQ5JZ+17g6kx0q2WdO+DA8APpLwieIUtHe2UOofoUJGrs/ZxZY+5De4P7ydyW4uPZBXoBLcDc8DtwUJwB3B9cEdwtIS3AncFx4PV4ARwZ/ArcEZ4bxGU8vrB06S8IVJeAdgfHCrlbg6mgSVgHjgcLABHSPkVYKXIWe33Szl9ZC1ubz9jQcnNNWQfD9xM6uOEfQYkPtkmngj2A08BB4AXSL1OA9U+ntTnTHCYhDcCzwcrRL4SPFv0RFj0L3ty4IYx9D+3V6j8eWA/8DAwDTwcTAcXgEXgQrAYbAVLwEXgcPBYcITEy3iSfTXuYVKefTw1SHmNYCrYDEq/yZ4YfRKj326RdEulnrfLeHwAdIJ3gTngPWA+uAwcAt4PFoqc+Oyy9yXjVsqx++w+LOU8Aprxj4L9wceknMcln2rZewmPsyhf5APkunGBmeAscIj4IA+TcCl4IFgJzpZ8JxuylwGWSL4p8DhrvEj9ThQ9nAxmg2dJ+08DiyVs9cclVntj9Me5kt8NYF/wRkk319oLAMfGGLd3yXV0t4zbZWA6eD+YAz4EFoLLQTVXyD31MXBD8AlwFPgkuBn4DLiFyH0FLrHW5eC1Un4WfLkhawPqmQJuAA4ENwQHgRvL+BwFVoCbg1XgVuBUcGtwd3A7cC9wB3BfCR8g4RoJByS8AJwMLgZ3Bs8Dp4AXgruAl4IVorcmWbOqtaHUewDskXpPl+s=
*/