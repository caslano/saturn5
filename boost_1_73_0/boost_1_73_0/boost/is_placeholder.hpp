#ifndef BOOST_IS_PLACEHOLDER_HPP_INCLUDED
#define BOOST_IS_PLACEHOLDER_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined( _MSC_VER ) && ( _MSC_VER >= 1020 )
# pragma once
#endif


//  is_placeholder.hpp - TR1 is_placeholder metafunction
//
//  Copyright (c) 2006 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt


namespace boost
{

template< class T > struct is_placeholder
{
    enum _vt { value = 0 };
};

} // namespace boost

#endif // #ifndef BOOST_IS_PLACEHOLDER_HPP_INCLUDED

/* is_placeholder.hpp
navs6+Ewq01BlQ+lzuww2x19kLtNd4oFVbARW9CVA6ehthiCx4Ww0VKt/EpW0GZVLwtl83BfCgmVcqgNWCwKoqI0hbYtGSHtnAk9CiqqVjm/WF1ar3ST680DIFlIJKvalCRDFhBGajI4hLqUaBpsc+idQudmY+13WrKvVYIuqRJ4NkohSp/BUlhlQ/gQzU7P5jP4MEqSUTxbwNkJjOIFcf0RxRPqtyIlA3hbGbSkbEBtqkKhbASfLhjrff7laeLzwFj3mp2oUn6yTrLnX4M1m413/9ITGtilEWbLWIK2Lhy8F0b5AbLs72+CsctLT8ZPzubx5PKSAaRb63BDY2sbsh0gisfv5pMpn0RJ2uBmOzVVZkUtkXpCU+60oVkZ7LLeRb8loySa7lPa2vw8lYiyHQcazlar9+WJvPrCmFoF8zj62CfdFbnDK5FdiTUG51frsS5Xag1/zaPpzD+vrtbcojBZzunlqAsCjfmnzklfWJ9hSS9N0Ges43J58K0tzREGOfGdRvEsZf4P64f/OqYdkHD3x580zt6znUTXw+DAxgXEoz+naWvVcRUCHlHo0vcKXcsCPzbnrS+n9DYXmDpahJEjs7Z9dugbzxsAtx2CC4I01ZFYMiUvk+mEvx8lbUmHuvuNg6M2ZayC/fD5
*/