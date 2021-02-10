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
Hz00nYA8QiMJ3eBhYhf2Jy68xfPTBezJUOPsUCx9y8NgCZsIQjc60ONBGotN+/ByGgDW2CIPOgI67p+cAsAQB1jD9kh98V81h51jPN8ZOhLpZKsoUZ6kFaWL4zROzqRvR/YHKIokWZ3eqN0FnAAo7Tgz/T3SbIZamflqBmIKEKr+7OnTp7qlkIwg47H37OnBO9yUyFZOKbw9HdV3xD7VYLlvRLAQTOtkii6t6c/uiv4M9chRdNcTNSa3gKKjcZ2tkNgq+EeMDE15wCyDJpSpqw56V9+5Afzp34TLZbzEHsK5mS0x+bKNHzmru8dEL7/pnendy83gdcBrLMIJVBmNG0SId+c3x8fe12x+xp7cV4UCQKDhJZ4V07YapTC/GLonoDFgsmDoSJKloqVd/LXZxc5m7uS+5RhnFY962jL65sruOSeI/7YJ2BLPW+3zXpUDnTPe+0MU/F77DazVP7Sd+U4H/VF/9P4UAerwpDk6fuvMZh4SG1nU0bK1OqoEtSKSwKBiOwkvVlfZeigMmgnac1LMm9Ba/MgbL+MkafBAEJhFCIaZiGJibaiHsDdfLQNAgZfoG0DbChCRxnGxs8rdF/AX7pXpAStpjLVgW5owvg4UYiO0qyB2lCSr8MDrzNnjZAxKDgJbYaHRmDvQ
*/