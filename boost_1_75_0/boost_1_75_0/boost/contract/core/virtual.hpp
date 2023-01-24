
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
O2Sqh4Wf/Qq4WYThQ4BTZb77KL5/wNkk8FfrGzZRL0HSIQDFpw6TREEmfpIPOCA3BcaFxXiQ45ffdwTvOjjhCexm0vtrTEDTNM+bDT3iNmBt5wCww1II3PxGJR201nXVYNs9BKtDSgnOeU1BjoVK8z7DeYiorgEI5226COHWEYGRMSbgrW+K3gtfTmKa0Rc+H4p7OCYEIUT742uF9U6p17if16UAeN8vHRl/5rPf/cNv/8XxO9fXtn5hD81DpgoyUSiQw+amjsb7ZztYBhOXIM8LcAF0cSvsxbfB3LuFkg/hHMGNrS/0ccaXBdf97/z1FVeQQkKbEgVKlKxAiSFytw3OUnChIA15noBzYJoBkoEZBlvA04sr8PtCJA/Q0pQgU+0LIJJeOHDrS6BhmJ/RTGuknQwLL78H+uq9sEmJYmggFFXmfkU8Ij9pJqvnMZwA3mOd1ffivycDZ0CSSEglvdnPHMrcYFQYlMbgnrcs4e++XUE1wN9Gwmnz05usvKb2DWCOt8M5Yg0fD+cclFJ1i7FQTBSIPEVRTHXxja2C+NqBUxB6/hlj6nuI2YhBIMRCoMlqjL6ziwVeWZbD6nUQAAHYsaBA9F718PonABNwB/A3t9E4z8zxuhQAAPDxf/2h81//1jO/928e+u9fHWwO7+wSgSfSCwGXwxahbBg+is+qoFrldzPjkA8tONNIt25FsnkAw73ngC7zFX0l
*/