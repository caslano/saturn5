// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_CHCONV_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_INFO_PARSER_CHCONV_HPP_INCLUDED

#include <string>

namespace boost { namespace property_tree { namespace info_parser
{

    template<class ChDest, class ChSrc>
    std::basic_string<ChDest> convert_chtype(const ChSrc *text)
    {
        std::basic_string<ChDest> result;
        while (*text)
        {
            result += ChDest(*text);
            ++text;
        }
        return result;
    }

} } }

#endif

/* info_parser_utils.hpp
LN75l/a/psFQ+4x/qaYz8Y+nL9S9cSY9PguP16DY4elqStXHKpsVl19/qC/bvn3adUQrqyFQRL03mYMb/Q9oOuZYQvvtTsPNS6eCFHvt1bEf+xjcsah3IvHOD3AnWL1TH++sgTsh6h3Mt/RjuBOq3rkN7yyAr1n7D46l+uy12TcuwXMFgUTixMRHwrNCcs9n2sXE2zCBNNIdQN0DoJYeF7M3R2JNP47z+dgCYm/EM/9Qf7iHbG+gZtihynxED3r1XXgVpaNHlOjtDU1jxeNc5KOQpaY3X4/Fv41rULWOZu2D34bRb5/zUJk3/sYLtwePdGUKgjP7o3COf3RfnFE4AEoEI9cdHBEZh4q63PT5Xp5gWz8QNBw/dGCBRSh9COfqTwJ28L7gky9b2JYtsW5pp9hsCHZIsgX44WJ2scVnHwi6mF0MQmUT83PzJtUSF4LwTAzLipjVqGNpOPyz/gXIG3Q9e2ucYxidWE/49xe9n8dkQPE4a4Sd9FQP9w7BWSO5U2kDnIjBNCr9xSzqWUiWDvnsX83CyRg9LMpY1ds4iOqx1vhDcZ6bW9D9oSN/7E3gxw5fHnrNsS/hryJqwp11VvwerzXhddX8HLmJKmGbVUKwQZjNj6Ol3TdpC5zCfJQ5KH8m2xllAwECYa93UAiNX1L8pc6mTAMeG3+ezaP02n9FzxezAr9zpvIzoOhwn70uepqZ9HuceqmeXqTm
*/