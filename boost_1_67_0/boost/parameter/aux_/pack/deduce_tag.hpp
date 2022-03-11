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