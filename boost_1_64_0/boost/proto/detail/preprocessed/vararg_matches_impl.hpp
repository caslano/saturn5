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
0xuPmMRmYDqWuzRrAuLy6xATt4kxlsk6wcN05A/3iEw4FqwG7a++WvxjvJvUfvQXf2EO6DSyVyEpUeESo8uOYhj6w9U8cdIY0EvITlCRs1M6OUQQmWUjWUif28QXgyjKw8hFoYDSlv4CzQAVr6sNnUs/jumbBkNc2j2nHspGWncXekvFba0MS3X90pZSUNoCeskZqfS2FUtnANdXlnDMaN1tg2TpKcpX0EyBZ4HSHD8lavoI8DCVn8QrkakQJBNXbktcsZfUtOTIHpPGblP/X2J/XqWJMZ6aP0LdkMVER3GFslnxTX30pfCFwa47Z+hoa+Q2afvWR5YMRx8joMPj/FzsD3oVMA4bRsmQG+qVuo1t0AHDcYE4u85dlMjJlId9ZG3F3uw97unqbX/uIu5daphpCBmMyGGh9j/cI4QwbVAzeayBkiX+jqbc8HgyQJQouTJb6DCDJ+zzFvBolcx0TZsp1Yt8WFH/l9lluD1vH7IaBNEs++fnTD8/FK+zz2VePMi3SQBPWAPXCKxAxgQy7kkZWcO1Qh5UncJhIjUMlUMumuYnxQS09S3OXA==
*/