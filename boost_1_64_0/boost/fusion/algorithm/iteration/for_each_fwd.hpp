/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOR_EACH_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FOR_EACH_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct for_each;
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence& seq, F f);

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence const& seq, F f);
}}

#endif

/* for_each_fwd.hpp
BdzUL/Bp+NN0tPnIffDoBuSrocSZzWLyVm0ZZd/DMp4KXxYeL8ffswVQJZdrNFgkoAyGt3FayNXkbKbL+/dGbWQ6QorQccrSeIb1a5amuFBiQgR6BFxX891vC2NR0m7r3bdUWKCoBkjROC44HiyNGvTppvXOoNp9QDhko81q2X17lAFFx9DPgKAdmhw8Mam48/c+ICYOWM317YnzRyi1POetU41L+qSFyo2CZ9XskUgSxghKrCJMBke/+vclW/zPNbq6qmWYlrkkGDIWtq6gW4FdIOL1oFG3njhcemtjXVH2RNNPrPDSCy0FMCd+hcSOSTBd+SLtd5yvI5gwmF+yRbnq2MxWmgSL8EKo48lGLeWTXtbTvOCnlWInKxJ4w4OYkSk4fOR53d1gO7r+Sg1WmS1i1aJGuHYaoWeSZ+83DsB8zKjyNOnshU7pNNG8a8iLOSNQdIY8nvMjCJ/U1b9DSnaHXOwHMoJrybKoK6nD31DPzDvZAGR6m7ndF9p1M+qqHS0XtQS/sK8lGut0Xf0r8ToRgXvDdzpWc+rMc0l8xc/WSY3bHRdYO7MaOg==
*/