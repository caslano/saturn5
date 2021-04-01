///////////////////////////////////////////////////////////////////////////////
/// \file begin.hpp
/// Proto callables for boost::begin()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_BEGIN_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_BEGIN_HPP_EAN_27_08_2012

#include <boost/range/begin.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::begin()
    struct begin
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_iterator<Rng const>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_iterator<Rng>
        {};

        template<typename Rng>
        typename boost::range_iterator<Rng>::type operator()(Rng &rng) const
        {
            return boost::begin(rng);
        }

        template<typename Rng>
        typename boost::range_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::begin(rng);
        }
    };

}}}

#endif

/* begin.hpp
yLbOn0Cbx0f+mHF5Y4xxPb/yVb1ms52Mz84iw3gB1CprpVwHUEMu0bWv3hn3NRkXr4EdOZD1lOWjGs2ju9zKb7r/JG7bHhIo1r5uiOAogM9mXPlvlzRyuhjy667lafdi3er6U0ejW50fzNU14tObVO/dPWT1EfGxx+Td+Q8BLI7WntnHsNd/siMmFyc4DiXwaEeUV9soVXiTiJgko0fYXoH7cF+sCBcqJZ7NOZ6l5AQnrPs0t7lvoEgGRJPMOmYLmBSMdB/msne8+Ffxji2ODleDM4clZCDzIbXxpMr8Sm4a6TuvBvZfkBK/Iz7YhkwHTzO6PdD+ep0GLzC9yg2MKNrT6nJe20mjGBe54Y+PTFcbN2/gD6jWdLfr+AJR9TnXd5KE3DT5EYOE1YD0mz9thp40Qul61FXNzyJrz11u7Fr/mYxvcB3Inm3/UpGayMS6AE90K5ABTvyQ0G1HioBl4IzMBgOEe5zJzNS9k67pCNBSdPb70LXgv7dbMG+fu/YcNhdnNMyJMRa8/8Ia2gcdtj2/vN5MVXuOdjN/VsWcNGQsaYx1B3/UGwAZJw==
*/