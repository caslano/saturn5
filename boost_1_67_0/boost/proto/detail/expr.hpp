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