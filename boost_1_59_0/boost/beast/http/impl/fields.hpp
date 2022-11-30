//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_FIELDS_HPP
#define BOOST_BEAST_HTTP_IMPL_FIELDS_HPP

#include <boost/beast/core/buffers_cat.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/core/detail/buffers_ref.hpp>
#include <boost/beast/core/detail/clamp.hpp>
#include <boost/beast/core/detail/static_string.hpp>
#include <boost/beast/core/detail/temporary_buffer.hpp>
#include <boost/beast/core/static_string.hpp>
#include <boost/beast/http/verb.hpp>
#include <boost/beast/http/rfc7230.hpp>
#include <boost/beast/http/status.hpp>
#include <boost/beast/http/chunk_encode.hpp>
#include <boost/core/exchange.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>
#include <string>

namespace boost {
namespace beast {
namespace http {

template<class Allocator>
class basic_fields<Allocator>::writer
{
public:
    using iter_type = typename list_t::const_iterator;

    struct field_iterator
    {
        iter_type it_;

        using value_type = net::const_buffer;
        using pointer = value_type const*;
        using reference = value_type const;
        using difference_type = std::ptrdiff_t;
        using iterator_category =
            std::bidirectional_iterator_tag;

        field_iterator() = default;
        field_iterator(field_iterator&& other) = default;
        field_iterator(field_iterator const& other) = default;
        field_iterator& operator=(field_iterator&& other) = default;
        field_iterator& operator=(field_iterator const& other) = default;

        explicit
        field_iterator(iter_type it)
            : it_(it)
        {
        }

        bool
        operator==(field_iterator const& other) const
        {
            return it_ == other.it_;
        }

        bool
        operator!=(field_iterator const& other) const
        {
            return !(*this == other);
        }

        reference
        operator*() const
        {
            return it_->buffer();
        }

        field_iterator&
        operator++()
        {
            ++it_;
            return *this;
        }

        field_iterator
        operator++(int)
        {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        field_iterator&
        operator--()
        {
            --it_;
            return *this;
        }

        field_iterator
        operator--(int)
        {
            auto temp = *this;
            --(*this);
            return temp;
        }
    };

    class field_range
    {
        field_iterator first_;
        field_iterator last_;

    public:
        using const_iterator =
            field_iterator;

        using value_type =
            typename const_iterator::value_type;

        field_range(iter_type first, iter_type last)
            : first_(first)
            , last_(last)
        {
        }

        const_iterator
        begin() const
        {
            return first_;
        }

        const_iterator
        end() const
        {
            return last_;
        }
    };

    using view_type = buffers_cat_view<
        net::const_buffer,
        net::const_buffer,
        net::const_buffer,
        field_range,
        chunk_crlf>;

    basic_fields const& f_;
    boost::optional<view_type> view_;
    char buf_[13];

public:
    using const_buffers_type =
        beast::detail::buffers_ref<view_type>;

    writer(basic_fields const& f,
        unsigned version, verb v);

    writer(basic_fields const& f,
        unsigned version, unsigned code);

    writer(basic_fields const& f);

    const_buffers_type
    get() const
    {
        return const_buffers_type(*view_);
    }
};

template<class Allocator>
basic_fields<Allocator>::writer::
writer(basic_fields const& f)
    : f_(f)
{
    view_.emplace(
        net::const_buffer{nullptr, 0},
        net::const_buffer{nullptr, 0},
        net::const_buffer{nullptr, 0},
        field_range(f_.list_.begin(), f_.list_.end()),
        chunk_crlf());
}

template<class Allocator>
basic_fields<Allocator>::writer::
writer(basic_fields const& f,
        unsigned version, verb v)
    : f_(f)
{
/*
    request
        "<method>"
        " <target>"
        " HTTP/X.Y\r\n" (11 chars)
*/
    string_view sv;
    if(v == verb::unknown)
        sv = f_.get_method_impl();
    else
        sv = to_string(v);

    // target_or_reason_ has a leading SP

    buf_[0] = ' ';
    buf_[1] = 'H';
    buf_[2] = 'T';
    buf_[3] = 'T';
    buf_[4] = 'P';
    buf_[5] = '/';
    buf_[6] = '0' + static_cast<char>(version / 10);
    buf_[7] = '.';
    buf_[8] = '0' + static_cast<char>(version % 10);
    buf_[9] = '\r';
    buf_[10]= '\n';

    view_.emplace(
        net::const_buffer{sv.data(), sv.size()},
        net::const_buffer{
            f_.target_or_reason_.data(),
            f_.target_or_reason_.size()},
        net::const_buffer{buf_, 11},
        field_range(f_.list_.begin(), f_.list_.end()),
        chunk_crlf());
}

template<class Allocator>
basic_fields<Allocator>::writer::
writer(basic_fields const& f,
        unsigned version, unsigned code)
    : f_(f)
{
/*
    response
        "HTTP/X.Y ### " (13 chars)
        "<reason>"
        "\r\n"
*/
    buf_[0] = 'H';
    buf_[1] = 'T';
    buf_[2] = 'T';
    buf_[3] = 'P';
    buf_[4] = '/';
    buf_[5] = '0' + static_cast<char>(version / 10);
    buf_[6] = '.';
    buf_[7] = '0' + static_cast<char>(version % 10);
    buf_[8] = ' ';
    buf_[9] = '0' + static_cast<char>(code / 100);
    buf_[10]= '0' + static_cast<char>((code / 10) % 10);
    buf_[11]= '0' + static_cast<char>(code % 10);
    buf_[12]= ' ';

    string_view sv;
    if(! f_.target_or_reason_.empty())
        sv = f_.target_or_reason_;
    else
        sv = obsolete_reason(static_cast<status>(code));

    view_.emplace(
        net::const_buffer{buf_, 13},
        net::const_buffer{sv.data(), sv.size()},
        net::const_buffer{"\r\n", 2},
        field_range(f_.list_.begin(), f_.list_.end()),
        chunk_crlf{});
}

//------------------------------------------------------------------------------

template<class Allocator>
char*
basic_fields<Allocator>::
value_type::
data() const
{
    return const_cast<char*>(
        reinterpret_cast<char const*>(
            static_cast<element const*>(this) + 1));
}

template<class Allocator>
net::const_buffer
basic_fields<Allocator>::
value_type::
buffer() const
{
    return net::const_buffer{data(),
        static_cast<std::size_t>(off_) + len_ + 2};
}

template<class Allocator>
basic_fields<Allocator>::
value_type::
value_type(field name,
    string_view sname, string_view value)
    : off_(static_cast<off_t>(sname.size() + 2))
    , len_(static_cast<off_t>(value.size()))
    , f_(name)
{
    //BOOST_ASSERT(name == field::unknown ||
    //    iequals(sname, to_string(name)));
    char* p = data();
    p[off_-2] = ':';
    p[off_-1] = ' ';
    p[off_ + len_] = '\r';
    p[off_ + len_ + 1] = '\n';
    sname.copy(p, sname.size());
    value.copy(p + off_, value.size());
}

template<class Allocator>
field
basic_fields<Allocator>::
value_type::
name() const
{
    return f_;
}

template<class Allocator>
string_view const
basic_fields<Allocator>::
value_type::
name_string() const
{
    return {data(),
        static_cast<std::size_t>(off_ - 2)};
}

template<class Allocator>
string_view const
basic_fields<Allocator>::
value_type::
value() const
{
    return {data() + off_,
        static_cast<std::size_t>(len_)};
}

template<class Allocator>
basic_fields<Allocator>::
element::
element(field name,
    string_view sname, string_view value)
    : value_type(name, sname, value)
{
}

//------------------------------------------------------------------------------

template<class Allocator>
basic_fields<Allocator>::
~basic_fields()
{
    delete_list();
    realloc_string(method_, {});
    realloc_string(
        target_or_reason_, {});
}

template<class Allocator>
basic_fields<Allocator>::
basic_fields(Allocator const& alloc) noexcept
    : boost::empty_value<Allocator>(boost::empty_init_t(), alloc)
{
}

template<class Allocator>
basic_fields<Allocator>::
basic_fields(basic_fields&& other) noexcept
    : boost::empty_value<Allocator>(boost::empty_init_t(),
        std::move(other.get()))
    , set_(std::move(other.set_))
    , list_(std::move(other.list_))
    , method_(boost::exchange(other.method_, {}))
    , target_or_reason_(boost::exchange(other.target_or_reason_, {}))
{
}

template<class Allocator>
basic_fields<Allocator>::
basic_fields(basic_fields&& other, Allocator const& alloc)
    : boost::empty_value<Allocator>(boost::empty_init_t(), alloc)
{
    if(this->get() != other.get())
    {
        copy_all(other);
    }
    else
    {
        set_ = std::move(other.set_);
        list_ = std::move(other.list_);
        method_ = other.method_;
        target_or_reason_ = other.target_or_reason_;
    }
}

template<class Allocator>
basic_fields<Allocator>::
basic_fields(basic_fields const& other)
    : boost::empty_value<Allocator>(boost::empty_init_t(), alloc_traits::
        select_on_container_copy_construction(other.get()))
{
    copy_all(other);
}

template<class Allocator>
basic_fields<Allocator>::
basic_fields(basic_fields const& other,
        Allocator const& alloc)
    : boost::empty_value<Allocator>(boost::empty_init_t(), alloc)
{
    copy_all(other);
}

template<class Allocator>
template<class OtherAlloc>
basic_fields<Allocator>::
basic_fields(basic_fields<OtherAlloc> const& other)
{
    copy_all(other);
}

template<class Allocator>
template<class OtherAlloc>
basic_fields<Allocator>::
basic_fields(basic_fields<OtherAlloc> const& other,
        Allocator const& alloc)
    : boost::empty_value<Allocator>(boost::empty_init_t(), alloc)
{
    copy_all(other);
}

template<class Allocator>
auto
basic_fields<Allocator>::
operator=(basic_fields&& other) noexcept(
    alloc_traits::propagate_on_container_move_assignment::value)
      -> basic_fields&
{
    static_assert(is_nothrow_move_assignable<Allocator>::value,
        "Allocator must be noexcept assignable.");
    if(this == &other)
        return *this;
    move_assign(other, std::integral_constant<bool,
        alloc_traits:: propagate_on_container_move_assignment::value>{});
    return *this;
}

template<class Allocator>
auto
basic_fields<Allocator>::
operator=(basic_fields const& other) ->
    basic_fields&
{
    copy_assign(other, std::integral_constant<bool,
        alloc_traits::propagate_on_container_copy_assignment::value>{});
    return *this;
}

template<class Allocator>
template<class OtherAlloc>
auto
basic_fields<Allocator>::
operator=(basic_fields<OtherAlloc> const& other) ->
    basic_fields&
{
    clear_all();
    copy_all(other);
    return *this;
}

//------------------------------------------------------------------------------
//
// Element access
//
//------------------------------------------------------------------------------

template<class Allocator>
string_view const
basic_fields<Allocator>::
at(field name) const
{
    BOOST_ASSERT(name != field::unknown);
    auto const it = find(name);
    if(it == end())
        BOOST_THROW_EXCEPTION(std::out_of_range{
            "field not found"});
    return it->value();
}

template<class Allocator>
string_view const
basic_fields<Allocator>::
at(string_view name) const
{
    auto const it = find(name);
    if(it == end())
        BOOST_THROW_EXCEPTION(std::out_of_range{
            "field not found"});
    return it->value();
}

template<class Allocator>
string_view const
basic_fields<Allocator>::
operator[](field name) const
{
    BOOST_ASSERT(name != field::unknown);
    auto const it = find(name);
    if(it == end())
        return {};
    return it->value();
}

template<class Allocator>
string_view const
basic_fields<Allocator>::
operator[](string_view name) const
{
    auto const it = find(name);
    if(it == end())
        return {};
    return it->value();
}

//------------------------------------------------------------------------------
//
// Modifiers
//
//------------------------------------------------------------------------------

template<class Allocator>
void
basic_fields<Allocator>::
clear()
{
    delete_list();
    set_.clear();
    list_.clear();
}

template<class Allocator>
inline
void
basic_fields<Allocator>::
insert(field name, string_view const& value)
{
    BOOST_ASSERT(name != field::unknown);
    insert(name, to_string(name), value);
}

template<class Allocator>
void
basic_fields<Allocator>::
insert(string_view sname, string_view const& value)
{
    auto const name =
        string_to_field(sname);
    insert(name, sname, value);
}

template<class Allocator>
void
basic_fields<Allocator>::
insert(field name,
    string_view sname, string_view const& value)
{
    auto& e = new_element(name, sname,
        static_cast<string_view>(value));
    auto const before =
        set_.upper_bound(sname, key_compare{});
    if(before == set_.begin())
    {
        BOOST_ASSERT(count(sname) == 0);
        set_.insert_before(before, e);
        list_.push_back(e);
        return;
    }
    auto const last = std::prev(before);
    // VFALCO is it worth comparing `field name` first?
    if(! beast::iequals(sname, last->name_string()))
    {
        BOOST_ASSERT(count(sname) == 0);
        set_.insert_before(before, e);
        list_.push_back(e);
        return;
    }
    // keep duplicate fields together in the list
    set_.insert_before(before, e);
    list_.insert(++list_.iterator_to(*last), e);
}

template<class Allocator>
void
basic_fields<Allocator>::
set(field name, string_view const& value)
{
    BOOST_ASSERT(name != field::unknown);
    set_element(new_element(name, to_string(name),
        static_cast<string_view>(value)));
}

template<class Allocator>
void
basic_fields<Allocator>::
set(string_view sname, string_view const& value)
{
    set_element(new_element(
        string_to_field(sname), sname, value));
}

template<class Allocator>
auto
basic_fields<Allocator>::
erase(const_iterator pos) ->
    const_iterator
{
    auto next = pos;
    auto& e = *next++;
    set_.erase(set_.iterator_to(e));
    list_.erase(pos);
    delete_element(const_cast<element&>(e));
    return next;
}

template<class Allocator>
std::size_t
basic_fields<Allocator>::
erase(field name)
{
    BOOST_ASSERT(name != field::unknown);
    return erase(to_string(name));
}

template<class Allocator>
std::size_t
basic_fields<Allocator>::
erase(string_view name)
{
    std::size_t n =0;
    set_.erase_and_dispose(name, key_compare{},
        [&](element* e)
        {
            ++n;
            list_.erase(list_.iterator_to(*e));
            delete_element(*e);
        });
    return n;
}

template<class Allocator>
void
basic_fields<Allocator>::
swap(basic_fields<Allocator>& other)
{
    swap(other, std::integral_constant<bool,
        alloc_traits::propagate_on_container_swap::value>{});
}

template<class Allocator>
void
swap(
    basic_fields<Allocator>& lhs,
    basic_fields<Allocator>& rhs)
{
    lhs.swap(rhs);
}

//------------------------------------------------------------------------------
//
// Lookup
//
//------------------------------------------------------------------------------

template<class Allocator>
inline
std::size_t
basic_fields<Allocator>::
count(field name) const
{
    BOOST_ASSERT(name != field::unknown);
    return count(to_string(name));
}

template<class Allocator>
std::size_t
basic_fields<Allocator>::
count(string_view name) const
{
    return set_.count(name, key_compare{});
}

template<class Allocator>
inline
auto
basic_fields<Allocator>::
find(field name) const ->
    const_iterator
{
    BOOST_ASSERT(name != field::unknown);
    return find(to_string(name));
}

template<class Allocator>
auto
basic_fields<Allocator>::
find(string_view name) const ->
    const_iterator
{
    auto const it = set_.find(
        name, key_compare{});
    if(it == set_.end())
        return list_.end();
    return list_.iterator_to(*it);
}

template<class Allocator>
inline
auto
basic_fields<Allocator>::
equal_range(field name) const ->
    std::pair<const_iterator, const_iterator>
{
    BOOST_ASSERT(name != field::unknown);
    return equal_range(to_string(name));
}

template<class Allocator>
auto
basic_fields<Allocator>::
equal_range(string_view name) const ->
    std::pair<const_iterator, const_iterator>
{
    auto result =
        set_.equal_range(name, key_compare{});
    if(result.first == result.second)
        return {list_.end(), list_.end()};
    return {
        list_.iterator_to(*result.first),
        ++list_.iterator_to(*(--result.second))};
}

//------------------------------------------------------------------------------

namespace detail {

struct iequals_predicate
{
    bool
    operator()(string_view s) const
    {
        return beast::iequals(s, sv1) || beast::iequals(s, sv2);
    }

    string_view sv1;
    string_view sv2;
};

// Filter the last item in a token list
BOOST_BEAST_DECL
void
filter_token_list_last(
    beast::detail::temporary_buffer& s,
    string_view value,
    iequals_predicate const& pred);

BOOST_BEAST_DECL
void
keep_alive_impl(
    beast::detail::temporary_buffer& s, string_view value,
    unsigned version, bool keep_alive);

} // detail

//------------------------------------------------------------------------------

// Fields

template<class Allocator>
inline
string_view
basic_fields<Allocator>::
get_method_impl() const
{
    return method_;
}

template<class Allocator>
inline
string_view
basic_fields<Allocator>::
get_target_impl() const
{
    if(target_or_reason_.empty())
        return target_or_reason_;
    return {
        target_or_reason_.data() + 1,
        target_or_reason_.size() - 1};
}

template<class Allocator>
inline
string_view
basic_fields<Allocator>::
get_reason_impl() const
{
    return target_or_reason_;
}

template<class Allocator>
bool
basic_fields<Allocator>::
get_chunked_impl() const
{
    auto const te = token_list{
        (*this)[field::transfer_encoding]};
    for(auto it = te.begin(); it != te.end();)
    {
        auto const next = std::next(it);
        if(next == te.end())
            return beast::iequals(*it, "chunked");
        it = next;
    }
    return false;
}

template<class Allocator>
bool
basic_fields<Allocator>::
get_keep_alive_impl(unsigned version) const
{
    auto const it = find(field::connection);
    if(version < 11)
    {
        if(it == end())
            return false;
        return token_list{
            it->value()}.exists("keep-alive");
    }
    if(it == end())
        return true;
    return ! token_list{
        it->value()}.exists("close");
}

template<class Allocator>
bool
basic_fields<Allocator>::
has_content_length_impl() const
{
    return count(field::content_length) > 0;
}

template<class Allocator>
inline
void
basic_fields<Allocator>::
set_method_impl(string_view s)
{
    realloc_string(method_, s);
}

template<class Allocator>
inline
void
basic_fields<Allocator>::
set_target_impl(string_view s)
{
    realloc_target(
        target_or_reason_, s);
}

template<class Allocator>
inline
void
basic_fields<Allocator>::
set_reason_impl(string_view s)
{
    realloc_string(
        target_or_reason_, s);
}

template<class Allocator>
void
basic_fields<Allocator>::
set_chunked_impl(bool value)
{
    beast::detail::temporary_buffer buf;
    auto it = find(field::transfer_encoding);
    if(value)
    {
        // append "chunked"
        if(it == end())
        {
            set(field::transfer_encoding, "chunked");
            return;
        }
        auto const te = token_list{it->value()};
        for(auto itt = te.begin();;)
        {
            auto const next = std::next(itt);
            if(next == te.end())
            {
                if(beast::iequals(*itt, "chunked"))
                    return; // already set
                break;
            }
            itt = next;
        }

        buf.append(it->value(), ", chunked");
        set(field::transfer_encoding, buf.view());
        return;
    }
    // filter "chunked"
    if(it == end())
        return;

    detail::filter_token_list_last(buf, it->value(), {"chunked", {}});
    if(! buf.empty())
        set(field::transfer_encoding, buf.view());
    else
        erase(field::transfer_encoding);
}

template<class Allocator>
void
basic_fields<Allocator>::
set_content_length_impl(
    boost::optional<std::uint64_t> const& value)
{
    if(! value)
        erase(field::content_length);
    else
    {
        set(field::content_length,
            to_static_string(*value));
    }
}

template<class Allocator>
void
basic_fields<Allocator>::
set_keep_alive_impl(
    unsigned version, bool keep_alive)
{
    // VFALCO What about Proxy-Connection ?
    auto const value = (*this)[field::connection];
    beast::detail::temporary_buffer buf;
    detail::keep_alive_impl(buf, value, version, keep_alive);
    if(buf.empty())
        erase(field::connection);
    else
        set(field::connection, buf.view());
}

//------------------------------------------------------------------------------

template<class Allocator>
auto
basic_fields<Allocator>::
new_element(field name,
    string_view sname, string_view value) ->
        element&
{
    if(sname.size() + 2 >
            (std::numeric_limits<off_t>::max)())
        BOOST_THROW_EXCEPTION(std::length_error{
            "field name too large"});
    if(value.size() + 2 >
            (std::numeric_limits<off_t>::max)())
        BOOST_THROW_EXCEPTION(std::length_error{
            "field value too large"});
    value = detail::trim(value);
    std::uint16_t const off =
        static_cast<off_t>(sname.size() + 2);
    std::uint16_t const len =
        static_cast<off_t>(value.size());
    auto a = rebind_type{this->get()};
    auto const p = alloc_traits::allocate(a,
        (sizeof(element) + off + len + 2 + sizeof(align_type) - 1) /
            sizeof(align_type));
    return *(::new(p) element(name, sname, value));
}

template<class Allocator>
void
basic_fields<Allocator>::
delete_element(element& e)
{
    auto a = rebind_type{this->get()};
    auto const n =
        (sizeof(element) + e.off_ + e.len_ + 2 + sizeof(align_type) - 1) /
            sizeof(align_type);
    e.~element();
    alloc_traits::deallocate(a,
        reinterpret_cast<align_type*>(&e), n);
}

template<class Allocator>
void
basic_fields<Allocator>::
set_element(element& e)
{
    auto it = set_.lower_bound(
        e.name_string(), key_compare{});
    if(it == set_.end() || ! beast::iequals(
        e.name_string(), it->name_string()))
    {
        set_.insert_before(it, e);
        list_.push_back(e);
        return;
    }
    for(;;)
    {
        auto next = it;
        ++next;
        set_.erase(it);
        list_.erase(list_.iterator_to(*it));
        delete_element(*it);
        it = next;
        if(it == set_.end() ||
            ! beast::iequals(e.name_string(), it->name_string()))
            break;
    }
    set_.insert_before(it, e);
    list_.push_back(e);
}

template<class Allocator>
void
basic_fields<Allocator>::
realloc_string(string_view& dest, string_view s)
{
    if(dest.empty() && s.empty())
        return;
    auto a = typename beast::detail::allocator_traits<
        Allocator>::template rebind_alloc<
            char>(this->get());
    char* p = nullptr;
    if(! s.empty())
    {
        p = a.allocate(s.size());
        s.copy(p, s.size());
    }
    if(! dest.empty())
        a.deallocate(const_cast<char*>(
            dest.data()), dest.size());
    if(p)
        dest = {p, s.size()};
    else
        dest = {};
}

template<class Allocator>
void
basic_fields<Allocator>::
realloc_target(
    string_view& dest, string_view s)
{
    // The target string are stored with an
    // extra space at the beginning to help
    // the writer class.
    if(dest.empty() && s.empty())
        return;
    auto a = typename beast::detail::allocator_traits<
        Allocator>::template rebind_alloc<
            char>(this->get());
    char* p = nullptr;
    if(! s.empty())
    {
        p = a.allocate(1 + s.size());
        p[0] = ' ';
        s.copy(p + 1, s.size());
    }
    if(! dest.empty())
        a.deallocate(const_cast<char*>(
            dest.data()), dest.size());
    if(p)
        dest = {p, 1 + s.size()};
    else
        dest = {};
}

template<class Allocator>
template<class OtherAlloc>
void
basic_fields<Allocator>::
copy_all(basic_fields<OtherAlloc> const& other)
{
    for(auto const& e : other.list_)
        insert(e.name(), e.name_string(), e.value());
    realloc_string(method_, other.method_);
    realloc_string(target_or_reason_,
        other.target_or_reason_);
}

template<class Allocator>
void
basic_fields<Allocator>::
clear_all()
{
    clear();
    realloc_string(method_, {});
    realloc_string(target_or_reason_, {});
}

template<class Allocator>
void
basic_fields<Allocator>::
delete_list()
{
    for(auto it = list_.begin(); it != list_.end();)
        delete_element(*it++);
}

//------------------------------------------------------------------------------

template<class Allocator>
inline
void
basic_fields<Allocator>::
move_assign(basic_fields& other, std::true_type)
{
    clear_all();
    set_ = std::move(other.set_);
    list_ = std::move(other.list_);
    method_ = other.method_;
    target_or_reason_ = other.target_or_reason_;
    other.method_ = {};
    other.target_or_reason_ = {};
    this->get() = other.get();
}

template<class Allocator>
inline
void
basic_fields<Allocator>::
move_assign(basic_fields& other, std::false_type)
{
    clear_all();
    if(this->get() != other.get())
    {
        copy_all(other);
    }
    else
    {
        set_ = std::move(other.set_);
        list_ = std::move(other.list_);
        method_ = other.method_;
        target_or_reason_ = other.target_or_reason_;
        other.method_ = {};
        other.target_or_reason_ = {};
    }
}

template<class Allocator>
inline
void
basic_fields<Allocator>::
copy_assign(basic_fields const& other, std::true_type)
{
    clear_all();
    this->get() = other.get();
    copy_all(other);
}

template<class Allocator>
inline
void
basic_fields<Allocator>::
copy_assign(basic_fields const& other, std::false_type)
{
    clear_all();
    copy_all(other);
}

template<class Allocator>
inline
void
basic_fields<Allocator>::
swap(basic_fields& other, std::true_type)
{
    using std::swap;
    swap(this->get(), other.get());
    swap(set_, other.set_);
    swap(list_, other.list_);
    swap(method_, other.method_);
    swap(target_or_reason_, other.target_or_reason_);
}

template<class Allocator>
inline
void
basic_fields<Allocator>::
swap(basic_fields& other, std::false_type)
{
    BOOST_ASSERT(this->get() == other.get());
    using std::swap;
    swap(set_, other.set_);
    swap(list_, other.list_);
    swap(method_, other.method_);
    swap(target_or_reason_, other.target_or_reason_);
}

} // http
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/http/impl/fields.ipp>
#endif

#endif

/* fields.hpp
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
*/