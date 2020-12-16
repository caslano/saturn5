// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_CONCEPTS_HPP_INCLUDED
#define BOOST_IOSTREAMS_CONCEPTS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // BOOST_MSVC
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/default_arg.hpp>
#include <boost/iostreams/detail/ios.hpp>  // openmode.
#include <boost/iostreams/positioning.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams {

//--------------Definitions of helper templates for device concepts-----------//

template<typename Mode, typename Ch = char>
struct device {
    typedef Ch char_type;
    struct category
        : Mode,
          device_tag,
          closable_tag,
          localizable_tag
        { };

    void close()
    {
        using namespace detail;
        BOOST_STATIC_ASSERT((!is_convertible<Mode, two_sequence>::value));
    }

    void close(BOOST_IOS::openmode)
    {
        using namespace detail;
        BOOST_STATIC_ASSERT((is_convertible<Mode, two_sequence>::value));
    }

    template<typename Locale>
    void imbue(const Locale&) { }
};

template<typename Mode, typename Ch = wchar_t>
struct wdevice : device<Mode, Ch> { };

typedef device<input>    source;
typedef wdevice<input>   wsource;
typedef device<output>   sink;
typedef wdevice<output>  wsink;

//--------------Definitions of helper templates for simple filter concepts----//

template<typename Mode, typename Ch = char>
struct filter {
    typedef Ch char_type;
    struct category
        : Mode,
          filter_tag,
          closable_tag,
          localizable_tag
        { };

    template<typename Device>
    void close(Device&)
    {
        using namespace detail;
        BOOST_STATIC_ASSERT((!is_convertible<Mode, two_sequence>::value));
        BOOST_STATIC_ASSERT((!is_convertible<Mode, dual_use>::value));
    }

    template<typename Device>
    void close(Device&, BOOST_IOS::openmode)
    {
        using namespace detail;
        BOOST_STATIC_ASSERT(
            (is_convertible<Mode, two_sequence>::value) ||
            (is_convertible<Mode, dual_use>::value)
        );
    }

    template<typename Locale>
    void imbue(const Locale&) { }
};

template<typename Mode, typename Ch = wchar_t>
struct wfilter : filter<Mode, Ch> { };

typedef filter<input>      input_filter;
typedef wfilter<input>     input_wfilter;
typedef filter<output>     output_filter;
typedef wfilter<output>    output_wfilter;
typedef filter<seekable>   seekable_filter;
typedef wfilter<seekable>  seekable_wfilter;
typedef filter<dual_use>   dual_use_filter;
typedef wfilter<dual_use>  dual_use_wfilter;
        
//------Definitions of helper templates for multi-character filter cncepts----//

template<typename Mode, typename Ch = char>
struct multichar_filter : filter<Mode, Ch> {
    struct category : filter<Mode, Ch>::category, multichar_tag { };
};

template<typename Mode, typename Ch = wchar_t>
struct multichar_wfilter : multichar_filter<Mode, Ch> { };

typedef multichar_filter<input>      multichar_input_filter;
typedef multichar_wfilter<input>     multichar_input_wfilter;
typedef multichar_filter<output>     multichar_output_filter;
typedef multichar_wfilter<output>    multichar_output_wfilter;
typedef multichar_filter<dual_use>   multichar_dual_use_filter;
typedef multichar_wfilter<dual_use>  multichar_dual_use_wfilter;

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_CONCEPTS_HPP_INCLUDED

/* concepts.hpp
4/CmP+dtP2WgOT8uXsbeOq+IThiJO5UNqK/PiQz1JWO895zmF3dW5rIYQXUnRS2HWroXq2hnS/NxHuFycVl+SqxSFpvS299I05tUBofVULFD1fupwZSmUhCXwuUW8nab3k8NoXrxviNUmmnX68rRJZR+z2Gxya33AR8jTO6TjXoSQ+me6P+YmCt/qGxVZjpksdCRKO5xPis/4Lku9fG3F6gnIdzX6fViBvo7vf94j56xyqbXpZoUvl2+kcZ0o12UIr9OEc5pPkR+v/OECYc92o70cbrfo3SvtgWjjw7nNDelNNe3VRen1FAb1mRyundSmAc9X8tT5Vr2K3JXV19JbytfUPhvIvVh6LH7GOO1bRR+ebgHUxvIQryvkt9s6hfHW/bj/YyyeoDa9253sHjdrcf5PsqrX5AP+41y6kJuwZT/ejmtomdPlR8WpwzZqxeFN92D+CBWHdDfVHOHc1x3UrzKeCbIs2wLnb3k/O9OKmtjrGKHKP6xK4TruJ6GgxLqOadzAj3rumqq97XN9f4vFG64raR4FbrZhTgHdSneFnOFvzJfvKc8IUap80VljndrqueZajxWF5zDSoMV0lMiWZ4ngpWZ4l1lgfHOHE1h3pdn7FpfbzsUxx72ThipnxEtsdNTG1EKq8/flDuLiUpl8b3SS7ylVhdV8U7YZetsjC3aUj5uk8eJ6tAZd4IeuIooL/emcenaIu4tEaKPUX/nejBt7HU033qwaAnjvXV4rnSkesCzifVS1v9YOs7xWbuFWNfUntyHr30hZ8PaTglDpTkDJweM3X/r1nHd7vVaxd2nobB1UJdN63pQYUUEz405+O8wY48Ensvm+bOIfHskxPNZhw3BxmAj8D7+fT//7si/n+bfC01ndjUB14N3m9YgJc01ncFnXoPEaz9oRGRag9SX/Xdn/+Y1SKG8xiKM12aE8xlkJXntCCx9sx1tXgN1k+d34Od3BDl/eI7OOn+acf604vxpDd7Hv+/n3x3599Pab86fNpw/bTl/2vPzDupzTTxHJviZe/h5d0veNVJNQTefaepPZ5ryWjL+hrwlWJLPLq3GZ5k21J4HtuezSweBHfgsxa589nMyuBTsxWetpoJv8O9LfLb0NXb/B7t/L3nd/w5q7ldAzX2P7HXfD8Kdy5PnZwopz4pcnpW4PGO4PCtzedbk8qxlrN3h+RLTXI157U5DPkO7EedLY30tGs0ZcD6z3yjYc/z3LxyPX0GaXub7FT6r3AmW5zVwlfjb/8qgH1gVDADr8Nq4Brw2rjGviWsNluc9BeqaznDtz9/8Z/GauWywHJfHXeBKPpN3NVgVXMdn827is3k3g7FcbrXAt8B48BN+zn5+Dp8dzfIuy/75zo6+wvmuwn8G5+MjnH8eyVsPl4HN+Czu5mB38F7wY7AVOELx1rdSKibcwAQwEXwPvB+8BHYEu6Ehdgb/DnYBK9q99TEO7AbOBFPAGAfG/WBXUKtfb4J9tPvRB/YDfwLTwMdckGo1f2ggw8CyHrwNwVxwBNgLL5qRYCIazigQAwqRoeUbOBrM1PYTAtsiX8aCPcBx4GDwQXACOF7LD3CC9jxwIvg0OAlcCz4Efgo+As5FvmWdUI31RBm8bsi8Tug07BxeB5SQb33PdNManVkIZ5FpDU5avvU1y3B9M+xe2HOwzpP4KgE2ATYFdjzsvJO+tTP/jebO6P/j0gZlZmkrAP6Q/l/T9QeUvLHPvx+/y/C+Qnh4f4E/aTrM0fp8cxxrfYSl3qcEmDVG87vUYq6Zw+G5ux95nlqX+T+na40kS/3m6ALzxobM+RVdqyGZ5nON8fZhulZJyqevMeY5R1Bcnzd0KYElYW+BLuVHC10=
*/