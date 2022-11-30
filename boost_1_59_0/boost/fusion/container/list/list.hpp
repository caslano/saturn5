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
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
*/