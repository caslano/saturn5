/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    static.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_STATIC_H
#define BOOST_HOF_GUARD_FUNCTION_STATIC_H

/// static
/// ======
/// 
/// Description
/// -----------
/// 
/// The `static_` adaptor is a static function adaptor that allows any
/// default-constructible function object to be static-initialized. Functions
/// initialized by `static_` cannot be used in `constexpr` functions. If the
/// function needs to be statically initialized and called in a `constexpr`
/// context, then a `constexpr` constructor needs to be used rather than
/// `static_`.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     class static_;
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [ConstFunctionObject](ConstFunctionObject)
/// * DefaultConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     // In C++ this class can't be static-initialized, because of the non-
///     // trivial default constructor.
///     struct times_function
///     {
///         double factor;
///         times_function() : factor(2)
///         {}
///         template<class T>
///         T operator()(T x) const
///         {
///             return x*factor;
///         }
///     };
/// 
///     static constexpr static_<times_function> times2 = {};
/// 
///     int main() {
///         assert(6 == times2(3));
///     }
/// 

#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/reveal.hpp>

namespace boost { namespace hof { 

template<class F>
struct static_
{

    struct failure
    : failure_for<F>
    {};

    const F& base_function() const
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(F)
    {
        static F f;
        return f;
    }

    BOOST_HOF_RETURNS_CLASS(static_);

    template<class... Ts>
    BOOST_HOF_SFINAE_RESULT(F, id_<Ts>...) 
    operator()(Ts && ... xs) const
    BOOST_HOF_SFINAE_RETURNS(BOOST_HOF_CONST_THIS->base_function()(BOOST_HOF_FORWARD(Ts)(xs)...));
};


}} // namespace boost::hof

#endif

/* static.hpp
tuOi5wC0PcANB3fvtL5a07jiK6nidTZq1KF5G0MR9w1dNKRGTJfmVsMS+A+MkINCTmuN2UI7WnieamGwO18j1WgFc+RoETLazUO/J/FvT/7N9GjjuQGfn8ZHFTJl8RyjDCJVnC9zf08z3b4P5pUv1l3oh4wj8WnWxIfZkRqCNjv0NTVrhMO7uFwac188OjvN5ydf5Essq0ipFRG9WpJZEJk3a8TLvm4+yzW366MWkz7rFYvPUqq5nUJzHWStbpdVoUEZhFVv3NfKaFCnonOCM0Byp5sh3dPSXX0lfTE9nr7oaiCtQ6Yx5uOi5mp4CK8GnbEfLmquBkIYDFpjGi5qoN5yANMbFxD27q0UJbmK2MT+aqRgydbzo54cprBNzXQpYfO0vBRI25plUre486FWqVucbzCEMsk16ckR7g2CM0HszUsz/VrX6mtJnMqwAMf1+UQoy2AHHadd0u/6qZHK5Y2VqXeGPkhtzLStOZB046epkB2emzw2tLGtUgoobDovOg7FGAfDQkTQKS7uoCyMptOeySD1lU0OZbct3WAi/bEvd0ua0pcuIdoMlxAQc+mHR30jLCzFiLP0ivDVDFy83HUdpF9xZef8OMSHjszPY00Q09wQdNNpBYj3bQYNqb6rx8tkjvcOMUo3dcqEpho5DusHxdi8mkQRoesxGEnUrEAP7TFzIW/Hj0jZy1Pvl0zPm+U1IlzGfAHSwMP9IdhVuB0ocxQMk1FwBoIhgReqx1LrJr5OlVHDOMtBGo9DgHzOhfMGRizB5LGgMuxGar8XJiUnpZrk3i1IyAJ+PMz8IAd6EMDSwMiThoas+8EFYI62DedR15/fIhatC36F5E/zwDv0dbnPYORbkvEu/RLJqgdEoMk3ZtEertrnxUEJxy5KH3sSVVfK8yufqGbkO9e1PDAgspJqhirC9gWDFwTSCb4Pe5Kn/DP9mVPXljwT3IlMufuQrUO9kwV3w9LVPw81T0GNmNZHbRGEtotpegI/NcyLJZyOH8SL+yPqRh24FFMHjG+SbiUVELCpgx5iXafqNJ1E7/vwTMNVgJ2smIV2QNsYP8Hu2ur8NHdLsnYv/iDyuYOPJIzMOotVzmx4ll1aPqs9XkyB7LnS8e/WXzA2wNf+ULP96gyDH6XbSlJMef9mSQrbpwhvKUwK22cS3iokKWyfSXirkKSwfSbhrYJJYfN7aH6rKRlPO+PzXbwz2ObnBlhs7q7v1V/L/XrGsiX2kwDGU4YNL3lh3i4pCNNH39toPyv3az4/Fg7OA6hdWAhjOFUkDLOj5Pl5s+Y7AS1JRYDxpyWZZy4pKFqy5dzXXcufqQq1zb92LKRx885haVw3/lak0gUuZ0UK/Z2yIpn+ejFgaOm2gg403PFsfMfjtdfwVbBLv7eK3wo6uJb1DLJBimPZ1mfz0twv4LsZ3zfx3Y7vp/i24puMuiyp1tTUVFuq/CSlxn/sqcf+JKf+a5+UF//Tn+aPTk2wf9Qv/v1hwMjYd/fO+PctO+LfxySU15DwXp8d//50h/j3nySkP9QSX/7AjvHxb50S/75xd3z6vqcn2H9K6N/QhPpTEuqfn1D/ownpJybUf1tC+cVx8Sx/UIcrDv6dOBS+eTXCF6r4eLcZ/05ivM/wS0KagpE8cuu0N1Uyo8l0qXYX2RX+BGyKugGa208ney1T3rKkCbbuBAPJtkCXAtNUfYudBY3HkuREXuScyGyHuD+2yMEresBEOBU5yCjSiSKRpwDFHoelb/ooexX39DTouf3hm95/7ra1QM+Z4JqRHyGNOKRhcwgk7siMqCGnmLhqjpWx1A/6GoYBV1KfdZ9df4bOqyUZxT2hf7YN+mfjrcUTovpn2+I=
*/