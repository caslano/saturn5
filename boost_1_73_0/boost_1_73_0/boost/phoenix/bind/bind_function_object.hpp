/*=============================================================================
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef PHOENIX_BIND_BIND_FUNCTION_OBJECT_HPP
#define PHOENIX_BIND_BIND_FUNCTION_OBJECT_HPP

#include <boost/phoenix/core/limits.hpp>

#if defined(BOOST_PHOENIX_NO_VARIADIC_BIND)
# include <boost/phoenix/bind/detail/cpp03/bind_function_object.hpp>
#else

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>

namespace boost { namespace phoenix
{
    template <typename F>
    inline typename detail::expression::function_eval<F>::type const
    bind(F f)
    {
        return detail::expression::function_eval<F>::make(f);
    }

    template <typename F, typename... A>
    inline typename detail::expression::function_eval<F, A...>::type const
    bind(F f, A const&... a)
    {
        return detail::expression::function_eval<F, A...>::make(f, a...);
    }
}} // namespace boost::phoenix

#endif
#endif

/* bind_function_object.hpp
2SyciqD957aslKPJxomdV5gCdawj8yCAVa59hzx9l3GFSJQjH5mJBE+NfpbBud9mBKuKoseS5uWAJPdg0tFLEzqdsdPeXhLH/yIEEIyRlkCc90YdSqiW2Qmxx3Tmlz6RQEi/OvJUyVa2KB2769D5trKyc6xbWmp38kv11TZtIddU7wvmAc7QsaK+awlR/Um2qX1KFlB8WcIon050IvuWaNWpvmMOEMgEc3egFyR3DsT+W5Y7WYz53kHLqtOzPqCL5nMyv+Lke6RPJCO8mTuJSsBd+TJ0FFUfhFUJxniWwe9XBB5SwuUwCOTFWyoRU1oGrQvyjczNhScHgmLyaImWFRQ4EDV8GAA4PuCFUZBPPG+jiGrNWuGMxG0J371cSlYczz/fo0TXKE2ca8U5yZHKzyI2nrT6/mUrhOZ/c09z5DBt6k5IDTsqUJ/6k1So3ZyZzimn+09z4FeMwqtSa6Hm6mAvRVwpG6ECQbaRcX82mym1tFSNJQ8NyXj5fDak18TKAlUCaYFcSU5hygOJKSI5ALRimIt8Y19prd59wNZuMl/IUZh66Vslpb3bJuTSFYMolbCBI+uyZve6zVZKrkomocpuW/y4LR6VpLjHQAhEgLXEMRGHTyGwHBhL0h33qGxidEoF6ujDte/6ov33
*/