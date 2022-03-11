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