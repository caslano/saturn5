///////////////////////////////////////////////////////////////////////////////
// covariance.hpp
//
//  Copyright 2006 Daniel Egloff, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_COVARIANCE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_COVARIANCE_HPP_DE_01_01_2006

#include <vector>
#include <limits>
#include <numeric>
#include <functional>
#include <complex>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/range.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/mean.hpp>

namespace boost { namespace numeric
{
    namespace functional
    {
        struct std_vector_tag;

        ///////////////////////////////////////////////////////////////////////////////
        // functional::outer_product
        template<typename Left, typename Right, typename EnableIf = void>
        struct outer_product_base
          : functional::multiplies<Left, Right>
        {};

        template<typename Left, typename Right, typename LeftTag = typename tag<Left>::type, typename RightTag = typename tag<Right>::type>
        struct outer_product
          : outer_product_base<Left, Right, void>
        {};

        template<typename Left, typename Right>
        struct outer_product<Left, Right, std_vector_tag, std_vector_tag>
        {
            typedef Left first_argument_type;
            typedef Right second_argument_type;
            typedef
                ublas::matrix<
                    typename functional::multiplies<
                        typename Left::value_type
                      , typename Right::value_type
                    >::result_type
                >
            result_type;

            result_type
            operator ()(Left & left, Right & right) const
            {
                std::size_t left_size = left.size();
                std::size_t right_size = right.size();
                result_type result(left_size, right_size);
                for (std::size_t i = 0; i < left_size; ++i)
                    for (std::size_t j = 0; j < right_size; ++j)
                        result(i,j) = numeric::multiplies(left[i], right[j]);
                return result;
            }
        };
    }

    namespace op
    {
        struct outer_product
          : boost::detail::function2<functional::outer_product<_1, _2, functional::tag<_1>, functional::tag<_2> > >
        {};
    }

    namespace
    {
        op::outer_product const &outer_product = boost::detail::pod_singleton<op::outer_product>::instance;
    }

}}

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // covariance_impl
    //
    /**
        @brief Covariance Estimator

        An iterative Monte Carlo estimator for the covariance \f$\mathrm{Cov}(X,X')\f$, where \f$X\f$ is a sample
        and \f$X'\f$ is a variate, is given by:

        \f[
            \hat{c}_n = \frac{n-1}{n} \hat{c}_{n-1} + \frac{1}{n-1}(X_n - \hat{\mu}_n)(X_n' - \hat{\mu}_n'),\quad n\ge2,\quad\hat{c}_1 = 0,
        \f]

        \f$\hat{\mu}_n\f$ and \f$\hat{\mu}_n'\f$ being the means of the samples and variates.
    */
    template<typename Sample, typename VariateType, typename VariateTag>
    struct covariance_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type sample_type;
        typedef typename numeric::functional::fdiv<VariateType, std::size_t>::result_type variate_type;
        // for boost::result_of
        typedef typename numeric::functional::outer_product<sample_type, variate_type>::result_type result_type;

        template<typename Args>
        covariance_impl(Args const &args)
          : cov_(
                numeric::outer_product(
                    numeric::fdiv(args[sample | Sample()], (std::size_t)1)
                  , numeric::fdiv(args[parameter::keyword<VariateTag>::get() | VariateType()], (std::size_t)1)
                )
            )
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            std::size_t cnt = count(args);

            if (cnt > 1)
            {
                extractor<tag::mean_of_variates<VariateType, VariateTag> > const some_mean_of_variates = {};

                this->cov_ = this->cov_*(cnt-1.)/cnt
                           + numeric::outer_product(
                                 some_mean_of_variates(args) - args[parameter::keyword<VariateTag>::get()]
                               , mean(args) - args[sample]
                             ) / (cnt-1.);
            }
        }

        result_type result(dont_care) const
        {
            return this->cov_;
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & cov_;
        }

    private:
        result_type cov_;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::covariance
//
namespace tag
{
    template<typename VariateType, typename VariateTag>
    struct covariance
      : depends_on<count, mean, mean_of_variates<VariateType, VariateTag> >
    {
        typedef accumulators::impl::covariance_impl<mpl::_1, VariateType, VariateTag> impl;
    };

    struct abstract_covariance
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::covariance
//
namespace extract
{
    extractor<tag::abstract_covariance> const covariance = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(covariance)
}

using extract::covariance;

template<typename VariateType, typename VariateTag>
struct feature_of<tag::covariance<VariateType, VariateTag> >
  : feature_of<tag::abstract_covariance>
{
};

// So that covariance can be automatically substituted with
// weighted_covariance when the weight parameter is non-void.
template<typename VariateType, typename VariateTag>
struct as_weighted_feature<tag::covariance<VariateType, VariateTag> >
{
    typedef tag::weighted_covariance<VariateType, VariateTag> type;
};

template<typename VariateType, typename VariateTag>
struct feature_of<tag::weighted_covariance<VariateType, VariateTag> >
  : feature_of<tag::covariance<VariateType, VariateTag> >
{};

}} // namespace boost::accumulators

#endif

/* covariance.hpp
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
*/