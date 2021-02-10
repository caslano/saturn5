/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BACK_EXTENDED_DEQUE_26112006_2209)
#define BOOST_FUSION_BACK_EXTENDED_DEQUE_26112006_2209

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

namespace boost { namespace fusion
{
    template <typename Deque, typename T>
    struct back_extended_deque
      : detail::keyed_element<typename Deque::next_up, T, Deque>
      , sequence_base<back_extended_deque<Deque, T> >
    {
        typedef detail::keyed_element<typename Deque::next_up, T, Deque> base;
        typedef typename Deque::next_down next_down;
        typedef mpl::int_<(Deque::next_up::value + 1)> next_up;
        typedef mpl::int_<(result_of::size<Deque>::value + 1)> size;

        template <typename Arg>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        back_extended_deque(Deque const& deque, Arg const& val)
          : base(val, deque)
        {}

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename Arg>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        back_extended_deque(Deque const& deque, Arg& val)
          : base(val, deque)
        {}
#else
        template <typename Arg>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        back_extended_deque(Deque const& deque, Arg&& val)
          : base(BOOST_FUSION_FWD_ELEM(Arg, val), deque)
        {}
#endif
    };
}}

#endif

/* back_extended_deque.hpp
i2EOmUoN+VBYnoOkIoozNiLCH7jZuWWt7oitbVsoChpHJ7kOM8UzntnhFpqFxlE2WVrO7MXx4b/Q8xOpSxr5+E2VsNEK8no59t+91LdrtMgktJIYMRE+lM45tRRpeWxfWZGMa1hyoPs6ytuylEROXWqilmZo1X0eiO5bYiYtC693pKI0iJOKbu90fBb7q2neeo0sU1okWoUoURhqh9GMn5ktUVlz0tZc6gNSBZQaomhgp4fA1ABBLtVgAVco5fsBqdzAzCwM2+u4TpyY3yJRkyizjEmcoNNp8mjdW67V0O7IdV1VKb1y3Kro6TxOSkwdeBWKpcM2PygLWs4GISIOf7KV/aHV7ROHub0BonHk9iyw4FRSr/R+EAWu6CxgPlQpdAm15uFthdVZaTlQ8OKDI0u65rwbhdhKJYMKy2ay4mDxkZzmKYszMtMIy1YlmzaswEWTRlDSSthZBHfS2GPloMnKtN1iekFjJ7wnfI50fbGqFArV1u1GPZs8AXEESNsk2VBLIwg++f6g2e3kLwsNM70m4M+6WUAQTGgvU8h0bq9p3t1osflZ85qdrzXv42D/iv5BnF6JfKV77rTzlg7d8YkTGc13vfFnZ+qRhhXElQuu0AVzJK4kDEC7El1sWSlUxKMUYKkROtwr92np
*/