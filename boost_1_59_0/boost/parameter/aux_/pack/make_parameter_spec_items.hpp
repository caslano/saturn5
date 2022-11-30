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
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
*/