#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        #include <boost/proto/detail/preprocessed/expr_variadic.hpp>
    #else
        #include <boost/proto/detail/preprocessed/expr.hpp>
    #endif

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

    // Generate variadic versions of expr
    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/expr_variadic.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file expr_variadic.hpp
    /// Contains definition of expr\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    // The expr<> specializations are actually defined here.
    #define BOOST_PROTO_DEFINE_TERMINAL
    #define BOOST_PP_ITERATION_PARAMS_1                                                         \
        (3, (0, 0, <boost/proto/detail/expr.hpp>))
    #include BOOST_PP_ITERATE()

    #undef BOOST_PROTO_DEFINE_TERMINAL
    #define BOOST_PP_ITERATION_PARAMS_1                                                         \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/expr.hpp>))
    #include BOOST_PP_ITERATE()

    // Generate non-variadic versions of expr
    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #define BOOST_NO_CXX11_VARIADIC_TEMPLATES
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/expr.hpp")

        ///////////////////////////////////////////////////////////////////////////////
        /// \file expr.hpp
        /// Contains definition of expr\<\> class template.
        //
        //  Copyright 2008 Eric Niebler. Distributed under the Boost
        //  Software License, Version 1.0. (See accompanying file
        //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

        #pragma wave option(preserve: 1)

        // The expr<> specializations are actually defined here.
        #define BOOST_PROTO_DEFINE_TERMINAL
        #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, 0, <boost/proto/detail/expr.hpp>))
        #include BOOST_PP_ITERATE()

        #undef BOOST_PROTO_DEFINE_TERMINAL
        #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/expr.hpp>))
        #include BOOST_PP_ITERATE()

        #pragma wave option(output: null)
        #undef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    #endif

    #undef BOOST_PROTO_CHILD
    #undef BOOST_PROTO_VOID

#else

    #define ARG_COUNT BOOST_PP_MAX(1, BOOST_PP_ITERATION())

    /// \brief Representation of a node in an expression tree.
    ///
    /// \c proto::expr\<\> is a node in an expression template tree. It
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
    /// \c proto::expr\<\> is a valid Fusion random-access sequence, where
    /// the elements of the sequence are the child expressions.
    #ifdef BOOST_PROTO_DEFINE_TERMINAL
    template<typename Tag, typename Arg0>
    struct expr<Tag, term<Arg0>, 0>
    #else
    template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(ARG_COUNT, typename Arg)>
    struct expr<Tag, BOOST_PP_CAT(list, BOOST_PP_ITERATION())<BOOST_PP_ENUM_PARAMS(ARG_COUNT, Arg)>, BOOST_PP_ITERATION() >
    #endif
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = BOOST_PP_ITERATION();
        typedef mpl::long_<BOOST_PP_ITERATION() > proto_arity;
        typedef expr proto_base_expr;
        #ifdef BOOST_PROTO_DEFINE_TERMINAL
        typedef term<Arg0> proto_args;
        #else
        typedef BOOST_PP_CAT(list, BOOST_PP_ITERATION())<BOOST_PP_ENUM_PARAMS(ARG_COUNT, Arg)> proto_args;
        #endif
        typedef basic_expr<Tag, proto_args, BOOST_PP_ITERATION() > proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef expr proto_derived_expr;
        typedef void proto_is_expr_; /**< INTERNAL ONLY */

        BOOST_PP_REPEAT(ARG_COUNT, BOOST_PROTO_CHILD, ~)
        BOOST_PP_REPEAT_FROM_TO(ARG_COUNT, BOOST_PROTO_MAX_ARITY, BOOST_PROTO_VOID, ~)

        /// \return *this
        ///
        BOOST_FORCEINLINE
        expr const &proto_base() const
        {
            return *this;
        }

        /// \overload
        ///
        BOOST_FORCEINLINE
        expr &proto_base()
        {
            return *this;
        }

    #ifdef BOOST_PROTO_DEFINE_TERMINAL
        /// \return A new \c expr\<\> object initialized with the specified
        /// arguments.
        ///
        template<typename A0>
        BOOST_FORCEINLINE
        static expr const make(A0 &a0)
        {
            return detail::make_terminal(a0, static_cast<expr *>(0), static_cast<proto_args *>(0));
        }

        /// \overload
        ///
        template<typename A0>
        BOOST_FORCEINLINE
        static expr const make(A0 const &a0)
        {
            return detail::make_terminal(a0, static_cast<expr *>(0), static_cast<proto_args *>(0));
        }
    #else
        /// \return A new \c expr\<\> object initialized with the specified
        /// arguments.
        ///
        template<BOOST_PP_ENUM_PARAMS(ARG_COUNT, typename A)>
        BOOST_FORCEINLINE
        static expr const make(BOOST_PP_ENUM_BINARY_PARAMS(ARG_COUNT, A, const &a))
        {
            expr that = {BOOST_PP_ENUM_PARAMS(ARG_COUNT, a)};
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

        /// Assignment
        ///
        /// \param a The rhs.
        /// \return A new \c expr\<\> node representing an assignment of \c that to \c *this.
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, expr const &>
          , 2
        > const
        operator =(expr const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, expr const &>
              , 2
            > that = {*this, a};
            return that;
        }

        /// Assignment
        ///
        /// \param a The rhs.
        /// \return A new \c expr\<\> node representing an assignment of \c a to \c *this.
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }

        /// \overload
        ///
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }

    #ifdef BOOST_PROTO_DEFINE_TERMINAL
        /// \overload
        ///
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }

        /// \overload
        ///
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
    #endif

        /// Subscript
        ///
        /// \param a The rhs.
        /// \return A new \c expr\<\> node representing \c *this subscripted with \c a.
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }

        /// \overload
        ///
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }

    #ifdef BOOST_PROTO_DEFINE_TERMINAL
        /// \overload
        ///
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a)
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }

        /// \overload
        ///
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a)
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
    #endif

        /// Encodes the return type of \c expr\<\>::operator(), for use with \c boost::result_of\<\>
        ///
        template<typename Sig>
        struct result
        {
            typedef typename result_of::funop<Sig, expr, default_domain>::type const type;
        };

    #ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        /// \overload
        ///
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr const(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a) const
        {
            return result_of::funop<
                expr const(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
        }

    #ifdef BOOST_PROTO_DEFINE_TERMINAL
        /// \overload
        ///
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a)
        {
            return result_of::funop<
                expr(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
        }
    #endif

    #else // BOOST_NO_CXX11_VARIADIC_TEMPLATES

        /// Function call
        ///
        /// \return A new \c expr\<\> node representing the function invocation of \c (*this)().
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr const &>, 1> const
        operator ()() const
        {
            proto::expr<proto::tag::function, list1<expr const &>, 1> that = {*this};
            return that;
        }

    #ifdef BOOST_PROTO_DEFINE_TERMINAL
        /// \overload
        ///
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr &>, 1> const
        operator ()()
        {
            proto::expr<proto::tag::function, list1<expr &>, 1> that = {*this};
            return that;
        }
    #endif

    #define BOOST_PP_ITERATION_PARAMS_2                                                             \
        (3, (1, BOOST_PP_DEC(BOOST_PROTO_MAX_FUNCTION_CALL_ARITY), <boost/proto/detail/expr_funop.hpp>))
    #include BOOST_PP_ITERATE()

#endif
    };

#undef ARG_COUNT

#endif

/* expr.hpp
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
*/