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
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
*/