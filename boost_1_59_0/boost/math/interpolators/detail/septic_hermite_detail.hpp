/*
 * Copyright Nick Thompson, 2020
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_MATH_INTERPOLATORS_DETAIL_SEPTIC_HERMITE_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_DETAIL_SEPTIC_HERMITE_DETAIL_HPP
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
class septic_hermite_detail {
public:
    using Real = typename RandomAccessContainer::value_type;
    septic_hermite_detail(RandomAccessContainer && x, RandomAccessContainer && y, RandomAccessContainer && dydx, RandomAccessContainer && d2ydx2, RandomAccessContainer && d3ydx3) 
    : x_{std::move(x)}, y_{std::move(y)}, dydx_{std::move(dydx)}, d2ydx2_{std::move(d2ydx2)}, d3ydx3_{std::move(d3ydx3)}
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
        if (x_.size() != d3ydx3_.size())
        {
            throw std::domain_error("Number of third derivatives must equal number of abscissas.");
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

    void push_back(Real x, Real y, Real dydx, Real d2ydx2, Real d3ydx3)
    {
        using std::abs;
        using std::isnan;
        if (x <= x_.back()) {
             throw std::domain_error("Calling push_back must preserve the monotonicity of the x's");
        }
        x_.push_back(x);
        y_.push_back(y);
        dydx_.push_back(dydx);
        d2ydx2_.push_back(d2ydx2);
        d3ydx3_.push_back(d3ydx3);
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
        // t \in [0, 1)
        if (x == x_.back())
        {
            return y_.back();
        }

        auto it = std::upper_bound(x_.begin(), x_.end(), x);
        auto i = std::distance(x_.begin(), it) -1;
        Real x0 = *(it-1);
        Real x1 = *it;
        Real dx = (x1-x0);
        Real t = (x-x0)/dx;

        // See: 
        // http://seisweb.usask.ca/classes/GEOL481/2017/Labs/interpolation_utilities_matlab/shermite.m
        Real t2 = t*t;
        Real t3 = t2*t;
        Real t4 = t3*t;
        Real dx2 = dx*dx/2;
        Real dx3 = dx2*dx/3;

        Real s = t4*(-35 + t*(84 + t*(-70 + 20*t)));
        Real z4 = -s;
        Real z0 = s + 1;
        Real z1 = t*(1 + t3*(-20 + t*(45 + t*(-36 + 10*t))));
        Real z2 = t2*(1 + t2*(-10 + t*(20 + t*(-15 + 4*t))));
        Real z3 = t3*(1 + t*(-4 + t*(6 + t*(-4 + t))));
        Real z5 = t4*(-15 + t*(39 + t*(-34 + 10*t)));
        Real z6 = t4*(5 + t*(-14 + t*(13 - 4*t)));
        Real z7 = t4*(-1 + t*(3 + t*(-3+t)));

        Real y0 = y_[i];
        Real y1 = y_[i+1];
        // Velocity:
        Real v0 = dydx_[i];
        Real v1 = dydx_[i+1];
        // Acceleration:
        Real a0 = d2ydx2_[i];
        Real a1 = d2ydx2_[i+1];
        // Jerk:
        Real j0 = d3ydx3_[i];
        Real j1 = d3ydx3_[i+1];

        return z0*y0 + z4*y1 + (z1*v0 + z5*v1)*dx + (z2*a0 + z6*a1)*dx2 + (z3*j0 + z7*j1)*dx3;
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
        Real v0 = dydx_[i];
        Real v1 = dydx_[i+1];
        Real a0 = d2ydx2_[i];
        Real a1 = d2ydx2_[i+1];
        Real j0 = d3ydx3_[i];
        Real j1 = d3ydx3_[i+1];
        Real dx = x1 - x0;
        Real t = (x-x0)/dx;
        Real t2 = t*t;
        Real t3 = t2*t;
        Real z0 = 140*t3*(1 + t*(-3 + t*(3 - t)));
        Real z1 = 1 + t3*(-80 + t*(225 + t*(-216 + 70*t)));
        Real z2 = t3*(-60 + t*(195 + t*(-204 + 70*t)));
        Real z3 = 1 + t2*(-20 + t*(50 + t*(-45 + 14*t)));
        Real z4 = t2*(10 + t*(-35 + t*(39 - 14*t)));
        Real z5 = 3 + t*(-16 + t*(30 + t*(-24 + 7*t)));
        Real z6 = t*(-4 + t*(15 + t*(-18 + 7*t)));

        Real dydx = z0*(y1-y0)/dx;
        dydx += z1*v0 + z2*v1;
        dydx += (x-x0)*(z3*a0 + z4*a1);
        dydx += (x-x0)*(x-x0)*(z5*j0 + z6*j1)/6;
        return dydx;
    }

    inline Real double_prime(Real) const
    {
        return std::numeric_limits<Real>::quiet_NaN();
    }

    friend std::ostream& operator<<(std::ostream & os, const septic_hermite_detail & m)
    {
        os << "(x,y,y') = {";
        for (size_t i = 0; i < m.x_.size() - 1; ++i) {
            os << "(" << m.x_[i] << ", " << m.y_[i] << ", " << m.dydx_[i] << ", " << m.d2ydx2_[i] <<  ", " << m.d3ydx3_[i] << "),  ";
        }
        auto n = m.x_.size()-1;
        os << "(" << m.x_[n] << ", " << m.y_[n] << ", " << m.dydx_[n] << ", " << m.d2ydx2_[n] << m.d3ydx3_[n] << ")}";
        return os;
    }

    int64_t bytes()
    {
        return 5*x_.size()*sizeof(Real) + 5*sizeof(x_);
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
    RandomAccessContainer d3ydx3_;
};

template<class RandomAccessContainer>
class cardinal_septic_hermite_detail {
public:
    using Real = typename RandomAccessContainer::value_type;
    cardinal_septic_hermite_detail(RandomAccessContainer && y, RandomAccessContainer && dydx, RandomAccessContainer && d2ydx2, RandomAccessContainer && d3ydx3, Real x0, Real dx)
    : y_{std::move(y)}, dy_{std::move(dydx)}, d2y_{std::move(d2ydx2)}, d3y_{std::move(d3ydx3)}, x0_{x0}, inv_dx_{1/dx}
    {
        if (y_.size() != dy_.size())
        {
            throw std::domain_error("Numbers of derivatives must = number of ordinates.");
        }
        if (y_.size() != d2y_.size())
        {
            throw std::domain_error("Number of second derivatives must equal number of ordinates.");
        }
        if (y_.size() != d3y_.size())
        {
            throw std::domain_error("Number of third derivatives must equal number of ordinates.");
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
            d2y *= (dx*dx/2);
        }
        for (auto & d3y : d3y_)
        {
            d3y *= (dx*dx*dx/6);
        }

    }

    inline Real operator()(Real x) const
    {
        Real xf = x0_ + (y_.size()-1)/inv_dx_;
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

    inline Real unchecked_evaluation(Real x) const {
        using std::floor;
        Real s3 = (x-x0_)*inv_dx_;
        Real ii = floor(s3);
        auto i = static_cast<decltype(y_.size())>(ii);
        Real t = s3 - ii;
        if (t == 0) {
            return y_[i];
        }
        // See:
        // http://seisweb.usask.ca/classes/GEOL481/2017/Labs/interpolation_utilities_matlab/shermite.m
        Real t2 = t*t;
        Real t3 = t2*t;
        Real t4 = t3*t;

        Real s = t4*(-35 + t*(84 + t*(-70 + 20*t)));
        Real z4 = -s;
        Real z0 = s + 1;
        Real z1 = t*(1 + t3*(-20 + t*(45 + t*(-36+10*t))));
        Real z2 = t2*(1 + t2*(-10 + t*(20 + t*(-15+4*t))));
        Real z3 = t3*(1 + t*(-4+t*(6+t*(-4+t))));
        Real z5 = t4*(-15 + t*(39 + t*(-34 + 10*t)));
        Real z6 = t4*(5 + t*(-14 + t*(13-4*t)));
        Real z7 = t4*(-1 + t*(3+t*(-3+t)));

        Real y0 = y_[i];
        Real y1 = y_[i+1];
        Real dy0 = dy_[i];
        Real dy1 = dy_[i+1];
        Real a0 = d2y_[i];
        Real a1 = d2y_[i+1];
        Real j0 = d3y_[i];
        Real j1 = d3y_[i+1];

        return z0*y0 + z1*dy0 + z2*a0 + z3*j0 + z4*y1 + z5*dy1 + z6*a1 + z7*j1;
    }

    inline Real prime(Real x) const
    {
        Real xf = x0_ + (y_.size()-1)/inv_dx_;
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
            return dy_.back()/inv_dx_;
        }

        return this->unchecked_prime(x);
    }

    inline Real unchecked_prime(Real x) const
    {
        using std::floor;
        Real s3 = (x-x0_)*inv_dx_;
        Real ii = floor(s3);
        auto i = static_cast<decltype(y_.size())>(ii);
        Real t = s3 - ii;
        if (t==0)
        {
            return dy_[i]/inv_dx_;
        }
 
        Real y0 = y_[i];
        Real y1 = y_[i+1];
        Real dy0 = dy_[i];
        Real dy1 = dy_[i+1];
        Real a0 = d2y_[i];
        Real a1 = d2y_[i+1];
        Real j0 = d3y_[i];
        Real j1 = d3y_[i+1];
        Real t2 = t*t;
        Real t3 = t2*t;
        Real z0 = 140*t3*(1 + t*(-3 + t*(3 - t)));
        Real z1 = 1 + t3*(-80 + t*(225 + t*(-216 + 70*t)));
        Real z2 = t3*(-60 + t*(195 + t*(-204 + 70*t)));
        Real z3 = 1 + t2*(-20 + t*(50 + t*(-45 + 14*t)));
        Real z4 = t2*(10 + t*(-35 + t*(39 - 14*t)));
        Real z5 = 3 + t*(-16 + t*(30 + t*(-24 + 7*t)));
        Real z6 = t*(-4 + t*(15 + t*(-18 + 7*t)));

        Real dydx = z0*(y1-y0)*inv_dx_;
        dydx += (z1*dy0 + z2*dy1)*inv_dx_;
        dydx += 2*t*(z3*a0 + z4*a1)*inv_dx_;
        dydx += t*t*(z5*j0 + z6*j1);
        return dydx;
    }

    inline Real double_prime(Real x) const
    {
        Real xf = x0_ + (y_.size()-1)/inv_dx_;
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
            return d2y_.back()*2*inv_dx_*inv_dx_;
        }

        return this->unchecked_double_prime(x);
    }

    inline Real unchecked_double_prime(Real x) const
    {
        using std::floor;
        Real s3 = (x-x0_)*inv_dx_;
        Real ii = floor(s3);
        auto i = static_cast<decltype(y_.size())>(ii);
        Real t = s3 - ii;
        if (t==0)
        {
            return d2y_[i]*2*inv_dx_*inv_dx_;
        }

        Real y0 = y_[i];
        Real y1 = y_[i+1];
        Real dy0 = dy_[i];
        Real dy1 = dy_[i+1];
        Real a0 = d2y_[i];
        Real a1 = d2y_[i+1];
        Real j0 = d3y_[i];
        Real j1 = d3y_[i+1];
        Real t2 = t*t;

        Real z0 = 420*t2*(1 + t*(-4 + t*(5 - 2*t)));
        Real z1 = 60*t2*(-4 + t*(15 + t*(-18 + 7*t)));
        Real z2 = 60*t2*(-3 + t*(13 + t*(-17 + 7*t)));
        Real z3 = (1 + t2*(-60 + t*(200 + t*(-225 + 84*t))));
        Real z4 = t2*(30 + t*(-140 + t*(195 - 84*t)));
        Real z5 = t*(1 + t*(-8 + t*(20 + t*(-20 + 7*t))));
        Real z6 = t2*(-2 + t*(10 + t*(-15 + 7*t)));

        Real d2ydx2 = z0*(y1-y0)*inv_dx_*inv_dx_;
        d2ydx2 += (z1*dy0 + z2*dy1)*inv_dx_*inv_dx_;
        d2ydx2 += (z3*a0 + z4*a1)*2*inv_dx_*inv_dx_;
        d2ydx2 += 6*(z5*j0 + z6*j1)/(inv_dx_*inv_dx_);

        return d2ydx2;
    }

    int64_t bytes() const
    {
        return 4*y_.size()*sizeof(Real) + 2*sizeof(Real) + 4*sizeof(y_);
    }

    std::pair<Real, Real> domain() const
    {
        return {x0_, x0_ + (y_.size()-1)/inv_dx_};
    }

private:
    RandomAccessContainer y_;
    RandomAccessContainer dy_;
    RandomAccessContainer d2y_;
    RandomAccessContainer d3y_;
    Real x0_;
    Real inv_dx_;
};


template<class RandomAccessContainer>
class cardinal_septic_hermite_detail_aos {
public:
    using Point = typename RandomAccessContainer::value_type;
    using Real = typename Point::value_type;
    cardinal_septic_hermite_detail_aos(RandomAccessContainer && dat, Real x0, Real dx)
    : data_{std::move(dat)}, x0_{x0}, inv_dx_{1/dx}
    {
        if (data_.size() < 2) {
            throw std::domain_error("At least 2 abscissas are required.");
        }
        if (data_[0].size() != 4) {
            throw std::domain_error("There must be 4 data items per struct.");
        }

        for (auto & datum : data_)
        {
            datum[1] *= dx;
            datum[2] *= (dx*dx/2);
            datum[3] *= (dx*dx*dx/6);
        }
    }

    inline Real operator()(Real x) const
    {
        Real xf = x0_ + (data_.size()-1)/inv_dx_;
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
        Real s3 = (x-x0_)*inv_dx_;
        Real ii = floor(s3);
        auto i = static_cast<decltype(data_.size())>(ii);
        Real t = s3 - ii;
        if (t==0)
        {
            return data_[i][0];
        }
        Real t2 = t*t;
        Real t3 = t2*t;
        Real t4 = t3*t;

        Real s = t4*(-35 + t*(84 + t*(-70 + 20*t)));
        Real z4 = -s;
        Real z0 = s + 1;
        Real z1 = t*(1 + t3*(-20 + t*(45 + t*(-36+10*t))));
        Real z2 = t2*(1 + t2*(-10 + t*(20 + t*(-15+4*t))));
        Real z3 = t3*(1 + t*(-4+t*(6+t*(-4+t))));
        Real z5 = t4*(-15 + t*(39 + t*(-34 + 10*t)));
        Real z6 = t4*(5 + t*(-14 + t*(13-4*t)));
        Real z7 = t4*(-1 + t*(3+t*(-3+t)));

        Real y0 = data_[i][0];
        Real dy0 = data_[i][1];
        Real a0 = data_[i][2];
        Real j0 = data_[i][3];
        Real y1 = data_[i+1][0];
        Real dy1 = data_[i+1][1];
        Real a1 = data_[i+1][2];
        Real j1 = data_[i+1][3];

        return z0*y0 + z1*dy0 + z2*a0 + z3*j0 + z4*y1 + z5*dy1 + z6*a1 + z7*j1;
    }

    inline Real prime(Real x) const
    {
        Real xf = x0_ + (data_.size()-1)/inv_dx_;
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
        Real s3 = (x-x0_)*inv_dx_;
        Real ii = floor(s3);
        auto i = static_cast<decltype(data_.size())>(ii);
        Real t = s3 - ii;
        if (t == 0)
        {
            return data_[i][1]*inv_dx_;
        }

        Real y0 = data_[i][0];
        Real y1 = data_[i+1][0];
        Real dy0 = data_[i][1];
        Real dy1 = data_[i+1][1];
        Real a0 = data_[i][2];
        Real a1 = data_[i+1][2];
        Real j0 = data_[i][3];
        Real j1 = data_[i+1][3];
        Real t2 = t*t;
        Real t3 = t2*t;
        Real z0 = 140*t3*(1 + t*(-3 + t*(3 - t)));
        Real z1 = 1 + t3*(-80 + t*(225 + t*(-216 + 70*t)));
        Real z2 = t3*(-60 + t*(195 + t*(-204 + 70*t)));
        Real z3 = 1 + t2*(-20 + t*(50 + t*(-45 + 14*t)));
        Real z4 = t2*(10 + t*(-35 + t*(39 - 14*t)));
        Real z5 = 3 + t*(-16 + t*(30 + t*(-24 + 7*t)));
        Real z6 = t*(-4 + t*(15 + t*(-18 + 7*t)));

        Real dydx = z0*(y1-y0)*inv_dx_;
        dydx += (z1*dy0 + z2*dy1)*inv_dx_;
        dydx += 2*t*(z3*a0 + z4*a1)*inv_dx_;
        dydx += t*t*(z5*j0 + z6*j1);
        return dydx;
    }

    inline Real double_prime(Real x) const
    {
        Real xf = x0_ + (data_.size()-1)/inv_dx_;
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
        Real s3 = (x-x0_)*inv_dx_;
        Real ii = floor(s3);
        auto i = static_cast<decltype(data_.size())>(ii);
        Real t = s3 - ii;
        if (t == 0)
        {
            return data_[i][2]*2*inv_dx_*inv_dx_;
        }
        Real y0 = data_[i][0];
        Real y1 = data_[i+1][0];
        Real dy0 = data_[i][1];
        Real dy1 = data_[i+1][1];
        Real a0 = data_[i][2];
        Real a1 = data_[i+1][2];
        Real j0 = data_[i][3];
        Real j1 = data_[i+1][3];
        Real t2 = t*t;

        Real z0 = 420*t2*(1 + t*(-4 + t*(5 - 2*t)));
        Real z1 = 60*t2*(-4 + t*(15 + t*(-18 + 7*t)));
        Real z2 = 60*t2*(-3 + t*(13 + t*(-17 + 7*t)));
        Real z3 = (1 + t2*(-60 + t*(200 + t*(-225 + 84*t))));
        Real z4 = t2*(30 + t*(-140 + t*(195 - 84*t)));
        Real z5 = t*(1 + t*(-8 + t*(20 + t*(-20 + 7*t))));
        Real z6 = t2*(-2 + t*(10 + t*(-15 + 7*t)));

        Real d2ydx2 = z0*(y1-y0)*inv_dx_*inv_dx_;
        d2ydx2 += (z1*dy0 + z2*dy1)*inv_dx_*inv_dx_;
        d2ydx2 += (z3*a0 + z4*a1)*2*inv_dx_*inv_dx_;
        d2ydx2 += 6*(z5*j0 + z6*j1)/(inv_dx_*inv_dx_);

        return d2ydx2;
    }

    int64_t bytes() const
    {
        return data_.size()*data_[0].size()*sizeof(Real) + 2*sizeof(Real) + sizeof(data_);
    }

    std::pair<Real, Real> domain() const
    {
        return {x0_, x0_ + (data_.size() -1)/inv_dx_};
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

/* septic_hermite_detail.hpp
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
*/