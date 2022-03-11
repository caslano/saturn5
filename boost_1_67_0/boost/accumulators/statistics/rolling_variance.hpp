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