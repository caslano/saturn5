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