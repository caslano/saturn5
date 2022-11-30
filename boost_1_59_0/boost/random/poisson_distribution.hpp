/* boost random/poisson_distribution.hpp header file
 *
 * Copyright Jens Maurer 2002
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 */

#ifndef BOOST_RANDOM_POISSON_DISTRIBUTION_HPP
#define BOOST_RANDOM_POISSON_DISTRIBUTION_HPP

#include <boost/config/no_tr1/cmath.hpp>
#include <cstdlib>
#include <iosfwd>
#include <boost/assert.hpp>
#include <boost/limits.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/detail/config.hpp>

#include <boost/random/detail/disable_warnings.hpp>

namespace boost {
namespace random {

namespace detail {

template<class RealType>
struct poisson_table {
    static RealType value[10];
};

template<class RealType>
RealType poisson_table<RealType>::value[10] = {
    0.0,
    0.0,
    0.69314718055994529,
    1.7917594692280550,
    3.1780538303479458,
    4.7874917427820458,
    6.5792512120101012,
    8.5251613610654147,
    10.604602902745251,
    12.801827480081469
};

}

/**
 * An instantiation of the class template @c poisson_distribution is a
 * model of \random_distribution.  The poisson distribution has
 * \f$p(i) = \frac{e^{-\lambda}\lambda^i}{i!}\f$
 *
 * This implementation is based on the PTRD algorithm described
 * 
 *  @blockquote
 *  "The transformed rejection method for generating Poisson random variables",
 *  Wolfgang Hormann, Insurance: Mathematics and Economics
 *  Volume 12, Issue 1, February 1993, Pages 39-45
 *  @endblockquote
 */
template<class IntType = int, class RealType = double>
class poisson_distribution {
public:
    typedef IntType result_type;
    typedef RealType input_type;

    class param_type {
    public:
        typedef poisson_distribution distribution_type;
        /**
         * Construct a param_type object with the parameter "mean"
         *
         * Requires: mean > 0
         */
        explicit param_type(RealType mean_arg = RealType(1))
          : _mean(mean_arg)
        {
            BOOST_ASSERT(_mean > 0);
        }
        /* Returns the "mean" parameter of the distribution. */
        RealType mean() const { return _mean; }
#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
        /** Writes the parameters of the distribution to a @c std::ostream. */
        template<class CharT, class Traits>
        friend std::basic_ostream<CharT, Traits>&
        operator<<(std::basic_ostream<CharT, Traits>& os,
                   const param_type& parm)
        {
            os << parm._mean;
            return os;
        }

        /** Reads the parameters of the distribution from a @c std::istream. */
        template<class CharT, class Traits>
        friend std::basic_istream<CharT, Traits>&
        operator>>(std::basic_istream<CharT, Traits>& is, param_type& parm)
        {
            is >> parm._mean;
            return is;
        }
#endif
        /** Returns true if the parameters have the same values. */
        friend bool operator==(const param_type& lhs, const param_type& rhs)
        {
            return lhs._mean == rhs._mean;
        }
        /** Returns true if the parameters have different values. */
        friend bool operator!=(const param_type& lhs, const param_type& rhs)
        {
            return !(lhs == rhs);
        }
    private:
        RealType _mean;
    };
    
    /**
     * Constructs a @c poisson_distribution with the parameter @c mean.
     *
     * Requires: mean > 0
     */
    explicit poisson_distribution(RealType mean_arg = RealType(1))
      : _mean(mean_arg)
    {
        BOOST_ASSERT(_mean > 0);
        init();
    }
    
    /**
     * Construct an @c poisson_distribution object from the
     * parameters.
     */
    explicit poisson_distribution(const param_type& parm)
      : _mean(parm.mean())
    {
        init();
    }
    
    /**
     * Returns a random variate distributed according to the
     * poisson distribution.
     */
    template<class URNG>
    IntType operator()(URNG& urng) const
    {
        if(use_inversion()) {
            return invert(urng);
        } else {
            return generate(urng);
        }
    }

    /**
     * Returns a random variate distributed according to the
     * poisson distribution with parameters specified by param.
     */
    template<class URNG>
    IntType operator()(URNG& urng, const param_type& parm) const
    {
        return poisson_distribution(parm)(urng);
    }

    /** Returns the "mean" parameter of the distribution. */
    RealType mean() const { return _mean; }
    
    /** Returns the smallest value that the distribution can produce. */
    IntType min BOOST_PREVENT_MACRO_SUBSTITUTION() const { return 0; }
    /** Returns the largest value that the distribution can produce. */
    IntType max BOOST_PREVENT_MACRO_SUBSTITUTION() const
    { return (std::numeric_limits<IntType>::max)(); }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(_mean); }
    /** Sets parameters of the distribution. */
    void param(const param_type& parm)
    {
        _mean = parm.mean();
        init();
    }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { }

#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
    /** Writes the parameters of the distribution to a @c std::ostream. */
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<<(std::basic_ostream<CharT,Traits>& os,
               const poisson_distribution& pd)
    {
        os << pd.param();
        return os;
    }
    
    /** Reads the parameters of the distribution from a @c std::istream. */
    template<class CharT, class Traits>
    friend std::basic_istream<CharT,Traits>&
    operator>>(std::basic_istream<CharT,Traits>& is, poisson_distribution& pd)
    {
        pd.read(is);
        return is;
    }
#endif
    
    /** Returns true if the two distributions will produce the same
        sequence of values, given equal generators. */
    friend bool operator==(const poisson_distribution& lhs,
                           const poisson_distribution& rhs)
    {
        return lhs._mean == rhs._mean;
    }
    /** Returns true if the two distributions could produce different
        sequences of values, given equal generators. */
    friend bool operator!=(const poisson_distribution& lhs,
                           const poisson_distribution& rhs)
    {
        return !(lhs == rhs);
    }

private:

    /// @cond show_private

    template<class CharT, class Traits>
    void read(std::basic_istream<CharT, Traits>& is) {
        param_type parm;
        if(is >> parm) {
            param(parm);
        }
    }

    bool use_inversion() const
    {
        return _mean < 10;
    }

    static RealType log_factorial(IntType k)
    {
        BOOST_ASSERT(k >= 0);
        BOOST_ASSERT(k < 10);
        return detail::poisson_table<RealType>::value[k];
    }

    void init()
    {
        using std::sqrt;
        using std::exp;

        if(use_inversion()) {
            _u._exp_mean = exp(-_mean);
        } else {
            _u._ptrd.smu = sqrt(_mean);
            _u._ptrd.b = 0.931 + 2.53 * _u._ptrd.smu;
            _u._ptrd.a = -0.059 + 0.02483 * _u._ptrd.b;
            _u._ptrd.inv_alpha = 1.1239 + 1.1328 / (_u._ptrd.b - 3.4);
            _u._ptrd.v_r = 0.9277 - 3.6224 / (_u._ptrd.b - 2);
        }
    }
    
    template<class URNG>
    IntType generate(URNG& urng) const
    {
        using std::floor;
        using std::abs;
        using std::log;

        while(true) {
            RealType u;
            RealType v = uniform_01<RealType>()(urng);
            if(v <= 0.86 * _u._ptrd.v_r) {
                u = v / _u._ptrd.v_r - 0.43;
                return static_cast<IntType>(floor(
                    (2*_u._ptrd.a/(0.5-abs(u)) + _u._ptrd.b)*u + _mean + 0.445));
            }

            if(v >= _u._ptrd.v_r) {
                u = uniform_01<RealType>()(urng) - 0.5;
            } else {
                u = v/_u._ptrd.v_r - 0.93;
                u = ((u < 0)? -0.5 : 0.5) - u;
                v = uniform_01<RealType>()(urng) * _u._ptrd.v_r;
            }

            RealType us = 0.5 - abs(u);
            if(us < 0.013 && v > us) {
                continue;
            }

            RealType k = floor((2*_u._ptrd.a/us + _u._ptrd.b)*u+_mean+0.445);
            v = v*_u._ptrd.inv_alpha/(_u._ptrd.a/(us*us) + _u._ptrd.b);

            RealType log_sqrt_2pi = 0.91893853320467267;

            if(k >= 10) {
                if(log(v*_u._ptrd.smu) <= (k + 0.5)*log(_mean/k)
                               - _mean
                               - log_sqrt_2pi
                               + k
                               - (1/12. - (1/360. - 1/(1260.*k*k))/(k*k))/k) {
                    return static_cast<IntType>(k);
                }
            } else if(k >= 0) {
                if(log(v) <= k*log(_mean)
                           - _mean
                           - log_factorial(static_cast<IntType>(k))) {
                    return static_cast<IntType>(k);
                }
            }
        }
    }

    template<class URNG>
    IntType invert(URNG& urng) const
    {
        RealType p = _u._exp_mean;
        IntType x = 0;
        RealType u = uniform_01<RealType>()(urng);
        while(u > p) {
            u = u - p;
            ++x;
            p = _mean * p / x;
        }
        return x;
    }

    RealType _mean;

    union {
        // for ptrd
        struct {
            RealType v_r;
            RealType a;
            RealType b;
            RealType smu;
            RealType inv_alpha;
        } _ptrd;
        // for inversion
        RealType _exp_mean;
    } _u;

    /// @endcond
};

} // namespace random

using random::poisson_distribution;

} // namespace boost

#include <boost/random/detail/enable_warnings.hpp>

#endif // BOOST_RANDOM_POISSON_DISTRIBUTION_HPP

/* poisson_distribution.hpp
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
*/