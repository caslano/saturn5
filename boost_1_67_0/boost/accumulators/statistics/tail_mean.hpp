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