
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_MUTEX_H
#define BOOST_FIBERS_MUTEX_H

#include <boost/config.hpp>

#include <boost/assert.hpp>

#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/spinlock.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4251)
#endif

namespace boost {
namespace fibers {

class condition_variable;

class BOOST_FIBERS_DECL mutex {
private:
    friend class condition_variable;

    using wait_queue_type = context::wait_queue_t;

    detail::spinlock            wait_queue_splk_{};
    wait_queue_type             wait_queue_{};
    context                 *   owner_{ nullptr };

public:
    mutex() = default;

    ~mutex() {
        BOOST_ASSERT( nullptr == owner_);
        BOOST_ASSERT( wait_queue_.empty() );
    }

    mutex( mutex const&) = delete;
    mutex & operator=( mutex const&) = delete;

    void lock();

    bool try_lock();

    void unlock();
};

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_MUTEX_H

/* mutex.hpp
3whaeRQCTjOm2gfk3VdCKoPOpMbytW5Ll7hwu5bCDbbp8LbFTWCpbakcWt+OuFkYx1F8aDcQL4Xc7ZILZujZK4I0Wm5w91GSrjLIra6536jJdJROExRqTZlXfTioXnTcEt5bC40sRbB7H1s2fdsY7+BpJSM/CL6y4eCTollwLLN1MsqjMA5tC5GODS7E3DWnUNwV0d52CHLFeeMyc5PIWoWbHViJQ0rwhoR0A3oblropPwkW09SbLaZTK8Bo02gcTRMvqGvAohzjDsc6INWNylWtrVb4JTifT0PPl6XnNozdjL/v7B8hhTnAXSLKAxIewj8efL+eSLBdS3gMYbC5bfktwxuA+8jJ0QCR8AfRERLVJid3JxeORo9j2zbsoNcqZ3WltHn76tVLB/8UhL2lORhxk4+o8fhzgNHpN3ztwJBwe/Xod5Irxr63vOZMds3mq389vxS2zMGnYDINPkymk3TpBUXhZnT/HvJhd7ppa3ZNo1qz3UpRwyVdLyuWX3FZaNf5OEwX8Qw+BdNF6MV2OjS4EYvONlPyA9Rhr7SYnc2iz7MsslcEGSAbh3hvez3IIs2ik+w8PI/iZY+HG+6G0ZbVXYmTIrhE/nLW4Lxj9VxcgyQMIZgmEd6iH2L4vymCAc4RduFBpdMoSTdK
*/