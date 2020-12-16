
#ifndef BOOST_CONTRACT_DETAIL_COND_POST_HPP_
#define BOOST_CONTRACT_DETAIL_COND_POST_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/cond_base.hpp>
#include <boost/contract/detail/none.hpp>
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #include <boost/contract/detail/type_traits/optional.hpp>
    #include <boost/optional.hpp>
    #include <boost/function.hpp>
    #include <boost/type_traits/remove_reference.hpp>
    #include <boost/mpl/if.hpp>
    #include <boost/preprocessor/facilities/empty.hpp>
#endif

/* PRIVATE */

#define BOOST_CONTRACT_DETAIL_COND_POST_DEF_( \
        result_type, result_param, ftor_type, ftor_var, ftor_call) \
    public: \
        template<typename F> \
        void set_post(F const& f) { ftor_var = f; } \
    \
    protected: \
        void check_post(result_type const& result_param) { \
            if(failed()) return; \
            try { if(ftor_var) { ftor_call; } } \
            catch(...) { fail(&boost::contract::postcondition_failure); } \
        } \
    \
    private: \
        boost::function<ftor_type> ftor_var; /* Boost.Func for lambdas, etc. */

/* CODE */

namespace boost { namespace contract { namespace detail {

template<typename VR>
class cond_post : public cond_base { // Non-copyable base.
public:
    explicit cond_post(boost::contract::from from) : cond_base(from) {}
    
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        private: typedef typename boost::mpl::if_<is_optional<VR>,
            boost::optional<typename boost::remove_reference<typename
                    optional_value_type<VR>::type>::type const&> const&
        ,
            VR const&
        >::type r_type;

        BOOST_CONTRACT_DETAIL_COND_POST_DEF_(
            r_type,
            r,
            void (r_type),
            // Won't raise this error if NO_POST (for optimization).
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_required,
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_required(r)
        )
    #endif
};

template<>
class cond_post<none> : public cond_base { // Non-copyable base.
public:
    explicit cond_post(boost::contract::from from) : cond_base(from) {}
    
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        BOOST_CONTRACT_DETAIL_COND_POST_DEF_(
            none,
            /* r */ BOOST_PP_EMPTY(),
            void (),
            // Won't raise this error if NO_POST (for optimization).
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed,
            BOOST_CONTRACT_ERROR_postcondition_result_parameter_not_allowed()
        )
    #endif
};

} } } // namespace

#endif // #include guard


/* cond_post.hpp
bVxaRpw3LmlgesZA5/yEThualuFNGZKerr4IovNsnTckLS0zNUPuoI0bGLxvT+XxHdvByfLNuBj1rVh9n4X5XkK8NyZFFlB5Nf15ySkpCf1jUoQ61xCmzzX0i9Y9VNvk9bZpNXfu1GB8nXEqG2+eraltnK1xngNnsGzXvkLXuTmGEhMvrw5PTO7vVZ/olZeH90/TRywyT1iKrh21TYxqfj9BfUM6v9AH9PZxlrmwRN+Zoc7OZo0pLnUOJ1Pe+f77oPwiM905W6u/2aU24ssrGkqDeeFmXrqxZ1Bh2DguSZBnS9N96lMl3CSaVVFQLnvFFVrGN0viff7v9UvQp74WxMZrX1lecUFO1W9pOuUyistpksIhy3UUKVSRCv/mT/RvUQvmdXG+Hx5T4BzLVURz8ns5Z179H2cNWX+0842jmNxceRtOpfqYdXDcSU4+m5lKFGGCNE4RcenxmsLmNx8Gu75j4f/OZkJOfrk6qh5oe7iAlhWlNOr/RpfZr5Ei3fmImBq2mZcXzFOnWsy8EtG/Qm6gT4zL82WPdb4ro883G7Sb6JSLJ7IgN9a7ipp1TnfKOmX8PQrkz3bnq14F+WqOP7/K2Y8EZHa++laxutZaEkHtIW2BTCca+m9RKPmKT+Zkr/ycm7665/hF9PfzzO99+LviPPNNpSx4sHi0Me81nDS9UdZJN/fQOb5ekhmP+RP1wf///Xf/JS6EP86xRLtLbfHpTM50LbfFnsO2iBpvib3XC3HXox5x/r3E42+2xPYxfL9sGvHgxzhXsJM9JXts0emgJd4hf3qJLfovsETE3UJ0fwm9MdUSbRJtMTfGFs9dZfHtEI94NZ9vRVwmxMuXcE/+jR7x9zQhBjwrRO4lxKiut8S0zXxH7TTuuGmFdX3BFvWacC9vtC2SP+FcNW1e0Jr+baH+TL4VstkWrdM5b9fJI1rO9Yg7drAusMISZ0XCv0VCvJfNHee/WOJdny22dbTE09tt0QN2G3eXR8Q3Z19SRyIk7xK36saa7UZbRL5ri8VngF2uscSSCkt8T1tfX22Jtcs573mVLZ4ZZ4vwByzx1cOssb5mibCv0O/bLfHYOZwhWWqL8z5mbEc5//+UENt9HnHJ50IcTuOWq3tt0ew9aBlrifW32mIE9OhbzxJ3L7FEvY+wR2XE5WuD6X7k9rInQRwfWyJplSX6X26LfgnE0/KIAXznEdPK6c+XnKfZ7xHvUo93F982PeARZ1zIzYhTPOKpIuo62xLn9PGIs+/hnpU3+A7vFFuse9sWS7/k2yR322Lab7Z4qJYQI7p4xLLDQtySbIuj31hi9CT28jDuGQj6krZ8c24iCO0ZS3T/Dcv/iiWGvmCJxr3BQ7y7vNQWnXda4t4OrCuvt8XsO9CND3lEu72WuPoL4m7MczQ89c2H8MUc7kyd7BETrmNN6mNbHCiwxdmM+0LeO6+ZJbZu5/s6u6AT9SbMs8XT7aDlXzkj/6NHPLicm3cOWeKOzzzilG+FGPImdLmLM8nJljh0HvU94xH7GN9dC9mTBkj6vpMlbqy0xYBTLLErjHn/grXMDdB1GN99WW2LydB3PuPZnCTE33azd6gWdP/EI656m7+PYmc90GKxR7zdlT49Bw6K9IjPmIMjl7LeutAWNXqDHcNs8Zcnsdfwa7ddlpgyg/kp9Yg5Gzxi13yPWPOVLQrgre9akh+LjaQPd9GXjoD2IxGcMO3PDZjUdVFd+p0IX91ui5l/t8X2N7m7CZ6o/5RHPMNcWHzk++JezPcltrgGmow9aIvPnxfi2iXQZxE8X9MSZwr2uHQidj+RfVmRtlj5syWa3mWLKxn/jxVCbOT3PddBvwm2mF6ITNxkiTk=
*/