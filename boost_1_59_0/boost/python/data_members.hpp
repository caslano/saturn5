// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef DATA_MEMBERS_DWA2002328_HPP
# define DATA_MEMBERS_DWA2002328_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/handle.hpp>

# include <boost/python/return_value_policy.hpp>
# include <boost/python/return_by_value.hpp>
# include <boost/python/return_internal_reference.hpp>
# include <boost/python/make_function.hpp>

# include <boost/python/converter/builtin_converters.hpp>

# include <boost/python/detail/indirect_traits.hpp>
# include <boost/python/detail/not_specified.hpp>
# include <boost/python/detail/value_arg.hpp>
# include <boost/python/detail/type_traits.hpp>

# include <boost/mpl/eval_if.hpp>
# include <boost/mpl/if.hpp>
# include <boost/mpl/vector/vector10.hpp>

# include <boost/detail/workaround.hpp>

namespace boost { namespace python { 

//
// This file defines the make_getter and make_setter function
// families, which are responsible for turning pointers, references,
// and pointers-to-data-members into callable Python objects which
// can be used for attribute access on wrapped classes.
//

namespace detail
{

  // A small function object which handles the getting and setting of
  // data members.
  template <class Data, class Class>
  struct member
  {
   public:      
      member(Data Class::*which) : m_which(which) {}
      
      Data& operator()(Class& c) const
      {
          return c.*m_which;
      }

      void operator()(Class& c, typename value_arg<Data>::type d) const
      {
          c.*m_which = d;
      }
   private:
      Data Class::*m_which;
  };

  // A small function object which handles the getting and setting of
  // non-member objects.
  template <class Data>
  struct datum
  {
   public:      
      datum(Data *which) : m_which(which) {}
      
      Data& operator()() const
      {
          return *m_which;
      }

      void operator()(typename value_arg<Data>::type d) const
      {
          *m_which = d;
      }
   private:
      Data *m_which;
  };
  
  //
  // Helper metafunction for determining the default CallPolicy to use
  // for attribute access.  If T is a [reference to a] class type X
  // whose conversion to python would normally produce a new copy of X
  // in a wrapped X class instance (as opposed to types such as
  // std::string, which are converted to native Python types, and
  // smart pointer types which produce a wrapped class instance of the
  // pointee type), to-python conversions will attempt to produce an
  // object which refers to the original C++ object, rather than a
  // copy.  See default_member_getter_policy for rationale.
  // 
  template <class T>
  struct default_getter_by_ref
      : mpl::and_<
          mpl::bool_<
              to_python_value<
                  typename value_arg<T>::type
              >::uses_registry
          >
        , indirect_traits::is_reference_to_class<
              typename value_arg<T>::type
          >
       >
  {
  };

  // Metafunction computing the default CallPolicy to use for reading
  // data members
  //
  // If it's a regular class type (not an object manager or other
  // type for which we have to_python specializations, use
  // return_internal_reference so that we can do things like
  //    x.y.z =  1
  // and get the right result.
  template <class T>
  struct default_member_getter_policy
    : mpl::if_<
          default_getter_by_ref<T>
        , return_internal_reference<>
        , return_value_policy<return_by_value>
      >
  {};

  // Metafunction computing the default CallPolicy to use for reading
  // non-member data.
  template <class T>
  struct default_datum_getter_policy
    : mpl::if_<
          default_getter_by_ref<T>
        , return_value_policy<reference_existing_object>
        , return_value_policy<return_by_value>
      >
  {};

  //
  // make_getter helper function family -- These helpers to
  // boost::python::make_getter are used to dispatch behavior.  The
  // third argument is a workaround for a CWPro8 partial ordering bug
  // with pointers to data members.  It should be convertible to
  // detail::true_ iff the first argument is a pointer-to-member, and
  // detail::false_ otherwise.  The fourth argument is for compilers
  // which don't support partial ordering at all and should always be
  // passed 0L.


#if BOOST_WORKAROUND(__EDG_VERSION__, <= 238)
  template <class D, class P>
  inline object make_getter(D& d, P& p, detail::false_, ...);
#endif

  // Handle non-member pointers with policies
  template <class D, class Policies>
  inline object make_getter(D* d, Policies const& policies, detail::false_, int)
  {
      return python::make_function(
          detail::datum<D>(d), policies, mpl::vector1<D&>()
      );
  }
  
  // Handle non-member pointers without policies
  template <class D>
  inline object make_getter(D* d, not_specified, detail::false_, long)
  {
      typedef typename default_datum_getter_policy<D>::type policies;
      return detail::make_getter(d, policies(), detail::false_(), 0);
  }

  // Handle pointers-to-members with policies
  template <class C, class D, class Policies>
  inline object make_getter(D C::*pm, Policies const& policies, detail::true_, int)
  {
#if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
      typedef typename detail::remove_cv<C>::type Class;
#else
      typedef C Class;
#endif 
      return python::make_function(
          detail::member<D,Class>(pm)
        , policies
        , mpl::vector2<D&,Class&>()
      );
  }
      
  // Handle pointers-to-members without policies
  template <class C, class D>
  inline object make_getter(D C::*pm, not_specified, detail::true_, long)
  {
      typedef typename default_member_getter_policy<D>::type policies;
      return detail::make_getter(pm, policies(), detail::true_(), 0);
  }

  // Handle references
  template <class D, class P>
  inline object make_getter(D& d, P& p, detail::false_, ...)
  {
      // Just dispatch to the handler for pointer types.
      return detail::make_getter(&d, p, detail::false_(), 0L);
  }

  //
  // make_setter helper function family -- These helpers to
  // boost::python::make_setter are used to dispatch behavior.  The
  // third argument is for compilers which don't support partial
  // ordering at all and should always be passed 0.
  //

  
  // Handle non-member pointers
  template <class D, class Policies>
  inline object make_setter(D* p, Policies const& policies, detail::false_, int)
  {
      return python::make_function(
          detail::datum<D>(p), policies, mpl::vector2<void,D const&>()
      );
  }

  // Handle pointers-to-members
  template <class C, class D, class Policies>
  inline object make_setter(D C::*pm, Policies const& policies, detail::true_, int)
  {
      return python::make_function(
          detail::member<D,C>(pm)
        , policies
        , mpl::vector3<void, C&, D const&>()
      );
  }

  // Handle references
  template <class D, class Policies>
  inline object make_setter(D& x, Policies const& policies, detail::false_, ...)
  {
      return detail::make_setter(&x, policies, detail::false_(), 0L);
  }
}

//
// make_getter function family -- build a callable object which
// retrieves data through the first argument and is appropriate for
// use as the `get' function in Python properties .  The second,
// policies argument, is optional.  We need both D& and D const&
// overloads in order be able to handle rvalues.
//
template <class D, class Policies>
inline object make_getter(D& d, Policies const& policies)
{
    return detail::make_getter(d, policies, detail::is_member_pointer<D>(), 0L);
}

template <class D, class Policies>
inline object make_getter(D const& d, Policies const& policies)
{
    return detail::make_getter(d, policies, detail::is_member_pointer<D>(), 0L);
}

template <class D>
inline object make_getter(D& x)
{
    detail::not_specified policy
        = detail::not_specified(); // suppress a SunPro warning
    return detail::make_getter(x, policy, detail::is_member_pointer<D>(), 0L);
}

#  if !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)
template <class D>
inline object make_getter(D const& d)
{
    detail::not_specified policy
        = detail::not_specified(); // Suppress a SunPro warning
    return detail::make_getter(d, policy, detail::is_member_pointer<D>(), 0L);
}
#  endif

//
// make_setter function family -- build a callable object which
// writes data through the first argument and is appropriate for
// use as the `set' function in Python properties .  The second,
// policies argument, is optional.  We need both D& and D const&
// overloads in order be able to handle rvalues.
//
template <class D, class Policies>
inline object make_setter(D& x, Policies const& policies)
{
    return detail::make_setter(x, policies, detail::is_member_pointer<D>(), 0);
}

template <class D, class Policies>
inline object make_setter(D const& x, Policies const& policies)
{
    return detail::make_setter(x, policies, detail::is_member_pointer<D>(), 0);
}

template <class D>
inline object make_setter(D& x)
{
    return detail::make_setter(x, default_call_policies(), detail::is_member_pointer<D>(), 0);
}

# if !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)
template <class D>
inline object make_setter(D const& x)
{
    return detail::make_setter(x, default_call_policies(), detail::is_member_pointer<D>(), 0);
}
# endif

}} // namespace boost::python

#endif // DATA_MEMBERS_DWA2002328_HPP

/* data_members.hpp
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
*/