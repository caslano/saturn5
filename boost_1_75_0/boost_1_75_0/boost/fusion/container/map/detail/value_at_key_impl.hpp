/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_KEY_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_KEY_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_key_impl;

        template <>
        struct value_at_key_impl<map_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : BOOST_FUSION_DECLTYPE_N3031((
                    boost::declval<Sequence>().get_val(mpl::identity<Key>())
                ))
            {};
        };
    }
}}

#endif

/* value_at_key_impl.hpp
6FFGJ/LJuFtk3DwDzClY8Ve1VYrtPW8Q+PODhzTjkBRYSx4u5pt2j1Abg7qiRweTlcbGVptnGFKBoAyorpjDHLM79JfTEwND2E1NhfxRJ3xyXHM64YvvZDvNPGuDOBxwj5Tzl7Z1bKPXhEq/hepKThp4JsHBTGei7cEhbSyHnFOR9B44sCWybx87pOSgSeztnzsMmQUdtlUfnQm2bwacCbYbNtutTBW/O6AlYF0eCax77oisSwvr9IKPzOtUlxHVLdFcPyACCxbN1vGOJagHV262lNF97EGLQYSRwLQyKs+Qz5WugtJw/W6Gd9dbcftFjnWJxcStXOU2XxaaLMqmQtVnNYfZ1t7cUht4O+P+WETzr8fSgIXZQMwD/b9Vhp6SVzmeDeRzlrOmIROe2oOIxlm9j8CNxPAWdTyDlRIcGO9WjmSlLwNdIGdZF3EmZ1Uug61NOlb2Ks9lWCW+3pdzEC7k/uTU0JRUNSmXU1JCU1LUX/572OCFO8vWCBKkFt5YMvsdc846ZIVml8D7VMkftVbpEjKz50ln2T8W/rFW/niSfvgHZvY76Swnt8xIW/u0qjqe0lcdcBgHUonl7KzBRKSh8HY4QyQHgxZzyWou+UikkhV6yTFQ8v2QknIZDY5Q0ldMxa4SaY2PG2WkH8yukcoUUJkEKDOY7pF6wWlc8KjdXBBPPM2XSwW/t5sPMc11uj+7m4L38ZTg4ViL
*/