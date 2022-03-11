
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