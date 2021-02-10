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
H7JQ7nF1XbOP3bq6QfnqYfHq6ILW6Mnrw0XZinRBzAddV91mJXpN1o5UUfS2P3GNHWaEO7vWIcqJmEpp1dV88VmYc2qnngUUGF5o3LM4fn3+77r4CKooAmg8WyOSYcWCNF8fydMGFI2Kfb6ssUAxJyTmea3rK1RFU9hZpBezQllihtomBZMQXASPsYVZ2O3oIAQP+ryrMaydmJeDkS9yNo543BOBePH68s358SUe3amvRt2YXmTTjXOfpgJrJlXTsewS01ar+t9N195c3N1USbUwAKwFMkBGb+RTRgIiQhw9JgRVYlBy2wuu1cRNDZbve4pAWcaN7lLYVW8VllJOp2srAtcLpuvyijujmKPXTwbt73UqjBGDbjPwSY1nVrvuqZPgcxTq7VYIbbHXFgMn3jS9QRzKrRSyx5CZ0CdZ90AHu5BXkY0CrCCVCqFCjsDsSp0uIdsNL/WCuGuUH4zB+lbiy0TVbcfClX355HXwsUC+HmUWQ16KAXZrgDTDdVNOrnd07Cy62tWt49dnF67whhf4i2GGdicwnofUb/Wa8Zz60XgptNr85hoNSBdV3azvC46NF+ns4tZFolyL1fqht6Hrt+V5vrxQ9Pjk5dFrojdod+XonachEc3Zaf+p5ZatQkXqNaolHLVofGPd
*/