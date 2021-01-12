/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ALL_05052005_1238)
#define BOOST_FUSION_ALL_05052005_1238

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/detail/all.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct all
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    all(Sequence const& seq, F f)
    {
        return detail::all(seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* all.hpp
fNT3sdLBCaD3esuXKN8hf9YUf7a3kxgtvml1Mutwx8X+y95MUm8Hc4cn7KfsYBoelXzbV0YMqZFpSP8wx77XDq8Hqsk7Uqy6YfUAbsh7qzHnP5J3bLLi6TPO1nYiWH6JhbCx91VeiTtnBsfU4UtFLyVsHJQtX+jzw+xV3ilmfiGX+q2W2L/VGhhMD62PEsPsS/3Hwmio7rhOzNTDptnvZeqxsPdKC0zchvaOqX9TS7qtpkJr
*/