/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_AT_IMPL_09122006_2017)
#define BOOST_FUSION_DEQUE_AT_IMPL_09122006_2017

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template<>
        struct at_impl<deque_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::next_up next_up;
                typedef typename Sequence::next_down next_down;
                BOOST_MPL_ASSERT_RELATION(next_down::value, !=, next_up::value);

                static int const offset = next_down::value + 1;
                typedef mpl::int_<(N::value + offset)> adjusted_index;
                typedef typename
                    detail::keyed_element_value_at<Sequence, adjusted_index>::type
                element_type;

                typedef typename
                    add_reference<
                      typename mpl::eval_if<
                      is_const<Sequence>,
                      add_const<element_type>,
                      mpl::identity<element_type> >::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return seq.get(adjusted_index());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
b7Y6W6RaN50IlFuNPeeyOirJT60yng54myShDZX8dyvxt0gTGioamFyzAT5PZSjdYdDcYdDeUW9QG+oNmgbZoAx1Gw1FkSHaJKxmaiCTLKZUdZlbwTWnRKt6JJ2QXsv1FawUaipTl/n7r/B+ImpKER7uMm/Eq5A0ljKEs0sf0qV8kSCcXXqdLrGFpH+8NuFpbWWUPuGpWz7w3CzpeJZUT5FYkFdhB5crkyALOIULCxcztHMJHzjGKBNd7Ek5ptIjqHYanmtNTmFEL7HJEIHQpFBFW/k4E4qsztH5anvdet6OBdo3UXuB2r5LtB+A9jdBtiJZzjHanun8EjCUkXw3FINic3fJesghcHcmmHMyUIkvP8nuYP3KUPqrdplfYl0UbVUc6QCcWJfTwVrYvuV7fvr++ihkXc3wlVjfzJQztliso4gDzWHtGMZRVs9FX3ZTD3aRPW2ZeFpnr09rvZ4bBFL5hZ78eV8ZPT/veuV5y9Xnfc2+KfsOxwAfaK+WyPnPMRuiVxkkNTr8TK9E/GDBUUDO4N/BsjJXQ9EjKwHdG+BKhZEhN6XGNO8wOzGV7Gd/iy+HmuZ9hqdbDVzVWLIOGmqNppJP6IetNZ4tF5cX8h/om54mbS++HGAxvVyFX5x9nz7wMsHd/46iPQzoMuNTy6YSouLlefdz/wGcSq8Sl+D+HOOgeCqAgOZCKTDTOZs7UZifMqFSN0ZUy6xr
*/