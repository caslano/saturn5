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
ElvDbtgE4t0e23LnE0RdXy4pX/hyKR+Kv4PiKgELkL63r7K+yNqq0I+8bxBETYxnRDFo3sNtlwoAO3IScckHOukAeV5dANSKAPo9FgyCefAEAH2M4+tS/C66LfcJvXymdrZjerkUmOlTVgm9hNW1yElBjJbXV95ijvmVlGDq/7SQ/Tb6Ix0qYNzbse9mM+81fZvLob2qmxmj/sQWFvoiu59RoW/Ehog4ZM4KqjR3jU+tayMvjkLu7kuYeb2l7Fw68Ha8F5tuCGciyMjPFWsxW5bWoeofiaRT40g5NSYdkQPSB12OnnvDU+Gjr1yL/GHXVAmY4eFFgfpfzbl36MkrhiPuOy3b6vLlJ1jLe+cslObMdFtRhfyjK7QfYQ3jNJ4+LVYqsM7nogsEIjwc2MsztA1yqZltzBnaFGGMxDhXQQv9bukwNh9sRvdrZZxxPX0y8meznfrZT5vaihsF5XMxOLRKgD5byyP15T9hXrsTrfO6SH4U3mGodMj25wnkzO/3BvhBsUqoTQV+7YR15z1M4yX36hweNNUMSHi4DlvPP80CxuvPOKoHrX/QBGv5vIcXms1Z/N9LfZgorFP23iGZxu8z60wHhiLpkVvPCL9L+Lx6XMc5H/2h/dG6Nav/+6bl2uur21vF7fUz2ltfy9LeoIgqNajPf1J/4mYcrgZifFQomDLp8YRnvAI+7X+slFAU3P6fpbydyq8M1+XrmuXzohZ6Ys95YjPPP030ibHHIJRijhunXj5chudLqLWnR9e6Eqyqq7y7pHuTH6Pp/V++Ovk1KFpEGFH1kVdO8+487YamrFaVb0YMeMaY8KzINuGJNeD5c7YFnktNeBb9oOGZqOGJBTz3IK8VmCYny6oKjPX9Q2ODv/rquQr+oPuP9sxX4W9C+lap/yspTevwbbHiG4jkUzhKqefs/D5hO+LpgyzpL8mwlWSWYcpU5v+nsYXfi31RoKIl+H6dlwL5/taWYvC/1OHLozjvHPqfl0aW+2QpeKapLAUtW51rKbg/3LIUdDwoS8Hbv6v+UsAfEEqezZ3nisCfA39x+IvHX2f8JeHPib/h+BuNvwn4m4o/mE6YQx3GF/GmPGHxZ5tvMXEGNWXfCjyLLT2ZG9hF1QIQ9FO992OZzKIBt1aYheekj7/EGuMB7jAi362AHMf30WD2u5gUc2oKZgwyPLt9z3FSG1PBezWCyH8s6aEAOkD+Y0l3RQWR/1jS6/yM8kH38183Ep3l6ZuEzOQWeyeSaKdaOtlNylfDRflqEAh3Ab23GX1apCTZtflyjA7szlJhn98w+7xJ9lxT1EOhdCWGcsNRjh/ne4srvJX/mrVZJtNu7SZZ2coO0Mr2gboy1LTE8it3Znr8tC7HkRg9fj8Z+/MHDgjULdhrfzdjf77DZiyn19H+/Msv0F166YgtQKtb0I/p2IiR9NO7AZuARohBdXTwSNHVXUTVDZsol00u9YBNWyAx6gQ+3M8Z2tANThEyL9g2hchxp/1eG+uLhrnhVbf9J9BHMPXvQsrr38EI5FMF2r7dhpLP8EvkbjXEPZHK30v1ria6xFuer0teFaNRmIqY+xE0HfHtoCmJ7zielnhWTVMT3wn4TsB3Z5qm+E7iqQqzYjRd8e3Gt5t5CKYunS14+sKQKE9hOP2kaYzv6TyVvbl6KtMXQgv8E9sLmJn1ywwvrSm7Y2Co9bPA9JNN5F6jAePPbTmx0TMrusXI73h0ZzQ9yekJ427d0jqRG/FcX0TOQbakjREvnGhqf8i+SRF1LcO+qY46BCGkHNwzSkRsJLcUIlWWS21pWdNC1AKU9sXcMbIxOGOP5xEg25e4Qbf3Pq5u+dLc890jr5hafxVtPDg=
*/