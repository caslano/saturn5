//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_LAMBDA_CONTEXT_HPP
#define BOOST_COMPUTE_LAMBDA_CONTEXT_HPP

#include <boost/proto/core.hpp>
#include <boost/proto/context.hpp>
#include <boost/type_traits.hpp>
#include <boost/preprocessor/repetition.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/function.hpp>
#include <boost/compute/lambda/result_of.hpp>
#include <boost/compute/lambda/functional.hpp>
#include <boost/compute/type_traits/result_of.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/meta_kernel.hpp>

namespace boost {
namespace compute {
namespace lambda {

namespace mpl = boost::mpl;
namespace proto = boost::proto;

#define BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(tag, op) \
    template<class LHS, class RHS> \
    void operator()(tag, const LHS &lhs, const RHS &rhs) \
    { \
        if(proto::arity_of<LHS>::value > 0){ \
            stream << '('; \
            proto::eval(lhs, *this); \
            stream << ')'; \
        } \
        else { \
            proto::eval(lhs, *this); \
        } \
        \
        stream << op; \
        \
        if(proto::arity_of<RHS>::value > 0){ \
            stream << '('; \
            proto::eval(rhs, *this); \
            stream << ')'; \
        } \
        else { \
            proto::eval(rhs, *this); \
        } \
    }

// lambda expression context
template<class Args>
struct context : proto::callable_context<context<Args> >
{
    typedef void result_type;
    typedef Args args_tuple;

    // create a lambda context for kernel with args
    context(boost::compute::detail::meta_kernel &kernel, const Args &args_)
        : stream(kernel),
          args(args_)
    {
    }

    // handle terminals
    template<class T>
    void operator()(proto::tag::terminal, const T &x)
    {
        // terminal values in lambda expressions are always literals
        stream << stream.lit(x);
    }

    void operator()(proto::tag::terminal, const uchar_ &x)
    {
        stream << "(uchar)(" << stream.lit(uint_(x)) << "u)";
    } 

    void operator()(proto::tag::terminal, const char_ &x)
    {
        stream << "(char)(" << stream.lit(int_(x)) << ")";
    } 

    void operator()(proto::tag::terminal, const ushort_ &x)
    {
        stream << "(ushort)(" << stream.lit(x) << "u)";
    } 

    void operator()(proto::tag::terminal, const short_ &x)
    {
        stream << "(short)(" << stream.lit(x) << ")";
    } 

    void operator()(proto::tag::terminal, const uint_ &x)
    {
        stream << "(" << stream.lit(x) << "u)";
    } 

    void operator()(proto::tag::terminal, const ulong_ &x)
    {
        stream << "(" << stream.lit(x) << "ul)";
    } 

    void operator()(proto::tag::terminal, const long_ &x)
    {
        stream << "(" << stream.lit(x) << "l)";
    } 

    // handle placeholders
    template<int I>
    void operator()(proto::tag::terminal, placeholder<I>)
    {
        stream << boost::get<I>(args);
    }

    // handle functions
    #define BOOST_COMPUTE_LAMBDA_CONTEXT_FUNCTION_ARG(z, n, unused) \
        BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(const Arg, n) BOOST_PP_CAT(&arg, n)

    #define BOOST_COMPUTE_LAMBDA_CONTEXT_FUNCTION(z, n, unused) \
    template<class F, BOOST_PP_ENUM_PARAMS(n, class Arg)> \
    void operator()( \
        proto::tag::function, \
        const F &function, \
        BOOST_PP_REPEAT(n, BOOST_COMPUTE_LAMBDA_CONTEXT_FUNCTION_ARG, ~) \
    ) \
    { \
        proto::value(function).apply(*this, BOOST_PP_ENUM_PARAMS(n, arg)); \
    }

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_LAMBDA_CONTEXT_FUNCTION, ~)

    #undef BOOST_COMPUTE_LAMBDA_CONTEXT_FUNCTION

    // operators
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::plus, '+')
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::minus, '-')
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::multiplies, '*')
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::divides, '/')
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::modulus, '%')
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::less, '<')
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::greater, '>')
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::less_equal, "<=")
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::greater_equal, ">=")
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::equal_to, "==")
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::not_equal_to, "!=")
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::logical_and, "&&")
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::logical_or, "||")
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::bitwise_and, '&')
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::bitwise_or, '|')
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::bitwise_xor, '^')
    BOOST_COMPUTE_LAMBDA_CONTEXT_DEFINE_BINARY_OPERATOR(proto::tag::assign, '=')

    // subscript operator
    template<class LHS, class RHS>
    void operator()(proto::tag::subscript, const LHS &lhs, const RHS &rhs)
    {
        proto::eval(lhs, *this);
        stream << '[';
        proto::eval(rhs, *this);
        stream << ']';
    }

    // ternary conditional operator
    template<class Pred, class Arg1, class Arg2>
    void operator()(proto::tag::if_else_, const Pred &p, const Arg1 &x, const Arg2 &y)
    {
        proto::eval(p, *this);
        stream << '?';
        proto::eval(x, *this);
        stream << ':';
        proto::eval(y, *this);
    }

    boost::compute::detail::meta_kernel &stream;
    Args args;
};

namespace detail {

template<class Expr, class Arg>
struct invoked_unary_expression
{
    typedef typename ::boost::compute::result_of<Expr(Arg)>::type result_type;

    invoked_unary_expression(const Expr &expr, const Arg &arg)
        : m_expr(expr),
          m_arg(arg)
    {
    }

    Expr m_expr;
    Arg m_arg;
};

template<class Expr, class Arg>
boost::compute::detail::meta_kernel&
operator<<(boost::compute::detail::meta_kernel &kernel,
           const invoked_unary_expression<Expr, Arg> &expr)
{
    context<boost::tuple<Arg> > ctx(kernel, boost::make_tuple(expr.m_arg));
    proto::eval(expr.m_expr, ctx);

    return kernel;
}

template<class Expr, class Arg1, class Arg2>
struct invoked_binary_expression
{
    typedef typename ::boost::compute::result_of<Expr(Arg1, Arg2)>::type result_type;

    invoked_binary_expression(const Expr &expr,
                              const Arg1 &arg1,
                              const Arg2 &arg2)
        : m_expr(expr),
          m_arg1(arg1),
          m_arg2(arg2)
    {
    }

    Expr m_expr;
    Arg1 m_arg1;
    Arg2 m_arg2;
};

template<class Expr, class Arg1, class Arg2>
boost::compute::detail::meta_kernel&
operator<<(boost::compute::detail::meta_kernel &kernel,
           const invoked_binary_expression<Expr, Arg1, Arg2> &expr)
{
    context<boost::tuple<Arg1, Arg2> > ctx(
        kernel,
        boost::make_tuple(expr.m_arg1, expr.m_arg2)
    );
    proto::eval(expr.m_expr, ctx);

    return kernel;
}

} // end detail namespace

// forward declare domain
struct domain;

// lambda expression wrapper
template<class Expr>
struct expression : proto::extends<Expr, expression<Expr>, domain>
{
    typedef proto::extends<Expr, expression<Expr>, domain> base_type;

    BOOST_PROTO_EXTENDS_USING_ASSIGN(expression)

    expression(const Expr &expr = Expr())
        : base_type(expr)
    {
    }

    // result_of protocol
    template<class Signature>
    struct result
    {
    };

    template<class This>
    struct result<This()>
    {
        typedef
            typename ::boost::compute::lambda::result_of<Expr>::type type;
    };

    template<class This, class Arg>
    struct result<This(Arg)>
    {
        typedef
            typename ::boost::compute::lambda::result_of<
                Expr,
                typename boost::tuple<Arg>
            >::type type;
    };

    template<class This, class Arg1, class Arg2>
    struct result<This(Arg1, Arg2)>
    {
        typedef typename
            ::boost::compute::lambda::result_of<
                Expr,
                typename boost::tuple<Arg1, Arg2>
            >::type type;
    };

    template<class Arg>
    detail::invoked_unary_expression<expression<Expr>, Arg>
    operator()(const Arg &x) const
    {
        return detail::invoked_unary_expression<expression<Expr>, Arg>(*this, x);
    }

    template<class Arg1, class Arg2>
    detail::invoked_binary_expression<expression<Expr>, Arg1, Arg2>
    operator()(const Arg1 &x, const Arg2 &y) const
    {
        return detail::invoked_binary_expression<
                   expression<Expr>,
                   Arg1,
                   Arg2
                >(*this, x, y);
    }

    // function<> conversion operator
    template<class R, class A1>
    operator function<R(A1)>() const
    {
        using ::boost::compute::detail::meta_kernel;

        std::stringstream source;

        ::boost::compute::detail::meta_kernel_variable<A1> arg1("x");

        source << "inline " << type_name<R>() << " lambda"
               << ::boost::compute::detail::generate_argument_list<R(A1)>('x')
               << "{\n"
               << "    return " << meta_kernel::expr_to_string((*this)(arg1)) << ";\n"
               << "}\n";

        return make_function_from_source<R(A1)>("lambda", source.str());
    }

    template<class R, class A1, class A2>
    operator function<R(A1, A2)>() const
    {
        using ::boost::compute::detail::meta_kernel;

        std::stringstream source;

        ::boost::compute::detail::meta_kernel_variable<A1> arg1("x");
        ::boost::compute::detail::meta_kernel_variable<A1> arg2("y");

        source << "inline " << type_name<R>() << " lambda"
               << ::boost::compute::detail::generate_argument_list<R(A1, A2)>('x')
               << "{\n"
               << "    return " << meta_kernel::expr_to_string((*this)(arg1, arg2)) << ";\n"
               << "}\n";

        return make_function_from_source<R(A1, A2)>("lambda", source.str());
    }
};

// lambda expression domain
struct domain : proto::domain<proto::generator<expression> >
{
};

} // end lambda namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_LAMBDA_CONTEXT_HPP

/* context.hpp
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
*/