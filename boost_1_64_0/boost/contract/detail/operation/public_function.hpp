
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
hShcuKuw640XB5xdPKT3Q1fejcifwzjuDzEcb59MjefsiAvcb2JnOlGN97fGPY57Jgyv5JrAH9xQ35v0+mHvw3zmMUuONDBf18hpvzGmhLyGVcGZg+1RcqKu/R+1OrqhOXTiYWrSIDBw9Wn7/TE0vxz7imbfFusst57qjR30cYKxzfbvr8Hc52gUGFD2HA5eKw9xcdsOxo03B9A5VfXg4uijI631gN6nPZ0TnxSPn/U+z71Kg016PJdKzeCZPCtKk01Uy4W/lw++v5aXTswMizPS3LTQpLm8cUlcwFdF6NC/0uKsHjAnTJsWxWOz6VWeJKt6PCO/84jpAWt2S4627kPHrLN+crXzdvqEF/v2CT1/c/rpT14KV/VPC3O7wV/7UIVa8C219RqaRskl935d7qiL4NmhmS3l1rfyrKmYNOPLl+Lueq45n49roc4DfaDn+qC0dXqSBqWD3odZo3DMhut6XbVgW1+6gjbqJUdntYfj+to3itMkLdV5dzw8Rv3nlWvy9yJd8iqPcvsdvTq5/Jm6y2EBJw2Caf/qcfwT5eyxuTfx3yJ95t9oStc/hYMiOPMgv/j+gSA3Q6EGNPsIvfKyPWHLhmCfxXhhcuYBcDE1vj7i+vjrlby0B096e4Rcru78gXmvaK6m5WrjlqGkM0zl3oEXj3B7Ubh3yD31qr4Pzmu3hnlReEqcf5Tja86EPXeIp3Dari+c4wp0Yza8N4C+q6Xfa6wNhogNnMnTjCZ9mT6DRTPE9XRW44lWF9301YrRz/fNXR96Jb2597D6P403asOlV/Sf+P0hNekKuFFhPV2fTy2Kz3EaZgtv8Z/cv9A2Ion0qUqHnDGyNnLtfnAmGS61/xon+flLfGMOHNkA1rTtRBdUVzuX1MF4WJ3C/fmN2bD2xng6KCTvf4Sd1rs3f1IMHg2h+4vD1Ds8yyW6OZ43T1+Arj/jHN5+fEH7P5+NfuERc/Plg/R479sPmqi2V7v+qEALw4BiJdX2Vf6Vr/hmKsx4z38Prdc5fRdzn/uTGu8Lt16wLrTVOtptX4ZwKPu4cNI+Vr3m+Ive3Q3TE5LDkv/gW139jXfoGLlYBB5lHRlRJ7yaupv6Ee1XAPbxjqV5+DeP49nr+KqMXPyCvy6jx5YJL4ThdG9aqzm9116fyJ8bja/HYL1fOHNErzkvbX6Pfl3RS68K9qaqq592Vd69Dadiaacn5d9s2vJZffiHNH/InkoJ/cHncRT9fHaTntFA41zKc9Jdh+RZ2/f1OXzv+XVqi5+5DG/yu8biqri7q3M2avB/cm9+V/nwhXziUWeIywi9nrP0wtpyUXDTOtahNRdE8B6MKaL3r280gP752Vj+7kv3y71OeowpOuAk//ZMWffDTZ+JQSHf2WjtClYOJe21D5LncXAjHY7Yg7PDhe21T7cHoRZGrTa2VLwRPd0dBmzIKN86+ntFXEZf9SgHw2DckUY4bRAdJM8jpfQVG9NU1Y3hezqLHn40AG6qk4w0VN1B9rELwUy1OV+cH56FHZvouES4tjSK74XlrfjKZDigCi19gndNgIXTwknnT+voiaaV//+qk5gR8gOfF/zNeSe+s/5LauAnGpsW/eVNc3qkrzIc/5+WQ87ZRY2jmQPPMNXfy+tF7/HznPZZS8LSZGr1O7VA/wb7LIlq5bqc/+UQrwYv0tyGxfRgjX/p/30wrwDO5UvzZdZjMr+8cKJNvFr4g89uIc9umA9Psexb+qs/rr0tr/XL6qqFWolwZCRs5gsiM3Daf7wsDG/zSpAbekV5rKWx5Linh2YvbuYyPrS72LaBDfTaOfeImylH8fUUuPugvj4u3Kul51nsL14htfpV97nk28XpfOs=
*/