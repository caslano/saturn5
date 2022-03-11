
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