//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_BUFFERS_CAT_HPP
#define BOOST_BEAST_IMPL_BUFFERS_CAT_HPP

#include <boost/beast/core/detail/tuple.hpp>
#include <boost/beast/core/detail/variant.hpp>
#include <boost/asio/buffer.hpp>
#include <cstdint>
#include <iterator>
#include <new>
#include <stdexcept>
#include <utility>

namespace boost {
namespace beast {

template<class Buffer>
class buffers_cat_view<Buffer>
{
    Buffer buffer_;
public:
    using value_type = buffers_type<Buffer>;

    using const_iterator = buffers_iterator_type<Buffer>;

    explicit
    buffers_cat_view(Buffer const& buffer)
        : buffer_(buffer)
    {
    }

    const_iterator
    begin() const
    {
        return net::buffer_sequence_begin(buffer_);
    }

    const_iterator
    end() const
    {
        return net::buffer_sequence_end(buffer_);
    }
};

#if defined(_MSC_VER) && ! defined(__clang__)
# define BOOST_BEAST_UNREACHABLE() __assume(false)
# define BOOST_BEAST_UNREACHABLE_RETURN(v) __assume(false)
#else
# define BOOST_BEAST_UNREACHABLE() __builtin_unreachable()
# define BOOST_BEAST_UNREACHABLE_RETURN(v) \
    do { __builtin_unreachable(); return v; } while(false)
#endif

#ifdef BOOST_BEAST_TESTS

#define BOOST_BEAST_LOGIC_ERROR(s) \
    do { \
        BOOST_THROW_EXCEPTION(std::logic_error((s))); \
        BOOST_BEAST_UNREACHABLE(); \
    } while(false)

#define BOOST_BEAST_LOGIC_ERROR_RETURN(v, s) \
    do { \
        BOOST_THROW_EXCEPTION(std::logic_error(s)); \
        BOOST_BEAST_UNREACHABLE_RETURN(v); \
    } while(false)

#else

#define BOOST_BEAST_LOGIC_ERROR(s) \
    do { \
        BOOST_ASSERT_MSG(false, s); \
        BOOST_BEAST_UNREACHABLE(); \
    } while(false)

#define BOOST_BEAST_LOGIC_ERROR_RETURN(v, s) \
    do { \
        BOOST_ASSERT_MSG(false, (s)); \
        BOOST_BEAST_UNREACHABLE_RETURN(v); \
    } while(false)

#endif

namespace detail {

struct buffers_cat_view_iterator_base
{
    struct past_end
    {
        char unused = 0; // make g++8 happy

        net::mutable_buffer
        operator*() const
        {
            BOOST_BEAST_LOGIC_ERROR_RETURN({},
                "Dereferencing a one-past-the-end iterator");
        }

        operator bool() const noexcept
        {
            return true;
        }
    };
};

} // detail

template<class... Bn>
class buffers_cat_view<Bn...>::const_iterator
    : private detail::buffers_cat_view_iterator_base
{
    // VFALCO The logic to skip empty sequences fails
    //        if there is just one buffer in the list.
    static_assert(sizeof...(Bn) >= 2,
        "A minimum of two sequences are required");

    detail::tuple<Bn...> const* bn_ = nullptr;
    detail::variant<
        buffers_iterator_type<Bn>..., past_end> it_{};

    friend class buffers_cat_view<Bn...>;

    template<std::size_t I>
    using C = std::integral_constant<std::size_t, I>;

public:
    using value_type = typename
        buffers_cat_view<Bn...>::value_type;
    using pointer = value_type const*;
    using reference = value_type;
    using difference_type = std::ptrdiff_t;
    using iterator_category =
        std::bidirectional_iterator_tag;

    const_iterator() = default;
    const_iterator(const_iterator const& other) = default;
    const_iterator& operator=(
        const_iterator const& other) = default;

    bool
    operator==(const_iterator const& other) const;

    bool
    operator!=(const_iterator const& other) const
    {
        return ! (*this == other);
    }

    reference
    operator*() const;

    pointer
    operator->() const = delete;

    const_iterator&
    operator++();

    const_iterator
    operator++(int);

    const_iterator&
    operator--();

    const_iterator
    operator--(int);

private:
    const_iterator(
        detail::tuple<Bn...> const& bn,
        std::true_type);

    const_iterator(
        detail::tuple<Bn...> const& bn,
        std::false_type);

    struct dereference
    {
        const_iterator const& self;

        reference
        operator()(mp11::mp_size_t<0>)
        {
            BOOST_BEAST_LOGIC_ERROR_RETURN({},
                "Dereferencing a default-constructed iterator");
        }

        template<class I>
        reference operator()(I)
        {
            return *self.it_.template get<I::value>();
        }
    };

    struct increment
    {
        const_iterator& self;

        void
        operator()(mp11::mp_size_t<0>)
        {
            BOOST_BEAST_LOGIC_ERROR(
                "Incrementing a default-constructed iterator");
        }

        template<std::size_t I>
        void
        operator()(mp11::mp_size_t<I>)
        {
            ++self.it_.template get<I>();
            next(mp11::mp_size_t<I>{});
        }

        template<std::size_t I>
        void
        next(mp11::mp_size_t<I>)
        {
            auto& it = self.it_.template get<I>();
            for(;;)
            {
                if (it == net::buffer_sequence_end(
                        detail::get<I-1>(*self.bn_)))
                    break;
                if(net::const_buffer(*it).size() > 0)
                    return;
                ++it;
            }
            self.it_.template emplace<I+1>(
                net::buffer_sequence_begin(
                    detail::get<I>(*self.bn_)));
            next(mp11::mp_size_t<I+1>{});
        }

        void
        operator()(mp11::mp_size_t<sizeof...(Bn)>)
        {
            auto constexpr I = sizeof...(Bn);
            ++self.it_.template get<I>();
            next(mp11::mp_size_t<I>{});
        }

        void
        next(mp11::mp_size_t<sizeof...(Bn)>)
        {
            auto constexpr I = sizeof...(Bn);
            auto& it = self.it_.template get<I>();
            for(;;)
            {
                if (it == net::buffer_sequence_end(
                        detail::get<I-1>(*self.bn_)))
                    break;
                if(net::const_buffer(*it).size() > 0)
                    return;
                ++it;
            }
            // end
            self.it_.template emplace<I+1>();
        }

        void
        operator()(mp11::mp_size_t<sizeof...(Bn)+1>)
        {
            BOOST_BEAST_LOGIC_ERROR(
                "Incrementing a one-past-the-end iterator");
        }
    };

    struct decrement
    {
        const_iterator& self;

        void
        operator()(mp11::mp_size_t<0>)
        {
            BOOST_BEAST_LOGIC_ERROR(
                "Decrementing a default-constructed iterator");
        }

        void
        operator()(mp11::mp_size_t<1>)
        {
            auto constexpr I = 1;

            auto& it = self.it_.template get<I>();
            for(;;)
            {
                if(it == net::buffer_sequence_begin(
                    detail::get<I-1>(*self.bn_)))
                {
                    BOOST_BEAST_LOGIC_ERROR(
                        "Decrementing an iterator to the beginning");
                }
                --it;
                if(net::const_buffer(*it).size() > 0)
                    return;
            }
        }

        template<std::size_t I>
        void
        operator()(mp11::mp_size_t<I>)
        {
            auto& it = self.it_.template get<I>();
            for(;;)
            {
                if(it == net::buffer_sequence_begin(
                        detail::get<I-1>(*self.bn_)))
                    break;
                --it;
                if(net::const_buffer(*it).size() > 0)
                    return;
            }
            self.it_.template emplace<I-1>(
                net::buffer_sequence_end(
                    detail::get<I-2>(*self.bn_)));
            (*this)(mp11::mp_size_t<I-1>{});
        }

        void
        operator()(mp11::mp_size_t<sizeof...(Bn)+1>)
        {
            auto constexpr I = sizeof...(Bn)+1;
            self.it_.template emplace<I-1>(
                net::buffer_sequence_end(
                    detail::get<I-2>(*self.bn_)));
            (*this)(mp11::mp_size_t<I-1>{});
        }
    };
};

//------------------------------------------------------------------------------

template<class... Bn>
buffers_cat_view<Bn...>::
const_iterator::
const_iterator(
    detail::tuple<Bn...> const& bn,
    std::true_type)
    : bn_(&bn)
{
    // one past the end
    it_.template emplace<sizeof...(Bn)+1>();
}

template<class... Bn>
buffers_cat_view<Bn...>::
const_iterator::
const_iterator(
    detail::tuple<Bn...> const& bn,
    std::false_type)
    : bn_(&bn)
{
    it_.template emplace<1>(
        net::buffer_sequence_begin(
            detail::get<0>(*bn_)));
    increment{*this}.next(
        mp11::mp_size_t<1>{});
}

template<class... Bn>
bool
buffers_cat_view<Bn...>::
const_iterator::
operator==(const_iterator const& other) const
{
    return bn_ == other.bn_ && it_ == other.it_;
}

template<class... Bn>
auto
buffers_cat_view<Bn...>::
const_iterator::
operator*() const ->
    reference
{
    return mp11::mp_with_index<
        sizeof...(Bn) + 2>(
            it_.index(),
            dereference{*this});
}

template<class... Bn>
auto
buffers_cat_view<Bn...>::
const_iterator::
operator++() ->
    const_iterator&
{
    mp11::mp_with_index<
        sizeof...(Bn) + 2>(
            it_.index(),
            increment{*this});
    return *this;
}

template<class... Bn>
auto
buffers_cat_view<Bn...>::
const_iterator::
operator++(int) ->
    const_iterator
{
    auto temp = *this;
    ++(*this);
    return temp;
}

template<class... Bn>
auto
buffers_cat_view<Bn...>::
const_iterator::
operator--() ->
    const_iterator&
{
    mp11::mp_with_index<
        sizeof...(Bn) + 2>(
            it_.index(),
            decrement{*this});
    return *this;
}

template<class... Bn>
auto
buffers_cat_view<Bn...>::
const_iterator::
operator--(int) ->
    const_iterator
{
    auto temp = *this;
    --(*this);
    return temp;
}

//------------------------------------------------------------------------------

template<class... Bn>
buffers_cat_view<Bn...>::
buffers_cat_view(Bn const&... bn)
    : bn_(bn...)
{
}


template<class... Bn>
auto
buffers_cat_view<Bn...>::begin() const ->
    const_iterator
{
    return const_iterator{bn_, std::false_type{}};
}

template<class... Bn>
auto
buffers_cat_view<Bn...>::end() const->
    const_iterator
{
    return const_iterator{bn_, std::true_type{}};
}

} // beast
} // boost

#endif

/* buffers_cat.hpp
u7exxvOduquc4a/y4cWUZubWxkDTbp3q2pgaSyVlaNq8kx/LWF3fzkAXJU/RtLNFGt6anbzZx8SR34Mu4C/4fhZmhviSNPLX4uSP4+IIfJGmW5e8nxNpADGX/fQJfD+XhvEl/TM6anlJ3d5P0lQyjt1FF5jxDN37yfyZak/SKxL3Ma7o1Xu2ph/4S++6vr3tfPe+vYqG/rXcczidOvFf4NRJXbt9VoCml9obeLrEJ2N3c7xOL6TJUj4gTpX4gdix3N3SPx2h+q5LJX2orT9a3IX9UbANj6O9+tV4yEZEtGEYBTn1QnnYhq0+OKAT5i/Dzsrear/gWXJvK9iG9RO6VHlijew0VONjyZOgzi15RuI5of0T3Oc+iP12uqSf490N/49DOAWhCeFyhAUIbyKYewr9qO/iLNkHDj8IG9n28P4EXX6PdvdlWjT6TAl8c16E51rizY74ugvt8S9UPD79lsDfeeP2HSnxa1W8QOKXqPj2Ej9LxbeT+AEqvq3Ex6r4CNqGq/4AdWLfazs3O7RfLJVt/9K++F69JFS/7ER0Y2jm7S3pufJdVNNQr76HbOn0+V+p9v4XOdLRziW9iumVKj2z3T6Asob7YQDmyjcS+OK9QuXDX3hRe+7wfLlXRb8M0+XZMNNx9BdFvVzmgKG3xpDexo/WzP9elOnUIen043akd2z+96LM9sftar83ZeGnldhqjoEOm8JkgT8DyvBWuAzMnxI1jyjDdf6mPid8PuLaPninXPjh966OJ9B07Ptax1NS73Ce9jDHtE6e5AgpHwrQ89TSRTy19nb5FkYbXGrlyf5Nr2l/pNF/0yM9unFRR9pf8F26vk+4bk/uC/lc5Wjwo8rLfdOqdbKQLl7GU69JeoDGuhextYN1YJFH7VN+Te6psm0y+TcJ7x8GmutqNpmc3/X6NtMWuX9Aese+69+Kon6C7Syub3j9jBuMuQSnLFHUzepO6N3K0/y+4W1/LzFOtvDk+A53+qshT6DpWNtWvl0cv6V5m4bzNB56SrPxJPrV8pLWSV6CffqUXPpmR8jmePbEgfgdtPEyo7y+wlfW4HfRDcdbe0r+MeSP9OLbanz6gE0hM54zAZiS2Ds5Rdx1eVO6eUM+VL5OM2y+X2SYyPJ7AkdLeeOZJ+jvQnKpb/EdJc+hwuMVMgAgjxwjTpL0UWovcG4UYwSd3tbmhu9NfwLPXBquN9mYSZ6c9Yj8f35vOsojb/b5wgv7ubf51WG82RZCpfnr2tvqTra3YH83ZLPwPmLfweZg0o035TtGxxfoOtZPKL4c/cRSF772M99JDV81/jn6d7OLeJq4eThPReApV8MTXDdoecrtJE/B+vvChaf9wVO+O0/TzNUpfZ8Kui7ia26ee59aqOGLv6M6vkDXufYerMPs/u7tvcidr0p46NTyVNRJXQXXvZb0d+8finU8+RvqAz+R0kVo+SvupM5GBdv9Fu78+d35qy2va6iq90Xmzd9J3lT73yK8PieYB76488ZBn56vxk7WafD3KIU/GLvx23w7hDbcawrnC04N9L+1KJ40PdXv6kKJD9T+9mYqmo3VvNMNEt9C+1v8APOr3//IcyhWvwkcf5Jv3i9Q9xVvtja1ckD4Wu8HuLc6XD919t9E7W83aTew6EWRUC8qT9T1a/1Nz7KNt1m2Yx1gyUApA3oMyfexKetlbnKp31OdTKTrLjK9IuNykqhvIpWnUzKhbNxj2Y4+s3FQuEwTzd9ijUz4LdbJQ5rukv6uyCPZlSxpnZAl+D30rsgi5drkGDs4XI4DcS9XIwd+vzVykIZyvC9ySHYlR24XyPG+yCHl2tpYjyHhcnwG+nxXOdRvvkYW0lGWN0QWIVE=
*/