
#ifndef BOOST_MPL_REMOVE_IF_HPP_INCLUDED
#define BOOST_MPL_REMOVE_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Pred, typename InsertOp > struct remove_if_helper
{
    template< typename Sequence, typename U > struct apply
    {
        typedef typename eval_if<
              typename apply1<Pred,U>::type
            , identity<Sequence>
            , apply2<InsertOp,Sequence,U>
            >::type type;
    };
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct remove_if_impl
    : fold<
          Sequence
        , typename Inserter::state
        , protect< aux::remove_if_helper<
              typename lambda<Predicate>::type
            , typename Inserter::operation
            > >
        >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct reverse_remove_if_impl
    : reverse_fold<
          Sequence
        , typename Inserter::state
        , protect< aux::remove_if_helper<
              typename lambda<Predicate>::type
            , typename Inserter::operation
            > >
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, remove_if)

}}

#endif // BOOST_MPL_REMOVE_IF_HPP_INCLUDED

/* remove_if.hpp
fHapho1VGu9FK3SWaLsAQ+eEAi2rZiIR4m+wy7JmLsOn0uUxUH2DH/adOW1ZT7k9VfsvyKpmOX23SdMtc2t5wisZEfVoOxUukjXk0U8mk2ObpV18nF59F89K6WvsrqrKXUnlFfKWXQ533TAoeJGxfXS+mggzBCh/iQvmUaDOl4IsKQNi2GT17RRCE+b805ywd0K7CMN30x3XJmtkNtGFhj77qq8agRPSaJBdWHdquSSrGjv0iLr83okU9yrJUHNVZTPtxngqSXWgtpi+XiSmJay2feChmWyb2Gxm4TEj2JsJbtVloYKucSstcZEuar6Tacj1gHiMnf4ToVj9hl6RElPOOVloCPMvL8NsiH1131naSdlGydd0jAdraXWWB73yqTTmiPHqFjeklBhI0x8dOhl7hTqpa/wXuuVvl/9CjzIbBHdYUBrt2ygxw31nL9b+EBYDxVMyH2HYPSIXnL91gjGDfU7MKWBVL7wEe0B3P9w3Kemwwrb/mT8VT59GKvJ9kCRtN0e7uq/ZdjGoYSC6kHRGrgAWGva7MKc9TsvxAK+wrA6yLAB3sA8eQXXPoU/RPTzvE1+53DLNra9EbJnCXLAhbpnqUkH9N3wHJAFEf6dl6zy14/Ht/kIXL39UnK2j4joP+pPdQYlzljY5S4QZByURxPvzJRchxxe/+MX6bMzm75+6LfFH9ZQ2sW9oS/Vc9esy9WuO+jVD/SpUv65Sv3zqV7H6NV3/ZV3p8GAmkcPe4xU7F+byfi8oO7fYt5kWImtqxn9KBwq056A0N91d08b7CPjfJBpx7qNWZPArOU1nEbhusebIEB0ANgM1/K+/5jL+XTpoFqjKmjfGpnqRoFrD6ZKalVx3lvZQuqAKkQP41w+VCDE7q4d4Qhezlx5Edz64hDupvhp0+V+W8WOOt1ZyKjCNCsFSDZIltIFtDugi6fLXEE3shTsnqeJMilWqy9uY4akfGhHXb216YFNDZaQit84geiI0gxoH7EKJssbirJjizrGZlCif9FSapAYu5zCBwMrLRBUfV6mp4SIsDSMA/ifUngv3nWYTXYdGPm6kdbnEuoJorKUcDEZOeHa2+IETX6ldmkLNdDBe2UdnZi4Yn6vr8zeEFEn+j51R9Ir1bg7UzAWV6r4QX9dqoW+OfEzZCG2gfMJsPIH/xURcqB5EZoPIFEUkgLp+Gilz6B4f/tnXsJsAQOGHRQkIUuyaJhz8ykJwfKtI+sqUtJBesdv4EZZY6b4OVP9eP1SX+vuaTOIJCEdnuf8zwtF/+x/7t+Y0Xv9Ltfq3EZ9KfzRW/6Vd/FKQumnUp2zH40SmcFLD4aS+BCc1EIuy/bGyn4XV/7SqjdQGKHxWzOGrxsNSpcO6633DUmv1KYh0Jd9KEWDDA0P8FVK2eE5IYwpQiqlkDhI1wa9201tBqpFDkCvI4cfZQ0WBGmZDLNWikr5En8MjzeBdcr3WQyDleGioB6gJ9Re6sAnWxdP8Lsg6CI5jIngrz5KMhLJ07I6FBLv1JCkOp79eE+EKiAow/jXt6IHRmM+f6ztVxVpiUj9mLwZSGY6npQijGyWrYdKULiqB2+7w9FCyGU++vmoW4dL+4VJ9yg6E/xXxyEsiNLcOZwfE2TIBPB1KlcnBn3IMcILNHE38M92EgACo064h0V0b+b8s9uXsvpmIGgO7HKKZ6BGBrZX821/irNoIOyh3CXKhs3x56pHIYb3te1/EriepopXj0PVviAI5B3499YvvZ/W+5FxeXFXLIZQTvZ6H/rsoRZ8YdlZ61U76S5Dp4oBPvJ1kk9j0S7nQx7v4A1OdofNDfxDr8HSNENGQb0BOLcNbSpDfkKzPIm510XyFcBTK5DI=
*/