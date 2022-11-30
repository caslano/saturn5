/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PAIR_07222005_1203)
#define FUSION_PAIR_07222005_1203

#include <boost/fusion/support/config.hpp>
#include <iosfwd>

#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    // A half runtime pair where the first type does not have data
    template <typename First, typename Second>
    struct pair
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        pair()
            : second() {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        pair(pair const& rhs)
            : second(rhs.second) {}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        pair(pair&& rhs)
            : second(BOOST_FUSION_FWD_ELEM(Second, rhs.second)) {}
#endif

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        pair(typename detail::call_param<Second>::type val)
            : second(val) {}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Second2>
        BOOST_FUSION_GPU_ENABLED
        pair(Second2&& val
          , typename boost::disable_if<is_lvalue_reference<Second2> >::type* /* dummy */ = 0
          , typename boost::enable_if<is_convertible<Second2, Second> >::type* /*dummy*/ = 0
        ) : second(BOOST_FUSION_FWD_ELEM(Second, val)) {}
#endif

        template <typename Second2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        pair(pair<First, Second2> const& rhs)
            : second(rhs.second) {}

        template <typename Second2>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        pair& operator=(pair<First, Second2> const& rhs)
        {
            second = rhs.second;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        pair& operator=(pair const& rhs)
        {
            second = rhs.second;
            return *this;
        }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        pair& operator=(pair&& rhs)
        {
            second = BOOST_FUSION_FWD_ELEM(Second, rhs.second);
            return *this;
        }
#endif

        typedef First first_type;
        typedef Second second_type;
        Second second;
    };

    namespace result_of
    {
        template<typename First, typename Second>
        struct make_pair
        {
            typedef fusion::pair<First,
                        typename detail::as_fusion_element<Second>::type> type;
        };

        template<class Pair>
        struct first
        {
            typedef typename Pair::first_type type;
        };

        template<class Pair>
        struct second
        {
            typedef typename Pair::second_type type;
        };
    }

    template <typename First, typename Second>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::make_pair<First,Second>::type
    make_pair(Second const& val)
    {
        return pair<First, typename detail::as_fusion_element<Second>::type>(val);
    }

    template <typename First, typename Second>
    inline std::ostream&
    operator<<(std::ostream& os, pair<First, Second> const& p)
    {
        os << p.second;
        return os;
    }

    template <typename First, typename Second>
    inline std::istream&
    operator>>(std::istream& is, pair<First, Second>& p)
    {
        is >> p.second;
        return is;
    }

    template <typename First, typename SecondL, typename SecondR>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    operator==(pair<First, SecondL> const& l, pair<First, SecondR> const& r)
    {
        return l.second == r.second;
    }

    template <typename First, typename SecondL, typename SecondR>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    operator!=(pair<First, SecondL> const& l, pair<First, SecondR> const& r)
    {
        return l.second != r.second;
    }

    template <typename First, typename SecondL, typename SecondR>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    operator<(pair<First, SecondL> const& l, pair<First, SecondR> const& r)
    {
        return l.second < r.second;
    }
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif

/* pair.hpp
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
*/