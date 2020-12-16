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
PCWr4TsB1aFJ4e+ysBZOyeMRe6XEGSpNqXVCRVDPH1A9HWG5M8z6cFo95ROvqQbL9I+JTDx2geLmrC9THq7E5Rsu1DHGhb/Q2isYJY2pZnOF2bw4upheGqstNLYFefQFjBs64zpTuOrcL0bn/eRYEeXlqRkK+qKefxXxWyK8EUZwXiyel/95Sf/0vGguV3s3F/9rLpws/u1kbNHYF9cu4D4VKlmmUu2MZZ3Qrv1+dKAzoI6TSR2sE14JG06vw5d3VpAO6vgyqsMRZ3NHORUEemW9PMLsFd2QJ+WZtop5NH27+hmqQxCVmfHZM6hjznsEdn+IVxEZygwTysHYLPeM6eDA2Pyt5ecdCUWprNcaxmZaz/pi+x2G6mgYqXZsHn0R64tXmkZKJdQ51jY4Z4Athh105iLuV9NZxrJVZAkIUfyHTXF4puUW9O/xLxl0BdXliVHe1AAHZZz/Fw0c6oV5cXIRj1tMPnWdDRM5F6/rZmuuf7cm/MpnESQ3TbuKC8vWzc36fEiP2346gRwFqA5WF/vImWBQx9jbR83cJGzYKyZjZXMyOkkPMtSldj7qeH1DdWhiZPRBMY3a8Ob9zT7JxvR6RA3j9I+2Hl5t/3gXuuDPqOdFi0dQaBMaMXKu0ccnX5qMk44uOd+uFVd3qhHKwg0btY0PdZBJHdZlFQ2nTR1x++T439ZxDdXhiS291NWcCTAfzlwsOOQvQHVIkoxUnGoJdcx5b7Q26d+9rf2SXaZ4a++vf3NbpUFfDz3RSONvDzT1wN6fyOt7c+Pb0dAc7vUP1ksSOAO/5g5AA2fbsa7xDPnXBV2xxDzeKCYSl5bv2ufG8lt3LOX9N249GGz1LYY4tHcq5f/hfPxtoJmdj+HM++Q7F5r/4vv025Xuv/g+ffpdCt0ZZ98vQ9n8W/HXT8ffip3JMjHxX8dT7b8Vwb/rn219lw1V3sVMdo6PD7Af2B2e0dBdyspQJ0VHVi9M7J3v0tKtVDOxRINbVHjUk14Z6rxPS/ts3WXf1Zz1ly8v/SfR9+l3bmtuG5ff81D+6NtKeaOTu1s4N+XB7XD58X4haWMg3R7KC+vm9YNG3//YlvWXGz3JWP8dgGYZDPnm4R6Kb4TGzBPbyWjpf5+3oh8z6GP9pnPNWPgQuo5TS9Be+lTIKd/SZm6sikVbWl82oP0+0gXNrTQ6e5IT5J0f/UZ/1NKuyMBF0lwQvrDHFHGg3wZ78JZ+1RT9oYWFXLnQr+QNz97i/u6Z473bq/nVPkbJqA/fvq0tXdwOQOSaR0KMpxldvbAZbTVm5X1E8e3r9V0D6hG3m9FVfYbyf8zLy8Xy2I5f3H5WfqPUP9pK3OHU8hpleIxtdMcZDcrV+4A7zcqPSpaFesEAdXwbaErZja1SVMVs9PjOs/LajlHOeXlpw/g29Ju7QPkyqvoJrO0QQOlBw33DXSvt3F/pj4vfl9OodvKrqyXdxXEu/fZpk/VPU0s7818HYoC51OjSt27DN7lLbSo7+nIY0T3YabSVtNXP87eb0y3ub4+3K+n41nkaXdHAJXYdfXQfdiptjw11/ulsusVVXDQCaD9yh39Pm5iFN9QLd/z3tJvlQ7p8k++1bfnjv+Hpr8TG2B136mlhA8aD8Ngxh82crpI1ffXjGU3T+Q3d6l2mdLjzweZlRgcdD7Lu3XVGgzu9ob3P3Wa0qNNb+66fzGnnnd7I9Mq7n0WP7yB/D3RwHmw7HGT/+j1mdNDhcD96zxkN6nDwZZzRoQ4HzIN7nUZXycY+/PuMZtbhQPvle89pcYeP/f28+8xp5x0+1v3nGT3ucJSf+L5AOx4McbePeX3udwbtRO9+cRod7n6g9fef0+IFB/DLhnI=
*/