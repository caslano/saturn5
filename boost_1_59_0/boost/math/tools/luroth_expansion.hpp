//  (C) Copyright Nick Thompson 2020.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_LUROTH_EXPANSION_HPP
#define BOOST_MATH_TOOLS_LUROTH_EXPANSION_HPP

#include <vector>
#include <ostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace boost::math::tools {

template<typename Real, typename Z = int64_t>
class luroth_expansion {
public:
    luroth_expansion(Real x) : x_{x}
    {
        using std::floor;
        using std::abs;
        using std::sqrt;
        using std::isfinite;
        if (!isfinite(x))
        {
            throw std::domain_error("Cannot convert non-finites into a Luroth representation.");
        }
        d_.reserve(50);
        Real dn1 = floor(x);
        d_.push_back(static_cast<Z>(dn1));
        if (dn1 == x)
        {
           d_.shrink_to_fit();
           return;
        }
        // This attempts to follow the notation of:
        // "Khinchine's constant for Luroth Representation", by Sophia Kalpazidou.
        x = x - dn1;
        Real computed = dn1;
        Real prod = 1;
        // Let the error bound grow by 1 ULP/iteration.
        // I haven't done the error analysis to show that this is an expected rate of error growth,
        // but if you don't do this, you can easily get into an infinite loop.
        Real i = 1;
        Real scale = std::numeric_limits<Real>::epsilon()*abs(x_)/2;
        while (abs(x_ - computed) > (i++)*scale)
        {
           Real recip = 1/x;
           Real dn = floor(recip);
           // x = n + 1/k => lur(x) = ((n; k - 1))
           // Note that this is a bit different than Kalpazidou (examine the half-open interval of definition carefully).
           // One way to examine this definition is better for rationals (it never happens for irrationals)
           // is to consider i + 1/3. If you follow Kalpazidou, then you get ((i, 3, 0)); a zero digit!
           // That's bad since it destroys uniqueness and also breaks the computation of the geometric mean.
           if (recip == dn) {
              d_.push_back(static_cast<Z>(dn - 1));
              break;
           }
           d_.push_back(static_cast<Z>(dn));
           Real tmp = 1/(dn+1);
           computed += prod*tmp;
           prod *= tmp/dn;
           x = dn*(dn+1)*(x - tmp);
        }

        for (size_t i = 1; i < d_.size(); ++i)
        {
            // Sanity check:
            if (d_[i] <= 0)
            {
                throw std::domain_error("Found a digit <= 0; this is an error.");
            }
        }
        d_.shrink_to_fit();
    }
    
    
    const std::vector<Z>& digits() const {
      return d_;
    }

    // Under the assumption of 'randomness', this mean converges to 2.2001610580.
    // See Finch, Mathematical Constants, section 1.8.1.
    Real digit_geometric_mean() const {
        if (d_.size() == 1) {
            return std::numeric_limits<Real>::quiet_NaN();
        }
        using std::log;
        using std::exp;
        Real g = 0;
        for (size_t i = 1; i < d_.size(); ++i) {
            g += log(static_cast<Real>(d_[i]));
        }
        return exp(g/(d_.size() - 1));
    }
    
    template<typename T, typename Z2>
    friend std::ostream& operator<<(std::ostream& out, luroth_expansion<T, Z2>& scf);

private:
    const Real x_;
    std::vector<Z> d_;
};


template<typename Real, typename Z2>
std::ostream& operator<<(std::ostream& out, luroth_expansion<Real, Z2>& luroth)
{
   constexpr const int p = std::numeric_limits<Real>::max_digits10;
   if constexpr (p == 2147483647)
   {
      out << std::setprecision(luroth.x_.backend().precision());
   }
   else
   {
      out << std::setprecision(p);
   }

   out << "((" << luroth.d_.front();
   if (luroth.d_.size() > 1)
   {
      out << "; ";
      for (size_t i = 1; i < luroth.d_.size() -1; ++i)
      {
         out << luroth.d_[i] << ", ";
      }
      out << luroth.d_.back();
   }
   out << "))";
   return out;
}


}
#endif

/* luroth_expansion.hpp
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
*/