    ///////////////////////////////////////////////////////////////////////////////
    /// \file vararg_matches_impl.hpp
    /// Specializations of the vararg_matches_impl template
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, 2, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::child1>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::child1>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, 2 + 1, To>
        >
    {};
    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, 2, 2>
      : matches_<
            typename detail::expr_traits<typename Args::child1>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::child1>::value_type::proto_grammar
          , Back
        >
    {};
    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, 3, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::child2>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::child2>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, 3 + 1, To>
        >
    {};
    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, 3, 3>
      : matches_<
            typename detail::expr_traits<typename Args::child2>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::child2>::value_type::proto_grammar
          , Back
        >
    {};
    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, 4, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::child3>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::child3>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, 4 + 1, To>
        >
    {};
    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, 4, 4>
      : matches_<
            typename detail::expr_traits<typename Args::child3>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::child3>::value_type::proto_grammar
          , Back
        >
    {};
    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, 5, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::child4>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::child4>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, 5 + 1, To>
        >
    {};
    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, 5, 5>
      : matches_<
            typename detail::expr_traits<typename Args::child4>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::child4>::value_type::proto_grammar
          , Back
        >
    {};
    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, 6, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::child5>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::child5>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, 6 + 1, To>
        >
    {};
    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, 6, 6>
      : matches_<
            typename detail::expr_traits<typename Args::child5>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::child5>::value_type::proto_grammar
          , Back
        >
    {};
    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, 7, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::child6>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::child6>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, 7 + 1, To>
        >
    {};
    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, 7, 7>
      : matches_<
            typename detail::expr_traits<typename Args::child6>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::child6>::value_type::proto_grammar
          , Back
        >
    {};
    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, 8, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::child7>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::child7>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, 8 + 1, To>
        >
    {};
    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, 8, 8>
      : matches_<
            typename detail::expr_traits<typename Args::child7>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::child7>::value_type::proto_grammar
          , Back
        >
    {};
    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, 9, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::child8>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::child8>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, 9 + 1, To>
        >
    {};
    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, 9, 9>
      : matches_<
            typename detail::expr_traits<typename Args::child8>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::child8>::value_type::proto_grammar
          , Back
        >
    {};
    template<typename Args, typename Back, long To>
    struct vararg_matches_impl<Args, Back, 10, To>
      : and_2<
            matches_<
                typename detail::expr_traits<typename Args::child9>::value_type::proto_derived_expr
              , typename detail::expr_traits<typename Args::child9>::value_type::proto_grammar
              , Back
            >::value
          , vararg_matches_impl<Args, Back, 10 + 1, To>
        >
    {};
    template<typename Args, typename Back>
    struct vararg_matches_impl<Args, Back, 10, 10>
      : matches_<
            typename detail::expr_traits<typename Args::child9>::value_type::proto_derived_expr
          , typename detail::expr_traits<typename Args::child9>::value_type::proto_grammar
          , Back
        >
    {};

/* vararg_matches_impl.hpp
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
*/