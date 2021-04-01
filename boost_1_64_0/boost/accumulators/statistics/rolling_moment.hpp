///////////////////////////////////////////////////////////////////////////////
// rolling_moment.hpp
// Copyright 2005 Eric Niebler.
// Copyright (C) 2014 Pieter Bastiaan Ober (Integricom).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ROLLING_MOMENT_HPP_EAN_27_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_ROLLING_MOMENT_HPP_EAN_27_11_2005

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/rolling_count.hpp>

namespace boost { namespace accumulators
{
namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // rolling_moment_impl
    template<typename N, typename Sample>
    struct rolling_moment_impl
      : accumulator_base
    {
        BOOST_MPL_ASSERT_RELATION(N::value, >, 0);
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t,void,void>::result_type result_type;

        template<typename Args>
        rolling_moment_impl(Args const &args)
          : sum_(args[sample | Sample()])
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            if(is_rolling_window_plus1_full(args))
            {
                this->sum_ -= numeric::pow(rolling_window_plus1(args).front(), N());
            }
            this->sum_ += numeric::pow(args[sample], N());
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(this->sum_, rolling_count(args));
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sum_;
        }

    private:
        result_type sum_;
    };
} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::rolling_moment
//
namespace tag
{
    template<int N>
    struct rolling_moment
      : depends_on< rolling_window_plus1, rolling_count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::rolling_moment_impl<mpl::int_<N>, mpl::_1> impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::rolling_window::window_size named parameter
        static boost::parameter::keyword<tag::rolling_window_size> const window_size;
        #endif
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::rolling_moment
//
namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, rolling_moment, (int))
}

using extract::rolling_moment;

// There is no weighted_rolling_moment (yet)...
//
//// So that rolling_moment<N> can be automatically substituted with
//// weighted_rolling_moment<N> when the weight parameter is non-void
//template<int N>
//struct as_weighted_feature<tag::rolling_moment<N> >
//{
//    typedef tag::weighted_rolling_moment<N> type;
//};
//
//template<int N>
//struct feature_of<tag::weighted_rolling_moment<N> >
//  : feature_of<tag::rolling_moment<N> >
//{
//};
}} // namespace boost::accumulators

#endif

/* rolling_moment.hpp
o+xwt29EPhtlzYqvZdJYG5nplvArnhet/5qpmGWR6MoFaQcHSZX55PhWKf8Dsmc1FiyZsJ5xH+4wBLFn4erJwHKsR+aaxLClN8Mb0VjjHxqq/Wod05/NLqtG0pZ+jPR1hifXZTMLqxlMyM1LQWuqR0rXRt8hmxCvCKPiFUPsYH6k4DRnwpaCMfYMBRU7Ie9qDPbD+TrX2AOV2OFo+MugAIpB7YfzIxQST4uOL6+Jk88VXCi9vDOvb/Kz1ZyTOsNsHtT5Gi1dXiMu9wW/265h/3dCJsk/FFFvsUb9PGt+MloWXGHD5zcwt3V53O4+tnuPcQ2wW5WXuK9yDUnk2ps5WaaVsPSNWMmpTRmZKHf1O+iirGfmHPL7I3hFTyAM9Nfi3ZDbmcrdAswM+H1OhNUjxVj4JJ7iv0T3yaf4OZTPoVks2i7NwXXeA4qTMe2uLiaXxp0UMwExhW6KU7LJkdslAncR416GWqPq6jWueUwYlVjkiFiiDsQAkoMW/jpbhyvXhzJZdNEfvHT28EtGxq6QFT0yvw+tt5HujU14b2ITwSIX6U3RLUAOcVvQ1A==
*/