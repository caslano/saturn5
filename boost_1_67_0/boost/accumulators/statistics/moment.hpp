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