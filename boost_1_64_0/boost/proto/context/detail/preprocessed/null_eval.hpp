    ///////////////////////////////////////////////////////////////////////////////
    /// \file null_eval.hpp
    /// Contains specializations of the null_eval\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, 1>
    {
        typedef void result_type;
        void operator ()(Expr &expr, Context &ctx) const
        {
            proto::eval(proto::child_c< 0>(expr), ctx);
        }
    };
    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, 2>
    {
        typedef void result_type;
        void operator ()(Expr &expr, Context &ctx) const
        {
            proto::eval(proto::child_c< 0>(expr), ctx); proto::eval(proto::child_c< 1>(expr), ctx);
        }
    };
    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, 3>
    {
        typedef void result_type;
        void operator ()(Expr &expr, Context &ctx) const
        {
            proto::eval(proto::child_c< 0>(expr), ctx); proto::eval(proto::child_c< 1>(expr), ctx); proto::eval(proto::child_c< 2>(expr), ctx);
        }
    };
    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, 4>
    {
        typedef void result_type;
        void operator ()(Expr &expr, Context &ctx) const
        {
            proto::eval(proto::child_c< 0>(expr), ctx); proto::eval(proto::child_c< 1>(expr), ctx); proto::eval(proto::child_c< 2>(expr), ctx); proto::eval(proto::child_c< 3>(expr), ctx);
        }
    };
    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, 5>
    {
        typedef void result_type;
        void operator ()(Expr &expr, Context &ctx) const
        {
            proto::eval(proto::child_c< 0>(expr), ctx); proto::eval(proto::child_c< 1>(expr), ctx); proto::eval(proto::child_c< 2>(expr), ctx); proto::eval(proto::child_c< 3>(expr), ctx); proto::eval(proto::child_c< 4>(expr), ctx);
        }
    };
    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, 6>
    {
        typedef void result_type;
        void operator ()(Expr &expr, Context &ctx) const
        {
            proto::eval(proto::child_c< 0>(expr), ctx); proto::eval(proto::child_c< 1>(expr), ctx); proto::eval(proto::child_c< 2>(expr), ctx); proto::eval(proto::child_c< 3>(expr), ctx); proto::eval(proto::child_c< 4>(expr), ctx); proto::eval(proto::child_c< 5>(expr), ctx);
        }
    };
    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, 7>
    {
        typedef void result_type;
        void operator ()(Expr &expr, Context &ctx) const
        {
            proto::eval(proto::child_c< 0>(expr), ctx); proto::eval(proto::child_c< 1>(expr), ctx); proto::eval(proto::child_c< 2>(expr), ctx); proto::eval(proto::child_c< 3>(expr), ctx); proto::eval(proto::child_c< 4>(expr), ctx); proto::eval(proto::child_c< 5>(expr), ctx); proto::eval(proto::child_c< 6>(expr), ctx);
        }
    };
    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, 8>
    {
        typedef void result_type;
        void operator ()(Expr &expr, Context &ctx) const
        {
            proto::eval(proto::child_c< 0>(expr), ctx); proto::eval(proto::child_c< 1>(expr), ctx); proto::eval(proto::child_c< 2>(expr), ctx); proto::eval(proto::child_c< 3>(expr), ctx); proto::eval(proto::child_c< 4>(expr), ctx); proto::eval(proto::child_c< 5>(expr), ctx); proto::eval(proto::child_c< 6>(expr), ctx); proto::eval(proto::child_c< 7>(expr), ctx);
        }
    };
    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, 9>
    {
        typedef void result_type;
        void operator ()(Expr &expr, Context &ctx) const
        {
            proto::eval(proto::child_c< 0>(expr), ctx); proto::eval(proto::child_c< 1>(expr), ctx); proto::eval(proto::child_c< 2>(expr), ctx); proto::eval(proto::child_c< 3>(expr), ctx); proto::eval(proto::child_c< 4>(expr), ctx); proto::eval(proto::child_c< 5>(expr), ctx); proto::eval(proto::child_c< 6>(expr), ctx); proto::eval(proto::child_c< 7>(expr), ctx); proto::eval(proto::child_c< 8>(expr), ctx);
        }
    };
    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, 10>
    {
        typedef void result_type;
        void operator ()(Expr &expr, Context &ctx) const
        {
            proto::eval(proto::child_c< 0>(expr), ctx); proto::eval(proto::child_c< 1>(expr), ctx); proto::eval(proto::child_c< 2>(expr), ctx); proto::eval(proto::child_c< 3>(expr), ctx); proto::eval(proto::child_c< 4>(expr), ctx); proto::eval(proto::child_c< 5>(expr), ctx); proto::eval(proto::child_c< 6>(expr), ctx); proto::eval(proto::child_c< 7>(expr), ctx); proto::eval(proto::child_c< 8>(expr), ctx); proto::eval(proto::child_c< 9>(expr), ctx);
        }
    };

/* null_eval.hpp
z1WwEzgw/ifHtHviEEmvMlibmwaIaBUnekLgALZS5GcC3ngCzP6HsJ2q8VbdJgd3hE/9QDQX59kXY5/1Ml2b+nhtgYmnIjQY8H0YBEb3hIl0TzLhUFwYemDUZyr0+rLYKPXZKBduaDJ1w4JI9SM5Nc3rhWbZe7Y+y/AjFEObETlDAQlEvsMvJeMrUMQgGW7yIy/qyAYUTk3ivTHUNuv9wVs2pqJ8EHT5HJ8pFg5QAknAlwqbZVQUYEWDnU/DMIQgFTZAU2LI1DKsJSjhYDMdC6ZQ3s4BdnDSR3QYCmc3lF82ApTE5MYyHyD0DVEvS4b2acAHDnxQivaHbtZU047IJux6x7e1r0pIFiuIlQo/zAZ4sj9NTH0GUcp0kg06RU8CBE2+baQ5hOO8jMJBfT+hlMaPwPliGO3yXr2tE1MfNtQRDmoSBHspeNV5Ak+0gF5t4JbGi2+z8T/qXDdwwovklGQcYN7fiGdIMvprR+60oTKSP7zbIZXzUf9k0nirGznlcmo+xM6gFrSjzx0jURgqsk0wxcWYZ7hYwZwRyDNCxTc2P/FwO3lkFkTk6w==
*/