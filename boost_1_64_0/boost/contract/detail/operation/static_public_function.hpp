
#ifndef BOOST_CONTRACT_DETAIL_STATIC_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_DETAIL_STATIC_PUBLIC_FUNCTION_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/cond_inv.hpp>
#include <boost/contract/detail/none.hpp>
#include <boost/contract/detail/exception.hpp>
#if     !defined(BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION) && ( \
        !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS))
    #include <boost/contract/detail/checking.hpp>
#endif
#if     !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/config.hpp>
    #include <exception>
#endif

namespace boost { namespace contract { namespace detail {

// No subcontracting because static so no obj and no substitution principle.
template<class C> // Non-copyable base.
class static_public_function : public cond_inv</* VR = */ none, C> {
public:
    explicit static_public_function() : cond_inv</* VR = */ none, C>(
            boost::contract::from_function, /* obj = */ 0) {}

private:
    #if     !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_OLDS)
        void init() /* override */ {
            #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
            #endif
            #if !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) || \
                    !defined(BOOST_CONTRACT_NO_PRECONDITIONS)
                { // Acquire checking guard.
                    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                        checking k;
                    #endif
                    #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                        this->check_entry_static_inv();
                    #endif
                    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                        #ifndef \
  BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
                            this->check_pre();
                            } // Release checking guard (after pre check).
                        #else
                            } // Release checking guard (before pre check).
                            this->check_pre();
                        #endif
                    #else
                        } // Release checking guard
                    #endif
            #endif
            #ifndef BOOST_CONTRACT_NO_OLDS
                this->copy_old();
            #endif
        }
    #endif

public:
    #if     !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        ~static_public_function() BOOST_NOEXCEPT_IF(false) {
            this->assert_initialized();
            #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
                checking k;
            #endif

            #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                this->check_exit_static_inv();
            #endif
            if(uncaught_exception()) {
                #ifndef BOOST_CONTRACT_NO_EXCEPTS
                    this->check_except();
                #endif
            } else {
                #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                    this->check_post(none());
                #endif
            }
        }
    #endif
};

} } } // namespace

#endif // #include guard


/* static_public_function.hpp
Kv+mx1uhi3gNg5/z8Xk6z/O2dC9+poY5L84NF36lu/vQNpMjzuYaA303wWc3x/FI9OTlCD9aEsYZf9bavBWP8cQtnD3Wv9MK/bYam/MGS3H2hFxquQANag6f480rA+mV1jROSvG2n1RKjjWGK8WvwyBYsdjYZsjvTnqQz1+mOfB1A9deFit2+OVf8XhX7zKqHwzowxOlMG+YPvo1GLz/sZ+89Y/aSWkszmbHNPTvZ1w/Hw4bbs2fMpZToJMeypKD98UppXFB+iL6JXL61nr+NnvEHsjj35dzbBqOfMUaXaPt67kufRpL/zfEly/D3jnudSrordcR466wexiN29Jn3w4710JXGdMXMDklPvbytFDL8zzDRBi0FRdd4Ido/SFTeF86vHAL/K/uT+ghLU+tXoYYN97/EL73qahnJ7f6RKux/tZpu37Jx/CN3/yRtqwPizfBlhID6aA4eakmm6j16OT6yC+Hkvbod3WgP80z1R6abjVvFAeX3oRRPWEAvTpUHta09lt7OOvP+/4G57fRGmOixJeWuksvFqADW7zMw+m5f/+uH1j7VvrpMyeb49fqdJd97i1yox58DnxQDZhu/BP07GLk+G1aa/1p62xPoqFe4oK+PGl2PEmDxhyEgy3p76+dkZmPZ1PjBs8K+EpoV0W1f593wVkfmNvNCyHnPj1P/RU/vJkP0hP7Dra83taZ2zL0Vj619BePukMNGs/RY7SLukj3nL5WKrm5AFbzFI/uiq86KblBfRRVRz1DNIZ1TsWHfqyHUcd8jeNgQd5YXyGNWHajodLAndvXjI3vnvOZ2IlDhhY8HO1+7A7e1tPeTre0TsQ7OLb4r/zYbbVtrX/IJV8+hyFvRyQ4rh5t7Rvyu9YyW4+QfSRnLzrzKoFWmMGTXOD329NOG3lQc8rQGO92geu51dFveAvfTjePDDxVdfn90mLaBXbEl/G5NXD0Kt230D1xalwD3INTt74oJvqMZejanHKxuHkUMIf0iTCsurMm1Vw3k3vSlQ3o2YtpHu+rNyqFg+Bxq4z6o8P5x2R47hnrb5xTYcqi8fBitX1SXD73EQ0sZzZ2oQ/fU+sd1XRFWrudZ8eC82B48o359AsujbZmI/fT375zx77PsBY8Vkoxqq2WUrneYuusN1I3OC+r5z07hq4ph3Nm+wxcPylnn+uFa/XOSxdSKzxae9c+FDxHQtfl7wDz9GX6trFeN90D7sTo2cbX0pf+ktfeay/EvvA39PTA4Lmfn9TuJjF2zdXycmQ7ddOFLp4Fx3nfm0vM4wOepKL1+VI9HcWbFayXdRrEo/6Fa+9E6KS34Gh9vmYY/UM/9uinxx3hmS/L11gepD1cNZ+t8PInumUSLfPlJdpNz+K1I2qwanAGAd8ZZz/YV956z9uhn2/Nw9/QZX14ZnPOP4h+1cd6SCckXsWj1eCxPAzeZfzqbvdtrw5GRiXp27doVluoeiL2xx7y8mrsO32Wrl+6Rie5DwfJ9aT3fiwtyPvBuMNwvJ+59aS/bszmt+bxojP1e2H1DONP+6/17g9zwrTYL3KgsnXKwxv7+aM36bGzcohGqKAXsDMNH6oP8YW8OxO8C0BPoxOMrbdMLryAm7PRJ5Vxv7PAlfUycsGDUXohEfXWHQbEBtqMpmtXGg7g5fz+PnIpHrYHUZm/n8fr1MpMT6u5/+iwcu3xwkH5Ca+6fwKHv+KNtskL8T9K+x+dQgvqJz9lTVvK4ytyjJQOVbuud8SPLm1pTaIjvAxvQav8HJxd4c37b8DZcmeVHvqTfMwzNPcKWPFQLd7pZt3u6NM2wzF7fC/oL17mgVZE/BAuuue7XfXi1oeS7n+3qRjr9XRvKD9r0hA=
*/