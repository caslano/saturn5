// Copyright David Abrahams, Daniel Wallin 2003.
// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_MAKE_ARG_LIST_HPP
#define BOOST_PARAMETER_AUX_PACK_MAKE_ARG_LIST_HPP

namespace boost { namespace parameter { namespace aux {

    template <
        typename List
      , typename DeducedArgs
      , typename TagFn
      , typename IsPositional
      , typename UsedArgs
      , typename ArgumentPack
      , typename Error
      , typename EmitsErrors
    >
    struct make_arg_list_aux;
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/arg_list.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/pack/unmatched_argument.hpp>
#include <boost/parameter/aux_/pack/tag_type.hpp>
#include <boost/parameter/aux_/pack/is_named_argument.hpp>
#include <boost/parameter/aux_/pack/insert_tagged.hpp>
#include <boost/parameter/aux_/pack/deduce_tag.hpp>
#include <boost/parameter/deduced.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    template <typename ArgumentPack, typename TaggedArg, typename EmitsErrors>
    struct append_to_make_arg_list
    {
        using type = ::boost::mp11::mp_push_front<
            ArgumentPack
          , ::boost::parameter::aux::flat_like_arg_tuple<
                typename TaggedArg::key_type
              , TaggedArg
              , EmitsErrors
            >
        >;
    };
#endif

    // Borland needs the insane extra-indirection workaround below so that
    // it doesn't magically drop the const qualifier from the argument type.
    template <
        typename List
      , typename DeducedArgs
      , typename TagFn
      , typename IsPositional
      , typename UsedArgs
      , typename ArgumentPack
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
      , typename _argument
#endif
      , typename Error
      , typename EmitsErrors
    >
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
    class make_arg_list00
#else
    class make_arg_list0
#endif
    {
#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
        typedef typename List::arg _argument;
#endif
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using _arg_type = typename ::std::remove_const<
            typename ::std::remove_reference<_argument>::type
        >::type;
        using _is_tagged = ::boost::parameter::aux
        ::is_named_argument<_argument>;
#else
        typedef typename ::boost::remove_const<
            typename ::boost::remove_reference<_argument>::type
        >::type _arg_type;
        typedef ::boost::parameter::aux
        ::is_named_argument<_argument> _is_tagged;
#endif
        typedef typename List::spec _parameter_spec;
        typedef typename ::boost::parameter::aux
        ::tag_type<_parameter_spec>::type _tag;

        // If this argument is either explicitly tagged or a deduced
        // parameter, then turn off positional matching.
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using _is_positional = ::boost::mp11::mp_if<
            IsPositional
          , ::boost::mp11::mp_if<
                ::boost::parameter::aux::is_deduced<_parameter_spec>
              , ::boost::mp11::mp_false
              , ::boost::mp11::mp_if<
                    _is_tagged
                  , ::boost::mp11::mp_false
                  , ::boost::mp11::mp_true
                >
            >
          , ::boost::mp11::mp_false
        >;
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
        typedef typename ::boost::mpl::eval_if<
            IsPositional
          , ::boost::mpl::eval_if<
                ::boost::parameter::aux::is_deduced<_parameter_spec>
              , ::boost::mpl::false_
              , ::boost::mpl::if_<
                    _is_tagged
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
            >
          , ::boost::mpl::false_
        >::type _is_positional;
#endif  // BOOST_PARAMETER_CAN_USE_MP11

        // If this parameter is explicitly tagged, then add it to the
        // used-parmeters set.  We only really need to add parameters
        // that are deduced, but we would need a way to check if
        // a given tag corresponds to a deduced parameter spec.
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using _used_args = typename ::boost::mp11::mp_if<
            _is_tagged
          , ::boost::parameter::aux::insert_tagged<UsedArgs,_arg_type>
          , ::boost::mp11::mp_identity<UsedArgs>
        >::type;
#else
        typedef typename ::boost::mpl::eval_if<
            _is_tagged
          , ::boost::parameter::aux::insert_tagged<UsedArgs,_arg_type>
          , ::boost::mpl::identity<UsedArgs>
        >::type _used_args;
#endif

        // If this parameter is neither explicitly tagged nor positionally
        // matched, then deduce the tag from the deduced parameter specs.
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using _deduced_data = typename ::boost::mp11::mp_if<
            ::boost::mp11::mp_if<
                _is_tagged
              , ::boost::mp11::mp_true
              , _is_positional
            >
          , ::boost::mp11::mp_identity<
                ::boost::mp11::mp_list< ::boost::parameter::void_,_used_args>
            >
#else
        typedef typename ::boost::mpl::eval_if<
            typename ::boost::mpl::if_<
                _is_tagged
              , ::boost::mpl::true_
              , _is_positional
            >::type
          , ::boost::mpl::pair< ::boost::parameter::void_,_used_args>
#endif
          , ::boost::parameter::aux::deduce_tag<
                _argument
              , ArgumentPack
              , DeducedArgs
              , _used_args
              , TagFn
              , EmitsErrors
            >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        >::type;
#else
        >::type _deduced_data;
#endif

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        // If this parameter is explicitly tagged ...
        using _tagged = ::boost::mp11::mp_if<
            _is_tagged
            // ... just use it
          , _arg_type
            // ... else ...
          , ::boost::mp11::mp_if<
                // if positional matching is turned on ...
                _is_positional
                // ... tag it positionally
              , ::boost::mp11::mp_apply_q<
                    TagFn
                  , ::boost::mp11::mp_list<_tag,_argument>
                >
                // ... else, use the deduced tag
              , ::boost::mp11::mp_at_c<_deduced_data,0>
            >
        >;
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
        // If this parameter is explicitly tagged ...
        typedef typename ::boost::mpl::eval_if<
            _is_tagged
            // ... just use it
          , ::boost::mpl::identity<_arg_type>
            // ... else ...
          , ::boost::mpl::eval_if<
                // if positional matching is turned on ...
                _is_positional
                // ... tag it positionally
              , ::boost::mpl::apply_wrap2<TagFn,_tag,_argument>
                // ... else, use the deduced tag
              , ::boost::mpl::first<_deduced_data>
            >
        >::type _tagged;
#endif  // BOOST_PARAMETER_CAN_USE_MP11

        // Build the arg_list incrementally, prepending new nodes.
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using _error = ::boost::mp11::mp_if<
            ::boost::mp11::mp_if<
                ::std::is_same<Error,::boost::parameter::void_>
              , ::std::is_same<_tagged,::boost::parameter::void_>
              , ::boost::mp11::mp_false
            >
#else
        typedef typename ::boost::mpl::if_<
            typename ::boost::mpl::if_<
                ::boost::is_same<Error,::boost::parameter::void_>
              , ::boost::is_same<_tagged,::boost::parameter::void_>
              , ::boost::mpl::false_
            >::type
#endif
          , ::boost::parameter::aux::unmatched_argument<_argument>
          , ::boost::parameter::void_
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        >;
#else
        >::type _error;
#endif

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using _argument_pack = typename ::boost::mp11::mp_if<
            ::std::is_same<_tagged,::boost::parameter::void_>
          , ::boost::mp11::mp_identity<ArgumentPack>
          , ::boost::parameter::aux
            ::append_to_make_arg_list<ArgumentPack,_tagged,EmitsErrors>
        >::type;
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
        typedef typename ::boost::mpl::if_<
            ::boost::is_same<_tagged,::boost::parameter::void_>
          , ArgumentPack
#if defined(BOOST_NO_SFINAE) || BOOST_WORKAROUND(BOOST_MSVC, < 1800)
          , ::boost::parameter::aux::arg_list<_tagged,ArgumentPack>
#else
          , ::boost::parameter::aux
            ::arg_list<_tagged,ArgumentPack,EmitsErrors>
#endif
        >::type _argument_pack;
#endif  // BOOST_PARAMETER_CAN_USE_MP11

     public:
        typedef typename ::boost::parameter::aux::make_arg_list_aux<
            typename List::tail
          , DeducedArgs
          , TagFn
          , _is_positional
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
          , ::boost::mp11::mp_at_c<_deduced_data,1>
#else
          , typename _deduced_data::second
#endif
          , _argument_pack
          , _error
          , EmitsErrors
        >::type type;
    };

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
    template <
        typename List
      , typename DeducedArgs
      , typename TagFn
      , typename IsPositional
      , typename UsedArgs
      , typename ArgumentPack
      , typename Error
      , typename EmitsErrors
    >
    struct make_arg_list0
    {
        typedef typename ::boost::mpl::eval_if<
            typename List::is_arg_const
          , ::boost::parameter::aux::make_arg_list00<
                List
              , DeducedArgs
              , TagFn
              , IsPositional
              , UsedArgs
              , ArgumentPack
              , typename List::arg const
              , Error
              , EmitsErrors
            >
          , ::boost::parameter::aux::make_arg_list00<
                List
              , DeducedArgs
              , TagFn
              , IsPositional
              , UsedArgs
              , ArgumentPack
              , typename List::arg
              , Error
              , EmitsErrors
            >
        >::type type;
    };
#endif  // Borland workarounds needed.

    // Returns an ArgumentPack where the list of arguments has been tagged
    // with keyword tags.
    //
    //   List:         A specialization of item<> (see below). Contains both
    //                 the ordered ParameterSpecs, and the given arguments.
    //
    //   DeducedArgs:  A specialization of deduced_item<> (see below).
    //                 A list containing only the deduced ParameterSpecs.
    //
    //   TagFn:        A metafunction class used to tag positional or deduced
    //                 arguments with a keyword tag.
    //
    //   IsPositional: An mpl::bool_<> specialization indicating if positional
    //                 matching is to be performed.
    //
    //   DeducedSet:   An mpl::set<> containing the keyword tags used so far.
    //
    //   ArgumentPack: The ArgumentPack built so far. This is initially an
    //                 empty_arg_list and is built incrementally.
    template <
        typename List
      , typename DeducedArgs
      , typename TagFn
      , typename IsPositional
      , typename DeducedSet
      , typename ArgumentPack
      , typename Error
      , typename EmitsErrors
    >
    struct make_arg_list_aux
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_if<
            ::std::is_same<List,::boost::parameter::void_>
          , ::boost::mp11::mp_identity<
                ::boost::mp11::mp_list<ArgumentPack,Error>
            >
#else
      : ::boost::mpl::eval_if<
            ::boost::is_same<List,::boost::parameter::void_>
          , ::boost::mpl::identity< ::boost::mpl::pair<ArgumentPack,Error> >
#endif
          , ::boost::parameter::aux::make_arg_list0<
                List
              , DeducedArgs
              , TagFn
              , IsPositional
              , DeducedSet
              , ArgumentPack
              , Error
              , EmitsErrors
            >
        >
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/set.hpp>

namespace boost { namespace parameter { namespace aux {

    // VC6.5 was choking on the default parameters for make_arg_list_aux,
    // so this just forwards to that adding in the defaults.
    template <
        typename List
      , typename DeducedArgs
      , typename TagFn
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      , typename EmitsErrors = ::boost::mp11::mp_true
#else
      , typename EmitsErrors = ::boost::mpl::true_
#endif
    >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using make_arg_list = ::boost::parameter::aux::make_arg_list_aux<
#else
    struct make_arg_list
      : ::boost::parameter::aux::make_arg_list_aux<
#endif
            List
          , DeducedArgs
          , TagFn
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
          , ::boost::mp11::mp_true
#else
          , ::boost::mpl::true_
#endif
          , ::boost::parameter::aux::set0
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
          , ::boost::parameter::aux::flat_like_arg_list<>
#else
          , ::boost::parameter::aux::empty_arg_list
#endif
          , ::boost::parameter::void_
          , EmitsErrors
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    >;
#else
        >
    {
    };
#endif
}}} // namespace boost::parameter::aux

#endif  // include guard


/* make_arg_list.hpp
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
*/