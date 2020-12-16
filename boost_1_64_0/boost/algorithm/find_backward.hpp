/*
   Copyright (c) T. Zachary Laine 2018.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALGORITHM_FIND_BACKWARD_HPP
#define BOOST_ALGORITHM_FIND_BACKWARD_HPP

#include <utility>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

template<typename BidiIter, typename T>
BOOST_CXX14_CONSTEXPR
BidiIter find_backward(BidiIter first, BidiIter last, const T & x)
{
    BidiIter it = last;
    while (it != first) {
        if (*--it == x)
            return it;
    }
    return last;
}

template<typename Range, typename T>
BOOST_CXX14_CONSTEXPR
typename boost::range_iterator<Range>::type find_backward(Range & range, const T & x)
{
    return ::boost::algorithm::find_backward(boost::begin(range), boost::end(range), x);
}

template<typename BidiIter, typename T>
BOOST_CXX14_CONSTEXPR
BidiIter find_not_backward(BidiIter first, BidiIter last, const T & x)
{
    BidiIter it = last;
    while (it != first) {
        if (*--it != x)
            return it;
    }
    return last;
}

template<typename Range, typename T>
BOOST_CXX14_CONSTEXPR
typename boost::range_iterator<Range>::type find_not_backward(Range & range, const T & x)
{
    return ::boost::algorithm::find_not_backward(boost::begin(range), boost::end(range), x);
}

template<typename BidiIter, typename Pred>
BOOST_CXX14_CONSTEXPR
BidiIter find_if_backward(BidiIter first, BidiIter last, Pred p)
{
    BidiIter it = last;
    while (it != first) {
        if (p(*--it))
            return it;
    }
    return last;
}

template<typename Range, typename Pred>
BOOST_CXX14_CONSTEXPR
typename boost::range_iterator<Range>::type find_if_backward(Range & range, Pred p)
{
    return ::boost::algorithm::find_if_backward(boost::begin(range), boost::end(range), p);
}

template<typename BidiIter, typename Pred>
BOOST_CXX14_CONSTEXPR
BidiIter find_if_not_backward(BidiIter first, BidiIter last, Pred p)
{
    BidiIter it = last;
    while (it != first) {
        if (!p(*--it))
            return it;
    }
    return last;
}

template<typename Range, typename Pred>
BOOST_CXX14_CONSTEXPR
typename boost::range_iterator<Range>::type find_if_not_backward(Range & range, Pred p)
{
    return ::boost::algorithm::find_if_not_backward(boost::begin(range), boost::end(range), p);
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_FIND_BACKWARD_HPP

/* find_backward.hpp
BlZt5PY4g8h9FnBiD4m3H9NbdRtbTtnUi90kUEBTc+HH0Bq9CHkgg1owhDJtbfzqRus29OR1TDe/o2mv/JEgCSkgLGaLmZe38qefkSLXvLhXtpRmkVXfgM6n8Nsp1HYrGq+OHdbLPu39906ynf/99Q0pAPkaITbGBj/dNkjkzyQyi41/vlrPNbhZZmRUSZcIHNKX5ni6l+R4vKMGerqPHIiwD2EfwucjfD7ClyN8OcLlCJd7vD9dwIpMIX5477qXQ9q9dssoDDsmWBuT56L98TX0KxXn13jhYizGC10HOTJnqahrO4FBf2mT8BXw106p7+B/tJ6cafDcu5JMeR27GUg1C5hgFnDvq+0V8FgUkGv0wFYjwSK8cIKf4kWp+qXMfY1FMvedcmyXratQPr4AoO388L7L3PFeSqME6H8G9HpOvTVYetFgeYj7v8LLRoOoXtzwpqZrRWizPrzG1aKRPlht1HnLaqPO6/FSsMfWSAVwcazveROfyatxN/1YjBS2sytaUV6MuCzEpUhcFsWdjjg34j7fy3FuissCGqai1qtFbvjLzEJMMAtRhhczeyoKFWHGmxYhHfJy88D+z53m+kjbzI0zF2tpsiaEAHKGvLpbbCEuRWSn64EJhiPYzxJNWeG2CXFHsCL32SU8oPxCZMuHXNlinTP6dXQ/L9HGZXG77F/DEf19mgnD0U2bOPoYCkBmSjNnTySNbztgkmP5Xh3gtXyvHrwWZ/v+Q3ommhde0pTAOyQx3ADbTtIbQNRwD2xn08x011LHH6SDDcu/rlyv+KDDbFRtvCWAZX1c4wLeglhgyi4I1oNsgKjVloFfnBgsSoUfbzL03UM2TGCwlR87jJ0l5uemDFU7VaWT/TcRU0YH9SvlZuKgceefvs1NGsHNw6gR6eLrXGERKwbztYuf4qH/LBUgRfuDmiSZ46fO4XP0N/QJ27lz8oz+wtSk5zZwVBZHRWZkQzQKRYAcvUzWGL0hcw2QL7f9lOXMz5CKxgWlPPWy1ARKoYTPVLRu878igPKTtai41vblRbFQByi0Y3QXQJvcNKG8byjYZBMnyYvStBmZlhOMTOvN6ldy/mbBOLFbWpaIrVS3gWdWOhTjRXGo87+mPGZvomFs1O2WD2TKGskT6Wv6s5hI6TNRazYuEdfPflMATgPAIgP/WvgMFvyTgF9eGH/Mwp9l4D/GwN+0X/CPF/xZFv6tGwVgFQOM8/IIWb5aIp9FJPezpRGNEZGdaV2Z+H36Iv4+fob8h6xmRIhsbZ2JlfAedw0WFq3vfxN4uozT34RXuSHnQPuZAqSwTRtPLDc49m/lxa3/ank7c6tId5ZiMXYgfpLFRg6G315V2yk8JbqPcwzNmZjgpxXuZjjG9iyYzT5F54xWIjOa1fCcZp/nuaM8z5U68Cx1Qe1Hib6X5UuvV6D4g5hEaAQhhDenPJIA4kuvxlsyPslbCh4Y45XvJDBq1ReZ6w5EP3UqWu3ehsjAFa3t/4/E//Nc+HOOA9iQX3p99N0sClN2yBtvTnlQdkrB+vS68PhdFE7GOCOYOgqkpNcFQivcSkFduOwLKJTt0hcfQVwFoNoyqEx+gXvCK514pyvCSxz84q4sSUTaZZUl+FBNACUuvDBEEl4YIhkQ1ZUlKSTpFlWdc3gszmkO7W/GwKEDnXPcoRUpcMIUdH6Ge3zXhfanzJwOeWzZk3Ryv0LRFswffT4Oo53R2DaqbiwQW0NlpqdUwAp47YEsDkxoDV5vB5cAwdajbaj64zH/jVfNVvh5j8PaCkhBEPwEQKmJojRR0voqL3BWlkp6fJb0+Jzsqyxl4dY02YaIdlKQaW9WMyuosVpaEFTo9zzXRyEyxMs=
*/