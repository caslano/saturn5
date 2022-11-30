// Copyright David Abrahams 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef PURE_VIRTUAL_DWA2003810_HPP
# define PURE_VIRTUAL_DWA2003810_HPP

# include <boost/python/def_visitor.hpp>
# include <boost/python/default_call_policies.hpp>
# include <boost/mpl/push_front.hpp>
# include <boost/mpl/pop_front.hpp>

# include <boost/python/detail/nullary_function_adaptor.hpp>

namespace boost { namespace python { 

namespace detail
{
  //
  // @group Helpers for pure_virtual_visitor. {
  //
  
  // Raises a Python RuntimeError reporting that a pure virtual
  // function was called.
  void BOOST_PYTHON_DECL pure_virtual_called();

  // Replace the two front elements of S with T1 and T2
  template <class S, class T1, class T2>
  struct replace_front2
  {
      // Metafunction forwarding seemed to confound vc6 
      typedef typename mpl::push_front<
          typename mpl::push_front<
              typename mpl::pop_front<
                  typename mpl::pop_front<
                      S
                  >::type
              >::type
            , T2
          >::type
        , T1
      >::type type;
  };

  // Given an MPL sequence representing a member function [object]
  // signature, returns a new MPL sequence whose return type is
  // replaced by void, and whose first argument is replaced by C&.
  template <class C, class S>
  typename replace_front2<S,void,C&>::type
  error_signature(S)
  {
      typedef typename replace_front2<S,void,C&>::type r;
      return r();
  }

  //
  // } 
  //

  //
  // A def_visitor which defines a method as usual, then adds a
  // corresponding function which raises a "pure virtual called"
  // exception unless it's been overridden.
  //
  template <class PointerToMemberFunction>
  struct pure_virtual_visitor
    : def_visitor<pure_virtual_visitor<PointerToMemberFunction> >
  {
      pure_virtual_visitor(PointerToMemberFunction pmf)
        : m_pmf(pmf)
      {}
      
   private:
      friend class python::def_visitor_access;
      
      template <class C_, class Options>
      void visit(C_& c, char const* name, Options& options) const
      {
          // This should probably be a nicer error message
          BOOST_STATIC_ASSERT(!Options::has_default_implementation);

          // Add the virtual function dispatcher
          c.def(
              name
            , m_pmf
            , options.doc()
            , options.keywords()
            , options.policies()
          );

          typedef BOOST_DEDUCED_TYPENAME C_::metadata::held_type held_type;
          
          // Add the default implementation which raises the exception
          c.def(
              name
            , make_function(
                  detail::nullary_function_adaptor<void(*)()>(pure_virtual_called)
                , default_call_policies()
                , detail::error_signature<held_type>(detail::get_signature(m_pmf))
              )
          );
      }
      
   private: // data members
      PointerToMemberFunction m_pmf;
  };
}

//
// Passed a pointer to member function, generates a def_visitor which
// creates a method that only dispatches to Python if the function has
// been overridden, either in C++ or in Python, raising a "pure
// virtual called" exception otherwise.
//
template <class PointerToMemberFunction>
detail::pure_virtual_visitor<PointerToMemberFunction>
pure_virtual(PointerToMemberFunction pmf)
{
    return detail::pure_virtual_visitor<PointerToMemberFunction>(pmf);
}

}} // namespace boost::python

#endif // PURE_VIRTUAL_DWA2003810_HPP

/* pure_virtual.hpp
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
*/