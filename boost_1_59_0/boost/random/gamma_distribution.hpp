/* boost random/gamma_distribution.hpp header file
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

#ifndef BOOST_RANDOM_GAMMA_DISTRIBUTION_HPP
#define BOOST_RANDOM_GAMMA_DISTRIBUTION_HPP

#include <boost/config/no_tr1/cmath.hpp>
#include <istream>
#include <iosfwd>
#include <boost/assert.hpp>
#include <boost/limits.hpp>
#include <boost/static_assert.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/exponential_distribution.hpp>

namespace boost {
namespace random {

// The algorithm is taken from Knuth

/**
 * The gamma distribution is a continuous distribution with two
 * parameters alpha and beta.  It produces values > 0.
 *
 * It has
 * \f$\displaystyle p(x) = x^{\alpha-1}\frac{e^{-x/\beta}}{\beta^\alpha\Gamma(\alpha)}\f$.
 */
template<class RealType = double>
class gamma_distribution
{
public:
    typedef RealType input_type;
    typedef RealType result_type;

    class param_type
    {
    public:
        typedef gamma_distribution distribution_type;

        /**
         * Constructs a @c param_type object from the "alpha" and "beta"
         * parameters.
         *
         * Requires: alpha > 0 && beta > 0
         */
        param_type(const RealType& alpha_arg = RealType(1.0),
                   const RealType& beta_arg = RealType(1.0))
          : _alpha(alpha_arg), _beta(beta_arg)
        {
        }

        /** Returns the "alpha" parameter of the distribution. */
        RealType alpha() const { return _alpha; }
        /** Returns the "beta" parameter of the distribution. */
        RealType beta() const { return _beta; }

#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
        /** Writes the parameters to a @c std::ostream. */
        template<class CharT, class Traits>
        friend std::basic_ostream<CharT, Traits>&
        operator<<(std::basic_ostream<CharT, Traits>& os,
                   const param_type& parm)
        {
            os << parm._alpha << ' ' << parm._beta;
            return os;
        }
        
        /** Reads the parameters from a @c std::istream. */
        template<class CharT, class Traits>
        friend std::basic_istream<CharT, Traits>&
        operator>>(std::basic_istream<CharT, Traits>& is, param_type& parm)
        {
            is >> parm._alpha >> std::ws >> parm._beta;
            return is;
        }
#endif

        /** Returns true if the two sets of parameters are the same. */
        friend bool operator==(const param_type& lhs, const param_type& rhs)
        {
            return lhs._alpha == rhs._alpha && lhs._beta == rhs._beta;
        }
        /** Returns true if the two sets fo parameters are different. */
        friend bool operator!=(const param_type& lhs, const param_type& rhs)
        {
            return !(lhs == rhs);
        }
    private:
        RealType _alpha;
        RealType _beta;
    };

#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
    BOOST_STATIC_ASSERT(!std::numeric_limits<RealType>::is_integer);
#endif

    /**
     * Creates a new gamma_distribution with parameters "alpha" and "beta".
     *
     * Requires: alpha > 0 && beta > 0
     */
    explicit gamma_distribution(const result_type& alpha_arg = result_type(1.0),
                                const result_type& beta_arg = result_type(1.0))
      : _exp(result_type(1)), _alpha(alpha_arg), _beta(beta_arg)
    {
        BOOST_ASSERT(_alpha > result_type(0));
        BOOST_ASSERT(_beta > result_type(0));
        init();
    }

    /** Constructs a @c gamma_distribution from its parameters. */
    explicit gamma_distribution(const param_type& parm)
      : _exp(result_type(1)), _alpha(parm.alpha()), _beta(parm.beta())
    {
        init();
    }

    // compiler-generated copy ctor and assignment operator are fine

    /** Returns the "alpha" paramter of the distribution. */
    RealType alpha() const { return _alpha; }
    /** Returns the "beta" parameter of the distribution. */
    RealType beta() const { return _beta; }
    /** Returns the smallest value that the distribution can produce. */
    RealType min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return 0; }
    /* Returns the largest value that the distribution can produce. */
    RealType max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return (std::numeric_limits<RealType>::infinity)(); }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(_alpha, _beta); }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        _alpha = parm.alpha();
        _beta = parm.beta();
        init();
    }
    
    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { _exp.reset(); }

    /**
     * Returns a random variate distributed according to
     * the gamma distribution.
     */
    template<class Engine>
    result_type operator()(Engine& eng)
    {
#ifndef BOOST_NO_STDC_NAMESPACE
        // allow for Koenig lookup
        using std::tan; using std::sqrt; using std::exp; using std::log;
        using std::pow;
#endif
        if(_alpha == result_type(1)) {
            return _exp(eng) * _beta;
        } else if(_alpha > result_type(1)) {
            // Can we have a boost::mathconst please?
            const result_type pi = result_type(3.14159265358979323846);
            for(;;) {
                result_type y = tan(pi * uniform_01<RealType>()(eng));
                result_type x = sqrt(result_type(2)*_alpha-result_type(1))*y
                    + _alpha-result_type(1);
                if(x <= result_type(0))
                    continue;
                if(uniform_01<RealType>()(eng) >
                    (result_type(1)+y*y) * exp((_alpha-result_type(1))
                                               *log(x/(_alpha-result_type(1)))
                                               - sqrt(result_type(2)*_alpha
                                                      -result_type(1))*y))
                    continue;
                return x * _beta;
            }
        } else /* alpha < 1.0 */ {
            for(;;) {
                result_type u = uniform_01<RealType>()(eng);
                result_type y = _exp(eng);
                result_type x, q;
                if(u < _p) {
                    x = exp(-y/_alpha);
                    q = _p*exp(-x);
                } else {
                    x = result_type(1)+y;
                    q = _p + (result_type(1)-_p) * pow(x,_alpha-result_type(1));
                }
                if(u >= q)
                    continue;
                return x * _beta;
            }
        }
    }

    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return gamma_distribution(parm)(urng);
    }

#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
    /** Writes a @c gamma_distribution to a @c std::ostream. */
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<<(std::basic_ostream<CharT,Traits>& os,
               const gamma_distribution& gd)
    {
        os << gd.param();
        return os;
    }
    
    /** Reads a @c gamma_distribution from a @c std::istream. */
    template<class CharT, class Traits>
    friend std::basic_istream<CharT,Traits>&
    operator>>(std::basic_istream<CharT,Traits>& is, gamma_distribution& gd)
    {
        gd.read(is);
        return is;
    }
#endif

    /**
     * Returns true if the two distributions will produce identical
     * sequences of random variates given equal generators.
     */
    friend bool operator==(const gamma_distribution& lhs,
                           const gamma_distribution& rhs)
    {
        return lhs._alpha == rhs._alpha
            && lhs._beta == rhs._beta
            && lhs._exp == rhs._exp;
    }

    /**
     * Returns true if the two distributions can produce different
     * sequences of random variates, given equal generators.
     */
    friend bool operator!=(const gamma_distribution& lhs,
                           const gamma_distribution& rhs)
    {
        return !(lhs == rhs);
    }

private:
    /// \cond hide_private_members

    template<class CharT, class Traits>
    void read(std::basic_istream<CharT, Traits>& is)
    {
        param_type parm;
        if(is >> parm) {
            param(parm);
        }
    }

    void init()
    {
#ifndef BOOST_NO_STDC_NAMESPACE
        // allow for Koenig lookup
        using std::exp;
#endif
        _p = exp(result_type(1)) / (_alpha + exp(result_type(1)));
    }
    /// \endcond

    exponential_distribution<RealType> _exp;
    result_type _alpha;
    result_type _beta;
    // some data precomputed from the parameters
    result_type _p;
};


} // namespace random

using random::gamma_distribution;

} // namespace boost

#endif // BOOST_RANDOM_GAMMA_DISTRIBUTION_HPP

/* gamma_distribution.hpp
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
*/