// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef STR_20020703_HPP
#define STR_20020703_HPP

# include <boost/python/detail/prefix.hpp>

#include <boost/python/object.hpp>
#include <boost/python/list.hpp>
#include <boost/python/converter/pytype_object_mgr_traits.hpp>

// disable defines in <cctype> provided by some system libraries
#undef isspace
#undef islower
#undef isalpha
#undef isdigit
#undef isalnum
#undef isupper

namespace boost { namespace python {

class str;

namespace detail
{
  struct BOOST_PYTHON_DECL str_base : object
  {
      str capitalize() const;

      str center(object_cref width) const;

      long count(object_cref sub) const;

      long count(object_cref sub, object_cref start) const;
    
      long count(object_cref sub, object_cref start, object_cref end) const;

#if PY_VERSION_HEX < 0x03000000
      object decode() const;
      object decode(object_cref encoding) const;

      object decode(object_cref encoding, object_cref errors) const;
#endif

      object encode() const;
      object encode(object_cref encoding) const;
      object encode(object_cref encoding, object_cref errors) const;

      bool endswith(object_cref suffix) const;
    
      bool endswith(object_cref suffix, object_cref start) const;
      bool endswith(object_cref suffix, object_cref start, object_cref end) const;
    
      str expandtabs() const;
      str expandtabs(object_cref tabsize) const;

      long find(object_cref sub) const;
      long find(object_cref sub, object_cref start) const;

      long find(object_cref sub, object_cref start, object_cref end) const;

      long index(object_cref sub) const;

      long index(object_cref sub, object_cref start) const;
      long index(object_cref sub, object_cref start, object_cref end) const;

      bool isalnum() const;
      bool isalpha() const;
      bool isdigit() const;
      bool islower() const;
      bool isspace() const;
      bool istitle() const;
      bool isupper() const;
    
      str join(object_cref sequence) const;

      str ljust(object_cref width) const;
      str lower() const;
      str lstrip() const;

      str replace(object_cref old, object_cref new_) const;
      str replace(object_cref old, object_cref new_, object_cref maxsplit) const;
      long rfind(object_cref sub) const;

      long rfind(object_cref sub, object_cref start) const;

      long rfind(object_cref sub, object_cref start, object_cref end) const;
      long rindex(object_cref sub) const;
      long rindex(object_cref sub, object_cref start) const;


      long rindex(object_cref sub, object_cref start, object_cref end) const;

      str rjust(object_cref width) const;
    
      str rstrip() const;
    
      list split() const; 
      list split(object_cref sep) const;
   
      list split(object_cref sep, object_cref maxsplit) const; 
    

      list splitlines() const;
      list splitlines(object_cref keepends) const;

      bool startswith(object_cref prefix) const;


      bool startswith(object_cref prefix, object_cref start) const;
      bool startswith(object_cref prefix, object_cref start, object_cref end) const;

      str strip() const;
      str swapcase() const;
      str title() const;
    
      str translate(object_cref table) const;

      str translate(object_cref table, object_cref deletechars) const;

    
      str upper() const;

   protected:
      str_base(); // new str
    
      str_base(const char* s); // new str

      str_base(char const* start, char const* finish);
      
      str_base(char const* start, std::size_t length);
      
      explicit str_base(object_cref other);

      BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(str_base, object)
   private:
      static new_reference call(object const&);
  };
}


class str : public detail::str_base
{
    typedef detail::str_base base;
 public:
    str() {} // new str
    
    str(const char* s) : base(s) {} // new str
    
    str(char const* start, char const* finish) // new str
      : base(start, finish)
    {}
    
    str(char const* start, std::size_t length) // new str
      : base(start, length)
    {}
    
    template <class T>
    explicit str(T const& other)
        : base(object(other))
    {
    }

    template <class T>
    str center(T const& width) const
    {
        return base::center(object(width));
    }

    template<class T>
    long count(T const& sub) const
    {
        return base::count(object(sub));
    }

    template<class T1, class T2>
    long count(T1 const& sub,T2 const& start) const
    {
        return base::count(object(sub), object(start));
    }

    template<class T1, class T2, class T3>
    long count(T1 const& sub,T2 const& start, T3 const& end) const
    {
        return base::count(object(sub), object(start), object(end));
    }

#if PY_VERSION_HEX < 0x03000000
    object decode() const { return base::decode(); }
    
    template<class T>
    object decode(T const& encoding) const
    {
        return base::decode(object(encoding));
    }

    template<class T1, class T2>
    object decode(T1 const& encoding, T2 const& errors) const
    {
        return base::decode(object(encoding),object(errors));
    }
#endif

    object encode() const { return base::encode(); }

    template <class T>
    object encode(T const& encoding) const
    {
        return base::encode(object(encoding));
    }

    template <class T1, class T2>
    object encode(T1 const& encoding, T2 const& errors) const
    {
        return base::encode(object(encoding),object(errors));
    }

    template <class T>
    bool endswith(T const& suffix) const
    {
        return base::endswith(object(suffix));
    }

    template <class T1, class T2>
    bool endswith(T1 const& suffix, T2 const& start) const
    {
        return base::endswith(object(suffix), object(start));
    }

    template <class T1, class T2, class T3>
    bool endswith(T1 const& suffix, T2 const& start, T3 const& end) const
    {
        return base::endswith(object(suffix), object(start), object(end));
    }
    
    str expandtabs() const { return base::expandtabs(); }

    template <class T>
    str expandtabs(T const& tabsize) const
    {
        return base::expandtabs(object(tabsize));
    }
    
    template <class T>
    long find(T const& sub) const
    {
        return base::find(object(sub));
    }

    template <class T1, class T2>
    long find(T1 const& sub, T2 const& start) const
    {
        return base::find(object(sub), object(start));
    }

    template <class T1, class T2, class T3>
    long find(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return base::find(object(sub), object(start), object(end));
    }
    
    template <class T>
    long index(T const& sub) const
    {
        return base::index(object(sub));
    }
    
    template <class T1, class T2>
    long index(T1 const& sub, T2 const& start) const
    {
        return base::index(object(sub), object(start));
    }

    template <class T1, class T2, class T3>
    long index(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return base::index(object(sub), object(start), object(end));
    }

    template <class T>
    str join(T const& sequence) const
    {
        return base::join(object(sequence));
    }
    
    template <class T>
    str ljust(T const& width) const
    {
        return base::ljust(object(width));
    }

    template <class T1, class T2>
    str replace(T1 const& old, T2 const& new_) const 
    {
        return base::replace(object(old),object(new_));
    }

    template <class T1, class T2, class T3>
    str replace(T1 const& old, T2 const& new_, T3 const& maxsplit) const 
    {
        return base::replace(object(old),object(new_), object(maxsplit));
    }
    
    template <class T>
    long rfind(T const& sub) const
    {
        return base::rfind(object(sub));
    }

    template <class T1, class T2>
    long rfind(T1 const& sub, T2 const& start) const
    {
        return base::rfind(object(sub), object(start));
    }
    
    template <class T1, class T2, class T3>
    long rfind(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return base::rfind(object(sub), object(start), object(end));
    }
    
    template <class T>
    long rindex(T const& sub) const
    {
        return base::rindex(object(sub));
    }

    template <class T1, class T2>
    long rindex(T1 const& sub, T2 const& start) const
    {
        return base::rindex(object(sub), object(start));
    }

    template <class T1, class T2, class T3>
    long rindex(T1 const& sub, T2 const& start, T3 const& end) const
    {
        return base::rindex(object(sub), object(start), object(end));
    }

    template <class T>
    str rjust(T const& width) const
    {
        return base::rjust(object(width));
    }
    
    list split() const { return base::split(); }
   
    template <class T>
    list split(T const& sep) const
    {
        return base::split(object(sep));
    }

    template <class T1, class T2>
    list split(T1 const& sep, T2 const& maxsplit) const
    {
        return base::split(object(sep), object(maxsplit));
    }

    list splitlines() const { return base::splitlines(); }

    template <class T>
    list splitlines(T const& keepends) const
    {
        return base::splitlines(object(keepends));
    }

    template <class T>
    bool startswith(T const& prefix) const
    {
        return base::startswith(object(prefix));
    }

    template <class T1, class T2>
    bool startswith(T1 const& prefix, T2 const& start) const
    {
        return base::startswith(object(prefix), object(start));
    }
     
    template <class T1, class T2, class T3>
    bool startswith(T1 const& prefix, T2 const& start, T3 const& end) const
    {
        return base::startswith(object(prefix), object(start), object(end));
    }

    template <class T>
    str translate(T const& table) const
    {
        return base::translate(object(table));
    }

    template <class T1, class T2>
    str translate(T1 const& table, T2 const& deletechars) const
    {
        return base::translate(object(table), object(deletechars));
    }
    
 public: // implementation detail -- for internal use only
    BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(str, base)
};

//
// Converter Specializations
//
namespace converter
{
  template <>
  struct object_manager_traits<str>
#if PY_VERSION_HEX >= 0x03000000
      : pytype_object_manager_traits<&PyUnicode_Type,str>
#else
      : pytype_object_manager_traits<&PyString_Type,str>
#endif
  {
  };
}

}}  // namespace boost::python

#endif // STR_20020703_HPP

/* str.hpp
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
*/