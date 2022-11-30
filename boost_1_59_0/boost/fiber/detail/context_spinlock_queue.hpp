
//          Copyright Oliver Kowalke 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FIBERS_DETAIL_SPINLOCK_QUEUE_H
#define BOOST_FIBERS_DETAIL_SPINLOCK_QUEUE_H

#include <cstddef>
#include <cstring>
#include <mutex>

#include <boost/config.hpp>

#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/spinlock.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

class context_spinlock_queue {
private:
	typedef context *   slot_type;

    mutable spinlock   splk_{};
	std::size_t                                 pidx_{ 0 };
	std::size_t                                 cidx_{ 0 };
	std::size_t                                 capacity_;
	slot_type                               *   slots_;

	void resize_() {
		slot_type * old_slots = slots_;
		slots_ = new slot_type[2*capacity_];
		std::size_t offset = capacity_ - cidx_;
		std::memcpy( slots_, old_slots + cidx_, offset * sizeof( slot_type) );
		if ( 0 < cidx_) {
			std::memcpy( slots_ + offset, old_slots, pidx_ * sizeof( slot_type) );
		}
		cidx_ = 0;
		pidx_ = capacity_ - 1;
		capacity_ *= 2;
		delete [] old_slots;
	}

	bool is_full_() const noexcept {
		return cidx_ == ((pidx_ + 1) % capacity_);
	}

	bool is_empty_() const noexcept {
		return cidx_ == pidx_;
	}

public:
	context_spinlock_queue( std::size_t capacity = 4096) :
			capacity_{ capacity } {
		slots_ = new slot_type[capacity_];
	}

	~context_spinlock_queue() {
		delete [] slots_;
	}

    context_spinlock_queue( context_spinlock_queue const&) = delete;
    context_spinlock_queue & operator=( context_spinlock_queue const&) = delete;

	bool empty() const noexcept {
        spinlock_lock lk{ splk_ };
		return is_empty_();
	}

	void push( context * c) {
        spinlock_lock lk{ splk_ };
		if ( is_full_() ) {
			resize_();
		}
		slots_[pidx_] = c;
		pidx_ = (pidx_ + 1) % capacity_;
	}

	context * pop() {
        spinlock_lock lk{ splk_ };
		context * c = nullptr;
		if ( ! is_empty_() ) {
			c = slots_[cidx_];
			cidx_ = (cidx_ + 1) % capacity_;
		}
		return c;
	}

	context * steal() {
        spinlock_lock lk{ splk_ };
		context * c = nullptr;
		if ( ! is_empty_() ) {
			c = slots_[cidx_];
            if ( c->is_context( type::pinned_context) ) {
                return nullptr;
            }
			cidx_ = (cidx_ + 1) % capacity_;
		}
		return c;
	}
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_SPINLOCK_QUEUE_H

/* context_spinlock_queue.hpp
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
*/