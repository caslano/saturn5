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
vums9PjOuHJe6IlRNRjiL73zibYoUeP6r7QiHC8HG3qg1T6kKmxhXdYJk9BaRA+EshRfE6torQ3wL2pPzwGwmCP2XXzGyb2xg/K3HTV/bzVSANtON4Sjy4/RRYlLAeRaHi1vjs0tnwYP2hcEW8N3drwqcnGyYKrAgSOgDTDNE31qoAAO5dl3kDoLXo2rzpBHe9vYzXJ9Jcn08c5Hn+xktQflKLxhK3R7gR7STLeThc3ohxn7jmvJfVTNm3m6XqAuYNtwkGrXD0Q1CDATehyh+flgfgwNJH4o3d4Me5SRIHeAyBIOQz9qu5q8sOuhbFt/YWXslh++AOYz/+tA6avbTad/6HlKN3UkII56B/JUN21BwvrF2+rsPIQPFErH2VmWIczrMxvqzyKaDV7hHRGT1KBx4PbGFLlQC76+jytGic71WBA1PmkGuGfGztHL3WiLEVxZO/bI4HrTCI+oUY/FbcOROsJMp00iFeqNFcd28ptIJGQp+4UAr+QlDfT8w76nnmzEcyUQ8ZT7b54u7R/d+7B3iG20sb/Kk5YW+Vzffva2E6J+/o5XvyaumA==
*/