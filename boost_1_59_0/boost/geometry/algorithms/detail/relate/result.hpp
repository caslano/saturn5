// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_RESULT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_RESULT_HPP

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <string>
#include <type_traits>

#include <boost/throw_exception.hpp>
#include <boost/tuple/tuple.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/exception.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/sequence.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

enum field { interior = 0, boundary = 1, exterior = 2 };

// TODO: IF THE RESULT IS UPDATED WITH THE MAX POSSIBLE VALUE FOR SOME PAIR OF GEOEMTRIES
// THE VALUE ALREADY STORED MUSN'T BE CHECKED
// update() calls chould be replaced with set() in those cases
// but for safety reasons (STATIC_ASSERT) we should check if parameter D is valid and set() doesn't do that
// so some additional function could be added, e.g. set_dim()

// --------------- MATRIX ----------------

// matrix

template <std::size_t Height, std::size_t Width = Height>
class matrix
{
public:
    typedef char value_type;
    typedef std::size_t size_type;
    typedef const char * const_iterator;
    typedef const_iterator iterator;

    static const std::size_t static_width = Width;
    static const std::size_t static_height = Height;
    static const std::size_t static_size = Width * Height;
    
    inline matrix()
    {
        ::memset(m_array, 'F', static_size);
    }

    template <field F1, field F2>
    inline char get() const
    {
        BOOST_STATIC_ASSERT(F1 < Height && F2 < Width);
        static const std::size_t index = F1 * Width + F2;
        BOOST_STATIC_ASSERT(index < static_size);
        return m_array[index];
    }

    template <field F1, field F2, char V>
    inline void set()
    {
        BOOST_STATIC_ASSERT(F1 < Height && F2 < Width);
        static const std::size_t index = F1 * Width + F2;
        BOOST_STATIC_ASSERT(index < static_size);
        m_array[index] = V;
    }

    inline char operator[](std::size_t index) const
    {
        BOOST_GEOMETRY_ASSERT(index < static_size);
        return m_array[index];
    }

    inline const_iterator begin() const
    {
        return m_array;
    }

    inline const_iterator end() const
    {
        return m_array + static_size;
    }

    inline static std::size_t size()
    {
        return static_size;
    }
    
    inline const char * data() const
    {
        return m_array;
    }

    inline std::string str() const
    {
        return std::string(m_array, static_size);
    }

private:
    char m_array[static_size];
};

// matrix_handler

template <typename Matrix>
class matrix_handler
{
public:
    typedef Matrix result_type;

    static const bool interrupt = false;

    matrix_handler()
    {}

    result_type const& result() const
    {
        return m_matrix;
    }

    result_type const& matrix() const
    {
        return m_matrix;
    }

    result_type & matrix()
    {
        return m_matrix;
    }

    template <field F1, field F2, char D>
    inline bool may_update() const
    {
        BOOST_STATIC_ASSERT('0' <= D && D <= '9');

        char const c = m_matrix.template get<F1, F2>();
        return D > c || c > '9';
    }

    template <field F1, field F2, char V>
    inline void set()
    {
        static const bool in_bounds = F1 < Matrix::static_height
                                   && F2 < Matrix::static_width;
        typedef std::integral_constant<bool, in_bounds> in_bounds_t;
        set_dispatch<F1, F2, V>(in_bounds_t());
    }

    template <field F1, field F2, char D>
    inline void update()
    {
        static const bool in_bounds = F1 < Matrix::static_height
                                   && F2 < Matrix::static_width;
        typedef std::integral_constant<bool, in_bounds> in_bounds_t;
        update_dispatch<F1, F2, D>(in_bounds_t());
    }

private:
    template <field F1, field F2, char V>
    inline void set_dispatch(std::true_type)
    {
        static const std::size_t index = F1 * Matrix::static_width + F2;
        BOOST_STATIC_ASSERT(index < Matrix::static_size);
        BOOST_STATIC_ASSERT(('0' <= V && V <= '9') || V == 'T' || V == 'F');
        m_matrix.template set<F1, F2, V>();
    }
    template <field F1, field F2, char V>
    inline void set_dispatch(std::false_type)
    {}

    template <field F1, field F2, char D>
    inline void update_dispatch(std::true_type)
    {
        static const std::size_t index = F1 * Matrix::static_width + F2;
        BOOST_STATIC_ASSERT(index < Matrix::static_size);
        BOOST_STATIC_ASSERT('0' <= D && D <= '9');
        char const c = m_matrix.template get<F1, F2>();
        if ( D > c || c > '9')
            m_matrix.template set<F1, F2, D>();
    }
    template <field F1, field F2, char D>
    inline void update_dispatch(std::false_type)
    {}

    Matrix m_matrix;
};

// --------------- RUN-TIME MASK ----------------

// run-time mask

template <std::size_t Height, std::size_t Width = Height>
class mask
{
public:
    static const std::size_t static_width = Width;
    static const std::size_t static_height = Height;
    static const std::size_t static_size = Width * Height;

    inline mask(const char * s)
    {
        char * it = m_array;
        char * const last = m_array + static_size;
        for ( ; it != last && *s != '\0' ; ++it, ++s )
        {
            char c = *s;
            check_char(c);
            *it = c;
        }
        if ( it != last )
        {
            ::memset(it, '*', last - it);
        }
    }

    inline mask(const char * s, std::size_t count)
    {
        if ( count > static_size )
        {
            count = static_size;
        }
        if ( count > 0 )
        {
            std::for_each(s, s + count, check_char);
            ::memcpy(m_array, s, count);
        }
        if ( count < static_size )
        {
            ::memset(m_array + count, '*', static_size - count);
        }
    }

    template <field F1, field F2>
    inline char get() const
    {
        BOOST_STATIC_ASSERT(F1 < Height && F2 < Width);
        static const std::size_t index = F1 * Width + F2;
        BOOST_STATIC_ASSERT(index < static_size);
        return m_array[index];
    }

private:
    static inline void check_char(char c)
    {
        bool const is_valid = c == '*' || c == 'T' || c == 'F'
                         || ( c >= '0' && c <= '9' );
        if ( !is_valid )
        {
            BOOST_THROW_EXCEPTION(geometry::invalid_input_exception());
        }
    }

    char m_array[static_size];
};

// interrupt()

template <typename Mask, bool InterruptEnabled>
struct interrupt_dispatch
{
    template <field F1, field F2, char V>
    static inline bool apply(Mask const&)
    {
        return false;
    }
};

template <typename Mask>
struct interrupt_dispatch<Mask, true>
{
    template <field F1, field F2, char V>
    static inline bool apply(Mask const& mask)
    {
        char m = mask.template get<F1, F2>();
        return check_element<V>(m);
    }

    template <char V>
    static inline bool check_element(char m)
    {
        if ( BOOST_GEOMETRY_CONDITION(V >= '0' && V <= '9') )
        {
            return m == 'F' || ( m < V && m >= '0' && m <= '9' );
        }
        else if ( BOOST_GEOMETRY_CONDITION(V == 'T') )
        {
            return m == 'F';
        }
        return false;
    }
};

template <typename Masks, int I = 0, int N = std::tuple_size<Masks>::value>
struct interrupt_dispatch_tuple
{
    template <field F1, field F2, char V>
    static inline bool apply(Masks const& masks)
    {
        typedef typename std::tuple_element<I, Masks>::type mask_type;
        mask_type const& mask = std::get<I>(masks);
        return interrupt_dispatch<mask_type, true>::template apply<F1, F2, V>(mask)
            && interrupt_dispatch_tuple<Masks, I+1>::template apply<F1, F2, V>(masks);
    }
};

template <typename Masks, int N>
struct interrupt_dispatch_tuple<Masks, N, N>
{
    template <field F1, field F2, char V>
    static inline bool apply(Masks const& )
    {
        return true;
    }
};

template <typename ...Masks>
struct interrupt_dispatch<std::tuple<Masks...>, true>
{
    typedef std::tuple<Masks...> mask_type;

    template <field F1, field F2, char V>
    static inline bool apply(mask_type const& mask)
    {
        return interrupt_dispatch_tuple<mask_type>::template apply<F1, F2, V>(mask);
    }
};

template <field F1, field F2, char V, bool InterruptEnabled, typename Mask>
inline bool interrupt(Mask const& mask)
{
    return interrupt_dispatch<Mask, InterruptEnabled>
                ::template apply<F1, F2, V>(mask);
}

// may_update()

template <typename Mask>
struct may_update_dispatch
{
    template <field F1, field F2, char D, typename Matrix>
    static inline bool apply(Mask const& mask, Matrix const& matrix)
    {
        BOOST_STATIC_ASSERT('0' <= D && D <= '9');

        char const m = mask.template get<F1, F2>();
        
        if ( m == 'F' )
        {
            return true;
        }
        else if ( m == 'T' )
        {
            char const c = matrix.template get<F1, F2>();
            return c == 'F'; // if it's T or between 0 and 9, the result will be the same
        }
        else if ( m >= '0' && m <= '9' )
        {
            char const c = matrix.template get<F1, F2>();
            return D > c || c > '9';
        }

        return false;
    }
};

template <typename Masks, int I = 0, int N = std::tuple_size<Masks>::value>
struct may_update_dispatch_tuple
{
    template <field F1, field F2, char D, typename Matrix>
    static inline bool apply(Masks const& masks, Matrix const& matrix)
    {
        typedef typename std::tuple_element<I, Masks>::type mask_type;
        mask_type const& mask = std::get<I>(masks);
        return may_update_dispatch<mask_type>::template apply<F1, F2, D>(mask, matrix)
            || may_update_dispatch_tuple<Masks, I+1>::template apply<F1, F2, D>(masks, matrix);
    }
};

template <typename Masks, int N>
struct may_update_dispatch_tuple<Masks, N, N>
{
    template <field F1, field F2, char D, typename Matrix>
    static inline bool apply(Masks const& , Matrix const& )
    {
        return false;
    }
};

template <typename ...Masks>
struct may_update_dispatch<std::tuple<Masks...>>
{
    typedef std::tuple<Masks...> mask_type;

    template <field F1, field F2, char D, typename Matrix>
    static inline bool apply(mask_type const& mask, Matrix const& matrix)
    {
        return may_update_dispatch_tuple<mask_type>::template apply<F1, F2, D>(mask, matrix);
    }
};

template <field F1, field F2, char D, typename Mask, typename Matrix>
inline bool may_update(Mask const& mask, Matrix const& matrix)
{
    return may_update_dispatch<Mask>
                ::template apply<F1, F2, D>(mask, matrix);
}

// check_matrix()

template <typename Mask>
struct check_dispatch
{
    template <typename Matrix>
    static inline bool apply(Mask const& mask, Matrix const& matrix)
    {
        return per_one<interior, interior>(mask, matrix)
            && per_one<interior, boundary>(mask, matrix)
            && per_one<interior, exterior>(mask, matrix)
            && per_one<boundary, interior>(mask, matrix)
            && per_one<boundary, boundary>(mask, matrix)
            && per_one<boundary, exterior>(mask, matrix)
            && per_one<exterior, interior>(mask, matrix)
            && per_one<exterior, boundary>(mask, matrix)
            && per_one<exterior, exterior>(mask, matrix);
    }

    template <field F1, field F2, typename Matrix>
    static inline bool per_one(Mask const& mask, Matrix const& matrix)
    {
        const char mask_el = mask.template get<F1, F2>();
        const char el = matrix.template get<F1, F2>();

        if ( mask_el == 'F' )
        {
            return el == 'F';
        }
        else if ( mask_el == 'T' )
        {
            return el == 'T' || ( el >= '0' && el <= '9' );
        }
        else if ( mask_el >= '0' && mask_el <= '9' )
        {
            return el == mask_el;
        }

        return true;
    }
};

template <typename Masks, int I = 0, int N = std::tuple_size<Masks>::value>
struct check_dispatch_tuple
{
    template <typename Matrix>
    static inline bool apply(Masks const& masks, Matrix const& matrix)
    {
        typedef typename std::tuple_element<I, Masks>::type mask_type;
        mask_type const& mask = std::get<I>(masks);
        return check_dispatch<mask_type>::apply(mask, matrix)
            || check_dispatch_tuple<Masks, I+1>::apply(masks, matrix);
    }
};

template <typename Masks, int N>
struct check_dispatch_tuple<Masks, N, N>
{
    template <typename Matrix>
    static inline bool apply(Masks const&, Matrix const&)
    {
        return false;
    }
};

template <typename ...Masks>
struct check_dispatch<std::tuple<Masks...>>
{
    typedef std::tuple<Masks...> mask_type;

    template <typename Matrix>
    static inline bool apply(mask_type const& mask, Matrix const& matrix)
    {
        return check_dispatch_tuple<mask_type>::apply(mask, matrix);
    }
};

template <typename Mask, typename Matrix>
inline bool check_matrix(Mask const& mask, Matrix const& matrix)
{
    return check_dispatch<Mask>::apply(mask, matrix);
}

// matrix_width

template <typename MatrixOrMask>
struct matrix_width
{
    static const std::size_t value = MatrixOrMask::static_width;
};

template <typename Tuple,
          int I = 0,
          int N = std::tuple_size<Tuple>::value>
struct matrix_width_tuple
{
    static const std::size_t
        current = matrix_width<typename std::tuple_element<I, Tuple>::type>::value;
    static const std::size_t
        next = matrix_width_tuple<Tuple, I+1>::value;

    static const std::size_t
        value = current > next ? current : next;
};

template <typename Tuple, int N>
struct matrix_width_tuple<Tuple, N, N>
{
    static const std::size_t value = 0;
};

template <typename ...Masks>
struct matrix_width<std::tuple<Masks...>>
{
    static const std::size_t
        value = matrix_width_tuple<std::tuple<Masks...>>::value;
};

// mask_handler

template <typename Mask, bool Interrupt>
class mask_handler
    : private matrix_handler
        <
            relate::matrix<matrix_width<Mask>::value>
        >
{
    typedef matrix_handler
        <
            relate::matrix<matrix_width<Mask>::value>
        > base_t;

public:
    typedef bool result_type;

    bool interrupt;

    inline explicit mask_handler(Mask const& m)
        : interrupt(false)
        , m_mask(m)
    {}

    result_type result() const
    {
        return !interrupt
            && check_matrix(m_mask, base_t::matrix());
    }

    template <field F1, field F2, char D>
    inline bool may_update() const
    {
        return detail::relate::may_update<F1, F2, D>(
                    m_mask, base_t::matrix()
               );
    }

    template <field F1, field F2, char V>
    inline void set()
    {
        if ( relate::interrupt<F1, F2, V, Interrupt>(m_mask) )
        {
            interrupt = true;
        }
        else
        {
            base_t::template set<F1, F2, V>();
        }
    }

    template <field F1, field F2, char V>
    inline void update()
    {
        if ( relate::interrupt<F1, F2, V, Interrupt>(m_mask) )
        {
            interrupt = true;
        }
        else
        {
            base_t::template update<F1, F2, V>();
        }
    }

private:
    Mask const& m_mask;
};

// --------------- FALSE MASK ----------------

struct false_mask {};

// --------------- COMPILE-TIME MASK ----------------

// static_check_characters
template <typename Seq>
struct static_check_characters {};

template <char C, char ...Cs>
struct static_check_characters<std::integer_sequence<char, C, Cs...>>
    : static_check_characters<std::integer_sequence<char, Cs...>>
{
    typedef std::integer_sequence<char, C, Cs...> type;
    static const bool is_valid = (C >= '0' && C <= '9')
                               || C == 'T' || C == 'F' || C == '*';
    BOOST_GEOMETRY_STATIC_ASSERT((is_valid),
                                 "Invalid static mask character",
                                 type);
};

template <char ...Cs>
struct static_check_characters<std::integral_constant<char, Cs...>>
{};

// static_mask

template <typename Seq, std::size_t Height, std::size_t Width = Height>
struct static_mask
{
    static const std::size_t static_width = Width;
    static const std::size_t static_height = Height;
    static const std::size_t static_size = Width * Height;

    BOOST_STATIC_ASSERT(
        std::size_t(util::sequence_size<Seq>::value) == static_size);
    
    template <detail::relate::field F1, detail::relate::field F2>
    struct static_get
    {
        BOOST_STATIC_ASSERT(std::size_t(F1) < static_height);
        BOOST_STATIC_ASSERT(std::size_t(F2) < static_width);

        static const char value
            = util::sequence_element<F1 * static_width + F2, Seq>::value;
    };

private:
    // check static_mask characters
    enum { mask_check = sizeof(static_check_characters<Seq>) };
};

// static_should_handle_element

template
<
    typename StaticMask, field F1, field F2,
    bool IsSequence = util::is_sequence<StaticMask>::value
>
struct static_should_handle_element_dispatch
{
    static const char mask_el = StaticMask::template static_get<F1, F2>::value;
    static const bool value = mask_el == 'F'
                           || mask_el == 'T'
                           || ( mask_el >= '0' && mask_el <= '9' );
};

template
<
    typename Seq, field F1, field F2,
    std::size_t I = 0,
    std::size_t N = util::sequence_size<Seq>::value
>
struct static_should_handle_element_sequence
{
    typedef typename util::sequence_element<I, Seq>::type StaticMask;

    static const bool value
        = static_should_handle_element_dispatch
            <
                StaticMask, F1, F2
            >::value
       || static_should_handle_element_sequence
            <
                Seq, F1, F2, I + 1
            >::value;
};

template <typename Seq, field F1, field F2, std::size_t N>
struct static_should_handle_element_sequence<Seq, F1, F2, N, N>
{
    static const bool value = false;
};

template <typename StaticMask, field F1, field F2>
struct static_should_handle_element_dispatch<StaticMask, F1, F2, true>
{
    static const bool value
        = static_should_handle_element_sequence
            <
                StaticMask, F1, F2
            >::value;
};

template <typename StaticMask, field F1, field F2>
struct static_should_handle_element
{
    static const bool value
        = static_should_handle_element_dispatch
            <
                StaticMask, F1, F2
            >::value;
};

// static_interrupt

template
<
    typename StaticMask, char V, field F1, field F2,
    bool InterruptEnabled,
    bool IsSequence = util::is_sequence<StaticMask>::value
>
struct static_interrupt_dispatch
{
    static const bool value = false;
};

template <typename StaticMask, char V, field F1, field F2, bool IsSequence>
struct static_interrupt_dispatch<StaticMask, V, F1, F2, true, IsSequence>
{
    static const char mask_el = StaticMask::template static_get<F1, F2>::value;

    static const bool value
        = ( V >= '0' && V <= '9' ) ? 
          ( mask_el == 'F' || ( mask_el < V && mask_el >= '0' && mask_el <= '9' ) ) :
          ( ( V == 'T' ) ? mask_el == 'F' : false );
};

template
<
    typename Seq, char V, field F1, field F2,
    std::size_t I = 0,
    std::size_t N = util::sequence_size<Seq>::value
>
struct static_interrupt_sequence
{
    typedef typename util::sequence_element<I, Seq>::type StaticMask;

    static const bool value
        = static_interrupt_dispatch
            <
                StaticMask, V, F1, F2, true
            >::value
       && static_interrupt_sequence
            <
                Seq, V, F1, F2, I + 1
            >::value;
};

template <typename Seq, char V, field F1, field F2, std::size_t N>
struct static_interrupt_sequence<Seq, V, F1, F2, N, N>
{
    static const bool value = true;
};

template <typename StaticMask, char V, field F1, field F2>
struct static_interrupt_dispatch<StaticMask, V, F1, F2, true, true>
{
    static const bool value
        = static_interrupt_sequence
            <
                StaticMask, V, F1, F2
            >::value;
};

template <typename StaticMask, char V, field F1, field F2, bool EnableInterrupt>
struct static_interrupt
{
    static const bool value
        = static_interrupt_dispatch
            <
                StaticMask, V, F1, F2, EnableInterrupt
            >::value;
};

// static_may_update

template
<
    typename StaticMask, char D, field F1, field F2,
    bool IsSequence = util::is_sequence<StaticMask>::value
>
struct static_may_update_dispatch
{
    static const char mask_el = StaticMask::template static_get<F1, F2>::value;
    static const int version
                        = mask_el == 'F' ? 0
                        : mask_el == 'T' ? 1
                        : mask_el >= '0' && mask_el <= '9' ? 2
                        : 3;

    // TODO: use std::enable_if_t instead of std::integral_constant

    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return apply_dispatch(matrix, std::integral_constant<int, version>());
    }

    // mask_el == 'F'
    template <typename Matrix>
    static inline bool apply_dispatch(Matrix const& , std::integral_constant<int, 0>)
    {
        return true;
    }
    // mask_el == 'T'
    template <typename Matrix>
    static inline bool apply_dispatch(Matrix const& matrix, std::integral_constant<int, 1>)
    {
        char const c = matrix.template get<F1, F2>();
        return c == 'F'; // if it's T or between 0 and 9, the result will be the same
    }
    // mask_el >= '0' && mask_el <= '9'
    template <typename Matrix>
    static inline bool apply_dispatch(Matrix const& matrix, std::integral_constant<int, 2>)
    {
        char const c = matrix.template get<F1, F2>();
        return D > c || c > '9';
    }
    // else
    template <typename Matrix>
    static inline bool apply_dispatch(Matrix const&, std::integral_constant<int, 3>)
    {
        return false;
    }
};

template
<
    typename Seq, char D, field F1, field F2,
    std::size_t I = 0,
    std::size_t N = util::sequence_size<Seq>::value
>
struct static_may_update_sequence
{
    typedef typename util::sequence_element<I, Seq>::type StaticMask;

    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return static_may_update_dispatch
                <
                    StaticMask, D, F1, F2
                >::apply(matrix)
            || static_may_update_sequence
                <
                    Seq, D, F1, F2, I + 1
                >::apply(matrix);
    }
};

template <typename Seq, char D, field F1, field F2, std::size_t N>
struct static_may_update_sequence<Seq, D, F1, F2, N, N>
{
    template <typename Matrix>
    static inline bool apply(Matrix const& /*matrix*/)
    {
        return false;
    }
};

template <typename StaticMask, char D, field F1, field F2>
struct static_may_update_dispatch<StaticMask, D, F1, F2, true>
{
    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return static_may_update_sequence
                <
                    StaticMask, D, F1, F2
                >::apply(matrix);
    }
};

template <typename StaticMask, char D, field F1, field F2>
struct static_may_update
{
    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return static_may_update_dispatch
                <
                    StaticMask, D, F1, F2
                >::apply(matrix);
    }
};

// static_check_matrix

template
<
    typename StaticMask,
    bool IsSequence = util::is_sequence<StaticMask>::value
>
struct static_check_dispatch
{
    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return per_one<interior, interior>::apply(matrix)
            && per_one<interior, boundary>::apply(matrix)
            && per_one<interior, exterior>::apply(matrix)
            && per_one<boundary, interior>::apply(matrix)
            && per_one<boundary, boundary>::apply(matrix)
            && per_one<boundary, exterior>::apply(matrix)
            && per_one<exterior, interior>::apply(matrix)
            && per_one<exterior, boundary>::apply(matrix)
            && per_one<exterior, exterior>::apply(matrix);
    }
    
    template <field F1, field F2>
    struct per_one
    {
        static const char mask_el = StaticMask::template static_get<F1, F2>::value;
        static const int version
                            = mask_el == 'F' ? 0
                            : mask_el == 'T' ? 1
                            : mask_el >= '0' && mask_el <= '9' ? 2
                            : 3;

        // TODO: use std::enable_if_t instead of std::integral_constant

        template <typename Matrix>
        static inline bool apply(Matrix const& matrix)
        {
            const char el = matrix.template get<F1, F2>();
            return apply_dispatch(el, std::integral_constant<int, version>());
        }

        // mask_el == 'F'
        static inline bool apply_dispatch(char el, std::integral_constant<int, 0>)
        {
            return el == 'F';
        }
        // mask_el == 'T'
        static inline bool apply_dispatch(char el, std::integral_constant<int, 1>)
        {
            return el == 'T' || ( el >= '0' && el <= '9' );
        }
        // mask_el >= '0' && mask_el <= '9'
        static inline bool apply_dispatch(char el, std::integral_constant<int, 2>)
        {
            return el == mask_el;
        }
        // else
        static inline bool apply_dispatch(char /*el*/, std::integral_constant<int, 3>)
        {
            return true;
        }
    };
};

template
<
    typename Seq,
    std::size_t I = 0,
    std::size_t N = util::sequence_size<Seq>::value
>
struct static_check_sequence
{
    typedef typename util::sequence_element<I, Seq>::type StaticMask;

    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return static_check_dispatch
                <
                    StaticMask
                >::apply(matrix)
            || static_check_sequence
                <
                    Seq, I + 1
                >::apply(matrix);
    }
};

template <typename Seq, std::size_t N>
struct static_check_sequence<Seq, N, N>
{
    template <typename Matrix>
    static inline bool apply(Matrix const& /*matrix*/)
    {
        return false;
    }
};

template <typename StaticMask>
struct static_check_dispatch<StaticMask, true>
{
    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return static_check_sequence
                <
                    StaticMask
                >::apply(matrix);
    }
};

template <typename StaticMask>
struct static_check_matrix
{
    template <typename Matrix>
    static inline bool apply(Matrix const& matrix)
    {
        return static_check_dispatch
                <
                    StaticMask
                >::apply(matrix);
    }
};

// static_mask_handler

template <typename StaticMask, bool Interrupt>
class static_mask_handler
    : private matrix_handler< matrix<3> >
{
    typedef matrix_handler< relate::matrix<3> > base_type;

public:
    typedef bool result_type;

    bool interrupt;

    inline static_mask_handler()
        : interrupt(false)
    {}

    inline explicit static_mask_handler(StaticMask const& /*dummy*/)
        : interrupt(false)
    {}

    result_type result() const
    {
        return (!Interrupt || !interrupt)
            && static_check_matrix<StaticMask>::apply(base_type::matrix());
    }

    template <field F1, field F2, char D>
    inline bool may_update() const
    {
        return static_may_update<StaticMask, D, F1, F2>::
                    apply(base_type::matrix());
    }

    template <field F1, field F2>
    static inline bool expects()
    {
        return static_should_handle_element<StaticMask, F1, F2>::value;
    }

    template <field F1, field F2, char V>
    inline void set()
    {
        static const bool interrupt_c = static_interrupt<StaticMask, V, F1, F2, Interrupt>::value;
        static const bool should_handle = static_should_handle_element<StaticMask, F1, F2>::value;
        static const int version = interrupt_c ? 0
                                 : should_handle ? 1
                                 : 2;

        set_dispatch<F1, F2, V>(integral_constant<int, version>());
    }

    template <field F1, field F2, char V>
    inline void update()
    {
        static const bool interrupt_c = static_interrupt<StaticMask, V, F1, F2, Interrupt>::value;
        static const bool should_handle = static_should_handle_element<StaticMask, F1, F2>::value;
        static const int version = interrupt_c ? 0
                                 : should_handle ? 1
                                 : 2;

        update_dispatch<F1, F2, V>(integral_constant<int, version>());
    }

private:
    // Interrupt && interrupt
    template <field F1, field F2, char V>
    inline void set_dispatch(integral_constant<int, 0>)
    {
        interrupt = true;
    }
    // else should_handle
    template <field F1, field F2, char V>
    inline void set_dispatch(integral_constant<int, 1>)
    {
        base_type::template set<F1, F2, V>();
    }
    // else
    template <field F1, field F2, char V>
    inline void set_dispatch(integral_constant<int, 2>)
    {}

    // Interrupt && interrupt
    template <field F1, field F2, char V>
    inline void update_dispatch(integral_constant<int, 0>)
    {
        interrupt = true;
    }
    // else should_handle
    template <field F1, field F2, char V>
    inline void update_dispatch(integral_constant<int, 1>)
    {
        base_type::template update<F1, F2, V>();
    }
    // else
    template <field F1, field F2, char V>
    inline void update_dispatch(integral_constant<int, 2>)
    {}
};

// --------------- UTIL FUNCTIONS ----------------

// set

template <field F1, field F2, char V, typename Result>
inline void set(Result & res)
{
    res.template set<F1, F2, V>();
}

template <field F1, field F2, char V, bool Transpose>
struct set_dispatch
{
    template <typename Result>
    static inline void apply(Result & res)
    {
        res.template set<F1, F2, V>();
    }
};

template <field F1, field F2, char V>
struct set_dispatch<F1, F2, V, true>
{
    template <typename Result>
    static inline void apply(Result & res)
    {
        res.template set<F2, F1, V>();
    }
};

template <field F1, field F2, char V, bool Transpose, typename Result>
inline void set(Result & res)
{
    set_dispatch<F1, F2, V, Transpose>::apply(res);
}

// update

template <field F1, field F2, char D, typename Result>
inline void update(Result & res)
{
    res.template update<F1, F2, D>();
}

template <field F1, field F2, char D, bool Transpose>
struct update_result_dispatch
{
    template <typename Result>
    static inline void apply(Result & res)
    {
        update<F1, F2, D>(res);
    }
};

template <field F1, field F2, char D>
struct update_result_dispatch<F1, F2, D, true>
{
    template <typename Result>
    static inline void apply(Result & res)
    {
        update<F2, F1, D>(res);
    }
};

template <field F1, field F2, char D, bool Transpose, typename Result>
inline void update(Result & res)
{
    update_result_dispatch<F1, F2, D, Transpose>::apply(res);
}

// may_update

template <field F1, field F2, char D, typename Result>
inline bool may_update(Result const& res)
{
    return res.template may_update<F1, F2, D>();
}

template <field F1, field F2, char D, bool Transpose>
struct may_update_result_dispatch
{
    template <typename Result>
    static inline bool apply(Result const& res)
    {
        return may_update<F1, F2, D>(res);
    }
};

template <field F1, field F2, char D>
struct may_update_result_dispatch<F1, F2, D, true>
{
    template <typename Result>
    static inline bool apply(Result const& res)
    {
        return may_update<F2, F1, D>(res);
    }
};

template <field F1, field F2, char D, bool Transpose, typename Result>
inline bool may_update(Result const& res)
{
    return may_update_result_dispatch<F1, F2, D, Transpose>::apply(res);
}

// result_dimension

template <typename Geometry>
struct result_dimension
{
    BOOST_STATIC_ASSERT(geometry::dimension<Geometry>::value >= 0);
    static const char value
        = ( geometry::dimension<Geometry>::value <= 9 ) ?
            ( '0' + geometry::dimension<Geometry>::value ) :
              'T';
};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_RESULT_HPP

/* result.hpp
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
*/