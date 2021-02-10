
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
VF9DT05WX1RPX05FVFdPUktfRlVOQ1RJT04uM1VUBQABtkgkYK1WbW/bRhL+zl8xUIGcHdBy3LSI06bFMbJ05lkWdSLlnAEBxIpchttSuwR3aUVt+t9vZpeU5CStg0MlSCR3d96feYbD1QCe/20fb0jq4MlPan8pfvDaC80b9QvPzJcF0vQjuC8KrvD6FabO4SD1MT2Fr5L6CCdWKu1svaH7NP0Kcytykv7OSXiV0i2uOMlOfqTqXSPelwZORqdw8fr1JZzBty8uXvlwxaTgFcSGyzVv3vvwJrcr/yzZhw9DzX/2gRtg1fCRwqQUGrQqzJY1HPC+EhmXmufANORcZ41Y44OQYEoOhag4jKL5fTj7lw/bUmRlp2enWtClaqscSvbAoeEZFw9OTc0aA6pADag/F9qgztYIJYdonoPhzUZ3asgJVmkF7IGJiq3RHDNQGlPrH87Ps7apMJLzXGX6POtTMSzN5pOo7tGbDduBqg0YBa3mPtB5HzYqFwVdMUW4WLfrSujSP7iFBmV+rhrQvKo6dSgquHYhcIi7bPl0Emr0Xhi6aCU1WduWavPoIKa1U1S0jURzmBY8lytMvA+tzHljz9tE9Fa6LNuUP1Gyg+85KIlewSCIIYwHsGZaaB/ehcl1tEzgXbBYBLPk
*/