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
6rjZJmbxyrUCZFZnSk5HKDlpupcERGAju1VIfEG9HrZyo9vLC1y2c5qx721JNBxzWK12uMEEIfsGVaG/ssvsLrlZnda6r/PFt4DEt6wWSdr3CRDG/6bIj6jEt+px//4q/zAmNpYOdCvjzAxRWW+b7Xyai5yNBNKb7qPlIwtTSdrX0Dm0kmCW+apGqTgPjtI8zWx73TPLROQqoW8VdmcrA7ZV2JLtPBxd7697i67ZBtjQPUP6X9OlO9BnGkR79i2D1QNIgseZf7nYrQfMkDesvfy6ZsPafgubJ41/UZnI8Q1rnW+w+dK4G8rc9fAbqg1rD6ar5qxZI3U3rF3MZjO60mueyHPePZGYS+3N5nOpU1eVJF5mSbC9bXn8jsRSv2BGJdvtnj6peq4hm1QJfnxStWD1E50aDTB76GrgTLM1qlnjiDeItmCGodppk2o0yk9HntvN7t5d6T4Vu+6wbTU10+jqPlp/3QUac5+UEqab5VZzGtREOSxxH7P+DSthpgwq7dxHq7NQVeRz/A3ZoHJhirLE8Qotebdo7noV4Jc5rB/+nAODQ+d4vr4x9Q1ur+g/XLkBkD5toVrkoOuhlzRQL3DErzC1wFFT4baRitspxO3cZgq3MeC2DHEbwLldOpVz++3rnNsPh4HbGI2w2HqNCYsrqWw5IwzLGYz5Ej/Kyxmd0ev3O/f6F+qxXn/Xynv9slS1IY/NcuVoQ2OE
*/