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
QYgr3NKUBl2IS4VvB2XVSIc/SB2eT/P+Nsq1NC4EBJcOwo49OgjXRoKABRFRvym0/htRv26MoYmKT4HRtivA8cddez2rvQoT+6dWPEjUc3HA4a6MKowXs65fO6yDtgEhsaj9Uj44W5pMBKXMfl4QGTXWacQmkkDIFw39GM2x3ErmOfpwhMbvg3SpZN/yybE5St25VRh1C3fD5t1AEoPOju55cNvpZclTSujw71OrnI0eUO8mOliZmcwGjOjzXbF0izR9ByggQip30PQnzsquSY9c+P5qEKoQKSTb7YSu3uavPZ/HJk9h9/ibDwGYDVM+jz24adDZ7fo6/ZWb1PiNg0ra9XVlHLFOu4YYVkiJiFxmaf9el6XG4ZUINBmrD12zFlsp+zKoY4rPraM3rZN49YGxYtVVwzGARJx6LqvR8ylZqCNaNnk+5aZdaERT51MXtQ4crby/Sz9HGgitMhJs2t/UUB1hPSIGsCZ4iAhBvbq90XOqF0WZB4vwMj7/StTPv4Llfxoj5UMy1UThQ7fLhjMygPiCaiiZJ+28qhF6bFTrMHsJa9j5ZFh6Z1to2GkN+771MfXZFsQaPMmJiao2dGPzyLj/Zhj3a7co161lqUHP5S9pfNss4duubR9UZ6tT88D+QZ2tN23cw7DJi/c5uUKXzSs/soHij1f3J2qE/8nSUjPSqxtaBO5XUL+zaJQp1ls9kaxmjWT9eTPJXR6bInf3xqnfIAyvW0HSVe41YCdCcrXBbJuZY1MRmySxmYhNldhcxGZK7AjE5kpsPmJH4BUx+eZm3UPfnPZ9FxOgx1WrtE/IKmP7unD7HpH2XR2nJkgYzaGwTf15U/Po9MbqHx0TmDWYLyDb2W+fwQexegBblihBdv6OqffEtDJDOiU814lRtLoSWT31tgkteRRmabGvcWwnjrWphZ1O3M9x0D4o1FbjpWjRHyGvZqogLXXIemIFRkbnEBqfEbC3yIGYLGUfVg2RoyuB/YAO6rYRtigkJHO/qJRjr/GY+c3hY7NE1Y2ghnNGmZldQBG9wDL0EZdlPhYd0NKaewa1msqz7HdYVjozKsctAMYhtINKgzSY0Zzh1273Rv1E6RlB5o9YdL0a2cWVap3qIumLi9pPvVb+HaiuSkLoLsuBO+ZQO97zM20ZIHq+285BOi8faWL6M9A1NwaC86kL1CsRNHAe8rkTOINkFmx6hb2aOk3zx/EQ1jdTRNJ9g7cBuWuk2NSV/IBbC2sx+Yh0UTeSS7AJlLNbKIBXBQGsRIoBwFIEDQD+C0EAmK2sagZ0tTEh0P1rqyw07bBIOz6ivUQGsvkqmr/ql4lhNuzZL5uNnI1M/wrW46snzobVdi+g6X0uOhd6gGGczWOUI0wzAQ2hDsgHmyPT5QlNja5QlOe6BY4T4YKA0dColRrnA8pQusv3BqWzvQzV3aFFwOXfc+hElJ2uQZIqUwUuEkL1LR7aFEkWQItuiUORCrTDO01HEbMii6p5LSZQzUCtGs1RKFelbRJ82MXV4x7+rEBHqGdqaDQ/pDNOwagyPiZgbBGOvzZitgpqyxHUZmCctvN5zefO8m+wet+X1VtPB7vUoXSc+oKcvHP/fwcNNlHszVVnRAfQXKePNVpKVR/6udaI8aZpQW3VjEWQjhWxchw+lCGDpi2brTQzUnHyYlg5E+uZ68+lusd8hLK01ayNqOcbLOo/0aL2Ak6BV4P7OYQ13xkzNGWbCzXgiziLusYSgH/4Fh3+Dw+HwL8CQQP8Sw4b4JdispVKDf6PGoH/nTri1Dgjz6vNOqf2ZDLJ0P+bvGy50IxOPH+updmDuVNIbZ57hOcOq9Ly3riN/MRdfYBPfuKu8g04QtQ=
*/