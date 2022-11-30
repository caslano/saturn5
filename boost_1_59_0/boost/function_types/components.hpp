
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

#if BOOST_WORKAROUND(BOOST_BORLANDC, <= 0x565)
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
#if BOOST_WORKAROUND(BOOST_BORLANDC, <= 0x565)
      template<typename T, typename OrigT, typename L> struct components_bcc;
#endif
    }

    template<typename T, typename ClassTypeTransform> 
    struct components
#if !BOOST_WORKAROUND(BOOST_BORLANDC, <= 0x565)
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

#if !BOOST_WORKAROUND(BOOST_BORLANDC, <= 0x565)
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