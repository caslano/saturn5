//  (C) Copyright Nick Thompson 2020.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_ENGEL_EXPANSION_HPP
#define BOOST_MATH_TOOLS_ENGEL_EXPANSION_HPP

#include <cmath>
#include <cstdint>
#include <vector>
#include <ostream>
#include <iomanip>
#include <limits>
#include <stdexcept>

namespace boost::math::tools {

template<typename Real, typename Z = int64_t>
class engel_expansion {
public:
    engel_expansion(Real x) : x_{x}
    {
        using std::floor;
        using std::abs;
        using std::sqrt;
        using std::isfinite;
        if (!isfinite(x))
        {
            throw std::domain_error("Cannot convert non-finites into an Engel expansion.");
        }

        if(x==0)
        {
            throw std::domain_error("Zero does not have an Engel expansion.");
        }
        a_.reserve(64);
        // Let the error bound grow by 1 ULP/iteration.
        // I haven't done the error analysis to show that this is an expected rate of error growth,
        // but if you don't do this, you can easily get into an infinite loop.
        Real i = 1;
        Real computed = 0;
        Real term = 1;
        Real scale = std::numeric_limits<Real>::epsilon()*abs(x_)/2;
        Real u = x;
        while (abs(x_ - computed) > (i++)*scale)
        {
            Real recip = 1/u;
            Real ak = ceil(recip);
            a_.push_back(static_cast<Z>(ak));
            u = u*ak - 1;
            if (u==0)
            {
                break;
            }
            term /= ak;
            computed += term;
        }

        for (size_t j = 1; j < a_.size(); ++j)
        {
            // Sanity check: This should only happen when wraparound occurs:
            if (a_[j] < a_[j-1])
            {
                throw std::domain_error("The digits of an Engel expansion must form a non-decreasing sequence; consider increasing the wide of the integer type.");
            }
            // Watch out for saturating behavior:
            if (a_[j] == (std::numeric_limits<Z>::max)())
            {
                throw std::domain_error("The integer type Z does not have enough width to hold the terms of the Engel expansion; please widen the type.");
            }
        }
        a_.shrink_to_fit();
    }
    
    
    const std::vector<Z>& digits() const
    {
        return a_;
    }

    template<typename T, typename Z2>
    friend std::ostream& operator<<(std::ostream& out, engel_expansion<T, Z2>& eng);

private:
    Real x_;
    std::vector<Z> a_;
};


template<typename Real, typename Z2>
std::ostream& operator<<(std::ostream& out, engel_expansion<Real, Z2>& engel)
{
    constexpr const int p = std::numeric_limits<Real>::max_digits10;
    if constexpr (p == 2147483647)
    {
        out << std::setprecision(engel.x_.backend().precision());
    }
    else
    {
        out << std::setprecision(p);
    }

    out << "{";
    for (size_t i = 0; i < engel.a_.size() - 1; ++i)
    {
        out << engel.a_[i] << ", ";
    }
    out << engel.a_.back();
    out << "}";
    return out;
}


}
#endif

/* engel_expansion.hpp
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
*/