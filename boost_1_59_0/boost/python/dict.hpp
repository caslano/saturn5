// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef DICT_20020706_HPP
#define DICT_20020706_HPP

# include <boost/python/detail/prefix.hpp>

#include <boost/python/object.hpp>
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/converter/pytype_object_mgr_traits.hpp>

namespace boost { namespace python {

class dict;

namespace detail
{
  struct BOOST_PYTHON_DECL dict_base : object
  {
      // D.clear() -> None.  Remove all items from D.
      void clear();

      // D.copy() -> a shallow copy of D
      dict copy();

      // D.get(k[,d]) -> D[k] if D.has_key(k), else d.  d defaults to None.
      object get(object_cref k) const;
    
      object get(object_cref k, object_cref d) const;

      // D.has_key(k) -> 1 if D has a key k, else 0
      bool has_key(object_cref k) const;

      // D.items() -> list of D's (key, value) pairs, as 2-tuples
      list items() const;
 
      // D.iteritems() -> an iterator over the (key, value) items of D
      object iteritems() const;

      // D.iterkeys() -> an iterator over the keys of D
      object iterkeys() const;

      // D.itervalues() -> an iterator over the values of D
      object itervalues() const;
 
      // D.keys() -> list of D's keys
      list keys() const;
 
      // D.popitem() -> (k, v), remove and return some (key, value) pair as a
      // 2-tuple; but raise KeyError if D is empty
      tuple popitem();

      // D.setdefault(k[,d]) -> D.get(k,d), also set D[k]=d if not D.has_key(k)
      object setdefault(object_cref k);

      object setdefault(object_cref k, object_cref d);

      // D.update(E) -> None.  Update D from E: for k in E.keys(): D[k] = E[k]
      void update(object_cref E);

      // D.values() -> list of D's values
      list values() const;

   protected:
      // dict() -> new empty dictionary.
      // dict(mapping) -> new dictionary initialized from a mapping object's
      //     (key, value) pairs.
      // dict(seq) -> new dictionary initialized as if via:
      dict_base();   // new dict
      explicit dict_base(object_cref data);

      BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(dict_base, object)
   private:
      static detail::new_reference call(object const&);
  };
}

class dict : public detail::dict_base
{
    typedef detail::dict_base base;
 public:
    // dict() -> new empty dictionary.
    // dict(mapping) -> new dictionary initialized from a mapping object's
    //     (key, value) pairs.
    // dict(seq) -> new dictionary initialized as if via:
    dict() {}   // new dict

    template <class T>
    explicit dict(T const& data)
        : base(object(data))
    {
    }

    template<class T>
    object get(T const& k) const 
    {
        return base::get(object(k));
    }
    
    template<class T1, class T2>
    object get(T1 const& k, T2 const& d) const 
    {
        return base::get(object(k),object(d));
    }
    
    template<class T>
    bool has_key(T const& k) const
    {
        return base::has_key(object(k));
    }
    
    template<class T>
    object setdefault(T const& k)
    {
        return base::setdefault(object(k));
    }
    
    template<class T1, class T2>
    object setdefault(T1 const& k, T2 const& d)
    {
        return base::setdefault(object(k),object(d));
    }

    template<class T>
    void update(T const& E)
    {
        base::update(object(E));
    }

 public: // implementation detail -- for internal use only
    BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(dict, base)
};

//
// Converter Specializations
//
namespace converter
{
  template <>
  struct object_manager_traits<dict>
      : pytype_object_manager_traits<&PyDict_Type,dict>
  {
  };
}

}}   // namespace boost::python

#endif


/* dict.hpp
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
*/