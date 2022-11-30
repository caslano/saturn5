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
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
*/