
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

namespace aux {

template<>
struct apply_chooser<0>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply0<
              F
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

namespace aux {

template<>
struct apply_chooser<1>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply1<
              F, T1
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

namespace aux {

template<>
struct apply_chooser<2>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply2<
              F, T1, T2
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

namespace aux {

template<>
struct apply_chooser<3>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply3<
              F, T1, T2, T3
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

namespace aux {

template<>
struct apply_chooser<4>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply4<
              F, T1, T2, T3, T4
            > type;
    };
};

} // namespace aux

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

namespace aux {

template<>
struct apply_chooser<5>
{
    template<
          typename F, typename T1, typename T2, typename T3, typename T4
        , typename T5
        >
    struct result_
    {
        typedef apply5<
              F, T1, T2, T3, T4, T5
            > type;
    };
};

} // namespace aux

namespace aux {

template< typename T >
struct is_apply_arg
{
    static bool const value  = true;
};

template<>
struct is_apply_arg<na>
{
    static bool const value  = false;
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    >
struct apply_count_args
{
    static int const value  = is_apply_arg<T1>::value + is_apply_arg<T2>::value + is_apply_arg<T3>::value + is_apply_arg<T4>::value + is_apply_arg<T5>::value;

};

}

template<
      typename F, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na
    >
struct apply
    : aux::apply_chooser<
          aux::apply_count_args< T1,T2,T3,T4,T5 >::value
        >::template result_< F,T1,T2,T3,T4,T5 >::type
{
};

}}


/* apply.hpp
PF4EOWD1+BAPPTaE5XEhco0JkW88CCVXGkGucyNxkrhL2DozHgQRRmwkrhAZhAODCLsTYcRG4gqRTTg1Z/yF5lq+VJu0SZu0SZu0SZu0SZu0SZu06X9teuL3/4/z8QsODngs9//HV9ZJjiZnLObmWAqdMd2W6z+f6a9ZSwN9/AIClPp99KMQ6H/TNaLwa9XG685HH+P9if8t9yHatleW+6yeHhuQFHLKpdaHC48mX2tv6f7BJ3/fYnHvQ/yr7jcM1V9nH1tt4B+r589vu3j1z2u3ZDmEWbrf0NL198d7H+JRnbwe5HXSqGTucYMryfU4O6yI1bAO2mM71fXdmjgUHTAIa2Ek1sEVWA+3YH08hE54CRtgCjbEb7ERZmJjLEl7mqItNsfa2AKdsRV6P8T9NHmvHcZElbZ0P80TuZfGdB/NI9xDkxhV+oneR3M3qvRju5fmYe+jsXAPzX/8/TP/K/fOdG6hXd/VJm3SJm3SJm36f57+nPP/cY/l/P+wmfP/Q2U5/8d3UDn/j7ls7vxf+nlq5//a+f8TOv+PGaNv/9NPLTx2plL6hjERJcJOXXL+a8//U6zk9SCvk0asYyOPr1jlPv+vghWxKtbBatgM7bETVse+WANHYk0MxFoYjrVxHtbBlVgXt2I9jMf6eBmfxc+xAWZgQxkHpxFWwcZYH5tgR2yKQ7AZ+mBznIwtMApb4mZshXuxNSZgG/wMXfAOtsVs7IDl2AYd0R47YwPshi7YHbtjDxyM7jgWe+I07IXR2A83YX/cgx54GAdgIg7EmzgI7+MwVN6kPLECDkcHHIFNcCS6ohf2wlE4BkdjBD6Py9Abd+AYPIZ+eB798TqOw9sYgPcwEK2teH/HOjgB2+EkdMdgHIqT0RdDMARDcQGG4RacgodwKl7COZiCc/FbjORfJs7DkqU5ttEW52NtjEJnXIAdcRH2wSU4ApdiAC7DqRiNS3A5bsAV+DauxHO4Cq/havwa1+CP+Cr+jmvxaeU9EavjemyIG7AtvoY9cDMOwS3og1txOm7DKHwdN2MMHsTtmIA78EN8A29hLH6POzELd+FTvK/sRjvcg/XwTWyJ+7ELvoUe+DaOxgM4BeNwLr6D6/EgvoWH8ATG40V8Fz/Dw3gHj+E/8TiWsGacI3wGT2ItfA+b4insgKdxMCbgBDyD0/Aszsf3cTUm4ut4Dt/CD/AEnsdP8AL+DS/iL3gJS/N+cxkr4xWsi1exBX6Iz+FH6IlJOAk/xln4CS7Ca7gOP8M38HN8B2+hl3Z98JGvD2rXBrVrg3mvDSa3064NapM2/b9MT/z83z8o1Cd00iOf/9fQ2VR80IzvasklOT9X7kMLDQhnxTRbf23geGWdaTxjJ7k2UE7uZ7MmSnPykHpWf22ge99BPuMZyjg4yM8/OLAI99SVpIbmumcM9+/Jut/AargO53PikmFYt+F24aAQ/To9za9zPuukbR319w1XZe0VGKd9WiLl+SofOHWqafzkybYsQGX+KH9bj8cRwYb5eObLNM8Zw3y/jFs9OUB/C6T+b+IMvy/AMkOZk8yHVNWP2a1/Tq3lOV2Qe/qryRjileU56c6pnpMyELhsKzvL20r/XEp9UPBzycrzXLLzPJcM41jy8gMOyrJ0M88vU/X81PsoVu7VP0dUIBKI25xU+tIunk9waMiE8Bl+Yfrnot7xVhbuWSzFf/iERUzVSfuNvwuh3EhZVdprTfuDwn0CQwKC/EJkrPwrJQ3jBrzO/DzDNjG1WykfJPMPmBx1PH/V9nGkzjA59pRoJ8/NUxo5RO6DH0BkN+NvDcdf6CSfcVzv8vdjjym3XBf62xd59o/FsdR/o47xYTntqyRjpBs=
*/