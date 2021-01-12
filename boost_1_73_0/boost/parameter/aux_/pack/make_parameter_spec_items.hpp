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
4fTtXYfT93cdbvN7j8Ntfn/vcJvfex1u8/sHh9v83udwm9/7HW7z+0fJ6TnygMNtfh90uM3vQw63+X3Y4Ta/+x1u8/uIw21+/+Rwm99HHW7z+2eH2/w+Jjn1V39xuM3vXx1u8/s3h9v8Pu5wm9+/O9zm9x8Ot/n9p8P5eVuc2/zWONzmt1Zyem7WOdzmt97hNr+LHG7z2+Bwm99Gh9v8Njnc5nexw21+lzjc5nepw21+l0lO
*/