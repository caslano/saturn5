/*=============================================================================
    BOOST_PP_VARIADICS version of BOOST_PP_IS_SEQ inspired from 
    boost/mpl/aux_/preprocessor/is_seq.hpp, original copyrights goes to :

    Copyright Paul Mensonides 2003
    Copyright Aleksey Gurtovoy 2003-2004

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_PREPROCESSOR_IS_SEQ_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_PREPROCESSOR_IS_SEQ_HPP

#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#define BOOST_FUSION_PP_IS_SEQ(seq) BOOST_PP_CAT(BOOST_FUSION_PP_IS_SEQ_,       \
    BOOST_FUSION_PP_IS_SEQ_0 seq BOOST_PP_RPAREN())

#define BOOST_FUSION_PP_IS_SEQ_0(...)                                           \
    BOOST_FUSION_PP_IS_SEQ_1(__VA_ARGS__

#define BOOST_FUSION_PP_IS_SEQ_ALWAYS_0(...)                                    \
    0

#define BOOST_FUSION_PP_IS_SEQ_BOOST_FUSION_PP_IS_SEQ_0                         \
    BOOST_FUSION_PP_IS_SEQ_ALWAYS_0(

#define BOOST_FUSION_PP_IS_SEQ_BOOST_FUSION_PP_IS_SEQ_1(...)                    \
    1

#endif // BOOST_PP_VARIADICS

#endif

/* is_seq.hpp
8ie5DhiMPxWdsO8i82krdZ3B4CR9T9sk7pVsUpwUdRus9UOUiFEmAv6fLidmaZkZmSVgcaRUnBmmBYslw1S5mGSVT+HjjKeIXbpHpKodnxF/Ujgl5hl6Xgs5R5+mHyMWgzj9tyfpV9Zi8ow3cDH9PhuKbnmaZCrUTBdol0yxxQwC7ywSvX1AHL9ZfelJLPMsV/fLIvG5nz7/dhE+di3SPqdpY19UIMvnSt5bxD4AuJZUke53d4APYJVWWgUR5mNPNScc9E35olAffmhQQer1lsw/uklpS1mO8j26vBIM4XGKblCgBWQsKCPGvUAXkBQg4241M6dmg803DmQ2ceA5sTAfONyd4GKmoISC8BwVTWaJEkRsawBfhI60UNshaDeVoasprKIoR1mfy1UUSZ9kAPVFAPUZKHv1IMg7wc/5rwTyDnXo82hgYyW3+WBh02iw2xElGOTvmgaGO2VTuWnvNJJJ43gLp0lJbqEmvAkR0JQBJO4Zih4fYC4plCFG7ELAS3xUgqD5UVzcPx+hFTv8CHqMDTyi2bnEG5aF5TTPHeoWGoz7+xxcGYoTn6HJ5VbeR8uSoctTMnBZlsLeEFy72+BXQfxCpwov3qfhVEdk94oz7gOcE20inFPgppDQhegHHNmKkaL6bHNpWiGaXkhPi5mIzfKnkVa4kz9z4meZHGmum9mw9CVkWOJH0xvLfYghjmpeMk8L2pu85FwK
*/