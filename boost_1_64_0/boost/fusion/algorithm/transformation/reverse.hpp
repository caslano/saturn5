/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REVERSE_07212005_1230)
#define FUSION_REVERSE_07212005_1230

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/reverse_view/reverse_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct reverse
        {
            typedef reverse_view<Sequence> type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , reverse_view<Sequence const>
        >::type
    reverse(Sequence const& view)
    {
        return reverse_view<Sequence const>(view);
    }
}}

#endif


/* reverse.hpp
oawKm9eqamsksCuud0lcfBP9OPHqj5ZAe1mPpSlgh8DsNao8VcQj1xyV4wT54MjXG5VSRoQnsft4+l8hn8nAwqzKWs1lXRxDNGWB+gJ8v7kCn1jhtNPeFYx4GbKGKA6wttgSAlmwN1EXZHZDu7VrhDyN+KRVCmOz8AVqJ+i0A31CGI0dPpkwH9agizKxM4kXp6+tWPtGhvZD32AXqObvtbmEN9Y/X8k6b+dsz6uw1qfrdjCJmEYq36jVBsvOCzlTVD+GOL5iJ7q6IwJzigDnayX8Y4nbL6CbZMuBdhqvY+eeNkyIpE94gEql8811IHMtxJYIBUJwQlAxwm+rIoJzkNS86Rz+3kPLdwh0Zd2thmxrihf2sezw/C97R5sYfEa5xy+zYSvtKu2WspRCX2liwpZIEeZUo8IB47YAXa/GrNRIWtxBKelbadtXX1RV6drpmsug4o37LHqpgLaUaIWO0luLQQQnTbMcBvs0IXjmcrv4NxCmO1tQoblYHKOLTQr7bX5XGGKYGMVZxXaT58C6qnf3RHygGCtiFt4lN6orAV+z7Jcl7PfUen11uw==
*/