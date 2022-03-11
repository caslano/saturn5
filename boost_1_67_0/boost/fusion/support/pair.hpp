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