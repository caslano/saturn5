
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