/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    remove_rvalue_reference.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_REMOVE_RVALUE_REFERENCE_H
#define BOOST_HOF_GUARD_FUNCTION_REMOVE_RVALUE_REFERENCE_H

namespace boost { namespace hof { namespace detail {

template<class T>
struct remove_rvalue_reference
{
    typedef T type;
};

template<class T>
struct remove_rvalue_reference<T&&>
: remove_rvalue_reference<T>
{};

}}} // namespace boost::hof

#endif

/* remove_rvalue_reference.hpp
J2RiRD2Dv45PQ3/S2wSCQqujo5LzM+y5274l57fH3CfWsORDXyq43+8RvUfzUKuN/uuZ+8uz0O+zrcyFOp+theO/T0484ChtXXm+VfooVsGjrctMJ+Bqoa7NQU78yOJp315yrmqK/PDbe7+/UFSOk97ZE3Rh7pEwbStBhzZdWaCCalzkZprYnFvZYl5sOiHf8OS5d+SJsLPLWgpdD6mqFAXjCCGTxUAvBwfTUuayP+Vlj8oePXqkk4Tf6eEu+8DNSCgCUMFglrut39DPj8e4a3VdwHNlX0nTj40/7OSWRgFL773De9BHcKc7poa7qGhtRLR5KaxzHR/XBtkE3eLNC7RqrUuKuvTRiuAWS3ajUDVMSgCPLOkFgd/ymicFa0mYewztPPZ/+XFjqX8ILJKaa1KWZ3ithS/J1ngh71AqJLv2yoK8NlaHJfHJkY+67DvTVpPQZ8Evv55OvK/KPT1+HxnrU7i3gUc+0SL/gzz6tk22/RWvHSX5SIHeXJklDN+4gvPX2mSLhu2/JPbAG7xVMCvLJ5ykw6h1UMHRl6GvIJ+NEc+CHQM7PKcFW/1OQ7d5o+zfXXvOGEQpidknCKWrj2RkRrCLCjTKJl2Di+tU7jyZ+3I9JXAr5alJ6KuHt3diVogaZZpdT3TnLn+Kya3/Dvrg6GKX7i01ISfLnfxHL4KwrVuUJJRU/XLNREXYd7svAaI9utXh2UXkvf08
*/