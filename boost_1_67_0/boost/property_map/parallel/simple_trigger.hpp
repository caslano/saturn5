// Copyright (C) 2007 Douglas Gregor 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file contains a simplification of the "trigger" method for
// process groups. The simple trigger handles the common case where
// the handler associated with a trigger is a member function bound to
// a particular pointer.

#ifndef BOOST_PROPERTY_MAP_PARALLEL_SIMPLE_TRIGGER_HPP
#define BOOST_PROPERTY_MAP_PARALLEL_SIMPLE_TRIGGER_HPP

#include <boost/property_map/parallel/process_group.hpp>

namespace boost { namespace parallel {

namespace detail {

/**
 * INTERNAL ONLY
 *
 * The actual function object that bridges from the normal trigger
 * interface to the simplified interface. This is the equivalent of
 * bind(pmf, self, _1, _2, _3, _4), but without the compile-time
 * overhead of bind.
 */
template<typename Class, typename T, typename Result>
class simple_trigger_t 
{
public:
  simple_trigger_t(Class* self, 
                   Result (Class::*pmf)(int, int, const T&, 
                                        trigger_receive_context))
    : self(self), pmf(pmf) { }

  Result 
  operator()(int source, int tag, const T& data, 
             trigger_receive_context context) const
  {
    return (self->*pmf)(source, tag, data, context);
  }

private:
  Class* self;
  Result (Class::*pmf)(int, int, const T&, trigger_receive_context);
};

} // end namespace detail

/**
 * Simplified trigger interface that reduces the amount of code
 * required to connect a process group trigger to a handler that is
 * just a bound member function.
 *
 * INTERNAL ONLY
 */
template<typename ProcessGroup, typename Class, typename T>
inline void 
simple_trigger(ProcessGroup& pg, int tag, Class* self, 
               void (Class::*pmf)(int source, int tag, const T& data, 
                                  trigger_receive_context context), int)
{
  pg.template trigger<T>(tag, 
                         detail::simple_trigger_t<Class, T, void>(self, pmf));
}

/**
 * Simplified trigger interface that reduces the amount of code
 * required to connect a process group trigger with a reply to a
 * handler that is just a bound member function.
 *
 * INTERNAL ONLY
 */
template<typename ProcessGroup, typename Class, typename T, typename Result>
inline void 
simple_trigger(ProcessGroup& pg, int tag, Class* self, 
               Result (Class::*pmf)(int source, int tag, const T& data, 
                                    trigger_receive_context context), long)
{
  pg.template trigger_with_reply<T>
    (tag, detail::simple_trigger_t<Class, T, Result>(self, pmf));
}

/**
 * Simplified trigger interface that reduces the amount of code
 * required to connect a process group trigger to a handler that is
 * just a bound member function.
 */
template<typename ProcessGroup, typename Class, typename T, typename Result>
inline void 
simple_trigger(ProcessGroup& pg, int tag, Class* self, 
               Result (Class::*pmf)(int source, int tag, const T& data, 
                                    trigger_receive_context context))
{
        // We pass 0 (an int) to help VC++ disambiguate calls to simple_trigger 
        // with Result=void.
        simple_trigger(pg, tag, self, pmf, 0); 
}

} } // end namespace boost::parallel

namespace boost { namespace graph { namespace parallel { using boost::parallel::simple_trigger; } } }

#endif // BOOST_PROPERTY_MAP_PARALLEL_SIMPLE_TRIGGER_HPP

/* simple_trigger.hpp
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
*/