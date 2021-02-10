
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_SEGMENTED_H
#define BOOST_CONTEXT_SEGMENTED_H

#include <cstddef>
#include <new>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

// forward declaration for splitstack-functions defined in libgcc
extern "C" {
void *__splitstack_makecontext( std::size_t,
                                void * [BOOST_CONTEXT_SEGMENTS],
                                std::size_t *);

void __splitstack_releasecontext( void * [BOOST_CONTEXT_SEGMENTS]);

void __splitstack_resetcontext( void * [BOOST_CONTEXT_SEGMENTS]);

void __splitstack_block_signals_context( void * [BOOST_CONTEXT_SEGMENTS],
                                         int * new_value, int * old_value);
}

namespace boost {
namespace context {

template< typename traitsT >
class basic_segmented_stack {
private:
    std::size_t     size_;

public:
    typedef traitsT traits_type;

    basic_segmented_stack( std::size_t size = traits_type::default_size() ) BOOST_NOEXCEPT_OR_NOTHROW :
        size_( size) {
    }

    stack_context allocate() {
        stack_context sctx;
        void * vp = __splitstack_makecontext( size_, sctx.segments_ctx, & sctx.size);
        if ( ! vp) throw std::bad_alloc();

        // sctx.size is already filled by __splitstack_makecontext
        sctx.sp = static_cast< char * >( vp) + sctx.size;

        int off = 0;
        __splitstack_block_signals_context( sctx.segments_ctx, & off, 0);

        return sctx;
    }

    void deallocate( stack_context & sctx) BOOST_NOEXCEPT_OR_NOTHROW {
        __splitstack_releasecontext( sctx.segments_ctx);
    }
};

typedef basic_segmented_stack< stack_traits > segmented_stack;
# if defined(BOOST_USE_SEGMENTED_STACKS)
typedef segmented_stack default_stack;
# endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_SEGMENTED_H

/* segmented_stack.hpp
u8byuOxSd9nyL5ec2CKhtj24YtjfeEMYYeq7kVq7dLXx0pY6HqFP2KVJCdtgpgXY7e1JgzzuuFEQRu3+id9rh33/8NkvrkXmTZxdtY1aty3aanR9bKO+9pHdsOQ1Eh3XoC1P4waPzdkNdCJNaKHZr5H5OpElXv2mTacvKYcvr2uzAm5h2YZgkNm7G0sJvlQo3GpGW0WpDdIRgu1W11BgHFrWns9t/VnB/IKrNdD9Uy70NiRp0+fe+bNh5Lxd4ziRsaowLRvLC1ZUfDsVbPNC+RzNhsP/BxJo72Q6jsa98TB0SJvdCj76J5NhYO+HuttbZLy+dheIUpg97O4OBqHCGdSeaJwqDBzY79fWKyQQ2R4d7sPfDty9TGhjd4ngo+XcHRTdzTzUlL5XtyOP12j2ErnsVEq4aM99Ku69pNxt9911ahKAEjoHmx5jMVsrq6e0xA58iAQqeozl3Qv3oGMlPMzXnWf/wZV7Anavd801tLmFahVo7ncUzcJgOjnFWck9OYv9Xi8Iw/g4OOvirzDoTYOIft22FwdDui3rzL90/tlOAf4HfzD03w6Gg+jM8dO0brX1jGMJUOBsOoIP/nAWOFOOQwHOl2RLEI+PqRcT0re3LuhqtZIKa6+eS2vC2eh4ND4dxWM7bRBTKU2N
*/