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
#include <cmath>

namespace boost::math::interpolators::detail {

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

    inline Real double_prime(Real x) const
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
#endif

/* septic_hermite_detail.hpp
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
*/