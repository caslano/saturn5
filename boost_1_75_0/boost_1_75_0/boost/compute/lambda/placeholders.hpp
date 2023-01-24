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
W0r18VpGXFm2gt9FXjB4zUP+6FWevaJU1mfjhNYulomEh8qpXtaH+OGVyvyx5A4Ue7KculBgOiv5WdNMZ5HnZyiwfwvMpxeV5FtPKYmfQWSIZBnpV5ItFCe+drNU5T9fXLJ0e1F+iJntY/xSVF48JzRPiC7vVn1lrOQ//6OP5a9uJedbZZkmY/wkijhXXi+ILYdmA3qM3sD+LbHWIcO6jLxCxizBXODvJceqRLb1MVYDlStWwINGD7ltMNtCLzNKzo/qY3wKnk/kH8Q0eesPmTLAv0q8i+SywElcwk9KNEKJMXOa8SnsMH54PUz/U0y7u3mVZJgidrG+xct8LfkFEZnv10fkeGyzSjLuwPIk+VWGlMSnYM7hfT/EPGCOf1EKwIPnmuQWhk+J8C955u8HWYaF/hk5HAZZt+uX92H3gleGaE1xdpX4W4i9EfgP2fMl3go6OX/+CEjG0JCDV0HMguBTwQeQ70SzU1Kwl4GLGqxoX17BupVi3Yh4nuHkSvCTksMUmTOwh/uZ784pf37gNGs4u1WWZ7C3TC+RfQLyEbhXnE2TYwoieVtTFfDglwqPZMg13vmD/7nzhXL8nUJZF478Kimm56myzjerJHNQN8ukyLaAv3jwIA8DK/QoyXUg/gLg0uBzCO8T6MOQa0lO/sn44IlNqVfB3g1/dbHXppXkSIG1Rc77RqxBUUHf1hOAB2oq/ph9SjIPw3+t
*/