///////////////////////////////////////////////////////////////////////////////
// tail_variate_means.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_TAIL_VARIATE_MEANS_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_TAIL_VARIATE_MEANS_HPP_DE_01_01_2006

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
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/accumulators/statistics/tail_variate.hpp>
#include <boost/accumulators/statistics/tail_mean.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>
#include <boost/serialization/vector.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif

namespace boost { namespace accumulators
{

namespace impl
{
    /**
        @brief Estimation of the absolute and relative tail variate means (for both left and right tails)

        For all \f$j\f$-th variates associated to the \f$\lceil n(1-\alpha)\rceil\f$ largest samples (or the
        \f$\lceil n(1-\alpha)\rceil\f$ smallest samples in case of the left tail), the absolute tail means
        \f$\widehat{ATM}_{n,\alpha}(X, j)\f$ are computed and returned as an iterator range. Alternatively,
        the relative tail means \f$\widehat{RTM}_{n,\alpha}(X, j)\f$ are returned, which are the absolute
        tail means normalized with the (non-coherent) sample tail mean \f$\widehat{NCTM}_{n,\alpha}(X)\f$.

        \f[
            \widehat{ATM}_{n,\alpha}^{\mathrm{right}}(X, j) =
                \frac{1}{\lceil n(1-\alpha) \rceil}
                \sum_{i=\lceil \alpha n \rceil}^n \xi_{j,i}
        \f]

        \f[
            \widehat{ATM}_{n,\alpha}^{\mathrm{left}}(X, j) =
                \frac{1}{\lceil n\alpha \rceil}
                \sum_{i=1}^{\lceil n\alpha \rceil} \xi_{j,i}
        \f]

        \f[
            \widehat{RTM}_{n,\alpha}^{\mathrm{right}}(X, j) =
                \frac{\sum_{i=\lceil n\alpha \rceil}^n \xi_{j,i}}
            {\lceil n(1-\alpha)\rceil\widehat{NCTM}_{n,\alpha}^{\mathrm{right}}(X)}
        \f]

        \f[
            \widehat{RTM}_{n,\alpha}^{\mathrm{left}}(X, j) =
                \frac{\sum_{i=1}^{\lceil n\alpha \rceil} \xi_{j,i}}
            {\lceil n\alpha\rceil\widehat{NCTM}_{n,\alpha}^{\mathrm{left}}(X)}
        \f]
    */

    ///////////////////////////////////////////////////////////////////////////////
    // tail_variate_means_impl
    //  by default: absolute tail_variate_means
    template<typename Sample, typename Impl, typename LeftRight, typename VariateTag>
    struct tail_variate_means_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<float_type> array_type;
        // for boost::result_of
        typedef iterator_range<typename array_type::iterator> result_type;

        tail_variate_means_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            std::size_t cnt = count(args);

            std::size_t n = static_cast<std::size_t>(
                std::ceil(
                    cnt * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] )
                )
            );

            std::size_t num_variates = tail_variate(args).begin()->size();

            this->tail_means_.clear();
            this->tail_means_.resize(num_variates, Sample(0));

            // If n is in a valid range, return result, otherwise return NaN or throw exception
            if (n < static_cast<std::size_t>(tail(args).size()))
            {
                this->tail_means_ = std::accumulate(
                    tail_variate(args).begin()
                  , tail_variate(args).begin() + n
                  , this->tail_means_
                  , numeric::plus
                );

                float_type factor = n * ( (is_same<Impl, relative>::value) ? non_coherent_tail_mean(args) : 1. );

                std::transform(
                    this->tail_means_.begin()
                  , this->tail_means_.end()
                  , this->tail_means_.begin()
#ifdef BOOST_NO_CXX98_BINDERS
                  , std::bind(std::divides<float_type>(), std::placeholders::_1, factor)
#else
                  , std::bind2nd(std::divides<float_type>(), factor)
#endif
                );
            }
            else
            {
                if (std::numeric_limits<float_type>::has_quiet_NaN)
                {
                    std::fill(
                        this->tail_means_.begin()
                      , this->tail_means_.end()
                      , std::numeric_limits<float_type>::quiet_NaN()
                    );
                }
                else
                {
                    std::ostringstream msg;
                    msg << "index n = " << n << " is not in valid range [0, " << tail(args).size() << ")";
                    boost::throw_exception(std::runtime_error(msg.str()));
                }
            }
            return make_iterator_range(this->tail_means_);
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & tail_means_;
        }

    private:

        mutable array_type tail_means_;

    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::absolute_tail_variate_means
// tag::relative_tail_variate_means
//
namespace tag
{
    template<typename LeftRight, typename VariateType, typename VariateTag>
    struct absolute_tail_variate_means
      : depends_on<count, non_coherent_tail_mean<LeftRight>, tail_variate<VariateType, VariateTag, LeftRight> >
    {
        typedef accumulators::impl::tail_variate_means_impl<mpl::_1, absolute, LeftRight, VariateTag> impl;
    };
    template<typename LeftRight, typename VariateType, typename VariateTag>
    struct relative_tail_variate_means
      : depends_on<count, non_coherent_tail_mean<LeftRight>, tail_variate<VariateType, VariateTag, LeftRight> >
    {
        typedef accumulators::impl::tail_variate_means_impl<mpl::_1, relative, LeftRight, VariateTag> impl;
    };
    struct abstract_absolute_tail_variate_means
      : depends_on<>
    {
    };
    struct abstract_relative_tail_variate_means
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::tail_variate_means
// extract::relative_tail_variate_means
//
namespace extract
{
    extractor<tag::abstract_absolute_tail_variate_means> const tail_variate_means = {};
    extractor<tag::abstract_relative_tail_variate_means> const relative_tail_variate_means = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail_variate_means)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(relative_tail_variate_means)
}

using extract::tail_variate_means;
using extract::relative_tail_variate_means;

// tail_variate_means<LeftRight, VariateType, VariateTag>(absolute) -> absolute_tail_variate_means<LeftRight, VariateType, VariateTag>
template<typename LeftRight, typename VariateType, typename VariateTag>
struct as_feature<tag::tail_variate_means<LeftRight, VariateType, VariateTag>(absolute)>
{
    typedef tag::absolute_tail_variate_means<LeftRight, VariateType, VariateTag> type;
};

// tail_variate_means<LeftRight, VariateType, VariateTag>(relative) ->relative_tail_variate_means<LeftRight, VariateType, VariateTag>
template<typename LeftRight, typename VariateType, typename VariateTag>
struct as_feature<tag::tail_variate_means<LeftRight, VariateType, VariateTag>(relative)>
{
    typedef tag::relative_tail_variate_means<LeftRight, VariateType, VariateTag> type;
};

// Provides non-templatized extractor
template<typename LeftRight, typename VariateType, typename VariateTag>
struct feature_of<tag::absolute_tail_variate_means<LeftRight, VariateType, VariateTag> >
  : feature_of<tag::abstract_absolute_tail_variate_means>
{
};

// Provides non-templatized extractor
template<typename LeftRight, typename VariateType, typename VariateTag>
struct feature_of<tag::relative_tail_variate_means<LeftRight, VariateType, VariateTag> >
  : feature_of<tag::abstract_relative_tail_variate_means>
{
};

// So that absolute_tail_means can be automatically substituted
// with absolute_weighted_tail_means when the weight parameter is non-void.
template<typename LeftRight, typename VariateType, typename VariateTag>
struct as_weighted_feature<tag::absolute_tail_variate_means<LeftRight, VariateType, VariateTag> >
{
    typedef tag::absolute_weighted_tail_variate_means<LeftRight, VariateType, VariateTag> type;
};

template<typename LeftRight, typename VariateType, typename VariateTag>
struct feature_of<tag::absolute_weighted_tail_variate_means<LeftRight, VariateType, VariateTag> >
  : feature_of<tag::absolute_tail_variate_means<LeftRight, VariateType, VariateTag> >
{
};

// So that relative_tail_means can be automatically substituted
// with relative_weighted_tail_means when the weight parameter is non-void.
template<typename LeftRight, typename VariateType, typename VariateTag>
struct as_weighted_feature<tag::relative_tail_variate_means<LeftRight, VariateType, VariateTag> >
{
    typedef tag::relative_weighted_tail_variate_means<LeftRight, VariateType, VariateTag> type;
};

template<typename LeftRight, typename VariateType, typename VariateTag>
struct feature_of<tag::relative_weighted_tail_variate_means<LeftRight, VariateType, VariateTag> >
  : feature_of<tag::relative_tail_variate_means<LeftRight, VariateType, VariateTag> >
{
};

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* tail_variate_means.hpp
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
*/