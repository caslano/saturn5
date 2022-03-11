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