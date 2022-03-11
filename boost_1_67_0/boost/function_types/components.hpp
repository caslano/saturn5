
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_COMPONENTS_HPP_INCLUDED
#define BOOST_FT_COMPONENTS_HPP_INCLUDED

#include <cstddef>

#include <boost/config.hpp>

#include <boost/detail/workaround.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/type_traits/integral_constant.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/vector/vector0.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, <= 0x565)
#   include <boost/type_traits/remove_cv.hpp>

#   include <boost/mpl/identity.hpp>
#   include <boost/mpl/bitand.hpp>
#   include <boost/mpl/vector/vector10.hpp>
#   include <boost/mpl/front.hpp>
#   include <boost/mpl/begin.hpp>
#   include <boost/mpl/advance.hpp>
#   include <boost/mpl/iterator_range.hpp>
#   include <boost/mpl/joint_view.hpp>
#   include <boost/mpl/equal_to.hpp>
#   include <boost/mpl/copy.hpp>
#   include <boost/mpl/front_inserter.hpp>

#   include <boost/function_types/detail/classifier.hpp>
#endif

#ifndef BOOST_FT_NO_CV_FUNC_SUPPORT
#   include <boost/mpl/remove.hpp>
#endif

#include <boost/function_types/config/config.hpp>

#   if   BOOST_FT_MAX_ARITY < 10
#     include <boost/mpl/vector/vector10.hpp>
#   elif BOOST_FT_MAX_ARITY < 20
#     include <boost/mpl/vector/vector20.hpp>
#   elif BOOST_FT_MAX_ARITY < 30
#     include <boost/mpl/vector/vector30.hpp>
#   elif BOOST_FT_MAX_ARITY < 40
#     include <boost/mpl/vector/vector40.hpp>
#   elif BOOST_FT_MAX_ARITY < 50
#     include <boost/mpl/vector/vector50.hpp>
#   endif

#include <boost/function_types/detail/class_transform.hpp>
#include <boost/function_types/property_tags.hpp>

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace boost 
{ 
  namespace function_types 
  {

    using mpl::placeholders::_;

    template< typename T, typename ClassTypeTransform = add_reference<_> > 
    struct components;

    namespace detail 
    {
      template<typename T, typename L> struct components_impl;
#if BOOST_WORKAROUND(__BORLANDC__, <= 0x565)
      template<typename T, typename OrigT, typename L> struct components_bcc;
#endif
    }

    template<typename T, typename ClassTypeTransform> 
    struct components
#if !BOOST_WORKAROUND(__BORLANDC__, <= 0x565)
      : detail::components_impl<T, ClassTypeTransform>
#else
      : detail::components_bcc<typename remove_cv<T>::type,T,
            ClassTypeTransform>
#endif
    { 
      typedef components<T,ClassTypeTransform> type;

      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,components,(T,ClassTypeTransform))
    };

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  namespace detail {

    struct components_mpl_sequence_tag; 

    struct components_non_func_base
    {
      typedef mpl::vector0<> types;
      typedef void function_arity;

      typedef detail::constant<0> bits;
      typedef detail::constant<0> mask;

      typedef components_mpl_sequence_tag tag;
    };

    template
    < typename Components
    , typename IfTagged
    , typename ThenTag
    , typename DefaultBase = components_non_func_base
    >
    struct retagged_if
      : mpl::if_
        < detail::represents_impl<Components, IfTagged>
        , detail::changed_tag<Components,IfTagged,ThenTag>
        , DefaultBase
        >::type
    { };

    // We detect plain function types and function references as function 
    // pointers by recursive instantiation of components_impl. 
    // The third specialization of components_impl makes sure the recursion 
    // terminates (when adding pointers).
    template<typename T, typename L>
    struct components_impl
      : detail::retagged_if
        < detail::components_impl<T*,L>
        , pointer_tag, /* --> */ function_tag >
    { };
    template<typename T, typename L>
    struct components_impl<T&, L>
      : detail::retagged_if
        < detail::components_impl<T*,L>
        , pointer_tag, /* --> */ reference_tag >
    { };

#if !BOOST_FT_NO_CV_FUNC_SUPPORT
    // Retry the type with a member pointer attached to detect cv functions
    class a_class;

    template<typename Base, typename T, typename L>
    struct cv_func_base
      : detail::retagged_if<Base,member_pointer_tag,function_tag>
    {
      typedef typename
        mpl::remove
          < typename Base::types
          , typename detail::class_transform<a_class,L>::type>::type
      types;
    };

    template<typename T, typename L>
    struct components_impl<T*, L>
      : mpl::if_
        < detail::represents_impl< detail::components_impl<T a_class::*, L>
                                 , member_pointer_tag >
        , detail::cv_func_base< detail::components_impl<T a_class::*, L>, T, L>
        , components_non_func_base
        >::type
    { };

    template<typename T, typename L>
    struct components_impl<T a_class::*, L>
      : components_non_func_base
    { };
#else
    template<typename T, typename L>
    struct components_impl<T*, L>
      : components_non_func_base
    { }; 
#endif

    template<typename T, typename L>
    struct components_impl<T* const, L> 
      : components_impl<T*,L>
    { };

    template<typename T, typename L>
    struct components_impl<T* volatile, L> 
      : components_impl<T*,L>
    { };

    template<typename T, typename L>
    struct components_impl<T* const volatile, L> 
      : components_impl<T*,L>
    { };

    template<typename T, typename L>
    struct components_impl<T const, L> 
      : components_impl<T,L>
    { };

    template<typename T, typename L>
    struct components_impl<T volatile, L> 
      : components_impl<T,L>
    { };

    template<typename T, typename L>
    struct components_impl<T const volatile, L> 
      : components_impl<T,L>
    { };


    template<typename T, class C>
    struct member_obj_ptr_result
    { typedef T & type; };

    template<typename T, class C>
    struct member_obj_ptr_result<T, C const>
    { typedef T const & type; };

    template<typename T, class C>
    struct member_obj_ptr_result<T, C volatile>
    { typedef T volatile & type; };

    template<typename T, class C>
    struct member_obj_ptr_result<T, C const volatile>
    { typedef T const volatile & type; };

    template<typename T, class C>
    struct member_obj_ptr_result<T &, C>
    { typedef T & type; };

    template<typename T, class C>
    struct member_obj_ptr_result<T &, C const>
    { typedef T & type; };

    template<typename T, class C>
    struct member_obj_ptr_result<T &, C volatile>
    { typedef T & type; };

    template<typename T, class C>
    struct member_obj_ptr_result<T &, C const volatile>
    { typedef T & type; };

    template<typename T, class C, typename L>
    struct member_obj_ptr_components
      : member_object_pointer_base
    {
      typedef function_types::components<T C::*, L> type;
      typedef components_mpl_sequence_tag tag;

      typedef mpl::integral_c<std::size_t,1> function_arity;

      typedef mpl::vector2< typename detail::member_obj_ptr_result<T,C>::type,
          typename detail::class_transform<C,L>::type > types;
    };

#if !BOOST_WORKAROUND(__BORLANDC__, <= 0x565)
#   define BOOST_FT_variations BOOST_FT_pointer|BOOST_FT_member_pointer

    template<typename T, class C, typename L>
    struct components_impl<T C::*, L>
      : member_obj_ptr_components<T,C,L>
    { };

#else  
#   define BOOST_FT_variations BOOST_FT_pointer

    // This workaround removes the member pointer from the type to allow 
    // detection of member function pointers with BCC. 
    template<typename T, typename C, typename L>
    struct components_impl<T C::*, L>
      : detail::retagged_if
        < detail::components_impl<typename boost::remove_cv<T>::type *, L>
        , pointer_tag, /* --> */ member_function_pointer_tag
        , member_obj_ptr_components<T,C,L> >
    { };

    // BCC lets us test the cv-qualification of a function type by template 
    // partial specialization - so we use this bug feature to find out the 
    // member function's cv-qualification (unfortunately there are some 
    // invisible modifiers that impose some limitations on these types even if
    // we remove the qualifiers, So we cannot exploit the same bug to make the 
    // library work for cv-qualified function types).
    template<typename T> struct encode_cv
    { typedef char (& type)[1]; BOOST_STATIC_CONSTANT(std::size_t, value = 1); };
    template<typename T> struct encode_cv<T const *>
    { typedef char (& type)[2]; BOOST_STATIC_CONSTANT(std::size_t, value = 2); };
    template<typename T> struct encode_cv<T volatile *>
    { typedef char (& type)[3]; BOOST_STATIC_CONSTANT(std::size_t, value = 3); };
    template<typename T> struct encode_cv<T const volatile *> 
    { typedef char (& type)[4]; BOOST_STATIC_CONSTANT(std::size_t, value = 4); };

    // For member function pointers we have to use a function template (partial
    // template specialization for a member pointer drops the cv qualification 
    // of the function type).
    template<typename T, typename C>
    typename encode_cv<T *>::type mfp_cv_tester(T C::*);

    template<typename T> struct encode_mfp_cv
    { 
      BOOST_STATIC_CONSTANT(std::size_t, value = 
          sizeof(detail::mfp_cv_tester((T)0L))); 
    };

    // Associate bits with the CV codes above.
    template<std::size_t> struct cv_tag_mfp_impl;

    template<typename T> struct cv_tag_mfp
      : detail::cv_tag_mfp_impl
        < ::boost::function_types::detail::encode_mfp_cv<T>::value >
    { };

    template<> struct cv_tag_mfp_impl<1> : non_cv              { };
    template<> struct cv_tag_mfp_impl<2> : const_non_volatile  { };
    template<> struct cv_tag_mfp_impl<3> : volatile_non_const  { };
    template<> struct cv_tag_mfp_impl<4> : cv_qualified        { };

    // Metafunction to decode the cv code and apply it to a type.
    // We add a pointer, because otherwise cv-qualifiers won't stick (another bug).
    template<typename T, std::size_t CV> struct decode_cv;

    template<typename T> struct decode_cv<T,1> : mpl::identity<T *>          {};
    template<typename T> struct decode_cv<T,2> : mpl::identity<T const *>    {};
    template<typename T> struct decode_cv<T,3> : mpl::identity<T volatile *> {};
    template<typename T> struct decode_cv<T,4> 
                                         : mpl::identity<T const volatile *> {};

    // The class type transformation comes after adding cv-qualifiers. We have
    // wrap it to remove the pointer added in decode_cv_impl.
    template<typename T, typename L> struct bcc_class_transform_impl;
    template<typename T, typename L> struct bcc_class_transform_impl<T *, L>
      : class_transform<T,L> 
    { };

    template<typename T, typename D, typename L> struct bcc_class_transform 
      : bcc_class_transform_impl
        < typename decode_cv
          < T
          , ::boost::function_types::detail::encode_mfp_cv<D>::value 
          >::type
        , L
        > 
    { };

    // After extracting the member pointee from the type the class type is still
    // in the type (somewhere -- you won't see with RTTI, that is) and that type
    // is flagged unusable and *not* identical to the nonmember function type.
    // We can, however, decompose this type via components_impl but surprisingly
    // a pointer to the const qualified class type pops up again as the first 
    // parameter type. 
    // We have to replace this type with the properly cv-qualified and 
    // transformed class type, integrate the cv qualification into the bits.
    template<typename Base, typename MFP, typename OrigT, typename L>
    struct mfp_components;


    template<typename Base, typename T, typename C, typename OrigT, typename L>
    struct mfp_components<Base,T C::*,OrigT,L> 
    {
    private:
      typedef typename mpl::front<typename Base::types>::type result_type;
      typedef typename detail::bcc_class_transform<C,OrigT,L>::type class_type;

      typedef mpl::vector2<result_type, class_type> result_and_class_type;

      typedef typename 
        mpl::advance
        < typename mpl::begin<typename Base::types>::type
        , typename mpl::if_
          < mpl::equal_to< typename detail::classifier<OrigT>::function_arity
                         , typename Base::function_arity >
          , mpl::integral_c<int,2> , mpl::integral_c<int,1> 
          >::type
        >::type
      from;
      typedef typename mpl::end<typename Base::types>::type to;

      typedef mpl::iterator_range<from,to> param_types;

      typedef mpl::joint_view< result_and_class_type, param_types> types_view;
    public:

      typedef typename 
        mpl::reverse_copy<types_view, mpl::front_inserter< mpl::vector0<> > >::type 
      types;

      typedef typename 
        function_types::tag< Base, detail::cv_tag_mfp<OrigT> >::bits 
      bits;

      typedef typename Base::mask mask;

      typedef typename detail::classifier<OrigT>::function_arity function_arity;

      typedef components_mpl_sequence_tag tag;
    };

    // Now put it all together: detect cv-qualification of function types and do
    // the weird transformations above for member function pointers.
    template<typename T, typename OrigT, typename L>
    struct components_bcc
      : mpl::if_
        < detail::represents_impl< detail::components_impl<T,L>
                                 , member_function_pointer_tag>
        , detail::mfp_components<detail::components_impl<T,L>,T,OrigT,L>
        , detail::components_impl<T,L>
        >::type
    { };

#endif // end of BORLAND WORKAROUND

#define BOOST_FT_al_path boost/function_types/detail/components_impl
#include <boost/function_types/detail/pp_loop.hpp>

  } } // namespace function_types::detail

} // namespace ::boost

#include <boost/function_types/detail/components_as_mpl_sequence.hpp>
#include <boost/function_types/detail/retag_default_cc.hpp>

#endif


/* components.hpp
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
*/