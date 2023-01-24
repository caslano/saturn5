//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_DETAIL_NVIDIA_BALLOT_HPP
#define BOOST_COMPUTE_FUNCTIONAL_DETAIL_NVIDIA_BALLOT_HPP

#include <boost/compute/function.hpp>
#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
class nvidia_ballot : public function<uint_(T)>
{
public:
    nvidia_ballot()
        : function<uint_(T)>("nvidia_ballot")
    {
        this->set_source(
            "inline uint nvidia_ballot(const uint x)\n"
            "{\n"
            "    uint result;\n"
            "    asm volatile(\n"
            "        \"setp.ne.u32 %%p1, %1, 0;\"\n"
            "        \"vote.ballot.b32 %0, %%p1;\"\n"
            "        : \"=r\"(result)\n"
            "        : \"r\"(x)\n"
            "    );\n"
            "    return result;\n"
            "}\n"
        );
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_DETAIL_NVIDIA_BALLOT_HPP

/* nvidia_ballot.hpp
RxA+HEM8xWnd1heFpcaYiclodZswodpFsL+PVMWvezgAR3Ury2Gd8BZY9581AHZEz/hbS4ICvu6kdfy8h8Rt1FpI5qp/lhH0ahpl1zy+BS9CW4+hv/jgbZQB19t7MEdF0/TQo6fEgmYha8agifTj4m4ERhpw+TLXgqq6ezcexs2aE1qELyjIQWrzf9btn1tQhm1XMybiwp1NSH4ydWzBTPRBp6YjyqZl2Y71phUZzjxHtxM7F/oRJV9tRTLGkxN3dizdOqXN8+9Cb9Fz6qd8wg7leKprCeUsNO7XGB4rKVp3i8A9bbprRNyJpB9LU5pL/VXiDVhdoTFOrUjesR+a6Uf1yLBvAsz7oLJ/vWdvfcMmDbWboXKIVvbprWbn9YNxExUvtMxBeubzNAuoP+7It8Mfi60Epx/bPQh/jz48BKa3ut2c2RlEDQ7kwaUGq/WT3rScdkAoAPhtHB9d10XkIBMx7z4cY0gcp3EeYmGP0i824LfegRGbW6ecI7pQ8lp+i+t8mxuqAy3e+S27CSJRGTOqYTVFBenMcXfRdiHAm3rG2yE/D5LYY/GmSvPT5b/dPj8Zc/Z1GjaLlXBZkbZxvaS9whpLLC2MGf3CCW5/GIKwcPLx6et5ddvYsvKYn2jgwzuXDP72UZp0WfZeSv/+q2K//xYme75n/9LBYyfeiP/VO5GgscrDhEyVa+t725Zt5NZj8EGJbPQHsgZq
*/