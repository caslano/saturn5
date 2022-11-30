
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
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
*/