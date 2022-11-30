// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef LIST_DWA2002627_HPP
# define LIST_DWA2002627_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/object.hpp>
# include <boost/python/converter/pytype_object_mgr_traits.hpp>
# include <boost/python/ssize_t.hpp>

namespace boost { namespace python { 

namespace detail
{
  struct BOOST_PYTHON_DECL list_base : object
  {
      void append(object_cref); // append object to end

      ssize_t count(object_cref value) const; // return number of occurrences of value

      void extend(object_cref sequence); // extend list by appending sequence elements
    
      long index(object_cref value) const; // return index of first occurrence of value

      void insert(ssize_t index, object_cref); // insert object before index
      void insert(object const& index, object_cref);

      object pop(); // remove and return item at index (default last)
      object pop(ssize_t index);
      object pop(object const& index);

      void remove(object_cref value); // remove first occurrence of value
    
      void reverse(); // reverse *IN PLACE*

      void sort(); //  sort *IN PLACE*; if given, cmpfunc(x, y) -> -1, 0, 1
#if PY_VERSION_HEX >= 0x03000000
      void sort(args_proxy const &args, 
                 kwds_proxy const &kwds);
#else
      void sort(object_cref cmpfunc);
#endif

   protected:
      list_base(); // new list
      explicit list_base(object_cref sequence); // new list initialized from sequence's items

      BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(list_base, object)
   private:    
      static detail::new_non_null_reference call(object const&);
  };
}

class list : public detail::list_base
{
    typedef detail::list_base base;
 public:
    list() {} // new list

    template <class T>
    explicit list(T const& sequence)
        : base(object(sequence))
    {
    }

    template <class T>
    void append(T const& x)
    {
        base::append(object(x));
    }

    template <class T>
    ssize_t count(T const& value) const
    {
        return base::count(object(value));
    }
    
    template <class T>
    void extend(T const& x)
    {
        base::extend(object(x));
    }

    template <class T>
    long index(T const& x) const
    {
        return base::index(object(x));
    }
    
    template <class T>
    void insert(ssize_t index, T const& x) // insert object before index
    {
        base::insert(index, object(x));
    }
    
    template <class T>
    void insert(object const& index, T const& x) // insert object before index
    {
        base::insert(index, object(x));
    }

    object pop() { return base::pop(); }
    object pop(ssize_t index) { return base::pop(index); }
    
    template <class T>
    object pop(T const& index)
    {
        return base::pop(object(index));
    }

    template <class T>
    void remove(T const& value)
    {
        base::remove(object(value));
    }

#if PY_VERSION_HEX <= 0x03000000
    void sort() { base::sort(); }

    template <class T>
    void sort(T const& value)
    {
        base::sort(object(value));
    }
#endif
    
 public: // implementation detail -- for internal use only
    BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(list, base)
};

//
// Converter Specializations
//
namespace converter
{
  template <>
  struct object_manager_traits<list>
      : pytype_object_manager_traits<&PyList_Type,list>
  {
  };
}

}} // namespace boost::python

#endif // LIST_DWA2002627_HPP

/* list.hpp
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
*/