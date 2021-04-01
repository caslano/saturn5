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
y7U7ylzJ1sqCKajKBU/xvtGdcL7TJ5e+3+4YDtY737KmcvInMw4ViF+Gdz+7xQ8A7CV+G56J/nfgF1AdRr2//01yZ8leI8uwUC6OVd0id9kcCIk9Qy7Q+e7NA121CLg/mZEGm9/YOY31p1tvxNBWX0PF1/+iQYTz2DkNDJcHHl2+gLxZwMuogi2X9v3NqcDS4U8tzPZJrJeAps0HiN+pa3QRXMS4ek6uHGDuh9OT/iXMECY8Ronlt55ctIqCgSoqzTEEjC1nKqerQoZwqRdqlGbkYDMtXtk1lO+UgVnxaLxRToyHGb6PSkTFa2FE81QaXMuxCui4BiPF9NAS4qL+MnB83pcXEnzp9wGxdhKuf2j4o+bfnHgP/8eHzXf7Gbtnos3wRd3inae07jwDB53PwlLZDkkf4vdUs0cUbNdYxI3orSGtsoF1Ny1ahQ3GAM+BrkfXPyHVOsy8ust3N9WfkbsdvFYNQ8iqyt3pnNHIntuNia7pNAoS5GTk7A4tQQZ6SsxkZrkdronJxc+5KgWSfbE7nFSV/q35J4XUccQk4naLFwwv0zZI4Zri9Q==
*/