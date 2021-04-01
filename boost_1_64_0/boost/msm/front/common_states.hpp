// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_COMMON_STATES_H
#define BOOST_MSM_FRONT_COMMON_STATES_H

#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/msm/front/detail/common_states.hpp>

namespace boost { namespace msm { namespace front
{
// default base: non-polymorphic, not visitable
struct default_base_state 
{
    ~default_base_state(){}
};
// default polymorphic base state. Derive all states from it to get polymorphic behavior
struct polymorphic_state
{
    virtual ~polymorphic_state() {}
};

}}}

#endif //BOOST_MSM_FRONT_COMMON_STATES_H


/* common_states.hpp
4CHALwkZAarnGJk7fojLQjvikWuReEhrZ9HPpM7QFZb4dKsorQlrVtltbnKrrKwS1A3XJy969APYxMnAIOvEgs9xiVtFxKuVaxSqsA+aEYc6Fjkc0BaE7wzmxkWWeBEZjw/BUpLKevDbSM10H3MuhcekceSwhTjm7Fcj5DNTehWQflBG5RQUGiUcdq8+hB2n7oAlTmZJnl/K/afCqDn/ARXtlGy1LkOk2tW4v3MbZ2WxWQcMJ+nbJ1HpFBPmz6O5lM6vCdJkWWnWZf6SLDIpGjj2pDxOpAMjUr1TZ0qA1perx4RwV6g25PkvsCp3aq+Hv94vXTBgMNSQ9a4YlE4FwyrnzTGA6zdSRDvSe1Y4f3oPavrMJ6He4JthhPTkAruhq8SjB7tsF4npDLCTMUL4DCZ+XLV/ZtC9WChbmosFNohBTxOpZko6Z+2jTv9X0DShaM+m5l1NcjjDb8nTjKd3Ul4y3+ok4o5XRp/Lr8GQix+q/Tw/cgqR28EZurUm0Wb326GADcUURVD5zVqcJ41bONFOSoxqGVEf1oHDvExlGru84WUvuWqn7URkSQ==
*/