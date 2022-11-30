
#ifndef BOOST_CONTRACT_VIRTUAL_HPP_
#define BOOST_CONTRACT_VIRTUAL_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Handle virtual public functions with contracts (for subcontracting).
*/

// IMPORTANT: Included by contract_macro.hpp so must #if-guard all its includes.
#include <boost/contract/core/config.hpp>
#ifndef BOOST_CONTRACT_NO_CONDITIONS
    #include <boost/contract/detail/decl.hpp>
#endif
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #include <boost/any.hpp>
#endif
#ifndef BOOST_CONTRACT_NO_OLDS
    #include <boost/shared_ptr.hpp>
    #include <queue>
#endif

namespace boost { namespace contract {
        
#ifndef BOOST_CONTRACT_NO_CONDITIONS
    namespace detail {
        BOOST_CONTRACT_DETAIL_DECL_DETAIL_COND_SUBCONTRACTING_Z(1,
                /* is_friend = */ 0, OO, RR, FF, CC, AArgs);
    }
#endif

/**
Type of extra function parameter to handle contracts for virtual public
functions (for subcontracting).

Virtual public functions (and therefore also public function overrides)
declaring contracts using this library must specify an extra function parameter
at the very end of their parameter list.
This parameter must be a pointer to this class and it must have default value
@c 0 or @c nullptr (this extra parameter is often named @c v in this
documentation, but any name can be used):

@code
class u {
public:
    virtual void f(int x, boost::contract::virtual_* v = 0) { // Declare `v`.
        ... // Contract declaration (which will use `v`) and function body.
    }

    ...
};
@endcode

In practice this extra parameter does not alter the calling interface of the
enclosing function declaring the contract because it is always the very last
parameter and it has a default value (so it can always be omitted when users
call the function).
This extra parameter must be passed to
@RefFunc{boost::contract::public_function}, @RefMacro{BOOST_CONTRACT_OLDOF}, and
all other operations of this library that accept a pointer to
@RefClass{boost::contract::virtual_}.
A part from that, this class is not intended to be directly used by programmers
(and that is why this class does not have any public member and it is not
copyable).

@see    @RefSect{tutorial.virtual_public_functions, Virtual Public Functions},
        @RefSect{tutorial.public_function_overrides__subcontracting_,
        Public Function Overrides}
*/
class virtual_ { // Non-copyable (see below) to avoid copy queue, stack, etc.
/** @cond */
private: // No public API (so users cannot use it directly by mistake).

    // No boost::noncopyable to avoid its overhead when contracts disabled.
    virtual_(virtual_&);
    virtual_& operator=(virtual_&);

    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        enum action_enum {
            // virtual_ always held/passed as ptr so nullptr used for user call.
            no_action,
            #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                check_entry_inv,
            #endif
            #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                check_pre,
            #endif
            #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                check_exit_inv,
            #endif
            #ifndef BOOST_CONTRACT_NO_OLDS
                // For outside .old(...).
                push_old_init_copy,
                // pop_old_init_copy as static function below.
                // For inside .old(...).
                call_old_ftor,
                push_old_ftor_copy,
                pop_old_ftor_copy,
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                check_post,
            #endif
            #ifndef BOOST_CONTRACT_NO_EXCEPTS
                check_except,
            #endif
        };
    #endif

    #ifndef BOOST_CONTRACT_NO_OLDS
        // Not just an enum value because the logical combination of two values.
        inline static bool pop_old_init_copy(action_enum a) {
            return
                #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                    a == check_post
                #endif
                #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) && \
                        !defined(BOOST_CONTRACT_NO_EXCEPTS)
                    ||
                #endif
                #ifndef BOOST_CONTRACT_NO_EXCEPTS
                    a == check_except
                #endif
            ;
        }
    #endif

    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        explicit virtual_(action_enum a) :
              action_(a)
            , failed_(false)
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                , result_type_name_()
                , result_optional_()
            #endif
        {}
    #endif

    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        action_enum action_;
        bool failed_;
    #endif
    #ifndef BOOST_CONTRACT_NO_OLDS
        std::queue<boost::shared_ptr<void> > old_init_copies_;
        std::queue<boost::shared_ptr<void> > old_ftor_copies_;
    #endif
    #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
        boost::any result_ptr_; // Result for virtual and overriding functions.
        char const* result_type_name_;
        bool result_optional_;
    #endif

    // Friends (used to limit library's public API).
    #ifndef BOOST_CONTRACT_NO_OLDS
        friend bool copy_old(virtual_*);
        friend class old_pointer;
    #endif
    #ifndef BOOST_CONTRACT_NO_CONDITIONS
        BOOST_CONTRACT_DETAIL_DECL_DETAIL_COND_SUBCONTRACTING_Z(1,
                /* is_friend = */ 1, OO, RR, FF, CC, AArgs);
    #endif
/** @endcond */
};

} } // namespace

#endif // #include guard


/* virtual.hpp
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
*/