/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_05062005_0857)
#define FUSION_VALUE_OF_IMPL_05062005_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_value_traits.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<filter_view_iterator_tag>
            : detail::adapt_value_traits {};
    }
}}

#endif



/* value_of_impl.hpp
3r4Irp0cvHg7PImqRUug1JMiRZo5whvqPAKexlgnnwCsM0ndjVnLfGY35Znk2OHZAXfSEC/0eMv5rJ8YWKs13TGcfaJliIIUcT2qrvq1awSICyV8nwKGMmTMDhDIAQ1a7WOcC6C+DIrvVhqEyyGytie54yAQkCyhunQ3As9jpwG9EbYPeIrOShDaNXJ0ZIbggH1qt1ou6vW/Oe7VRL0E8uAQpBpwYx05N+DDOqhVxHpfTysOwoP0v8KlMNoWSWrDl+E6hYfE8kDJG3m3DPhTeFA3blJ7sUQMzDgMAWSTemo+JvEPl/Z+6gceQ/8yGszuo55NOK5LklEompHEhgFe+YpkauNP76ucbMZFWts0TtIzIzmzSQzXyaYKNECLfBEXCIdvezMbV7sgoRSy8NXuBisVDtmg+H4ikuJeZDBBSioXY6mJQWacck7QFRIxfI1Jlau5M255v7+M6U4+DcILUdGgX5jsB8kJJngBVJ33CsgFzxpIY2/jErdsGPGPjHYOqgVhjrE5hk5qqzmsowluq+kc5UwVW0mGWVjw4awcAs81pz0mKoTxIj+mQI9ZJLXBQJlxJ0SC1uAd0ED0LLuFdFHaeTyUqOaSwiDmfHZr6jrgaDOoYTYqJ94A6NrtZoSABVsZxI5d0R7rb2zC
*/