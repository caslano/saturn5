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
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
*/