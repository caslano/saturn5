// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_DEFAULT_COMPILE_POLICY_HPP
#define BOOST_MSM_BACK_DEFAULT_COMPILE_POLICY_HPP

#include <boost/mpl/bool.hpp>

namespace boost { namespace msm { namespace back
{
struct favor_runtime_speed 
{
    typedef int compile_policy;
    typedef ::boost::mpl::true_ add_forwarding_rows;
};

}}}// boost::msm::back
#endif // BOOST_MSM_BACK_DEFAULT_COMPILE_POLICY_HPP

/* default_compile_policy.hpp
ANADAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0OTM3VVQFAAG2SCRgbVPbTuMwEH231H+YLeIFKQRoq10qK9qIFhqppdkkdC9vrj2l2U3iyHaA8vXrXGihuy/xZHw855wZmxrUhjONHqFpsZF2+YO7Z6mE9ki8SEIS+/G8+YD/kMxgEtxN48RZTEbvkuHcD+7b/8ny+/1d5E+mJLq9ufoyuKzX4fVoSKh7qEzdloyckBOIUT2hcnQqkFCFZbazAN0keS48csTbsUXTcP4T+kebfRgMhhBV63Wqtx3mDEYXl61QfOFbVjwicFZwzDIUsN4Bz1IszIeKDUdbrAlBV2UplUHRwfzZ6vXXj8DnV6vfPF9dwNVgBH5ltrZSylkNpO47E9TtnDWWbxrGznJLv/fsEZ2bcn/a5jfITKXQ9u1THIcBEbiuHglXu9JIiztsAy1Yju3g3neMHXSlsoDn1GyhmZaQz8WjYlYFULc9S7URaeGRnKUZrKXY9WopbQ4ol3nOCtFqHLvu6WwZJ0E4Pq0pw2WUuNeDz+A49WlH8dKAQp6WtcGv+MLyMsNzW+MNsVE21lgIVB+3K6is/bFGrtCAk4BjVezJbdj1rOnmClW62YFghgHbGFRg7UJ9s2HLNKwRC+jr
*/