/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FRONT_09162005_0343)
#define FUSION_FRONT_09162005_0343

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    namespace result_of
    {
        template <typename Sequence>
        struct front
            : result_of::deref<typename result_of::begin<Sequence>::type>
        {};
    }
    
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::front<Sequence>::type
    front(Sequence& seq)
    {
        return *fusion::begin(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::front<Sequence const>::type
    front(Sequence const& seq)
    {
        return *fusion::begin(seq);
    }
}}

#endif

/* front.hpp
/jll19ebmr9oATfAks2c1XAqNGgVmyuWckA4ESGXmkfANERch6kY4xchwUw5xCLhcHD67mP/5FULrqYinBKThcpAT1WWRDBllxxSHnJx6XjMWWpAxUiOzCOhDTLMjFByE2VzMDydaeJB4lmiFbBLJhI2RkHMwNSYud5tt8MsTVD7dqRC3Q4L8zenZuYt+YhKzNgC1NyAUZBp3gI62YKZikRMv9EhiJxn40ToaavUBkXJqK1S0DxJiBfSCa6d2hzOcve06BjMUWNh6JdWUpOoq6ma1Q6iH4lLnKUSBaEf8FCk0M0tyGTEU3vYWl6IyH1qHXzn1ZT6RqAkKgMr3TPon63AmGmhW/C+P3x9ej6E993BoHsy/AinR9A9+UjM3vRPDvHqBQpLgV/PU65ReApiNk8Ej3KZP+/TbjTaa9DTIZtb76Lh3H05HxwDlyHeiZxQXJFNcqJdOMSZDCk4NMaQQfcBA8mvbHwkiQoZme4ISPmT8+NjEDF5gqcpIlSIgZKiOQCkwS9ChkkWcVih+BlpZDnfnK5UHjynBy66pi+qBIiJmGF0ukTiRcgEHVfHSiU3mA6FqKOduXUcqh45Fdpr1t6EaQM74E/Q/esil8bc5Z2gm6KwQZuWTJqjK0xcF2IfzPhMpYv6A8RFfJxN
*/