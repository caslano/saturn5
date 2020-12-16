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
7X8tfrXm/HEevlI4+WO/uw6vFr6oh5M/1+NR4c/hVvm4AQ8L79fTKR+Z7NxyfnYzTbb/a/DVmv1fi6/U7H9eP/pwycqfC1+BZ2iOXx2uq59r8Gaa8DfiPTXbb8OnarbP7m8W9iTt17H4N2b7iTdqP0vw5xSX7Wc5vlFx2X5mD2AfcRl/Byt+/Ca8g+I7eNPSjH8UfqPwXhz8NDP+sfhVwsO4x3w3Dl8l/A3cOmrbBpK/mvbFGEQbb+ZfZ8U7md4JX4GnK3795U7+TcHnCJ9+l5N/3QZzfiR9qt+CW6ntjp8nvPndTvrX0FY/ojk/rsfv0pwfP8bPEu5V0hfKTty/TDffL8Hn2v0Zu/9rt59L8dnC/4Tb5w9cm/857EuC/etjeib+Xsw8jj99tNN/6oVv3cOxEeyj+a43/rbwWbhVfvrgbwl/ArfyP2MoxztB+ehvpq8nvlwc/4M5YR1qpq8vfq7wk/AOZmxH4MuE34gfbKZvBB4U7u2hlI9hjKfM/OumpO84M31v4UPwDqmO77yDcm2mbws+WHjOnfQBzfTtwHsLPx9PN9P3JX6I8K9wu30fzvk3Qf51NNM3BF+Cpym+YALjBjN92XiN8Lvw5mb6jsIjwnfj1vEdjlcK/8MpSv6N4BgkaL8GWOd3/I4E/eNWVv7hNzTuH9vl7238usb9Yzt97+DXaPrH246hfGj6d9vxpYrL83fhSL6juBwf+fAPFJfjoyL8PcXl+MiPb1Vcjo+uxm8THpzv7F/esRx/zf5Nw2s0/deF+Fjhh9/kvKvH709wfDPMELbidThm+xfznPH5Nvwa4YNKnPB/wc8UvvIGJbZRhrFY+LfK8a39DfVJc37PoCLfmWB828b0rvi1eKrifdKd49cN/4NwH24dv+74VcLX4lZqz8MHCT+lVBmfHM/4WnP8NuFzNMfvO7yP8OZDlPmfXMLX9P964XMUl+HX4pdo5jfOxpdr5jfOx8/VzG9cgJ+jmd+4DZ8p/PRrlPPLaJ5vrZ4f5fgFX6+4nD9shz+muJw/moMXKS7nDwvwfOED5jnpq8fvUl2OL/E7FZf97/fxa4Rnn+Sk70N8tfAx1znp+wS/TPgtuF1/xlB/Ncf3PJz4k87/nI9frTu++JWa45s5ljZQ0772wn2a9rU3frqmfe2Dz9W0ryvwo2JxJZkfr9c6+zSOMqQbn+LvJBhfHGn6JPxBPK2Z49Hb6YNa88f4XcLX4e3M1MzGbxLe6g5e5js/fqXwCG7XnwnkgSd5+o7Ay/A0r+Pe25z05eCFwsfgVvqOwU8VfgVupW8sPkX4btxKX91E2tcE6Rtopu8xPISnpjhefRPxm+nbhJcIfxhvZabvJTxfeMublfkZvJ2xp1fi9vzbiRwv5fwi868QH4934GV5PRWqvZm++fixwjOuJQ1m+sL4UOF+3Or/RPBs4S/i9vllMv0tzflxG/6oWj9l/wh/WHHZPtVNYf+V8OX8/U14WHE5f387Pl9x2f5mTuUcl2D+9WCr/4vH0p+m+Cc3O+kbg98qvN8tTvhj8ZuFL467WX/whcK34nb/nLZ4mOb83QsfqrjMv0J8kCf5/JsPH6C6vP6FH44ny78VXLzI08yPbcM3K8dXxr8d/6viMv4d+EuKy/g35unbx234KZr+yXZ8mmZ+KhfsrAm/ENd5LR7WzH+ejYeM5Pl/Dh7UlF9jOu2PJnwPHtCE78X9mvBD+D3NFRfXf5fg48nM0xQfXkH/15p/wMcJr8LTzXdn4WOEP4e3NmvDhfhw4QOCSv2YTXuUoP6mWfUDf14453d7/Ho4vkn4oh7O+LAf/qTw53CrfeyPb1Bczp/uxD/PbJx/g6zr/3PoA7UhP1M=
*/