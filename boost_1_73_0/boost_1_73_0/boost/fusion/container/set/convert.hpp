/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09232005_1341)
#define FUSION_CONVERT_09232005_1341

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/as_set.hpp>
#include <boost/fusion/container/set/detail/convert_impl.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_set
        {
            typedef typename detail::as_set<result_of::size<Sequence>::value> gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_set<Sequence>::type
    as_set(Sequence& seq)
    {
        typedef typename result_of::as_set<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_set<Sequence const>::type
    as_set(Sequence const& seq)
    {
        typedef typename result_of::as_set<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* convert.hpp
Fi+hOYAvApkB4CYL4ugN0BYsE+laIgaS56GMGX/kQcjnQIhnbJVlifz3+bm/SUPg/nwR+/LcL7v/ZpWttz25AybW/JnFScaymG2kOGX45Clbx4tgib9BIHAx2czDQK5Od9wAqWhxHqdMijBELGgXCJmzLZhTiOcUH2MJcBxk+EvGkURST6t4XXkQ5Igoy00aASGQAzy0iEHMp2wDUypVD6uelyQKmSoBHxyaHb8LFkfADDvRHGY4J2zOZSBP2RfDvbFmLvui2bZmunfMGjHNvEOwz4Y5hKEPgFjKxLckFRKIpyxYJ2EgFgXNf+7r/AXMfvafv/nFAOe8OVNucBz8lC9REn4cLYP7XDWX0CMwPY0GOcw/wQ3inP3Nr2avRrrmzmzdOWWjmTlwDct0cmUb6iPDNNSFppHIYf4JbhDHtFz938wWS1AQNRFBaVE136z5w066Ml6LUmmXIb+XbC7C+KkEQUUPpJq9fhw/4CSSmySJwQbk3P6wUT5F+Yqh4WhXYx18hvXZ0J02jPQ5yeL7lCdgahjfANUoC3yO9qML0L6bupanzdybFtChMXA7Gpe3a61GxljvaFXerrdyp12N8ru1NjduZ6Pydq3VeKh1tSpv11q5+tjUu6Sxe6DesrtrbnvfHkU6j6VgaMgi
*/