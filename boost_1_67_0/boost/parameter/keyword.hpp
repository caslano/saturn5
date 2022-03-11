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