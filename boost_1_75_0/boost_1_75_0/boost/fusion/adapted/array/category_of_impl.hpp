/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_CATEGORY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_CATEGORY_OF_IMPL_HPP

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename>
        struct category_of_impl;

        template<>
        struct category_of_impl<po_array_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
eBMX1xdgkOZ316M9/Fpsdts9QMCuTvcvIK1qjOkUOVs1JN33Lsc4SG6EsIoijOhezzNejLewSQi6vgjQFjcwaizDd0HQMSeQoBy0mlN0uEqQkLPpPruJFN+9mAh9dzH1zmJkng7X2d9Zie7kAWc7gEta/lzM/3VbrPIdMMcEJ6jLHmP0oVGyBZNuMPIPtWo5vGoQyDo7kqbbD+Pj+bttDjgHD3ZYBP15BvKirQN9ekFTNgr6IQKVf7p5XxYlnMS4KOTfhd5ozM/4rRKIP4gUHy6+EQ5kMoD2RWtDIdfXit+vUYYEg5Gj2Ql5wPDd3FxOv9YTmxbrMiVXD5Z5r34CosjU15a+nYjfPiZq+jbDYePJ9K0CZH8wGYbkwKbyKVFgsqL/Mgllun9ALJ6v4FmFWuVv8KbbNuD0iBaBFPujV78BPeTA6Hy2A2+A/O0+saPX7oA//dEz8XWHXAe73Wf4o8eLdctAuwagdtFHn4Ya5YeuAZKPd9YXBfCnFw2OFLOL4ARX5W5cxcKn1JlFUi3U+11zay2AUM4k7n4rsQmwoS7T2seQkv7X8cTQbB8PivnDAm21no6agJbpQBX90vHECC0YT/ZT+h1UBgoHmdZEk7RrrOHNWMMbf7esEa8kWfIbrHYnQT71IRh9B66rOj6Tkp5PQ9vQ33SMFodjwNlrMOCqwKd08H9+lEScmO+tJeyHP/oXccXM8Nu+2wYS
*/