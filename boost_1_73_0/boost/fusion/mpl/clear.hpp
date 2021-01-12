/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CLEAR_10022005_1817)
#define FUSION_CLEAR_10022005_1817

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/mpl/detail/clear.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct clear_impl;

    template <>
    struct clear_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {            
            typedef typename 
                fusion::detail::clear<typename fusion::detail::tag_of<Sequence>::type>::type 
            type;
        };
    };
}}

#endif


/* clear.hpp
IwhOou2IRzbCKEMlatCKdnShFwMYRoA1NgZxSEQ68lCEUlSgGnVoRAs60YN+DGEUsSfSfmQihBKUowq1aEAzOtCNPgxiBMFo2o54ZCAbYZShBvVoQit6MYBhBCbTbiQiHTnIQxEqUI0WtKETPRhC9Em0FwlIRgi5KEQJqtCAZnSgG30YQfBk2op4pCID2QgjH8UoQyVa0Y4uDGAYgRj+i0SkIB1ZyEMRSlGBatShBZ3oQT+G
*/