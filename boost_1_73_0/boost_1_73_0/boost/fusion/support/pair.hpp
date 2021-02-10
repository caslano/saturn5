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
XZDiaZjRhLFrrFptfAjzPrL6iSKHDQInny0DpvfhXRebJzNWsu32Q40apQbeWIxPd6rDRuTQZBYFYXyQg99UAiEn0o6hKvp/B8Gldz80iZtxdQ4t4D62OD497V/+4q3ozuOptHzbfXt59aFoGXJQtVjUjfsEk0WOUbX/5bve2eVFv/fr2UmX+6Mt4fl1IYp8EQ7ZguFbhF4BRG6YkoQEKp5HUaEsi8BCQzgBeTdrDkeMggIgJTfT+HwVYO8vfrm4/PXCjJFIitU8voVFPLZDRKpQ+Cudzy5OLt++O+/2upKSLJkK7qIxTDDegEYNrG8L7W6aJml7jYFVAkbgZ8UIbqCd17sGHCJJzjMHY1H68RCAlr8irFMa4/l59/XxeR+D5h+UYVAYRfoGllInA8gfDIDCS1pfvkHEnP3nLaslw2SkC79hoxBG2QtujGU0dPsY9Hmrgi5J1uQph2nGPlYH/PN5WrhcHfaiwd1if1Ipb0TscfWt61tSeWwOKwwgZ8cf95bG1bXQmkMvJZRIhZlA/lHujQ0ypjYTfRkzzXJBJr1Dt5QfpBiHHKfJtJAH9D23yHGlg5sQfTucUA09wHcbROCD5JMgRwHrXb3vqqkO8PwIHy30boqLbUprUhDzrDBY00DdJDgfWcbHSXPw
*/