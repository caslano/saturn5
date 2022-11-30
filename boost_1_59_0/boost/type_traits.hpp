//  (C) Copyright John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

//  See boost/type_traits/*.hpp for full copyright notices.

#ifndef BOOST_TYPE_TRAITS_HPP
#define BOOST_TYPE_TRAITS_HPP

#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_cv.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_rvalue_reference.hpp>
#include <boost/type_traits/add_volatile.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/conjunction.hpp>
#include <boost/type_traits/copy_cv.hpp>
#include <boost/type_traits/copy_cv_ref.hpp>
#include <boost/type_traits/copy_reference.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/declval.hpp>
#include <boost/type_traits/disjunction.hpp>
#include <boost/type_traits/enable_if.hpp>
#include <boost/type_traits/extent.hpp>
#include <boost/type_traits/floating_point_promotion.hpp>
#include <boost/type_traits/function_traits.hpp>

#include <boost/type_traits/has_bit_and.hpp>
#include <boost/type_traits/has_bit_and_assign.hpp>
#include <boost/type_traits/has_bit_or.hpp>
#include <boost/type_traits/has_bit_or_assign.hpp>
#include <boost/type_traits/has_bit_xor.hpp>
#include <boost/type_traits/has_bit_xor_assign.hpp>
#include <boost/type_traits/has_complement.hpp>
#include <boost/type_traits/has_dereference.hpp>
#include <boost/type_traits/has_divides.hpp>
#include <boost/type_traits/has_divides_assign.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/type_traits/has_greater.hpp>
#include <boost/type_traits/has_greater_equal.hpp>
#include <boost/type_traits/has_left_shift.hpp>
#include <boost/type_traits/has_left_shift_assign.hpp>
#include <boost/type_traits/has_less.hpp>
#include <boost/type_traits/has_less_equal.hpp>
#include <boost/type_traits/has_logical_and.hpp>
#include <boost/type_traits/has_logical_not.hpp>
#include <boost/type_traits/has_logical_or.hpp>
#include <boost/type_traits/has_minus.hpp>
#include <boost/type_traits/has_minus_assign.hpp>
#include <boost/type_traits/has_modulus.hpp>
#include <boost/type_traits/has_modulus_assign.hpp>
#include <boost/type_traits/has_multiplies.hpp>
#include <boost/type_traits/has_multiplies_assign.hpp>
#include <boost/type_traits/has_negate.hpp>
#if !defined(BOOST_BORLANDC) && (!(defined(__CUDACC__) && (__CUDACC_VER_MAJOR__ < 11)) || defined(__CUDA__))
#include <boost/type_traits/has_new_operator.hpp>
#endif
#include <boost/type_traits/has_not_equal_to.hpp>
#include <boost/type_traits/has_nothrow_assign.hpp>
#include <boost/type_traits/has_nothrow_constructor.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>
#include <boost/type_traits/has_nothrow_destructor.hpp>
#include <boost/type_traits/has_plus.hpp>
#include <boost/type_traits/has_plus_assign.hpp>
#include <boost/type_traits/has_post_decrement.hpp>
#include <boost/type_traits/has_post_increment.hpp>
#include <boost/type_traits/has_pre_decrement.hpp>
#include <boost/type_traits/has_pre_increment.hpp>
#include <boost/type_traits/has_right_shift.hpp>
#include <boost/type_traits/has_right_shift_assign.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/type_traits/has_trivial_move_assign.hpp>
#include <boost/type_traits/has_trivial_move_constructor.hpp>
#include <boost/type_traits/has_unary_minus.hpp>
#include <boost/type_traits/has_unary_plus.hpp>
#include <boost/type_traits/has_virtual_destructor.hpp>

#include <boost/type_traits/integral_constant.hpp>

#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_assignable.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_complex.hpp>
#include <boost/type_traits/is_compound.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_constructible.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_copy_assignable.hpp>
#include <boost/type_traits/is_copy_constructible.hpp>
#include <boost/type_traits/is_default_constructible.hpp>
#include <boost/type_traits/is_destructible.hpp>
#include <boost/type_traits/is_empty.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_final.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_list_constructible.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/type_traits/is_member_object_pointer.hpp>
#include <boost/type_traits/is_member_pointer.hpp>
#include <boost/type_traits/is_nothrow_move_assignable.hpp>
#include <boost/type_traits/is_nothrow_move_constructible.hpp>
#include <boost/type_traits/is_nothrow_swappable.hpp>
#include <boost/type_traits/is_object.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_rvalue_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_scalar.hpp>
#include <boost/type_traits/is_scoped_enum.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_stateless.hpp>
#include <boost/type_traits/is_trivially_copyable.hpp>
#include <boost/type_traits/is_union.hpp>
#include <boost/type_traits/is_unscoped_enum.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/type_traits/is_virtual_base_of.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/make_signed.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/make_void.hpp>
#include <boost/type_traits/negation.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/remove_all_extents.hpp>
#include <boost/type_traits/remove_bounds.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_cv_ref.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_volatile.hpp>
#include <boost/type_traits/type_identity.hpp>
#include <boost/type_traits/type_with_alignment.hpp>

#if !(defined(__sgi) && defined(__EDG_VERSION__) && (__EDG_VERSION__ == 238))
#include <boost/type_traits/integral_promotion.hpp>
#include <boost/type_traits/promote.hpp>
#endif

#endif // BOOST_TYPE_TRAITS_HPP

/* type_traits.hpp
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
*/