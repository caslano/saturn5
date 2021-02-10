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
jHAF9h+ze1GsjAJPw6FXOqwddXq/D147BaecsUup5ZyhVUbqeCRJvshudfp7C3OVcfmBpZ5ztrKz1iVd/a1opPTx9Wvg6fVEF+n4YrPDhEO4sKAc6b1EXteqHrTOqUkgKSf4oFIu84xyeMvhPlurzOhCFWstDljKwNuqIbgluii8VTev+hXTGJEBlXbG8ljkoFdVmg+1QNlkXCrIt4iFqEG/57QWzCmeAF69TBTU07QateWXHIZ4XekoFlRrkmKTHittFq3X26rbRnPplwBWRX52/4xUya6Ks9HVvJyX3eOwy4AfnQ6OOyft9skRJvX5Q/UGEPo2zQsn5RD7OHP4OQJqzAUrVR1IlW0W8311j1/nmJRY7xbSgQ3gQiW6OSUGTmz96NCAhbmT4Q3puTCTxpfZJIwTzqVhKrNZ3cFx0SjY7+dIfLiJt4UvnRwaan/8DfrJOSkEyAGl4chy5K+asIG6l9qNJAGUvHkq9tIevJpW1pxRDax3VX5f4ssU6cIjWFBozIN0rorYqhz2VhBqEEuJUHmhD+raO4P573iH83KnbhNOUma0Ma2ySnh8b6UC63WFmVT+QoQzgV9yW7cYCNaE1BfBQgz1bC0o6w/s7Dqou4io9hAcHtytTd0XxcSgJRRriv6qa5zcE/sQ
*/