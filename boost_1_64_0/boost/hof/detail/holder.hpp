/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    holder.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_HOLDER_H
#define BOOST_HOF_GUARD_HOLDER_H

namespace boost { namespace hof { namespace detail {

template<class... Ts>
struct holder
{
    typedef void type;
};

template<template<class...> class T>
struct template_holder
{
    typedef void type;
};

}}} // namespace boost::hof

#endif

/* holder.hpp
q8qzcDN7Q1yR2IE+3IED3IE9M0pFhWpRz6TGuqKIR2ysVTjILuAgqp3c1kOmdR+y7xm2TwmdSF65EExc7WVmfzoN9vYh6XKmMS7qW581izrRPOoG9NMS9djnMld9Hr2YL0FDPfD/OvxPMv4W4P/VL7eNN26sz8WkvzaW9l9gDFQQw9e4or8wWAVsN6rCPiS4pqrCMSS40ldXnhQYA4N24QOU4yC4GUPiQu5EI3gRR84hxJJzxbrxw+c2VuUPRpbJtvwDlf28OQeSDpUUR1yjr7IFuxeXwMzfPHMntmPjpfgyVjN+DD+HyYuzn5NL5wrfgCVi+ETz8itIe7IoxYuvZPpqR19O+kqiLwd90eWXgsuPSxZW8eVX5zlJUsV0A06nGzAN+WI3IGXsWSVvwLUt3IBw3TEh7gY0Ve7oIkTim2tjgqJtkF+2fpqq77DIf9VY5L8s6R0s6fNrE8PDLPnXLk4Mv1CdEOa7JJ11Iw1Fw3m30oPxZCVf49mk+EJsovbgL+4J4e7vqFVxhjcrzfsfoZrx70eN8hs5eSeSyUdwLqSVrzUFl8vGcyzmR6raZkp7u929RtntXHYNV51+TkqO0r77/DUmPjdQWXVTvvDpLUZ/ReBWIhYCfavFOMVn1eYLISotvg0w8LctIeUNxsP+Yb9tJzZt1clCuJmrJJrBnYhAMLi8kGWagRy5fXHWHQ7wC82Qv/OLr1Yr0tdFePzlo/I6MPOK8ZWpnKPe4yBru8ANPSB/vUyTM9Av9ocNhWhCOtOqK8jYG7MEvUyFYJEyn5iHosbz5xfEep4s+lWbGlpDFJkOqeejvFd0KOHEsd9CMT1l7DfwJ7gALFwy6Kr1RxbtJUwJcxiajuNLc8k4ZdnhW5LusLH8TKYVJl/Da2kaWXdoIMi/yQxJpqDmqPoC45tIrBiOJtigs13+yJASL+7aZOXbronM2bXc1i+ZtZkZmaedsqmefiOup79bdqaefotL50Z6a33McX4zrvSDyyhdcoUEEF3+cZ/OP7LMhXUACwuE/OH8KAA5y7Cxe19IPun2/Te72qpPdxH/Y1VMXqI6242okvDW7AH4+9RuwKw0/DAHfOEd2dn46w/vyh6Iv6QVT/PaoEBF+j/r52V3gzWY3tAB6gEdIAom+hH5VbycOitkjk7RCwNzeHp4ZrSvy+lpt/RMk/vsHJ7cvN1N97ZDdlpE4pGxkhOeQlWvo+gFcjUuVXU+uuRMdQbMOqe2w+DJX064gXyi0DBICjY4oGp1djebfoF0j2JGd5HD48TgoYQR3kMjnGzDEBfJId4bN8S+Z+zOkdmqO085WQf710pLAvaiEBNYImvcGlfjq4vPVGOtWaOG8vW221rtECitZqiTbGmOzgl6xWMgu5O4QXBsYKWx3VX73jO2395sXyTJs9tu0n1h59eF/qCwSculU43PRFBuyReReNAT01+4qOVmvj2Lj40mdjjZjQ4ePt8KkxzcW290uUtce5MkSrsh2zIh3LH2Rle4I9FV/HiJJdm94k/Poyz5Kc7mRckF7fZwkj88xRW27YNisPh4PjOCmqY5kP4VlQnkBMSHk7S7VQxQPLFPxmE1qANyfyErCCJSgk7KAIq0m84EwAPMn53SVIsmYezYbQHYOACMYdVOq9/fDayFWbrya5ZOJENtm9l+VlMG3UtI0GzoiHFXpY8yxcrWjg52DbiY1PShpniNr/AZObUAYTbCVOulk3V3XK177AQ37YcqKmwvTNrvJSXVD240IB5OAswH1Wouon2FYb/BALneSOBA4/ZR4SQTzE2zSO34kXhgripjYD52VmBCcPYMwLzNx0c9PHTk03gKm/LsDNUMC1SPUs0+V2hPu7o=
*/