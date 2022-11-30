
#ifndef BOOST_CONTRACT_ACCESS_HPP_
#define BOOST_CONTRACT_ACCESS_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Allow to declare invariants, base types, etc all as private members.
*/

// IMPORTANT: Included by contract_macro.hpp so must #if-guard all its includes.
#include <boost/contract/core/config.hpp>
#if !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
        defined(BOOST_CONTRACT_STATIC_LINK)
    #include <boost/contract/detail/decl.hpp>
    #include <boost/contract/detail/type_traits/mirror.hpp>
#endif
#ifndef BOOST_CONTRACT_NO_INVARIANTS
    #include <boost/contract/detail/debug.hpp>
    #include <boost/function_types/property_tags.hpp>
    #include <boost/mpl/vector.hpp>
#endif

namespace boost { namespace contract {
        
#if !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
        defined(BOOST_CONTRACT_STATIC_LINK)
    class virtual_;

    namespace detail {
        BOOST_CONTRACT_DETAIL_DECL_DETAIL_COND_SUBCONTRACTING_Z(1,
                /* is_friend = */ 0, OO, RR, FF, CC, AArgs);
    }
#endif
#ifndef BOOST_CONTRACT_NO_INVARIANTS
    namespace detail {
        template<typename RR, class CC>
        class cond_inv;
    }
#endif

/**
Declare this class as friend to program invariants and base types as private
members.

Declare this class a friend of the user-defined class specifying the contracts
and then invariant functions and the base types @c typedef can be declared as
non-public members:

@code
class u
    #define BASES public b, private w
    : BASES
{
    friend class boost::contract::access;

    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types; // Private.
    #undef BASES

    void invariant() const { ... } // Private (same for static and volatile).

public:
    ...
};
@endcode

In real code, programmers will likely chose to declare this class as friend so
to fully control public interfaces of their user-defined classes (this is not
extensively done in the examples of this documentation only for brevity).
This class is not intended to be directly used by programmers a part from
being declared as @c friend (and that is why this class does not have any public
member and it is not copyable).

@warning    Not declaring this class friend of user-defined classes will cause
            compiler errors on some compilers (e.g., MSVC) because the private
            members needed to check the contracts will not be accessible.
            On other compilers (e.g., GCC and CLang), the private access will
            instead fail SFINAE and no compiler error will be reported while
            invariants and subcontracting will be silently skipped at run-time.
            Therefore, programmers must make sure to either declare this class
            as friend or to always declare invariant functions and base types
            @c typedef as public members.

@see @RefSect{advanced.access_specifiers, Access Specifiers}
*/
class access { // Non-copyable (see below).
/** @cond */
private: // No public APIs (so users cannot use it directly by mistake).

    access(); // Should never be constructed (not even internally).
    ~access();
    
    // No boost::noncopyable to avoid its overhead when contracts disabled.
    access(access&);
    access& operator=(access&);
    
    #if !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
            defined(BOOST_CONTRACT_STATIC_LINK)
        BOOST_CONTRACT_DETAIL_MIRROR_HAS_TYPE(has_base_types,
                BOOST_CONTRACT_BASES_TYPEDEF)

        template<class C>
        struct base_types_of {
            typedef typename C::BOOST_CONTRACT_BASES_TYPEDEF type;
        };
    #endif

    #ifndef BOOST_CONTRACT_NO_INVARIANTS
        BOOST_CONTRACT_DETAIL_MIRROR_HAS_MEMBER_FUNCTION(
                has_static_invariant_f, BOOST_CONTRACT_STATIC_INVARIANT_FUNC)
        
        BOOST_CONTRACT_DETAIL_MIRROR_HAS_STATIC_MEMBER_FUNCTION(
                has_static_invariant_s, BOOST_CONTRACT_STATIC_INVARIANT_FUNC)

        template<class C>
        struct has_static_invariant : has_static_invariant_s<C, void,
                boost::mpl::vector<> > {};

        template<class C>
        static void static_invariant() {
            C::BOOST_CONTRACT_STATIC_INVARIANT_FUNC();
        }

        template<class C>
        class static_invariant_addr { // Class so to pass it as tparam.
            typedef void (*func_ptr)();
        public:
            static func_ptr apply() {
                return &C::BOOST_CONTRACT_STATIC_INVARIANT_FUNC;
            }
        };

        BOOST_CONTRACT_DETAIL_MIRROR_HAS_MEMBER_FUNCTION(
                has_invariant_f, BOOST_CONTRACT_INVARIANT_FUNC)
        
        BOOST_CONTRACT_DETAIL_MIRROR_HAS_STATIC_MEMBER_FUNCTION(
                has_invariant_s, BOOST_CONTRACT_INVARIANT_FUNC)

        template<class C>
        struct has_cv_invariant : has_invariant_f<C, void, boost::mpl::vector<>,
                boost::function_types::cv_qualified> {};
        
        template<class C>
        struct has_const_invariant : has_invariant_f<C, void, boost::mpl::
                vector<>, boost::function_types::const_qualified> {};

        template<class C>
        static void cv_invariant(C const volatile* obj) {
            BOOST_CONTRACT_DETAIL_DEBUG(obj);
            obj->BOOST_CONTRACT_INVARIANT_FUNC();
        }
        
        template<class C>
        static void const_invariant(C const* obj) {
            BOOST_CONTRACT_DETAIL_DEBUG(obj);
            obj->BOOST_CONTRACT_INVARIANT_FUNC();
        }
    #endif
    
    // Friends (used to limit library's public API).
    // NOTE: Using friends here and in all other places in this library
    // does not increase compilation times (I experimented replacing all
    // friends with public and got the same compilation times).
    #if !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
            defined(BOOST_CONTRACT_STATIC_LINK)
        BOOST_CONTRACT_DETAIL_DECL_DETAIL_COND_SUBCONTRACTING_Z(1,
                /* is_friend = */ 1, OO, RR, FF, CC, AArgs);
            
        BOOST_CONTRACT_DETAIL_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTIONS_Z(1,
                OO, RR, FF, CC, AArgs, vv, rr, ff, oobj, aargs)
    #endif
    #ifndef BOOST_CONTRACT_NO_INVARIANTS
        template<typename RR, class CC>
        friend class boost::contract::detail::cond_inv;
    #endif
/** @endcond */
};

} } // namespace

#endif // #include guard


/* access.hpp
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
*/