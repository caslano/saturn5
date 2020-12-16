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
zDpM6cjKfTGVv8pf5a/yV/mr/FX+/j9+f/H6/5zhh2j9//XO+n9dq7JJ3zczMOFzcD/hv6XPyytlzrixrPkeGzrHPyvvIs9589l+3yk1nu0JN9z32znhzDn8K7FPszGUKCk+MQn9bN58zNreZRKHtR3E6Uz4qZgrnDiB2vIN0zEHOEsh6kz7bLEnGvvwiPNvrWBZ2Wznv43+ssliLueA8tlYTvkQzsjnRa5zfYC5bOdak+VyxX0QbusCB5bbJo/cCgm/BuOV26GUXbhdtdAFU6JnD9NQ21Wpn+xG5pUpN0GtLyVsbf+1G2XlaL7R7hC/en5yNfHqI4u4IHbMDWnIIo4jv+KTgqkSnjaJ+zaMyClYN2b7ijsIGYXbV2F8lIy0faW84CsjbV9l5VTvhZhyIq3Yckp7IbaciGfk1JqEWlPA+a6c4pCT+G3Br0W8vwx345cZHynDQynH8Hq79noQS5qmUBvzKYLp7SfHguKsi/PGjyOI773SV+LE+8lS07Pl2oq4rn3hawvUtA7m/vHeL511L05jbQuN9H4Z5ncNhSW+7aBAwqb5nyW6n3aQK371/c8V9VxzZ+S8GxOuz0NVj+H74VWVQTVNoarW4zw/GYwpHm6Vo78lbrnO2Ikup7dcuxK1XWmMVMwXzhjpV65ixu6cEs/ZvixUG225Y5jESfAfO8vUUbb/2Fm2Ln3XlS0t57Wneq/dlJd6iqq3pBj3X+tqZeXzlTNOxpaP9GWyhi1KRgHsm2LLSNPUNXexZBQdLraMTDjpr4i4mUY3w2nfqVa57umw7DJ9ZJfplZ2xD49YL1baQNd+k28/eCT8qSHuUq4rePSTBz9d1qwbPVR2SzIIE14XzzV1pXIy/v3HH0kvOu4pVRsmJJq1e4niViVyDNVrd+KmO2HCbpSmH3Hds0DH5GbJMjo3n87kkyZpJlZN8+RTU9yS3brwyScpKh85x82TT1ZxwcV5nry6k1d3SXdH4u74RHMvfbdZ9rqZtY+ZEqZZ4AK7toZhZa2ESXDr3Kc8KdHXbdbNm3PWTVn2sBiqheSzNzHOKbted0NxOwJVwo3jjoj73Q6X8blXZZ+G2btyzuuOPeiu6fQpT1pUedx1/LKlxJRlF2VpK/nuTtwX79bBYVoHYbncJmWYQ+1fZvJN88k3IyrfxtK/hPPNKiqcUOysVgxXj0krwyethlFptYmRlvxRlJ2by1uKJmyu41SRVcDU9xkvy14lk29Dn3wzo9uWkZ27589bn2m0rZ4ir9LEXR4Zdha3TiavTJ+8WkTlVV+v0ZtXFktLR5bkm3bSRa7hS1rAWutdTzto4ZN+a592WSTp8xBDzzCxk1sHrX3it/Uvn+yv0nKpyN19NZOkfE2CLQMtrfsDbcz60g4heQROs9NC7Qrbg2/IvlXa1bVmL1efzdq+WW64jfZ5usTbnNg3vnFA7vPwWszQes+IvaN3Sd41zb3ylGPXM1Qt6ukisa9ImBV81I51LvwOyb+22t37P9177ZJ16NLr63rQenpP57HKdHZ8b/uoxFTyxQ/Xja85fiWsYc2TsiRSlt4SflviF/GhevmlYSht3SItY80Awjn57lM/3dw1PpvFS81I5wvk84Skk01uLa2BtLIZ1kV8sz3fGqPpZqZo3FA3b+7pR0T259vXWnX1+S8s+zhvPdMO88bSqY4YwUJbr6yfFVkG9d4ipNiPCJ0fS7muFPvNCRcGX/OsBc8xe28vD4UP1rK+kb0MSVzrVeK2MKFTcI8nToGJ0/4Vx//i+B7Wr3Gpmu9okW2/wBTrUVvOyiXvSySdOxIeCCZabjqjTNkby7XPM7LYJGmcZ+da92le4Tr7wUa7mh2WT/vXJV0=
*/