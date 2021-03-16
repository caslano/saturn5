/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REMOVE_IF_07162005_0818)
#define FUSION_REMOVE_IF_07162005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct remove_if
        {
            typedef filter_view<Sequence, mpl::not_<Pred> > type;
        };
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::remove_if<Sequence const, Pred>::type
    remove_if(Sequence const& seq)
    {
        typedef typename result_of::remove_if<Sequence const, Pred>::type result_type;
        return result_type(seq);
    }
}}

#endif


/* remove_if.hpp
OvzMK4frCdFg5njrTyLqr7J7GoMx15/YK+3eZc87rr9llqcxeZqAqWiUJ65KwAH2NAUjZ71Z/ybkeReMeZyQb4fPOfY0A6M+//wueZqDMe8zRh55to49LcC0UMrTnDzvgSki/uv+Tksw6v2d98jTCsx/73dag/FTPK3I0waMHEXpB/Jiz7EbLdnTFsx9zZrvbcjTDszHQn9+o0HpoZ3Y0x5MklKeduTpAEbeoZBjaOyuxXHs6QhGfu+qn+HpQJ4=
*/