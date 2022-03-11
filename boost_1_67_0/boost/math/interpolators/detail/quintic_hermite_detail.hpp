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
#include <cmath>

namespace boost::math::interpolators::detail {

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
#endif

/* quintic_hermite_detail.hpp
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
*/