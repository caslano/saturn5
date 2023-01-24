/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_JOIN_200601222109)
#define FUSION_JOIN_200601222109

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/joint_view.hpp>

namespace boost { namespace fusion {

    namespace result_of
    {
        template<typename LhSequence, typename RhSequence>
        struct join
        {
            typedef joint_view<LhSequence, RhSequence> type;
        };
    }

    template<typename LhSequence, typename RhSequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::join<LhSequence const, RhSequence const>::type
    join(LhSequence const& lhs, RhSequence const& rhs)
    {
        return typename result_of::join<LhSequence const, RhSequence const>::type(
            lhs, rhs);
    }
}}

#endif

/* join.hpp
2y7H0EYNemDyFCg6heBoIjO/5rdm4xaLx0qmoiVkF936ge7WbOF+jZ67XLrJVmahCGFXAyiba62YdcGVsMH3YlNFE2e2xsRZ31NNkRObIU2KwxyxjMV0nY+cptN8Yjxt6FSs01F0umoBTGoPNRM2/aUQhKeaCSds7jk2Z26A6WIofBTY7ESrNFeQqFo8geafW/GEcps/xROa9fRQPAGLcaeVCxGkZzm8i2avQBr64At/KiIFGKEwcl5EPua4zLufijaAEGEbCv7PE8ibEVYCIPdCIvdfOiO5244huffGAxfbrRMjNeLhc0/xfR62DRkaadCns3x/Es92rRZvz7ckbQDGZiotE5sWRyCP4Z8TqIlVmVvFMXpdQ3H8cZ4ajnxcQzRetDVhTYnEpRoQnKFzP9Y5mUY1zf0UN/7Bte+R2y9xVVI/MQadBw7CpEjayX7zXSiPzRFe73kiNkfxZeYbrgxSCGIMRNpxNuMznP2wWGccrJ9wOVPalQl5R18VGkt4vnxlg8slnUE5ny3SYVapOcy0wTFg7ZgfQOOXaXCiS3MPt3lNQtfnae1ST5uT1QaeSE5sTjieSoci/fysxJbbFfflo08J9+XwAPV1uSZiASF+2KVmOvdlIWt3Vruj+7JZ4IKewxvJRflDowK5nT0yTxHtA7WBleVgUxIfdwZ8kGTqZ5sAd7ys3vGyuAMITtwxhN8BjYUPZDgfOAPi
*/