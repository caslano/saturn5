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