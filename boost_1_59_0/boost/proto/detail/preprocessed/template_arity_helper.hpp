    ///////////////////////////////////////////////////////////////////////////////
    // template_arity_helper.hpp
    // Overloads of template_arity_helper, used by the template_arity\<\> class template
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<
        template<typename P0> class F
      , typename T0
    >
    sized_type<2>::type
    template_arity_helper(F<T0> **, mpl::int_<1> *);
    template<
        template<typename P0 , typename P1> class F
      , typename T0 , typename T1
    >
    sized_type<3>::type
    template_arity_helper(F<T0 , T1> **, mpl::int_<2> *);
    template<
        template<typename P0 , typename P1 , typename P2> class F
      , typename T0 , typename T1 , typename T2
    >
    sized_type<4>::type
    template_arity_helper(F<T0 , T1 , T2> **, mpl::int_<3> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3> class F
      , typename T0 , typename T1 , typename T2 , typename T3
    >
    sized_type<5>::type
    template_arity_helper(F<T0 , T1 , T2 , T3> **, mpl::int_<4> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3 , typename P4> class F
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4
    >
    sized_type<6>::type
    template_arity_helper(F<T0 , T1 , T2 , T3 , T4> **, mpl::int_<5> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3 , typename P4 , typename P5> class F
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5
    >
    sized_type<7>::type
    template_arity_helper(F<T0 , T1 , T2 , T3 , T4 , T5> **, mpl::int_<6> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6> class F
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6
    >
    sized_type<8>::type
    template_arity_helper(F<T0 , T1 , T2 , T3 , T4 , T5 , T6> **, mpl::int_<7> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7> class F
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7
    >
    sized_type<9>::type
    template_arity_helper(F<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7> **, mpl::int_<8> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7 , typename P8> class F
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8
    >
    sized_type<10>::type
    template_arity_helper(F<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8> **, mpl::int_<9> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7 , typename P8 , typename P9> class F
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9
    >
    sized_type<11>::type
    template_arity_helper(F<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> **, mpl::int_<10> *);

/* template_arity_helper.hpp
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
*/