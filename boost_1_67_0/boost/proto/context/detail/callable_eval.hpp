#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/context/detail/preprocessed/callable_eval.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_CHILD_N_TYPE(Z, N, Expr)                                                    \
        typedef typename proto::result_of::child_c<Expr const &, N>::type BOOST_PP_CAT(child, N);   \
        /**/

    #define BOOST_PROTO_CHILD_N(Z, N, expr)                                                         \
        proto::child_c<N>(expr)                                                                     \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/callable_eval.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file callable_eval.hpp
    /// Contains specializations of the callable_eval\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/context/detail/callable_eval.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_CHILD_N_TYPE
    #undef BOOST_PROTO_CHILD_N

#else

    #define N BOOST_PP_ITERATION()

    namespace detail
    {
        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, N>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;

            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(
                            stag_
                            BOOST_PP_ENUM_TRAILING(N, BOOST_PROTO_CHILD_N, sexpr_)
                        ), 0)
                    )
                );

            typedef mpl::bool_<value> type;
        };
    }

    namespace context
    {
        /// \brief A BinaryFunction that accepts a Proto expression and a
        /// callable context and calls the context with the expression tag
        /// and children as arguments, effectively fanning the expression
        /// out.
        ///
        /// <tt>callable_eval\<\></tt> requires that \c Context is a
        /// PolymorphicFunctionObject that can be invoked with \c Expr's
        /// tag and children as expressions, as follows:
        ///
        /// \code
        /// context(Expr::proto_tag(), child_c\<0\>(expr), child_c\<1\>(expr), ...)
        /// \endcode
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, N>
        {
            BOOST_PP_REPEAT(N, BOOST_PROTO_CHILD_N_TYPE, Expr)

            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(
                        typename Expr::proto_tag
                        BOOST_PP_ENUM_TRAILING_PARAMS(N, child)
                    )
                >::type
            result_type;

            /// \param expr The current expression
            /// \param context The callable evaluation context
            /// \return <tt>context(Expr::proto_tag(), child_c\<0\>(expr), child_c\<1\>(expr), ...)</tt>
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    BOOST_PP_ENUM_TRAILING(N, BOOST_PROTO_CHILD_N, expr)
                );
            }
        };
    }

    #undef N

#endif

/* callable_eval.hpp
m9+DpGYPOFC2cvUKEFEtI0d6I+k8mwLMdY7xGT1o1zj2hykfANxMiGs4o5w6OUYugvbEawSaXuK6o5/09X/vm0IO1V1YDw7OOfKITKj/SnnEExvkktGP2oudtArGFbv1QKedyKZT44pdor1N7gr0buz5KbKFaOfkb8Th0gJNEp8sPF3uP6BeYKKUD3+S2AZLh9KpdkAGCyD0zlMbB4zGQn8kr3+sK2sH0M5cW01tcOBcBsaWMjmyB1GzB7Q2O7kqBiv0gtoqgyhwdNkUOd38CRLL20+jO82MwFjRJAGUaZYifIE+y40nHSC6d/Nm06Bnv4RIhGpvNp4E6hMvEO5vL2yWRFABFC6xy43CK7N1VArlE+1cnMKip0VZtVbkfsZwFtTwFU7w5nFWnuD1yUq1Fq9Lrk+3PsnNNy5exO/hJDvlMNFCvLJbq6iHlXFFk4QnyKAD7CdV2FpuRmRc8r3ag1hjmYj/QOhCxWGtohmR1SpazOGewgEHBhvvw4axJTLk2NfG+3rwsCNIG8T9HFUDW1adwH5wqx7simW5tFnb9FmnCmYdP2Zos7brs9bqT/KMNccCWx3HQlrVGm1WHT6tPMAKoZmRtI7ZbCi7Vq8DeIlfw9LsyfpsF513N8aC6xDRJeQ21G2xwDo6xBOorZufZUfUobWGeoAgQkecKhN/7uyBjyrbVYRy/S2NNZKIkCDMjD5jbGNG4tsfATPQgiuJaJ4ml8qI7zBv0Bm9ZxXN3crKnPGUaJeJeXSIyIQh37H4+dG6/w9r7wIeVXX1D89kJslABmaABIIGiYqKBhUNInFAgzBJvAxOiMyAmkAt2jjaFvUciJUE0skgp8dBam1r36LFC15aW7EqxIIYCCVBKERACZLWqLTudKIGiRBM4Hzrt/aZyQT1/f+/5/t4OJlz2fe99tprrb0uyxHSBxmehPYoamiLe1cWurfLVRfGruacok+D3LlU93VGM0fP9pcy5B7kLrTFu0BDMaTDxztfl+5rsTVT8u68XaV+OLdv9H9PFmfHWQxpXbSJ2rYCcftL87439VB2HaP7VmMHmNOVJzPkeQ/Y3pv9fXkyOhgPUQYfkq4u9VOjviftMHnAFE/b+n9ovj3kilXQoOhQYMscrZevnk1t/+7C7SF37EoueTelQaEYoC7brtLvLNtV96EFRxNzOz7kHrfoYzAFHFe8O4E89p9RCbHxT0JWH27/pgMMP8TI3k4APPJ1yZrOzDQMU/8kx+3+Ozxpx+7VWYmRttDW763JmajpVOwyrgat6qKp+O5K+lt2MtwwPObQfU+Iqw6fMhJHaFVZcSKGDw2c4Ybj4Z70JTcY4yLnfmBzi38PIvLp598mn7CLXiya8DVCX2PtYhPu63B/QLyK+zDum8WOD08ZUr3x9Ps2N66v6DpA1+AP5D1+8WziuYUDxIaHZNjGV0QNlZN/vOB16WExLcU8IXzwO/bioKQcF5g4jNNs1tQGGZpFIjfqQIHX4ar7FzbJakeKFCDq3lbdR9RMC5E5mlrv2eqqgzzBeJ0X/z8+xDkGL/rrLpH7w3rsVA9hLdmY7d41YIeS2FBtzXsd2EwvP5CntuSV785TRV75EaKcdWue2p5X3kZ095w1s2kDSkFj6i1Kin5ML1+v2/J3FvjqXU9sRdTc5zlGFR8Dqi/p3ufz1LV53jXqpMhx9VZ2cUao6xcXM9qZKUOmr+v4iKGY9vN63Xsgz7s7z9fZcRFzDY4U4rhd9GzzdduatVscsfP0Wxx5hDuaCU1rrtgITuMgCNOKHbFURKlMjxxXJtDrNGU0PipIYlWG6MXOPCIBd9D+GjtHL7YTMQgdhB2xQUiLInq0YmcM8Ua0YrtkR3A0ytG73/AHQhdCxpJ1Kzg69Q31snhn3h7PnUGRetCpu0KZiJEVdOQR1qFF/EpAvD7ydD89/ufhA0iPCcmkXEKjYPChxFHU0vHwLTtvHrHdP4VOTBCxPiDXviMOW99Fdn6n9ICpb297nleERjIpzDoYrZIgPgIlEW+bjdZoMBik1LLNoJa+GZZEew4QlxMId+qHwPgS8JYfGdgOVGeC5DWtif68cpEpdqoWEAo8DfJpWhv08ecMlAkZq+9jEUK3PqcTku9DeR96WquHRJ0pmq+7yYujL0bGc9r11rzyLs+HevmR6lE0e7ZtRBiaCTCdwNfUXQIifWQwNMkPZEfEJtH+xuM4F6pMBbsTZNr0pRcQCUsog+X8r+ftx5y5Y+6kYcguC+QfpgmDTm8dzmMAaoQD1JGeXhim9Qt6XHVwdk5vR+jpZf0RVV0RMKu/4BM01wbaq3uuaVRGfc9hEiIFDTjFAf0rAPReaQXNRGHUJ0rZ7hsHhaCkvA6WcWkrcEogrrwQyCDq69NW8LkCSHWtvE/KWPQuzzHlbFO2t5CqLCjvgf4ZP8Oc3tRqSD42HECh5zcEkglzAMZRSe9Lug48CRxlmTQtM2Nsqs7C9z0mOybeHM5wB7ALu5KQfrhz0hnnNOFZ2e7jRdkp+iFXBMfsBIttJiR+S2ZG6ax6EUKMJoPofJqSlrw57bY5Yrb+Xt6cNtucI7EMPZBpowUccINsKJVc2qNMhgMiEB33TGEA0kimIM+WAnMrrciBGSqCH9YfH2C2gyHotaFJpDLNTljYiUFSMksg3Jf+PYk591CO2HjJhbM4W7Lgxw8keA9bKlXjDkA9bmq/tr24033aeBlkpjo3Hib515Qpbwf21sKCoiqlQCuqShR8llnwU/0F/9HO4vfhOC+rhG0GTyCCMePcnio6UTQXURuVLgKHL0P2+gs+g1n6lTRJJ6HV8tlBWKQTw/Sz0OjbaWkoBaGJ4tTBPsQs7so/PAPHoTuUQXqz2HVBOsEczuoD0cdY8e/LwXbolGlFOVrFhFhBaKrYLjM6NDWea93f4rnCd0+ymDm1ihzxV8rcVAQxi0UMze8PCTkAX4Xv6rTAa1/4rm4LTvUl+kqCUhr8KS6MoaXQAiKmM8/rsAGcHfoGJt+vYQW7G6HmmK5PZmy1l8n3LiZnOpPJd0nexLnss2n/29bPXr/olLuA+KQdkaVMi4IBnCizzlDMCOYbRBIQ/p9SUJWr5PeLXL6N9Nmn2eWLCOKeZjXa6mbPR+qw2+O1XoFaG/MNvdHzkRligXrClehn85wPIQaNUQjmvMDbXH0bZF/9dL/kSqGrAd8I6kVx7koOgo4ljNB4EFS2QUmC17q6XV+FOpgJhleygFidm2oxvM2Rw67Ij2mj74C5nvjgo76EMmKSSMo8Tcs/zHzz3gFMo3li0OoX1v1wtUxYpU2/avWLo9zY4Hzd4Ox+i1M+xJ3syttjIyoMUW3aY7fo2zz7lR8i8tVse8Fcp3ptwdxsJUcnqmjROF0V2qLx2lznMwdGjXLTHmn1tsfG5PlaPb7OZTYQ9ZSgZJxMkzcEiTz71T8TGzop2Xh762BWsjz9r/5+JStZ6od0H2IeT9etBIqmtmZXdBO2k3XrMB/r5CJ8MHednJFomFWG5AywCLCLNqz5FYwxbxelg5PwS2kpywyJ+HYHWM+7Jw7qUmxohhp+Hy6qoUE8GCiIhbp7RP1eIr4TuJdNO3gWhJFB6LncsQXQFdmhOI83FkIuzM4BjzfalPP1xnFW14YGSc03hMXycPMoPztb9YNLf2nIaeN440TFrTduFfZwuxUvZ/BLp3IN3T9NFVDBl6P3iLy2jZ5Dlq2xlPCn1rLKFRiNJSZ4UgIWXf8BbfL28c6UUHQMSp2PuFpL3Tm842EzY5UUIqRrLZCxmxoHma+mD/AjE3kfNUlirHoABiz502+CePkSXhVYbO6qez3eFhkLMY9SEZUdYZFjelkoJWRJ6ANDjUJvjZ9ZQ6Mkcvh2VYWkK0kv5qHbpM5IBB5PJGpO2ZtAzS7DatGhFX+t/oh5JD+J1Qcu45Ci40NxtYsZf+5Xu1CGiZfWp1hig/vriVMYOCOR+jsmjTFf31PR8Q6cgX/HfgtzV1qAQDBHB0ptAInyqAk1oNo47VneppW3gyosTxaC7RGP3Ut1SDXgb4m6fG02cMztHFVPilxa9DlH8uZ027baOA9UhOfwzssyqXVypQXTkyAf6kw1ikUdZc6+OhSuf9Kgvy9F5HvEwd0E4P32/NCYJFpuzKSXR7ldEeje6BzeGNqG1H9sbX8+SesE419qag7p892ELvaKqrFxS4O94r6x/ZYGoJbyd3oa4Q+w2K0fogkbSUluoCQaF95UzIrtsfTwC3g0q/R4+1R75LByHtxMNvXC2I1Wqoi2sBDNGV7gsGAQ/9wLE6r5BRyPWZ1Q4O1T3AVcgDpWTnFslHxWXEnqXBH021wn3HF9DNLyXoOSpJhWjKXawi/gBTTijf20vGTldq58IqL1cuH09iK8+WIvMrz07QyytcY30tQxoYuX4HRydycW1+Nnm7Kni3R3QunO1IAFK8AqEPxijxlseI9w7WJEldjtk4HWnFNMlisCDSupseWKfEx/43ONdZ7AFsln5FL//yy53j29UsEKcJQOypqW8RGTjH/c8r+AfHxlDNy0mN8GT9sGT0eqm6G9HVRDEsATlOu/4VXSQkQmxItzWhPnBbkmgvj4XWY+h/U3LGCsnsmr2aQ5p9kT5z/R1+T5PcR7fuN+UxQfvjCuls72EeaaIZpLqSKe5mz1AewLEmkSDbZH/J7mMlYuYcycxNvfTUziP0YnNCcLJMXcr/kxXrcFa3dAAzOuSxlKoW2ujKXawJPzI1AzZXifvFMCaoL8nziA/CdwheIr7Z9MHR3wNLnqTmFUhxFPYcwep7eCwonhDTcCTo/Aih0CBsS+KTUvpTckmaSSkyh3yW2VcXoQLsUXJR5L8MjjTuhH3E1PkOm/dwU4llYZWpUYJWa56P26bJ4ap25DzEpjNRSpWXVoeNppI55ouUx0rmxCq2wColZag3wIHOSW2UwI+y7WRkYyjOsjnEOPIZspswcdxmPbg06qB4jw60+MEduFIXQHg2VYYth6YAxjRX9kOvCB30ltynM85g1ZA4sqHQYja6lsasYoh4jK14W+cGzShFgoIVkxFZowLlezjTbN+yOpp6WPfV6GRPQObuIA8cCU+oggOMZdxuPYQo0N8ggpfm4US+d7/4IE+XW9Nb4pBPSrLNmj3ES7XxDUaxz65KB4sYlH3l0ZSZX6gUHJ/ROd/s/vPoIKmjrPP25KQPtHIyHMYPHMCWXG/3II6GTut58fUEYmK32lFlRnqnZ9R/IBXMSCxsPDkrR9MRm67QgVVFHFO9F5enEuFXW2pOqmMkQTjlyW66npP0Ekjs/T+F0cHRElrN1Z+UMbvxUFbVB9zW+4vV86teAMnjv/cFDzbdfUzZ5jaqpW3hBL04tyNW8DXLB5bDRzK3A0RPVN00vu03zNnl1KfnTRrcwShOzrEOOR2QL2bak2w/jWPBnuhE9z3ICgRbD6gUYli7OkIHO3p5HVKllb96oD1I2ykGt+LIdgmB2zZm2Ww9smn7YjQfwbTlIO6lcVoibc1+vVu5mAk1tjCJ7aP/CLO+nX06OkiuL9cNxCFI93OyEBrbz528dVLN7vtkknmF3v9ehdeUejN6aW6if9ed8YWSuBIrNQoV9koFjvbvXeMjiQb+lv6mzde4CNHvO2KlfRlVlSolxF1/UyFboQ+xurGm4PZUHBIK+JmnQkb4e/TMxLOW3EngpXt56t/jY2rMkLbGaJOQy1VXx0mAh7iaTVhoSm+ayC8mblOt27uaws5E4wemw1Ao83VIc4eoga2qiMi7904GXbIVY1uQj1DdZ9m0N2cZP1tEGlSeVB/SpOfUwditR/QWoIlEKmzcnGEXHvQtGVU+GA6AbT3OTppA9QjIhNNC1NIkkfoLcSG2VanNwX/zA0uhJbi6HuFn/5GdHG6u74+k+DbrrhtxOvmcAFk09lJHCBZA8kdDn+QWVmj0how1zPEGGO1lVEr7Ubpzj+nKkRJHN12jPd4pPhJr0yVNp6vcQacSqRc0ATSefYzmc6iUGULg16JN8dkO4DEbwWrg16/G+1UxKRuwVCb7dFySOqT7RuA6LhuhbH6xqOTR6no2ybg6G8Ckn/zEl5qdwEfxBSz/QsOJJR2NTWcHu8TtbgD4hDv4VScA9RQouJvOzn89jDMG0GR8UyxNhiWwXTCotqvrrfXmGCue9fvQ2eHaWV4oZhkhLpj6ueq7GJVzJRxQ384zCMdv5hkFVK1gCFI7oXjQarqOQd5PJGD7RiyDrIcPgDg7X0k+xQaUCK7MShvgVm37N1yVXKvGnPUO0PPDjtWfpZfNO05/Bz1zRoBi2eNu0F/ASngWJdfPk0LD9lfKx4GoRbDxROS6GfxdnTbPi5cloqfgannjyFSITWJefqj2TL5o4KV+ValGHEhlamJwtOwLg+8PQpQ9q9xiXG3yHaIf5gq6sOo1RQkuuq24Th+g24grKgPg0llZZugkimDAhojjAOFniFqw4UZzx/aSl/89G3SEPN5cATLGsp9BPTL8SfhsJFuwD2h8CYMyEDl7T0PfkCX+VLTEvsSg9b3FZfBuT3Hcwelw8PFJ3+kBEQFUNSLZ7e6nfny8O6CrHrZEZcTn7c63BAwjkm5AhEuS6/uGWcHZT7fyAo2SPsn4OP6bd/073OAHZE/X57bJQ+MTaCPWQUOfziiZ+wGewQfTJt0R3xPDtiJ+KcTL/Lj2nS5Ufxn0+d6fJjtOnyYyiKDYhCWWbC58fH3/b5cfVO6asi4fOjKc0xhKB48l/7HZ/MQcD6uOcP04HA+jFOSyUk6+LUtr4zgs+nitlUqrjrnLh1EqS3tl39rkTsSQU+A0bFPG0gtDeWocxciMPlx2RcLvkyrWKpvodSX+QXZdsM4PMqfRV/WAWujniypkKsFItYSBMQu52IuWSaLJvpK17jy7YkqJ2jQ0zUe5a56JuWr0mRpJnYOESOZMiWvFzf6uW1fM/bvFzjWmhxE3QTH/zPEBO3jZR4tIE+veRWHJBHPHzYMOJ6RANzLYznMrGvzKVyrjoz17dJOBrnNsRzkH177u1E37KGJI7ZpKEbm0V+L0XH0C8FM1cTlxHKgj2EeaokGr/hXl8ZMwwiiQcQXQn57/EMkysD3sX0f9ZgQLJ2vDGFtp2krYY7u8RpdvYs2TZIPZm3SAshMMVqKNseb7Tyi0H9L+z8wtH/ws0vRsdfEF/KloNiXi8vxuX/lYY2A9ucZPAsnu7khEU0cLS/DEpsteYcmcxjUBn9vWImyn3/UYgPoPgFfi9JKezMkwnb5oT4y03sUwSOoeWxRy7RnSHLO32j4OJrr9jayx4DU8WvdvYZeHHZo1ZLHOHcOdYuhVtRxBs0l1t4C3hhCy3FT7vQacIXIXtCq01bga9JRysv/k1SAfaMhthFpsdCG7XB/xaaIKa10cJ3BGp3oMaAuI9qhN0yvbTUf9g5zC2eHQ1rRr06u9bnppKXE6WRTc189/gp4y2cNkS2KrZBPgcR9Eyzr0D3Kxe4RrjhTFt6zD7mkd68WS4CdkXGJAFz4Qe2q34FB03ZeuuJw2cd5iOSrV2iZmafcbqR5VFeqvPKoHQbedFgE54+S4y5y7SuevG/PNB7zIHOCZhixZd/nQ5NI7F+NHsl7hcMm17zTALmbc6dBZrE+7cETbJxEOpLyGmkRyzTDSQNvEUcoN2gPOGCS3rX2ysWHudRVy5nOmY0dcBG3I1JK+VPgge8jl8Cnck3x04aRkctPW8BzYRN+NxBTESowYCYhCboXXraPCZHbLAlcUBYRdumv2wTCpC2lbxcWhCdo4dK+Phr2YRzuQkj4k2A04h89sDnwP1D8CwsvQ15+5ZuvN3kveBWLOHAgEgU2GQfJyj9fEcfrXVn5LDSTURyV4hABi7j9Fm5nseAmIhOuylX49uQtUx8hq2SyaQuq+mAwCz1eOrzsJxiDvGdtS/CgWt4CL8SLnMl7L62z6icr9OOZNC+PI+rpSaE0AReIHEjDtAy0o0ojZhNL8wtsLkiy/FhGjYZi7qE9lD6tMizAuTBssoSv+my472FnCeolzhEaDAkoI4Hbgz3DFp8LeSiV4Z7RqueLQ9dj5VR2NSHCVke4FV7HR5cdXBz8wxar81wYuTcWzquJcL2vS3P4Odd08TJicW0+QfUkTkjaTEdIhAxTV/FNelQutHCMGv2nKbFuZMW5y25BTpGUFpVJr3W+LX4gprij/oc4o/TwOfB9RPcWj+5/xQbW+0Sfzh2yoB/ZGaWl4Ev+MAfkq6g2MIHzHPivTXpvTUoJp2KT5mJqi/Jbyjg9imZBY+sddKvs+CRWzOgYBcaHksJpUihBwQZlVW53KuFaQy8WeF3kN7CkiR3PJFMDnggkh4r/YnCPkOMGNl/9Kl73XG5PZH0QY29PYjf47gnPYCWZQIbL8st2MIglyYNyuXWA2GcvDPdRYwtKHcC3TODFRtWVnaGNaU5Q5WZlLx+CQ6FR2fxJJlKtEk6tJdtSCB1z3+srEP7qt3UoX0BtG40ivCO4o4AIjfiNhptP80+xzUO3WiGtfzXLKLu3uyPd16/nXaQafKcoQGyMrbGfxNRPxNKVZq6m4hc7+4873bd15zna/CXBgLgszW1RVMPaGqrprbJ436DQ2IaWffJYJJogVh7K89IUPe25XkP6L7WPF+LvzSeUkkKvntjkFNeapgNRItBJxlvHkFBm+mzxgFJoxHuG3dMho/O1dS1mvq8pr6kqa9o6mpNfQK2YOoa4yCLMSCelHqva4F6fj6b0L73Cd23+kSr/8ShUin4wGEK7syxfPcmjFW2kRwlXZ4zIsizLWE0eUEwET2Tw4qHeQ44rLhZUnEpQfabaK2EQDdL9KK+9axUth4RgFQEPJeAL6efPXHIyb/ijcTkX3vEiklXBnPoHMlamAXJzGJZNuwwq3R3mSnQXM9hPbh2bE6Pz0QVbBodjiKErBHmEN40nLn0F4d0bwGkm3BXioYucoRrCCz5s36dVpTrimjAcDW0oaUpM8NvyxCnqVFfe+y8aBThuNl/M/xNhBtSCjgU+rJ5SaFLE980/habFuZgtlBfjiKYbOycaLSwPyk30+NYOhJFLOp/b9E42jg1NOJD27iPoK2EUYIB5wbz6puop1Uq8UAL0Sii3cru6jYeOZjo6FwYjVciyr2dwwMhUrsZzl0+LSccdjo51DuKQ9wCOcMjK8cth+E=
*/