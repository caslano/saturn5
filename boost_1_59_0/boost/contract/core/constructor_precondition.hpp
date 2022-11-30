
#ifndef BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION_HPP_
#define BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Program preconditions for constructors.
*/

// IMPORTANT: Included by contract_macro.hpp so must #if-guard all its includes.
#include <boost/contract/core/config.hpp>
#ifndef BOOST_CONTRACT_NO_PRECONDITIONS
    #include <boost/contract/core/exception.hpp>
    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
        #include <boost/contract/detail/checking.hpp>
    #endif
#endif

namespace boost { namespace contract {

/**
Program preconditions for constructors.

This class must be the very first base of the class declaring the
constructor for which preconditions are programmed (that way constructor
arguments can be checked by preconditions even before they are used to
initialize other base classes):

@code
    class u
        #define BASES private boost::contract::constructor_precondition<u>, \
                public b
        : BASES
    {
        friend class boost::contract::access;

        typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
        #undef BASES

    public:
        explicit u(unsigned x) :
            boost::contract::constructor_precondition<u>([&] {
                BOOST_CONTRACT_ASSERT(x != 0);
                ...
            }),
            b(1.0 / float(x))
        {
            ...
        }

        ...
    };
@endcode

User-defined classes should inherit privately from this class (to not alter the
public interface of user-defined classes).
In addition, this class should never be declared as a virtual base (because
virtual bases are initialized only once across the entire inheritance hierarchy
preventing preconditions of other base classes from being checked).

This class cannot be used this way in a @c union because unions cannot have base
classes in C++.
Instead, this class is used in a @c union to declare a local object within the
constructor definition just before @RefFunc{boost::contract::constructor} is
used (see @RefSect{extras.unions, Unions}).

@see @RefSect{tutorial.constructors, Constructors}

@tparam Class   The class type of the constructor for which preconditions are
                being programmed.
*/
template<class Class>
class constructor_precondition { // Copyable (has no data).
public:
    /**
    Construct this object without specifying constructor preconditions.

    This is implicitly called for those constructors of the contracted class
    that do not specify preconditions.
    
    @note   The implementation of this library is optimized so that calling this
            default constructor should amount to negligible compile-time and
            run-time overheads (likely to be optimized away completely by most
            compilers).
    */
    constructor_precondition() {}

    /**
    Construct this object specifying constructor preconditions.

    @param f    Nullary functor called by this library to check constructor
                preconditions @c f().
                Assertions within this functor call are usually programmed
                using @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown
                by a call to this functor indicates a contract failure (and will
                result in this library calling
                @RefFunc{boost::contract::precondition_failure}).
                This functor should capture variables by (constant) value, or
                better by (constant) reference to avoid extra copies.
    */
    template<typename F>
    explicit constructor_precondition(F const& f) {
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            try {
                #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                    if(boost::contract::detail::checking::already()) return;
                    #ifndef BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
                        boost::contract::detail::checking k;
                    #endif
                #endif
                f();
            } catch(...) { precondition_failure(from_constructor); }
        #endif
    }

    // Default copy operations (so user's derived classes can be copied, etc.).
};

} } // namespace

#endif // #include guard


/* constructor_precondition.hpp
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
*/