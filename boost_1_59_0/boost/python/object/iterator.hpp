// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef ITERATOR_DWA2002510_HPP
# define ITERATOR_DWA2002510_HPP

# include <boost/python/detail/prefix.hpp>
# include <boost/python/detail/type_traits.hpp>

# include <boost/python/class.hpp>
# include <boost/python/return_value_policy.hpp>
# include <boost/python/return_by_value.hpp>
# include <boost/python/handle.hpp>
# include <boost/python/make_function.hpp>

# include <boost/python/object/iterator_core.hpp>
# include <boost/python/object/class_detail.hpp>
# include <boost/python/object/function_object.hpp>

# include <boost/mpl/vector/vector10.hpp>
# include <boost/mpl/if.hpp>

# include <boost/python/detail/raw_pyobject.hpp>

# include <boost/type.hpp>

# include <iterator>

namespace boost { namespace python { namespace objects {

// CallPolicies for the next() method of iterators. We don't want
// users to have to explicitly specify that the references returned by
// iterators are copied, so we just replace the result_converter from
// the default_iterator_call_policies with a permissive one which
// always copies the result.
typedef return_value_policy<return_by_value> default_iterator_call_policies;

// Instantiations of these are wrapped to produce Python iterators.
template <class NextPolicies, class Iterator>
struct iterator_range
{
    iterator_range(object sequence, Iterator start, Iterator finish);

    typedef std::iterator_traits<Iterator> traits_t;

    struct next
    {
        typedef typename mpl::if_<
            is_reference<
                typename traits_t::reference
            >
          , typename traits_t::reference
          , typename traits_t::value_type
        >::type result_type;
        
        result_type
        operator()(iterator_range<NextPolicies,Iterator>& self)
        {
            if (self.m_start == self.m_finish)
                stop_iteration_error();
            return *self.m_start++;
        }

# if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
        // CWPro8 has a codegen problem when this is an empty class
        int garbage;
# endif 
    };
    
    typedef next next_fn;
    
    object m_sequence; // Keeps the sequence alive while iterating.
    Iterator m_start;
    Iterator m_finish;
};

namespace detail
{
  // Get a Python class which contains the given iterator and
  // policies, creating it if necessary. Requires: NextPolicies is
  // default-constructible.
  template <class Iterator, class NextPolicies>
  object demand_iterator_class(char const* name, Iterator* = 0, NextPolicies const& policies = NextPolicies())
  {
      typedef iterator_range<NextPolicies,Iterator> range_;

      // Check the registry. If one is already registered, return it.
      handle<> class_obj(
          objects::registered_class_object(python::type_id<range_>()));
        
      if (class_obj.get() != 0)
          return object(class_obj);

      typedef typename range_::next_fn next_fn;
      typedef typename next_fn::result_type result_type;
      
      return class_<range_>(name, no_init)
          .def("__iter__", identity_function())
          .def(
#if PY_VERSION_HEX >= 0x03000000
              "__next__"
#else
              "next"
#endif
            , make_function(
                next_fn()
              , policies
              , mpl::vector2<result_type,range_&>()
            ));
  }

  // A function object which builds an iterator_range.
  template <
      class Target
    , class Iterator
    , class Accessor1
    , class Accessor2
    , class NextPolicies
  >
  struct py_iter_
  {
      py_iter_(Accessor1 const& get_start, Accessor2 const& get_finish)
        : m_get_start(get_start)
        , m_get_finish(get_finish)
      {}
      
      // Extract an object x of the Target type from the first Python
      // argument, and invoke get_start(x)/get_finish(x) to produce
      // iterators, which are used to construct a new iterator_range<>
      // object that gets wrapped into a Python iterator.
      iterator_range<NextPolicies,Iterator>
      operator()(back_reference<Target&> x) const
      {
          // Make sure the Python class is instantiated.
          detail::demand_iterator_class("iterator", (Iterator*)0, NextPolicies());
          
          return iterator_range<NextPolicies,Iterator>(
              x.source()
            , m_get_start(x.get())
            , m_get_finish(x.get())
          );
      }
   private:
      Accessor1 m_get_start;
      Accessor2 m_get_finish;
  };

  template <class Target, class Iterator, class NextPolicies, class Accessor1, class Accessor2>
  inline object make_iterator_function(
      Accessor1 const& get_start
    , Accessor2 const& get_finish
    , NextPolicies const& /*next_policies*/
    , Iterator const& (*)()
    , boost::type<Target>*
    , int
  )
  {
      return make_function(
          py_iter_<Target,Iterator,Accessor1,Accessor2,NextPolicies>(get_start, get_finish)
        , default_call_policies()
        , mpl::vector2<iterator_range<NextPolicies,Iterator>, back_reference<Target&> >()
      );
  }

  template <class Target, class Iterator, class NextPolicies, class Accessor1, class Accessor2>
  inline object make_iterator_function(
      Accessor1 const& get_start
    , Accessor2 const& get_finish
    , NextPolicies const& next_policies
    , Iterator& (*)()
    , boost::type<Target>*
    , ...)
  {
      return make_iterator_function(
          get_start
        , get_finish
        , next_policies
        , (Iterator const&(*)())0
        , (boost::type<Target>*)0
        , 0
      );
  }

}

// Create a Python callable object which accepts a single argument
// convertible to the C++ Target type and returns a Python
// iterator. The Python iterator uses get_start(x) and get_finish(x)
// (where x is an instance of Target) to produce begin and end
// iterators for the range, and an instance of NextPolicies is used as
// CallPolicies for the Python iterator's next() function. 
template <class Target, class NextPolicies, class Accessor1, class Accessor2>
inline object make_iterator_function(
    Accessor1 const& get_start
  , Accessor2 const& get_finish
  , NextPolicies const& next_policies
  , boost::type<Target>* = 0
)
{
    typedef typename Accessor1::result_type iterator;
    typedef typename boost::python::detail::add_const<iterator>::type iterator_const;
    typedef typename boost::python::detail::add_lvalue_reference<iterator_const>::type iterator_cref;
      
    return detail::make_iterator_function(
        get_start
      , get_finish
      , next_policies
      , (iterator_cref(*)())0
      , (boost::type<Target>*)0
      , 0
    );
}

//
// implementation
//
template <class NextPolicies, class Iterator>
inline iterator_range<NextPolicies,Iterator>::iterator_range(
    object sequence, Iterator start, Iterator finish)
    : m_sequence(sequence), m_start(start), m_finish(finish)
{
}

}}} // namespace boost::python::objects

#endif // ITERATOR_DWA2002510_HPP

/* iterator.hpp
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
*/