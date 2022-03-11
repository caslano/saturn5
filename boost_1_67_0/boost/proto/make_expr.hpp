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