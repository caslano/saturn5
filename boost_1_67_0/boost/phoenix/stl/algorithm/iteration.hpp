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