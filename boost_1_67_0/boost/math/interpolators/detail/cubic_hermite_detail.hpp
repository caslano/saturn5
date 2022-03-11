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

namespace boost::math::interpolators::detail {

template<class RandomAccessContainer>
class cubic_hermite_detail {
public:
    using Real = typename RandomAccessContainer::value_type;

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

    auto size() const
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


    auto size() const
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


    auto size() const
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
#endif

/* cubic_hermite_detail.hpp
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
*/