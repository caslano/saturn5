/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_VALUE_AT_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_VALUE_AT_IMPL_01062013_1700

namespace boost { namespace fusion {
    
    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<std_array_tag>
        {
            template <typename Sequence, typename N>
            struct apply 
            {
                typedef typename Sequence::value_type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
TaVDjK7CrtfWeNeLG/EuX1wVGZeqSWhnwtMkSWgKTAozEr3gvDbaF4iFQ9aSvQW/1fYTpdvUKd2m/tIV4KZY84INkNh6Ruol9+L+6oBIqvyY166ZYcMpbu9teYzLsNLVZX2D0hqL/bk9B+1UdzRxo/JAhMJ8drkbl2zK1SEvyNUGI8oXaLNgillU5Yc4imCrhQBGM+pYmjQS3sMovPmK2dpgPOut32wVfSsquKN+cuY8hmKkN/sdWg5LLAn1kXukUGeaRuqXe7CIfGPTPQEyvhx+1kZjo9cKfusxTU4Qdo4XF/Le+xIyT7hrMXEVfIBpoWj7fNQ4xr8qQsHXiurmaguyVc33NG6rOt9Tj63qIXRfjuhNMVf/obmaU4jtucFo7q1jsV4t+18t1pv/m8Xylf0fLFbcsLoWK3JYQG8eubspFmvcxeewWP0mYsfdPNFcl0hscliaDN1lLU1MbPKglbjn7uCVuNvXLxv2bK8S61k+1iRv7Egx5GQpjLrLns5y+76m6LUYKNqVZ42XahJo6OksmOYjzPOgn3iSj4ent9fqhEpkFrb8f4fWuxzHnQ7F//cimqB7cE0+jEbdGwrr2e+Cpui/U12lBWU1yB9qCS2EiByTOw4t/A7XULCG94gWuS2LYZTuyZIM36Y2Bz14UU5q7a6yGWpgn/nALM6P+asPDZESUXcTYo351Q9cGOzmco81PwV8ABqRwu/d
*/