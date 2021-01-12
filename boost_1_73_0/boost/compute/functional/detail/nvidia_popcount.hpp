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
F8A34BD4HhwGv4YXQZfqGfXAETAaDoRJMBumw1xYF06AjeEU2AFOhb1gHhwA58I8eCWcBRfBx+BS+BJcBt+Fy+EReA2s4ma8gM3hTbAzvA0OgA/BQXADHAYbwLGwKVyo9svgGvgIXAd3wj/DLzX8V+rvVdVXNIQJ+GRkCbIK2YLsQUbF29Zh6GdiUxfpnEX5wrHIMmQ9cgN2+xhotvP3fsTj3LQ85jJIXf4uzPvt+pD6EX4a
*/