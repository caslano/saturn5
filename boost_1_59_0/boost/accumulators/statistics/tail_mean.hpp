///////////////////////////////////////////////////////////////////////////////
// tail_mean.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_TAIL_MEAN_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_TAIL_MEAN_HPP_DE_01_01_2006

#include <numeric>
#include <vector>
#include <limits>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/accumulators/statistics/tail_quantile.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif

namespace boost { namespace accumulators
{

namespace impl
{

    ///////////////////////////////////////////////////////////////////////////////
    // coherent_tail_mean_impl
    //
    /**
        @brief Estimation of the coherent tail mean based on order statistics (for both left and right tails)

        The coherent tail mean \f$\widehat{CTM}_{n,\alpha}(X)\f$ is equal to the non-coherent tail mean \f$\widehat{NCTM}_{n,\alpha}(X)\f$
        plus a correction term that ensures coherence in case of non-continuous distributions.

        \f[
            \widehat{CTM}_{n,\alpha}^{\mathrm{right}}(X) = \widehat{NCTM}_{n,\alpha}^{\mathrm{right}}(X) +
            \frac{1}{\lceil n(1-\alpha)\rceil}\hat{q}_{n,\alpha}(X)\left(1 - \alpha - \frac{1}{n}\lceil n(1-\alpha)\rceil \right)
        \f]

        \f[
            \widehat{CTM}_{n,\alpha}^{\mathrm{left}}(X) = \widehat{NCTM}_{n,\alpha}^{\mathrm{left}}(X) +
            \frac{1}{\lceil n\alpha\rceil}\hat{q}_{n,\alpha}(X)\left(\alpha - \frac{1}{n}\lceil n\alpha\rceil \right)
        \f]
    */
    template<typename Sample, typename LeftRight>
    struct coherent_tail_mean_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef float_type result_type;

        coherent_tail_mean_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            std::size_t cnt = count(args);

            std::size_t n = static_cast<std::size_t>(
                std::ceil(
                    cnt * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] )
                )
            );

            extractor<tag::non_coherent_tail_mean<LeftRight> > const some_non_coherent_tail_mean = {};

            return some_non_coherent_tail_mean(args)
                 + numeric::fdiv(quantile(args), n)
                 * (
                     ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability]
                     - numeric::fdiv(n, count(args))
                   );
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

    ///////////////////////////////////////////////////////////////////////////////
    // non_coherent_tail_mean_impl
    //
    /**
        @brief Estimation of the (non-coherent) tail mean based on order statistics (for both left and right tails)

        An estimation of the non-coherent tail mean \f$\widehat{NCTM}_{n,\alpha}(X)\f$ is given by the mean of the
        \f$\lceil n\alpha\rceil\f$ smallest samples (left tail) or the mean of the  \f$\lceil n(1-\alpha)\rceil\f$
        largest samples (right tail), \f$n\f$ being the total number of samples and \f$\alpha\f$ the quantile level:

        \f[
            \widehat{NCTM}_{n,\alpha}^{\mathrm{right}}(X) = \frac{1}{\lceil n(1-\alpha)\rceil} \sum_{i=\lceil \alpha n \rceil}^n X_{i:n}
        \f]

        \f[
            \widehat{NCTM}_{n,\alpha}^{\mathrm{left}}(X) = \frac{1}{\lceil n\alpha\rceil} \sum_{i=1}^{\lceil \alpha n \rceil} X_{i:n}
        \f]

        It thus requires the caching of at least the \f$\lceil n\alpha\rceil\f$ smallest or the \f$\lceil n(1-\alpha)\rceil\f$
        largest samples.

        @param quantile_probability
    */
    template<typename Sample, typename LeftRight>
    struct non_coherent_tail_mean_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        // for boost::result_of
        typedef float_type result_type;

        non_coherent_tail_mean_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            std::size_t cnt = count(args);

            std::size_t n = static_cast<std::size_t>(
                std::ceil(
                    cnt * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] )
                )
            );

            // If n is in a valid range, return result, otherwise return NaN or throw exception
            if (n <= static_cast<std::size_t>(tail(args).size()))
                return numeric::fdiv(
                    std::accumulate(
                        tail(args).begin()
                      , tail(args).begin() + n
                      , Sample(0)
                    )
                  , n
                );
            else
            {
                if (std::numeric_limits<result_type>::has_quiet_NaN)
                {
                    return std::numeric_limits<result_type>::quiet_NaN();
                }
                else
                {
                    std::ostringstream msg;
                    msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                    boost::throw_exception(std::runtime_error(msg.str()));
                    return Sample(0);
                }
            }
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

} // namespace impl


///////////////////////////////////////////////////////////////////////////////
// tag::coherent_tail_mean<>
// tag::non_coherent_tail_mean<>
//
namespace tag
{
    template<typename LeftRight>
    struct coherent_tail_mean
      : depends_on<count, quantile, non_coherent_tail_mean<LeftRight> >
    {
        typedef accumulators::impl::coherent_tail_mean_impl<mpl::_1, LeftRight> impl;
    };

    template<typename LeftRight>
    struct non_coherent_tail_mean
      : depends_on<count, tail<LeftRight> >
    {
        typedef accumulators::impl::non_coherent_tail_mean_impl<mpl::_1, LeftRight> impl;
    };

    struct abstract_non_coherent_tail_mean
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::non_coherent_tail_mean;
// extract::coherent_tail_mean;
//
namespace extract
{
    extractor<tag::abstract_non_coherent_tail_mean> const non_coherent_tail_mean = {};
    extractor<tag::tail_mean> const coherent_tail_mean = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(non_coherent_tail_mean)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(coherent_tail_mean)
}

using extract::non_coherent_tail_mean;
using extract::coherent_tail_mean;

// for the purposes of feature-based dependency resolution,
// coherent_tail_mean<LeftRight> provides the same feature as tail_mean
template<typename LeftRight>
struct feature_of<tag::coherent_tail_mean<LeftRight> >
  : feature_of<tag::tail_mean>
{
};

template<typename LeftRight>
struct feature_of<tag::non_coherent_tail_mean<LeftRight> >
  : feature_of<tag::abstract_non_coherent_tail_mean>
{
};

// So that non_coherent_tail_mean can be automatically substituted
// with weighted_non_coherent_tail_mean when the weight parameter is non-void.
template<typename LeftRight>
struct as_weighted_feature<tag::non_coherent_tail_mean<LeftRight> >
{
    typedef tag::non_coherent_weighted_tail_mean<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::non_coherent_weighted_tail_mean<LeftRight> >
  : feature_of<tag::non_coherent_tail_mean<LeftRight> >
{};

// NOTE that non_coherent_tail_mean cannot be feature-grouped with tail_mean,
// which is the base feature for coherent tail means, since (at least for
// non-continuous distributions) non_coherent_tail_mean is a different measure!

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* tail_mean.hpp
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
*/