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
#include <boost/beast/core/detail/temporary_buffer.hpp>
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
insert(field name, string_param const& value)
{
    BOOST_ASSERT(name != field::unknown);
    insert(name, to_string(name), value);
}

template<class Allocator>
void
basic_fields<Allocator>::
insert(string_view sname, string_param const& value)
{
    auto const name =
        string_to_field(sname);
    insert(name, sname, value);
}

template<class Allocator>
void
basic_fields<Allocator>::
insert(field name,
    string_view sname, string_param const& value)
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
set(field name, string_param const& value)
{
    BOOST_ASSERT(name != field::unknown);
    set_element(new_element(name, to_string(name),
        static_cast<string_view>(value)));
}

template<class Allocator>
void
basic_fields<Allocator>::
set(string_view sname, string_param const& value)
{
    set_element(new_element(
        string_to_field(sname), sname,
            static_cast<string_view>(value)));
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
        set(field::content_length, *value);
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