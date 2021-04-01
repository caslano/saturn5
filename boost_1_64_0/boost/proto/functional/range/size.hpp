///////////////////////////////////////////////////////////////////////////////
/// \file size.hpp
/// Proto callables for boost::size()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_SIZE_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_SIZE_HPP_EAN_27_08_2012

#include <boost/range/size.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::size()
    struct size
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_size<Rng>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_size<Rng>
        {};

        template<typename Rng>
        typename boost::range_size<Rng>::type operator()(Rng const &rng) const
        {
            return boost::size(rng);
        }
    };

}}}

#endif

/* size.hpp
xmS933Ma6hv6P+X+tvL9BtoaRGqeeeT2p5GkUX911N4d1ofKHYCh23ubr+G8q4guSvnmlaogKL/xAUpEYY6ZAPr7/rVPazes9X9s/yCX+MtOSj26WRm4ar0KbIJLWHg+Pul030ivju64lv4yoRMSBlaeUtmt1AHiQpzDzUEHts0HYy3EKX6zlitJsPazNb4ECsT874lQk5V1bl0hntYgSfHay54GxZxctBZYdkiWK/ULM7eDPZX4yGU9Rbu5b5McBpzCQT/V+JrrDtdGGidnyK2txNNFdyQmmP8IWWritEsV1f2XplpgZc3xPFxOwHEfCwj/St6ePxJBVs3hkylAxqxnMQoyB9ntaSBKi72sJayleyoaBcpZ02Lw8wJ2eD9u17h8DRYDHWVW7SLdEWtrqz/tzdlGBYKUgXGx2Bw5gw8ZO/7WoCbHeip/Ezj97vx4/0YUZlABUIpX179xmo/uKBigrQi37hr4cxvIHe6uoF6heLQl9jzNqDZpi9TAxcKgce08FEy68hUJbA39nLn4a2tCI3eNdFESerYicTMj9gZ1WetMF3h7vQH/3A==
*/