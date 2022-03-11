
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