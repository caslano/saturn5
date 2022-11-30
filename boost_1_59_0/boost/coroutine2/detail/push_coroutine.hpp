
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_PUSH_COROUTINE_HPP
#define BOOST_COROUTINES2_DETAIL_PUSH_COROUTINE_HPP

#include <iterator>
#include <type_traits>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/coroutine2/detail/config.hpp>
#include <boost/coroutine2/detail/disable_overload.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename T >
class push_coroutine {
private:
    template< typename X >
    friend class pull_coroutine;

    struct control_block;

    control_block   *   cb_;

    explicit push_coroutine( control_block *) noexcept;

public:
    template< typename Fn,
              typename = detail::disable_overload< push_coroutine, Fn >
    >
    explicit push_coroutine( Fn &&);

    template< typename StackAllocator, typename Fn >
    push_coroutine( StackAllocator &&, Fn &&);

    ~push_coroutine();

    push_coroutine( push_coroutine const&) = delete;
    push_coroutine & operator=( push_coroutine const&) = delete;

    push_coroutine( push_coroutine &&) noexcept;

    push_coroutine & operator=( push_coroutine && other) noexcept {
        if ( this == & other) return * this;
        std::swap( cb_, other.cb_);
        return * this;
    }

    push_coroutine & operator()( T const&);

    push_coroutine & operator()( T &&);

    explicit operator bool() const noexcept;

    bool operator!() const noexcept;

    class iterator {
    private:
        push_coroutine< T > *   c_{ nullptr };

    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        iterator() noexcept = default;

        explicit iterator( push_coroutine< T > * c) noexcept :
            c_{ c } {
        }

        iterator & operator=( T t) {
            BOOST_ASSERT( nullptr != c_);
            if ( ! ( * c_)( t) ) {
                c_ = nullptr;
            }
            return * this;
        }

        bool operator==( iterator const& other) const noexcept {
            return other.c_ == c_;
        }

        bool operator!=( iterator const& other) const noexcept {
            return other.c_ != c_;
        }

        iterator & operator*() noexcept {
            return * this;
        }

        iterator & operator++() noexcept {
            return * this;
        }
    };
};

template< typename T >
class push_coroutine< T & > {
private:
    template< typename X >
    friend class pull_coroutine;

    struct control_block;

    control_block   *   cb_;

    explicit push_coroutine( control_block *) noexcept;

public:
    template< typename Fn,
              typename = detail::disable_overload< push_coroutine, Fn >
    >
    explicit push_coroutine( Fn &&);

    template< typename StackAllocator, typename Fn >
    push_coroutine( StackAllocator &&, Fn &&);

    ~push_coroutine();

    push_coroutine( push_coroutine const&) = delete;
    push_coroutine & operator=( push_coroutine const&) = delete;

    push_coroutine( push_coroutine &&) noexcept;

    push_coroutine & operator=( push_coroutine && other) noexcept {
        if ( this == & other) return * this;
        std::swap( cb_, other.cb_);
        return * this;
    }

    push_coroutine & operator()( T &);

    explicit operator bool() const noexcept;

    bool operator!() const noexcept;

    class iterator {
    private:
        push_coroutine< T & >   *   c_{ nullptr };

    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        iterator() noexcept = default;

        explicit iterator( push_coroutine< T & > * c) noexcept :
            c_{ c } {
        }

        iterator & operator=( T & t) {
            BOOST_ASSERT( nullptr != c_);
            if ( ! ( * c_)( t) ) {
                c_ = nullptr;
            }
            return * this;
        }

        bool operator==( iterator const& other) const noexcept {
            return other.c_ == c_;
        }

        bool operator!=( iterator const& other) const noexcept {
            return other.c_ != c_;
        }

        iterator & operator*() noexcept {
            return * this;
        }

        iterator & operator++() noexcept {
            return * this;
        }
    };
};

template<>
class push_coroutine< void > {
private:
    template< typename X >
    friend class pull_coroutine;

    struct control_block;

    control_block   *   cb_;

    explicit push_coroutine( control_block *) noexcept;

public:
    template< typename Fn,
              typename = detail::disable_overload< push_coroutine, Fn >
    >
    explicit push_coroutine( Fn &&);

    template< typename StackAllocator, typename Fn >
    push_coroutine( StackAllocator &&, Fn &&);

    ~push_coroutine();

    push_coroutine( push_coroutine const&) = delete;
    push_coroutine & operator=( push_coroutine const&) = delete;

    push_coroutine( push_coroutine &&) noexcept;

    push_coroutine & operator=( push_coroutine && other) noexcept {
        if ( this == & other) return * this;
        std::swap( cb_, other.cb_);
        return * this;
    }

    push_coroutine & operator()();

    explicit operator bool() const noexcept;

    bool operator!() const noexcept;
};

template< typename T >
typename push_coroutine< T >::iterator
begin( push_coroutine< T > & c) {
    return typename push_coroutine< T >::iterator( & c);
}

template< typename T >
typename push_coroutine< T >::iterator
end( push_coroutine< T > &) {
    return typename push_coroutine< T >::iterator();
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_PUSH_COROUTINE_HPP

/* push_coroutine.hpp
eUOrZO+vmK5VtjmOnM6thZe2uFC2/khC5pSsEYpQ9it+7Tq5wXhq8gy9KiGHQBnGhV8IpzlyEYQq7mMXdeWCeOjZ2XNpLt6qDwwiwoIhoBSPEmwhc5eS0ei9lYXZRvyJftNBQeNkcdZ1CZYMfwvqCwy/oUb6IS+VHmHkYqq7hAZvFMNOS9+sAZL2iuBhIyuzJhfySR2F265Z24ekDO0KZxpIx8ZFI9yOFqpGWM2ms0KSs06Hvv+c3HysExRoHLIdGwL7lB+XbGirB+zNa5gvwVYUAK2kkSsVKp5KuFEKa4mA0qdiCeFFZtpuo4iPWwHAwJlSetMS/bmfou2Ztkptgw9IcXF0K3RtD09o3E4KoS9t78HQdopnhrfqk738vRGGQY8G4WW35RQGf9NxeIiYus1n+IYOYCb8IqzNuE8duF2HB2S6o2iPoh7yXt8aSxjcYq+Z051CZZxhCnfSdz0IOMG/UKh3ZIWYpo5HFBbx+UwEqkGRDz3rZ6BQR+/lbeN/P82NDyRB/6rHVz3qb9w2dSnSiz1YBfHjiPlfkFzDFeziRtzyuqL0kE1G9nUUP3FW0L9rc9+e1kMHfuDL1A3+H/WsjTQb0yVBxBbCzQSUCiSN7iydNVdikPGTUrUAjtbvTfa8XvaXhRcloxlYQUDRCRvrI94yjSi0xBPYzgt3HZK5dBlJG8jqjjDwrZrp1tN1HRzrMsaglV0jolAFLa9tyZ0UzikP5xVFNeLpHSaxTdMPRNa3hchJV+QQMHgRf5NbfMjL+5QGnwpqximGWmdYslUadJ9DF9TJj8mULqM23pXY5Jj2NqjXuSxRDP++jO1+6zCsFBvzSpy3rHYx/VOTDTcbAk08ft+UFTMsLJo8+Kp1AKSNQfqFGUH4DgeX0a6hC3Ec/PMuc6w4i/iVprGsHQHKwTXQkA/WDdRRG2chucQ8J60TI+YjeltrX6nFLE7B0/CwkmOvxRJQQ0k29pQX7rqJijQO8ftuxR0Oil3R5Va7XLTNQB2UnDhnfpFf3z6DR8q9kpCw5otoK/RYRo5zdu7gvZ8UaeUjqgRDgas74cl4swVwMMisZ6mG1QDgpPpfZDOUgGCewz2gFB6rGm1pc1aWQkNWyiFKUzn9uI1N08uxxKNKfrLUVGqNwyLLcDECQ3dReKnWN2F+KAztYOzg77ASvS0krgATTz2jA8XKm6CiBVcTqVxpTfjVSZJ3e05sWkBWCsW0YgqlpzvMekHjxT1VHZRhYBHByYKhKcaTk/x2EKP6JNXBlz31+HNz+Ce54Uku7BSZ1B7+Wc7xECaLcDavDevLD2NFiqJMGqJiSo72XUeLnkwWNwuVadOCfzuAA1jG9eVSVOLIxHa6RUKf4osf/XBmDeiyqKx6Cc8gjm2W69qeO+GdFVjW4IWEoelgKDUvQtVZn8OfTzYJKeCIoghdJE5muSXWC5o8uy42LLUR+Fi8hICyK/uDLxMI/X7d49rHx3hvo1CxfXWt6g8bybwGKiLzVFu940yJ2lWB6YJC3zoEbNZ1d1zJHiHiJicN/e6KDgtIGqrzUCQEV2ESXVXaHTZz+smg3SEKot2mffQfyRMkJwXfFTrQY2+kwBaSSDc0ylVyqbFZN0nIze4bHDL32uZDH6VL+RW+eHeTrNmv1S4Hkc7l+GsfToOl24BIPHYg1fEuttw9KFvvRXB1Uu0YA0wbp4GuTVLzabwJEc5rLCO2CBD718Zrw3Cwmh1hkNIMaBP/9UL5klNNRFRdawD8rOdUZn+9e1bSfTy6hHt2rbrWPKY5TM0mshXuGM1/J7GLXZ9i8xI2GD2K0UuZ2M40Ou4ha/hn+F2o0W0WLQ82c/dWaqAhMIHuLsgAOC96hOeZiJ7tRJM4UYExVdyX8AFM2GXxYOkbZcX/Z8C4XrNNs2Qe7G7vcnfJnfFv30X2l3AaH3DiSZo7Dc7T8dQyhKNf2tWgYzQwqtkJZGGbnN1aBcENIvVcfitlNcZVOURrmoKcn8tmEtewARsre/WuQlLzHAoLJxTB1svHBHCFmSk2DaSym5HI3M22hUZ9QJA7aOexeOoJzu/jvuzhd9ZPTBb754HtiyvZzy/kaZLvR+PnV+0dSOQXd59Ey280lRA8WQrnp5P5IKz399zrPa73tx9P5yGv/YvvN9APP+/nCern9x3r5zfl51B6iIX3qw/v57vq65su9rP3YbXPBx7QFS929KESr9AO3Dxa/LNisMGlLvU/nUd8ZzKSL/urG8GTkwmqzbAiazN2fMU1qBVVNB0BLu4wEnsgVyFm6Ne2+rIJ9G/WEP/h1Ik73MrjfH5mV6W+rgLggbD3RO7g7UoR3bo6S2kMBi0l3Nzhxte+osyHQR5rhNBSO/Gxt13WykDCjkrgAfF7ZGIlA9Hmutrwh+Ay1SiqCB8qyt1A0UowZLAL/h6QGZO94n00K9MGKfKKAkBKyH0XGjcSgFz7gZ1n8bA0yuxW6tDKrJ2rYUMoGnvmJD2CrmFQgd2jNH9rocT9cexuCpVTz7QBGs5zsF418v82l6mTea3TUlcZZ6xSZzAyUBPBw/yFXIhKwEljdEUJ8RLrO3UnEkR8EeYvBs5TAPNiKBdYJNfDRNb3C5WIxFOuB/YJrUTCGD/CCBu/XA8ZmlI0ACIOwvf9L+N19YFd2hPhQHbDlBGuOqrjeyU6nzdrtymLCKPP4XhW9Nelr+bIzt/wQTq1gnRyrEnbZNUN/lP6gLRohEN/mrcD6+0JC2gjTdm1Rdk+L4BWoO1hFa9/CipKHgFn4cmqr1xlE7HUVqJvXR936YViKrF1kIj79ElyaNZ3xKg9TW7AdntEoMEZTn6g1FTUvfSyMYLmATNcB8rQRYgWaCBqcP/E0DD/bym3TlZdJ0eBZEtvaPLxNHlV90DOp7CtpPD+Xy87QtUtfZepQ6VJ46OmFLLCxFriKHnad/08K0/mVFhHxZKBeFJyScmy3ua+SV9dR2VayuDYC8ASp0DubJA0FAYo3S3+PwiEMq6cLKbjmrc1dydGzSHZHva9yDWU+hT2aJ018qEx3ndzBLeE+WsRK+z71NsirZ0k6k05jZk7Qt53rdSZlpRWoIcRTMWU7UNydNd89fdI/H/Rua0EvKbDFq8CP6vvbo4oJYPV+Ca62PjKXDIIlRay+/+55AOWS6FRTqp0Qk3r+iWMGqlfegHhlBIGoIRMmCkqwwcMG1Z2CiYB00GBouV5BuikxodEcz8uMPBSFlmkcWo8QeXkWSSyahO1zs/LH3cSyW19RWrZKA1IcyP+N2IDCi8RWOnlEi6qvSfBM//tlTsIZLsYyPBmrkIGo2022sHDYqhQnZ9xYqphPFFAfIDol1E/8ORuTiSSAGree0axQAe+cAqHMmYv4d2SZb3u8MVT6ik1FU3ti1n4nnUqOk0ZYi7ni0kwDvcwSiKI7id6ECh221JsHojykyH6QRlxjhDQ8liqb2vxfe7/n50i4UlTGsjaRe10pe1xzN0DF9F/n71l1dpQHVjZoJw7S+x2u9nOl4b1nMErWpf//Tuuqd3xdUA8OQy82fYseXvkp1AezzCdiVniLlDmoXodrgTarPo1BAtPvMw/9E593DSp1KuTlsvaIvnGz/AJYweXI6RH/a9oxR1+9hgonpiddqextESrTXn9ONrsnHVIFkp+Cd57QtXPKqAeCUnlS8DzoOJ81f5EmGF/8mr6hRrVkslss7ASwZXoN2BuZ6TTAhLQoyXKZ2OWuWF0xdAKSnTbKUV+GlwAdvvCKBvyPv0SeKrSRVOT5G7lUq75o4FZVYeN90bCL6t6Xhz2LheoKQcO+mQd8lBekvqXjkcILCiaImbhfsX4nD09yzyNWGLJA1TKeKyrQhOsJOTtPASwvKmCrkC+L8CgSgSg/C1ALmeaVj3XAPe7frAx+2vw7I0f2ICzgJLlkNdDdQH5lRkP43o4hLP7ccG3OJETWb40k4QyDYvqbmrpxzQ7Zrsw8f26vdMKgxL7slN3F16Ras1OA/A9ExyYxuQqDtLSvIT9SpLYUJiY5J7BOZBGGadrZF1RwG5aE0+icq1PWepMlFSHiMnUB2uUU2jYbypOTlmmehMxY/Nz7vbhJTV0p+5xa+MenixBhUb0gBZO/7jBw2LEnJkVcUoZd54/16RMGcZtZkIw0m4P0thicFLcrtWssxh/xB0XLDfE08pjgyIpuN3gy4T+2J1Z7IPJ3wOd9UH34PTxk2wTEjYZiwct8tYnZZygvsSQOggXTIlNGlw/ci1/v17LbSOzX8/fgcewxgIa7kLG6N5/fjJSsRLecYL0RpRGy8+OBjX8Pg+3pWZh3BTlEqqql+AxJQqtbNxJoSv35QikUQVWImcXlNG6tPOt8VXnZutSQSnDw2A2nGUskHCNjfxcUJf62gPkEjUtskEzSTKhHDZgtoNejXZqb1moJRT0n+rQKoCGn8aO8zbWFbBYarEc0t5ymsEZ10Ij88W//gwJrYoayoxo7rpWXtpBYUOBYpPLfDnVxtYSW08YKm0bT5wexeJe6sFqYwWRSsNGTu+gRT464zylSq+28iwuSe45XBOykMeKVWuTAyBel9qNwFazBerLLRvFVULwJgM84CY7n1YmrLJK8yomWAScOyON7uH5YKMm1m3+aZHp05tCrP0cke/7hOb5Y4BBdoH1jOndXh6V6k0ibxm/cc3ZIghuOB2+AXXZJF39a0W8mxqEcFm2VJDyYeluzonB+S0FUwtskTcfiJIXbZbewOp4oNdrSxLyqzsVe+t9KWJvFEOmYdAosgS/QpcWQ601CS/oVI3gzco1X0SF5XAnNlbPO3MYgklCWZtEBtoYe58Z2zcJp+JPDpIcqSsIHkHsg/Df+zpxjkZb/cONOoJZrX66ZrfboTSR4JLy2v4bM+ZfFPqyloSG2by1BkBi5i7OW7P2SpnQwzl8yOO46jW8TAwdYEr00uhTYiuNvn+SWv+JDnT2y+07al5jOCqBzJWjQ8r8Oz916XFBk0uFIWBp139zHq9tNoHivv+k8iTU5vDzUDWhly9RLuofi3Jc45zgvG5r1euVRuJJJ7NpqCCsT3ZsKs9TIzLJy21VTvst/mW8C+QjWkvR4AIqzNV4uMH/wk06G2HwaVTRASklF9txKz1vtz+Hn5GcFHnRQaY4v7VnpSh3jbFYs2cm9O3bWtD/ICC0iUBu1KUS5OniGlfRM27rM6AUkqb4eHg6ImRb0VvDCy5EpOHEaAnXmfNcxC08gPR/dP1AXa3/laUtQ23+rwTZIObic1dUqNPB38lhSLVpVLYp6g2kZ/x4Pp0cwzLjILqlQDCkhaD0Bs+AI6M8ngbarqSE4jHAnYsga1KoXZXAbfSo3c1ilNMoCstfZeRL9Vk/MBXBKy00LDIrU0kEBEe5LminR+HAkrep10LxLuBSXkB7lMpdI1GncWxpM4lp87x/nfH36CwNxcoBJ3hjRgBlmY3tgUJJUs2tAXMbTsfHr1qn8VfRx9NoieOizW8QikZGDjjXMcspWxNYdlau/r8mTMjJngfvjRaO9UxRZKdCqZ0DjsWFnx6iMfhvJgYWcFEhueI8MpnC2RUjKatpIqiAdItQBr08g2btlkjhmg4dm7GN05Uwd8B6prvyQdPDoaMSzukHb66JC4v2b9YMqb1BZY7/5N0x5Pdir1XUSNSF9hXyRVznUwUgfF60+7r+webG7NdZzWVmCWDXo1YcXQe6m268KNTKthKKJPSzlwZ3DQJvwioxyajX0Qx32Y394lyDQlDs2MvYxBZSm8gWFzmqJQmvlTj1lCZZcqA05tAYRGovSTRkbS3LA5yjViUITv5HaM6Tp0BB7ZaYShRi5hepD93X2TFegyBu28qSwTPA7MEldaN4Q2dXy4dWmlEtITN6qWqRfSLT6U+Y0uB0ab5VWFoL75SERtPWa3cwDG7YNkSQuC+nJCfL8Bg6vo0Zqf3p+/Vzi5gOByuNIzK3EM74oQktcdOWH9/s/TJ4TIbU7c+YOa5mJt5jgBPteqfsA45IARsji10e8PNZvopZqERL6DrRVeKiFIeT+qSvTBNv/ZpY0pYkA9jwHyJtStXlWNvDiHpHzLetpofgnDPcFH77ILJh4uoZbZLMUBqvm1O7FabtVteEvm9GQgA6Iu+50ozKbrX9PEALb+P9dWRm5asSpxFat2US0OVtmTa9okHiRCmvtJoMNQxdr10PJBwm0KiKriJCWc1Xb8UnQ/soNdFw+w1a+8ThrxpEAmycWTALr7CKEV6jQmnCmRkkyRqglo/sw/Vgorybj+i7yVc/KWZgCGX3BiXP5LVx/1jIeSAJLhOXCpkr0mstLny5h+h1HA0ngF1DI3ysB9nbIvk/yYpaVfZq5dxxtL7Fdilykd0TjwDfW4vz6t3dtpwXpo54ZVCc8WUtgn1RrVVWLGv1BUdkvn0xOxoKGmQYafzx3qHd5gcEFCaRu0CcSF8vkzRRaPjwJNWXUaXh9pHtDDmOK4jUflkPqBPi5eJIJKgQ8THBl9hKuhYvrVNKSmeAgSW6+mvnNKgQiMd+9f6cG0TQidZggXZkX126iv3y8h4MpOpVG9+L/KqunIzSVLAe483HEvorPuXIlxWvEmNFNlrOYwzDuUiE9BwSUCdWBUVkWYOghognblUTlO9w88cWAxNxDuUMg2WJeZrhXolGZOvA459yw7EH7y9hn0WwHNkYt2rASTGs64kB6ktXHNctKSUlN685i/3IyVZQOT7KTLGH1fhRJeUJSmqcYzkl15Xi6fWYUp/6K6tK2fbzqX4tIslOFZIECnflf25K7QMwj60ry+HStComg3dUhNV3fgE1AvSmDnUnCTRAiywr7HIVm7L7diorBjWFbHqsrgFmQyX0Q6VwqgsxOeOrrFkHq9E56xE3M3eOt6bSvU7f6NgT9xQDlP+CGpLUSEagvC1gdZYQLBXJywSXViIT8Db3kbOAGOEF+6rf/jvpHoR3/XC7L8rOyqMUee7df/G2dZulhMiQca8M2yPOiOL2qbJw7cRid6LpH6rXEb5aSkMsYpgosJnoHW7FUOgWoZF//37PPihKS3kxa5H58TcKgudISWpNclYBbM5yLA+Lvf7eUSF/F5JTHX88FYhK1PUy7i0s8+VYWy+Lx/Jhkvti7HAGL7uQ8uU05AP7ukjnwpby9UHRKq1U14GMNT5z5B+J42ypeu71z9vxLCMhsYSQUc9VfLP9b7+zRCP6q/ICe919nyNEFBR/TEblaSKamhdQfzucU2UbX4wlF/6TrTRSSU8qXUQIe/294zwUxfdzpa8ljVYDFn4DpWNAhiDJ8R+/TNTx246uxtjGhPVsVAHGmU1snPycQ5CD1PR9z1PlSkDP/JXstVfvskSGGXUB3ZT91SmabuuhLkjXgLFFeBDJCB9h4O8vyxas9i70t5jODhAORbuxKPq5ltWlpvj6a67gUorImDqjJNgPIu1iv0THxjClk4dW5SnIMrWV+Ta/z/y+KKcjg9z+RzV07GDqcmZrTZW0W1LvDA5SLqZD3Da2CdE7mgXUbDxtadWSsbov3xW7ZmBtbuq6rcXyevDiUUblblM/lwxBHcZucWVjQmS0nT+PfpKO0wFh3Jo4V0v8jcZH7dliGfl3xm1pbLoBpubml4p8C+R/YuS6k+NUkoehZlRX
*/