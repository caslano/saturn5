/*==============================================================================
    Copyright (c) 2013 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_ALGORITHM_FLATTEN_HPP_INCLUDED
#define BOOST_FUSION_ALGORITHM_FLATTEN_HPP_INCLUDED


#include <boost/fusion/view/flatten_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>


namespace boost { namespace fusion { namespace result_of
{
    template<typename Sequence>
    struct flatten
    {
        typedef flatten_view<Sequence> type;
    };
}}}

namespace boost { namespace fusion
{
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::flatten<Sequence>::type
    flatten(Sequence& view)
    {
        return flatten_view<Sequence>(view);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::flatten<Sequence const>::type
    flatten(Sequence const& view)
    {
        return flatten_view<Sequence const>(view);
    }
}}


#endif


/* flatten.hpp
KjfbrhEyDGDpFB5SMKZAc3HIMigzHexmZs/gajzpXyi+Oj8YhQr0K6y971yfMFcCpxaQnIRtxvDd9zhOUefGYNbHRmJtk2HHEiUuqYhA097EX7T7/ggX2md4K/d7owwgE3H2wstMa+APm7CXMoFsZyhkAznRWLeuqCQ79eIs0jJN78KZc4ffOhb6bckO4yyA1ynsMVgTYDhcKDjGOdUoqE0vOVHUAysZ9Ck9rqs54GEG693DP86TNMBolAx/2Ox9KMP/42P6iBtYiDmLGNXY8Th/4jhyJgcLcDLkGYKKYlmybdESR+JhBTs6swNaPY6/4SCMgGIL1DkdjHb/S4/PGK3O1aVvjvlx5mSswmRzH6ZeD/bSdzJMF06rUDMAyRDIbrvJNwszmZxJzRr5m0LLkd8ctj5m8QItnQTyxEEgT8oIpHYQYHb3on/Vs8Cf1O2PWP9klu/1wWkmXt6pHk9F0EZ+rU2/zeEHWuueFndPnITyxEEoT8oIJRICDS+aLT9/jvARsEL74piGFSfg5MzR81lJz+N+n2SL3jfae3GpHVmL+RpIxP4PIUTcBHRjfxatkExyHsfLJEPsRQ2KxBi0SLVs9yBEVxAb05jWYGF0o/Eyq2qkYfndHl3XAmsy+tYbN79qinACYnQZzFUk
*/