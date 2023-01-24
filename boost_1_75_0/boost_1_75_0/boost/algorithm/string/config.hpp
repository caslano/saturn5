//  Boost string_algo library config.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CONFIG_HPP
#define BOOST_STRING_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_STRING_DEDUCED_TYPENAME
#   error "macro already defined!"
#endif

#define BOOST_STRING_TYPENAME BOOST_DEDUCED_TYPENAME

// Metrowerks workaround
#if BOOST_WORKAROUND(__MWERKS__, <= 0x3003) // 8.x
#pragma parse_func_templ off
#endif

#endif  // BOOST_STRING_CONFIG_HPP

/* config.hpp
BCmSpW4/DmRIGDVqz6it79LXOVrY4Yu3fSGtEv6t1r+Ex96jt8FfRmCWXbLz5u4PXCdWg1VSmmOliYPOvN9oWhQ4nmK1M/WtYOfdXXBL8oRun5CQbgSgmqvu5iSM7kay8DAGapsljO42aWfQlimFMeFxZ+6x5azjJTHHnTeIAiObf0RnruOBpma8Tuvv6gNqfxNl0ULDjLb5FN81uVcxaNLuS76QCDr/i2vNvUhS+zmJZhrnK573OXccrkVg0Q7bnXRP0oE8zeBH8uUgw9aIFZzrUjfVWG/8/OziHY67vmC1Te1W1h6OajKCmlzWQLU2K7tzuysxlnM3QJaoIGPC2mIYk2SSU/6fNaKKPhVCa/Gauvdlwn+RalUCxR/94JyLjfjYuxnsj6ZH1w3+PXKH36XK2/4ify3ruzRKIQnZ569kbIfCgqb9oTMpfgJkg7bnOPta1lWiv2vnnuKMVBfGziOGPSf09PEMv2e1TSDrpNq4ZN6d8nMG3sCKJhIx8/IsqoOqjsgrf0bviv/zpdTI33IZahZVhb4ctZn7h8MW1HVef8IyHht9Kv6PSKm1r0NOUEzKSO7xLInkP3pxxlxgiYCMwahr8X/OJkNmhujp+Xf+Spj7z/0jXOvkMaXpUQot2pEkCtbOT64uVyb+qu+4D8qkDrm0UB8c5aResm3RpD2SLtP1ql/37eNMhX8liFobfv42EIH4q5HrVNA2
*/