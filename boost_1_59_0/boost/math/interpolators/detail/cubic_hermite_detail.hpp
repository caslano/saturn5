// Copyright Nick Thompson, 2020
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_DETAIL_CUBIC_HERMITE_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_DETAIL_CUBIC_HERMITE_DETAIL_HPP
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <limits>

namespace boost {
namespace math {
namespace interpolators {
namespace detail {

template<class RandomAccessContainer>
class cubic_hermite_detail {
public:
    using Real = typename RandomAccessContainer::value_type;
    using Size = typename RandomAccessContainer::size_type;

    cubic_hermite_detail(RandomAccessContainer && x, RandomAccessContainer && y, RandomAccessContainer dydx)
     : x_{std::move(x)}, y_{std::move(y)}, dydx_{std::move(dydx)}
    {
        using std::abs;
        using std::isnan;
        if (x_.size() != y_.size())
        {
            throw std::domain_error("There must be the same number of ordinates as abscissas.");
        }
        if (x_.size() != dydx_.size())
        {
            throw std::domain_error("There must be the same number of ordinates as derivative values.");
        }
        if (x_.size() < 2)
        {
            throw std::domain_error("Must be at least two data points.");
        }
        Real x0 = x_[0];
        for (size_t i = 1; i < x_.size(); ++i)
        {
            Real x1 = x_[i];
            if (x1 <= x0)
            {
                std::ostringstream oss;
                oss.precision(std::numeric_limits<Real>::digits10+3);
                oss << "Abscissas must be listed in strictly increasing order x0 < x1 < ... < x_{n-1}, ";
                oss << "but at x[" << i - 1 << "] = " << x0 << ", and x[" << i << "] = " << x1 << ".\n";
                throw std::domain_error(oss.str());
            }
            x0 = x1;
        }
    }

    void push_back(Real x, Real y, Real dydx)
    {
        using std::abs;
        using std::isnan;
        if (x <= x_.back())
        {
             throw std::domain_error("Calling push_back must preserve the monotonicity of the x's");
        }
        x_.push_back(x);
        y_.push_back(y);
        dydx_.push_back(dydx);
    }

    Real operator()(Real x) const
    {
        if  (x < x_[0] || x > x_.back())
        {
            std::ostringstream oss;
            oss.precision(std::numeric_limits<Real>::digits10+3);
            oss << "Requested abscissa x = " << x << ", which is outside of allowed range ["
                << x_[0] << ", " << x_.back() << "]";
            throw std::domain_error(oss.str());
        }
        // We need t := (x-x_k)/(x_{k+1}-x_k) \in [0,1) for this to work.
        // Sadly this neccessitates this loathesome check, otherwise we get t = 1 at x = xf.
        if (x == x_.back())
        {
            return y_.back();
        }

        auto it = std::upper_bound(x_.begin(), x_.end(), x);
        auto i = std::distance(x_.begin(), it) -1;
        Real x0 = *(it-1);
        Real x1 = *it;
        Real y0 = y_[i];
        Real y1 = y_[i+1];
        Real s0 = dydx_[i];
        Real s1 = dydx_[i+1];
        Real dx = (x1-x0);
        Real t = (x-x0)/dx;

        // See the section 'Representations' in the page
        // https://en.wikipedia.org/wiki/Cubic_Hermite_spline
        Real y = (1-t)*(1-t)*(y0*(1+2*t) + s0*(x-x0))
              + t*t*(y1*(3-2*t) + dx*s1*(t-1));
        return y;
    }

    Real prime(Real x) const
    {
        if  (x < x_[0] || x > x_.back())
        {
            std::ostringstream oss;
            oss.precision(std::numeric_limits<Real>::digits10+3);
            oss << "Requested abscissa x = " << x << ", which is outside of allowed range ["
                << x_[0] << ", " << x_.back() << "]";
            throw std::domain_error(oss.str());
        }
        if (x == x_.back())
        {
            return dydx_.back();
        }
        auto it = std::upper_bound(x_.begin(), x_.end(), x);
        auto i = std::distance(x_.begin(), it) -1;
        Real x0 = *(it-1);
        Real x1 = *it;
        Real y0 = y_[i];
        Real y1 = y_[i+1];
        Real s0 = dydx_[i];
        Real s1 = dydx_[i+1];
        Real dx = (x1-x0);

        Real d1 = (y1 - y0 - s0*dx)/(dx*dx);
        Real d2 = (s1 - s0)/(2*dx);
        Real c2 = 3*d1 - 2*d2;
        Real c3 = 2*(d2 - d1)/dx;
        return s0 + 2*c2*(x-x0) + 3*c3*(x-x0)*(x-x0); 
    }


    friend std::ostream& operator<<(std::ostream & os, const cubic_hermite_detail & m)
    {
        os << "(x,y,y') = {";
        for (size_t i = 0; i < m.x_.size() - 1; ++i)
        {
            os << "(" << m.x_[i] << ", " << m.y_[i] << ", " << m.dydx_[i] << "),  ";
        }
        auto n = m.x_.size()-1;
        os << "(" << m.x_[n] << ", " << m.y_[n] << ", " << m.dydx_[n] << ")}";
        return os;
    }

    Size size() const
    {
        return x_.size();
    }

    int64_t bytes() const
    {
        return 3*x_.size()*sizeof(Real) + 3*sizeof(x_);
    }

    std::pair<Real, Real> domain() const
    {
        return {x_.front(), x_.back()};
    }

    RandomAccessContainer x_;
    RandomAccessContainer y_;
    RandomAccessContainer dydx_;
};

template<class RandomAccessContainer>
class cardinal_cubic_hermite_detail {
public:
    using Real = typename RandomAccessContainer::value_type;
    using Size = typename RandomAccessContainer::size_type;

    cardinal_cubic_hermite_detail(RandomAccessContainer && y, RandomAccessContainer dydx, Real x0, Real dx)
    : y_{std::move(y)}, dy_{std::move(dydx)}, x0_{x0}, inv_dx_{1/dx}
    {
        using std::abs;
        using std::isnan;
        if (y_.size() != dy_.size())
        {
            throw std::domain_error("There must be the same number of derivatives as ordinates.");
        }
        if (y_.size() < 2)
        {
            throw std::domain_error("Must be at least two data points.");
        }
        if (dx <= 0)
        {
            throw std::domain_error("dx > 0 is required.");
        }

        for (auto & dy : dy_)
        {
            dy *= dx;
        }
    }

    // Why not implement push_back? It's awkward: If the buffer is circular, x0_ += dx_.
    // If the buffer is not circular, x0_ is unchanged.
    // We need a concept for circular_buffer!

    inline Real operator()(Real x) const
    {
        const Real xf = x0_ + (y_.size()-1)/inv_dx_;
        if  (x < x0_ || x > xf)
        {
            std::ostringstream oss;
            oss.precision(std::numeric_limits<Real>::digits10+3);
            oss << "Requested abscissa x = " << x << ", which is outside of allowed range ["
                << x0_ << ", " << xf << "]";
            throw std::domain_error(oss.str());
        }
        if (x == xf)
        {
            return y_.back();
        }
        return this->unchecked_evaluation(x);
    }

    inline Real unchecked_evaluation(Real x) const
    {
        using std::floor;
        Real s = (x-x0_)*inv_dx_;
        Real ii = floor(s);
        auto i = static_cast<decltype(y_.size())>(ii);
        Real t = s - ii;
        Real y0 = y_[i];
        Real y1 = y_[i+1];
        Real dy0 = dy_[i];
        Real dy1 = dy_[i+1];

        Real r = 1-t;
        return r*r*(y0*(1+2*t) + dy0*t)
              + t*t*(y1*(3-2*t) - dy1*r);
    }

    inline Real prime(Real x) const
    {
        const Real xf = x0_ + (y_.size()-1)/inv_dx_;
        if  (x < x0_ || x > xf)
        {
            std::ostringstream oss;
            oss.precision(std::numeric_limits<Real>::digits10+3);
            oss << "Requested abscissa x = " << x << ", which is outside of allowed range ["
                << x0_ << ", " << xf << "]";
            throw std::domain_error(oss.str());
        }
        if (x == xf)
        {
            return dy_.back()*inv_dx_;
        }
        return this->unchecked_prime(x);
    }

    inline Real unchecked_prime(Real x) const
    {
        using std::floor;
        Real s = (x-x0_)*inv_dx_;
        Real ii = floor(s);
        auto i = static_cast<decltype(y_.size())>(ii);
        Real t = s - ii;
        Real y0 = y_[i];
        Real y1 = y_[i+1];
        Real dy0 = dy_[i];
        Real dy1 = dy_[i+1];

        Real dy = 6*t*(1-t)*(y1 - y0)  + (3*t*t - 4*t+1)*dy0 + t*(3*t-2)*dy1;
        return dy*inv_dx_;
    }


    Size size() const
    {
        return y_.size();
    }

    int64_t bytes() const
    {
        return 2*y_.size()*sizeof(Real) + 2*sizeof(y_) + 2*sizeof(Real);
    }

    std::pair<Real, Real> domain() const
    {
        Real xf = x0_ + (y_.size()-1)/inv_dx_;
        return {x0_, xf};
    }

private:

    RandomAccessContainer y_;
    RandomAccessContainer dy_;
    Real x0_;
    Real inv_dx_;
};


template<class RandomAccessContainer>
class cardinal_cubic_hermite_detail_aos {
public:
    using Point = typename RandomAccessContainer::value_type;
    using Real = typename Point::value_type;
    using Size = typename RandomAccessContainer::size_type;

    cardinal_cubic_hermite_detail_aos(RandomAccessContainer && dat, Real x0, Real dx)
    : dat_{std::move(dat)}, x0_{x0}, inv_dx_{1/dx}
    {
        if (dat_.size() < 2)
        {
            throw std::domain_error("Must be at least two data points.");
        }
        if (dat_[0].size() != 2)
        {
            throw std::domain_error("Each datum must contain (y, y'), and nothing else.");
        }
        if (dx <= 0)
        {
            throw std::domain_error("dx > 0 is required.");
        }

        for (auto & d : dat_)
        {
            d[1] *= dx;
        }
    }

    inline Real operator()(Real x) const
    {
        const Real xf = x0_ + (dat_.size()-1)/inv_dx_;
        if  (x < x0_ || x > xf)
        {
            std::ostringstream oss;
            oss.precision(std::numeric_limits<Real>::digits10+3);
            oss << "Requested abscissa x = " << x << ", which is outside of allowed range ["
                << x0_ << ", " << xf << "]";
            throw std::domain_error(oss.str());
        }
        if (x == xf)
        {
            return dat_.back()[0];
        }
        return this->unchecked_evaluation(x);
    }

    inline Real unchecked_evaluation(Real x) const
    {
        using std::floor;
        Real s = (x-x0_)*inv_dx_;
        Real ii = floor(s);
        auto i = static_cast<decltype(dat_.size())>(ii);

        Real t = s - ii;
        // If we had infinite precision, this would never happen.
        // But we don't have infinite precision.
        if (t == 0)
        {
            return dat_[i][0];
        }
        Real y0 = dat_[i][0];
        Real y1 = dat_[i+1][0];
        Real dy0 = dat_[i][1];
        Real dy1 = dat_[i+1][1];

        Real r = 1-t;
        return r*r*(y0*(1+2*t) + dy0*t)
              + t*t*(y1*(3-2*t) - dy1*r);
    }

    inline Real prime(Real x) const
    {
        const Real xf = x0_ + (dat_.size()-1)/inv_dx_;
        if  (x < x0_ || x > xf)
        {
            std::ostringstream oss;
            oss.precision(std::numeric_limits<Real>::digits10+3);
            oss << "Requested abscissa x = " << x << ", which is outside of allowed range ["
                << x0_ << ", " << xf << "]";
            throw std::domain_error(oss.str());
        }
        if (x == xf)
        {
            return dat_.back()[1]*inv_dx_;
        }
        return this->unchecked_prime(x);
    }

    inline Real unchecked_prime(Real x) const
    {
        using std::floor;
        Real s = (x-x0_)*inv_dx_;
        Real ii = floor(s);
        auto i = static_cast<decltype(dat_.size())>(ii);
        Real t = s - ii;
        if (t == 0)
        {
            return dat_[i][1]*inv_dx_;
        }
        Real y0 = dat_[i][0];
        Real dy0 = dat_[i][1];
        Real y1 = dat_[i+1][0];
        Real dy1 = dat_[i+1][1];

        Real dy = 6*t*(1-t)*(y1 - y0)  + (3*t*t - 4*t+1)*dy0 + t*(3*t-2)*dy1;
        return dy*inv_dx_;
    }


    Size size() const
    {
        return dat_.size();
    }

    int64_t bytes() const
    {
        return dat_.size()*dat_[0].size()*sizeof(Real) + sizeof(dat_) + 2*sizeof(Real);
    }

    std::pair<Real, Real> domain() const
    {
        Real xf = x0_ + (dat_.size()-1)/inv_dx_;
        return {x0_, xf};
    }


private:
    RandomAccessContainer dat_;
    Real x0_;
    Real inv_dx_;
};

}
}
}
}
#endif

/* cubic_hermite_detail.hpp
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
*/