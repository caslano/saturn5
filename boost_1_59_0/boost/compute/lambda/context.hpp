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
Yo1bleptu4DsBE7M/IVyQCVIan6EmdyL03/v5OWFnL5O31z7ZUUd71r+Dh+GTJzXzGVC94H8LItEbYQXkhVSXcupOG0f2EBwAZO+2ldhyYSkf19BwbF0CKOWIspimUKkvB7CqD0B/TifEIK3bJq0ngn2h/iD6SO8zgDBC4j0kZ3u0Ra5IUMsohUbTAAKWn97ovHoS2RlKdOcl6YIpypMIjYe40/7iDWk1IiqH4CRg+wjbSWVhDWjp05z5IM0XdUuhiV4++QnGxqun918hNqv8q83tEKGWsDF9UPd79/fd5W6zvsv6s+ed3QGje0dzlxaALKJRdGgQyE703kKx1TjkZlHfAFKV6q0vmDm3ZHkXc3qv/HxRj+VoRGpW6xzl3O6fS4Pm38XWx6aF34mh74nhoLxOlFqxRyAcSYQc1Q2lwwIWih/Om4l5Q4kZn6ZzjAWQPF/ghzvHrznkbKHrQOBKUspc92N9SCEVElgCESdakHMCDD7JQdB4ltiHyWKL+niaX0yFxDJWc/Aw0M+F9iODspZBE65A1xwtnJMFU2jmhVdp32yqmmnStKlOQHBWMkLCym3LaMY5LjL7WcqvCmDSnmZBHTLnSBNSh/mfYaWJh7CGGI92f5G1V3CyheN9B8nOTtsQPlP/pNF4xpM2f7Hc93P0Io2/tsbud4Gdu0PIrW/frt/ulNyOUE7AwNwEWvI0U56NahFyR8imdvZKwQf2aBoTkq6Z4qzWGVnrrhNrgY2vufeaPW1NLRaHq7bNcRPMne824K2sh9iAJSdWTxZ7cPUvy0QXqdPmUR46ictBkvyjof1AsfpfU7J+ObvQc5In8vcO2+k5xgnrF1l5L5BqXVx/VwIGyYphg4T3cXzdm2xJ/G2BR2g+cdUC2DnnPtEcsLsjQSGK9AAWiq1wdROICaX8qOUiJpRjRGhDiQ7JcdKqeQHhxUCzxojCzuSp0T9YMxxfL2wMMLJ1nHYqrbla1Ef+JYH2dUbvzg6plW+RWNtgKm8eP5t9nu13x2/h3k+9foXPLDlpfp+DjxGIyLPMpbNDHPNyYSFAJlqO6QvJ2ozoaT1CHeTnuX7VgjSkFSivQiYD9A6Nm2Zc7vbnQ2dyz0uv/XqHW3s6de4Y+gghV5Bav0gK8O4oswvRThTLTSpzgoFdQpJkc4aXyT6E2mLT0KFLKS5F9kAgtK5NM1G72MBnQI6AVJxqnAnyGBIr7UGflHaCHxnyX3zvadyj2ILQfXQwaHZYnd/PRIIqltdK02F2llmwuXENlBFK/DNvJalHwVAwJI9hpThZ16wSGiStsP8HWihagOPGT2AAqJCVcxucXZ9mOIaSBlB1yrXDN04+VrfBydMaBzOaCZlHuY96edFOdgt1kf3FDywFTLEAiaLti9HnfPefup4ODTfv6y7hrrivQz502adZqlog4Co21ViqjVhOtSxg9gFzpUkHSjrjOGoU/eWCgCpYjAyV8qGVsPzul18S5Y6XO7q9R35/x4RZqIs8y1OqtM0McSmm0NhFEOc8wpvk/d6oVQhHPUgwC+MJUeLAZAdgp4wL0IrzT7gwZuvgtA+SWwvfZTZE+zdEvZkTwX9QWDpOUtEEGm4f3B2lp2xVX4mbx2N5DmGAwA6EfeFRAAyPuLoC0mJS8G9zOkGqzLocQwWDO3Y8wyeA1zB5kAI6tRKUk2m3YDGKCA4D+hcRNcBZ1FSWHTeP2DDZDSsIYjxoKYaD0Kurkr24xJmDLuaKwsmrP1ieC4SxDcb30zXsBbKNECBj+/v2yXgumWi2CfTN0lv4fr9laO9Z+uPUkx45Vn1g9yx0tH+msff4c72+xkJLyLu3STMhzFEPNbpTEYeCZj2BTwtrtu2LmdlWBV5DysqFGSgREJdc2Juw8WGw57ruxuMbTkpmXJ//XjqsqH2Hbz6HnDsRj2UA6QZUNYawnlnVQZ/VaARzoY8Cj7E3uc6kcgGTZWY+QTrSJ2Ttof/OqJEByDBFUA9C9rMtzDDM5yeB0oY6gMWLl4zifV1gD2ff9XciSwPFQPm07Abt9oXSwIdt8FbsaB3wca5sr286WZlpILNvqGmgQhLqufnWZ1FzM8FSgEsxBJdVBjarr2PgNSDzO1GrRqqrHyzwWwpeopmDBIZICF195sm1Z9Wv9e58x2Wq07GSB3XZNS1Jq+QA/8GPJq0GVTXFhv7/klPmSBOnXMQkeMDV58fWPt6hetHUlH9q3Dndx3uf/p5hzPbqufhMfj4kQNJhPScN8UzLaArbJdy1uEf6ihF73pWoMSzXD2bGOckrh1wooMqTERMEo05NrQZbqfX6ebofLLZE5x0aQ0vTxZeTbNMKulLKQCsIFbtDqVIKaZaXkPgtWCIE1j0vsOoPYtMVHiSvIXIRIv6jLEUmWcAKRwGUcjjRAYIKKTZzgGXQwXIKrxOMs/FuujOpm5WHKc5Fr3dQcVRuA1yaLus2b13UOR0kxLqBq7g2nmjhm2jwtr7zOhTXzfyZTL+6BsH3Lswsgx4RgMauA+YzhmoOQVyFDlhkprskIwY+jL3YigFBAfyRfBSIKeIt0eIIc47cUJbvRXl7Sc6l3QPEMldjAocUmgV3KmGoHjF2npbXv+8NKeupglIBVEFw/Wvv4sW9Xz3tQGm0IOU8/xs7/2iq3diq/P/POr1/fz6vB9Y5BG6CpJrF3c17XNRA+W6KifWv9yqcalEqqPE0ObufEM0CwYfeA21CVnhd3u+L5bMnGS9wstd1vFeEhbGmMMkx/QAicoRowuFJGGH+B0g51FazR5iasuBGAhdhBOzXuFyaNJHyPVL2pe8lb8wLAEGAAwhcudtALRoaWHjwlyqyhyqaNpTHQLWOFBDCcnVihegtFdqU0NDU+/8PeQas6vaBWyOxSO4bKAdeHgwmDWSUsOPp2IAJKuwgEstGOfcR2kOe45rwFP4jLlrAup+Tp5/pjtLFNaSCwTQBsbJPH45T5CcoS4vPU/UoJgDAQyNkO00zoyziaSRsyUWTj+M7p5aW67CYX4GiQwQUeQL3srFZpkc9ag62gKosunPFIvOe2vZe78P3v361vfxtH8mPa1B2Qb5UxguHnxGGTW8tJyD0YEKqntvjpNy7ATU3jVe5rZ+FB9u6PY6FbpGX13TZ+99Ehn8U+5t3sbu5zKNo0rnB5tPACLpbLijPGy8PybJ+lKceIRRsGJQxSBz0ckMOVjfGFg6X7feLoqXsouSoTetHToOFh4kjaE07ZyRKnHsXtlET86SvpgnEt8Q4HGtvm63zI6+FY2hiZbKNWPXpXt3+dHsz1N+3YD0vt7DYIBuEyso5LQEAv8RE9APCqXMg5S63f+iPVBxTDPfFEPvyts4veZR20SXvaZGGmdpoRf/uoJfA0CVvb3SaFXvKEd7WhXFB82p6EbqUcjzDH+hQR7qLJxcQ4ihiyPpz53eb7myP72NmnGWTZ15Kf/jDW6w0b2C/zvS13Q/Xcb3PZF2+7r6cz57cL4rmDdAK36uhA95pjk8iGRi7uzY5C/K70rfSYcPOKpzMrV7xbUclIsK8UjcRs8XqdXndrawcOzaOmKKZ1F7WwQdh9aa3S5LHGEnUaw5DY2KA9EJiyKgGSVSoQ6acdJVPBTZZwD6kMCBpH8uKPcoVeEASOu7LCu274wUEfJCAg8PzoF9ON/d2dPQ2N6xrqWlfUvnVLTDjTkb/1Etxnc5E+8tHBjigZ0ByjdkCV9Io4riAWdbqhgcIxEvGhER56Sto0ngdFZC4rVF14FkhLVWEnHGxkgX5lIFUDnIAuiaH9MhhPEpBmOB4K9C0iHnxLXUetutlrM2SL1nOqWmfGsyB616u8HnQMcym03szEXYSsoApxj8mYL62PKUQHtPZiCa9Dhs/PX9Zf77PjIyxe6/v7ftqfL5NeVDxugD9KIn/0o6cOxJ802B9QKbLTPGBXAiYnWu6tQuBKLC84zaWf2zUFa3q6F7refr+5o+EkGuzEuV7Z6JijPqUcCcg4WNpFGATOpmZPKqEnf8TYCnnxzgke9Hup9MYI4BQYJVIUxnqhMLg7mjmFHI6A8luDIq40N9CAjwd96CpS1tSxp9/TXmZg5NnmESpz5na3bg4CuBaSoZRhFOYMQ+mU7tKVEdCyuboBTB1OSQe8wUD0CxJ8YDg5zAKS2qvogAFA3jCxBJVGiuB/kjSSfijPDWMKtNPmhon5YH1GZhfBX7q8I57C2dvaIIzSsjeVUWPM0GXkRyFpJDb8OsewxbLY4aLJDjRCphYmKWMy1WNYQ9cLKrbEY3e+1n0v+1LpfXyiXv+7Gn6AF/jxOG8Z4mIqr4kKD/2MypEQG2YHixXHHXOALOl1ovIYLBVn/Dxp7P1fTzb8+33lGL+BgGtQPnSDVuIbZvxqeEwQb1qbbOGwX7Ijgdmc1cQM1zo0Qd9AVCP4qz+h/yZ6J6ktTjbiSkSk4cmCanav9CGZ4hSnQh46GmzJ9A6Ry1rJt5NbY0LWqHP3Lwbi7xoDng4uQdO5gqdEcL3+VwCiua3aWi1vN4wNHcTKSXIJ5ECooIijA7iDiAbNMn7WqC5RxJ+x0HAgBl455kiyeiSyLkSdEi2M5oz3TkUPt/9DQYe2IURIeXjUM+DdvzT4dR26PCq0n+jh8zZStTrnsEQdeHMdOfpWo1JHj0x1A3Fo8zkhq+g6Rt/JvvtbPlomrpaw8N3JN1lboGhUbzvqb8v4+6vj9Sfj9D18S5w48ipfm242CsfKZLzkEAidMHwRNEhGRUQhxYTjTB4uJ8Rl05QeJKonOkPova6vbwZk6v9H3zqxYdoqRlfXp6PSKDi0g0gyBGBrJzDrhkDgWCvIEkAVJ2UZGEL/iOPR0QIuRmj+P7Otb/hHcyVhgfzND9oXgsyULAqeSz1tnT0zyzfqmKucwBdsve5MSZhuNstCWos4JJyOp0QicOxoIQsV8qfLPuZLuC0ASTA0ZZhbwPiSd69bDQbrgxg2FrOCMYjrn4WWaCYAReZ9GBYLvCWYJ8yL2aTrcvbASCCJqDNN+EFTgtZozVuDRWRBM4jJOP6gkAQuYJRkeTpI2wI6JyHe8ALYDK1bs/jFIWg47BQsty7sixcOaP/TcRo9wB0GhXfgT3fWlLy/vfH/G/PRb9HN71NXJ7uay30e4RfIz8XAbMIOhEyYURZt+q/3lVGluEiWXCDVm6w98gboHfbXfw9Da+Wb2Kh6Oq4+PKYPA9TI8uC66VAOGSO/zzBOIelPTOMzKYrc+khBDV/4cD4wI5BI19VAPO7ieIEHQSG3b9Ssga41WDG9Q8ygrRPUqTFxyQxrqFGntnJbqK+ioGAHpTEe8abwYOnLhY+Sxhnw2hfpiGXQGHqa651hGrmex1cAuQvxcFkJT/8Ti3YSgZb9lyC3AwATxILjC0U8UQiz4RWQMQ5wmskcoHi7wZpXFPAGBG1x20+kPrXC0/l89gi3lTMF9Lj7M7Rq4fgQaayN712spmUS5OrVVSpKBHNTQFb/RQdv+jVyJ0yVEPJpex3KftSkcfWiPv/cW/s8fh/aOs1+W1/qNDHb/Bl3HIFBFkWvtC3avpyjtttulCswA7gS8QJjwizOekfqMijkGrmrnuiVd+z+PDhEPLK2VlLELNUHYVuQflVwl+Ukb5QK6WGFEabmAAIKJgpjHuAAGdqgMdBI3sjSB/GV1mir8MiAwOLK4zirH3mgkxl9LGttaFO20VnV0NTavq3CslR5jt0sTz94GA1lUMnaMX/UkCwR2AfFKkwgPoWYb6NGdf50CTDuOJdJivPUjvko2iN9LBAVDqBTBJoHxfj2ZBq9cAEan+HY2wnwbDU9wO0xIbXGCUmwUSABnYE/dL3ABIAkkJJDa8HseVDpiqRB4gIVUwF0oKjOBoIhbWNDOXmlPBsbV7tR2kbRYlKdqXPfhKtj/KrbSH50P9c9r+ewp7ZXbz9fvh+2gCva8Tm3ZKBR637jk5R7AbgnS++15nNiQgJP3P1JMzUvpOysfYw4ug2MymMvparU01/Y6Xbxt7V9eUGeYTFxoQb7cjNlAMGB9VwjGVANTgiwyUKorMGkkskqe6HGogNnIvu+oHIB/f4E6y/iiQZCi1mK8LNhraoaq3p63jy+LHIhexj3l4Hce+KD/35asZLljwz36IVEdafjDUzEFXAXAJhk2WxqbTLriFyD2XY0GEhSQkj0o7lSutfccluyi3CLsos5GGCmAd4ZCrWVT1QJ4lvA+zx7jkF9kajSByALzjvB8R/YnSIZnCS4RUvgbUE2u7M/Jd6Jtd5sCGh/pR3Ec5Kf0HAUfldqR3BwTz5cmXNpxT0HWXGs2XVv9HqP+9P4/3oobX32iPRv93vs9adCL9Z6GHuQV9eMfgro2w0Pvjh6j9GLGzMLuRFC/0xtFJoabv69iaMnmyJdMca/d4sAXyAdZld4RfgtP6Y04mqPrMUgtaExCcQIBZhgBSjJw5qWBQXXjE5FLPeEA2CoKIYClpgoL0pVcnrEh0Z//Py9XF01Ejc1v43wpdPopeZweesZe4uglQcaVGobp6ukt5hKLncx2UgCCsDgl6+AeUfWi49CIUFTVkHK3nQYZAu5N8hGKpRCwGFFBWguSpN890HNZqqGGV5KNtpn280SOicU4YMxm8MIYoDPRTY7yBigDh3LGZCHSjvGAS+agBRp3cxXpkY3Eyad1JnKZNS1IYYIjEiMKCF64WMrGV8bOuP849yPV2O50rb3/0v/P4WvnLd74G1eHDMNBKPfjHxA+k1Em9yVIDsw/07H9KUxzl2IMJc5/UzwlXXnV1Ojw8rb8juz7JU7q6eH0WR6vzBF7zX+X4oS+nRB0a3U/BN6N2X/Jj8oi5BJ6KPTCm2KL+NB0bCKJF+IklWTh4i7YpHWWos6dt7mijr7VhpKexyvAc3nmUX2SXBYWlPdcMSSHhP8o5t+2b7CDPbVeoFcr3k9xLA80dCl83huU7ssc0VDvgyG6CIpBM7wdto79rgR0EwH1F6f/x03oAEIQB2y1CDXpyjHaCUukww5DlOeTJIvNIzQqhUK8p4AIyaMc+URuLZhHeHs5L6Ablx0Ebld48tn3/cuRASoWRmOVOsIWdn6IS9iPZW1wiFszyyiT4pQNZ4waoGl1Dz5r7ff+9Vnb/a66d5/1+kCCfOTv5XmlkUrSgFE4le7FQEddeNtuKOELIISJ8VuOTFgoVG8/v+/1dvqat39HH79dfKArJzymtwJdjPRY2jxzpkUPcnVP1EzJb+iij0Nx0pLurCCSZMFJpkLikkd9Cy8MwHmmIUgnz23E5slJyMmW9Q6t0wcfBkcvHweN0SbMMd04eoQMVHAxWJww+KM7opk0kz0Q/abnDm5Y86APnQeq1hyoWhPKQzk0XTQ5nuhoqCbS6FRj/i4CsB7I2ad4dYgGmaNwQciy5p7rY69/67cwvHAtXrBqSzaFWF3IOSFOrnhwqDYA5gtiRvOK+MkOkH3egP/4tARkcfUP2JuKOIRnFQ0RJpBgaQQ1OLGiflNtfJgcw64Qkq+Pn7ljbBqCmBHSTPzYyE/8zDL+3gU/300e/jQ9Jgy0HJ7okKj628MRc8GV3f0ELGQd5sO6ytJOS3qalW07H7331yAz/13tG/b6x/2UeoU7kzuFU9VzoOdeooDBfm0Z62XJ9H0LB
*/