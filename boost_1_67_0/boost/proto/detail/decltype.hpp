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