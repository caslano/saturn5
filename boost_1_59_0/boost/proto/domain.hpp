///////////////////////////////////////////////////////////////////////////////
/// \file domain.hpp
/// Contains definition of domain\<\> class template and helpers for
/// defining domains with a generator and a grammar for controlling
/// operator overloading.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DOMAIN_HPP_EAN_02_13_2007
#define BOOST_PROTO_DOMAIN_HPP_EAN_02_13_2007

#include <boost/ref.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/generate.hpp>
#include <boost/proto/detail/as_expr.hpp>
#include <boost/proto/detail/deduce_domain.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{

    namespace detail
    {
        struct not_a_generator
        {};

        struct not_a_grammar
        {};

        struct not_a_domain
        {};
    }

    namespace domainns_
    {
        /// \brief For use in defining domain tags to be used
        /// with \c proto::extends\<\>. A \e Domain associates
        /// an expression type with a \e Generator, and optionally
        /// a \e Grammar.
        ///
        /// The Generator determines how new expressions in the
        /// domain are constructed. Typically, a generator wraps
        /// all new expressions in a wrapper that imparts
        /// domain-specific behaviors to expressions within its
        /// domain. (See \c proto::extends\<\>.)
        ///
        /// The Grammar determines whether a given expression is
        /// valid within the domain, and automatically disables
        /// any operator overloads which would cause an invalid
        /// expression to be created. By default, the Grammar
        /// parameter defaults to the wildcard, \c proto::_, which
        /// makes all expressions valid within the domain.
        ///
        /// The Super declares the domain currently being defined
        /// to be a sub-domain of Super. Expressions in sub-domains
        /// can be freely combined with expressions in its super-
        /// domain (and <I>its</I> super-domain, etc.).
        ///
        /// Example:
        /// \code
        /// template<typename Expr>
        /// struct MyExpr;
        ///
        /// struct MyGrammar
        ///   : or_< terminal<_>, plus<MyGrammar, MyGrammar> >
        /// {};
        ///
        /// // Define MyDomain, in which all expressions are
        /// // wrapped in MyExpr<> and only expressions that
        /// // conform to MyGrammar are allowed.
        /// struct MyDomain
        ///   : domain<generator<MyExpr>, MyGrammar>
        /// {};
        ///
        /// // Use MyDomain to define MyExpr
        /// template<typename Expr>
        /// struct MyExpr
        ///   : extends<Expr, MyExpr<Expr>, MyDomain>
        /// {
        ///     // ...
        /// };
        /// \endcode
        ///
        template<
            typename Generator // = default_generator
          , typename Grammar   // = proto::_
          , typename Super     // = no_super_domain
        >
        struct domain
          : Generator
        {
            typedef Generator proto_generator;
            typedef Grammar   proto_grammar;
            typedef Super     proto_super_domain;
            typedef domain    proto_base_domain;

            /// INTERNAL ONLY
            typedef void proto_is_domain_;

            /// \brief A unary MonomorphicFunctionObject that turns objects into Proto
            /// expression objects in this domain.
            ///
            /// The <tt>as_expr\<\></tt> function object turns objects into Proto expressions, if
            /// they are not already, by making them Proto terminals held by value if
            /// possible. Objects that are already Proto expressions are left alone.
            ///
            /// If <tt>wants_basic_expr\<Generator\>::value</tt> is true, then let \c E be \c basic_expr;
            /// otherwise, let \t E be \c expr. Given an lvalue \c t of type \c T:
            ///
            /// If \c T is not a Proto expression type the resulting terminal is
            /// calculated as follows:
            ///
            ///   If \c T is a function type, an abstract type, or a type derived from
            ///   \c std::ios_base, let \c A be <tt>T &</tt>.
            ///   Otherwise, let \c A be the type \c T stripped of cv-qualifiers.
            ///   Then, the result of applying <tt>as_expr\<T\>()(t)</tt> is
            ///   <tt>Generator()(E\<tag::terminal, term\<A\> \>::make(t))</tt>.
            ///
            /// If \c T is a Proto expression type and its generator type is different from
            /// \c Generator, the result is <tt>Generator()(t)</tt>.
            ///
            /// Otherwise, the result is \c t converted to an (un-const) rvalue.
            ///
            template<typename T, typename IsExpr = void, typename Callable = proto::callable>
            struct as_expr
              : detail::as_expr<
                    T
                  , typename detail::base_generator<Generator>::type
                  , wants_basic_expr<Generator>::value
                >
            {
                BOOST_PROTO_CALLABLE()
            };

            /// INTERNAL ONLY
            ///
            template<typename T>
            struct as_expr<T, typename T::proto_is_expr_, proto::callable>
            {
                BOOST_PROTO_CALLABLE()
                typedef typename remove_const<T>::type result_type;

                BOOST_FORCEINLINE
                result_type operator()(T &e) const
                {
                    return e;
                }
            };

            /// \brief A unary MonomorphicFunctionObject that turns objects into Proto
            /// expression objects in this domain.
            ///
            /// The <tt>as_child\<\></tt> function object turns objects into Proto expressions, if
            /// they are not already, by making them Proto terminals held by reference.
            /// Objects that are already Proto expressions are simply returned by reference.
            ///
            /// If <tt>wants_basic_expr\<Generator\>::value</tt> is true, then let \c E be \c basic_expr;
            /// otherwise, let \t E be \c expr. Given an lvalue \c t of type \c T:
            ///
            /// If \c T is not a Proto expression type the resulting terminal is
            /// <tt>Generator()(E\<tag::terminal, term\<T &\> \>::make(t))</tt>.
            ///
            /// If \c T is a Proto expression type and its generator type is different from
            /// \c Generator, the result is <tt>Generator()(t)</tt>.
            ///
            /// Otherwise, the result is the lvalue \c t.
            ///
            template<typename T, typename IsExpr = void, typename Callable = proto::callable>
            struct as_child
              : detail::as_child<
                    T
                  , typename detail::base_generator<Generator>::type
                  , wants_basic_expr<Generator>::value
                >
            {
                BOOST_PROTO_CALLABLE()
            };

            /// INTERNAL ONLY
            ///
            template<typename T>
            struct as_child<T, typename T::proto_is_expr_, proto::callable>
            {
                BOOST_PROTO_CALLABLE()
                typedef T &result_type;

                BOOST_FORCEINLINE
                result_type operator()(T &e) const
                {
                    return e;
                }
            };
        };

        /// \brief The domain expressions have by default, if
        /// \c proto::extends\<\> has not been used to associate
        /// a domain with an expression.
        ///
        struct default_domain
          : domain<>
        {};

        /// \brief A domain to use when you prefer the use of
        /// \c proto::basic_expr\<\> over \c proto::expr\<\>.
        ///
        struct basic_default_domain
          : domain<basic_default_generator>
        {};

        /// \brief A pseudo-domain for use in functions and
        /// metafunctions that require a domain parameter. It
        /// indicates that the domain of the parent node should
        /// be inferred from the domains of the child nodes.
        ///
        /// \attention \c deduce_domain is not itself a valid domain.
        ///
        struct deduce_domain
          : domain<detail::not_a_generator, detail::not_a_grammar, detail::not_a_domain>
        {};

        /// \brief Given a domain, a tag type and an argument list,
        /// compute the type of the expression to generate. This is
        /// either an instance of \c proto::expr\<\> or
        /// \c proto::basic_expr\<\>.
        ///
        template<typename Domain, typename Tag, typename Args, bool WantsBasicExpr>
        struct base_expr
        {
            typedef proto::expr<Tag, Args, Args::arity> type;
        };

        /// INTERNAL ONLY
        ///
        template<typename Domain, typename Tag, typename Args>
        struct base_expr<Domain, Tag, Args, true>
        {
            typedef proto::basic_expr<Tag, Args, Args::arity> type;
        };

    }

    /// A metafunction that returns \c mpl::true_
    /// if the type \c T is the type of a Proto domain;
    /// \c mpl::false_ otherwise. If \c T inherits from
    /// \c proto::domain\<\>, \c is_domain\<T\> is
    /// \c mpl::true_.
    template<typename T, typename Void  /* = void*/>
    struct is_domain
      : mpl::false_
    {};

    /// INTERNAL ONLY
    ///
    template<typename T>
    struct is_domain<T, typename T::proto_is_domain_>
      : mpl::true_
    {};

    /// A metafunction that returns the domain of
    /// a given type. If \c T is a Proto expression
    /// type, it returns that expression's associated
    /// domain. If not, it returns
    /// \c proto::default_domain.
    template<typename T, typename Void /* = void*/>
    struct domain_of
    {
        typedef default_domain type;
    };

    /// INTERNAL ONLY
    ///
    template<typename T>
    struct domain_of<T, typename T::proto_is_expr_>
    {
        typedef typename T::proto_domain type;
    };

    /// INTERNAL ONLY
    ///
    template<typename T>
    struct domain_of<T &, void>
    {
        typedef typename domain_of<T>::type type;
    };

    /// INTERNAL ONLY
    ///
    template<typename T>
    struct domain_of<boost::reference_wrapper<T>, void>
    {
        typedef typename domain_of<T>::type type;
    };

    /// INTERNAL ONLY
    ///
    template<typename T>
    struct domain_of<boost::reference_wrapper<T> const, void>
    {
        typedef typename domain_of<T>::type type;
    };

    /// A metafunction that returns \c mpl::true_
    /// if the type \c SubDomain is a sub-domain of
    /// \c SuperDomain; \c mpl::false_ otherwise.
    template<typename SubDomain, typename SuperDomain>
    struct is_sub_domain_of
      : is_sub_domain_of<typename SubDomain::proto_super_domain, SuperDomain>
    {};

    /// INTERNAL ONLY
    ///
    template<typename SuperDomain>
    struct is_sub_domain_of<proto::no_super_domain, SuperDomain>
      : mpl::false_
    {};

    /// INTERNAL ONLY
    ///
    template<typename SuperDomain>
    struct is_sub_domain_of<SuperDomain, SuperDomain>
      : mpl::true_
    {};

}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* domain.hpp
wsTj99hNAB4P2/+dWKfpMFVe/TogeNIZgsfxQxA8CeA7921OBN/RfZj0ZMRmyf1rYvDMLEetQ7CsE+8xFM/tfG8o1nfiPUbkuYLvZWKZJ95jYJ5edK8HMI9ndQIwzzVhQPFopUVaabHIWM64PF0PG8aCcKm9r5qilc6nqaigIdkz1FaMqOWqNgxSKgYJ2QYikXbiH7S3BX2KtoMWPkK24WHYEBqqsyBd2H5pwbcAGkIZKzYuo3bvnhJ5G3UV5udn7/csn6e7XU/ujqhOiUdhcAtmarypC9ugoy5e+Sktxkgrmr6sjEagHF/hODeo5MpIyBk03XuSjKnFREEnTnE9VaN3iNFozc0Z907q3Vu2yFfYki+b4NR7mIzw8gBx7pbLQckZ+j8hgpbtiuV4gM1YyEOtc0/Y/+Mp0wmIaxb3HUqziUKX9A5wVF32Mvzf+mOVwWdngSc3XYE1lcFWcJBC164sp4N0KR2kT/BBen+ecg+dX2qTscQJ0/mNYVqOS4ayjY8OsCvC7J0iGcIkoUg++mTTxSfgm/h3MeapLkurew2+7osWfpLr/CR3qJVrcSV4kjuO5jqP5g6NfrlAz3Vm71/gpe9X4wAdmqe05ylOHKC9SPwMQAGIEijg+DW+3Zo7lAPn+b1MaCN4xlD/pAfTql9xjvMYzlDPu/fF75akVy3BAN3az0LBAnzH23/oNrKPcfT5EFbPpAMIRXWAe5vYjcCTlgA7cmUAbEkPOSWegN5LxgHjL3y8xfwFfAbwCTt6kwl4da+8yCfoxXQxUsEoBLY7vxrm1orsWhF9OrUiB9yP+SQRQ9Nsxi3IAVv6KjVO39KFQt/qckcyveZYeI1D87WNOOLrKrB1UjnZrxjbT64Ed9WzeNF8JxsDfE7dRmOu+eG51Cr619ELI0aM2tR83fTC0v8ZUS5Tu8zQVlzhF5bhynX8rsynPnJ//D3zSBIQP70//o630AXqarLszstOmdMxvaoF3dnT1xx3QNHIHrUE4Nv7yL7YFAznKciMT0HN9+dMAaIUBZO6IbJ3WkU744TNj/fsjxvNGfjb/Hjvnt0IB6900Dmzk/D+s0gaP5f7OooMTbzOj15H1zUZxrZPvEsvsifTVowzpmroK/RqAbqSfUz/ZqI2Z4pYtxr4qs5IZDPNoPhsBb0cs0l/2QTBjt2Uldl6v9GtI9zew+q14qOmbmz14pHHMt0i+Ciw4Lx1xIXVi7lfENUzC7rKjrGzetB4G/VGyvEp+ayAqHak2rRy1M+ObhLQQYaX0wOykMRokE/nG5UYwUhkK7rYsdn6ClH5mz/yuNwcKd9AVwLyhvZ7VC6ufAOsOr8Y80uTdtFwRVAOBODq39AK5+LMnb1G4pKHX1q5wgQnOKz0lR0Qx4eRHC3fhBb7w7XdfFZMEQUVMSSDw2qaCW8QGY4Y7c1mM3vW0ar7rz6W1+MUTMCC3hzeTsdozQIgeeUO5bV+eW1srQ/pudYbxIJOI2Gd05osGTxDC2/gSJOhdSmIu6qbyKskskMmsqPqSwZHdnByu39vCd833yaD2YkFrab29wwxeQaixEvRqXcdWPAydrAADLbqF+N/bEpUzg1SogKfj1iCbzhaWJ8A99mMYrcxzG1kPIqOmUGD0cnwJTDjCb8U/3qCRp5Ro4mRvlnCTYN8Lw6B3rWTDGYKlrEgRKXBrIqJdegxDodL6y0phq3qt+jxMIcZ66hwrKPaS1eHxJGQZ8tXyeBbroQ+amnR2yUUMzUzxurMEPH5I8x0nCcc8ronOBySeqKliW/Wcl8ednBfqsoM5rvAmzXPB3CZVhHoBf5uGn8W8Wcxf87iz/n8uZA+69I2G6BW83pJagWs4rokXGtLW2BLgHh2BIlF00+J90I2TkQhClPp+LAlpUEs1tPUgSWDiJXQDwcA4VRiE3+77LQxl2rbH0/5lHNWkmsd0Gz1QXiO6Ec1tVOkUJWcnKfkRFGWr4bI7ZYtSUCZaw5A+9wgXlwGC3QnHFxCB6WvzcGI73iA1uJukRxuQSa4g4HsE8RhbOMRUI8Tn0FVh2v6oQrxFrXg2YbXV2bp9Kx60ATGC9ckl5zRfMezTxTGQdc8Y2oOj3ArDs+29axV18MIJkjytevhFv7SYYzZwBhs9caYrQ0jOFhfDF96Jg7pOv7LDI4xAWKiFX27apm0Zl4VXubop2aGxyMG26YO1pPqVi0058FK9JgTTQuIt1SbLTHGMVyNybSpGbEIevHsIqSiwdO2cPWrDBbSz0zD8yL/jCcs4CBJzLAYTovFYuRPzz4rljLcPqRHjkiGD8GCcpWNgcaO++Aqvxoa6vOCFMDpw1ONaVAc+uzjuq8jmqbPpgHohG9WTY6nGotRobNpE8PrwIIbQEyxXKsScsBTjZWpXqP3a/wcRF3J1JOCSHJWYFSiM0aAuA+5xMV6opDRy/TczCBVQyWKoZk0i2UsfBjHHsolwPa+dpBoSJOnGpeVq7yfKpfT0zJ26eBF7K7s2l4TKL4A9Sw2jW8Ig6Q+VnOnq7fyZ7y/MYiEmR6eBsUpZ0HjXxZM6giRYQH9wuFb6QeVpNJLLG2gNxhw7jpIQHHumWyOFnoYjSt9hJeeZeN9Xdh62BPmlf4zYFD8QFKsWDosQCNuEauS7Iik0/2tWQ6ZOi3c1ieg+ZuluWjuHKJFl1KBy7gNKnFZmIeUz4fmn3ByogbhuvS0YeaWlemysBOyv8hISMFgrideATfItYR4cwyqcpnGvu7iJwcAPsujODxxFKODPNVoXu0fX/+TfglU3oRULtKyw/V7PBuLZTsbuf6rg6I/qt7YY4L4l7ZxM3++AZDfKMA+xZcLafPMNFGo/gqan5XM0UqbZ5oH0+KnONycg1DoPIWXsrhxwBkpBRwR0f4SJ6DYmZzpxjBDLtBmt4vfX3BGwqLS5DABhgNEcVOSLIV49OWxEkKSdI4k3xwr0SpmxEq0SuLOoeMLYyVaxC2xEi2S8HPw+LhYiWaRgRL/D6GPQ989SACAQ0ulfQ1clFX2/wwMMOrgjAqKhkZlaWFlkeU0mm8NkjY6SDCaIb267ORW1vMoFoPSMObT46C9u5u11upmm1u2WWKaofgTSFIq1kipqGi7NKxhsUry8vzPOfc+M4O6u7/////5+MF5Xu597su5555z7jnfUykl2fObJKsanyPCICnSHzqAIs49/cPR4vIa2nt6jSROVEyETlXxv5GECkiGZBGwxer3rTudFn/nzStzpCl+doU0Pksa6WdDpYFZWfJyHObDJ5INoXH469hP8OvixRR/kbaYAjCGhybgkzZ8QpOSDL8WIKoScki7n90ljQUdbUSWnI5PT5+gp/K3eDEJC32Gv+7HT6DDMVuO977EfFhic8pvfQ7D1fnPigvDPx9uFT8FUAnSRRghKlwak3/LlsL95z7ELfnV6p5IEl9tmQSyy1j4mJ7EF14JziliDzwLouCc4kWt98EPoZZNk8iCjDFZbz0TFZhXG04ttmVHj1Ydfx2MMktegOQ4R2ItT4O0l8CvithRvPp1Pl0Vsxq8CtEVN2zvfJrCijJqldVriAvj1Clk5VDIZqGQsUIp3yiEA4HNVKZjM9G371oNbZ5TjP7uefSzCH/Opp8S/py6msM1VW+KiyxQeE1d0BE4Lo/hjVGNaLpPxrAatmkCeozCsJEqGyrEeb4Hk7kGtKI5al6x49GOlZlB05TF/km2AjnT0bVyonWnyYyp8FAv056mwHVe7SD/ox3AQoBcRiEwh5nNmEAzIlmxVguPuXpzFQ6ESAUgmhhcUKwO8aiPglTg6LWWzeYh1nY5yVr2IiUIKxkTzNIch4uvcxxZOR6aMqtATg5apmf5W2PgYX9H9coRi/32AumEo1oegWfLZsKKHt+KKij/7vXwXcfB4p/h3RNQw/QCyer2FgATffk63sgaTK1gVAeo2R2O/dbgJygpWqZBkQ8d+1fuxuqtATxYnOrfF+PYX/yPVjT3q7dI6i0djn2+4cHrpgcqi56B6tct9t9UIJun+g/GOPYV/0hoUXqT/GmG0EroS6DWuuZexDY+Yl2HQf/UJ2lM8LbpvVn+H2NuCVSWpOA7U8U7E+mdGwvkb2B038ZDF2PQrWXNgvcuCHxqXZOC5okBjuwO67pEerV4Wm+B9DV0KYQfV8YDjatTO6ggjb0t7OsvOPh6gonxGkHG6HaT4FkAnDUnnI5slqzBpv9fE3OH8Zlw1UzsiRgw43LPkXtssLH6d6/nEJGv8qQ5WLsHP4/N+BDZgEfkoaSwA34fZm0/OsWha//F+k3xnqHve38g8JgON4E1clga6FFuu11uXxmjHkXgWWeH3dWBgO6OT+DvJ46D8OBgwSKHs0OOc+S2SwO8Bvc8qCpL0hBjwFHVoy2kcGZTxa+4TZV1JYOwbCEWcl87Ht6O4wGMbravHJV2m2pQ3R3qQHUpaRvz3HnZsDqqne1ktrj/M7ID+Q8kscHdyQQTmfoGVHslVnsSd7l2NbMIwUSHqcskih7uvy46eriIPX6b2CGz8XuZxRmYshtKlExxdBXfBTccRR0rFwCNFRXIl6iZEl7OgmVctNixGpOoyXH2fIvUj6q4Y0k3VjET3inepx/v/L6cjncW+CttdLzzRSkd79wNTYRVzBfY34u7tDpQMOdi4x86kyyA8Eii78/iYMJanyK3VDPh4gXot0XqYAdyROufCXahOSKIWbDse5FNSgO9Rjf7kUcQG0P93WzWGa7gU4G73wqb+GZii2CkHuuAD/hiobHB66Ygxo+F1f0zGQNV4X5JP1gAqIebBgZnt7MhpQR9tfEM9QKa/jg2/d1fkwm6dAMJ9wls9j6QFe9go/RW/nOtOHCkFhqotbyd06Pa+eqvUe18/81wO/+4ikL51Ic6glnt7KlV1IIRvAXRh6KgiW5b3s3PQv+FQg9sMTNe4vZ92F8mws/FQFl0KS1WaBrZxS/h6WmS4MfoyZ7EBsK9UBxbDmO7KLzsKW+lhSeBym8NgcIvEkK5g3iYRiLYxzgYxzuTyTLWwkbNo/43sn+qQgprJCkMZ4xtw6QqciMINOy+OFxwDYj6c2ccyj51AvWngSWbdQmpge9/rDZbRM1ugEpJuymciIVcdWTE+WcCYf5YMTR8akdGLZ727wPd+GlejLG7eDGQ5gzhYrHsPV4MYyyI57U5pnVIMRmat2AR8/CiTewyXhREtDqTXtTEHuNFL0TMADR4SMmOqpJBgUo9Yrh9RZdm3XkNyO1oFA1o0sV4oCIzTW5jk2EMQsOqoRqEvrn/eZOtCgP6LGzVacKix9vsczd9v5n9+Un6PgiRG8LfT2Bd8fT9AQhB5Gphc9E472pGwllc0qUjTy6knxR16S4JU5azBI8f68jAlWrAco14+6oSEiN3ntaJvBPntf4Urc9KWKE+M6juhJjnkLtpZl1mdvB+5AJFOHz5ZoQYrZZcuFqT7DM6Smbg4jnqw3pbx1CewGLgbzA9n5YMD9QWjUCGk9WxcjAwnKwC2ThzmuOj4h/sj3WE/ocP4htFaCEq49DJ6JRTSgC4bUY6RFFzOhxnfL/BSrM6ArXS5SCJVCPH2s8Z2DTEoYN77zjOrHwLmNhjgolJY+Hmy3DzD3gTeLaQvPaOo4g7XchRXG0zEfRcfqF1goZ7SBtsPulk3S+C0UAXezultCkmefCPih5uS+488LxkQkCzrrmWSiBjta67jG/g0LZB1p3UFjedxm8fRNCexEoPqblm9XYYJFgwrjZEudhMSLRUQ5AwNaDWJphvqvIz+IEM2t9ZIM9DQWA/PjlkXfc+PUidtdjx8ioO7JZZRCVeESVAMsvR5TKgpNtzqCmXQlM0zDpmBmoJpRFbGYH1ekW9d8P/ix2mWfLl06B90NKZcHctiiaEGw/i7r9e79JVk2OPAU+5WFx8/FiXiNZv/YE2WzO9fvB1/TZ74zEeUp/xL50GL9kGNHhrR589AjeFF+jcYINu0f+LS/DcFU90adwcidzG+WWPhvJAO2y16QgO6mwD+r1Fd6sFipYmwS5H8/c1liyC+fOZPfxgjA3pj5E+FhBLvYYwuMr9S6Dpc9uZ9ijv5Z+J/ZP/N95xtjEZmou7vqUiE1tf/gu2niXoTTy6mpqYcRwbCZrcpqYeUkxhKL7QejTdAdT+MlZsDazm6MTUh99080xVege47rKkH+w7d8NvrP15qkLK4Y+y+6FWTRLbxSSxtbmRCcKTNzpIZhMu/c/fDxzpvwUdi2mMf5T4xLpfUASxVPwW+/iXn7GPWDXBsW3nRSITJAB8D7Mx7/dorHu2YOaHAroBuQ3b9PxxPl3QKFbcRV019+1qqRlDWkkQlJJoVPRvwsPGXzTNSxDb0Kd2tt/LgdMiE3TrCmr5339OFvEma7HtJ07+L9t+P2JKTdXbbu3b9mPHIm2vPHO+tv9Pwn9oe2rftsef0/b1RdT24aLtYyt+wLZfS20XeUKddVTb7u2EhNCnC58jkmNFj8a/2OjO4RPqbHQ4WQmilLLCWWK7uaGsi5CxdPI0HsPYIZbubIenbmp1k5v9fngPSTBs/CwxHpofJT/yb4RdHeSyl1Flle5CeWfevzR6iTbdo1tw4TToEAM7l6MkimKr5EGJtBbFUZfD1e7LchwqThFbhI22CMk4dxpcFX8TGsc3iCcf7tJA/2gPV29iy/tWPx+q96CYgW1srsYwvaZsgoehw8q7OgjSJ1wggY3h7SExwlEF+4DjkJrfJMWpMzrQLy22WvW1OWZ2+K5yoz861uq5HEaIu4xRrWaWMRHF+nq9yoZlOHd2ngOAwKTQJ+8Pneejkj/GnUsldTqVnGrvQyXNv9EI0iZCJV74EjKnu/F/2HtvX9aliwVzqRGs8adkAT7U/69AQCdPJAuXazQnyCWc68jLoLk0f9UEfWDksPGE2/jdafL7nSWa9N0JjURNVzsSS0oXBpm2AwNKJKuvlrwDKDOEPnpXvteDTVNA26Zvsb0ysktLyMqvMypB+DSjL/kE0cTRFZOxiXOoidadGOLYxn6J7dG2miXKIXnF1KGGkGWrTbLi1T1ThhqsOyvhpQXqSL4g2onbCeUQKP4zHFBGGw8GzB9mW34iCB/YewO1KyxqnuSYDjtkAF1aXS3WtcX0w2xd9wj+cMIdL/2AO3fhjxprIBdFgLwiNGhYyyxGeirfqs5Bbf8W0OoT9eltzSQsLoQmCn/+sp8IfQuNCrAS20s+A2EE7ycspolVXExxtWdzpuI5QQLfdmir14AZORjc/Oo+jXMdFFQP7oCpGO81crMXdleIgbdJhAeDafeAamb0I2FjqvjWi/eJnRtGig8SPMQuBp5DiU3viG/oWW33ntBIPwH6+1WzlhUSKKC1/E70vjdkZ7e6EeCPN33jPzXa1k72il0fOIj41GGWTKASZk1uIrxZM6yK1gsiZe8UZd/tJTGKkJfKMM5RzWUZtSCCtCi5zYFPix7BNVvUofgaHZ+vXBw0ua07JyrouNcQnGX0V8bANPrGgcw52+FqXJmJD331i1Vfw2K7r17upzlbpsFLIRNGWPt9TQb5CPbN15K+31FdclE4DsfZ7DUELROz3a1Lw/ai+AeAw8yDfsH4utmqpB4OT6ZZyyntr6893QcE1pJePVVwDDNbA1Pg5qAs
*/