/*
 * Copyright Nick Thompson, 2020
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_MATH_INTERPOLATORS_DETAIL_QUINTIC_HERMITE_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_DETAIL_QUINTIC_HERMITE_DETAIL_HPP
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <limits>
#include <cmath>

namespace boost {
namespace math {
namespace interpolators {
namespace detail {

template<class RandomAccessContainer>
class quintic_hermite_detail {
public:
    using Real = typename RandomAccessContainer::value_type;
    quintic_hermite_detail(RandomAccessContainer && x, RandomAccessContainer && y, RandomAccessContainer && dydx, RandomAccessContainer && d2ydx2) : x_{std::move(x)}, y_{std::move(y)}, dydx_{std::move(dydx)}, d2ydx2_{std::move(d2ydx2)}
    {
        if (x_.size() != y_.size())
        {
            throw std::domain_error("Number of abscissas must = number of ordinates.");
        }
        if (x_.size() != dydx_.size())
        {
            throw std::domain_error("Numbers of derivatives must = number of abscissas.");
        }
        if (x_.size() != d2ydx2_.size())
        {
            throw std::domain_error("Number of second derivatives must equal number of abscissas.");
        }
        if (x_.size() < 2)
        {
            throw std::domain_error("At least 2 abscissas are required.");
        }
        Real x0 = x_[0];
        for (decltype(x_.size()) i = 1; i < x_.size(); ++i)
        {
            Real x1 = x_[i];
            if (x1 <= x0)
            {
                throw std::domain_error("Abscissas must be sorted in strictly increasing order x0 < x1 < ... < x_{n-1}");
            }
            x0 = x1;
        }
    }

    void push_back(Real x, Real y, Real dydx, Real d2ydx2)
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
        d2ydx2_.push_back(d2ydx2);
    }

    inline Real operator()(Real x) const
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
        Real v0 = dydx_[i];
        Real v1 = dydx_[i+1];
        Real a0 = d2ydx2_[i];
        Real a1 = d2ydx2_[i+1];

        Real dx = (x1-x0);
        Real t = (x-x0)/dx;
        Real t2 = t*t;
        Real t3 = t2*t;

        // See the 'Basis functions' section of:
        // https://www.rose-hulman.edu/~finn/CCLI/Notes/day09.pdf
        // Also: https://github.com/MrHexxx/QuinticHermiteSpline/blob/master/HermiteSpline.cs
        Real y = (1- t3*(10 + t*(-15 + 6*t)))*y0;
        y += t*(1+ t2*(-6 + t*(8 -3*t)))*v0*dx;
        y += t2*(1 + t*(-3 + t*(3-t)))*a0*dx*dx/2;
        y += t3*((1 + t*(-2 + t))*a1*dx*dx/2 + (-4 + t*(7 - 3*t))*v1*dx + (10 + t*(-15 + 6*t))*y1);
        return y;
    }

    inline Real prime(Real x) const
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
        Real dx = x1 - x0;

        Real y0 = y_[i];
        Real y1 = y_[i+1];
        Real v0 = dydx_[i];
        Real v1 = dydx_[i+1];
        Real a0 = d2ydx2_[i];
        Real a1 = d2ydx2_[i+1];
        Real t= (x-x0)/dx;
        Real t2 = t*t;

        Real dydx = 30*t2*(1 - 2*t + t*t)*(y1-y0)/dx;
        dydx += (1-18*t*t + 32*t*t*t - 15*t*t*t*t)*v0 - t*t*(12 - 28*t + 15*t*t)*v1;
        dydx += (t*dx/2)*((2 - 9*t + 12*t*t - 5*t*t*t)*a0 + t*(3 - 8*t + 5*t*t)*a1);
        return dydx;
    }

    inline Real double_prime(Real x) const
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
            return d2ydx2_.back();
        }

        auto it = std::upper_bound(x_.begin(), x_.end(), x);
        auto i = std::distance(x_.begin(), it) -1;
        Real x0 = *(it-1);
        Real x1 = *it;
        Real dx = x1 - x0;

        Real y0 = y_[i];
        Real y1 = y_[i+1];
        Real v0 = dydx_[i];
        Real v1 = dydx_[i+1];
        Real a0 = d2ydx2_[i];
        Real a1 = d2ydx2_[i+1];
        Real t = (x-x0)/dx;

        Real d2ydx2 = 60*t*(1 + t*(-3 + 2*t))*(y1-y0)/(dx*dx);
        d2ydx2 += 12*t*(-3 + t*(8 - 5*t))*v0/dx;
        d2ydx2 -= 12*t*(2 + t*(-7 + 5*t))*v1/dx;
        d2ydx2 += (1 + t*(-9 + t*(18 - 10*t)))*a0;
        d2ydx2 += t*(3 + t*(-12 + 10*t))*a1;

        return d2ydx2;
    }

    friend std::ostream& operator<<(std::ostream & os, const quintic_hermite_detail & m)
    {
        os << "(x,y,y') = {";
        for (size_t i = 0; i < m.x_.size() - 1; ++i) {
            os << "(" << m.x_[i] << ", " << m.y_[i] << ", " << m.dydx_[i] << ", " << m.d2ydx2_[i] << "),  ";
        }
        auto n = m.x_.size()-1;
        os << "(" << m.x_[n] << ", " << m.y_[n] << ", " << m.dydx_[n] << ", " << m.d2ydx2_[n] << ")}";
        return os;
    }

    int64_t bytes() const
    {
        return 4*x_.size()*sizeof(x_);
    }

    std::pair<Real, Real> domain() const
    {
        return {x_.front(), x_.back()};
    }

private:
    RandomAccessContainer x_;
    RandomAccessContainer y_;
    RandomAccessContainer dydx_;
    RandomAccessContainer d2ydx2_;
};


template<class RandomAccessContainer>
class cardinal_quintic_hermite_detail {
public:
    using Real = typename RandomAccessContainer::value_type;
    cardinal_quintic_hermite_detail(RandomAccessContainer && y, RandomAccessContainer && dydx, RandomAccessContainer && d2ydx2, Real x0, Real dx)
    : y_{std::move(y)}, dy_{std::move(dydx)}, d2y_{std::move(d2ydx2)}, x0_{x0}, inv_dx_{1/dx}
    {
        if (y_.size() != dy_.size())
        {
            throw std::domain_error("Numbers of derivatives must = number of abscissas.");
        }
        if (y_.size() != d2y_.size())
        {
            throw std::domain_error("Number of second derivatives must equal number of abscissas.");
        }
        if (y_.size() < 2)
        {
            throw std::domain_error("At least 2 abscissas are required.");
        }
        if (dx <= 0)
        {
            throw std::domain_error("dx > 0 is required.");
        }

        for (auto & dy : dy_)
        {
            dy *= dx;
        }

        for (auto & d2y : d2y_)
        {
            d2y *= (dx*dx)/2;
        }
    }


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
        if (t == 0)
        {
            return y_[i];
        }
        Real y0 = y_[i];
        Real y1 = y_[i+1];
        Real dy0 = dy_[i];
        Real dy1 = dy_[i+1];
        Real d2y0 = d2y_[i];
        Real d2y1 = d2y_[i+1];

        // See the 'Basis functions' section of:
        // https://www.rose-hulman.edu/~finn/CCLI/Notes/day09.pdf
        // Also: https://github.com/MrHexxx/QuinticHermiteSpline/blob/master/HermiteSpline.cs
        Real y = (1- t*t*t*(10 + t*(-15 + 6*t)))*y0;
        y += t*(1+ t*t*(-6 + t*(8 -3*t)))*dy0;
        y += t*t*(1 + t*(-3 + t*(3-t)))*d2y0;
        y += t*t*t*((1 + t*(-2 + t))*d2y1 + (-4 + t*(7 -3*t))*dy1 + (10 + t*(-15 + 6*t))*y1);
        return y;
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
        if (t == 0)
        {
            return dy_[i]*inv_dx_;
        }
        Real y0 = y_[i];
        Real y1 = y_[i+1];
        Real dy0 = dy_[i];
        Real dy1 = dy_[i+1];
        Real d2y0 = d2y_[i];
        Real d2y1 = d2y_[i+1];

        Real dydx = 30*t*t*(1 - 2*t + t*t)*(y1-y0);
        dydx += (1-18*t*t + 32*t*t*t - 15*t*t*t*t)*dy0 - t*t*(12 - 28*t + 15*t*t)*dy1;
        dydx += t*((2 - 9*t + 12*t*t - 5*t*t*t)*d2y0 + t*(3 - 8*t + 5*t*t)*d2y1);
        dydx *= inv_dx_;
        return dydx;
    }

    inline Real double_prime(Real x) const
    {
        const Real xf = x0_ + (y_.size()-1)/inv_dx_;
        if  (x < x0_ || x > xf) {
            std::ostringstream oss;
            oss.precision(std::numeric_limits<Real>::digits10+3);
            oss << "Requested abscissa x = " << x << ", which is outside of allowed range ["
                << x0_ << ", " << xf << "]";
            throw std::domain_error(oss.str());
        }
        if (x == xf)
        {
            return d2y_.back()*2*inv_dx_*inv_dx_;
        }

        return this->unchecked_double_prime(x);
    }

    inline Real unchecked_double_prime(Real x) const
    {
        using std::floor;
        Real s = (x-x0_)*inv_dx_;
        Real ii = floor(s);
        auto i = static_cast<decltype(y_.size())>(ii);
        Real t = s - ii;
        if (t==0)
        {
            return d2y_[i]*2*inv_dx_*inv_dx_;
        }

        Real y0 = y_[i];
        Real y1 = y_[i+1];
        Real dy0 = dy_[i];
        Real dy1 = dy_[i+1];
        Real d2y0 = d2y_[i];
        Real d2y1 = d2y_[i+1];

        Real d2ydx2 = 60*t*(1 - 3*t + 2*t*t)*(y1 - y0)*inv_dx_*inv_dx_;
        d2ydx2 += (12*t)*((-3 + 8*t - 5*t*t)*dy0 - (2 - 7*t + 5*t*t)*dy1);
        d2ydx2 += (1 - 9*t + 18*t*t - 10*t*t*t)*d2y0*(2*inv_dx_*inv_dx_) + t*(3 - 12*t + 10*t*t)*d2y1*(2*inv_dx_*inv_dx_);
        return d2ydx2;
    }

    int64_t bytes() const
    {
        return 3*y_.size()*sizeof(Real) + 2*sizeof(Real);
    }

    std::pair<Real, Real> domain() const
    {
        Real xf = x0_ + (y_.size()-1)/inv_dx_;
        return {x0_, xf};
    }

private:
    RandomAccessContainer y_;
    RandomAccessContainer dy_;
    RandomAccessContainer d2y_;
    Real x0_;
    Real inv_dx_;
};


template<class RandomAccessContainer>
class cardinal_quintic_hermite_detail_aos {
public:
    using Point = typename RandomAccessContainer::value_type;
    using Real = typename Point::value_type;
    cardinal_quintic_hermite_detail_aos(RandomAccessContainer && data, Real x0, Real dx)
    : data_{std::move(data)} , x0_{x0}, inv_dx_{1/dx}
    {
        if (data_.size() < 2)
        {
            throw std::domain_error("At least two points are required to interpolate using cardinal_quintic_hermite_aos");
        }

        if (data_[0].size() != 3)
        {
            throw std::domain_error("Each datum passed to the cardinal_quintic_hermite_aos must have three elements: {y, y', y''}");
        }
        if (dx <= 0)
        {
            throw std::domain_error("dx > 0 is required.");
        }

        for (auto & datum : data_)
        {
            datum[1] *= dx;
            datum[2] *= (dx*dx/2);
        }
    }


    inline Real operator()(Real x) const
    {
        const Real xf = x0_ + (data_.size()-1)/inv_dx_;
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
            return data_.back()[0];
        }
        return this->unchecked_evaluation(x);
    }

    inline Real unchecked_evaluation(Real x) const
    {
        using std::floor;
        Real s = (x-x0_)*inv_dx_;
        Real ii = floor(s);
        auto i = static_cast<decltype(data_.size())>(ii);
        Real t = s - ii;
        if (t == 0)
        {
            return data_[i][0];
        }

        Real y0 = data_[i][0];
        Real dy0 = data_[i][1];
        Real d2y0 = data_[i][2];
        Real y1 = data_[i+1][0];
        Real dy1 = data_[i+1][1];
        Real d2y1 = data_[i+1][2];

        Real y = (1 - t*t*t*(10 + t*(-15 + 6*t)))*y0;
        y += t*(1 + t*t*(-6 + t*(8 - 3*t)))*dy0;
        y += t*t*(1 + t*(-3 + t*(3 - t)))*d2y0;
        y += t*t*t*((1 + t*(-2 + t))*d2y1 + (-4 + t*(7 - 3*t))*dy1 + (10 + t*(-15 + 6*t))*y1);
        return y;
    }

    inline Real prime(Real x) const
    {
        const Real xf = x0_ + (data_.size()-1)/inv_dx_;
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
            return data_.back()[1]*inv_dx_;
        }

        return this->unchecked_prime(x);
    }

    inline Real unchecked_prime(Real x) const
    {
        using std::floor;
        Real s = (x-x0_)*inv_dx_;
        Real ii = floor(s);
        auto i = static_cast<decltype(data_.size())>(ii);
        Real t = s - ii;
        if (t == 0)
        {
            return data_[i][1]*inv_dx_;
        }


        Real y0 = data_[i][0];
        Real y1 = data_[i+1][0];
        Real v0 = data_[i][1];
        Real v1 = data_[i+1][1];
        Real a0 = data_[i][2];
        Real a1 = data_[i+1][2];

        Real dy = 30*t*t*(1 - 2*t + t*t)*(y1-y0);
        dy += (1-18*t*t + 32*t*t*t - 15*t*t*t*t)*v0 - t*t*(12 - 28*t + 15*t*t)*v1;
        dy += t*((2 - 9*t + 12*t*t - 5*t*t*t)*a0 + t*(3 - 8*t + 5*t*t)*a1);
        return dy*inv_dx_;
    }

    inline Real double_prime(Real x) const
    {
        const Real xf = x0_ + (data_.size()-1)/inv_dx_;
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
            return data_.back()[2]*2*inv_dx_*inv_dx_;
        }

        return this->unchecked_double_prime(x);
    }

    inline Real unchecked_double_prime(Real x) const
    {
        using std::floor;
        Real s = (x-x0_)*inv_dx_;
        Real ii = floor(s);
        auto i = static_cast<decltype(data_.size())>(ii);
        Real t = s - ii;
        if (t == 0) {
            return data_[i][2]*2*inv_dx_*inv_dx_;
        }
        Real y0 = data_[i][0];
        Real dy0 = data_[i][1];
        Real d2y0 = data_[i][2];
        Real y1 = data_[i+1][0];
        Real dy1 = data_[i+1][1];
        Real d2y1 = data_[i+1][2];

        Real d2ydx2 = 60*t*(1 - 3*t + 2*t*t)*(y1 - y0)*inv_dx_*inv_dx_;
        d2ydx2 += (12*t)*((-3 + 8*t - 5*t*t)*dy0 - (2 - 7*t + 5*t*t)*dy1);
        d2ydx2 += (1 - 9*t + 18*t*t - 10*t*t*t)*d2y0*(2*inv_dx_*inv_dx_) + t*(3 - 12*t + 10*t*t)*d2y1*(2*inv_dx_*inv_dx_);
        return d2ydx2;
    }

    int64_t bytes() const
    {
        return data_.size()*data_[0].size()*sizeof(Real) + 2*sizeof(Real);
    }

    std::pair<Real, Real> domain() const
    {
        Real xf = x0_ + (data_.size()-1)/inv_dx_;
        return {x0_, xf};
    }

private:
    RandomAccessContainer data_;
    Real x0_;
    Real inv_dx_;
};

}
}
}
}
#endif

/* quintic_hermite_detail.hpp
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
*/