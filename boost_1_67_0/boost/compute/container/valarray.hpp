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