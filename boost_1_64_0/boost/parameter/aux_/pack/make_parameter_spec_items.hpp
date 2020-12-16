// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_MAKE_PARAMETER_SPEC_ITEMS_HPP
#define BOOST_PARAMETER_AUX_PACK_MAKE_PARAMETER_SPEC_ITEMS_HPP

namespace boost { namespace parameter { namespace aux {

    // This recursive metafunction forwards successive elements of
    // parameters::parameter_spec to make_deduced_items<>.
    // -- Cromwell D. Enage
    template <typename SpecSeq>
    struct make_deduced_list;

    // Helper for match_parameters_base_cond<...>, below.
    template <typename ArgumentPackAndError, typename SpecSeq>
    struct match_parameters_base_cond_helper;

    // Helper metafunction for make_parameter_spec_items<...>, below.
    template <typename SpecSeq, typename ...Args>
    struct make_parameter_spec_items_helper;
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/void.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename SpecSeq>
    struct make_parameter_spec_items_helper<SpecSeq>
    {
        typedef ::boost::parameter::void_ type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/pack/make_deduced_items.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/list.hpp>
#else
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename SpecSeq>
    struct make_deduced_list_not_empty
      : ::boost::parameter::aux::make_deduced_items<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            ::boost::mp11::mp_front<SpecSeq>
#else
            typename ::boost::mpl::front<SpecSeq>::type
#endif
          , ::boost::parameter::aux::make_deduced_list<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                ::boost::mp11::mp_pop_front<SpecSeq>
#else
                typename ::boost::mpl::pop_front<SpecSeq>::type
#endif
            >
        >
    {
    };
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/identity.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename SpecSeq>
    struct make_deduced_list
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_if<
            ::boost::mp11::mp_empty<SpecSeq>
          , ::boost::mp11::mp_identity< ::boost::parameter::void_>
#else
      : ::boost::mpl::eval_if<
            ::boost::mpl::empty<SpecSeq>
          , ::boost::mpl::identity< ::boost::parameter::void_>
#endif
          , ::boost::parameter::aux::make_deduced_list_not_empty<SpecSeq>
        >
    {
    };
}}} // namespace boost::parameter::aux

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename ArgumentPackAndError>
    struct is_arg_pack_error_void
      : ::boost::mpl::if_<
            ::boost::is_same<
                typename ::boost::mpl::second<ArgumentPackAndError>::type
              , ::boost::parameter::void_
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11

namespace boost { namespace parameter { namespace aux {

    // Checks if the arguments match the criteria of overload resolution.
    // If NamedList satisfies the PS0, PS1, ..., this is a metafunction
    // returning parameters.  Otherwise it has no nested ::type.
    template <typename ArgumentPackAndError, typename SpecSeq>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using match_parameters_base_cond = ::boost::mp11::mp_if<
        ::boost::mp11::mp_empty<SpecSeq>
      , ::std::is_same<
            ::boost::mp11::mp_at_c<ArgumentPackAndError,1>
          , ::boost::parameter::void_
        >
      , ::boost::parameter::aux::match_parameters_base_cond_helper<
            ArgumentPackAndError
          , SpecSeq
        >
    >;
#else
    struct match_parameters_base_cond
      : ::boost::mpl::eval_if<
            ::boost::mpl::empty<SpecSeq>
          , ::boost::parameter::aux
            ::is_arg_pack_error_void<ArgumentPackAndError>
          , ::boost::parameter::aux::match_parameters_base_cond_helper<
                ArgumentPackAndError
              , SpecSeq
            >
        >
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/pack/satisfies.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename ArgumentPackAndError, typename SpecSeq>
    struct match_parameters_base_cond_helper
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_if<
#else
      : ::boost::mpl::eval_if<
#endif
            ::boost::parameter::aux::satisfies_requirements_of<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                ::boost::mp11::mp_at_c<ArgumentPackAndError,0>
              , ::boost::mp11::mp_front<SpecSeq>
#else
                typename ::boost::mpl::first<ArgumentPackAndError>::type
              , typename ::boost::mpl::front<SpecSeq>::type
#endif
            >
          , ::boost::parameter::aux::match_parameters_base_cond<
                ArgumentPackAndError
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
              , ::boost::mp11::mp_pop_front<SpecSeq>
#else
              , typename ::boost::mpl::pop_front<SpecSeq>::type
#endif
            >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
          , ::boost::mp11::mp_false
#else
          , ::boost::mpl::false_
#endif
        >
    {
    };

    // This parameters item chaining metafunction class does not require
    // the lengths of the SpecSeq and of Args parameter pack to match.
    // Used by argument_pack to build the items in the resulting arg_list.
    // -- Cromwell D. Enage
    template <typename SpecSeq, typename ...Args>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using make_parameter_spec_items = ::boost::mp11::mp_if<
        ::boost::mp11::mp_empty<SpecSeq>
      , ::boost::mp11::mp_identity< ::boost::parameter::void_>
      , ::boost::parameter::aux
        ::make_parameter_spec_items_helper<SpecSeq,Args...>
    >;
#else
    struct make_parameter_spec_items
      : ::boost::mpl::eval_if<
            ::boost::mpl::empty<SpecSeq>
          , ::boost::mpl::identity< ::boost::parameter::void_>
          , ::boost::parameter::aux
            ::make_parameter_spec_items_helper<SpecSeq,Args...>
        >
    {
    };
#endif
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/pack/make_items.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename SpecSeq, typename A0, typename ...Args>
    struct make_parameter_spec_items_helper<SpecSeq,A0,Args...>
      : ::boost::parameter::aux::make_items<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            ::boost::mp11::mp_front<SpecSeq>
#else
            typename ::boost::mpl::front<SpecSeq>::type
#endif
          , A0
          , ::boost::parameter::aux::make_parameter_spec_items<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                ::boost::mp11::mp_pop_front<SpecSeq>
#else
                typename ::boost::mpl::pop_front<SpecSeq>::type
#endif
              , Args...
            >
        >
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* make_parameter_spec_items.hpp
u1en+/fUbwD+CKvBn6CcaQibw73abn+B/eE+OAzGkX4+jIeXwUQ4BybB62AyFJnAJep+h7rrGWO6tpWxUsvlPWOsvl5PA1gNNoapsAlMg81hHdgUNoHNYAt1J32J3FvTn6zpJ2NKNP1WhLPh4bAWbAt7wY7wRNgJ/g12hlmwCyyAPeBYeDQsUnux2kvUPkntesabru80/UvEGW/btF1+DFvCUngk3A6PgTtg+HpK9Xou9bmee7Uel8PG8D7YGt4Pu8GVsDd8APaBa2Bf+KDOpz0Es+E/4Dj4MJwAV8CpGv57uNGsNySslqOO46/leJRwNtwAM+GzWo7ntBwvw5PgK/BU+Bk8Db4KB8PXYQ58Q/vBt+FoDVcI39V+8QN4FdwGr4GfwCVwJ7xTw98Fn4L3w41wlbrrOKJr+6grn3HkS72Or2BV+DWsB3fBZvBb2AN+p+mtcoymt0/Tq41Zpul9qu34C9gGfg07O/G1Xf0Ar4B74Ez4M1wEf9X7Zh9cDX+Hj8gNz/McCMLNMAD/CavAz2Ai/A5WhXtgNfgz/JL4v6pd54d1XRdt0md+uAbhJDtYBdaCVWEGrA5TYQqsDZvDNNgW1oFHabj2sC7spPbv4ezwGiY4RfOtgZmq+Q7W+/M8ldv5MBmOhE64obA2vEDv+yzYFg6DR8Fs2A3mwEEwFxZo/FFwBJys9u/hbrPehTavz0UNMDu0PKMJVx1OhCfAKdpPXAxz4SXaH06FF8FL4UQ4DV4Fp8Mb4Qy4GM6Ey+AsuAZeBV+Cf4c74dXwCzgH1nXmG2EHuBB2gjfCwXAxlPcyOBwugZPhHXA6vAvOhsvgQng3vBfeo9c9Obx+AhRpPXjPwLxf5f8grAefhA3hKng4/AdsB1fDo+Ej8HS4Fg6Bj8Jh8Ak4Aq6HYzWd8Pz3PM3/cUz0/PfThEuCz8GW8AXN9yWt55fhsfAV7b9fhcfD1+AA+IbW/5swG76l99nbcD58R8end+G98AP4ANwG18IPobTX8Pd5OMCnvfbR8epEHZf6abs8RdvlqbADHAA7wtPgMfB02AeeAfup/ymwPzxN7afDk2B/tYefB3ZreRr4PA+s1HHlAVgfPgTDZ2+Gv4UnYJZjYp29yVwIZ6vs//yVhlkBqydmafgMlspzVyp07kp+n4qdvTK1z//3+SvTMIsO8vyVAdP3fwbLjul//TksQ7IC/7OzWIpmHJrzWBb1ObRnshQik7mYVZjNmD2YjGEBqztmCKYEcxtmI2YHxsrGH9MbMxQzDbMIsw5TikkcHrDaYvpicjFTMcsw6zGlGCsnYLXGDMBMxizArMK8itmFScmlz8EMxczALMe8mlt5Xkzlr/JX+av8Vf4qf5W/yl/lr/L3//qL+2vP/8sbm/Pnz/9zzvibmWaZPbXL9BWjg+2yjaP/Zqure0KOQOecv9yI/Tlq130gLSR8kv8+h60V0wv8noR37Qu2unqBr91aVsf17K1ldVxP31pWx/XUrWV1XE/cWlbXdJHrZvIY5bqZPHJdN5PHha6byWPI1rJ6qge6bh2M3tCtZfVAnrQ1Ug9kb2PvKvajjb2L2LsZe+fIPUNaX949WguqqPCDofXXLeBR+Cx936OXGKUjI/PCW2eKS9iv5XuG0nqJUy/YwPbXUUeaUfuDJ+UX5OSb8+yrfIAbpzT+06rptz/ZxE/16IOYwMFOubnIieazgL1Oz0mYuoFqJsxYc15Gqw8dv9Gk3QwdV0c4J1Sac0VaiN8QkU0K91Ibq4rR73+flIszJchjEXmE7D0Cvax+9hy7sbgvj3A/Afe6cp2NpbU7JXT3kJ0o4apy1tCPsldyKXFPEbebA49ZJ4lsN0i8HLNHaks=
*/