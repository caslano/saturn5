/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_05042005_1144)
#define FUSION_PRIOR_05042005_1144

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct prior_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct prior_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template prior<Iterator> {};
        };

        template <>
        struct prior_impl<boost_array_iterator_tag>;

        template <>
        struct prior_impl<mpl_iterator_tag>;

        template <>
        struct prior_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct prior
            : extension::prior_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::prior<Iterator>::type const
    prior(Iterator const& i)
    {
        return result_of::prior<Iterator>::call(i);
    }
}}

#endif

/* prior.hpp
w2m9xSpH68DBPbUuUZV22uwi56h33kXAvONi78iRD6NZT4I5GIG3jG276CBjDJs2+TS3LKNIp91rn7bPu4wAfSUsuGcd6oBugLkZ6ARkX0Xt0I/B0aKt+X+nq29FPdOYV0BEKYCi6kNXz2UqR6ywjmEzWBj9MJbl1Yyidjor4vC8CFAQOuhtu+M1QLXa3ebbVu1cwdLkbAYjXPZiJw4nckd0u+eYr+BjIgE5WCgC0JsDHaodj31OBID/XS0o+qB4965nGLhxVQaC740MJAxTBFJi4HtIu4GTKRicrEj3xS9Pq9VDO4JixhfH4/0hzDBAd6NkjUEC+s5Z7bzb6PZqnd4isiFY0FYTN7rfZ7+f9r7WAw9T0jz7+A5WcEUcnfOCm9+iBjb68+N8z2AUfwVL/0f7J6jFWKzd1VSCjNq8q4sGipkF9EyiT7wXTw1Oa2dNTYKr9WQpdXZaa7bO2qmhsmYHtrRcilbn/Afx4obrIJbtYiFm6dzACo7kbXizjjBIpwS+gWBWAgwKeH2D5fx7+32jnIaHF/XKXTq4ah05hCW5GfPp7heblBZejJTzBpak0zg7a3d6a7HQRa337kdYCNutxUJ2B3qiLHG/QmCsuYrWXD9z4NEhn8UbdQASr3fZ3WyJtjvNt+uRd9O1
*/