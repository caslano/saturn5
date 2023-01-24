
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#if defined(BOOST_USE_UCONTEXT)
#include <boost/context/continuation_ucontext.hpp>
#elif defined(BOOST_USE_WINFIB)
#include <boost/context/continuation_winfib.hpp>
#else
#include <boost/context/continuation_fcontext.hpp>
#endif

/* continuation.hpp
gMwmfcW9pNsjrQ5YotmG9JENVxKSiXyLKSe6EWlqQmHR1JOrJZ74YyH7wYwT/Yytb97H1Wdz1k+mVMNVvv6/KqrJkCPLjisPa4olSHuGcnSTrvfscSf17/bqOAGok3XaaebeOZwzMSrgcE6FwRlKZuPC2/69UrEwrGFN42u6/qqtJfPWvQlTsqBAWqdrZFg1d3r+pDVUP0gKeub99VDzEAW/bgfmPEs9h8Y1BF8t9G2/X0SYTCZzjUDiepmAAl7zet0pgHkUICx3+/LhX/3Ym1545IX/9NiZk4iqGC4/T7os5N2MNEnI0oxBMaBnDFamTJiQGEWvF8ijYVkholjNErpaY2K1XTcREikZT3OWcsd0ktDzG2TZt7DjjJWNKf2eBd1H+wQrE4QxRg1QkiGiqGRKLx0zlQGiDB0C0HUq/Pg9qXCqx5OTjCX2mOouiVJYCVDS6GABkOD3zpE/iiZcLnXwWqmaKgyOQ4SnoQJQIj9Qd7eJEDxu9EBOBuiroj+aGI3C0nnLdU6dvMhyb8Lx/oisMtz39jFvfHvBs49Z8BVr6wOe/13FhY0paTcJ0RWlUYWhk5dQ5OxtTesfkrnU27YSQM1ea/wSBeLw3kSIHF0Aq2NUILgPWqnYJrztBrR85TkuwFNnjbYFU6gLrOrn9NzHnHclaiQxrxwOQwbh+cOyANvWXDWFQCH1WZhOHbff1ifPU3Z2JwvH19Gc
*/