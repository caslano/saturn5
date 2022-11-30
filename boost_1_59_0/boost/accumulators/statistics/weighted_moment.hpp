///////////////////////////////////////////////////////////////////////////////
// weighted_moment.hpp
//
//  Copyright 2006, Eric Niebler, Olivier Gygi. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MOMENT_HPP_EAN_15_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_WEIGHTED_MOMENT_HPP_EAN_15_11_2005

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/moment.hpp> // for pow()
#include <boost/accumulators/statistics/sum.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // weighted_moment_impl
    template<typename N, typename Sample, typename Weight>
    struct weighted_moment_impl
      : accumulator_base // TODO: also depends_on sum of powers
    {
        BOOST_MPL_ASSERT_RELATION(N::value, >, 0);
        typedef typename numeric::functional::multiplies<Sample, Weight>::result_type weighted_sample;
        // for boost::result_of
        typedef typename numeric::functional::fdiv<weighted_sample, Weight>::result_type result_type;

        template<typename Args>
        weighted_moment_impl(Args const &args)
          : sum(args[sample | Sample()] * numeric::one<Weight>::value)
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            this->sum += args[weight] * numeric::pow(args[sample], N());
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(this->sum, sum_of_weights(args));
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sum;
        }

    private:
        weighted_sample sum;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::weighted_moment
//
namespace tag
{
    template<int N>
    struct weighted_moment
      : depends_on<count, sum_of_weights>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::weighted_moment_impl<mpl::int_<N>, mpl::_1, mpl::_2> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::weighted_moment
//
namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, weighted_moment, (int))
}

using extract::weighted_moment;

}} // namespace boost::accumulators

#endif

/* weighted_moment.hpp
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
*/