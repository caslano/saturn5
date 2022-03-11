
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