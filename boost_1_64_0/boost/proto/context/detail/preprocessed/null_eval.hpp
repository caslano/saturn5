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
Ppf4raCcOchs8fzd566EfUJdrDLL7tjxPqVvuRrB/C7XowQf4rVrIw5Y12+79wqfM/x6WD6OQkz6ee+bCYZZAJtQxXr4R25IcK7KDTb9527M4ASjPNw37WFQ7J5sgl/zK26OsLNjVTzPRf6dW2A5DIzTLsMLTejfj8bfHK7M69iQQPPl22C5u2+4nod6Lt4FYaRKDv7Tl+dYPvIvPN4XnGwfLvX2FZgdjvmakn585o2goya4473lz5pPD+KfKWXzRlthxm/Hj4UbJtwxvCscml32jGDtru5u4Lsw+oQ84zC1Y9iMMP7vwb728KFPxdHeRgSc/T0ptdF+OrYvL02hC7iLiftjclTcFdnRjq7l46PdRTs6OXhbf8tT+BlW6Uxnua4EPn2ePDHIp3luYHsmOzjFQDRxuM62mlvp8Vhqnz8TxXyojEoyVaOf4CD2ysB+sAJM28kGfQSHVdCdnb7r0T2fX+TssuuBfxMRr4dv7sazH+owBuIsl+1NV0lViDhe3zruu888TN+Ffxa3Zzzb76VpsqihYrcnQTnz8WFzW4C9+U1mfHOCn/RR5O+iH7M5c92HEPyTg/yKMrOqru3Ub9/T49d3Be7RiYICQelJ1AX4e3XEu8QEbCrVmYuM2JPOmf7n3nZvcdzbOEGLgdfuLN37OK9GyAz+1I3Ezxh/Pp7bmtPMF2mTFWht6KP0DfNUXvlTg1z5Zapkrkhv3F9Px0M5YetwU057osUE0qihZ+r8mZWUdIGfGuZlyjC7N+Z3f4JzM/Kjg5cLz4Pf8eaj+rKkg+HA/FsrZ6ltYQ8SHFclolZ5Z2qLd/n1LTIswxsEWm/50TlK8QyR1y7Vu8N5ndRNg9cR57YyGsbyujAYzypVui2zJrITjEhn9ny+mX7tmeUzW7OwqqFIE+zGT2Iw8NbksLOeDohmz2xx2L0vEgyIehi9J6YeRgPQrxmomugvfw2ueVfeL/qdG9O44N7s/A9gNs5s+Fxe0RiUQndpojrbhvhqZpvm1DAMHb9nvCXiYwQ+l9nCtmRr1d8lt9jI4rwJmh34hveidRnxSkSaNGlq8gbtixypi6rJiM94u+OItsFkxEnRZq3I4CQjvRQNYd8xxkcYuidwPlKi4iEtkjT973SPPVsxc2KB/Majfb4T6K9eNnkTtQvEAsh9DJuZUzD4MNPONvjkMK7QCc5zVuO22BbwHOpmK1uLkd12p7qmrRKFeHgxie9tImpnIoy2VV2kVgxawx6koKuhbe7coH093tbx3HjuYSzH8yHXRi8kSxhPoy+/sjtPyqXFvsyfMYtJBnhEf9Vgnw+YUA51PvEQzfF+ijO544ZXQDk7LAsuO83cE2icfQD3ZL2uj+H/0fhtLUtSGD8buRFOejCGM+Z7QB/NoyapZZeXk7ExSEsS8+O5jv8StaUWZVLXhalrFvcgtj5b88GGVzPyE/nYwD/VlBnqbPq4DRtbnnCal314YzjH+XTCqqqV2qT9GwMmTYbfBnFCLkR1d0J1pTFdaw+O+YCbPPGai2LUfy/ipYQuukZ1SRXiDPCuDDmH+f6XiI8WGmN117mkWAP/fkiC/eThj/M11oJiJMubEl5QAbU/8bZoTl328UEMyqROqq5rhXLYcy7bWJz1EHzOfOxMTn9cg2LSWtWKR6+djWVL8fFhjp9U15lsXWyIWmVcCYOUzM52KepPDRPNJnmOdcAzPiIzXcHDonpakeZJhtkiRFyFn5c8OS2XSy9wPqeaus3Two4zaIbX54rkZo4rC9HZWsMmkYa8LExvU7pZyRzlo3zr7/j4IJ5AowuQdwytUb4Ceq6xr2zU7rzsOq0LLTD6IVDE7f561O5MdEYXdV4oF6c=
*/