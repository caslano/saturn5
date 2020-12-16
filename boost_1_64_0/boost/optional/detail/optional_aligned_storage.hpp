// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
// Copyright (C) 2016 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//  akrzemi1@gmail.com

#ifndef BOOST_OPTIONAL_OPTIONAL_DETAIL_OPTIONAL_ALIGNED_STORAGE_AJK_12FEB2016_HPP
#define BOOST_OPTIONAL_OPTIONAL_DETAIL_OPTIONAL_ALIGNED_STORAGE_AJK_12FEB2016_HPP

namespace boost {

namespace optional_detail {
// This local class is used instead of that in "aligned_storage.hpp"
// because I've found the 'official' class to ICE BCB5.5
// when some types are used with optional<>
// (due to sizeof() passed down as a non-type template parameter)
template <class T>
class aligned_storage
{
    // Borland ICEs if unnamed unions are used for this!
    // BOOST_MAY_ALIAS works around GCC warnings about breaking strict aliasing rules when casting storage address to T*
    union BOOST_MAY_ALIAS dummy_u
    {
        char data[ sizeof(T) ];
        BOOST_DEDUCED_TYPENAME type_with_alignment<
          ::boost::alignment_of<T>::value >::type aligner_;
    } dummy_ ;

  public:

#if defined(BOOST_OPTIONAL_DETAIL_USE_ATTRIBUTE_MAY_ALIAS)
    void const* address() const { return &dummy_; }
    void      * address()       { return &dummy_; }
#else
    void const* address() const { return dummy_.data; }
    void      * address()       { return dummy_.data; }
#endif

#if defined(BOOST_OPTIONAL_DETAIL_USE_ATTRIBUTE_MAY_ALIAS)
    // This workaround is supposed to silence GCC warnings about broken strict aliasing rules
    T const* ptr_ref() const
    {
        union { void const* ap_pvoid; T const* as_ptype; } caster = { address() };
        return caster.as_ptype;
    }
    T *      ptr_ref()
    {
        union { void* ap_pvoid; T* as_ptype; } caster = { address() };
        return caster.as_ptype;
    }
#else
    T const* ptr_ref() const { return static_cast<T const*>(address()); }
    T *      ptr_ref()       { return static_cast<T *>     (address()); }
#endif

    T const& ref() const { return *ptr_ref(); }
    T &      ref()       { return *ptr_ref(); }
  
} ;

} // namespace optional_detail
} // namespace boost

#endif // header guard

/* optional_aligned_storage.hpp
3S8jb0gTapR3GyNcr77a+5nrdivzU30xvrMWVHu/2f9b2fsMBP6Dx6Az4258LplvnOPuk/LeCSTpcq+lWG+YACdIuY53xtb7XeWakWV2YurWxu111xpnaz+jvMpTwrMDe/H2xl1L/fd9WZ6z8jLo/lDK9n1UfzUXPJA3PzKq03X2QiH9PNffiHDyckq7r+yZF8Jyz//Erx7MesmHuHePPSR2V5u8W7vxOAeRPz4zP5MActdQ07Sb46TYz86FULlr1vFbNxCemLnuZtF9l5yTkO84aPsa6GMC4WRps82e52Pu0narWXmtiZnz/jKdYZsONvDOuKd2d8yqRI1tQUUF4s8MtJW52s1KajXcFdaodH0Rmmud7UntrrdVyGqRpx+znP1G2C5UbvR9TUmsCpXS7wFCkPdsJmSNCYRrWtrpb4xF2CBCbZf3nMcu1eEkXTNc9xmgmc63cW5gHdWZ9yr5S9AyFDS3D8hVonssEpCffOfJXHLh7jsPv2MiXSd3HyxCDVT3R7zo1SZ0pQW1C2fta5H2MxY5K2i1RAW3DwnXu30E9pPeq90Ms5IplXpWEc92I+HotDxv+pqsSa42M0vbV/VsM26/zypDymaotM/FPFedvvZmAmoiz6Zp3n1t60K6v2usn8cJlv1f1ZvT/6r0J0j6MdNpUOlKkHS571gp9n7uvMiWedHN6rzyS3nri/UbLfBe71acMpqj/SR41hPhXfuditTTQu2mg1WMfqU2KrieJBwp6wb63HTGMIwD+4vrafv1Vrg6yYdqjxqDWuC9PuuEF9Sunbafpu3LWaVd30rJ0mb91Zl8vYeuLUr5H6o3mIyYlOmSm9a4dd/32Ujrfbp/OE5bWf2e6R9iQsrqb3aoU4XRYSHqc4We+0h64999v9oprY/U/YJz519TwmuGao5qUej636SXuYrnO5WI4HcqATlT5Z8g5e9+zo/8wAT+vY05/E7G9NZBt0w5n8ZxRlFBaxZaJsK0n8/sibbnN7UJM/g72e76S33ZlJePnXhVKPMSyHvEBxa26lsZ0/V34qrxPQ4fHM7XR6pTC4mx1nXv5HS/k6X/1QWZGWfUpzc0ngotNFKnzcqYNCl4nOE+w9LwY+Oxg+xnaSPlmXkoX3nKcXrv8pRzlNpPPdu2Q+Q7NU44j7nLVczcZ8vl/LBrHFDpFeVGnW0P5c1kpcBcppc2Tw86l+6ul77aTR969dTcM4vIGOdxA3s1r+o0NMWFz+VGziuLfJzQbt7VJ3F2WeGBecn72jzMPWcKjCEWa7sq9s/YSxqdcPPcldVcpzFK9OxE1/q4QLkV0fpNkjanjHL3kKZo+wa0t/BAnqpps6XkKFrilnw7ZStxv6vTOBJ38VYxTIPTEJij6cp26mSKtm+m7xdj7OOKg+8pmG3WgbnigzqOdcxzwiy3LJ+JMw+imYr/w1yqsPucltSpe9y87ZzxXNY2z5wUm5IrSriH88mzCLL7XZ9Th3sOG9mrZpXx6BckLJHf8eZ+DXm5ltu3dNVunmfdt1Hws8YJwz0W1mVt6qmUtKcE7aakHaFG8Kg3UD+g5B27hFEpEK6Y5Tv3ZU4Neq9pO+7dY+jJelbulEVbbb/fmixtKcu1B9zZk7xQu5mi194qk1/nXEqaNn+VMutv3WXVdz9zAjLVSrv5nh7Cbx1EueJQa1SBc1jDtbsHdRwdiUOfW3DFkYhNaauFisd136HUsuvdai3t3rJjcF+C2nkOX055NtR2v+v1wib0i8c/lXtthkan5C7thXrutcg6nPcufyeMiHMSRqtrh+E8z3vpMJLdz1sZh4u6oT2RoYUuHA7u++U9beC5q+Q2wSW3ie79jy5ZTHTf3y2ylP8=
*/