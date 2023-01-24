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
Bx9dRD154cs69s09qw0syNvqzeNDKE+Tl2W876FjO/K2/YkGQlHdiY7mO16lenXDtsbnx3/H4HaORT6ySdGrFrz00n4PlW+Rsn1zNHwfVyzmXazKtdbFfiun1HhMPCBIlDtpSK8g5TDHHTV4ME5XPk0ZkTIXUrva5gfYAihNXPJv8WNuSzzyiz63F44RMNRdY6qyjlR9giGP717h6QY5CgbJ6VxPGGBIOlib4wv4LXwqbKUH3KlHZ8kWiWPJK3qRdXD61ZoCikqYZjh0+Sq7XPEriZmI8XJUv998RnPe/T9Qd6pL1XGH3a2vU5VEw6Pb64JUPEvZciDnzpj01w17GmFLS1p91PKnufJss/LlGoPS2Dvm7KMAS9YqXiy27uyE/efOFGWlylrjJQGKdRML7zAjWKbyAzaVF1BbEEOnpgE77ypROefutNRVhKKBB9XdZU/Cn+WcxXvHlTfRY6vkBZrtGPrPNwhkgpzV4FFySmyQ8LqNeYgOe084a+noePJ+n02Hz72dIIR4KUWWdQWQpjxfm0usTxzSLS4e4J/06MGfWC4UafeCxTbFdN1mi/qwcsrQUef3S2elIr1YusDkPB+q3P6EJUTIAAvafAhT9sXNdzS+xlo/J9kTBO7Q8Rcyn/m49nrstW7+cIHqfxPfNl2E/J1Wb15XBhUAei+X4u9vL8XlSZGMNirzwu9nn8ZTGUc9msaqnhLqLYKB
*/