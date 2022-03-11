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