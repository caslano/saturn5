/* boost random/piecewise_linear_distribution.hpp header file
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

#ifndef BOOST_RANDOM_PIECEWISE_LINEAR_DISTRIBUTION_HPP_INCLUDED
#define BOOST_RANDOM_PIECEWISE_LINEAR_DISTRIBUTION_HPP_INCLUDED

#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
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
 * The class @c piecewise_linear_distribution models a \random_distribution.
 */
template<class RealType = double>
class piecewise_linear_distribution {
public:
    typedef std::size_t input_type;
    typedef RealType result_type;

    class param_type {
    public:

        typedef piecewise_linear_distribution distribution_type;

        /**
         * Constructs a @c param_type object, representing a distribution
         * that produces values uniformly distributed in the range [0, 1).
         */
        param_type()
        {
            _weights.push_back(RealType(1));
            _weights.push_back(RealType(1));
            _intervals.push_back(RealType(0));
            _intervals.push_back(RealType(1));
        }
        /**
         * Constructs a @c param_type object from two iterator ranges
         * containing the interval boundaries and weights at the boundaries.
         * If there are fewer than two boundaries, then this is equivalent to
         * the default constructor and the distribution will produce values
         * uniformly distributed in the range [0, 1).
         *
         * The values of the interval boundaries must be strictly
         * increasing, and the number of weights must be the same as
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
                _weights.push_back(RealType(1));
                _weights.push_back(RealType(1));
                _intervals.push_back(RealType(0));
                _intervals.push_back(RealType(1));
            } else {
                _weights.reserve(_intervals.size());
                for(std::size_t i = 0; i < _intervals.size(); ++i) {
                    _weights.push_back(*weight_first++);
                }
            }
        }
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
        /**
         * Constructs a @c param_type object from an initializer_list
         * containing the interval boundaries and a unary function
         * specifying the weights at the boundaries.  Each weight is
         * determined by calling the function at the corresponding point.
         *
         * If the initializer_list contains fewer than two elements,
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
                _weights.push_back(RealType(1));
                _weights.push_back(RealType(1));
                _intervals.push_back(RealType(0));
                _intervals.push_back(RealType(1));
            } else {
                _weights.reserve(_intervals.size());
                for(typename std::vector<RealType>::const_iterator
                    iter = _intervals.begin(), end = _intervals.end();
                    iter != end; ++iter)
                {
                    _weights.push_back(f(*iter));
                }
            }
        }
#endif
        /**
         * Constructs a @c param_type object from Boost.Range ranges holding
         * the interval boundaries and the weights at the boundaries.  If
         * there are fewer than two interval boundaries, this is equivalent
         * to the default constructor and the distribution will produce
         * values uniformly distributed in the range [0, 1).  The
         * number of weights must be equal to the number of
         * interval boundaries.
         */
        template<class IntervalRange, class WeightRange>
        param_type(const IntervalRange& intervals_arg,
                   const WeightRange& weights_arg)
          : _intervals(boost::begin(intervals_arg), boost::end(intervals_arg)),
            _weights(boost::begin(weights_arg), boost::end(weights_arg))
        {
            if(_intervals.size() < 2) {
                _weights.clear();
                _weights.push_back(RealType(1));
                _weights.push_back(RealType(1));
                _intervals.clear();
                _intervals.push_back(RealType(0));
                _intervals.push_back(RealType(1));
            }
        }

        /**
         * Constructs the parameters for a distribution that approximates a
         * function.  The range of the distribution is [xmin, xmax).  This
         * range is divided into nw equally sized intervals and the weights
         * are found by calling the unary function f on the boundaries of the
         * intervals.
         */
        template<class F>
        param_type(std::size_t nw, RealType xmin, RealType xmax, F f)
        {
            std::size_t n = (nw == 0) ? 1 : nw;
            double delta = (xmax - xmin) / n;
            BOOST_ASSERT(delta > 0);
            for(std::size_t k = 0; k < n; ++k) {
                _weights.push_back(f(xmin + k*delta));
                _intervals.push_back(xmin + k*delta);
            }
            _weights.push_back(f(xmax));
            _intervals.push_back(xmax);
        }

        /**  Returns a vector containing the interval boundaries. */
        std::vector<RealType> intervals() const { return _intervals; }

        /**
         * Returns a vector containing the probability densities
         * at all the interval boundaries.
         */
        std::vector<RealType> densities() const
        {
            RealType sum = static_cast<RealType>(0);
            for(std::size_t i = 0; i < _intervals.size() - 1; ++i) {
                RealType width = _intervals[i + 1] - _intervals[i];
                sum += (_weights[i] + _weights[i + 1]) * width / 2;
            }
            std::vector<RealType> result;
            result.reserve(_weights.size());
            for(typename std::vector<RealType>::const_iterator
                iter = _weights.begin(), end = _weights.end();
                iter != end; ++iter)
            {
                result.push_back(*iter / sum);
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
            std::vector<RealType> new_weights;
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
        friend class piecewise_linear_distribution;

        std::vector<RealType> _intervals;
        std::vector<RealType> _weights;
    };

    /**
     * Creates a new @c piecewise_linear_distribution that
     * produces values uniformly distributed in the range [0, 1).
     */
    piecewise_linear_distribution()
    {
        default_init();
    }
    /**
     * Constructs a piecewise_linear_distribution from two iterator ranges
     * containing the interval boundaries and the weights at the boundaries.
     * If there are fewer than two boundaries, then this is equivalent to
     * the default constructor and creates a distribution that
     * produces values uniformly distributed in the range [0, 1).
     *
     * The values of the interval boundaries must be strictly
     * increasing, and the number of weights must be equal to
     * the number of interval boundaries.  If there are extra
     * weights, they are ignored.
     *
     * For example,
     *
     * @code
     * double intervals[] = { 0.0, 1.0, 2.0 };
     * double weights[] = { 0.0, 1.0, 0.0 };
     * piecewise_constant_distribution<> dist(
     *     &intervals[0], &intervals[0] + 3, &weights[0]);
     * @endcode
     *
     * produces a triangle distribution.
     */
    template<class IntervalIter, class WeightIter>
    piecewise_linear_distribution(IntervalIter first_interval,
                                  IntervalIter last_interval,
                                  WeightIter first_weight)
      : _intervals(first_interval, last_interval)
    {
        if(_intervals.size() < 2) {
            default_init();
        } else {
            _weights.reserve(_intervals.size());
            for(std::size_t i = 0; i < _intervals.size(); ++i) {
                _weights.push_back(*first_weight++);
            }
            init();
        }
    }
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * Constructs a piecewise_linear_distribution from an
     * initializer_list containing the interval boundaries
     * and a unary function specifying the weights.  Each
     * weight is determined by calling the function at the
     * corresponding interval boundary.
     *
     * If the initializer_list contains fewer than two elements,
     * this is equivalent to the default constructor and the
     * distribution will produce values uniformly distributed
     * in the range [0, 1).
     */
    template<class T, class F>
    piecewise_linear_distribution(std::initializer_list<T> il, F f)
      : _intervals(il.begin(), il.end())
    {
        if(_intervals.size() < 2) {
            default_init();
        } else {
            _weights.reserve(_intervals.size());
            for(typename std::vector<RealType>::const_iterator
                iter = _intervals.begin(), end = _intervals.end();
                iter != end; ++iter)
            {
                _weights.push_back(f(*iter));
            }
            init();
        }
    }
#endif
    /**
     * Constructs a piecewise_linear_distribution from Boost.Range
     * ranges holding the interval boundaries and the weights.  If
     * there are fewer than two interval boundaries, this is equivalent
     * to the default constructor and the distribution will produce
     * values uniformly distributed in the range [0, 1).  The
     * number of weights must be equal to the number of
     * interval boundaries.
     */
    template<class IntervalsRange, class WeightsRange>
    piecewise_linear_distribution(const IntervalsRange& intervals_arg,
                                  const WeightsRange& weights_arg)
      : _intervals(boost::begin(intervals_arg), boost::end(intervals_arg)),
        _weights(boost::begin(weights_arg), boost::end(weights_arg))
    {
        if(_intervals.size() < 2) {
            default_init();
        } else {
            init();
        }
    }
    /**
     * Constructs a piecewise_linear_distribution that approximates a
     * function.  The range of the distribution is [xmin, xmax).  This
     * range is divided into nw equally sized intervals and the weights
     * are found by calling the unary function f on the interval boundaries.
     */
    template<class F>
    piecewise_linear_distribution(std::size_t nw,
                                  RealType xmin,
                                  RealType xmax,
                                  F f)
    {
        if(nw == 0) { nw = 1; }
        RealType delta = (xmax - xmin) / nw;
        _intervals.reserve(nw + 1);
        for(std::size_t i = 0; i < nw; ++i) {
            RealType x = xmin + i * delta;
            _intervals.push_back(x);
            _weights.push_back(f(x));
        }
        _intervals.push_back(xmax);
        _weights.push_back(f(xmax));
        init();
    }
    /**
     * Constructs a piecewise_linear_distribution from its parameters.
     */
    explicit piecewise_linear_distribution(const param_type& parm)
      : _intervals(parm._intervals),
        _weights(parm._weights)
    {
        init();
    }

    /**
     * Returns a value distributed according to the parameters of the
     * piecewise_linear_distribution.
     */
    template<class URNG>
    RealType operator()(URNG& urng) const
    {
        std::size_t i = _bins(urng);
        bool is_in_rectangle = (i % 2 == 0);
        i = i / 2;
        uniform_real<RealType> dist(_intervals[i], _intervals[i+1]);
        if(is_in_rectangle) {
            return dist(urng);
        } else if(_weights[i] < _weights[i+1]) {
            return (std::max)(dist(urng), dist(urng));
        } else {
            return (std::min)(dist(urng), dist(urng));
        }
    }
    
    /**
     * Returns a value distributed according to the parameters
     * specified by param.
     */
    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return piecewise_linear_distribution(parm)(urng);
    }
    
    /** Returns the smallest value that the distribution can produce. */
    result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return _intervals.front(); }
    /** Returns the largest value that the distribution can produce. */
    result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return _intervals.back(); }

    /**
     * Returns a vector containing the probability densities
     * at the interval boundaries.
     */
    std::vector<RealType> densities() const
    {
        RealType sum = static_cast<RealType>(0);
        for(std::size_t i = 0; i < _intervals.size() - 1; ++i) {
            RealType width = _intervals[i + 1] - _intervals[i];
            sum += (_weights[i] + _weights[i + 1]) * width / 2;
        }
        std::vector<RealType> result;
        result.reserve(_weights.size());
        for(typename std::vector<RealType>::const_iterator
            iter = _weights.begin(), end = _weights.end();
            iter != end; ++iter)
        {
            result.push_back(*iter / sum);
        }
        return result;
    }
    /**  Returns a vector containing the interval boundaries. */
    std::vector<RealType> intervals() const { return _intervals; }

    /** Returns the parameters of the distribution. */
    param_type param() const
    {
        return param_type(_intervals, _weights);
    }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        std::vector<RealType> new_intervals(parm._intervals);
        std::vector<RealType> new_weights(parm._weights);
        init(new_intervals, new_weights);
        _intervals.swap(new_intervals);
        _weights.swap(new_weights);
    }
    
    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { _bins.reset(); }

    /** Writes a distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(
        os, piecewise_linear_distribution, pld)
    {
        os << pld.param();
        return os;
    }

    /** Reads a distribution from a @c std::istream */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(
        is, piecewise_linear_distribution, pld)
    {
        param_type parm;
        if(is >> parm) {
            pld.param(parm);
        }
        return is;
    }

    /**
     * Returns true if the two distributions will return the
     * same sequence of values, when passed equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(
        piecewise_linear_distribution, lhs,  rhs)
    {
        return lhs._intervals == rhs._intervals && lhs._weights == rhs._weights;
    }
    /**
     * Returns true if the two distributions may return different
     * sequences of values, when passed equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(piecewise_linear_distribution)

private:

    /// @cond \show_private

    void init(const std::vector<RealType>& intervals_arg,
              const std::vector<RealType>& weights_arg)
    {
        using std::abs;
        std::vector<RealType> bin_weights;
        bin_weights.reserve((intervals_arg.size() - 1) * 2);
        for(std::size_t i = 0; i < intervals_arg.size() - 1; ++i) {
            RealType width = intervals_arg[i + 1] - intervals_arg[i];
            RealType w1 = weights_arg[i];
            RealType w2 = weights_arg[i + 1];
            bin_weights.push_back((std::min)(w1, w2) * width);
            bin_weights.push_back(abs(w1 - w2) * width / 2);
        }
        typedef discrete_distribution<std::size_t, RealType> bins_type;
        typename bins_type::param_type bins_param(bin_weights);
        _bins.param(bins_param);
    }

    void init()
    {
        init(_intervals, _weights);
    }

    void default_init()
    {
        _intervals.clear();
        _intervals.push_back(RealType(0));
        _intervals.push_back(RealType(1));
        _weights.clear();
        _weights.push_back(RealType(1));
        _weights.push_back(RealType(1));
        init();
    }

    discrete_distribution<std::size_t, RealType> _bins;
    std::vector<RealType> _intervals;
    std::vector<RealType> _weights;

    /// @endcond
};

}
}

#endif

/* piecewise_linear_distribution.hpp
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
*/