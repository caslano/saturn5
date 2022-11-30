// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_DEDUCE_TAG_HPP
#define BOOST_PARAMETER_AUX_PACK_DEDUCE_TAG_HPP

namespace boost { namespace parameter { namespace aux {

    template <
        typename Argument
      , typename ArgumentPack
      , typename DeducedArgs
      , typename UsedArgs
      , typename TagFn
      , typename EmitsErrors
    >
    struct deduce_tag;
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/lambda_tag.hpp>
#include <boost/parameter/config.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/lambda.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)

namespace boost { namespace parameter { namespace aux {

    template <typename Predicate, typename Argument, typename ArgumentPack>
    struct deduce_tag_condition_mpl
      : ::boost::mpl::apply_wrap2<
            typename ::boost::mpl::lambda<
                Predicate
              , ::boost::parameter::aux::lambda_tag
            >::type
          , Argument
          , ArgumentPack
        >
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/has_nested_template_fn.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Predicate, typename Argument, typename ArgumentPack>
    struct deduce_tag_condition_mp11
    {
        using type = ::boost::mp11::mp_apply_q<
            Predicate
          , ::boost::mp11::mp_list<Argument,ArgumentPack>
        >;
    };

    template <typename Predicate, typename Argument, typename ArgumentPack>
    using deduce_tag_condition = ::boost::mp11::mp_if<
        ::boost::parameter::aux::has_nested_template_fn<Predicate>
      , ::boost::parameter::aux
        ::deduce_tag_condition_mp11<Predicate,Argument,ArgumentPack>
      , ::boost::parameter::aux
        ::deduce_tag_condition_mpl<Predicate,Argument,ArgumentPack>
    >;
}}} // namespace boost::parameter::aux

#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/assert.hpp>
#endif  // BOOST_PARAMETER_CAN_USE_MP11

#include <boost/parameter/aux_/set.hpp>
#include <boost/parameter/aux_/pack/tag_type.hpp>
#include <boost/parameter/aux_/pack/tag_deduced.hpp>

namespace boost { namespace parameter { namespace aux {

    // Helper for deduce_tag<...>, below.
    template <
        typename Argument
      , typename ArgumentPack
      , typename DeducedArgs
      , typename UsedArgs
      , typename TagFn
      , typename EmitsErrors
    >
    class deduce_tag0
    {
        typedef typename DeducedArgs::spec _spec;

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        typedef typename ::boost::parameter::aux::deduce_tag_condition<
            typename _spec::predicate
#else
        typedef typename ::boost::mpl::apply_wrap2<
            typename ::boost::mpl::lambda<
                typename _spec::predicate
              , ::boost::parameter::aux::lambda_tag
            >::type
#endif
          , Argument
          , ArgumentPack
        >::type _condition;

#if !defined(BOOST_PARAMETER_CAN_USE_MP11)
        // Deduced parameter matches several arguments.
        BOOST_MPL_ASSERT((
            typename ::boost::mpl::eval_if<
                typename ::boost::parameter::aux::has_key_<
                    UsedArgs
                  , typename ::boost::parameter::aux::tag_type<_spec>::type
                >::type
              , ::boost::mpl::eval_if<
                    _condition
                  , ::boost::mpl::if_<
                        EmitsErrors
                      , ::boost::mpl::false_
                      , ::boost::mpl::true_
                    >
                  , ::boost::mpl::true_
                >
              , ::boost::mpl::true_
            >::type
        ));
#endif  // BOOST_PARAMETER_CAN_USE_MP11

     public:
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = typename ::boost::mp11::mp_if<
#else
        typedef typename ::boost::mpl::eval_if<
#endif
            _condition
          , ::boost::parameter::aux
            ::tag_deduced<UsedArgs,_spec,Argument,TagFn>
          , ::boost::parameter::aux::deduce_tag<
                Argument
              , ArgumentPack
              , typename DeducedArgs::tail
              , UsedArgs
              , TagFn
              , EmitsErrors
            >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        >::type;
#else
        >::type type;
#endif
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/void.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#else
#include <boost/mpl/pair.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // Tries to deduced a keyword tag for a given Argument.
    // Returns an mpl::pair<> consisting of the tagged_argument<>,
    // and an mpl::set<> where the new tag has been inserted.
    //
    //  Argument:     The argument type to be tagged.
    //
    //  ArgumentPack: The ArgumentPack built so far.
    //
    //  DeducedArgs:  A specialization of deduced_item<> (see below).
    //                A list containing only the deduced ParameterSpecs.
    //
    //  UsedArgs:     An mpl::set<> containing the keyword tags used so far.
    //
    //  TagFn:        A metafunction class used to tag positional or deduced
    //                arguments with a keyword tag.
    template <
        typename Argument
      , typename ArgumentPack
      , typename DeducedArgs
      , typename UsedArgs
      , typename TagFn
      , typename EmitsErrors
    >
    struct deduce_tag
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_if<
            ::std::is_same<DeducedArgs,::boost::parameter::void_>
          , ::boost::mp11::mp_identity<
                ::boost::mp11::mp_list< ::boost::parameter::void_,UsedArgs>
            >
#else
      : ::boost::mpl::eval_if<
            ::boost::is_same<DeducedArgs,::boost::parameter::void_>
          , ::boost::mpl::pair< ::boost::parameter::void_,UsedArgs>
#endif
          , ::boost::parameter::aux::deduce_tag0<
                Argument
              , ArgumentPack
              , DeducedArgs
              , UsedArgs
              , TagFn
              , EmitsErrors
            >
        >
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* deduce_tag.hpp
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
*/