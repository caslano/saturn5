//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_IMPL_OBJECT_HPP
#define BOOST_JSON_IMPL_OBJECT_HPP

#include <boost/json/value.hpp>
#include <iterator>
#include <cmath>
#include <type_traits>
#include <utility>

BOOST_JSON_NS_BEGIN

namespace detail {

// Objects with size less than or equal
// to this number will use a linear search
// instead of the more expensive hash function.
static
constexpr
std::size_t
small_object_size_ = 18;

BOOST_STATIC_ASSERT(
    small_object_size_ <
    BOOST_JSON_MAX_STRUCTURED_SIZE);

} // detail

//----------------------------------------------------------

struct alignas(key_value_pair)
    object::table
{
    std::uint32_t size = 0;
    std::uint32_t capacity = 0;
    std::uintptr_t salt = 0;

#if defined(_MSC_VER) && BOOST_JSON_ARCH == 32
    // VFALCO If we make key_value_pair smaller,
    //        then we might want to revisit this
    //        padding.
    BOOST_STATIC_ASSERT(
        sizeof(key_value_pair) == 32);
    char pad[4] = {}; // silence warnings
#endif

    constexpr table();

    // returns true if we use a linear
    // search instead of the hash table.
    bool is_small() const noexcept
    {
        return capacity <=
            detail::small_object_size_;
    }

    key_value_pair&
    operator[](
        std::size_t pos) noexcept
    {
        return reinterpret_cast<
            key_value_pair*>(
                this + 1)[pos];
    }

    // VFALCO This is exported for tests
    BOOST_JSON_DECL
    std::size_t
    digest(string_view key) const noexcept;

    inline
    index_t&
    bucket(std::size_t hash) noexcept;

    inline
    index_t&
    bucket(string_view key) noexcept;

    inline
    void
    clear() noexcept;

    static
    inline
    table*
    allocate(
        std::size_t capacity,
        std::uintptr_t salt,
        storage_ptr const& sp);

    static
    void
    deallocate(
        table* p,
        storage_ptr const& sp) noexcept
    {
        if(p->capacity == 0)
            return;
        if(! p->is_small())
            sp->deallocate(p,
                sizeof(table) + p->capacity * (
                    sizeof(key_value_pair) +
                    sizeof(index_t)));
        else
            sp->deallocate(p,
                sizeof(table) + p->capacity *
                    sizeof(key_value_pair));
    }
};

//----------------------------------------------------------

class object::revert_construct
{
    object* obj_;

    BOOST_JSON_DECL
    void
    destroy() noexcept;

public:
    explicit
    revert_construct(
        object& obj) noexcept
        : obj_(&obj)
    {
    }

    ~revert_construct()
    {
        if(! obj_)
            return;
        destroy();
    }

    void
    commit() noexcept
    {
        obj_ = nullptr;
    }
};

//----------------------------------------------------------

class object::revert_insert
{
    object* obj_;
    std::size_t size_;

    BOOST_JSON_DECL
    void
    destroy() noexcept;

public:
    explicit
    revert_insert(
        object& obj) noexcept
        : obj_(&obj)
        , size_(obj_->size())
    {
    }

    ~revert_insert()
    {
        if(! obj_)
            return;
        destroy();
        obj_->t_->size = static_cast<
            index_t>(size_);
    }

    void
    commit() noexcept
    {
        obj_ = nullptr;
    }
};

//----------------------------------------------------------
//
// Iterators
//
//----------------------------------------------------------

auto
object::
begin() noexcept ->
    iterator
{
    return &(*t_)[0];
}

auto
object::
begin() const noexcept ->
    const_iterator
{
    return &(*t_)[0];
}

auto
object::
cbegin() const noexcept ->
    const_iterator
{
    return &(*t_)[0];
}

auto
object::
end() noexcept ->
    iterator
{
    return &(*t_)[t_->size];
}

auto
object::
end() const noexcept ->
    const_iterator
{
    return &(*t_)[t_->size];
}

auto
object::
cend() const noexcept ->
    const_iterator
{
    return &(*t_)[t_->size];
}

auto
object::
rbegin() noexcept ->
    reverse_iterator
{
    return reverse_iterator(end());
}

auto
object::
rbegin() const noexcept ->
    const_reverse_iterator
{
    return const_reverse_iterator(end());
}

auto
object::
crbegin() const noexcept ->
    const_reverse_iterator
{
    return const_reverse_iterator(end());
}

auto
object::
rend() noexcept ->
    reverse_iterator
{
    return reverse_iterator(begin());
}

auto
object::
rend() const noexcept ->
    const_reverse_iterator
{
    return const_reverse_iterator(begin());
}

auto
object::
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

bool
object::
empty() const noexcept
{
    return t_->size == 0;
}

auto
object::
size() const noexcept ->
    std::size_t
{
    return t_->size;
}

constexpr
std::size_t
object::
max_size() noexcept
{
    // max_size depends on the address model
    using min = std::integral_constant<std::size_t,
        (std::size_t(-1) - sizeof(table)) /
            (sizeof(key_value_pair) + sizeof(index_t))>;
    return min::value < BOOST_JSON_MAX_STRUCTURED_SIZE ?
        min::value : BOOST_JSON_MAX_STRUCTURED_SIZE;
}

auto
object::
capacity() const noexcept ->
    std::size_t
{
    return t_->capacity;
}

//----------------------------------------------------------
//
// Lookup
//
//----------------------------------------------------------

auto
object::
at(string_view key) ->
    value&
{
    auto it = find(key);
    if(it == end())
        detail::throw_out_of_range(
            BOOST_JSON_SOURCE_POS);
    return it->value();
}

auto
object::
at(string_view key) const ->
    value const&
{
    auto it = find(key);
    if(it == end())
        detail::throw_out_of_range(
            BOOST_JSON_SOURCE_POS);
    return it->value();
}

//----------------------------------------------------------

template<class P, class>
auto
object::
insert(P&& p) ->
    std::pair<iterator, bool>
{
    key_value_pair v(
        std::forward<P>(p), sp_);
    return insert_impl(pilfer(v));
}

template<class M>
auto
object::
insert_or_assign(
    string_view key, M&& m) ->
        std::pair<iterator, bool>
{
    reserve(size() + 1);
    auto const result = detail::find_in_object(*this, key);
    if(result.first)
    {
        value(std::forward<M>(m),
            sp_).swap(result.first->value());
        return { result.first, false };
    }
    key_value_pair kv(key,
        std::forward<M>(m), sp_);
    return { insert_impl(pilfer(kv),
        result.second), true };
}

template<class Arg>
auto
object::
emplace(
    string_view key,
    Arg&& arg) ->
        std::pair<iterator, bool>
{
    reserve(size() + 1);
    auto const result = detail::find_in_object(*this, key);
    if(result.first)
        return { result.first, false };
    key_value_pair kv(key,
        std::forward<Arg>(arg), sp_);
    return { insert_impl(pilfer(kv),
        result.second), true };
}

//----------------------------------------------------------
//
// (private)
//
//----------------------------------------------------------

template<class InputIt>
void
object::
construct(
    InputIt first,
    InputIt last,
    std::size_t min_capacity,
    std::input_iterator_tag)
{
    reserve(min_capacity);
    revert_construct r(*this);
    while(first != last)
    {
        insert(*first);
        ++first;
    }
    r.commit();
}

template<class InputIt>
void
object::
construct(
    InputIt first,
    InputIt last,
    std::size_t min_capacity,
    std::forward_iterator_tag)
{
    auto n = static_cast<
        std::size_t>(std::distance(
            first, last));
    if( n < min_capacity)
        n = min_capacity;
    reserve(n);
    revert_construct r(*this);
    while(first != last)
    {
        insert(*first);
        ++first;
    }
    r.commit();
}

template<class InputIt>
void
object::
insert(
    InputIt first,
    InputIt last,
    std::input_iterator_tag)
{
    // Since input iterators cannot be rewound,
    // we keep inserted elements on an exception.
    //
    while(first != last)
    {
        insert(*first);
        ++first;
    }
}

template<class InputIt>
void
object::
insert(
    InputIt first,
    InputIt last,
    std::forward_iterator_tag)
{
    auto const n =
        static_cast<std::size_t>(
            std::distance(first, last));
    auto const n0 = size();
    if(n > max_size() - n0)
        detail::throw_length_error(
            "object too large",
            BOOST_JSON_SOURCE_POS);
    reserve(n0 + n);
    revert_insert r(*this);
    while(first != last)
    {
        insert(*first);
        ++first;
    }
    r.commit();
}

//----------------------------------------------------------

namespace detail {

unchecked_object::
~unchecked_object()
{
    if(! data_)
        return;
    if(sp_.is_not_shared_and_deallocate_is_trivial())
        return;
    value* p = data_;
    while(size_--)
    {
        p[0].~value();
        p[1].~value();
        p += 2;
    }
}

} // detail

BOOST_JSON_NS_END

#endif

/* object.hpp
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
*/