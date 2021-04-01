/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::first_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
0WgrkW1Z/MY1lOrjCzJv4th/Y8XNvh1lb+d5yfycn5xKq27BBs9cAnfNgcuRd7PBkFv/8XACmodNZY4CjY1yfeFbVPaMjmhz3qKIzGAZq2pJzlx43vlsYRGrG4I1hQk8tgYKorJytxHa8V+eeEmjk5/HdlSayo0oVrydXxvcoYneP3YtEQOQo3Z5/mzOow+lyYABWBIjVGBIO2/1VuJqBbV/mGTX9OmdayoMjs7y570cpM0MC6u+qNs5FHq9zJGl7sWBCNfz8pw77n1nn/TtpFk55YKijW/dY/Y/hDdrsgsnF7ADWxpKVEEbI6U57gkbpK2Ws4OgBLsVGfPnjyh0VA3WMQlwN5MLLRgaPXjiTG/QycrXi+4tbzMnfx0EIM8iE5ySXwPZPLUxsWTrbdGWi9xOkKjFmg103VDYpljc5ORJ89IBSPf1fH61kAi7Bo7C8C7RaL05SAt51Ylnpa4+IggapJ2DfiKuNzuTnrkdRO2YGeosXH+VoItRKzA3TatqO8zDEql5Czv+ET/FqYf54q7q0FeuyvUkpWxpeIiqhAY4Q5lm6ePr4pFjKg==
*/