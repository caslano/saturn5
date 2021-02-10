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
syBmEY/aEEUqmW+/6JBnnid6xjeF30B/6lRyQscnA0I+ZTLXg/1TsbtI+VRgRX6O6g34UUmvB0+T85DSd0gKJcfzZNUIT5C2otftGP8TK8SfXxmOrQj7VoLjRW118dybZcr2w3UbDDiwe1Fve/328OP+taoE2nnfHo664yfBjj7c3Q27o1HwbhC033fb10/Cwh2CpwEWuxKftxsc60QG+MrsppWQD6ZGfHBhxJMAvfdezrvuOMToGz6xiEU+OJfbkNPG8p9hRHz+j/xV7wYtmJR0xqy72l/IT+7o8/JutyiwKxiNDeIxDS1hAC7Rs0gg2KdKWfJ5EwLaY4XrOaJvtJdl4e3fTfaRsNyNiwRSlYXY0f1DJ6z9swS/gyvO6lM57VYcWgntziUSn7fl4urZkkFj/jWyYQ/wPOn0VuPzpNN7C8+XzjQrz5Tu+bq7/zrd3T9Nd8W+DO51VzdlftDfsBkXUT4NSyZM8GSALlhJeNtDzBiErUpLILX95PIEqqHhpUQP++IHzDLwzQ8CKABUEPgPbC29jaYYFqUK1wfd+wO17S7PCvmw1frUv8v4AxeP/Pt6WS1GnZ5VkOXrDuTsuTbduTeiISEt4LbV5aXF65ji0ZWseCqHJWN+ylrZ7Lp8tYGVV4d78Mz+18Xl
*/