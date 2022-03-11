/*=============================================================================
    Adaptable closures

    Phoenix V0.9
    Copyright (c) 2001-2002 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See
    accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)

    URL: http://spirit.sourceforge.net/

==============================================================================*/
#ifndef PHOENIX_CLOSURES_HPP
#define PHOENIX_CLOSURES_HPP

///////////////////////////////////////////////////////////////////////////////
#include "boost/lambda/core.hpp"
///////////////////////////////////////////////////////////////////////////////
namespace boost {
namespace lambda {

///////////////////////////////////////////////////////////////////////////////
//
//  Adaptable closures
//
//      The framework will not be complete without some form of closures
//      support. Closures encapsulate a stack frame where local
//      variables are created upon entering a function and destructed
//      upon exiting. Closures provide an environment for local
//      variables to reside. Closures can hold heterogeneous types.
//
//      Phoenix closures are true hardware stack based closures. At the
//      very least, closures enable true reentrancy in lambda functions.
//      A closure provides access to a function stack frame where local
//      variables reside. Modeled after Pascal nested stack frames,
//      closures can be nested just like nested functions where code in
//      inner closures may access local variables from in-scope outer
//      closures (accessing inner scopes from outer scopes is an error
//      and will cause a run-time assertion failure).
//
//      There are three (3) interacting classes:
//
//      1) closure:
//
//      At the point of declaration, a closure does not yet create a
//      stack frame nor instantiate any variables. A closure declaration
//      declares the types and names[note] of the local variables. The
//      closure class is meant to be subclassed. It is the
//      responsibility of a closure subclass to supply the names for
//      each of the local variable in the closure. Example:
//
//          struct my_closure : closure<int, string, double> {
//
//              member1 num;        // names the 1st (int) local variable
//              member2 message;    // names the 2nd (string) local variable
//              member3 real;       // names the 3rd (double) local variable
//          };
//
//          my_closure clos;
//
//      Now that we have a closure 'clos', its local variables can be
//      accessed lazily using the dot notation. Each qualified local
//      variable can be used just like any primitive actor (see
//      primitives.hpp). Examples:
//
//          clos.num = 30
//          clos.message = arg1
//          clos.real = clos.num * 1e6
//
//      The examples above are lazily evaluated. As usual, these
//      expressions return composite actors that will be evaluated
//      through a second function call invocation (see operators.hpp).
//      Each of the members (clos.xxx) is an actor. As such, applying
//      the operator() will reveal its identity:
//
//          clos.num() // will return the current value of clos.num
//
//      *** [note] Acknowledgement: Juan Carlos Arevalo-Baeza (JCAB)
//      introduced and initilally implemented the closure member names
//      that uses the dot notation.
//
//      2) closure_member
//
//      The named local variables of closure 'clos' above are actually
//      closure members. The closure_member class is an actor and
//      conforms to its conceptual interface. member1..memberN are
//      predefined typedefs that correspond to each of the listed types
//      in the closure template parameters.
//
//      3) closure_frame
//
//      When a closure member is finally evaluated, it should refer to
//      an actual instance of the variable in the hardware stack.
//      Without doing so, the process is not complete and the evaluated
//      member will result to an assertion failure. Remember that the
//      closure is just a declaration. The local variables that a
//      closure refers to must still be instantiated.
//
//      The closure_frame class does the actual instantiation of the
//      local variables and links these variables with the closure and
//      all its members. There can be multiple instances of
//      closure_frames typically situated in the stack inside a
//      function. Each closure_frame instance initiates a stack frame
//      with a new set of closure local variables. Example:
//
//          void foo()
//          {
//              closure_frame<my_closure> frame(clos);
//              /* do something */
//          }
//
//      where 'clos' is an instance of our closure 'my_closure' above.
//      Take note that the usage above precludes locally declared
//      classes. If my_closure is a locally declared type, we can still
//      use its self_type as a paramater to closure_frame:
//
//          closure_frame<my_closure::self_type> frame(clos);
//
//      Upon instantiation, the closure_frame links the local variables
//      to the closure. The previous link to another closure_frame
//      instance created before is saved. Upon destruction, the
//      closure_frame unlinks itself from the closure and relinks the
//      preceding closure_frame prior to this instance.
//
//      The local variables in the closure 'clos' above is default
//      constructed in the stack inside function 'foo'. Once 'foo' is
//      exited, all of these local variables are destructed. In some
//      cases, default construction is not desirable and we need to
//      initialize the local closure variables with some values. This
//      can be done by passing in the initializers in a compatible
//      tuple. A compatible tuple is one with the same number of
//      elements as the destination and where each element from the
//      destination can be constructed from each corresponding element
//      in the source. Example:
//
//          tuple<int, char const*, int> init(123, "Hello", 1000);
//          closure_frame<my_closure> frame(clos, init);
//
//      Here now, our closure_frame's variables are initialized with
//      int: 123, char const*: "Hello" and int: 1000.
//
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//
//  closure_frame class
//
///////////////////////////////////////////////////////////////////////////////
template <typename ClosureT>
class closure_frame : public ClosureT::tuple_t {

public:

    closure_frame(ClosureT& clos)
    : ClosureT::tuple_t(), save(clos.frame), frame(clos.frame)
    { clos.frame = this; }

    template <typename TupleT>
    closure_frame(ClosureT& clos, TupleT const& init)
    : ClosureT::tuple_t(init), save(clos.frame), frame(clos.frame)
    { clos.frame = this; }

    ~closure_frame()
    { frame = save; }

private:

    closure_frame(closure_frame const&);            // no copy
    closure_frame& operator=(closure_frame const&); // no assign

    closure_frame* save;
    closure_frame*& frame;
};

///////////////////////////////////////////////////////////////////////////////
//
//  closure_member class
//
///////////////////////////////////////////////////////////////////////////////
template <int N, typename ClosureT>
class closure_member {

public:

    typedef typename ClosureT::tuple_t tuple_t;

    closure_member()
    : frame(ClosureT::closure_frame_ref()) {}

    template <typename TupleT>
    struct sig {

        typedef typename detail::tuple_element_as_reference<
            N, typename ClosureT::tuple_t
        >::type type;
    };

    template <class Ret, class A, class B, class C>
    //    typename detail::tuple_element_as_reference
    //        <N, typename ClosureT::tuple_t>::type
    Ret
    call(A&, B&, C&) const
    {
        assert(frame);
        return boost::tuples::get<N>(*frame);
    }


private:

    typename ClosureT::closure_frame_t*& frame;
};

///////////////////////////////////////////////////////////////////////////////
//
//  closure class
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename T0 = null_type,
    typename T1 = null_type,
    typename T2 = null_type,
    typename T3 = null_type,
    typename T4 = null_type
>
class closure {

public:

    typedef tuple<T0, T1, T2, T3, T4> tuple_t;
    typedef closure<T0, T1, T2, T3, T4> self_t;
    typedef closure_frame<self_t> closure_frame_t;

                            closure()
                            : frame(0)      { closure_frame_ref(&frame); }
    closure_frame_t&        context()       { assert(frame); return frame; }
    closure_frame_t const&  context() const { assert(frame); return frame; }

    typedef lambda_functor<closure_member<0, self_t> > member1;
    typedef lambda_functor<closure_member<1, self_t> > member2;
    typedef lambda_functor<closure_member<2, self_t> > member3;
    typedef lambda_functor<closure_member<3, self_t> > member4;
    typedef lambda_functor<closure_member<4, self_t> > member5;

private:

    closure(closure const&);            // no copy
    closure& operator=(closure const&); // no assign

    template <int N, typename ClosureT>
    friend class closure_member;

    template <typename ClosureT>
    friend class closure_frame;

    static closure_frame_t*&
    closure_frame_ref(closure_frame_t** frame_ = 0)
    {
        static closure_frame_t** frame = 0;
        if (frame_ != 0)
            frame = frame_;
        return *frame;
    }

    closure_frame_t* frame;
};

}}
   //  namespace 

#endif

/* closures.hpp
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
*/