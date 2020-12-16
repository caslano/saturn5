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
zF2Ys7CCLiO49+MwT2Ffm8Yw5/NhMifsdn0t+jfkO42vueCh/x/MQZiDsKk2/U5xrsBshZ1+ff6rshDtmh9v7mONdYD5Civ3oB9nVTys1v/NDXao2gZr7h1mLWz67i9bOQNgvsIitm3mO0oezEPYLx+sZil7D3MSNnbAYc4xW7whBEir2Y57CIb5CFsb0S+HdQRTfcIVdu7psiHcH8xbWOdhqeyDaTA3YbU7dSpkX4KpeLrA0mP/aqcsG2YpbOTHyHrKcmG+wg4enHaCe4e5CRsQso97cESXtRL2w7t5fZR5wGyFjV0dvZA5AfMRVmGcRYGySFgZYbfeWG1RFgOzEfZw1dUbjBmsqrDrFUvxnTYDZiZs8+E2b5kvsPLCWtQbwv3lwsoJO5pauI1xgfkJC/+r9t/c+x7jWNf7ucRG9hCYk7C0Nd0msh5gZnLvt3pw9ofC7IUtX/Dcn7Wi3e9BTq3TzDOYh7Amt2YNZMxg8vz61XX3VpYAqyDvZ7MhmfGEyTPqH+WyTtkR7Zp3o2u+5GyE+QsrKD+wjrLnMGthT4fe4LvwZ5iXsGeHiv4evMde41xauvI5+1IozFvYkqBX/GbuBasrLGhvm3OsMW1dkzc529lDYGWFLarSm7P/KkzWSuRDO74vvYZVEdbKPPgJc2If3omEjV5Y2431AJN7//taNT5nrGbH+9/2UZYMk8/ye5saa5nzMBmz+3532OtyYHLvHh1bFucZwWT9OVkuL/rd1f3Gebb6+xnZPCOYrBXnVTcseUYwuffTjzKnc/7BDMJanzxXgbkLk/kyxN0qXNk0mLuwC6nLlipLh6m9l4Hd+JbHeXscFiDM7op3orJCWElhK6O7F/UCmLWwsIXfxygzO4DvFWETAoq35tyEmQvz/LkOa8UbVkZYTJTpOM4VbZ21bzBrOhQWJGxFqutW5gvMUthPowL6M57ac7qe9OO7TRLMRVi5klXtla2BeQrzP3t4NeMJsxV2dMMb5lIuzF2Y7YWO/2KewXyFHb9XmrnkmIWcF+bTYirfaWvBigtb/Ldj0e8wwuTepzyMn8yYweRz7nI4yPeXSJg6B2eY08rKJpxHMCdhtZdcLvr9Ypi9sEXn6hZTlgJT9eAE61f+55PsL2KdIyy02WS+g2XDLIX1XbtkCeMJ8xSWsf9dBHsPzEnYj5Piuyj7z5dEDWGvzzsyz0JhLsKqbuldQ1kXmJewS4c+pTOXYPJZ1hRU+529FeYj7M3Fce2VZcFKCstst4I1dhom9/DZZVgrZbdhdYW16zZiDGsMJ2IlLGRbnZ6sMdh3wrLXRvM5o2A2wlq+vXSPfQkWLOz4zJb7WA8wB2GNZwzO49nCbIWVahbQl/uDybM1vbTDij0ZJnOidbmZZ5TlwwzCYn7y4rM8hzkLGzf7d77vWh02vl+HN/0ZF1uYPPdB59/yezoA5iFsstsdZ2Vh2jXfV52WoiwCJs9vX8UbdsqiYVWF2VQKfsBa0a75qIZltLKlMJlLHy2usE8cgRmEVX5ZYjjrSNufvXulAMYTJnN31crJgezlR4wtfm6x65zhMFkP3de+a864wEoLO38njnndAWYra+z62R2Mi7ZuZ8+Ri5TFwQKFXUtsxudMh5USljT/h6JvbZivsEo3ot+wh8AqCTs46s9KykyOGu9vzIf5aawjmL+w3L4H2MvDYTIHt7R9zOfsBZN7d87M/8pZBSsnLNR1QX3mBEye+6+zvGuyxrRr+rSxO8EagxmEVTFbOIl7h8k8u/6s8k5leTB57tG3ql1V9ll/zuHLWzMux4zjkvKwTxPGBSbXndu0bgH7C0zer2dnv1zOYpg824kvTEewHmDyjEwHzH7C3qo=
*/