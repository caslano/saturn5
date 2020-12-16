// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_KEYWORD_HPP
#define BOOST_PARAMETER_KEYWORD_HPP

#include <boost/parameter/aux_/tag.hpp>
#include <boost/parameter/aux_/default.hpp>
#include <boost/parameter/keyword_fwd.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/core/enable_if.hpp>
#include <utility>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_const.hpp>
#endif

namespace boost { namespace parameter {

    // Instances of unique specializations of keyword<...> serve to
    // associate arguments with parameter names.  For example:
    //
    //     struct rate_;             // parameter names
    //     struct skew_;
    //
    //     namespace
    //     {
    //         keyword<rate_> rate;  // keywords
    //         keyword<skew_> skew;
    //     }
    //
    //     ...
    //
    //     f(rate = 1, skew = 2.4);
    template <typename Tag>
    struct keyword
    {
        typedef Tag tag;

        inline BOOST_CONSTEXPR keyword()
        {
        }

        template <typename T>
        inline BOOST_CONSTEXPR typename ::boost::lazy_enable_if<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            ::boost::mp11::mp_if<
                ::std::is_scalar<T>
              , ::boost::mp11::mp_true
              , ::boost::mp11::mp_if<
                    ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::in_reference
                    >
                  , ::boost::mp11::mp_true
                  , ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >
            >
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
            typename ::boost::mpl::eval_if<
                ::boost::is_scalar<T>
              , ::boost::mpl::true_
              , ::boost::mpl::eval_if<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::in_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::mpl::if_<
                        ::boost::is_same<
                            typename Tag::qualifier
                          , ::boost::parameter::forward_reference
                        >
                      , ::boost::mpl::true_
                      , ::boost::mpl::false_
                    >
                >
            >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
          , ::boost::parameter::aux::tag<Tag,T const&>
        >::type
            operator=(T const& x) const
        {
            typedef typename ::boost::parameter::aux
            ::tag<Tag,T const&>::type result;
            return result(x);
        }

        template <typename Default>
        inline BOOST_CONSTEXPR typename ::boost::enable_if<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            ::boost::mp11::mp_if<
                ::std::is_scalar<Default>
              , ::boost::mp11::mp_true
              , ::boost::mp11::mp_if<
                    ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::in_reference
                    >
                  , ::boost::mp11::mp_true
                  , ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >
            >
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
            typename ::boost::mpl::eval_if<
                ::boost::is_scalar<Default>
              , ::boost::mpl::true_
              , ::boost::mpl::eval_if<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::in_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::mpl::if_<
                        ::boost::is_same<
                            typename Tag::qualifier
                          , ::boost::parameter::forward_reference
                        >
                      , ::boost::mpl::true_
                      , ::boost::mpl::false_
                    >
                >
            >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
          , ::boost::parameter::aux::default_<Tag,Default const>
        >::type
            operator|(Default const& d) const
        {
            return ::boost::parameter::aux::default_<Tag,Default const>(d);
        }

        template <typename T>
        inline BOOST_CONSTEXPR typename ::boost::lazy_enable_if<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            ::boost::mp11::mp_if<
                ::boost::mp11::mp_if<
                    ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::out_reference
                    >
                  , ::boost::mp11::mp_true
                  , ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >
              , ::boost::mp11::mp_if<
                    ::std::is_const<T>
                  , ::boost::mp11::mp_false
                  , ::boost::mp11::mp_true
                >
              , ::boost::mp11::mp_false
            >
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
            typename ::boost::mpl::eval_if<
                typename ::boost::mpl::if_<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::out_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >::type
              , ::boost::mpl::if_<
                    ::boost::is_const<T>
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
              , ::boost::mpl::false_
            >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
          , ::boost::parameter::aux::tag<Tag,T&>
        >::type
            operator=(T& x) const
        {
            typedef typename ::boost::parameter::aux
            ::tag<Tag,T&>::type result;
            return result(x);
        }

        template <typename Default>
        inline BOOST_CONSTEXPR typename ::boost::enable_if<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            ::boost::mp11::mp_if<
                ::boost::mp11::mp_if<
                    ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::out_reference
                    >
                  , ::boost::mp11::mp_true
                  , ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >
              , ::boost::mp11::mp_if<
                    ::std::is_const<Default>
                  , ::boost::mp11::mp_false
                  , ::boost::mp11::mp_true
                >
              , ::boost::mp11::mp_false
            >
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
            typename ::boost::mpl::eval_if<
                typename ::boost::mpl::if_<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::out_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >::type
              , ::boost::mpl::if_<
                    ::boost::is_const<Default>
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
              , ::boost::mpl::false_
            >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
          , ::boost::parameter::aux::default_<Tag,Default>
        >::type
            operator|(Default& d) const
        {
            return ::boost::parameter::aux::default_<Tag,Default>(d);
        }

        template <typename Default>
        inline BOOST_CONSTEXPR
        ::boost::parameter::aux::lazy_default<Tag,Default const>
            operator||(Default const& d) const
        {
            return ::boost::parameter::aux
            ::lazy_default<Tag,Default const>(d);
        }

        template <typename Default>
        inline BOOST_CONSTEXPR
        ::boost::parameter::aux::lazy_default<Tag,Default>
            operator||(Default& d) const
        {
            return ::boost::parameter::aux::lazy_default<Tag,Default>(d);
        }

        template <typename T>
        inline BOOST_CONSTEXPR typename ::boost::lazy_enable_if<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            ::boost::mp11::mp_if<
                ::std::is_scalar<T>
              , ::boost::mp11::mp_false
              , ::boost::mp11::mp_if<
                    ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::in_reference
                    >
                  , ::boost::mp11::mp_true
                  , ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >
            >
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
            typename ::boost::mpl::eval_if<
                ::boost::is_scalar<T>
              , ::boost::mpl::false_
              , ::boost::mpl::eval_if<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::in_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::mpl::if_<
                        ::boost::is_same<
                            typename Tag::qualifier
                          , ::boost::parameter::forward_reference
                        >
                      , ::boost::mpl::true_
                      , ::boost::mpl::false_
                    >
                >
            >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
          , ::boost::parameter::aux::tag<Tag,T const>
        >::type
            operator=(T const&& x) const
        {
            typedef typename ::boost::parameter::aux
            ::tag<Tag,T const>::type result;
            return result(::std::forward<T const>(x));
        }

        template <typename T>
        inline BOOST_CONSTEXPR typename ::boost::lazy_enable_if<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            ::boost::mp11::mp_if<
                ::std::is_scalar<T>
              , ::boost::mp11::mp_false
              , ::boost::mp11::mp_if<
                    ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::consume_reference
                    >
                  , ::boost::mp11::mp_true
                  , ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >
            >
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
            typename ::boost::mpl::eval_if<
                ::boost::is_scalar<T>
              , ::boost::mpl::false_
              , ::boost::mpl::eval_if<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::consume_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::mpl::if_<
                        ::boost::is_same<
                            typename Tag::qualifier
                          , ::boost::parameter::forward_reference
                        >
                      , ::boost::mpl::true_
                      , ::boost::mpl::false_
                    >
                >
            >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
          , ::boost::parameter::aux::tag<Tag,T>
        >::type
            operator=(T&& x) const
        {
            typedef typename ::boost::parameter::aux::tag<Tag,T>::type result;
            return result(::std::forward<T>(x));
        }

        template <typename Default>
        inline BOOST_CONSTEXPR typename ::boost::enable_if<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            ::boost::mp11::mp_if<
                ::std::is_scalar<Default>
              , ::boost::mp11::mp_false
              , ::boost::mp11::mp_if<
                    ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::in_reference
                    >
                  , ::boost::mp11::mp_true
                  , ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >
            >
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
            typename ::boost::mpl::eval_if<
                ::boost::is_scalar<Default>
              , ::boost::mpl::false_
              , ::boost::mpl::eval_if<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::in_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::mpl::if_<
                        ::boost::is_same<
                            typename Tag::qualifier
                          , ::boost::parameter::forward_reference
                        >
                      , ::boost::mpl::true_
                      , ::boost::mpl::false_
                    >
                >
            >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
          , ::boost::parameter::aux::default_r_<Tag,Default const>
        >::type
            operator|(Default const&& d) const
        {
            return ::boost::parameter::aux::default_r_<Tag,Default const>(
                ::std::forward<Default const>(d)
            );
        }

        template <typename Default>
        inline BOOST_CONSTEXPR typename ::boost::enable_if<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            ::boost::mp11::mp_if<
                ::std::is_scalar<Default>
              , ::boost::mp11::mp_false
              , ::boost::mp11::mp_if<
                    ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::consume_reference
                    >
                  , ::boost::mp11::mp_true
                  , ::std::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >
            >
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
            typename ::boost::mpl::eval_if<
                ::boost::is_scalar<Default>
              , ::boost::mpl::false_
              , ::boost::mpl::eval_if<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::consume_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::mpl::if_<
                        ::boost::is_same<
                            typename Tag::qualifier
                          , ::boost::parameter::forward_reference
                        >
                      , ::boost::mpl::true_
                      , ::boost::mpl::false_
                    >
                >
            >::type
#endif  // BOOST_PARAMETER_CAN_USE_MP11
          , ::boost::parameter::aux::default_r_<Tag,Default>
        >::type
            operator|(Default&& d) const
        {
            return ::boost::parameter::aux
            ::default_r_<Tag,Default>(::std::forward<Default>(d));
        }

     public: // Insurance against ODR violations
        // Users will need to define their keywords in header files.  To
        // prevent ODR violations, it's important that the keyword used in
        // every instantiation of a function template is the same object.
        // We provide a reference to a common instance of each keyword
        // object and prevent construction by users.
        static ::boost::parameter::keyword<Tag> const instance;

        // This interface is deprecated.
        static ::boost::parameter::keyword<Tag>& get()
        {
            return const_cast< ::boost::parameter::keyword<Tag>&>(instance);
        }
    };

    template <typename Tag>
    ::boost::parameter::keyword<Tag> const ::boost::parameter
    ::keyword<Tag>::instance = ::boost::parameter::keyword<Tag>();
}} // namespace boost::parameter

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#if !defined(BOOST_NO_SFINAE)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_const.hpp>
#endif  // BOOST_NO_SFINAE

namespace boost { namespace parameter {

    // Instances of unique specializations of keyword<...> serve to
    // associate arguments with parameter names.  For example:
    //
    //     struct rate_;             // parameter names
    //     struct skew_;
    //
    //     namespace
    //     {
    //         keyword<rate_> rate;  // keywords
    //         keyword<skew_> skew;
    //     }
    //
    //     ...
    //
    //     f(rate = 1, skew = 2.4);
    template <typename Tag>
    struct keyword
    {
        typedef Tag tag;

        inline BOOST_CONSTEXPR keyword()
        {
        }

        template <typename T>
#if defined(BOOST_NO_SFINAE)
        inline typename ::boost::parameter::aux::tag<Tag,T const&>::type
#else
        inline BOOST_CONSTEXPR typename ::boost::lazy_enable_if<
            typename ::boost::mpl::eval_if<
                ::boost::is_scalar<T>
              , ::boost::mpl::true_
              , ::boost::mpl::eval_if<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::in_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::mpl::if_<
                        ::boost::is_same<
                            typename Tag::qualifier
                          , ::boost::parameter::forward_reference
                        >
                      , ::boost::mpl::true_
                      , ::boost::mpl::false_
                    >
                >
            >::type
          , ::boost::parameter::aux::tag<Tag,T const&>
        >::type
#endif  // BOOST_NO_SFINAE
            operator=(T const& x) const
        {
            typedef typename ::boost::parameter::aux
            ::tag<Tag,T const&>::type result;
            return result(x);
        }

        template <typename Default>
#if defined(BOOST_NO_SFINAE)
        inline ::boost::parameter::aux::default_<Tag,Default const>
#else
        inline BOOST_CONSTEXPR typename ::boost::enable_if<
            typename ::boost::mpl::eval_if<
                ::boost::is_scalar<Default>
              , ::boost::mpl::true_
              , ::boost::mpl::eval_if<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::in_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::mpl::if_<
                        ::boost::is_same<
                            typename Tag::qualifier
                          , ::boost::parameter::forward_reference
                        >
                      , ::boost::mpl::true_
                      , ::boost::mpl::false_
                    >
                >
            >::type
          , ::boost::parameter::aux::default_<Tag,Default const>
        >::type
#endif  // BOOST_NO_SFINAE
            operator|(Default const& d) const
        {
            return ::boost::parameter::aux::default_<Tag,Default const>(d);
        }

        template <typename T>
#if defined(BOOST_NO_SFINAE)
        inline typename ::boost::parameter::aux::tag<Tag,T&>::type
#else
        inline BOOST_CONSTEXPR typename ::boost::lazy_enable_if<
            typename ::boost::mpl::eval_if<
                typename ::boost::mpl::if_<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::out_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >::type
              , ::boost::mpl::if_<
                    ::boost::is_const<T>
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
              , ::boost::mpl::false_
            >::type
          , ::boost::parameter::aux::tag<Tag,T&>
        >::type
#endif  // BOOST_NO_SFINAE
            operator=(T& x) const
        {
            typedef typename ::boost::parameter::aux
            ::tag<Tag,T&>::type result;
            return result(x);
        }

        template <typename Default>
#if defined(BOOST_NO_SFINAE)
        inline ::boost::parameter::aux::default_<Tag,Default>
#else
        inline BOOST_CONSTEXPR typename ::boost::enable_if<
            typename ::boost::mpl::eval_if<
                typename ::boost::mpl::if_<
                    ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::out_reference
                    >
                  , ::boost::mpl::true_
                  , ::boost::is_same<
                        typename Tag::qualifier
                      , ::boost::parameter::forward_reference
                    >
                >::type
              , ::boost::mpl::if_<
                    ::boost::is_const<Default>
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
              , ::boost::mpl::false_
            >::type
          , ::boost::parameter::aux::default_<Tag,Default>
        >::type
#endif  // BOOST_NO_SFINAE
            operator|(Default& d) const
        {
            return ::boost::parameter::aux::default_<Tag,Default>(d);
        }

        template <typename Default>
        inline BOOST_CONSTEXPR
        ::boost::parameter::aux::lazy_default<Tag,Default const>
            operator||(Default const& d) const
        {
            return ::boost::parameter::aux
            ::lazy_default<Tag,Default const>(d);
        }

        template <typename Default>
        inline BOOST_CONSTEXPR
        ::boost::parameter::aux::lazy_default<Tag,Default>
            operator||(Default& d) const
        {
            return ::boost::parameter::aux::lazy_default<Tag,Default>(d);
        }

     public: // Insurance against ODR violations
        // Users will need to define their keywords in header files.  To
        // prevent ODR violations, it's important that the keyword used in
        // every instantiation of a function template is the same object.
        // We provide a reference to a common instance of each keyword
        // object and prevent construction by users.
        static ::boost::parameter::keyword<Tag> const instance;

        // This interface is deprecated.
        static ::boost::parameter::keyword<Tag>& get()
        {
            return const_cast< ::boost::parameter::keyword<Tag>&>(instance);
        }
    };

    template <typename Tag>
    ::boost::parameter::keyword<Tag> const ::boost::parameter
    ::keyword<Tag>::instance = ::boost::parameter::keyword<Tag>();
}} // namespace boost::parameter

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

#include <boost/parameter/aux_/name.hpp>
#include <boost/preprocessor/stringize.hpp>

// Reduces boilerplate required to declare and initialize keywords without
// violating ODR.  Declares a keyword tag type with the given name in
// namespace tag_namespace, and declares and initializes a reference in an
// anonymous namespace to a singleton instance of that type.
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_KEYWORD(tag_namespace, name)                         \
    namespace tag_namespace                                                  \
    {                                                                        \
        struct name                                                          \
        {                                                                    \
            static BOOST_CONSTEXPR char const* keyword_name()                \
            {                                                                \
                return BOOST_PP_STRINGIZE(name);                             \
            }                                                                \
            using _ = BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(name);            \
            using _1 = _;                                                    \
            BOOST_PARAMETER_TAG_MP11_PLACEHOLDER_BINDING(binding_fn, name);  \
            BOOST_PARAMETER_TAG_MP11_PLACEHOLDER_VALUE(fn, name);            \
            using qualifier = ::boost::parameter::forward_reference;         \
        };                                                                   \
    }                                                                        \
    namespace                                                                \
    {                                                                        \
        ::boost::parameter::keyword<tag_namespace::name> const& name         \
            = ::boost::parameter::keyword<tag_namespace::name>::instance;    \
    }
/**/
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_KEYWORD(tag_namespace, name)                         \
    namespace tag_namespace                                                  \
    {                                                                        \
        struct name                                                          \
        {                                                                    \
            static BOOST_CONSTEXPR char const* keyword_name()                \
            {                                                                \
                return BOOST_PP_STRINGIZE(name);                             \
            }                                                                \
            typedef BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(name) _;            \
            typedef BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(name) _1;           \
            typedef ::boost::parameter::forward_reference qualifier;         \
        };                                                                   \
    }                                                                        \
    namespace                                                                \
    {                                                                        \
        ::boost::parameter::keyword<tag_namespace::name> const& name         \
            = ::boost::parameter::keyword<tag_namespace::name>::instance;    \
    }
/**/
#endif  // BOOST_PARAMETER_CAN_USE_MP11

#endif  // include guard


/* keyword.hpp
dur/fDbxPN96f6Z421Z/631FPbeMSnN3JM2eftK87oHo78f3S5pRdeALVYk6/3D14rTk1gFvur+1pPuap6yTVJskh7+rSrqlpPtWiHSDq+vSWrRJS26T1nJwWnJb9z2b79S4aJ7dT5xFTlnSV29xy7GYZ1fWeAeoqTLKcbjKNzUqjR2ksdvJt9Xq27x3vy7gGdnW/buUtMtwf5T32yXyjrsUV45bhvsLYb/LCLvlPFfg8nFzcJW4cxy/TBWmvymlNHC2g+pH9vu+Y96PTZ16RbHsLZQEz8ANICR/i6sX9Hmkvuzl+VuaeO7oltjvRlUdcE2wm/o5P3Sca4dcHE6ot3GPR3/y3GbUf0VlBTtTMahyUwhfjmr4hlpUbvnekenIxZa434tI0//3IpNWvhcxHlrnFCatzH/LixaUlFvmFLZ0y0nXOqfQtG0j5wFY5hO2NCt1mt0M2m4GbbaWDz5dytoklxe5RpxcFadx9hSRA+s3r0zzm5fwVOYnMvdWvJP5idAJj0ifuutzBRRNN5dG6pyDX64re2bdZB7/nqoL9ewaPT6vLQtXpE8SPAF7g873h3oth3KGrcUW+bmi6ZEUtt1IHFLqRRaG/OEf/1t29la1RzfJ0XlZi5FjnDovNr3utpjzYoVmr0uTWvdDL02O0HQuhV90jOS5qYtSJztnxaZru2g19Xvdk+bxpXJ2buqqb7xpZgtNcal7bu6qO9OSOwRizsUVuiugW5ap6G6IR3M/NF/gl9Zh1bB4NDug+Ro/0unlpZEzfvQZtzVyxm0tiOPbgvu9AcezGhPk3B9QuXPlb9edx7MTvqJD087DFfnXz6Zd9Kc/1XbRqO9LL8rFMcdLgsfh2iOjW3/myp86j9Q88KKk2PJ9yaL3JA2ZF4b0e4yefz2swkdgQ2xl1YVm/FqlN+lq9m+I0PrTFZbvU1pfUEZ5JzH0RQp+Kl/POUhLY89BCjmDyENRfFMvoX7Gz8BD/sqf6FvhAblIN7yPgzribickZClTQVEtJ+85S2GjyqbfdbJVnPmBkwidY/1mIOlK+/w4fN69861Uj4njVHg7a9uacTeG41ZXLi3Tcaer8B7WtjbjfqLevxSX9bteNxU+NzCF/2eKraeQ9roN/pyvdEwoZo2j4nsj38scGurNs6q3lpmNyk/VJ/pbToV8w5X2uRyXjcysjWkfMVx4v91L29yk6FcGzre3C+l55hvynu7y9pcqPM3WLjpupsQ17Bo6/quKJmRpG0ve8t7vxn1b4lrmKMS16gsd91MV3sk6ZzHj0mfFDhKZ33/7H+auBK6qYo2fyyYC4gUREVzINJey0NS0rMgll1x4Li8rCxBQVJAri2laYVmZmVJZamVZalnqy0rNfSlNK0syNStf0WZmVmRqVlbvf77znWHuOXPvPUDv/Z4/h/89Z75v5ptvZr5ZziycZlU/pkxdnsT49Unyv00r5rKk5WP+YcLfX5agL/ucSohyTgXvLXMqCvuVYNov1oW8vmyzR9y5Tf9ast1PXeNVFqXNcfg5pqB4bCbsv+VbWLR55xPxnqcqkwhXmbeqMgha53Y/dU317Cbb/RrZ/BET7Ta/EXTmETqTzj93ON/qcSi/ao5Uti1tCg3i6/i7dn+4BMhWapUtB8vfirKKi2y2he/TIvre2jXqc0wQnvd47TZk/FS4aY6+c4fG7F7je7wqp2dvof37bGOkp0KRHqySctTGgtdr/vP2Gowx5TFkXpF97VASZNTWChmVZ7k7+ZasrXVWLkS5VvQHwovtazCaQL5ki3y0OHisvuU1F18eAsuWXAvZxD6sSVVzumFwK+B+h8FK8ZKtQ3pRiQejcNgccYS7ej1bJ+J7Dnc=
*/