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
eS1WUISNjeiuECrb0BZixxxaqPpd9uNJIw9E5nyyXLbIz4zgtR53x9Ym0XNPF9X4vNMkh2SbedoxHtThYTUCyskk+rnRq5XneacpjxCHY104vDEA82S3BUqJroI0GHI5MOa8Hh8ypA3U0RgMNLYEaCGncAQ1d6OnydPoaJGJ+EQcF4EIdE0udafmdnjwqDhcbuj8nY5WTxBj4A7yur28FaQrVMxJj0JHo1/r5NNuM+UqB+ww2Vz0ur9jw5QbYu26bTV3V2/asmF1qdWxWtYsXyYlleRAJTyNftwkuT6+Rq3TESQbwcp2PJAuh+bkhkC1HT4/W84WugMBn5/oe6J+IgHdTw5vA3LyanxiV9jq8cN2rxemtgc1DONQEy0nNFOrJ6RhOHCqi+aKCeWt5Gh2hxo7XBRgy0J+5M9pdhBIyA8R3z0ibHCGmO8SNnCDX4dyMJiENTdyXTwh7ji6aYo73NxveIBafe6OFlpKXuGYSXQn0rpbHBgtXGluJjPi+X1Nnua2gNvhc+Kx6XA4A83tRGtkfnLqyqncU88SdoLTYvh97rAn5Ajx84W5ghzSzQDlKE2Tcjji/naH3Y14GqYnuhy2BEIODEDI6FLcCQIbm8Sc49Q8Jd5gSYfHV4J4JUExf5S05nk8zYgRaPOFPF53fpQZMbzsHNfQGTpbHNGJZ9GLg/udqKn3bLaglfGGFDpLPi2YXKflsLVyQ3lN
*/