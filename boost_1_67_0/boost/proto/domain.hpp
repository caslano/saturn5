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
uoC6TnVJeXUMYpvqhtYhvhhZqus54upkpev1xRbP3Ko3zgG/1qxo8gG/wpZSz8nsNkEuNY0xdtGqzZ6xiLhmKtqAWjaT5Dn2RmSX9NJnELtL+0y8kw8YWYbtRxGtbcDHkf3jwMVFICKvnl0IFKzH1pokIruK+xCVwxKPC4jGdcSjF7hXjBhsRPyxF8ZZh1lEXAIxR2XfK0iXdyAEtCsD3tUcaHPNHMyAbVLRp3LikSgLgm0Wb5kyGEJ0zQLLAqKQ1AC52sNdcpbkJGJnBZjlRbyED1YiTlqAT8MHpxEXq4iIkFRgVYiCNvj+8KFR4NAC/N447IGv1wFzmkQHtM85HBW+twg/X2N11bDLWMsg3nilpioLcdqDWBOFd/cDZ4aB3JpTVyWMAobDlyZNdk227Zps18429mRjsjF5wp68s23btmtqZ7vz/YOz1rk8d8/t+6z13L1c+3mlM5gthjyn9KJXUu5OunKNUUO8X0C5waLWIZ3XesaWYvE0Xpd0V2Z2lzAzwTpwU5iFiEEgrWCQGvdlyLRycPJkn3n6Trkm2VvYYH7iMhTcWpg/Kgzsk35K+cjHW1Gly5NZjFucdE8VzU6EZg9e4vZJlP3IFfST6WKXwLVorj4bVZf1NFblyP1CzK6nY5Wd1dfn9cxX3eBjgiv+lyzO1m0YINH3rlxmnl0SkdbfEtQMKdKj4/LVuUy6mJcjaaMRdC6XdC7MtMpL6FeebIRFaUCEcjX/bPoDjeqJhJSQRq7xgZGUVOblPpGDEQ5i96VDBsb4vZZygwxq3USDQkzdGqmyn85siXCZj5yhnpq6Hd3IDubEq3GugdK3LJQ6VZ4H0NXHatW/5NuU4hs3NXYby+p/dEjsYMovWl46ywrcuo4YKeQfV5H7wvWQZDTmm5yc851KmHzR6JvGS6xHOcl4CsvEo7C+D8ECm3cFoTQa7TQu6D58JYJ7XS/6yIG6yAL7dEqdZuiQf9Zc9oq8JBLfehPbgxaanvtAjEV1Wpu9zpqNE1AQk3GjUuNFxRVkklsm/iNu/bpeoSe2V1ykg1CDPy6IMp2kwx3lheheQihUuRI8iACCP3DutJw9Cz/hTgQt5Bbw5FkTcKyI4gNAC6m3JnVCrAL6VpF2Fh6yk6iovchWO3APhYkqba4YUZ8ejLATMHjJCO9zgqref25U/8lYgQq0kRb5K8AFk5CBgFlFPAZDVnShzkKQh9oa5G1ycRX8l6mcgQhfepilYOMGFXS3eQN3PzYocxoW2ETOGAt1e7RDCckzOFHFu0CiZJxROaVmbYgMXo2QB8ryHYce8sb0tG90insp7m6xzbC0NXsDs+4KSl/RKc1jFVR80N44WnW8lRCNNNBjIT8vUfp8rRKZMXuamDQdUoMtUE3iJsHLAonMQwOuXpXZjd/J+MxUF37VeKkqqYUciodI9UsVgCdopCaNa+qkSTvAxCs4qR3sNUCYlsbYaHtHEAKODrsfGKOiWsktQW1nBNtvaOMSmqU2lwEvNcRmzuEwiuBJ6Xvb0KqJ25mLVvBwY6GQFQ7+HoI+I4KOvcgMWjyP3SS4sse6gyNVm4WgQOmrWbFblZu4ULghfVkA6RUrt3cxW8Hwb+4s8QfVeUvozGC6NCZ1yq75MMIInKmR3tqQZDBwKUlOCOzkovEcKiAxmefjpYaOv/h1ZSG/aMdbdf5gjMq59SCtqZ+kBzdVNy2Mlxqd6L091oTGnsAj9S2fBBtGYy2U/b6kI0LgSd4Gp3FcIDGM0AvQUUJgZP4aM8YZJWy0I4//Rmf2rEDmglJrqY0/+7KV6BbK0Btxirz2k+m9L6RY7YT2C8Dyn8I2nRFM8eITMffeKHYKZMYY6kzVq2/L2P0a+bYiHKnf09yviB98YcBEZQ/c0MZgxQTy+Zpm80jCyRPiJcQJfi0WYCbU8bdiixD3p17rm0F9QlXfx2/jisU3MTe4ZVPirTBO9RM7d6Ohh26jHH5DWXuECy0LDebtdAbmJsTZQANhsSqMxKghQvGs3Dm1H09wNZ6wIsnooFLYNYN4UxRo2wzjpQHRjl/GZVTNDT8dH/UNzDENsiLNiaekA65hXW8O3/IITySbgvQT+gRpioaUbpN2DaXzDim7mAmK4c7aFHxoJK5S2XsLdK8SGhPRK35bE2HEaRplJl2YfQ8InAKaqpH4FSJ3eBNXeGNsUCIjSqLTI+g4hQNR8ghzpJjL6mS/TrTg6xZiOBSQibDDAb/dPO0gu4/gq10ZEXlnd7DvmxF594AID1Bp7SeCfWmCRM5KjvvxRn5kSWbu4ihZ/eSxB3+tL2JA0UdpULKqG+oxw5P0lYOy5YuTCsdofPuDwGQ+MCeCt4uKhn4/Hov0ni/fhiL5h/0A03qOmzdM9J4Fd05HQFUg+7ejobjydThyktLpLpkSLvp599mbnWrKBDxbCi5jfWyeSxaMgi60RKNrTI5uhs7vHu2n8scCMVqfmWy3HZSDVJdxT8JB37WwVrS+QCs+Be4qr5hkrY3YRgzSedbokdi3sXAdt0+/3kLwTlIfBVHELxMWi/KzgsWQ5poQnm+LuJzjDQalS7Bb36vz8tkBbAZsemzQS3Wha2NTDM/golP1EU56vU7dDDEeJOzU0WyNNgRUROOcsGO2BL6NImJujfqrRZGn6YoJrqR2r4d2Ybq2brhVC5dPLiEbo1NKjbsHphNbHNx0cpDkT5FzMdCsJmoy8/J8Fb3t10+CmpvIm2ymPyojY5RKCC+GrnMKWXa4WZ0LcpNzCBcctpPfq1PX8FNE3jfwSEOWmfL2pgX+QgeOptp1f5Vd2Ckz04xnD+3H7hMklFShPFUkr6/xMBaVHDA1oodNj8u387zVtUpp7B+6Y6FkTL4tgb6OJGSM4CMVz2YvpGENleEKGn8gD1Tsw0pTi6g+z2M9+Jm0gBhzjkHDQZ2qYFa9V/0MbrZXVwzlHzClyHKNLANghllUQ8+Co3fRtaSUrmAHjc6jqdUK62SEGY5oFibObyBRB9XzVyHesyDF3vSKFFqu4PYy22kCtSxtiy1OheLV732SZ7+1nVfIS+OtqeqZYI2F+owhhSV7B6l5v+hLHZbl+eqnDTBraWDaBjiLd7AYR2g9aExRIWyrcoy+Xn0ipWblFWe7bL9Srxjqwidl+8C2hNTWbrJanNCigHAyL/VMCgripn3V7Tz2hYZ5DqniDvLLH9R1ksgtCJBVpB8rli7Lz4bSAdGeBzAaDD+pnbAz0Zhhpfh0R9HCDMele/jWkoikk/AAs6ro97JOP24XcC0iTGMyq+S4ISbyyalkQz28uF/SmAPpUsrCDe98ZvXgD8p0D4oXAGlfdHbI0ESpBS1z/65rzv+WWn3tGME2VWOYV7MaMiNtsl4Yz077TlBGh0WPTq5CfTuCcxnZw/kXh3IPT/MtPUanMpqHbj7OgtTRhCSkT9MaztFhWpWgwOgt/7IH6ofVS082mDjcnUUKHxEL7hgf6jhDOh7QyGDgGW+DhP5nyDTB4TtDDn/mttIx+aRJOY8K9W86Ukxcq7IOM3kaV93rqh5evxGM6ExMifyeeHavYSlItmU7vPKyMKFF24xpmfx7DSdip/TkvrYca7lClT17k7XPdAX35gEGdTUxcSGGYiOZ194PTTuP5yv8QVV+f5FQOyvFhmuCa2KK8TLNQd38lVoONLmweSq9kW+A8n1hew6yv+kbfU4/CkxiC6JmfDGlRikQLMssujr4i6KY5EWj9AxY3mROLKKLUGDNjxK1fr2+9+Bq87hzUM9ae09UlONOsdKnGcxRfXCclDnAINz0SttRxXCNt/JRIljtMMb0yQnZygMEGbJnFwh4yovK6py5kjCukwaxL0dSvcMYFrhQ82Pv+jWKg2hoZgYQuEyZDZLnBrCnM1L1Mrwtzr9C8I+SEIWKDL1OQ58QvaTN0msZ2lgzbTPZkAVjYmPG7K2TKpgbgW4q07kBanJWPxksinR/SUUfygcp7eCH4Jat6A4c4Udn1nU1ZtLT/gOOZ4uRTBRfs5R2I178ojtkl1cSee9ICpBWUotxI3qtjPZAe6PQPRh29jxG8cCSkUTSV2Sf/54pUQ5TTOeYsrxWwFOWYVubzf0V+ndDgTxBqtE7V93gKa5R74uFOv6JHdL08xeAUMOkwNFt2geOpEfkN0G695jTZUz8fwIvwWzE0h6q3qb4Bq5T35HrxhE5xIlOtQWxmEJ0fmmtybTC0bHH+rFFFGSl6A3QfgmUXGDlGBU5aS512Cn7bhKg8HkH0IswjKj5ciL2lhA1lRfvjghQQ6/4C62t+IfHED7ibmRWyTpx3xdPXWZZ589e7ppOEd19tramHjxBUZnG5hcw1uM935FwqYC78hSbac6p1EREmIaHXIcKLjMus362i6vjWEGlnYZxtBRPzJclyi8ZZUp4PdRajnaUkgIxXF/3LdWjFlK50tx+MseWUPgrpbDinDgGIyVrh5bokKDa6vF6F7BmE6HBEFCAeRyK2Si54SHI+p10ioN8jMjuW+FYh/E3wkffYbRijqDRsTHvdp5U/nwxTIPgPYfRPiU+ejcQJV2TaPWJLD37Rj8uyKXpnJlQDeLqPCaS/KPKu+JQq7C3tlTpdVAvdV6RVE+nacDoUUPnfI4lnD8xV7WRpERCQcRuGJlhJU1rrMl9/M/Nc10284EECytWahmckInNNngQS4epsl4+vs7fb5jpTYd4too/cxZS+TH6ZxCtVEzV/xvySHqBUoBsnCvYAntYn8T+UTcHDV01tT/2SgKkcOLGMEnK32w9pl79q6g18tElM8tZ57c/vXZNowudCIA2VaI+e7g/VpRuwpnYO1DOTqlIy2Gx7jRUZk1rMPYAqaSshgCWEZn7hJ/cDq41GOOKiJEgW/hWrrM05eZuwuTsGrA1hyg9w9r5tSie9vEp6d1xsUwFW9kHSSvKUidAVcMcI9PGCZ63BZtxRFmjdqPNGn2lqNKX5kvyCIY3XqkIa7FtqVOUob8A3a5VmjJC5eYc69GuGmROvP4eWf/WzYfSKbXDmCHmDNbbBU2xoJy1juZesjYbeUlbwGYRQ7PUC4fPKhxsEa6biX60IZ3LXd+7Xf4Xk1VVR3f/3wwV1Hz4EgKK3KmVGVArqPk5VSYSvmxNy5ek3wdv22AakqMzJb5ND72alhIVS9QHvygEv0JKq2T543l9KWDnFklSbWk4esOEs4vpJJxUb7GExeD0yw3W7T17vBqImEn5mOQPGVxCCujBW8tBFvD689oT0w2Jooar2qv5cMOrak3H6mVFy+oEZXP/+j9A07KdihqrxEYAFfGvbPyBd5fiCsPNukWqzsD/R7DhlVpZK+9UiUEXzRhRl09dYw5miY3J21KdIRZOxwlpJHMvmpdHLs60PEthTmWzTB6sOM8k3IihQFuyNMrZoFUc5TDKhmVCID+uh76+FjpJf77GZchcUsbt+kO52JQ1HQh25nZSa5WkPb8igsA/S39dmY8U4gg9De5+OE4l+OGxMrQrrgsWWFWDwIAy4I2ZGG2g7PGllQFMV72iPjsIZ+FpSMdZrHXHI3zCPHRYObHGuRg6Td1qGZvEx93yMAj4tpM9O4ydH1rID7iP8z4ZOL5E+Y4nJjd/8DC0o7IFfGxwFAWojsXLXL9pgVYrX1jWDcq3gZKc+MCK1tPC7ZFoP2HsFF3xXCwD1g07pO3tBOGZoL+7q9/qV2CRIDqWkIptKpB4zuSFqYiLacHEXyU8+BpeTKn7EXPOuWa5kWyv1gn8hfHYnwLzZmJWUFUH0Wish3ZCWGJz93tCCzMWQ5paij/MrLp8rgqQdqUHRhDjJUATaVMKOhEfv2P8t6FESTA7B74+rCNWEIVtwx3qsK1TgZwfXGEWJ07z/oDNmNUhU+XvQme8hDWgd7FyK4s6NXsBV3ijoXrUsV678MeJqCOcxFOqUJ9G4CWdEHMrL5V3KQG3XYJFsZyXQZqbDVFiEk2lXAXcLB8qf8IWa2ukF2dwdr1BCqqxBV4lcmuYN3XmaR+PyedjjECtg9KX6kv0L8vEYo61/zxg/GN0Nxo6GJwNOcQpxuD7Kk3zF7OoVygxrsVaxxzRl5lcx3U8TQS/lQpDIodkQli2erKf9CyxVKQuDEcto4Nj0IjG+nWJXF3Qwlj959Qv17KFCaMuxS/OwU1IvumLu2XuLJ3bgBFVTh9TzS/nPZGrquQzQSui6BuPl8ySdx6y990MOrG72QZdmt7CLg9wtPvFQSenscisbJ2kvp7Er9y6GTE+XaS5QtCxRjIW9dWb1PO2QiU2uN5rtF4Ol+OmO+yLJKC71OC9UlT12nvdDxtc1+giaRoemd593ENCkmK3X3YVJxNW/NZO2m2LrSOlqOAZmtqI0TmJUvta6SRRmd4ZHakiNXkjENgz2aWowNJiYEOCvJwG8iuK6ZVB8oJz5ezWCZP1xK4wvV0gWPj4hqI6ge2c9+1XltHUPQa8pbKVsGZHiZUKMsczl18eGr8fsR8rkZZJ4R+kxh4qfEMeCgaYLZ54+S2oeJkDJk5uHe5wv1ymG/KsZTkeMoyU3Boa8JEl2orioFaTIqwrRy3mWywWKuOItfdVMM2o0oTivoll+WDAjpPrKNSMB5zMloj+tv/WwZK9K8FtQAHmqyXbQVf+HKMnqqj13F1qhw+Zt1uW4oCSY5tAtABtYtvYWJeCIcR6rycFrImMu74i1Oleeyp9P+u1lHWzH2RxyPK0kz02Oh5gTsjbq5RbADhkDCSpECEuYTo7YVzt3ueYtg9KXwoyVw008yzH33Aljk12vQjncVxrsJ0vVsr6H8DK4i2gOCmqEZURGaIEWDY1TEiNc4ddigPwmnrXOA21wTEijMe4My55VGz33Zie96xFNSKPJ7gTLWXVbgWnxtyvA4CDbSSMQe4IS+s1AQiMkfftAOCwD4I26dKl6bvIklOFX4VoTxsWJAdAXiEM8K39UvOlNrrmwfR8mGGIoVcgSCsaZ0gg0h0RwqZNsERmthnmzqvNrw23hFHhW8NQuxV271QRGKIV5o4NEQZcDkabaJmT9AvEa4W4s2ozLyFVCFQ8mnaSQUQqfCqSAY/mwkGLQffflhBqSPvsBnzwISGAaaCDg6TzK3mFBoBsyK7PbtDnH0gBYBLwiQvhWhqu0av5QITsA0A9dv0v5hWBEfdyFR4VMrWk/ac9L6hb+2FvEv/d4f8BGNHHgNgD62udJ5jenONn+fejPKt3QEle2Y/awDM6os2LOGqFz8bDKayj4Y8NNjPrJ69jRW0mNd89QEeWSozDGd3wfFuJfoz95OOunF+LL0ZCisisizDpJOHWBXNGPImh/Vln5uVzF8JFN6sHl9qVxC0wd4Ld7PP1AOv6iXibNcAql4xmbaulX7+9ljK2csmsXnDC0a78mq/ZTnnLCh+vCwNylOzapdUq7GEFHXi/ZcOC2gZ6uLxuGEXp2A6rWhny3TLzuhwsG36JbCTd869dnNIyrujT0L9yANrXNbt33jkoLwsYuVM82HgcaC5FxZFsmQa0Z1+Adrf2G82uo+9l32zqCAMDIoDO+Y8WZuYR6CobYACrrdKRnwf24xDDEvJUoCBWoPDjbfbHMOgVxDupnfV8KuEh8pvLLMoVx36DkgwYn3NnvIIbmI7R7olaLWAJ/hxMqNJeJhWc1a9tq+1nBeW7BwLDaI12o4hFLRf26i3LfS8jtbzMZYSHVSwlKRaPBHl4eMwefS7Asm5TT/GlsF/LAYyQSgBjpWzuh/qZRf7rahqR3eTnnfWpjbDzNuzjLZ/QV0HG5qXJjQ3iB5UKCqJ28INkr/RJa3YVht+ml+tRGGTPeI/204Sp3VXgNqRI1O49fdM6MHvi5LRvf1ghcM3n3fPKZjis2fNDADbQ+uqS91/ACrS+udQXCOxkLnk1bPkUXL+6tOkPEew4ZsAEMnAK1JB1d20SOQ4LzyK9IWx3Pc5aXBZA+DC9oNAOe5WY1F4MxmexrqMtDjSl3XCn15/IakM+qscvWri1k85ynVrZ667nXXHkApQvxu/thDgvYf2KfaYEcl05czXYNvVrA0yJLnbURk/6MDh+9LS/HOJbDUe3pO8/VpHEbKU5k/Dg8E89jqm3i4h6uAl7ADFfdYR/q/kzmX2kSkahr3eTbkeTQV0Yd15rOCg50s5vTRUzW6zpe/39pQ849F9Bbt1AxkFy/9uVZbnx2EPlCbqvbgicKEIZvl2QvutucHrkCYgjilMM9ws3/Tj3qL5ulDxkAfY++jBiDturSO7h2McF2oJJZohAnTW1GAnVO92Ls+uxigU7J/uzpGejssBHlIszYc7pz4BMFVUR3RdJZU8VXCNmVgG0GJDugPEIQVSg1BSfkX9V1udWj+BdwGrKMj369EkXUXX9+/h7heWbJWnvMAtfwiTIu+MOgd9wut/XbGvF4YxlesjvuKG52RdnWsA9y6/NK/vzr3CrU24rtEpyhJmj/bWKRcoHQ8llhJ+t5c167PZm0v2mytbdu0zzctlyxiGw1vhq+/TkqDO3ae7IYgqEsicFp3LPU+1fs7xc0aUg9MtWphf9K9z2uzOHmb+cvX5Ax3OpiZvAfdQE5Ml56sf04P6b9r9DazUShrsmZBLI6vvbqHkDeNUHBDx6pDvm5p/f4ySn9pu72l9LravMsYfSWWTnFMHvAhFZshVZ64wrfBgJrIAEjqLcyGzIUTevRfqNe/gy247EEssnBXqDQ/XttfWX3HORT8DPtc8Sj0GE6Cd4tWkJwY7hiaiSf2jxSVRuuOsqKXPmp1No1gJdMlVCnxRexR47emhPfUL5Fc+JU3sM2in2ToSmDZ3329umA0+HAB5nS7JnVRVxz4BmeqAl9TSfYUkbymVkiDNK1ZiM+abbSOS+4ydJe93OifXHHe/D6+DUzDo0rUpgWFX4cbZ3x6uf8jLIqsWAeevo/F3QiZX0+JFfvzb3emP/6Y2oEhj3znes/2lgzxOQKVd4KMs8m4LwDvLoqXzs4Q6gFElOE22fFsw1h2YzvuEUAyhu0eBah+46cpg3D4om/e3YCUP2fOdumnmWS0iaXx4OcVY4UeLfBO0aNw9d3FCQkt7iXz96rQGZO6vuj1Zu907u/iAX1T5a7JY7iKbqkmRtejGknW2NnAgM45GOnnbSIn/G6RBkLl7rXdZ6tSYRRHUv6zvm5u7nDTvXEM8iywxsddOnYcRYkAw=
*/