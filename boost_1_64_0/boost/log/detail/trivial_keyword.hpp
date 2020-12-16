/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   trivial_keyword.hpp
 * \author Andrey Semashev
 * \date   02.12.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_TRIVIAL_KEYWORD_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_TRIVIAL_KEYWORD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace trivial {

//! Trivial severity keyword
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)

} // namespace trivial

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_TRIVIAL_KEYWORD_HPP_INCLUDED_

/* trivial_keyword.hpp
3/+/FPD9/y49wNeMi0jRbOId67rWo/RYV+DyymHXV95+nTf8S/Y41cisr7xomFc21qyvvErSTDHrK08fgT9gjdb+4ncrCW/8lvMYGWmVtL5ygsTtZtZX/pMui28MbZnE3+96yzoismSTH+vJ+9dY1jKXkngBYWxVx3nsjXRLnlegw1DTU9kFaay91cT3nTudNZZ1+OJjTsYWemvRebu8OiRrEFcwcS61R7K7lC8tv9x5DD81oNwtrDiVbz9u4vrPWUFj5COkrP4x8tbSBqlG5sZdIbIUpzWZzZoRL0rfijF97UPJ63NVm3UjfO35tqTTwUpHg/K1p5J412Dd7e7ytd8RCTcG6+9gUx+fSHo7XUusA5ZvTdjDEm6jNbmE/dmmD5P0+V4uRn+z70t/otWLVcBeQfvz5bFF5Iesx62QtZhNn107nDAB6xxHS/m7m2/yXxf/BjuHmnsYTfhv1ov6nC/f51lrerXkO9qqG3bvs07F8omVPt3TzDNYIPXx3T/ZOxPAqIozAL+XhJCQAEkIIRxCgKjcBEgU5DBIkADhjhAETSIJkBJCTIKNFTUonqBNLW2p1YotVFRqo2LFiko9Wmux0opK1Vpt0dJKLaUeVOnx7Z9/Z3ezszkA7eE+/fny5s3Mm/nfvNk3888R+Qf3PfSBn8B3Q/0ZN1KT3nRdZXOvX0lcEcZGskzykBbR3vmjWT85QeKZ7fTQd/VWCfNe5GjCPU8t91v3L67tnrjh3+cWSYnQ9Yz12W+LvIJnGspec6PcZ2nEJc4Vbm9x85WZ9vQc/Nw51c2NKETjW4PWP/bWaWtF76ucFMtz4BmY9OzEnatugxt67eM4uffHEXOc2yO8Y3h+Lm6PRWCb4S5r3WERq4y9+BOJc7s+x8D61FfW40Ksadz6PcYkXr/z5RU+u8MFFcF91edVBPdVz6gI7queXBHcV31ORXBf9VkVwX3VIyuC+6oHVQT3VaeWB69p3MnnZtIc5XMzaT62InhN4w98bibN7/rcTJrf8rmZNP96xf/OmsbHMwenrf3M9rWIj28OTqWrv0H6DVMEByMlzax9eRo8FY6Cp8HV6n6lntfD0+E34AD4CBwIH4OD4D44FB6Cw+DfYAbswj1HwBw4Cs6AmfA+OAY+B8dqf+942EHXtuwEJ8NkeC48BU6BZepered1MBdeB6fBJ2Ee3A9nwN/DmfAPcBb8J5wNT9U1LgfCufBMmA+z4XlwClwAq2EBXAMXwq/B8+E34WL4PvxCG+f4bA/3wYWP8BE+/g+Pz6j9v2RF9cqTMv7/ab/2/0Ed6LdXbJgQZvN1krbctP/13jKc1tr+7wavEf8r3Declbb2OvGZdi3t1IC9101bYWWZx89YW7ua8PZ2tZl7YPwUmHBet7bM1ce/rT1t2qLD5HoX27hUCduW/YZS+atKwlzhznE7BrULvW2Ab4ifhe5YJxb7aRQ2w3VBbbsU9Xud+I1yo+hbeMOJMm2qCeL+gDsVtyS3K2vwLzPthi2i9yFGj7Xit9a17JUjOnhS/Hcipkjc9NlJmMW0e+a6KdquO0vcfuiOoqRe7XbRshPcDhsh/ka780mxuHG2Xtxm8wzHNm0vmXXlviV+znPPJP55pOZ+9NKBto7rtG5evLc9s1fyo3sSlwV/t/fxuZm2Rlefm2lrdPS5mfE90T63kaZdsdy4mfbHEZ9bhpRp3P5k3MZY2wq6HzHf+a3bj7it8/hPZtvgsHzrv7P/a2XP/O7nnxy76rkV58SkR7S9zXA8bYPN3ndT67cMmIhsdHz7THSAKdDj3g0WwFS4AnaHldqG+CLsCRtgL/gAPEX3++gPh0BpU8DT4FQ4AM6BA+ESOAiug1k=
*/