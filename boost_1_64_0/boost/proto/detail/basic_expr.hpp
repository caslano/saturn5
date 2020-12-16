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
ydISM55Oxq5c4rgn2sSWVtc59rwBVWjc1odFba3S0ragyBcez8tREc+8q23ewT6BYt3E3e0cx53TIIvUujBiLAMO43vscFwrTNUo3aW5EzCKFq6G+MPF66K3dTrLLsZj0pagUcwzRuoIjM8TF423arTNM50JN7ccbkK4L4lw4UN3RVtnOC6QyGmA+6qoHQrfjpTOxT5HJtzL42+jMa1nhXaeIban3yfewXFlKUxRK/TS+Y9x8k8+wK0aV4Y8ZUry19sGdsO5lnmRj8+i0qC7yVqILoEOKCF208os3TfjcU9la2pymh5KnJi35a8Qx/nCOI7zyu4jHxtyuTyJytBvsy+7OC7DawFEIwDNHOLuwF3gGYQLOFT2nHEZXhxD2QuwDN4aYP8EnlA3tPgl47J+nSN9X/4Kqmvkyp58S/iW4zLQEwNPpH8KlP3yTljmpsmo9517KpRblO/6vAiNxfT+DnYRYEse1nYLGmHON/X6QL8NerRlNzmWsc9Yfjsq3ydAePu491XgPjQeE+g/e994iS93YugMzztyVYLh+ASa7/ly1x8o8nHG7NUJxq9kgXbzGgSHGx8OEavvyx52bn1zJ5Rf69pUHudf2blOKN9jfJ50XSrH3SKUb16Pys+v8X7a61P5Fjhshrb+8UZUDsfSMphwsrrfcWOC7axssP4VN/Xl0DkUmwLNa29GsJjX7125v+LenMpvQeU071g9h3sYRY9l+WeudluEwZGCRg2zY7sEiscHur+xDtxHBo/zsVzH6+wAZ3WFgMwf7UFXRlg/WUYeYUS0f+nh5wNsm2A/uKaD7W4GGLXrwrUJNjv0nZ7xvB3O2iNHeyG+He2f13Wwc+PuTrbrHYccfLQS6ibar1+PYDEx0T7n+mP4+irzvyPa39+gh8Wknra4kYNvrU7We7Wb9DCMYhxIg07OwWEFgcKM4Pw7XXLwCxuT43HkpgjDpBChy5z3JQ/nsboC/Dk3I/iup+d1f/3WCB8v1Inx+qWDbUI61AnYkZuPYVuj9cdMwC442PbqyPP0MsbdjvE7hgIpLKkKCT4cA3/UzSdH8bOKvJSYec3N16EOleuHjzdKZSBklALmboxXRHg53DK7pGoEzNX4XtxwvNO6rpu6AEnUz+nhG9iDOP6JrivqopWdwPlNqImPKfhIrkfuEjhvs8QImrMTeuRNznu2kGmhpVhfncjHssPxTmlblqhzFv18HvjqPDXSp2AulqpqMQ12LJ9ciPTuuqowLFMr3DwefK+L0Ri0tUmVtqnAOT0hEz4n4tu2dQsSuRZujg/4viTqV1cVxnaZ6Kf7APdVEd+mMl2XmgKRdyf4viNqb9rlBqTdROB8nmjvByLcQtY6tSDD4/yewL0UtcHUpc4r3Qn3EDJow9c57pzWplNNmoqpc+w7EW6rNKp9ujHu/BD3B1F7K1AzZSprBBuxmZAvOJrrUtq0qapK+ACjQ96/jr6Hyao8SdtC9AFl4/nzx6jNpqzzyspaRAmMvO4hGrcqSfMOhFHRpyKLx+1ar+W4NjewKKpSwEeGJgxwb8hx58sil7qG56Bl550er/vbRLi6wCT1UgPyaH3X+yBzv9qoHVmiZF4lEvD3fAeFj3nAcU9hEJ4Cn2JHoM1e3lgb3AWjN6yikm2e1pkYQUxemkLhXYjjzmJWhrbNtNgbDe4lNqoftI+2snUj0DqDPFTDnY3jnshBDSM7mJePhAeIyZwO0RioCmZDA/MSMlzMzrp8a2zdR7hlK2tZ5QZxj88T7o1p3wv5jPDtsPV5dTmPRnQmT6qukuLMJqiUZs/MkQKX8D8S4+suk0XWpj3+aHZuYFf/TY7fot2eLTFdCARNg+fu2XlIVrA=
*/