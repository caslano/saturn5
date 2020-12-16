
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
RTnuJvozqI/d3Ud7/NZ5Gdi5Xm86rmB40/RrnuuOezsqqDw/QuX5VSjPra48oRDhDQhjYwu5vzzMvhj8T4HzPtK2/qHBjqTAdX/hhUGaUq/7E8kBY0QGrLLguDQud6PZcenXxEc/I2PmVWOzvJ2yi2k733aJaVtaxgZzIJfGfJ9/GYyvSQ/8E3kYf0UsmDO61LTlV8aQF56T89OxY/VvxsJzTn8eJ+NqOePwgqw92nm/b8Wy3Au8C3Xa6eNa1Qfxvg5k1vxdZ/J3g4SvA11hmRKc5bVl+p0YnAvg85Cyh8z0774XM3vIYn47fZO0TdcZ+lsM/XVCfyuUoeNh5/ZvA/x1EfgfAj5eKm0l4H8MeNsH4LlByS/VZQlDP6LQ1/dEOROWnqk6DO47+/CU4WfLfxYLr6+eOxLXV5lkh7TfnAbKlzb7+u8Red4DechPy7kFzDvElb1a90veisqBHsr2kxMC+3E0aD8Px4afvRhp+vKPGN0yD9Dtb6AvqPLwez/7B7b8REzTC2RxMJTlKQ0XKS30tSHs+h0Y/oLyBjmQ3zkGf5oJn2LCZ5rwWRDWvPD5J9jbRzDUG+P/TDDEl5v1qpcM/i5js381+C8YPf/N4O3ewr8b/Dkm/qsGf5rB/9PgTzH4fxn8mQb/usGfZfBvqK+COZrCiHnR/8I41dLZedC3DW0JvD9t98m8C3ONyDdaDiKolX012eglDbuvZkSt7o+z8bKltZtXWIv715BuZ+mN8YpqIWzOYA3BD89pjamFdYbJwXkvO5bavdb4i6KAxsXjNY1av/7fOZl9mY69+PsXHvZb+9q70yntQ5KmaJwC44sP7ef6PNSZT/cOYH+wlPq73JeT8Q/f+eT1djKNhMu93nVrawgG8aq5b96TlH4x6/VAL+2uAsyE6zzuqPQk2pOheZlFAHcc5ss7+2Mpr/qvxWttq6f9/01r4o0rVnMzjwCc02QZbX0dR7wi57/y4Mt3AdeG+1IfofALZu1vb4LlGPNymaLNTwR6h9MzcWp3to7sE8Uf/lr+Uwx/4B1ZB/eFOmjln6Fz8MIL6+A0sFvs62I9mQE054+NpvlobeBfrD6sL9rf0Apd5FnCWVnLJVpvs4G3rEdDPHMGvxbmLaQ+fkm+DyYee8I5T/xVZv3Z/teeXg2lYeY0DJ2cywcdk6ycv9LZZv2DaDD8bHnQjjxVPnxO6ECix7UAcjs7MP52mFO6fnbEWoLEj0/m+FT7wvFfgjXaF6YMj18n8Yum+vG3wdoD6Ez7mMyzEfRldYt90aZaCFNa35qsdqL0ueIXeYvATnLQsp0sIVqUW/djotzNtXi+geXh8G5TZY9+sa+LASmLetIFv7syPbC9I4yfaq31f+in2sRmVwjtTt54a2ttiQ+l6CWngU3+g/GRGBljHZk/z3XL4h2Jjq4k8DQY4blaeOr80SpuF1zCKZbJwdYQbLSXYblD5yFoziiZ7HQTVwwj3fPaQnJtYqgnHV/nKawsA1vmzZe1taOg/Sn3nGBHNtS3NekwEwHcTmhZ4Pz30aL7G2S8cIzo/thafFNf70KWuXrB7ewduJamZW1tzfEWujVy8TJz6NQgg3l84b0k+xvbGB1YZ8FJGXUKX14DgLylTd7WAV2XfJ8d7rfQpNFaN5GXmafqcGUL66Jra/kcKL0utpnLr5vCpd4Gt6Ij83Q8xzY42D/oaXg/LzG4ribAl7twzA+7sql24fhg/yb3FqOsCR0P5U99mc3peGe7Fr6Esp8vztNeemrD9tJba/b7UlhxawxugMJSz7lOFE8N+85BxQtfXYPYc6qPT4NPIljkfQUbDU3UPvLNhkb9H/r5E2o1bbGHqRjmeRjlqbI=
*/