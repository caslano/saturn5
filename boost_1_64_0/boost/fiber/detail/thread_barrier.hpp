
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_THREAD_BARRIER_H
#define BOOST_FIBER_DETAIL_THREAD_BARRIER_H

#include <cstddef>
#include <condition_variable>
#include <mutex>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

class thread_barrier {
private:
	std::size_t             initial_;
	std::size_t             current_;
	bool                    cycle_{ true };
    std::mutex              mtx_{};
    std::condition_variable cond_{};

public:
	explicit thread_barrier( std::size_t initial) :
        initial_{ initial },
        current_{ initial_ } {
        BOOST_ASSERT ( 0 != initial);
    }

    thread_barrier( thread_barrier const&) = delete;
    thread_barrier & operator=( thread_barrier const&) = delete;

    bool wait() {
        std::unique_lock< std::mutex > lk( mtx_);
        const bool cycle = cycle_;
        if ( 0 == --current_) {
            cycle_ = ! cycle_;
            current_ = initial_;
            lk.unlock(); // no pessimization
            cond_.notify_all();
            return true;
        }
        cond_.wait( lk, [&](){ return cycle != cycle_; });
        return false;
    }
};

}}}

#endif // BOOST_FIBER_DETAIL_THREAD_BARRIER_H

/* thread_barrier.hpp
WaY2cLWFyaXlyO+im7kUBFrPtG67WldFZv5oDJLGm8R8vZKWuL83AKaO4Lwf3b/KIZv9yMtvux/N/MQ2xWvYGKG1n5e26Lz81JoMgShIZUD9v0Y50hajDhf9hpqYZ6ULJUHfPkIm5S3tXgZC46PT6o/w1whFMioQVw/teMNsigTMImg427GXCZpkjFT//+u17cHv3vAQtFyasB4x6P5PsfwgoVeWHdkdc+6CazhJVntX2fRxYbD8cze1mJnBcdFlbSmHYRw2OoZZwX7Fprfk3AafYTQy6+aUMVTo66yl5KXqAilyWOHTOCtsmmwaSRjTa4SoTqJSVkRxUFrfWXOVO+kQdl+Y95zon2dDjX2F2LCwTEymipHtH+P65LsS05kpVDHVdA8EtBogqPm9c3zy9VnQkYoFIlyHnm4b90LuPtq9Q/y+XqJduAwzBTQZ+fhBaNE7BgulP0MCjQ6+IX8q4ofZ0yilnuH4MChrPIXmrltzQZ90wx92DrWJP0xTVAawo+nNzIGyqcb1fRbtZIzWmlRG4hhkUr6r/kW+pIh0Q61552ZVj0h8zek1zQ==
*/