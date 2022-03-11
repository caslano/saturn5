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