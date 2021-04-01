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
d8V2DqcArh/4qnDPmL9qaw+5mZliug05T8I5ruNzAKy2Z04SOReHf5lJBEa9q5saaFnS8W1cez2K5taD/mJOt4iHs+vMrNHUDsSEiCTAWvrGDPUmapQlAbsDyHetZioPlBD+ei/SXkO4Y1qqKVZxZqNB4IK+9c2kGeAeiXxk2qXysI98VUEXkz1zPXNfNTN1fjMqj9rQpGYIj+Ciohmqb/i5hylKmoao3OlvnY28PTSPTReBWZVWeb+SiOsGCXDaWiPUkNCuVgRjl9eWCwtrrp6sShkyckZo+PukC+lGY1UtUFWwh8+zsmSzq1kNQqYafP63J2hK8FD6vvhNRi3+aDy6aNNzJsNkhl4qX67L5dFjDSLt3zDRpt0I93tjU6TAEzuSRdJ2EsMG++Qfvcq7sGn1BJVRgkUId+hlIQvOgX3QWhpYRMcqcGGiPm1w4u1FXygjX03w2VTUSkaSRkCyMeY7Z0+z6EUdGkG5JC2KxFOjd9vrEyHYPk/h1s1kzdV1qVO97UawR8/60tHoDk2TTxXI8lFqLsmphM3Txzefv4CEc0Qwmk348z6QDg==
*/