/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ANY_05052005_1230)
#define FUSION_ANY_05052005_1230

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/detail/any.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct any
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    any(Sequence const& seq, F f)
    {
        return detail::any(seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* any.hpp
BnFrwl982voY2A2wm/ewn1t1hrJs8Zwa+18Lz37+cMuGPvIsRMMrn18hrlJiQ/06i3SNuRG7CujEcadHzX5aKoKV3BeT/UPMb5WspYPG06U1iJuFQwOmFZTPGavGjRvipdJwfA8ZnhCZ+5SJrG9OZ+zHZC3Y3YDMmda60ZOc39W1Z6GDYddpRkKBVVC2xq6APsdDjcl79mB0TbLznjVFQxSvtyzzLS02KkO1IWJ3kVUtx4bnz0SKXXrwxfd7Vn5N92YxDJA1gjrPxekAgt79Z6wmSzf0DRAs6pxePS4/dHBKHLWTlAf2xw4lnCng7Sod3esepBteUGDhVxXY4C98PGyuMw8lXrBu/4JMLquQXJWG/WzS564Bu28PB188/zIufBN01X0mSgqNaQhYRb//TgFoBY44/MDNEyPnGfDB7ZWNOVOmWsOuz1Ha9xm0DnBUx7hVriJC68pGRwCWPZMJsTvXaozvJdtD8z+2rsDGSgsNU9PiFmtiWtKD2EUTCsS5ApyPILIFhu3/khUxluQry2RdQ0iOhUV3TupYiMukDp1cO90dhUKDE0DG4WxLpYN4+mmkUqKEFi1d88C2IXc10Myt5hPdUWzmAkv2R95vepbsecAXohmMmHLI7hTYBcTej8R+NrJ1eaiNvoum
*/