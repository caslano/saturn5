/*=============================================================================
    Adaptable closures

    Phoenix V0.9
    Copyright (c) 2001-2002 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See
    accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)

    URL: http://spirit.sourceforge.net/

==============================================================================*/
#ifndef BOOST_LAMBDA_CLOSURES_HPP
#define BOOST_LAMBDA_CLOSURES_HPP

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