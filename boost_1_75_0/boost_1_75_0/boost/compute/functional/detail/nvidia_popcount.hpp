//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_DETAIL_NVIDIA_POPCOUNT_HPP
#define BOOST_COMPUTE_FUNCTIONAL_DETAIL_NVIDIA_POPCOUNT_HPP

#include <boost/compute/function.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
class nvidia_popcount : public function<T(T)>
{
public:
    nvidia_popcount()
        : function<T(T)>("nvidia_popcount")
    {
        this->set_source(
            "inline uint nvidia_popcount(const uint x)\n"
            "{\n"
            "    uint count;\n"
            "    asm(\"popc.b32 %0, %1;\" : \"=r\"(count) : \"r\"(x));\n"
            "    return count;\n"
            "}\n"
        );
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_DETAIL_NVIDIA_POPCOUNT_HPP

/* nvidia_popcount.hpp
zA1NBHIAq4AwMoGHQvMbAVxTMA8CX4cLQcI9lkAJLNjhILhf4FQlOIx/GE6uILBXgYx6uKAvT8ggk/L2zYSz+TqjM1EuxlEkXglS02rj8gtXadj0Rr2q8BuJBns6tCwtbBDSnsOU66zALYO6Trwdqt/zRW9dn8cDSmwUpKOY2YSbKF6BwWcngCSQrAWnl/04yqKEuxe5V04lndsaJYA9qXir/JWg6gUgpN/yEThSYqidlAhs4+S6oqgcMoIxg2N3YSErc8hL3UQEnTt++j46/8GeNjVbQMvhszEzA/oQg+u6P2l+7mwAFJ+CZgd+Aixk7pFCEEH+C/kbUDSrKJU9gE1FLNEo1ImJDkwVCb2Ro/eTRFjiwwZZ7QyebQQawEsW7kAEawQBIQbIwghr/fl0Kp8qWKFaxiwCDnYJKBqCXwCuNHonWrgodIWvonm+8G1QZKSayLK0SvNsPbmhfiHS2H1D6iaKxdsiEWA7qZGjmX8EtvPniTsIbqOQRuW2fvPbi7kog9dC9omPsnZNRh95enKjXBYoo/57mCuc3+0oxddjS3lAiGBGLIp44TF/+wHeH07HJ4ghgMnbe1JwtF7UHk/KH83OS9aHMfNYz3Dw8fJoT14hBoi6u43B3NrRwAtWdABo4RYNFEn7eQXTCN9tlEx1Qa1O/EV/VyZVzPEwfKm2O4FGWJnyQzDUuLPMeeQccCXIFbUawVvMiI2Y
*/