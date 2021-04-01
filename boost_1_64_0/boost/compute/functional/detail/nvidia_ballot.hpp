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
M6i3gnJbYA4NZVyJ20jSbsPj0/aT+4Sx1lgI9BxrzLDIMlTTi5wKF5FiHGfJjN0cWTr6Z7IJJ2hhHo6wf+SBQvVTb10UdhPTLozmXi42RQco6OV4fm2hgMHDgZhSkH2+Xb/Vx0wYGLccL1YIvnRaoCfHWSqpZRtwoRejwN60R9qzHnK1E9lbKLzWgQHJVtVafmKsKPPoQ3s5VurwCr9VyMJlKrKmq6Ks8LFevUbcHw35zZJWWvyWGi21aYjLEEa+wiDPo+MGtrmCKBIKKhkA/5qstpSwLMx2DTrmjUSWTR0LEApy0IxcHx0IynogqnpyVkSjQMTEXju5JE+bf2gPheKuX8bFT7tKKOpEi+IAht5lUe6DhONB9GkaHkluLdoQuwrCxdlLFSiAvDqq48sxFqzvQUn79uGQVHGNtPCUVaLRga2qWVsd5dB/1Hvc41B4nwWd1n4LRZ8+RN6JSKAtI83d66mAZWCNrTgDUDLa9UEDd8Ez0EEzZFpTYLpWlbYfGuzptLVn1jZM54VaViQM23IBj8A8gfIQanHCbsfMrLHuHl7ZczIipUzSrg==
*/