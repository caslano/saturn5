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
DRgPDAEmA4O2tboj/ObfI9/H3o9efM9aFmunrnK3VbvT/FA/mT67Pus/ofwTuhf8Y7uH/DO+vL5I391f8x67d77av/j9+TVIU+HoU1OGxoxptei1rbW3G7kamxtRG5gac+tdqnL7G38xE/pZeyg+krmR8ScSjx81Oq+8nJud5614r2gFKPfsQAjkU+3oB6jvzPTM9CQE8kNXQk/DLMEJoTQhZ+KJwxzC+RI2Mf70n5nNX8uvFFkwbDQE74j0etTZOwg7aDmosXDz8HqIsnxnQNCAVURjQl6CYUaqgf9k8nC+nu6FC1KEBaJ24byTPUtf5/Xaz4CGeur+UnLpv3DU3EBC6/uxK+3BxzSIuzN+o+6B7YdQOwzcYXzeJiL995cOttOVy/EMZthnWsfzeROcDbSV5MqwvwkKQnCGyxR4uA224xGiNBcrexMatY6s2NSxhirQXhepHGOb3LDyNEIPIboXKNchDvGVCsAxBLzjwsHBN2EXxsATYwfNADqAcBkuupoGrl7Tkc1AmE5YBt5WqfakOCoZekQbgRuoV/GOABx9kSKVMjX2uMnNGmfX/W5e/c2pC3iCUUG4/cuhJnGv5cuPfrNbvVAe1WLjVoQN/FyGVFIKSQalkeQGZGwKPVC8twffLqqXcfuUINtHWIwFoIP5tNS15WuGlDmpHK/AKkUKFGBPslFe+u0y7M27t/9+oHPosen6PgiERraL
*/