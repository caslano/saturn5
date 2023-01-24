/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_05052005_1126)
#define FUSION_VALUE_OF_05052005_1126

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
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
        struct value_of_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct value_of_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template value_of<Iterator> {};
        };

        template <>
        struct value_of_impl<boost_array_iterator_tag>;

        template <>
        struct value_of_impl<mpl_iterator_tag>;

        template <>
        struct value_of_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct value_of
            : extension::value_of_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }
}}

#endif

/* value_of.hpp
w5fHePiimyPpM1E4X+gFDrwwSgzETJOB/CTCI1xdYfDVky0Yhsyt7IfOqH2xJ5Hk11/n/e6duP2OeEPxhzBt3+CpklXI69Up5JjkUU8aUn1OGR4IKBxB+CAcI3xbmSXuHBS0mk+wJ9HtcRjAdM6uPlTRzw2CI3lNDyTdPbMLIfHYycDwm4L/xpPJsEZsKJUOZdHVcmioybW2HRoxcfkiFAJYAliT4nZM/mF1sfJAu9ux0y35doLkpr7cRqvMC9tUxCOYB8oD3emYmBoubwcqPfHaj0gF152gUnC6pSSfcUJQl+wbZAW1D3czmQQC6N2bY+P5js4LGSMx97ymIbR7xdDQRS3Yg7AoBvW2kON3qrxwb7gEhj0VUdq7Ek3ieXVMTJy4fDxCaBLJ/wq/YWUotfCK3thbUV9fmNypKHvCecPDOX4NlumiXrqg5eaxuo0WZTx1NVMSjiU9aOhaVp3D/FjqBzdqnXwBB9CAHQ8UMTmLMjFH4Wh8js3lJhuayzGB+tQ0uqRu/wBn0MI005YsmmN71VfoCpvU9R6H7swy1XeOs+LTyqonYiZFv3IBGIMbYaA+kZXXyE6sA3HgMRJl2khfC7slptJ15SLm7FiKzpQVqOdeRR5SGIP8DqlXAr294SGuhhQ82kOnysIpUWsZRtKI6m6E6tDAtxLPzqhRQu2bOJk2GAa/TcfYrJYQI0QqiVOjdJNfs/HtyKhY
*/