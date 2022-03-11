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