///////////////////////////////////////////////////////////////////////////////
// env.hpp
// Helpers for producing and consuming tranform env variables.
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_ENV_HPP_EAN_18_07_2012
#define BOOST_PROTO_TRANSFORM_ENV_HPP_EAN_18_07_2012

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/ref.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/transform/impl.hpp>
#include <boost/proto/detail/poly_function.hpp>
#include <boost/proto/detail/is_noncopyable.hpp>

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4180) // qualifier applied to function type has no meaning; ignored
#endif

namespace boost
{
    namespace proto
    {
        namespace detail
        {
            template<typename T>
            struct value_type
            {
                typedef typename remove_const<T>::type value;
                typedef typename add_reference<T>::type reference;
                typedef typename mpl::if_c<is_noncopyable<T>::value, reference, value>::type type;
            };

            template<typename T>
            struct value_type<T &>
            {
                typedef T &value;
                typedef T &reference;
                typedef T &type;
            };
        }

    #define BOOST_PROTO_DEFINE_ENV_VAR(TAG, NAME)                                                   \
        struct TAG                                                                                  \
        {                                                                                           \
            template<typename Value>                                                                \
            boost::proto::env<TAG, Value &> const                                                   \
                operator =(boost::reference_wrapper<Value> &value) const                            \
            {                                                                                       \
                return boost::proto::env<TAG, Value &>(value.get());                                \
            }                                                                                       \
            template<typename Value>                                                                \
            boost::proto::env<TAG, Value &> const                                                   \
                operator =(boost::reference_wrapper<Value> const &value) const                      \
            {                                                                                       \
                return boost::proto::env<TAG, Value &>(value.get());                                \
            }                                                                                       \
            template<typename Value>                                                                \
            typename boost::disable_if_c<                                                           \
                boost::is_const<Value>::value                                                       \
              , boost::proto::env<TAG, typename boost::proto::detail::value_type<Value>::type>      \
            >::type const operator =(Value &value) const                                            \
            {                                                                                       \
                return boost::proto::env<TAG, typename boost::proto::detail::value_type<Value>::type>(value); \
            }                                                                                       \
            template<typename Value>                                                                \
            boost::proto::env<TAG, typename boost::proto::detail::value_type<Value const>::type> const \
                operator =(Value const &value) const                                                \
            {                                                                                       \
                return boost::proto::env<TAG, typename boost::proto::detail::value_type<Value const>::type>(value); \
            }                                                                                       \
        };                                                                                          \
                                                                                                    \
        TAG const NAME = {}                                                                         \
        /**/

        namespace envns_
        {
            ////////////////////////////////////////////////////////////////////////////////////////////
            // env
            // A transform env is a slot-based storage mechanism, accessible by tag.
            template<typename Key, typename Value, typename Base /*= empty_env*/>
            struct env
              : private Base
            {
            private:
                Value value_;

            public:
                typedef Value value_type;
                typedef typename add_reference<Value>::type reference;
                typedef typename add_reference<typename add_const<Value>::type>::type const_reference;
                typedef void proto_environment_; ///< INTERNAL ONLY

                explicit env(const_reference value, Base const &base = Base())
                  : Base(base)
                  , value_(value)
                {}

                #if BOOST_WORKAROUND(__GNUC__, == 3) || (BOOST_WORKAROUND(__GNUC__, == 4) && __GNUC_MINOR__ <= 2)
                /// INTERNAL ONLY
                struct found
                {
                    typedef Value type;
                    typedef typename add_reference<typename add_const<Value>::type>::type const_reference;
                };

                template<typename OtherKey, typename OtherValue = key_not_found>
                struct lookup
                  : mpl::if_c<
                        is_same<OtherKey, Key>::value
                      , found
                      , typename Base::template lookup<OtherKey, OtherValue>
                    >::type
                {};
                #else
                /// INTERNAL ONLY
                template<typename OtherKey, typename OtherValue = key_not_found>
                struct lookup
                  : Base::template lookup<OtherKey, OtherValue>
                {};

                /// INTERNAL ONLY
                template<typename OtherValue>
                struct lookup<Key, OtherValue>
                {
                    typedef Value type;
                    typedef typename add_reference<typename add_const<Value>::type>::type const_reference;
                };
                #endif

                // For key-based lookups not intended to fail
                using Base::operator[];
                const_reference operator[](Key) const
                {
                    return this->value_;
                }

                // For key-based lookups that can fail, use the default if key not found.
                using Base::at;
                template<typename T>
                const_reference at(Key, T const &) const
                {
                    return this->value_;
                }
            };

            // define proto::data_type type and proto::data global
            BOOST_PROTO_DEFINE_ENV_VAR(data_type, data);
        }

        using envns_::data;

        namespace functional
        {
            ////////////////////////////////////////////////////////////////////////////////////////
            // as_env
            struct as_env
            {
                BOOST_PROTO_CALLABLE()
                BOOST_PROTO_POLY_FUNCTION()

                /// INTERNAL ONLY
                template<typename T, bool B = is_env<T>::value>
                struct impl
                {
                    typedef env<data_type, typename detail::value_type<T>::type> result_type;

                    result_type const operator()(detail::arg<T> t) const
                    {
                        return result_type(t());
                    }
                };

                /// INTERNAL ONLY
                template<typename T>
                struct impl<T, true>
                {
                    typedef T result_type;

                    typename add_const<T>::type operator()(detail::arg<T> t) const
                    {
                        return t();
                    }
                };

                template<typename Sig>
                struct result;

                template<typename This, typename T>
                struct result<This(T)>
                {
                    typedef typename impl<typename detail::normalize_arg<T>::type>::result_type type;
                };

                template<typename T>
                typename impl<typename detail::normalize_arg<T &>::type>::result_type const
                    operator()(T &t BOOST_PROTO_DISABLE_IF_IS_CONST(T)) const
                {
                    return impl<typename detail::normalize_arg<T &>::type>()(
                        static_cast<typename detail::normalize_arg<T &>::reference>(t)
                    );
                }

                template<typename T>
                typename impl<typename detail::normalize_arg<T const &>::type>::result_type const
                    operator()(T const &t) const
                {
                    return impl<typename detail::normalize_arg<T const &>::type>()(
                        static_cast<typename detail::normalize_arg<T const &>::reference>(t)
                    );
                }
            };

            ////////////////////////////////////////////////////////////////////////////////////////
            // has_env_var
            template<typename Key>
            struct has_env_var
              : detail::poly_function<has_env_var<Key> >
            {
                BOOST_PROTO_CALLABLE()

                template<typename Env, bool IsEnv = is_env<Env>::value>
                struct impl
                {
                    typedef
                        mpl::not_<
                            is_same<
                                typename remove_reference<Env>::type::template lookup<Key>::type
                              , key_not_found
                            >
                        >
                    result_type;

                    result_type operator()(detail::arg<Env>) const
                    {
                        return result_type();
                    }
                };

                template<typename Env>
                struct impl<Env, false>
                {
                    typedef mpl::false_ result_type;

                    result_type operator()(detail::arg<Env>) const
                    {
                        return result_type();
                    }
                };
            };

            template<>
            struct has_env_var<data_type>
              : detail::poly_function<has_env_var<data_type> >
            {
                BOOST_PROTO_CALLABLE()

                template<typename Env, bool IsEnv = is_env<Env>::value>
                struct impl
                {
                    typedef
                        mpl::not_<
                            is_same<
                                typename remove_reference<Env>::type::template lookup<data_type>::type
                              , key_not_found
                            >
                        >
                    result_type;

                    result_type operator()(detail::arg<Env>) const
                    {
                        return result_type();
                    }
                };

                template<typename Env>
                struct impl<Env, false>
                {
                    typedef mpl::true_ result_type;

                    result_type operator()(detail::arg<Env>) const
                    {
                        return result_type();
                    }
                };
            };

            ////////////////////////////////////////////////////////////////////////////////////////
            // env_var
            template<typename Key>
            struct env_var
              : detail::poly_function<env_var<Key> >
            {
                BOOST_PROTO_CALLABLE()

                template<typename Env>
                struct impl
                {
                    typedef
                        typename remove_reference<Env>::type::template lookup<Key>::type
                    result_type;

                    result_type operator()(detail::arg<Env> e) const
                    {
                        return e()[Key()];
                    }
                };
            };

            template<>
            struct env_var<data_type>
              : detail::poly_function<env_var<data_type> >
            {
                BOOST_PROTO_CALLABLE()

                template<typename Env, bool B = is_env<Env>::value>
                struct impl
                {
                    typedef Env result_type;

                    result_type operator()(detail::arg<Env> e) const
                    {
                        return e();
                    }
                };

                template<typename Env>
                struct impl<Env, true>
                {
                    typedef
                        typename remove_reference<Env>::type::template lookup<data_type>::type
                    result_type;

                    result_type operator()(detail::arg<Env> e) const
                    {
                        return e()[proto::data];
                    }
                };
            };
        }

        namespace result_of
        {
            template<typename T>
            struct as_env
              : BOOST_PROTO_RESULT_OF<functional::as_env(T)>
            {};

            template<typename Env, typename Key>
            struct has_env_var
              : BOOST_PROTO_RESULT_OF<functional::has_env_var<Key>(Env)>::type
            {};

            template<typename Env, typename Key>
            struct env_var
              : BOOST_PROTO_RESULT_OF<functional::env_var<Key>(Env)>
            {};
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        // as_env
        template<typename T>
        typename proto::result_of::as_env<T &>::type const as_env(T &t BOOST_PROTO_DISABLE_IF_IS_CONST(T))
        {
            return proto::functional::as_env()(t);
        }

        template<typename T>
        typename proto::result_of::as_env<T const &>::type const as_env(T const &t)
        {
            return proto::functional::as_env()(t);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        // has_env_var
        template<typename Key, typename Env>
        typename proto::result_of::has_env_var<Env &, Key>::type has_env_var(Env &e BOOST_PROTO_DISABLE_IF_IS_CONST(Env))
        {
            return functional::has_env_var<Key>()(e);
        }

        template<typename Key, typename Env>
        typename proto::result_of::has_env_var<Env const &, Key>::type has_env_var(Env const &e)
        {
            return functional::has_env_var<Key>()(e);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        // env_var
        template<typename Key, typename Env>
        typename proto::result_of::env_var<Env &, Key>::type env_var(Env &e BOOST_PROTO_DISABLE_IF_IS_CONST(Env))
        {
            return functional::env_var<Key>()(e);
        }

        template<typename Key, typename Env>
        typename proto::result_of::env_var<Env const &, Key>::type env_var(Env const &e)
        {
            return functional::env_var<Key>()(e);
        }

        namespace envns_
        {
            ////////////////////////////////////////////////////////////////////////////////////////
            // env operator,
            template<typename T, typename T1, typename V1>
            inline typename disable_if_c<
                is_const<T>::value
              , env<T1, V1, BOOST_PROTO_UNCVREF(typename result_of::as_env<T &>::type)>
            >::type const operator,(T &t, env<T1, V1> const &head)
            {
                return env<T1, V1, BOOST_PROTO_UNCVREF(typename result_of::as_env<T &>::type)>(
                    head[T1()]
                  , proto::as_env(t)
                );
            }

            template<typename T, typename T1, typename V1>
            inline env<T1, V1, BOOST_PROTO_UNCVREF(typename result_of::as_env<T const &>::type)> const
                operator,(T const &t, env<T1, V1> const &head)
            {
                return env<T1, V1, BOOST_PROTO_UNCVREF(typename result_of::as_env<T const &>::type)>(
                    head[T1()]
                  , proto::as_env(t)
                );
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        // _env_var
        template<typename Key>
        struct _env_var
          : proto::transform<_env_var<Key> >
        {
            template<typename Expr, typename State, typename Data>
            struct impl
              : transform_impl<Expr, State, Data>
            {
                typedef typename impl::data::template lookup<Key>::type result_type;
                BOOST_MPL_ASSERT_NOT((is_same<result_type, key_not_found>)); // lookup failed

                BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, typename impl::data::template lookup<Key>::const_reference)
                operator ()(
                    typename impl::expr_param
                  , typename impl::state_param
                  , typename impl::data_param d
                ) const
                {
                    return d[Key()];
                }
            };
        };

        struct _env
          : transform<_env>
        {
            template<typename Expr, typename State, typename Data>
            struct impl
              : transform_impl<Expr, State, Data>
            {
                typedef Data result_type;

                BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, typename impl::data_param)
                operator ()(
                    typename impl::expr_param
                  , typename impl::state_param
                  , typename impl::data_param d
                ) const
                {
                    return d;
                }
            };
        };

        /// INTERNAL ONLY
        template<typename Key>
        struct is_callable<_env_var<Key> >
          : mpl::true_
        {};

        /// INTERNAL ONLY
        template<typename Key>
        struct is_callable<functional::has_env_var<Key> >
          : mpl::true_
        {};

        /// INTERNAL ONLY
        template<typename Key>
        struct is_callable<functional::env_var<Key> >
          : mpl::true_
        {};
    }
}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif

/* env.hpp
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
*/