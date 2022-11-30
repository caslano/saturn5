/*=============================================================================
    Phoenix V1.2.1
    Copyright (c) 2001-2002 Joel de Guzman
    MT code Copyright (c) 2002-2003 Martin Wille

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_SPIRIT_CLASSIC_PHOENIX_CLOSURES_HPP
#define BOOST_SPIRIT_CLASSIC_PHOENIX_CLOSURES_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/phoenix/actor.hpp>
#include <boost/assert.hpp>

#ifdef PHOENIX_THREADSAFE
#include <boost/thread/tss.hpp>
#include <boost/thread/once.hpp>
#endif

///////////////////////////////////////////////////////////////////////////////
namespace phoenix {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

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
//      use its self_type as a parameter to closure_frame:
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

namespace impl
{
    ///////////////////////////////////////////////////////////////////////
    // closure_frame_holder is a simple class that encapsulates the
    // storage for a frame pointer. It uses thread specific data in
    // case when multithreading is enabled, an ordinary pointer otherwise
    //
    // it has get() and set() member functions. set() has to be used
    // _after_ get(). get() contains intialisation code in the multi
    // threading case
    //
    // closure_frame_holder is used by the closure<> class to store
    // the pointer to the current frame.
    //
#ifndef PHOENIX_THREADSAFE
    template <typename FrameT>
    struct closure_frame_holder
    {
        typedef FrameT frame_t;
        typedef frame_t *frame_ptr;

        closure_frame_holder() : frame(0) {}

        frame_ptr &get() { return frame; }
        void set(frame_t *f) { frame = f; }

    private:
        frame_ptr frame;

        // no copies, no assignments
        closure_frame_holder(closure_frame_holder const &);
        closure_frame_holder &operator=(closure_frame_holder const &);
    };
#else
    template <typename FrameT>
    struct closure_frame_holder
    {
        typedef FrameT   frame_t;
        typedef frame_t *frame_ptr;

        closure_frame_holder() : tsp_frame() {}

        frame_ptr &get()
        {
            if (!tsp_frame.get())
                tsp_frame.reset(new frame_ptr(0));
            return *tsp_frame;
        }
        void set(frame_ptr f)
        {
            *tsp_frame = f;
        }

    private:
        boost::thread_specific_ptr<frame_ptr> tsp_frame;

        // no copies, no assignments
        closure_frame_holder(closure_frame_holder const &);
        closure_frame_holder &operator=(closure_frame_holder const &);
    };
#endif
} // namespace phoenix::impl

///////////////////////////////////////////////////////////////////////////////
//
//  closure_frame class
//
///////////////////////////////////////////////////////////////////////////////
template <typename ClosureT>
class closure_frame : public ClosureT::tuple_t {

public:

    closure_frame(ClosureT const& clos)
    : ClosureT::tuple_t(), save(clos.frame.get()), frame(clos.frame)
    { clos.frame.set(this); }

    template <typename TupleT>
    closure_frame(ClosureT const& clos, TupleT const& init)
    : ClosureT::tuple_t(init), save(clos.frame.get()), frame(clos.frame)
    { clos.frame.set(this); }

    ~closure_frame()
    { frame.set(save); }

private:

    closure_frame(closure_frame const&);            // no copy
    closure_frame& operator=(closure_frame const&); // no assign

    closure_frame* save;
    impl::closure_frame_holder<closure_frame>& frame;
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
    : frame(ClosureT::closure_frame_holder_ref()) {}

    template <typename TupleT>
    struct result {

        typedef typename tuple_element<
            N, typename ClosureT::tuple_t
        >::rtype type;
    };

    template <typename TupleT>
    typename tuple_element<N, typename ClosureT::tuple_t>::rtype
    eval(TupleT const& /*args*/) const
    {
        using namespace std;
        BOOST_ASSERT(frame.get() != 0);
        tuple_index<N> const idx;
        return (*frame.get())[idx];
    }

private:
    impl::closure_frame_holder<typename ClosureT::closure_frame_t> &frame;
};

///////////////////////////////////////////////////////////////////////////////
//
//  closure class
//
///////////////////////////////////////////////////////////////////////////////
template <
        typename T0 = nil_t
    ,   typename T1 = nil_t
    ,   typename T2 = nil_t

#if PHOENIX_LIMIT > 3
    ,   typename T3 = nil_t
    ,   typename T4 = nil_t
    ,   typename T5 = nil_t

#if PHOENIX_LIMIT > 6
    ,   typename T6 = nil_t
    ,   typename T7 = nil_t
    ,   typename T8 = nil_t

#if PHOENIX_LIMIT > 9
    ,   typename T9 = nil_t
    ,   typename T10 = nil_t
    ,   typename T11 = nil_t

#if PHOENIX_LIMIT > 12
    ,   typename T12 = nil_t
    ,   typename T13 = nil_t
    ,   typename T14 = nil_t

#endif
#endif
#endif
#endif
>
class closure {

public:

    typedef tuple<
            T0, T1, T2
#if PHOENIX_LIMIT > 3
        ,   T3, T4, T5
#if PHOENIX_LIMIT > 6
        ,   T6, T7, T8
#if PHOENIX_LIMIT > 9
        ,   T9, T10, T11
#if PHOENIX_LIMIT > 12
        ,   T12, T13, T14
#endif
#endif
#endif
#endif
        > tuple_t;

    typedef closure<
            T0, T1, T2
#if PHOENIX_LIMIT > 3
        ,   T3, T4, T5
#if PHOENIX_LIMIT > 6
        ,   T6, T7, T8
#if PHOENIX_LIMIT > 9
        ,   T9, T10, T11
#if PHOENIX_LIMIT > 12
        ,   T12, T13, T14
#endif
#endif
#endif
#endif
        > self_t;

    typedef closure_frame<self_t> closure_frame_t;

                            closure()
                            : frame()       { closure_frame_holder_ref(&frame); }

    typedef actor<closure_member<0, self_t> > member1;
    typedef actor<closure_member<1, self_t> > member2;
    typedef actor<closure_member<2, self_t> > member3;

#if PHOENIX_LIMIT > 3
    typedef actor<closure_member<3, self_t> > member4;
    typedef actor<closure_member<4, self_t> > member5;
    typedef actor<closure_member<5, self_t> > member6;

#if PHOENIX_LIMIT > 6
    typedef actor<closure_member<6, self_t> > member7;
    typedef actor<closure_member<7, self_t> > member8;
    typedef actor<closure_member<8, self_t> > member9;

#if PHOENIX_LIMIT > 9
    typedef actor<closure_member<9, self_t> > member10;
    typedef actor<closure_member<10, self_t> > member11;
    typedef actor<closure_member<11, self_t> > member12;

#if PHOENIX_LIMIT > 12
    typedef actor<closure_member<12, self_t> > member13;
    typedef actor<closure_member<13, self_t> > member14;
    typedef actor<closure_member<14, self_t> > member15;

#endif
#endif
#endif
#endif

#if !defined(__MWERKS__) || (__MWERKS__ > 0x3002)
private:
#endif

    closure(closure const&);            // no copy
    closure& operator=(closure const&); // no assign

#if !defined(__MWERKS__) || (__MWERKS__ > 0x3002)
    template <int N, typename ClosureT>
    friend class closure_member;

    template <typename ClosureT>
    friend class closure_frame;
#endif

    typedef impl::closure_frame_holder<closure_frame_t> holder_t;

#ifdef PHOENIX_THREADSAFE
    static boost::thread_specific_ptr<holder_t*> &
    tsp_frame_instance()
    {
        static boost::thread_specific_ptr<holder_t*> the_instance;
        return the_instance;
    }

    static void
    tsp_frame_instance_init()
    {
        tsp_frame_instance();
    }
#endif

    static holder_t &
    closure_frame_holder_ref(holder_t* holder_ = 0)
    {
#ifdef PHOENIX_THREADSAFE
#ifndef BOOST_THREAD_PROVIDES_ONCE_CXX11
        static boost::once_flag been_here = BOOST_ONCE_INIT;
#else
        static boost::once_flag been_here;
#endif
        boost::call_once(been_here, tsp_frame_instance_init);
        boost::thread_specific_ptr<holder_t*> &tsp_frame = tsp_frame_instance();
        if (!tsp_frame.get())
            tsp_frame.reset(new holder_t *(0));
        holder_t *& holder = *tsp_frame;
#else
        static holder_t* holder = 0;
#endif
        if (holder_ != 0)
            holder = holder_;
        return *holder;
    }

    mutable holder_t frame;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

}
   //  namespace phoenix

#endif

/* closures.hpp
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
*/