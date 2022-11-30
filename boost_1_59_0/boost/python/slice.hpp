#ifndef BOOST_PYTHON_SLICE_JDB20040105_HPP
#define BOOST_PYTHON_SLICE_JDB20040105_HPP

// Copyright (c) 2004 Jonathan Brandmeyer
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/python/detail/prefix.hpp>
#include <boost/config.hpp>
#include <boost/python/object.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/converter/pytype_object_mgr_traits.hpp>

#include <boost/iterator/iterator_traits.hpp>

#include <iterator>
#include <algorithm>

namespace boost { namespace python {

namespace detail
{
  class BOOST_PYTHON_DECL slice_base : public object
  {
   public:
      // Get the Python objects associated with the slice.  In principle, these 
      // may be any arbitrary Python type, but in practice they are usually 
      // integers.  If one or more parameter is ommited in the Python expression 
      // that created this slice, than that parameter is None here, and compares 
      // equal to a default-constructed boost::python::object.
      // If a user-defined type wishes to support slicing, then support for the 
      // special meaning associated with negative indices is up to the user.
      object start() const;
      object stop() const;
      object step() const;
        
   protected:
      explicit slice_base(PyObject*, PyObject*, PyObject*);

      BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(slice_base, object)
  };
}

class slice : public detail::slice_base
{
    typedef detail::slice_base base;
 public:
    // Equivalent to slice(::)
    slice() : base(0,0,0) {}

    // Each argument must be slice_nil, or implicitly convertable to object.
    // They should normally be integers.
    template<typename Integer1, typename Integer2>
    slice( Integer1 start, Integer2 stop)
        : base( object(start).ptr(), object(stop).ptr(), 0 )
    {}
    
    template<typename Integer1, typename Integer2, typename Integer3>
    slice( Integer1 start, Integer2 stop, Integer3 stride)
        : base( object(start).ptr(), object(stop).ptr(), object(stride).ptr() )
    {}
        
    // The following algorithm is intended to automate the process of 
    // determining a slice range when you want to fully support negative
    // indices and non-singular step sizes.  Its functionallity is simmilar to 
    // PySlice_GetIndicesEx() in the Python/C API, but tailored for C++ users.
    // This template returns a slice::range struct that, when used in the 
    // following iterative loop, will traverse a slice of the function's
    // arguments.
    // while (start != end) { 
    //     do_foo(...); 
    //     std::advance( start, step); 
    // }
    // do_foo(...); // repeat exactly once more.
    
    // Arguments: a [begin, end) pair of STL-conforming random-access iterators.
        
    // Return: slice::range, where start and stop define a _closed_ interval
    // that covers at most [begin, end-1] of the provided arguments, and a step 
    // that is non-zero.
    
    // Throws: error_already_set() if any of the indices are neither None nor 
    //   integers, or the slice has a step value of zero.
    // std::invalid_argument if the resulting range would be empty.  Normally, 
    //   you should catch this exception and return an empty sequence of the
    //   appropriate type.
    
    // Performance: constant time for random-access iterators.
    
    // Rationale: 
    //   closed-interval: If an open interval were used, then for a non-singular
    //     value for step, the required state for the end iterator could be 
    //     beyond the one-past-the-end postion of the specified range.  While 
    //     probably harmless, the behavior of STL-conforming iterators is 
    //     undefined in this case.
    //   exceptions on zero-length range: It is impossible to define a closed 
    //     interval over an empty range, so some other form of error checking 
    //     would have to be used by the user to prevent undefined behavior.  In
    //     the case where the user fails to catch the exception, it will simply
    //     be translated to Python by the default exception handling mechanisms.

    template<typename RandomAccessIterator>
    struct range
    {
        RandomAccessIterator start;
        RandomAccessIterator stop;
        typename iterator_difference<RandomAccessIterator>::type step;
    };
    
    template<typename RandomAccessIterator>
    slice::range<RandomAccessIterator>
    get_indices( const RandomAccessIterator& begin, 
        const RandomAccessIterator& end) const
    {
        // This is based loosely on PySlice_GetIndicesEx(), but it has been 
        // carefully crafted to ensure that these iterators never fall out of
        // the range of the container.
        slice::range<RandomAccessIterator> ret;
        
        typedef typename iterator_difference<RandomAccessIterator>::type difference_type;
        difference_type max_dist = std::distance(begin, end);

        object slice_start = this->start();
        object slice_stop = this->stop();
        object slice_step = this->step();
        
        // Extract the step.
        if (slice_step == object()) {
            ret.step = 1;
        }
        else {
            ret.step = extract<long>( slice_step);
            if (ret.step == 0) {
                PyErr_SetString( PyExc_IndexError, "step size cannot be zero.");
                throw_error_already_set();
            }
        }
        
        // Setup the start iterator.
        if (slice_start == object()) {
            if (ret.step < 0) {
                ret.start = end;
                --ret.start;
            }
            else
                ret.start = begin;
        }
        else {
            difference_type i = extract<long>( slice_start);
            if (i >= max_dist && ret.step > 0)
                    throw std::invalid_argument( "Zero-length slice");
            if (i >= 0) {
                ret.start = begin;
                BOOST_USING_STD_MIN();
                std::advance( ret.start, min BOOST_PREVENT_MACRO_SUBSTITUTION(i, max_dist-1));
            }
            else {
                if (i < -max_dist && ret.step < 0)
                    throw std::invalid_argument( "Zero-length slice");
                ret.start = end;
                // Advance start (towards begin) not farther than begin.
                std::advance( ret.start, (-i < max_dist) ? i : -max_dist );
            }
        }
        
        // Set up the stop iterator.  This one is a little trickier since slices
        // define a [) range, and we are returning a [] range.
        if (slice_stop == object()) {
            if (ret.step < 0) {
                ret.stop = begin;
            }
            else {
                ret.stop = end;
                std::advance( ret.stop, -1);
            }
        }
        else {
            difference_type i = extract<long>(slice_stop);
            // First, branch on which direction we are going with this.
            if (ret.step < 0) {
                if (i+1 >= max_dist || i == -1)
                    throw std::invalid_argument( "Zero-length slice");
                
                if (i >= 0) {
                    ret.stop = begin;
                    std::advance( ret.stop, i+1);
                }
                else { // i is negative, but more negative than -1.
                    ret.stop = end;
                    std::advance( ret.stop, (-i < max_dist) ? i : -max_dist);
                }
            }
            else { // stepping forward
                if (i == 0 || -i >= max_dist)
                    throw std::invalid_argument( "Zero-length slice");
                
                if (i > 0) {
                    ret.stop = begin;
                    std::advance( ret.stop, (std::min)( i-1, max_dist-1));
                }
                else { // i is negative, but not more negative than -max_dist
                    ret.stop = end;
                    std::advance( ret.stop, i-1);
                }
            }
        }
        
        // Now the fun part, handling the possibilites surrounding step.
        // At this point, step has been initialized, ret.stop, and ret.step
        // represent the widest possible range that could be traveled
        // (inclusive), and final_dist is the maximum distance covered by the
        // slice.
        typename iterator_difference<RandomAccessIterator>::type final_dist = 
            std::distance( ret.start, ret.stop);
        
        // First case, if both ret.start and ret.stop are equal, then step
        // is irrelevant and we can return here.
        if (final_dist == 0)
            return ret;
        
        // Second, if there is a sign mismatch, than the resulting range and 
        // step size conflict: std::advance( ret.start, ret.step) goes away from
        // ret.stop.
        if ((final_dist > 0) != (ret.step > 0))
            throw std::invalid_argument( "Zero-length slice.");
        
        // Finally, if the last step puts us past the end, we move ret.stop
        // towards ret.start in the amount of the remainder.
        // I don't remember all of the oolies surrounding negative modulii,
        // so I am handling each of these cases separately.
        if (final_dist < 0) {
            difference_type remainder = -final_dist % -ret.step;
            std::advance( ret.stop, remainder);
        }
        else {
            difference_type remainder = final_dist % ret.step;
            std::advance( ret.stop, -remainder);
        }
        
        return ret;
    }

    // Incorrect spelling. DO NOT USE. Only here for backward compatibility.
    // Corrected 2011-06-14.
    template<typename RandomAccessIterator>
    slice::range<RandomAccessIterator>
    get_indicies( const RandomAccessIterator& begin, 
        const RandomAccessIterator& end) const
    {
        return get_indices(begin, end);
    }
        
 public:
    // This declaration, in conjunction with the specialization of 
    // object_manager_traits<> below, allows C++ functions accepting slice 
    // arguments to be called from from Python.  These constructors should never
    // be used in client code.
    BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(slice, detail::slice_base)
};


namespace converter {

template<>
struct object_manager_traits<slice>
    : pytype_object_manager_traits<&PySlice_Type, slice>
{
};
    
} // !namesapce converter

} } // !namespace ::boost::python


#endif // !defined BOOST_PYTHON_SLICE_JDB20040105_HPP

/* slice.hpp
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
*/