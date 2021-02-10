
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
zlhbGXskyc1KNW8tNlbLyYIqJLErUOS0V6iqUiv9LYmMh8nraHqJucTR6emPz45OevdZnUdTS1RU3R5ej07Rgl5MbKKSu3al/m5QmChj3eEkHDGsiPG1fSfClxbsc04aI60ie3qtDV/2OwE/D2ajxCM22oXJNEqiQTSKvWQUH+FbAAazwpypSjub4R/B1WQ0tCMMOWJEBtsuX65TOyeod9LWFKepUSlfZKhj3fxyuvPpCPPe4+RxGzC3GjVI4KDY3KvW/IzPO5PF2mARXnSm9ACbCpqM7rbG+HxnjD9cWNrSZPhzMz7S9jE/eLAX8oH1jted9Wbx0IYqDsjBC5iMggTrdOWYH10ewns7PLvO2Ggm2XzEL6+wRl/YsadybutHz/tshtPCf5nd/1INGuCFsPUMrjF88CochcmNF2zfnq22IZM6GU3PomFsY7vxGdv5yvQdgYHPBMZRZjpMZtMxXAej2dCb2vPrLUQdXfdGrm7rWtEkc/LkNs7Gl+Po9TiN7OsGGaG8Ofe9eDiEYBRH+OL2anoXqCTadODupa2Hrwc+9L6A6Ne2ev8AUEsDBAoAAAAIAC1nSlKH9VtwewYAANoOAABAAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9Q
*/