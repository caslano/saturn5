///////////////////////////////////////////////////////////////////////////////
// reference_accumulator.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_REFERENCE_ACCUMULATOR_HPP_EAN_03_23_2006
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_REFERENCE_ACCUMULATOR_HPP_EAN_03_23_2006

#include <boost/ref.hpp>
#include <boost/mpl/always.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/accumulators/framework/depends_on.hpp> // for feature_tag
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    //////////////////////////////////////////////////////////////////////////
    // reference_accumulator_impl
    //
    template<typename Referent, typename Tag>
    struct reference_accumulator_impl
      : accumulator_base
    {
        typedef Referent &result_type;

        template<typename Args>
        reference_accumulator_impl(Args const &args)
          : ref(args[parameter::keyword<Tag>::instance])
        {
        }

        result_type result(dont_care) const
        {
            return this->ref;
        }

    private:
        reference_wrapper<Referent> ref;
    };
} // namespace impl

namespace tag
{
    //////////////////////////////////////////////////////////////////////////
    // reference_tag
    template<typename Tag>
    struct reference_tag
    {
    };

    //////////////////////////////////////////////////////////////////////////
    // reference
    template<typename Referent, typename Tag>
    struct reference
      : depends_on<>
    {
        /// INTERNAL ONLY
        ///
        typedef mpl::always<accumulators::impl::reference_accumulator_impl<Referent, Tag> > impl;
    };
}

namespace extract
{
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, reference, (typename)(typename))
    BOOST_ACCUMULATORS_DEFINE_EXTRACTOR(tag, reference_tag, (typename))
}

using extract::reference;
using extract::reference_tag;

// Map all reference<V,T> features to reference_tag<T> so
// that references can be extracted using reference_tag<T>
// without specifying the referent type.
template<typename ValueType, typename Tag>
struct feature_of<tag::reference<ValueType, Tag> >
  : feature_of<tag::reference_tag<Tag> >
{
};

}} // namespace boost::accumulators

#endif

/* reference_accumulator.hpp
+Fajgy2EsoOVKTCwtUY2anufEom+c146oLfq0HMOP7r1eh0+jG616udIOnmSScoFKEx+TyaZpVyzqj+ojMflwY68DZ88BoMwTXHKc+W0uYYzGs1WOVV6vTBxHc33wmSi76XCFGDSPOaBffo4NEguSVzYbi6FeeAAyp59C4XLS5IB5KQNBDmDacnZ2/ti3sTQUYCUgaRkYfLCUJqjrFQqKWIvvU2kpLbM5cP8yr1vQbdeoS5vVfEqtpyvLu6WDUW8f1kP4M4ib7qhzGiYhdpCkMyWREv6Pwwdt2kEOh8o3YIIf1Z7S2Ycxnj/FRmJpe+J0DGP+cp4nGbAM5jT51vQ7oaUJjNNfcohoYXi3raCXsQAMF6qVLrFY2l24+rF4XA/BYW6l8FFSRJghjuUpKc0oXPFG3puHb6xxWEiPuCDCIaj3SIXd1v/xT75Cof4ckXxCM3cb/BM9eWaYMPa3pZwYIJeCLrM0lDpTybpT2byIpEKXYFWpgrTpkomCTipIpOcY4LJQzpU6SgRzTMGl4yTfCYpPjgFsLqkg3kB8EPfZjcj/gLugKRIyZI9BUlpe2op+wiFg0Vv67WXkDpO8TH29NY+pRSmYrBkBstda+RKS+FNPEasQtEJ6VoCkofIBEDz4otoY4FgQE8vmT258nJi6tXFqk60Y1KhBRFUM076mVJhWkxQIFWOlSoz2gozEam2FWaT6fXKHJxNbYX5
*/