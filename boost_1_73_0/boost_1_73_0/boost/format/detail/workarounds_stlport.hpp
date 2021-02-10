// ----------------------------------------------------------------------------
// workarounds_stlport.hpp : workaround STLport issues
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// see http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_MACROS_STLPORT_HPP
#define BOOST_MACROS_STLPORT_HPP

// *** This should go to "boost/config/stdlib/stlport.hpp".

// If the streams are not native and there are problems with using templates
// accross namespaces, we define some macros to enable a workaround for this.

// STLport 4.5
#if !defined(_STLP_OWN_IOSTREAMS) && defined(_STLP_USE_NAMESPACES) && defined(BOOST_NO_USING_TEMPLATE)
#  define BOOST_IO_STD 
#  define BOOST_IO_NEEDS_USING_DECLARATION
#endif

// STLport 4.0
#if !defined(__SGI_STL_OWN_IOSTREAMS) && defined(__STL_USE_OWN_NAMESPACE) && defined(BOOST_NO_USING_TEMPLATE)
#  define BOOST_IO_STD 
#  define BOOST_IO_NEEDS_USING_DECLARATION
#endif


// ----------------------------------------------------------------------------

#endif // BOOST_MACROS_STLPORT_HPP

/* workarounds_stlport.hpp
Uht0vA0bQVihW7QIB+t2zZks7WdZSFiRsWhAUs57OExlVHZToBD3btk6EmpUz5RupKikZrsrxWYnEG3tgYq2qZAObcE4ItB4G9qK0MbEGyO2LL3LxvJvLNmzdgKiQlUwcGPw4wGsM8mkDR/95CpcJPDRjSI3SJYQXoIbLHu8az+YYm0wZG2A3tcNlaiiAbapOaNkh/yH7nTLSa5gsohm4TxJY8+7nrqJC0cwOPwN/morXde/DmDA2VovPBw7R8fOAQ7op5Rm8iGVVOklxh9Wk0TA+AoC971nfYG62oe8lQpXphasQqexKqXsFkLbLSn9DHnG+TrLPxuceBmE89iPrZ9YlfOWUDjTxF0RlueW4cgFjr/UM9RvYK/E8uBYJS+12HArGIG9Xsjo1NBNvXgS+fPEDwNrmqkMVoXfR6yKuZapBX9VLpZVlXf7yS/MTsSC12EWYvyf/XIRTDTB8GikMTvb7G5f4lcDb91BlDecw40+MqTFqrpVTq/z0l3MEqtnIqJ6o1COMig2BIvZTGPturtV2kHMozAJJ+Estq6SZG7Dpb7FeDdvvb/d9/OZZzlVYUmVKZbj6aPMjNN8Pey8wwk2td05L4oi1edLgSpsEyvwXGDVyPrHAsCt0eKfAtGW7hH4A4Y7IyODdIqB
*/