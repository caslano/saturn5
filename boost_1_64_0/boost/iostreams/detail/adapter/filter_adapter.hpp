/*
 * Defines the class template boost::iostreams::detail::filter_adapter,
 * a convenience base class for filter adapters.
 *
 * File:        boost/iostreams/detail/adapter/filter_adapter.hpp
 * Date:        Mon Nov 26 14:35:48 MST 2007
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_FILTER_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FILTER_ADAPTER_HPP_INCLUDED

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
class filter_adapter {
private:
    typedef typename detail::value_type<T>::type value_type;
    typedef typename detail::param_type<T>::type param_type;
public:
    explicit filter_adapter(param_type t) : t_(t) { }
    T& component() { return t_; }

    template<typename Device>
    void close(Device& dev) 
    { 
        detail::close_all(t_, dev); 
    }

    template<typename Device>
    void close(Device& dev, BOOST_IOS::openmode which) 
    { 
        iostreams::close(t_, dev, which); 
    }

    template<typename Device>
    void flush(Device& dev) 
    { 
        return iostreams::flush(t_, dev); 
    }

    template<typename Locale> // Avoid dependency on <locale>
    void imbue(const Locale& loc) { iostreams::imbue(t_, loc); }

    std::streamsize optimal_buffer_size() const 
    { return iostreams::optimal_buffer_size(t_); }
public:
    value_type t_;
};

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FILTER_ADAPTER_HPP_INCLUDED

/* filter_adapter.hpp
V7vNVDrtA9eQ8uIa5L/JxpJ7Tarkrbgn6DAlHz22l8b7pG2i2BzeBh+gbVa/ZGqbhIGO1KP6tillPeAV1TZN81iEF7Y96jVG+S/710KlU7aGNkoYxjYq10dHXb+tqc3iN3yb1XsD1PXjTW0Y/5G34f+wdyZwUVRhAJ9dFi8QweQyI/IK7SIzs1JDJbPSoszuAhQsSpEU1EoLS4vKisrKyorK7stuLTO777Jfh3bTfRfZZWXHf95++5idfcCuUlnN1PPPznzv+t4313tvvlf7UvTnMLLuc1j7DRr8in1soi/N2tdnOK+JG/15XftSbOe1K222oWXObx6OUGXLtLJkLtmdSn5W4Cyr0JfkH2dd7h/j+ymunfq26BVss4/SbceAnV6bVHXaVUzc3lLHP+X4ChV/WqDxOrInjdN4fZis4m+i1+2fpX4vjevQeJ3QdjRAlW2qr681zBe6ZmSofV3lezKfVaR+n+jjmkHf/V5qDuyHpLtGlSM/4Lqe6bl5dep4bWCY9Xhc+0CHoJ8WFMBZWTmDf3uLfp5UcscGMpmXursvi9L0sC7iY6Gf/U9b78cF9PcQK1Q5vmIMZYGq22rK8KzEbSxDgdJFmtTlCFX3XpzHbZk969c+TErUfr9uo13kfEyTdf+nquOPxg3yf2cNoAwddNvmN/pmUjLTra7iByVZpbHEHyCVAVY6Yzf5frucX5LeYlXO0wJh3zKIPfyu0pmmv32oVOkM9udYKf5G+WP0NX2s0sPWuuxTX7V/p+n0Vqj448x6kzxuVXEC/A7WN5jnI/7Geu6pjr3FsftV2Wdqe+QYjz2Nc9yXqeNVgZOtsQ49VejyrlP1myTneDA+jaTnaXdRZTmM61aWLvNktW8IJRzgmI85TX9j977K86W43tjLAb4eWJhff5v3sTpWEGgsyzCtq24qXfIRXQ1WZZvpv80q8Zny7ir6Whs8h/xtKMMivsq8yZ+g8qsnvxtUfuc4bHCMXT1tJ6NU3Da6DIly7Q3pb4g6vr+SCM0vP1Dtq487h3t0d2S2RO8pmcrnDf4Mw8OtEvog01fCVoQ+jr9v4vgdnYP8kUzfIrwtlKDkqzm+0BUWS9g6NfhssHUL3+c9q/RnlZaXBH/f9WrE93rcq/99zw7OZ4G1nczP6UWrjM8ClRMGNv2cXk4cx3M6aRif09kf23N60aron9OLVsX2nF60Kvp7fNGq6O/xRauie04vWhX9/bxoVWz3c+SbfU5/Z1V0z+l3r4r+Ob0SWedz+on8dj+nd870ntONz+n/8zlXGe/b+3fPXfX6KSclnnNHYuUb5/a8pJc352pjnXO1Ro2PS3+A3EMaCJ0IcxxrMHeAvWFnmAM3g33gQNgXjoZbwX3hDnA/+X2wzHeaDbeDc2EurBG5M+H28CrYDy6S/Wtghl/eZ+Q9twHmERLZz6bW9E2CY2BfeADMhYfBXeHhcDg8Co6CR8NxsAxOgcfCk+FEeAGcBK+H5XAZnAyfgRVwNZwC34CV8GdYBS2ZdxQPZ8Dh8AS4BzwRHg1nwolwFqyGJ8FLxW/PYljN/8/DuXAr8d8zAJ4JZ8nvOfBseDU8B94DL4aPwgVwJbwEfgwvg+vg5bBzHLYCc2EdHA6vhofARbAcXgfnwBtgDbwRXgpvhjfB2+At8Ha4FC6GL8K74LuS/s9wLkwOSL7wApgO58MecCncFS6De8MH4ZFwOTwOqnlUcAU8Ez4ML4CPwIXwUXg1fAyK3XJ/bNpuB4rdDha73U3sNk/sdqjY7TCx273EboeJ3eaL3Y4Qu90D1ojcmXCk2O2ecJHsH+TNK/HmlXjzSmKaV9LtHNZOJpSc480V8TZv8zZv87Z///b3jf8=
*/