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
ZKkI/oevV+DxGIB5j8kRaJSZpOl4sMsTjS7V6NGdGt0w6shtW7JO9Nz38EsQprcgHviW55l1PWnOviSnDwQ9Slfa0VKwHIXGuvOihcGbwBHKiCx6h67iS+ueph/+5VqSXo9Syj3hR9W9CPPgta4j6XEehCG94tTROvTaBVo3req0+/7ViL5G9PxBLfF2RBdyVwVNbDe1+J54BJkpoYssjPfZNWZvjex2gmi5DQs06/0W/zwbJxtEpwd1iXHWRdWlOF+mO21Mu/ri7YDrxBvZ7pLQKTn2bG9v0mmZxRdE1a0RPSBr5pOX4ib6PPDnLwk69VMlXkZf6fcuv2Bj2rmCaIwPjCsz2qYYWxjV8fHDonA5pr7fhs4pxaHMbdixNi4OTgNTR398ERhTTuvYP7Tp6UqSaDlbvwRoxjipQwfZabPqcoTWw5rfxvC3UINKEpmx0xdmYGRWqO9FG9eJHrgSpXTNeZA+VO87fcnBLHMyxnZu05fvcVe0mb6f/aVWvXnnYGw56R+aR9pn07TSrajGhm0j0oKexuT+7KBnIbPHDm65yllIII9fdui1e6lKxBhnNuZBcSdGi5q+zn1jfMgxVoG86rG6QtdaLsXLDxUH0MXQ1X3862sVcLSZz4zIKsbHPcHP3nRk6R5gxguqvAoN1ip7bpgYDqgZO7oNOxLDrxuNa3GVBhm/LSKOOuY5/+9dVuHa9HDxaDilsR/zd/ki2EbvMTFL/fX+YDxdUk9oannwP2jghDLUb5Y+DvzQlWxhTFFPecY4Nn11z7q8xIQNvos78XJFyw3aWUlEe6g+pHyXaOhlSw9VHajXYQamkyfBQ5fpijDj3f4j8Kd584gOH+hukS6mIl3GhSPw2AmMrkMb0JoNdGfaQH/MwGyOjTnVKgdTSxdz6paRh/QYWXdt36lIV3MXdFoJxrw75tRXDB7YsUPPeyj6yqTJvsI4+ukVJC2qqpSou0HLWzn28a37rH+mMQZigv2Wn2u60QUT9AHqBTpmbvDhYNAFpqwPNEY1MXTrnS0amhdtW6Rb/Tt+1rUVPSTLZWn5oULQoPducw1F73TEdcJ8IQq9d1uTHnc6K9ESafilOEiA8S0M9UJK44Xn5enYqKeCD3adXkhnXhmrK52gHpl9cgB+LRttBWOrlK714vjrqj2otrSk6k8mykCJ0G9FTK23M9g+Z2COihhlEAHjfaOAEQhD381jrLO2o3axdYKOpUyVTkmj5U41yCPegJhwzTF34dcFbCdvBVUioZ0ulmJibU9Cp4t3S5aimr4b+8lXlbSs2snFxMCeNDXzzy2MmBhC+ow1d5EuXvY08ji0MaTMKQuDfmzTs5S4fKBBn3uKRScimyk13S/QV2g29lYgKw6dqlghXd4xeTgoYsJgOdBxMUU6qwTo3lMLdJphI73fbdHVeXBRD9h8NoZG34Oox5Ks6mnMeQdDg5BaeynyDMwFB0PSmESMI8JgDfTsayvMciNa4oMPa8CHKJnKK9ECjx8D7eIDDZog6TZ4qKa1wtqCJHew7pxcTdFb1c5dF+hTADl2aCSN9Q6lhaxOHXo7qHZ5D+l65y6mE9Qiysfs5/1P2xg5h9VRd5e+OdZv6H3BpN1Tx3rZ32nk10n+9Drh2KHTOF96aL6sde8XXTq3z0h9aoxfwDyIJCOPTN0ytjFKiwdpKDW5ed7KwZINFOddLo8dyLyN4cIWhYZ986US+pLIBHqxBGMwH8BXJOY34KhbtMw5NOoSHQd8ezP/e7nTcwDb9g4Wzp2igRtvXNLEsQXTg2gGE8Y54bBHd5drzcbJfQHcZXESVpTfxRixsVY7ePM2jVJqXf7Jaysa5ttuTr2ehXoNtQwMvwI=
*/