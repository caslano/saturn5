// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef DEF_HELPER_DWA200287_HPP
# define DEF_HELPER_DWA200287_HPP

# include <boost/python/args.hpp>
# include <boost/python/detail/indirect_traits.hpp>
# include <boost/python/detail/type_traits.hpp>
# include <boost/mpl/not.hpp>
# include <boost/mpl/and.hpp>
# include <boost/mpl/or.hpp>
# include <boost/mpl/lambda.hpp>
# include <boost/mpl/apply.hpp>
# include <boost/tuple/tuple.hpp>
# include <boost/python/detail/not_specified.hpp>
# include <boost/python/detail/def_helper_fwd.hpp>

namespace boost { namespace python {

struct default_call_policies;

namespace detail
{
  // tuple_extract<Tuple,Predicate>::extract(t) returns the first
  // element of a Tuple whose type E satisfies the given Predicate
  // applied to add_reference<E>. The Predicate must be an MPL
  // metafunction class.
  template <class Tuple, class Predicate>
  struct tuple_extract;

  // Implementation class for when the tuple's head type does not
  // satisfy the Predicate
  template <bool matched>
  struct tuple_extract_impl
  {
      template <class Tuple, class Predicate>
      struct apply
      {
          typedef typename Tuple::head_type result_type;
          
          static typename Tuple::head_type extract(Tuple const& x)
          {
              return x.get_head();
          }
      };
  };

  // Implementation specialization for when the tuple's head type
  // satisfies the predicate
  template <>
  struct tuple_extract_impl<false>
  {
      template <class Tuple, class Predicate>
      struct apply
      {
          // recursive application of tuple_extract on the tail of the tuple
          typedef tuple_extract<typename Tuple::tail_type, Predicate> next;
          typedef typename next::result_type result_type;
          
          static result_type extract(Tuple const& x)
          {
              return next::extract(x.get_tail());
          }
      };
  };

  // A metafunction which selects a version of tuple_extract_impl to
  // use for the implementation of tuple_extract
  template <class Tuple, class Predicate>
  struct tuple_extract_base_select
  {
      typedef typename Tuple::head_type head_type;
      typedef typename mpl::apply1<Predicate,
              typename add_lvalue_reference<head_type>::type>::type match_t;
      BOOST_STATIC_CONSTANT(bool, match = match_t::value);
      typedef typename tuple_extract_impl<match>::template apply<Tuple,Predicate> type;
  };
  
  template <class Tuple, class Predicate>
  struct tuple_extract
      : tuple_extract_base_select<
         Tuple
         , typename mpl::lambda<Predicate>::type
      >::type
  {
  };


  //
  // Specialized extractors for the docstring, keywords, CallPolicies,
  // and default implementation of virtual functions
  //

  template <class Tuple>
  struct doc_extract
      : tuple_extract<
        Tuple
        , mpl::not_<
           mpl::or_<
               indirect_traits::is_reference_to_class<mpl::_1>
             , indirect_traits::is_reference_to_member_function_pointer<mpl::_1 >
           >
        >
     >
  {
  };
  
  template <class Tuple>
  struct keyword_extract
      : tuple_extract<Tuple, is_reference_to_keywords<mpl::_1 > >
  {
  };

  template <class Tuple>
  struct policy_extract
      : tuple_extract<
          Tuple
          , mpl::and_<
             mpl::not_<is_same<not_specified const&,mpl::_1> >
              , indirect_traits::is_reference_to_class<mpl::_1 >
              , mpl::not_<is_reference_to_keywords<mpl::_1 > >
          >
        >
  {
  };

  template <class Tuple>
  struct default_implementation_extract
      : tuple_extract<
          Tuple
          , indirect_traits::is_reference_to_member_function_pointer<mpl::_1 >
          >
  {
  };

  //
  // A helper class for decoding the optional arguments to def()
  // invocations, which can be supplied in any order and are
  // discriminated by their type properties. The template parameters
  // are expected to be the types of the actual (optional) arguments
  // passed to def().
  //
  template <class T1, class T2, class T3, class T4>
  struct def_helper
  {
      // A tuple type which begins with references to the supplied
      // arguments and ends with actual representatives of the default
      // types.
      typedef boost::tuples::tuple<
          T1 const&
          , T2 const&
          , T3 const&
          , T4 const&
          , default_call_policies
          , detail::keywords<0>
          , char const*
          , void(not_specified::*)()   // A function pointer type which is never an
                                       // appropriate default implementation
          > all_t;

      // Constructors; these initialize an member of the tuple type
      // shown above.
      def_helper(T1 const& a1) : m_all(a1,m_nil,m_nil,m_nil) {}
      def_helper(T1 const& a1, T2 const& a2) : m_all(a1,a2,m_nil,m_nil) {}
      def_helper(T1 const& a1, T2 const& a2, T3 const& a3) : m_all(a1,a2,a3,m_nil) {}
      def_helper(T1 const& a1, T2 const& a2, T3 const& a3, T4 const& a4) : m_all(a1,a2,a3,a4) {}

   private: // types
      typedef typename default_implementation_extract<all_t>::result_type default_implementation_t;
      
   public: // Constants which can be used for static assertions.

      // Users must not supply a default implementation for non-class
      // methods.
      BOOST_STATIC_CONSTANT(
          bool, has_default_implementation = (
              !is_same<default_implementation_t, void(not_specified::*)()>::value));
      
   public: // Extractor functions which pull the appropriate value out
           // of the tuple
      char const* doc() const
      {
          return doc_extract<all_t>::extract(m_all);
      }
      
      typename keyword_extract<all_t>::result_type keywords() const
      {
          return keyword_extract<all_t>::extract(m_all);
      }
      
      typename policy_extract<all_t>::result_type policies() const
      {
          return policy_extract<all_t>::extract(m_all);
      }

      default_implementation_t default_implementation() const
      {
          return default_implementation_extract<all_t>::extract(m_all);
      }
      
   private: // data members
      all_t m_all; 
      not_specified m_nil; // for filling in not_specified slots
  };
}

}} // namespace boost::python::detail

#endif // DEF_HELPER_DWA200287_HPP

/* def_helper.hpp
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
*/