/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_MODIFY_KEY_ADAPTOR_HPP
#define BOOST_MULTI_INDEX_DETAIL_MODIFY_KEY_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* Functional adaptor to resolve modify_key as a call to modify.
 * Preferred over compose_f_gx and stuff cause it eliminates problems
 * with references to references, dealing with function pointers, etc.
 */

template<typename Fun,typename Value,typename KeyFromValue>
struct modify_key_adaptor
{

  modify_key_adaptor(Fun f_,KeyFromValue kfv_):f(f_),kfv(kfv_){}

  void operator()(Value& x)
  {
    f(kfv(x));
  }

private:
  Fun          f;
  KeyFromValue kfv;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* modify_key_adaptor.hpp
y0eVW2GTPbESdaAo2pwxQgoMrkFviN//QnTm2Hs1xThQUmJxf2axoW56Fbn/ynIyodKspDy/TZaTxE0++YdWHIzx24AWJQ/R5TGJkbNcy6MIH2GOeGWyWFPfr8lpwGK58r3Ry9DuJjisdHtRewzJPRBDcruWYSCJ4PUuucJFai7J/ASSMvITSFm84mKtl0xlr6DyC0okX8UBUn0pHdqg5zQFFW6M0xYl5Z0mpenCKEJrB7/XlKZzrciIHHNpmC1L/jqe63yZyuKvXIxphGp711cWCsO/FjkUT1K+MmKSRbsNIHeuZBkKZqHdbhoUGF0eSmdFmMI8HoirZ804soeoAMnPDmRHhhiJdoAiMY9a3u3eifj7j+u844HpeTBplHc0rNnqcpHoVln1NOWrAV7Bl0syZKleCrxI7Qc63QKleZH6p4YjPS3nEvHsszFZHRAt5SryDUB8x5GAEW+7x5hJspyKHGQySvVQdZ8dcEUgpJORrOt7lgOjnjeV3zoRhUAEOCOAU0z233cT2sAlCEMbquMi1QKbv4ZfHFZ0RrUv3Shk+dvtQzY2OOkoP9WyGD7ppnYFZuCXX01N2b/oKdWO79HxBiMNFtN7/OMVRhYKIgs2ax1A7Cju1x6fY5RQ3OZANo9omPGgRllADM7ommAGLVQPGIQ0Du2N+hL2rVHGRYYSHnjk9ZzwAN9Ac7XYh2HMrmUWxvq19MJn12KL
*/