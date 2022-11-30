/* boost random/uniform_on_sphere.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_UNIFORM_ON_SPHERE_HPP
#define BOOST_RANDOM_UNIFORM_ON_SPHERE_HPP

#include <vector>
#include <algorithm>     // std::transform
#include <functional>    // std::bind2nd, std::divides
#include <boost/assert.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/normal_distribution.hpp>

namespace boost {
namespace random {

/**
 * Instantiations of class template uniform_on_sphere model a
 * \random_distribution. Such a distribution produces random
 * numbers uniformly distributed on the unit sphere of arbitrary
 * dimension @c dim. The @c Cont template parameter must be a STL-like
 * container type with begin and end operations returning non-const
 * ForwardIterators of type @c Cont::iterator. 
 */
template<class RealType = double, class Cont = std::vector<RealType> >
class uniform_on_sphere
{
public:
    typedef RealType input_type;
    typedef Cont result_type;

    class param_type
    {
    public:

        typedef uniform_on_sphere distribution_type;

        /**
         * Constructs the parameters of a uniform_on_sphere
         * distribution, given the dimension of the sphere.
         */
        explicit param_type(int dim_arg = 2) : _dim(dim_arg)
        {
            BOOST_ASSERT(_dim >= 0);
        }

        /** Returns the dimension of the sphere. */
        int dim() const { return _dim; }

        /** Writes the parameters to a @c std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._dim;
            return os;
        }

        /** Reads the parameters from a @c std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            is >> parm._dim;
            return is;
        }

        /** Returns true if the two sets of parameters are equal. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._dim == rhs._dim; }

        /** Returns true if the two sets of parameters are different. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)

    private:
        int _dim;
    };

    /**
     * Constructs a @c uniform_on_sphere distribution.
     * @c dim is the dimension of the sphere.
     *
     * Requires: dim >= 0
     */
    explicit uniform_on_sphere(int dim_arg = 2)
      : _container(dim_arg), _dim(dim_arg) { }

    /**
     * Constructs a @c uniform_on_sphere distribution from its parameters.
     */
    explicit uniform_on_sphere(const param_type& parm)
      : _container(parm.dim()), _dim(parm.dim()) { }

    // compiler-generated copy ctor and assignment operator are fine

    /** Returns the dimension of the sphere. */
    int dim() const { return _dim; }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(_dim); }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        _dim = parm.dim();
        _container.resize(_dim);
    }

    /**
     * Returns the smallest value that the distribution can produce.
     * Note that this is required to approximate the standard library's
     * requirements.  The behavior is defined according to lexicographical
     * comparison so that for a container type of std::vector,
     * dist.min() <= x <= dist.max() where x is any value produced
     * by the distribution.
     */
    result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    {
        result_type result(_dim);
        if(_dim != 0) {
            result.front() = RealType(-1.0);
        }
        return result;
    }
    /**
     * Returns the largest value that the distribution can produce.
     * Note that this is required to approximate the standard library's
     * requirements.  The behavior is defined according to lexicographical
     * comparison so that for a container type of std::vector,
     * dist.min() <= x <= dist.max() where x is any value produced
     * by the distribution.
     */
    result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    {
        result_type result(_dim);
        if(_dim != 0) {
            result.front() = RealType(1.0);
        }
        return result;
    }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() {}

    /**
     * Returns a point uniformly distributed over the surface of
     * a sphere of dimension dim().
     */
    template<class Engine>
    const result_type & operator()(Engine& eng)
    {
        using std::sqrt;
        switch(_dim)
        {
        case 0: break;
        case 1:
            {
                if(uniform_01<RealType>()(eng) < 0.5) {
                    *_container.begin() = -1;
                } else {
                    *_container.begin() = 1;
                }
                break;
            }
        case 2:
            {
                uniform_01<RealType> uniform;
                RealType sqsum;
                RealType x, y;
                do {
                    x = uniform(eng) * 2 - 1;
                    y = uniform(eng) * 2 - 1;
                    sqsum = x*x + y*y;
                } while(sqsum == 0 || sqsum > 1);
                RealType mult = 1/sqrt(sqsum);
                typename Cont::iterator iter = _container.begin();
                *iter = x * mult;
                iter++;
                *iter = y * mult;
                break;
            }
        case 3:
            {
                uniform_01<RealType> uniform;
                RealType sqsum;
                RealType x, y;
                do {
                    x = uniform(eng) * 2 - 1;
                    y = uniform(eng) * 2 - 1;
                    sqsum = x*x + y*y;
                } while(sqsum > 1);
                RealType mult = 2 * sqrt(1 - sqsum);
                typename Cont::iterator iter = _container.begin();
                *iter = x * mult;
                ++iter;
                *iter = y * mult;
                ++iter;
                *iter = 2 * sqsum - 1;
                break;
            }
        default:
            {
                detail::unit_normal_distribution<RealType> normal;
                RealType sqsum;
                do {
                    sqsum = 0;
                    for(typename Cont::iterator it = _container.begin();
                        it != _container.end();
                        ++it) {
                        RealType val = normal(eng);
                        *it = val;
                        sqsum += val * val;
                    }
                } while(sqsum == 0);
                // for all i: result[i] /= sqrt(sqsum)
                RealType inverse_distance = 1 / sqrt(sqsum);
                for(typename Cont::iterator it = _container.begin();
                    it != _container.end();
                    ++it) {
                    *it *= inverse_distance;
                }
            }
        }
        return _container;
    }

    /**
     * Returns a point uniformly distributed over the surface of
     * a sphere of dimension param.dim().
     */
    template<class Engine>
    result_type operator()(Engine& eng, const param_type& parm) const
    {
        return uniform_on_sphere(parm)(eng);
    }

    /** Writes the distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, uniform_on_sphere, sd)
    {
        os << sd._dim;
        return os;
    }

    /** Reads the distribution from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, uniform_on_sphere, sd)
    {
        is >> sd._dim;
        sd._container.resize(sd._dim);
        return is;
    }

    /**
     * Returns true if the two distributions will produce identical
     * sequences of values, given equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(uniform_on_sphere, lhs, rhs)
    { return lhs._dim == rhs._dim; }

    /**
     * Returns true if the two distributions may produce different
     * sequences of values, given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(uniform_on_sphere)

private:
    result_type _container;
    int _dim;
};

} // namespace random

using random::uniform_on_sphere;

} // namespace boost

#endif // BOOST_RANDOM_UNIFORM_ON_SPHERE_HPP

/* uniform_on_sphere.hpp
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
*/