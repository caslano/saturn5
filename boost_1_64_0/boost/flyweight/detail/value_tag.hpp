/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_VALUE_TAG_HPP
#define BOOST_FLYWEIGHT_DETAIL_VALUE_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

namespace detail{

/* Three ways to indicate that a given class T is a value policy:
 *   1. Make it derived from value_marker.
 *   2. Specialize is_value to evaluate to boost::mpl::true_.
 *   3. Pass it as value<T> when defining a flyweight type.
 *
 * For the time being the interface of value policies is not public.
 */

struct value_marker{};

template<typename T>
struct is_value:is_base_and_derived<value_marker,T>
{};

template<typename T=parameter::void_>
struct value:parameter::template_keyword<value<>,T>
{};

} /* namespace flyweights::detail */

} /* namespace flyweights */

} /* namespace boost */

#endif

/* value_tag.hpp
GrkKNhyN9FjBO7QC4vJG7eI6jyHaZVWcRoqijNDY0TJXxTo0DjnfBhz5DwAlZErD9gGx/OxtDKh8FWB5+W4ulsCR199YAMINuNWxJ12t4uB6kt8POGIxuGrutR5cM5eV0Fdjl5n7avQyKf/8Bn01CB5pNoa8o4cFV0t+gbx1MZgXQ3kxR8zD7cq7aLilRoUMtxjca3Vx0T3+VUaZ5n5k9Bli9M7DyGiqkdHWH1gz+vTSEhh9dKmZ0ZlLBaMPnANm7mbMOCBb3n0epD3zI0lvzLp6Yh38AxPBJryo6paizbm3mOHI1OWQLAKbvmYe39kW43slje8Zh/Txffo14/iethPKGIbPKmruPof48Kl81v7weZnHbz5kMXw+e8+6Vbs/X0KrZj1vbtUWz4tWTYdxTQ20Cds3KTr8h5pt50PFXtFGVwz9ULMj/FArnw9ywuoBYazHHmSDbjM1z5lPLAbd5j3WzdPwuRKap+pz5uap+JxonjL4Bf2KLg7vdimf0bZPzJ/R2dvoM3rfafEZwfejkXY5186Mup1GXPIn+oh76BXTjLq0tBmVCOgOBGyJUXorj8P0KnT0QvcZfdzdo/ai2DiCTbP7mHE2Evzv8hc/2W4yfxb7qfnaHeCfRfC0/c/iAPV78GOLz2LHLut+b/FMCf1e+xlzv1d7RvR7OTjSYIF0AmzMFVPdU1jdC4x154Wpe92SEupeusRc99NLRN3zfoa60VsIN4MdixR8ThQ4rbjftdOaglYlUVA3hIIakgIPUBCIpdsdGRRlqJbeJ27tR7/SbdRD5LBhlJscNpyCbQ+aPrn/3iX+/fP3T4Q/ii792CFFf5/3gj39/cpDZv39lg8i0N/fech8/nGiVP+Zcfus7YdTCZd27xrFPrHt4lLxNUB8Jv9nBwlVBqJC/2ffFZfuv2EJB+ql1r9+kR37yFs5aAVeX4XviiPxt1aPg9+32tr/gVYcmT+FA58QvinW+MpoxbbvAxVyVJ+uMvszeOGbYhv+EHpy+LMh8MMFvLk//XuV/syzvP9+QDHaozUK9soyPjP4T4EhoflgqVMz8t2QcwvmXMMWQcgp/bjEMl7KGKxf9dezFvvb7K8nm5bhCvvkMjxPLsOd32bb/LHhHYWTWr2XSxyG/EZGNXrWzS7hnHx2cmVoMt1DzVQ3C+FA1lt6UKzXiynW7s9olrCcpKvfP1ABexJgbXnhRAIPFMDrZbzdPGKv5V5k73Yje7ds4Q2sihj7ICychXkh4HgHczCRhIvNTwrh4pVvQbjo7v9SXA0hI6Hm8hiP1OV9iZIVHyAlTxopObwZxRO6V5LAgw5vw7b/P4lDos5/H9Gn4ntPnf+etDP/fLWfQNsiKPo/9tuY79YgkPR//Yyt8+fxBKP4vzheHPl5LUPVnFBBx23bQGeaXuj76045uZn8mzBjSO9IvrycogQasnWgm6lE3DvSmNpDKSfeFSlkiZxT5OLj/E2B9qO3DUUagoE+FTn8vsC7VhaR7s/mvssPWC/G9ljMb++FWf8+pE48v17t/yds9f8+An1nPe//byJaf5Zx8KkAbuX/8nP768W1HFXb9SH+byQW8/r9vvF+0W3wXnJ8hp/3skrkmZfhIHqI8aJgWe5KbQQd99HU3INmjA/el1PzXD3+wUY2NdcoLQB8JxnDYas5APxAixgOCXIC4ye7fYiGnoyGkUYa0jZanOzOnRfuwHPKPMOB56R5Yv68V4PtYWMnnYgIf33VD3N9sJ7o0WJ5Yj6/Zu3mNwJHK+c4S96zIPW+NyxI/XpuOFIPzjWQ+vFcQeoOGLL+ycxH3QemI1HliKbGexY99vMGXCXk6eYQ7kd5kPSjLEcDrTzIO7M=
*/