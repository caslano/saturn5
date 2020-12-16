//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_STRING_TYPE_HPP
#define BOOST_BEAST_STRING_TYPE_HPP

#include <boost/beast/core/detail/config.hpp>

#if defined(BOOST_BEAST_USE_STD_STRING_VIEW)
#include <string_view>
#else
#include <boost/utility/string_view.hpp>
#endif

namespace boost {
namespace beast {

#if BOOST_BEAST_DOXYGEN || ! defined(BOOST_BEAST_USE_STD_STRING_VIEW)
/// The type of string view used by the library
using string_view = boost::string_view;

/// The type of `basic_string_view` used by the library
template<class CharT, class Traits>
using basic_string_view =
    boost::basic_string_view<CharT, Traits>;

#else
using string_view = std::string_view;

template<class CharT, class Traits>
using basic_string_view =
    std::basic_string_view<CharT, Traits>;

#endif

} // beast
} // boost

#endif

/* string_type.hpp
rKT7nPdttd7j11kvWCv7t9DzitQ6q+uuN5/d7Y5WzfEN0yJjsqNCveO4Wk1yTlN7neOMQrdT66zeIXn5o8MDbfAvwf2VEad1VodKXpKNFMjnOtT+1xifE6mzmnmjGXbI8CB3t6NdmxsRagN8Nrr9usyhdPvXhqyTQaoL+0EDCXsZGua9VHtjteMRZ7nq7pqp7nOVqGT3m8rlKVAlnom6nt7+lbSJGqMcWhf8Ram7p7ywivD6bSI+usF8dq8zWjWC3lV7R3vo6692erVe/GIp4ybnIJR/G8rew4hWlxiPGOOc6MOso1RJYwdCm6g41k0vqf9/QsTjAnT4U9nGByTdOLypXM2HJprHKFVzjHx10JiohjgK1D2OyxGTY4Ck9QXSaqbLd5m0eQb2XR1af32i1JHLwC+abtsz2X5JyP8ytNEhUHvmu4PkoafLi/HtUeSyNyTuMVAjR7nxvNOpdZNfkHr7k3cNJGOl43SV6ezpoj2Hlmvr2JXIPL4h+XnNtHZQ5+K84VrU8X3MbzzCe0m9PY8xdYVuo46Sp9F4Fq3aU767S/lvMtqrKNRgY4zibdQt4NgGn9PI1OV3yftGqgiEJ7L80fIswxGBUWc2NGWfNwaopo72Kp510FjC70UvGa+WIafxLPMt8jwTT5Lx/QSn1u1vJ3kuQk66aN3+0yR/n6F9tmnd/h43+nTGo1UfrdvfX+J+ipL9UcaFIj2+uELq9rssfcJOd/8Mec8El814pdM8g2m2DNkPqduP8Gahw7Uuf6xdfIZH2IT3ZXi0JTyULv9Rkde2hkNdCr3SAnwL93zIAW3hpP4qXB7VFFJzPfSZ56g3jXlqomO3Mc4FexfK3XO+voc2b6eOgvNPRit1EfT1X3G4VQJl6kmR6Re9bYx9zkthOfCq+3eGvz8fkPx9gJ4yUPeBGyRfFxt5+C1/UkVjdI4JqZ/f2Kb83RkO0OHmb2x2LfTzl/4f6OfPkTOxF7elfjOy/M+3XJ/34PKpPSYurPvZ2g/Vzz983S9LP1/WD1yLbPoB+vmxVSenn59WFdbPVw7O4zg33cQ14RHDXj8/kfr5yUH6+cPJl039/MnUzy/k93iKqaf/CPX0/8Xv8Dipp9+TevpnA0cAZwPTgZXAC4AdkNcLgadTT38e9fSvAV4CXE19/bXAbOAIp++7OpXU118EzAeupN7+w8AC4FvAqcAECFAhMIN6+5Opt3819fbXUG9/F3A68B1gKfALYBkwhnr7zYAzgH2ot3899fZvBc4G/hk4F/gR8CpgJ+rxd6Ue/0Tq8a8AXg1cBVwIfAi4GPikh98eBy4Deqm/35r6+0Oov38l8Drq+68ErgGuAt4JrAJ+CFxzEnr1dT3TXgv/FtAu0LsgNTl8xh12YRd2YRd2YRd2YRd2YRd2YedzP9v5f2FBTlmB799To/8/t53SZ2LJPPP9AtQG9FfQNPyx4Wo5Ezs/Y9h5F144Omt0elYeMocjU55lZbSRs8wC63fCd0qcR6rPxcSfzLOvGmfBDO+mzwv/Iv4nhN8pZ4ul+eWWs9LRC63fGzTUbPE3E/4XZLOpqMiql3C6hKfQ7+dvjp30cxs+YO5zObDmR11EOztGeaLaReVGdYg6LWpyVGpU56h2nginG/82iI6JMdN/qZPOjz4XPib5das4flvekPSX4taWSGueuilLGY5KnLEhykA9BZYhjvvTbwl/A6TotPCYsoA0ea7xd+HZJOF9ZcM8dxL+0d80/1zCb8X20nkN/eeuOeCbV4tzV/+ZKtob+71obz5Lt+4LS5v2bSjtZ+4+x/r8cQt9fuQpQM/AxfP5aaDmxIlI/+WFNWSuOKewsIa8sX3J31nLz7fiP1s=
*/