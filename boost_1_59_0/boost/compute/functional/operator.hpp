//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_OPERATORS_HPP
#define BOOST_COMPUTE_FUNCTIONAL_OPERATORS_HPP

#include <string>

namespace boost {
namespace compute {
namespace detail {

template<class Expr1, class Expr2, class Result>
struct invoked_binary_operator
{
    typedef Result result_type;

    invoked_binary_operator(const std::string &op,
                            const Expr1 &arg1,
                            const Expr2 &arg2)
        : m_op(op),
          m_expr1(arg1),
          m_expr2(arg2)
    {
    }

    std::string op() const
    {
        return m_op;
    }

    Expr1 arg1() const
    {
        return m_expr1;
    }

    Expr2 arg2() const
    {
        return m_expr2;
    }

    std::string m_op;
    Expr1 m_expr1;
    Expr2 m_expr2;
};

} // end detail namespace

/// \internal_
#define BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(name, op, return_type, arg_type) \
    template<class arg_type> \
    class name : public function<return_type (arg_type, arg_type)> \
    { \
    public: \
        name() : function<return_type (arg_type, arg_type)>(BOOST_PP_STRINGIZE(name)) { } \
        \
        template<class Arg1, class Arg2> \
        detail::invoked_binary_operator<Arg1, Arg2, T> \
        operator()(const Arg1 &x, const Arg2 &y) const \
        { \
        return detail::invoked_binary_operator<Arg1, Arg2, T>(op, x, y); \
        } \
    };

// arithmetic operations
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(plus, "+", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(minus, "-", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(multiplies, "*", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(divides, "/", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(modulus, "%", T, T)

// comparisons
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(equal_to, "==", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(not_equal_to, "!=", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(greater, ">", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(less, "<", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(greater_equal, ">=", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(less_equal, "<=", T, T)

// logical operators
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(logical_and, "&&", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(logical_or, "||", T, T)

// bitwise operations
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(bit_and, "&", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(bit_or, "|", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(bit_xor, "^", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(shift_left, "<<", T, T)
BOOST_COMPUTE_DECLARE_BINARY_OPERATOR(shift_right, ">>", T, T)

} // end compute namespace
} // end boost namespace
#endif // BOOST_COMPUTE_FUNCTIONAL_OPERATORS_HPP

/* operator.hpp
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
*/