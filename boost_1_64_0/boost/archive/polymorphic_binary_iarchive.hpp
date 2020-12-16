#ifndef BOOST_ARCHIVE_POLYMORPHIC_BINARY_IARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_BINARY_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_binary_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_binary_iarchive :
    public detail::polymorphic_iarchive_route<binary_iarchive>
{
public:
    polymorphic_binary_iarchive(std::istream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<binary_iarchive>(is, flags)
    {}
    ~polymorphic_binary_iarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_binary_iarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_BINARY_IARCHIVE_HPP


/* polymorphic_binary_iarchive.hpp
fwsaQo5rY9Qx8kiRWTIYRVDU04bSYwnKfF+EZkqi6OsBIAL+02lwURujguOX7yK2VPYbVpf9Sb+u6XG+Bge9YS7NkezQKqtOPF/hfw/yftW4Iuyelq6yv8gb++wTChd8FzDTgN6h4f+DFvn2vBDyb0t+ztUh5N+W/JvvDCH/t+SPXx5C/m/Jbx1CXpZoyX/n9hDy/weC+c+HwAd3WfKHhhj/Xyz55UUh5m/J73pViPlb8sdCo6lR/hpYTpspNRHeHfeM9N+fYH8NMH76+C/B8H9n2sVNY42+4iphARxgFkCWQf+DD2F6jx3wZLRNxOpQEOvyZTwpiLWg97RoQRObpwldEV9FjL8fKHjW50JxV5mDWQE1X8SzWhfBZqnhsCm/yqUXO1CtCb/RGOdlj0dTCeEF6H3+Yr7tcKcgfAN4KCWIKJo57+oTgbJzPqvaNdVj5xOUDaek4W4tljy+ZC1jZCFTiP/fzxTiv42EcPJfVn5rbTWy2U8QfL0JePBPergGGBvwJ5llZkiZArPMn/VPoDZG88XI2RP2ZP55DxlcEHNksoRjuYgC5U9IytOuRJimubC3uxZsj/2/LhA4gc8v+D8BfiLxQYBN3MwTbO7S9jAywZFFq/Upkezyx4ECRShgBPoAJ5AWIxe5jBSb6p3uk9MjJvnxY7X5s0+o31b67z7Tnxwyhf6f1BD9b5Rv+sWjBv3/fKP0+2V9dt2r1ucA+WCLeEq9Nof09BvkOq3mWe+ikyMeimHYTXe1u35lExtfiReRTPJiPtNMn6TSsVlxI2GrhHnlW/Qx+twqj9iuqeL1vrtvQURLZ3Gx9MKt6825Ye9EYLCqrXSjLe9Lbo2ZfND2uHUGa3v0V/w+lQF05Bs2ft9F3Wx0cFOnqUzoeFw8g3U83g6l6o8NLetHONJnW0/9J7j+4MFb4Nyoe4IYMZYwC2miXANLT/zu21LdW+KMsDssWmvMDcxUEDfxettSrI2OtYFHYMLy1uG/oH3a+ptlvadeZtIUl14pzM5ECUtNKDWLAoZOlB0fLMG90wKk8kNh/1dwvtAg7afzok+ftgZFgC2u4BOT4MsI86ZJ4OthbNnsHeILhHmSigO8pcAKf9LvwV5ou9mf9YIwf6TvUC/vfDQCgLb5cg5Z9CdX5k/e+Jd70Q5c/HJv+jNa+Ub44+Xcba5yihAf7LWz9LpDet0sJyhVdeW5gnppprwbXHo5I0cvI0iEJnMme8tHCMjH2omqg/k2sKlBsG0tJ8KO1u9VzVjd4qeOBSxwMBVwMAj/EHvl5VQa8KOwKvmwrBl93bX13/pR7/9dBjwZ+JDh//KihvhfRvmmcUb5a/58SviJjE/DHYhy+XvRXaZdMwv4yfFv5VTe5a7GkcvHa/oH8e+o/E2M+UAU1d+cy5xwGGeWTpVTOwI7qPxAwzNOTum1YRIcfz/YD2Qtg3bEx0ff9+2GK+gVcw11d19GtLN4N7pUtg0+mrw2y6G11n+HU+E76vCOdK4dGeVcOzrSuXZYdA6+ROC/S8LxLywHWXb8F4VRkueLLLRYAtIbDQ1GQzn4npqD6XfnMEjx6NXv8R1N8o5L+2Caie9TfcJR5kbb0IMdTbgq9zpyYiv0j+bQezwvzHc02tsERW75Fr7N43xHnSw6qnhAluQmbFOgync0YfFf/C3JrgkNUfr9qO2P1LuCgCS/I6r0ZJQmbGKDnn+ZGHK+xU44sHZs419mt4gRxK/vxN+OFjuevkSHO/jwkCao6Ex4zoB6ZMZSttJL4OtnYXJwZMb4tJ1E6rTkMgs+dE/JTso8J2lpQlmv2oVh7dKaFAa1Ea31CT+orIO7z6jw7e11QjwThf/errDY8yFaXO8=
*/