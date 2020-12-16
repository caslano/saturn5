///////////////////////////////////////////////////////////////////////////////
// error_of.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_MEAN_HPP_EAN_27_03_2006
#define BOOST_ACCUMULATORS_STATISTICS_ERROR_OF_MEAN_HPP_EAN_27_03_2006

#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/error_of.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/count.hpp>

namespace boost { namespace accumulators
{

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // error_of_mean_impl
    template<typename Sample, typename Variance>
    struct error_of_mean_impl
      : accumulator_base
    {
        // for boost::result_of
        typedef typename numeric::functional::fdiv<Sample, std::size_t>::result_type result_type;

        error_of_mean_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            using namespace std;
            extractor<Variance> const variance = {};
            return sqrt(numeric::fdiv(variance(args), count(args) - 1));
        }
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::error_of
//
namespace tag
{
    template<>
    struct error_of<mean>
      : depends_on<lazy_variance, count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::error_of_mean_impl<mpl::_1, lazy_variance> impl;
    };

    template<>
    struct error_of<immediate_mean>
      : depends_on<variance, count>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::error_of_mean_impl<mpl::_1, variance> impl;
    };
}

}} // namespace boost::accumulators

#endif

/* error_of_mean.hpp
kfhfh3OBBGtaf7FV7BdcK/Dpumu38YtRyqvgBNAl5BGBIwgIU4HF8BUCalVreb9N77W0vPgcxBeEO0IOOmOwQQUWce5Sc7HwUzeZ1UeTQmviPl0BOBVO25Ymd1fW6LWX0ZuDulAHj9716pXGqMDFRXvyrWwa3sLG0pxd0ZGbF8vXXg7zVVdJNo4KrFKGOjAv+VbKK5wRlkUFPYEkh+gJ9NZ51RZsKKYiZFcHWVglOsnoeZMWC7Ic4AHJ4adyV3GtU2wqBTv36rarHxqh3VPFlSHditmbw9dj6h6G5Dvfak4Py4jrwxaYxQBTkgYYQNtWs5lzO8utnFWyt2DuOi4mmLtD3dPIdosGvNFqOq+brKavQUcqWHptLhBa2CAkq86AoG9w/9OtIFSk/3rSD2vHk57WQSZmPlCfZewFf2eUqsY/hGjwHCaTf0ighxUN1TmdrXPB/SQQ8TKVvzrB8pZ1k0eo3cYreRQG0Xdnpny+r93GuHh6eNyISqpjxDRJoYsoghUeMf6snv+xzII7wHzy7uz/QwKPlds/DmONOvnZqC+ahusykqR0QwtJHMcMu7jSGtxCnJr1vZyGk7m/M+5LUvN/52v65EqgGTGQrdKDdLBVG7aRx5Ltque1qv6RN7RlUDjlJoRZRn5wsiluLJY7aMFksMePPDcv7uvkuXKXggiZpKMheldzWOha2d8xW75W/b8rtWyAXIICLhTg7QGAGIjcdkWo/tUC4TCflM6EiKb6896a80JO9xUhEmhQCakicbCrsbuHlxP3egUZk+jmTj00OindKCYi8AA2yNzyIKu4DNstHexBHYzkDjZCB29Rd1mS3eIzdeIz7fdEnGfxomyvCre/BZmENF9LV/5que1et8uJPw2P4I+6oaPIZTBvkZnFJu7gIipx0urEP7I2QDgrXp+SHeSnDT0eEcbULdOdAcltx4IyTc1mCDW+B2hx5fUl24KL1E0xpm1BPN2ZjMe6wYljO1klDCnRfbdd+aSzrYjYGcSl/AhXcDsWLKw1QK2N3wDJfT7i4lnf3otMWKTIiXNccBszK8zClrT3ogyStnCQE7ypZPDZ6+xT5GXnyVdPiIH22VyRNf2N0CeX9s2x0qXwffopCzWr1kL50/hp+09tGNNlrmhHdnNX/ssynvG7tG5YJJjzGjgQkVcZLjcMjhXZwrE2A2RxHj8dGfk73uN3EN4SzIwJyMiINCOSdESKGZHCoPlXc/1plerPtNWfZat/GOovqqb8CFv+UchfVHn+tzZXMFba/XnuLOAnbCcmeo9AKZ/Z64hokDSq4D4qwtkozBnbL9bZyA2Vjp7xzkZp8QgnIZyEcBrCaQhnIpyJ8DCEh32PiFHfI2ZUrjvaUUtJo9s/0F1RfscU2pVAH0n4SKKPFHzg38BYr9+FLc4TX3QSeGlFFcOZKJSFQsOKJDwC4VH4tuzffWS3b2dEzXbG2cOOqudr8/6jlSlvBk7PyXPH03tZAFMHvym16yrPQxzLkUhzqNSmvnB/dCW94uK0FAdr49ThzcVNEHoAwhAN4drKEFIBwZU/ROZ70kcibGl2SSWw6NQ7Z8WFsZZhMLsfeyHoxCxAN95oWCbb3sYY7v/QKfWoPXXlScXZbSrDhBG7knrqqnhtFcnoxzcRLdTBcNFnNDnTPxGbu5DE2MU9Y2Wb2lHcs2skvkSo/WAb5ikeFwF5LM3os1n0baro+kTjuXfgRpDBM2pd6fR/6COmTPMd7J2h0O2PGt4Qs6UG+cfZVeQJcbRGIyBPYOF/YQQyFPeUSy5/KhvikMuhjSFZgzu4j3f32sk1NP9j1Yw63RnsWucVvXd8IGxJKrqAbWMuC7t+jKok7Np3kv4=
*/