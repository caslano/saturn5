
#ifndef BOOST_CONTRACT_CALL_IF_HPP_
#define BOOST_CONTRACT_CALL_IF_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Statically disable compilation and execution of functor calls.

@note   These facilities allow to emulate C++17 <c>if constexpr</c> statements
        when used together with functor templates (and C++14 generic lambdas).
        Therefore, they are not useful on C++17 compilers where
        <c> if constexpr</c> can be directly used instead.
*/

#include <boost/contract/detail/none.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/config.hpp>

/* PRIVATE */

/** @cond */

// Boost.ResultOf not always able to deduce lambda result type (on MSVC).
#ifndef BOOST_NO_CXX11_DECLTYPE
    #include <boost/utility/declval.hpp>
    #define BOOST_CONTRACT_CALL_IF_RESULT_OF_(F) \
        decltype(boost::declval<F>()())
#else
    #include <boost/utility/result_of.hpp>
    #define BOOST_CONTRACT_CALL_IF_RESULT_OF_(F) \
        typename boost::result_of<F()>::type
#endif

/** @endcond */

/* CODE */

namespace boost { namespace contract {

/**
Select compilation and execution of functor template calls using a static
boolean predicate (not needed on C++17 compilers, use <c>if constexpr</c>
instead).

This class template has no members because it is never used directly, it is only
used via its specializations.
Usually this class template is instantiated only via the return value of
@RefFunc{boost::contract::call_if} and @RefFunc{boost::contract::call_if_c}.

@see    @RefSect{extras.assertion_requirements__templates_,
        Assertion Requirements}

@tparam Pred    Static boolean predicate that selects which functor template
                call to compile and execute.
@tparam Then Type of the functor template to call if the static predicate
        @c Pred is @c true.
@tparam ThenResult Return type of then-branch functor template call (this is
        usually automatically deduced by this library so it is never explicitly
        specified by the user, and that is why it is often marked as
        @c internal_type in this documentation).
*/
template<bool Pred, typename Then, typename ThenResult =
    #ifndef BOOST_CONTRACT_DETAIL_DOXYGEN
        boost::contract::detail::none
    #else
        internal_type
    #endif
>
struct call_if_statement {}; // Empty so cannot be used (but copyable).

/**
Template specialization to dispatch between then-branch functor template calls
that return void and the ones that return non-void (not needed on C++17
compilers, use <c>if constexpr</c> instead).


The base class is a call-if statement so the else and else-if statements can be
specified if needed.
Usually this class template is instantiated only via the return value of
@RefFunc{boost::contract::call_if} and @RefFunc{boost::contract::call_if_c}.

@note   The <c>result_of<Then()>::type</c> expression needs be evaluated only
        when the static predicate is already checked to be @c true (because
        @c Then() is required to compile only in that case).
        Thus, this template specialization introduces an extra level of
        indirection necessary for proper lazy evaluation of this result-of
        expression.

@see    @RefSect{extras.assertion_requirements__templates_,
        Assertion Requirements}

@tparam Then Type of functor template to call when the static predicate is
        @c true (as it is for this template specialization).
*/
template<typename Then>
struct call_if_statement<true, Then,
    #ifndef BOOST_CONTRACT_DETAIL_DOXYGEN
        boost::contract::detail::none
    #else
        internal_type
    #endif
> :
    call_if_statement<true, Then,
        #ifndef BOOST_CONTRACT_DETAIL_DOXYGEN
            BOOST_CONTRACT_CALL_IF_RESULT_OF_(Then)
        #else
            typename result_of<Then()>::type
        #endif
    >
{ // Copyable (as its base).
    /**
    Construct this object with the then-branch functor template.

    @param f    Then-branch nullary functor template.
                The functor template call @c f() is compiled and called for this
                template specialization (because the if-statement static
                predicate is @c true).
                The return type of @c f() must be the same as (or implicitly
                convertible to) the return type of all other functor template
                calls specified for this call-if object.
    */
    explicit call_if_statement(Then f) : call_if_statement<true, Then,
            BOOST_CONTRACT_CALL_IF_RESULT_OF_(Then)>(f) {}
};

/**
Template specialization to handle static predicates that are @c true for
then-branch functor template calls that do not return void (not needed on C++17
compilers, use <c>if constexpr</c> instead).


Usually this class template is instantiated only via the return value of
@RefFunc{boost::contract::call_if} and @RefFunc{boost::contract::call_if_c}.

@see    @RefSect{extras.assertion_requirements__templates_,
        Assertion Requirements}

@tparam Then Type of functor template to call when the static predicate is
        @c true (as it is for this template specialization).
@tparam ThenResult Non-void return type of the then-branch functor template
        call.
*/
template<typename Then, typename ThenResult>
struct call_if_statement<true, Then, ThenResult> { // Copyable (as *).
    /**
    Construct this object with the then-branch functor template.

    @param f    Then-branch nullary functor template.
                The functor template call @c f() is actually compiled and
                executed for this template specialization (because the
                if-statement static predicate is @c true).
                The return type of @c f() must be the same as (or implicitly
                convertible to) the @p ThenResult type.
    */
    explicit call_if_statement(Then f) :
            r_(boost::make_shared<ThenResult>(f())) {}

    /**
    This implicit type conversion returns a copy of the value returned by the
    call to the then-branch functor template.
    */
    operator ThenResult() const { return *r_; }

    /**
    Specify the else-branch functor template.

    @param f    Else-branch nullary functor template.
                The functor template call @c f() is never compiled or executed
                for this template specialization (because the if-statement
                static predicate is @c true).
                The return type of @c f() must be the same as (or implicitly
                convertible to) the @p ThenResult type.
    
    @return A copy of the value returned by the call to the then-branch functor
            template (because the else-branch functor template call is not
            executed).
    */
    template<typename Else>
    ThenResult else_(Else const&
        #ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
            f
        #endif
    ) const { return *r_; }
    
    /**
    Specify an else-if-branch functor template (using a static boolean
    predicate).

    @param f    Else-if-branch nullary functor template.
                The functor template call @c f() is never compiled or executed
                for this template specialization (because the if-statement
                static predicate is @c true).
                The return type of @c f() must be the same as (or implicitly
                convertible to) the @p ThenResult type.
    
    @tparam ElseIfPred  Static boolean predicate selecting which functor
                        template call to compile and execute.
    
    @return A call-if statement so the else statement and additional else-if
            statements can be specified if needed.
            Eventually, it will be the return value of the then-branch functor
            template call for this template specialization (because the
            if-statement static predicate is @c true).
    */
    template<bool ElseIfPred, typename ElseIfThen>
    call_if_statement<true, Then, ThenResult> else_if_c(
        ElseIfThen const&
        #ifdef BOOST_CONTRACT_DETAIL_DOXYGEN // Avoid unused param warning.
            f
        #endif
    ) const { return *this; }

    /**
    Specify an else-if-branch functor template (using a nullary boolean
    meta-function).

    @param f    Else-if-branch nullary functor template.
                The functor template call @c f() is never compiled or executed
                for this template specialization (because the if-statement
                static predicate is @c true).
                The return type of @c f() must be the same as (or implicitly
                convertible to) the @p ThenResult type.
    
    @tparam ElseIfPred  Nullary boolean meta-function selecting which functor
                        template call to compile and execute.
    
    @return A call-if statement so the else statement and additional else-if
            statements can be specified if needed.
            Eventually, it will be the return value of the then-branch functor
            template call for this template specialization (because the
            if-statement static predicate is @c true).
    */
    template<class ElseIfPred, typename ElseIfThen>
    call_if_statement<true, Then, ThenResult> else_if(
        ElseIfThen const&
        #ifdef BOOST_CONTRACT_DETAIL_DOXYGEN // Avoid unused param warning.
            f
        #endif
    ) const { return *this; }
    
private:
    boost::shared_ptr<ThenResult> r_;
};

/**
Template specialization to handle static predicates that are @c true for
then-branch functor template calls that return void (not needed on C++17
compilers, use <c>if constexpr</c> instead).


Usually this class template is instantiated only via the return value of
@RefFunc{boost::contract::call_if} and @RefFunc{boost::contract::call_if_c}.

@see    @RefSect{extras.assertion_requirements__templates_,
        Assertion Requirements}

@tparam Then Type of functor template to call when the static predicate if
        @c true (as it is for this template specialization).
*/
template<typename Then>
struct call_if_statement<true, Then, void> { // Copyable (no data).
    /**
    Construct this object with the then-branch functor template.

    @param f    Then-branch nullary functor template.
                The functor template call @c f() is actually compiled and
                executed for this template specialization (because the
                if-statement static predicate is @c true).
                The return type of @c f() must be @c void for this template
                specialization (because the then-branch functor template calls
                return void).
    */
    explicit call_if_statement(Then f) { f(); }
    
    // Cannot provide `operator ThenResult()` here, because ThenResult is void.

    /**
    Specify the else-branch functor template.

    @param f    Else-branch nullary functor template.
                The functor template call @c f() is never compiled or executed
                for this template specialization (because the if-statement
                static predicate is @c true).
                The return type of @c f() must be @c void for this template
                specialization (because the then-branch functor template calls
                return void).
    */
    template<typename Else>
    void else_(Else const&
        #ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
            f
        #endif
    ) const {}
    
    /**
    Specify an else-if-branch functor template (using a static boolean
    predicate).

    @param f    Else-if-branch nullary functor template.
                The functor template call @c f() is never compiled or executed
                for this template specialization (because the if-statement
                static predicate is @c true).
                The return type of @c f() must be @c void for this template
                specialization (because the then-branch functor template calls
                return void).
    
    @tparam ElseIfPred  Static boolean predicate selecting which functor
                        template call to compile and execute.
    
    @return A call-if statement so the else statement and additional else-if
            statements can be specified if needed.
            Eventually, it will return void for this template specialization
            (because the then-branch functor template calls return void).
    */
    template<bool ElseIfPred, typename ElseIfThen>
    call_if_statement<true, Then, void> else_if_c(
        ElseIfThen const&
        #ifdef BOOST_CONTRACT_DETAIL_DOXYGEN // Avoid unused param warning.
            f
        #endif
    ) const { return *this; }

    /**
    Specify an else-if-branch functor template (using a nullary boolean
    meta-function).

    @param f    Else-if-branch nullary functor template.
                The functor template call @c f() is never compiled or executed
                for this template specialization (because the if-statement
                static predicate is @c true).
                The return type of @c f() must be @c void for this template
                specialization (because the then-branch functor template calls
                return void).

    @tparam ElseIfPred  Nullary boolean meta-function selecting which functor
                        template call to compile and execute.

    @return A call-if statement so the else statement and additional else-if
            statements can be specified if needed.
            Eventually, it will return void for this template specialization
            (because the then-branch functor template calls return void).
    */
    template<class ElseIfPred, typename ElseIfThen>
    call_if_statement<true, Then, void> else_if(
        ElseIfThen const&
        #ifdef BOOST_CONTRACT_DETAIL_DOXYGEN // Avoid unused param warning.
            f
        #endif
    ) const { return *this; }
};

/**
Template specialization to handle static predicates that are @c false (not
needed on C++17 compilers, use <c>if constexpr</c> instead).

This template specialization handles all else-branch functor template calls
(whether they return void or not).
Usually this class template is instantiated only via the return value of
@RefFunc{boost::contract::call_if} and @RefFunc{boost::contract::call_if_c}.

@see    @RefSect{extras.assertion_requirements__templates_,
        Assertion Requirements}

@tparam Then Type of functor template to call when the static predicate is
        @c true (never the case for this template specialization).
*/
template<typename Then> // Copyable (no data).
struct call_if_statement<false, Then,
    #ifndef BOOST_CONTRACT_DETAIL_DOXYGEN
        boost::contract::detail::none
    #else
        internal_type
    #endif
> {
    /**
    Construct this object with the then-branch functor template.

    @param f    Then-branch nullary functor template.
                The functor template call @c f() is never compiled or executed
                for this template specialization (because the if-statement
                static predicate is @c false).
                The return type of @c f() must be the same as (or implicitly
                convertible to) the return type of all other functor template
                calls specified for this call-if object.
    */
    explicit call_if_statement(Then const&
        #ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
            f
        #endif
    ) {}

    // Do not provide `operator result_type()` here, require else_ instead.

    /**
    Specify the else-branch functor template.

    @note   The <c>result_of<Else()>::type</c> expression needs be evaluated
            only when the static predicate is already checked to be @c false
            (because @c Else() is required to compile only in that case).
            Thus, this result-of expression is evaluated lazily and only in
            instantiations of this template specialization.
    
    @param f    Else-branch nullary functor template.
                The functor template call @c f() is actually compiled and
                executed for this template specialization (because the
                if-statement static predicate is @c false).
                The return type of @c f() must be the same as (or implicitly
                convertible to) the return type of all other functor template
                calls specified for this call-if object.
    
    @return A copy of the value returned by the call to the else-branch functor
            template @c f().
    */
    template<typename Else>
    #ifndef BOOST_CONTRACT_DETAIL_DOXYGEN
        BOOST_CONTRACT_CALL_IF_RESULT_OF_(Else)
    #else
        typename result_of<Else()>::type
    #endif
    else_(Else f) const { return f(); }
    
    /**
    Specify an else-if-branch functor template (using a static boolean
    predicate).

    @param f    Else-if-branch nullary functor template.
                The functor template call @c f() is actually compiled and
                executed if and only if @c ElseIfPred is @c true (because the
                if-statement static predicate is already @c false for this
                template specialization).
                The return type of @c f() must be the same as (or implicitly
                convertible to) the return type of all other functor template
                calls specified for this call-if object.
    
    @tparam ElseIfPred  Static boolean predicate selecting which functor
                        template call to compile and execute.

    @return A call-if statement so the else statement and additional else-if
            statements can be specified if needed.
            Eventually, this will be the return value of the one functor
            template call being compiled and executed.
    */
    template<bool ElseIfPred, typename ElseIfThen>
    call_if_statement<ElseIfPred, ElseIfThen> else_if_c(ElseIfThen f) const {
        return call_if_statement<ElseIfPred, ElseIfThen>(f);
    }
    
    /**
    Specify an else-if-branch functor template (using a nullary boolen
    meta-function).

    @param f    Else-if-branch nullary functor template.
                The functor template call @c f() is actually compiled and
                executed if and only if @c ElseIfPred::value is @c true (because
                the if-statement static predicate is already @c false for this
                template specialization).
                The return type of @c f() must be the same as (or implicitly
                convertible to) the return type of all other functor template
                calls specified for this call-if object.

    @tparam ElseIfPred  Nullary boolean meta-function selecting which functor
                        template call to compile and execute.

    @return A call-if statement so the else statement and additional else-if
            statements can be specified if needed.
            Eventually, this will be the return value of the one functor
            template call being compiled and executed.
    */
    template<class ElseIfPred, typename ElseIfThen>
    call_if_statement<ElseIfPred::value, ElseIfThen> else_if(ElseIfThen f)
            const {
        return call_if_statement<ElseIfPred::value, ElseIfThen>(f);
    }
};

/**
Select compilation and execution of functor template calls using a static
boolean predicate (not needed on C++17 compilers, use <c>if constexpr</c>
instead).

Create a call-if object with the specified then-branch functor template:

@code
boost::contract::call_if_c<Pred1>(
    then_functor_template1
).template else_if_c<Pred2>(            // Optional.
    then_functor_template2
)                                       // Optionally, other `else_if_c` or
...                                     // `else_if`.
.else_(                                 // Optional for `void` functors,
    else_functor_template               // but required for non `void`.
)
@endcode

Optional functor templates for else-if-branches and the else-branch can be
specified as needed (the else-branch function template is required if @c f
returns non-void).

@see    @RefSect{extras.assertion_requirements__templates_,
        Assertion Requirements}

@param f    Then-branch nullary functor template.
            The functor template call @c f() is compiled and executed if and
            only if @c Pred is @c true.
            The return type of other functor template calls specified for this
            call-if statement (else-branch, else-if-branches, etc.) must be the
            same as (or implicitly convertible to) the return type of
            then-branch functor call @c f().

@tparam Pred    Static boolean predicate selecting which functor template call
                to compile and execute.

@return A call-if statement so else and else-if statements can be specified if
        needed.
        Eventually, this will be the return value of the one functor template
        call being compiled and executed (which could also be @c void).
*/
template<bool Pred, typename Then>
call_if_statement<Pred, Then> call_if_c(Then f) {
    return call_if_statement<Pred, Then>(f);
}

/**
Select compilation and execution of functor template calls using a nullary
boolean meta-function (not needed on C++17 compilers, use <c>if constexpr</c>
instead).

This is equivalent to <c>boost::contract::call_if_c<Pred::value>(f)</c>.
Create a call-if object with the specified then-branch functor template:

@code
boost::contract::call_if<Pred1>(
    then_functor_template1
).template else_if<Pred2>(              // Optional.
    then_functor_template2
)                                       // Optionally, other `else_if` or
...                                     // `else_if_c`.
.else_(                                 // Optional for `void` functors,
    else_functor_template               // but required for non `void`.
)
@endcode

Optional functor templates for else-if-branches and the else-branch can be
specified as needed (the else-branch functor template is required if @c f
returns non-void).

@see    @RefSect{extras.assertion_requirements__templates_,
        Assertion Requirements}

@param f    Then-branch nullary functor template.
            The functor template call @c f() is compiled and executed if and
            only if @c Pred::value is @c true.
            The return type of other functor template calls specified for this
            call-if statement (else-branch, else-if-branches, etc.) must be the
            same as (or implicitly convertible to) the return type of
            then-branch functor template call @c f().

@tparam Pred    Nullary boolean meta-function selecting which functor template
                call to compile and execute.

@return A call-if statement so else and else-if statements can be specified if
        needed.
        Eventually, this will be the return value of the one functor template
        call being compiled and executed (which could also be @c void).
*/
template<class Pred, typename Then>
call_if_statement<Pred::value, Then> call_if(Then f) {
    return call_if_statement<Pred::value, Then>(f);
}

/**
Select compilation and execution of a boolean functor template condition using a
static boolean predicate (not needed on C++17 compilers, use
<c>if constexpr</c> instead).

Compile and execute the nullary boolean functor template call @c f() if and only
if the specified static boolean predicate @p Pred is @c true, otherwise
trivially return @p else_ (@c true by default) at run-time.

A call to <c>boost::contract::condition_if_c<Pred>(f, else_)</c> is logically
equivalent to <c>boost::contract::call_if_c<Pred>(f, [] { return else_; })</c>
(but its internal implementation is optimized and it does not actually use
@c call_if_c).

@see    @RefSect{extras.assertion_requirements__templates_,
        Assertion Requirements}

@param f    Nullary boolean functor template.
            The functor template call @c f() is compiled and executed if and
            only if @c Pred is @c true.

@tparam Pred    Static boolean predicate selecting when the functor template
                call @c f() should be compiled and executed.
@param else_    Boolean value to return when @c Pred is @c false (instead of
                compiling and executing the functor template call @c f()).

@return Boolean value returned by @c f() if the static predicate @c Pred is
        @c true. Otherwise, trivially return @p else_.
*/
#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    template<bool Pred, typename Then>
    bool condition_if_c(Then f, bool else_ = true);
#else
    // NOTE: condition_if is a very simple special case of call_if so it can be
    // trivially implemented using enable_if instead of call_if as done below.

    template<bool Pred, typename Then>
    typename boost::enable_if_c<Pred, bool>::type
    condition_if_c(Then f, bool /* else_ */ = true) { return f(); }

    template<bool Pred, typename Then>
    typename boost::disable_if_c<Pred, bool>::type
    condition_if_c(Then /* f */, bool else_ = true) { return else_; }
#endif

/**
Select compilation and execution of a boolean functor template condition using a
nullary boolean meta-function (not needed on C++17 compilers, use
<c>if constexpr</c> instead).

This is equivalent to
<c>boost::contract::condition_if_c<Pred::value>(f, else_)</c>.
Compile and execute the nullary boolean functor template call @c f() if and only
if the specified nullary boolean meta-function @p Pred::value is @c true,
otherwise trivially return @p else_ (@c true by default) at run-time.

@see    @RefSect{extras.assertion_requirements__templates_,
        Assertion Requirements}

@param f    Nullary boolean functor template.
            The functor template call @c f() is compiled and executed if and
            only if @c Pred::value is @c true.
@param else_    Boolean value to return when @c Pred::value is @c false (instead
                of compiling and executing the functor template call @c f()).

@tparam Pred    Nullary boolean meta-function selecting when the functor
                template call @c f() should be compiled and executed.

@return Boolean value returned by @c f() if the static predicate @c Pred::value
        is @c true. Otherwise, trivially return @p else_.
*/
template<class Pred, typename Then>
bool condition_if(Then f, bool else_ = true) {
    return condition_if_c<Pred::value>(f, else_);
}

} } // namespace

#endif // #include guard


/* call_if.hpp
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
*/