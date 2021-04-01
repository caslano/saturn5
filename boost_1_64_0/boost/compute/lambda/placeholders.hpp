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
ZdjPXPUxa6Zixo/FPCAqQVQStqTCPZq35Txf8HVJoq4QxDVFLIgBWI4eyUkjeG2ZNMxpHmCMb9Lidrvrk1O7mw/p5yW73JA6Dm95Qw49b9lz4mwU21cS3iBiIkh6fNg9TjP3Cz5xLgveiNXu3xhJcSQW1ogC8kobHprUDCDQQpsoCAQ6Uk2EYTx8q0rL6TFwSA+wkj70TJ0rINMa7CUPEOz4i2b5SOM75vbJnNWZcWlNzkqUK2MS6mlak+SUcbCzKUqhQZ+aNzlmnERbiyLiIwmlwpu7Psclrfj8epsItaYwoZ7n1PIZ4u2WuIZ5sMn0kmzxqq24nI69i6yfwHhctWgmOx6j+NSqDCCgCFRcrecRf7U6Ls7fOjhcmu06PaC6MHS7+sBl0MjHdZO/d8J3LuqQ1Bn/pX/F3wYJc4Gx/j7mj6/HY237Xg231bVeT1ezrs2G0hP2vTilmfOFWtFO3sYobWFvPvAky72qKOg6re8EDuwarJWh0xTXBaCx8krHZAP9VQ/rFebM3/XGzJV2XAtw5xdQ58BZXMgycTjZWwY2gDzTeuPSeWjW9Q==
*/