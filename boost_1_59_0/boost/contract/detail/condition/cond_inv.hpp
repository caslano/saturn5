
#ifndef BOOST_CONTRACT_DETAIL_COND_INV_HPP_
#define BOOST_CONTRACT_DETAIL_COND_INV_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/cond_post.hpp>
#ifndef BOOST_CONTRACT_NO_INVARIANTS
    #include <boost/contract/core/access.hpp>
    #include <boost/type_traits/add_pointer.hpp>
    #include <boost/type_traits/is_volatile.hpp>
    #include <boost/mpl/vector.hpp>
    #include <boost/mpl/transform.hpp>
    #include <boost/mpl/for_each.hpp>
    #include <boost/mpl/copy_if.hpp>
    #include <boost/mpl/eval_if.hpp>
    #include <boost/mpl/not.hpp>
    #include <boost/mpl/and.hpp>
    #include <boost/mpl/placeholders.hpp>
    #include <boost/utility/enable_if.hpp>
    #ifndef BOOST_CONTRACT_PERMISSIVE
        #include <boost/function_types/property_tags.hpp>
        #include <boost/static_assert.hpp>
    #endif
#endif

namespace boost { namespace contract { namespace detail {

template<typename VR, class C>
class cond_inv : public cond_post<VR> { // Non-copyable base.
    #if     !defined(BOOST_CONTRACT_NO_INVARIANTS) && \
            !defined(BOOST_CONTRACT_PERMISSIVE)
        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_static_invariant_f<
                C, void, boost::mpl:: vector<>
            >::value),
            "static invariant member function cannot be mutable "
            "(it must be static instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_static_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::const_non_volatile
            >::value),
            "static invariant member function cannot be const qualified "
            "(it must be static instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_static_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::volatile_non_const
            >::value),
            "static invariant member function cannot be volatile qualified "
            "(it must be static instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_static_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::cv_qualified
            >::value),
            "static invariant member function cannot be const volatile "
            "qualified (it must be static instead)"
        );

        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_invariant_s<
                C, void, boost::mpl::vector<>
            >::value),
            "non-static invariant member function cannot be static "
            "(it must be either const or const volatile qualified instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::non_cv
            >::value),
            "non-static invariant member function cannot be mutable "
            "(it must be either const or const volatile qualified instead)"
        );
        BOOST_STATIC_ASSERT_MSG(
            (!boost::contract::access::has_invariant_f<
                C, void, boost::mpl::vector<>,
                        boost::function_types::volatile_non_const
            >::value),
            "non-static invariant member function cannot be volatile qualified "
            "(it must be const or const volatile qualified instead)"
        );
    #endif

public:
    // obj can be 0 for static member functions.
    explicit cond_inv(boost::contract::from from, C* obj) :
        cond_post<VR>(from)
        #ifndef BOOST_CONTRACT_NO_CONDITIONS
            , obj_(obj)
        #endif
    {}
    
protected:
    #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
        void check_entry_inv() { check_inv(true, false, false); }
        void check_entry_static_inv() { check_inv(true, true, false); }
        void check_entry_all_inv() { check_inv(true, false, true); }
    #endif
    
    #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
        void check_exit_inv() { check_inv(false, false, false); }
        void check_exit_static_inv() { check_inv(false, true, false); }
        void check_exit_all_inv() { check_inv(false, false, true); }
    #endif

    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        C* object() { return obj_; }
    #endif

private:
    #ifndef BOOST_CONTRACT_NO_INVARIANTS
        // Static, cv, and const inv in that order as strongest qualifier first.
        void check_inv(bool on_entry, bool static_only, bool const_and_cv) {
            if(this->failed()) return;
            try {
                // Static members only check static inv.
                check_static_inv<C>();
                if(!static_only) {
                    if(const_and_cv) {
                        check_cv_inv<C>();
                        check_const_inv<C>();
                    } else if(boost::is_volatile<C>::value) {
                        check_cv_inv<C>();
                    } else {
                        check_const_inv<C>();
                    }
                }
            } catch(...) {
                if(on_entry) {
                    this->fail(&boost::contract::entry_invariant_failure);
                } else this->fail(&boost::contract::exit_invariant_failure);
            }
        }
        
        template<class C_>
        typename boost::disable_if<
                boost::contract::access::has_const_invariant<C_> >::type
        check_const_inv() {}
        
        template<class C_>
        typename boost::enable_if<
                boost::contract::access::has_const_invariant<C_> >::type
        check_const_inv() { boost::contract::access::const_invariant(obj_); }
        
        template<class C_>
        typename boost::disable_if<
                boost::contract::access::has_cv_invariant<C_> >::type
        check_cv_inv() {}

        template<class C_>
        typename boost::enable_if<
                boost::contract::access::has_cv_invariant<C_> >::type
        check_cv_inv() { boost::contract::access::cv_invariant(obj_); }
        
        template<class C_>
        typename boost::disable_if<
                boost::contract::access::has_static_invariant<C_> >::type
        check_static_inv() {}
        
        template<class C_>
        typename boost::enable_if<
                boost::contract::access::has_static_invariant<C_> >::type
        check_static_inv() {
            // SFINAE HAS_STATIC_... returns true even when member is inherited
            // so extra run-time check here (not the same for non static).
            if(!inherited<boost::contract::access::has_static_invariant,
                    boost::contract::access::static_invariant_addr>::apply()) {
                boost::contract::access::static_invariant<C_>();
            }
        }

        // Check if class's func is inherited from its base types or not.
        template<template<class> class HasFunc, template<class> class FuncAddr>
        struct inherited {
            static bool apply() {
                try {
                    boost::mpl::for_each<
                        // For now, no reason to deeply search inheritance tree
                        // (SFINAE HAS_STATIC_... already fails in that case).
                        typename boost::mpl::transform<
                            typename boost::mpl::copy_if<
                                typename boost::mpl::eval_if<boost::contract::
                                        access::has_base_types<C>,
                                    typename boost::contract::access::
                                            base_types_of<C>
                                ,
                                    boost::mpl::vector<>
                                >::type,
                                HasFunc<boost::mpl::_1>
                            >::type,
                            boost::add_pointer<boost::mpl::_1>
                        >::type
                    >(compare_func_addr());
                } catch(signal_equal const&) { return true; }
                return false;
            }

        private:
            class signal_equal {}; // Except. to stop for_each as soon as found.

            struct compare_func_addr {
                template<typename B>
                void operator()(B*) {
                    // Inherited func has same addr as in its base.
                    if(FuncAddr<C>::apply() == FuncAddr<B>::apply()) {
                        throw signal_equal();
                    }
                }
            };
        };
    #endif

    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        C* obj_;
    #endif
};

} } } // namespace

#endif // #include guard


/* cond_inv.hpp
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
*/