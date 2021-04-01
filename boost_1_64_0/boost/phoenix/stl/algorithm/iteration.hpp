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
cFnuDQLdwxrY5YvLkw493zesRUrLhsQXCKjB8XUUOIXm8TWzQyvVRyoJcr0z+9+8P8tJVDykEIbrC/xgjQi1ge/Azdw0FH8LFwPJjT6CA5g4fKGasyl3UxYVSj+uo7I7mbiMiFViQhGn8ICTnWZyZ57myzSv+H8t4Woy7AjgniTQ2ZSeh7psT6FyOyZtQlGmugtoFTNqHGbaiiwGRDxiKJUxZwbcFnvw0ysuV61unin3SBZKYBamcahz9yVL8d9emUUqUgg1SJ9LsqBzp/0Y/N3NEJC8CuieP6I9Xmal2lFt5YOjIyMQFdSiG5YQlrnNWqy1kpOJ+rkPEpKTTvuYBCkjZ/aDeJuZZ8GLNauMWlJisrrZmmCx8XonvAWihaEMTdHkSb6nWXcYZYfSNaZ5pjCGQY/UOZ4BjI/6KgkdVk29ye9T8569VnGyVNaBu1BHWyZzaWYfsqcBZehPSSdop5808NIek/WecrlfANoeWdQ5dCgoExQwqRDPRAaEE0ZxV+oUrR/RcSSscpiE/AWLM0k6QtXouBVHEOcZ8/0hW72wlqs6uHaZY5mU6g==
*/