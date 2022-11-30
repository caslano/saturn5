///////////////////////////////////////////////////////////////////////////////
// moment.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_MOMENT_HPP_EAN_15_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_MOMENT_HPP_EAN_15_11_2005

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
#include <boost/accumulators/statistics/count.hpp>

namespace boost { namespace numeric
{
    /// INTERNAL ONLY
    ///
    template<typename T>
    T const &pow(T const &x, mpl::int_<1>)
    {
        return x;
    }

    /// INTERNAL ONLY
    ///
    template<typename T, int N>
    T pow(T const &x, mpl::int_<N>)
    {
        using namespace operators;
        T y = numeric::pow(x, mpl::int_<N/2>());
        T z = y * y;
        return (N % 2) ? (z * x) : z;
    }
}}

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // moment_impl
    template<typename N, typename Sample>
    struct moment_impl
      : accumulator_base // TODO: also depends_on sum of powers
    {
        BOOST_MPL_ASSERT_RELATION(N::value, >, 0);
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        template<typename Args>
        moment_impl(Args const &args)
          : sum(args[sample | Sample()])
        {
        }

        template<typename Args>
        void operator ()(Args const &args)
        {
            this->sum += numeric::pow(args[sample], N());
        }

        template<typename Args>
        result_type result(Args const &args) const
        {
            return numeric::fdiv(this->sum, count(args));
        }

        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & sum;
        }

    private:
        Sample sum;
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::moment
//
namespace tag
{
    template<int N>
    struct moment
      : depends_on<count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::moment_impl<mpl::int_<N>, mpl::_1> impl;
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::moment
//
namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, moment, (int))
}

using extract::moment;

// So that moment<N> can be automatically substituted with
// weighted_moment<N> when the weight parameter is non-void
template<int N>
struct as_weighted_feature<tag::moment<N> >
{
    typedef tag::weighted_moment<N> type;
};

template<int N>
struct feature_of<tag::weighted_moment<N> >
  : feature_of<tag::moment<N> >
{
};

}} // namespace boost::accumulators

#endif

/* moment.hpp
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
*/