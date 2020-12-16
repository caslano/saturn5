/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REMOVE_07162005_0818)
#define FUSION_REMOVE_07162005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct remove
        {
            typedef filter_view<Sequence, mpl::not_<is_same<mpl::_, T> > > type;
        };
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::remove<Sequence const, T>::type
    remove(Sequence const& seq)
    {
        typedef typename result_of::remove<Sequence const, T>::type result_type;
        return result_type(seq);
    }
}}

#endif


/* remove.hpp
m7vrbaauWbalgHZbn6MW00Af+pHk434p+7ul7Ksvs86H6kKbmRdfH9r8vHjbV87JcrY60h2JQY6gO2+LVV4KyipLXSHXZf1ZC++dbDhrQdpzDfrknAm/btXTtIM/88DQ3+jPWvCzI+cU81kTb2nP/gB2eE4kCf7MB70der1fi94k0RmH/AG9EVsD6C0urWCT/Sbp1b1rypkfUr8szp+YLvYVdjGfa1Ov9bcB7FMn3ARRNvpyONbFUP5S76oD6An1rA/qnmX5F3U11D/pt2sD6A31rI9JiY2f9fGpvPda730f+lkF1nvZh75n/Xd9toH1HveB97K3Pssh8JkE1mc2BDp74Ls/YyDUsxmszwwIdNZC6GdFhHr2w/2TtfDnd8aeFV+656Phj9z8UMLee+sDnfEQ+KwCzx4q8j0OdyPGPVQuFx+Yq+BYuB0mwx1wOdwJz4HXwA3wWrgJ7oJXwevgNfB6NVcr38ewq8Vc7Y0yh3wzTIQ1cDa8Ba6GP4Vr4W2wAu6H1fCg6DkEd8Hb4QF4BzwE74SH4V3wMXgPPApr4dvwXvg+vB9+DR+AHbHvQdgZPgQ9c+DyDQyHG+fAZc64A3wfdoUfwEj4J9gfHodD4Z/hMPihpJuK1Eu6/RDjnqRvSbpvS7p/kHTrYV/4jkpHvldhX4t0XpV0fi/pvCbpvA77QKqLrFWVb0+YgRjXqv5S5uSfhAPhU3AIfBrOhL+Cc+CvofJBlPTOsfBBfFZ8rp6Hg+DvpJxekHTqYCY8CrPgi3AZfEndF/n+g06L+/KIpP9zOAI+CkfDw3AC/AWcCx+Da+DjUO3tK+kustjbd4Xc1wK5n3Y4Fq6CybAILofFMBc6pB6XwA2wFF4Ey+Al0Al3wHL4E1gBD0IXvA9WwkfgOvgErIKvwfXwDXie2H0+/BRugN/CjbAL9l8AT4XVYeK7DKfBS+A8uAnOh5tVPZBvOnimRT1YKvVgOUyCZ8GJMAemw7PhQniOrn7WSXoZFvVzgaSXKekthKfBxVIPspRd8k0FF1rYNYDr+kEbHAkHw3g4RO73ULEvWudzVyvp/dTC5y5G7vMYGA1jpf6MFTvHwckwTup/PFwEE2ARHA/Ph4lwJ0yC18NkuAemyP2eoOyR7xZ4v4U9kyV/qXAonAZj4XSYAmfAqXAmnA1nwSw4W+rfGXAjTIO3wDnwAJwr/eU8eDdMV/dNvj1grMV96yk+NlGwL+wFB8LeMAb20ftkkU4gn6fFeh8+uW5wg9fJOzpMauS6PLmuVyPXVW8NTm/t1obzgb+w8nMJ7BPj8X+pasT/JbDvi6XfS9A+L831d2nA16VF/VyyYAC/lh/Un6Upviyh+LAE678ivitGvxW9z4ryV8FXpVl+Ki/Ht5x/Sqi+KeKXIj4pLeeP0tK+KAY/lB+1D8qxDUa/k8b9TZ5DvH4mT73EPUb6v4xvH+JEdiNPIR8hPVg4lIhkIS5kN3IYOY50eZV/Q3KQTUgt8vKrrb4KrX+tf9/j/L+ryqU5ADR//t8xmndMGcN+TebF7iQTkcKtvDAfWe+bp5ODV90HljK3VVaeW+EqJ9WwsMbnNcPDumigjyI9qM2TJXj+Ozo9IyU5TMJG+sKSvGE2X1iiN6yXL2y8NyzcF5bgDevgC4v3hn29QYXFecM+UWHJE71hH/rCJnjD3vGFpXjDXvOFqXy84AtT+fiVL0zl4xe+MJWPe31hKh+3+cJUPvb4wlQ+rlRhSSofF/nCVD4qfWEqH8W+MJWPs31hKh8LfWEqH7N8YSofE31hKh+xvjCVj8G+MJWPniosUeXjJF+Yysc356swlY+/+8JUPt73hal8vO4LU/l43hem8vGEL0zl40E=
*/