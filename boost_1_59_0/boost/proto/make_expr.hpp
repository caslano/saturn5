///////////////////////////////////////////////////////////////////////////////
/// \file make_expr.hpp
/// Definition of the \c make_expr() and \c unpack_expr() utilities for
/// building Proto expression nodes from child nodes or from a Fusion
/// sequence of child nodes, respectively.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_MAKE_EXPR_HPP_EAN_04_01_2005
#define BOOST_PROTO_MAKE_EXPR_HPP_EAN_04_01_2005

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/ref.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/domain.hpp>
#include <boost/proto/generate.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/include/value_of.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/proto/detail/poly_function.hpp>
#include <boost/proto/detail/deprecated.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4180) // qualifier applied to function type has no meaning; ignored
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
/// INTERNAL ONLY
///
#define BOOST_PROTO_AS_CHILD_TYPE(Z, N, DATA)                                                   \
    typename boost::proto::detail::protoify<                                                    \
        BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(3, 0, DATA), N)                                        \
      , BOOST_PP_TUPLE_ELEM(3, 2, DATA)                                                         \
    >::result_type                                                                              \
    /**/

/// INTERNAL ONLY
///
#define BOOST_PROTO_AS_CHILD(Z, N, DATA)                                                        \
    boost::proto::detail::protoify<                                                             \
        BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(3, 0, DATA), N)                                        \
      , BOOST_PP_TUPLE_ELEM(3, 2, DATA)                                                         \
    >()(BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(3, 1, DATA), N))                                       \
    /**/

    namespace detail
    {
        template<typename T, typename Domain>
        struct protoify
          : Domain::template as_expr<T>
        {};

        template<typename T, typename Domain>
        struct protoify<T &, Domain>
          : Domain::template as_child<T>
        {};

        template<typename T, typename Domain>
        struct protoify<boost::reference_wrapper<T>, Domain>
          : Domain::template as_child<T>
        {};

        template<typename T, typename Domain>
        struct protoify<boost::reference_wrapper<T> const, Domain>
          : Domain::template as_child<T>
        {};

        // Definition of detail::unpack_expr_
        #include <boost/proto/detail/unpack_expr_.hpp>

        // Definition of detail::make_expr_
        #include <boost/proto/detail/make_expr_.hpp>
    }

    namespace result_of
    {
        /// \brief Metafunction that computes the return type of the
        /// \c make_expr() function, with a domain deduced from the
        /// domains of the children.
        ///
        /// Use the <tt>result_of::make_expr\<\></tt> metafunction to
        /// compute the return type of the \c make_expr() function.
        ///
        /// In this specialization, the domain is deduced from the
        /// domains of the child types. (If
        /// <tt>is_domain\<A0\>::value</tt> is \c true, then another
        /// specialization is selected.)
        template<
            typename Tag
          , BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename A)
          , typename Void1  // = void
          , typename Void2  // = void
        >
        struct make_expr
        {
            /// Same as <tt>result_of::make_expr\<Tag, D, A0, ... AN\>::type</tt>
            /// where \c D is the deduced domain, which is calculated as follows:
            ///
            /// For each \c x in <tt>[0,N)</tt> (proceeding in order beginning with
            /// <tt>x=0</tt>), if <tt>domain_of\<Ax\>::type</tt> is not
            /// \c default_domain, then \c D is <tt>domain_of\<Ax\>::type</tt>.
            /// Otherwise, \c D is \c default_domain.
            typedef
                typename detail::make_expr_<
                    Tag
                  , deduce_domain
                    BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, A)
                >::result_type
            type;
        };

        /// \brief Metafunction that computes the return type of the
        /// \c make_expr() function, within the specified domain.
        ///
        /// Use the <tt>result_of::make_expr\<\></tt> metafunction to compute
        /// the return type of the \c make_expr() function.
        template<
            typename Tag
          , typename Domain
            BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, typename A)
        >
        struct make_expr<
            Tag
          , Domain
            BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, A)
          , typename Domain::proto_is_domain_
        >
        {
            /// If \c Tag is <tt>tag::terminal</tt>, then \c type is a
            /// typedef for <tt>boost::result_of\<Domain(expr\<tag::terminal,
            /// term\<A0\> \>)\>::type</tt>.
            ///
            /// Otherwise, \c type is a typedef for <tt>boost::result_of\<Domain(expr\<Tag,
            /// listN\< as_child\<A0\>::type, ... as_child\<AN\>::type\>)
            /// \>::type</tt>, where \c N is the number of non-void template
            /// arguments, and <tt>as_child\<A\>::type</tt> is evaluated as
            /// follows:
            ///
            /// \li If <tt>is_expr\<A\>::value</tt> is \c true, then the
            /// child type is \c A.
            /// \li If \c A is <tt>B &</tt> or <tt>cv boost::reference_wrapper\<B\></tt>,
            /// and <tt>is_expr\<B\>::value</tt> is \c true, then the
            /// child type is <tt>B &</tt>.
            /// \li If <tt>is_expr\<A\>::value</tt> is \c false, then the
            /// child type is <tt>boost::result_of\<Domain(expr\<tag::terminal, term\<A\> \>
            /// )\>::type</tt>.
            /// \li If \c A is <tt>B &</tt> or <tt>cv boost::reference_wrapper\<B\></tt>,
            /// and <tt>is_expr\<B\>::value</tt> is \c false, then the
            /// child type is <tt>boost::result_of\<Domain(expr\<tag::terminal, term\<B &\> \>
            /// )\>::type</tt>.
            typedef
                typename detail::make_expr_<
                    Tag
                  , Domain
                    BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, A)
                >::result_type
            type;
        };

        /// \brief Metafunction that computes the return type of the
        /// \c unpack_expr() function, with a domain deduced from the
        /// domains of the children.
        ///
        /// Use the <tt>result_of::unpack_expr\<\></tt> metafunction to
        /// compute the return type of the \c unpack_expr() function.
        ///
        /// \c Sequence is a Fusion Forward Sequence.
        ///
        /// In this specialization, the domain is deduced from the
        /// domains of the child types. (If
        /// <tt>is_domain\<Sequence>::value</tt> is \c true, then another
        /// specialization is selected.)
        template<
            typename Tag
          , typename Sequence
          , typename Void1  // = void
          , typename Void2  // = void
        >
        struct unpack_expr
        {
            /// Let \c S be the type of a Fusion Random Access Sequence
            /// equivalent to \c Sequence. Then \c type is the
            /// same as <tt>result_of::make_expr\<Tag,
            /// fusion::result_of::value_at_c\<S, 0\>::type, ...
            /// fusion::result_of::value_at_c\<S, N-1\>::type\>::type</tt>,
            /// where \c N is the size of \c S.
            typedef
                typename detail::unpack_expr_<
                    Tag
                  , deduce_domain
                  , Sequence
                  , fusion::result_of::size<Sequence>::type::value
                >::type
            type;
        };

        /// \brief Metafunction that computes the return type of the
        /// \c unpack_expr() function, within the specified domain.
        ///
        /// Use the <tt>result_of::make_expr\<\></tt> metafunction to compute
        /// the return type of the \c make_expr() function.
        template<typename Tag, typename Domain, typename Sequence>
        struct unpack_expr<Tag, Domain, Sequence, typename Domain::proto_is_domain_>
        {
            /// Let \c S be the type of a Fusion Random Access Sequence
            /// equivalent to \c Sequence. Then \c type is the
            /// same as <tt>result_of::make_expr\<Tag, Domain,
            /// fusion::result_of::value_at_c\<S, 0\>::type, ...
            /// fusion::result_of::value_at_c\<S, N-1\>::type\>::type</tt>,
            /// where \c N is the size of \c S.
            typedef
                typename detail::unpack_expr_<
                    Tag
                  , Domain
                  , Sequence
                  , fusion::result_of::size<Sequence>::type::value
                >::type
            type;
        };
    }

    namespace functional
    {
        /// \brief A callable function object equivalent to the
        /// \c proto::make_expr() function.
        ///
        /// In all cases, <tt>functional::make_expr\<Tag, Domain\>()(a0, ... aN)</tt>
        /// is equivalent to <tt>proto::make_expr\<Tag, Domain\>(a0, ... aN)</tt>.
        ///
        /// <tt>functional::make_expr\<Tag\>()(a0, ... aN)</tt>
        /// is equivalent to <tt>proto::make_expr\<Tag\>(a0, ... aN)</tt>.
        template<typename Tag, typename Domain  /* = deduce_domain*/>
        struct make_expr
        {
            BOOST_PROTO_CALLABLE()
            BOOST_PROTO_POLY_FUNCTION()

            template<typename Sig>
            struct result;

            template<typename This, typename A0>
            struct result<This(A0)>
            {
                typedef
                    typename result_of::make_expr<
                        Tag
                      , Domain
                      , A0
                    >::type
                type;
            };

            /// Construct an expression node with tag type \c Tag
            /// and in the domain \c Domain.
            ///
            /// \return <tt>proto::make_expr\<Tag, Domain\>(a0,...aN)</tt>
            template<typename A0>
            BOOST_FORCEINLINE
            typename result_of::make_expr<
                Tag
              , Domain
              , A0 const
            >::type const
            operator ()(A0 const &a0) const
            {
                return proto::detail::make_expr_<
                    Tag
                  , Domain
                  , A0 const
                >()(a0);
            }

            // Additional overloads generated by the preprocessor ...
            #include <boost/proto/detail/make_expr_funop.hpp>

            /// INTERNAL ONLY
            ///
            template<
                BOOST_PP_ENUM_BINARY_PARAMS(
                    BOOST_PROTO_MAX_ARITY
                  , typename A
                  , = void BOOST_PP_INTERCEPT
                )
            >
            struct impl
              : detail::make_expr_<
                    Tag
                  , Domain
                    BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, A)
                >
            {};
        };

        /// \brief A callable function object equivalent to the
        /// \c proto::unpack_expr() function.
        ///
        /// In all cases, <tt>functional::unpack_expr\<Tag, Domain\>()(seq)</tt>
        /// is equivalent to <tt>proto::unpack_expr\<Tag, Domain\>(seq)</tt>.
        ///
        /// <tt>functional::unpack_expr\<Tag\>()(seq)</tt>
        /// is equivalent to <tt>proto::unpack_expr\<Tag\>(seq)</tt>.
        template<typename Tag, typename Domain /* = deduce_domain*/>
        struct unpack_expr
        {
            BOOST_PROTO_CALLABLE()

            template<typename Sig>
            struct result;

            template<typename This, typename Sequence>
            struct result<This(Sequence)>
            {
                typedef
                    typename result_of::unpack_expr<
                        Tag
                      , Domain
                      , typename remove_reference<Sequence>::type
                    >::type
                type;
            };

            /// Construct an expression node with tag type \c Tag
            /// and in the domain \c Domain.
            ///
            /// \param sequence A Fusion Forward Sequence
            /// \return <tt>proto::unpack_expr\<Tag, Domain\>(sequence)</tt>
            template<typename Sequence>
            BOOST_FORCEINLINE
            typename result_of::unpack_expr<Tag, Domain, Sequence const>::type const
            operator ()(Sequence const &sequence) const
            {
                return proto::detail::unpack_expr_<
                    Tag
                  , Domain
                  , Sequence const
                  , fusion::result_of::size<Sequence>::type::value
                >::call(sequence);
            }
        };

    } // namespace functional

    /// \brief Construct an expression of the requested tag type
    /// with a domain and with the specified arguments as children.
    ///
    /// This function template may be invoked either with or without
    /// specifying a \c Domain argument. If no domain is specified,
    /// the domain is deduced by examining in order the domains of
    /// the given arguments and taking the first that is not
    /// \c default_domain, if any such domain exists, or
    /// \c default_domain otherwise.
    ///
    /// Let \c wrap_(x) be defined such that:
    /// \li If \c x is a <tt>boost::reference_wrapper\<\></tt>,
    /// \c wrap_(x) is equivalent to <tt>as_child\<Domain\>(x.get())</tt>.
    /// \li Otherwise, \c wrap_(x) is equivalent to
    /// <tt>as_expr\<Domain\>(x)</tt>.
    ///
    /// Let <tt>make_\<Tag\>(b0,...bN)</tt> be defined as
    /// <tt>expr\<Tag, listN\<C0,...CN\> \>::make(c0,...cN)</tt>
    /// where \c Bx is the type of \c bx.
    ///
    /// \return <tt>Domain()(make_\<Tag\>(wrap_(a0),...wrap_(aN)))</tt>.
    template<typename Tag, typename A0>
    BOOST_FORCEINLINE
    typename lazy_disable_if<
        is_domain<A0>
      , result_of::make_expr<
            Tag
          , A0 const
        >
    >::type const
    make_expr(A0 const &a0)
    {
        return proto::detail::make_expr_<
            Tag
          , deduce_domain
          , A0 const
        >()(a0);
    }

    /// \overload
    ///
    template<typename Tag, typename Domain, typename C0>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
      , C0 const
    >::type const
    make_expr(C0 const &c0)
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
          , C0 const
        >()(c0);
    }

    // Additional overloads generated by the preprocessor...
    #include <boost/proto/detail/make_expr.hpp>

    /// \brief Construct an expression of the requested tag type
    /// with a domain and with childres from the specified Fusion
    /// Forward Sequence.
    ///
    /// This function template may be invoked either with or without
    /// specifying a \c Domain argument. If no domain is specified,
    /// the domain is deduced by examining in order the domains of the
    /// elements of \c sequence and taking the first that is not
    /// \c default_domain, if any such domain exists, or
    /// \c default_domain otherwise.
    ///
    /// Let \c s be a Fusion Random Access Sequence equivalent to \c sequence.
    /// Let <tt>wrap_\<N\>(s)</tt>, where \c s has type \c S, be defined
    /// such that:
    /// \li If <tt>fusion::result_of::value_at_c\<S,N\>::type</tt> is a reference,
    /// <tt>wrap_\<N\>(s)</tt> is equivalent to
    /// <tt>as_child\<Domain\>(fusion::at_c\<N\>(s))</tt>.
    /// \li Otherwise, <tt>wrap_\<N\>(s)</tt> is equivalent to
    /// <tt>as_expr\<Domain\>(fusion::at_c\<N\>(s))</tt>.
    ///
    /// Let <tt>make_\<Tag\>(b0,...bN)</tt> be defined as
    /// <tt>expr\<Tag, listN\<B0,...BN\> \>::make(b0,...bN)</tt>
    /// where \c Bx is the type of \c bx.
    ///
    /// \param sequence a Fusion Forward Sequence.
    /// \return <tt>Domain()(make_\<Tag\>(wrap_\<0\>(s),...wrap_\<N-1\>(s)))</tt>,
    /// where N is the size of \c Sequence.
    template<typename Tag, typename Sequence>
    BOOST_FORCEINLINE
    typename lazy_disable_if<
        is_domain<Sequence>
      , result_of::unpack_expr<Tag, Sequence const>
    >::type const
    unpack_expr(Sequence const &sequence)
    {
        return proto::detail::unpack_expr_<
            Tag
          , deduce_domain
          , Sequence const
          , fusion::result_of::size<Sequence>::type::value
        >::call(sequence);
    }

    /// \overload
    ///
    template<typename Tag, typename Domain, typename Sequence2>
    BOOST_FORCEINLINE
    typename result_of::unpack_expr<Tag, Domain, Sequence2 const>::type const
    unpack_expr(Sequence2 const &sequence2)
    {
        return proto::detail::unpack_expr_<
            Tag
          , Domain
          , Sequence2 const
          , fusion::result_of::size<Sequence2>::type::value
        >::call(sequence2);
    }

    /// INTERNAL ONLY
    ///
    template<typename Tag, typename Domain>
    struct is_callable<functional::make_expr<Tag, Domain> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<typename Tag, typename Domain>
    struct is_callable<functional::unpack_expr<Tag, Domain> >
      : mpl::true_
    {};

}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif // BOOST_PROTO_MAKE_EXPR_HPP_EAN_04_01_2005

/* make_expr.hpp
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
*/