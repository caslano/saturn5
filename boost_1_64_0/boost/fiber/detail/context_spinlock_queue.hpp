
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
ER6erunlBBitcYPkp3Mr1n7PJ+/F7SFmZdm4Tr4MRxXmVbt51XGF9dvu6epbv9BK3hp8WQJ1+jjrxv5itjfyX/O2xFQE8GFXTPhk7sTTFxnpXvKRpIw99xDAzPld8EUEzWNdb8R9e8DYa5RLZR8o89qcv+X0B3m3Il4tYsC73LKtfueoa5Sz+LbSdtvuUlb6BC/joQWR3mdJzLcoYIe0WVH8ivm0g4dggfFSlPJOPDIN2y9otpr/Usg7sEWvd/OQKUtrZVDI8zsBofiL3xrGKvDllkmhUvC+0YX5UJ/i11nlp9dwaQDkj2v3ssq29q252dj/x9EFk2Cz06Jo2v0ZyuPPhbMeD75AmxccK/bgeWEoiYSWSLkcy+z9dxR+YmkcV0rZUAh8oIHFXljxU9DFZT5XO4cIiB5DIepDqIDXDW/fJphxpk+BIUWWDycKpAbjXeTJIUYDkTS7kccVXYdUOihx5a045Go5IXS7N0c1g8Mg0oqNXEZvykfyWbijx5p+UQ+e6HPNLzQe4v7hZGfT30aq2tgTLrm3SWUAtXlbjQgevHRgFUZKEic2SQ==
*/