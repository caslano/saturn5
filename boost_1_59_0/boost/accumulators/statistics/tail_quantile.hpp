///////////////////////////////////////////////////////////////////////////////
// tail_quantile.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_TAIL_QUANTILE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_TAIL_QUANTILE_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <boost/config/no_tr1/cmath.hpp>             // For ceil
#include <boost/throw_exception.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/accumulators/statistics/count.hpp>
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
    // tail_quantile_impl
    //  Tail quantile estimation based on order statistics
    /**
        @brief Tail quantile estimation based on order statistics (for both left and right tails)

        The estimation of a tail quantile \f$\hat{q}\f$ with level \f$\alpha\f$ based on order statistics requires the
        caching of at least the \f$\lceil n\alpha\rceil\f$ smallest or the \f$\lceil n(1-\alpha)\rceil\f$ largest samples,
        \f$n\f$ being the total number of samples. The largest of the \f$\lceil n\alpha\rceil\f$ smallest samples or the
        smallest of the \f$\lceil n(1-\alpha)\rceil\f$ largest samples provides an estimate for the quantile:

        \f[
            \hat{q}_{n,\alpha} = X_{\lceil \alpha n \rceil:n}
        \f]

        @param quantile_probability
    */
    template<typename Sample, typename LeftRight>
    struct tail_quantile_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef Sample result_type;

        tail_quantile_impl(dont_care) {}

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
            if ( n < static_cast<std::size_t>(tail(args).size()))
            {
               // Note that the cached samples of the left are sorted in ascending order,
               // whereas the samples of the right tail are sorted in descending order
               return *(boost::begin(tail(args)) + n - 1);
            }
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
// tag::tail_quantile<>
//
namespace tag
{
    template<typename LeftRight>
    struct tail_quantile
      : depends_on<count, tail<LeftRight> >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::tail_quantile_impl<mpl::_1, LeftRight> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::tail_quantile
//
namespace extract
{
    extractor<tag::quantile> const tail_quantile = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail_quantile)
}

using extract::tail_quantile;

// for the purposes of feature-based dependency resolution,
// tail_quantile<LeftRight> provide the same feature as quantile
template<typename LeftRight>
struct feature_of<tag::tail_quantile<LeftRight> >
  : feature_of<tag::quantile>
{
};

// So that tail_quantile can be automatically substituted with
// weighted_tail_quantile when the weight parameter is non-void.
template<typename LeftRight>
struct as_weighted_feature<tag::tail_quantile<LeftRight> >
{
    typedef tag::weighted_tail_quantile<LeftRight> type;
};

template<typename LeftRight>
struct feature_of<tag::weighted_tail_quantile<LeftRight> >
  : feature_of<tag::tail_quantile<LeftRight> >
{};

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* tail_quantile.hpp
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
*/