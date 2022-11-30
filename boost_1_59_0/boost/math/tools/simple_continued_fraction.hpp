//  (C) Copyright Nick Thompson 2020.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_SIMPLE_CONTINUED_FRACTION_HPP
#define BOOST_MATH_TOOLS_SIMPLE_CONTINUED_FRACTION_HPP

#include <array>
#include <vector>
#include <ostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <boost/math/tools/is_standalone.hpp>

#ifndef BOOST_MATH_STANDALONE
#include <boost/core/demangle.hpp>
#endif

namespace boost::math::tools {

template<typename Real, typename Z = int64_t>
class simple_continued_fraction {
public:
    simple_continued_fraction(Real x) : x_{x} {
        using std::floor;
        using std::abs;
        using std::sqrt;
        using std::isfinite;
        if (!isfinite(x)) {
            throw std::domain_error("Cannot convert non-finites into continued fractions.");  
        }
        b_.reserve(50);
        Real bj = floor(x);
        b_.push_back(static_cast<Z>(bj));
        if (bj == x) {
           b_.shrink_to_fit();
           return;
        }
        x = 1/(x-bj);
        Real f = bj;
        if (bj == 0) {
           f = 16*(std::numeric_limits<Real>::min)();
        }
        Real C = f;
        Real D = 0;
        int i = 0;
        // the "1 + i++" lets the error bound grow slowly with the number of convergents.
        // I have not worked out the error propagation of the Modified Lentz's method to see if it does indeed grow at this rate.
        // Numerical Recipes claims that no one has worked out the error analysis of the modified Lentz's method.
        while (abs(f - x_) >= (1 + i++)*std::numeric_limits<Real>::epsilon()*abs(x_))
        {
          bj = floor(x);
          b_.push_back(static_cast<Z>(bj));
          x = 1/(x-bj);
          D += bj;
          if (D == 0) {
             D = 16*(std::numeric_limits<Real>::min)();
          }
          C = bj + 1/C;
          if (C==0) {
             C = 16*(std::numeric_limits<Real>::min)();
          }
          D = 1/D;
          f *= (C*D);
       }
       // Deal with non-uniqueness of continued fractions: [a0; a1, ..., an, 1] = a0; a1, ..., an + 1].
       // The shorter representation is considered the canonical representation,
       // so if we compute a non-canonical representation, change it to canonical:
       if (b_.size() > 2 && b_.back() == 1) {
          b_[b_.size() - 2] += 1;
          b_.resize(b_.size() - 1);
       }
       b_.shrink_to_fit();
       
       for (size_t i = 1; i < b_.size(); ++i) {
         if (b_[i] <= 0) {
            std::ostringstream oss;
            oss << "Found a negative partial denominator: b[" << i << "] = " << b_[i] << "."
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
        if (b_.size() == 1) { 
         return std::numeric_limits<Real>::quiet_NaN();
        }
         using std::log;
         using std::exp;
         // Precompute the most probable logarithms. See the Gauss-Kuzmin distribution for details.
         // Example: b_i = 1 has probability -log_2(3/4) ~ .415:
         // A random partial denominator has ~80% chance of being in this table:
         const std::array<Real, 7> logs{std::numeric_limits<Real>::quiet_NaN(), Real(0), log(static_cast<Real>(2)), log(static_cast<Real>(3)), log(static_cast<Real>(4)), log(static_cast<Real>(5)), log(static_cast<Real>(6))};
         Real log_prod = 0;
         for (size_t i = 1; i < b_.size(); ++i) {
            if (b_[i] < static_cast<Z>(logs.size())) {
               log_prod += logs[b_[i]];
            }
            else
            {
               log_prod += log(static_cast<Real>(b_[i]));
            }
         }
         log_prod /= (b_.size()-1);
         return exp(log_prod);
    }
    
    Real khinchin_harmonic_mean() const {
        if (b_.size() == 1) {
          return std::numeric_limits<Real>::quiet_NaN();
        }
        Real n = b_.size() - 1;
        Real denom = 0;
        for (size_t i = 1; i < b_.size(); ++i) {
            denom += 1/static_cast<Real>(b_[i]);
        }
        return n/denom;
    }
    
    const std::vector<Z>& partial_denominators() const {
      return b_;
    }
    
    template<typename T, typename Z2>
    friend std::ostream& operator<<(std::ostream& out, simple_continued_fraction<T, Z2>& scf);

private:
    const Real x_;
    std::vector<Z> b_;
};


template<typename Real, typename Z2>
std::ostream& operator<<(std::ostream& out, simple_continued_fraction<Real, Z2>& scf) {
   constexpr const int p = std::numeric_limits<Real>::max_digits10;
   if constexpr (p == 2147483647) {
      out << std::setprecision(scf.x_.backend().precision());
   } else {
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

/* simple_continued_fraction.hpp
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
*/