// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_SATISFIES_HPP
#define BOOST_PARAMETER_AUX_PACK_SATISFIES_HPP

#include <boost/parameter/config.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
#include <boost/parameter/aux_/arg_list.hpp>
#include <boost/parameter/aux_/augment_predicate.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/type_traits/is_same.hpp>
#else   // !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif
#include <boost/parameter/aux_/yesno.hpp>
#include <boost/parameter/aux_/preprocessor/nullptr.hpp>
#endif  // MSVC-7.1 workarounds needed

namespace boost { namespace parameter { namespace aux {

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    template <typename ArgList, typename ParameterRequirements, typename Bound>
    struct satisfies_impl
      : ::boost::parameter::aux::augment_predicate<
            typename ParameterRequirements::predicate
          , typename ArgList::reference
          , typename ArgList::key_type
          , Bound
          , ArgList
        >
    {
    };
#endif

    // Returns mpl::true_ iff the given ParameterRequirements are satisfied by
    // ArgList.
    template <typename ArgList, typename ParameterRequirements>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using satisfies = ::boost::mp11::mp_bool<
        sizeof(
            ::boost::parameter::aux::to_yesno(
                ArgList::satisfies(
                    static_cast<ParameterRequirements*>(
                        BOOST_PARAMETER_AUX_PP_NULLPTR
                    )
                  , static_cast<ArgList*>(BOOST_PARAMETER_AUX_PP_NULLPTR)
                )
            )
        ) == sizeof(::boost::parameter::aux::yes_tag)
    >;
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
    class satisfies
    {
#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        // VC7.1 can't handle the sizeof() implementation below,
        // so we use this instead.
        typedef typename ::boost::mpl::apply_wrap3<
            typename ArgList::binding
          , typename ParameterRequirements::keyword
          , ::boost::parameter::void_
          , ::boost::mpl::false_
        >::type _bound;

     public:
        typedef typename ::boost::mpl::eval_if<
            ::boost::is_same<_bound,::boost::parameter::void_>
          , typename ParameterRequirements::has_default
          , ::boost::mpl::eval_if<
                ::boost::is_same<
                    ArgList
                  , ::boost::parameter::aux::empty_arg_list
                >
              , ::boost::mpl::false_
              , ::boost::parameter::aux::satisfies_impl<
                    ArgList
                  , ParameterRequirements
                  , _bound
                >
            >
        >::type type;
#else   // !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        BOOST_STATIC_CONSTANT(
            bool, _value = (
                sizeof(
                    ::boost::parameter::aux::to_yesno(
                        ArgList::satisfies(
                            static_cast<ParameterRequirements*>(
                                BOOST_PARAMETER_AUX_PP_NULLPTR
                            )
                          , static_cast<ArgList*>(BOOST_PARAMETER_AUX_PP_NULLPTR)
                        )
                    )
                ) == sizeof(::boost::parameter::aux::yes_tag)
            )
        );

     public:
        typedef ::boost::mpl::bool_<
            ::boost::parameter::aux
            ::satisfies<ArgList,ParameterRequirements>::_value
        > type;
#endif  // MSVC-7.1 workarounds needed
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/pack/as_parameter_requirements.hpp>

namespace boost { namespace parameter { namespace aux {

    // Returns mpl::true_ if the requirements of the given ParameterSpec
    // are satisfied by ArgList.
    template <typename ArgList, typename ParameterSpec>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    using satisfies_requirements_of = ::boost::parameter::aux::satisfies<
        ArgList
      , typename ::boost::parameter::aux
        ::as_parameter_requirements<ParameterSpec>::type
    >;
#else
    struct satisfies_requirements_of
      : ::boost::parameter::aux::satisfies<
            ArgList
          , typename ::boost::parameter::aux
            ::as_parameter_requirements<ParameterSpec>::type
        >::type
    {
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}}} // namespace boost::parameter::aux

#endif  // include guard


/* satisfies.hpp
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
*/