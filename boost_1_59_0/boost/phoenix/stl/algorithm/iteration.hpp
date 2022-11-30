// Copyright 2005 Daniel Wallin. 
// Copyright 2005 Joel de Guzman.
// Copyright 2005 Dan Marsden. 
//
// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_ITERATION_HPP
#define BOOST_PHOENIX_ALGORITHM_ITERATION_HPP

#include <algorithm>
#include <numeric>

#include <boost/phoenix/stl/algorithm/detail/begin.hpp>
#include <boost/phoenix/stl/algorithm/detail/end.hpp>

#include <boost/phoenix/function/adapt_callable.hpp>

namespace boost { namespace phoenix {
    namespace impl
    {
        struct for_each
        {
            template <typename Sig>
            struct result;

            template<typename This, class R, class F>
            struct result<This(R&, F)>
                : result<This(R&, F const &)>
            {};

            template<typename This, class R, class F>
            struct result<This(R&, F &)>
            {
                typedef F type;
            };

            template<class R, class F>
            F const operator()(R& r, F const& fn) const
            {        
                return std::for_each(detail::begin_(r), detail::end_(r), fn);
            }
        };

        struct accumulate
        {
            template <typename Sig>
            struct result;
            
            template<typename This, class R, class I>
            struct result<This(R&, I)>
                : result<This(R&, I const &)>
            {};
            
            template<typename This, class R, class I>
            struct result<This(R&, I &)>
            {
                typedef I type;
            };
            
            template<typename This, class R, class I, class C>
            struct result<This(R&, I, C)>
                : result<This(R&, I const &, C)>
            {};

            template<typename This, class R, class I, class C>
            struct result<This(R&, I &, C)>
            {
                typedef I type;
            };

            template<class R, class I>
            I
            operator()(R& r, I i) const
            {
                return std::accumulate(detail::begin_(r), detail::end_(r), i);
            }

            template<class R, class I, class C>
            I
            operator()(R& r, I i, C c) const
            {
                return std::accumulate(detail::begin_(r), detail::end_(r), i, c);
            }
        };
    }

    BOOST_PHOENIX_ADAPT_CALLABLE(for_each, impl::for_each, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(accumulate, impl::accumulate, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(accumulate, impl::accumulate, 3)

}}

#endif

/* iteration.hpp
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
*/