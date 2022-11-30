#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/basic_expr.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_CHILD(Z, N, DATA)                                                       \
        typedef BOOST_PP_CAT(Arg, N) BOOST_PP_CAT(proto_child, N);                              \
        BOOST_PP_CAT(proto_child, N) BOOST_PP_CAT(child, N);                                    \
        /**< INTERNAL ONLY */

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_VOID(Z, N, DATA)                                                        \
        typedef void BOOST_PP_CAT(proto_child, N);                                              \
        /**< INTERNAL ONLY */

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/basic_expr.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file basic_expr.hpp
    /// Contains definition of basic_expr\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    // The expr<> specializations are actually defined here.
    #define BOOST_PROTO_DEFINE_TERMINAL
    #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, 0, <boost/proto/detail/basic_expr.hpp>))
    #include BOOST_PP_ITERATE()

    #undef BOOST_PROTO_DEFINE_TERMINAL
    #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/basic_expr.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_CHILD
    #undef BOOST_PROTO_VOID

#else

    #define ARG_COUNT BOOST_PP_MAX(1, BOOST_PP_ITERATION())

    /// \brief Simplified representation of a node in an expression tree.
    ///
    /// \c proto::basic_expr\<\> is a node in an expression template tree. It
    /// is a container for its child sub-trees. It also serves as
    /// the terminal nodes of the tree.
    ///
    /// \c Tag is type that represents the operation encoded by
    ///             this expression. It is typically one of the structs
    ///             in the \c boost::proto::tag namespace, but it doesn't
    ///             have to be.
    ///
    /// \c Args is a type list representing the type of the children
    ///             of this expression. It is an instantiation of one
    ///             of \c proto::list1\<\>, \c proto::list2\<\>, etc. The
    ///             child types must all themselves be either \c expr\<\>
    ///             or <tt>proto::expr\<\>&</tt>. If \c Args is an
    ///             instantiation of \c proto::term\<\> then this
    ///             \c expr\<\> type represents a terminal expression;
    ///             the parameter to the \c proto::term\<\> template
    ///             represents the terminal's value type.
    ///
    /// \c Arity is an integral constant representing the number of child
    ///             nodes this node contains. If \c Arity is 0, then this
    ///             node is a terminal.
    ///
    /// \c proto::basic_expr\<\> is a valid Fusion random-access sequence, where
    /// the elements of the sequence are the child expressions.
    #ifdef BOOST_PROTO_DEFINE_TERMINAL
    template<typename Tag, typename Arg0>
    struct basic_expr<Tag, term<Arg0>, 0>
    #else
    template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(ARG_COUNT, typename Arg)>
    struct basic_expr<Tag, BOOST_PP_CAT(list, BOOST_PP_ITERATION())<BOOST_PP_ENUM_PARAMS(ARG_COUNT, Arg)>, BOOST_PP_ITERATION() >
    #endif
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = BOOST_PP_ITERATION();
        typedef mpl::long_<BOOST_PP_ITERATION() > proto_arity;
        typedef basic_expr proto_base_expr;
        #ifdef BOOST_PROTO_DEFINE_TERMINAL
        typedef term<Arg0> proto_args;
        #else
        typedef BOOST_PP_CAT(list, BOOST_PP_ITERATION())<BOOST_PP_ENUM_PARAMS(ARG_COUNT, Arg)> proto_args;
        #endif
        typedef basic_expr proto_grammar;
        typedef basic_default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; /**< INTERNAL ONLY */

        BOOST_PP_REPEAT(ARG_COUNT, BOOST_PROTO_CHILD, ~)
        BOOST_PP_REPEAT_FROM_TO(ARG_COUNT, BOOST_PROTO_MAX_ARITY, BOOST_PROTO_VOID, ~)

        /// \return *this
        ///
        BOOST_FORCEINLINE
        basic_expr const &proto_base() const
        {
            return *this;
        }

        /// \overload
        ///
        BOOST_FORCEINLINE
        basic_expr &proto_base()
        {
            return *this;
        }

    #ifdef BOOST_PROTO_DEFINE_TERMINAL
        /// \return A new \c expr\<\> object initialized with the specified
        /// arguments.
        ///
        template<typename A0>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 &a0)
        {
            return detail::make_terminal(a0, static_cast<basic_expr *>(0), static_cast<proto_args *>(0));
        }

        /// \overload
        ///
        template<typename A0>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 const &a0)
        {
            return detail::make_terminal(a0, static_cast<basic_expr *>(0), static_cast<proto_args *>(0));
        }
    #else
        /// \return A new \c expr\<\> object initialized with the specified
        /// arguments.
        ///
        template<BOOST_PP_ENUM_PARAMS(ARG_COUNT, typename A)>
        BOOST_FORCEINLINE
        static basic_expr const make(BOOST_PP_ENUM_BINARY_PARAMS(ARG_COUNT, A, const &a))
        {
            basic_expr that = {BOOST_PP_ENUM_PARAMS(ARG_COUNT, a)};
            return that;
        }
    #endif

    #if 1 == BOOST_PP_ITERATION()
        /// If \c Tag is \c boost::proto::tag::address_of and \c proto_child0 is
        /// <tt>T&</tt>, then \c address_of_hack_type_ is <tt>T*</tt>.
        /// Otherwise, it is some undefined type.
        typedef typename detail::address_of_hack<Tag, proto_child0>::type address_of_hack_type_;

        /// \return The address of <tt>this->child0</tt> if \c Tag is
        /// \c boost::proto::tag::address_of. Otherwise, this function will
        /// fail to compile.
        ///
        /// \attention Proto overloads <tt>operator&</tt>, which means that
        /// proto-ified objects cannot have their addresses taken, unless we use
        /// the following hack to make \c &x implicitly convertible to \c X*.
        BOOST_FORCEINLINE
        operator address_of_hack_type_() const
        {
            return boost::addressof(this->child0);
        }
    #else
        /// INTERNAL ONLY
        ///
        typedef detail::not_a_valid_type address_of_hack_type_;
    #endif
    };

#undef ARG_COUNT

#endif

/* basic_expr.hpp
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
*/