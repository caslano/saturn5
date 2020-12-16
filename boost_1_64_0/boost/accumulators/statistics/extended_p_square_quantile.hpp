///////////////////////////////////////////////////////////////////////////////
// extended_p_square_quantile.hpp
//
//  Copyright 2005 Daniel Egloff. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_EXTENDED_SINGLE_QUANTILE_HPP_DE_01_01_2006
#define BOOST_ACCUMULATORS_STATISTICS_EXTENDED_SINGLE_QUANTILE_HPP_DE_01_01_2006

#include <vector>
#include <functional>
#include <boost/throw_exception.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/permutation_iterator.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/parameters/quantile_probability.hpp>
#include <boost/accumulators/statistics/extended_p_square.hpp>
#include <boost/accumulators/statistics/weighted_extended_p_square.hpp>
#include <boost/accumulators/statistics/times2_iterator.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
#endif

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // extended_p_square_quantile_impl
    //  single quantile estimation
    /**
        @brief Quantile estimation using the extended \f$P^2\f$ algorithm for weighted and unweighted samples

        Uses the quantile estimates calculated by the extended \f$P^2\f$ algorithm to compute
        intermediate quantile estimates by means of quadratic interpolation.

        @param quantile_probability The probability of the quantile to be estimated.
    */
    template<typename Sample, typename Impl1, typename Impl2> // Impl1: weighted/unweighted // Impl2: linear/quadratic
    struct extended_p_square_quantile_impl
      : accumulator_base
    {
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type float_type;
        typedef std::vector<float_type> array_type;
        typedef iterator_range<
            detail::lvalue_index_iterator<
                permutation_iterator<
                    typename array_type::const_iterator
                  , detail::times2_iterator
                >
            >
        > range_type;
        // for boost::result_of
        typedef float_type result_type;

        template<typename Args>
        extended_p_square_quantile_impl(Args const &args)
          : probabilities(
                boost::begin(args[extended_p_square_probabilities])
              , boost::end(args[extended_p_square_probabilities])
            )
        {
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            typedef
                typename mpl::if_<
                    is_same<Impl1, weighted>
                  , tag::weighted_extended_p_square
                  , tag::extended_p_square
                >::type
            extended_p_square_tag;

            extractor<extended_p_square_tag> const some_extended_p_square = {};

            array_type heights(some_extended_p_square(args).size());
            std::copy(some_extended_p_square(args).begin(), some_extended_p_square(args).end(), heights.begin());

            this->probability = args[quantile_probability];

            typename array_type::const_iterator iter_probs = std::lower_bound(this->probabilities.begin(), this->probabilities.end(), this->probability);
            std::size_t dist = std::distance(this->probabilities.begin(), iter_probs);
            typename array_type::const_iterator iter_heights = heights.begin() + dist;

            // If this->probability is not in a valid range return NaN or throw exception
            if (this->probability < *this->probabilities.begin() || this->probability > *(this->probabilities.end() - 1))
            {
                if (std::numeric_limits<result_type>::has_quiet_NaN)
                {
                    return std::numeric_limits<result_type>::quiet_NaN();
                }
                else
                {
                    std::ostringstream msg;
                    msg << "probability = " << this->probability << " is not in valid range (";
                    msg << *this->probabilities.begin() << ", " << *(this->probabilities.end() - 1) << ")";
                    boost::throw_exception(std::runtime_error(msg.str()));
                    return Sample(0);
                }

            }

            if (*iter_probs == this->probability)
            {
                return heights[dist];
            }
            else
            {
                result_type res;

                if (is_same<Impl2, linear>::value)
                {
                    /////////////////////////////////////////////////////////////////////////////////
                    // LINEAR INTERPOLATION
                    //
                    float_type p1 = *iter_probs;
                    float_type p0 = *(iter_probs - 1);
                    float_type h1 = *iter_heights;
                    float_type h0 = *(iter_heights - 1);

                    float_type a = numeric::fdiv(h1 - h0, p1 - p0);
                    float_type b = h1 - p1 * a;

                    res = a * this->probability + b;
                }
                else
                {
                    /////////////////////////////////////////////////////////////////////////////////
                    // QUADRATIC INTERPOLATION
                    //
                    float_type p0, p1, p2;
                    float_type h0, h1, h2;

                    if ( (dist == 1 || *iter_probs - this->probability <= this->probability - *(iter_probs - 1) ) && dist != this->probabilities.size() - 1 )
                    {
                        p0 = *(iter_probs - 1);
                        p1 = *iter_probs;
                        p2 = *(iter_probs + 1);
                        h0 = *(iter_heights - 1);
                        h1 = *iter_heights;
                        h2 = *(iter_heights + 1);
                    }
                    else
                    {
                        p0 = *(iter_probs - 2);
                        p1 = *(iter_probs - 1);
                        p2 = *iter_probs;
                        h0 = *(iter_heights - 2);
                        h1 = *(iter_heights - 1);
                        h2 = *iter_heights;
                    }

                    float_type hp21 = numeric::fdiv(h2 - h1, p2 - p1);
                    float_type hp10 = numeric::fdiv(h1 - h0, p1 - p0);
                    float_type p21  = numeric::fdiv(p2 * p2 - p1 * p1, p2 - p1);
                    float_type p10  = numeric::fdiv(p1 * p1 - p0 * p0, p1 - p0);

                    float_type a = numeric::fdiv(hp21 - hp10, p21 - p10);
                    float_type b = hp21 - a * p21;
                    float_type c = h2 - a * p2 * p2 - b * p2;

                    res = a * this->probability * this-> probability + b * this->probability + c;
                }

                return res;
            }

        }

    public:
        // make this accumulator serializeable
        // TODO: do we need to split to load/save and verify that the parameters did not change?
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & probabilities;
            ar & probability;
        }

    private:

        array_type probabilities;
        mutable float_type probability;

    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::extended_p_square_quantile
//
namespace tag
{
    struct extended_p_square_quantile
      : depends_on<extended_p_square>
    {
        typedef accumulators::impl::extended_p_square_quantile_impl<mpl::_1, unweighted, linear> impl;
    };
    struct extended_p_square_quantile_quadratic
      : depends_on<extended_p_square>
    {
        typedef accumulators::impl::extended_p_square_quantile_impl<mpl::_1, unweighted, quadratic> impl;
    };
    struct weighted_extended_p_square_quantile
      : depends_on<weighted_extended_p_square>
    {
        typedef accumulators::impl::extended_p_square_quantile_impl<mpl::_1, weighted, linear> impl;
    };
    struct weighted_extended_p_square_quantile_quadratic
      : depends_on<weighted_extended_p_square>
    {
        typedef accumulators::impl::extended_p_square_quantile_impl<mpl::_1, weighted, quadratic> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::extended_p_square_quantile
// extract::weighted_extended_p_square_quantile
//
namespace extract
{
    extractor<tag::extended_p_square_quantile> const extended_p_square_quantile = {};
    extractor<tag::extended_p_square_quantile_quadratic> const extended_p_square_quantile_quadratic = {};
    extractor<tag::weighted_extended_p_square_quantile> const weighted_extended_p_square_quantile = {};
    extractor<tag::weighted_extended_p_square_quantile_quadratic> const weighted_extended_p_square_quantile_quadratic = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(extended_p_square_quantile)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(extended_p_square_quantile_quadratic)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_extended_p_square_quantile)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(weighted_extended_p_square_quantile_quadratic)
}

using extract::extended_p_square_quantile;
using extract::extended_p_square_quantile_quadratic;
using extract::weighted_extended_p_square_quantile;
using extract::weighted_extended_p_square_quantile_quadratic;

// extended_p_square_quantile(linear) -> extended_p_square_quantile
template<>
struct as_feature<tag::extended_p_square_quantile(linear)>
{
    typedef tag::extended_p_square_quantile type;
};

// extended_p_square_quantile(quadratic) -> extended_p_square_quantile_quadratic
template<>
struct as_feature<tag::extended_p_square_quantile(quadratic)>
{
    typedef tag::extended_p_square_quantile_quadratic type;
};

// weighted_extended_p_square_quantile(linear) -> weighted_extended_p_square_quantile
template<>
struct as_feature<tag::weighted_extended_p_square_quantile(linear)>
{
    typedef tag::weighted_extended_p_square_quantile type;
};

// weighted_extended_p_square_quantile(quadratic) -> weighted_extended_p_square_quantile_quadratic
template<>
struct as_feature<tag::weighted_extended_p_square_quantile(quadratic)>
{
    typedef tag::weighted_extended_p_square_quantile_quadratic type;
};

// for the purposes of feature-based dependency resolution,
// extended_p_square_quantile and weighted_extended_p_square_quantile
// provide the same feature as quantile
template<>
struct feature_of<tag::extended_p_square_quantile>
  : feature_of<tag::quantile>
{
};
template<>
struct feature_of<tag::extended_p_square_quantile_quadratic>
  : feature_of<tag::quantile>
{
};
// So that extended_p_square_quantile can be automatically substituted with
// weighted_extended_p_square_quantile when the weight parameter is non-void
template<>
struct as_weighted_feature<tag::extended_p_square_quantile>
{
    typedef tag::weighted_extended_p_square_quantile type;
};

template<>
struct feature_of<tag::weighted_extended_p_square_quantile>
  : feature_of<tag::extended_p_square_quantile>
{
};

// So that extended_p_square_quantile_quadratic can be automatically substituted with
// weighted_extended_p_square_quantile_quadratic when the weight parameter is non-void
template<>
struct as_weighted_feature<tag::extended_p_square_quantile_quadratic>
{
    typedef tag::weighted_extended_p_square_quantile_quadratic type;
};
template<>
struct feature_of<tag::weighted_extended_p_square_quantile_quadratic>
  : feature_of<tag::extended_p_square_quantile_quadratic>
{
};

}} // namespace boost::accumulators

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* extended_p_square_quantile.hpp
5ix1XbMQ9/UVsVb04nXAFr64/ZDmJ22PTvJn9XSY8Hj1Sq7Dy/H958qsJZk0MflqopV8BZKLJTlWjf2QQdXn49DW0mBJK5MlbFTH1PctBl8pvzMloK6CT2vO1OD/v75G5S7Ru8X0HlVEC9CT5Mqf6CAmIp45bqiS4l8KCfSyqOuDXPnTZTmkFcmC7YpOUjbWGKjskEBufWgjvW4EmEWE/H9IqZwp5NT5tB0XVNR/qacvWQrTeFk9jCsRe3qvSukDlZluuCKrWU/N6oXm+wdeY95rvD4/EW3pmAhaST17lFxEtkRwnm7hgUpK6jqf05Pq8NX3GBtk1n9JmRvxO+xbSO42Soh1+Goi1gvVqh9LT6mtWC1/mN1H06yR0TaaVUXUEW6TczxUKHIOHrblwdKa9Th1/wWy12iUYTyxy9756+Qlfv2StmRmLHWbL8aTGuara+vxjaEe3yM9ji2kHi9QW3ALifPsaXVZ2jOtrk0eNQKUkuhP5miqLiucry+25fV9GlU9vwok+tYfTMzy8bJDwWjzza0oak1CJhT5AUXUFfa8G3z1eTLWRpB10vZ+VMeGv3w7/s45Jf7ahPA3RvC37T3C31Pqoe9PPWPM88ugOjWcXzbI+cUbW1b5/JK+PnR+eSP+V+g2m/Ozm56fW6Mqzk+ZlrYDx9GVQkieO6dGzWI9/lGh8X+YxCbmFuQjjD0XTlvQk8DUX1fqLWj4kUpTwKenwEsyBe5fyVPgMIqpy4/UfruqoX1fR9raRxTe3IKboR6q9me6qnzbvgUXHq7QwgRK5awOMc37ybvcwqXgp19Rjxz+tU2U9vWq2j7BXzY/jGP8zSd7wO9q/J1/uBL+ss3nZYK/q6R1R1BMHT30axtnte/5iFD7Zq4Kq6JhmSA4KX4HZGy7qUE78VAlDG43X4VL7sff4TbOYQxec6j016hjmvyPrX2T1iHGJEFjqb7LIpgEbcrr+wSqbYtq1ZcHK+FvrG7bFdK2X1Zw2w6hiHr7YGkthec1tu+WcBv+tlH7+FAxTlfaTyqdKZVuzOv7uOpRqYFW3gGS9wbJe5DyNj/463AXat8ah619+6z25eg6b5U6VQHXuSGv7zy16EDF9ll5b5e870jeA5R37IFf377K5zPxh9RM2qsvvfE/UtjPRKOhucIeqZezml8E1EJkTRFPT7lz5FVqni6XYPlCiqcVV1/9zaH9H+FavVZ+kMzzYm6YnZ63p/e0y4W0dKDVm+kxGd/bvgud//i8kZNJJ8Z7K+oq37+ctpS5wOB6dbmthCu/s01beyhyLWcG6oaNFU6MV+u6u3Dd95onxgMllU+MRl0W8kcEMzPJDIIrP0Uo/y/5QvlfbvZPPvNp+geWxzq/5JjEbwJ1YTYTv7+gU7fla+LXvqTS3JugkfeYIC8tn+feNyimfvr29IifXX7+6gmzVeLCBvNopqbNF6Oa3W8LkrfR3rEcCbRvcAOnodIqUvTOlIcLfBQu9O/tkHbHYjWwchkWlrOOKX3Fi55HVyhxaB2MNnGssNjVArtXwPawgX1d/YTr/6qCaw6bMvrfrFNUE/5G/lIj/i7E8N7HT/55eB9Bux9Ypoe3DzW56h3EfbqbK6Sb1yM7CqKTAdUsUBvcXRLC3ZfNGXeXWECLBGgdC+ghtUr9azFnXw+X/hxaD2mjzM1sIrV0kvDTRXl9Z5M94LecOBCqSuthou7VVOlVEjKhyH4UUd9+c3qbmel/71lIDIVj9pKS2BMKkTh6MqXb9qYshLERRG2yhNI1VhO5KvG4BzoM3rLJrQ97jMh13tRYX3N4TANDP/qQx9ho+uXDTXjBTN308bKN+N6kAZmJ1u9VnRneKT344Vdlv/g=
*/