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
LUf7GL1adTyqbnrV2rPlF5pubwiE8iZqXeBsaAZ42qMqMP/hvpTnPKipHzS3Q/1YrapR2iy+iX8PIUinP9HfpjibbdoLpb7b66LA4MzmcwXrEL4JdSB6vWPva1AzwX6UmcBDYwvjtr05fSVjcwNtjYiPI4bymWR/qmdgsNifbub9gC5/A8BeZTOmTy6MV6RtvP/x+fHKGUJP7/lK8xmXY1qSZVgRoWWffNvC+OPAfuAgfJ89uN8C7AAOrO6Ib8W9BhSAFcAyoB049FaUAfYBth+1G8/bgOuBzUAF6AWWAfOAwzOwKcBeYBcwBVwJ9AAXAcuBduCZ60ATaJk3pyN+EM/7gX3ATuBwDT4S7jWgB1gDLAEObFkYfxDYCVhABVgPpIFlQBvwzFuQD9gL3A7sAgpo5wbcK7hvxn057hXct+G+HvcExQHtwMHNoAXYQXzCfSeF4Qtej3sFyAErgThw+M3oK7AHuAXYjnwbgO14ngF0YD3QCySAFcBSgAHno/6D1y50/Mzlbwc/EXcEWIJnBtjth8sr3JCCxj/EaJKxwWyqJ5POFiLew+Z5Zkm35d2zhdRcfsD/3cz+d7p2+N9+P9+xtTfeE/o+UdQ7Bu77TE4/xa8DOA6mR4dv2Cr8hGOf473KqFyfTL0LssKEz/H7JQvc85N73fOACB1gq2lH0fvyDaol+kEdr6cTqrdFPttTCt3r9Z3l9WhjFZ1+l0I1w96p9eUFy6plhX7zgn4WxXHY3t3F2N8C/wd4F7ANeAL4BfBT4GfAz4EfAz8Bfgj8CDjQdextNfXTm5f/eB7PVj9qH9y8x5qvHvVuY9C+zybbtDg21bKjfCNkQO7BcrcofN0lf87SPugP1iN/HkQT70gIeQ7NQ1IGz0fsLIXbJk++8HehPDuuRzmrEPvUnsQoO0g9n9Wee/LKV0/rx5rf/vHSY80v9xiD2VnuNuhfJubyx766wD2z+4fQ898/z7lK6J6q0airEe/4DuepG0KSpIMd1U+ecTY/iXxQamqWPOv572cNZNMJ/wmKTwacPEj4ImwwE9flP3R5uGRfiO/Bf9VEyFQC5bYzwfupgx79uk/o14g++hZEs+TxvXDhyzeUpSkVei6U4j+u7HJ6NtnmWUN8cW77YF1T62i9Ev6Nq/tOSrKrJ9iOeNct/LsB25ePODMTbQ/0DgxGfFsbKLzyfvgZ8txn87KTnHOfRwJj59jdkHfGHJoC/nXP/f9Z29tcSyjPLr00lAZPHW75hxfaZ/ps9IKTHBnbfN/i+BTS2kXf2cUXun1/C9I2IO2gLPcFT9oWpPUgbb88P5/zhpOcva/rkLYGac+cLPj50amTHD985r5Z9mo9h+S+PE6GfmVSG6NffgqXZydfj0YHx9NR6zwnn3+gjkZX2PmJL99sabPpIjFgQ9Wy4Thd4WNKWVx6H/2Ju9Z5+D0nxVdeIHj8TAiP/XuP7oInmC+w1GU3PrWQfy9PY7zqppOcd8Qq98t3xZhYu5Esn8jEu0ULmPh2hv6aNfm59C3NEuA0gPaY6B3ElQDpyhnUL99BY7s89Wv3R76LEFz+R+kmyke/MxaVd4jriNzgQC6XXJvpHugviI8NInWdbZuPwf7QDwCG+heUx78/mqzXtbHws56UqusDo1eHyYPY49FK41H7En32ep/nPKo/IVxTsxyeO6r9o7yXwF8U9SjoQDr/CSnN9ubF1f+LxJc+e+pX0+dQHuBwz+L4HQ8eHdfJ6wjy73kwGiwr33WRV2MHY/Udbph+eZ0ukkeS25hEq7zTnjHJMr1/NB84ngn5n8OE7LfL+1x5P0GmnehJo3rnyzu9v031xmUc2YhTJCj+dBn/OhlOynBKhnOyzKCMz8t7UdZ/uWxbl/ETwDKgxsRcNJmglfpB+WeYoPmt8v42mf52mX69rOe9wNmM/naNCH+MCXp2yfZulvFfZIK+h2X692X6kjmCFzbP7KuuVT0hxkr0U/re9GtMyw39d1/xyEukL4u8Zq32L+ZSRktldeNYRbt6XJ+oGrVrzLrVmNw0NX2tSE92pdKZ7rU92UvX9fb1D+QuG8wXhoaL6y+/YvZ6/5Ku/+0yIK+/cFFYtg5rqVhb+y4o8g1vm37b6TL+kz8W9499Qtzf+vcHjtA9sWWG33cj/70ff+zjy4IVyuutfxT3hLzfeYz5k/L+BeT/1k1P3HQa+/lNT970xsj8iS0f40+XwfBc9thVjy1jI49d/diq5vzfffRHB/7A2LlbREk6dyVb8cxxi+KHgIPAk8ATwAHgceAR4CFgH7AHuAXYBewAbgC2A9uArcD1wAywGZgCLKAG6EAF2AAUgF4gLfNfBJwPrACWAUuAeQADjrQtih8GDgKPAg8Bc9uE/aVrH8J7gTuAW4BdwI3ADcD1gAWUgRxwEbACWALEgXaAUf2t6DvwJHAAeBTYDzwI3APsAXYDNwBbgc0yfw0oAwUgAawElgLtAAMOx8BHYC+wOyb8GpvuP/eVzvn9lj81bO/b+i6Pb/RoEmPZDX6tXRTvQdnbLxOgeWS/A/h4ahF/njnBLvWfvw7PwbgAXr+QfidSdX4SwvNjkbi+qp0cPxbY+Ttf7G/P7rcXMSYumx9BvhxrfFR6MHy0/FHp/z9cMzVB16Hfit/fyeULRykx+5VL/2nldxYWxw8UhEzaccHnlzL6W6WMkSWaAj7I6O/nMvYIo79eB/8UHVoJ9AMTLW6ZC5nwnzcBHwDuAL4LPM3ob6DRL4zT3weGb+0ZqM7F7jNdtP5NzF0UfwnuadxpDXw+7iSWa3B/Ge65CxbFO3Dvwf10yo87raFXIJ186OW40zphIe4k2GuQTuuPlbgTnYfbF8VpvfAM7stwP4Q7962Rn3ztNtwX4X4W8pPPfwTpp+K+DGHyzZfgTmuaOO7k47fjzruB+xmUf82i+MupHdxp7f4M7mfifhD3V+B+YI2Yu2j5OnE/LDXEb2TYmY4z9j2eduR7hjYDbBbu/Gehg+je4p0APu0lLpq3s80Re+321+uv1/+Wq+UoVyxwtcrLX4s9j4Uf8BjsPM0z2o8Jzrdlx73/VDfE2A2kEMh/O/LCC7Rn8R/cPQt0VEWW1Z1AGowkICONIHkEolGh04GEJBDoTgifOEGyBBRxWOh0N6SH/OzukODgpANo4iiCDCqz6wdmFFnX8TNnR1mXkVZRYQ8K/sYcfxMVhVmPTmadPUYN9N5b91W/T7/XCQ6cmTPVuV1Vt27dqrp169at6s5rtD9ugFgKLf4OsApoa/DMLwFgQ+ijxhnstrrlFGOHhyjpb23xtPu+9Hi6+sWMeHryX0aJdOSeXReLtHTgubGUTj14ZNydBZje88XR18a98OY1bqn3gd82X7Xv1y/dH3AfX3k659NL7lw89vPN7hvveefuuSOGbL3iiQfc3xzcXfFFx6htHZv+032w9O29x2KVWW0vvOluernnjj9Gjix49uf7yg7csm7Z5SVbv27u2Vh+4IM7P/zm/u8+/+mj/zR3z2frPzn6v1fkbem4rCI3c8yjfY9nfvLSoW8rPn/kra++/vyjq2+6+9g8/9FX7hqx9/HdYz/51fwL/WPSWzpubVl/ZOGi5eUnHvl5yazC/b/5ombRI5+unP3Sylm3P7BjRWzl3t49UnTpw3cUeV4/ffuK27tzVt72zXtrH72776vLD/7y8MoPIo1VR/71Xuln1iWrD+W04NBfPfrqUQrfuW6cPfydXzXjW59rhW/WHxZvvbdx1Ob/c7345hT/2I+Xj3nm9T+7jmdM2rJg3ILHXnrkS5d779OB+ieG/K7o1s9d02cfKL/p07d3Hvz9SdcLp0+/5tkysvXov59w5VXd8NGiQ8/tvPuzI64dh2pmtVS8Ovq5f3nC9eHaZ3eWzPv1hKeO7XRNnvTyxweenZXvuf0ml2fZ9c//9KmajaP+a5XrnS/ztg59bsctP/iuwjXZ9fAfSx6+/H/a913puvmxPScO+DbOP/7Bsjnenww9Omlp6+bYXR2z7/p25tibvDlz86OPlU687fXiTQvu3c9OvzPr/a7ltnFPnfrk1r0ps17eMq887elftBS955g5/cbxb0x6b9qXldtXlOztfC563bsPb9r7y99O+7juNyMfWfJgxfXPZE7JqTwxdUbB4prHX1uXs+361IeiH75w83enXp7wwMmuFdfdVXqwenO2/Zof+mtPb972xNCdN488MfXDB19743DqB3u7Nd6v2o+tb1ob8Gof064t5z8Abf4c96aW8KqmNauC+Ku0ohx3VTXNqqomb6ChWfekfi0f3sAqr/jfA0OaVQv8jf6g6G4isYa2Un7GvQmxhpb+c9CMLZtyHfgsAEsBKgDa5Hz9dWRzhHDxd/6C+JUOKdd7hZRfUjJt6jSns0Cq3SBVO652SNX1npa1/uAUqZ5+GcGHJRWBxnUtDa2eoH+KVBX2OaSyqippSeWChUtrpCXzauYtuXYev2iGUHAD+EYADKB3BZyJAaIADwFsB9gIUAewFMAJMB7ABtB/PZxdAd4HOA4QBXgSYDfAdoCNAD8CWAgwWaYdDdC/HNIAbwEcAtgPsA9g53KiaZNjH8TVAAUAEoBNxl+lm5OlNfwb3Ul/80GmGcxvR/BHafmD+ONGpjRJyw2fV88/02jwmf3vJz43lp6iaFxW1mzwLF36kKOMP8hSJtDovu4cqT9n8t8Q0J0x/x5DKn9P4/vvQtjf0K/thhjPAX0Q4/293cIi6PdvhxgHabeyCO61TqvyvBnik0l8rMRnNcToALRBzP/HxEp891mJbxRi/AyjG2Lct3shxs8EbCmMH/0liHGfL06h9qshxnNLHcR4jgHmETy/7Eqhfj2Zou+PlY3aANs94EdD3GNQboGDWx/ygzgzVV9+IbNAA7mAt0LshjgF4uUQj4S4GeJREHdBfBHEuyEeDfF+iMdCfBziSyA+BfE47OgQFhkPsR3iSyF2QpwH8cIh+nYzmAX6uxrwF0PcBvEYiLdDbId4H8RjIY5CfAnE3RCPg7gX+UNsGwr8IZYgngBxMcRZEFdDLEFcB/HEDXxyI9kQ74J4EsRPDtX3w8Ln87ABHue3xwCPd2x9Q2WkDm9Lk5E6vN0En2uCLzbBLzTBLzfB15ng20zwXSb4XSb4fSb4/Sb4wyb4bhP8KRN8nwnepvpATCN/E3yuCb7YBL/QBL/cBF9ngm8zwXeZ4HeZ4PeZ4Peb4A+b4LtN8KdM8H0meNswGanD203wuSb4YhP8QhP8chN8nQm+zQTfZYLfZYLfZ4Lfb4I/bILvNsGfMsH3meBtsKnYvx3D8PtYJ6iAVX03ht+/iTzr15YXnNbm685o8/fFtPnjzK7Jp1q1+eIUbb4+VZvfPUSbf2uoNm+zafOlw7T55uHa/EMXaPPd6Xa2nyn57RfaWYW6vRF2hs+0EfkDGVBfle+F/CZVPpxpZ1eq8rshv0XFb/IoO/ssVcmnj7Ezn1XV37F29q4qXzXezn6m4tcN+cdU+S2X2tmHqrxvgp3tU/OfZGe5Kn4FOXY2RUW/GvKlQ1Tzd6Wd4V2kyEchP1qVf0uXP6XL9+vymVdp85N1+WJdvkqXX63Lh3X5Ll3+Pl3+SV3+kC7fDXlnipK35dnZKpW8rPDKhVhidL9CHgBPGAb1FYtpKGb0xaxmgNUAPQBRxkYCjI0wloXQDxDVAeKBFO+i8X6Z3yVrOfMgPjeKnUlLhM0xAiukh6bFzgC8NiItdgggOiElFs2yxKKWCEC0PWrpcUUtvQQM0oy5ohJrjzazWLTPEnu+PyX2IrB6BeBYvNFYDGWEMsO+SUyRWcSgr3J/WRoUpoKDveUwY0fA8f438D93QLwZ8hEfwBuMdVwB+RLGbgF2XbDotm+E9cW46FhfO+3z6Ks4O6FtAAsA/1IQOt0TWVxY6KulAY+MzSBPmC5XDD3M0ed+nvk/k0fwMVQEmJZvAC2xM4x7jRFQNDdskBJ0Dj9V0NElCyqRG4d+gL72WKzXRYDpfl6CrXOIsZRYLAK6EM2IxXqyEuiShUxmO/cyE8ESgYlygywkkAnKBmWEskKZWZBZIh0CphFnEgYaUzycaQcZuEAWWSATlA3KCGWFMmMEejoETCPOJAxnI86PzPgX5yI0fqsEADKrBZntSGWW4VYOmOY4LOM0bqozgK6ZDkYdUF/622n8/VkAILP7QGbpKbEzqRYOmOY4LOM0LrlOEr4QfnC+ZMZ1JyKvUQB8yoF0BzSyA3RsDwGmEZcp0yAt1kmiYxiSj0gOXHfa5TUK0AMQDYGOeWAEbgJMI65HpumT6yTRMQzpbNT5kRkG3HgmpzNWDjtp+WRIVwBuC/AG/bICpALYUvkFAl+zrv541WQh6YDU4STAi1/FYh2fAMAO9CJsaCdBt84AwJ4U6wPoBehJoTWLMIgw+nzKDIXmBFnlloO8ALIhPRFwUgTADSDRHiDJdu5cywyFdgxk9UoHyAvgeUhHARdtB3ABZNEeEJXt3CBlls4uOH8yQxlIsh6hPqFeoX6hnqG+od6h/qEeoj7alarJwkBjigchB9Qj1CfUK9Qv1DPUN9Q71D/UQ9THk0rVZOEiNvz8yQxDex/5FG7QJ7cE4AaI0Jeay8HxrADHaiHIrxpgNaS5M5o8DDQmTUB/ggPoUyQLwAXQDgBlHeApbu6MxTpBftsAHoS0xns0DpngoRnJLGLeX5MSVXCCzlTDIXj7MGbJtEWsmTZ36sguyTZqYWbm6FwbAqYRh2VIg7S8DtYdIAw0ptgx0Jltf47FMnpjZzJ62/szel19I5qzetOdGT22zDQETCMOy5AGaXkdrDtAMJPZoPXsXPhgSIO0WIevZRvxMvHVNAM4Fz6YoMM6fC2nES89nRwyzpfM0JZFU5jFbY1Y3VZ3atkmyVZenplZkW1DwDTisAxpkFaxf+dAZgiu/tgZV397v6vf1TdnY1ZvaWlGT/H4NARMIw7LkAZpFfuXXGZ/tZ79DYJmAGbhT18nrtERza6+dGcWAqYT1iTWGUT4h5FZsjWqp9HrziDXpAj/0DLDcPC0skbnbHT1lZZmIWA6viaRBsMgZYbyEv8fZZFvf6tNexuhDTUSoQhfiIK3aDQKmBj/Q4vKI3yREWa2LghAq8Stra0YA6TxOBajWIYEeopFwH5PZPS9JtHv95lZiBj2G/uMfU/W7y5dQOptKLgufOvrbKVhCFwvx3VqcCwDcG1dalwvMO/r7OrqVONgawEcEKpwsV7W19nZ2tWpaZdhu21aXC/vixan6p/ROA6xwxixIWwYu4Q9w+Zjhl3D/Pybtja2iNXAWqphdYCph5fEKuCd/i+PyWoyFGr/BGixtU3sMrm2xAksbI9Mk8FuZvnMB1SbGQVYm7zsNijNhfO7Bbdgtpj9UHCPl4/h5VZePpd5WCPz8v7o6a7idPM/QrrL2EJO08wpDsvjZJpxJh9hKvSlmf/yYhqUe9h6SEvgIIdgLGUy7XwWgNgPOAnavpI5AK4Arsv47zUGALDUx9vK4D2XWAu8N0K6gZdIbI3MIzFUl+HM4EgCQGlEoaadAJJvAn5+FoRXE4DE2wjBywMjwt4HeE9xLB7eqofV8rYdbBKMKQwvP9Rp5rGPU4oeh+C9GV5N/BcpqbSJyycIVDjWJqBysMnAR+K/THkj1AjwlE/GhICmBVI4exLoiIf3poVLI7FHI0D+LcAZ21kjj6WBt78BSidAO6Jv6wCagB/m1aOvk1togha9vGXqjQPsxjyuRU28fpjXUo84wKWAfGiEiA+CDFviv8Upf1lJFy5ilTJfasvL+y9mWMy6A46h8+XxUqthPnPUGrbv431Wt2ZcA2eW9DKxxkUqrfVyWTRyLQjFa+fAinQxyZCzl/cfZxbrC63YYNjSBLaUrx9lpELTkBdyw3kNyjqoHasD1uNcPg/1vHWcSZRZCN7p108lPhMB3pbEfgzltVDrYsNeYzs4ozheSV7TzUA9js8LzTPOAq5dD9fneuDhVWmwWoMcsGaxbw3wQunRalVadcBaR764NtbwsXsBSCpafRX9I21aw7ENcSloV1A1zNsGPn4/p8F5WMvlGZZ5UQtB3hZKGeeW5rmW+RlpUJBR64gXek1yopmqBGtRqZmxXEitkSk3wMiUFYq2B2lo3TtYObc0YU5LdpBWqOAdOsv+58rrVd8n6gOtTf2IHDD/qHWkZ7RW13JJijYV+0OaqNfQHMBP4S0gF9IYMWKhhThTLbLkSDvC8TbVo3RAbN4bwqKmoa1S66voVQOnCXGKtVxCbXFbSz2VeJnZOBwQK+2jtnp5rlHm7uFyV/REWDmyVbi2SQPJ9kqcKsj7Q6Om+aWWcK8Zye0nrSc1N8Ss5VhcO1oalCpajVq5fNKAPEifw1wHSKvRYim6nMOmxW25WTvfh0cjnxtau2SxyHqKumRNcXa9ch2USyasW1onZPWxJ7V8BwszWtnfZ8ROVV+nsUJ4OdjYhBGjruBs4RzSDOtnI7GOjwnrTvzz5FWIPGiX0s8yjlzsoqg5uA9fmECzALyfSvCijMoU3olloj9iZx3DvShaCSRTrb9EqzPItRt3ocV8dobLHqKyglESwvLR+hAcHEB9Le8BWj6y0nWcm7LO9Hs5rRS0FcqOIPoj9nfyFjBGu4fzgbOfBTJBWxTmPVLvOD7er3U8FZRrCKuxhu+M9VC/kMtD+EfCgtAuTf1Aq4P2BuUwhXMIx/mI/ZZkWMtHG+L0ft4L2uXrAYdyKTNsq5X3jnRG8SD0LYkeTeV863lLpFln14f8AXy0FmakHWr/jyw7jUD0SlhY7Pm5bkPIR9tGYqguy+JlMxnZn+Hcy6ATA9ou6i+dEwSvEPfIAtwLc4H3U8GlTdpIexf2Ez3rZiY0i/jnG/RA3RezkkkD6JuiDeqZVnvNYW4hjPmodclIYxL5mPepHt6pT2gLcDb0Poj29IL+4CITygpWBS+hyyh9PJng3k3nBrTxtO4VDmqfUPHMBZ32DGZ8bqBQXTbK4AyXeHqZOoizj76WVlM9vJT6pdXWkfIeZ+4Job8v9kHSWg/nQSdLtV9hZDcdrNjQ31fOPsS7ltdEbz7EaKbrGK1OxbqK0wV552RnBBdhlXFntoO8lPGqbZfWx8XVRhJ2yhI2Goli78kr8MVXP3Hy8FZQ/gFGOxpJP8Bo3yA5G0tB7eOaSUJta5VdStk=
*/