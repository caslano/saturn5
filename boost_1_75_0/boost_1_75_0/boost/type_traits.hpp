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
#include <boost/type_traits/copy_cv.hpp>
#include <boost/type_traits/copy_cv_ref.hpp>
#include <boost/type_traits/copy_reference.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/declval.hpp>
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
#if !defined(__BORLANDC__) && !defined(__CUDACC__)
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
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_stateless.hpp>
#include <boost/type_traits/is_union.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/type_traits/is_virtual_base_of.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/make_signed.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/make_void.hpp>
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
TZQhTp+sqG4m0gh5PbFtpP4k3VOzdOmLTlARbPXvjyS299ttgVv1G1GBWLpd8+9H0SXxTeLhGWAdP+P1WJGrI05/Hr9PefM7I2zib4cFPjLrX6jOh/qUaJMihHUj1XMYCzS3sK5VWMk4jTUj1b8/Got/dZg6y9zXMlDr9l/y3T1MYTTaR1fxQ3Qd+ObB57SMfNzJjo919LLmbK3WGO1BStIJ31FDCojPmB3/gqOXLWd7xwQD5QSovbp580woZYg83wrq997HnsDZLX9hwSQ9kpf2dDhKP46+81w+zZohal9MHt6hL+QJiik3mwIdgpaniXszQxz9rMJwwNIzxBvDsYQ/zlPHp9OzWsXCLd11eE4O0TKohDt2eKPNKs4arIXKhQopGEmLcXo+VLq2jMwgGoBK+f1wZBZNMgi+ppK1rHs8JG4qSWQ9FgikmWqaSjSsZ9pgEqgiaaogPtnAz9D9UfYhhN3ZnGzQ00sqJsvQC129ozWA+5MjYo6noBujZJ2ncs3TqVNs4p+CaU4I1cIkfRGnL9SYs1pZzzDIhx5qp6Mgh8vvd3Qi1zRr32eYw+hDpSlJF+X4hz0oDXDSP/7NMP2OomFHn995WGoZpGXE43PxPiXK3OCIEL+gcCKEDUCBkYg8+oy1iW/Nle0QShJeNctGEtA+X0s46x0KpRTMMqCbUG8SYLDHukNa6k87c5/p0SNzFR0jm7gA5l/m
*/