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