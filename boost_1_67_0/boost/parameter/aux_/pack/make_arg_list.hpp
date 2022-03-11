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
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
      , typename _argument
#endif
      , typename Error
      , typename EmitsErrors
    >
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
    class make_arg_list00
#else
    class make_arg_list0
#endif
    {
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
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

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
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