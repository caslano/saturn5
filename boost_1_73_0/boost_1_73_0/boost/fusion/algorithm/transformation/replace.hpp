/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_08182005_0830)
#define FUSION_REPLACE_08182005_0830

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view.hpp>
#include <boost/fusion/algorithm/transformation/detail/replace.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct replace
        {
            typedef transform_view<Sequence, detail::replacer<T> > type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , typename result_of::replace<Sequence const, T>::type
        >::type
    replace(Sequence const& seq, T const& old_value, T const& new_value)
    {
        typedef typename result_of::replace<Sequence const, T>::type result;
        detail::replacer<T> f(old_value, new_value);
        return result(seq, f);
    }
}}

#endif


/* replace.hpp
98GEGvUqemqjg6cTGHl+anreJ09nt3Z2vv/1ARj1fm5n8nQBI6//yC2z1uzMwp6uYOYp7dyFPN3AxBueR/d8HebFh2DmKO3cjTzdwawS+ngeHdJvAnt6gLmpWethd/LEgPE2tpeLCv2WPT01+/yKIU8vMOb2HO2HzmdPb/L0Ik8fN8+RnFkdytNXZxRPH/LEuvW783WJj8BEKv0eS55+YOT1eTmep48oM5c9/V397md4+pFnAJjo9N9kWzcJbNQ=
*/