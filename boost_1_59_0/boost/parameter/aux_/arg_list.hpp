// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_ARG_LIST_HPP
#define BOOST_PARAMETER_AUX_ARG_LIST_HPP

namespace boost { namespace parameter { namespace aux {

    //
    // Structures used to build the tuple of actual arguments.  The tuple is a
    // nested cons-style list of arg_list specializations terminated by an
    // empty_arg_list.
    //
    // Each specialization of arg_list is derived from its successor in the
    // list type.  This feature is used along with using declarations to build
    // member function overload sets that can match against keywords.
    //

    // MPL sequence support
    struct arg_list_tag;

    template <typename T>
    struct get_reference
    {
        typedef typename T::reference type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    struct value_type_is_void
    {
    };

    struct value_type_is_not_void
    {
    };
}}} // namespace boost::parameter::aux

#endif

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/aux_/yesno.hpp>
#include <boost/parameter/aux_/result_of0.hpp>
#include <boost/parameter/aux_/default.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <utility>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>
#endif

namespace boost { namespace parameter { namespace aux {

    // Terminates arg_list<> and represents an empty list.  Since this is just
    // the terminating case, you might want to look at arg_list first to get a
    // feel for what's really happening here.
    struct empty_arg_list
    {
        struct tagged_arg
        {
            typedef ::boost::parameter::void_ value_type;
        };

        // Variadic constructor also serves as default constructor.
        template <typename ...Args>
        inline BOOST_CONSTEXPR empty_arg_list(Args&&...)
        {
        }

        // A metafunction class that, given a keyword and a default type,
        // returns the appropriate result type for a keyword lookup given
        // that default.
        struct binding
        {
            template <typename KW, typename Default, typename Reference>
            struct apply
            {
                typedef Default type;
            };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            template <typename KW, typename Default, typename Reference>
            using fn = Default;
#endif
        };

        // Terminator for has_key, indicating that the keyword is unique.
        template <typename KW>
        static ::boost::parameter::aux::no_tag has_key(KW*);

        // If either of these operators are called, it means there is no
        // argument in the list that matches the supplied keyword.  Just
        // return the default value.
        template <typename K, typename Default>
        inline BOOST_CONSTEXPR Default&
            operator[](::boost::parameter::aux::default_<K,Default> x) const
        {
            return x.value;
        }

        template <typename K, typename Default>
        inline BOOST_CONSTEXPR Default&&
            operator[](::boost::parameter::aux::default_r_<K,Default> x) const
        {
            return ::std::forward<Default>(x.value);
        }

        // If this operator is called, it means there is no argument in the
        // list that matches the supplied keyword.  Just evaluate and return
        // the default value.
        template <typename K, typename F>
        inline BOOST_CONSTEXPR
        typename ::boost::parameter::aux::result_of0<F>::type
            operator[](BOOST_PARAMETER_lazy_default_fallback<K,F> x) const
        {
            return x.compute_default();
        }

        // No argument corresponding to ParameterRequirements::key_type
        // was found if we match this overload, so unless that parameter
        // has a default, we indicate that the actual arguments don't
        // match the function's requirements.
        template <typename ParameterRequirements, typename ArgPack>
        static typename ParameterRequirements::has_default
            satisfies(ParameterRequirements*, ArgPack*);

        // MPL sequence support
        typedef ::boost::parameter::aux::empty_arg_list type; // convenience
        // For dispatching to sequence intrinsics
        typedef ::boost::parameter::aux::arg_list_tag tag;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/preprocessor/nullptr.hpp>
#include <boost/parameter/aux_/yesno.hpp>
#include <boost/parameter/aux_/is_maybe.hpp>
#include <boost/parameter/aux_/tagged_argument_fwd.hpp>
#include <boost/parameter/aux_/parameter_requirements.hpp>
#include <boost/parameter/aux_/augment_predicate.hpp>
#include <boost/parameter/keyword_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace parameter { namespace aux {

    // A tuple of tagged arguments, terminated with empty_arg_list.  Every
    // TaggedArg is an instance of tagged_argument<> or
    // tagged_argument_rref<>.
    template <
        typename TaggedArg
      , typename Next = ::boost::parameter::aux::empty_arg_list
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      , typename EmitsErrors = ::boost::mp11::mp_true
#else
      , typename EmitsErrors = ::boost::mpl::true_
#endif
    >
    class arg_list : public Next
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using _holds_maybe = typename ::boost::parameter::aux
        ::is_maybe<typename TaggedArg::value_type>::type;
#else
        typedef typename ::boost::parameter::aux
        ::is_maybe<typename TaggedArg::value_type>::type _holds_maybe;
#endif

        TaggedArg arg;      // Stores the argument

     public:
        typedef TaggedArg tagged_arg;
        typedef ::boost::parameter::aux::arg_list<TaggedArg,Next> self;
        typedef typename TaggedArg::key_type key_type;

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using reference = typename ::boost::mp11::mp_if<
            _holds_maybe
          , ::boost::parameter::aux
            ::get_reference<typename TaggedArg::value_type>
          , ::boost::parameter::aux::get_reference<TaggedArg>
        >::type;

        using value_type = ::boost::mp11
        ::mp_if<_holds_maybe,reference,typename TaggedArg::value_type>;
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
        typedef typename ::boost::mpl::eval_if<
            _holds_maybe
          , ::boost::parameter::aux
            ::get_reference<typename TaggedArg::value_type>
          , ::boost::parameter::aux::get_reference<TaggedArg>
        >::type reference;

        typedef typename ::boost::mpl::if_<
            _holds_maybe
          , reference
          , typename TaggedArg::value_type
        >::type value_type;
#endif  // BOOST_PARAMETER_CAN_USE_MP11

        // Create a new list by prepending arg to a copy of tail.  Used when
        // incrementally building this structure with the comma operator.
        inline BOOST_CONSTEXPR arg_list(
            TaggedArg const& head
          , Next const& tail
        ) : Next(tail), arg(head)
        {
        }

        // Store the arguments in successive nodes of this list.
        // Use tag dispatching to determine whether to forward all arguments
        // to the Next constructor, or store the first argument and forward
        // the rest. -- Cromwell D. Enage
        template <typename A0>
        inline BOOST_CONSTEXPR arg_list(
            ::boost::parameter::aux::value_type_is_not_void
          , A0&& a0
        ) : Next(
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                ::boost::mp11::mp_if<
                    ::std::is_same<
#else
                typename ::boost::mpl::if_<
                    ::boost::is_same<
#endif
                        typename Next::tagged_arg::value_type
                      , ::boost::parameter::void_
                    >
                  , ::boost::parameter::aux::value_type_is_void
                  , ::boost::parameter::aux::value_type_is_not_void
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                >()
#else
                >::type()
#endif
            )
          , arg(::std::forward<A0>(a0))
        {
        }

        template <typename ...Args>
        inline BOOST_CONSTEXPR arg_list(
            ::boost::parameter::aux::value_type_is_void
          , Args&&... args
        ) : Next(
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                ::boost::mp11::mp_if<
                    ::std::is_same<
#else
                typename ::boost::mpl::if_<
                    ::boost::is_same<
#endif
                        typename Next::tagged_arg::value_type
                      , ::boost::parameter::void_
                    >
                  , ::boost::parameter::aux::value_type_is_void
                  , ::boost::parameter::aux::value_type_is_not_void
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                >()
#else
                >::type()
#endif
              , ::std::forward<Args>(args)...
            )
          , arg(::boost::parameter::aux::void_reference())
        {
        }

        template <typename A0, typename A1, typename ...Args>
        inline BOOST_CONSTEXPR arg_list(
            ::boost::parameter::aux::value_type_is_not_void
          , A0&& a0
          , A1&& a1
          , Args&&... args
        ) : Next(
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                ::boost::mp11::mp_if<
                    ::std::is_same<
#else
                typename ::boost::mpl::if_<
                    ::boost::is_same<
#endif
                        typename Next::tagged_arg::value_type
                      , ::boost::parameter::void_
                    >
                  , ::boost::parameter::aux::value_type_is_void
                  , ::boost::parameter::aux::value_type_is_not_void
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
                >()
#else
                >::type()
#endif
              , ::std::forward<A1>(a1)
              , ::std::forward<Args>(args)...
            )
          , arg(::std::forward<A0>(a0))
        {
        }

        // A metafunction class that, given a keyword and a default type,
        // returns the appropriate result type for a keyword lookup given
        // that default.
        struct binding
        {
            typedef typename Next::binding next_binding;

            template <typename KW, typename Default, typename Reference>
            struct apply
            {
                typedef typename ::boost::mpl::eval_if<
                    ::boost::is_same<KW,key_type>
                  , ::boost::mpl::if_<Reference,reference,value_type>
                  , ::boost::mpl
                    ::apply_wrap3<next_binding,KW,Default,Reference>
                >::type type;
            };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            template <typename KW, typename Default, typename Reference>
            using fn = ::boost::mp11::mp_if<
                ::std::is_same<KW,key_type>
              , ::boost::mp11::mp_if<Reference,reference,value_type>
              , ::boost::mp11::mp_apply_q<
                    next_binding
                  , ::boost::mp11::mp_list<KW,Default,Reference>
                >
            >;
#endif
        };

        // Overload for key_type, so the assert below will fire
        // if the same keyword is used again.
        static ::boost::parameter::aux::yes_tag has_key(key_type*);
        using Next::has_key;

     private:
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using _has_unique_key = ::boost::mp11::mp_bool<
#else
        typedef ::boost::mpl::bool_<
#endif
            sizeof(
                Next::has_key(
                    static_cast<key_type*>(BOOST_PARAMETER_AUX_PP_NULLPTR)
                )
            ) == sizeof(::boost::parameter::aux::no_tag)
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        >;
#else
        > _has_unique_key;
#endif

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        static_assert(
            !(EmitsErrors::value) || (_has_unique_key::value)
          , "duplicate keyword"
        );
#else
        BOOST_MPL_ASSERT_MSG(
            !(EmitsErrors::value) || (_has_unique_key::value)
          , duplicate_keyword
          , (key_type)
        );
#endif

        //
        // Begin implementation of indexing operators
        // for looking up specific arguments by name.
        //

        // Helpers that handle the case when TaggedArg is empty<T>.
        template <typename D>
        inline BOOST_CONSTEXPR reference
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            get_default(D const&, ::boost::mp11::mp_false) const
#else
            get_default(D const&, ::boost::mpl::false_) const
#endif
        {
            return this->arg.get_value();
        }

        template <typename D>
        inline BOOST_CONSTEXPR reference
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            get_default(D const& d, ::boost::mp11::mp_true) const
#else
            get_default(D const& d, ::boost::mpl::true_) const
#endif
        {
            return (
                this->arg.get_value()
              ? this->arg.get_value().get()
              : this->arg.get_value().construct(d.value)
            );
        }

     public:
        inline BOOST_CONSTEXPR reference
            operator[](::boost::parameter::keyword<key_type> const&) const
        {
#if !defined(BOOST_NO_CXX14_CONSTEXPR)
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            static_assert(!_holds_maybe::value, "must not hold maybe");
#elif !( \
        BOOST_WORKAROUND(BOOST_GCC, >= 40700) && \
        BOOST_WORKAROUND(BOOST_GCC, < 40900) \
    ) && !BOOST_WORKAROUND(BOOST_GCC, >= 50000) && \
    !BOOST_WORKAROUND(BOOST_MSVC, < 1910)
            BOOST_MPL_ASSERT_NOT((_holds_maybe));
#endif
#endif
            return this->arg.get_value();
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::default_<key_type,Default> const& d
            ) const
        {
            return this->get_default(d, _holds_maybe());
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::default_r_<key_type,Default> const& d
            ) const
        {
            return this->get_default(d, _holds_maybe());
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                BOOST_PARAMETER_lazy_default_fallback<key_type,Default> const&
            ) const
        {
#if !defined(BOOST_NO_CXX14_CONSTEXPR)
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            static_assert(!_holds_maybe::value, "must not hold maybe");
#elif !( \
        BOOST_WORKAROUND(BOOST_GCC, >= 40700) && \
        BOOST_WORKAROUND(BOOST_GCC, < 40900) \
    ) && !BOOST_WORKAROUND(BOOST_GCC, >= 50000) && \
    !BOOST_WORKAROUND(BOOST_MSVC, < 1910)
            BOOST_MPL_ASSERT_NOT((_holds_maybe));
#endif
#endif
            return this->arg.get_value();
        }

        // Builds an overload set including operator[]s defined
        // in base classes.
        using Next::operator[];

        //
        // End of indexing support
        //

        // For parameter_requirements matching this node's key_type, return
        // a bool constant wrapper indicating whether the requirements are
        // satisfied by TaggedArg.  Used only for compile-time computation
        // and never really called, so a declaration is enough.
        template <typename HasDefault, typename Predicate, typename ArgPack>
        static typename ::boost::lazy_enable_if<
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
            ::boost::mp11::mp_if<
                EmitsErrors
              , ::boost::mp11::mp_true
              , _has_unique_key
            >
          , ::boost::parameter::aux::augment_predicate_mp11<
#else
            typename ::boost::mpl::if_<
                EmitsErrors
              , ::boost::mpl::true_
              , _has_unique_key
            >::type
          , ::boost::parameter::aux::augment_predicate<
#endif
                Predicate
              , reference
              , key_type
              , value_type
              , ArgPack
            >
        >::type
            satisfies(
                ::boost::parameter::aux::parameter_requirements<
                    key_type
                  , Predicate
                  , HasDefault
                >*
              , ArgPack*
            );

        // Builds an overload set including satisfies functions defined
        // in base classes.
        using Next::satisfies;

        // Comma operator to compose argument list without using parameters<>.
        // Useful for argument lists with undetermined length.
        template <typename KW, typename T2>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::arg_list<
            ::boost::parameter::aux::tagged_argument<KW,T2>
          , self
        >
            operator,(
                ::boost::parameter::aux::tagged_argument<KW,T2> const& x
            ) const
        {
            return ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument<KW,T2>
              , self
            >(x, *this);
        }

        template <typename KW, typename T2>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::arg_list<
            ::boost::parameter::aux::tagged_argument_rref<KW,T2>
          , self
        >
            operator,(
                ::boost::parameter::aux::tagged_argument_rref<KW,T2> const& x
            ) const
        {
            return ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument_rref<KW,T2>
              , self
            >(x, *this);
        }

        // MPL sequence support
        typedef self type;        // Convenience for users
        typedef Next tail_type;   // For the benefit of iterators
        // For dispatching to sequence intrinsics
        typedef ::boost::parameter::aux::arg_list_tag tag;
    };
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

namespace boost { namespace parameter { namespace aux {

    // Terminates arg_list<> and represents an empty list.  Since this is just
    // the terminating case, you might want to look at arg_list first to get a
    // feel for what's really happening here.
    struct empty_arg_list
    {
        inline BOOST_CONSTEXPR empty_arg_list()
        {
        }

        // Constructor taking BOOST_PARAMETER_COMPOSE_MAX_ARITY empty_arg_list
        // arguments; this makes initialization.
        inline BOOST_CONSTEXPR empty_arg_list(
            BOOST_PP_ENUM_PARAMS(
                BOOST_PARAMETER_COMPOSE_MAX_ARITY
              , ::boost::parameter::void_ BOOST_PP_INTERCEPT
            )
        )
        {
        }

        // A metafunction class that, given a keyword and a default type,
        // returns the appropriate result type for a keyword lookup given
        // that default.
        struct binding
        {
            template <typename KW, typename Default, typename Reference>
            struct apply
            {
                typedef Default type;
            };
        };

        // Terminator for has_key, indicating that the keyword is unique.
        template <typename KW>
        static ::boost::parameter::aux::no_tag has_key(KW*);

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
        // The overload set technique doesn't work with these older compilers,
        // so they need some explicit handholding.

        // A metafunction class that, given a keyword, returns the type of the
        // base sublist whose get() function can produce the value for that key.
        struct key_owner
        {
            template <typename KW>
            struct apply
            {
                typedef ::boost::parameter::aux::empty_arg_list type;
            };
        };
#endif  // Borland workarounds needed

        // If either of these operators are called, it means there is no
        // argument in the list that matches the supplied keyword.  Just
        // return the default value.
        template <typename K, typename Default>
        inline BOOST_CONSTEXPR Default&
            operator[](::boost::parameter::aux::default_<K,Default> x) const
        {
            return x.value;
        }

        // If this operator is called, it means there is no argument in the
        // list that matches the supplied keyword.  Just evaluate and return
        // the default value.
        template <typename K, typename F>
        inline BOOST_CONSTEXPR
        typename ::boost::parameter::aux::result_of0<F>::type
            operator[](BOOST_PARAMETER_lazy_default_fallback<K,F> x) const
        {
            return x.compute_default();
        }

        // No argument corresponding to ParameterRequirements::key_type
        // was found if we match this overload, so unless that parameter
        // has a default, we indicate that the actual arguments don't
        // match the function's requirements.
        template <typename ParameterRequirements, typename ArgPack>
        static typename ParameterRequirements::has_default
            satisfies(ParameterRequirements*, ArgPack*);

        // MPL sequence support
        typedef ::boost::parameter::aux::empty_arg_list type; // convenience
        // For dispatching to sequence intrinsics
        typedef ::boost::parameter::aux::arg_list_tag tag;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/yesno.hpp>
#include <boost/parameter/aux_/is_maybe.hpp>
#include <boost/parameter/aux_/tagged_argument_fwd.hpp>
#include <boost/parameter/aux_/parameter_requirements.hpp>
#include <boost/parameter/aux_/augment_predicate.hpp>
#include <boost/parameter/keyword_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>

#if !defined(BOOST_NO_SFINAE) && !BOOST_WORKAROUND(BOOST_MSVC, < 1800)
#include <boost/core/enable_if.hpp>
#endif

#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
#include <boost/parameter/aux_/preprocessor/nullptr.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // A tuple of tagged arguments, terminated with empty_arg_list.  Every
    // TaggedArg is an instance of tagged_argument<>.
    template <
        typename TaggedArg
      , typename Next = ::boost::parameter::aux::empty_arg_list
      , typename EmitsErrors = ::boost::mpl::true_
    >
    class arg_list : public Next
    {
        typedef typename ::boost::parameter::aux
        ::is_maybe<typename TaggedArg::value_type>::type _holds_maybe;

        TaggedArg arg;      // Stores the argument

     public:
        typedef TaggedArg tagged_arg;
        typedef ::boost::parameter::aux::arg_list<TaggedArg,Next> self;
        typedef typename TaggedArg::key_type key_type;

        typedef typename ::boost::mpl::eval_if<
            _holds_maybe
          , ::boost::parameter::aux
            ::get_reference<typename TaggedArg::value_type>
          , ::boost::parameter::aux::get_reference<TaggedArg>
        >::type reference;

        typedef typename ::boost::mpl::if_<
            _holds_maybe
          , reference
          , typename TaggedArg::value_type
        >::type value_type;

        // Create a new list by prepending arg to a copy of tail.  Used when
        // incrementally building this structure with the comma operator.
        inline BOOST_CONSTEXPR arg_list(
            TaggedArg const& head
          , Next const& tail
        ) : Next(tail), arg(head)
        {
        }

        // Store the arguments in successive nodes of this list.
        template <
            // typename A0, typename A1, ...
            BOOST_PP_ENUM_PARAMS(
                BOOST_PARAMETER_COMPOSE_MAX_ARITY
              , typename A
            )
        >
        inline BOOST_CONSTEXPR arg_list(
            // A0& a0, A1& a1, ...
            BOOST_PP_ENUM_BINARY_PARAMS(
                BOOST_PARAMETER_COMPOSE_MAX_ARITY
              , A
              , & a
            )
        ) : Next(
                // a1, a2, ...
                BOOST_PP_ENUM_SHIFTED_PARAMS(
                    BOOST_PARAMETER_COMPOSE_MAX_ARITY
                  , a
                )
              , ::boost::parameter::aux::void_reference()
            )
          , arg(a0)
        {
        }

        // A metafunction class that, given a keyword and a default type,
        // returns the appropriate result type for a keyword lookup given
        // that default.
        struct binding
        {
            typedef typename Next::binding next_binding;

            template <typename KW, typename Default, typename Reference>
            struct apply
            {
                typedef typename ::boost::mpl::eval_if<
                    ::boost::is_same<KW,key_type>
                  , ::boost::mpl::if_<Reference,reference,value_type>
                  , ::boost::mpl::apply_wrap3<
                        next_binding
                      , KW
                      , Default
                      , Reference
                    >
                >::type type;
            };
        };

#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
        // Overload for key_type, so the assert below will fire
        // if the same keyword is used again.
        static ::boost::parameter::aux::yes_tag has_key(key_type*);
        using Next::has_key;

     private:
#if defined(BOOST_NO_SFINAE) || BOOST_WORKAROUND(BOOST_MSVC, < 1800)
        BOOST_MPL_ASSERT_MSG(
            sizeof(
                Next::has_key(
                    static_cast<key_type*>(BOOST_PARAMETER_AUX_PP_NULLPTR)
                )
            ) == sizeof(::boost::parameter::aux::no_tag)
          , duplicate_keyword
          , (key_type)
        );
#else
        typedef ::boost::mpl::bool_<
            sizeof(
                Next::has_key(
                    static_cast<key_type*>(BOOST_PARAMETER_AUX_PP_NULLPTR)
                )
            ) == sizeof(::boost::parameter::aux::no_tag)
        > _has_unique_key;

        BOOST_MPL_ASSERT_MSG(
            !(EmitsErrors::value) || (_has_unique_key::value)
          , duplicate_keyword
          , (key_type)
        );
#endif  // SFINAE/MSVC workarounds needed
#endif  // Borland workarounds not needed

     private:
        //
        // Begin implementation of indexing operators
        // for looking up specific arguments by name.
        //

        // Helpers that handle the case when TaggedArg is empty<T>.
        template <typename D>
        inline BOOST_CONSTEXPR reference
            get_default(D const&, ::boost::mpl::false_) const
        {
            return this->arg.get_value();
        }

        template <typename D>
        inline BOOST_CONSTEXPR reference
            get_default(D const& d, ::boost::mpl::true_) const
        {
            return (
                this->arg.get_value()
              ? this->arg.get_value().get()
              : this->arg.get_value().construct(d.value)
            );
        }

     public:
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
        // These older compilers don't support the overload set creation
        // idiom well, so we need to do all the return type calculation
        // for the compiler and dispatch through an outer function template.

        // A metafunction class that, given a keyword, returns the base
        // sublist whose get() function can produce the value for that key.
        struct key_owner
        {
            typedef typename Next::key_owner next_key_owner;

            template <typename KW>
            struct apply
            {
                typedef typename ::boost::mpl::eval_if<
                    ::boost::is_same<KW,key_type>
                  , ::boost::mpl::identity<
                        ::boost::parameter::aux::arg_list<TaggedArg,Next>
                    >
                  , ::boost::mpl::apply_wrap1<next_key_owner,KW>
                >::type type;
            };
        };

        // Outer indexing operators that dispatch to the right node's
        // get() function.
        template <typename KW>
        inline BOOST_CONSTEXPR typename ::boost::mpl::apply_wrap3<
            binding
          , KW
          , ::boost::parameter::void_
          , ::boost::mpl::true_
        >::type
            operator[](::boost::parameter::keyword<KW> const& x) const
        {
            typename ::boost::mpl::apply_wrap1<key_owner,KW>::type const&
                sublist = *this;
            return sublist.get(x);
        }

        template <typename KW, typename Default>
        inline BOOST_CONSTEXPR typename ::boost::mpl::apply_wrap3<
            binding
          , KW
          , Default&
          , ::boost::mpl::true_
        >::type
            operator[](
                ::boost::parameter::aux::default_<KW,Default> const& x
            ) const
        {
            typename ::boost::mpl::apply_wrap1<key_owner,KW>::type const&
                sublist = *this;
            return sublist.get(x);
        }

        template <typename KW, typename F>
        inline BOOST_CONSTEXPR typename ::boost::mpl::apply_wrap3<
            binding
          , KW
          , typename ::boost::parameter::aux::result_of0<F>::type
          , ::boost::mpl::true_
        >::type
            operator[](
                BOOST_PARAMETER_lazy_default_fallback<KW,F> const& x
            ) const
        {
            typename ::boost::mpl::apply_wrap1<key_owner,KW>::type const&
                sublist = *this;
            return sublist.get(x);
        }

        // These just return the stored value; when empty_arg_list is reached,
        // indicating no matching argument was passed, the default is
        // returned, or if no default_ or lazy_default was passed, compilation
        // fails.
        inline BOOST_CONSTEXPR reference
            get(::boost::parameter::keyword<key_type> const&) const
        {
            BOOST_MPL_ASSERT_NOT((_holds_maybe));
            return this->arg.get_value();
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            get(
                ::boost::parameter::aux::default_<key_type,Default> const& d
            ) const
        {
            return this->get_default(d, _holds_maybe());
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            get(
                BOOST_PARAMETER_lazy_default_fallback<key_type,Default> const&
            ) const
        {
            return this->arg.get_value();
        }
#else   // !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
        inline BOOST_CONSTEXPR reference
            operator[](::boost::parameter::keyword<key_type> const&) const
        {
            BOOST_MPL_ASSERT_NOT((_holds_maybe));
            return this->arg.get_value();
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                ::boost::parameter::aux::default_<key_type,Default> const& d
            ) const
        {
            return this->get_default(d, _holds_maybe());
        }

        template <typename Default>
        inline BOOST_CONSTEXPR reference
            operator[](
                BOOST_PARAMETER_lazy_default_fallback<key_type,Default> const&
            ) const
        {
            BOOST_MPL_ASSERT_NOT((_holds_maybe));
            return this->arg.get_value();
        }

        // Builds an overload set including operator[]s defined
        // in base classes.
        using Next::operator[];

        //
        // End of indexing support
        //

        // For parameter_requirements matching this node's key_type, return
        // a bool constant wrapper indicating whether the requirements are
        // satisfied by TaggedArg.  Used only for compile-time computation
        // and never really called, so a declaration is enough.
        template <typename HasDefault, typename Predicate, typename ArgPack>
        static typename
#if !defined(BOOST_NO_SFINAE) && !BOOST_WORKAROUND(BOOST_MSVC, < 1800)
        ::boost::lazy_enable_if<
            typename ::boost::mpl::if_<
                EmitsErrors
              , ::boost::mpl::true_
              , _has_unique_key
            >::type,
#endif
            ::boost::parameter::aux::augment_predicate<
                Predicate
              , reference
              , key_type
              , value_type
              , ArgPack
#if !defined(BOOST_NO_SFINAE) && !BOOST_WORKAROUND(BOOST_MSVC, < 1800)
           >
#endif
        >::type
            satisfies(
                ::boost::parameter::aux::parameter_requirements<
                    key_type
                  , Predicate
                  , HasDefault
                >*
              , ArgPack*
            );

        // Builds an overload set including satisfies functions defined
        // in base classes.
        using Next::satisfies;
#endif  // Borland workarounds needed

        // Comma operator to compose argument list without using parameters<>.
        // Useful for argument lists with undetermined length.
        template <typename KW, typename T2>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::arg_list<
            ::boost::parameter::aux::tagged_argument<KW,T2>
          , self
        >
            operator,(
                ::boost::parameter::aux::tagged_argument<KW,T2> const& x
            ) const
        {
            return ::boost::parameter::aux::arg_list<
                ::boost::parameter::aux::tagged_argument<KW,T2>
              , self
            >(x, *this);
        }

        // MPL sequence support
        typedef self type;        // Convenience for users
        typedef Next tail_type;   // For the benefit of iterators
        // For dispatching to sequence intrinsics
        typedef ::boost::parameter::aux::arg_list_tag tag;
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

#if defined(BOOST_PARAMETER_CAN_USE_MP11)

namespace boost { namespace parameter { namespace aux {

    template <typename ...ArgTuples>
    struct arg_list_cons;

    template <>
    struct arg_list_cons<>
    {
        using type = ::boost::parameter::aux::empty_arg_list;
    };

    template <typename ArgTuple0, typename ...Tuples>
    struct arg_list_cons<ArgTuple0,Tuples...>
    {
        using type = ::boost::parameter::aux::arg_list<
            typename ArgTuple0::tagged_arg
          , typename ::boost::parameter::aux::arg_list_cons<Tuples...>::type
          , typename ArgTuple0::emits_errors
        >;
    };

    template <
        typename Keyword
      , typename TaggedArg
      , typename EmitsErrors = ::boost::mp11::mp_true
    >
    struct flat_like_arg_tuple
    {
        using tagged_arg = TaggedArg;
        using emits_errors = EmitsErrors;
    };

    template <typename ...ArgTuples>
    class flat_like_arg_list
      : public ::boost::parameter::aux::arg_list_cons<ArgTuples...>::type
    {
        using _base_type = typename ::boost::parameter::aux
        ::arg_list_cons<ArgTuples...>::type;

     public:
        inline BOOST_CONSTEXPR flat_like_arg_list(
            typename _base_type::tagged_arg const& head
          , typename _base_type::tail_type const& tail
        ) : _base_type(head, tail)
        {
        }

        template <typename ...Args>
        inline BOOST_CONSTEXPR flat_like_arg_list(Args&&... args)
          : _base_type(::std::forward<Args>(args)...)
        {
        }

        using _base_type::operator[];
        using _base_type::satisfies;

        // Comma operator to compose argument list without using parameters<>.
        // Useful for argument lists with undetermined length.
        template <typename TaggedArg>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::flat_like_arg_list<
            ::boost::parameter::aux::flat_like_arg_tuple<
                typename TaggedArg::base_type::key_type
              , typename TaggedArg::base_type
            >
          , ArgTuples...
        >
            operator,(TaggedArg const& x) const
        {
            return ::boost::parameter::aux::flat_like_arg_list<
                ::boost::parameter::aux::flat_like_arg_tuple<
                    typename TaggedArg::base_type::key_type
                  , typename TaggedArg::base_type
                >
              , ArgTuples...
            >(
                static_cast<typename TaggedArg::base_type const&>(x)
              , static_cast<_base_type const&>(*this)
            );
        }
    };

    template <>
    class flat_like_arg_list<>
      : public ::boost::parameter::aux::empty_arg_list
    {
        using _base_type = ::boost::parameter::aux::empty_arg_list;

     public:
        template <typename ...Args>
        inline BOOST_CONSTEXPR flat_like_arg_list(Args&&... args)
          : _base_type(::std::forward<Args>(args)...)
        {
        }

        using _base_type::operator[];
        using _base_type::satisfies;

        // Comma operator to compose argument list without using parameters<>.
        // Useful for argument lists with undetermined length.
        template <typename TaggedArg>
        inline BOOST_CONSTEXPR ::boost::parameter::aux::flat_like_arg_list<
            ::boost::parameter::aux::flat_like_arg_tuple<
                typename TaggedArg::base_type::key_type
              , typename TaggedArg::base_type
            >
        >
            operator,(TaggedArg const& x) const
        {
            return ::boost::parameter::aux::flat_like_arg_list<
                ::boost::parameter::aux::flat_like_arg_tuple<
                    typename TaggedArg::base_type::key_type
                  , typename TaggedArg::base_type
                >
            >(
                static_cast<typename TaggedArg::base_type const&>(x)
              , static_cast<_base_type const&>(*this)
            );
        }
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11

#include <boost/mpl/iterator_tags.hpp>

namespace boost { namespace parameter { namespace aux {

    // MPL sequence support
    template <typename ArgumentPack>
    struct arg_list_iterator
    {
        typedef ::boost::mpl::forward_iterator_tag category;

        // The incremented iterator
        typedef ::boost::parameter::aux
        ::arg_list_iterator<typename ArgumentPack::tail_type> next;

        // dereferencing yields the key type
        typedef typename ArgumentPack::key_type type;
    };

    template <>
    struct arg_list_iterator< ::boost::parameter::aux::empty_arg_list>
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/mpl/begin_end_fwd.hpp>

// MPL sequence support
namespace boost { namespace mpl {

    template <>
    struct begin_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename S>
        struct apply
        {
            typedef ::boost::parameter::aux::arg_list_iterator<S> type;
        };
    };

    template <>
    struct end_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename>
        struct apply
        {
            typedef ::boost::parameter::aux::arg_list_iterator<
                ::boost::parameter::aux::empty_arg_list
            > type;
        };
    };
}} // namespace boost::mpl

#include <boost/parameter/value_type.hpp>
#include <boost/mpl/has_key_fwd.hpp>
#include <boost/type_traits/is_void.hpp>

namespace boost { namespace mpl {

    template <>
    struct has_key_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename ArgList, typename Keyword>
        struct apply
        {
            typedef typename ::boost::mpl::if_<
                ::boost::is_void<
                    typename ::boost::parameter
                    ::value_type<ArgList,Keyword,void>::type
                >
              , ::boost::mpl::false_
              , ::boost::mpl::true_
            >::type type;
        };
    };
}} // namespace boost::mpl

#include <boost/mpl/count_fwd.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace mpl {

    template <>
    struct count_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename ArgList, typename Keyword>
        struct apply
        {
            typedef typename ::boost::mpl::if_<
                ::boost::is_void<
                    typename ::boost::parameter
                    ::value_type<ArgList,Keyword,void>::type
                >
              , ::boost::mpl::int_<0>
              , ::boost::mpl::int_<1>
            >::type type;
        };
    };
}} // namespace boost::mpl

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace mpl {

    template <>
    struct key_type_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename ArgList, typename Keyword>
        struct apply
        {
            typedef typename ::boost::mpl::eval_if<
                ::boost::is_void<
                    typename ::boost::parameter
                    ::value_type<ArgList,Keyword,void>::type
                >
              , void
              , ::boost::mpl::identity<Keyword>
            >::type type;
        };
    };
}} // namespace boost::mpl

#include <boost/mpl/value_type_fwd.hpp>

namespace boost { namespace mpl {

    template <>
    struct value_type_impl< ::boost::parameter::aux::arg_list_tag>
      : ::boost::mpl::key_type_impl< ::boost::parameter::aux::arg_list_tag>
    {
    };
}} // namespace boost::mpl

#include <boost/mpl/at_fwd.hpp>

namespace boost { namespace mpl {

    template <>
    struct at_impl< ::boost::parameter::aux::arg_list_tag>
      : ::boost::mpl::key_type_impl< ::boost::parameter::aux::arg_list_tag>
    {
    };
}} // namespace boost::mpl

#include <boost/mpl/order_fwd.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/distance.hpp>

namespace boost { namespace mpl {

    template <>
    struct order_impl< ::boost::parameter::aux::arg_list_tag>
    {
        template <typename ArgList, typename Keyword>
        struct apply
        {
            typedef typename ::boost::mpl::find<ArgList,Keyword>::type Itr;
            typedef typename ::boost::mpl::eval_if<
                ::boost::is_void<
                    typename ::boost::parameter
                    ::value_type<ArgList,Keyword,void>::type
                >
              , ::boost::mpl::identity< ::boost::mpl::void_>
              , ::boost::mpl::distance<
                    Itr
                  , ::boost::parameter::aux::arg_list_iterator<
                        ::boost::parameter::aux::empty_arg_list
                    >
                >
            >::type type;
        };
    };
}} // namespace boost::mpl

#endif  // include guard


/* arg_list.hpp
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
*/