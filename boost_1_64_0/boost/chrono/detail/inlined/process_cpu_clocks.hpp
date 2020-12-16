//  boost process_cpu_clocks.cpp  -----------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//
#ifndef BOOST_CHRONO_DETAIL_INLINED_PROCESS_CPU_CLOCKS_HPP
#define BOOST_CHRONO_DETAIL_INLINED_PROCESS_CPU_CLOCKS_HPP


#include <boost/chrono/config.hpp>
#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)

#include <boost/version.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/throw_exception.hpp>
#if defined BOOST_CHRONO_PROVIDE_HYBRID_ERROR_HANDLING
#include <boost/system/system_error.hpp>
#endif
//----------------------------------------------------------------------------//
//                                Windows                                     //
//----------------------------------------------------------------------------//
#if defined(BOOST_CHRONO_WINDOWS_API)
#include <boost/chrono/detail/inlined/win/process_cpu_clocks.hpp>

//----------------------------------------------------------------------------//
//                                 Mac                                        //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_MAC_API)
#include <boost/chrono/detail/inlined/mac/process_cpu_clocks.hpp>

//----------------------------------------------------------------------------//
//                                POSIX                                     //
//----------------------------------------------------------------------------//
#elif defined(BOOST_CHRONO_POSIX_API)
#include <boost/chrono/detail/inlined/posix/process_cpu_clocks.hpp>

#endif  // POSIX

#endif

#endif

/* process_cpu_clocks.hpp
cWASmAhWAJPAiiCcqgJWBlPB6iDcjJpgPbA22MjQ9k2+2yOthX3zDtbbnbSP3gUm0s95e/kejD5A0vvO25tmuMbZtTDPC7YC20g81/jFNoar/tuBl4AXgb3A9py3uCM4AEwHR4CdwLH054O9wY/APuAusC/4BZgB7gcv43Xepd/F8A7IfJYDpzOfObieSuBIjrMczXGWY9kPjeM4wFxwCMef5nL84J3gRPZHeeAijh98jvFe5fjB1+l3l/tClnuyRblPZ7nfwPGYN4IJ9DM93lXsx2P2N1zpr2R5XwW2BweyPOYpPluDzzF9LDiT6VdyfOQq2rNXc1znG2APmfPXVT9o81Ivb3J85DrerxvBfHATx9Wu5/zBb4EPgG+zv34HfJrxF9HP/PEZEpsRmL932b9t4f39AXgh54nuw3HPV4A7wKHgR+CNDL8V3MnfjV3gw+yHn2I/vJL973vsf7cy3TfgPu/5k0u4b25m/d3C++ZWMJH+RMfp7fRR6zBf7Lq/vq0+5Pn/nb2+67qIP91mPxDnnAo3G24p3Aa4fXCn4BLXw2YP1xVuCFwB3Ey4RXBr1v81bflns/1J9v/ciaPO3f5v2vGPlVfy/lQ3+P501u9Pf7f3pNLM1b4YDv3MX7p//1/17Wfbr59Nnx7cgltwC27BLbgFt+AW3IJbcDv77U96/x+JF/jzNv5/9mKv+f/l0K75//d7jf9f6qAhljb5RmALGH1OfO2t8ZfEKl7b2U3vhKzxOdruy/g1tY084RvTn2iU02nGTxyR49HQxsr+3eLvpdOncr+hqhyj1sFf18/0RyR9C8v4D8qVSZa1zb2mxC9nUAdt7s/LFPkQ4lCH0Vji/EfVgO26DPxflnfZ5ffAiaaeNvrcUtjnk8Qe77a/6/Lys8uzTKALlvwh/OoEl78z/fVTXP5Z9Leif76f/wT9bVN8dfUHqasv4Df7MXDXJKJtHPOt3zyEx0vZUf+TkzXeY9dnfC99yovi71Wq9R1caavo9R2WiX9Aies7rDnm1jRFUkcu5S9aldxSaMeSqCnA9aCcXddzJus8XBRiPR4h7Vtdbq5bqtTjHGLkuEdsxiOkf1v68QiIW+J4hM7fnp/xCAvc2tsQXKOQmvRDklfz6kuaF4Px6mj9UTfx/+Bs6wy306UzTaqlLr0CmCH7jzprOROpt3KnSbPTpXN/I63h6iP+Y842TgfP49v+EsEuEudnZ2tntHef4tKoURfX/7AZ53oVCYtxS15zT0l33NkNLaYf3Bi4KXAz4R6FewZW5T5GH+Mth0O965isxxyMP+I/p/gkQTzrNFL2J0j9uMf+TJSwMlL27aRB5aHuOkv/Mlvy8S9HGcRPVDGqPtgK7AMORqsOMcJVf8cF6gYHjufpE0d4nzP3K+nTcdZQHHdwXCTCDpWXPlA4Oc6nj5Rw3V+Woo90a+JXyHV4/Hcd8WjkTx12a8ybtVYMO+kJ03r47z1hWg9/0BOm9fBzv9Ka9TR32NeHAjXymxHmr4dfpMNaiX+69jcXP+rDfWxbPZa/Hj7DQg8/0E8PX45pUcdmmPT397jOrTqw/3+E/k70L6O/fyWXfzX9bbl/G/1d6N9L/8X0O6ScYLvk3OYxfv5qfv6B9Hdn+pFf+Z5vGv096L/bzz/osO/vXegR3/xHH/E9XjL8jO87FogmqVxqf0dSwzbsa91nlbimRb7EG+S9pgXTxp/2N8dv7IDk8/Gvfa/jWfrb+uU73WtO/gST1LXOOKjzfdp5aVxxG9mNHeD+mv5jBfT9Pk/2t5BfavatTJPMNIFjdR6S/UNVQ1xLJ4TGSzhUlmY4/NEqVOZVGYh6KYzkOMkBkXVlUpXA3zj9W/E=
*/