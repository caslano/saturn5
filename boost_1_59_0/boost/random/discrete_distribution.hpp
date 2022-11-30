/* boost random/discrete_distribution.hpp header file
 *
 * Copyright Steven Watanabe 2009-2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_DISCRETE_DISTRIBUTION_HPP_INCLUDED
#define BOOST_RANDOM_DISCRETE_DISTRIBUTION_HPP_INCLUDED

#include <vector>
#include <limits>
#include <numeric>
#include <utility>
#include <iterator>
#include <boost/assert.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/detail/vector_io.hpp>

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/random/detail/disable_warnings.hpp>

namespace boost {
namespace random {
namespace detail {

template<class IntType, class WeightType>
struct integer_alias_table {
    WeightType get_weight(IntType bin) const {
        WeightType result = _average;
        if(bin < _excess) ++result;
        return result;
    }
    template<class Iter>
    WeightType init_average(Iter begin, Iter end) {
        WeightType weight_average = 0;
        IntType excess = 0;
        IntType n = 0;
        // weight_average * n + excess == current partial sum
        // This is a bit messy, but it's guaranteed not to overflow
        for(Iter iter = begin; iter != end; ++iter) {
            ++n;
            if(*iter < weight_average) {
                WeightType diff = weight_average - *iter;
                weight_average -= diff / n;
                if(diff % n > excess) {
                    --weight_average;
                    excess += n - diff % n;
                } else {
                    excess -= diff % n;
                }
            } else {
                WeightType diff = *iter - weight_average;
                weight_average += diff / n;
                if(diff % n < n - excess) {
                    excess += diff % n;
                } else {
                    ++weight_average;
                    excess -= n - diff % n;
                }
            }
        }
        _alias_table.resize(static_cast<std::size_t>(n));
        _average = weight_average;
        _excess = excess;
        return weight_average;
    }
    void init_empty()
    {
        _alias_table.clear();
        _alias_table.push_back(std::make_pair(static_cast<WeightType>(1),
                                              static_cast<IntType>(0)));
        _average = static_cast<WeightType>(1);
        _excess = static_cast<IntType>(0);
    }
    bool operator==(const integer_alias_table& other) const
    {
        return _alias_table == other._alias_table &&
            _average == other._average && _excess == other._excess;
    }
    static WeightType normalize(WeightType val, WeightType /* average */)
    {
        return val;
    }
    static void normalize(std::vector<WeightType>&) {}
    template<class URNG>
    WeightType test(URNG &urng) const
    {
        return uniform_int_distribution<WeightType>(0, _average)(urng);
    }
    bool accept(IntType result, WeightType val) const
    {
        return result < _excess || val < _average;
    }
    static WeightType try_get_sum(const std::vector<WeightType>& weights)
    {
        WeightType result = static_cast<WeightType>(0);
        for(typename std::vector<WeightType>::const_iterator
                iter = weights.begin(), end = weights.end();
            iter != end; ++iter)
        {
            if((std::numeric_limits<WeightType>::max)() - result > *iter) {
                return static_cast<WeightType>(0);
            }
            result += *iter;
        }
        return result;
    }
    template<class URNG>
    static WeightType generate_in_range(URNG &urng, WeightType max)
    {
        return uniform_int_distribution<WeightType>(
            static_cast<WeightType>(0), max-1)(urng);
    }
    typedef std::vector<std::pair<WeightType, IntType> > alias_table_t;
    alias_table_t _alias_table;
    WeightType _average;
    IntType _excess;
};

template<class IntType, class WeightType>
struct real_alias_table {
    WeightType get_weight(IntType) const
    {
        return WeightType(1.0);
    }
    template<class Iter>
    WeightType init_average(Iter first, Iter last)
    {
        std::size_t size = std::distance(first, last);
        WeightType weight_sum =
            std::accumulate(first, last, static_cast<WeightType>(0));
        _alias_table.resize(size);
        return weight_sum / size;
    }
    void init_empty()
    {
        _alias_table.clear();
        _alias_table.push_back(std::make_pair(static_cast<WeightType>(1),
                                              static_cast<IntType>(0)));
    }
    bool operator==(const real_alias_table& other) const
    {
        return _alias_table == other._alias_table;
    }
    static WeightType normalize(WeightType val, WeightType average)
    {
        return val / average;
    }
    static void normalize(std::vector<WeightType>& weights)
    {
        WeightType sum =
            std::accumulate(weights.begin(), weights.end(),
                            static_cast<WeightType>(0));
        for(typename std::vector<WeightType>::iterator
                iter = weights.begin(),
                end = weights.end();
            iter != end; ++iter)
        {
            *iter /= sum;
        }
    }
    template<class URNG>
    WeightType test(URNG &urng) const
    {
        return uniform_01<WeightType>()(urng);
    }
    bool accept(IntType, WeightType) const
    {
        return true;
    }
    static WeightType try_get_sum(const std::vector<WeightType>& /* weights */)
    {
        return static_cast<WeightType>(1);
    }
    template<class URNG>
    static WeightType generate_in_range(URNG &urng, WeightType)
    {
        return uniform_01<WeightType>()(urng);
    }
    typedef std::vector<std::pair<WeightType, IntType> > alias_table_t;
    alias_table_t _alias_table;
};

template<bool IsIntegral>
struct select_alias_table;

template<>
struct select_alias_table<true> {
    template<class IntType, class WeightType>
    struct apply {
        typedef integer_alias_table<IntType, WeightType> type;
    };
};

template<>
struct select_alias_table<false> {
    template<class IntType, class WeightType>
    struct apply {
        typedef real_alias_table<IntType, WeightType> type;
    };
};

}

/**
 * The class @c discrete_distribution models a \random_distribution.
 * It produces integers in the range [0, n) with the probability
 * of producing each value is specified by the parameters of the
 * distribution.
 */
template<class IntType = int, class WeightType = double>
class discrete_distribution {
public:
    typedef WeightType input_type;
    typedef IntType result_type;

    class param_type {
    public:

        typedef discrete_distribution distribution_type;

        /**
         * Constructs a @c param_type object, representing a distribution
         * with \f$p(0) = 1\f$ and \f$p(k|k>0) = 0\f$.
         */
        param_type() : _probabilities(1, static_cast<WeightType>(1)) {}
        /**
         * If @c first == @c last, equivalent to the default constructor.
         * Otherwise, the values of the range represent weights for the
         * possible values of the distribution.
         */
        template<class Iter>
        param_type(Iter first, Iter last) : _probabilities(first, last)
        {
            normalize();
        }
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
        /**
         * If wl.size() == 0, equivalent to the default constructor.
         * Otherwise, the values of the @c initializer_list represent
         * weights for the possible values of the distribution.
         */
        param_type(const std::initializer_list<WeightType>& wl)
          : _probabilities(wl)
        {
            normalize();
        }
#endif
        /**
         * If the range is empty, equivalent to the default constructor.
         * Otherwise, the elements of the range represent
         * weights for the possible values of the distribution.
         */
        template<class Range>
        explicit param_type(const Range& range)
          : _probabilities(boost::begin(range), boost::end(range))
        {
            normalize();
        }

        /**
         * If nw is zero, equivalent to the default constructor.
         * Otherwise, the range of the distribution is [0, nw),
         * and the weights are found by  calling fw with values
         * evenly distributed between \f$\mbox{xmin} + \delta/2\f$ and
         * \f$\mbox{xmax} - \delta/2\f$, where
         * \f$\delta = (\mbox{xmax} - \mbox{xmin})/\mbox{nw}\f$.
         */
        template<class Func>
        param_type(std::size_t nw, double xmin, double xmax, Func fw)
        {
            std::size_t n = (nw == 0) ? 1 : nw;
            double delta = (xmax - xmin) / n;
            BOOST_ASSERT(delta > 0);
            for(std::size_t k = 0; k < n; ++k) {
                _probabilities.push_back(fw(xmin + k*delta + delta/2));
            }
            normalize();
        }

        /**
         * Returns a vector containing the probabilities of each possible
         * value of the distribution.
         */
        std::vector<WeightType> probabilities() const
        {
            return _probabilities;
        }

        /** Writes the parameters to a @c std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            detail::print_vector(os, parm._probabilities);
            return os;
        }
        
        /** Reads the parameters from a @c std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            std::vector<WeightType> temp;
            detail::read_vector(is, temp);
            if(is) {
                parm._probabilities.swap(temp);
            }
            return is;
        }

        /** Returns true if the two sets of parameters are the same. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        {
            return lhs._probabilities == rhs._probabilities;
        }
        /** Returns true if the two sets of parameters are different. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)
    private:
        /// @cond show_private
        friend class discrete_distribution;
        explicit param_type(const discrete_distribution& dist)
          : _probabilities(dist.probabilities())
        {}
        void normalize()
        {
            impl_type::normalize(_probabilities);
        }
        std::vector<WeightType> _probabilities;
        /// @endcond
    };

    /**
     * Creates a new @c discrete_distribution object that has
     * \f$p(0) = 1\f$ and \f$p(i|i>0) = 0\f$.
     */
    discrete_distribution()
    {
        _impl.init_empty();
    }
    /**
     * Constructs a discrete_distribution from an iterator range.
     * If @c first == @c last, equivalent to the default constructor.
     * Otherwise, the values of the range represent weights for the
     * possible values of the distribution.
     */
    template<class Iter>
    discrete_distribution(Iter first, Iter last)
    {
        init(first, last);
    }
#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * Constructs a @c discrete_distribution from a @c std::initializer_list.
     * If the @c initializer_list is empty, equivalent to the default
     * constructor.  Otherwise, the values of the @c initializer_list
     * represent weights for the possible values of the distribution.
     * For example, given the distribution
     *
     * @code
     * discrete_distribution<> dist{1, 4, 5};
     * @endcode
     *
     * The probability of a 0 is 1/10, the probability of a 1 is 2/5,
     * the probability of a 2 is 1/2, and no other values are possible.
     */
    discrete_distribution(std::initializer_list<WeightType> wl)
    {
        init(wl.begin(), wl.end());
    }
#endif
    /**
     * Constructs a discrete_distribution from a Boost.Range range.
     * If the range is empty, equivalent to the default constructor.
     * Otherwise, the values of the range represent weights for the
     * possible values of the distribution.
     */
    template<class Range>
    explicit discrete_distribution(const Range& range)
    {
        init(boost::begin(range), boost::end(range));
    }
    /**
     * Constructs a discrete_distribution that approximates a function.
     * If nw is zero, equivalent to the default constructor.
     * Otherwise, the range of the distribution is [0, nw),
     * and the weights are found by  calling fw with values
     * evenly distributed between \f$\mbox{xmin} + \delta/2\f$ and
     * \f$\mbox{xmax} - \delta/2\f$, where
     * \f$\delta = (\mbox{xmax} - \mbox{xmin})/\mbox{nw}\f$.
     */
    template<class Func>
    discrete_distribution(std::size_t nw, double xmin, double xmax, Func fw)
    {
        std::size_t n = (nw == 0) ? 1 : nw;
        double delta = (xmax - xmin) / n;
        BOOST_ASSERT(delta > 0);
        std::vector<WeightType> weights;
        for(std::size_t k = 0; k < n; ++k) {
            weights.push_back(fw(xmin + k*delta + delta/2));
        }
        init(weights.begin(), weights.end());
    }
    /**
     * Constructs a discrete_distribution from its parameters.
     */
    explicit discrete_distribution(const param_type& parm)
    {
        param(parm);
    }

    /**
     * Returns a value distributed according to the parameters of the
     * discrete_distribution.
     */
    template<class URNG>
    IntType operator()(URNG& urng) const
    {
        BOOST_ASSERT(!_impl._alias_table.empty());
        IntType result;
        WeightType test;
        do {
            result = uniform_int_distribution<IntType>((min)(), (max)())(urng);
            test = _impl.test(urng);
        } while(!_impl.accept(result, test));
        if(test < _impl._alias_table[static_cast<std::size_t>(result)].first) {
            return result;
        } else {
            return(_impl._alias_table[static_cast<std::size_t>(result)].second);
        }
    }
    
    /**
     * Returns a value distributed according to the parameters
     * specified by param.
     */
    template<class URNG>
    IntType operator()(URNG& urng, const param_type& parm) const
    {
        if(WeightType limit = impl_type::try_get_sum(parm._probabilities)) {
            WeightType val = impl_type::generate_in_range(urng, limit);
            WeightType sum = 0;
            std::size_t result = 0;
            for(typename std::vector<WeightType>::const_iterator
                    iter = parm._probabilities.begin(),
                    end = parm._probabilities.end();
                iter != end; ++iter, ++result)
            {
                sum += *iter;
                if(sum > val) {
                    return result;
                }
            }
            // This shouldn't be reachable, but round-off error
            // can prevent any match from being found when val is
            // very close to 1.
            return static_cast<IntType>(parm._probabilities.size() - 1);
        } else {
            // WeightType is integral and sum(parm._probabilities)
            // would overflow.  Just use the easy solution.
            return discrete_distribution(parm)(urng);
        }
    }
    
    /** Returns the smallest value that the distribution can produce. */
    result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return 0; }
    /** Returns the largest value that the distribution can produce. */
    result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return static_cast<result_type>(_impl._alias_table.size() - 1); }

    /**
     * Returns a vector containing the probabilities of each
     * value of the distribution.  For example, given
     *
     * @code
     * discrete_distribution<> dist = { 1, 4, 5 };
     * std::vector<double> p = dist.param();
     * @endcode
     *
     * the vector, p will contain {0.1, 0.4, 0.5}.
     *
     * If @c WeightType is integral, then the weights
     * will be returned unchanged.
     */
    std::vector<WeightType> probabilities() const
    {
        std::vector<WeightType> result(_impl._alias_table.size(), static_cast<WeightType>(0));
        std::size_t i = 0;
        for(typename impl_type::alias_table_t::const_iterator
                iter = _impl._alias_table.begin(),
                end = _impl._alias_table.end();
                iter != end; ++iter, ++i)
        {
            WeightType val = iter->first;
            result[i] += val;
            result[static_cast<std::size_t>(iter->second)] += _impl.get_weight(i) - val;
        }
        impl_type::normalize(result);
        return(result);
    }

    /** Returns the parameters of the distribution. */
    param_type param() const
    {
        return param_type(*this);
    }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        init(parm._probabilities.begin(), parm._probabilities.end());
    }
    
    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() {}

    /** Writes a distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, discrete_distribution, dd)
    {
        os << dd.param();
        return os;
    }

    /** Reads a distribution from a @c std::istream */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, discrete_distribution, dd)
    {
        param_type parm;
        if(is >> parm) {
            dd.param(parm);
        }
        return is;
    }

    /**
     * Returns true if the two distributions will return the
     * same sequence of values, when passed equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(discrete_distribution, lhs, rhs)
    {
        return lhs._impl == rhs._impl;
    }
    /**
     * Returns true if the two distributions may return different
     * sequences of values, when passed equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(discrete_distribution)

private:

    /// @cond show_private

    template<class Iter>
    void init(Iter first, Iter last, std::input_iterator_tag)
    {
        std::vector<WeightType> temp(first, last);
        init(temp.begin(), temp.end());
    }
    template<class Iter>
    void init(Iter first, Iter last, std::forward_iterator_tag)
    {
        size_t input_size = std::distance(first, last);
        std::vector<std::pair<WeightType, IntType> > below_average;
        std::vector<std::pair<WeightType, IntType> > above_average;
        below_average.reserve(input_size);
        above_average.reserve(input_size);
        
        WeightType weight_average = _impl.init_average(first, last);
        WeightType normalized_average = _impl.get_weight(0);
        std::size_t i = 0;
        for(; first != last; ++first, ++i) {
            WeightType val = impl_type::normalize(*first, weight_average);
            std::pair<WeightType, IntType> elem(val, static_cast<IntType>(i));
            if(val < normalized_average) {
                below_average.push_back(elem);
            } else {
                above_average.push_back(elem);
            }
        }

        typename impl_type::alias_table_t::iterator
            b_iter = below_average.begin(),
            b_end = below_average.end(),
            a_iter = above_average.begin(),
            a_end = above_average.end()
            ;
        while(b_iter != b_end && a_iter != a_end) {
            _impl._alias_table[static_cast<std::size_t>(b_iter->second)] =
                std::make_pair(b_iter->first, a_iter->second);
            a_iter->first -= (_impl.get_weight(b_iter->second) - b_iter->first);
            if(a_iter->first < normalized_average) {
                *b_iter = *a_iter++;
            } else {
                ++b_iter;
            }
        }
        for(; b_iter != b_end; ++b_iter) {
            _impl._alias_table[static_cast<std::size_t>(b_iter->second)].first =
                _impl.get_weight(b_iter->second);
        }
        for(; a_iter != a_end; ++a_iter) {
            _impl._alias_table[static_cast<std::size_t>(a_iter->second)].first =
                _impl.get_weight(a_iter->second);
        }
    }
    template<class Iter>
    void init(Iter first, Iter last)
    {
        if(first == last) {
            _impl.init_empty();
        } else {
            typename std::iterator_traits<Iter>::iterator_category category;
            init(first, last, category);
        }
    }
    typedef typename detail::select_alias_table<
        (::boost::is_integral<WeightType>::value)
    >::template apply<IntType, WeightType>::type impl_type;
    impl_type _impl;
    /// @endcond
};

}
}

#include <boost/random/detail/enable_warnings.hpp>

#endif

/* discrete_distribution.hpp
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
*/