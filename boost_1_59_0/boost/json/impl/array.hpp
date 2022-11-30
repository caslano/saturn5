//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_IMPL_ARRAY_HPP
#define BOOST_JSON_IMPL_ARRAY_HPP

#include <boost/json/value.hpp>
#include <boost/json/detail/except.hpp>
#include <algorithm>
#include <stdexcept>
#include <type_traits>

BOOST_JSON_NS_BEGIN

//----------------------------------------------------------

struct alignas(value)
    array::table
{
    std::uint32_t size = 0;
    std::uint32_t capacity = 0;

    constexpr table();

    value&
    operator[](std::size_t pos) noexcept
    {
        return (reinterpret_cast<
            value*>(this + 1))[pos];
    }

    BOOST_JSON_DECL
    static
    table*
    allocate(
        std::size_t capacity,
        storage_ptr const& sp);

    BOOST_JSON_DECL
    static
    void
    deallocate(
        table* p,
        storage_ptr const& sp);
};

//----------------------------------------------------------

class array::revert_construct
{
    array* arr_;

public:
    explicit
    revert_construct(
        array& arr) noexcept
        : arr_(&arr)
    {
    }

    ~revert_construct()
    {
        if(! arr_)
            return;
        arr_->destroy();
    }

    void
    commit() noexcept
    {
        arr_ = nullptr;
    }
};

//----------------------------------------------------------

class array::revert_insert
{
    array* arr_;
    std::size_t const i_;
    std::size_t const n_;

public:
    value* p;

    BOOST_JSON_DECL
    revert_insert(
        const_iterator pos,
        std::size_t n,
        array& arr);

    BOOST_JSON_DECL
    ~revert_insert();

    value*
    commit() noexcept
    {
        auto it =
            arr_->data() + i_;
        arr_ = nullptr;
        return it;
    }
};

//----------------------------------------------------------

void
array::
relocate(
    value* dest,
    value* src,
    std::size_t n) noexcept
{
    if(n == 0)
        return;
    std::memmove(
        static_cast<void*>(dest),
        static_cast<void const*>(src),
        n * sizeof(value));
}

//----------------------------------------------------------
//
// Construction
//
//----------------------------------------------------------

template<class InputIt, class>
array::
array(
    InputIt first, InputIt last,
    storage_ptr sp)
    : array(
        first, last,
        std::move(sp),
        iter_cat<InputIt>{})
{
    BOOST_STATIC_ASSERT(
        std::is_constructible<value,
            decltype(*first)>::value);
}

//----------------------------------------------------------
//
// Modifiers
//
//----------------------------------------------------------

template<class InputIt, class>
auto
array::
insert(
    const_iterator pos,
    InputIt first, InputIt last) ->
        iterator
{
    BOOST_STATIC_ASSERT(
        std::is_constructible<value,
            decltype(*first)>::value);
    return insert(pos, first, last,
        iter_cat<InputIt>{});
}

template<class Arg>
auto
array::
emplace(
    const_iterator pos,
    Arg&& arg) ->
        iterator
{
    BOOST_ASSERT(
        pos >= begin() &&
        pos <= end());
    value jv(
        std::forward<Arg>(arg),
        storage());
    return insert(pos, pilfer(jv));
}

template<class Arg>
value&
array::
emplace_back(Arg&& arg)
{
    value jv(
        std::forward<Arg>(arg),
        storage());
    return push_back(pilfer(jv));
}

//----------------------------------------------------------
//
// Element access
//
//----------------------------------------------------------

value&
array::
at(std::size_t pos)
{
    if(pos >= t_->size)
        detail::throw_out_of_range(
            BOOST_JSON_SOURCE_POS);
    return (*t_)[pos];
}

value const&
array::
at(std::size_t pos) const
{
    if(pos >= t_->size)
        detail::throw_out_of_range(
            BOOST_JSON_SOURCE_POS);
    return (*t_)[pos];
}

value&
array::
operator[](std::size_t pos) noexcept
{
    BOOST_ASSERT(pos < t_->size);
    return (*t_)[pos];
}

value const&
array::
operator[](std::size_t pos) const noexcept
{
    BOOST_ASSERT(pos < t_->size);
    return (*t_)[pos];
}

value&
array::
front() noexcept
{
    BOOST_ASSERT(t_->size > 0);
    return (*t_)[0];
}

value const&
array::
front() const noexcept
{
    BOOST_ASSERT(t_->size > 0);
    return (*t_)[0];
}

value&
array::
back() noexcept
{
    BOOST_ASSERT(
        t_->size > 0);
    return (*t_)[t_->size - 1];
}

value const&
array::
back() const noexcept
{
    BOOST_ASSERT(
        t_->size > 0);
    return (*t_)[t_->size - 1];
}

value*
array::
data() noexcept
{
    return &(*t_)[0];
}

value const*
array::
data() const noexcept
{
    return &(*t_)[0];
}

value const*
array::
if_contains(
    std::size_t pos) const noexcept
{
    if( pos < t_->size )
        return &(*t_)[pos];
    return nullptr;
}

value*
array::
if_contains(
    std::size_t pos) noexcept
{
    if( pos < t_->size )
        return &(*t_)[pos];
    return nullptr;
}

//----------------------------------------------------------
//
// Iterators
//
//----------------------------------------------------------

auto
array::
begin() noexcept ->
    iterator
{
    return &(*t_)[0];
}

auto
array::
begin() const noexcept ->
    const_iterator
{
    return &(*t_)[0];
}

auto
array::
cbegin() const noexcept ->
    const_iterator
{
    return &(*t_)[0];
}

auto
array::
end() noexcept ->
    iterator
{
    return &(*t_)[t_->size];
}

auto
array::
end() const noexcept ->
    const_iterator
{
    return &(*t_)[t_->size];
}

auto
array::
cend() const noexcept ->
    const_iterator
{
    return &(*t_)[t_->size];
}

auto
array::
rbegin() noexcept ->
    reverse_iterator
{
    return reverse_iterator(end());
}

auto
array::
rbegin() const noexcept ->
    const_reverse_iterator
{
    return const_reverse_iterator(end());
}

auto
array::
crbegin() const noexcept ->
    const_reverse_iterator
{
    return const_reverse_iterator(end());
}

auto
array::
rend() noexcept ->
    reverse_iterator
{
    return reverse_iterator(begin());
}

auto
array::
rend() const noexcept ->
    const_reverse_iterator
{
    return const_reverse_iterator(begin());
}

auto
array::
crend() const noexcept ->
    const_reverse_iterator
{
    return const_reverse_iterator(begin());
}

//----------------------------------------------------------
//
// Capacity
//
//----------------------------------------------------------

std::size_t
array::
size() const noexcept
{
    return t_->size;
}

constexpr
std::size_t
array::
max_size() noexcept
{
    // max_size depends on the address model
    using min = std::integral_constant<std::size_t,
        (std::size_t(-1) - sizeof(table)) / sizeof(value)>;
    return min::value < BOOST_JSON_MAX_STRUCTURED_SIZE ?
        min::value : BOOST_JSON_MAX_STRUCTURED_SIZE;
}

std::size_t
array::
capacity() const noexcept
{
    return t_->capacity;
}

bool
array::
empty() const noexcept
{
    return t_->size == 0;
}

void
array::
reserve(
    std::size_t new_capacity)
{
    // never shrink
    if(new_capacity <= t_->capacity)
        return;
    reserve_impl(new_capacity);
}

//----------------------------------------------------------
//
// private
//
//----------------------------------------------------------

template<class InputIt>
array::
array(
    InputIt first, InputIt last,
    storage_ptr sp,
    std::input_iterator_tag)
    : sp_(std::move(sp))
    , t_(&empty_)
{
    revert_construct r(*this);
    while(first != last)
    {
        reserve(size() + 1);
        ::new(end()) value(
            *first++, sp_);
        ++t_->size;
    }
    r.commit();
}

template<class InputIt>
array::
array(
    InputIt first, InputIt last,
    storage_ptr sp,
    std::forward_iterator_tag)
    : sp_(std::move(sp))
{
    std::size_t n =
        std::distance(first, last);
    if( n == 0 )
    {
        t_ = &empty_;
        return;
    }

    t_ = table::allocate(n, sp_);
    t_->size = 0;
    revert_construct r(*this);
    while(n--)
    {
        ::new(end()) value(
            *first++, sp_);
        ++t_->size;
    }
    r.commit();
}

template<class InputIt>
auto
array::
insert(
    const_iterator pos,
    InputIt first, InputIt last,
    std::input_iterator_tag) ->
        iterator
{
    BOOST_ASSERT(
        pos >= begin() && pos <= end());
    if(first == last)
        return data() + (pos - data());
    array temp(first, last, sp_);
    revert_insert r(
        pos, temp.size(), *this);
    relocate(
        r.p,
        temp.data(),
        temp.size());
    temp.t_->size = 0;
    return r.commit();
}

template<class InputIt>
auto
array::
insert(
    const_iterator pos,
    InputIt first, InputIt last,
    std::forward_iterator_tag) ->
        iterator
{
    std::size_t n =
        std::distance(first, last);
    revert_insert r(pos, n, *this);
    while(n--)
    {
        ::new(r.p) value(*first++);
        ++r.p;
    }
    return r.commit();
}

BOOST_JSON_NS_END

#endif

/* array.hpp
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
*/