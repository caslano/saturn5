//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_VALARRAY_HPP
#define BOOST_COMPUTE_CONTAINER_VALARRAY_HPP

#include <cstddef>
#include <valarray>

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/fill.hpp>
#include <boost/compute/algorithm/max_element.hpp>
#include <boost/compute/algorithm/min_element.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/algorithm/accumulate.hpp>
#include <boost/compute/detail/buffer_value.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/functional/bind.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits.hpp>

namespace boost {
namespace compute {

template<class T>
class valarray
{
public:
    explicit valarray(const context &context = system::default_context())
        : m_buffer(context, 0)
    {
    }

    explicit valarray(size_t size,
                      const context &context = system::default_context())
        : m_buffer(context, size * sizeof(T))
    {
    }

    valarray(const T &value,
             size_t size,
             const context &context = system::default_context())
        : m_buffer(context, size * sizeof(T))
    {
        fill(begin(), end(), value);
    }

    valarray(const T *values,
             size_t size,
             const context &context = system::default_context())
        : m_buffer(context, size * sizeof(T))
    {
        copy(values, values + size, begin());
    }

    valarray(const valarray<T> &other)
        : m_buffer(other.m_buffer.get_context(), other.size() * sizeof(T))
    {
        copy(other.begin(), other.end(), begin());
    }

    valarray(const std::valarray<T> &valarray,
             const context &context = system::default_context())
        : m_buffer(context, valarray.size() * sizeof(T))
    {
        copy(&valarray[0], &valarray[valarray.size()], begin());
    }

    valarray<T>& operator=(const valarray<T> &other)
    {
        if(this != &other){
            // change to other's OpenCL context
            m_buffer = buffer(other.m_buffer.get_context(), other.size() * sizeof(T));
            copy(other.begin(), other.end(), begin());
        }

        return *this;
    }

    valarray<T>& operator=(const std::valarray<T> &valarray)
    {
        m_buffer = buffer(m_buffer.get_context(), valarray.size() * sizeof(T));
        copy(&valarray[0], &valarray[valarray.size()], begin());

        return *this;
    }

    valarray<T>& operator*=(const T&);

    valarray<T>& operator/=(const T&);

    valarray<T>& operator%=(const T& val);

    valarray<T> operator+() const
    {
        //  This operator can be used with any type.
        valarray<T> result(size());
        copy(begin(), end(), result.begin());
        return result;
    }

    valarray<T> operator-() const
    {
        BOOST_STATIC_ASSERT_MSG(
            is_fundamental<T>::value,
            "This operator can be used with all OpenCL built-in scalar"
            " and vector types"
        );
        valarray<T> result(size());
        BOOST_COMPUTE_FUNCTION(T, unary_minus, (T x),
        {
            return -x;
        });
        transform(begin(), end(), result.begin(), unary_minus);
        return result;
    }

    valarray<T> operator~() const
    {
        BOOST_STATIC_ASSERT_MSG(
            is_fundamental<T>::value &&
                !is_floating_point<typename scalar_type<T>::type>::value,
            "This operator can be used with all OpenCL built-in scalar"
            " and vector types except the built-in scalar and vector float types"
        );
        valarray<T> result(size());
        BOOST_COMPUTE_FUNCTION(T, bitwise_not, (T x),
        {
            return ~x;
        });
        transform(begin(), end(), result.begin(), bitwise_not);
        return result;
    }

    /// In OpenCL there cannot be memory buffer with bool type, for
    /// this reason return type is valarray<char> instead of valarray<bool>.
    /// 1 means true, 0 means false.
    valarray<char> operator!() const
    {
        BOOST_STATIC_ASSERT_MSG(
            is_fundamental<T>::value,
            "This operator can be used with all OpenCL built-in scalar"
            " and vector types"
        );
        valarray<char> result(size());
        BOOST_COMPUTE_FUNCTION(char, logical_not, (T x),
        {
            return !x;
        });
        transform(begin(), end(), &result[0], logical_not);
        return result;
    }

    valarray<T>& operator+=(const T&);

    valarray<T>& operator-=(const T&);

    valarray<T>& operator^=(const T&);

    valarray<T>& operator&=(const T&);

    valarray<T>& operator|=(const T&);

    valarray<T>& operator<<=(const T&);

    valarray<T>& operator>>=(const T&);

    valarray<T>& operator*=(const valarray<T>&);

    valarray<T>& operator/=(const valarray<T>&);

    valarray<T>& operator%=(const valarray<T>&);

    valarray<T>& operator+=(const valarray<T>&);

    valarray<T>& operator-=(const valarray<T>&);

    valarray<T>& operator^=(const valarray<T>&);

    valarray<T>& operator&=(const valarray<T>&);

    valarray<T>& operator|=(const valarray<T>&);

    valarray<T>& operator<<=(const valarray<T>&);

    valarray<T>& operator>>=(const valarray<T>&);

    ~valarray()
    {

    }

    size_t size() const
    {
        return m_buffer.size() / sizeof(T);
    }

    void resize(size_t size, T value = T())
    {
        m_buffer = buffer(m_buffer.get_context(), size * sizeof(T));
        fill(begin(), end(), value);
    }

    detail::buffer_value<T> operator[](size_t index)
    {
        return *(begin() + static_cast<ptrdiff_t>(index));
    }

    const detail::buffer_value<T> operator[](size_t index) const
    {
        return *(begin() + static_cast<ptrdiff_t>(index));
    }

    T (min)() const
    {
        return *(boost::compute::min_element(begin(), end()));
    }

    T (max)() const
    {
        return *(boost::compute::max_element(begin(), end()));
    }

    T sum() const
    {
        return boost::compute::accumulate(begin(), end(), T(0));
    }

    template<class UnaryFunction>
    valarray<T> apply(UnaryFunction function) const
    {
        valarray<T> result(size());
        transform(begin(), end(), result.begin(), function);
        return result;
    }

    const buffer& get_buffer() const
    {
        return m_buffer;
    }


private:
    buffer_iterator<T> begin() const
    {
        return buffer_iterator<T>(m_buffer, 0);
    }

    buffer_iterator<T> end() const
    {
        return buffer_iterator<T>(m_buffer, size());
    }

private:
    buffer m_buffer;
};

/// \internal_
#define BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT(op, op_name, assert) \
    template<class T> \
    inline valarray<T>& \
    valarray<T>::operator op##=(const T& val) \
    { \
        assert \
        transform(begin(), end(), begin(), \
            ::boost::compute::bind(op_name<T>(), placeholders::_1, val)); \
        return *this; \
    } \
    \
    template<class T> \
    inline valarray<T>& \
    valarray<T>::operator op##=(const valarray<T> &rhs) \
    { \
        assert \
        transform(begin(), end(), rhs.begin(), begin(), op_name<T>()); \
        return *this; \
    }

/// \internal_
#define BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT_ANY(op, op_name) \
    BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT(op, op_name, \
        BOOST_STATIC_ASSERT_MSG( \
            is_fundamental<T>::value, \
            "This operator can be used with all OpenCL built-in scalar" \
            " and vector types" \
        ); \
    )

/// \internal_
/// For some operators class T can't be floating point type.
/// See OpenCL specification, operators chapter.
#define BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT_NO_FP(op, op_name) \
    BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT(op, op_name, \
        BOOST_STATIC_ASSERT_MSG( \
            is_fundamental<T>::value && \
                !is_floating_point<typename scalar_type<T>::type>::value, \
            "This operator can be used with all OpenCL built-in scalar" \
            " and vector types except the built-in scalar and vector float types" \
        ); \
    )

// defining operators
BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT_ANY(+, plus)
BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT_ANY(-, minus)
BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT_ANY(*, multiplies)
BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT_ANY(/, divides)
BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT_NO_FP(^, bit_xor)
BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT_NO_FP(&, bit_and)
BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT_NO_FP(|, bit_or)
BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT_NO_FP(<<, shift_left)
BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT_NO_FP(>>, shift_right)

// The remainder (%) operates on
// integer scalar and integer vector data types only.
// See OpenCL specification.
BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT(%, modulus,
    BOOST_STATIC_ASSERT_MSG(
        is_integral<typename scalar_type<T>::type>::value,
        "This operator can be used only with OpenCL built-in integer types"
    );
)

#undef BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT_ANY
#undef BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT_NO_FP

#undef BOOST_COMPUTE_DEFINE_VALARRAY_COMPOUND_ASSIGNMENT

/// \internal_
/// Macro for defining binary operators for valarray
#define BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR(op, op_name, assert) \
    template<class T> \
    valarray<T> operator op (const valarray<T>& lhs, const valarray<T>& rhs) \
    { \
        assert \
        valarray<T> result(lhs.size()); \
        transform(buffer_iterator<T>(lhs.get_buffer(), 0), \
                  buffer_iterator<T>(lhs.get_buffer(), lhs.size()), \
                  buffer_iterator<T>(rhs.get_buffer(), 0), \
                  buffer_iterator<T>(result.get_buffer(), 0), \
                  op_name<T>()); \
        return result; \
    } \
    \
    template<class T> \
    valarray<T> operator op (const T& val, const valarray<T>& rhs) \
    { \
        assert \
        valarray<T> result(rhs.size()); \
        transform(buffer_iterator<T>(rhs.get_buffer(), 0), \
                  buffer_iterator<T>(rhs.get_buffer(), rhs.size()), \
                  buffer_iterator<T>(result.get_buffer(), 0), \
                  ::boost::compute::bind(op_name<T>(), val, placeholders::_1)); \
        return result; \
    } \
    \
    template<class T> \
    valarray<T> operator op (const valarray<T>& lhs, const T& val) \
    { \
        assert \
        valarray<T> result(lhs.size()); \
        transform(buffer_iterator<T>(lhs.get_buffer(), 0), \
                  buffer_iterator<T>(lhs.get_buffer(), lhs.size()), \
                  buffer_iterator<T>(result.get_buffer(), 0), \
                  ::boost::compute::bind(op_name<T>(), placeholders::_1, val)); \
        return result; \
    }

/// \internal_
#define BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR_ANY(op, op_name) \
    BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR(op, op_name, \
        BOOST_STATIC_ASSERT_MSG( \
            is_fundamental<T>::value, \
            "This operator can be used with all OpenCL built-in scalar" \
            " and vector types" \
        ); \
    )

/// \internal_
/// For some operators class T can't be floating point type.
/// See OpenCL specification, operators chapter.
#define BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR_NO_FP(op, op_name) \
    BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR(op, op_name, \
        BOOST_STATIC_ASSERT_MSG( \
            is_fundamental<T>::value && \
                !is_floating_point<typename scalar_type<T>::type>::value, \
            "This operator can be used with all OpenCL built-in scalar" \
            " and vector types except the built-in scalar and vector float types" \
        ); \
    )

// defining binary operators for valarray
BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR_ANY(+, plus)
BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR_ANY(-, minus)
BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR_ANY(*, multiplies)
BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR_ANY(/, divides)
BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR_NO_FP(^, bit_xor)
BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR_NO_FP(&, bit_and)
BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR_NO_FP(|, bit_or)
BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR_NO_FP(<<, shift_left)
BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR_NO_FP(>>, shift_right)

#undef BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR_ANY
#undef BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR_NO_FP

#undef BOOST_COMPUTE_DEFINE_VALARRAY_BINARY_OPERATOR

/// \internal_
/// Macro for defining valarray comparison operators.
/// For return type valarray<char> is used instead of valarray<bool> because
/// in OpenCL there cannot be memory buffer with bool type.
///
/// Note it's also used for defining binary logical operators (==, &&)
#define BOOST_COMPUTE_DEFINE_VALARRAY_COMPARISON_OPERATOR(op, op_name) \
    template<class T> \
    valarray<char> operator op (const valarray<T>& lhs, const valarray<T>& rhs) \
    { \
        BOOST_STATIC_ASSERT_MSG( \
            is_fundamental<T>::value, \
            "This operator can be used with all OpenCL built-in scalar" \
            " and vector types" \
        ); \
        valarray<char> result(lhs.size()); \
        transform(buffer_iterator<T>(lhs.get_buffer(), 0), \
                  buffer_iterator<T>(lhs.get_buffer(), lhs.size()), \
                  buffer_iterator<T>(rhs.get_buffer(), 0), \
                  buffer_iterator<char>(result.get_buffer(), 0), \
                  op_name<T>()); \
        return result; \
    } \
    \
    template<class T> \
    valarray<char> operator op (const T& val, const valarray<T>& rhs) \
    { \
        BOOST_STATIC_ASSERT_MSG( \
            is_fundamental<T>::value, \
            "This operator can be used with all OpenCL built-in scalar" \
            " and vector types" \
        ); \
        valarray<char> result(rhs.size()); \
        transform(buffer_iterator<T>(rhs.get_buffer(), 0), \
                  buffer_iterator<T>(rhs.get_buffer(), rhs.size()), \
                  buffer_iterator<char>(result.get_buffer(), 0), \
                  ::boost::compute::bind(op_name<T>(), val, placeholders::_1)); \
        return result; \
    } \
    \
    template<class T> \
    valarray<char> operator op (const valarray<T>& lhs, const T& val) \
    { \
        BOOST_STATIC_ASSERT_MSG( \
            is_fundamental<T>::value, \
            "This operator can be used with all OpenCL built-in scalar" \
            " and vector types" \
        ); \
        valarray<char> result(lhs.size()); \
        transform(buffer_iterator<T>(lhs.get_buffer(), 0), \
                  buffer_iterator<T>(lhs.get_buffer(), lhs.size()), \
                  buffer_iterator<char>(result.get_buffer(), 0), \
                  ::boost::compute::bind(op_name<T>(), placeholders::_1, val)); \
        return result; \
    }

BOOST_COMPUTE_DEFINE_VALARRAY_COMPARISON_OPERATOR(==, equal_to)
BOOST_COMPUTE_DEFINE_VALARRAY_COMPARISON_OPERATOR(!=, not_equal_to)
BOOST_COMPUTE_DEFINE_VALARRAY_COMPARISON_OPERATOR(>, greater)
BOOST_COMPUTE_DEFINE_VALARRAY_COMPARISON_OPERATOR(<, less)
BOOST_COMPUTE_DEFINE_VALARRAY_COMPARISON_OPERATOR(>=, greater_equal)
BOOST_COMPUTE_DEFINE_VALARRAY_COMPARISON_OPERATOR(<=, less_equal)

/// \internal_
/// Macro for defining binary logical operators for valarray.
///
/// For return type valarray<char> is used instead of valarray<bool> because
/// in OpenCL there cannot be memory buffer with bool type.
/// 1 means true, 0 means false.
#define BOOST_COMPUTE_DEFINE_VALARRAY_LOGICAL_OPERATOR(op, op_name) \
    BOOST_COMPUTE_DEFINE_VALARRAY_COMPARISON_OPERATOR(op, op_name)

BOOST_COMPUTE_DEFINE_VALARRAY_LOGICAL_OPERATOR(&&, logical_and)
BOOST_COMPUTE_DEFINE_VALARRAY_LOGICAL_OPERATOR(||, logical_or)

#undef BOOST_COMPUTE_DEFINE_VALARRAY_LOGICAL_OPERATOR

#undef BOOST_COMPUTE_DEFINE_VALARRAY_COMPARISON_OPERATOR

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_VALARRAY_HPP

/* valarray.hpp
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
*/