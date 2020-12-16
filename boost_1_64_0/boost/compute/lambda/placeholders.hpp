//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_LAMBDA_PLACEHOLDERS_HPP
#define BOOST_COMPUTE_LAMBDA_PLACEHOLDERS_HPP

#include <boost/mpl/has_xxx.hpp>

#include <boost/compute/lambda/context.hpp>
#include <boost/compute/lambda/result_of.hpp>

namespace boost {
namespace compute {
namespace lambda {

namespace mpl = boost::mpl;
namespace proto = boost::proto;

// lambda placeholders
expression<proto::terminal<placeholder<0> >::type> const _1;
expression<proto::terminal<placeholder<1> >::type> const _2;
expression<proto::terminal<placeholder<2> >::type> const _3;

namespace detail {

BOOST_MPL_HAS_XXX_TRAIT_DEF(result_type)

template<class T, bool HasResultType>
struct terminal_type_impl;

template<class T>
struct terminal_type_impl<T, true>
{
    typedef typename T::result_type type;
};

template<class T>
struct terminal_type_impl<T, false>
{
    typedef T type;
};

template<class T>
struct terminal_type
{
    typedef typename terminal_type_impl<T, has_result_type<T>::value>::type type;
};

} // end detail namespace

// result_of placeholders
template<class Args>
struct result_of<expression<proto::terminal<placeholder<0> >::type>, Args, proto::tag::terminal>
{
    typedef typename boost::tuples::element<0, Args>::type arg_type;

    typedef typename detail::terminal_type<arg_type>::type type;
};

template<class Args>
struct result_of<expression<proto::terminal<placeholder<1> >::type>, Args, proto::tag::terminal>
{
    typedef typename boost::tuples::element<1, Args>::type arg_type;

    typedef typename detail::terminal_type<arg_type>::type type;
};

template<class Args>
struct result_of<expression<proto::terminal<placeholder<2> >::type>, Args, proto::tag::terminal>
{
    typedef typename boost::tuples::element<2, Args>::type arg_type;

    typedef typename detail::terminal_type<arg_type>::type type;
};

} // end lambda namespace

// lift lambda placeholders up to the boost::compute namespace
using lambda::_1;
using lambda::_2;
using lambda::_3;

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_LAMBDA_PLACEHOLDERS_HPP

/* placeholders.hpp
sOFqjLz79zb0/74//hswg/0x9ry/uI/G3ML5dOuIxt3C+VTcV+PmxWgEbXhWPPoYelZMslY2XNxyPFXTU34cv9IvbzGLVFnULbu4t7dD34Gd8XEnW5VFhRQJWz4e+Duf9XFLxk2siarCFjjt/ES6Ms/72GelSVsmJjf84uKzLJKcTz+64N02zs7zoJ9fsHTo5OYGzU156BCl723Pznd4I3Rn0DXr+qUdT9/ZXT2au9xwEJT/ysPAzIIhX9ndIvGNHk3vfvNE1nl063krujFDH2vp/ViUVZUkcZQz8i3tsEdf4WPbOMtVrbXFf8sG7N/8ei6mcS6ztC1Z2yC/e/9u9F8+dklWsWhSvWzH1h9T1B1+An9wf6yXM60/kWZhp467ldzj2TL3FU99Zn/vdi4+Q2KUfN3mfvCp9nYAkWuQO3EhxNkLG5Tz/TuFdBdRfHLJ2DVQztmDA5zRZ03HfUZI1xfLXsy2uwzol035sD/ebZRuowyjLXcPMTRX79l7DuhTk2VBHxRRxpl7ATPVLq2aZJsJ+pOODOiXXT8gh2lI13WAbSi9P+izqOr7WNsRQAnxgR6gsSPvlX5mf7fTyHbyOeNJd6KfS8ceHax/aZRHSXbLgRgwl7y15cML9CZ3pk36i26H0bOl3Wkca6C+fi4fHOLs/e3exEAh+56HhjijgUZ2GGM6vfM41slGmUfvMhdnr+LqTAD7tLv+d2zDc9hQ2eH/jl3XB2l9Jt/y63L2bvN53JVYH8vWYfEBpoMAPd+5R4jDAKCsnXsGGL/zPRy7V4CjnQ+Z+/cOceh4tFXcZxyDTvewZ46MYtHp8O+ycfRD7Hinw//sfvPwuIPEvb3FYT9IOhxtf/cDBjh0OO59HxhiaIfDZv2gEEc6HDI/8uAQhw5HH24dDTHDDkdumYfMw6LD0d/veGiIHe9w5CB6WIgPNbzHsocDi41huNjg2/SIOdhA7649cgRHux/Ydz8qxA4XHNxRHxvDYhjQXx959CguHArgv/6YuXgMB/zY7P3sXHw4JGjnjcfN5wnnwdseD+yaviHe2cMna0rygZ9/Yo/bXb9oovbNzL5BTNOtJwHX2y2cCRc+mE8GxtrlHBn0608F3QbId+Se/+majvNVJlwVUNcjz3R02Be8WvixOY8Dd0Wf06avX9c25Flh+B5/4aTG2PMVLeMZXYy8RU0ft++Oxtk/vDQf78wHOEv9CVj99s8ohozPjNkjzjx7iIN5zjvnLT5niOuEqm5/8Qj/jG2fO/E4iYPce7vd1aC2bOH6ibwvTf1yWpZJ0WRpJBn1SKB3reeJ7JQlTaR4oSsxagbDVeJOZ8u4g/BHTNZpnOZKsMA85hiRZ/I9hC9mvKiUMIk0ByZsaju5Svg4U0I1idJ84VHMCcQ9BuFTLOclV3Wj2Ji5O4it9mfar3FVZqpIBKNWcFJPrcy0fVpUlpVRygam8eA9IeGTrFJFU0dVw7ypaxOWbu65nunfMxwPeaOmKGMVsRFTefgmNfV5WyaTNmurpGX0hBnEKgjayJsiyfJCMbIMYPTRxv2gno3Km9pEeBm6J6CNiA1IeHPW5qrWXdQyeq1jPzBWi1zeYugP4eeszlvOeZKxcPs/49s82emPz1cyIdqsqsqWdZk1J7tuIH27EpFVsDrNUimStntPtmkev+nPw5XZFd7SqzcnW25gUMY/gjIS0cgiT5Vfxp6+TBwrAzr1qOBdo26xjYjkytBNn72Nwggf2OrkHye8BYtVViVRkvUPqoxymTGelWByPITv6lpSRs2qTKo2rTPmN/7CRJs+J6QxoS/cPilH6DWjaCtdl9njKTvauKB33Bu4T3W80BvVlnnW2vdT6711b2o=
*/