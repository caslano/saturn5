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
/vHf9seMsZz93T+3/P9b+kN/h5eu6+qfLm0+/8Lt7b+s/I9e/Eh/f8VWR7Z761+3L+xXvfUv+5zfutW9/oafb2+/YruPIBL/OcLLH2/xI/1G3tT3T6vtvs5X68Y+P31hX33//Xd2ZF+/fP1yaM+SMneFnTWuXLh6NbR/y/g3/1gnnz6Nvfv70LrGJsW4t+B8nXvrq2XzkNTO0s9FnrrSu8wm3mbOp3W+oH/kpW3Wzi7zwtnTq+tfppc/De3DOk/Xus6+2lm/rnZFZtfJvbO1S11+L8tsk7qx1ZJWoPWz3De05q7Jq3JM2zvbuHrjdRkQkRS+ssl9khfJgrZLGrtumq0/PjpKd3VBJznKqtQfpYEV43WzOTjVL0TNJtnbatvYprI774YWzw/tpsryJf4mFtEvt7tFkfv1sCOLNiyzo6q23hWFLkev5s7LEZydKbeGeNJuifq8wV++Kj12e1hXm96DxFZdaLmrS9qO2ELPZRUxfmh3ZeZqfp4ZEXZRLjPLf0dkHe2ZrUqiyg5OZnY6G9hF4nM/tB+m8zdX7+b2w8nNzcnl/Bd7dW5PLn/R9X6eXp6RbuS0a23dp23tPFFR23yzLXKX9Tb/t1q6Gc/fkL4tINaRd/RX3uztN3bw6ht77hak16++G9iBPtH9
*/