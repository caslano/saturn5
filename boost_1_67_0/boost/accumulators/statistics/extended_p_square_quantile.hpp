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
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
*/