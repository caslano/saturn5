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
JYyfdM+XwG/XzB9Pw2/VzB9Px6/VzB+fil+hmT82Sj1GywTlv6X5vgXuUVz2f9Pw75T9kf3flvi3mueP1eODFZf3p2aU0X/Q5F8mvlpXPvELdOUTP09XPvGluvKJR3XlE9e1P/V4eWry+pcbjM+PJ+2/hFhc2UIZn8rjtxBvZrly/NKs6y94ivAH8RZmampw+me2y+P3Qojxn6G4OH61Czk+qcnvv7oBX5BKPirO/Jc9Pr0RLxN+zAzn+t2tuF/4ctw6PnfjcxWX81+Z1R4jE0+2fn8S7qV+T/Q6vn2+M74/ETeE91rgtP+T8Z8x1aO41f5PwX8U/g5uX5/j5ubtmvVHk/FX8XTFv5jntF9T8HrF5f3T2UuZ/1bH5/L5JXgXPFVxdX53Nr7bUFzM787B/624nN+di3+nuKw/IR6ekZuipE9c/1iCd8LTFFefX7AUb6+4fH7B2XgbxeX61XPw1qrL5xfUcv5Q2lc5f7AWv0px2X4+gK9SXLafD+KXa9rvvLM9xpGa66/T8BzN9dfp+BDN9dfT8T6a669FeHfN9dcV+OeArF+DzfT9Ef+exuq6DMVLab/R+LHC/yU8rYwyZr5bh38q/HQ8zUzNBny78Odwu326jP6L5vljF+Pn4amKf3WMU/7fxnOEDx7p7O07+BDhZ5U4sXl+T/st/APcbp9WML7T3R+IRzTj8zo8T3P94W58hCf59aV78OF4sutL9+LD8GTXl+7Dh+LJri/tXMX1kRaN0zfMTF+n1dRfPD/V8V1FzvmhM95W+FC/c37ogzcTfgFupa8vniJ8J26X32u5/pOSfP3JtfgO9i9X8SN8Tvquw7cJL8Wt9F2Pvy/8Mdxaf3In/qrwbkXK/BQPb7oTT3Z8F+CL8c6K9z3UOb7leLXw1mc4x7cCjwrPx638C+Jh4U/idv+Nh0+t1aw/r8d3munvm6B934p/iKcqzvnHbt+34e8pLtcPb8e3Ki7XD+/A31Zd9t9u8RiFLZIf/5fwT9i+WPHCAuf4v4z/XXgdbh3/t/B3hH+DW+nbgm8RPrtQaR/udtanZCS4vzkLr9TcfzsEr9Dcf1uHr/Zq2g/8IE35ugdP15Sve/FWmvJ1H56mKV+593H9TUmffH5QCR7AO2c4Hsh30leK+4XfjlvpK8N9wnfjVvrm4wXCi09XcnOtxzhUMz7NxAexvSz/x5s+Af8nP9NTHT/tVOIz038y/pnwP+AZ1vgP3yH8S9w6Pxbgbws/9TQn/ZMeiF/fT+p5D+Jm+jMT3D85C/8X26te1dG5/28u/qXwRT2c+/8K8U8Ul/P3AXyH6nL+fh3jEzzZ/U8L8K54quLq/QnleAfFZftSgbdTXLYvQTxDcdm+rODm0oma5ydcjo/XPD9hW9w199/j43T33+NjNPU/+xF9+Dm4LvyhuC78WlwX/tm4LvxzcF349fidisvxdatHGX+bv+N2+2XPL+LzhftxK/x0vFT4QzjSsH94H039X4OfbyS4P9Wlr8drzN9T5fMHXXjuY6w/MOtH5wT1YzL+R1w8X8+uH1PwOxSX68um4rcpLteXnYTfgid5vh47wPqp5o3Hf0PN9A3FP2tGPVJ88Gzl+jHeOWVPr8Cto/E53lH4Rtw6fjvxtsIPn+OkL3sT7VOHxsd3gZmCE/DrKMyjPI7fyPazzPSNx68W/gE+03x3DT5W+NC5Tv5di48WfjVu9w+4ef+QFKX9k/NjeBqeqrg6P5aNe3HZ/qWaseXghnA/nmLNj+E/eJO3f7l0vvKaJ+9fTMY/5vhOUXz5TKX84R8JfxG3yx/+ofAus5Tyh28XfhZut88fUL/xZOm7Fm+uWb91Hf6LN/n6revxn/Bk67c=
*/