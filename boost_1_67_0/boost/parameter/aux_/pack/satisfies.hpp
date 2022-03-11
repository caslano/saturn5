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