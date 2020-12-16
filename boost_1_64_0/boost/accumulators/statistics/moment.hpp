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
fYsjoVk+aJYfGSov+r/Yn7MvIE3WeFIXIneKn6qRS6Tq3mwdESUClzD1FxaCFAzS/F6iulupta+JH0aZRfeXBVGpWLymnTUN7LiXTP9vpTa6aTaneFnLeMR02VgeNPuu86TQ/jmXRXjZwxHHucX4JN+/cLHsbvSdUyAgCsKkUya7cQ0oLr8hbYwP1hdjT3e0P5XcQ+GzORxB4T9SuHkoPJDCjUNhlzW2UXIiajIGFPeYUNyz1UacALmfJRebt9kl0fT1Jc9cl+2wsme0LqgeQyGa6U88CHLNKr7uDSbn8uUq+UpRu1cJk/IB/npZ3APOgLYjWfxZWgACFWCqb7vdj/ZIqUrXrdqjPixQq8wZd7L2X/QL6SMNCcmjy94U4ysbg16a2MYPNg4s0Ms47IVwevp8oQIjaGXUNYoCU0IKVhAhsW8t1XwCMonnWgRZOqQ2P02nzl1Q/R/lS9RC1iLiRs9vwndoLWiLyHEZH/MW4SEKiOaQRJxFlVGLRjnBPO9wLR9EV+SbmOulum54ALnWhgTNpoz5t916CK3XZiyE1O96Q7CzJYiHByJGTje+5cfynSOFGC5+HVk0GT1HxzUr1mSeY6MQyyeVnyMkOfEvITJ/h8Mi8yVIVslTeIe0yN89Dk3mN0thrynomwthC9+gTua/vAGpa0OBFEhZVC8Jm2871KUICz3XTzzSRsrB7M90gQVSaznYO4ChC7SSJzKyq5Quq4bqT3II1X+Gtwan2veWcMjLdfiLdyT8koQh7FN5cszxP8ZRA6LVYl1mmhmxRBfK1hFUaqguNYzjhpJfE+hykdRhyZ9t3GwekewGegvKQZl043CPvMgDfMObunZCrCuvN+8/6XkXhrsKf4nwGoIal/GRtf+sG2+DOI8g0gnEDuZi81W27Dyu3P209fRKXKtGQthmFn2Kik4g2knan0TQMVnT8CbELA36xwdANWRSqNQiKuXmXacFyiA756GudrZle4GyneeQN0yeFRXeRN1+l4zq4oqj6lItnsKouvRbeTfEvgQ6AYcdABFXq48CUoVT8muWb9OmgMrQ1Lb5AIMvrvvpsdr/8Wty8EzC0YxbLGDRfvNoduMEhn2NBXuZBTv/ThN2NsF+mr4GYGVVOHqvtLL7rey9kL1ktDkbPqYd5VJoSpkis/cdtvMXl0DpfiitYqhgN+CYihwDaUkum7YqzfnI2pJ2nE+utTn/OcjPQNgd4Y4nKa9sS1h/Y9Apvtsskj0rfQOhQRYphg47j5gu0ZvVrbze75OGrL5DuiHQ1b2AHCry/ycup/kT/v6CpVreRt4lh2WQKTWSiZHbU0iTxThZSlHBcT3ELWUkRt0eGuKn1OHHT22d2KzvrSX6Qncw6Z6Ge40sVPpJtmkGuXJFdStUNKNWFVWwz9YrVF+O1JdJ9XWUdyt+cJHW9Z6ljCIPYoI72C5bwQndoo7SIt9tdjl36TxqUa0MuEl73los7dGPwq0mCQrcQEHlCiMrVDi11hVq+5eLbfYvszC+Jqq/sISVl0g980eE6lmoWs2zUH1y+8evyPxh+KMqwP+54lBm2+DPV+/MrR38aa9Y4zdCkDWiwnz5pSKynLZKnlRDT1lJZX7PbpVrFJ9/pX5od+dlvaavlhRxFeuYnn/PIleofNPfrF7GiV7GwV7GflLUv3tFTx7gH8n/ywjZYb6ilkFPx5JzqTcfk6d7o58Weng7/tKJ5Sb+i11HZXHKVtV/pUgx+VKT6d4ou6UnlXCvPo9qriMqL8tVMolgPfaqnH7e4h2Y7imwewPid49JfJaWRe6cQtwkxfRGDPaot5iHWYX7h4l/Em2uRdO4yEMXIAOiF74Rw9GGjj4L0QB0P3g=
*/