/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP
#define BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP

#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <boost/callable_traits/detail/utility.hpp>

namespace boost { namespace callable_traits { namespace detail {

    // Here is where the magic happens
    template<typename T>
    using traits = typename BOOST_CLBL_TRTS_DISJUNCTION(
        function_object<unwrap_reference<T>>,
        function<T>,
        pmf<T>,
        pmd<T>,
        default_callable_traits<T>
    )::traits;

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP

/* traits.hpp
pNbI7G/Q4jUW7c186CdUSq/Q3I608bNjYamhnxD1yytyw3GwG3ONhXj2jTG1s5tKesgngj2v4OrPgerp1Xo0gin1BePqtNbkrUYz50AzWCzWn4pGIqIm/0fhS3MCM9idqxQfFop8IByaxi7CYogzeSlwDdbhefi4J5hrzW50zMcQOMFB1pxsxTG/J9yXHy45hwGZn07HQjEY5yejWstRnBI6SAeI+8sPOx5ZRAcik1PT88p/KemEn/nk4vRwXJ58lxPtO/ItHvkrOsGloUlyUp0wj8wHdAzl2iyccuUKOnD6peQqTKhbPoWOAuPzqBcjU0uxDrnnl9R8uk9W8uSu5K4lyQ3wzKNelxY6Qvr6gmTOa196XFUxtRYmTqYa+1KNBU5MwXihJF8vyuVTOf/pXnkmxuyhSin5MY7TJx/wPKx6oK9WmEFfdo1jziPCyLPIgsrgyAEV4TmTPqCZVqM/RYpyjNq5yjwoPuHVhyXJza2HlSNPQIy72wkd0dP0JXEPeD5hdP4c8TZff5sv3ubG7svJ/skx70ZSkRc4+aTPnwFflfTzZd3qLPlLnrwmdDa8hle5ePYjqnHiQssXcVRi8Q0M0a0nIPWJo29EX8f76DMRJMMI7IBy76txgBSvsqUElnjqvVhTyokkWsNanIIIWuLBzLFB8kwDcvLNKxwqYiHB8uZMrzzV7ZWnm2Ny0LnRP3+JoXOje+GKZt13
*/