/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_10262014_0537
#define FUSION_LIST_10262014_0537

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/list_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/list/detail/cpp03/list.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <utility>
#include <boost/fusion/container/list/detail/list_to_cons.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    template <>
    struct list<>
        : detail::list_to_cons<>::type
    {
    private:
        typedef detail::list_to_cons<> list_to_cons;
        typedef list_to_cons::type inherited_type;

    public:
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list()
            : inherited_type() {}

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        list(Sequence const& rhs)
            : inherited_type(rhs) {}

        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list&
        operator=(Sequence const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }
#else
        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        list(Sequence&& rhs)
            : inherited_type(std::forward<Sequence>(rhs)) {}

        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list&
        operator=(Sequence&& rhs)
        {
            inherited_type::operator=(std::forward<Sequence>(rhs));
            return *this;
        }
#endif
    };

    template <typename ...T>
    struct list
        : detail::list_to_cons<T...>::type
    {
    private:
        typedef detail::list_to_cons<T...> list_to_cons;
        typedef typename list_to_cons::type inherited_type;

    public:
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list()
            : inherited_type() {}

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        list(Sequence const& rhs)
            : inherited_type(rhs) {}
#else
        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        list(Sequence&& rhs)
            : inherited_type(std::forward<Sequence>(rhs)) {}
#endif

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit
        list(typename detail::call_param<T>::type ...args)
            : inherited_type(list_to_cons::call(args...)) {}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list&
        operator=(Sequence const& rhs)
        {
            inherited_type::operator=(rhs);
            return *this;
        }
#else
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        list&
        operator=(Sequence&& rhs)
        {
            inherited_type::operator=(std::forward<Sequence>(rhs));
            return *this;
        }
#endif
    };
}}

#endif
#endif

/* list.hpp
WTZOJVtPC2u1i17g9Sxlacm6aQK/P0MY+wYL95cL+9yiXuV0LhLeexouvK+xjsVoGOfeP9D5t0Vr7O7XblTWB/d6M3uySdgnOfBtXn9XIc3XDcOtqYLOBgvrd+2F2CqAzS9hDBR+S/VLHs7rOTuC13N1hJIf2/+U7/h4/c63XE/XCukh31L8T5U4H0YLPtVZYT/DpVGc/7YUgQZhrqMmhecpz+J9mdqf879E0OtVBp4eLuDzbCK/f0SI7xKM/L4sxBEjhfG9P/M9koX9wJHWCcI6hZeAgRohfo+ay+vXCPvtxxfwdLmwnsXnh2OtI4W1hpJhdrK7vZ7LYpmQPrxOkAu5j+e3wz6k6xeH+nE6t7J0kjVhJO/v8JGc58NH875MEPZHjRTe++srxLNbewjjyJM83akv79fwRH5/ueBjl47meWzC2kc5mwcgtvSoivi37QWf/7TgM08V3jNqce22aDMPf0L3fA4W5iGXP8tjH74nDY0R+/l62VZxbXq3N5v34+vvsdauwrjf3cz7dWI0L7tXmCv4UlhXPTuE57k6ROkvXiNTl15j8v39ayxTbJMrvuGy3vc1nf+pZGN6ivUEe38wwzphBJfpVGHtbDRLJ1vl5/j9GQI/U4X5nOUxvI+Tn+L5++o5/RsEf2y2oIMrBJ98sWBjuS+NfMJxSt9xfKTaQPsVJfghp8XYU9DH2cL7dwOjuEyDJ/E1rEUm
*/