// Copyright Nick Thompson, 2021
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_BILINEAR_UNIFORM_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_BILINEAR_UNIFORM_DETAIL_HPP

#include <stdexcept>
#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <utility>

namespace boost::math::interpolators::detail {

template <class RandomAccessContainer>
class bilinear_uniform_imp
{
public:
    using Real = typename RandomAccessContainer::value_type;
    using Z = typename RandomAccessContainer::size_type;

    bilinear_uniform_imp(RandomAccessContainer && fieldData, Z rows, Z cols, Real dx = 1, Real dy = 1, Real x0 = 0, Real y0 = 0)
    {
        using std::to_string;
        if(fieldData.size() != rows*cols)
        {
            std::string err = std::string(__FILE__) + ":" + to_string(__LINE__)
               + " The field data must have rows*cols elements. There are " + to_string(rows)  + " rows and " + to_string(cols) + " columns but " + to_string(fieldData.size()) + " elements in the field data.";
            throw std::logic_error(err);
        }
        if (rows < 2) {
            throw std::logic_error("There must be at least two rows of data for bilinear interpolation to be well-defined.");
        }
        if (cols < 2) {
            throw std::logic_error("There must be at least two columns of data for bilinear interpolation to be well-defined.");
        }

        fieldData_ = std::move(fieldData);
        rows_ = rows;
        cols_ = cols;
        x0_ = x0;
        y0_ = y0;
        dx_ = dx;
        dy_ = dy;

        if (dx_ <= 0) {
            std::string err = std::string(__FILE__) + ":" + to_string(__LINE__) + " dx = " + to_string(dx) + ", but dx > 0 is required. Are the arguments out of order?";
            throw std::logic_error(err);
        }
        if (dy_ <= 0) {
            std::string err = std::string(__FILE__) + ":" + to_string(__LINE__) + " dy = " + to_string(dy) + ", but dy > 0 is required. Are the arguments out of order?";
            throw std::logic_error(err);
        }
    }

    Real operator()(Real x, Real y) const
    {
        using std::floor;
        if (x > x0_ + (cols_ - 1)*dx_ || x < x0_) {
            std::cerr << __FILE__ << ":" << __LINE__ << ":" << __func__ << "\n";
            std::cerr << "Querying the bilinear_uniform interpolator at (x,y) = (" << x << ", " << y << ") is not allowed.\n";
            std::cerr << "x must lie in the interval [" << x0_ << ", " << x0_ + (cols_ -1)*dx_ << "]\n";
            return std::numeric_limits<Real>::quiet_NaN();
        }
        if (y > y0_ + (rows_ - 1)*dy_ || y < y0_) {
            std::cerr << __FILE__ << ":" << __LINE__ << ":" << __func__ << "\n";
            std::cerr << "Querying the bilinear_uniform interpolator at (x,y) = (" << x << ", " << y << ") is not allowed.\n";
            std::cerr << "y must lie in the interval [" << y0_ << ", " << y0_ + (rows_ -1)*dy_ << "]\n";
            return std::numeric_limits<Real>::quiet_NaN(); 
        }

        Real s = (x - x0_)/dx_;
        Real s0 = floor(s);
        Real t = (y - y0_)/dy_;
        Real t0 = floor(t);
        Z xidx = s0;
        Z yidx = t0;
        Z idx = yidx*cols_  + xidx;
        Real alpha = s - s0;
        Real beta = t - t0;

        Real fhi;
        // If alpha = 0, then we can segfault by reading fieldData_[idx+1]:
        if (alpha <= 2*s0*std::numeric_limits<Real>::epsilon())  {
            fhi = fieldData_[idx];
        } else {
            fhi = (1 - alpha)*fieldData_[idx] + alpha*fieldData_[idx + 1];
        }

        // Again, we can get OOB access without this check.
        // This corresponds to interpolation over a line segment aligned with the axes.
        if (beta <= 2*t0*std::numeric_limits<Real>::epsilon()) {
            return fhi;
        }

        auto bottom_left = fieldData_[idx + cols_];
        Real flo;
        if (alpha <= 2*s0*std::numeric_limits<Real>::epsilon()) {
            flo = bottom_left;
        }
        else {
            flo = (1 - alpha)*bottom_left + alpha*fieldData_[idx + cols_ + 1];
        }
        // Convex combination over vertical to get the value:
        return (1 - beta)*fhi + beta*flo;
    }

    friend std::ostream& operator<<(std::ostream& out, bilinear_uniform_imp<RandomAccessContainer> const & bu) {
        out << "(x0, y0) = (" << bu.x0_ << ", " << bu.y0_ << "), (dx, dy) = (" << bu.dx_ << ", " << bu.dy_ << "), ";
        out << "(xf, yf) = (" << bu.x0_ + (bu.cols_ - 1)*bu.dx_ << ", " << bu.y0_ + (bu.rows_ - 1)*bu.dy_ << ")\n";
        for (Z j = 0; j < bu.rows_; ++j) {
            out << "{";
            for (Z i = 0; i < bu.cols_ - 1; ++i) {
                out << bu.fieldData_[j*bu.cols_ + i] << ", ";
            }
            out << bu.fieldData_[j*bu.cols_ + bu.cols_ - 1] << "}\n";
        }
        return out;
    }

private:
    RandomAccessContainer fieldData_;
    Z rows_;
    Z cols_;
    Real x0_;
    Real y0_;
    Real dx_;
    Real dy_;
};


}
#endif

/* bilinear_uniform_detail.hpp
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
*/