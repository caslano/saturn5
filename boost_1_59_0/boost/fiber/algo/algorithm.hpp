//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_ALGO_ALGORITHM_H
#define BOOST_FIBERS_ALGO_ALGORITHM_H

#include <atomic>
#include <chrono>
#include <cstddef>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>

#include <boost/fiber/properties.hpp>
#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class context;

namespace algo {

class BOOST_FIBERS_DECL algorithm {
private:
    std::atomic< std::size_t >    use_count_{ 0 };

public:
    typedef intrusive_ptr< algorithm >  ptr_t;

    virtual ~algorithm() = default;

    virtual void awakened( context *) noexcept = 0;

    virtual context * pick_next() noexcept = 0;

    virtual bool has_ready_fibers() const noexcept = 0;

    virtual void suspend_until( std::chrono::steady_clock::time_point const&) noexcept = 0;

    virtual void notify() noexcept = 0;

    #if !defined(BOOST_EMBTC)
      
    friend void intrusive_ptr_add_ref( algorithm * algo) noexcept {
        BOOST_ASSERT( nullptr != algo);
        algo->use_count_.fetch_add( 1, std::memory_order_relaxed);
    }

    friend void intrusive_ptr_release( algorithm * algo) noexcept {
        BOOST_ASSERT( nullptr != algo);
        if ( 1 == algo->use_count_.fetch_sub( 1, std::memory_order_release) ) {
            std::atomic_thread_fence( std::memory_order_acquire);
            delete algo;
        }
    }
    
    #else
      
    friend void intrusive_ptr_add_ref( algorithm * algo) noexcept;
    friend void intrusive_ptr_release( algorithm * algo) noexcept;
    
    #endif
      
};

#if defined(BOOST_EMBTC)

    inline void intrusive_ptr_add_ref( algorithm * algo) noexcept {
        BOOST_ASSERT( nullptr != algo);
        algo->use_count_.fetch_add( 1, std::memory_order_relaxed);
    }

    inline void intrusive_ptr_release( algorithm * algo) noexcept {
        BOOST_ASSERT( nullptr != algo);
        if ( 1 == algo->use_count_.fetch_sub( 1, std::memory_order_release) ) {
            std::atomic_thread_fence( std::memory_order_acquire);
            delete algo;
        }
    }
    
#endif
    
class BOOST_FIBERS_DECL algorithm_with_properties_base : public algorithm {
public:
    // called by fiber_properties::notify() -- don't directly call
    virtual void property_change_( context * ctx, fiber_properties * props) noexcept = 0;

protected:
    static fiber_properties* get_properties( context * ctx) noexcept;
    static void set_properties( context * ctx, fiber_properties * p) noexcept;
};

template< typename PROPS >
struct algorithm_with_properties : public algorithm_with_properties_base {
    typedef algorithm_with_properties_base super;

    // Mark this override 'final': algorithm_with_properties subclasses
    // must override awakened() with properties parameter instead. Otherwise
    // you'd have to remember to start every subclass awakened() override
    // with: algorithm_with_properties<PROPS>::awakened(fb);
    void awakened( context * ctx) noexcept final {
        fiber_properties * props = super::get_properties( ctx);
        if ( BOOST_LIKELY( nullptr == props) ) {
            // TODO: would be great if PROPS could be allocated on the new
            // fiber's stack somehow
            props = new_properties( ctx);
            // It is not good for new_properties() to return 0.
            BOOST_ASSERT_MSG( props, "new_properties() must return non-NULL");
            // new_properties() must return instance of (a subclass of) PROPS
            BOOST_ASSERT_MSG( dynamic_cast< PROPS * >( props),
                              "new_properties() must return properties class");
            super::set_properties( ctx, props);
        }
        // Set algo_ again every time this fiber becomes READY. That
        // handles the case of a fiber migrating to a new thread with a new
        // algorithm subclass instance.
        props->set_algorithm( this);

        // Okay, now forward the call to subclass override.
        awakened( ctx, properties( ctx) );
    }

    // subclasses override this method instead of the original awakened()
    virtual void awakened( context *, PROPS &) noexcept = 0;

    // used for all internal calls
    PROPS & properties( context * ctx) noexcept {
        return static_cast< PROPS & >( * super::get_properties( ctx) );
    }

    // override this to be notified by PROPS::notify()
    virtual void property_change( context * /* ctx */, PROPS & /* props */) noexcept {
    }

    // implementation for algorithm_with_properties_base method
    void property_change_( context * ctx, fiber_properties * props) noexcept final {
        property_change( ctx, * static_cast< PROPS * >( props) );
    }

    // Override this to customize instantiation of PROPS, e.g. use a different
    // allocator. Each PROPS instance is associated with a particular
    // context.
    virtual fiber_properties * new_properties( context * ctx) {
        return new PROPS( ctx);
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_ALGO_ALGORITHM_H

/* algorithm.hpp
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
*/