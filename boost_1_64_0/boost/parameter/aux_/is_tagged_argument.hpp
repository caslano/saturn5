// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_IS_TAGGED_ARGUMENT_HPP
#define BOOST_PARAMETER_IS_TAGGED_ARGUMENT_HPP

namespace boost { namespace parameter { namespace aux {

    struct tagged_argument_base
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING) || \
    (0 < BOOST_PARAMETER_EXPONENTIAL_OVERLOAD_THRESHOLD_ARITY)
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace parameter { namespace aux {

    // This metafunction identifies tagged_argument specializations
    // and their derived classes.
    template <typename T>
    struct is_tagged_argument
      : ::boost::mpl::if_<
            // Cannot use is_convertible<> to check if T is derived from
            // tagged_argument_base. -- Cromwell D. Enage
            ::boost::is_base_of<
                ::boost::parameter::aux::tagged_argument_base
              , typename ::boost::remove_const<
                    typename ::boost::remove_reference<T>::type
                >::type
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#else   // no perfect forwarding support and no exponential overloads
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_tagged_argument_aux
      : ::boost::is_convertible<
            T*
          , ::boost::parameter::aux::tagged_argument_base const*
        >
    {
    };

    // This metafunction identifies tagged_argument specializations
    // and their derived classes.
    template <typename T>
    struct is_tagged_argument
      : ::boost::mpl::if_<
            ::boost::is_lvalue_reference<T>
          , ::boost::mpl::false_
          , ::boost::parameter::aux::is_tagged_argument_aux<T>
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // perfect forwarding support, or exponential overloads

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using is_tagged_argument_mp11 = ::std::is_base_of<
        ::boost::parameter::aux::tagged_argument_base
      , typename ::std::remove_const<
            typename ::std::remove_reference<T>::type
        >::type
    >;
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* is_tagged_argument.hpp
wrqwHWwE28NrYQc53o5wLOwEk2AXiT8c5Ur8jSV+429kXJR3bv0ClQmrhFuNCiRctoQz/rbIAKnn66E3HAjDYARsA0fBdnAIjIBD4RA4DI6Aw+FkOBImiv8kGAnniHuWuEu7k3WH1LVJuwuX/HSD9WB36AN7SPj1Wt4k/BwJ7wvzJPwYCT9Wjmcc9IfRMBDeAJvD8bA9nAC7wRj4FzgRDofT5fgmSX3EwolwMpwGp8jxToWzxb8jf2XV5C9e8pcg+Zsp+UuU/CVJ/pIlfymSv1mSv1TJn1XyN1vyN0fyly75myv5y5D8WSV/QW6OdWja9caeP62+faBF3tGm8UlYR97V1kbe1dYOvg07wGfgQFgMhyl3e36eg1o+SuBk+AKMhztguvjLgC/C+fAluETcl8Jd8Da4G94B98D7ZP/98GX4kGxvhKXwUfgq3A1fg0fhXvi++CuHb/6LvTOBrqo4A/BbspIHWQghhAAhJCGsBgiLbGUJCIgQMbIJJCELCQQIJCibEBYFKyIICqgoKlpUtKhYN1QUqlhREdEioEXAihUVERAVbb8773/zbl7uC8Hanp5Tw/n53syd9Z/1zp07F34Ed8Fz8A1o5H03DIe4U/p51vN+FrxWyi8abpby24M7B3wP1oX7YAz8CtaH78MG8APYFP5V9PchbAsPwfbwAOwIP4KXwr/BIfAwHAaPwGvgUZgNj8F8iacAHocT4RdwuthLPyTvNtGGLPqhb6R8T8F68LSk74yU61nYBn4v6T0H08Qs/Ym884NOLPoTHsUSO2bYAF4PE+A82BZWwI5wAewNF8JBcDEcAW+ABfBGuBgugavhUngfXAYfhbfAUzATUe+8wFxJD/VWP0t4EXcGX4Jd4cuwm5hHiXm0mHPELOHyzof/cJ+VcJ+TcJ+H3cQ8SsyjxZwjZglX3nugr7UIFzdKf6dhJDwDE+BZmAq/g53hOdgTfq+/rSPvDsBkCdd8JuNuKZe3YBh8G9aF78CGcC9U+/uhJ7zD1YT3voT3gYT3Vwlvv4R3UMI7IOHlePang24SXijMkvB2kA+Df4YB8DXYAL4BG8O/wGT4JkwR+w5i31XsPfFkVhPP2xLPHonnXYlnn8TzvsTzAUwR+w5i31XsT8ENiNorDTdKPGofksTzN/LthEdhPfil6OUsbASPwTbwU9gOfgb7w8+lHfwDXgO/guPh13A6PAlnwW/gTfBbeCs8DdfCM/ABicczHm0QfcyxGI8OSn07DNW7pzAWHoFN4VHRwzHYAn4NW8JPYUf4d3gpPA4z4OfwSvgPOBJ+AYvgCTgNfgVnSzjSHmRfLHXOoj1cYZfxXPqNobCTmPuKOUPMl4lZwmX/pv9we0u4fSTcvrCTmPuKOUPMl4nZE+4KSW+6RbjDJNxcGALHw9qwENaBeTAKFsAOYn8KoiPZm0ceJNxacIyEu0La220wHK6SerUOxsDVUq9ul372DsnXGqlXa+EQce+Zh60Q/bSwmIedl3YSjPsAGApTYS3x3wupkPQ2F//mb8TdLXq4B0bAe2ETuAGmwPtM/cKW6f7b6zOSjuekvT4v7fVFaa8vSXt9GaaIfQdlL/29uZ7N8t+fvy7p3SX9+Ruwm5hHiXm0mHPErMeJasafVyXcHRLuTthNzKPEPFrMOWL2hHu4mnpWLOFOk3o2XerZtVLPyqSezZB6hr3MD2QfB+xkMT+4U+YHd0MXvBdGwg0y33kQRsMHYBrcCDuKvf6WoYRfZDE/eFDSvUnGjYdl3HgExsFHYQJ8XNL9R9gFboG/g09Iu3wa9oNbYa6Yx8PH4AQxn4KliHo+DzMkPWEwX9LTUtLTVtKTJnprBxvCdOmnO8I02Fk=
*/