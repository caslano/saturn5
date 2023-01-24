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
19n9CNZuunj2+wCB1zhLWCj59AfatILuw0sSWKmUiKn0BCm9l5SeKKX3k4wSkYzptpp0K9gbKd0upcfLFVWXOViUuvzWwSL8KkTlyFlRc9B71kCTwQ4SOY2SHBz405Em+FWKh8fR+X04WIF/O+SEtPW3WyJxh72xwjYYaaRo44rZmPHX1dBW5y7TPKyD4ba8X9oKEBoviRsuAJW9c4HjueGPttAbFF+lxBSXUqjbOEpiyQXGVuv6DgxT6boL7MPhKEpvRVElAaseRJXmIMrKXC87YD/Jn67YoJYTA0HnSjF6+5LIzLkd6Q0iTh2LHhG6sSpREHHgNFbR/HeHiGpcy/NyrXw+pZyyvFc7mqGWe8tPjKBX3fAT1/MUnVUmIt82giAVDwnS9rNw9jdaruhY4308uPUCEG/l3ZL+vnxFLL9wyLyPnp8KVDCNjlV/RbK0GR2XxHoM4rz/XKqwvh56c/xlSWc5iBeTQu/JTO0GN6LmpM8zpI3Ip56wx7GBg2hnv39bmOqBoFiFWr2+Z9nlThNHuljXF5ET03SyOVRH33KosQKVfdUI4nO3YRLovG9KRtCC28JXcDLqHwnIiRLsXWDTJR6PEuzHowT78YsEO5LqHFpEAvR4CEcnoZrp/XWPKaM0r0VsXPHjbHXvzWF860nMSyJK9X/wHuGR/sIJqxDYQAngp+X6m0gscNEO4+O91ojQ3DQQI7AI4rPJ
*/