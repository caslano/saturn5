// Copyright David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_TAG_DWA2005610_HPP
#define BOOST_PARAMETER_AUX_TAG_DWA2005610_HPP

#include <boost/parameter/aux_/unwrap_cv_reference.hpp>
#include <boost/parameter/aux_/tagged_argument.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11) && \
    !BOOST_WORKAROUND(BOOST_MSVC, >= 1910)
// MSVC-14.1+ assigns rvalue references to tagged_argument instances
// instead of tagged_argument_rref instances with this code.
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>

namespace boost { namespace parameter { namespace aux { 

    template <typename Keyword, typename Arg>
    struct tag_if_lvalue_reference
    {
        using type = ::boost::parameter::aux::tagged_argument_list_of_1<
            ::boost::parameter::aux::tagged_argument<
                Keyword
              , typename ::boost::parameter::aux
                ::unwrap_cv_reference<Arg>::type
            >
        >;
    };

    template <typename Keyword, typename Arg>
    struct tag_if_scalar
    {
        using type = ::boost::parameter::aux::tagged_argument_list_of_1<
            ::boost::parameter::aux
            ::tagged_argument<Keyword,typename ::std::add_const<Arg>::type>
        >;
    };

    template <typename Keyword, typename Arg>
    using tag_if_otherwise = ::boost::mp11::mp_if<
        ::std::is_scalar<typename ::std::remove_const<Arg>::type>
      , ::boost::parameter::aux::tag_if_scalar<Keyword,Arg>
      , ::boost::mp11::mp_identity<
            ::boost::parameter::aux::tagged_argument_list_of_1<
                ::boost::parameter::aux::tagged_argument_rref<Keyword,Arg>
            >
        >
    >;

    template <typename Keyword, typename Arg>
    using tag = ::boost::mp11::mp_if<
        ::boost::mp11::mp_if<
            ::std::is_lvalue_reference<Arg>
          , ::boost::mp11::mp_true
          , ::boost::parameter::aux::is_cv_reference_wrapper<Arg>
        >
      , ::boost::parameter::aux::tag_if_lvalue_reference<Keyword,Arg>
      , ::boost::parameter::aux::tag_if_otherwise<Keyword,Arg>
    >;
}}} // namespace boost::parameter::aux_

#elif defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <typename Keyword, typename ActualArg>
    struct tag
    {
        typedef typename ::boost::parameter::aux
        ::unwrap_cv_reference<ActualArg>::type Arg;
        typedef typename ::boost::add_const<Arg>::type ConstArg;
        typedef typename ::boost::remove_const<Arg>::type MutArg;
        typedef typename ::boost::mpl::eval_if<
            typename ::boost::mpl::if_<
                ::boost::is_lvalue_reference<ActualArg>
              , ::boost::mpl::true_
              , ::boost::parameter::aux::is_cv_reference_wrapper<ActualArg>
            >::type
          , ::boost::mpl::identity<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                ::boost::parameter::aux::tagged_argument_list_of_1<
#endif
                    ::boost::parameter::aux::tagged_argument<Keyword,Arg>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                >
#endif
            >
          , ::boost::mpl::if_<
                ::boost::is_scalar<MutArg>
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
              , ::boost::parameter::aux::tagged_argument_list_of_1<
                    ::boost::parameter::aux::tagged_argument<Keyword,ConstArg>
                >
              , ::boost::parameter::aux::tagged_argument_list_of_1<
                    ::boost::parameter::aux::tagged_argument_rref<Keyword,Arg>
                >
#else
              , ::boost::parameter::aux::tagged_argument<Keyword,ConstArg>
              , ::boost::parameter::aux::tagged_argument_rref<Keyword,Arg>
#endif
            >
        >::type type;
    };
}}} // namespace boost::parameter::aux_

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux { 

    template <
        typename Keyword
      , typename Arg
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
      , typename = typename ::boost::parameter::aux
        ::is_cv_reference_wrapper<Arg>::type
#endif
    >
    struct tag
    {
        typedef ::boost::parameter::aux::tagged_argument<
            Keyword
          , typename ::boost::parameter::aux::unwrap_cv_reference<Arg>::type
        > type;
    };
}}} // namespace boost::parameter::aux_

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <typename Keyword, typename Arg>
    struct tag<Keyword,Arg,::boost::mpl::false_>
    {
        typedef ::boost::parameter::aux::tagged_argument<
            Keyword
          , typename ::boost::remove_reference<Arg>::type
        > type;
    };
}}} // namespace boost::parameter::aux_

#endif  // Borland workarounds needed.
#endif  // MP11 or perfect forwarding support
#endif  // include guard


/* tag.hpp
guDSsKAywimZpuzBErZ43/jpVQ4070WSw9op/7josy1xU7iWBrUnKMmX9tUT973anGI2s0x2JqN+wfQbB+N7MkN3DPYmv9hp7KCZlfn+CP+MWqHENdFIwV38Wfqb9qjF0kCpx10cX3+DWy68OdFioflK+GSMXVYpwO847dp839VrC5Z7iSDbLVVEREcflWSPO0WHUP1qxqX1qpdG0AxD2yiepe9LZmvUJOYoZLiWK0MUab2EYBIJzskXGMGvuyh/UQYEgYFDIjlNlliQwpXBJCawU4IOREcO0XbtlBI4zzp/2MKz0oyLMPM4+facKxUG8bjdCVhFTG+SNMLdJEXD1+L8iG7IdrH+5Oex7CyYGh3RsFaM6fCi8lSsHX5wzEXCIb+VCP7s2wK5ntC1yLXpYZrFZF8JqY8vXksOmw6LDyNZvm6kvfk4/HoXafdNKZA/AYde9nVpzGu6hJg39hQLJXd0dBx3PZ/vh2LoY0pjrGL2YtyHJ2MIYz7vi0XeY0CD0K/s8OvfzLydmfR4qavSR7Ko7/bGVNqa4Qr7t4MYL35zjIC1P+4VP50ZPSjkJIu/tHCJiQemwZM/e4wvPZmlxXxkd9eQPTFrTR/AYUPe3GZhK6flhZP7q0USD+M5sadA5WQvQ6jaCPKU3fwtsUWMejWxyiFwqY3ditvtrDMNRixS4eTzeyFtrLbFlfxX1ZeU5RrodUtBgJi1afYc
*/