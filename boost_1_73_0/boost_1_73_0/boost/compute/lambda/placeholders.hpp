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
w8CAz/Yd833n81xpjFYctTVPbm0+dvbB89T9c2TLmV6UNpWmaem1CexG8UjSo04dWAwWYSUVt3F765i5mfvsyzRtRiN4kCknM9oxhMS4uTbRkIWxOFtRjGPvfZWFQvmd1ua1gYpEjHMWCvRgSQuebRMf7jWO1Vkze4NUTqXNg5BV4H7slhkRqONaa5Q3DGDrVzPo3T/WFYg93z3VQy11rRCMwBXE/iUmiLoS1VrMPr22WtwH+SdosWZTT6ajL46ZEMoZrfopjhMBt+ssgzCKHEhqrfe2pADz7Xzoe6l6fhc/GVj0C81BtZSq06v+9vCv5To1tjD5lopI3c3j/u3oLDW2LLve81aE04oea8zfPNJB2GUIKBKlcWu1xaL3jF+Wgd2s0kGqvWsJTs4kMxYOBc9yh5pl4hmWiJZiWZU/tHlN656N5HjrvGljIRro5K8rUfrqEk2toepWsv8AwUMfONRUxraCGlhcPHn98CQPsjRC3IEDYkft4NB3qRkkfiXkLbY4ALsmH9YaKV3O1vgC9xbaYvDq5NclvK90wPfJLkb97vQ5h65mYSWVhu/THOd6+pGt6taBr7IXRLm0jIfd0h/eEt03R3uFr2/B6bTw9E1fhFuhGhaXLLouS6Di5lgFb2+RCsizDUQKGc5j
*/