/*=============================================================================
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef PHOENIX_BIND_BIND_MEMBER_FUNCTION_HPP
#define PHOENIX_BIND_BIND_MEMBER_FUNCTION_HPP

#include <boost/phoenix/core/limits.hpp>

#if defined(BOOST_PHOENIX_NO_VARIADIC_BIND)
# include <boost/phoenix/bind/detail/cpp03/bind_member_function.hpp>
#else

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/reference.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>

namespace boost { namespace phoenix
{
    namespace detail
    {
        template <typename RT, typename FP>
        struct member_function_ptr
        {
            typedef RT result_type;

            member_function_ptr(FP fp_)
                : fp(fp_) {}

            template <typename Class, typename... A>
            result_type operator()(Class& obj, A&... a) const
            {
                BOOST_PROTO_USE_GET_POINTER();

                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a...);
            }

            template <typename Class, typename... A>
            result_type operator()(Class* obj, A&... a) const
            {
                return (obj->*fp)(a...);
            }

            bool operator==(member_function_ptr const& rhs) const
            {
                return fp == rhs.fp;
            }

            template <int M, typename RhsRT, typename RhsFP>
            bool operator==(member_function_ptr<RhsRT, RhsFP> const& /*rhs*/) const
            {
                return false;
            }

            FP fp;
        };
    } // namespace boost::phoenix::detail

    template <typename RT, typename ClassT, typename... T, typename ClassA, typename... A>
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<RT, RT(ClassT::*)(T...)>
      , ClassA
      , A...
    >::type const
    bind(RT (ClassT::*f)(T...), ClassA const & obj, A const&... a)
    {
        typedef detail::member_function_ptr<RT, RT (ClassT::*)(T...)> fp_type;
        return detail::expression::function_eval<fp_type, ClassA, A...>::make(fp_type(f), obj, a...);
    }

    template <typename RT, typename ClassT, typename... T, typename ClassA, typename... A>
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<RT, RT (ClassT::*)(T...) const>
      , ClassA
      , A...
    >::type const
    bind(RT (ClassT::*f)(T...) const, ClassA const & obj, A const&... a)
    {
        typedef detail::member_function_ptr<RT, RT(ClassT::*)(T...) const> fp_type;
        return detail::expression::function_eval<fp_type, ClassA, A...>::make(fp_type(f), obj, a...);
    }

    template <typename RT, typename ClassT, typename... T, typename... A>
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<RT, RT(ClassT::*)(T...)>
      , ClassT
      , A...
    >::type const
    bind(RT (ClassT::*f)(T...), ClassT & obj, A const&... a)
    {
        typedef detail::member_function_ptr<RT, RT(ClassT::*)(T...)> fp_type;
        return detail::expression::function_eval<fp_type, ClassT, A...>::make(fp_type(f), obj, a...);
    }

    template <typename RT, typename ClassT, typename... T, typename... A>
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<RT, RT(ClassT::*)(T...) const>
      , ClassT
      , A...
    >::type const
    bind(RT (ClassT::*f)(T...) const, ClassT const& obj, A const&... a)
    {
        typedef detail::member_function_ptr<RT, RT(ClassT::*)(T...) const> fp_type;
        return detail::expression::function_eval<fp_type, ClassT, A...>::make(fp_type(f), obj, a...);
    }
}} // namespace boost::phoenix

#endif
#endif

/* bind_member_function.hpp
/rtStUtpuDHdp3ZLfRnvdl9ZZ851HirHPYAJl8Ou19X35XrDbdIdrk/6gwO6aLaw7/FDgMlloSJ9A0+FIOa+3bogrRDdbrPHgB5ud8KQfN0hHiQ/tcMW0LkdqAoo7RNE2UglrHZKgy51mzII1WMpXNf97n2FOtW1s641ee2icmQyGHOa2Vx/pq/kKW8Ep76fAZyrx24/GgRG6E2ppz/o2y23LiiZ0qHngFZvwKMHOpAnmTtu2zu+mAcDerYE7xx/BHXuezzflqOee0rQz2aj6zVUjpcDZ0CZkcnRoZaf76vvG+7rVNt+upNmHHnyjlQ1cKBR319vy9PfUwrKcTSkB7YeviOg2ywdf/XjEqPoTl29360r567sh2Lbn/KhOv2s27Y7A18cD99T/aoegzr6cqhf2OPT50EPZxbI+k1Rv9AH6Ipdv+Ogc0F8ffe/f8+WLYv69b9/X7ZjIKJfrxci+7ct59+AcRVF68dX0c6y0+n++I9wfwz5of3rvtFzknvP5L/A7cC9g6BvBPWzeJVbP/aYuQx01oWwrtwbdDkWuPW7SfvywtWYpgb/+32ofpvejj6v0Z/TZbnPquiyuGVeCVz0vEOqSGW+aLVvoF8TdJde1/13gHEmfb9s91/l9iXbF30N6KH5wvHx7ALGHU9dn67fIP9QQUi2n7p9hHxXHx5qN7ufPxJ0d2xlySLHkD7ouJ92Q2S5qOjUx3tWRY97nAfdz4zSD5Kzh/yamxk8GpuZ7tQnJ/rVGrbV3xrEhmU/DkEzyBT7EXnAlf9EwPPxq9wx09ZZGOD2WO/co/4G+hordFDmzKpoO0jWaQmYsH1o6/uP7qvvzeImP6rVo35cjdAD1xbzgAmNzY4+DZDec9cJz5m/cnWmL0i7K1J+u4zNKBkcf9XhVc7474zrv7Dz3wm98nVm/6qYecEp41iojGF7bypcnyH/7XaIT7gPXAeMM2j7OvIVlKExgPNCxZl0+bmybpx6eRT5x5xYhP117T8z2KajUbWvtm/0ADZSNyYYu3Tp/NgelS9hD9xdYPFgabC0R70S/eYrBB3HTx3s/gSPR/kOPobPjcskDuKT/8+1RF9zT6bTUsrQbpY07MknBG33vSTtOTODYyz7TcuZRj5DVtpzV4Ie4+u04iqbRuKaOrxphUMPVThj566+DLaH8919Xwc7gR/o1xH91CqHjnhKzcAtypTrZasZQ+4Qhrb+WtBifLTWPMChUaF1W1fXOHTZkEJnjj7QwVEhNJ9jD3LpXAjJZ3UXcPP4hN0s6OzWwf6m5x4COqwAO3wS+3t2P5ToUU/bSz4PkzgCCD06sE7Rh4Ipo6m8t5l29JGKRukmp/2d41VEu/go0NQ+DY7pZbmLj8H3sK+bSZfdoOjgR+l0vW7diO/OrMcuN6xDJyJxM+OS10BPGMOuOcyruikKB/ccgdnaG8aQq5Ap89rNwDi3xCGS4XFbmE4suJ/dsoUwzgkzi835fepxhOXTWGTHMu/Z6tIpO9Hu1eslBskFbU7SKOmjtD49XtHmO1ZKGOytecLGHitxme6qElbr+2CT4sWSLtYdOuXsHp9IX+RzjcumUUdGpt5Gnmzjob7Y0983OD3K7XRmh40Jl4r9tnc/hbDu9rron8d3EUYeZ0hdfhrRZeQnugnaEnU9u5twscdyjD39DBsbLgPX4V3PJOy8x2KMP9508JHcuT6zewiPIFSDE1HMGXvHpMRGMeZ6XX6AsM4xkB4/O8+PpNM4y33p6Gw0DsetBjP7kmgMRjmT39KXEybySIZ15jThwkemXLYTryCMfWRn8tr6KkWPOybivLa+lnDu8ZYcC17PGOUg55+JE234DQ4N04E197yR6PI=
*/