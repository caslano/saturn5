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
5eOFR7yxoeNnxhya4OSfdewJ1y7Y88PkL5fubQ7sdf9hW4xv2nVDg4K/e+T3Wz9+aAx7mYBmyH4glbIuaBaMk3daJMo7LdY6ZSOCvw/4PSH36QzjoaOnZH3R01L+WVk/tAJ2hJ/I+qBP4f5wJUyCq2AfuBomwzUwDX4m+3N+Do+GX8g+nF9CN/wK5sGvYT78BhbDH2AZXAsr4I9wGlwHT4Y/ybs1foZnwF/lHRob4Dy4ES6EzSJM5c2wObwHtoBLYDR8EbaCH8IYSN2mNVxv/x8HxivJBH93UUbGqxFkDKz4Sthxbw+bw73gWntf+i7lXpFynWAkdPRwRGCcH4Fx8FHYDr4LO8L3oFPH+3B/+AFMgh/CPvAjmAw/hmlwBRwOP4FHw0/hGLgSuuEqmAdXw3y4BhbDL2EZ/ApWwK/hNPgNPBl+Cyvhd/AMuBaeC3+C8wxyBcY5At4MG8F7YCR8AraAy2G0jMvQiODvRDvGdlyc72cydJQi4zJQxiVVxmWcjMt4GZcJMi5uGZeJMi45Mi6TZFw8Mi65Mi5eGZc8GZd8GZcCGZdCGZdiGZcSGZdSGZcyGZcpMi4+GZcKGZdpMi6nw4Vwtnz/zoT3wTnwQXgufAyeD5+BF8KX4UXwI3gJ/BHOg00Ym8tgFLwSxsL5MAHWOb/AvMOqdtEmqn206Upy5iIyYDXnh7aMNlWto3d47qGM+9Q1/1DAfQvaRIfmIdbJXERurfmIKsrP5tp1/LyA6525iSTSIFI1+YvJu5drZI5ki/MWy7iu5twFiXK/kOL3ijZDSWV76VpFlUr131MkaUJ9+//yirJQAMCYnYoBbIs3zwrz5hniTReQWpOqZP39SWc7fwvMcoeMkbuwpNDvDlpLE4s3PyvFoPLp5TSDPOu91+FLnHN3JBpU5vXlefw+Ofe1nKuwNYZuhZ9JjYmBrnOcOl0mluNY528p24Yepgt5lLeep32wvCusaXKrWLnPXFsuAf/U1Hq4OLNZUcKgd8U32zbTl1BPyLNtpQ+hHpBn668ItTzg+e+0dfF3W2Lg+DE5fiUucLys1vGbcryU64OeLaoePdu/tRZjgfVOa5Y0X3fTvLK+p7/02vpXO+wzbfs9XnA/Bvv9k+/lUlNzP4YRdLMJzJR9FsbLvgg5sAecJN6nCA6AU8Tz+GEGrJD3Dp4iXuds8TZXyLsE5sOpTt3iba6S9wZWwznyvsAL5H2BVfBGuHyra0u2f03JI2mNd25dCan232obkhvX+Hut+6y615o8pX+fqVQqlUqlUqlUqCHm/+1kqycvvwc5De/93YkmOC9t5woD+ZuZjw9+c47jvZa68ytyfLlu2z53oYft9jgv/p3z2Tm+fK8/6N9jTbBck63MFycMirD3aMI9YOge4o1tedqVYnQ+czu895bmM/17O/nzsp7akLrvr2+/ftN9G/d84JGXtz6f2TX0Odrvg50HcsF4Y2X3KnQ4EL4BHa8bF1/T6+KD7XxGcvyOz2fUPZfx9/MYMocRmr+o5hgfvM3PWYyLV++rUqlUKpVKpVKpGmz+37pslgDUyzMA2xIDKAib/58oMQAQlI0B/GDn4iv/GgNwl5SWbT0OIGUjthYHqOxcZxyg5trtZdIo7mnlZF4Xh08Nb5u0yraw3O0tySv1eby5f1v3rjT3fp31+Ws2+psfsnJNt+Xzb+h/ztxvf93+eIT4f/n8jE1LTbj/r7EPYmgd7lq5PlauD1+HO0WuL4cx0A+D+zAQO9ipOfKdmR/fnpjAG8QENpC6dtDYgEqlUqlUKtWf7J0HeBRFFMeXSwjtEtKJgYSQxAQRNRFUUCQoqKiIUfkU63HkLiRyJvHuIqAoQVFjj4o=
*/