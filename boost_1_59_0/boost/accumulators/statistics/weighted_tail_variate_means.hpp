///////////////////////////////////////////////////////////////////////////////
// weighted_tail_variate_means.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_TAIL_VARIATE_MEANS_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_TAIL_VARIATE_MEANS_HPP_DE_01_01_2006

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
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/tail.hpp>
#include <boost/accumulators/statistics/tail_variate.hpp>
#include <boost/accumulators/statistics/tail_variate_means.hpp>
#include <boost/accumulators/statistics/weighted_tail_mean.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif

namespace boost
{
    // for _BinaryOperatrion2 in std::inner_product below
    // multiplies two values and promotes the result to double
    namespace numeric { namespace functional
    {
        ///////////////////////////////////////////////////////////////////////////////
        // numeric::functional::multiply_and_promote_to_double
        template<typename T, typename U>
        struct multiply_and_promote_to_double
          : multiplies<T, double const>
        {
        };
    }}
}

namespace boost { namespace accumulators
{

namespace impl
{
    /**
        @brief Estimation of the absolute and relative weighted tail variate means (for both left and right tails)

        For all \f$j\f$-th variates associated to the

        \f[
            \lambda = \inf\left\{ l \left| \frac{1}{\bar{w}_n}\sum_{i=1}^{l} w_i \geq \alpha \right. \right\}
        \f]

        smallest samples (left tail) or the weighted mean of the

        \f[
            n + 1 - \rho = n + 1 - \sup\left\{ r \left| \frac{1}{\bar{w}_n}\sum_{i=r}^{n} w_i \geq (1 - \alpha) \right. \right\}
        \f]

        largest samples (right tail), the absolute weighted tail means \f$\widehat{ATM}_{n,\alpha}(X, j)\f$
        are computed and returned as an iterator range. Alternatively, the relative weighted tail means
        \f$\widehat{RTM}_{n,\alpha}(X, j)\f$ are returned, which are the absolute weighted tail means
        normalized with the weighted (non-coherent) sample tail mean \f$\widehat{NCTM}_{n,\alpha}(X)\f$.

        \f[
            \widehat{ATM}_{n,\alpha}^{\mathrm{right}}(X, j) =
                \frac{1}{\sum_{i=\rho}^n w_i}
                \sum_{i=\rho}^n w_i \xi_{j,i}
        \f]

        \f[
            \widehat{ATM}_{n,\alpha}^{\mathrm{left}}(X, j) =
                \frac{1}{\sum_{i=1}^{\lambda}}
                \sum_{i=1}^{\lambda} w_i \xi_{j,i}
        \f]

        \f[
            \widehat{RTM}_{n,\alpha}^{\mathrm{right}}(X, j) =
                \frac{\sum_{i=\rho}^n w_i \xi_{j,i}}
            {\sum_{i=\rho}^n w_i \widehat{NCTM}_{n,\alpha}^{\mathrm{right}}(X)}
        \f]

        \f[
            \widehat{RTM}_{n,\alpha}^{\mathrm{left}}(X, j) =
                \frac{\sum_{i=1}^{\lambda} w_i \xi_{j,i}}
            {\sum_{i=1}^{\lambda} w_i \widehat{NCTM}_{n,\alpha}^{\mathrm{left}}(X)}
        \f]
    */

    ///////////////////////////////////////////////////////////////////////////////
    // weighted_tail_variate_means_impl
    //  by default: absolute weighted_tail_variate_means
    template<typename Sample, typename Weight, typename Impl, typename LeftRight, typename VariateType>
    struct weighted_tail_variate_means_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Weight, Weight>::result_type float_type;
        typedef typename numeric::functional::fdiv<typename numeric::functional::multiplies<VariateType, Weight>::result_type, Weight>::result_type array_type;
        // for boost::result_of
        typedef iterator_range<typename array_type::iterator> result_type;

        weighted_tail_variate_means_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            float_type threshold = sum_of_weights(args)
                             * ( ( is_same<LeftRight, left>::value ) ? args[quantile_probability] : 1. - args[quantile_probability] );

            std::size_t n = 0;
            Weight sum = Weight(0);

            while (sum < threshold)
            {
                if (n < static_cast<std::size_t>(tail_weights(args).size()))
                {
                    sum += *(tail_weights(args).begin() + n);
                    n++;
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
            }

            std::size_t num_variates = tail_variate(args).begin()->size();

            this->tail_means_.clear();
            this->tail_means_.resize(num_variates, Sample(0));

            this->tail_means_ = std::inner_product(
                tail_variate(args).begin()
              , tail_variate(args).begin() + n
              , tail_weights(args).begin()
              , this->tail_means_
              , numeric::functional::plus<array_type const, array_type const>()
              , numeric::functional::multiply_and_promote_to_double<VariateType const, Weight const>()
            );

            float_type factor = sum * ( (is_same<Impl, relative>::value) ? non_coherent_weighted_tail_mean(args) : 1. );

            std::transform(
                this->tail_means_.begin()
              , this->tail_means_.end()
              , this->tail_means_.begin()
#ifdef BOOST_NO_CXX98_BINDERS
              , std::bind(numeric::functional::divides<typename array_type::value_type const, float_type const>(), std::placeholders::_1, factor)
#else
              , std::bind2nd(numeric::functional::divides<typename array_type::value_type const, float_type const>(), factor)
#endif
            );

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
// tag::absolute_weighted_tail_variate_means
// tag::relative_weighted_tail_variate_means
//
namespace tag
{
    template<typename LeftRight, typename VariateType, typename VariateTag>
    struct absolute_weighted_tail_variate_means
      : depends_on<non_coherent_weighted_tail_mean<LeftRight>, tail_variate<VariateType, VariateTag, LeftRight>, tail_weights<LeftRight> >
    {
        typedef accumulators::impl::weighted_tail_variate_means_impl<mpl::_1, mpl::_2, absolute, LeftRight, VariateType> impl;
    };
    template<typename LeftRight, typename VariateType, typename VariateTag>
    struct relative_weighted_tail_variate_means
      : depends_on<non_coherent_weighted_tail_mean<LeftRight>, tail_variate<VariateType, VariateTag, LeftRight>, tail_weights<LeftRight> >
    {
        typedef accumulators::impl::weighted_tail_variate_means_impl<mpl::_1, mpl::_2, relative, LeftRight, VariateType> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_tail_variate_means
// extract::relative_weighted_tail_variate_means
//
namespace extract
{
    extractor<tag::abstract_absolute_tail_variate_means> const weighted_tail_variate_means = {};
    extractor<tag::abstract_relative_tail_variate_means> const relative_weighted_tail_variate_means = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_tail_variate_means)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(relative_weighted_tail_variate_means)
}

using extract::weighted_tail_variate_means;
using extract::relative_weighted_tail_variate_means;

// weighted_tail_variate_means<LeftRight, VariateType, VariateTag>(absolute) -> absolute_weighted_tail_variate_means<LeftRight, VariateType, VariateTag>
template<typename LeftRight, typename VariateType, typename VariateTag>
struct as_feature<tag::weighted_tail_variate_means<LeftRight, VariateType, VariateTag>(absolute)>
{
    typedef tag::absolute_weighted_tail_variate_means<LeftRight, VariateType, VariateTag> type;
};

// weighted_tail_variate_means<LeftRight, VariateType, VariateTag>(relative) -> relative_weighted_tail_variate_means<LeftRight, VariateType, VariateTag>
template<typename LeftRight, typename VariateType, typename VariateTag>
struct as_feature<tag::weighted_tail_variate_means<LeftRight, VariateType, VariateTag>(relative)>
{
    typedef tag::relative_weighted_tail_variate_means<LeftRight, VariateType, VariateTag> type;
};

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* weighted_tail_variate_means.hpp
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
*/