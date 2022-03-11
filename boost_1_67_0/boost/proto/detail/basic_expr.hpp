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