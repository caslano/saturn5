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
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
*/