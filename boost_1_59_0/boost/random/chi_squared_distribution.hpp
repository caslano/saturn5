/* boost random/chi_squared_distribution.hpp header file
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_CHI_SQUARED_DISTRIBUTION_HPP_INCLUDED
#define BOOST_RANDOM_CHI_SQUARED_DISTRIBUTION_HPP_INCLUDED

#include <iosfwd>
#include <boost/limits.hpp>

#include <boost/random/detail/config.hpp>
#include <boost/random/gamma_distribution.hpp>

namespace boost {
namespace random {

/**
 * The chi squared distribution is a real valued distribution with
 * one parameter, @c n.  The distribution produces values > 0.
 *
 * The distribution function is
 * \f$\displaystyle P(x) = \frac{x^{(n/2)-1}e^{-x/2}}{\Gamma(n/2)2^{n/2}}\f$.
 */
template<class RealType = double>
class chi_squared_distribution {
public:
    typedef RealType result_type;
    typedef RealType input_type;

    class param_type {
    public:
        typedef chi_squared_distribution distribution_type;
        /**
         * Construct a param_type object.  @c n
         * is the parameter of the distribution.
         *
         * Requires: t >=0 && 0 <= p <= 1
         */
        explicit param_type(RealType n_arg = RealType(1))
          : _n(n_arg)
        {}
        /** Returns the @c n parameter of the distribution. */
        RealType n() const { return _n; }
#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
        /** Writes the parameters of the distribution to a @c std::ostream. */
        template<class CharT, class Traits>
        friend std::basic_ostream<CharT,Traits>&
        operator<<(std::basic_ostream<CharT,Traits>& os,
                   const param_type& parm)
        {
            os << parm._n;
            return os;
        }
    
        /** Reads the parameters of the distribution from a @c std::istream. */
        template<class CharT, class Traits>
        friend std::basic_istream<CharT,Traits>&
        operator>>(std::basic_istream<CharT,Traits>& is, param_type& parm)
        {
            is >> parm._n;
            return is;
        }
#endif
        /** Returns true if the parameters have the same values. */
        friend bool operator==(const param_type& lhs, const param_type& rhs)
        {
            return lhs._n == rhs._n;
        }
        /** Returns true if the parameters have different values. */
        friend bool operator!=(const param_type& lhs, const param_type& rhs)
        {
            return !(lhs == rhs);
        }
    private:
        RealType _n;
    };
    
    /**
     * Construct a @c chi_squared_distribution object. @c n
     * is the parameter of the distribution.
     *
     * Requires: t >=0 && 0 <= p <= 1
     */
    explicit chi_squared_distribution(RealType n_arg = RealType(1))
      : _impl(static_cast<RealType>(n_arg / 2))
    {
    }
    
    /**
     * Construct an @c chi_squared_distribution object from the
     * parameters.
     */
    explicit chi_squared_distribution(const param_type& parm)
      : _impl(static_cast<RealType>(parm.n() / 2))
    {
    }
    
    /**
     * Returns a random variate distributed according to the
     * chi squared distribution.
     */
    template<class URNG>
    RealType operator()(URNG& urng)
    {
        return 2 * _impl(urng);
    }
    
    /**
     * Returns a random variate distributed according to the
     * chi squared distribution with parameters specified by @c param.
     */
    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return chi_squared_distribution(parm)(urng);
    }

    /** Returns the @c n parameter of the distribution. */
    RealType n() const { return 2 * _impl.alpha(); }

    /** Returns the smallest value that the distribution can produce. */
    RealType min BOOST_PREVENT_MACRO_SUBSTITUTION() const { return 0; }
    /** Returns the largest value that the distribution can produce. */
    RealType max BOOST_PREVENT_MACRO_SUBSTITUTION() const
    { return (std::numeric_limits<RealType>::infinity)(); }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(n()); }
    /** Sets parameters of the distribution. */
    void param(const param_type& parm)
    {
        typedef gamma_distribution<RealType> impl_type;
        typename impl_type::param_type impl_parm(static_cast<RealType>(parm.n() / 2));
        _impl.param(impl_parm);
    }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { _impl.reset(); }

#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
    /** Writes the parameters of the distribution to a @c std::ostream. */
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<<(std::basic_ostream<CharT,Traits>& os,
               const chi_squared_distribution& c2d)
    {
        os << c2d.param();
        return os;
    }
    
    /** Reads the parameters of the distribution from a @c std::istream. */
    template<class CharT, class Traits>
    friend std::basic_istream<CharT,Traits>&
    operator>>(std::basic_istream<CharT,Traits>& is,
               chi_squared_distribution& c2d)
    {
        c2d.read(is);
        return is;
    }
#endif

    /** Returns true if the two distributions will produce the same
        sequence of values, given equal generators. */
    friend bool operator==(const chi_squared_distribution& lhs,
                           const chi_squared_distribution& rhs)
    {
        return lhs._impl == rhs._impl;
    }
    /** Returns true if the two distributions could produce different
        sequences of values, given equal generators. */
    friend bool operator!=(const chi_squared_distribution& lhs,
                           const chi_squared_distribution& rhs)
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

    gamma_distribution<RealType> _impl;

    /// @endcond
};

}

}

#endif

/* chi_squared_distribution.hpp
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
*/