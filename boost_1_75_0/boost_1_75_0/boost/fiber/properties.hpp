//          Copyright Nat Goodspeed 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Define fiber_properties, a base class from which a library consumer can
// derive a subclass with specific properties important to a user-coded
// scheduler.

#ifndef BOOST_FIBERS_PROPERTIES_HPP
#define BOOST_FIBERS_PROPERTIES_HPP

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

# if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4275)
# endif

namespace boost {
namespace fibers {

class context;

namespace algo {

class algorithm;

}

class BOOST_FIBERS_DECL fiber_properties {
protected:
    // initialized by constructor
    context         *   ctx_;
    // set every time this fiber becomes READY
    algo::algorithm *   algo_{ nullptr };

    // Inform the relevant algorithm instance that something important
    // has changed, so it can (presumably) adjust its data structures
    // accordingly.
    void notify() noexcept;

public:
    // Any specific property setter method, after updating the relevant
    // instance variable, can/should call notify().

    // fiber_properties, and by implication every subclass, must accept a back
    // pointer to its context.
    explicit fiber_properties( context * ctx) noexcept :
        ctx_{ ctx } {
    }

    // We need a virtual destructor (hence a vtable) because fiber_properties
    // is stored polymorphically (as fiber_properties*) in context, and
    // destroyed via that pointer.
    virtual ~fiber_properties() = default;

    // not really intended for public use, but algorithm_with_properties
    // must be able to call this
    void set_algorithm( algo::algorithm * algo) noexcept {
        algo_ = algo;
    }
};

}} // namespace boost::fibers

# if defined(BOOST_MSVC)
# pragma warning(pop)
# endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_PROPERTIES_HPP

/* properties.hpp
gCJPPfCJp3tzb85FI9EVFtwvdOY3PliQVQXO22B4mawWcN7mbIV1rL2ZuLMy4s6yUGIgROfax2zanwZcqqzbzGXKFcKWHOcYPSsypvNHtl0sy4vYwg6nhf0cVuxztJ07iws7XizsnW0Wtk75baC2sBCgCdaSdcfHfxu3+hpgkyckAWrpYSueCRWF2ORPcL7GYn43rFTZNBCUg8gTG9mN0eddKXsFy0aTMb2PNgf34AieE0ADzuZBv3SuEPkIYxcv7t9LUsKvC5PKOeSsQnvx6FWN9EAhjHsVCEDdW3hWAz0UygJr2YyyLWil6XkOze/cKTbPeNAoafH2lpT73geDKHPsfaAIsF/JZa957oWMxw8/wbJZDWCiV43xVrqgh/zqNvC/Rz9fbqNBpeiDZIa6il8wEjKWoV/ot64r+a17wB0nFb+AnjtAFAXT1vTY0DC+zkadH/PKcB35lE/gbtqBbAD539AOP7Wr/Q8/6I+YO/oE6QIGzmSsbOTf2AZVNr58zougPNPKGMs+dnnvipvOwAJ0qu78HUJpdZitWDHADQxvZOZq4XTYnyZqHsW/Ha+52VDdie/9O8CxzzmDaMDnYeoQ863yaTgsfuOQX+em0nqTY5kMernSSAnJ4eD2jOYiF/ln6OaHbpqLXG0ucithaJmmLe+hzWd6iysiz1J8PsRl9hT82By14jyM2GWEtDBTZgvsocj1RnI/2sWW
*/