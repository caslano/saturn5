//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_LAMBDA_RESULT_OF_HPP
#define BOOST_COMPUTE_LAMBDA_RESULT_OF_HPP

#include <boost/mpl/vector.hpp>
#include <boost/proto/proto.hpp>

#include <boost/compute/type_traits/common_type.hpp>

namespace boost {
namespace compute {
namespace lambda {

namespace mpl = boost::mpl;
namespace proto = boost::proto;

// meta-function returning the result type of a lambda expression
template<class Expr,
         class Args = void,
         class Tags = typename proto::tag_of<Expr>::type>
struct result_of
{
};

// terminals
template<class Expr, class Args>
struct result_of<Expr, Args, proto::tag::terminal>
{
    typedef typename proto::result_of::value<Expr>::type type;
};

// binary operators
#define BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(tag) \
    template<class Expr, class Args> \
    struct result_of<Expr, Args, tag> \
    { \
        typedef typename proto::result_of::child_c<Expr, 0>::type left; \
        typedef typename proto::result_of::child_c<Expr, 1>::type right; \
        \
        typedef typename boost::common_type< \
            typename ::boost::compute::lambda::result_of< \
                         left, \
                         Args, \
                         typename proto::tag_of<left>::type>::type, \
            typename ::boost::compute::lambda::result_of< \
                         right, \
                         Args, \
                         typename proto::tag_of<right>::type>::type \
         >::type type; \
    };

BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::plus)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::minus)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::multiplies)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::divides)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::modulus)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::bitwise_and)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::bitwise_or)
BOOST_COMPUTE_LAMBDA_RESULT_OF_BINARY_OPERATOR(proto::tag::bitwise_xor)

// comparision operators
#define BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(tag) \
    template<class Expr, class Args> \
    struct result_of<Expr, Args, tag> \
    { \
        typedef bool type; \
    };

BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::less)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::greater)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::less_equal)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::greater_equal)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::equal_to)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::not_equal_to)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::logical_and)
BOOST_COMPUTE_LAMBDA_RESULT_OF_COMPARISON_OPERATOR(proto::tag::logical_or)

// assignment operator
template<class Expr, class Args>
struct result_of<Expr, Args, proto::tag::assign>
{
    typedef typename proto::result_of::child_c<Expr, 0>::type left;
    typedef typename proto::result_of::child_c<Expr, 1>::type right;

    typedef typename ::boost::compute::lambda::result_of<
        right, Args, typename proto::tag_of<right>::type
    >::type type;
};

// functions
template<class Expr, class Args>
struct result_of<Expr, Args, proto::tag::function>
{
    typedef typename proto::result_of::child_c<Expr, 0>::type func_expr;
    typedef typename proto::result_of::value<func_expr>::type func;

    typedef typename func::template lambda_result<Expr, Args>::type type;
};

} // end lambda namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_LAMBDA_RESULT_OF_HPP

/* result_of.hpp
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
*/