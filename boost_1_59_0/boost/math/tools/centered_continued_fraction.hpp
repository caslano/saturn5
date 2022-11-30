//  (C) Copyright Nick Thompson 2020.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_CENTERED_CONTINUED_FRACTION_HPP
#define BOOST_MATH_TOOLS_CENTERED_CONTINUED_FRACTION_HPP

#include <cmath>
#include <cstdint>
#include <vector>
#include <ostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <array>
#include <type_traits>
#include <boost/math/tools/is_standalone.hpp>

#ifndef BOOST_MATH_STANDALONE
#include <boost/core/demangle.hpp>
#endif

namespace boost::math::tools {

template<typename Real, typename Z = int64_t>
class centered_continued_fraction {
public:
    centered_continued_fraction(Real x) : x_{x} {
        static_assert(std::is_integral_v<Z> && std::is_signed_v<Z>,
                      "Centered continued fractions require signed integer types.");
        using std::round;
        using std::abs;
        using std::sqrt;
        using std::isfinite;
        if (!isfinite(x))
        {
            throw std::domain_error("Cannot convert non-finites into continued fractions.");  
        }
        b_.reserve(50);
        Real bj = round(x);
        b_.push_back(static_cast<Z>(bj));
        if (bj == x)
        {
            b_.shrink_to_fit();
            return;
        }
        x = 1/(x-bj);
        Real f = bj;
        if (bj == 0)
        {
            f = 16*(std::numeric_limits<Real>::min)();
        }
        Real C = f;
        Real D = 0;
        int i = 0;
        while (abs(f - x_) >= (1 + i++)*std::numeric_limits<Real>::epsilon()*abs(x_))
        {
            bj = round(x);
            b_.push_back(static_cast<Z>(bj));
            x = 1/(x-bj);
            D += bj;
            if (D == 0) {
                D = 16*(std::numeric_limits<Real>::min)();
            }
            C = bj + 1/C;
            if (C==0)
            {
                C = 16*(std::numeric_limits<Real>::min)();
            }
            D = 1/D;
            f *= (C*D);
        }
        // Deal with non-uniqueness of continued fractions: [a0; a1, ..., an, 1] = a0; a1, ..., an + 1].
        if (b_.size() > 2 && b_.back() == 1)
        {
            b_[b_.size() - 2] += 1;
            b_.resize(b_.size() - 1);
        }
        b_.shrink_to_fit();

        for (size_t i = 1; i < b_.size(); ++i)
        {
            if (b_[i] == 0) {
                std::ostringstream oss;
                oss << "Found a zero partial denominator: b[" << i << "] = " << b_[i] << "."
                    #ifndef BOOST_MATH_STANDALONE
                    << " This means the integer type '" << boost::core::demangle(typeid(Z).name())
                    #else
                    << " This means the integer type '" << typeid(Z).name()
                    #endif
                    << "' has overflowed and you need to use a wider type,"
                    << " or there is a bug.";
                throw std::overflow_error(oss.str());
            }
        }
    }

    Real khinchin_geometric_mean() const {
        if (b_.size() == 1)
        { 
            return std::numeric_limits<Real>::quiet_NaN();
        }
        using std::log;
        using std::exp;
        using std::abs;
        const std::array<Real, 7> logs{std::numeric_limits<Real>::quiet_NaN(), Real(0), log(static_cast<Real>(2)), log(static_cast<Real>(3)), log(static_cast<Real>(4)), log(static_cast<Real>(5)), log(static_cast<Real>(6))};
        Real log_prod = 0;
        for (size_t i = 1; i < b_.size(); ++i)
        {
            if (abs(b_[i]) < static_cast<Z>(logs.size()))
            {
                log_prod += logs[abs(b_[i])];
            }
            else
            {
                log_prod += log(static_cast<Real>(abs(b_[i])));
            }
        }
        log_prod /= (b_.size()-1);
        return exp(log_prod);
    }

    const std::vector<Z>& partial_denominators() const {
        return b_;
    }
    
    template<typename T, typename Z2>
    friend std::ostream& operator<<(std::ostream& out, centered_continued_fraction<T, Z2>& ccf);

private:
    const Real x_;
    std::vector<Z> b_;
};


template<typename Real, typename Z2>
std::ostream& operator<<(std::ostream& out, centered_continued_fraction<Real, Z2>& scf) {
    constexpr const int p = std::numeric_limits<Real>::max_digits10;
    if constexpr (p == 2147483647)
    {
        out << std::setprecision(scf.x_.backend().precision());
    }
    else
    {
        out << std::setprecision(p);
    }
   
    out << "[" << scf.b_.front();
    if (scf.b_.size() > 1)
    {
        out << "; ";
        for (size_t i = 1; i < scf.b_.size() -1; ++i)
        {
            out << scf.b_[i] << ", ";
        }
        out << scf.b_.back();
    }
    out << "]";
    return out;
}


}
#endif

/* centered_continued_fraction.hpp
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
*/