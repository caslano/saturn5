///////////////////////////////////////////////////////////////////////////////
/// \file impl.hpp
/// Contains definition of transform<> and transform_impl<> helpers.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_IMPL_HPP_EAN_04_03_2008
#define BOOST_PROTO_TRANSFORM_IMPL_HPP_EAN_04_03_2008

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/detail/any.hpp>
#include <boost/proto/detail/static_const.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace envns_
    {
        ////////////////////////////////////////////////////////////////////////////////////////////
        struct key_not_found
        {};

        ////////////////////////////////////////////////////////////////////////////////////////////
        // empty_env
        struct empty_env
        {
            typedef void proto_environment_;

            template<typename OtherTag, typename OtherValue = key_not_found>
            struct lookup
            {
                typedef OtherValue type;
                typedef
                    typename add_reference<typename add_const<OtherValue>::type>::type
                const_reference;
            };

            key_not_found operator[](detail::any) const
            {
                return key_not_found();
            }

            template<typename T>
            T const &at(detail::any, T const &t) const
            {
                return t;
            }
        };
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    // is_env
    template<typename T, typename Void>
    struct is_env
      : mpl::false_
    {};

    template<typename T>
    struct is_env<T, typename T::proto_environment_>
      : mpl::true_
    {};

    template<typename T>
    struct is_env<T &, void>
      : is_env<T>
    {};

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_TRANSFORM_(PrimitiveTransform, X)                                                       \
    BOOST_PROTO_CALLABLE()                                                                                      \
    typedef X proto_is_transform_;                                                                              \
    typedef PrimitiveTransform transform_type;                                                                  \
                                                                                                                \
    template<typename Sig>                                                                                      \
    struct result                                                                                               \
    {                                                                                                           \
        typedef typename boost::proto::detail::apply_transform<Sig>::result_type type;                          \
    };                                                                                                          \
                                                                                                                \
    template<typename Expr>                                                                                     \
    BOOST_FORCEINLINE                                                                                           \
    typename boost::proto::detail::apply_transform<transform_type(Expr &)>::result_type                         \
    operator ()(Expr &e) const                                                                                  \
    {                                                                                                           \
        boost::proto::empty_state s = 0;                                                                        \
        boost::proto::empty_env d;                                                                              \
        return boost::proto::detail::apply_transform<transform_type(Expr &)>()(e, s, d);                        \
    }                                                                                                           \
                                                                                                                \
    template<typename Expr>                                                                                     \
    BOOST_FORCEINLINE                                                                                           \
    typename boost::proto::detail::apply_transform<transform_type(Expr const &)>::result_type                   \
    operator ()(Expr const &e) const                                                                            \
    {                                                                                                           \
        boost::proto::empty_state s = 0;                                                                        \
        boost::proto::empty_env d;                                                                              \
        return boost::proto::detail::apply_transform<transform_type(Expr const &)>()(e, s, d);                  \
    }                                                                                                           \
                                                                                                                \
    template<typename Expr, typename State>                                                                     \
    BOOST_FORCEINLINE                                                                                           \
    typename boost::proto::detail::apply_transform<transform_type(Expr &, State &)>::result_type                \
    operator ()(Expr &e, State &s) const                                                                        \
    {                                                                                                           \
        boost::proto::empty_env d;                                                                              \
        return boost::proto::detail::apply_transform<transform_type(Expr &, State &)>()(e, s, d);               \
    }                                                                                                           \
                                                                                                                \
    template<typename Expr, typename State>                                                                     \
    BOOST_FORCEINLINE                                                                                           \
    typename boost::proto::detail::apply_transform<transform_type(Expr const &, State &)>::result_type          \
    operator ()(Expr const &e, State &s) const                                                                  \
    {                                                                                                           \
        boost::proto::empty_env d;                                                                              \
        return boost::proto::detail::apply_transform<transform_type(Expr const &, State &)>()(e, s, d);         \
    }                                                                                                           \
                                                                                                                \
    template<typename Expr, typename State>                                                                     \
    BOOST_FORCEINLINE                                                                                           \
    typename boost::proto::detail::apply_transform<transform_type(Expr &, State const &)>::result_type          \
    operator ()(Expr &e, State const &s) const                                                                  \
    {                                                                                                           \
        boost::proto::empty_env d;                                                                              \
        return boost::proto::detail::apply_transform<transform_type(Expr &, State const &)>()(e, s, d);         \
    }                                                                                                           \
                                                                                                                \
    template<typename Expr, typename State>                                                                     \
    BOOST_FORCEINLINE                                                                                           \
    typename boost::proto::detail::apply_transform<transform_type(Expr const &, State const &)>::result_type    \
    operator ()(Expr const &e, State const &s) const                                                            \
    {                                                                                                           \
        boost::proto::empty_env d;                                                                              \
        return boost::proto::detail::apply_transform<transform_type(Expr const &, State const &)>()(e, s, d);   \
    }                                                                                                           \
                                                                                                                \
    template<typename Expr, typename State, typename Data>                                                      \
    BOOST_FORCEINLINE                                                                                           \
    typename boost::proto::detail::apply_transform<transform_type(Expr &, State &, Data &)>::result_type        \
    operator ()(Expr &e, State &s, Data &d) const                                                               \
    {                                                                                                           \
        return boost::proto::detail::apply_transform<transform_type(Expr &, State &, Data &)>()(e, s, d);       \
    }                                                                                                           \
                                                                                                                \
    template<typename Expr, typename State, typename Data>                                                      \
    BOOST_FORCEINLINE                                                                                           \
    typename boost::proto::detail::apply_transform<transform_type(Expr const &, State &, Data &)>::result_type  \
    operator ()(Expr const &e, State &s, Data &d) const                                                         \
    {                                                                                                           \
        return boost::proto::detail::apply_transform<transform_type(Expr const &, State &, Data &)>()(e, s, d); \
    }                                                                                                           \
                                                                                                                \
    template<typename Expr, typename State, typename Data>                                                      \
    BOOST_FORCEINLINE                                                                                           \
    typename boost::proto::detail::apply_transform<transform_type(Expr &, State const &, Data &)>::result_type  \
    operator ()(Expr &e, State const &s, Data &d) const                                                         \
    {                                                                                                           \
        return boost::proto::detail::apply_transform<transform_type(Expr &, State const &, Data &)>()(e, s, d); \
    }                                                                                                           \
                                                                                                                \
    template<typename Expr, typename State, typename Data>                                                      \
    BOOST_FORCEINLINE                                                                                           \
    typename boost::proto::detail::apply_transform<transform_type(Expr const &, State const &, Data &)>::result_type  \
    operator ()(Expr const &e, State const &s, Data &d) const                                                   \
    {                                                                                                           \
        return boost::proto::detail::apply_transform<transform_type(Expr const &, State const &, Data &)>()(e, s, d); \
    }                                                                                                           \
    /**/

#else

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_TRANSFORM_(PrimitiveTransform, X)                                                       \
    BOOST_PROTO_CALLABLE()                                                                                      \
    typedef X proto_is_transform_;                                                                              \
    typedef PrimitiveTransform transform_type;                                                                  \
                                                                                                                \
    template<typename Sig>                                                                                      \
    struct result                                                                                               \
    {                                                                                                           \
        typedef typename boost::proto::detail::apply_transform<Sig>::result_type type;                          \
    };                                                                                                          \
                                                                                                                \
    template<typename Expr>                                                                                     \
    BOOST_FORCEINLINE                                                                                           \
    typename boost::proto::detail::apply_transform<transform_type(Expr const &)>::result_type                   \
    operator ()(Expr &&e) const                                                                                 \
    {                                                                                                           \
        boost::proto::empty_state s = 0;                                                                        \
        boost::proto::empty_env d;                                                                              \
        return boost::proto::detail::apply_transform<transform_type(Expr const &)>()(e, s, d);                  \
    }                                                                                                           \
                                                                                                                \
    template<typename Expr, typename State>                                                                     \
    BOOST_FORCEINLINE                                                                                           \
    typename boost::proto::detail::apply_transform<transform_type(Expr const &, State const &)>::result_type    \
    operator ()(Expr &&e, State &&s) const                                                                      \
    {                                                                                                           \
        boost::proto::empty_env d;                                                                              \
        return boost::proto::detail::apply_transform<transform_type(Expr const &, State const &)>()(e, s, d);   \
    }                                                                                                           \
                                                                                                                \
    template<typename Expr, typename State, typename Data>                                                      \
    BOOST_FORCEINLINE                                                                                           \
    typename boost::proto::detail::apply_transform<transform_type(Expr const &, State const &, Data const &)>::result_type \
    operator ()(Expr &&e, State &&s, Data &&d) const                                                            \
    {                                                                                                           \
        return boost::proto::detail::apply_transform<transform_type(Expr const &, State const &, Data const &)>()(e, s, d); \
    }                                                                                                           \
    /**/

#endif

    #define BOOST_PROTO_TRANSFORM(PrimitiveTransform)                                                           \
        BOOST_PROTO_TRANSFORM_(PrimitiveTransform, void)                                                        \
        /**/

    namespace detail
    {
        template<typename Sig>
        struct apply_transform;

        template<typename PrimitiveTransform, typename Expr>
        struct apply_transform<PrimitiveTransform(Expr)>
          : PrimitiveTransform::template impl<Expr, empty_state, empty_env>
        {};

        template<typename PrimitiveTransform, typename Expr, typename State>
        struct apply_transform<PrimitiveTransform(Expr, State)>
          : PrimitiveTransform::template impl<Expr, State, empty_env>
        {};

        template<typename PrimitiveTransform, typename Expr, typename State, typename Data>
        struct apply_transform<PrimitiveTransform(Expr, State, Data)>
          : PrimitiveTransform::template impl<Expr, State, Data>
        {};
    }

    template<typename PrimitiveTransform, typename X>
    struct transform
    {
        BOOST_PROTO_TRANSFORM_(PrimitiveTransform, X)
    };

    template<typename Expr, typename State, typename Data>
    struct transform_impl
    {
        typedef Expr const expr;
        typedef Expr const &expr_param;
        typedef State const state;
        typedef State const &state_param;
        typedef Data const data;
        typedef Data const &data_param;
    };

    template<typename Expr, typename State, typename Data>
    struct transform_impl<Expr &, State, Data>
    {
        typedef Expr expr;
        typedef Expr &expr_param;
        typedef State const state;
        typedef State const &state_param;
        typedef Data const data;
        typedef Data const &data_param;
    };

    template<typename Expr, typename State, typename Data>
    struct transform_impl<Expr, State &, Data>
    {
        typedef Expr const expr;
        typedef Expr const &expr_param;
        typedef State state;
        typedef State &state_param;
        typedef Data const data;
        typedef Data const &data_param;
    };

    template<typename Expr, typename State, typename Data>
    struct transform_impl<Expr, State, Data &>
    {
        typedef Expr const expr;
        typedef Expr const &expr_param;
        typedef State const state;
        typedef State const &state_param;
        typedef Data data;
        typedef Data &data_param;
    };

    template<typename Expr, typename State, typename Data>
    struct transform_impl<Expr &, State &, Data>
    {
        typedef Expr expr;
        typedef Expr &expr_param;
        typedef State state;
        typedef State &state_param;
        typedef Data const data;
        typedef Data const &data_param;
    };

    template<typename Expr, typename State, typename Data>
    struct transform_impl<Expr &, State, Data &>
    {
        typedef Expr expr;
        typedef Expr &expr_param;
        typedef State const state;
        typedef State const &state_param;
        typedef Data data;
        typedef Data &data_param;
    };

    template<typename Expr, typename State, typename Data>
    struct transform_impl<Expr, State &, Data &>
    {
        typedef Expr const expr;
        typedef Expr const &expr_param;
        typedef State state;
        typedef State &state_param;
        typedef Data data;
        typedef Data &data_param;
    };

    template<typename Expr, typename State, typename Data>
    struct transform_impl<Expr &, State &, Data &>
    {
        typedef Expr expr;
        typedef Expr &expr_param;
        typedef State state;
        typedef State &state_param;
        typedef Data data;
        typedef Data &data_param;
    };

}} // namespace boost::proto

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* impl.hpp
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
*/