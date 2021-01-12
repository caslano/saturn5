/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_EQUAL_TO_IMPL_02012005_2133)
#define BOOST_FUSION_EQUAL_TO_IMPL_02012005_2133

namespace boost { namespace fusion 
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template<typename I1, typename I2>
        struct equal_to;

        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<filter_view_iterator_tag>
        {
            template<typename I1, typename I2>
            struct apply
                : result_of::equal_to<typename I1::first_type, typename I2::first_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
1VfhYGoDZtJb2fuEbEy08rKqoKEK42mJsxKAUlvg2AzrEt/PKwyKGN4P+DPKVUS6rz4q7dstcTi2LH0Grg8kcNt54Eel7fgRTuCkgWOlvl/Vp2hgnfB69PRUt83XcVEGJ44Q4RiG4Lp3fQ26x8vwWIH1CkxWfNhZOuNMZrgWP+PYp3HsvhTNsfTRLQKroQx7Usgt4ZRw4ziz6uVUM5OjOno1x1aWE2eV7xcMjBYJozT4d8k6
*/