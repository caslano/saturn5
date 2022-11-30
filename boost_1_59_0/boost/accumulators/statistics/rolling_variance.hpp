///////////////////////////////////////////////////////////////////////////////
// rolling_variance.hpp
// Copyright (C) 2005 Eric Niebler
// Copyright (C) 2014 Pieter Bastiaan Ober (Integricom).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ROLLING_VARIANCE_HPP_EAN_15_11_2011
#define BOOST_ACCUMULATORS_STATISTICS_ROLLING_VARIANCE_HPP_EAN_15_11_2011

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>
#include <boost/accumulators/statistics/rolling_moment.hpp>

#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace accumulators
{
namespace impl
{
    //! Immediate (lazy) calculation of the rolling variance.
    /*!
    Calculation of sample variance \f$\sigma_n^2\f$ is done as follows, see also
    http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance.
    For a rolling window of size \f$N\f$, when \f$n <= N\f$, the variance is computed according to the formula
    \f[
    \sigma_n^2 = \frac{1}{n-1} \sum_{i = 1}^n (x_i - \mu_n)^2.
    \f]
    When \f$n > N\f$, the sample variance over the window becomes:
    \f[
    \sigma_n^2 = \frac{1}{N-1} \sum_{i = n-N+1}^n (x_i - \mu_n)^2.
    \f]
    */
    ///////////////////////////////////////////////////////////////////////////////
    // lazy_rolling_variance_impl
    //
    template<typename Sample>
    struct lazy_rolling_variance_impl
        : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t,void,void>::result_type result_type;

        lazy_rolling_variance_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            result_type mean = rolling_mean(args);
            size_t nr_samples = rolling_count(args);
            if (nr_samples < 2) return result_type();
            return nr_samples*(rolling_moment<2>(args) - mean*mean)/(nr_samples-1);
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

    //! Iterative calculation of the rolling variance.
    /*!
    Iterative calculation of sample variance \f$\sigma_n^2\f$ is done as follows, see also
    http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance.
    For a rolling window of size \f$N\f$, for the first \f$N\f$ samples, the variance is computed according to the formula
    \f[
    \sigma_n^2 = \frac{1}{n-1} \sum_{i = 1}^n (x_i - \mu_n)^2 = \frac{1}{n-1}M_{2,n},
    \f]
    where the sum of squares \f$M_{2,n}\f$ can be recursively computed as:
    \f[
    M_{2,n} = \sum_{i = 1}^n (x_i - \mu_n)^2 = M_{2,n-1} + (x_n - \mu_n)(x_n - \mu_{n-1}),
    \f]
    and the estimate of the sample mean as:
    \f[
    \mu_n = \frac{1}{n} \sum_{i = 1}^n x_i = \mu_{n-1} + \frac{1}{n}(x_n - \mu_{n-1}).
    \f]
    For further samples, when the rolling window is fully filled with data, one has to take into account that the oldest
    sample \f$x_{n-N}\f$ is dropped from the window. The sample variance over the window now becomes:
    \f[
    \sigma_n^2 = \frac{1}{N-1} \sum_{i = n-N+1}^n (x_i - \mu_n)^2 = \frac{1}{n-1}M_{2,n},
    \f]
    where the sum of squares \f$M_{2,n}\f$ now equals:
    \f[
    M_{2,n} = \sum_{i = n-N+1}^n (x_i - \mu_n)^2 = M_{2,n-1} + (x_n - \mu_n)(x_n - \mu_{n-1}) - (x_{n-N} - \mu_n)(x_{n-N} - \mu_{n-1}),
    \f]
    and the estimated mean is:
    \f[
    \mu_n = \frac{1}{N} \sum_{i = n-N+1}^n x_i = \mu_{n-1} + \frac{1}{n}(x_n - x_{n-N}).
    \f]

    Note that the sample variance is not defined for \f$n <= 1\f$.

    */
    ///////////////////////////////////////////////////////////////////////////////
    // immediate_rolling_variance_impl
    //
    template<typename Sample>
    struct immediate_rolling_variance_impl
        : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        template<typename Args>
        immediate_rolling_variance_impl(Args const &args)
            : previous_mean_(numeric::fdiv(args[sample | Sample()], numeric::one<std::size_t>::value))
            , sum_of_squares_(numeric::fdiv(args[sample | Sample()], numeric::one<std::size_t>::value))
        {
        }

        template<typename Args>
        void operator()(Args const &args)
        {
            Sample added_sample = args[sample];

            result_type mean = immediate_rolling_mean(args);
            sum_of_squares_ += (added_sample-mean)*(added_sample-previous_mean_);

            if(is_rolling_window_plus1_full(args))
            {
                Sample removed_sample = rolling_window_plus1(args).front();
                sum_of_squares_ -= (removed_sample-mean)*(removed_sample-previous_mean_);
                prevent_underflow(sum_of_squares_);
            }
            previous_mean_ = mean;
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            size_t nr_samples = rolling_count(args);
            if (nr_samples < 2) return result_type();
            return numeric::fdiv(sum_of_squares_,(nr_samples-1));
        }
        
        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & previous_mean_;
            ar & sum_of_squares_;
        }

    private:

        result_type previous_mean_;
        result_type sum_of_squares_;

        template<typename T>
        void prevent_underflow(T &non_negative_number,typename boost::enable_if<boost::is_arithmetic<T>,T>::type* = 0)
        {
            if (non_negative_number < T(0)) non_negative_number = T(0);
        }
        template<typename T>
        void prevent_underflow(T &non_arithmetic_quantity,typename boost::disable_if<boost::is_arithmetic<T>,T>::type* = 0)
        {
        }
    };
} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag:: lazy_rolling_variance
// tag:: immediate_rolling_variance
// tag:: rolling_variance
//
namespace tag
{
    struct lazy_rolling_variance
        : depends_on< rolling_count, rolling_mean, rolling_moment<2> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::lazy_rolling_variance_impl< mpl::_1 > impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::rolling_window::window_size named parameter
        static boost::parameter::keyword<tag::rolling_window_size> const window_size;
        #endif
    };

    struct immediate_rolling_variance
        : depends_on< rolling_window_plus1, rolling_count, immediate_rolling_mean>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::immediate_rolling_variance_impl< mpl::_1> impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::rolling_window::window_size named parameter
        static boost::parameter::keyword<tag::rolling_window_size> const window_size;
        #endif
    };

    // make immediate_rolling_variance the default implementation
    struct rolling_variance : immediate_rolling_variance {};
} // namespace tag

///////////////////////////////////////////////////////////////////////////////
// extract::lazy_rolling_variance
// extract::immediate_rolling_variance
// extract::rolling_variance
//
namespace extract
{
    extractor<tag::lazy_rolling_variance> const lazy_rolling_variance = {};
    extractor<tag::immediate_rolling_variance> const immediate_rolling_variance = {};
    extractor<tag::rolling_variance> const rolling_variance = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(lazy_rolling_variance)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(immediate_rolling_variance)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(rolling_variance)
}

using extract::lazy_rolling_variance;
using extract::immediate_rolling_variance;
using extract::rolling_variance;

// rolling_variance(lazy) -> lazy_rolling_variance
template<>
struct as_feature<tag::rolling_variance(lazy)>
{
    typedef tag::lazy_rolling_variance type;
};

// rolling_variance(immediate) -> immediate_rolling_variance
template<>
struct as_feature<tag::rolling_variance(immediate)>
{
    typedef tag::immediate_rolling_variance type;
};

// for the purposes of feature-based dependency resolution,
// lazy_rolling_variance provides the same feature as rolling_variance
template<>
struct feature_of<tag::lazy_rolling_variance>
    : feature_of<tag::rolling_variance>
{
};

// for the purposes of feature-based dependency resolution,
// immediate_rolling_variance provides the same feature as rolling_variance
template<>
struct feature_of<tag::immediate_rolling_variance>
  : feature_of<tag::rolling_variance>
{
};
}} // namespace boost::accumulators

#endif

/* rolling_variance.hpp
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
*/