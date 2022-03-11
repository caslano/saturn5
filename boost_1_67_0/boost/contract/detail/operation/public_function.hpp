
#ifndef BOOST_CONTRACT_DETAIL_PUBLIC_FUNCTION_HPP_
#define BOOST_CONTRACT_DETAIL_PUBLIC_FUNCTION_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/virtual.hpp>
#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/core/virtual.hpp>
#include <boost/contract/detail/condition/cond_subcontracting.hpp>
#include <boost/contract/detail/tvariadic.hpp>
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
#endif
#if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <exception>
#endif

namespace boost { namespace contract { namespace detail {

template<
    class O, typename VR, typename F, class C
    BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
    BOOST_CONTRACT_DETAIL_TVARIADIC_TPARAMS_Z(1, BOOST_CONTRACT_MAX_ARGS, Args)
>
class public_function : // Non-copyable base.
    public cond_subcontracting<
        O, VR, F, C
        BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
        BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(1, BOOST_CONTRACT_MAX_ARGS, Args)
    >
{
public:
    explicit public_function(
        boost::contract::virtual_* v, C* obj, VR& r
        BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
        BOOST_CONTRACT_DETAIL_TVARIADIC_FPARAMS_Z(1,
                BOOST_CONTRACT_MAX_ARGS, Args, &, args)
    ) :
        cond_subcontracting<
            O, VR, F, C
            BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
            BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(1,
                    BOOST_CONTRACT_MAX_ARGS, Args)
        >(
            boost::contract::from_function, v, obj, r
            BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(BOOST_CONTRACT_MAX_ARGS)
            BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(1,
                    BOOST_CONTRACT_MAX_ARGS, args)
        )
    {}

private:
    #if     !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        void init() /* override */ {
            #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                    !defined(BOOST_CONTRACT_NO_EXCEPTS)
                this->init_subcontracted_old();
            #endif
            if(!this->base_call()) {
                #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                    if(checking::already()) return;
                #endif
                { // Acquire checking guard.
                    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                        checking k;
                    #endif
                    #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                        this->check_subcontracted_entry_inv();
                    #endif
                    #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                        #ifndef \
  BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
                            this->check_subcontracted_pre();
                            } // Release checking guard (after pre check).
                        #else
                            } // Release checking guard (before pre check).
                            this->check_subcontracted_pre();
                        #endif
                    #else
                        } // Release checking guard.
                    #endif
                #ifndef BOOST_CONTRACT_NO_OLDS
                    this->copy_subcontracted_old();
                #endif
            } else {
                #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                    this->check_subcontracted_entry_inv();
                #endif
                #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                    this->check_subcontracted_pre();
                #endif
                #ifndef BOOST_CONTRACT_NO_OLDS
                    this->copy_subcontracted_old();
                #endif
                #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                    this->check_subcontracted_exit_inv();
                #endif
                if(uncaught_exception()) {
                    #ifndef BOOST_CONTRACT_NO_EXCEPTS
                        this->check_subcontracted_except();
                    #endif
                } else {
                    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                        this->check_subcontracted_post();
                    #endif
                }
            }
        }
    #endif

public:
    #if     !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        ~public_function() BOOST_NOEXCEPT_IF(false) {
            this->assert_initialized();
            if(!this->base_call()) {
                #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                    if(checking::already()) return;
                    checking k;
                #endif

                #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                    this->check_subcontracted_exit_inv();
                #endif
                if(uncaught_exception()) {
                    #ifndef BOOST_CONTRACT_NO_EXCEPTS
                        this->check_subcontracted_except();
                    #endif
                } else {
                    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                        this->check_subcontracted_post();
                    #endif
                }
            }
        }
    #endif
};

} } } // namespace

#endif // #include guard


/* public_function.hpp
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
*/