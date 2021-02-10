/*=============================================================================
    Copyright (c) 2012 Nathan Ridge

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_SUPPORT_AS_CONST_HPP
#define BOOST_FUSION_SUPPORT_AS_CONST_HPP

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion { namespace extension
{
    // A customization point that allows certain wrappers around
    // Fusion sequence elements (e.g. adt_attribute_proxy) to be
    // unwrapped in contexts where the element only needs to be
    // read. The library wraps accesses to Fusion elements in
    // such contexts with calls to this function. Users can
    // specialize this function for their own wrappers.
    template <typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline const T& as_const(const T& obj) BOOST_NOEXCEPT
    {
        return obj;
    }

}}}

#endif

/* as_const.hpp
Ka/jeBvRLWvjn4iRtzEvaYdgjBya8sHKu9zDwfAQ3p2cvIe3cHx0fBTCSGiJCuYe9QrtXQinab3zKRebTc/hxxDQg1C91tUilw6cyfxaWARaK5mgdpiCcJCiS6xc0YPU4HOETCqE4fRqOZ58CWGdyyRnJw+mApebSqWQi3sEiwnK+8ZHKawHkxGcnKfSeXJYeWl0j7gRPNrCsQ+mF8oZEPdCKrEiIuEh9750H6Ioqawi9VFqEhclT8fv5b54PsmSRBTiAUzpwRuoHIbAliEUJpUZzxQQ2iyrlZIuD1/UEJVOI2PBoVLsi3ASXSMbYd6GJ2QzKEmx9Dw5ox1TrXNT/GVIcWQvWWU1EVEcyCg1FOYQKiojWxvXJ3+iaGNaB/i/qXnRm4LRJAb2BnMYz/dgJZx0IdyMFxfT6wXcDGazwWSxhOk5DCZLdvZ1PBlR6iWRWcBNadERuQVZlEpi2nLubkRBsNPyryPCbYUiKH9USKnyVbljyRTeinoF01zNposp/AwAklxY6JbC532IunW2+AHWSFcNraDbQ8kg9JNpZhGfzUsjteeMmxoplDKJ4ASuaPGdnRSV88CYsKmRgm928GpXoGucka/Mtvdtn2n2nzlqDbSELO037arLEnVTtk0xl97UYiyKtHb0hmG/
*/