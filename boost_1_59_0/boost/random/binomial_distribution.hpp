/* boost random/binomial_distribution.hpp header file
 *
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_BINOMIAL_DISTRIBUTION_HPP_INCLUDED
#define BOOST_RANDOM_BINOMIAL_DISTRIBUTION_HPP_INCLUDED

#include <boost/config/no_tr1/cmath.hpp>
#include <cstdlib>
#include <iosfwd>

#include <boost/random/detail/config.hpp>
#include <boost/random/uniform_01.hpp>

#include <boost/random/detail/disable_warnings.hpp>

namespace boost {
namespace random {

namespace detail {

template<class RealType>
struct binomial_table {
    static const RealType table[10];
};

template<class RealType>
const RealType binomial_table<RealType>::table[10] = {
    0.08106146679532726,
    0.04134069595540929,
    0.02767792568499834,
    0.02079067210376509,
    0.01664469118982119,
    0.01387612882307075,
    0.01189670994589177,
    0.01041126526197209,
    0.009255462182712733,
    0.008330563433362871
};

}

/**
 * The binomial distribution is an integer valued distribution with
 * two parameters, @c t and @c p.  The values of the distribution
 * are within the range [0,t].
 *
 * The distribution function is
 * \f$\displaystyle P(k) = {t \choose k}p^k(1-p)^{t-k}\f$.
 *
 * The algorithm used is the BTRD algorithm described in
 *
 *  @blockquote
 *  "The generation of binomial random variates", Wolfgang Hormann,
 *  Journal of Statistical Computation and Simulation, Volume 46,
 *  Issue 1 & 2 April 1993 , pages 101 - 110
 *  @endblockquote
 */
template<class IntType = int, class RealType = double>
class binomial_distribution {
public:
    typedef IntType result_type;
    typedef RealType input_type;

    class param_type {
    public:
        typedef binomial_distribution distribution_type;
        /**
         * Construct a param_type object.  @c t and @c p
         * are the parameters of the distribution.
         *
         * Requires: t >=0 && 0 <= p <= 1
         */
        explicit param_type(IntType t_arg = 1, RealType p_arg = RealType (0.5))
          : _t(t_arg), _p(p_arg)
        {}
        /** Returns the @c t parameter of the distribution. */
        IntType t() const { return _t; }
        /** Returns the @c p parameter of the distribution. */
        RealType p() const { return _p; }
#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
        /** Writes the parameters of the distribution to a @c std::ostream. */
        template<class CharT, class Traits>
        friend std::basic_ostream<CharT,Traits>&
        operator<<(std::basic_ostream<CharT,Traits>& os,
                   const param_type& parm)
        {
            os << parm._p << " " << parm._t;
            return os;
        }
    
        /** Reads the parameters of the distribution from a @c std::istream. */
        template<class CharT, class Traits>
        friend std::basic_istream<CharT,Traits>&
        operator>>(std::basic_istream<CharT,Traits>& is, param_type& parm)
        {
            is >> parm._p >> std::ws >> parm._t;
            return is;
        }
#endif
        /** Returns true if the parameters have the same values. */
        friend bool operator==(const param_type& lhs, const param_type& rhs)
        {
            return lhs._t == rhs._t && lhs._p == rhs._p;
        }
        /** Returns true if the parameters have different values. */
        friend bool operator!=(const param_type& lhs, const param_type& rhs)
        {
            return !(lhs == rhs);
        }
    private:
        IntType _t;
        RealType _p;
    };
    
    /**
     * Construct a @c binomial_distribution object. @c t and @c p
     * are the parameters of the distribution.
     *
     * Requires: t >=0 && 0 <= p <= 1
     */
    explicit binomial_distribution(IntType t_arg = 1,
                                   RealType p_arg = RealType(0.5))
      : _t(t_arg), _p(p_arg)
    {
        init();
    }
    
    /**
     * Construct an @c binomial_distribution object from the
     * parameters.
     */
    explicit binomial_distribution(const param_type& parm)
      : _t(parm.t()), _p(parm.p())
    {
        init();
    }
    
    /**
     * Returns a random variate distributed according to the
     * binomial distribution.
     */
    template<class URNG>
    IntType operator()(URNG& urng) const
    {
        if(use_inversion()) {
            if(0.5 < _p) {
                return _t - invert(_t, 1-_p, urng);
            } else {
                return invert(_t, _p, urng);
            }
        } else if(0.5 < _p) {
            return _t - generate(urng);
        } else {
            return generate(urng);
        }
    }
    
    /**
     * Returns a random variate distributed according to the
     * binomial distribution with parameters specified by @c param.
     */
    template<class URNG>
    IntType operator()(URNG& urng, const param_type& parm) const
    {
        return binomial_distribution(parm)(urng);
    }

    /** Returns the @c t parameter of the distribution. */
    IntType t() const { return _t; }
    /** Returns the @c p parameter of the distribution. */
    RealType p() const { return _p; }

    /** Returns the smallest value that the distribution can produce. */
    IntType min BOOST_PREVENT_MACRO_SUBSTITUTION() const { return 0; }
    /** Returns the largest value that the distribution can produce. */
    IntType max BOOST_PREVENT_MACRO_SUBSTITUTION() const { return _t; }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(_t, _p); }
    /** Sets parameters of the distribution. */
    void param(const param_type& parm)
    {
        _t = parm.t();
        _p = parm.p();
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
               const binomial_distribution& bd)
    {
        os << bd.param();
        return os;
    }
    
    /** Reads the parameters of the distribution from a @c std::istream. */
    template<class CharT, class Traits>
    friend std::basic_istream<CharT,Traits>&
    operator>>(std::basic_istream<CharT,Traits>& is, binomial_distribution& bd)
    {
        bd.read(is);
        return is;
    }
#endif

    /** Returns true if the two distributions will produce the same
        sequence of values, given equal generators. */
    friend bool operator==(const binomial_distribution& lhs,
                           const binomial_distribution& rhs)
    {
        return lhs._t == rhs._t && lhs._p == rhs._p;
    }
    /** Returns true if the two distributions could produce different
        sequences of values, given equal generators. */
    friend bool operator!=(const binomial_distribution& lhs,
                           const binomial_distribution& rhs)
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
        // BTRD is safe when np >= 10
        return m < 11;
    }

    // computes the correction factor for the Stirling approximation
    // for log(k!)
    static RealType fc(IntType k)
    {
        if(k < 10) return detail::binomial_table<RealType>::table[k];
        else {
            RealType ikp1 = RealType(1) / (k + 1);
            return (RealType(1)/12
                 - (RealType(1)/360
                 - (RealType(1)/1260)*(ikp1*ikp1))*(ikp1*ikp1))*ikp1;
        }
    }

    void init()
    {
        using std::sqrt;
        using std::pow;

        RealType p = (0.5 < _p)? (1 - _p) : _p;
        IntType t = _t;
        
        m = static_cast<IntType>((t+1)*p);

        if(use_inversion()) {
            _u.q_n = pow((1 - p), static_cast<RealType>(t));
        } else {
            _u.btrd.r = p/(1-p);
            _u.btrd.nr = (t+1)*_u.btrd.r;
            _u.btrd.npq = t*p*(1-p);
            RealType sqrt_npq = sqrt(_u.btrd.npq);
            _u.btrd.b = 1.15 + 2.53 * sqrt_npq;
            _u.btrd.a = -0.0873 + 0.0248*_u.btrd.b + 0.01*p;
            _u.btrd.c = t*p + 0.5;
            _u.btrd.alpha = (2.83 + 5.1/_u.btrd.b) * sqrt_npq;
            _u.btrd.v_r = 0.92 - 4.2/_u.btrd.b;
            _u.btrd.u_rv_r = 0.86*_u.btrd.v_r;
        }
    }

    template<class URNG>
    result_type generate(URNG& urng) const
    {
        using std::floor;
        using std::abs;
        using std::log;

        while(true) {
            RealType u;
            RealType v = uniform_01<RealType>()(urng);
            if(v <= _u.btrd.u_rv_r) {
                u = v/_u.btrd.v_r - 0.43;
                return static_cast<IntType>(floor(
                    (2*_u.btrd.a/(0.5 - abs(u)) + _u.btrd.b)*u + _u.btrd.c));
            }

            if(v >= _u.btrd.v_r) {
                u = uniform_01<RealType>()(urng) - 0.5;
            } else {
                u = v/_u.btrd.v_r - 0.93;
                u = ((u < 0)? -0.5 : 0.5) - u;
                v = uniform_01<RealType>()(urng) * _u.btrd.v_r;
            }

            RealType us = 0.5 - abs(u);
            IntType k = static_cast<IntType>(floor((2*_u.btrd.a/us + _u.btrd.b)*u + _u.btrd.c));
            if(k < 0 || k > _t) continue;
            v = v*_u.btrd.alpha/(_u.btrd.a/(us*us) + _u.btrd.b);
            RealType km = abs(k - m);
            if(km <= 15) {
                RealType f = 1;
                if(m < k) {
                    IntType i = m;
                    do {
                        ++i;
                        f = f*(_u.btrd.nr/i - _u.btrd.r);
                    } while(i != k);
                } else if(m > k) {
                    IntType i = k;
                    do {
                        ++i;
                        v = v*(_u.btrd.nr/i - _u.btrd.r);
                    } while(i != m);
                }
                if(v <= f) return k;
                else continue;
            } else {
                // final acceptance/rejection
                v = log(v);
                RealType rho =
                    (km/_u.btrd.npq)*(((km/3. + 0.625)*km + 1./6)/_u.btrd.npq + 0.5);
                RealType t = -km*km/(2*_u.btrd.npq);
                if(v < t - rho) return k;
                if(v > t + rho) continue;

                IntType nm = _t - m + 1;
                RealType h = (m + 0.5)*log((m + 1)/(_u.btrd.r*nm))
                           + fc(m) + fc(_t - m);

                IntType nk = _t - k + 1;
                if(v <= h + (_t+1)*log(static_cast<RealType>(nm)/nk)
                          + (k + 0.5)*log(nk*_u.btrd.r/(k+1))
                          - fc(k)
                          - fc(_t - k))
                {
                    return k;
                } else {
                    continue;
                }
            }
        }
    }

    template<class URNG>
    IntType invert(IntType t, RealType p, URNG& urng) const
    {
        RealType q = 1 - p;
        RealType s = p / q;
        RealType a = (t + 1) * s;
        RealType r = _u.q_n;
        RealType u = uniform_01<RealType>()(urng);
        IntType x = 0;
        while(u > r) {
            u = u - r;
            ++x;
            RealType r1 = ((a/x) - s) * r;
            // If r gets too small then the round-off error
            // becomes a problem.  At this point, p(i) is
            // decreasing exponentially, so if we just call
            // it 0, it's close enough.  Note that the
            // minimum value of q_n is about 1e-7, so we
            // may need to be a little careful to make sure that
            // we don't terminate the first time through the loop
            // for float.  (Hence the test that r is decreasing)
            if(r1 < std::numeric_limits<RealType>::epsilon() && r1 < r) {
                break;
            }
            r = r1;
        }
        return x;
    }

    // parameters
    IntType _t;
    RealType _p;

    // common data
    IntType m;

    union {
        // for btrd
        struct {
            RealType r;
            RealType nr;
            RealType npq;
            RealType b;
            RealType a;
            RealType c;
            RealType alpha;
            RealType v_r;
            RealType u_rv_r;
        } btrd;
        // for inversion
        RealType q_n;
    } _u;

    /// @endcond
};

}

// backwards compatibility
using random::binomial_distribution;

}

#include <boost/random/detail/enable_warnings.hpp>

#endif

/* binomial_distribution.hpp
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
*/