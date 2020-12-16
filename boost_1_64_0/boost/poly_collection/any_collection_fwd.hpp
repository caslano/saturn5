/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_ANY_COLLECTION_FWD_HPP
#define BOOST_POLY_COLLECTION_ANY_COLLECTION_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <memory>

namespace boost{

namespace poly_collection{

namespace detail{
template<typename Concept> struct any_model;
}

template<typename Concept>
using any_collection_value_type=
  typename detail::any_model<Concept>::value_type;

template<
  typename Concept,
  typename Allocator=std::allocator<any_collection_value_type<Concept>>
>
class any_collection;

template<typename Concept,typename Allocator>
bool operator==(
  const any_collection<Concept,Allocator>& x,
  const any_collection<Concept,Allocator>& y);

template<typename Concept,typename Allocator>
bool operator!=(
  const any_collection<Concept,Allocator>& x,
  const any_collection<Concept,Allocator>& y);

template<typename Concept,typename Allocator>
void swap(
  any_collection<Concept,Allocator>& x,any_collection<Concept,Allocator>& y);

} /* namespace poly_collection */

using poly_collection::any_collection;

} /* namespace boost */

#endif

/* any_collection_fwd.hpp
v8Ua6j1TrKPue5v1081aM70DfRiE+39cL70LvRiqWCs9Mmm99DxKqFwvvR9WDMM5xXrpMWRQhGEGYZ5irfQ+DMIGB7yT1khPY6xiffRGtKAdXejFAOz/p7XSRxFDBrlJ66TXVqyV3oE+DMIBNwIII4oE0ijANPOf11DvwgCGKtZP9yM+xfrpdUeR9mhDD/oxDB+CiCEHw6Q101vRgW70YRA2OOCGFwGEEUWiYl31Muor1lPvxQDscL3FWuql/3E99SBG32ZddQua0DppTXUHAoiioHXTayatnd6OLtjhgn/S2ulZ5FGCUeunN1esoW7F8KS102PIoQjDbNIclrdZL33yOukFlCvWSW9Ey1usle6BH5FJa6WXYNRa6Q2T1kv/l3XS/80a6bUV66R3oA+DcMM7aa30AsowzfnnddLb0YsBDL3Neul5lFCtNdLbKtZJt2IYTozAh2DFeulFGN5NmGFBE1qnXjNd66UTbkSRwBgKKMOktdMb0YJ2dFWso+6CZ9L66ZPXTq9DA3oq1kkPYhQx5GDQ2uiWSeujD8IGN7wIIPwW66I3oh1dGIAdroo10ONIIYs8SjBOrIs+xZrow3DCh2DF2uiZirXRzVobvQmt6EB3xdrobngRQLRibfQCTMeTtpPWRR+YtC66HyHEkUIWJVRXrIfeiR70wwkfghXroWeQQxEGrYluQRO0JrrWQ9da6AhXrIeenmJN9Eb0/uua6FoPnbAiW7EuerXWRG9GP6wYgW+K9dBzKML8PsL6b9ZDd8NbsSZ6GgWUUd9AmUU7utCLAQxNWhNd66FrLXTC+TZroY8giFHEkEEORRi0DnoTutGHQdgq1kAPI4oCypi07vmUa55PXu+8NGm982b0TFrjfARBjCKGDHJa47wWFrSiA30YhO1t1jufWOu8ES1oRxcGMFSx3rkfIcSR/S/WOX+79c1zWt/cPMUa531TrG0eRgJplCvWNW9HV8Xa5i544EcEKWRRQnXFmuZt6EQPrG+zvnkMSeTeYp3zVnSgG31wwIsAokhMsdb5xDrn7RVrm9vhgh8RxJFCdoq1zhvQXLHGuRXDcCKIJHKT1jW3TLG2uQ3e/2BN83o0ogXt6MIA7PAghBSyyKMEYwthRR0aMHltcyuG4axY23z0LdY2N2tN81Z0TLGuuRdhRJGYtKZ5jdYzb6lY03wIdnjgr1jPPIU8SjCeQfhRhwY0ow2d6IEVzom1zadY17y2lTCjA91TrGUerljPvIAyTIsI65Rrm//ruuZxpJBFCcYp1zXXmub/w3rmreiADQ54J61n/i9rmb/NOuYueBBCCnmUYFysNczR/Bbrl4+8xbrlORSnWL+8Ca1vtY75pDXM0xibtIZ5TcUa5l1TrGPugR8RxCvWMS/B2E580IDmijXMrXDCN2n98iS0fvnbrl3ugBteBBBGtGIt87Ep1jJvQRcGYIfr36xdXvcJwvwW65YP/2Ptcq1bPmnN8iIMk9Ys70YfBmGDA254EUAYUSQmrWVehqliLfMWtE9a03yoYl3zECIV65pnJ61t3oA2dKIH/RiGEyPwIYgkcijCMrGu+RRrmocRRRpjKKBcsa55I9rRhV4MVKxtHnqb9c2rlxJWNKMH/bBWrG/ue5v1zS1az7wbg3D8B+uYT6xh3ogu9FasZ+6CHxGk/s1a5s3oRA+G4YQPo0gigxyKFeuZWyatY26DY9I65lEkMPY2a5h3YaBi/XIP/IggjhSyyMOodczb0IP+yWuX/+u65QSQ8KIWFnRgEI6KdcqjSKMA07lvvT75EFzwwP82a5TXaV3yNnSiv3Jd8klrkieRQRGGLxBWVK5R3o2+t1ifPFCxRnm6Ym3yGq0=
*/