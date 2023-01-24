/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_MAP_07222005_1247)
#define FUSION_MAKE_MAP_07222005_1247

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/generation/detail/pp_make_map.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/support/pair.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename ...Key>
        struct make_map
        {
            template <typename ...T>
            struct apply
            {
                typedef map<
                    fusion::pair<
                        Key
                      , typename detail::as_fusion_element<T>::type
                    >...>
                type;
            };
        };
    }

    template <typename ...Key, typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<
        fusion::pair<
            Key
          , typename detail::as_fusion_element<T>::type
        >...>
    make_map(T const&... arg)
    {
        typedef map<
            fusion::pair<
                Key
              , typename detail::as_fusion_element<T>::type
            >...>
        result_type;

        return result_type(arg...);
    }
 }}

#endif
#endif

/* make_map.hpp
rlkvEdpew5LTgdHyZb3naz+tLcXFSyL9taCL1hmGp0gttOAR0iXrtcwNCetoFSlRimJQpZoIZcdaFvlhy/+G/X4kC2ZDdZOR+L/Csuy/KOLnJGnltuFIpYqiIg2jyh/FD+EWMYqb8vYMzR9cLi1hfxtl3s5g3vLIvuU51X+v+PbR1VsKak/ekbdVtQmLzY1ej2uXhWeeupkcRhlIXrIqZTB1NedIX2yFjpX3VRyV1o+Uv66c+ZnpqlNr7iu60ivLFBvf+Zj5hUH9KnSSJNDWn5r8exZF4GPAbzxnR6Wbf6f6jwDverf948cPhJX/ZO3Gru6rPF7uTmgYupFf+TQ12WfYu3HH4onC0oLZok6Yp/gzYwcvduEt/K96t7rT5htqWp4A/WiA+vhA8/O5KzOpT+Gv2deAyB+GffsNbtwjSZNV1aORQUWusMOzqOTfKkKD7GMqTVKqqm7/NEfQ7Y11pQ4t3yL5EgO4XTqdj4Zn8a8dF4rCap6pipnJCl9osCn7j4SPZcCOilytv7iVXGsPSUMzyxns60Z9ulpMIFWcE3JftdjQ95Rw+FKw+oP2ftzclKy7nlr0Bvg4Whd7p/RVkHtHT6alh7hvqvDfzRqvyiaRe2FjDQWZS+6rcnduGiSqtLZUZXg/pwlzESo/0bEHSyvtldp6+QpjJt/3ea6iant2GqU4188yd9ZV3lQJOJ3w/eJrZJy72OARX620
*/