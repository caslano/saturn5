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