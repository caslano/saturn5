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
+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
*/