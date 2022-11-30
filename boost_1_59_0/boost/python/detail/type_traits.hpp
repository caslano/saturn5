// Copyright Shreyans Doshi 2017.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PYTHON_DETAIL_TYPE_TRAITS_HPP
# define BOOST_PYTHON_DETAIL_TYPE_TRAITS_HPP


#include <boost/config.hpp>
#ifdef BOOST_NO_CXX11_HDR_TYPE_TRAITS
# include <boost/type_traits/transform_traits.hpp>
# include <boost/type_traits/same_traits.hpp>
# include <boost/type_traits/cv_traits.hpp>
# include <boost/type_traits/is_polymorphic.hpp>
# include <boost/type_traits/composite_traits.hpp>
# include <boost/type_traits/conversion_traits.hpp>
# include <boost/type_traits/add_pointer.hpp>
# include <boost/type_traits/remove_pointer.hpp>
# include <boost/type_traits/is_void.hpp>
# include <boost/type_traits/object_traits.hpp>
# include <boost/type_traits/add_lvalue_reference.hpp>
# include <boost/type_traits/function_traits.hpp>
# include <boost/type_traits/is_scalar.hpp>
# include <boost/type_traits/alignment_traits.hpp>
# include <boost/mpl/bool.hpp>
#else
# include <type_traits>
#endif

# include <boost/type_traits/is_base_and_derived.hpp>
# include <boost/type_traits/alignment_traits.hpp>
# include <boost/type_traits/has_trivial_copy.hpp>


namespace boost { namespace python { namespace detail {

#ifdef BOOST_NO_CXX11_HDR_TYPE_TRAITS
    using boost::alignment_of;
    using boost::add_const;
    using boost::add_cv;
    using boost::add_lvalue_reference;
    using boost::add_pointer;

    using boost::is_array;
    using boost::is_class;
    using boost::is_const;
    using boost::is_convertible;
    using boost::is_enum;
    using boost::is_function;
    using boost::is_integral;
    using boost::is_lvalue_reference;
    using boost::is_member_function_pointer;
    using boost::is_member_pointer;
    using boost::is_pointer;
    using boost::is_polymorphic;
    using boost::is_reference;
    using boost::is_same;
    using boost::is_scalar;
    using boost::is_union;
    using boost::is_void;
    using boost::is_volatile;

    using boost::remove_reference;
    using boost::remove_pointer;
    using boost::remove_cv;
    using boost::remove_const;

    using boost::mpl::true_;
    using boost::mpl::false_;
#else
    using std::alignment_of;
    using std::add_const;
    using std::add_cv;
    using std::add_lvalue_reference;
    using std::add_pointer;

    using std::is_array;
    using std::is_class;
    using std::is_const;
    using std::is_convertible;
    using std::is_enum;
    using std::is_function;
    using std::is_integral;
    using std::is_lvalue_reference;
    using std::is_member_function_pointer;
    using std::is_member_pointer;
    using std::is_pointer;
    using std::is_polymorphic;
    using std::is_reference;
    using std::is_same;
    using std::is_scalar;
    using std::is_union;
    using std::is_void;
    using std::is_volatile;

    using std::remove_reference;
    using std::remove_pointer;
    using std::remove_cv;
    using std::remove_const;

    typedef std::integral_constant<bool, true> true_;
    typedef std::integral_constant<bool, false> false_;
#endif
    using boost::is_base_and_derived;
    using boost::type_with_alignment;
    using boost::has_trivial_copy;
}}} // namespace boost::python::detail


#endif //BOOST_DETAIL_TYPE_TRAITS_HPP

/* type_traits.hpp
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
*/