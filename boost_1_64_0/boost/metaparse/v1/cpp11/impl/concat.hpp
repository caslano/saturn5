#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_CONCAT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_CONCAT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class A, class B>
        struct concat;

        template <char... As, char... Bs>
        struct concat<string<As...>, string<Bs...>> : string<As..., Bs...> {};
      }
    }
  }
}

#endif


/* concat.hpp
yMie4VGzx997buhPzY/bMzgwOGBS9nbvSuyJxzzoYpGOPKV17zIIHvSwiRvYtSu2o3uXZ3XkMujI+9pBYSyfz+UHS9NjqbyvIzXU6kjblt/dzO9unRnWM0vHNw8aOUYdx3PTYZ3oLWlyWDFhfQ8sJ0iNLfsfpuzEwfFEsljMk0tE8jfZ0kK9I2s8BJfy46nuAN7SYhZxE/Cb7H93RWJ2qQyNH7iTQxoLMymiwtIHH9iXGF/+oOdfi6AnN0NvblAOAU0IL4quAxF9sVIKbAettKR7/P7pdeCOHubN/7RzvGOtLWHiquh33JIqb0mHAUTF+eumnp2PL/PnxwQ3f6s7fF8atWv9fNFeR0z4fgoLfh05njh+DOFHko++Z/IwuUDX2zyqg1wAq7f6ZCI1Tu5QKKHl53Jv1ZJlHWKt/L/Ez55QplI9uZxx/+FB7lMD5HFlP/UiyH6qP5NLFrkPp/pypbGMqecVJHvVkL2ajoiWn0pl6MVMB3RwW4LOWhNfFugcEXhdc7KLqNrzK5PJyiizTD1aSnyZfZCS2WM7WC5N3HGQ2RVo8w4rgwaPZXAl8f3BFI6ikOSIcFnWTP2Xkgw9RMhQ9f+p/ncvCWWsO3t4T8E4AoKM9eZ6zTYXw5YQbGj3QODsx4+AzC3zUirCws1e4O6UUe0+0MJqCWYfHBWwOk6PSC63i+OQGcddFtIpYwJfoxyHHDluaWpHJjeWzCBK1sWrRpzxHSlo9GpSgiPArWXawmsFMk09qqMibVxXaqBv1+7cRCnj8GzJZd5l1Bq57OHpXEnwv/oyz7SLMU7pfKILp7bZkyXTkPMxcLs/G6MTp6gfw2tIR6QmyUHxaHK/TkPtE7c7t6gH4KaNduXoBRGNT+0znM+RsBUP63JM+8SMxtNpqG1GU9MzGVKqnIbjJFMYviQ1QLc49gcUAG7aq9u4/pjK57JgmMjv/qd2WtkmViO/55NOfDh0Ym2FOrFESblzIRzoQwS6zN9F9sBLj1oXojCpBo6ifKP/Vln9xzrPhFdD5x2z0qeoBTpvJcGDuhudtwZhLpZ9zHg4h3Up9N3aReu7B6aO52AcrfKSdBCsOE3iCH1WoMcZMikeN+2hTaw7ZFOlIt0aCtcZxnLG3+tBkp1jIDsnRslOcco8gEv5srAwLBAYAejiBPPZcWOVyYnODEyrrAwjCyepsXCdGAtN3MmQi4eiLVVcpP22Hvbbw+hvD+TI5CvZYuy1h0uYK0+Ez/JkeFFN8vQIKU8PMC/EnIMstrwH+cnQ24+piUBPU3g2eZjOFbpzjg1RcpHcvz9PqquYHMssYFYJzAfEttf5MSsqLQm2/SlKNjYK2TBxmyAbp6JdVFykbGyGbDxSyMZGYVcZudhC4ehKYF1H2FYHIBunSdn4L/HkYGXzTPJ8l0qTDFUy02Tcedo9W1m76xxlLSsvDW1/um173gd4FIXrRRub+DNsG9P5H/AeckK4Cg9yUg88FQc5QRzk5CzIyTb8baC/j4e8PErKi/F9T2FVQWmLE74776v3z0YlD9P1kwS5okhZzwk+n5eRLG0XslTzX+TzBeE4NZHJhDomdQh2E9UbL8OFa+OlLK02jKcn00InxfbFQnzj0X6g14QnzXoMZLUxSj9NW4trfhkFznyy+fjKZJNzYl4tnDtksQmy2EPydbzZ96PwylrXL0S9x98aXh/CWPZMns1W9o73WqT8In8HD/LbBjwVFym/rZDbdvztoL9jVb78PkbJbyeFXWbgLrOSW0N/tT37zuEaec8RsBVeqZSekH41M+NBuB53ZrLFvH2nkX2uGMuqQMVn97t3ZhhuUhkHo0GaOhFHEhzCN1k4OWdNMQ1bLAw5oNw=
*/