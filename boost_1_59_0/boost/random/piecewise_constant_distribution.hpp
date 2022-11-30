/* boost random/piecewise_constant_distribution.hpp header file
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

#ifndef BOOST_RANDOM_PIECEWISE_CONSTANT_DISTRIBUTION_HPP_INCLUDED
#define BOOST_RANDOM_PIECEWISE_CONSTANT_DISTRIBUTION_HPP_INCLUDED

#include <vector>
#include <numeric>
#include <boost/assert.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/discrete_distribution.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/detail/vector_io.hpp>

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost {
namespace random {

/**
 * The class @c piecewise_constant_distribution models a \random_distribution.
 */
template<class RealType = double, class WeightType = double>
class piecewise_constant_distribution {
public:
    typedef std::size_t input_type;
    typedef RealType result_type;

    class param_type {
    public:

        typedef piecewise_constant_distribution distribution_type;

        /**
         * Constructs a @c param_type object, representing a distribution
         * that produces values uniformly distributed in the range [0, 1).
         */
        param_type()
        {
            _weights.push_back(WeightType(1));
            _intervals.push_back(RealType(0));
            _intervals.push_back(RealType(1));
        }
        /**
         * Constructs a @c param_type object from two iterator ranges
         * containing the interval boundaries and the interval weights.
         * If there are less than two boundaries, then this is equivalent to
         * the default constructor and creates a single interval, [0, 1).
         *
         * The values of the interval boundaries must be strictly
         * increasing, and the number of weights must be one less than
         * the number of interval boundaries.  If there are extra
         * weights, they are ignored.
         */
        template<class IntervalIter, class WeightIter>
        param_type(IntervalIter intervals_first, IntervalIter intervals_last,
                   WeightIter weight_first)
          : _intervals(intervals_first, intervals_last)
        {
            if(_intervals.size() < 2) {
                _intervals.clear();
                _intervals.push_back(RealType(0));
                _intervals.push_back(RealType(1));
                _weights.push_back(WeightType(1));
            } else {
                _weights.reserve(_intervals.size() - 1);
                for(std::size_t i = 0; i < _intervals.size() - 1; ++i) {
                    _weights.push_back(*weight_first++);
                }
            }
        }
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
        /**
         * Constructs a @c param_type object from an
         * initializer_list containing the interval boundaries
         * and a unary function specifying the weights.  Each
         * weight is determined by calling the function at the
         * midpoint of the corresponding interval.
         *
         * If the initializer_list contains less than two elements,
         * this is equivalent to the default constructor and the
         * distribution will produce values uniformly distributed
         * in the range [0, 1).
         */
        template<class T, class F>
        param_type(const std::initializer_list<T>& il, F f)
          : _intervals(il.begin(), il.end())
        {
            if(_intervals.size() < 2) {
                _intervals.clear();
                _intervals.push_back(RealType(0));
                _intervals.push_back(RealType(1));
                _weights.push_back(WeightType(1));
            } else {
                _weights.reserve(_intervals.size() - 1);
                for(std::size_t i = 0; i < _intervals.size() - 1; ++i) {
                    RealType midpoint = (_intervals[i] + _intervals[i + 1]) / 2;
                    _weights.push_back(f(midpoint));
                }
            }
        }
#endif
        /**
         * Constructs a @c param_type object from Boost.Range
         * ranges holding the interval boundaries and the weights.  If
         * there are less than two interval boundaries, this is equivalent
         * to the default constructor and the distribution will produce
         * values uniformly distributed in the range [0, 1).  The
         * number of weights must be one less than the number of
         * interval boundaries.
         */
        template<class IntervalRange, class WeightRange>
        param_type(const IntervalRange& intervals_arg,
                   const WeightRange& weights_arg)
          : _intervals(boost::begin(intervals_arg), boost::end(intervals_arg)),
            _weights(boost::begin(weights_arg), boost::end(weights_arg))
        {
            if(_intervals.size() < 2) {
                _intervals.clear();
                _intervals.push_back(RealType(0));
                _intervals.push_back(RealType(1));
                _weights.push_back(WeightType(1));
            }
        }

        /**
         * Constructs the parameters for a distribution that approximates a
         * function.  The range of the distribution is [xmin, xmax).  This
         * range is divided into nw equally sized intervals and the weights
         * are found by calling the unary function f on the midpoints of the
         * intervals.
         */
        template<class F>
        param_type(std::size_t nw, RealType xmin, RealType xmax, F f)
        {
            std::size_t n = (nw == 0) ? 1 : nw;
            double delta = (xmax - xmin) / n;
            BOOST_ASSERT(delta > 0);
            for(std::size_t k = 0; k < n; ++k) {
                _weights.push_back(f(xmin + k*delta + delta/2));
                _intervals.push_back(xmin + k*delta);
            }
            _intervals.push_back(xmax);
        }

        /**  Returns a vector containing the interval boundaries. */
        std::vector<RealType> intervals() const { return _intervals; }

        /**
         * Returns a vector containing the probability densities
         * over all the intervals of the distribution.
         */
        std::vector<RealType> densities() const
        {
            RealType sum = std::accumulate(_weights.begin(), _weights.end(),
                                             static_cast<RealType>(0));
            std::vector<RealType> result;
            result.reserve(_weights.size());
            for(std::size_t i = 0; i < _weights.size(); ++i) {
                RealType width = _intervals[i + 1] - _intervals[i];
                result.push_back(_weights[i] / (sum * width));
            }
            return result;
        }

        /** Writes the parameters to a @c std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            detail::print_vector(os, parm._intervals);
            detail::print_vector(os, parm._weights);
            return os;
        }
        
        /** Reads the parameters from a @c std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            std::vector<RealType> new_intervals;
            std::vector<WeightType> new_weights;
            detail::read_vector(is, new_intervals);
            detail::read_vector(is, new_weights);
            if(is) {
                parm._intervals.swap(new_intervals);
                parm._weights.swap(new_weights);
            }
            return is;
        }

        /** Returns true if the two sets of parameters are the same. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        {
            return lhs._intervals == rhs._intervals
                && lhs._weights == rhs._weights;
        }
        /** Returns true if the two sets of parameters are different. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)

    private:

        friend class piecewise_constant_distribution;

        std::vector<RealType> _intervals;
        std::vector<WeightType> _weights;
    };

    /**
     * Creates a new @c piecewise_constant_distribution with
     * a single interval, [0, 1).
     */
    piecewise_constant_distribution()
    {
        _intervals.push_back(RealType(0));
        _intervals.push_back(RealType(1));
    }
    /**
     * Constructs a piecewise_constant_distribution from two iterator ranges
     * containing the interval boundaries and the interval weights.
     * If there are less than two boundaries, then this is equivalent to
     * the default constructor and creates a single interval, [0, 1).
     *
     * The values of the interval boundaries must be strictly
     * increasing, and the number of weights must be one less than
     * the number of interval boundaries.  If there are extra
     * weights, they are ignored.
     *
     * For example,
     *
     * @code
     * double intervals[] = { 0.0, 1.0, 4.0 };
     * double weights[] = { 1.0, 1.0 };
     * piecewise_constant_distribution<> dist(
     *     &intervals[0], &intervals[0] + 3, &weights[0]);
     * @endcode
     *
     * The distribution has a 50% chance of producing a
     * value between 0 and 1 and a 50% chance of producing
     * a value between 1 and 4.
     */
    template<class IntervalIter, class WeightIter>
    piecewise_constant_distribution(IntervalIter first_interval,
                                    IntervalIter last_interval,
                                    WeightIter first_weight)
      : _intervals(first_interval, last_interval)
    {
        if(_intervals.size() < 2) {
            _intervals.clear();
            _intervals.push_back(RealType(0));
            _intervals.push_back(RealType(1));
        } else {
            std::vector<WeightType> actual_weights;
            actual_weights.reserve(_intervals.size() - 1);
            for(std::size_t i = 0; i < _intervals.size() - 1; ++i) {
                actual_weights.push_back(*first_weight++);
            }
            typedef discrete_distribution<std::size_t, WeightType> bins_type;
            typename bins_type::param_type bins_param(actual_weights);
            _bins.param(bins_param);
        }
    }
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * Constructs a piecewise_constant_distribution from an
     * initializer_list containing the interval boundaries
     * and a unary function specifying the weights.  Each
     * weight is determined by calling the function at the
     * midpoint of the corresponding interval.
     *
     * If the initializer_list contains less than two elements,
     * this is equivalent to the default constructor and the
     * distribution will produce values uniformly distributed
     * in the range [0, 1).
     */
    template<class T, class F>
    piecewise_constant_distribution(std::initializer_list<T> il, F f)
      : _intervals(il.begin(), il.end())
    {
        if(_intervals.size() < 2) {
            _intervals.clear();
            _intervals.push_back(RealType(0));
            _intervals.push_back(RealType(1));
        } else {
            std::vector<WeightType> actual_weights;
            actual_weights.reserve(_intervals.size() - 1);
            for(std::size_t i = 0; i < _intervals.size() - 1; ++i) {
                RealType midpoint = (_intervals[i] + _intervals[i + 1]) / 2;
                actual_weights.push_back(f(midpoint));
            }
            typedef discrete_distribution<std::size_t, WeightType> bins_type;
            typename bins_type::param_type bins_param(actual_weights);
            _bins.param(bins_param);
        }
    }
#endif
    /**
     * Constructs a piecewise_constant_distribution from Boost.Range
     * ranges holding the interval boundaries and the weights.  If
     * there are less than two interval boundaries, this is equivalent
     * to the default constructor and the distribution will produce
     * values uniformly distributed in the range [0, 1).  The
     * number of weights must be one less than the number of
     * interval boundaries.
     */
    template<class IntervalsRange, class WeightsRange>
    piecewise_constant_distribution(const IntervalsRange& intervals_arg,
                                    const WeightsRange& weights_arg)
      : _bins(weights_arg),
        _intervals(boost::begin(intervals_arg), boost::end(intervals_arg))
    {
        if(_intervals.size() < 2) {
            _intervals.clear();
            _intervals.push_back(RealType(0));
            _intervals.push_back(RealType(1));
        }
    }
    /**
     * Constructs a piecewise_constant_distribution that approximates a
     * function.  The range of the distribution is [xmin, xmax).  This
     * range is divided into nw equally sized intervals and the weights
     * are found by calling the unary function f on the midpoints of the
     * intervals.
     */
    template<class F>
    piecewise_constant_distribution(std::size_t nw,
                                    RealType xmin,
                                    RealType xmax,
                                    F f)
      : _bins(nw, xmin, xmax, f)
    {
        if(nw == 0) { nw = 1; }
        RealType delta = (xmax - xmin) / nw;
        _intervals.reserve(nw + 1);
        for(std::size_t i = 0; i < nw; ++i) {
            _intervals.push_back(xmin + i * delta);
        }
        _intervals.push_back(xmax);
    }
    /**
     * Constructs a piecewise_constant_distribution from its parameters.
     */
    explicit piecewise_constant_distribution(const param_type& parm)
      : _bins(parm._weights),
        _intervals(parm._intervals)
    {
    }

    /**
     * Returns a value distributed according to the parameters of the
     * piecewist_constant_distribution.
     */
    template<class URNG>
    RealType operator()(URNG& urng) const
    {
        std::size_t i = _bins(urng);
        return uniform_real<RealType>(_intervals[i], _intervals[i+1])(urng);
    }
    
    /**
     * Returns a value distributed according to the parameters
     * specified by param.
     */
    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return piecewise_constant_distribution(parm)(urng);
    }
    
    /** Returns the smallest value that the distribution can produce. */
    result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return _intervals.front(); }
    /** Returns the largest value that the distribution can produce. */
    result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return _intervals.back(); }

    /**
     * Returns a vector containing the probability density
     * over each interval.
     */
    std::vector<RealType> densities() const
    {
        std::vector<RealType> result(_bins.probabilities());
        for(std::size_t i = 0; i < result.size(); ++i) {
            result[i] /= (_intervals[i+1] - _intervals[i]);
        }
        return(result);
    }
    /**  Returns a vector containing the interval boundaries. */
    std::vector<RealType> intervals() const { return _intervals; }

    /** Returns the parameters of the distribution. */
    param_type param() const
    {
        return param_type(_intervals, _bins.probabilities());
    }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        std::vector<RealType> new_intervals(parm._intervals);
        typedef discrete_distribution<std::size_t, WeightType> bins_type;
        typename bins_type::param_type bins_param(parm._weights);
        _bins.param(bins_param);
        _intervals.swap(new_intervals);
    }
    
    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { _bins.reset(); }

    /** Writes a distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(
        os, piecewise_constant_distribution, pcd)
    {
        os << pcd.param();
        return os;
    }

    /** Reads a distribution from a @c std::istream */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(
        is, piecewise_constant_distribution, pcd)
    {
        param_type parm;
        if(is >> parm) {
            pcd.param(parm);
        }
        return is;
    }

    /**
     * Returns true if the two distributions will return the
     * same sequence of values, when passed equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(
        piecewise_constant_distribution, lhs,  rhs)
    {
        return lhs._bins == rhs._bins && lhs._intervals == rhs._intervals;
    }
    /**
     * Returns true if the two distributions may return different
     * sequences of values, when passed equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(piecewise_constant_distribution)

private:
    discrete_distribution<std::size_t, WeightType> _bins;
    std::vector<RealType> _intervals;
};

}
}

#endif

/* piecewise_constant_distribution.hpp
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
*/