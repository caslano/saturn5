///////////////////////////////////////////////////////////////////////////////
/// \file decltype.hpp
/// Contains definition the BOOST_PROTO_DECLTYPE_() macro and assorted helpers
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_DECLTYPE_HPP_EAN_04_04_2008
#define BOOST_PROTO_DETAIL_DECLTYPE_HPP_EAN_04_04_2008

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/get_pointer.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_member_object_pointer.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/detail/any.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

// We're STILL using Boost.Typeof on MSVC even for msvc-11.0 because of this bug:
// https://connect.microsoft.com/VisualStudio/feedback/details/765392/decltype-of-a-pointer-to-member-operator-gets-ref-qualification-wrong
#if !defined(BOOST_NO_CXX11_DECLTYPE) && !BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1700))
# define BOOST_PROTO_DECLTYPE_(EXPR, TYPE) typedef decltype((EXPR)) TYPE;
#else
# define BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL_(NESTED, EXPR)                                     \
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(BOOST_PP_CAT(nested_and_hidden_, NESTED), EXPR)                 \
    static int const BOOST_PP_CAT(sz, NESTED) = sizeof(boost::proto::detail::check_reference(EXPR));\
    struct NESTED                                                                                   \
      : boost::mpl::if_c<                                                                           \
            1 == BOOST_PP_CAT(sz, NESTED)                                                           \
          , typename BOOST_PP_CAT(nested_and_hidden_, NESTED)::type &                               \
          , typename BOOST_PP_CAT(nested_and_hidden_, NESTED)::type                                 \
        >                                                                                           \
    {};
# define BOOST_PROTO_DECLTYPE_(EXPR, TYPE)                                                          \
    BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL_(BOOST_PP_CAT(nested_, TYPE), (EXPR))                   \
    typedef typename BOOST_PP_CAT(nested_, TYPE)::type TYPE;
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        struct as_mutable
        {
            typedef T &type;
        };

        template<typename T>
        struct as_mutable<T &>
        {
            typedef T &type;
        };

        template<typename T>
        struct as_mutable<T const &>
        {
            typedef T &type;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        T make();

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        typename as_mutable<T>::type make_mutable();

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        struct subscript_wrapper
          : T
        {
            using T::operator[];

            #if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
            any operator[](any const volatile &) const volatile;
            #else
            any operator[](any const &) const volatile;
            #endif
        };

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        struct as_subscriptable
        {
            typedef
                typename mpl::if_c<
                    is_class<T>::value
                  , subscript_wrapper<T>
                  , T
                >::type
            type;
        };

        template<typename T>
        struct as_subscriptable<T const>
        {
            typedef
                typename mpl::if_c<
                    is_class<T>::value
                  , subscript_wrapper<T> const
                  , T const
                >::type
            type;
        };

        template<typename T>
        struct as_subscriptable<T &>
        {
            typedef
                typename mpl::if_c<
                    is_class<T>::value
                  , subscript_wrapper<T> &
                  , T &
                >::type
            type;
        };

        template<typename T>
        struct as_subscriptable<T const &>
        {
            typedef
                typename mpl::if_c<
                    is_class<T>::value
                  , subscript_wrapper<T> const &
                  , T const &
                >::type
            type;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        typename as_subscriptable<T>::type make_subscriptable();

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        char check_reference(T &);

        template<typename T>
        char (&check_reference(T const &))[2];

        namespace has_get_pointerns
        {
            using boost::get_pointer;
            void *(&get_pointer(...))[2];

            ////////////////////////////////////////////////////////////////////////////////////////////
            template<typename T>
            struct has_get_pointer
            {
                static const bool value = sizeof(void *) == sizeof(get_pointer(make<T &>()));
                typedef mpl::bool_<value> type;
            };
        }

        using has_get_pointerns::has_get_pointer;

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        struct class_member_traits;

        template<typename T, typename U>
        struct class_member_traits<T U::*>
        {
            typedef U class_type;
            typedef T result_type;
        };

        // Other specializations are generated by the preprocessor
        #include <boost/proto/detail/class_member_traits.hpp>

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        T &lvalue(T &t)
        {
            return t;
        }

        template<typename T>
        T const &lvalue(T const &t)
        {
            return t;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename U, typename V, typename T>
        U *proto_get_pointer(T &t, V *, U *)
        {
            return boost::addressof(t);
        }

        template<typename U, typename V, typename T>
        U const *proto_get_pointer(T &t, V *, U const *)
        {
            return boost::addressof(t);
        }

        template<typename U, typename V, typename T>
        V *proto_get_pointer(T &t, V *, ...)
        {
            return get_pointer(t);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        #define BOOST_PROTO_USE_GET_POINTER()                                                       \
        using namespace boost::proto::detail::get_pointerns                                         \
        /**/

        #define BOOST_PROTO_GET_POINTER(Type, Obj)                                                  \
        boost::proto::detail::proto_get_pointer<Type>(                                              \
            boost::proto::detail::lvalue(Obj)                                                       \
          , (true ? 0 : get_pointer(Obj))                                                           \
          , (true ? 0 : boost::addressof(boost::proto::detail::lvalue(Obj)))                        \
        )                                                                                           \
        /**/

        ////////////////////////////////////////////////////////////////////////////////////////////
        namespace get_pointerns
        {
            using boost::get_pointer;

            template<typename T>
            typename disable_if_c<has_get_pointer<T>::value, T *>::type
            get_pointer(T &t)
            {
                return boost::addressof(t);
            }

            template<typename T>
            typename disable_if_c<has_get_pointer<T>::value, T const *>::type
            get_pointer(T const &t)
            {
                return boost::addressof(t);
            }

            char test_ptr_to_const(void *);
            char (&test_ptr_to_const(void const *))[2];

            template<typename U> char test_V_is_a_U(U *);
            template<typename U> char test_V_is_a_U(U const *);
            template<typename U> char (&test_V_is_a_U(...))[2];

            ////////////////////////////////////////////////////////////////////////////////////////////
            // result_of_ is a wrapper around boost::result_of that also handles "invocations" of
            // member object pointers.
            template<typename T, typename Void = void>
            struct result_of_
              : BOOST_PROTO_RESULT_OF<T>
            {};

            template<typename T, typename U, typename V>
            struct result_of_<T U::*(V), typename enable_if_c<is_member_object_pointer<T U::*>::value>::type>
            {
                static const bool is_V_a_smart_ptr = 2 == sizeof(test_V_is_a_U<U>(&lvalue(make<V>())));
                static const bool is_ptr_to_const = 2 == sizeof(test_ptr_to_const(BOOST_PROTO_GET_POINTER(U, make<V>())));

                // If V is not a U, then it is a (smart) pointer and we can always return an lvalue.
                // Otherwise, we can only return an lvalue if we are given one.
                typedef
                    typename mpl::eval_if_c<
                        (is_V_a_smart_ptr || is_reference<V>::value)
                      , mpl::eval_if_c<
                            is_ptr_to_const
                          , add_reference<typename add_const<T>::type>
                          , add_reference<T>
                        >
                      , mpl::identity<T>
                    >::type
                type;
            };

            ////////////////////////////////////////////////////////////////////////////////////////////
            template<
                typename T
              , typename U
              , bool IsMemPtr = is_member_object_pointer<
                    typename remove_reference<U>::type
                >::value
            >
            struct mem_ptr_fun
            {
                BOOST_PROTO_DECLTYPE_(
                    proto::detail::make_mutable<T>() ->* proto::detail::make<U>()
                  , result_type
                )

                result_type operator()(
                    typename add_reference<typename add_const<T>::type>::type t
                  , typename add_reference<typename add_const<U>::type>::type u
                ) const
                {
                    return t ->* u;
                }
            };

            ////////////////////////////////////////////////////////////////////////////////////////////
            template<typename T, typename U>
            struct mem_ptr_fun<T, U, true>
            {
                typedef
                    typename class_member_traits<
                        typename uncvref<U>::type
                    >::class_type
                V;

                BOOST_PROTO_DECLTYPE_(
                    BOOST_PROTO_GET_POINTER(V, proto::detail::make_mutable<T>()) ->* proto::detail::make<U>()
                  , result_type
                )

                result_type operator()(
                    typename add_reference<typename add_const<T>::type>::type t
                  , U u
                ) const
                {
                    return BOOST_PROTO_GET_POINTER(V, t) ->* u;
                }
            };
        }

        using get_pointerns::result_of_;
        using get_pointerns::mem_ptr_fun;

        ////////////////////////////////////////////////////////////////////////////////////////////
        template<typename A0, typename A1>
        struct comma_result
        {
            BOOST_PROTO_DECLTYPE_((proto::detail::make<A0>(), proto::detail::make<A1>()), type)
        };

        template<typename A0>
        struct comma_result<A0, void>
        {
            typedef void type;
        };

        template<typename A1>
        struct comma_result<void, A1>
        {
            typedef A1 type;
        };

        template<>
        struct comma_result<void, void>
        {
            typedef void type;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////
        // normalize a function type for use with boost::result_of
        template<typename T, typename U = T>
        struct result_of_fixup
          : mpl::if_c<is_function<T>::value, T *, U>
        {};

        template<typename T, typename U>
        struct result_of_fixup<T &, U>
          : result_of_fixup<T, T>
        {};

        template<typename T, typename U>
        struct result_of_fixup<T const &, U>
          : result_of_fixup<T, T>
        {};

        template<typename T, typename U>
        struct result_of_fixup<T *, U>
          : result_of_fixup<T, U>
        {};

        template<typename R, typename T, typename U>
        struct result_of_fixup<R T::*, U>
        {
            typedef R T::*type;
        };

        template<typename T, typename U>
        struct result_of_fixup<T const, U>
          : result_of_fixup<T, U>
        {};

        //// Tests for result_of_fixup
        //struct bar {};
        //BOOST_MPL_ASSERT((is_same<bar,        result_of_fixup<bar>::type>));
        //BOOST_MPL_ASSERT((is_same<bar const,  result_of_fixup<bar const>::type>));
        //BOOST_MPL_ASSERT((is_same<bar,        result_of_fixup<bar &>::type>));
        //BOOST_MPL_ASSERT((is_same<bar const,  result_of_fixup<bar const &>::type>));
        //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(*)()>::type>));
        //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(* const)()>::type>));
        //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(* const &)()>::type>));
        //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(&)()>::type>));

        template<typename T, typename PMF>
        struct memfun
        {
            typedef typename uncvref<PMF>::type pmf_type;
            typedef typename class_member_traits<pmf_type>::class_type V;
            typedef typename class_member_traits<pmf_type>::result_type result_type;

            memfun(T t, pmf_type p)
              : obj(t)
              , pmf(p)
            {}

            result_type operator()() const
            {
                BOOST_PROTO_USE_GET_POINTER();
                return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)();
            }

            // Other overloads generated by the preprocessor
            #include <boost/proto/detail/memfun_funop.hpp>

        private:
            T obj;
            pmf_type pmf;
        };

    } // namespace detail
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* decltype.hpp
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
*/